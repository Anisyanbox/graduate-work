/**********************************************************************************************************************
  Copyright (c) 2015 Milandr Corporation. All rights reserved.

  History:
   08-May-2015 Andrei Abramchuk - Created.
   17-April-2019 Anisimov Alexander - Added some comments and fix
**********************************************************************************************************************/
#ifndef __HAL_PLL_H_
#define __HAL_PLL_H_

/************************************************ INCLUDES ***********************************************************/
/************************************************ DEFINITIONS ********************************************************/
/************************************************ TYPES **************************************************************/
/**//**
 * \brief Type of PLL configuration structure.
 */
typedef struct
{
    unsigned int ref_freq_khz;
    unsigned int pll_freq_khz;
    union
    {
        unsigned int value;
        struct
        {
            unsigned int divr   : 4;
            unsigned int divf   : 7;
            unsigned int divq   : 3;
            unsigned int range  : 3;
            unsigned int ivco   : 3;
            unsigned int bypass : 1;
            unsigned int        : 11;
        };
    };
} PLL_ConfigTypeDef;

typedef struct
{
    int CoreClk;
    int LinkClk;
    int BusClk;
} PLL_Freq_type;

extern PLL_Freq_type PLL_Freq;

/************************************************ PROTOTYPES *********************************************************/
/******************************************************************************************************************//**
  \brief Calculate PLL configuration dividers and store actual frequencies values into pll_cfg structure.

  \param[out] pll_cfg      - result.
  \param[in]  ref_freq_khz - REF frequency (in kHz).
  \param[in]  pll_freq_khz - desired PLLOUT frequency (in kHz).
  \param[in]  ext_range    - 0 to limit calculated frequency to verified frequency range.

  \return                  -1 when error.
  \return                  actual PLLOUT frequency (in kHz).
**********************************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
    /* setup settings for PLL and start func */
    void HAL_PLL_CoreSetup(unsigned int ref_freq, unsigned int pll_freq);
    void HAL_PLL_StartCoreSync(void);
    void HAL_Pll_CoreStart(void);
    void HAL_PLL_StopCoreSync(void);

    void HAL_PLL_StartExtBusSync(void);
    void HAL_PLL_LinkSetup(unsigned int ref_freq, unsigned int pll_freq);
    void HAL_Pll_LinkStart(void);
    void HAL_PLL_StopExtBusSyn(void);

    void HAL_PLL_BusSetup(unsigned int ref_freq, unsigned int pll_freq);
    void HAL_Pll_BusStart(void);

    /* return clock from XTI */
    void HAL_XTI_CoreSwitch(void);
    void HAL_XTI_BusSwitch(void);
    void HAL_XTI_LinkSwitch(void);

    /* switching SDRAM(bus) clock to part from core clock */
    void HAL_PLL_BusSwitchHalfCore(void);
    void HAL_PLL_BusSwitchFourthCore(void);
    void HAL_PLL_BusSwitchEighthCore(void);

    /* sleep/non-sleep mode func */
    void HAL_PLL_SleepOn(void);

    /* returns value in KHz */
    int HAL_PLL_GetRealCoreClock(void);
    int HAL_PLL_GetRealBusClock(void);
    int HAL_PLL_GetRealLinkClock(void);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* __HAL_PLL_H_ */
