
/*********************************************************************/
/*                                                                   */
/*                           stdio.h                                 */
/*                                                                   */
/*          (c) 2014-2016, Angioscan Electronics                     */
/*********************************************************************/

#ifndef __STDIO_H
#define __STDIO_H

#include <stdarg.h>

/* if you do not want print/scan floating type operands, */
/*#define __NOFLOAT*/

#ifndef _SIZE_T
#define _SIZE_T
#ifdef __EDG__
typedef __EDG_SIZE_TYPE__  size_t;
#else
typedef unsigned int size_t;
#endif
#endif

#ifndef __cplusplus
#ifndef _WCHAR_T
#define _WCHAR_T
#if (__CHAR_BIT__==32)
typedef int wchar_t;
#else
typedef short wchar_t;
#endif
#endif
#endif

#ifndef EOF
#define EOF (-1)
#endif

#ifndef NULL
#define NULL 0
#endif


/* Declaration of the FILE type */
typedef struct {
    unsigned int _ftype;            /* stream type                        */
    unsigned int _fstat;            /* stream status flags                */
    int (* _iogetp)   (void);       /* ptr to custom "get" function       */
    int (* _ioputp)   (int);        /* ptr to custom "put" function       */
    void(* _ioclrerr) (void);       /* ptr to custom "clearerr" function  */
    void(* _ioinit)   (void);       /* ptr to custom stream init function */
    union {
        struct {
            unsigned char __ugt_byte0;  /* 1st unget character */
            unsigned char __ugt_byte1;  /* 2nd unget character */
        } __file_unget;
        char * __ssptr;                 /* ptr for internal purposes only */
    } __file_union;
} FILE;

/* Possible _ftype values */
#define _STREAM_RO   1
#define _STREAM_WO   2
#define _STREAM_RW   3

/* Declarations of the standard i/o stream and appropriate pointers */
extern FILE _stdio_stream;

/* Function name modifications for different char/double sizes */
#define getchar   __C_FUN(getchar)
#define putchar   __C_FUN(putchar)
#define gets      __C_FUN(gets)
#define puts      __C_FUN(puts)
#define fscanf    __CD_FUN(fscanf)
#define scanf     __CD_FUN(scanf)
#define sscanf    __CD_FUN(sscanf)
#define sprintf   __CD_FUN(sprintf)
#define printf    __CD_FUN(printf)
#define vprintf   __CD_FUN(vprintf)
#define vsprintf  __CD_FUN(vsprintf)
#define vsnprintf __CD_FUN(vsnprintf)
#define fprintf   __CD_FUN(fprintf)
#define fputc     __C_FUN(fputc)
#define fgetc     __C_FUN(fgetc)
#define fgets     __C_FUN(fgets)
#define fputs     __C_FUN(fputs)
#define ungetc    __C_FUN(ungetc)

#ifdef __llvm__
#define stdin     __C_FUN(stdin)
#define stderr     __C_FUN(stderr)
#define stdout     __C_FUN(stdout)
#endif

extern FILE * stdin, * stdout, * stderr;

#if defined(__cplusplus)
extern "C" {
#endif

extern int    getchar (void);
extern int    putchar (int c);
extern char * gets (char *s);
extern int    puts (const char *);
extern int    fscanf (FILE *, const char *, ...);
extern int    scanf (const char *, ...);
extern int    sscanf (const char *,const char *, ...);
extern int    sprintf (char *,const char *, ...);
extern int    printf (const char *, ...);
extern int    vprintf (const char *, va_list);
extern int    vsprintf (char *,const char *, va_list);
extern int    vsnprintf (char *, size_t, const char *, va_list);   /* extension */

extern int    fputc (int, FILE *);
extern int    fgetc (FILE *);
extern int    ungetc (int, FILE *);
extern int    fprintf (FILE *, const char *, ...);
extern char * fgets(char *, int, FILE *);
extern int    fputs(const char *, FILE *);
extern void   clearerr(FILE * stream);
extern int    ferror(FILE * stream);
extern void   _fopen(FILE * stream);

/* Customizable low level i/o operations */
extern int  _putchar ( int c );
extern int  _getchar ( void  );
extern void _clrerr ( void  );
extern void _init_IO ( void  );

#if defined(__cplusplus)
}
#endif

#undef getchar
#undef putchar
#define getchar()   (fgetc(stdin))
#define putchar(c)  (fputc((c),stdout))

#endif  /*__STDIO_H*/
