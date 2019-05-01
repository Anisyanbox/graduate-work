/**********************************************************************************************************************
  Copyright (c) 2016 Milandr Corporation. All rights reserved.

  History:
  	  Zatonsky Pavel - Created.
**********************************************************************************************************************/
#include <hal_1967VN034R1.h>


int HAL_RTC_RegRead(enum RTCRegType RTCReg){
  	asm("j8 = [j4 + 0x800001E0];;");
  	asm("j8 = [j4 + 0x800001E0];;");
  	while(LX_RTC->RTC_BUSY == 1);
  	return 0;
}

void HAL_RTC_Busy(void){
	 while(LX_RTC->RTC_BUSY == 1);
}

void HAL_RTC_InitTicPeriod(int NumOfXTI){
	NumOfXTI--;
	while(LX_RTC->RTC_BUSY == 1);
	LX_RTC->TIC_VAL = NumOfXTI;
	while(LX_RTC->RTC_BUSY == 1);
}

int HAL_RTC_InitTicPeriodUS(int XTI_khz, int Period_us){
	int divider;
	float real_period;
	divider = ((XTI_khz)/(Period_us*1000));
	real_period = (1/(float)XTI_khz)*(float)divider;
	while(LX_RTC->RTC_BUSY == 1);
	LX_RTC->TIC_VAL = divider - 1;
	while(LX_RTC->RTC_BUSY == 1);
	return (int)(real_period*1000000); //ns
}

void HAL_RTC_InitSecPeriod(int NumOfTic){
	NumOfTic--;
	while(LX_RTC->RTC_BUSY == 1);
	LX_RTC->SEC_VAL = NumOfTic;
	while(LX_RTC->RTC_BUSY == 1);
}


void HAL_RTC_AlarmIntEn(int MR_sec){
	int tmp32;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 = LX_RTC->RTC_CR;
	tmp32 = LX_RTC->RTC_CR;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 &= ~ (1<<10);
	LX_RTC->RTC_CR = tmp32;			//Enable Alarm Interrupt
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 = LX_RTC->RTC_CNT;
	tmp32 = LX_RTC->RTC_CNT;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 += MR_sec;
	LX_RTC->RTC_MR = tmp32;//Init Alarm
	while(LX_RTC->RTC_BUSY == 1);
}

void HAL_RTC_AlarmIntEnExactTime(int MRExact_sec){
	int tmp32;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 = LX_RTC->RTC_CR;
	tmp32 = LX_RTC->RTC_CR;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 &= ~ (1<<10);
	LX_RTC->RTC_CR = tmp32;			//Enable Alarm Interrupt
	while(LX_RTC->RTC_BUSY == 1);

	LX_RTC->RTC_MR = MRExact_sec;	//Init Alarm
	while(LX_RTC->RTC_BUSY == 1);
}


void HAL_RTC_TicIntEn(void){
	int tmp32;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 = LX_RTC->RTC_CR;
	tmp32 = LX_RTC->RTC_CR;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 &= ~ (1<<8);
	LX_RTC->RTC_CR = tmp32;			//Enable TIC Interrupt
	while(LX_RTC->RTC_BUSY == 1);
}

void HAL_RTC_WDogIntEn(int WDT_tic){
	int tmp32;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 = LX_RTC->RTC_CR;
	tmp32 = LX_RTC->RTC_CR;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 &= ~ (1<<9);

	switch(WDT_tic){
	case 1:
		tmp32 &= ~(7<<4); //reset WDT_SEL
		break;
	case 2:
		tmp32 &= ~(7<<4); //reset WDT_SEL
		tmp32 |= (1<<4);
		break;
	case 4:
		tmp32 &= ~(7<<4); //reset WDT_SEL
		tmp32 |= (2<<4);
		break;
	case 8:
		tmp32 &= ~(7<<4); //reset WDT_SEL
		tmp32 |= (3<<4);
		break;
	case 16:
		tmp32 &= ~(7<<4); //reset WDT_SEL
		tmp32 |= (4<<4);
		break;
	case 32:
		tmp32 &= ~(7<<4); //reset WDT_SEL
		tmp32 |= (5<<4);
		break;
	case 64:
		tmp32 &= ~(7<<4); //reset WDT_SEL
		tmp32 |= (6<<4);
		break;
	case 128:
		tmp32 &= ~(7<<4); //reset WDT_SEL
		tmp32 |= (7<<4);
		break;
	default: break;
	}

	LX_RTC->WDT_CNT = 0x04072013;	//A little magic
	while(LX_RTC->RTC_BUSY == 1);

	LX_RTC->RTC_CR = tmp32;			//Enable TIC Interrupt
	while(LX_RTC->RTC_BUSY == 1);
}

void HAL_RTC_WDogHWResetEn(int WDT_tic){
	int tmp32;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 = LX_RTC->RTC_CR;
	tmp32 = LX_RTC->RTC_CR;
	while(LX_RTC->RTC_BUSY == 1);


	switch(WDT_tic){
	case 1:
		tmp32 &= ~(7<<4); //reset WDT_SEL
		break;
	case 2:
		tmp32 &= ~(7<<4); //reset WDT_SEL
		tmp32 |= (1<<4);
		break;
	case 4:
		tmp32 &= ~(7<<4); //reset WDT_SEL
		tmp32 |= (2<<4);
		break;
	case 8:
		tmp32 &= ~(7<<4); //reset WDT_SEL
		tmp32 |= (3<<4);
		break;
	case 16:
		tmp32 &= ~(7<<4); //reset WDT_SEL
		tmp32 |= (4<<4);
		break;
	case 32:
		tmp32 &= ~(7<<4); //reset WDT_SEL
		tmp32 |= (5<<4);
		break;
	case 64:
		tmp32 &= ~(7<<4); //reset WDT_SEL
		tmp32 |= (6<<4);
		break;
	case 128:
		tmp32 &= ~(7<<4); //reset WDT_SEL
		tmp32 |= (7<<4);
		break;
	default: break;
	}

	LX_RTC->RTC_CR = tmp32;			//Init Wdog
	while(LX_RTC->RTC_BUSY == 1);
	tmp32 |= (1<<2);

	LX_RTC->WDT_CNT = 0x04072013;	//A little magic
	while(LX_RTC->RTC_BUSY == 1);

	LX_RTC->RTC_CR = tmp32;			//Enable WDog
	while(LX_RTC->RTC_BUSY == 1);
}


void HAL_RTC_AlarmIntDis(void){
	int tmp32;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 = LX_RTC->RTC_CR;
	tmp32 = LX_RTC->RTC_CR;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 |=  (1<<10);
	LX_RTC->RTC_CR = tmp32;			//Disable Alarm Interrupt
	while(LX_RTC->RTC_BUSY == 1);
}

void HAL_RTC_TicIntDis(void){
	int tmp32;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 = LX_RTC->RTC_CR;
	tmp32 = LX_RTC->RTC_CR;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 |=  (1<<8);
	LX_RTC->RTC_CR = tmp32;			//Disable Tic Interrupt
	while(LX_RTC->RTC_BUSY == 1);
}

void HAL_RTC_WDogIntDis(void){
	int tmp32;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 = LX_RTC->RTC_CR;
	tmp32 = LX_RTC->RTC_CR;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 |=  (1<<9);
	LX_RTC->RTC_CR = tmp32;			//Disable WDog Interrupt
	while(LX_RTC->RTC_BUSY == 1);
}

void HAL_RTC_WDogHWResetDis(void){
	int tmp32;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 = LX_RTC->RTC_CR;
	tmp32 = LX_RTC->RTC_CR;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 &= ~(1 << 2);
	LX_RTC->RTC_CR = tmp32;			//Disable WDog core reset
	while(LX_RTC->RTC_BUSY == 1);
}



void HAL_RTC_WDogLock(void){
	int tmp32;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 = LX_RTC->RTC_CR;
	tmp32 = LX_RTC->RTC_CR;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 |= (1<<3);
	LX_RTC->RTC_CR = tmp32;			//Lock WDOG
	while(LX_RTC->RTC_BUSY == 1);
}

void HAL_RTC_Lock(void){
	int tmp32;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 = LX_RTC->RTC_CR;
	tmp32 = LX_RTC->RTC_CR;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 |= (1<<7);
	LX_RTC->RTC_CR = tmp32;			//Lock WDOG
	while(LX_RTC->RTC_BUSY == 1);
}

void HAL_RTC_WDogUnLock(void){
	int tmp32;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 = LX_RTC->RTC_CR;
	tmp32 = LX_RTC->RTC_CR;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 &= ~(1<<3);
	LX_RTC->RTC_CR = tmp32;			//Lock WDOG
	while(LX_RTC->RTC_BUSY == 1);
}

void HAL_RTC_UnLock(void){
	int tmp32;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 = LX_RTC->RTC_CR;
	tmp32 = LX_RTC->RTC_CR;
	while(LX_RTC->RTC_BUSY == 1);

	tmp32 &= ~(1<<7);
	LX_RTC->RTC_CR = tmp32;			//Lock WDOG
	while(LX_RTC->RTC_BUSY == 1);
}

