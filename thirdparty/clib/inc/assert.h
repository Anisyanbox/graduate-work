/*********************************************************************/
/*                                                                   */
/*                            assert.h                               */
/*                                                                   */
/*          (c) 2014-2016, Angioscan Electronics                     */
/*********************************************************************/

#ifndef __ASSERT_H
#define __ASSERT_H

#include <stdarg.h>

#undef assert

#ifdef NDEBUG
#define assert(condition) ((void)(0))
#else

#define __assert    __C_FUN(__assert)

#if defined(__cplusplus)
extern "C" {
#endif

extern void __assert ( const char * );

#if defined(__cplusplus)
}
#endif

#undef  __VALUE
#undef  __STRING
#define __VALUE(a)  #a
#define __STRING(a) __VALUE(a)
//#define assert(condition)   ((condition) ? ((void)0) \
//    : __assert( __FILE__ "," __STRING(__LINE__) "): " #condition ))
#define assert(condition)  if(condition) ((void)0); else asm("emutrap;;");
/*
 *   Sample message:
 *   Assertion failed (myfile.c,123): p == 0
 */

#endif                                  /* NDEBUG */
#endif                                  /* __ASSERT_H */
