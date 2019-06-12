#include <hal_1967VN034R1.h>
#include <stdint.h>

static __builtin_quad audioTcbTx;
static __builtin_quad audioTcbRx;

void HAL_AUDIO_I2SInit( AUDIO_type* const AudioX, AUDIO_I2S_type* I2sConf ) {
  uint16_t usReqlp;

  AudioX->SICR0.word = 0x00000000;

  usReqlp = ( PLL_Freq.CoreClk * 1000 / 4 ) / ( I2sConf->AudioFreq * I2sConf->DataLen );
  AudioX->SICR2.b.REQLP = usReqlp;
  AudioX->SICR2.b.ERPL = 1;

  AudioX->I2S_T_CR.b.TEN = 1;
  AudioX->I2S_T_CR.b.MODE = I2sConf->Mode;
  AudioX->I2S_T_CR.b.SONY = I2sConf->Standart;
  AudioX->I2S_T_CR.b.MS = I2sConf->Role;
  AudioX->I2S_T_CR.b.DSS = I2sConf->DataLen - 1;
  AudioX->I2S_T_CR.b.PNOS = I2sConf->TfsPos;
  AudioX->I2S_T_CR.b.SWHW = I2sConf->SwapLR;

  if( I2sConf->DataLen <= 16 )
    AudioX->I2S_T_CR.b.PACKH = 1;
  else
    AudioX->I2S_T_CR.b.PACKH = 0;

  if( AudioX == LX_AUDIO0 )
    HAL_GPIO_Init( LX_GPIO_PA, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_16 | GPIO_PIN_17 | GPIO_PIN_18, GPIO_PinMode_Alt );
  else
    HAL_GPIO_Init( LX_GPIO_PA, GPIO_PIN_19 | GPIO_PIN_20 | GPIO_PIN_21 | GPIO_PIN_22 | GPIO_PIN_23 | GPIO_PIN_24, GPIO_PinMode_Alt );
}

void HAL_AUDIO_StartDMATx( uint32_t ulChannel, AUDIO_type* const AudioX, void *pvDataBuf, uint16_t usSize, void* pvDmaIsrHandler ) {
  uint32_t *ptr = ( uint32_t* ) &audioTcbTx;

  if( ulChannel < 4 || ulChannel > 7 )
    ulChannel = 4;

  HAL_DMA_Stop( ulChannel );

  *( ptr + 0 ) = ( uint32_t ) pvDataBuf;
  *( ptr + 1 ) = ( usSize << 16 ) | 1;
  *( ptr + 2 ) = 0;
  *( ptr + 3 ) = TCB_NORMAL;
  HAL_DMA_CreateChannelDest( ulChannel, &audioTcbTx, &audioTcbTx );
  *( ptr + 3 ) |=   ( ( uint32_t ) pvDataBuf < 0x0C000000 ) ? TCB_INTMEM : TCB_EXTMEM;

  if( AudioX == LX_AUDIO0 ) {
    HAL_DMA_RqstSet( ulChannel, dmaSSI0 );
  } else {
    HAL_DMA_RqstSet( ulChannel, dmaSSI1 );
  }

  if ( pvDmaIsrHandler ) {
    switch( ulChannel ) {
      case 4:
        HAL_Interrupt_SubscribeHandler( intDMA4, pvDmaIsrHandler );
        HAL_Interrupt_Enable( intDMA4 );
        break;
      case 5:
        HAL_Interrupt_SubscribeHandler( intDMA5, pvDmaIsrHandler );
        HAL_Interrupt_Enable( intDMA5 );
        break;
      case 6:
        HAL_Interrupt_SubscribeHandler( intDMA6, pvDmaIsrHandler );
        HAL_Interrupt_Enable( intDMA6 );
        break;
      case 7:
        HAL_Interrupt_SubscribeHandler( intDMA7, pvDmaIsrHandler );
        HAL_Interrupt_Enable( intDMA7 );
        break;
      default:
        break;
    }
    *( ptr + 3 ) |= TCB_INT;
  }

  HAL_DMA_WriteDC( ulChannel, &audioTcbTx );
}

 void HAL_AUDIO_StartDMARx(uint32_t ulChannel, 
                            AUDIO_type* const AudioX, 
                           void *pvDataBuf, 
                           uint16_t usSize, 
                           void* pvDmaIsrHandler) {
  uint32_t *ptr = ( uint32_t* ) &audioTcbRx;
  
  if( ulChannel < 8 || ulChannel > 11 ) {
    ulChannel = 9;
  }
  HAL_DMA_Stop(ulChannel);
  
  *( ptr + 0 ) = ( uint32_t ) pvDataBuf;
  *( ptr + 1 ) = ( usSize << 16 ) | 1;
  *( ptr + 2 ) = 0;
  *( ptr + 3 ) = TCB_NORMAL;
  HAL_DMA_CreateChannelDest( ulChannel, &audioTcbRx, &audioTcbRx );
  *( ptr + 3 ) |=   ((uint32_t)pvDataBuf < 0x0C000000) ? TCB_INTMEM : TCB_EXTMEM;

  if( AudioX == LX_AUDIO0 ) {
    HAL_DMA_RqstSet( ulChannel, dmaSSI0 );
  } else {
    HAL_DMA_RqstSet( ulChannel, dmaSSI1 );
  }
  
  if (pvDmaIsrHandler) {
    switch(ulChannel) {
      case 8:
        HAL_Interrupt_SubscribeHandler(intDMA8, pvDmaIsrHandler);
        HAL_Interrupt_Enable(intDMA8);
        break;
      case 9:
        HAL_Interrupt_SubscribeHandler(intDMA9, pvDmaIsrHandler);
        HAL_Interrupt_Enable(intDMA9);
        break;
      case 10:
        HAL_Interrupt_SubscribeHandler(intDMA10, pvDmaIsrHandler);
        HAL_Interrupt_Enable(intDMA10);
        break;
      case 11:
        HAL_Interrupt_SubscribeHandler(intDMA11, pvDmaIsrHandler);
        HAL_Interrupt_Enable(intDMA11);
        break;
      default:
        break;
    }
    *( ptr + 3 ) |= TCB_INT;
  }
  HAL_DMA_WriteDC( ulChannel, &audioTcbRx );
}

void HAL_AUDIO_StopDMA(uint32_t channel) {
  HAL_DMA_Stop( channel );

  switch( channel ) {
    case 4:
      HAL_Interrupt_Disable( intDMA4 );
      break;
    case 5:
      HAL_Interrupt_Disable( intDMA5 );
      break;
    case 6:
      HAL_Interrupt_Disable( intDMA6 );
      break;
    case 7:
      HAL_Interrupt_Disable( intDMA7 );
      break;
    case 8:
      HAL_Interrupt_Disable( intDMA8 );
      break;
    case 9:
      HAL_Interrupt_Disable( intDMA9 );
      break;
    case 10:
      HAL_Interrupt_Disable( intDMA10 );
      break;
    case 11:
      HAL_Interrupt_Disable( intDMA11 );
      break;
    default:
      break;
  }
}
