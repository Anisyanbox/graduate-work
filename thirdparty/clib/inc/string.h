/*********************************************************************/
/*                                                                   */
/*                            string.h                               */
/*                                                                   */
/*          (c) 2014-2016, Angioscan Electronics                     */
/*********************************************************************/

#ifndef __STRING_H
#define __STRING_H

#include <stdarg.h>

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


/* Function name modifications for different char/double sizes */
#define _memccpy  __C_FUN(_memccpy)
#define memchr    __C_FUN(memchr)
#define memcmp    __C_FUN(memcmp)
#define memcpy    __C_FUN(memcpy)
#define memmove   __C_FUN(memmove)
#define memset    __C_FUN(memset)
#define strcpy    __C_FUN(strcpy)
#define strncpy   __C_FUN(strncpy)
#define strcat    __C_FUN(strcat)
#define strncat   __C_FUN(strncat)
#define strcmp    __C_FUN(strcmp)
#define strncmp   __C_FUN(strncmp)
#define strdup    __C_FUN(strdup)
#define strndup   __C_FUN(strndup)
#define strcspn   __C_FUN(strcspn)
#define strpbrk   __C_FUN(strpbrk)
#define strlen    __C_FUN(strlen)
#define strchr    __C_FUN(strchr)
#define strrchr   __C_FUN(strrchr)
#define strspn    __C_FUN(strspn)
#define strrpbrk  __C_FUN(strrpbrk)
#define strtok    __C_FUN(strtok)
#define strstr    __C_FUN(strstr)
#define strerror  __C_FUN(strerror)
#define strxfrm  __C_FUN(strxfrm)
#define strcoll  __C_FUN(strcoll)

#if defined(__cplusplus)
extern "C" {
#endif

extern void * _memccpy (void * d, const void * s, char c, size_t n);
extern void * memchr (const void *s, int c, size_t n);
extern int    memcmp (const void *s1, const void *s2, size_t n);
extern void * memcpy (void * d, const void * s, size_t n);
extern void * memmove (void * d, const void * s, size_t n);
extern void * memset (void * d, int c, size_t);

extern char * strcpy (char *, const char *);
extern char * strncpy (char *, const char *, size_t);
extern char * strcat (char *, const char *);
extern char * strncat (char *, const char *, size_t);
extern int    strcmp (const char *, const char *);
extern int    strncmp (const char *, const char *, size_t);
extern char * strdup(const char *);                            /* extension */
extern char * strndup(const char *, size_t);                   /* extension */
extern size_t strcspn (const char *, const char *);
extern char * strpbrk (const char *, const char *);
extern size_t strlen (const char *);
extern char * strchr(const char *, char);
extern char * strrchr (const char *, char);
extern size_t strspn (const char *, const char *);
extern char * strrpbrk (const char *, const char *);
extern char * strtok(char * s, const char * delim);
extern char * strstr(const char * s, const char * find);
extern char * strerror(int errnum);
extern size_t strxfrm(char *s1, const char *s2, size_t n);
extern int strcoll(const char *_S1, const char *_S2);


#if defined(__cplusplus)
}
#endif


#endif /*__STRING_H*/
