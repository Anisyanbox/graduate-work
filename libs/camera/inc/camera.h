#ifndef _ADAPTERS_INC_CAMERA_ADAPTER_H_
#define _ADAPTERS_INC_CAMERA_ADAPTER_H_

typedef void (*LcdFillBackground)(void);

void CameraStartVideo(void);
void CameraStopShowVideo(LcdFillBackground lcd_fill);

#endif  // _ADAPTERS_INC_CAMERA_ADAPTER_H_
