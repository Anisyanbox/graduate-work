#include "audio.h"
#include "audio_controller.h"
#include "audio_buffer.h"
#include "audio_adapter.h"
#include "aic23b.h"
#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define PI 3.14159265358979323846

/*
* Export functions from audio_adapter.c
*/

// 'music_buf_out' - user buffer with music data.
// In current audio codec and i2s interface settings: 
// MSB 16 bits from music_buf_out - Left channel.
// LSB 16 bits from music_buf_out - Right channel.
//
// if 'is_playback_cyclically' == 0, your music will not 
// play continue cyclically after end
//
// 'sound_end' will be called after each cycle
extern void AudioSend(uint32_t * music_buf_out, 
               size_t len_in_words,
               AudioPlaySoundDone sound_end,
               bool is_playback_cyclically);
extern void AudioStopSend(void);
extern void AudioStartReceive(AudioRecordFrameDone record_frame_done);
extern void AudioStopReceive(void);

// -----------------------------------------------------------------------------
void AudioPlayTrack(unsigned int * track, 
                    size_t len,
                    AudioPlaySoundDone play_done) {
  AudioSend((uint32_t*)track, len, play_done, false);
}

// -----------------------------------------------------------------------------
void AudioPlaySin(unsigned int hz) {
  uint32_t * signal = GetAudioOutBufferAddr();
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
  AudioSend(signal, nsamples, NULL, true);
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
