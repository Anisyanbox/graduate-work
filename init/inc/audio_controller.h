#ifndef _INIT_INC_AUDIO_CONTROLLER_H_
#define _INIT_INC_AUDIO_CONTROLLER_H_

#include <stddef.h>

void AudioControllerInit(void);
void AudioControllerStartOut(void * out, 
                             size_t len_in_word, 
                             void (*end_handler)(void));
void AudioControllerStartIn(void * in, 
                            size_t len_in_word, 
                            void (*end_handler)(void));
void AudioControllerStopOut(void);
void AudioControllerStopIn(void);
unsigned int AudioConrollerGetSampleRate(void);

#endif  // _INIT_INC_AUDIO_CONTROLLER_H_
