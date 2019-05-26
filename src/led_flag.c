#include <stdbool.h>
#include <sysreg.h>
#include "led_flag.h"
#include "led_flag_adapter.h"
#include "delay.h"
#include "pthread.h"
#include "main.h"

#define CNT_LEDS_ONBOARD                (4)
#define SLEEP_LED_THREAD_MS             (10U)
#define LED_FLAG_THREAD_PRIORITY        MAIN_THREAD_NORMAL_PRIO

typedef enum {
  LED_FLAG_0 = ((unsigned int)(1 << 0)),
  LED_FLAG_1 = ((unsigned int)(1 << 1)),
  LED_FLAG_2 = ((unsigned int)(1 << 2)),
  LED_FLAG_3 = ((unsigned int)(1 << 3)),
} LedFlagType_t;

typedef enum {
  LED_BLINKY,
  LED_STATIC_ON,
  LED_STATIC_OFF
} LedFlagMode_t;

typedef struct {
  LedFlagType_t flag;
  LedFlagMode_t mode;
  unsigned int cur_delay_phase;
  unsigned int delay_on;
  unsigned int delay_off;
  void (*led_on_func_ptr)(void);
  void (*led_off_func_ptr)(void);
} Led_t;

// -----------------------------------------------------------------------------
static void FlagPinSet(LedFlagType_t flag) {
  __builtin_sysreg_write(__FLAGREGST, (const int)(flag << 4));
}

// -----------------------------------------------------------------------------
static void FlagPinReset(LedFlagType_t flag) {
  unsigned int val = ~(flag << 4);

  __builtin_sysreg_write(__FLAGREGCL, (const int)val);
}

// -----------------------------------------------------------------------------
static void FlagOutModeEn(LedFlagType_t flag) {
  __builtin_sysreg_write(__FLAGREGST, (const int)flag);
}

// -----------------------------------------------------------------------------
static void Flag0On(void) {
  FlagPinReset(LED_FLAG_0);
}

static void Flag0Off(void) {
  FlagPinSet(LED_FLAG_0);
}

// -----------------------------------------------------------------------------
static void Flag1On(void) {
  FlagPinReset(LED_FLAG_1);
}

static void Flag1Off(void) {
  FlagPinSet(LED_FLAG_1);
}

// -----------------------------------------------------------------------------
static void Flag2On(void) {
  FlagPinReset(LED_FLAG_2);
}

static void Flag2Off(void) {
  FlagPinSet(LED_FLAG_2);
}

// -----------------------------------------------------------------------------
static void Flag3On(void) {
  FlagPinReset(LED_FLAG_3);
}

static void Flag3Off(void) {
  FlagPinSet(LED_FLAG_3);
}

// -----------------------------------------------------------------------------
static Led_t leds_table[CNT_LEDS_ONBOARD] = {
  {LED_FLAG_0, LED_BLINKY, 0U, 100U, 100U, Flag0On, Flag0Off},
  {LED_FLAG_1, LED_BLINKY, 0U, 200U, 200U, Flag1On, Flag1Off},
  {LED_FLAG_2, LED_BLINKY, 0U, 400U, 400U, Flag2On, Flag2Off},
  {LED_FLAG_3, LED_BLINKY, 0U, 800U, 800U, Flag3On, Flag3Off}
};

// -----------------------------------------------------------------------------
static void * LedFlagThread(void * args) {
  (void)args;
 
  while (true) {   
    int i;
    for (i = 0; i < CNT_LEDS_ONBOARD; ++i) {
      unsigned int period = leds_table[i].delay_on + leds_table[i].delay_off;

      switch (leds_table[i].mode) {
        case LED_BLINKY:
          leds_table[i].cur_delay_phase += SLEEP_LED_THREAD_MS;

          if (leds_table[i].cur_delay_phase <= leds_table[i].delay_on) {
            leds_table[i].led_on_func_ptr();
          } else if (leds_table[i].cur_delay_phase <= period) {
            leds_table[i].led_off_func_ptr();
          } else {
            leds_table[i].cur_delay_phase = 0;
          }
          break;

        case LED_STATIC_ON:
          leds_table[i].led_on_func_ptr();
          leds_table[i].cur_delay_phase = 0;
          break;

        case LED_STATIC_OFF:
          leds_table[i].led_off_func_ptr();
          leds_table[i].cur_delay_phase = 0;
          break;

        default:
          break;
      }
    }
    DelayMs(SLEEP_LED_THREAD_MS);
  }
}

// -----------------------------------------------------------------------------
LedInitStat_t LedFlagInit(void) {
  static pthread_t led_thread_handl;
  pthread_attr_t led_flag_attr;
  sched_param_t led_flag_thread_prio;

  HAL_SYS_FlagEnable();
  __builtin_sysreg_write(__FLAGREGST, 0xFF);
  FlagOutModeEn(LED_FLAG_0 | LED_FLAG_1 | LED_FLAG_2 | LED_FLAG_3);

  if (pthread_attr_init(&led_flag_attr) != 0) {
    return LED_INIT_FALSE;
  }
  led_flag_thread_prio.sched_priority = LED_FLAG_THREAD_PRIORITY;
  if (pthread_attr_setschedparam(&led_flag_attr,
                                (const sched_param_t*)&led_flag_thread_prio) != 0) {
    return LED_INIT_FALSE;
  }
  if (pthread_create(&led_thread_handl,
                    (const pthread_attr_t*)led_flag_attr,
                    LedFlagThread,
                    NULL) != 0) {
    return LED_INIT_FALSE;
  }
  if (pthread_attr_destroy(&led_flag_attr) != 0) {
    return LED_INIT_FALSE;
  }

  return LED_INIT;
}
