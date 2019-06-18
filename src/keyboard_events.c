#include "keyboard_events.h"
#include "btn_adapter.h"
#include "camera.h"
#include "lcd.h"
#include "hal_1967VN034R1.h"
#include "audio_controller.h"
#include "audio_effects.h"
#include "audio_buffer.h"
#include "gui_func.h"
#include "audio.h"
#include "aic23b.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// -----------------------------------------------------------------------------
static void EventHandler(BtnChar_t c) {
  static char buffer[10] = {0};

  sprintf(buffer, "%c", c);
  HAL_UART_Send(LX_UART1, buffer, strlen((const char*)buffer));
  return;
}

// -----------------------------------------------------------------------------
static short curr_volume = 50;
static void UpBtnEvent(BtnChar_t c) {
  curr_volume += 5;
  if (curr_volume > 80) {
    curr_volume = 80;
  }
  AudioPlayVolumeSet((unsigned short)curr_volume);
}

static void DownBtnEvent(BtnChar_t c) {
  curr_volume -= 5;
  if (curr_volume < 30) {
    curr_volume = 30;
  }
  AudioPlayVolumeSet((unsigned short)curr_volume);
}

// -----------------------------------------------------------------------------
static void SB1Event(BtnChar_t c) {
  AudioStopPlay();
  AudioPlayTrack((unsigned int * )AudioGeneratePureSinSignal(32767, 440),
                  GetAudioOutBufferSizeInWords(),
                  NULL,
                  true);
}

static void SB2Event(BtnChar_t c) {
  AudioStopPlay();
  AudioPlayTrack((unsigned int * )AudioGenerateChangingSinSignal(220,
                                                                 880,
                                                                 32767, 
                                                                 NULL),
                  GetAudioOutBufferSizeInWords(),
                  NULL,
                  true);
}

static void SB3Event(BtnChar_t c) {
  unsigned int * signal = (unsigned int * )AudioGenerateChangingSinSignal(220,
                                                                          880,
                                                                          32767, 
                                                                          NULL);

  AudioStopPlay();
  AudioPlayEchoEffect(signal, GetAudioOutBufferSizeInWords(), 5000);
}

// -----------------------------------------------------------------------------
KeyboardInitStat_t KeyboardInit(void) {
  /* low level initialization and thread create */
  if (BtnInit() != 0) {
    return KEYBOARD_INIT_FALSE;
  }

  /* Subscribe handlers for event */
  BtnSubscribeSyncEventHandler(BTN_SB1_ID, PRESS_EVNT, SB1Event);
  BtnSubscribeSyncEventHandler(BTN_SB2_ID, PRESS_EVNT, SB2Event);
  BtnSubscribeSyncEventHandler(BTN_SB3_ID, PRESS_EVNT, SB3Event);
  BtnSubscribeSyncEventHandler(BTN_SB4_ID, RELEASE_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB5_ID, PRESS_EVNT, UpBtnEvent);
  BtnSubscribeSyncEventHandler(BTN_SB6_ID, RELEASE_EVNT, EventHandler);
  BtnSubscribeSyncEventHandler(BTN_SB7_ID, PRESS_EVNT, DownBtnEvent);
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
