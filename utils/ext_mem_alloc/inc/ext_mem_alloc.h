#ifndef _UTILS_EXT_MEM_ALLOC_INC_EXT_MEM_ALLOC_H_
#define _UTILS_EXT_MEM_ALLOC_INC_EXT_MEM_ALLOC_H_

#include <stdlib.h>

/*
* Function returns pointer to allocated memory or 
* NULL if has no enough memory
* 
* - num_words - count words to allocate
*/
unsigned int * ExtMemAlloc(size_t num_words);

#endif  // _UTILS_EXT_MEM_ALLOC_INC_EXT_MEM_ALLOC_H_
