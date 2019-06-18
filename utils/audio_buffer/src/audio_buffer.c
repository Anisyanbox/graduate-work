#include "audio_buffer.h"
#include "ext_mem_alloc.h"
#include "audio_controller.h"

static uint32_t * audio_out_buf = NULL;
static uint32_t * audio_out_effects_buf = NULL;
static uint32_t * audio_curr_in_buf = NULL;
static uint32_t * audio_next_in_buf = NULL;

static uint32_t audio_out_size = 0;
static uint32_t audio_in_size = 0;

// -----------------------------------------------------------------------------
AudioBufStat_t AudioBufferInit(void) {
  unsigned int srate = AudioConrollerGetSampleRate();

  audio_out_buf = (uint32_t *)ExtMemAlloc((size_t)srate);
  audio_curr_in_buf = (uint32_t *)ExtMemAlloc((size_t)srate);
  audio_next_in_buf = (uint32_t *)ExtMemAlloc((size_t)srate);
  audio_out_effects_buf = (uint32_t *)ExtMemAlloc((size_t)srate);

  audio_out_size = (uint32_t)srate;
  audio_in_size = (uint32_t)srate;

  if ((audio_out_buf == NULL) || (audio_curr_in_buf == NULL) || \
      (audio_next_in_buf == NULL) || (audio_out_effects_buf == NULL)) {
    return AUDIO_BUF_FALSE;
  }
  return AUDIO_BUF_INIT;
}

// -----------------------------------------------------------------------------
uint32_t * GetAudioOutBufferAddr(void) {
  return audio_out_buf;
}

// -----------------------------------------------------------------------------
uint32_t * GetAudioOutEffectsBufferAddr(void) {
  return audio_out_effects_buf;
}

// -----------------------------------------------------------------------------
uint32_t * GetAudioCurrInBufferAddr(void) {
return audio_curr_in_buf;
}

// -----------------------------------------------------------------------------
uint32_t * GetAudioNextInBufferAddr(void) {
return audio_next_in_buf;
}

// -----------------------------------------------------------------------------
uint32_t GetAudioOutBufferSizeInWords(void) {
  return audio_out_size;
}

// -----------------------------------------------------------------------------
uint32_t GetAudioInBufferSizeInWords(void) {
  return audio_in_size;
}
