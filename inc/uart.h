#ifndef _INC_UART_H_
#define _INC_UART_H_

typedef enum {
  UART_INIT = 0,
  UART_INIT_FALSE
} UartInitStat_t;

UartInitStat_t UartInit(void);

#endif  // _INC_UART_H_
