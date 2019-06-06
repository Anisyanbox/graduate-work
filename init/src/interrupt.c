#include <sysreg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <builtins.h>
#include "interrupt.h"
#include "hal_1967VN034R1.h"
#include "main.h"

// -----------------------------------------------------------------------------
#pragma interrupt
static void IntHwIrq(void) {
  static char buf[100] = { 0 };

  sprintf(buf, "System HW error: systat =  0x%X; DMA status = 0x%X\n", 
              __builtin_sysreg_read(__SYSTATCL),
              __builtin_mem_read2((volatile long long *)base_DMASTATCL));
  HAL_UART_Send(UART_DEBUG_PORT, buf, strlen((const char *)buf));
}

// -----------------------------------------------------------------------------
#pragma interrupt
static void IntKernelIrq(void) {
  static char buf[100] = { 0 };

  sprintf(buf, "intKERNEL: systat =  0x%X; DMA status = 0x%X\n",
              __builtin_sysreg_read(__SYSTATCL),
              __builtin_mem_read2((volatile long long *)base_DMASTATCL));
  HAL_UART_Send(UART_DEBUG_PORT, buf, strlen((const char *)buf));
}

// -----------------------------------------------------------------------------
void InterruptInit(void) {
  HAL_Interrupt_IMASKClear();
  HAL_Interrupt_ILATClear();
  asm("rds;;");

  HAL_Interrupt_SubscribeHandler(intHW, IntHwIrq);
  HAL_Interrupt_Enable(intHW);

  HAL_Interrupt_SubscribeHandler(intKERNEL, IntKernelIrq);
  HAL_Interrupt_Enable(intKERNEL);
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
