#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "uart_adapter.h"
#include "clock.h"
#include "pthread.h"
#include "delay.h"
#include "apptime.h"
#include "main.h"

#define UART1_THREAD_SLEEP_MS   ((unsigned int)1000)
#define UART1_THREAD_PRIORITY   MAIN_THREAD_NORMAL_PRIO

static bool is_it_happened = false;

// -----------------------------------------------------------------------------
#pragma interrupt
static void Uart1IrqHandler(void) {
  is_it_happened = true;
}

// -----------------------------------------------------------------------------
static void * Uart1TxThread(void * args) {
  static char buffer[30] = {0};
  uint32_t * lcd_buf = NULL;

  while(true) {
    sprintf(buffer, "--> %llu", AppTimeGetInMs() / 1000);
    //HAL_UART_Send(LX_UART1, buffer, strlen((const char*)buffer));
    DelayMs(UART1_THREAD_SLEEP_MS);
  }
}

// -----------------------------------------------------------------------------
UartInitStat_t UartInit(void) {
  static pthread_t uart1_tx_thread_handl;
  pthread_attr_t uart_attr;
  sched_param_t uart1_thread_prio;
  UART_Init_type uart1_init_struct;

  /* init UART1 (PA2 - RxD; PA3 - TxD) */
  uart1_init_struct.BitRate       = 115200;
  uart1_init_struct.WorkMode      = UART_Mode_TxRx;
  uart1_init_struct.OverSampling  = UART_OverSampling_High;
  uart1_init_struct.WordLength    = UART_WordLen_8bit;
  uart1_init_struct.StopBits      = UART_Stop_1bit;
  uart1_init_struct.ParityMode    = UART_Parity_Off;
  uart1_init_struct.FIFOSize      = UART_FIFOSize_Byte;
  uart1_init_struct.TXDMode       = UART_TXD_Direct;
  uart1_init_struct.DMACtrlErr    = UART_DMACtrl_Dis;
  uart1_init_struct.TxIT          = UART_IT_Dis;
  uart1_init_struct.RxIT          = UART_IT_En;
  uart1_init_struct.RxErrIT       = UART_IT_Dis;
  uart1_init_struct.MSIT          = UART_IT_Dis;
  uart1_init_struct.UDIT          = UART_IT_Dis;
  uart1_init_struct.TxEmptIT      = UART_IT_Dis;
  uart1_init_struct.RxTOIT        = UART_IT_Dis;

  HAL_GPIO_Init(LX_GPIO_PA, GPIO_PIN_2 | GPIO_PIN_3, GPIO_PinMode_Alt);
  if (HAL_UART_Init(LX_UART1, &uart1_init_struct, ClockGetInputXtiKhz()) != 0) {
    return UART_INIT_FALSE;
  }

  HAL_Interrupt_SubscribeHandler(intUART1, Uart1IrqHandler);
  HAL_Interrupt_Enable(intUART1);

  /* create tx and rx thread for reading info from queue and further proccessing */
  if (pthread_attr_init(&uart_attr) != 0) {
    return UART_INIT_FALSE;
  }
  uart1_thread_prio.sched_priority = UART1_THREAD_PRIORITY;
  if (pthread_attr_setschedparam(&uart_attr,
                                (const sched_param_t*)&uart1_thread_prio) != 0) {
    return UART_INIT_FALSE;
  }
  if (pthread_create(&uart1_tx_thread_handl, 
                    (const pthread_attr_t*)uart_attr, 
                    Uart1TxThread, 
                    NULL) != 0) {
    return UART_INIT_FALSE;
  }
  if (pthread_attr_destroy(&uart_attr) != 0) {
    return UART_INIT_FALSE;
  }

  return UART_INIT;
}
