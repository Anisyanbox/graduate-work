/**********************************************************************************************************************
  Copyright (c) 2017 Milandr Corporation. All rights reserved.

  History:
  	  Zatonsky Pavel - Created.
**********************************************************************************************************************/
#ifndef __HAL_MILSTD_H__
#define __HAL_MILSTD_H__

#include "hal_typedef.h"
#include "def1967VN034R1.h"
#define __IO 			volatile


typedef union {
	unsigned int word;
	struct {
		unsigned int MR 		:	BITSIZEOF(MILSTD_CONTROL_MR_MASK);
		unsigned int BCSTART    :	BITSIZEOF(MILSTD_CONTROL_BCSTART_MASK);
		unsigned int MODE    	:	BITSIZEOF(MILSTD_CONTROL_MODE_MASK);
		unsigned int TRA        :	BITSIZEOF(MILSTD_CONTROL_TRA_MASK);
		unsigned int TRB        :	BITSIZEOF(MILSTD_CONTROL_TRB_MASK);
		unsigned int RTA        :	BITSIZEOF(MILSTD_CONTROL_RTA_MASK);
		unsigned int DIV6_0     :	BITSIZEOF(MILSTD_CONTROL_DIV6_0_MASK);
		unsigned int RERR    	:	BITSIZEOF(MILSTD_CONTROL_RERR_MASK);
		unsigned int INVTR   	:	BITSIZEOF(MILSTD_CONTROL_INVTR_MASK);
		unsigned int ENFILTER	:	BITSIZEOF(MILSTD_CONTROL_ENFILTER_MASK);
		unsigned int AUTOTUNE	:	BITSIZEOF(MILSTD_CONTROL_AUTOTUNE_MASK);
		unsigned int ENFILTER3  :	BITSIZEOF(MILSTD_CONTROL_ENFILTER3_MASK);
		unsigned int EN_XRTA    :	BITSIZEOF(MILSTD_CONTROL_EN_XRTA_MASK);
		unsigned int DIV7       :	BITSIZEOF(MILSTD_CONTROL_DIV7_MASK);
		unsigned int SYNC_DM    :	BITSIZEOF(MILSTD_CONTROL_SYNC_DM_MASK);
		unsigned int RSV	    :	BITSIZEOF(MILSTD_CONTROL_RSV_MASK);
	} b;
} MILSTD_CONTROL;

typedef union {
	unsigned int word;
	struct {
		unsigned int IDLE		:	BITSIZEOF(MILSTD_STATUS_IDLE_MASK);
		unsigned int RFLAGN   	:	BITSIZEOF(MILSTD_STATUS_RFLAGN_MASK);
		unsigned int VALMESS	:	BITSIZEOF(MILSTD_STATUS_VALMESS_MASK);
		unsigned int ERR  		:	BITSIZEOF(MILSTD_STATUS_ERR_MASK);
		unsigned int RCVA  	  	:	BITSIZEOF(MILSTD_STATUS_RCVA_MASK);
		unsigned int RCVB  	  	:	BITSIZEOF(MILSTD_STATUS_RCVB_MASK);
		unsigned int RSV	   	:	BITSIZEOF(MILSTD_STATUS_RSV_MASK);
	} b;
} MILSTD_STATUS;

typedef union {
	unsigned int word;
	struct {
		unsigned int NORCV		:	BITSIZEOF(MILSTD_ERROR_NORCV_MASK);
		unsigned int MANERR	  	:	BITSIZEOF(MILSTD_ERROR_MANERR_MASK);
		unsigned int DSYCERR	:	BITSIZEOF(MILSTD_ERROR_DSYCERR_MASK);
		unsigned int CSYCERR  	:	BITSIZEOF(MILSTD_ERROR_CSYCERR_MASK);
		unsigned int GAPERR		:	BITSIZEOF(MILSTD_ERROR_GAPERR_MASK);
		unsigned int CONERR	  	:	BITSIZEOF(MILSTD_ERROR_CONERR_MASK);
		unsigned int PROERR	  	:	BITSIZEOF(MILSTD_ERROR_PROERR_MASK);
		unsigned int RTAERR	   	:	BITSIZEOF(MILSTD_ERROR_RTAERR_MASK);
		unsigned int RSV	   	:	BITSIZEOF(MILSTD_ERROR_RSV_MASK);
	} b;
} MILSTD_ERROR;

typedef union {
	unsigned int word;
	struct {
		unsigned int CODECOMM			:	BITSIZEOF(MILSTD_COMMWORD_CODECOMM_MASK);
		unsigned int SUBADDR		  	:	BITSIZEOF(MILSTD_COMMWORD_SUBADDR_MASK);
		unsigned int TXRX				:	BITSIZEOF(MILSTD_COMMWORD_TXRX_MASK);
		unsigned int RTA				:	BITSIZEOF(MILSTD_COMMWORD_RTA_MASK);
		unsigned int RSV	     	  	:	BITSIZEOF(MILSTD_COMMWORD_RSV_MASK);
	} b;
} MILSTD_COMMWORD;

typedef union {
	unsigned int word;
	struct {
		unsigned int RT_FAIL			:	BITSIZEOF(MILSTD_STATWORD_RT_FAIL_MASK);
		unsigned int CFG_INTF_ACCEPT	:	BITSIZEOF(MILSTD_STATWORD_CFG_INTF_ACCEPT_MASK);
		unsigned int SUB_FAIL			:	BITSIZEOF(MILSTD_STATWORD_SUB_FAIL_MASK);
		unsigned int SUB_BUSY			:	BITSIZEOF(MILSTD_STATWORD_SUB_BUSY_MASK);
		unsigned int GROUP_COMM_ACCEPT	:	BITSIZEOF(MILSTD_STATWORD_GROUP_COMM_ACCEPT_MASK);
		unsigned int RSV0				:	BITSIZEOF(MILSTD_STATWORD_RSV0_MASK);
		unsigned int SERVICE_RQST		:	BITSIZEOF(MILSTD_STATWORD_SERVICE_RQST_MASK);
		unsigned int TRAN_ANSWER_WORD	:	BITSIZEOF(MILSTD_STATWORD_TRAN_ANSWER_WORD_MASK);
		unsigned int MSG_ERR			:	BITSIZEOF(MILSTD_STATWORD_MSG_ERR_MASK);
		unsigned int RTA				:	BITSIZEOF(MILSTD_STATWORD_RTA_MASK);
		unsigned int RSV1	     		:	BITSIZEOF(MILSTD_STATWORD_RSV1_MASK);
	} b;
} MILSTD_STATWORD;

typedef union {
	unsigned int word;
	struct {
		unsigned int IDLEIE		:	BITSIZEOF(MILSTD_INTEN_IDLEIE_MASK);
		unsigned int RFLAGNIE	:	BITSIZEOF(MILSTD_INTEN_RFLAGNIE_MASK);
		unsigned int VALMESSIE	:	BITSIZEOF(MILSTD_INTEN_VALMESSIE_MASK);
		unsigned int ERRIE		:	BITSIZEOF(MILSTD_INTEN_ERRIE_MASK);
		unsigned int RTAIE		:	BITSIZEOF(MILSTD_INTEN_RTAIE_MASK);
		unsigned int RSV	  	:	BITSIZEOF(MILSTD_INTEN_RSV_MASK);
	} b;
} MILSTD_INTEN;


typedef struct {
	__IO unsigned int		DT[0x400];
	__IO MILSTD_CONTROL 	CONTROL;
	__IO MILSTD_STATUS		STATUS;
	__IO MILSTD_ERROR		ERROR;
	__IO MILSTD_COMMWORD	COMMWORD1;
	__IO MILSTD_COMMWORD	COMMWORD2;
	__IO unsigned int		MODEDATA;
	__IO MILSTD_STATWORD	STATWORD1;
	__IO MILSTD_STATWORD	STATWORD2;
	__IO MILSTD_INTEN		INTEN;
	__IO unsigned int		MSG;
	__IO unsigned int 		RSV[0x3F6];
	__IO unsigned int		DR[0x400];
} MILSTD_type;

#define LX_MILSTD0           ((MILSTD_type    *) MILSTD0_BASE)
#define LX_MILSTD1           ((MILSTD_type    *) MILSTD1_BASE)

#define SYNCERR					DSYCERR
#define SEQERR					CSYCERR
#define AMOUNTDATA				CODECOMM
#define MILSTD_RTA_GROUP_COMM	0x1F

typedef enum {MILSTD_Mode_BC = 1, MILSTD_Mode_RT = 2, MILSTD_Mode_Monitor = 3} MILSTD_Mode_type;
typedef enum {MILSTD_Channel_Main = (1<<4), MILSTD_Channel_Reserv = (1<<5)} MILSTD_Channel_type;
typedef enum {MILSTD_ResetErr_IDLE, MILSTD_ResetErr_MR} MILSTD_ResetErr_type;
typedef enum {MILSTD_InvPRD_Dis, MILSTD_InvPRD_En} MILSTD_InvPRD_type;
typedef enum {MILSTD_Filter_Dis = 0, MILSTD_Filter_NRZ = (1<<20), MILSTD_Filter_Interference = (1<<22), MILSTD_Filter_En = ((1<<20)|(1<<22))} MILSTD_Filter_type;
typedef enum {MILSTD_AutoTune_Dis,MILSTD_AutoTune_En} MILSTD_AutoTune_type;
typedef enum {MILSTD_XRTA_InternalReg,MILSTD_XRTA_ExternalPins} MILSTD_XRTA_type;
typedef enum {MILSTD_SyncDM_1986BE1T, MILSTD_SyncDM_TS201} MILSTD_SyncDM_type;
typedef enum {MILSTD_IT_IDLEIE=1, MILSTD_IT_RFLAGNIE=2, MILSTD_IT_VALMESSIE=4, MILSTD_IT_ERRIE=8, MILSTD_IT_RTAIE=16} MILSTD_IT_type;

typedef struct {
	MILSTD_Mode_type 		Mode;
	MILSTD_Channel_type 	Channel;
	MILSTD_ResetErr_type	ResetErr;
	unsigned int			RTA;
	MILSTD_InvPRD_type		InvPRD;
	MILSTD_Filter_type		Filter;
	MILSTD_AutoTune_type	AutoTune;
	MILSTD_XRTA_type		XRTA;
	MILSTD_SyncDM_type		SyncDM;
} MILSTD_Init_type;
/*******************Include Function*********************/
#ifdef __cplusplus
extern "C"
	{
#endif

		void HAL_MILSTD_Reset(MILSTD_type *MILSTDx);
		void HAL_MILSTD_Init(MILSTD_type *MILSTDx, MILSTD_Init_type *InitStruct, unsigned int SOC_CLK_KHz);
		void HAL_MILSTD_DeInit(MILSTD_type *MILSTDx);
		void HAL_MILSTD_ITEnable(MILSTD_type *MILSTDx, MILSTD_IT_type ITName);
		void HAL_MILSTD_ITDisable(MILSTD_type *MILSTDx, MILSTD_IT_type ITName);
		void HAL_MILSTD_CWInit(MILSTD_type *MILSTDx, unsigned int NumCW, unsigned int TxRxMode, unsigned int RTA, unsigned int amount, unsigned int SubAddr);
		void HAL_MILSTD_DTWrite (MILSTD_type *MILSTDx, void *Buff, unsigned int amount, unsigned int subaddr);
		void HAL_MILSTD_StartCWTransmit (MILSTD_type *MILSTDx);
		void HAL_MILSTD_DRRead (MILSTD_type *MILSTDx, void *Buff, unsigned int amount, unsigned int subaddr);

#ifdef __cplusplus
	}
#endif // __cplusplus

/********************************************************/

#endif
