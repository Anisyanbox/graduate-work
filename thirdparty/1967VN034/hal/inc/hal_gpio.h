/**********************************************************************************************************************
  Copyright (c) 2017 Milandr Corporation. All rights reserved.

  History:
  	  14-Mar-2017 Ivan Osadchy 	 - add LX_GPIO_...
  	  02-Mar-2017 Ivan Osadchy   - Created
**********************************************************************************************************************/

#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H

// Инклуды:


// Типы переменных:
typedef unsigned short	ushort;
#define __IO			volatile
#define uint 			unsigned int
#define uchar 			unsigned char


// Дефайны:


// Макросы:


// Набор пинов порта:
typedef enum {
	GPIO_PIN_0 	= ((uint) (1 <<  0)),
	GPIO_PIN_1 	= ((uint) (1 <<  1)),
	GPIO_PIN_2 	= ((uint) (1 <<  2)),
	GPIO_PIN_3 	= ((uint) (1 <<  3)),
	GPIO_PIN_4 	= ((uint) (1 <<  4)),
	GPIO_PIN_5 	= ((uint) (1 <<  5)),
	GPIO_PIN_6 	= ((uint) (1 <<  6)),
	GPIO_PIN_7 	= ((uint) (1 <<  7)),
	GPIO_PIN_8 	= ((uint) (1 <<  8)),
	GPIO_PIN_9 	= ((uint) (1 <<  9)),
	GPIO_PIN_10 = ((uint) (1 << 10)),
	GPIO_PIN_11 = ((uint) (1 << 11)),
	GPIO_PIN_12 = ((uint) (1 << 12)),
	GPIO_PIN_13 = ((uint) (1 << 13)),
	GPIO_PIN_14 = ((uint) (1 << 14)),
	GPIO_PIN_15 = ((uint) (1 << 15)),
	GPIO_PIN_16 = ((uint) (1 << 16)),
	GPIO_PIN_17 = ((uint) (1 << 17)),
	GPIO_PIN_18 = ((uint) (1 << 18)),
	GPIO_PIN_19 = ((uint) (1 << 19)),
	GPIO_PIN_20 = ((uint) (1 << 20)),
	GPIO_PIN_21 = ((uint) (1 << 21)),
	GPIO_PIN_22 = ((uint) (1 << 22)),
	GPIO_PIN_23 = ((uint) (1 << 23)),
	GPIO_PIN_24 = ((uint) (1 << 24)),
	GPIO_PIN_25 = ((uint) (1 << 25)),
	GPIO_PIN_26 = ((uint) (1 << 26)),
	GPIO_PIN_27 = ((uint) (1 << 27)),
	GPIO_PIN_28 = ((uint) (1 << 28)),
	GPIO_PIN_29 = ((uint) (1 << 29)),
	GPIO_PIN_30 = ((uint) (1 << 30)),
	GPIO_PIN_31 = 0x80000000, //((uint) (1 << 31)),
} GPIO_PIN;


// Набор из 4х регистров:
typedef __IO struct {
	uint LD;
	uint SET;
	uint CLR;
	uint INV;
} GPIO_REGSET;


// Набор регистров для портов PA, PB и PC:
typedef __IO struct {
	GPIO_REGSET DR;
	GPIO_REGSET DDR;
	GPIO_REGSET PEIE;
	GPIO_REGSET NEIE;
	GPIO_REGSET INVR;
	GPIO_REGSET IMR;
	GPIO_REGSET ALT;
	GPIO_REGSET PUR;
	uint 		PXD;
	uint 		INTREQ;
	uint 		rsv;
	uint 		ECLR;
} GPIO_PortPi;


// Набор регистров для порта PxA:
typedef __IO struct {
	uint DR;
	uint SET;
	uint CLR;
} GPIO_PortPxA;

// Набор регистров для порта PxD:
typedef __IO struct {
	uint DR;
	uint SET;
	uint CLR;
	uint DIR;
	uint res[5];
	uint PXD;
	uint PUR;
} GPIO_PortPxD;

// Регистр PxALT:
typedef __IO struct {
	union {
		uint word;
		struct {
			uint PDB 	: 4; 	// 3:0
			uint PAB 	: 3; 	// 6:4
			uint PDXF 	: 2; 	// 8:7
			uint res 	: 23; 	// 31:9
		} b;
	};
} GPIO_RegPxALT;


// Указатели на порты/регистр ALT:
#define 	LX_GPIO_PA 			((GPIO_PortPi 	*) base_GPA)
#define 	LX_GPIO_PB 			((GPIO_PortPi 	*) base_GPB)
#define 	LX_GPIO_PC 			((GPIO_PortPi 	*) base_GPC)
#define 	LX_GPIO_PxA 		((GPIO_PortPxA  *) PXA_LOAD_LOC)
#define 	LX_GPIO_PxD 		((GPIO_PortPxD  *) PXD_LOAD_LOC)
#define 	LX_GPIO_PxALT 		((GPIO_RegPxALT *) PX_ALT_LOC)

// Тип порта Px:
typedef enum {
	GPIO_PxPort_A = 0,
	GPIO_PxPort_D = 1,
} GPIO_PxPort;

// Режимы работы пина:
typedef enum {
	GPIO_PinMode_In 	= 0,
	GPIO_PinMode_InPU	= 1,
	GPIO_PinMode_Out	= 2,
	GPIO_PinMode_OutPU	= 3,
	GPIO_PinMode_Alt	= 4
} GPIO_PinMode;


// Состояния пина:
typedef enum {
	GPIO_PinState_Reset = 0,
	GPIO_PinState_Set 	= 1,
} GPIO_PinState;


// Различные варианты альтернативных функций для PxA и PxD:
typedef enum {
	GPIO_PxAlt_Data7_0					= 0x1,
	GPIO_PxAlt_Data15_8					= 0x2,
	GPIO_PxAlt_Data23_16				= 0x4,
	GPIO_PxAlt_Data31_24				= 0x8,
	GPIO_PxAlt_Addr7_0					= 0x10,
	GPIO_PxAlt_Addr15_8					= 0x20,
	GPIO_PxAlt_Addr21_16				= 0x40,
	GPIO_PxAlt_All						= 0x7F
} GPIO_PxAlt_type;

// Различные варианты альтернативных функций для PxA и PxD:
typedef enum {
	GPIO_PxAlt_Mode_SDRAM				= 0x0,
	GPIO_PxAlt_Mode_NAND				= 0x1,
	GPIO_PxAlt_Mode_MILSTD				= 0x3
} GPIO_PxAlt_Mode_type;

// Режимы прерываний:
typedef enum {
	GPIO_InterruptMode_Off,
	GPIO_InterruptMode_Posedge,
	GPIO_InterruptMode_Negedge,
	GPIO_InterruptMode_LowLvl,
	GPIO_InterruptMode_HighLvl,
} GPIO_InterruptMode;

/* Exported functions ------------------------------------------------------- */


/*******************Include Function*********************/
#ifdef __cplusplus
  extern "C"
	{
	#endif

  	  void 				HAL_GPIO_Init 				(GPIO_PortPi * const GPIO_Pi, const uint Pins, const GPIO_PinMode Mode);
  	  void 				HAL_GPIO_DeInit 			(GPIO_PortPi * const GPIO_Pi, const uint Pins);
  	  void 				HAL_GPIO_PxD_Init 			(const uint Pins, const GPIO_PinMode Mode);
  	  void 				HAL_GPIO_PxD_DeInit 		(const uint Pins);
  	  void 				HAL_GPIO_Px_AltInit 		(const GPIO_PxAlt_type PxAlt, const GPIO_PxAlt_Mode_type PxAltMode);
  	  void 				HAL_GPIO_Px_AltDeInit		(void);

  	  void 				HAL_GPIO_WritePin 			(GPIO_PortPi * const GPIO_Pi, const GPIO_PIN Pin, const GPIO_PinState NewState);
  	  GPIO_PinState 	HAL_GPIO_ReadPin 			(GPIO_PortPi * const GPIO_Pi, const GPIO_PIN Pin);
  	  void 				HAL_GPIO_WritePins 			(GPIO_PortPi * const GPIO_Pi, const uint Pins, const uint Data);
  	  void 				HAL_GPIO_TogglePins 		(GPIO_PortPi * const GPIO_Pi, const uint Pins);
  	  uint 				HAL_GPIO_ReadPins 			(GPIO_PortPi * const GPIO_Pi, const uint Pins);

  	  void 				HAL_GPIO_Px_WritePins 		(const GPIO_PxPort Px, const uint Pins, const uint Data);
  	  uint 				HAL_GPIO_Px_ReadPins 		(const GPIO_PxPort Px, const uint Pins);

  	  void 				HAL_GPIO_InterruptConfig 	(GPIO_PortPi * const GPIO_Pi, const uint Pins, const GPIO_InterruptMode Mode);
  	  uint 				HAL_GPIO_InterruptCheck		(GPIO_PortPi * const GPIO_Pi, const uint Pins);
  	  void 				HAL_GPIO_InterruptEdgeClear	(GPIO_PortPi * const GPIO_Pi, const uint Pins);

	#ifdef __cplusplus
	}
#endif // __cplusplus

/********************************************************/



#endif
