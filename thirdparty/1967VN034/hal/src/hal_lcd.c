#include <hal_1967VN034R1.h>

#define wa_delay()  asm("nop;; nop;; nop;; nop;;")

void HAL_LCD_Enable(void) {
  LX_LCD->CTRL.field.VEN = 1;
}

void HAL_LCD_Disable(void) {
  LX_LCD->CTRL.field.VEN = 0;
}

void HAL_LCD_GpioInit(void) {
  LX_GPIO_PB->ALT.SET = 0x7C3FFFF0;
}

void HAL_LCD_GpioDeInit(void) {
  LX_GPIO_PB->ALT.CLR = 0x7C3FFFF0;
}

void HAL_LCD_ExGpioInit(LCD_ExGpioNum_type eGpio, LCD_ExGpio_type *pxExGpioCfg) {
  uint32_t ulTemp;

  switch (eGpio) {
    case LCD_Gpio_0:
      LX_GPIO_PB->ALT.SET = 0x00400000;
      ulTemp = pxExGpioCfg->StartPosition;
      if ( ulTemp > 0 ) ulTemp--;
      LX_LCD->GPIO_0.field.GPO_ST = ulTemp & 0x03FF;
      ulTemp = pxExGpioCfg->StopPosition;
      if ( ulTemp > 0 ) ulTemp--;
      LX_LCD->GPIO_0.field.GPO_SP = ulTemp & 0x03FF;
      if ( pxExGpioCfg->ActiveLevel == 1 )
        LX_LCD->GPIO_0.field.HPL = 0;
      else
        LX_LCD->GPIO_0.field.HPL = 1;
      break;
    case LCD_Gpio_1:
      LX_GPIO_PB->ALT.SET = 0x00800000;
      ulTemp = pxExGpioCfg->StartPosition;
      if ( ulTemp > 0 ) ulTemp--;
      LX_LCD->GPIO_1.field.GPO_ST = ulTemp & 0x03FF;
      ulTemp = pxExGpioCfg->StopPosition;
      if ( ulTemp > 0 ) ulTemp--;
      LX_LCD->GPIO_1.field.GPO_SP = ulTemp & 0x03FF;
      if ( pxExGpioCfg->ActiveLevel == 1 )
        LX_LCD->GPIO_1.field.HPL = 0;
      else
        LX_LCD->GPIO_1.field.HPL = 1;
      break;
    case LCD_Gpio_2:
      LX_GPIO_PB->ALT.SET = 0x01000000;
      ulTemp = pxExGpioCfg->StartPosition;
      if ( ulTemp > 0 ) ulTemp--;
      LX_LCD->GPIO_2.field.GPO_ST = ulTemp & 0x03FF;
      ulTemp = pxExGpioCfg->StopPosition;
      if ( ulTemp > 0 ) ulTemp--;
      LX_LCD->GPIO_2.field.GPO_SP = ulTemp & 0x03FF;
      if ( pxExGpioCfg->ActiveLevel == 1 )
        LX_LCD->GPIO_2.field.HPL = 0;
      else
        LX_LCD->GPIO_2.field.HPL = 1;
      break;
    case LCD_Gpio_3:
      LX_GPIO_PB->ALT.SET = 0x02000000;
      ulTemp = pxExGpioCfg->StartPosition;
      if ( ulTemp > 0 ) ulTemp--;
      LX_LCD->GPIO_3.field.GPO_ST = ulTemp & 0x03FF;
      ulTemp = pxExGpioCfg->StopPosition;
      if ( ulTemp > 0 ) ulTemp--;
      LX_LCD->GPIO_3.field.GPO_SP = ulTemp & 0x03FF;
      if ( pxExGpioCfg->ActiveLevel == 1 )
        LX_LCD->GPIO_3.field.HPL = 0;
      else
        LX_LCD->GPIO_3.field.HPL = 1;
      break;
  }
}

void HAL_LCD_ExGpioDeInit(LCD_ExGpioNum_type eGpio) {
  switch(eGpio) {
    case LCD_Gpio_0:
      LX_GPIO_PB->ALT.CLR = 0x00400000;
      break;
    case LCD_Gpio_1:
      LX_GPIO_PB->ALT.CLR = 0x00800000;
      break;
    case LCD_Gpio_2:
      LX_GPIO_PB->ALT.CLR = 0x01000000;
      break;
    case LCD_Gpio_3:
      LX_GPIO_PB->ALT.CLR = 0x02000000;
      break;
  }
}

void HAL_LCD_Setup(LCD_Conf_type *pxCfg) {
  uint32_t ulTemp;

  LX_LCD->CTRL.REG = 0;
  LX_LCD->PWM_CR.REG = 0;

  LX_LCD->VSIZE.field.VSIZE = pxCfg->usHSize * pxCfg->usVSize / (( pxCfg->ulRgbMode >> 4) & 0x0F);

  ulTemp = PLL_Freq.CoreClk / ( 2 * pxCfg->ulPixelClock );  // PX_CLK = SOC_CLK / (P_div + 1)
  if ( ulTemp > 0 ) ulTemp -= 1;
  LX_LCD->PXDV.field.P_DIV = ulTemp;
  wa_delay();
  LX_LCD->PXDV.field.EN_DIV = 1;

  LX_LCD->HVLEN.field.HT = ( ( pxCfg->usHFrontBlank + pxCfg->usHSize + pxCfg->usHBackBlank ) >> 3 ) - 1;
  wa_delay();
  LX_LCD->HVLEN.field.VT = ( pxCfg->usVFrontBlank + pxCfg->usVSize + pxCfg->usVBackBlank ) - 1;

  // HSYNC (fpline) 
  LX_LCD->HTIM.field.HPS = pxCfg->usHSyncPos - 1;
  wa_delay();
  LX_LCD->HTIM.field.HPL = ~pxCfg->bHSyncActiveLevel;
  wa_delay();
  LX_LCD->HTIM.field.HPW = pxCfg->usHSyncPos + pxCfg->usHSyncLen - 1;

  // VSYNC (fpframe)
  LX_LCD->VTIM.field.VPS = pxCfg->usVSyncPos - 1;
  wa_delay();
  LX_LCD->VTIM.field.VPL = ~pxCfg->bVSyncActiveLevel;
  wa_delay();
  LX_LCD->VTIM.field.VPW = pxCfg->usVSyncPos + pxCfg->usVSyncLen - 1;

  LX_LCD->HDTIM.field.HDPS = pxCfg->usHFrontBlank - 1;
  wa_delay();
  LX_LCD->HDTIM.field.HDPE = pxCfg->usHFrontBlank + pxCfg->usHSize - 1;

  LX_LCD->VDTIM.field.VDPS = pxCfg->usVFrontBlank - 1;
  wa_delay();
  LX_LCD->VDTIM.field.VDPE = pxCfg->usVFrontBlank + pxCfg->usVSize - 1;

  if ( pxCfg->pxWindow ) {
    LX_LCD->HDxTIM.field.HXDPS = pxCfg->usHFrontBlank + pxCfg->pxWindow->sHOffset - 1;
    wa_delay();
    LX_LCD->HDxTIM.field.HXDPE = pxCfg->usHFrontBlank + pxCfg->pxWindow->sHOffset + pxCfg->pxWindow->usHSize - 1;

    LX_LCD->VDxTIM.field.VXDPS = pxCfg->usVFrontBlank + pxCfg->pxWindow->sVOffset - 1;
    wa_delay();
    LX_LCD->VDxTIM.field.VXDPE = pxCfg->usVFrontBlank + pxCfg->pxWindow->sVOffset + pxCfg->pxWindow->usVSize - 1;

    LX_LCD->FON = pxCfg->pxWindow->ulBackgndColor;
  }

  LX_LCD->PANEL_CFG.field.FPSHI = pxCfg->bPClkInverse;

  LX_LCD->PWM_CR.field.RELOAD = HAL_LCD_MAX_PWM_DUTY;
  wa_delay();
  LX_LCD->PWM_CR.field.DUTY = 0;
  wa_delay();
  LX_LCD->PWM_CR.field.PWM_Dv = pxCfg->ulPwmDiv;
  wa_delay();
  LX_LCD->PWM_CR.field.CLKEN = 1;

  LX_LCD->CTRL.field.VBGR = pxCfg->bSwapRgbToBgr;
  wa_delay();
  LX_LCD->CTRL.field.CD = ( pxCfg->ulRgbMode >> 2 ) & 0x3;
  wa_delay();
  LX_LCD->CTRL.field.VBL = ( pxCfg->ulRgbMode >> 0 ) & 0x3;
  wa_delay();
  LX_LCD->CTRL.field.BL = ~pxCfg->bDReadyActiveLevel;
  wa_delay();
  LX_LCD->CTRL.field.W2W_EN = ( pxCfg->pxWindow != 0 );
  wa_delay();
  LX_LCD->CTRL.field.PXP_EN = pxCfg->bStopPclkWhenNoData;
}

void HAL_LCD_PwmSetDuty(uint8_t ucValue) {
  if ( ucValue >= HAL_LCD_MAX_PWM_DUTY )
    ucValue = HAL_LCD_MAX_PWM_DUTY + 1;
  LX_LCD->PWM_CR.field.DUTY = ucValue;
}

void HAL_LCD_StartDma(uint32_t ulChannel,
                      void *pvLcdBuf,
                      uint32_t ulXSize, 
                      uint32_t ulYSize,
                      uint32_t ulRgbMode,
                      void *pvDmaIsrHandler ) {
  // Transmitton Control Block (tcb) for DMA controller
  // Block from 4 words defining DMA mode
  static __builtin_quad tcb;
  uint32_t *ptr = ( uint32_t* ) &tcb;

  if( ulChannel < 4 || ulChannel > 7 ) {
    ulChannel = 4;
  }
  HAL_DMA_Stop( ulChannel );

  switch ( ( ulRgbMode >> 4 ) & 0x0F ) {
    case 2:
      ulXSize >>= 1;
      break;
    case 4:
      ulXSize >>= 2;
      break;
    default:
      break;
  }

  *( ptr + 0 ) = ( uint32_t ) pvLcdBuf;
  *( ptr + 1 ) = ( ulXSize << 16 ) | 4;
  *( ptr + 2 ) = ( ulYSize << 16 ) | 4;
  *( ptr + 3 ) =  TCB_TWODIM  |
                  TCB_QUAD    |
                  TCB_CHAIN   |
                  HAL_DMA_GetTCBChannelDest( ulChannel ) |
                  ( ( uint32_t ) &tcb >> 2 );
  *( ptr + 3 ) |= ( ( uint32_t ) pvLcdBuf < 0x0C000000 ) ? TCB_INTMEM : TCB_EXTMEM;
  HAL_DMA_SourceRqstSet( ulChannel, dmaVIDEO );

  if (pvDmaIsrHandler) {
    switch (ulChannel) {
      case 4:
        HAL_Interrupt_SubscribeHandler( intDMA4, pvDmaIsrHandler );
        HAL_Interrupt_Enable(intDMA4);
        break;
      case 5:
        HAL_Interrupt_SubscribeHandler( intDMA5, pvDmaIsrHandler );
        HAL_Interrupt_Enable(intDMA5);
        break;
      case 6:
        HAL_Interrupt_SubscribeHandler( intDMA6, pvDmaIsrHandler );
        HAL_Interrupt_Enable(intDMA6);
        break;
      case 7:
        HAL_Interrupt_SubscribeHandler( intDMA7, pvDmaIsrHandler );
        HAL_Interrupt_Enable(intDMA7);
        break;
      default:
        break;
    }
    *( ptr + 3 ) |= TCB_INT;
  }
  HAL_DMA_WriteDC( ulChannel, &tcb );
}
