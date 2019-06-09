#include "touch_events.h"
#include "touch_adapter.h"
#include "xpt2046.h"
#include "lcd_controller.h"
#include "lcd.h"

// -----------------------------------------------------------------------------
static void DrawPoint(unsigned int x, unsigned int y) {
  LcdDrawPixel(x, y, 0);
  return;
}

// -----------------------------------------------------------------------------
TouchInitStat_t TouchInit(void) {
  Xpt2046LcdInfo_t lcd_info;

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
  return TOUCH_INIT;
}
