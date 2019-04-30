/**********************************************************************************************************************
  Copyright (c) 2017 Milandr Corporation. All rights reserved.

  History:
  	  Zatonsky Pavel - Created.
**********************************************************************************************************************/
#ifndef __HAL_ARINC_H__
#define __HAL_ARINC_H__

#include "hal_typedef.h"
#include "def1967VN034R1.h"
#define __IO 			volatile


typedef union {
	unsigned int word;
	struct {
		unsigned int CH_EN		:	BITSIZEOF(ARINC_RX_CONTROL_CH_EN_MASK	);
		unsigned int CLK	  	:	BITSIZEOF(ARINC_RX_CONTROL_CLK_MASK	    );
		unsigned int LB_EN		:	BITSIZEOF(ARINC_RX_CONTROL_LB_EN_MASK	);
		unsigned int SD_EN	  	:	BITSIZEOF(ARINC_RX_CONTROL_SD_EN_MASK	);
		unsigned int DA		  	:	BITSIZEOF(ARINC_RX_CONTROL_DA_MASK		);
		unsigned int SDI1	  	:	BITSIZEOF(ARINC_RX_CONTROL_SDI1_MASK	);
		unsigned int SDI2		:	BITSIZEOF(ARINC_RX_CONTROL_SDI2_MASK	);
		unsigned int ENSYNC		:	BITSIZEOF(ARINC_RX_CONTROL_ENSYNC_MASK	);
		unsigned int ENPAR		:	BITSIZEOF(ARINC_RX_CONTROL_ENPAR_MASK	);
		unsigned int ODD		:	BITSIZEOF(ARINC_RX_CONTROL_ODD_MASK	    );
		unsigned int RSV0		:	BITSIZEOF(ARINC_RX_CONTROL_RSV0_MASK    );
		unsigned int INTEDR	  	:	BITSIZEOF(ARINC_RX_CONTROL_INTEDR_MASK	);
		unsigned int INTEER	  	:	BITSIZEOF(ARINC_RX_CONTROL_INTEER_MASK	);
		unsigned int INTEFF	  	:	BITSIZEOF(ARINC_RX_CONTROL_INTEFF_MASK	);
		unsigned int INTEHF	  	:	BITSIZEOF(ARINC_RX_CONTROL_INTEHF_MASK	);
		unsigned int DIV	  	:	BITSIZEOF(ARINC_RX_CONTROL_DIV_MASK	    );
		unsigned int RSV1	  	:	BITSIZEOF(ARINC_RX_CONTROL_RSV1_MASK    );
	} b;
} ARINC_RX_CONTROL;

typedef union {
	unsigned int word;
	struct {
		unsigned int DR			:	BITSIZEOF(ARINC_RX_STATUS_DR_MASK		 );
		unsigned int ERR		:	BITSIZEOF(ARINC_RX_STATUS_ERR_MASK		 );
		unsigned int FF        	:	BITSIZEOF(ARINC_RX_STATUS_FF_MASK        );
		unsigned int HF         :	BITSIZEOF(ARINC_RX_STATUS_HF_MASK        );
		unsigned int IRQ_DR     :	BITSIZEOF(ARINC_RX_STATUS_IRQ_DR_MASK    );
		unsigned int IRQ_ERR    :	BITSIZEOF(ARINC_RX_STATUS_IRQ_ERR_MASK   );
		unsigned int IRQ_FF    	:	BITSIZEOF(ARINC_RX_STATUS_IRQ_FF_MASK    );
		unsigned int IRQ_HF    	:	BITSIZEOF(ARINC_RX_STATUS_IRQ_HF_MASK    );
		unsigned int IRQ_RX_CH0	:	BITSIZEOF(ARINC_RX_STATUS_IRQ_RX_CH0_MASK);
		unsigned int IRQ_RX_CH1	:	BITSIZEOF(ARINC_RX_STATUS_IRQ_RX_CH1_MASK);
		unsigned int IRQ_RX_CH2	:	BITSIZEOF(ARINC_RX_STATUS_IRQ_RX_CH2_MASK);
		unsigned int IRQ_RX_CH3 :	BITSIZEOF(ARINC_RX_STATUS_IRQ_RX_CH3_MASK);
		unsigned int IRQ_RX_CH4 :	BITSIZEOF(ARINC_RX_STATUS_IRQ_RX_CH4_MASK);
		unsigned int IRQ_RX_CH5 :	BITSIZEOF(ARINC_RX_STATUS_IRQ_RX_CH5_MASK);
		unsigned int IRQ_RX_CH6 :	BITSIZEOF(ARINC_RX_STATUS_IRQ_RX_CH6_MASK);
		unsigned int IRQ_RX_CH7 :	BITSIZEOF(ARINC_RX_STATUS_IRQ_RX_CH7_MASK);
		unsigned int CHAN_WP    :	BITSIZEOF(ARINC_RX_STATUS_CHAN_WP_MASK   );
		unsigned int DATA_RP    :	BITSIZEOF(ARINC_RX_STATUS_DATA_RP_MASK   );
	} b;
} ARINC_RX_STATUS;

typedef union {
	unsigned int word;
	struct {
		unsigned int CH_EN   	:	BITSIZEOF(ARINC_TX_CONTROL_CH_EN_MASK   );
		unsigned int CLK     	:	BITSIZEOF(ARINC_TX_CONTROL_CLK_MASK     );
		unsigned int EN_PAR  	:	BITSIZEOF(ARINC_TX_CONTROL_EN_PAR_MASK  );
		unsigned int ODD      	:	BITSIZEOF(ARINC_TX_CONTROL_ODD_MASK     );
		unsigned int INTE_TXR 	:	BITSIZEOF(ARINC_TX_CONTROL_INTE_TXR_MASK);
		unsigned int INTE_FFT 	:	BITSIZEOF(ARINC_TX_CONTROL_INTE_FFT_MASK);
		unsigned int INTE_HFT	:	BITSIZEOF(ARINC_TX_CONTROL_INTE_HFT_MASK);
		unsigned int ENSYNC  	:	BITSIZEOF(ARINC_TX_CONTROL_ENSYNC_MASK  );
		unsigned int DIV     	:	BITSIZEOF(ARINC_TX_CONTROL_DIV_MASK     );
		unsigned int RSV     	:	BITSIZEOF(ARINC_TX_CONTROL_RSV_MASK     );
	} b;
} ARINC_TX_CONTROL;

typedef union {
	unsigned int word;
	struct {
		unsigned int TX_R      	:	BITSIZEOF(ARINC_TX_STATUS_TX_R_MASK      );
		unsigned int BUSY      	:	BITSIZEOF(ARINC_TX_STATUS_BUSY_MASK      );
		unsigned int FFT       	:	BITSIZEOF(ARINC_TX_STATUS_FFT_MASK       );
		unsigned int HFT        :	BITSIZEOF(ARINC_TX_STATUS_HFT_MASK       );
		unsigned int IRQ_TXR    :	BITSIZEOF(ARINC_TX_STATUS_IRQ_TXR_MASK   );
		unsigned int RSV0		:	BITSIZEOF(ARINC_TX_STATUS_RSV0_MASK		 );
		unsigned int IRQ_FFT   	:	BITSIZEOF(ARINC_TX_STATUS_IRQ_FFT_MASK   );
		unsigned int IRQ_HFT   	:	BITSIZEOF(ARINC_TX_STATUS_IRQ_HFT_MASK   );
		unsigned int IRQ_TX_CH0	:	BITSIZEOF(ARINC_TX_STATUS_IRQ_TX_CH0_MASK);
		unsigned int IRQ_TX_CH1	:	BITSIZEOF(ARINC_TX_STATUS_IRQ_TX_CH1_MASK);
		unsigned int IRQ_TX_CH2	:	BITSIZEOF(ARINC_TX_STATUS_IRQ_TX_CH2_MASK);
		unsigned int IRQ_TX_CH3 :	BITSIZEOF(ARINC_TX_STATUS_IRQ_TX_CH3_MASK);
		unsigned int RSV1       :	BITSIZEOF(ARINC_TX_STATUS_RSV1_MASK      );
		unsigned int DATA_WP    :	BITSIZEOF(ARINC_TX_STATUS_DATA_WP_MASK   );
		unsigned int CHAN_RP    :	BITSIZEOF(ARINC_TX_STATUS_CHAN_RP_MASK   );
	}b;
} ARINC_TX_STATUS;

typedef struct {
	ARINC_RX_CONTROL	RX_CONTROL;
	unsigned int 		RSV;
	unsigned int 		RX_DATA;
	ARINC_RX_STATUS		RX_STATUS;
} ARINC_RX_type;

typedef struct {
	ARINC_TX_CONTROL	TX_CONTROL;
	unsigned int 		RSV;
	unsigned int 		TX_DATA;
	ARINC_TX_STATUS		TX_STATUS;
} ARINC_TX_type;

/******************* Init Structure *********************/
typedef enum {ARINC_Clk_100kHz, ARINC_Clk_12p5kHz} ARINC_Clk;
typedef enum {ARINC_LB_Dis, ARINC_LB_En} ARINC_LB;
typedef enum {ARINC_SD_Dis, ARINC_SD_En} ARINC_SD;
typedef enum {ARINC_DA_Dis, ARINC_DA_En} ARINC_DA;
typedef enum {ARINC_SDI_Null, ARINC_SDI_One} ARINC_SDI;
typedef enum {ARINC_Sync_Dis, ARINC_Sync_En} ARINC_Sync;
typedef enum {ARINC_Parity_Dis, ARINC_Parity_Odd, ARINC_Parity_Even} ARINC_Parity;
typedef enum {ARINC_IT_Dis, ARINC_IT_En} ARINC_IT;

typedef enum {ARINC_RX_IT_nEmptyFIFO, ARINC_RX_IT_Err, ARINC_RX_IT_HalfFIFO, ARINC_RX_IT_FullFIFO} ARINC_RX_IT;
typedef enum {ARINC_TX_IT_EmptyFIFO, ARINC_TX_IT_HalfFIFO, ARINC_TX_IT_FullFIFO} ARINC_TX_IT;

typedef struct {
	ARINC_Clk 		Clk;
	ARINC_LB		LB;
	ARINC_SD		SD;
	ARINC_DA		DA;
	ARINC_SDI		SDI1;
	ARINC_SDI		SDI2;
	ARINC_Sync		Sync;
	ARINC_Parity 	Parity;
	ARINC_IT		ITnEmptyFIFO;
	ARINC_IT		ITErr;
	ARINC_IT		ITFullFIFO;
	ARINC_IT		ITHalfFIFO;
} ARINC_RX_Init_type;

typedef struct {
	ARINC_Clk		Clk;
	ARINC_Parity 	Parity;
	ARINC_Sync		Sync;
	ARINC_IT		ITEmptyFIFO;
	ARINC_IT		ITFullFIFO;
	ARINC_IT		ITHalfFIFO;
} ARINC_TX_Init_type;

typedef union{
	unsigned int word;
	struct {
		unsigned int LABEL	:	8;
		unsigned int SDI	:	2;
		unsigned int DATA	:	19;
		unsigned int SSM	:	2;
		unsigned int P		:	1;
	}b;
} ARINC_Word_type;

#define LX_ARINC_RX_CH0      ((ARINC_RX_type    *) ARINT_RX_CH0_BASE)
#define LX_ARINC_RX_CH1      ((ARINC_RX_type    *) ARINT_RX_CH1_BASE)
#define LX_ARINC_RX_CH2      ((ARINC_RX_type    *) ARINT_RX_CH2_BASE)
#define LX_ARINC_RX_CH3      ((ARINC_RX_type    *) ARINT_RX_CH3_BASE)
#define LX_ARINC_RX_CH4      ((ARINC_RX_type    *) ARINT_RX_CH4_BASE)
#define LX_ARINC_RX_CH5      ((ARINC_RX_type    *) ARINT_RX_CH5_BASE)
#define LX_ARINC_RX_CH6      ((ARINC_RX_type    *) ARINT_RX_CH6_BASE)
#define LX_ARINC_RX_CH7      ((ARINC_RX_type    *) ARINT_RX_CH7_BASE)

#define LX_ARINC_RX_MEM0	 ((unsigned int 	*) ARINC_RX_MEM0_LOC)
#define LX_ARINC_RX_MEM1	 ((unsigned int 	*) ARINC_RX_MEM1_LOC)
#define LX_ARINC_RX_MEM2	 ((unsigned int 	*) ARINC_RX_MEM2_LOC)
#define LX_ARINC_RX_MEM3	 ((unsigned int 	*) ARINC_RX_MEM3_LOC)
#define LX_ARINC_RX_MEM4	 ((unsigned int 	*) ARINC_RX_MEM4_LOC)
#define LX_ARINC_RX_MEM5	 ((unsigned int 	*) ARINC_RX_MEM5_LOC)
#define LX_ARINC_RX_MEM6	 ((unsigned int 	*) ARINC_RX_MEM6_LOC)
#define LX_ARINC_RX_MEM7	 ((unsigned int 	*) ARINC_RX_MEM7_LOC)
#define LX_ARINC_RX_LABEL0	 ((unsigned int 	*) ARINC_RX_LABEL0_LOC)
#define LX_ARINC_RX_LABEL1	 ((unsigned int 	*) ARINC_RX_LABEL1_LOC)
#define LX_ARINC_RX_LABEL2	 ((unsigned int 	*) ARINC_RX_LABEL2_LOC)
#define LX_ARINC_RX_LABEL3	 ((unsigned int 	*) ARINC_RX_LABEL3_LOC)
#define LX_ARINC_RX_LABEL4	 ((unsigned int 	*) ARINC_RX_LABEL4_LOC)
#define LX_ARINC_RX_LABEL5	 ((unsigned int 	*) ARINC_RX_LABEL5_LOC)
#define LX_ARINC_RX_LABEL6	 ((unsigned int 	*) ARINC_RX_LABEL6_LOC)
#define LX_ARINC_RX_LABEL7	 ((unsigned int 	*) ARINC_RX_LABEL7_LOC)

#define LX_ARINC_TX_CH0      ((ARINC_TX_type    *) ARINT_TX_CH0_BASE)
#define LX_ARINC_TX_CH1      ((ARINC_TX_type    *) ARINT_TX_CH1_BASE)
#define LX_ARINC_TX_CH2      ((ARINC_TX_type    *) ARINT_TX_CH2_BASE)
#define LX_ARINC_TX_CH3      ((ARINC_TX_type    *) ARINT_TX_CH3_BASE)

#define LX_ARINC_TX_MEM0	 ((unsigned int 	*) ARINC_TX_MEM0_LOC)
#define LX_ARINC_TX_MEM1	 ((unsigned int 	*) ARINC_TX_MEM1_LOC)
#define LX_ARINC_TX_MEM2	 ((unsigned int 	*) ARINC_TX_MEM2_LOC)
#define LX_ARINC_TX_MEM3	 ((unsigned int 	*) ARINC_TX_MEM3_LOC)

/*******************Include Function*********************/
#ifdef __cplusplus
extern "C"
	{
#endif
	void HAL_ARINC_RX_Init(ARINC_RX_type *LX_ARINC_RX_CHx, ARINC_RX_Init_type *InitStruct, unsigned int SOC_CLK);
	void HAL_ARINC_RX_DeInit(ARINC_RX_type *LX_ARINC_RX_CHx);
	void HAL_ARINC_RX_ITEn(ARINC_RX_type *LX_ARINC_RX_CHx, ARINC_RX_IT ITName);
	void HAL_ARINC_RX_ITDis(ARINC_RX_type *LX_ARINC_RX_CHx, ARINC_RX_IT ITName);
	void HAL_ARINC_RX_Enable(ARINC_RX_type *LX_ARINC_RX_CHx);
	void HAL_ARINC_RX_Disable(ARINC_RX_type *LX_ARINC_RX_CHx);
	void HAL_ARINC_RX_LabelSet(unsigned int *LX_ARINC_RX_LABELx, unsigned int *CorrectLabel, unsigned int Size);
	void HAL_ARINC_RX_LabelReset(unsigned int *LX_ARINC_RX_LABELx, unsigned int *IncorrectLabel, unsigned int Size);
	void HAL_ARINC_RX_LabelAllReset(unsigned int *LX_ARINC_RX_LABELx);
	void HAL_ARINC_RX_DataRead(ARINC_RX_type *LX_ARINC_RX_CHx, void *PtrRxArr, unsigned int Size);
	void HAL_ARINC_RX_MDataRead(unsigned int *LX_ARINC_RX_MEMx, void *PtrRxArr, unsigned int Size);
	unsigned int HAL_ARINC_RX_AllDataRead(ARINC_RX_type *LX_ARINC_RX_CHx, void *PtrRxArr);

	void HAL_ARINC_TX_Init(ARINC_TX_type *LX_ARINC_TX_CHx, ARINC_TX_Init_type *InitStruct, unsigned int SOC_CLK);
	void HAL_ARINC_TX_DeInit(ARINC_TX_type *LX_ARINC_TX_CHx);
	void HAL_ARINC_TX_ITEn(ARINC_TX_type *LX_ARINC_TX_CHx, ARINC_TX_IT ITName);
	void HAL_ARINC_TX_ITDis(ARINC_TX_type *LX_ARINC_TX_CHx, ARINC_TX_IT ITName);
	void HAL_ARINC_TX_DataWrite(ARINC_TX_type *LX_ARINC_TX_CHx, void *PtrTxArr,unsigned int Size);
	void HAL_ARINC_TX_Enable(ARINC_TX_type *LX_ARINC_TX_CHx);
	void HAL_ARINC_TX_Disable(ARINC_TX_type *LX_ARINC_TX_CHx);
#ifdef __cplusplus
	}
#endif // __cplusplus

/********************************************************/

#endif

