/*********************************************************************/
/*                                                                   */
/*                            stdarg.h                               */
/*                                                                   */
/*          (c) 2014-2016, Angioscan Electronics                     */
/*********************************************************************/

#ifndef __STDARG_H
#define __STDARG_H

#ifndef __clang__

#define __sizeof_ints(x)            ((sizeof(x)-1) / sizeof(int) + 1)
#define __alignof_ints_minus_1(x)   ((__alignof__(x)-1) / __alignof__(int))


/* This version is intened for word-addressing architectures */
typedef int* va_list;
#define va_start(ap, parmN)	(((ap) = (va_list)((int *)(&parmN) + __sizeof_ints(parmN))))

#define va_arg(ap, type)     (*(type *)(((*(int **)&(ap)) = (int*)((unsigned int)((*(int **)&(ap)) + __alignof_ints_minus_1(type)) & (~__alignof_ints_minus_1(type))) + __sizeof_ints(type)) \
			           - __sizeof_ints(type)))
#define va_end(ap)

#else

#ifndef _VA_LIST
typedef __builtin_va_list va_list;
#define _VA_LIST
#endif
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap)          __builtin_va_end(ap)
#define va_arg(ap, type)    __builtin_va_arg(ap, type)

/* GCC always defines __va_copy, but does not define va_copy unless in c99 mode
 * or -ansi is not specified, since it was not part of C90.
 */
#define __va_copy(d,s) __builtin_va_copy(d,s)

#if __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L || !defined(__STRICT_ANSI__)
#define va_copy(dest, src)  __builtin_va_copy(dest, src)
#endif

/* Hack required to make standard headers work, at least on Ubuntu */
#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST 1
#endif
typedef __builtin_va_list __gnuc_va_list;

#endif


#include "decor.h"


#endif /*__STDARG_H*/
