#ifndef _ADAPTERS_INC_AUDIO_ADAPTER_H_
#define _ADAPTERS_INC_AUDIO_ADAPTER_H_

#include <stddef.h>
#include <stdint.h>

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


#endif  // _ADAPTERS_INC_AUDIO_ADAPTER_H_
