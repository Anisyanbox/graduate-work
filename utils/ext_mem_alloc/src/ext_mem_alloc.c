#include "ext_mem_alloc.h"
#include "pthread.h"

#define SDRAM_START_BANK0         ((unsigned int)0x40000000)
#define SDRAM_END_BANK0           ((unsigned int)0x44000000)
#define SDRAM_BANK0_SIZE_IN_WORDS ((unsigned int)(SDRAM_END_BANK0 - SDRAM_START_BANK0))

typedef struct {
  size_t free_words_count;
  unsigned int curr_free_addr;
} AllocatedMemMap_t;

// -----------------------------------------------------------------------------
static AllocatedMemMap_t alloced_mem = {SDRAM_BANK0_SIZE_IN_WORDS, SDRAM_START_BANK0};

// -----------------------------------------------------------------------------
void * ExtMemAlloc(size_t num_words) {
  if (num_words > alloced_mem.free_words_count) {
    return NULL;
  }
  alloced_mem.free_words_count -= num_words;
  alloced_mem.curr_free_addr += (unsigned int)num_words;
  return (void* )(alloced_mem.curr_free_addr - (unsigned int)num_words);
}
