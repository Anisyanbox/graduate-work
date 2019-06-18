#ifndef _LIBS_LCD_INC_LCD_H_
#define _LIBS_LCD_INC_LCD_H_

#include <stdint.h>
#include <string.h> // for size_t

typedef uint16_t Rgb565Color_t;

//
// Func return size of one picture line in pixels
//
// 'picture_data' - pointer to array with rgb565 value
// 1 pixel == 1 element of 'picture_data' array
//
// 'pixels_cnt' - real pixels count of imagine are saved in this pointer
//
typedef size_t (*GetIconArray)(uint16_t ** picture_data, size_t * pixels_cnt);

void LcdDrawPixel(unsigned int x, unsigned int y, Rgb565Color_t color);
void LcdDrawIcon(unsigned int x_start, 
                 unsigned int y_start, 
                 GetIconArray get_icon);
void LcdSetBrightness(unsigned int bright_pwm);

void LcdDrawPhotoBuffer(void);

#endif  // _LIBS_LCD_INC_LCD_H_
