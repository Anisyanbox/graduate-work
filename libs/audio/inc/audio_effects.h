#ifndef _LIBS_AUDIO_INC_AUDIO_EFFECTS_H
#define _LIBS_AUDIO_INC_AUDIO_EFFECTS_H

#include <stddef.h>

// array 'out' will be played with some effects
void AudioPlayEchoEffect(unsigned int * out, size_t len, int phase);
void AudioPlayReverbEffect(unsigned int * out, 
                           size_t len,
                           int phase,
                           float damping);

#endif  // _LIBS_AUDIO_INC_AUDIO_EFFECTS_H
