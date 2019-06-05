#include "cam_controller.h"
#include "lcd_controller.h"
#include "hal_1967VN034R1.h"
#include "ov7670.h"

#define CAM_DMA_CHANNEL     ((uint32_t)8)
#define PIXELS_IN_WORD      ((uint32_t)2)

static uint32_t picture_xsize = 0;
static uint32_t picture_ysize = 0;

// -----------------------------------------------------------------------------
#pragma interrupt
static void CamDmaDoneTransfIrqHandler(void) {
  HAL_CAMERA_Disable();
  HAL_CAMERA_StartDma(CAM_DMA_CHANNEL,
                    (void*)LcdControllerGetVideoBufAddr(),
                    picture_xsize,
                    picture_ysize,
                    4,
                    PIXELS_IN_WORD,
                    CamDmaDoneTransfIrqHandler);
  HAL_CAMERA_Enable(RECEIVE_MODE_CAMERA);
}

// -----------------------------------------------------------------------------
void CamControllerInit(void) {
  picture_xsize = LcdControllerGetVideoBufWigth();
  picture_ysize = LcdControllerGetVideoBufHeigth();
  
  ov7670HwInit();
  ov7670Reset();
  ov7670Init();

  HAL_CAMERA_Disable();
  HAL_CAMERA_SetupGpio();
  HAL_CAMERA_StartDma(CAM_DMA_CHANNEL,
                      (void*)LcdControllerGetVideoBufAddr(),
                      picture_xsize,
                      picture_ysize,
                      4,
                      PIXELS_IN_WORD,
                      CamDmaDoneTransfIrqHandler);
  HAL_CAMERA_Enable(RECEIVE_MODE_CAMERA);
}
