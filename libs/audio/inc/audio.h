#ifndef _ADAPTERS_INC_AUDIO_H_
#define _ADAPTERS_INC_AUDIO_H_

#include <stddef.h>
#include "audio_adapter.h"

void AudioPlayTrack(unsigned int * track, 
                    size_t len,
                    AudioPlaySoundDone play_done);
void AudioPlaySin(unsigned int hz);
void AudioPlayVolumeSet(unsigned short percent);
void AudioStopPlay(void);

// Microphone has two internal buffers.
// Func 'AudioStartRecording' will be recorded data to one of internal buffer.
// Each buffers have len for 2 seconds input data.
// After this you can do processing it in 'record_done' func
void AudioStartRecording(AudioRecordFrameDone record_done);
void AudioInVolumeSet(unsigned short percent);
void AudioStopRecording(void);

#endif  // _ADAPTERS_INC_AUDIO_H_
