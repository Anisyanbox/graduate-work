/*********************************************************************/
/*                                                                   */
/*                         limits.h                                  */
/*                                                                   */
/*          (c) 2014-2016, Angioscan Electronics                     */
/*********************************************************************/

#ifndef __LIMITS_H
#define __LIMITS_H

#if __TS_BYTE_ADDRESS

#define CHAR_BIT			      8

#if __SCHAR__ != 0
#define CHAR_MAX            +127
#define CHAR_MIN            (-127-1)
#else
#define CHAR_MAX			      255
#define CHAR_MIN			      0
#endif

#define SCHAR_MAX           +127
#define SCHAR_MIN           (-127-1)
#define UCHAR_MAX			      255

#define SHRT_MAX            +32767
#define SHRT_MIN            (-32767-1)
#define USHRT_MAX           65535U

#else

#define CHAR_BIT            32

#if __SCHAR__ != 0
#define CHAR_MAX            +2147483647
#define CHAR_MIN            (-2147483647-1)
#else
#define CHAR_MAX            4294967295U
#define CHAR_MIN            0
#endif

#define SCHAR_MAX           +2147483647
#define SCHAR_MIN           (-2147483647-1)
#define UCHAR_MAX           4294967295U

#define SHRT_MAX            +2147483647
#define SHRT_MIN            (-2147483647-1)
#define USHRT_MAX           4294967295U

#endif  /* __TS_BYTE_ADDRESS */

#define INT_MAX             +2147483647
#define INT_MIN             (-2147483647-1)
#define UINT_MAX            4294967295U

#define LONG_MAX            +2147483647L
#define LONG_MIN            (-2147483647L-1L)
#define ULONG_MAX           4294967295UL

#ifndef __NO_LONG_LONG
#define LONG_LONG_MAX	      9223372036854775807LL
#define LONG_LONG_MIN       (-LONG_LONG_MAX-1)
#define ULONG_LONG_MAX      (LONG_LONG_MAX * 2ULL + 1)
#define LLONG_MAX	          LONG_LONG_MAX
#define LLONG_MIN	          LONG_LONG_MIN
#define ULLONG_MAX	        ULONG_LONG_MAX
#endif  /* __NO_LONG_LONG */

#define MB_LEN_MAX          1
#define PATH_MAX            4096

#endif /*__LIMITS_H*/
