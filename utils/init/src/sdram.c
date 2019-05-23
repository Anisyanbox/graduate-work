#include <sysreg.h>
#include "sdram.h"
#include "hal_1967VN034R1.h"

// Only 16 or 32 integer value
// There is NAND (data16-data31) on the board.
// That's why we need to make bus 16-bits wide.
// Such we can use one SDRAM chip and NAND chip simultaneosly.
#define EXT_BUS_BIT_SIZE      ((int)16)

void SdramControllerInit (void) {
  int sdrcon = 0;

  sdrcon =  SDRCON_INIT |     // cmd MRS after memory regeneration
            SDRCON_RAS2PC2 |  // delay from strob RAS to PreCharge cmd, 20 ns
            SDRCON_PC2RAS2 |  // delay from PreCharge cmd to strob RAS, 20 ns
            SDRCON_REF1100 |  // period memory regeneration
            SDRCON_PG1K |     // page size MT48LC16M16A2
            SDRCON_CLAT3 |    // MT48LC16M16A2 supports delay 3
            SDRCON_ENBL;      // enable controller SDRAM
  HAL_GPIO_Px_AltInit(GPIO_PxAlt_Data7_0 | GPIO_PxAlt_Data15_8 |                        \
                      GPIO_PxAlt_Addr7_0 | GPIO_PxAlt_Addr15_8 | GPIO_PxAlt_Addr21_16,  \
                      GPIO_PxAlt_Mode_SDRAM);
  
  // SCKL     - PIN_7  - clock signal for external 
  // CKE      - GPIO_PIN_8  - allowed sync
  // nMSSD0   - GPIO_PIN_9  - low lewel = active choosen memory chip
  // nCAS     - GPIO_PIN_13 - bit cmd
  // nRAS     - GPIO_PIN_14 - bit cmd
  // nWE      - GPIO_PIN_15 - bit cmd
  // DQM      - GPIO_PIN_16 - mask for write operatons
  // A10      - GPIO_PIN_17 - bit10 for addres
  // after this function this pins are controlled by SDRAM contoller
  HAL_GPIO_Init(LX_GPIO_PC,                                             \
                GPIO_PIN_8  | GPIO_PIN_9  | GPIO_PIN_13 |               \
                GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_16 | GPIO_PIN_17,  \
                GPIO_PinMode_Alt);
  HAL_SYS_ExtBusEnable(EXT_BUS_BIT_SIZE);
  HAL_SYS_SDRAMEnable(sdrcon);								
}
