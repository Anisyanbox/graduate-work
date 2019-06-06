#include <sysreg.h>
#include "ext_bus.h"
#include "hal_1967VN034R1.h"

// Only 16 or 32 integer value
// There is NAND (data16-data31) on the board.
// That's why we need to make bus 16-bits wide.
// Such we can use one SDRAM chip and NAND chip simultaneously.
#define EXT_BUS_BIT_SIZE      ((int)16)

// -----------------------------------------------------------------------------
void ExtBusInit (void) {
  unsigned int temp32u = 0;

  // Enable multiple writes to SYSCON/SDRCON
  // Turn off MIL-controller from GPIO pins
  *(unsigned int*)CMU_CFG1_LOC = ((1 << 3) | (1 << 8));
  HAL_Core_PrimariPriority();

  // Alternate function for DATA and ADDR bus
  temp32u = PX_ALT_PDB0 | PX_ALT_PDB1 | PX_ALT_PDB2 | PX_ALT_PDB3;  // data
  temp32u |= PX_ALT_PAB0 | PX_ALT_PAB1 | PX_ALT_PAB2;               // addr
  temp32u |= PX_ALT_PDB23F0;                                        // NAND flash controller
  *(unsigned int *)(PX_ALT_LOC) = temp32u;

  // set drive NAND control
  *(unsigned int *)(base_GPX + 3) = 0x7F000000;

  // sync signal for external memory
  temp32u = (PF_ALT << 7);
  *(unsigned int *)GPC_ALT_SET_LOC = temp32u;

  // Alternative functions for PORTC SRAM signals
  temp32u = (PF_ALT << 18) | (PF_ALT << 19) | (PF_ALT << 20) | \
            (PF_ALT << 21) | (PF_ALT << 22) | (PF_ALT << 23);
  *(unsigned int *)GPC_ALT_SET_LOC = temp32u;

  // Alternative functions for PORTC SDRAM signals
  temp32u = (PF_ALT << 8)  | (PF_ALT << 9)  | (PF_ALT << 10) | (PF_ALT << 11) | \
            (PF_ALT << 12) | (PF_ALT << 13) | (PF_ALT << 14) | (PF_ALT << 15) | \
            (PF_ALT << 16) | (PF_ALT << 17);
  *(unsigned int *)GPC_ALT_SET_LOC = temp32u;

  // short delay
  for (int i = 0; i < 1000; ++i) {
    __NOP;
  }
}

// -----------------------------------------------------------------------------
void SramInit(void) {
  unsigned int temp32u = 0;

  // Initializing SRAM
  temp32u = SYSCON_MS0_WT3		| \
            SYSCON_MS0_PIPE4	| \
            SYSCON_MS1_IDLE		| \
            SYSCON_MS1_WT3		| \
            SYSCON_MS1_PIPE4	| \
            SYSCON_MEM_WID16    | \
			(1 << 27);
  __builtin_sysreg_write(__SYSCON, temp32u);
}

// -----------------------------------------------------------------------------
void SdramInit(void) {
  unsigned int temp32u = 0;

  // Initializing SDRAM 
  temp32u = SDRCON_RAS2PC5 | \
            SDRCON_PC2RAS2 | \
            SDRCON_REF1100 | \
            SDRCON_PG512 |   \
            SDRCON_CLAT3 |   \
            SDRCON_ENBL;
  __builtin_sysreg_write(__SDRCON, temp32u);
  while((__builtin_sysreg_read(__SYSTAT) & (1 << 13)) == 0);
}
