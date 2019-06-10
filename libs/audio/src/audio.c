#include "audio.h"
#include "audio_controller.h"
#include "aic23b.h"

// -----------------------------------------------------------------------------
void AudioPlayTrack(unsigned int * track, 
                     size_t len, 
                     void (*end_handler)(void)) {
  AudioControllerStart((void*)track, len, end_handler);                     
}

// -----------------------------------------------------------------------------
void AudioStopPlay(void) {
  AudioControllerStop();
}
