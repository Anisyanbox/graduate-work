#include <stdio.h>
#include <stdlib.h>
#include "video_buffer.h"
#include "ext_mem_alloc.h"
#include "cam_controller.h"
#include "lcd_controller.h"

static uint32_t * video_buf = NULL;
static uint32_t * photo = NULL;
static uint32_t * photo_with_effects = NULL;

// -----------------------------------------------------------------------------
VideoBufStat_t VideoBufferInit(void) {
  video_buf = (uint32_t *)ExtMemAlloc((size_t)CamGetBufSizeInWords());
  photo = (uint32_t *)ExtMemAlloc((size_t)LcdGetBufSizeInWords());
  photo_with_effects = (uint32_t *)ExtMemAlloc((size_t)LcdGetBufSizeInWords());

  if ((video_buf == NULL) || (photo == NULL) || (photo_with_effects == NULL)) {
    return FRAME_BUF_FALSE;
  }
  return FRAME_BUF_INIT;
}

// -----------------------------------------------------------------------------
uint32_t * GetPhotoBufferAddr(void) {
  return photo;
}

// -----------------------------------------------------------------------------
uint32_t * GetVideoBufferAddr(void) {
  return video_buf;
}

// -----------------------------------------------------------------------------
uint32_t GetVideoBufferSizeInWords(void) {
  return LcdGetBufSizeInWords();
}

// -----------------------------------------------------------------------------
uint32_t GetVideoBufferWidthInWords(void) {
  return LcdGetWigthInPixels() / 2;
}
