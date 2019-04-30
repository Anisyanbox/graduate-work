/*********************************************************************/
/*                                                                   */
/*                             _math.h                               */
/*                                                                   */
/*          (c) 2014-2016, Angioscan Electronics                     */
/*********************************************************************/

#ifndef ___MATH_H
#define ___MATH_H

#define frndint(x) ((float)(long)(x))

#define DWORDF(f) (*(unsigned long *)&(f))
#define HWORDF(f) (*(((unsigned short *)&(f)) + (sizeof(float)/sizeof(short) - 1)))
#define HBYTEF(f) (*(((unsigned char *)&(f)) + (sizeof(float) - 1)))

#define DWORDD(f) (*(unsigned long *)&(f))
#define HWORDD(f) (*(((unsigned long *)&(f)) + (sizeof(double)/sizeof(long) - 1)))
#define HBYTED(f) (*(((unsigned char *)&(f)) + (sizeof(double) - 1)))


/* double functions (via macros) */
#if __DOUBLES_ARE_FLOATS__

#define __eval_poly(x,y,z)    ((double)__eval_polyf((float)(x), (const float*)(y), z))
#define __trunc(x)            ((double)__truncf((float)(x)))
#define __isfg2p(x,y)         __isfg2pf((float)(x), y)

#else /* !__DOUBLES_ARE_FLOATS__ */

#define __eval_poly(x,y,z)    ((double)__eval_polyd((long double)(x), (const long double*)(y), z))
#define __trunc(x)            ((double)__truncd((long double)(x)))
#define __isfg2p(x,y)         __isfg2pd((long double)(x), y)

#endif /* __DOUBLES_ARE_FLOATS__ */


#if defined(__cplusplus)
extern "C" {
#endif

/* long double functions */
extern long double __eval_polyd (long double, const long double *, int);
extern long double __truncd (long double x);
extern int    __isfg2pd (long double f, int i);

/* float functions */
extern float  __eval_polyf(float, const float *, int);
extern float  __truncf(float x);
extern int    __isfg2pf(float f, int i);

#if defined(__cplusplus)
}
#endif


#endif /*___MATH_H*/
