#ifndef _UTILS_INIT_INC_VIDEO_BUFFER_H_
#define _UTILS_INIT_INC_VIDEO_BUFFER_H_

#include <stdint.h>

typedef enum {
  FRAME_BUF_INIT = 0,
  FRAME_BUF_FALSE
} VideoBufStat_t;

VideoBufStat_t VideoBufferInit(void);
uint32_t * GetVideoBufferAddr(void);

#endif  // _UTILS_INIT_INC_VIDEO_BUFFER_H_
