#include <sysreg.h>
#include "interrupt.h"
#include "hal_1967VN034R1.h"

// -----------------------------------------------------------------------------
void InterruptInit(void) {
  HAL_Interrupt_IMASKClear();
  HAL_Interrupt_ILATClear();
  __builtin_sysreg_write(__SQCTLST, SQCTL_NMOD);
  asm("rds;;");
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
