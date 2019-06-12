#include "audio_buffer.h"
#include "ext_mem_alloc.h"
#include "audio_controller.h"

static uint32_t * audio_buf = NULL;

// -----------------------------------------------------------------------------
AudioBufStat_t AudioBufferInit(void) {
  audio_buf = (uint32_t *)ExtMemAlloc((size_t)AudioConrollerGetSampleRate());
  if (audio_buf == NULL) {
    return AUDIO_BUF_FALSE;
  }
  return AUDIO_BUF_INIT;
}

// -----------------------------------------------------------------------------
uint32_t * GetAudioBufferAddr(void) {
  return audio_buf;
}

// -----------------------------------------------------------------------------
uint32_t GetAudioBufferSizeInWords(void) {
  return (uint32_t)((size_t)AudioConrollerGetSampleRate());
}
