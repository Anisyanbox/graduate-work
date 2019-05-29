#include <sysreg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "interrupt.h"
#include "hal_1967VN034R1.h"
#include "main.h"

// -----------------------------------------------------------------------------
#pragma interrupt
static void IntHwIrq(void) {
  static char buf[50] = { 0 };

  sprintf(buf, "System HW error: systat =  %X\n", __builtin_sysreg_read(__SYSTATCL));  
  HAL_UART_Send(UART_DEBUG_PORT, buf, strlen((const char *)buf));
}

// -----------------------------------------------------------------------------
void InterruptInit(void) {
  HAL_Interrupt_IMASKClear();
  HAL_Interrupt_ILATClear();
  asm("rds;;");

  HAL_Interrupt_SubscribeHandler(intHW, IntHwIrq);
  HAL_Interrupt_Enable(intHW);
}

// -----------------------------------------------------------------------------
void InterruptDisableGlobal(void) {
  HAL_Interrupt_GlobalDisable();
  asm("rds;;");
}

// -----------------------------------------------------------------------------
void InterruptEnableGlobal(void) {
  HAL_Interrupt_GlobalEnable();
}
