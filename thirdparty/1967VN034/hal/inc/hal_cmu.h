/**********************************************************************************************************************
  Copyright (c) 2017 Milandr Corporation. All rights reserved.

  History:
  	  Zatonsky Pavel - Created.
**********************************************************************************************************************/
#ifndef __HAL_CMU_H__
#define __HAL_CMU_H__

#include "hal_typedef.h"
#include "def1967VN034R1.h"
#define __IO 			volatile

typedef union {
	unsigned int word;
	struct {
		unsigned int RSV0			:	BITSIZEOF(CMU_CFG1_RSV0_MASK);
		unsigned int LINK_BW		:	BITSIZEOF(CMU_CFG1_LINK_BW_MASK);
		unsigned int SYS_WE			:	BITSIZEOF(CMU_CFG1_SYS_WE_MASK);
		unsigned int ARINC_T0_EN	:	BITSIZEOF(CMU_CFG1_ARINC_T0_EN_MASK);
		unsigned int ARINC_T1_EN	:	BITSIZEOF(CMU_CFG1_ARINC_T1_EN_MASK);
		unsigned int ARINC_T2_EN	:	BITSIZEOF(CMU_CFG1_ARINC_T2_EN_MASK);
		unsigned int ARINC_T3_EN	:	BITSIZEOF(CMU_CFG1_ARINC_T3_EN_MASK);
		unsigned int MIL_DIS   		:	BITSIZEOF(CMU_CFG1_MIL_DIS_MASK);
		unsigned int RSV1      		:	BITSIZEOF(CMU_CFG1_RSV1_MASK);
		unsigned int DMA_HP_EN		:	BITSIZEOF(CMU_CFG1_DMA_HP_EN_MASK);
		unsigned int RSV2      		:	BITSIZEOF(CMU_CFG1_RSV2_MASK);
	} b;
} CMU_CFG1_type;

typedef union {
	unsigned int word;
	struct {
		unsigned int DIVR	:	BITSIZEOF(CMU_CFG_PLL_DIVR_MASK  );
		unsigned int DIVF	:	BITSIZEOF(CMU_CFG_PLL_DIVF_MASK  );
		unsigned int DIVQ	:	BITSIZEOF(CMU_CFG_PLL_DIVQ_MASK  );
		unsigned int RANGE	:	BITSIZEOF(CMU_CFG_PLL_RANGE_MASK );
		unsigned int BYPASS	:	BITSIZEOF(CMU_CFG_PLL_BYPASS_MASK);
		unsigned int S		:	BITSIZEOF(CMU_CFG_PLL_S_MASK     );
		unsigned int RSV	:	BITSIZEOF(CMU_CFG_PLL_RSV_MASK   );
	} b;
} CMU_CFG_PLL_type;

typedef union {
	unsigned int word;
	struct {
		unsigned int CPLL_SEL	:	BITSIZEOF(CMU_CFG4_CPLL_SEL_MASK);
		unsigned int BPLL_SEL	:	BITSIZEOF(CMU_CFG4_BPLL_SEL_MASK);
		unsigned int DIS_CC  	:	BITSIZEOF(CMU_CFG4_DIS_CC_MASK  );
		unsigned int DIS_BC  	:	BITSIZEOF(CMU_CFG4_DIS_BC_MASK  );
		unsigned int BCLK_SEL	:	BITSIZEOF(CMU_CFG4_BCLK_SEL_MASK);
		unsigned int RSV0    	:	BITSIZEOF(CMU_CFG4_RSV0_MASK    );
		unsigned int LPLL_SEL	:	BITSIZEOF(CMU_CFG4_LPLL_SEL_MASK);
		unsigned int RSV1    	:	BITSIZEOF(CMU_CFG4_RSV1_MASK    );
	} b;
} CMU_CFG4_type;

typedef union {
	unsigned int word;
	struct {
		unsigned int BOOT_0  	:	BITSIZEOF(CMU_SYS_STS_BOOT_0_MASK  );
		unsigned int BOOT_1  	:	BITSIZEOF(CMU_SYS_STS_BOOT_1_MASK  );
		unsigned int BOOT_2  	:	BITSIZEOF(CMU_SYS_STS_BOOT_2_MASK  );
		unsigned int RSV0    	:	BITSIZEOF(CMU_SYS_STS_RSV0_MASK    );
		unsigned int L0_BCMPO	:	BITSIZEOF(CMU_SYS_STS_L0_BCMPO_MASK);
		unsigned int L1_BCMPO	:	BITSIZEOF(CMU_SYS_STS_L1_BCMPO_MASK);
		unsigned int RST    	:	BITSIZEOF(CMU_SYS_STS_RST_MASK     );
		unsigned int POR    	:	BITSIZEOF(CMU_SYS_STS_POR_MASK     );
		unsigned int RSV1    	:	BITSIZEOF(CMU_SYS_STS_RSV1_MASK    );
	} b;
} CMU_SYS_STS_type;

typedef union {
	unsigned int word;
	struct {
		unsigned int I2S0_EN	:	BITSIZEOF(CMU_CFG8_I2S0_EN_MASK );
		unsigned int I2S1_EN	:	BITSIZEOF(CMU_CFG8_I2S1_EN_MASK );
		unsigned int VCAM_EN	:	BITSIZEOF(CMU_CFG8_VCAM_EN_MASK );
		unsigned int SPI_EN		:	BITSIZEOF(CMU_CFG8_SPI_EN_MASK  );
		unsigned int NAND_EN	:	BITSIZEOF(CMU_CFG8_NAND_EN_MASK );
		unsigned int ARINC_EN	:	BITSIZEOF(CMU_CFG8_ARINC_EN_MASK);
		unsigned int MIL0_EN	:	BITSIZEOF(CMU_CFG8_MIL0_EN_MASK );
		unsigned int MIL1_EN	:	BITSIZEOF(CMU_CFG8_MIL1_EN_MASK );
		unsigned int UDDC0_EN	:	BITSIZEOF(CMU_CFG8_UDDC0_EN_MASK);
		unsigned int UDDC1_EN	:	BITSIZEOF(CMU_CFG8_UDDC1_EN_MASK);
		unsigned int UDDC2_EN	:	BITSIZEOF(CMU_CFG8_UDDC2_EN_MASK);
		unsigned int UDDC3_EN	:	BITSIZEOF(CMU_CFG8_UDDC3_EN_MASK);
		unsigned int GPS0_EN	:	BITSIZEOF(CMU_CFG8_GPS0_EN_MASK );
		unsigned int GPS1_EN	:	BITSIZEOF(CMU_CFG8_GPS1_EN_MASK );
		unsigned int LCD_EN		:	BITSIZEOF(CMU_CFG8_LCD_EN_MASK  );
		unsigned int UART1_EN	:	BITSIZEOF(CMU_CFG8_UART1_EN_MASK);
		unsigned int UART2_EN	:	BITSIZEOF(CMU_CFG8_UART2_EN_MASK);
		unsigned int RSV		:	BITSIZEOF(CMU_CFG8_RSV_MASK     );
	} b;
} CMU_CFG8_type;


typedef struct {
	CMU_CFG1_type			CFG1;
	CMU_CFG_PLL_type		CFG2;
	CMU_CFG_PLL_type		CFG3;
	CMU_CFG4_type			CFG4;
	CMU_CFG_PLL_type		CFG5;
	CMU_SYS_STS_type		SYS_STS;
	unsigned long long int 	RSV;
	CMU_CFG8_type			CFG8;
} CMU_type;

#define LX_CMU			((CMU_type	*) CMU_BASE)
#define CFG_CPU_PLL		CFG2
#define CFG_BUS_PLL		CFG3
#define CFG_LINK_PLL	CFG5
#define CFG_CLKDIS		CFG8

/*******************Include Function*********************/
#ifdef __cplusplus
extern "C"
	{
#endif

#ifdef __cplusplus
	}
#endif // __cplusplus

/********************************************************/

#endif

