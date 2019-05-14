#include "interrupt.h"
#include "hal_1967VN034R1.h"

// -----------------------------------------------------------------------------
void InterruptInit(void) {
  asm("rds;;");
  HAL_Interrupt_IMASKClear();
  HAL_Interrupt_ILATClear();
  HAL_Interrupt_GlobalEnable();
  return;
}

// -----------------------------------------------------------------------------
void InterruptDisableGlobal(void) {
  asm("rds;;");
  HAL_Interrupt_GlobalDisable();
}
