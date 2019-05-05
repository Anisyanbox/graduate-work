#include "interrupt.h"
#include "hal_1967VN034R1.h"

// -----------------------------------------------------------------------------
void IntInit(void) {
  asm("rds;;");
  HAL_Interrupt_IMASKClear();
  HAL_Interrupt_ILATClear();
  HAL_Interrupt_GlobalEnable();
  return;
}
