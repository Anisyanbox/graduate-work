#ifndef _ADAPTERS_INC_AUDIO_ADAPTER_H_
#define _ADAPTERS_INC_AUDIO_ADAPTER_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * Use this types into audio libs (audio.c/.h)
*/
typedef void (*AudioPlaySoundDone)(void);

// 'frame' - buffer with microphone data from audio codec.
// In current audio codec and i2s interface settings: 
// MSB 16 bits from frame - Left channel.
// LSB 16 bits from frame - Right channel.
typedef void (*AudioRecordFrameDone)(unsigned int * frame, 
                                     size_t len_in_word);

typedef enum {
  AUDIO_INIT = 0,
  AUDIO_INIT_FALSE
} AudioInitStat_t;

AudioInitStat_t AudioInit(void);

// 'music_buf_out' - user buffer with music data.
// In current audio codec and i2s interface settings: 
// MSB 16 bits from music_buf_out - Left channel.
// LSB 16 bits from music_buf_out - Right channel.
//
// if 'is_playback_cyclically' == 0, your music will not 
// play continue cyclically after end
//
// 'sound_end' will be called after each cycle
void AudioSend(uint32_t * music_buf_out, 
               size_t len_in_words,
               AudioPlaySoundDone sound_end,
               bool is_playback_cyclically);
void AudioStopSend(void);
void AudioStartReceive(AudioRecordFrameDone record_frame_done);
void AudioStopReceive(void);

#endif  // _ADAPTERS_INC_AUDIO_ADAPTER_H_
