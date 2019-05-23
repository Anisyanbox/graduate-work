#include <stdbool.h>
#include <stdint.h>

#include "clock.h"
#include "reset_reason.h"
#include "interrupt.h"
#include "rtc.h"
#include "sdram.h"

#include "main.h"
#include "led_flag.h"
#include "uart.h"
#include "keyboard.h"

// -----------------------------------------------------------------------------
static void SystemInitError(ErrFlags err) {
  (void)err;
  while (true);
}

// -----------------------------------------------------------------------------
static void SystemInit(void) {
  /* ====== */
  InterruptDisableGlobal();

  /* ====== */
  RstRsnSave();
  
  /* ====== */
  ClockInit();

  /* ====== */
  SdramControllerInit();
  
  /* ====== */
  RtcInit();
  
  /* ====== */
  if (UartInit() != UART_INIT) {
    SystemInitError(UART_INIT_ERROR);
  }

  /* ====== */
  if (LedFlagInit() != LED_INIT) {
    SystemInitError(LED_INIT_ERROR);
  }

  /* ====== */
  if (KeyboardInit() != KEYBOARD_INIT) {
    SystemInitError(KEYBOARD_INIT_ERROR);
  }

  /* ====== */
  InterruptInit();
  InterruptEnableGlobal();
}

// -----------------------------------------------------------------------------
int main(void) {
  SystemInit();
}
