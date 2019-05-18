#include <stdbool.h>
#include "keyboard.h"
#include "keyboard_adapter.h"
#include "pthread.h"
#include "delay.h"
#include "main.h"

#define THREAD_SLEEP_MS             ((unsigned int)5)
#define THREAD_PRIORITY             MAIN_THREAD_NORMAL_PRIO
#define BTN_CNT                     (16)

#define used_extertal_port          true
#define unused_extertal_port        false

typedef enum {
  BTN_PRESSED = 0,
  BTN_RELEASED
} BtnState_t;

typedef char BtnChar_t;

typedef enum {
  PRESS_EVNT = 0,
  RELEASE_EVNT,
  BOTH_EVNT
} EventForHandler_t;

typedef struct {
  GPIO_PinState level_when_released;
  bool          is_external_port_used;
  GPIO_PortPi   port;
  GPIO_PxPort   ext_port;
  GPIO_PIN      pin;
} HwBtnOptions_t;

typedef struct {
  HwBtnOptions_t hw_params;
  BtnState_t curr_state;
  BtnChar_t character;
  int pressed_delay_ms;
  int released_delay_ms;
  int curr_pressed_delay_ms;
  int curr_released_delay_ms;
  EventForHandler_t event;
  void (*press_handler)(BtnChar_t c);
  void (*release_handler)(BtnChar_t c);
} Btn_t;

// -----------------------------------------------------------------------------
static void btn_press_handler(BtnChar_t c) {
  return;
}

// -----------------------------------------------------------------------------
static void btn_release_handler(BtnChar_t c) {
  return;
}

// -----------------------------------------------------------------------------
static Btn_t keyboard[BTN_CNT] = {
  {{GPIO_PinState_Set, used_extertal_port, NULL, GPIO_PxPort_D, GPIO_PIN_9},
    BTN_RELEASED, '0', 20, 20, 0, 0, PRESS_EVNT, btn_press_handler, btn_release_handler},

  {{GPIO_PinState_Set, used_extertal_port, NULL, GPIO_PxPort_D, GPIO_PIN_0},
    BTN_RELEASED, '1', 20, 20, 0, 0, PRESS_EVNT, btn_press_handler, btn_release_handler},
    
  {{GPIO_PinState_Set, used_extertal_port, NULL, GPIO_PxPort_D, GPIO_PIN_1},
    BTN_RELEASED, '2', 20, 20, 0, 0, PRESS_EVNT, btn_press_handler, btn_release_handler},
    
  {{GPIO_PinState_Set, used_extertal_port, NULL, GPIO_PxPort_D, GPIO_PIN_2},
    BTN_RELEASED, '3', 20, 20, 0, 0, PRESS_EVNT, btn_press_handler, btn_release_handler},
    
  {{GPIO_PinState_Set, used_extertal_port, NULL, GPIO_PxPort_D, GPIO_PIN_3},
    BTN_RELEASED, '4', 20, 20, 0, 0, PRESS_EVNT, btn_press_handler, btn_release_handler},
    
  {{GPIO_PinState_Set, used_extertal_port, NULL, GPIO_PxPort_D, GPIO_PIN_4},
    BTN_RELEASED, '5', 20, 20, 0, 0, RELEASE_EVNT, btn_press_handler, btn_release_handler},
    
  {{GPIO_PinState_Set, used_extertal_port, NULL, GPIO_PxPort_D, GPIO_PIN_5},
    BTN_RELEASED, '6', 20, 20, 0, 0, RELEASE_EVNT, btn_press_handler, btn_release_handler},
    
  {{GPIO_PinState_Set, used_extertal_port, NULL, GPIO_PxPort_D, GPIO_PIN_6},
    BTN_RELEASED, '7', 20, 20, 0, 0, RELEASE_EVNT, btn_press_handler, btn_release_handler},
    
  {{GPIO_PinState_Set, used_extertal_port, NULL, GPIO_PxPort_D, GPIO_PIN_7},
    BTN_RELEASED, '8', 20, 20, 0, 0, RELEASE_EVNT, btn_press_handler, btn_release_handler},
    
  {{GPIO_PinState_Set, used_extertal_port, NULL, GPIO_PxPort_D, GPIO_PIN_8},
    BTN_RELEASED, '9', 20, 20, 0, 0, RELEASE_EVNT, btn_press_handler, btn_release_handler},
    
  {{GPIO_PinState_Set, used_extertal_port, NULL, GPIO_PxPort_D, GPIO_PIN_13},
    BTN_RELEASED, '*', 20, 20, 0, 0, RELEASE_EVNT, btn_press_handler, btn_release_handler},
    
  {{GPIO_PinState_Set, used_extertal_port, NULL, GPIO_PxPort_D, GPIO_PIN_11},
    BTN_RELEASED, '#', 20, 20, 0, 0, RELEASE_EVNT, btn_press_handler, btn_release_handler},

  {{GPIO_PinState_Set, used_extertal_port, NULL, GPIO_PxPort_D, GPIO_PIN_12},
    BTN_RELEASED, '<', 20, 20, 0, 0, BOTH_EVNT, btn_press_handler, btn_release_handler},
    
  {{GPIO_PinState_Set, used_extertal_port, NULL, GPIO_PxPort_D, GPIO_PIN_10},
    BTN_RELEASED, '^', 20, 20, 0, 0, BOTH_EVNT, btn_press_handler, btn_release_handler},
    
  {{GPIO_PinState_Set, used_extertal_port, NULL, GPIO_PxPort_D, GPIO_PIN_14},
    BTN_RELEASED, '>', 20, 20, 0, 0, BOTH_EVNT, btn_press_handler, btn_release_handler},
    
  {{GPIO_PinState_Set, used_extertal_port, NULL, GPIO_PxPort_D, GPIO_PIN_15},
    BTN_RELEASED, '~', 20, 20, 0, 0, BOTH_EVNT, btn_press_handler, btn_release_handler}
};

// -----------------------------------------------------------------------------
static void * KeyboardThread(void * args) {
  (void)args;

  while(true) {
    DelayMs(THREAD_SLEEP_MS);
  }
}

// -----------------------------------------------------------------------------
KeyboardInitStat_t KeyboardInit(void) {
  static pthread_t keyboard_thread_handl;
  pthread_attr_t keyboard_attr;
  sched_param_t keyboard_thread_prio;

  if (pthread_attr_init(&keyboard_attr) != 0) {
    return KEYBOARD_INIT_FALSE;
  }
  keyboard_thread_prio.sched_priority = THREAD_PRIORITY;
  if (pthread_attr_setschedparam(&keyboard_attr,
                                (const sched_param_t*)&keyboard_thread_prio) != 0) {
    return KEYBOARD_INIT_FALSE;
  }
  if (pthread_create(&keyboard_thread_handl, 
                    (const pthread_attr_t*)keyboard_attr, 
                    KeyboardThread, 
                    NULL) != 0) {
    return KEYBOARD_INIT_FALSE;
  }
  if (pthread_attr_destroy(&keyboard_attr) != 0) {
    return KEYBOARD_INIT_FALSE;
  }
  return KEYBOARD_INIT;
}
