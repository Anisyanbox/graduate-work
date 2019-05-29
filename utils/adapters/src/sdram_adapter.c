#include "sdram_adapter.h"

#define SDRAM_START_BANK0     ((unsigned int)0x40000000)
#define SDRAM_END_BANK0       ((unsigned int)0x44000000)
#define SDRAM_WORD_SIZE_BANK0 ((unsigned int)(SDRAM_END_BANK0 - SDRAM_START_BANK0))

// -----------------------------------------------------------------------------
uint32_t * SramGetStartBank0Addr (void) {
  return (unsigned int*)SDRAM_START_BANK0;
}
