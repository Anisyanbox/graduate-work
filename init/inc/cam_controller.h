#ifndef _INIT_INC_CAM_CONTROLLER_H_
#define _INIT_INC_CAM_CONTROLLER_H_

#include <stdint.h>

typedef enum {
  CAMERA_INIT = 0,
  CAMERA_INIT_FALSE
} CameraInitStat_t;

CameraInitStat_t CamControllerInit(void);
void CamControllerStop(void);
void CamControllerStart(void);
unsigned int CamGetBufSizeInWords(void);
unsigned int CamGetBufWigthInPixels(void);
unsigned int CamGetBufHeigthInPixels(void);

#endif  // _INIT_INC_CAM_CONTROLLER_H_
