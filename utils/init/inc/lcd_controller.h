#ifndef _UTILS_INIT_INC_LCD_CONTROLLER_H_
#define _UTILS_INIT_INC_LCD_CONTROLLER_H_

void LcdControllerInit(void);
uint32_t * LcdControllerGetVideoBufAddr(void);

int LcdControllerGetVideoBufSuze(void);
int LcdControllerGetVideoBufWigth(void);
int LcdControllerGetVideoBufHeigth(void);
 
#endif  // _UTILS_INIT_INC_LCD_CONTROLLER_H_
