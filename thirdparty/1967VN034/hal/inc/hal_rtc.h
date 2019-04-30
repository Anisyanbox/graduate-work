/**********************************************************************************************************************
  Copyright (c) 2016 Milandr Corporation. All rights reserved.

  History:
  	  13-Dec-2016 Pavel Zatonsky   - Created
**********************************************************************************************************************/
#ifndef __HAL_RTC_H
#define __HAL_RTC_H


/************************************************ INCLUDES ***********************************************************/


#ifndef __cplusplus
#define inline __inline
#endif /* __cplusplus */

#define __IO			volatile
#define __WDT_REINIT	0x04072013

enum RTCRegType {rtcCNT, rtcMR, rtcWDT, rtcTDIV, rtcCR, rtcSDIV, rtcTICVAL, rtcSECVAL};

typedef struct
{
	__IO unsigned int RTC_CNT;   /*!< RTC счетчик секунд,                                         Address offset: 0x00 */
	__IO unsigned int RTC_MR;    /*!< RTC регистр сравнения,                                      Address offset: 0x01 */
	__IO unsigned int WDT_CNT;   /*!< RTC текущее значение сторожевого счетчика,                  Address offset: 0x02 */
	__IO unsigned int RTC_TDIV;  /*!< RTC таймера Текущее значение делителя тик-импульса,         Address offset: 0x03 */
	__IO unsigned int RTC_CR;    /*!< RTC Регистр управления,                                     Address offset: 0x04 */
	__IO unsigned int RTC_SDIV;  /*!< RTC Текущее значение делителя секунды,                      Address offset: 0x05 */
	__IO unsigned int TIC_VAL;   /*!< RTC Период тик-импульса минус 1, max 20 bit (1048575)       Address offset: 0x06 */
	__IO unsigned int SEC_VAL;   /*!< RTC Количество тик-импульсов в секунде,                     Address offset: 0x07 */
	__IO unsigned int RTC_BUSY;  /*!< RTC Флаг занятости интерфейса,                              Address offset: 0x08 */
} RTC_TypeDef;


#define LX_RTC                 ((RTC_TypeDef *) base_RTC )  // base_RTC=0x800001e0 



/* Exported functions ------------------------------------------------------- */


/*******************Include Function*********************/
#ifdef __cplusplus
  extern "C"
	{
	#endif
  	  void HAL_RTC_Busy(void);
  	  int HAL_RTC_RegRead(enum RTCRegType RTCReg);

  	  void HAL_RTC_AlarmIntEn(int MR_sec);
  	  void  HAL_RTC_WDogResetEn(int WDT_tic);
  	  void HAL_RTC_WDogIntEn(int WDT_tic);
  	  void HAL_RTC_TicIntEn(void);

  	  void HAL_RTC_AlarmIntDis(void);
  	  void  HAL_RTC_WDogResetDis(void);
  	  void HAL_RTC_WDogIntDis(void);
  	  void HAL_RTC_TicIntDis(void);

  	  void HAL_RTC_InitTicPeriod(int NumOfXTI);
  	  int  HAL_RTC_InitTicPeriodUS(int XTI_khz, int Period_us);
  	  void HAL_RTC_InitSecPeriod(int NumOfTic);
        
  	  void HAL_RTC_WDogLock(void);
  	  void HAL_RTC_Lock(void);
		
	#ifdef __cplusplus
	}
#endif // __cplusplus

/********************************************************/

#endif
