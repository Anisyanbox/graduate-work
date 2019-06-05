#include <stdbool.h>
#include <stdint.h>
#include <sysreg.h>
#include <stdio.h>

#include "hal_1967VN034R1.h"
#include "clock.h"
#include "reset_reason.h"
#include "interrupt.h"
#include "rtc.h"
#include "ext_bus.h"
#include "lcd_controller.h"
#include "cam_controller.h"

#include "main.h"
#include "led_flag.h"
#include "uart.h"
#include "keyboard.h"
#include "pthread.h"
#include "stupid_delay.h"

// -----------------------------------------------------------------------------
static void ErrorHandler(ErrFlags err) {
  while (true) {
    switch (err) {
      case UART_INIT_ERROR:
      break;

      case LED_INIT_ERROR:
      break;

      case KEYBOARD_INIT_ERROR:
      break;

      case CAMERA_INIT_ERROR:
      break;

      default:
      break;
    }
    StupidDelayMs(1000);
  }
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
  CamControllerInit();
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
  StupidDelayMs(500);
  pthread_exit(NULL);
}
