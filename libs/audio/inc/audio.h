#ifndef _ADAPTERS_INC_AUDIO_H_
#define _ADAPTERS_INC_AUDIO_H_

#include <stddef.h>

// Func 'end_handler' will run into interrupt 
// after ending of playing track
void AudioPlayTrack(unsigned int * track, 
                     size_t len, 
                     void (*end_handler)(void));
void AudioStopPlay(void);
void AudioGenerateSin(unsigned int hz);
void AudioVolumeSet(unsigned short percent);

#endif  // _ADAPTERS_INC_AUDIO_H_
