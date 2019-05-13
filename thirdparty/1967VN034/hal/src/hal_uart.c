/**********************************************************************************************************************
  Copyright (c) 2016 Milandr Corporation. All rights reserved.

  History:
  	  Zatonsky Pavel - Created.
**********************************************************************************************************************/
#include <hal_1967VN034R1.h>
#include <math.h>

/**
  * @brief  Initializes the UARTx peripheral according to the specified
  *         parameters in the UART_InitStruct.
  * @param  UARTx: Select the UART peripheral.
  *         This parameter can be one of the following values:
  *         UART1, UART2.
  * @param  UART_InitStruct: pointer to a UART_Init_type structure
  *         that contains the configuration information for the specified UART peripheral.
  * @retval The Baud Rate status (BaudRateValid or BaudRateInvalid).
  */
int HAL_UART_Init ( UART_type* UARTx,
						   UART_Init_type* InitStruct, unsigned int XTI_khz ){
	unsigned int tmpreg = 0;
	unsigned int XTIBaud;
	
	XTIBaud = XTI_khz * 1000;
	//Check UART ID
	if ((UARTx != (UART_type*)base_UART0) && (UARTx != (UART_type*)base_UART1)) return 1; // Error UART_type
	// Work Mode
	tmpreg |= InitStruct->WorkMode;
	// Over Sampling
	tmpreg |= InitStruct->OverSampling;
	// BitRate init
	if (InitStruct->BitRate == 0) return 2; 		// Error - BitRate = 0
	if(InitStruct->OverSampling == UART_OverSampling_High){
		if (InitStruct->BitRate > XTIBaud/16)
			return 4; // Error - BitRate > max UART speeed for current over_sampling
	}
	else{
		if (InitStruct->BitRate > XTIBaud/4)
			return 3; 	// Error - BitRate > max UART speed
	}

	if(InitStruct->OverSampling == UART_OverSampling_High)
		UARTx->UBitRate = round(XTIBaud / (InitStruct->BitRate * 16.0)) - 1;
	else
		UARTx->UBitRate = round(XTIBaud / (InitStruct->BitRate * 4.0)) - 1;

	// Word Length
	tmpreg |= InitStruct->WordLength;
	// Stop Bits
	tmpreg |= InitStruct->StopBits;
	// Parity Mode
	tmpreg |= InitStruct->ParityMode;
	// FIFO Size
	tmpreg |= InitStruct->FIFOSize;
	// TXD Mode
	tmpreg |= InitStruct->TXDMode;
	// DMA Control Error
	tmpreg |= (InitStruct->DMACtrlErr<<3);
	// Interrupt control
	tmpreg |= 	(InitStruct->TxIT<<16) 	 | (InitStruct->RxIT<<17) 	 |
				(InitStruct->RxErrIT<<18) | (InitStruct->MSIT<<19) 	 |
				(InitStruct->UDIT<<20) 	 | (InitStruct->TxEmptIT<<21) |
				(InitStruct->RxTOIT<<22);
	//UART init 
	UARTx->UCR_LOAD.word = tmpreg;
	//UART enable
	UARTx->UCR_SET.word = (1<<UCR_UARTEN_P);
	return 0;
}

//-------------------------------------------------------------------------------------------//
void HAL_UART_DeInit (UART_type* UARTx){
	UARTx->UBitRate = 0;
	UARTx->UINT.word = 0;
	UARTx->UCR_LOAD.word = 0;
	return;
}

//-------------------------------------------------------------------------------------------//
void HAL_UART_DefaultInitStruct (UART_Init_type* InitStruct){
	InitStruct->BitRate		 = 9600;
	InitStruct->WorkMode     = UART_Mode_TxRx;
	InitStruct->OverSampling = UART_OverSampling_Normal;
	InitStruct->WordLength   = UART_WordLen_8bit;
	InitStruct->StopBits     = UART_Stop_1bit;
	InitStruct->ParityMode   = UART_Parity_Off;
	InitStruct->FIFOSize     = UART_FIFOSize_Byte;
	InitStruct->TXDMode      = UART_TXD_Direct;
	InitStruct->DMACtrlErr   = UART_DMACtrl_Dis;
	InitStruct->TxIT       	 = UART_IT_Dis;
	InitStruct->RxIT       	 = UART_IT_Dis;
	InitStruct->RxErrIT   	 = UART_IT_Dis;
	InitStruct->MSIT       	 = UART_IT_Dis;
	InitStruct->UDIT       	 = UART_IT_Dis;
	InitStruct->TxEmptIT  	 = UART_IT_Dis;
	InitStruct->RxTOIT    	 = UART_IT_Dis;
	return;
}

//-------------------------------------------------------------------------------------------//
int HAL_UART_Send (UART_type* UARTx, char* BuffAddr, unsigned int amount){
	unsigned char data;
	unsigned int i;
	//Check UART ID
	if ((UARTx != (UART_type*)base_UART0) && (UARTx != (UART_type*)base_UART1)) return 1; // Error UART_type

	for (i=0;i<amount;i++){
		while (UARTx->UFLAG.b.UTXFF); //While (TX_BUFF == FULL)
		data = *(BuffAddr + i);
		UARTx->UDR = data;
	}
	return 0;
}

//-------------------------------------------------------------------------------------------//
int HAL_UART_Receive (UART_type* UARTx, char* BuffAddr, unsigned int amount){
	unsigned char data;
	unsigned int i;
	int errFlag;

	//Check UART ID
	if ((UARTx != (UART_type*)base_UART0) && (UARTx != (UART_type*)base_UART1)) return 1; // Error UART_type

	for (i=0;i<amount;i++){
		if (!UARTx->UFLAG.b.URXFE){
			data = UARTx->UDR;
			*(BuffAddr + i) = data;
		}
		else return 2; 	//Error - RX buff empty
	}

	errFlag = UARTx->RXSTAT.word;
	return errFlag;
}

//-------------------------------------------------------------------------------------------//
void HAL_UARTDMA_Send(int uart_num, int dma_ch, void *tcb){
	uart_num++;
	HAL_DMA_SourceRqstSet(dma_ch,(DMARequester_type)uart_num);
	HAL_DMA_WriteDC(dma_ch,tcb);
}

//-------------------------------------------------------------------------------------------//
void HAL_UARTDMA_Receive(int uart_num, int dma_ch, void *tcb){
	uart_num++;
	HAL_DMA_DestRqstSet(dma_ch,(DMARequester_type)uart_num);
	HAL_DMA_WriteDC(dma_ch,tcb);
}

