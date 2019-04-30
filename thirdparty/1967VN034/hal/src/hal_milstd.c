/**********************************************************************************************************************
  Copyright (c) 2017 Milandr Corporation. All rights reserved.

  History:
  	  Zatonsky Pavel - Created.
**********************************************************************************************************************/

#include <hal_1967VN034R1.h>

void HAL_MILSTD_Reset(MILSTD_type *MILSTDx){
	MILSTDx->CONTROL.b.MR = 1;
	return;
}

void HAL_MILSTD_Init(MILSTD_type *MILSTDx, MILSTD_Init_type *InitStruct, unsigned int SOC_CLK_KHz){
	int tmp;
	MILSTDx->CONTROL.b.MR = 0;
	//MILSTDx->CONTROL.word = 0;
	tmp = SOC_CLK_KHz / 1000;
	if (tmp<128){
		MILSTDx->CONTROL.b.DIV6_0 = tmp;
		MILSTDx->CONTROL.b.DIV7   = 0;
	}
	else{
		MILSTDx->CONTROL.b.DIV6_0 = tmp & 0x7F;
		MILSTDx->CONTROL.b.DIV7   = 1;
	}
	MILSTDx->CONTROL.b.MODE = InitStruct->Mode;
	if (InitStruct->Mode == MILSTD_Mode_RT){
		MILSTDx->CONTROL.b.TRA = 1;
		MILSTDx->CONTROL.b.TRB = 1;
		MILSTDx->CONTROL.b.RTA = InitStruct->RTA;
	}
	else MILSTDx->CONTROL.word |= InitStruct->Channel;
	MILSTDx->CONTROL.b.RERR = InitStruct->ResetErr;
	MILSTDx->CONTROL.b.INVTR = InitStruct->InvPRD;
	MILSTDx->CONTROL.word |= InitStruct->Filter;
	MILSTDx->CONTROL.b.AUTOTUNE = InitStruct->AutoTune;
	MILSTDx->CONTROL.b.EN_XRTA = InitStruct->XRTA;
	MILSTDx->CONTROL.b.SYNC_DM = InitStruct->SyncDM;
}

void HAL_MILSTD_ITEnable(MILSTD_type *MILSTDx, MILSTD_IT_type ITName){
	MILSTDx->INTEN.word |= ITName;
}

void HAL_MILSTD_ITDisable(MILSTD_type *MILSTDx, MILSTD_IT_type ITName){
	MILSTDx->INTEN.word &= ~ITName;
}

void HAL_MILSTD_DeInit(MILSTD_type *MILSTDx){
	MILSTDx->CONTROL.b.MR = 1;
	MILSTDx->CONTROL.word = 0;
}


void HAL_MILSTD_CWInit(MILSTD_type *MILSTDx, unsigned int NumCW, unsigned int TxRxMode, unsigned int RTA, unsigned int amount, unsigned int SubAddr){
	unsigned int tmp;
	tmp = (RTA<<11) | (TxRxMode<<10) | (SubAddr<<5) | (amount<<0);
	switch(NumCW){
	case 1:
		MILSTDx->COMMWORD1.word = tmp;
		break;
	case 2:
		MILSTDx->COMMWORD2.word = tmp;
		break;
	default: break;
	}

}

void HAL_MILSTD_DTWrite (MILSTD_type *MILSTDx, void *Buff, unsigned int amount, unsigned int subaddr){
	unsigned int i, *bptr, AddrWD;
	AddrWD = subaddr*32;
	bptr = (unsigned int *)Buff;
	for (i=0;i<amount;i++){
		MILSTDx->DT[AddrWD++] = bptr[i];
	}
}

void HAL_MILSTD_StartCWTransmit (MILSTD_type *MILSTDx){
	MILSTDx->CONTROL.b.BCSTART = 1;
}

void HAL_MILSTD_DRRead (MILSTD_type *MILSTDx, void *Buff, unsigned int amount, unsigned int subaddr){
	unsigned int i, *bptr, AddrWD;
	AddrWD = subaddr * 32;
	bptr = (unsigned int *)Buff;
	for (i=0;i<amount;i++){
		bptr[i] = MILSTDx->DR[AddrWD++];
	}
}


