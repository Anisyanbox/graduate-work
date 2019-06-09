#include <stdio.h>
#include <stdlib.h>
#include "video_buffer.h"
#include "ext_mem_alloc.h"
#include "cam_controller.h"
#include "lcd_controller.h"

static uint32_t * video_buf = NULL;

// -----------------------------------------------------------------------------
VideoBufStat_t VideoBufferInit(void) {
  video_buf = (uint32_t *)ExtMemAlloc((size_t)CamGetBufSizeInWords());
  if (video_buf == NULL) {
    return FRAME_BUF_FALSE;
  }
  return FRAME_BUF_INIT;
}

// -----------------------------------------------------------------------------
uint32_t * GetVideoBufferAddr(void) {
  return video_buf;
}

// -----------------------------------------------------------------------------
uint32_t GetVideoBufferSizeInWords(void) {
  return LcdGetBufSizeInWords();
}
