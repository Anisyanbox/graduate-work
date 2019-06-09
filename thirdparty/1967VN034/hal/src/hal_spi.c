/**********************************************************************************************************************
  Copyright (c) 2017 Milandr Corporation. All rights reserved.

  History:
  	  27-Feb-2017 Ivan Osadchy   - Created
**********************************************************************************************************************/
#include <hal_1967VN034R1.h>
#include <hal_spi.h>

void HAL_SPI_Init (SPI_TypeDefInit *SPI) {
	if ((SPI->CLK_Phase != SPI_CLK_Phase_Negedge) && (SPI->CLK_Phase != SPI_CLK_Phase_Posedge)) 		return;
	if ((SPI->CLK_Polarity != SPI_CLK_Polarity_High) && (SPI->CLK_Polarity != SPI_CLK_Polarity_Low)) 	return;
	if (SPI->CLK_Prescaler > 4095) 																		return;
	if (SPI->CSNum > 5) 																				return;
	if ((SPI->CS_Active != SPI_CS_Active_High) && (SPI->CS_Active != SPI_CS_Active_Low)) 				return;
	if ((SPI->FirstBit != SPI_FirstBit_LSB) && (SPI->FirstBit != SPI_FirstBit_MSB)) 					return;
	if ((SPI->Mode != SPI_Mode_Master) && (SPI->Mode != SPI_Mode_Slave)) 								return;
	if ((SPI->WordSize < 4) || (SPI->WordSize > 16)) 													return;
	if ((SPI->LoopBack != SPI_LoopBack_Off) && (SPI->LoopBack != SPI_LoopBack_On))  					return;

	LX_SPI->SPCR0.word 	= SPI->CLK_Polarity | SPI->CLK_Phase | SPI->FirstBit;
	LX_SPI->SPCR0.b.SCR = SPI->CLK_Prescaler;
	LX_SPI->SPCR0.b.DSS = SPI->WordSize - 1;
	LX_SPI->SPCR0.b.CSN = SPI->CSNum;
	LX_SPI->SPCR1.word 	 = (SPI->CS_Hold | SPI->Mode | SPI->LoopBack);
	LX_SPI->SPCR1.b.CSAL = (SPI->CS_Active << SPI->CSNum);

	HAL_SPI_Enable (SPI_State_Enable);
	HAL_SPI_ClearFlag (SPI_Flag_RxFifoOverflow);
}

void HAL_SPI_DeInit (void) {
	LX_SPI->SPCR0.word 	= 0;
	LX_SPI->SPCR1.word 	= 0;
	LX_SPI->RX_CNT 		= 0;
}

void HAL_SPI_DefaultInitStruct (SPI_TypeDefInit *SPI) {
	SPI->CLK_Phase 		= SPI_CLK_Phase_Negedge;
	SPI->CLK_Polarity 	= SPI_CLK_Polarity_High;
	SPI->CLK_Prescaler 	= 2;
	SPI->CSNum			= 0;
	SPI->CS_Active 		= SPI_CS_Active_Low;
	SPI->FirstBit 		= SPI_FirstBit_MSB;
	SPI->Mode 			= SPI_Mode_Master;
	SPI->CS_Hold 		= SPI_CS_Unhold;
	SPI->WordSize 		= 8;
	SPI->LoopBack 		= SPI_LoopBack_Off;
}

void HAL_SPI_Enable (const SPI_State State) {
	LX_SPI->SPCR1.b.SPE = (uint) State;
}

void HAL_SPI_SetExchangeMode (SPI_ExchangeMode Mode) {
	LX_SPI->SPCR1.b.TXO = (Mode == SPI_ExchangeMode_TxOnly);
	LX_SPI->SPCR1.b.RXO = (Mode == SPI_ExchangeMode_RxOnly);
}

SPI_ExchangeMode HAL_SPI_GetExchangeMode () {
	return ((SPI_ExchangeMode) ((LX_SPI->SPCR1.b.RXO << 1) | LX_SPI->SPCR1.b.TXO));
}

uint HAL_SPI_WriteToTxFIFO (u16 *src, const uint Size) {
	u16 *SrcStart 	= src;
	u16 *SrcEnd 	= src + Size;
	while ((HAL_SPI_GetFlag(SPI_Flag_TxFifoNotFull) == SPI_State_Enable) && (src != SrcEnd)) {
		LX_SPI->SPDR = *src++;
	}
	return (src - SrcStart);
}

uint HAL_SPI_ReadFromRxFIFO	(u16 *dst, const uint Size) {
	u16 *DstStart 	= dst;
	u16 *DstEnd 	= dst + Size;
	while ((HAL_SPI_GetFlag(SPI_Flag_RxFifoNotEmpty) == SPI_State_Enable) && (dst != DstEnd)) {
		*dst++ = LX_SPI->SPDR;
	}
	return (dst - DstStart);
}

void HAL_SPI_SendOnly (u16 *src, const uint Size) {
	SPI_ExchangeMode EM = HAL_SPI_GetExchangeMode();
	u16 *SrcEnd 		= src + Size;

	HAL_SPI_SetExchangeMode (SPI_ExchangeMode_TxOnly);
	while (src != SrcEnd) {
		if (LX_SPI->SPSR.b.TNF != 0) LX_SPI->SPDR = *src++;
	}
	while (LX_SPI->SPSR.b.TFE == 0);
	while (LX_SPI->SPSR.b.BSY == 1);
	HAL_SPI_SetExchangeMode (EM);
}

void HAL_SPI_ReceiveOnly (u16 *dst, uint Size, const uchar DO_State) {
	SPI_ExchangeMode EM = HAL_SPI_GetExchangeMode();
	HAL_SPI_SetExchangeMode (SPI_ExchangeMode_RxOnly);

	LX_SPI->SPCR1.b.ROTL = (DO_State != 0);
	while (Size != 0) {
		if (Size > 8) {
			LX_SPI->RX_CNT = 8;
			Size -= 8;
		} else {
			LX_SPI->RX_CNT = Size;
			Size = 0;
		}
		while (LX_SPI->RX_CNT != 0);
		while( LX_SPI->SPSR.b.BSY == 1);
		while (LX_SPI->SPSR.b.RNE) *dst++ = LX_SPI->SPDR;
	}
	HAL_SPI_SetExchangeMode (EM);
}

void HAL_SPI_SendAndReceive (u16 *src, u16 *dst, const uint Size) {
	u16 *SrcEnd = src + Size;
	u16 *DstEnd = dst + Size;
	SPI_ExchangeMode EM = HAL_SPI_GetExchangeMode();
	uchar i;

	HAL_SPI_SetExchangeMode (SPI_ExchangeMode_All);
	while ((src != SrcEnd) || (dst != DstEnd)) {
		i = 0;
		while ((i < 8) && (src != SrcEnd)) {
			LX_SPI->SPDR = *src++;
			i++;
		}
		while ((LX_SPI->SPSR.b.TFE == 0) || LX_SPI->SPSR.b.BSY);
		while (LX_SPI->SPSR.b.RNE && (dst != DstEnd)) *dst++ = LX_SPI->SPDR;
	}
	HAL_SPI_SetExchangeMode (EM);
}

SPI_State HAL_SPI_GetFlag (const SPI_Flag Flag) {
	return ((SPI_State) ((LX_SPI->SPSR.word & Flag) != 0));
}

void HAL_SPI_ClearFlag (const SPI_Flag Flag) {
	LX_SPI->SPSR.word |= ((uint) Flag);
}

void HAL_SPI_ITConfig (const SPI_ITType IT, const SPI_State State) {
	uint S = ((uint) State);

	if (IT == SPI_IT_RxCntEnd) {
		LX_SPI->SPCR1.b.CIM = S;
		return;
	}
	if ((IT == SPI_IT_RxFifoHalfFull) || (IT == SPI_IT_RxFifoNotEmpty)) {
		LX_SPI->SPCR1.b.R_RQM 	= (IT == SPI_IT_RxFifoNotEmpty);
		LX_SPI->SPCR1.b.RIM 	= S;
		return;
	}
	if (IT == SPI_IT_RxFifoOverflow) {
		LX_SPI->SPCR1.b.ROM = S;
		return;
	}
	if ((IT == SPI_IT_TxFifoHalfEmpty) || (IT == SPI_IT_TxFifoNotFull)) {
		LX_SPI->SPCR1.b.T_RQM 	= (IT == SPI_IT_TxFifoNotFull);
		LX_SPI->SPCR1.b.TIM 	= S;
		return;
	}
	if (IT == SPI_IT_TxReadEmptyFifo) {
		LX_SPI->SPCR1.b.TUM = S;
		return;
	}
}

SPI_State HAL_SPI_ITCheck (const SPI_ITType IT) {
	uint S = SPI_State_Disable;
	switch (IT) {
		case SPI_IT_RxCntEnd:			S = LX_SPI->SPCR1.b.CIM && (LX_SPI->RX_CNT == 0);						break;
		case SPI_IT_RxFifoHalfFull: 	S = LX_SPI->SPCR1.b.RIM && HAL_SPI_GetFlag(SPI_Flag_RxFifoHalfFull);	break;
		case SPI_IT_RxFifoNotEmpty: 	S = LX_SPI->SPCR1.b.RIM && HAL_SPI_GetFlag(SPI_Flag_RxFifoNotEmpty); 	break;
		case SPI_IT_RxFifoOverflow: 	S = LX_SPI->SPCR1.b.ROM && HAL_SPI_GetFlag(SPI_Flag_RxFifoOverflow);	break;
		case SPI_IT_TxFifoHalfEmpty: 	S = LX_SPI->SPCR1.b.TIM && HAL_SPI_GetFlag(SPI_Flag_TxFifoHalfEmpty);	break;
		case SPI_IT_TxFifoNotFull: 		S = LX_SPI->SPCR1.b.TIM && HAL_SPI_GetFlag(SPI_Flag_TxFifoNotFull);		break;
		case SPI_IT_TxReadEmptyFifo: 	S = LX_SPI->SPCR1.b.TUM && HAL_SPI_GetFlag(SPI_Flag_TxFifoReadEmpty);	break;
	}
	return ((SPI_State) S);
}

void HAL_SPI_DMA_Transmit (int ch_number, void *tcb) {
	if (ch_number > 3) return;
	HAL_DMA_SourceRqstSet	(ch_number + 4, dmaSPI);
	HAL_DMA_WriteDC			(ch_number + 4, tcb);
}

void HAL_SPI_DMA_Reveive (int ch_number, void *tcb) {
	if (ch_number > 3) return;
	HAL_DMA_DestRqstSet	(ch_number + 8, dmaSPI);
	HAL_DMA_WriteDC		(ch_number + 8, tcb);
}
