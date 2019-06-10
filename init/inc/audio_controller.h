#ifndef _INIT_INC_AUDIO_CONTROLLER_H_
#define _INIT_INC_AUDIO_CONTROLLER_H_

#include <stddef.h>

typedef enum {
  AUDIO_INIT = 0,
  AUDIO_INIT_FALSE
} AudioInitStat_t;

AudioInitStat_t AudioControllerInit(void);
void AudioControllerStart(void * buf, size_t len, void (*end_handler)(void));
void AudioControllerStop(void);

#endif  // _INIT_INC_AUDIO_CONTROLLER_H_
