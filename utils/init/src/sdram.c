#include <sysreg.h>
#include "sdram.h"
#include "hal_1967VN034R1.h"

// Only 16 or 32 integer value
// There is NAND (data16-data31) on the board.
// That's why we need to make bus 16-bits wide.
// Such we can use one SDRAM chip and NAND chip simultaneosly.
#define EXT_BUS_BIT_SIZE      ((int)16)

void SdramControllerInit (void) {
  HAL_GPIO_Px_AltDeInit();

  // Enable multiple writes to SYSCON/SDRCON
  *(unsigned int*)CMU_CFG1_LOC = (1 << 3);  // SYS_WE
  
  // Atlernative functions for PORTC static memory signals
  unsigned int temp32u = 0;
  temp32u = (PF_ALT<<18) | (PF_ALT<<19) | (PF_ALT<<20) | (PF_ALT<<21) | (PF_ALT<<22);;// | (PF_ALT<<23);;
  *(unsigned int *)GPC_ALT_SET_LOC = temp32u;

  // Atlernative functions for DRAM memory signals
  HAL_GPIO_Px_AltInit(GPIO_PxAlt_Data7_0 | GPIO_PxAlt_Data15_8 |                        \
                      GPIO_PxAlt_Addr7_0 | GPIO_PxAlt_Addr15_8 | GPIO_PxAlt_Addr21_16,  \
                      GPIO_PxAlt_Mode_SDRAM);
  
  // SCKL     - PIN_7  - clock signal for external 
  // CKE      - GPIO_PIN_8  - allowed sync
  // nMSSD0   - GPIO_PIN_9  - low level = active chosen memory chip
  // nCAS     - GPIO_PIN_13 - bit cmd
  // nRAS     - GPIO_PIN_14 - bit cmd
  // nWE      - GPIO_PIN_15 - bit cmd
  // DQM      - GPIO_PIN_16 - mask for write operations
  // A10      - GPIO_PIN_17 - bit10 for addres
  // after this function this pins are controlled by SDRAM controller
  HAL_GPIO_Init(LX_GPIO_PC,                                             \
                GPIO_PIN_8  | GPIO_PIN_9  |GPIO_PIN_10 | GPIO_PIN_11 |  \
                GPIO_PIN_12 | GPIO_PIN_13 |GPIO_PIN_14 | GPIO_PIN_15 |  \
                GPIO_PIN_16 | GPIO_PIN_17,  \
                GPIO_PinMode_Alt);

  // config SYSCON register
  temp32u =  SYSCON_MS0_IDLE   |
            SYSCON_MS0_WT3    |
            SYSCON_MS0_PIPE1  |
            SYSCON_MS0_SLOW   |

            SYSCON_MS1_IDLE   |
            SYSCON_MS1_WT0    |
            SYSCON_MS1_PIPE2  |
            //SYSCON_MS1_SLOW	|

            //SYSCON_MSH_IDLE |
            //SYSCON_MSH_WT0  |
            //SYSCON_MSH_PIPE2  |
            //SYSCON_MSH_SLOW |

            SYSCON_MEM_WID64  |		// 16 bits width
            //SYSCON_MP_WID64	|
            //SYSCON_HOST_WID64	|
            0x00;;	
  __builtin_sysreg_write(__SYSCON, temp32u);
  
  // config SDRCON register
  temp32u =  SDRCON_INIT |     // cmd MRS after memory regeneration
            SDRCON_RAS2PC2 |  // delay from strob RAS to PreCharge cmd, 20 ns
            SDRCON_PC2RAS2 |  // delay from PreCharge cmd to strob RAS, 20 ns
            SDRCON_REF1100 |  // period memory regeneration
            SDRCON_PG1K |     // page size MT48LC16M16A2
            SDRCON_CLAT3 |    // MT48LC16M16A2 supports delay 3
            SDRCON_INIT |
            SDRCON_ENBL;      // enable controller SDRAM

  HAL_SYS_ExtBusEnable(EXT_BUS_BIT_SIZE);
  __builtin_sysreg_write(__SDRCON, temp32u);
  while( !(__builtin_sysreg_read(__SYSTAT)&(1<<13)) ); //Wait SDRAM Enable
}
