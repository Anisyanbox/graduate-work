#include "cam_controller.h"
#include "hal_1967VN034R1.h"
#include "stupid_delay.h"
#include "video_buffer.h"
#include "ov7670.h"
#include "soft_i2c.h"

#define CAM_DMA_CHAN_NUM          ((uint32_t)8)
#define PIXELS_IN_WORD            ((uint8_t)2)

#define CAM_MAX_XRESOLUTION       ((uint32_t)640)
#define CAM_MAX_YRESOLUTION       ((uint32_t)480)

static uint32_t delta = 0;

// -----------------------------------------------------------------------------
#pragma interrupt
static void CamDmaDoneTransfIrqHandler(void) {
  HAL_CAMERA_Disable();
  HAL_CAMERA_StartDma(CAM_DMA_CHAN_NUM,             \
                      (void*)GetVideoBufferAddr(),  \
                      CAM_MAX_XRESOLUTION,          \
                      CAM_MAX_YRESOLUTION,          \
                      delta,                        \
                      PIXELS_IN_WORD,               \
                      CamDmaDoneTransfIrqHandler);
  HAL_CAMERA_Enable();
}

// -----------------------------------------------------------------------------
CameraInitStat_t CamControllerInit(void) {
  CAMERA_Conf_type pxConf;
  Ov7670HwDependFunc_t cam_hw;
  unsigned int* ptr;

  /* init SCCB and ov7670 camera driver */
  cam_hw.sccb_delay_ms = StupidDelayMs;
  cam_hw.sccb_start = SoftI2cStart;
  cam_hw.sccb_end = SoftI2cEnd;
  cam_hw.sccb_init = SoftI2cInit;
  cam_hw.sccb_send_byte = SoftI2cSendByte;
  cam_hw.sccb_rec_byte = SoftI2cReadByte;
  if (ov7670Init(&cam_hw, RES480x272_RGB565) != 0) {
    return CAMERA_INIT_FALSE;
  }
  ov7670MirrorImage();

  /* init camera controller pins */
  HAL_CAMERA_SetupGpio();

  /* configure interface for camera mode */
  pxConf.eMode = CAMERA_RECEIVE_MODE_CAMERA;
  HAL_CAMERA_Config(&pxConf);

  /* Stop camera and reset flags */
  HAL_CAMERA_Disable();

  /* Select request source Video for channel 8 and setup it */
  delta = 4;
  HAL_CAMERA_StartDma(CAM_DMA_CHAN_NUM,             \
                      (void*)GetVideoBufferAddr(),  \
                      CAM_MAX_XRESOLUTION,          \
                      CAM_MAX_YRESOLUTION,          \
                      delta,                        \
                      PIXELS_IN_WORD,               \
                      CamDmaDoneTransfIrqHandler);
  /* Start video */
  HAL_CAMERA_Enable();
  return CAMERA_INIT;
}

// -----------------------------------------------------------------------------
unsigned int CamGetBufSizeInWords(void) {
  return (unsigned int)(CAM_MAX_XRESOLUTION * CAM_MAX_YRESOLUTION / PIXELS_IN_WORD);
}

// -----------------------------------------------------------------------------
unsigned int CamGetBufWigthInPixels(void) {
  return (unsigned int)CAM_MAX_XRESOLUTION;
}

// -----------------------------------------------------------------------------
unsigned int CamGetBufHeigthInPixels(void) {
  return (unsigned int)CAM_MAX_YRESOLUTION;
}