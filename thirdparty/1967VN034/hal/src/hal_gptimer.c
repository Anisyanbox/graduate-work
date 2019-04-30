/**********************************************************************************************************************
  Copyright (c) 2017 Milandr Corporation. All rights reserved.

  History:
  	  27-Feb-2017 Ivan Osadchy   - Created
**********************************************************************************************************************/
#include <hal_1967VN034R1.h>
#include <hal_gptimer.h>

void HAL_GPTimer_Init (GPTimer_X Timer, u64 Count, GPTimer_State State) {
	if (Timer > GPTimer_1) 				return;
	if (State > GPTimer_State_Enable) 	return;

	HAL_GPTimer_SetCount (Timer, Count);
	HAL_GPTimer_SetState (Timer, State);

}


void HAL_GPTimer_DeInit (GPTimer_X Timer) {

	HAL_GPTimer_Init (Timer, 0, GPTimer_State_Disable);

}

u64 HAL_GPTimer_GetCurrent (GPTimer_X Timer) {

	__IO u32 *pReg 	= ((__IO u32*)&LX_GPTIMER->Timer_curr[Timer]);
	u64 Curr;
	u32 *pCurr 	= ((u32*)&Curr);

	*pCurr++ 	= *pReg++;
	*pCurr 		= *pReg;

	return Curr;

	//return LX_GPTIMER->Timer_curr[Timer];

}

void HAL_GPTimer_SetCount (GPTimer_X Timer, u64 Count) {

	u32 *pCount = ((u32*)&Count);
	__IO u32 *pTimer = ((__IO u32*)&LX_GPTIMER->Timer_count[(u8) Timer]);

	*pTimer++ 	= *pCount++;
	*pTimer 	= *pCount;

	//LX_GPTIMER->Timer_count[(u8) Timer] = Count;

}

void HAL_GPTimer_SetCountNow (GPTimer_X Timer, u64 Count) {

	GPTimer_State State = HAL_GPTimer_GetState (Timer);
	HAL_GPTimer_SetState (Timer, GPTimer_State_Disable);
	HAL_GPTimer_SetCount (Timer, Count);
	HAL_GPTimer_SetState (Timer, State);

}

u64 HAL_GPTimer_GetCount (GPTimer_X Timer) {

	__IO u32 *pReg 	= ((__IO u32*)&LX_GPTIMER->Timer_count[Timer]);
	u64 Count;
	u32 *pCount = ((u32*)&Count);

	*pCount++ 	= *pReg++;
	*pCount 	= *pReg;

	return Count;

	//return LX_GPTIMER->Timer_count[(u8) Timer];

}

void HAL_GPTimer_SetState (GPTimer_X Timer, GPTimer_State State) {

	if (Timer == GPTimer_0) LX_GPTIMER->CTRL.T0.ena = State;
	if (Timer == GPTimer_1) LX_GPTIMER->CTRL.T1.ena = State;

}

GPTimer_State HAL_GPTimer_GetState (GPTimer_X Timer) {

	return ((GPTimer_State) ((Timer == GPTimer_0)? LX_GPTIMER->CTRL.T0.ena : LX_GPTIMER->CTRL.T1.ena));

}

void HAL_GPTimers_SetState 	(GPTimer_State Timer0, GPTimer_State Timer1) {

	u32 State = (((u32) Timer1) << 1) | ((u32) Timer0);

	LX_GPTIMER->CTRL.All.ena = State;

}
