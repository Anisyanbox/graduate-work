/**********************************************************************************************************************
  Copyright (c) 2017 Milandr Corporation. All rights reserved.

  History:
  	  27-Feb-2017 Ivan Osadchy   - Created
**********************************************************************************************************************/
#include <hal_1967VN034R1.h>
#include <hal_updown.h>


// Значения по умолчанию для структуры инициализации:
void HAL_UPDOWN_DefaultInitStruct (UPDOWN_InitTypeDef *Init) {

	Init->Mode 			= UPDOWN_Mode_Down;
	Init->LinkX 		= UPDOWN_Link_Test;
	Init->FiltersStage 	= UPDOWN_FiltersStage_3;
	Init->Round 		= UPDOWN_Round_Off;
	Init->Shift 		= 0xFF;
	Init->FifoMode 		= UPDOWN_FifoMode_LowWord_IQ;
	Init->Coefficient 	= 4;
	Init->CntMode 		= UPDOWN_CntMode_Off;
	Init->Step 			= 0;
	Init->Cnt 			= 0;

}


//
void HAL_UPDOWN_Init (UPDOWN_TypeDef * const LX_UPDOWNx, UPDOWN_InitTypeDef * const Init) {

	u8 tmp;
	u8 i = 0;

	// Сброс всех настроек:
	HAL_UPDOWN_DeInit (LX_UPDOWNx);

	// Настройка регистра CR:
	LX_UPDOWNx->CR.b.DAM 		= Init->Mode;
	LX_UPDOWNx->CR.b.FLEN 		= Init->FiltersStage;
	LX_UPDOWNx->CR.b.LNKUSE 	= ((Init->LinkX 	& 0x01) != 0);
	LX_UPDOWNx->CR.b.LINK 		= ((Init->LinkX 	& 0x02) != 0);
	LX_UPDOWNx->CR.b.ROUND 		= ((Init->Round 	& 0x01) != 0);
	LX_UPDOWNx->CR.b.SAT 		= ((Init->Round 	& 0x02) != 0);
	LX_UPDOWNx->CR.b.ROUNDM 	= ((Init->Round 	& 0x04) != 0);
	LX_UPDOWNx->CR.b.IQ_QI 		= ((Init->FifoMode  & 0x01) != 0);
	LX_UPDOWNx->CR.b.TBD   		= ((Init->FifoMode  & 0x02) != 0);
	LX_UPDOWNx->CR.b.RCNT_ON 	= ((Init->CntMode  	& 0x01) != 0);
	LX_UPDOWNx->CR.b.INT_BLK 	= ((Init->CntMode  	& 0x02) != 0);

	if 		(Init->Coefficient < 3) 		LX_UPDOWNx->CR.b.Kdelay = 1;
	else if (Init->Coefficient > 0x201) 	LX_UPDOWNx->CR.b.Kdelay = 0x1FF;
	else  									LX_UPDOWNx->CR.b.Kdelay = (Init->Coefficient - 2) / 2;

	if (Init->Shift < 0x80) {
		LX_UPDOWNx->CR.b.SHFR = Init->Shift;
	} else {
		tmp = (LX_UPDOWNx->CR.b.Kdelay + 1) * 2;
		while (tmp != 0) { i++; tmp >>= 1; }
		LX_UPDOWNx->CR.b.SHFR = i * LX_UPDOWNx->CR.b.FLEN;
	}

	// Настройка RCNT и STEP:
	HAL_UPDOWN_SetRcntStep (LX_UPDOWNx, Init->Cnt, Init->Step);

	// Запуск:
	HAL_UPDOWN_Enable 			(LX_UPDOWNx);

}


// Деинициализация:
void HAL_UPDOWN_DeInit (UPDOWN_TypeDef * const LX_UPDOWNx) {

	LX_UPDOWNx->CR.word = 0;
	LX_UPDOWNx->STEP 	= 0;
	LX_UPDOWNx->RCNT 	= 0;
	LX_UPDOWNx->XCR 	= 0;

}


// Включение UPDOWN модуля:
void HAL_UPDOWN_Enable (UPDOWN_TypeDef * const LX_UPDOWNx) {

	LX_UPDOWNx->CR.b.EN = 1;

}


// Выключение UPDOWN модуля:
void HAL_UPDOWN_Disable (UPDOWN_TypeDef * const LX_UPDOWNx) {

	LX_UPDOWNx->CR.b.EN = 0;

}


// Одновременная запись значений в регистры RCNT и Step:
void HAL_UPDOWN_SetRcntStep (UPDOWN_TypeDef * const LX_UPDOWNx, const u32 RCNT, const u16 Step) {

	u64 tmp = RCNT;
	tmp = (tmp << 32) | Step;

	*((u64 *) &LX_UPDOWNx->RCNT) = tmp;

}


// Получение значения флага из регистра SR:
UPDOWN_FlagState HAL_UPDOWN_GetFlag (UPDOWN_TypeDef * const LX_UPDOWNx, const UPDOWN_Flag Flag) {

	return ((UPDOWN_FlagState) ((LX_UPDOWNx->SR.word & Flag) != 0));

}


// Подключение DMA:
void HAL_UPDOWN_ConnectDMA 	(UPDOWN_TypeDef * const LX_UPDOWNx, int ch_number, void *tcb) {

	DMARequester_type RT;

	// Определяем номер UPDOWN:
	if 		(LX_UPDOWNx == LX_UPDOWN0) RT = dmaUPDOWN0;
	else if (LX_UPDOWNx == LX_UPDOWN1) RT = dmaUPDOWN1;
	else if (LX_UPDOWNx == LX_UPDOWN2) RT = dmaUPDOWN2;
	else if (LX_UPDOWNx == LX_UPDOWN3) RT = dmaUPDOWN3;
	else return;

	// Если режим DOWN:
	if (((UPDOWN_Mode) LX_UPDOWNx->CR.b.DAM) == UPDOWN_Mode_Down) {
		if (ch_number > 3) return;
		HAL_DMA_DestRqstSet	(ch_number + 8, RT);
		HAL_DMA_WriteDC		(ch_number + 8, tcb);
		return;
	}

	// Если режим UP:
	if (((UPDOWN_Mode) LX_UPDOWNx->CR.b.DAM) == UPDOWN_Mode_Up) {
		if (ch_number > 3) return;
		HAL_DMA_SourceRqstSet	(ch_number + 4, RT);
		HAL_DMA_WriteDC			(ch_number + 4, tcb);
		return;
	}

}

