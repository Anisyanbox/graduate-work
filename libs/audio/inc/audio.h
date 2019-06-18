#ifndef _LIBS_AUDIO_INC_AUDIO_H_
#define _LIBS_AUDIO_INC_AUDIO_H_

#include <stddef.h>
#include <stdbool.h>
#include "audio_adapter.h"

// type for define sweep function
typedef double (*SweepFunc_t)(double f0, double f1, double koef);

void AudioPlayTrack(unsigned int * track, 
                    size_t len,
                    AudioPlaySoundDone play_done,
                    bool is_replay);
void AudioPlayVolumeSet(unsigned short percent);
void AudioStopPlay(void);

// Microphone has two internal buffers.
// Func 'AudioStartRecording' will be recorded data to one of internal buffer.
// Each buffers have len for 2 seconds input data.
// After this you can do processing it in 'record_done' func
void AudioStartRecording(AudioRecordFrameDone record_done);
void AudioInVolumeSet(unsigned short percent);
void AudioStopRecording(void);

unsigned int * AudioGeneratePureSinSignal(unsigned int ampl_dac, 
                                          unsigned int hz);

// Func for generate chirp impulse
// If 'sweep_func' == NULL, standart linear sweepping function will be used 
unsigned int * AudioGenerateChangingSinSignal(unsigned int f0,
                                              unsigned int f1,
                                              unsigned int ampl_dac,
                                              SweepFunc_t sweep_func);

#endif  // _LIBS_AUDIO_INC_AUDIO_H_
