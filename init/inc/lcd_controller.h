#ifndef _INIT_INC_LCD_CONTROLLER_H_
#define _INIT_INC_LCD_CONTROLLER_H_

#include <stdint.h>

void LcdControllerInit(void);
void LcdControllerSetPwm(unsigned int pwm);
unsigned int LcdGetBufSizeInWords(void);
unsigned int LcdGetWigthInPixels(void);
unsigned int LcdGetHeigthInPixels(void);

void LcdControllerSaveCurrImage2PhotoBuf(void);
void LcdControllerFillInVideoBuf(uint32_t * new_buf);

#endif  // _INIT_INC_LCD_CONTROLLER_H_
