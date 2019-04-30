/**********************************************************************************************************************
  Copyright (c) 2017 Milandr Corporation. All rights reserved.

  History:
  	  09-Mar-2017 Ivan Osadchy   - delete pins
  	  27-Feb-2017 Ivan Osadchy   - Created
**********************************************************************************************************************/
#ifndef __HAL_SPI_H
#define __HAL_SPI_H


/************************************************ INCLUDES ***********************************************************/

// Инклуды:
#include <hal_interrupt.h>
#include <hal_dma.h>


// Типы переменных:
#define __IO			volatile
#define uint 			unsigned int
#define uchar 			unsigned char
#define u16 			unsigned short


// Регистры:
typedef union {
	uint word;
	struct {
		uint DSS 	: 4;		// 3:0
		uint res0 	: 2;		// 5:4
		uint SPO 	: 1;		// 6
		uint SPH 	: 1;		// 7
		uint TWI_on : 1; 		// 8
		uint TWI_rw : 1; 		// 9
		uint LMSF 	: 1; 		// 10
		uint res1 	: 1; 		// 11
		uint CSN 	: 3; 		// 14:12
		uint res2 	: 1; 		// 15
		uint SCR 	: 12; 		// 27:16
		uint res3 	: 4; 		// 31:28
	} b;
} SPI_SPCR0;

typedef union {
	uint word;
	struct {
		uint RIM 	: 1; 		// 0
		uint TIM 	: 1; 		// 1
		uint LBM 	: 1; 		// 2
		uint SPE 	: 1; 		// 3
		uint MS 	: 1; 		// 4
		uint TUM 	: 1; 		// 5
		uint ROM 	: 1; 		// 6
		uint res0 	: 1; 		// 7
		uint R_RQM 	: 1; 		// 8
		uint T_RQM 	: 1; 		// 9
		uint TXO 	: 1; 		// 10
		uint RXO 	: 1; 		// 11
		uint CIM 	: 1; 		// 12
		uint res1 	: 1; 		// 13
		uint HOLDCS	: 1; 		// 14
		uint ROTL 	: 1; 		// 15
		uint CSAL 	: 6; 		// 21:16
		uint res2 	: 10; 		// 31:22
	} b;
} SPI_SPCR1;

typedef union {
	uint word;
	struct {
		uint TFE 	: 1; 		// 0
		uint TNF 	: 1; 		// 1
		uint RNE 	: 1; 		// 2
		uint BSY 	: 1; 		// 3
		uint TFS 	: 1; 		// 4
		uint RFS 	: 1; 		// 5
		uint ROR 	: 1; 		// 6
		uint TUR 	: 1; 		// 7
		uint RFF 	: 1; 		// 8
		uint res 	: 23; 		// 31:9
	} b;
} SPI_SPSR;

typedef struct {
	__IO SPI_SPCR0 	SPCR0;				/*!< SPI регистр управления 0, 										Address offset: 0x00 */
	__IO SPI_SPCR1 	SPCR1;				/*!< SPI регистр управления 1, 										Address offset: 0x01 */
	__IO uint 		SPDR;				/*!< SPI регистр данных, 	 										Address offset: 0x02 */
	__IO SPI_SPSR 	SPSR;				/*!< SPI регистр состояния, 										Address offset: 0x03 */
	__IO uint 		RX_CNT;				/*!< SPI счетчик приемника, 										Address offset: 0x04 */
} SPI_TypeDef;

#define LX_SPI                 ((SPI_TypeDef *) base_SPI)  												// base_SPI = 0x80000140


// Структура для инициализации:
typedef enum { SPI_LoopBack_Off  		= (0 <<  2), 	SPI_LoopBack_On 		= (1 <<  2) } 	SPI_LOOPBACK;
typedef enum { SPI_Mode_Master 			= (0 <<  4), 	SPI_Mode_Slave 			= (1 <<  4) } 	SPI_MODE;
typedef enum { SPI_CLK_Polarity_High 	= (0 <<  6), 	SPI_CLK_Polarity_Low 	= (1 <<  6) } 	SPI_CLK_POLARITY;
typedef enum { SPI_CLK_Phase_Negedge 	= (0 <<  7), 	SPI_CLK_Phase_Posedge 	= (1 <<  7) } 	SPI_CLK_PHASE;
typedef enum { SPI_FirstBit_MSB 		= (0 <<  8), 	SPI_FirstBit_LSB 		= (1 <<  8) } 	SPI_FIRSTBIT;
typedef enum { SPI_CS_Unhold 			= (0 << 14), 	SPI_CS_Hold 			= (1 << 14) } 	SPI_CSHOLD;
typedef enum { SPI_CS_Active_Low 	 	= (0 << 16), 	SPI_CS_Active_High 		= (1 << 16) } 	SPI_CSACTIVE;

typedef struct {
	uchar 				WordSize;
	SPI_CLK_POLARITY	CLK_Polarity;
	SPI_CLK_PHASE		CLK_Phase;
	SPI_FIRSTBIT 		FirstBit;
	uchar				CSNum;
	u16 				CLK_Prescaler;
	SPI_MODE 			Mode;
	SPI_CSHOLD 			CS_Hold;
	SPI_CSACTIVE 		CS_Active;
	SPI_LOOPBACK 		LoopBack;
} SPI_TypeDefInit;


// Общий тип для выключения/включения:
typedef enum { SPI_State_Disable = 0, SPI_State_Enable = 1 } SPI_State;

// Типы режимов обмена:
typedef enum {
	SPI_ExchangeMode_All 	= 0,
	SPI_ExchangeMode_TxOnly = 1,
	SPI_ExchangeMode_RxOnly = 2
} SPI_ExchangeMode;


// Типы флагов статусного регистра и их значения:
typedef enum {
	SPI_Flag_TxFifoEmpty 		= (1 << 0),
	SPI_Flag_TxFifoNotFull 		= (1 << 1),
	SPI_Flag_RxFifoNotEmpty 	= (1 << 2),
	SPI_Flag_Busy 				= (1 << 3),
	SPI_Flag_TxFifoHalfEmpty 	= (1 << 4),
	SPI_Flag_RxFifoHalfFull 	= (1 << 5),
	SPI_Flag_RxFifoOverflow 	= (1 << 6),
	SPI_Flag_TxFifoReadEmpty 	= (1 << 7),
	SPI_Flag_RxFifoFull 		= (1 << 8),
} SPI_Flag;


// Типы прерываний:
typedef enum {
	SPI_IT_TxFifoNotFull,
	SPI_IT_TxFifoHalfEmpty,
	SPI_IT_TxReadEmptyFifo,
	SPI_IT_RxFifoNotEmpty,
	SPI_IT_RxFifoHalfFull,
	SPI_IT_RxFifoOverflow,
	SPI_IT_RxCntEnd
} SPI_ITType;


/* Exported functions ------------------------------------------------------- */


/*******************Include Function*********************/
#ifdef __cplusplus
  extern "C"
	{
	#endif

  	  void 				HAL_SPI_Init 				(SPI_TypeDefInit *SPI);
  	  void 				HAL_SPI_DeInit 				();
  	  void 				HAL_SPI_DefaultInitStruct 	(SPI_TypeDefInit *SPI);
  	  void 				HAL_SPI_Enable				(const SPI_State State);

  	  void 				HAL_SPI_SetExchangeMode 	(SPI_ExchangeMode Mode);
  	  SPI_ExchangeMode	HAL_SPI_GetExchangeMode		();

  	  uint 				HAL_SPI_WriteToTxFIFO 		(u16 *src, const uint Size);
  	  uint 				HAL_SPI_ReadFromRxFIFO		(u16 *dst, const uint Size);
  	  void 				HAL_SPI_SendOnly 			(u16 *src, const uint Size);
  	  void 				HAL_SPI_ReceiveOnly 		(u16 *dst, uint Size, const uchar DO_State);
  	  void 				HAL_SPI_SendAndReceive 		(u16 *src, u16 *dst, const uint Size);

  	  SPI_State 		HAL_SPI_GetFlag 			(const SPI_Flag Flag);
  	  void 				HAL_SPI_ClearFlag 			(const SPI_Flag Flag);

  	  void 				HAL_SPI_ITConfig 			(const SPI_ITType IT, const SPI_State State);
  	  SPI_State			HAL_SPI_ITCheck 			(const SPI_ITType IT);

  	  void 				HAL_SPI_DMA_Transmit 		(int ch_number, void *tcb);
  	  void 				HAL_SPI_DMA_Reveive 		(int ch_number, void *tcb);

	#ifdef __cplusplus
	}
#endif // __cplusplus

/********************************************************/


#endif
