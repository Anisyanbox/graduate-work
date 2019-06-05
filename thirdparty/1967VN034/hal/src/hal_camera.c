/*
 * hal_camera.c
 *
 *      Author: sharavyev.d
 */

#include <hal_1967VN034R1.h>
#include <stdint.h>

static __builtin_quad camera_tcb;

void HAL_CAMERA_SetupGpio(void) {
  LX_GPIO_PA->ALT.CLR = 0xFE000000;
  LX_GPIO_PA->DDR.CLR = 0xFE000000;

  LX_GPIO_PB->ALT.CLR = 0x0000000F;
  LX_GPIO_PB->DDR.CLR = 0x0000000F;
}

void HAL_CAMERA_Enable(CAMERA_Mode_type eMode) {
  if (eMode == RECEIVE_MODE_MASTER) {
    LX_CAMERA->CR.b.SMODE = 1;
  }
  LX_CAMERA->CR.b.VCON = 1;
}

void HAL_CAMERA_Disable(void) {
  LX_CAMERA->CR.word = 0x00000000;
  LX_CAMERA->SR.word = 0xFFFFFFFF;
}

void HAL_CAMERA_StartDma(uint32_t ulChannel,
                         void *pvCameraBuf, 
                         uint32_t ulXSize, 
                         uint32_t ulYSize,
                         uint32_t ulDelta, 
                         uint8_t ucPixelsInWord, 
                         void *pvDmaIsrHandler) {
  uint32_t *ptr = ( uint32_t* ) &camera_tcb;

  if( ulChannel < 8 || ulChannel > 11 ) {
    ulChannel = 8;
  }
  HAL_DMA_Stop(ulChannel);
  switch (ucPixelsInWord) {
    case 2:
      ulXSize >>= 1;
      break;
    case 4:
      ulXSize >>= 2;
      break;
    default:
      break;
  }

  *( ptr + 0 ) = ( uint32_t ) pvCameraBuf;
  *( ptr + 1 ) = ( ulXSize << 16 ) | 4;
  *( ptr + 2 ) = ( ulYSize << 16 ) | ulDelta;
  *( ptr + 3 ) =  TCB_TWODIM |
//                  TCB_HPRIORITY |
                  TCB_QUAD |
                  HAL_DMA_GetTCBChannelDest( ulChannel );
  *( ptr + 3 ) |= ( ( uint32_t ) pvCameraBuf < 0x0C000000 ) ? TCB_INTMEM : TCB_EXTMEM;
  HAL_DMA_DestRqstSet(ulChannel, dmaVIDEO);
  
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
  HAL_DMA_WriteDC(ulChannel, &camera_tcb);
}
