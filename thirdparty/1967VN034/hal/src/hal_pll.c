/**********************************************************************************************************************
  Copyright (c) 2015 Milandr Corporation. All rights reserved.

  History:
   08-May-2015 Andrei Abramchuk - Created.
   17-April-2019 Anisimov Alexander - Added some comments and fix
**********************************************************************************************************************/
/************************************************ INCLUDES ***********************************************************/
#include <stdio.h>
#include <hal_1967VN034R1.h>
#include <sysreg.h>
#include <builtins.h>

/************************************************ DEFINITIONS ********************************************************/
#define FREQ_KHZ_RANGE1         (10000)
#define FREQ_KHZ_RANGE2         (16000)
#define FREQ_KHZ_RANGE3         (25000)
#define FREQ_KHZ_RANGE4         (40000)
#define FREQ_KHZ_RANGE5         (65000)
#define FREQ_KHZ_RANGE6         (100000)

#define PLL_FREQ_KHZ_MIN        (400000)
#define PLL_FREQ_KHZ_MAX        (800000)

#define RESULT_ERROR            (-1)

/************************************************ CONSTANTS **********************************************************/
/************************************************ VARIABLES **********************************************************/
PLL_Freq_type PLL_Freq;

/************************************************ STATIC FUNCTIONS PROTOTYPES ****************************************/
static void pause_clk(unsigned int clk)
{
    unsigned long long int stop = __read_ccnt();
    stop += clk;

    while ((((unsigned long long int)(__read_ccnt())) - stop) & ((unsigned long long int)1<<63));
}

static void HAL_PLL_CoreSwitch(PLL_ConfigTypeDef* pll_cfg){
	*((unsigned int*) CPU_CLK_CONFIG_LOC) &= ~(CPU_CPLL_SEL);
	*((unsigned int*)PLL_CORE_CFG_LOC) = pll_cfg->value;
	pause_clk(500);
}

static void HAL_PLL_LinkSwitch(PLL_ConfigTypeDef* pll_cfg)
{
	*((unsigned int*) CPU_CLK_CONFIG_LOC) &= ~(1<<7);		//LPLL_SEL ???? (for Rev. 1) (1<<7)
	pll_cfg->bypass = 1;
	*((unsigned int*)PLL_LINK_CFG_LOC) = pll_cfg->value;
	pll_cfg->bypass = 0;
	*((unsigned int*)PLL_LINK_CFG_LOC) = pll_cfg->value;
	pause_clk(2000);
}

static void HAL_PLL_BusSwitch(PLL_ConfigTypeDef* pll_cfg)
{
	*((unsigned int*) CPU_CLK_CONFIG_LOC) &= ~(CPU_BPLL_SEL);		//BPLL XTI
	pll_cfg->bypass = 1;
	*((unsigned int*)PLL_BUS_CFG_LOC) = pll_cfg->value;
	pll_cfg->bypass = 0;
	*((unsigned int*)PLL_BUS_CFG_LOC) = pll_cfg->value;
	pause_clk(2000);
	*((unsigned int*) CPU_CLK_CONFIG_LOC) |= (CPU_BPLL_SEL);		//BPLL SET
}

static int HAL_PLL_ConfigCalc(PLL_ConfigTypeDef* pll_cfg, unsigned int ref_freq, unsigned int pll_freq/*, unsigned int ext_range*/)
{
    unsigned int divr = 1;
    unsigned int divf;
    unsigned int divq = 0;
    unsigned int range;
    unsigned int ivco   = 0;
    unsigned int bypass = 0;

    float tmp;

 /*   if (!ext_range)
    if (((float)ref_freq / (float)pll_freq > (float)4.0) || ((float)pll_freq / (float)ref_freq > (float)4.0))
        return RESULT_ERROR;*/

    if ((ref_freq < FREQ_KHZ_RANGE1) || (ref_freq / 16 > FREQ_KHZ_RANGE6))
        return RESULT_ERROR;

    if ((pll_freq > PLL_FREQ_KHZ_MAX) || (pll_freq * 32 < PLL_FREQ_KHZ_MIN))
        return RESULT_ERROR;

    while (pll_freq < PLL_FREQ_KHZ_MIN)
    {
        pll_freq *= 2;
        divq += 1;
    }

    while ((ref_freq / divr >= FREQ_KHZ_RANGE1) && (divr < 16))
    {
        divr += 1;
    }

    divr -= 1;
    tmp = (float)ref_freq / (float)divr;
    divr -= 1;

    if      (tmp < (float)FREQ_KHZ_RANGE2) range = 1;
    else if (tmp < (float)FREQ_KHZ_RANGE3) range = 2;
    else if (tmp < (float)FREQ_KHZ_RANGE4) range = 3;
    else if (tmp < (float)FREQ_KHZ_RANGE5) range = 4;
    else                                   range = 5;

    tmp = (float)pll_freq / tmp + (float)0.5;
    divf = (unsigned int)tmp - 2;

    tmp = (float)ref_freq * (float)(divf + 2) / (float)(divr + 1) / (float)(1 << divq) + (float)0.5;

    pll_cfg->divr = divr;
    pll_cfg->divf = divf;
    pll_cfg->divq = divq;
    pll_cfg->range = range;
    pll_cfg->ivco = ivco;
    pll_cfg->bypass = bypass;

    pll_cfg->ref_freq_khz = ref_freq;
    pll_cfg->pll_freq_khz = (unsigned int)tmp;

    return (int)tmp;
}

/************************************************ IMPLEMENTATION *****************************************************/
void HAL_PLL_SleepOn(void)
{
	unsigned int sqctlBuff, rtcCR, tmp32;
	sqctlBuff = __builtin_sysreg_read(__SQCTL);
	__builtin_sysreg_write(__SQCTLCL,0x3FFB);
	rtcCR = *(unsigned int *)RTC_CR_LOC;
	rtcCR = *(unsigned int *)RTC_CR_LOC;
	*(unsigned int *)RTC_CR_LOC = rtcCR | 0x600;
	while(*(unsigned int *)RTC_BUSY_LOC != 0){};

	tmp32 = *(unsigned int *)CMU_CFG4_LOC;
	*(unsigned int *)CMU_CFG4_LOC = tmp32 | 4;
	pause_clk(16);
	*(unsigned int *)CMU_CFG4_LOC = tmp32;
	pause_clk(8);

	*(unsigned int *)CMU_CFG4_LOC = tmp32 | 4;
	*(unsigned int *)CMU_CFG4_LOC = tmp32 | 5;
	pause_clk(16);
	*(unsigned int *)CMU_CFG4_LOC = tmp32 | 1;
	__builtin_sysreg_write(__SQCTL,sqctlBuff);
	*(unsigned int *)RTC_CR_LOC = rtcCR;
}

void HAL_PLL_CoreSetup( unsigned int ref_freq, unsigned int pll_freq )
{
	PLL_ConfigTypeDef pll_cfg;
	PLL_Freq.CoreClk = HAL_PLL_ConfigCalc( &pll_cfg, ref_freq, pll_freq );
	HAL_PLL_CoreSwitch( &pll_cfg );
}

void HAL_PLL_LinkSetup( unsigned int ref_freq, unsigned int pll_freq )
{
	PLL_ConfigTypeDef pll_cfg;
	PLL_Freq.LinkClk = HAL_PLL_ConfigCalc( &pll_cfg, ref_freq, pll_freq );
	HAL_PLL_LinkSwitch( &pll_cfg );
}

void HAL_PLL_BusSetup( unsigned int ref_freq, unsigned int pll_freq )
{
	PLL_ConfigTypeDef pll_cfg;
	PLL_Freq.BusClk = HAL_PLL_ConfigCalc( &pll_cfg, ref_freq, pll_freq );
	HAL_PLL_BusSwitch( &pll_cfg );
}

void HAL_Pll_CoreStart(void)
{
	*((unsigned int*) CPU_CLK_CONFIG_LOC) |= CPU_CPLL_SEL;
}

void HAL_Pll_LinkStart(void)
{
	*((unsigned int*) CPU_CLK_CONFIG_LOC) |= CPU_LPLL_SEL;
}

void HAL_Pll_BusStart(void)
{
	*((unsigned int*) CPU_CLK_CONFIG_LOC) |= CPU_BPLL_SEL;
}

void HAL_XTI_CoreSwitch(void)
{
	*((unsigned int*) CPU_CLK_CONFIG_LOC) &= ~(CPU_CPLL_SEL);
	pause_clk(100);
}

void HAL_XTI_BusSwitch(void)
{
	*((unsigned int*) CPU_CLK_CONFIG_LOC) &= ~(CPU_BPLL_SEL);
}

void HAL_XTI_LinkSwitch(void)
{
	PLL_ConfigTypeDef pll_cfg;
	*((unsigned int*) CPU_CLK_CONFIG_LOC) &= ~(1<<7);		//LPLL_SEL ???? (for Rev. 1) (1<<7)
	pll_cfg.value = *((unsigned int*)PLL_LINK_CFG_LOC);
	pll_cfg.bypass = 1;
	*((unsigned int*)PLL_LINK_CFG_LOC) = pll_cfg.value;
}

void HAL_PLL_BusSwitchHalfCore(void)
{
	*((unsigned int*) CPU_CLK_CONFIG_LOC) |= (CPU_BPLL_SEL) | (1<<4);		//BPLL = CPLL / 2
}

void HAL_PLL_BusSwitchFourthCore(void)
{
	*((unsigned int*) CPU_CLK_CONFIG_LOC) |= (CPU_BPLL_SEL) | (2<<4);		//BPLL = CPLL / 4
}

void HAL_PLL_BusSwitchEighthCore(void)
{
	*((unsigned int*) CPU_CLK_CONFIG_LOC) |= (CPU_BPLL_SEL) | (3<<4);		//BPLL = CPLL / 8
}

void HAL_PLL_StartCoreSync(void)
{
	*((unsigned int*) CPU_CLK_CONFIG_LOC) &= ~(CPU_DIS_CC);
}

void HAL_PLL_StartExtBusSync(void)
{
	*((unsigned int*) CPU_CLK_CONFIG_LOC) &= ~(CPU_DIS_BC);
}

void HAL_PLL_StopCoreSync(void)
{
	*((unsigned int*) CPU_CLK_CONFIG_LOC) |= CPU_DIS_CC;
}

void HAL_PLL_StopExtBusSyn(void)
{
	*((unsigned int*) CPU_CLK_CONFIG_LOC) |= CPU_DIS_BC;
}

int HAL_PLL_GetRealCoreClock(void)
{
	return PLL_Freq.CoreClk;
}

int HAL_PLL_GetRealBusClock(void)
{
	return PLL_Freq.BusClk;
}

int HAL_PLL_GetRealLinkClock(void)
{
	return PLL_Freq.LinkClk;
}
