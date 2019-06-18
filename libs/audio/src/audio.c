#include "audio.h"
#include "audio_controller.h"
#include "audio_buffer.h"
#include "audio_adapter.h"
#include "aic23b.h"
#include <math.h>
#include <stdint.h>

#define M_PI		3.14159265358979323846

// -----------------------------------------------------------------------------
static double LinearSweep(double f0, double f1, double koef) {
  return f0 + (f1 - f0) * koef;
}

// -----------------------------------------------------------------------------
void AudioPlayTrack(unsigned int * track, 
                    size_t len,
                    AudioPlaySoundDone play_done,
                    bool is_replay) {
  AudioSend((uint32_t*)track, len, play_done, is_replay);
}

// -----------------------------------------------------------------------------
void AudioPlayVolumeSet(unsigned short percent) {
  Aic23bSetOutVolume(percent);
}

// -----------------------------------------------------------------------------
void AudioStopPlay(void) {
  AudioStopSend();
}

// -----------------------------------------------------------------------------
void AudioStartRecording(AudioRecordFrameDone record_done) {
  AudioStartReceive(record_done);
}

// -----------------------------------------------------------------------------
void AudioInVolumeSet(unsigned short percent) {
  Aic23bSetInputVolume(percent);
}

// -----------------------------------------------------------------------------
void AudioStopRecording(void) {
  AudioStopReceive();
}

// -----------------------------------------------------------------------------
unsigned int * AudioGeneratePureSinSignal(unsigned int ampl_dac, 
                                          unsigned int hz) {
  uint32_t * signal = GetAudioOutBufferAddr();
  int nsamples = AudioConrollerGetSampleRate();
  int i = 0;
  double t_sin = 0.0;
  double curr_time = 0.0;
  volatile uint32_t temp_sig_val = 0;
  volatile uint32_t temp_ch_val = 0;

  while(i < nsamples) {
    curr_time = ((double)i)/((double)nsamples);
    t_sin = sin((double)hz * 2.0 * M_PI * curr_time);
    temp_ch_val = (uint32_t)((double)ampl_dac * (t_sin + 1.0));
 
    temp_sig_val = temp_ch_val << 16;       // left
    temp_sig_val |= (uint16_t)temp_ch_val;  // right
    signal[i] = temp_sig_val;      
    ++i;
  }
  return (unsigned int*)signal;
}

// -----------------------------------------------------------------------------
unsigned int * AudioGenerateChangingSinSignal(unsigned int f0,
                                              unsigned int f1,
                                              unsigned int ampl_dac,
                                              SweepFunc_t sweep_func) {
  double instantaneous_f = f0;
  double current_phase = 0.0;
  uint32_t * signal = GetAudioOutBufferAddr();
  int nsamples = AudioConrollerGetSampleRate();
  volatile uint32_t temp_sig_val = 0;
  volatile uint32_t temp_ch_val = 0;

  if (sweep_func == NULL) {
    sweep_func = LinearSweep;
  }

  for (int i = 0 ; i < nsamples; i++) {
    temp_ch_val = (uint32_t)((double)ampl_dac * (sin(current_phase) + 1.0));
    instantaneous_f = sweep_func(f0, f1, (0.2 * i) / nsamples);
    current_phase = 2.0 * M_PI * instantaneous_f * (double)i / (double)nsamples;

    temp_sig_val = temp_ch_val << 16;       // left
    temp_sig_val |= (uint16_t)temp_ch_val;  // right
    signal[i] = temp_sig_val;
  }
  return (unsigned int *)signal;
}
