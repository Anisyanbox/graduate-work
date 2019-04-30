/**********************************************************************************************************************
  Copyright (c) 2016 Milandr Corporation. All rights reserved.

  History:
  	  Zatonsky Pavel - Created.
**********************************************************************************************************************/
#include <hal_1967VN034R1.h>
#include <sysreg.h>
#include <builtins.h>


int HAL_LinkRx_GetStat(int link_num){
	switch(link_num){
	case 0:
		return (int)__builtin_sysreg_read(__LRSTAT0);
	case 1:
		return (int)__builtin_sysreg_read(__LRSTAT1);
	default: return -1;
	}
}

int HAL_LinkTx_GetStat(int link_num){
	switch(link_num){
	case 0:
		return (int)__builtin_sysreg_read(__LTSTAT0);
	case 1:
		return (int)__builtin_sysreg_read(__LTSTAT1);
	default: return -1;
	}
}

int HAL_LinkRx_GetStatCl(int link_num){
	switch(link_num){
	case 0:
		return (int)__builtin_sysreg_read(__LRSTATC0);
	case 1:
		return (int)__builtin_sysreg_read(__LRSTATC1);
	default: return -1;
	}
}

int HAL_LinkTx_GetStatCl(int link_num){
	switch(link_num){
	case 0:
		return (int)__builtin_sysreg_read(__LTSTATC0);
	case 1:
		return (int)__builtin_sysreg_read(__LTSTATC1);
	default: return -1;
	}
}


int HAL_LinkRx_Enable(int link_num, LinkRx_Init_type *LRxInit, LinkRxEx_type *LRxExInit){
	unsigned int tmpreg = 0;
	//Check Sum
	tmpreg |= LRxInit->CheckSum;
	//Check BCMPI
	tmpreg |= LRxInit->CheckBCMPI;
	//Time Out Interrupt
	tmpreg |= LRxInit->TOIntEn;
	//Overwrite Interrupt
	tmpreg |= LRxInit->OVRIntEn;
	//Data Size
	tmpreg |= LRxInit->DataSize;
	
	if ( LRxExInit )
	{
		tmpreg |= LRxExInit->GpsClk;
		tmpreg |= LRxExInit->RxDest;
		tmpreg |= LRxExInit->AdcDataSize;
		tmpreg |= LRxExInit->Rcode;
		tmpreg |= LRxExInit->BitOrder;
	}
	
	//Link Num
	switch(link_num){
	case 0:
		//*(unsigned *)GPC_ALT_LOAD_LOC |= (1<<24); //ALT Func for GPC_24 = ACKO 0
		__builtin_sysreg_write(__LRCTL0, tmpreg);
		tmpreg |= LRX_EN;
		__builtin_sysreg_write(__LRCTL0, tmpreg);
		break;
	case 1:
		//*(unsigned *)GPC_ALT_LOAD_LOC |= (1<<28); //ALT Func for GPC_28 = ACKO 1
		tmpreg |= (1<<16);//CLK1 Source for Link1
		__builtin_sysreg_write(__LRCTL1, tmpreg);
		tmpreg |= LRX_EN;
		__builtin_sysreg_write(__LRCTL1, tmpreg);
		break;
	default: return -1;
	}
	return 0;
}

void HAL_LinkRx_Disable(int link_num){
	switch(link_num){
	case 0:
	//	*(unsigned *)GPC_ALT_LOAD_LOC &= ~(0x1<<27); //ALT Func for GPC_27 = Disable
		__builtin_sysreg_write(__LRCTL0, 0);
		break;
	case 1:
	//	*(unsigned *)GPC_ALT_LOAD_LOC &= ~(0x1<<31); //ALT Func for GPC_31 = Disable
		__builtin_sysreg_write(__LRCTL1, 0);
		break;
	}
}

int HAL_LinkCore_Receive(int link_num, void *BuffPtr, int size){
	__builtin_quad bq;
	int i, *bqPtr, *bp, LRStat;
	bp = (int *)BuffPtr;
	size>>=2; // size/4
	switch(link_num){
	case 0:
		LRStat = __builtin_sysreg_read(__LRSTAT0);
		if(!(LRStat&0x40)) return -1;
		for(i=0;i<size;i++){
			while((LRStat&0x41) != 0x41){
				LRStat = __builtin_sysreg_read(__LRSTAT0);
				if(LRStat & 0x3C) return -1;
			}
			bq = __builtin_sysreg_read4(__LBUFRX0);
			bqPtr = (int *)&bq;
			*(bp+0) = *(bqPtr+0);
			*(bp+1) = *(bqPtr+1);
			*(bp+2) = *(bqPtr+2);
			*(bp+3) = *(bqPtr+3);
			bp+=4;
		}
		break;
	case 1:
		LRStat = __builtin_sysreg_read(__LRSTAT1);
		if(!(LRStat&0x40)) return -1;
		for(i=0;i<size;i++){
			while((LRStat&0x41) != 0x41){
				LRStat = __builtin_sysreg_read(__LRSTAT1);
				if(LRStat & 0x3C) return -1;
			}
			bq = __builtin_sysreg_read4(__LBUFRX1);
			bqPtr = (int *)&bq;
			*(bp+0) = *(bqPtr+0);
			*(bp+1) = *(bqPtr+1);
			*(bp+2) = *(bqPtr+2);
			*(bp+3) = *(bqPtr+3);
			bp+=4;
		}
		break;
	}
	return 0;
}

void HAL_LinkDMA_Receive(int link_num, void *tcb){
	HAL_DMA_DestRqstSet(8+link_num,dmaSTD);
	HAL_DMA_WriteDC(8+link_num,tcb);
}


int HAL_LinkTx_Enable(int link_num, LinkTx_Init_type *LTxInit, LinkTxEx_type *LTxExInit){
	unsigned int tmpreg = 0;
	//Check Sum
	tmpreg |= LTxInit->CheckSum;
	//Check BCMPI
	tmpreg |= LTxInit->CheckBCMPO;
	//Time Out Interrupt
	tmpreg |= LTxInit->TOIntEn;
	//Data Size
	tmpreg |= LTxInit->DataSize;
	//Link Clk Source
	tmpreg |= LTxInit->ClkSource;
	
	if( LTxExInit )
	{
		tmpreg |= LTxExInit->TxSource;
		tmpreg |= LTxExInit->Tcode;
		tmpreg |= LTxExInit->CheckACKI;
	}
	
	if(LTxInit->ClkSource == Link_TxClk_Master)
		tmpreg |= LTxInit->ClkDiv;
	//Link Num
	switch(link_num){
	case 0:
		__builtin_sysreg_write(__LTCTL0, tmpreg);
		tmpreg |= LTX_EN;
		__builtin_sysreg_write(__LTCTL0, tmpreg);
		break;
	case 1:
		__builtin_sysreg_write(__LTCTL1, tmpreg);
		tmpreg |= LTX_EN;
		__builtin_sysreg_write(__LTCTL1, tmpreg);
		break;
	default: return -1;
	}
	return 0;
}

void HAL_LinkTx_Disable(int link_num){
	switch(link_num){
	case 0:
	//	*(unsigned *)GPC_ALT_LOAD_LOC &= ~(0xA<<24); //ALT Func for GPC_24,26 = Disable
		__builtin_sysreg_write(__LTCTL0, 0);
		break;
	case 1:
	//	*(unsigned *)GPC_ALT_LOAD_LOC &= ~(0xA<<28); //ALT Func for GPC_28,30 = Disable
		__builtin_sysreg_write(__LTCTL1, 0);
		break;
	}
}

int HAL_LinkCore_Transmit(int link_num, void *BuffPtr, int size){
	int *bp, i, LTStat = 0;
	bp = (int *)BuffPtr;
	size>>=2;
	switch(link_num){
	case 0:
		for(i=0;i<size;i++){
			while(LTStat != 3){
				LTStat = __builtin_sysreg_read(__LTSTAT0);
				if(LTStat & 0xC) return -1;
			}
			__builtin_sysreg_write4(__LBUFTX0, *(__builtin_quad *)bp);
			bp+=4;
		}
		break;
	case 1:
		for(i=0;i<size;i++){
			while(LTStat != 3){
				LTStat = __builtin_sysreg_read(__LTSTAT1);
				if(LTStat & 0xC) return -1;
			}
			__builtin_sysreg_write4(__LBUFTX1, *(__builtin_quad *)bp);
			bp+=4;
		}
		break;
	default: return -1;
	}
	return 0;
}

void HAL_LinkDMA_Transmit(int link_num, void *tcb){
	HAL_DMA_SourceRqstSet(4+link_num,dmaSTD);
	HAL_DMA_WriteDC(4+link_num,tcb);
}



