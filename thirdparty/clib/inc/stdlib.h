/*********************************************************************/
/*                                                                   */
/*                         stdlib.h                                  */
/*                                                                   */
/*          (c) 2014-2016, Angioscan Electronics                     */
/*********************************************************************/

#ifndef __STDLIB_H
#define __STDLIB_H

#include <stdarg.h>
#include <stddef.h>

#ifndef _SIZE_T
#define _SIZE_T
#ifdef __EDG__
typedef __EDG_SIZE_TYPE__  size_t;
#else
typedef unsigned int size_t;
#endif
#endif

#ifndef   NULL
#define   NULL 0
#endif

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

# define RAND_MAX	32767
# define MB_CUR_MAX	1


typedef struct
{
  int   quot;
  int   rem;
} div_t;

typedef struct
{
  long       quot;
  long       rem;
} ldiv_t;

typedef void (*_VFUNC_T)();

#define RAND_MAX 32767


/* Function name modifications for different char/double sizes */
#define atof      __CD_FUN(atof)
#define atoi      __C_FUN(atoi)
#define atol      __C_FUN(atol)
#define calloc    __C_FUN(calloc)
#define malloc    __C_FUN(malloc)
#define realloc   __C_FUN(realloc)
#define _ultohex  __C_FUN(_ultohex)
#define strtod    __CD_FUN(strtod)
#define strtol    __C_FUN(strtol)
#define strtoul   __C_FUN(strtoul)
#ifndef __NO_LONG_LONG
#define strtoll   __C_FUN(strtoll)
#define strtoull  __C_FUN(strtoull)
#endif  /* __NO_LONG_LONG */
#define bsearch   __C_FUN(bsearch)
#define qsort     __C_FUN(qsort)
#define mblen     __C_FUN(mblen)
#define mbtowc    __C_FUN(mbtowc)
#define wctomb    __C_FUN(wctomb)
#define mbstowcs  __C_FUN(mbstowcs)
#define wcstombs  __C_FUN(wcstombs)





#if defined(__cplusplus)
extern "C" {
#endif

#define abs(a) __builtin_abs(a)
#define count_ones(a) __builtin_count_ones(a)
extern int avg(int, int);
extern div_t div(int, int);
extern int clip(int, int);
extern int max(int, int);
extern int min(int, int);


#define labs(a) ((long)__builtin_abs((int)a))
#define lcount_ones(a) ((long)__builtin_count_ones((int)a))
extern long lavg(long, long);
extern ldiv_t ldiv(long, long);
extern long lclip(long, long);
extern long lmax(long, long);
extern long lmin(long, long);

extern int addbitrev(int, int);

extern void   abort(void);
extern int    atexit(_VFUNC_T);
extern void   exit(int);
extern double atof(const char* nptr);
extern int    atoi(const char* nptr);
extern long   atol(const char* nptr);
extern int    rand(void);
extern void   srand(unsigned int);
extern void * calloc(size_t, size_t len);
extern void * malloc(size_t);
extern void   free(void *);
extern void * realloc(void *, size_t);
extern void   _heap_check(void);
extern void   _heap_err_handler(int, _VFUNC_T *);
extern char * _ultohex(unsigned long val, char *buf);

extern double        strtod(const char *,char **);
extern long double	 strtold(const char *, char **);
extern long double	 atold(const char *);

extern long          strtol(const char *,  char **, int );
extern unsigned long strtoul(const char *, char **, int );

#ifndef __NO_LONG_LONG

extern long long			  atoll(const char *);
extern long long          strtoll(const char *,  char **, int );
extern unsigned long long strtoull(const char *, char **, int );


#define llabs(a) __builtin_llabs((a))
#define llmax(a, b) __builtin_llmax((a), (b))
#define llmin(a, b) __builtin_llmin((a), (b))

extern long long llavg(long long, long long);
extern long long llclip(long long, long long);
extern long long llcount_ones(long long);


#endif  /* __NO_LONG_LONG */





extern void * bsearch(const void *key, const void *base, size_t nmemb, 
                      size_t size, int (*compar)(const void *, const void *));

extern void   qsort(const void *base, size_t nmemb, 
                      size_t size, int (*compar)(const void *, const void *));

extern int mblen(const char *_S, size_t _N);
extern int mbtowc(wchar_t *_Pwc, const char *_S, size_t _N);
extern int wctomb(char *_S, wchar_t _Wchar);
extern size_t mbstowcs(wchar_t *_Pwcs, const char *_S, size_t _N);
extern size_t wcstombs(char *_S, const wchar_t *_Pwcs, size_t _N);

#if defined(__cplusplus)
}
#endif


#endif  /*__STDLIB_H*/
