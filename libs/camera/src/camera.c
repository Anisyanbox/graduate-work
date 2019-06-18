#include "camera.h"
#include "cam_controller.h"
#include "lcd_controller.h"
#include "video_buffer.h"
#include <string.h>

typedef enum {
  STREAMING_EN = 0,
  STREAMING_DIS
} StreamingStat_t;

static StreamingStat_t video_streaming_status = STREAMING_DIS;

// -----------------------------------------------------------------------------
void CameraStartVideo(void) {
  if (video_streaming_status == STREAMING_EN) {
    return;
  }
  video_streaming_status = STREAMING_EN;
  CamControllerStart();
}

// -----------------------------------------------------------------------------
void CameraStopShowVideo(LcdFillBackground lcd_fill) {
  if (video_streaming_status == STREAMING_DIS) {
    return;
  }
  video_streaming_status = STREAMING_DIS;
  CamControllerStop();

  if (lcd_fill != NULL) {
    lcd_fill();
  }
}

// -----------------------------------------------------------------------------
void CameraTakePhoto(void) {
  if (video_streaming_status == STREAMING_DIS) {
    return;
  }

  CamControllerStop();
  LcdControllerSaveCurrImage2PhotoBuf();
  CamControllerStart();
}

// -----------------------------------------------------------------------------
uint32_t * CameraGetPhoto(void){
  return GetPhotoBufferAddr();
}
