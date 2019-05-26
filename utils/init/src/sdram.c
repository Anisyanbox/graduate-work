#include <sysreg.h>
#include "sdram.h"
#include "hal_1967VN034R1.h"

// Only 16 or 32 integer value
// There is NAND (data16-data31) on the board.
// That's why we need to make bus 16-bits wide.
// Such we can use one SDRAM chip and NAND chip simultaneosly.
#define EXT_BUS_BIT_SIZE      ((int)16)

// -----------------------------------------------------------------------------
void SdramControllerInit (void) {
  unsigned int temp32u;

	// Enable multiple writes to SYSCON/SDRCON
	*(unsigned int*)CMU_CFG1_LOC = (1 << 3) | (1 << 8);
	
	// ---------------------------- //
	// GPIO setup	

	// sync signal for external mem
  temp32u = (PF_ALT << 7);
  *(unsigned int *)GPC_ALT_SET_LOC = temp32u;

  // Atlernate functions for PORTC SRAM signals
	temp32u = (PF_ALT << 18) | (PF_ALT << 19) | (PF_ALT << 20) | \
            (PF_ALT << 21) | (PF_ALT << 22) | (PF_ALT << 23);
	*(unsigned int *)GPC_ALT_SET_LOC = temp32u;
		
	// Atlernate functions for PORTC SDRAM signals
	temp32u = (PF_ALT << 8)  | (PF_ALT << 9)  | (PF_ALT << 10) | (PF_ALT << 11) | \
            (PF_ALT << 12) | (PF_ALT << 13) | (PF_ALT << 14) | (PF_ALT << 15) | \
            (PF_ALT << 16) | (PF_ALT << 17);
	*(unsigned int *)GPC_ALT_SET_LOC = temp32u;
	
	// Alternate function for DATA and ADDR bus
	temp32u = PX_ALT_PDB0 | PX_ALT_PDB1 | PX_ALT_PDB2 | PX_ALT_PDB3;  // data
	temp32u |= PX_ALT_PAB0 | PX_ALT_PAB1 | PX_ALT_PAB2;               // addr
	*(unsigned int *)(PX_ALT_LOC) = temp32u;

  // ---------------------------- //
	// Configure syscon register
  temp32u =   SYSCON_MS0_IDLE		|
              SYSCON_MS0_WT3		|
              SYSCON_MS0_PIPE1	|
              SYSCON_MS0_SLOW		|
              SYSCON_MS1_IDLE		|
              SYSCON_MS1_WT0		|
              SYSCON_MS1_PIPE2	|
              SYSCON_MEM_WID64;
  __builtin_sysreg_write(__SYSCON, temp32u);
	
  // ---------------------------- //
  // Initializing SDRAM 
  temp32u =   SDRCON_ENBL 	|
              SDRCON_CLAT3 	|     // only CAS latency 2 or 3 are supported by mt48lc4m32b2 model
              SDRCON_PG1K		|     //Column Addressing range A0�A9 -> MT48LC32M16A2
              SDRCON_REF1100  |
              SDRCON_PC2RAS4	|		// trp, precharge to active time, 20 ns
              SDRCON_RAS2PC8	|		// tras,  active to precharge time, 42 ns min
              SDRCON_INIT;
  __builtin_sysreg_write(__SDRCON, temp32u);
	while((__builtin_sysreg_read(__SYSTAT) & (1 << 13)) == 0);
}
