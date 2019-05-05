#include <stdbool.h>
#include <sysreg.h>
#include "led_flag.h"
#include "hal_1967VN034R1.h"
#include "stupid_delay.h"
#include "pthread.h"

// -----------------------------------------------------------------------------
static void FlagPinsOutModeEn(LedFlagType_t led) {
  __builtin_sysreg_write(__FLAGREGST, (const int)led);
}

// -----------------------------------------------------------------------------
static void * LedFlag0Thread(void * args) {
  (void)args;

  while (true) {
    LedOn(LED_ALL_FLAGS);
    StupidDelayMs((uint32_t)500);
    LedOff(LED_ALL_FLAGS);
    StupidDelayMs((uint32_t)500);
  }
}

// -----------------------------------------------------------------------------
void LedFlagInit(void) {
  static pthread_t led0_handl;

  HAL_SYS_FlagEnable();
  FlagPinsOutModeEn(LED_ALL_FLAGS);
  
  pthread_create(&led0_handl, NULL, LedFlag0Thread, NULL);
}

// -----------------------------------------------------------------------------
void LedOn(LedFlagType_t led) {
  __builtin_sysreg_write(__FLAGREGST, (const int)(led << 4));
}

// -----------------------------------------------------------------------------
void LedOff(LedFlagType_t led) {
  unsigned int val = ~(led << 4);

  __builtin_sysreg_write(__FLAGREGCL, (const int)val);
}
