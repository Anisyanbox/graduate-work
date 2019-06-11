#include "audio_controller.h"
#include "hal_1967VN034R1.h"
#include "aic23b.h"
#include "stupid_delay.h"
#include "soft_spi.h"

#ifndef NULL
#define NULL 0
#endif

#define DMA_AUDIO_CHANNEL   5
#define AUDIO_RATE_HZ       48000
#define DATA_LEN_BIT        32

static void (*app_handler_ptr)(void) = NULL;

// -----------------------------------------------------------------------------
#pragma interrupt
static void AudioDoneTransfIrqHandler(void) {
  if (app_handler_ptr != NULL) {
    app_handler_ptr();
    app_handler_ptr = NULL;
  }
}

// -----------------------------------------------------------------------------
AudioInitStat_t AudioControllerInit(void) {
  AUDIO_I2S_type i2s_conf;
  Aic23bHwDependFuncs_t hw_funcs;

  hw_funcs.delay = StupidDelayMs;
  hw_funcs.hw_init = SoftSpiInit;
  hw_funcs.select = SoftSpiSelect;
  hw_funcs.unselect = SoftSpiUnselect;
  hw_funcs.send = SoftSpiSend;
  if (Aic23bInit(&hw_funcs) != 0) {
    return AUDIO_INIT_FALSE;
  }

  i2s_conf.Role = ROLE_SLAVE;
  i2s_conf.Mode = MODE_I2S;
  i2s_conf.Standart = STANDART_PHILLIPS;
  i2s_conf.TfsPos = 0;
  i2s_conf.SwapLR = 0;
  i2s_conf.DataLen = DATA_LEN_BIT;
  i2s_conf.AudioFreq = AUDIO_RATE_HZ;

  LX_CMU->CFG8.b.I2S0_EN = 0;
  HAL_AUDIO_I2SInit(LX_AUDIO0, &i2s_conf);
  return AUDIO_INIT;
}

// -----------------------------------------------------------------------------
void AudioControllerStart(void * buf, size_t len, void (*end_handler)(void)) {
  app_handler_ptr = end_handler;
  HAL_AUDIO_StartDMA(DMA_AUDIO_CHANNEL, 
                     LX_AUDIO0,
                     buf,
                     len,
                     AudioDoneTransfIrqHandler);
}

// -----------------------------------------------------------------------------
void AudioControllerStop(void) {
  HAL_AUDIO_StopDMA(LX_AUDIO0);
}

// -----------------------------------------------------------------------------
unsigned int AudioConrollerGetSampleRate(void) {
  return (unsigned int)AUDIO_RATE_HZ;
}
