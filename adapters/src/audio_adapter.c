#include "audio_adapter.h"
#include "audio_controller.h"
#include "audio_buffer.h"
#include "pthread.h"
#include "semaphore.h"
#include "errno.h"
#include "delay.h"
#include "main.h"
#include "aic23b.h"
#include "soft_spi.h"
#include "stupid_delay.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define THREAD_OUT_SLEEP_MS     ((unsigned int)10)
#define THREAD_OUT_PRIORITY     MAIN_THREAD_NORMAL_PRIO
#define THREAD_IN_SLEEP_MS      ((unsigned int)10)
#define THREAD_IN_PRIORITY      MAIN_THREAD_NORMAL_PRIO

/* Variables for out data streaming */
static uint32_t * out_buffer = NULL;
static uint32_t out_len = 0;
static AudioPlaySoundDone sound_end_handler = NULL;
static bool is_replay_need = false;
static bool is_play_started = false;
static bool is_music_end = false;

/* Variables for microphone data reading */
static uint32_t * in_curr_buffer = NULL;
static uint32_t * in_next_buffer = NULL;
static AudioRecordFrameDone record_end_handler = NULL;
static bool is_record_start = false;
static bool is_record_end = false;

// ----------------------------------------------------------------------------
static void DoAppMusicEndHandler(void) {
  if (sound_end_handler != NULL) {
    sound_end_handler();
  }
}

// ----------------------------------------------------------------------------
static void DoAppMicrophoneEndHandler(void) {
  if (record_end_handler != NULL) {
    record_end_handler(in_curr_buffer, GetAudioInBufferSizeInWords());
  }
}

/*
* Funcs for reading music
*/
// ----------------------------------------------------------------------------
static void RecFrameDoneHandler(void) {
  static int calls = 0;
  
  if (calls == 0) {
    in_curr_buffer = GetAudioCurrInBufferAddr();
    in_next_buffer = GetAudioNextInBufferAddr();
    calls = 1;
  } else {
    in_curr_buffer = GetAudioNextInBufferAddr();
    in_next_buffer = GetAudioCurrInBufferAddr();
    calls = 0;
  }
  AudioControllerStartIn((void*)in_next_buffer, 
                         GetAudioInBufferSizeInWords(), 
                         RecFrameDoneHandler);
  is_record_end = true; // ToDo: need semaphore here
}

// -----------------------------------------------------------------------------
static void * AudioInThread(void * args) {
  while(true) {
     if (is_record_end) {
       DoAppMicrophoneEndHandler();
       is_record_end = false;
     }
  }
}

/*
* Funcs for streaming music
*/
// -----------------------------------------------------------------------------
static void SendFrameDoneHandler(void) {
  // ToDo: need semaphore here
  is_music_end = true;
}

// -----------------------------------------------------------------------------
static void * AudioOutThread(void * args) { 
  while(true) {
    // ToDo: need semaphore here
    if (is_music_end) {
      DoAppMusicEndHandler();
      is_music_end = false;

      if (!is_replay_need) {
        AudioControllerStopOut();
        is_music_end = false;
        is_replay_need = false;
        is_play_started = false;
      }
    }
  }
}

// -----------------------------------------------------------------------------
void AudioSend(uint32_t * music_buf_out, 
               size_t len_in_words,
               AudioPlaySoundDone sound_end,
               bool is_playback_cyclically) {
  if (!is_play_started) {
    is_play_started = true;
    out_buffer = music_buf_out;
    out_len = len_in_words;
    sound_end_handler = sound_end;
    is_replay_need = is_playback_cyclically;
    AudioControllerStartOut((void*)out_buffer, out_len, SendFrameDoneHandler);
  }
}

// -----------------------------------------------------------------------------
void AudioStopSend(void) {
  AudioControllerStopOut();
  is_music_end = false;
  is_replay_need = false;
  is_play_started = false;
}

// -----------------------------------------------------------------------------
void AudioStartReceive(AudioRecordFrameDone record_frame_done) {
  if (!is_record_start) {
    is_record_start = true;
    record_end_handler = record_frame_done;
    AudioControllerStartIn((void*)GetAudioCurrInBufferAddr(), 
                          GetAudioInBufferSizeInWords(), 
                          RecFrameDoneHandler);
  }
}

// -----------------------------------------------------------------------------
void AudioStopReceive(void) {
  AudioControllerStopIn();
  is_record_start = false;
}

// -----------------------------------------------------------------------------
AudioInitStat_t AudioInit(void) {
  Aic23bHwDependFuncs_t hw_funcs;

  static pthread_t audio_out_thread_handl;
  static pthread_t audio_in_thread_handl;

  pthread_attr_t audio_out_attr;
  pthread_attr_t audio_in_attr;

  sched_param_t audio_out_thread_prio;
  sched_param_t audio_in_thread_prio;

  // init hw I2S/interrupts/DMA
  AudioControllerInit();

  // audio codec init
  hw_funcs.delay = StupidDelayMs;
  hw_funcs.hw_init = SoftSpiInit;
  hw_funcs.select = SoftSpiSelect;
  hw_funcs.unselect = SoftSpiUnselect;
  hw_funcs.send = SoftSpiSend;
  if (Aic23bInit(&hw_funcs) != 0) {
    return AUDIO_INIT_FALSE;
  }

  // init out audio thread
  if (pthread_attr_init(&audio_out_attr) != 0) {
    return AUDIO_INIT_FALSE;
  }
  audio_out_thread_prio.sched_priority = THREAD_OUT_PRIORITY;
  if (pthread_attr_setschedparam(&audio_out_attr,
                                (const sched_param_t*)&audio_out_thread_prio) != 0) {
    return AUDIO_INIT_FALSE;
  }
  if (pthread_create(&audio_out_thread_handl, 
                    (const pthread_attr_t*)audio_out_attr, 
                    AudioOutThread, 
                    NULL) != 0) {
    return AUDIO_INIT_FALSE;
  }
  if (pthread_attr_destroy(&audio_out_attr) != 0) {
    return AUDIO_INIT_FALSE;
  }

  // init in audio thread
  if (pthread_attr_init(&audio_in_attr) != 0) {
    return AUDIO_INIT_FALSE;
  }
  audio_in_thread_prio.sched_priority = THREAD_IN_PRIORITY;
  if (pthread_attr_setschedparam(&audio_in_attr,
                                (const sched_param_t*)&audio_in_thread_prio) != 0) {
    return AUDIO_INIT_FALSE;
  }
  if (pthread_create(&audio_in_thread_handl, 
                    (const pthread_attr_t*)audio_in_attr, 
                    AudioInThread, 
                    NULL) != 0) {
    return AUDIO_INIT_FALSE;
  }
  if (pthread_attr_destroy(&audio_in_attr) != 0) {
    return AUDIO_INIT_FALSE;
  }
  return AUDIO_INIT;
}
