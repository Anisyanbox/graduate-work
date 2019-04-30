/**********************************************************************************************************************
  Copyright (c) 2016 Milandr Corporation. All rights reserved.

  History:
  	  Zatonsky Pavel - Created.
**********************************************************************************************************************/
#include <hal_1967VN034R1.h>
#include <sysreg.h>
#include <builtins.h>


#define TIC_PERIOD_GCF	16000
unsigned long long int ccntStart, ccntStop = 0;


#ifdef __HAL_1967VN034R2__
#pragma interrupt
void GetCoreFreq_HNDLR(){
	ccntStop = __read_ccnt();
	HAL_Interrupt_Disable(intTIC);
}


int HAL_SYS_GetCoreFreq(int XTI_khz){

	float untmp32;
	float currentFreq;

	//HAL_RTC_InitTicPeriod(1);				//TIC Period Reset
	HAL_RTC_InitTicPeriod(TIC_PERIOD_GCF);	//TIC Period Init

	ccntStart = __read_ccnt();
	HAL_Interrupt_RqstReset(intTIC);		//Reset Posible int Rqst

	HAL_Interrupt_Enable(intTIC, (unsigned int)GetCoreFreq_HNDLR);

	while(!ccntStop);

	//untmp32 = (float)(ccntStop - ccntStart)/(float)(ALARM_TIME_GCF*SEC_PERIOD_GCF*TIC_PERIOD_GCF);
	untmp32 = (float)(ccntStop - ccntStart)/(float)(TIC_PERIOD_GCF);
	currentFreq = untmp32*(float)XTI_khz;

	//__RDS;
	return ((int)currentFreq);

}
#endif
/*************************************************************************************************/
void HAL_SYS_ExtBusEnable(int size){
	unsigned int tmp = 0;
	switch(size){
	case 16:
		tmp =	PX_ALT_PDB0 | PX_ALT_PDB1 | PX_ALT_PAB0
				| PX_ALT_PAB1 | PX_ALT_PAB2;
		break;
	case 32:
		tmp = 	PX_ALT_PDB0 | PX_ALT_PDB1 | PX_ALT_PDB2 | PX_ALT_PDB3
				| PX_ALT_PAB0 | PX_ALT_PAB1 | PX_ALT_PAB2;
		break;
	}
	*(unsigned *)PX_ALT_LOC = tmp;
}
/*************************************************************************************************/
void HAL_SYS_ExtBusDisable(void){
	*(unsigned *)PX_ALT_LOC = 0;
}
/*************************************************************************************************/
void HAL_SYS_SDRAMEnable(int sdrconValue){
	*(unsigned *)GPC_ALT_SET_LOC = (0x3FF<<8);		//SDRAM Func for GPIO
	__builtin_sysreg_write(__SDRCON, sdrconValue);
	while( !(__builtin_sysreg_read(__SYSTAT)&(1<<13)) ); //Wait SDRAM Enable
}
/*************************************************************************************************/
void HAL_SYS_SDRAMDisable(void){
	*(unsigned *)GPC_ALT_CLEAR_LOC = (0x3FF<<8);	//SDRAM Func for GPIO
	__builtin_sysreg_write(__SDRCON, 0);
}
/*************************************************************************************************/
void HAL_SYS_SRAMEnable(int sysconValue){
	*(unsigned *)GPC_ALT_SET_LOC = (0x1F<<18);		//SRAM Func for GPIO
	__builtin_sysreg_write(__SYSCON, sysconValue);
}
/*************************************************************************************************/
void HAL_SYS_SRAMDisable(void){
	*(unsigned *)GPC_ALT_CLEAR_LOC = (0x1F<<18);	//SRAM Func for GPIO
	__builtin_sysreg_write(__SYSCON, 0);
}
/*************************************************************************************************/
void HAL_SYS_FlagEnable(void){
	*(unsigned *)GPC_ALT_SET_LOC = 0xF;
}
/*************************************************************************************************/
void HAL_SYS_FlagDisable(void){
	*(unsigned *)GPC_ALT_CLEAR_LOC = 0xF;
}
/*************************************************************************************************/
void HAL_Core_PrimariPriority(void){
	*(unsigned *)CMU_CFG1_LOC &= ~(1<<12);
}
/*************************************************************************************************/
void HAL_SYS_MultipleWriteSysconSdrconEn(void){
	LX_CMU->CFG1.b.SYS_WE = 1;
}
/*************************************************************************************************/





