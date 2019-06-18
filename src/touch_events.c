#include "touch_events.h"
#include "touch_adapter.h"
#include "xpt2046.h"
#include "lcd_controller.h"
#include "lcd.h"
#include "gui_func.h"
#include "camera.h"
#include "audio.h"

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
static void MusicIconEvent(void) {
  AudioStopPlay();
}

// -----------------------------------------------------------------------------
TouchInitStat_t TouchInit(void) {
  Xpt2046LcdInfo_t lcd_info;
  TouchArea_t cam_icon;
  TouchArea_t music_icon;
  TouchArea_t take_photo_region;

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
  
  return TOUCH_INIT;
}
