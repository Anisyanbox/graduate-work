/*********************************************************************/
/*                                                                   */
/*                             float.h                               */
/*                                                                   */
/*          (c) 2014-2016, Angioscan Electronics                     */
/*********************************************************************/

#ifndef __FLOAT_H
#define __FLOAT_H

#define FLT_ROUNDS              1       /* rounding mode: to nearest */
#define FLT_RADIX               2

#define FLT_MANT_DIG            24
#define FLT_EPSILON             1.19209290E-07F
#define FLT_DIG                 6
#define FLT_MIN_EXP             (-125)
#define FLT_MIN                 1.17549435E-38F
#define FLT_MIN_10_EXP          (-37)
#define FLT_MAX_EXP             +128
#define FLT_MAX                 3.40282347E+38F
#define FLT_MAX_10_EXP          +38

#define LDBL_MANT_DIG           53
#define LDBL_EPSILON            2.2204460492503131E-16L
#define LDBL_DIG                15
#define LDBL_MIN_EXP            (-1021)
#define LDBL_MIN                2.2250738585072014E-308L
#define LDBL_MIN_10_EXP         (-307)
#define LDBL_MAX_EXP            +1024
#define LDBL_MAX                1.7976931348623157E+308L
#define LDBL_MAX_10_EXP         +308


#if __DOUBLES_ARE_FLOATS__

#define DBL_MANT_DIG            FLT_MANT_DIG
#define DBL_EPSILON             ((double)FLT_EPSILON)
#define DBL_DIG                 FLT_DIG
#define DBL_MIN_EXP             FLT_MIN_EXP
#define DBL_MIN                 ((double)FLT_MIN)
#define DBL_MIN_10_EXP          FLT_MIN_10_EXP
#define DBL_MAX_EXP             FLT_MAX_EXP
#define DBL_MAX                 ((double)FLT_MAX)
#define DBL_MAX_10_EXP          FLT_MAX_10_EXP

#else /* !__DOUBLES_ARE_FLOATS__ */

#define DBL_MANT_DIG            LDBL_MANT_DIG
#define DBL_EPSILON             ((double)LDBL_EPSILON)
#define DBL_DIG                 LDBL_DIG
#define DBL_MIN_EXP             LDBL_MIN_EXP
#define DBL_MIN                 ((double)LDBL_MIN)
#define DBL_MIN_10_EXP          LDBL_MIN_10_EXP
#define DBL_MAX_EXP             LDBL_MAX_EXP
#define DBL_MAX                 ((double)LDBL_MAX)
#define DBL_MAX_10_EXP          LDBL_MAX_10_EXP

#endif /* __DOUBLES_ARE_FLOATS__ */

#endif /* __FLOAT_H */
