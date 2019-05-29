#include <stdbool.h>
#include <stdint.h>
#include "btn_adapter.h"
#include "pthread.h"
#include "main.h"
#include "delay.h"
#include "hal_1967VN034R1.h"

#define THREAD_SLEEP_MS         ((unsigned int)10)
#define SLEEP_DELAY_STEP        THREAD_SLEEP_MS
#define THREAD_PRIORITY         MAIN_THREAD_NORMAL_PRIO
#define EXT_PORT_BTN_ADR        ((unsigned int)0x383FFFFF)

// -----------------------------------------------------------------------------
typedef struct {
  bool                is_external_port_used;  // true if btn connected to PxD (ports for external bus)
  const GPIO_PinState level_when_released;    // depend on schematic
  GPIO_PortPi *       port;
  GPIO_PIN            pin;
  GPIO_PxPort         ext_port;
} BtnLowLewelOpt_t;

static BtnLowLewelOpt_t btns[BTN_CNT] = {
  [BTN_SB1_ID] = {true, GPIO_PinState_Set, LX_GPIO_PA, GPIO_PIN_0, GPIO_PxPort_D},
  [BTN_SB2_ID] = {true, GPIO_PinState_Set, LX_GPIO_PA, GPIO_PIN_1, GPIO_PxPort_D},
  [BTN_SB3_ID] = {true, GPIO_PinState_Set, LX_GPIO_PA, GPIO_PIN_2, GPIO_PxPort_D},
  [BTN_SB4_ID] = {true, GPIO_PinState_Set, LX_GPIO_PA, GPIO_PIN_12, GPIO_PxPort_D},
  [BTN_SB5_ID] = {true, GPIO_PinState_Set, LX_GPIO_PA, GPIO_PIN_10, GPIO_PxPort_D},
  [BTN_SB6_ID] = {true, GPIO_PinState_Set, LX_GPIO_PA, GPIO_PIN_14, GPIO_PxPort_D},
  [BTN_SB7_ID] = {true, GPIO_PinState_Set, LX_GPIO_PA, GPIO_PIN_15, GPIO_PxPort_D},
  [BTN_SB8_ID] = {true, GPIO_PinState_Set, LX_GPIO_PA, GPIO_PIN_3, GPIO_PxPort_D},
  [BTN_SB9_ID] = {true, GPIO_PinState_Set, LX_GPIO_PA, GPIO_PIN_4, GPIO_PxPort_D},
  [BTN_SB10_ID] = {true, GPIO_PinState_Set, LX_GPIO_PA, GPIO_PIN_5, GPIO_PxPort_D},
  [BTN_SB11_ID] = {true, GPIO_PinState_Set, LX_GPIO_PA, GPIO_PIN_6, GPIO_PxPort_D},
  [BTN_SB12_ID] = {true, GPIO_PinState_Set, LX_GPIO_PA, GPIO_PIN_7, GPIO_PxPort_D},
  [BTN_SB13_ID] = {true, GPIO_PinState_Set, LX_GPIO_PA, GPIO_PIN_8, GPIO_PxPort_D},
  [BTN_SB14_ID] = {true, GPIO_PinState_Set, LX_GPIO_PA, GPIO_PIN_11, GPIO_PxPort_D},
  [BTN_SB15_ID] = {true, GPIO_PinState_Set, LX_GPIO_PA, GPIO_PIN_9, GPIO_PxPort_D},
  [BTN_SB16_ID] = {true, GPIO_PinState_Set, LX_GPIO_PA, GPIO_PIN_13, GPIO_PxPort_D}
};

// -----------------------------------------------------------------------------
typedef enum {
  BTN_PRESSED = 0,
  BTN_RELEASED,
} BtnState_t;

typedef enum {
  BTN_ASYNC = 0,
  BTN_SYNC,
  UNKNOWN_MODE
} BtnMode_t;

typedef struct {
  BtnId_t           id;                 // own uniq id 
  BtnChar_t         character;          // ascii symbol
  BtnMode_t         mode;               // btn geterate interrupt or not
  int               pressed_delay_ms;
  int               released_delay_ms;
  int               curr_pressed_delay_ms;
  int               curr_released_delay_ms;
  EventForHandler_t event;
  void (*press_handler)(BtnChar_t c);    // event handler if mode == BTN_SYNC
  void (*release_handler)(BtnChar_t c);  // event handler if mode == BTN_SYNC
  void (*async_handler)(void);           // interrupt handler, if mode == BTN_ASYNC
} Btn_t;

static Btn_t keyboard[BTN_CNT] = {
  {BTN_SB1_ID, '1', UNKNOWN_MODE, 30, 30, 0, 0, PRESS_EVNT, NULL, NULL, NULL},
  {BTN_SB2_ID, '2', UNKNOWN_MODE, 30, 30, 0, 0, PRESS_EVNT, NULL, NULL, NULL},
  {BTN_SB3_ID, '3', UNKNOWN_MODE, 30, 30, 0, 0, PRESS_EVNT, NULL, NULL, NULL},
  {BTN_SB4_ID, '<', UNKNOWN_MODE, 30, 30, 0, 0, BOTH_EVNT, NULL, NULL, NULL},
  {BTN_SB5_ID, '^', UNKNOWN_MODE, 30, 30, 0, 0, BOTH_EVNT, NULL, NULL, NULL},
  {BTN_SB6_ID, '>', UNKNOWN_MODE, 30, 30, 0, 0, BOTH_EVNT, NULL, NULL, NULL},
  {BTN_SB7_ID, '~', UNKNOWN_MODE, 30, 30, 0, 0, BOTH_EVNT, NULL, NULL, NULL},
  {BTN_SB8_ID, '4', UNKNOWN_MODE, 30, 30, 0, 0, PRESS_EVNT, NULL, NULL, NULL},
  {BTN_SB9_ID, '5', UNKNOWN_MODE, 30, 30, 0, 0, RELEASE_EVNT, NULL, NULL, NULL},
  {BTN_SB10_ID, '6', UNKNOWN_MODE, 30, 30, 0, 0, RELEASE_EVNT, NULL, NULL, NULL},
  {BTN_SB11_ID, '7', UNKNOWN_MODE, 30, 30, 0, 0, RELEASE_EVNT, NULL, NULL, NULL},
  {BTN_SB12_ID, '8', UNKNOWN_MODE, 30, 30, 0, 0, RELEASE_EVNT, NULL, NULL, NULL},
  {BTN_SB13_ID, '9', UNKNOWN_MODE, 30, 30, 0, 0, RELEASE_EVNT, NULL, NULL, NULL},
  {BTN_SB14_ID, '#', UNKNOWN_MODE, 30, 30, 0, 0, RELEASE_EVNT, NULL, NULL, NULL},
  {BTN_SB15_ID, '0', UNKNOWN_MODE, 30, 30, 0, 0, PRESS_EVNT, NULL, NULL, NULL},
  {BTN_SB16_ID, '*', UNKNOWN_MODE, 30, 30, 0, 0, RELEASE_EVNT, NULL, NULL, NULL}
};

// -----------------------------------------------------------------------------
static BtnState_t BtnGetState(BtnId_t id) {
  GPIO_PinState st = GPIO_PinState_Reset;
  uint temp = 0;

  if (btns[id].is_external_port_used) {
    temp = (*(unsigned int* )EXT_PORT_BTN_ADR) & 0x0000FFFF;
    temp &= btns[id].pin;

    if (temp > 0) {
      st = GPIO_PinState_Set;
    }
    if (st == btns[id].level_when_released) {
      return BTN_RELEASED;
    } else {
      return BTN_PRESSED;
    }
  } else {
    if ((HAL_GPIO_ReadPin((GPIO_PortPi * const)btns[id].port, 
                          (const GPIO_PIN)btns[id].pin)) == btns[id].level_when_released) {
      return BTN_RELEASED;
    } else {
      return BTN_PRESSED;
    }
  }
}

// -----------------------------------------------------------------------------
#pragma interrupt
static void GpioIrqHandler (void) {
  for (int i = 0; i < BTN_CNT; ++i) {
    if (HAL_GPIO_InterruptCheck((GPIO_PortPi * const)btns[i].port,
                                (const uint)btns[i].pin)) {
      if (keyboard[i].async_handler != NULL) {
        keyboard[i].async_handler();
      }
      HAL_GPIO_InterruptEdgeClear((GPIO_PortPi * const)btns[i].port,
                                  (const uint)btns[i].pin);
    }
  }
}

// -----------------------------------------------------------------------------
static void * KeyboardThread(void * args) {
  static BtnState_t last_state[BTN_CNT];
  static BtnState_t curr_state[BTN_CNT];

  for (int i = 0; i < BTN_CNT; ++i) {
    last_state[i] = BtnGetState((BtnId_t)i);
    curr_state[i] = last_state[i];
  }

  while(true) {
    DelayMs(THREAD_SLEEP_MS);
    for (int i = 0; i < BTN_CNT; ++i) {
      if (keyboard[i].mode == BTN_SYNC) {
        curr_state[i] = BtnGetState((BtnId_t)i);
        if  (curr_state[i] != last_state[i]) {
          if (curr_state[i] == BTN_PRESSED) { /* PRESSED */
            keyboard[i].curr_released_delay_ms = 0;
            keyboard[i].curr_pressed_delay_ms += SLEEP_DELAY_STEP;
            if (keyboard[i].curr_pressed_delay_ms == keyboard[i].pressed_delay_ms) {
              curr_state[i] = BTN_PRESSED;
              last_state[i] = curr_state[i];
              if (keyboard[i].press_handler != NULL) {
                keyboard[i].press_handler(keyboard[i].character);
              }
            }
          } else { /* RELEASED */
            keyboard[i].curr_pressed_delay_ms = 0;
            keyboard[i].curr_released_delay_ms += SLEEP_DELAY_STEP;
            if (keyboard[i].curr_released_delay_ms == keyboard[i].released_delay_ms) {
              curr_state[i] = BTN_RELEASED;
              last_state[i] = curr_state[i];
              if (keyboard[i].release_handler != NULL) {
                keyboard[i].release_handler(keyboard[i].character);
              }
            }
          }
        }
      }
    }
  }
}

// -----------------------------------------------------------------------------
int BtnInit(void) {
  static pthread_t keyboard_thread_handl;
  pthread_attr_t keyboard_attr;
  sched_param_t keyboard_thread_prio;

  for (int i = 0; i < BTN_CNT; ++i) {
    if (btns[i].is_external_port_used) {
      asm("nop;;");
      // Not config pins for external port, because it is read with help
      // SRAM controller
    } else {
      HAL_GPIO_Init((GPIO_PortPi * const)btns[i].port,
                    (const uint)btns[i].pin,
                    (const GPIO_PinMode)GPIO_PinMode_InPU);
    }
  }
  
  HAL_Interrupt_SubscribeHandler(intGPIO, GpioIrqHandler);
  HAL_Interrupt_Enable(intGPIO);
  
  if (pthread_attr_init(&keyboard_attr) != 0) {
    return 1;
  }
  keyboard_thread_prio.sched_priority = THREAD_PRIORITY;
  if (pthread_attr_setschedparam(&keyboard_attr,
                                (const sched_param_t*)&keyboard_thread_prio) != 0) {
    return 1;
  }
  if (pthread_create(&keyboard_thread_handl, 
                    (const pthread_attr_t*)keyboard_attr, 
                    KeyboardThread, 
                    NULL) != 0) {
    return 1;
  }
  if (pthread_attr_destroy(&keyboard_attr) != 0) {
    return 1;
  }
  return 0;
}

// -----------------------------------------------------------------------------
void BtnSubscribeAsyncEventHandler(BtnId_t id_key_btn, 
                                   void (*async_handler)(void)) {
  GPIO_InterruptMode it_mode;
  
  it_mode = (btns[id_key_btn].level_when_released == GPIO_PinState_Set) ? \
            (GPIO_InterruptMode_Negedge) : (GPIO_InterruptMode_Posedge);
  if (!btns[id_key_btn].is_external_port_used) {
	  keyboard[id_key_btn].mode = BTN_ASYNC;
	  keyboard[id_key_btn].async_handler = async_handler;

    HAL_GPIO_InterruptConfig((GPIO_PortPi * const)btns[id_key_btn].port,
                             (const uint)btns[id_key_btn].pin,
                             (const GPIO_InterruptMode)it_mode);
  }
}

// -----------------------------------------------------------------------------
void BtnSubscribeSyncEventHandler(BtnId_t id_key_btn,
                                  EventForHandler_t e,
                                  void (*handler)(BtnChar_t c)) {
  // disable btn interrupts if it was enabled
  if (keyboard[id_key_btn].mode == BTN_ASYNC) {
    if (!btns[id_key_btn].is_external_port_used) {
        HAL_GPIO_InterruptConfig((GPIO_PortPi * const)btns[id_key_btn].port,
                                 (const uint)btns[id_key_btn].pin,
                                 (const GPIO_InterruptMode)GPIO_InterruptMode_Off);
    } else {
      return;
    }
  }

  keyboard[id_key_btn].mode = BTN_SYNC;
  keyboard[id_key_btn].event = e;

  switch (e) {
    case PRESS_EVNT:
      keyboard[id_key_btn].press_handler = handler;
      break;
    
    case RELEASE_EVNT:
      keyboard[id_key_btn].release_handler = handler;
      break;
    
    case BOTH_EVNT:
      keyboard[id_key_btn].press_handler = handler;
      keyboard[id_key_btn].release_handler = handler;
      break;
    
    default:
      break;
  }
}
