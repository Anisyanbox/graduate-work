#include <stdbool.h>
#include <stdint.h>
#include <sysreg.h>

#include "clock.h"
#include "reset_reason.h"
#include "interrupt.h"
#include "rtc.h"
#include "lcd_controller.h"

#include "main.h"
#include "led_flag.h"
#include "uart.h"
#include "keyboard.h"
#include "ext_bus.h"

// -----------------------------------------------------------------------------
static void ErrorHandler(ErrFlags err) {
  (void)err;
  while (true);
}

// -----------------------------------------------------------------------------
static void ResetErrHardwareFlag(void) {
  uint32_t tmp = __builtin_sysreg_read(__SYSTATCL);
}

// -----------------------------------------------------------------------------
static void SystemInit(void) {
  ResetErrHardwareFlag();
  InterruptDisableGlobal();
  RstRsnSave();
  ExtBusInit();
  ClockInit();
  SramInit();
  SdramInit();
  RtcInit();
  LcdControllerInit();
  if (UartInit() != UART_INIT) {
    ErrorHandler(UART_INIT_ERROR);
  }
  if (LedFlagInit() != LED_INIT) {
    ErrorHandler(LED_INIT_ERROR);
  }
  if (KeyboardInit() != KEYBOARD_INIT) {
    ErrorHandler(KEYBOARD_INIT_ERROR);
  }
  InterruptInit();
  InterruptEnableGlobal();
}

// -----------------------------------------------------------------------------
int main(void) {
  SystemInit();
}
