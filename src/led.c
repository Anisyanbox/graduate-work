#include <stdbool.h>
#include <sysreg.h>
#include "led.h"
#include "hal_1967VN034R1.h"
#include "stupid_delay.h"
#include "pthread.h"

#define LED_FLAG0_DELAY_BLINK ((uint32_t)1000)

// -----------------------------------------------------------------------------
static void * LedFlag0Thread(void * args) {
  (void)args;

  while (true) {
    __builtin_sysreg_write(__FLAGREGST, 0x01); // on FLAG0
    StupidDelayMs(LED_FLAG0_DELAY_BLINK);
    __builtin_sysreg_write(__FLAGREGCL, 0x00); // off FLAG0
    StupidDelayMs(LED_FLAG0_DELAY_BLINK);
  }
}

// -----------------------------------------------------------------------------
void LedInit(void) {
  static pthread_t led1_handl;

  HAL_SYS_FlagEnable();
  pthread_create(&led1_handl, NULL, LedFlag0Thread, NULL);
}
