#include "clock.h"
#include "hal_1967VN034R1.h"

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
}

// -----------------------------------------------------------------------------
unsigned int ClockGetInputXtiKhz(void) {
  return INPUT_XTI_CLOCK_KHZ;
}
