#ifndef _DRIVERS_INC_OV7670_H_
#define _DRIVERS_INC_OV7670_H_

void ov7670HwInit(void);
void ov7670Reset(void);
int ov7670Init(void);

void ov7670StandbyDisable(void);
void ov7670StandbyEnable(void);

void ov7670MirrorImage(void);

#endif  // _DRIVERS_INC_OV7670_H_
