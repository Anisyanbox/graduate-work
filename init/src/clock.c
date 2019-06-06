#include "clock.h"
#include "hal_1967VN034R1.h"
#include "stupid_delay.h"

#define INPUT_XTI_CLOCK_KHZ ((unsigned int)25000)

#define CORE_CLOCK_KHZ      ((unsigned int)300000)
#define BUS_CLOCK_KHZ       ((unsigned int)125000)
#define LINK_CLOCK_KHZ      ((unsigned int)300000)

// -----------------------------------------------------------------------------
void ClockInit(void) {
  HAL_PLL_CoreSetup(INPUT_XTI_CLOCK_KHZ, CORE_CLOCK_KHZ);
  HAL_PLL_LinkSetup(INPUT_XTI_CLOCK_KHZ, LINK_CLOCK_KHZ);
  HAL_PLL_BusSetup(INPUT_XTI_CLOCK_KHZ, BUS_CLOCK_KHZ);

  HAL_PLL_StartCoreSync();
  HAL_PLL_StartExtBusSync();

  HAL_Pll_CoreStart();
  HAL_Pll_LinkStart();
  HAL_Pll_BusStart();

  // disable clock for some peripherals
  *(unsigned int* )(CMU_CFG8_LOAD_LOC) = 0x30e0;
  StupidDelayMs(100);
}

// -----------------------------------------------------------------------------
unsigned int ClockGetInputXtiKhz(void) {
  return INPUT_XTI_CLOCK_KHZ;
}
