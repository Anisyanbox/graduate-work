#include "camera.h"
#include "cam_controller.h"

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
  lcd_fill();
}
