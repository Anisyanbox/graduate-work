#ifndef _LIBS_CAMERA_INC_CAMERA_ADAPTER_H_
#define _LIBS_CAMERA_INC_CAMERA_ADAPTER_H_

#include <stdint.h>

typedef void (*LcdFillBackground)(void);

void CameraStartVideo(void);
void CameraStopShowVideo(LcdFillBackground lcd_fill);
void CameraTakePhoto(void);
uint32_t * CameraGetPhoto(void);

#endif  // _LIBS_CAMERA_INC_CAMERA_ADAPTER_H_
