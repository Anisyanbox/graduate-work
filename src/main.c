#include <stdbool.h>
#include <stdint.h>
#include <sysreg.h>
#include <stdio.h>
#include <builtins.h>

#include "def1967VN034R1.h"
#include "clock.h"
#include "reset_reason.h"
#include "interrupt.h"
#include "rtc.h"
#include "ext_bus.h"
#include "lcd_controller.h"
#include "cam_controller.h"
#include "audio_controller.h"

#include "main.h"
#include "led_flag.h"
#include "uart.h"
#include "pthread.h"
#include "stupid_delay.h"
#include "video_buffer.h"
#include "touch_events.h"
#include "keyboard_events.h"
#include "gui_func.h"

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

      case FRAME_BUF_INIT_ERROR:
      break;

      case TOUCH_INIT_ERROR:
      break;

      case AUDIO_INIT_ERROR:
      break;

      default:
      break;
    }
    StupidDelayMs(1000);
  }
}

// -----------------------------------------------------------------------------
static void ResetErrHardwareFlag(void) {
  int stat = __builtin_sysreg_read(__SYSTATCL);
  long long dmastat = __builtin_mem_read2((volatile long long *)base_DMASTATCL);
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
  if (VideoBufferInit() != FRAME_BUF_INIT) {
    ErrorHandler(FRAME_BUF_INIT_ERROR);
  }
  LcdControllerInit();
  if (AudioControllerInit() != AUDIO_INIT) {
    ErrorHandler(AUDIO_INIT_ERROR);
  }
  if (CamControllerInit() != CAMERA_INIT) {
    ErrorHandler(CAMERA_INIT_ERROR);
  }
  if (UartInit() != UART_INIT) {
    ErrorHandler(UART_INIT_ERROR);
  }
  if (LedFlagInit() != LED_INIT) {
    ErrorHandler(LED_INIT_ERROR);
  }
  if (KeyboardInit() != KEYBOARD_INIT) {
    ErrorHandler(KEYBOARD_INIT_ERROR);
  }
  if (TouchInit() != TOUCH_INIT) {
    ErrorHandler(TOUCH_INIT_ERROR);
  }
  InterruptInit();
  InterruptEnableGlobal();
}

// -----------------------------------------------------------------------------
int main(void) {
  SystemInit();
  StupidDelayMs(100);
  GuiDrawMainWindow();
  pthread_exit(NULL);
}
