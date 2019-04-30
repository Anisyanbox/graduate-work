#ifndef __DECOR_H
#define __DECOR_H

#ifdef __llvm__
/* add prefix for addembler functions */
#define __ASM_FUN(fun) _##fun
#define __ASM_VAR(fun) _##fun
#else
#define __ASM_FUN(fun) fun
#define __ASM_VAR(fun) fun
#endif


/* Library function prefixes for different double and char sizes */
#if defined(__CLIB_PREFIX_CHAR) && defined(__CLIB_PREFIX_DOUBLE)
#define __1_IMP_FUN(pfx, fun)         pfx##_##fun
#define __2_IMP_FUN(pfx1, pfx2, fun)  pfx1##pfx2##_##fun
#define __1_FUN(pfx, fun)           __1_IMP_FUN(pfx, fun)
#define __2_FUN(pfx1, pfx2, fun)    __2_IMP_FUN(pfx1, pfx2, fun)
#define __C_FUN(fun)                __1_FUN(__CLIB_PREFIX_CHAR, fun)
#define __D_FUN(fun)                __1_FUN(__CLIB_PREFIX_DOUBLE, fun)
#define __CD_FUN(fun)               __2_FUN(__CLIB_PREFIX_CHAR, __CLIB_PREFIX_DOUBLE, fun)
#else
#define __C_FUN(fun)                fun
#define __D_FUN(fun)                fun
#define __CD_FUN(fun)               fun
#endif /* __CLIB_PREFIX_CHAR && __CLIB_PREFIX_DOUBLE */



#endif /* __DECOR_H */

