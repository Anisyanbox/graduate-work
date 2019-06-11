#include "keyboard_events.h"
#include "btn_adapter.h"
#include "camera.h"
#include "lcd.h"
#include "hal_1967VN034R1.h"
#include "gui_func.h"
#include "audio.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static int curr_lcd_bright = 100;

// -----------------------------------------------------------------------------
static void EventHandler(BtnChar_t c) {
  static char buffer[10] = {0};

  sprintf(buffer, "%c", c);
  HAL_UART_Send(LX_UART1, buffer, strlen((const char*)buffer));
  return;
}

// -----------------------------------------------------------------------------
static void LeftBtnEventHandler(BtnChar_t c) {
  CameraStopShowVideo(GuiDrawMainWindow);
}

// -----------------------------------------------------------------------------
static void RightBtnEventHandler(BtnChar_t c) {
  CameraStartVideo();
}

// -----------------------------------------------------------------------------
static void UpBtnEventHandler(BtnChar_t c) {
  curr_lcd_bright += 20;
  if (curr_lcd_bright > 100) {
    curr_lcd_bright = 100;
  }
  LcdSetBrightness((unsigned int)curr_lcd_bright);
}

// -----------------------------------------------------------------------------
static void DownBtnEventHandler(BtnChar_t c) {
  curr_lcd_bright -= 20;
  if (curr_lcd_bright < 0) {
    curr_lcd_bright = 0;
  }
  LcdSetBrightness((unsigned int)curr_lcd_bright);
}

// -----------------------------------------------------------------------------
static void SB1EventHandler(BtnChar_t c) {
  AudioVolumeSet(100);
  AudioGenerateSin(1000);
}

// -----------------------------------------------------------------------------
static void SB2EventHandler(BtnChar_t c) {
  AudioStopPlay();
}

// -----------------------------------------------------------------------------
KeyboardInitStat_t KeyboardInit(void) {
  /* low level initialization and thread create */
  if (BtnInit() != 0) {
    return KEYBOARD_INIT_FALSE;
  }

  /* Subscribe handlers for event */
  BtnSubscribeSyncEventHandler(BTN_SB1_ID, PRESS_EVNT, SB1EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB2_ID, PRESS_EVNT, SB2EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB3_ID, PRESS_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB4_ID, RELEASE_EVNT, LeftBtnEventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB5_ID, PRESS_EVNT, UpBtnEventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB6_ID, RELEASE_EVNT, RightBtnEventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB7_ID, PRESS_EVNT, DownBtnEventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB8_ID, PRESS_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB9_ID, PRESS_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB10_ID, PRESS_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB11_ID, RELEASE_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB12_ID, RELEASE_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB13_ID, RELEASE_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB14_ID, RELEASE_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB15_ID, BOTH_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB16_ID, BOTH_EVNT, EventHandler);
  return KEYBOARD_INIT;
}
