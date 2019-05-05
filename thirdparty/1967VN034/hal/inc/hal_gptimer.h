/**********************************************************************************************************************
  Copyright (c) 2017 Milandr Corporation. All rights reserved.

  History:
  	  07-Mar-2017 Ivan Osadchy   - Created
**********************************************************************************************************************/
#ifndef __HAL_GPTIMER_H
#define __HAL_GPTIMER_H


/************************************************ INCLUDES ***********************************************************/


#define 	__IO                volatile
typedef 	unsigned int 			  u32;
typedef 	unsigned long long  u64;
typedef 	unsigned char 			u8;

typedef struct {
	union {
		u32 word;
		struct {
			u32	res0 		: 4; 		// 3:0
			u32 ena			: 2;		// 5:4
			u32 res1 		: 26;   // 31:6
		} All;
		struct {
			u32	res0 		: 4; 		// 3:0
			u32 ena			: 1;		// 4
			u32 res1 		: 27;   // 31:5
		} T0;
		struct {
			u32	res0 		: 5; 		// 4:0
			u32 ena			: 1;		// 5
			u32 res1 		: 26;   // 31:6
		} T1;
	} CTRL;
	u64 Timer_curr[2];
	u64 Timer_count[2];
} GPTIMER_TypeDef;

#define 	LX_GPTIMER  			((__IO GPTIMER_TypeDef *) 0x8000034E)

typedef enum {
	GPTimer_0 	= 0,
	GPTimer_1 	= 1,
} GPTimer_X;

typedef enum {
	GPTimer_State_Disable	= 0,
	GPTimer_State_Enable 	= 1,
} GPTimer_State;

/*******************Include Function*********************/
#ifdef __cplusplus
extern "C" {
#endif
  void HAL_GPTimer_Init(GPTimer_X Timer, u64 Count, GPTimer_State State);
  void HAL_GPTimer_DeInit(GPTimer_X Timer);

  u64  HAL_GPTimer_GetCurrent(GPTimer_X Timer);

  void HAL_GPTimer_SetCount(GPTimer_X Timer, u64 Count);
  void HAL_GPTimer_SetCountNow(GPTimer_X Timer, u64 Count);
  u64  HAL_GPTimer_GetCount(GPTimer_X Timer);
  void HAL_GPTimer_SetState(GPTimer_X Timer, GPTimer_State State);
  GPTimer_State HAL_GPTimer_GetState(GPTimer_X Timer);

  void HAL_GPTimers_SetState(GPTimer_State Timer0, GPTimer_State Timer1);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif
