#include "lcd.h"
#include "lcd_controller.h"
#include "video_buffer.h"
#include <stdint.h>

#ifndef NULL
#define NULL 0
#endif

// -----------------------------------------------------------------------------
void LcdDrawPixel(unsigned int x, unsigned int y, Rgb565Color_t color) {
  static uint32_t pixel2word = 0;
  static unsigned int pixel_number = 0;
  static uint32_t changing_word = 0;

  if (x == 0 || y == 0) {
    return;
  }
  --x; --y;
  if ((x > LcdGetWigthInPixels()) || (y > LcdGetHeigthInPixels())) {
    return;
  }

  // define word number in video buffer array
  pixel_number = y * LcdGetWigthInPixels() + x;
  pixel2word = (pixel_number / 2);
  
  // define msb half-word or lsb half-word
  // It need because one word contain two real pixels
  if (pixel_number % 2 == 0) {
    changing_word = *(GetVideoBufferAddr() + pixel2word);
    changing_word &= 0xffff0000;
    changing_word |= ((uint32_t)color);
    *(GetVideoBufferAddr() + pixel2word) = changing_word;
  } else {
    changing_word = *(GetVideoBufferAddr() + pixel2word);
    changing_word &= 0x0000ffff;
    changing_word |= (((uint32_t)color) << 16);
    *(GetVideoBufferAddr() + pixel2word) = changing_word;
  }
}

// -----------------------------------------------------------------------------
void LcdDrawIcon(unsigned int x_start, 
                 unsigned int y_start,
                 GetIconArray get_icon) {
  uint16_t * icon_data = NULL;
  size_t icon_len_in_pixels = 0;
  size_t icon_line_len_in_pixels = get_icon(&icon_data, &icon_len_in_pixels);

  unsigned int curr_x_pixel = x_start;
  unsigned int curr_y_pixel = y_start;

  for (unsigned int i = 0; i < icon_len_in_pixels; ++i) {
    LcdDrawPixel(curr_x_pixel, 
                 curr_y_pixel, 
                 *(icon_data + i));
    ++curr_x_pixel;
    if ((curr_x_pixel - x_start) >= icon_line_len_in_pixels) {
      ++curr_y_pixel;
      curr_x_pixel -= icon_line_len_in_pixels;
    }
  }
}

// -----------------------------------------------------------------------------
void LcdSetBrightness(unsigned int bright_pwm) {
  LcdControllerSetPwm(bright_pwm);
}

// -----------------------------------------------------------------------------
void LcdDrawPhotoBuffer(void) {
  LcdControllerFillInVideoBuf(GetPhotoBufferAddr());
}
