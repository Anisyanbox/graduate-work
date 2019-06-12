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
  AudioControllerStartOut((void*)track, len, end_handler);                     
}

// -----------------------------------------------------------------------------
void AudioStopPlay(void) {
  AudioControllerStopOut();
}

// -----------------------------------------------------------------------------
void AudioVolumeSet(unsigned short percent) {
	Aic23bSetOutVolume(percent);
}

// -----------------------------------------------------------------------------
void AudioGenerateSin(unsigned int hz) {
  uint32_t * signal = GetAudioBufferAddr();
  int nsamples = AudioConrollerGetSampleRate();

  int i = 0;
  while(i < nsamples) {
    volatile uint32_t temp_sig_val = 0;
    double t = ((double)i)/((double)nsamples);
    uint32_t tmp = (uint32_t)(32767*sin((double)hz * 2.0 * PI * t));

    temp_sig_val = tmp << 16;       // left
    temp_sig_val |= (uint16_t)tmp;   // right
    signal[i] = temp_sig_val;      
    ++i;
  }
  AudioControllerStartOut((void*)signal, nsamples, NULL);
}
