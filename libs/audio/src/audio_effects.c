#include "audio_effects.h"
#include "audio_adapter.h"
#include "audio_buffer.h"
#include "audio_controller.h"
#include "aic23b.h"
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

// -----------------------------------------------------------------------------
void AudioPlayEchoEffect(unsigned int * out, size_t len, int phase) {
  int i, j;
  uint32_t * buf_with_echo = GetAudioOutEffectsBufferAddr();
  
  for (i = 0; i < phase; ++i) {
    buf_with_echo[i] = out[i];
  }
  for (j = 0; i < len; ++i, ++j) {
    buf_with_echo[i] = out[i] + out[j] - Aic23bGetDacRes() / 2;
  }
  AudioSend(buf_with_echo, len, NULL, true);
}

// -----------------------------------------------------------------------------
void AudioPlayReverbEffect(unsigned int * out, 
                           size_t len,
                           int phase,
                           float damping) {
  int i, j;
  uint32_t * buf_with_reverb = GetAudioOutEffectsBufferAddr();

  for (i = 0; i < phase; ++i) {
    buf_with_reverb[i] = out[i];
  }
  for (j = 0; i < len; ++i, ++j) {
    buf_with_reverb[i] = (uint32_t)((float)out[i] + (float)out[j] * damping);
  }
  AudioSend(buf_with_reverb, len, NULL, true);
}
