/**********************************************************************************************************************
  Copyright (c) 2016 Milandr Corporation. All rights reserved.

  History:
      Zatonsky Pavel - Created.
      Zatonsky Pavel - Correction.
      Anisimov Alexander - Fixed.
**********************************************************************************************************************/
#ifndef __HAL_UART_H__
#define __HAL_UART_H__

#include "hal_typedef.h"
#include "def1967VN034R1.h"

typedef enum {
  UART_WordLen_8bit = 0,
  UART_WordLen_7bit = (1<<13),
  UART_WordLen_6bit = (2<<13),
  UART_WordLen_5bit = (3<<13)
} UART_WordLen_type;

typedef enum {
  UART_TXD_Direct = 0,
  UART_TXD_Low = ((1<<8)|(1<<15)),
  UART_TXD_High = ((1<<8)|(0<<15)),
  UART_TXD_Compliment = ((0<<8)|(1<<15))
} UART_TXD_type;

typedef enum {
  UART_Parity_Off = 0,
  UART_Parity_Even = (1<<9),
  UART_Parity_Odd = ((1<<9)|(1<<10))
} UART_Parity_type;

typedef enum {
  UART_Mode_TxRx = 0,
  UART_Mode_Tx = ((1<<2)|(1<<5)),
  UART_Mode_Rx = ((1<<1)|(1<<4))
} UART_Mode_type;

typedef enum {
  UART_Stop_1bit = 0,
  UART_Stop_2bit = (1<<11)
} UART_StopBits_type;

typedef enum {
  UART_FIFOSize_Byte = 0,
  UART_FIFOSize_DWord = (1<<12)
} UART_FIFOSize_type;

typedef enum {
  UART_DMACtrl_Dis = 0,
  UART_DMACtrl_En = 1
} UART_DMACtrl_type;

typedef enum {
  UART_IT_Dis = 0,
  UART_IT_En = 1
} UART_IT_type;

typedef enum {
  UART_OverSampling_High = 0,
  UART_OverSampling_Normal = (1<<6)
} UART_OverSampling_type;

#define __IO      volatile

typedef union {
  unsigned int word;
  struct {
    unsigned int FRAME    : 1; //0
    unsigned int PARITY   : 1; //1
    unsigned int OVERRUN  : 1; //2
    unsigned int ERROR    : 1; //3
    unsigned int res      : 28; //4:31
  }b;
} UART_RXSTAT;

typedef union {
  unsigned int word;
  struct {
    unsigned int UARTEN   : 1; //0
    unsigned int UTXDIS   : 1; //1
    unsigned int URXDIS   : 1; //2
    unsigned int DMAONERR : 1; //3
    unsigned int UTXFDIS  : 1; //4
    unsigned int URXFDIS  : 1; //5
    unsigned int UHBRE    : 2; //6:7
    unsigned int BREAK    : 1; //8
    unsigned int PRTEN    : 1; //9
    unsigned int EVENPRT  : 1; //10
    unsigned int XSTOP    : 1; //11
    unsigned int UFIFOEN  : 1; //12
    unsigned int WRDLEN   : 2; //13:14
    unsigned int INV      : 1; //15
    unsigned int TXINT    : 1; //16
    unsigned int RXINT    : 1; //17
    unsigned int RXERRINT : 1; //18
    unsigned int MSINT    : 1; //19
    unsigned int UDINT    : 1; //20
    unsigned int UTXEINT  : 1; //21
    unsigned int URXTINT  : 1; //22
    unsigned int RSV      : 8; //23:30
    unsigned int LBM      : 1; //31
  }b;
} UART_CR;

typedef union {
  unsigned int word;
  struct {
    unsigned int res_low  : 3; //0:2
    unsigned int UBUSY    : 1; //3
    unsigned int URXFE    : 1; //4
    unsigned int UTXFF    : 1; //5
    unsigned int res_high : 26; //6:31
  }b;
} UART_FLAG;

typedef union {
  unsigned int word;
  struct {
    unsigned int TXINT    : 1; //0
    unsigned int RXINT    : 1; //1
    unsigned int RXERRINT : 1; //2
    unsigned int MSINT    : 1; //3
    unsigned int UDINT    : 1; //4
    unsigned int UTXEINT  : 1; //5
    unsigned int URXTINT  : 1; //6
    unsigned int RSV    : 25; //7:31
  }b;
} UART_INT;

typedef struct {
  __IO unsigned int UDR;
  __IO UART_RXSTAT  RXSTAT;
  __IO UART_CR    UCR_LOAD;
  __IO UART_CR    UCR_SET;
  __IO UART_CR    UCR_CLEAR;
  __IO unsigned int UBitRate;
  __IO UART_FLAG  UFLAG;
  __IO UART_INT   UINTM;
  __IO UART_INT   UINT;
}UART_type;

typedef struct {
  unsigned int BitRate;                 /* This member configures the UART communication baud rate. (bit pre sec)
                                          The baud rate is computed using the following formula:
                                          - BitRate = (XTI /  (UBitRate + 1)) / (OverSampling) */
  UART_Mode_type WorkMode;                /*!< default = transiver */ /*!<  reciver, transmiter, transiver */
  UART_OverSampling_type OverSampling;    /*!< number of clk per 1 bit information. */
  UART_WordLen_type WordLength;           /*!< Specifies the number of data bits transmitted or received in a frame. */
  UART_StopBits_type StopBits;            /*!< Specifies the number of stop bits transmitted(one or two). */
  UART_Parity_type ParityMode;            /**//*!< Specifies the parity mode.*/
  UART_FIFOSize_type FIFOSize;            /*!< Specifies the FIFO mode.byte = 8bit, dword = 64 bit*/
  UART_TXD_type TXDMode;                  /*!< direct - txd = data, compliment - txd = inverse data. */
  UART_DMACtrl_type DMACtrlErr;           /*!< EN - dma stopped, if detected error. */
  UART_IT_type TxIT, RxIT, RxErrIT, MSIT, UDIT, TxEmptIT, RxTOIT;
}UART_Init_type;


#define LX_UART0            ((UART_type    *) base_UART0)
#define LX_UART1            ((UART_type    *) base_UART1)

/*******************Include Function*********************/
#ifdef __cplusplus
extern "C" {
#endif
  int  HAL_UART_Init (UART_type*, UART_Init_type*, unsigned int);
  void HAL_UART_DefaultInitStruct (UART_Init_type* InitStruct);
  void HAL_UART_DeInit (UART_type* UARTx);

  int  HAL_UART_Send (UART_type* UARTx, char* BuffAddr, unsigned int amount);
  int  HAL_UART_Receive (UART_type* UARTx, char* BuffAddr, unsigned int amount);
    
  void HAL_UARTDMA_Send(int uart_num, int dma_ch, void *tcb);
  void HAL_UARTDMA_Receive(int uart_num, int dma_ch, void *tcb);
#ifdef __cplusplus
}
#endif // __cplusplus

/********************************************************/
#endif
