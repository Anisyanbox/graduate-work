/**********************************************************************************************************************
  Copyright (c) 2017 Milandr Corporation. All rights reserved.

  History:
  	  10-Mar-2017 Ivan Osadchy   - Created
**********************************************************************************************************************/
#ifndef __HAL_UPDOWN_H
#define __HAL_UPDOWN_H


/************************************************ INCLUDES ***********************************************************/


// Инклуды:
#include <hal_dma.h>


// Дефайны:


// Типы переменных:
#define 	__IO					volatile


// Структура для регистров:
typedef __IO struct {
	union {
		u32 word;
		struct {
			u32 EN 		: 1; 	// 0
			u32 LINK 	: 1; 	// 1
			u32 ROUND	: 1; 	// 2
			u32 SAT		: 1; 	// 3
			u32 ROUNDM	: 1; 	// 4
			u32 TBD		: 1; 	// 5
			u32 IQ_QI	: 1; 	// 6
			u32 DAM		: 1; 	// 7
			u32 Kdelay	: 9; 	// 16:8
			u32 SHFR	: 7; 	// 23:17
			u32 INT_BLK	: 1; 	// 24
			u32 res		: 3; 	// 27:25
			u32 FLEN	: 2; 	// 29:28
			u32 RCNT_ON	: 1; 	// 30
			u32 LNKUSE	: 1; 	// 31
		} b;
	} CR;										// Смещение: 0
	union {
		u32 word;
		struct {
			u32 T_req 	: 1; 	// 0
			u32 R_req 	: 1; 	// 1
			u32 Ferr 	: 1; 	// 2
			u32 overf 	: 1; 	// 3
			u32 res 	: 28; 	// 31:4
		} b;
	} SR;										// Смещение: 1
	u32 STEP;									// Смещение: 2
	u32 res; 									// Смещение: 3
	u32 DR[4];									// Смещения: 4-7
	u32 RCNT;									// Смещение: 8
	u32 XCR;									// Смещение: 9

} UPDOWN_TypeDef;

#define 	LX_UPDOWN0 			((UPDOWN_TypeDef *) base_ADA0)
#define 	LX_UPDOWN1 			((UPDOWN_TypeDef *) base_ADA1)
#define 	LX_UPDOWN2 			((UPDOWN_TypeDef *) base_ADA2)
#define 	LX_UPDOWN3 			((UPDOWN_TypeDef *) base_ADA3)


// Структура для инициализации:
typedef enum {
	UPDOWN_Mode_Down 	= 0,
	UPDOWN_Mode_Up 		= 1,
} UPDOWN_Mode;

typedef enum {
	UPDOWN_Link_Test 				= 0x00,
	UPDOWN_Link_0 					= 0x02,
	UPDOWN_Link_1 					= 0x03,
} UPDOWN_Link;

typedef enum {
	UPDOWN_FiltersStage_3 			= 0,
	UPDOWN_FiltersStage_5 			= 1,
	UPDOWN_FiltersStage_7 			= 2,
} UPDOWN_FiltersStage;

typedef enum {
	UPDOWN_Round_Off 				= 0x00,
	UPDOWN_Round_MultOnly 			= 0x04,
	UPDOWN_Round_OutOnly 			= 0x01,
	UPDOWN_Round_OutOnlyNoOverflow 	= 0x03,
	UPDOWN_Round_All 				= 0x05,
	UPDOWN_Round_AllNoOverflow 		= 0x07,
} UPDOWN_Round;

typedef enum {
	UPDOWN_FifoMode_LowWord_IQ 		= 0x00,
	UPDOWN_FifoMode_LowWord_QI 		= 0x01,
	UPDOWN_FifoMode_HighWord_IQ 	= 0x02,
	UPDOWN_FifoMode_HighWord_QI 	= 0x03,
} UPDOWN_FifoMode;

typedef enum {
	UPDOWN_CntMode_Off 				= 0x00,
	UPDOWN_CntMode_Run 				= 0x01,
	UPDOWN_CntMode_IT 				= 0x03,
} UPDOWN_CntMode;

typedef struct {
	UPDOWN_Mode 		Mode;
	UPDOWN_Link 		LinkX;
	UPDOWN_FiltersStage	FiltersStage;
	UPDOWN_Round 		Round;
	u8 					Shift;
	UPDOWN_FifoMode 	FifoMode;
	u16 				Coefficient;
	UPDOWN_CntMode 		CntMode;
	u32 				Cnt;
	u32 				Step;
} UPDOWN_InitTypeDef;

typedef enum {
	UPDOWN_Flag_Treq 		= 0x01,
	UPDOWN_Flag_Rreq		= 0x02,
	UPDOWN_Flag_Ferr		= 0x04,
	UPDOWN_Flag_Overf		= 0x08,
} UPDOWN_Flag;

typedef enum {
	UPDOWN_FlagState_Off 	= 0,
	UPDOWN_FlagState_On  	= 1,
} UPDOWN_FlagState;



/* Exported functions ------------------------------------------------------- */


/*******************Include Function*********************/
#ifdef __cplusplus
  extern "C"
	{
	#endif

  	  void 				HAL_UPDOWN_DefaultInitStruct 	(UPDOWN_InitTypeDef *Init);
  	  void 				HAL_UPDOWN_Init 				(UPDOWN_TypeDef * const LX_UPDOWNx, UPDOWN_InitTypeDef * const Init);
  	  void 				HAL_UPDOWN_DeInit 				(UPDOWN_TypeDef * const LX_UPDOWNx);

  	  void 				HAL_UPDOWN_Enable 				(UPDOWN_TypeDef * const LX_UPDOWNx);
  	  void 				HAL_UPDOWN_Disable 				(UPDOWN_TypeDef * const LX_UPDOWNx);

  	  void 				HAL_UPDOWN_SetRcntStep			(UPDOWN_TypeDef * const LX_UPDOWNx, const u32 RCNT, const u16 Step);
  	  UPDOWN_FlagState 	HAL_UPDOWN_GetFlag 				(UPDOWN_TypeDef * const LX_UPDOWNx, const UPDOWN_Flag Flag);

  	  void 				HAL_UPDOWN_ConnectDMA 			(UPDOWN_TypeDef * const LX_UPDOWNx, int ch_number, void *tcb);

	#ifdef __cplusplus
	}
#endif // __cplusplus

#endif
