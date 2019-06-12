#ifndef _INIT_INC_AUDIO_CONTROLLER_H_
#define _INIT_INC_AUDIO_CONTROLLER_H_

#include <stddef.h>

typedef enum {
  AUDIO_INIT = 0,
  AUDIO_INIT_FALSE
} AudioInitStat_t;

AudioInitStat_t AudioControllerInit(void);
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
