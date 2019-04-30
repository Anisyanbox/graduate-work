/**********************************************************************************************************************
  Copyright (c) 2017 Milandr Corporation. All rights reserved.

  History:
  	  Zatonsky Pavel - Created.
**********************************************************************************************************************/
#ifndef __HAL_NAND_H__
#define __HAL_NAND_H__

#include "def1967VN034R1.h"
#include "hal_typedef.h"

#define __IO			volatile
typedef enum { K9F8G08UXM, K9F2G08X0B} NAND_Samsung_type;

#ifdef __cplusplus
extern "C"
{
#endif


typedef struct
{
	__IO unsigned int IO_CFG;
	__IO unsigned int WCT_CFG;
	__IO unsigned int NAND_CFG;
	__IO unsigned int WR_CFG;
	__IO unsigned int RD_CFG;
	__IO unsigned int RESERV0;
	__IO unsigned int RESERV1;
	__IO unsigned int RESERV2;
	__IO unsigned int CR;
	__IO unsigned int SR;
	__IO unsigned int AR;
	__IO unsigned int CNTR;
	__IO unsigned int DR;
	__IO unsigned int ERR12;
	__IO unsigned int ERR32;
	__IO unsigned int SP_BUF;
} NAND_TypeDef;

#define LX_NAND           ((NAND_TypeDef    *) base_NAND)

/*******************Include Function*********************/



#ifdef __cplusplus
}
#endif // __cplusplus

/********************************************************/


#endif
