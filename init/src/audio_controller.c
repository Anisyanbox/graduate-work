#include "audio_controller.h"
#include "hal_1967VN034R1.h"
#include "stupid_delay.h"

#ifndef NULL
#define NULL 0
#endif

#define DMA_OUT_AUDIO_CHANNEL   5
#define DMA_IN_AUDIO_CHANNEL    9
#define AUDIO_RATE_HZ           48000
#define DATA_LEN_BIT            16

static void (*app_tx_handler_ptr)(void) = NULL;
static void (*app_rx_handler_ptr)(void) = NULL;

// -----------------------------------------------------------------------------
#pragma interrupt
static void AudioDoneTransfIrqHandler(void) {
  if (app_tx_handler_ptr != NULL) {
    app_tx_handler_ptr();
    app_tx_handler_ptr = NULL;
  }
}

// -----------------------------------------------------------------------------
#pragma interrupt
static void AudioDoneReceiveIrqHandler(void) {
  if (app_rx_handler_ptr != NULL) {
    app_rx_handler_ptr();
    app_rx_handler_ptr = NULL;
  }
}

// -----------------------------------------------------------------------------
void AudioControllerInit(void) {
  AUDIO_I2S_type i2s_conf;
  uint16_t usReqlp = usReqlp = (PLL_Freq.CoreClk * 1000 / 4 ) / \
                               (AUDIO_RATE_HZ * DATA_LEN_BIT);
  // init I2S gpio
  HAL_GPIO_Init(LX_GPIO_PA, 
                GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 | \
                GPIO_PIN_16 | GPIO_PIN_17 | GPIO_PIN_18, 
                GPIO_PinMode_Alt);

  // clock I2S enable
  LX_CMU->CFG8.b.I2S0_EN = 0;

  // reset tx/rx FIFO state machine to start position
  LX_AUDIO0->SICR0.word = 0x00000000;
  LX_AUDIO0->SICR0.b.RST = 1;
  StupidDelayMs(10);
  LX_AUDIO0->SICR0.b.RST = 0;
  LX_AUDIO0->SIADR = 0;

  // stereo 16 bit out and 16 bit stereo in
  LX_AUDIO0->SICR0.b.MONO_DA = 0;
  LX_AUDIO0->SICR0.b.BIT8_DA = 0;
  LX_AUDIO0->SICR0.b.BIT8_AD = 0;
  LX_AUDIO0->SICR0.b.MONO_AD = 0;

  // allow tx and rx
  LX_AUDIO0->SICR2.b.REQLP = usReqlp;
  LX_AUDIO0->SICR2.b.ERPL = 1;
  LX_AUDIO0->SICR2.b.EREC = 1;

  // I2S transmitter 
  LX_AUDIO0->I2S_T_CR.b.TEN = 1;
  LX_AUDIO0->I2S_T_CR.b.MODE = MODE_I2S;
  LX_AUDIO0->I2S_T_CR.b.SONY = STANDART_PHILLIPS;
  LX_AUDIO0->I2S_T_CR.b.MS = ROLE_SLAVE;
  LX_AUDIO0->I2S_T_CR.b.DSS = DATA_LEN_BIT - 1;
  LX_AUDIO0->I2S_T_CR.b.PNOS = 1;
  LX_AUDIO0->I2S_T_CR.b.SWHW = 0;
  
  if(DATA_LEN_BIT <= 16) {
    LX_AUDIO0->I2S_T_CR.b.PACKH = 1;
  } else {
    LX_AUDIO0->I2S_T_CR.b.PACKH = 0;
  }

  // I2S receiver
  LX_AUDIO0->I2S_R_CR.b.REN = 1;
  LX_AUDIO0->I2S_R_CR.b.MODE = MODE_I2S;
  LX_AUDIO0->I2S_R_CR.b.SONY = STANDART_PHILLIPS;
  LX_AUDIO0->I2S_R_CR.b.MS = ROLE_SLAVE;
  LX_AUDIO0->I2S_R_CR.b.DSS = DATA_LEN_BIT - 1;
  LX_AUDIO0->I2S_R_CR.b.PNOS = 1;
  LX_AUDIO0->I2S_R_CR.b.SWHW = 0;
}

// -----------------------------------------------------------------------------
void AudioControllerStartOut(void * out, 
                             size_t len_in_word, 
                             void (*end_handler)(void)) {
  app_tx_handler_ptr = end_handler;
  HAL_AUDIO_StartDMATx(DMA_OUT_AUDIO_CHANNEL, 
                       LX_AUDIO0,
                       out,
                       len_in_word,
                       AudioDoneTransfIrqHandler);
}

// -----------------------------------------------------------------------------
void AudioControllerStopOut(void) {
  HAL_AUDIO_StopDMA(DMA_OUT_AUDIO_CHANNEL);
}

// -----------------------------------------------------------------------------
void AudioControllerStartIn(void * in, 
                            size_t len_in_word, 
                            void (*end_handler)(void)) {
  app_rx_handler_ptr = end_handler;
  HAL_AUDIO_StartDMARx(DMA_IN_AUDIO_CHANNEL, 
                       LX_AUDIO0,
                       in,
                       len_in_word,
                       AudioDoneReceiveIrqHandler);
}

// -----------------------------------------------------------------------------
void AudioControllerStopIn(void) {
  HAL_AUDIO_StopDMA(DMA_IN_AUDIO_CHANNEL);
}

// -----------------------------------------------------------------------------
unsigned int AudioConrollerGetSampleRate(void) {
  return (unsigned int)AUDIO_RATE_HZ;
}
