/*********************************************************************/
/*                                                                   */
/*                         _stdlib.h                                 */
/*                                                                   */
/*          (c) 2014-2016, Angioscan Electronics                     */
/*********************************************************************/

#ifndef ___STDLIB_H
#define ___STDLIB_H

#include <stdlib.h>

#define FREE    0
#define IN_USE  1
#define LAST    2

#define size_BP 2

//#define SIZEM 0xffffU
#define SIZEM 0xffffffffUL


typedef struct h_list {

    // IlyaG: change memory alignment to 4 words
    int align1;
    int align2;

    size_t  flag;
    struct  h_list * nxt_ptr;
} H_LIST;

#define ERR_HEAP_INV 0 /* invalid memory block pointer */
#define ERR_HEAP_FRE 1 /* attempt to release free memory block */
#define ERR_HEAP_COR 2 /* internal heap structure is corrupt */
#define ERR_HEAP_REE 3 /* incorrect usage: heap functions are not reentrant */
#define ERR_HEAP_REA 4 /* attempt to reallocate free memory block */

#define NDIG    (DBL_DIG+2)
#define BLOCK   65535

extern H_LIST *      __HEAP_START_PTR;
extern H_LIST *      __HEAP_END_PTR;

extern void *        __VFUNC_PTR;

extern unsigned char __HEAP_UNLOCKED;

#define LOCK_HEAP   if (!( __HEAP_UNLOCKED ))  {\
                        _heap_err_handler(ERR_HEAP_REE, \
                        (_VFUNC_T *)(* (size_t *)__VFUNC_PTR) ); \
                        goto exit_if_locked; } \
                        else { __HEAP_UNLOCKED = 0; }
#define UNLOCK_HEAP __HEAP_UNLOCKED = 1

#endif /* ___STDLIB_H*/
