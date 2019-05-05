/**********************************************************************************************************************
  Copyright (c) 2016 Milandr Corporation. All rights reserved.

  History:
      13-Dec-2016 Pavel Zatonsky     - Created
      05-May-2019 Anisimov Alexander - Fixed
**********************************************************************************************************************/
#ifndef __HAL_RTC_H
#define __HAL_RTC_H


/************************************************ INCLUDES ***********************************************************/


#ifndef __cplusplus
#define inline __inline
#endif /* __cplusplus */

#define __IO      volatile
#define __WDT_REINIT  0x04072013

enum RTCRegType {
  rtcCNT,
  rtcMR,
  rtcWDT,
  rtcTDIV,
  rtcCR,
  rtcSDIV,
  rtcTICVAL,
  rtcSECVAL
};

typedef struct {
  __IO unsigned int RTC_CNT;    /* second cnt; 32 bits; Address offset: 0x00 */
  __IO unsigned int RTC_MR;     /* compare register; 32 bits; Address offset: 0x01 */
  __IO unsigned int WDT_CNT;    /* current value wdt cnt; 8 bits; Address offset: 0x02 */
  __IO unsigned int RTC_TDIV;   /* current value devider tic-impulse; 20 bits; Address offset: 0x03 */
  __IO unsigned int RTC_CR;     /* control register; 8 bits; Address offset: 0x04 */
  __IO unsigned int RTC_SDIV;   /* current value second devider; 16 bits; Address offset: 0x05 */
  __IO unsigned int TIC_VAL;    /* period tic-impulse; 20 bits; Address offset: 0x06 */
  __IO unsigned int SEC_VAL;    /* cnt tic-impulses in second; 16 bits; Address offset: 0x07 */
  __IO unsigned int RTC_BUSY;   /* busy flag; 1 bit; Address offset: 0x08 */
} RTC_TypeDef;


#define LX_RTC            ((RTC_TypeDef *) base_RTC )  // base_RTC=0x800001e0 

/*******************Include Function*********************/
#ifdef __cplusplus
extern "C" {
#endif
  void HAL_RTC_Busy(void);
  int HAL_RTC_RegRead(enum RTCRegType RTCReg);

  void HAL_RTC_AlarmIntEn(int MR_sec);
  void HAL_RTC_WDogResetEn(int WDT_tic);
  void HAL_RTC_WDogIntEn(int WDT_tic);
  void HAL_RTC_TicIntEn(void);

  void HAL_RTC_AlarmIntDis(void);
  void HAL_RTC_WDogResetDis(void);
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
