/*********************************************************************/
/*                                                                   */
/*                         _stdio.h                                  */
/*                                                                   */
/*          (c) 2014-2016, Angioscan Electronics                     */
/*********************************************************************/

#ifndef ___STDIO_H
#define ___STDIO_H

#include <stdio.h>
#include <stdarg.h>


/* FILE._ftype */
#define IOSTRING             0x04
#define IOREAD               0x01
#define IOWRITE              0x02

/* FILE._fstat */
#define IOEOF               0x01
#define IOERR               0x02
#define UNGET_BYTE0_READY   0x04
#define UNGET_BYTE1_READY   0x08

/* macros to access several members of FILE */
#define SPTR                __file_union.__ssptr
#define UNGET_BYTE0         __file_union.__file_unget.__ugt_byte0
#define UNGET_BYTE1         __file_union.__file_unget.__ugt_byte1

/* 64-bit format is supported, but MAXEXP is set for single precision format */
/* 8-bit exponent takes up 38 decimal digits     */

#define	MAXEXP		38

/* 53 bit fraction takes up 16 decimal digits; max reasonable precision  */

#define	MAXFRACT	16
#define	DEFPREC		6

#define BUF             (MAXEXP+MAXFRACT+1)     /* + decimal point */

#ifndef __NO_LONG_LONG
#define ARG(basetype) \
        _ulong = flags&LLONGINT ? va_arg(argp, long long) : \
                 flags&LONGINT  ? (long basetype)va_arg(argp, long) : \
                 flags&SHORTINT ? (short basetype)va_arg(argp, int) : \
                                  (basetype)va_arg(argp, int)
#define _T_MAX_LONG      long long
#define _T_MAX_ULONG     unsigned long long
#else
#define ARG(basetype) \
        _ulong = flags&LONGINT ? va_arg(argp, long) : \
        flags&SHORTINT ? (short basetype)va_arg(argp, int) : \
        va_arg(argp, int)
#define _T_MAX_LONG      long
#define _T_MAX_ULONG     unsigned long
#endif  /* __NO_LONG_LONG */

#define	todigit(c)	((c) - '0')
#define	tochar(n)	((n) + '0')

#define LONGINT         0x01   /* long integer */
#define LONGDBL         0x02   /* long double */
#define SHORTINT        0x04   /* short integer */
#define ALT             0x08   /* alternate form */
#define LADJUST         0x10   /* left adjustment */
#define ZEROPAD         0x20   /* zero (as opposed to blank) pad */
#define HEXPREFIX       0x40   /* add 0x or 0X prefix */
#ifndef __NO_LONG_LONG
#define LLONGINT        0x80   /* long long integer */
#endif  /* __NO_LONG_LONG */

#define SPC     1
#define STP     2

#define	SHORT	  0
#define	REGULAR	1
#define	LONG	  2
#define LONG_L  3
#ifndef __NO_LONG_LONG
#define	LLONG	  4
#endif  /* __NO_LONG_LONG */
#define INT     0
#define	FLOAT	  1


/* Function name modifications for different char/double sizes */
#define __round     __C_FUN(__round)
#define __cvt       __C_FUN(__cvt)
#define __exponent  __C_FUN(__exponent)
#define __doprintf  __CD_FUN(__doprintf)
#define __donprintf __CD_FUN(__donprintf)
#define __doscan    __CD_FUN(__doscan)
#define __innum     __CD_FUN(__innum)
#define __getccl    __C_FUN(__getccl)
#define __instr     __C_FUN(__instr)
#define __fputc     __C_FUN(__fputc)
#define __fgetc     __C_FUN(__fgetc)
#define __ungetc    __C_FUN(__ungetc)


#if defined(__cplusplus)
extern "C" {
#endif

extern char * __round (long double , int *, char *, char *, char, char *);
extern int    __cvt (long double, int, int, char *, unsigned char, char *, char *);
extern char * __exponent (char *, int, unsigned char);
extern int    __doprintf (FILE *, const char *, va_list);
extern int    __donprintf (FILE *, size_t, const char *, va_list);
extern int    __doscan (FILE *, const char *, void **);
extern int    __innum (int **, int, int, int, FILE *, int *,int *);
extern char * __getccl (unsigned char *);
extern int    __instr ( char *, int, int, FILE *, int *,int *);


extern int    __fputc (int, FILE *);
extern int    __fgetc (FILE *);
extern int    __ungetc (int, FILE *);

#if defined(__cplusplus)
}
#endif


#endif /*___STDIO_H*/
