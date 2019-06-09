#include "gui_func.h"
#include "pictures.h"
#include "video_buffer.h"
#include "lcd.h"
#include "pictures.h"
#include <stdint.h>

#define VIDEO_ICON_START_X_PIXEL        45
#define VIDEO_ICON_START_Y_PIXEL        83
#define MUSIC_ICON_START_X_PIXEL        190
#define MUSIC_ICON_START_Y_PIXEL        83
#define MICROPHONE_ICON_START_X_PIXEL   335
#define MICROPHONE_ICON_START_Y_PIXEL   83

// -----------------------------------------------------------------------------
void GuiDrawMainWindow(void) {
  uint32_t * video_buf = GetVideoBufferAddr();

  // clear lcd
  for (uint32_t i = 0; i < GetVideoBufferSizeInWords(); ++i) {
    *(video_buf + i) = 0xffffffff;
  }
  
  // draw video icon
  LcdDrawIcon(VIDEO_ICON_START_X_PIXEL,
              VIDEO_ICON_START_Y_PIXEL, 
              GetVideoIconArray);

  // Draw music icon
  LcdDrawIcon(MUSIC_ICON_START_X_PIXEL,
              MUSIC_ICON_START_Y_PIXEL, 
              GetMusicIconArray);

  // Draw microphone icon
  LcdDrawIcon(MICROPHONE_ICON_START_X_PIXEL,
              MICROPHONE_ICON_START_Y_PIXEL, 
              GetMicrophoneIconArray);
}
