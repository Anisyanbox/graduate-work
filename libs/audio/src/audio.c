#include "audio.h"
#include "audio_controller.h"
#include "audio_buffer.h"
#include "aic23b.h"
#include <math.h>
#include <stdint.h>

#define PI 3.14159265358979323846

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

// -----------------------------------------------------------------------------
void AudioVolumeSet(unsigned int vol) {
  Aic23bSetVolume((unsigned short)vol);
}

// -----------------------------------------------------------------------------
void AudioGenerateSin(unsigned int hz) {
  uint32_t * signal = GetAudioBufferAddr();
  int nsamples = AudioConrollerGetSampleRate();

  int i = 0;
  while(i < nsamples) {
    double t = ((double)i)/((double)nsamples);
    signal[i] = ((uint32_t)(32767*sin(hz * 2 * PI * t))) << 16; // left
    signal[i] |= (uint16_t)signal[i]; // right
    ++i;
  }
  AudioControllerStart((void*)signal, nsamples, NULL);
}
