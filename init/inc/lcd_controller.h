#ifndef _INIT_INC_LCD_CONTROLLER_H_
#define _INIT_INC_LCD_CONTROLLER_H_

void LcdControllerInit(void);
void LcdControllerSetPwm(unsigned int pwm);
unsigned int LcdGetBufSizeInWords(void);
unsigned int LcdGetWigthInPixels(void);
unsigned int LcdGetHeigthInPixels(void);

#endif  // _INIT_INC_LCD_CONTROLLER_H_
