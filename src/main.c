#include <stdbool.h>
#include <stdint.h>
#include "clock.h"
#include "main.h"
#include "led_flag.h"
#include "reset_reason.h"
#include "interrupt.h"
#include "sysreg.h"
#include "rtc.h"
#include "uart.h"

// -----------------------------------------------------------------------------
static void SystemInitError(ErrFlags err) {
  (void)err;
  while (true);
}

// -----------------------------------------------------------------------------
static void SystemInit(void) {
  /* ====== */
  RstRsnSave();
  
  /* ====== */
  ClockInit();
  
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
  IntInit();
}

// -----------------------------------------------------------------------------
int main(void) {
  SystemInit();
}
