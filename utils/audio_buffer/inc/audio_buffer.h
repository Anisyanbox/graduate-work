#ifndef _UTILS_INIT_INC_AUDIO_BUFFER_H_
#define _UTILS_INIT_INC_AUDIO_BUFFER_H_

#include <stdint.h>

typedef enum {
  AUDIO_BUF_INIT = 0,
  AUDIO_BUF_FALSE
} AudioBufStat_t;

AudioBufStat_t AudioBufferInit(void);
uint32_t * GetAudioOutBufferAddr(void);
uint32_t * GetAudioCurrInBufferAddr(void);
uint32_t GetAudioOutBufferSizeInWords(void);
uint32_t GetAudioInBufferSizeInWords(void);

#endif  // _UTILS_INIT_INC_AUDIO_BUFFER_H_
