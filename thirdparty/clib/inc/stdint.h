/*********************************************************************/
/*                                                                   */
/*             stdint.h standard header                              */
/*                                                                   */
/*          (c) 2014-2016, Angioscan Electronics                     */
/*********************************************************************/

#ifndef __STDINT_H
#define __STDINT_H


   typedef   signed          char int8_t;
   typedef   signed short     int int16_t;
   typedef   signed           int int32_t;
#ifndef __NO_LONG_LONG
   typedef   signed long long int int64_t; 
#endif  /* __NO_LONG_LONG */

   typedef unsigned          char uint8_t;
   typedef unsigned short     int uint16_t;
   typedef unsigned           int uint32_t;
#ifndef __NO_LONG_LONG
   typedef unsigned long long int uint64_t; 
#endif  /* __NO_LONG_LONG */

   typedef   signed          char int_least8_t;
   typedef   signed short     int int_least16_t;
   typedef   signed           int int_least32_t;
#ifndef __NO_LONG_LONG
   typedef   signed long long int int_least64_t; 
#endif  /* __NO_LONG_LONG */

   typedef unsigned          char uint_least8_t;
   typedef unsigned short     int uint_least16_t;
   typedef unsigned           int uint_least32_t;
#ifndef __NO_LONG_LONG
   typedef unsigned long long int uint_least64_t; 
#endif  /* __NO_LONG_LONG */

   typedef   signed           int int_fast8_t;
   typedef   signed           int int_fast16_t;
   typedef   signed           int int_fast32_t;
#ifndef __NO_LONG_LONG
   typedef   signed long long int int_fast64_t; 
#endif  /* __NO_LONG_LONG */

   typedef unsigned           int uint_fast8_t;
   typedef unsigned           int uint_fast16_t;
   typedef unsigned           int uint_fast32_t;
#ifndef __NO_LONG_LONG
   typedef unsigned long long int uint_fast64_t; 
#endif  /* __NO_LONG_LONG */

   typedef   signed           int intptr_t;
   typedef unsigned           int uintptr_t;

#if __TS_BYTE_ADDRESS
   #define INT8_MIN           (-127-1)
   #define INT16_MIN          (-32767-1)
#else
   #define INT8_MIN           (-2147483647-1)
   #define INT16_MIN          (-2147483647-1)
#endif /* __TS_BYTE_ADDRESS */
   #define INT32_MIN          (-2147483647-1)
#ifndef __NO_LONG_LONG
   #define INT64_MIN          (-9223372036854775807LL-1)
#endif  /* __NO_LONG_LONG */

#if __TS_BYTE_ADDRESS
   #define INT8_MAX           +127
   #define INT16_MAX          +32767
#else
   #define INT8_MAX           +2147483647
   #define INT16_MAX          +2147483647
#endif /* __TS_BYTE_ADDRESS */
   #define INT32_MAX          +2147483647
#ifndef __NO_LONG_LONG
   #define INT64_MAX          +9223372036854775807LL 
#endif  /* __NO_LONG_LONG */

#if __TS_BYTE_ADDRESS
   #define UINT8_MAX          255
   #define UINT16_MAX         65535U
#else
   #define UINT8_MAX          4294967295U
   #define UINT16_MAX         4294967295U
#endif /* __TS_BYTE_ADDRESS */
   #define UINT32_MAX         4294967295U
#ifndef __NO_LONG_LONG
   #define UINT64_MAX         (9223372036854775807ULL * 2 + 1) 
#endif  /* __NO_LONG_LONG */

#if __TS_BYTE_ADDRESS
   #define INT_LEAST8_MIN     (-127-1)           
   #define INT_LEAST16_MIN    (-32767-1)         
#else
   #define INT_LEAST8_MIN     (-2147483647-1)
   #define INT_LEAST16_MIN    (-2147483647-1)
#endif /* __TS_BYTE_ADDRESS */
   #define INT_LEAST32_MIN    (-2147483647-1)    
#ifndef __NO_LONG_LONG
   #define INT_LEAST64_MIN    (-9223372036854775807LL-1)
#endif  /* __NO_LONG_LONG */
   
#if __TS_BYTE_ADDRESS
   #define INT_LEAST8_MAX     +127                 
   #define INT_LEAST16_MAX    +32767               
#else
   #define INT_LEAST8_MAX     +2147483647
   #define INT_LEAST16_MAX    +2147483647
#endif /* __TS_BYTE_ADDRESS */
   #define INT_LEAST32_MAX    +2147483647          
#ifndef __NO_LONG_LONG
   #define INT_LEAST64_MAX    +9223372036854775807LL 
#endif  /* __NO_LONG_LONG */
   
#if __TS_BYTE_ADDRESS
   #define UINT_LEAST8_MAX    255          
   #define UINT_LEAST16_MAX   65535U       
#else
   #define UINT_LEAST8_MAX    4294967295U
   #define UINT_LEAST16_MAX   4294967295U
#endif /* __TS_BYTE_ADDRESS */
   #define UINT_LEAST32_MAX   4294967295U
#ifndef __NO_LONG_LONG
   #define UINT64_LEAST_MAX   (9223372036854775807ULL * 2 + 1) 
#endif  /* __NO_LONG_LONG */

   #define INT_FAST8_MIN      INT32_MIN
   #define INT_FAST16_MIN     INT32_MIN
   #define INT_FAST32_MIN     INT32_MIN
#ifndef __NO_LONG_LONG
   #define INT_FAST64_MIN     INT64_MIN
#endif  /* __NO_LONG_LONG */
   
   #define INT_FAST8_MAX      INT32_MAX       
   #define INT_FAST16_MAX     INT32_MAX       
   #define INT_FAST32_MAX     INT32_MAX       
#ifndef __NO_LONG_LONG
   #define INT_FAST64_MAX     INT64_MAX
#endif  /* __NO_LONG_LONG */
   
   #define UINT_FAST8_MAX     UINT32_MAX       
   #define UINT_FAST16_MAX    UINT32_MAX       
   #define UINT_FAST32_MAX    UINT32_MAX       
#ifndef __NO_LONG_LONG
   #define UINT_FAST64_MAX    UINT64_MAX
#endif  /* __NO_LONG_LONG */
 
   #define INTPTR_MIN         INT32_MIN
   #define INTPTR_MAX         INT32_MAX
   #define UINTPTR_MAX        UINT32_MAX

   #define PTRDIFF_MIN        INT32_MIN
   #define PTRDIFF_MAX        INT32_MAX
   
   #define SIG_ATOMIC_MIN     INT32_MIN
   #define SIG_ATOMIC_MAX     INT32_MAX

   #define SIZE_MAX           UINT32_MAX

   #define WCHAR_MIN          0
   #define WCHAR_MAX          UINT16_MAX

   #define WINT_MIN           INT32_MIN
   #define WINT_MAX           INT32_MAX

   #define INT8_C(x)          (x)
   #define INT16_C(x)         (x)
   #define INT32_C(x)         (x)
#ifndef __NO_LONG_LONG
   #define INT64_C(x)         (x ## LL)
#endif  /* __NO_LONG_LONG */

   #define UINT8_C(x)         (x ## U)
   #define UINT16_C(x)        (x ## U)
   #define UINT32_C(x)        (x ## U)
#ifndef __NO_LONG_LONG
   #define UINT64_C(x)        (x ## ULL)
#endif  /* __NO_LONG_LONG */
   
#endif /* __STDINT_H */
   
/* end of stdint.h */
   
