#include "touch_events.h"
#include "touch_adapter.h"
#include "xpt2046.h"
#include "lcd_controller.h"
#include "lcd.h"
#include "gui_func.h"
#include "camera.h"
#include "audio.h"
#include "lcd.h"
#include "gui_func.h"
#include "video_buffer.h"
#include <string.h>

// -----------------------------------------------------------------------------
static void DrawPoint(unsigned int x, unsigned int y) {
  LcdDrawPixel(x, y, 0);
  return;
}

// -----------------------------------------------------------------------------
static void CamIconEvent(void) {
  static int press_cnt = 0;

  if (press_cnt == 0) {
    CameraStartVideo();
    press_cnt = 1;
  } else {
    CameraStopShowVideo(GuiDrawMainWindow);
    press_cnt = 0;
  }
}

// -----------------------------------------------------------------------------
static void TakePhotoEvent(void) {
  CameraTakePhoto();
}

// -----------------------------------------------------------------------------
static void MusicIconEvent(void) {
  AudioStopPlay();
}

// -----------------------------------------------------------------------------
static void ShowPhotoEvent(void) {
  CameraStopShowVideo(NULL);
  LcdDrawPhotoBuffer();
}

// -----------------------------------------------------------------------------
static void ShowMainScreenEvent(void) {
  CameraStopShowVideo(NULL);
  GuiDrawMainWindow();
}

// -----------------------------------------------------------------------------
TouchInitStat_t TouchInit(void) {
  Xpt2046LcdInfo_t lcd_info;
  TouchArea_t cam_icon;
  TouchArea_t music_icon;
  TouchArea_t take_photo_region;
  TouchArea_t show_photo_region;
  TouchArea_t return_screen_region;

  // init touch hw and thread creation
  if (TouchPanelInit() != 0) {
    return TOUCH_INIT_FALSE;
  }
  lcd_info.x_lcd_size = LcdGetWigthInPixels();
  lcd_info.y_lcd_size = LcdGetHeigthInPixels();
  lcd_info.is_xy_lcd_and_xy_touch_swap = 1;
  lcd_info.is_x_lcd_and_x_touch_diff_direction = 0;
  lcd_info.is_y_lcd_and_y_touch_diff_direction = 1;
  Xpt2046Calibrate(DrawPoint, &lcd_info);


  music_icon.p1.x = 200;
  music_icon.p1.y = 115;
  music_icon.p2.x = 270;
  music_icon.p2.y = 160;
  TouchSubsribeArea(&music_icon, MusicIconEvent);

  cam_icon.p1.x = 75;
  cam_icon.p1.y = 115;
  cam_icon.p2.x = 140;
  cam_icon.p2.y = 175;
  TouchSubsribeArea(&cam_icon, CamIconEvent);

  take_photo_region.p1.x = 440;
  take_photo_region.p1.y = 1;
  take_photo_region.p2.x = 480;
  take_photo_region.p2.y = 52;
  TouchSubsribeArea(&take_photo_region, TakePhotoEvent);

  show_photo_region.p1.x = 440;
  show_photo_region.p1.y = 225;
  show_photo_region.p2.x = 480;
  show_photo_region.p2.y = 272;
  TouchSubsribeArea(&show_photo_region, ShowPhotoEvent);
  
  return_screen_region.p1.x = 1;
  return_screen_region.p1.y = 225;
  return_screen_region.p2.x = 50;
  return_screen_region.p2.y = 272;
  TouchSubsribeArea(&return_screen_region, ShowMainScreenEvent); 
  return TOUCH_INIT;
}
