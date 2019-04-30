/*********************************************************************/
/*                                                                   */
/*                              math.h                               */
/*                                                                   */
/*          (c) 2014-2016, Angioscan Electronics                     */
/*********************************************************************/

#ifndef __MATH_H
#define __MATH_H


/* long double constants and macros */
#define HUGE_VAL_D    _PLUS_INF
#define _PLUS_INF_D   _PLUS_INF
#define _MINUS_INF_D  _MINUS_INF
#define _NAN_D        _NAN
#define isnand(x)        (((*(((unsigned long*)&(x)) + 1)) & 0x7FF80000UL) == 0x7FF80000UL)

extern const long double _PLUS_INF;
extern const long double _MINUS_INF;
extern const long double _NAN;


/* float constants and macros */
#define HUGE_VAL_F    _PLUS_INF_F
#define _PLUS_INF_F   _PLUS_INF_F
#define _MINUS_INF_F  _MINUS_INF_F
#define _NAN_F        _NAN_F
#define isnanf(x)        (((*((unsigned long*)&(x))) & 0xFFC00000UL) == 0xFFC00000UL)

extern const float    _PLUS_INF_F;
extern const float    _MINUS_INF_F;
extern const float    _NAN_F;


/* double constants and functions (via macros) */
#if __DOUBLES_ARE_FLOATS__

#define HUGE_VAL      (*((const double*)&_PLUS_INF_F))
#define _PLUS_INF     (*((const double*)&_PLUS_INF_F))
#define _MINUS_INF    (*((const double*)&_MINUS_INF_F))
#define _NAN          (*((const double*)&_NAN_F))
#define isnan(x)      isnanf(x)

#define fabs(x)       ((double)fabsf((float)(x)))
#define floor(x)      ((double)floorf((float)(x)))
#define fmod(x,y)     ((double)fmodf((float)(x), (float)(y)))
#define ceil(x)       ((double)ceilf((float)(x)))
#define round(x)      ((double)roundf((float)(x)))
#define modf(x,y)     ((double)modff((float)(x), (float*)(y)))
#define sqrt(x)       ((double)sqrtf((float)(x)))
#define sin(x)        ((double)sinf((float)(x)))
#define cos(x)        ((double)cosf((float)(x)))
#define tan(x)        ((double)tanf((float)(x)))
#define asin(x)       ((double)asinf((float)(x)))
#define acos(x)       ((double)acosf((float)(x)))
#define atan(x)       ((double)atanf((float)(x)))
#define atan2(x,y)    ((double)atan2f((float)(x), (float)(y)))
#define frexp(x,y)    ((double)frexpf((float)(x), y))
#define ldexp(x,y)    ((double)ldexpf((float)(x), y))
#define log(x)        ((double)logf((float)(x)))
#define log10(x)      ((double)log10f((float)(x)))
#define pow(x,y)      ((double)powf((float)(x), (float)(y)))
#define exp(x)        ((double)expf((float)(x)))
#define sinh(x)       ((double)sinhf((float)(x)))
#define cosh(x)       ((double)coshf((float)(x)))
#define tanh(x)       ((double)tanhf((float)(x)))

#else /* !__DOUBLES_ARE_FLOATS__ */

#define HUGE_VAL      (*((const double*)&_PLUS_INF))
#define _PLUS_INF     (*((const double*)&_PLUS_INF))
#define _MINUS_INF    (*((const double*)&_MINUS_INF))
#define _NAN          (*((const double*)&_NAN))
#define isnan(x)      isnand(x)

#define fabs(x)       ((double)fabsd((long double)(x)))
#define floor(x)      ((double)floord((long double)(x)))
#define fmod(x,y)     ((double)fmodd((long double)(x), (long double)(y)))
#define ceil(x)       ((double)ceild((long double)(x)))
#define round(x)      ((double)roundd((long double)(x)))
#define modf(x,y)     ((double)modfd((long double)(x), (long double*)(y)))
#define sqrt(x)       ((double)sqrtd((long double)(x)))
#define sin(x)        ((double)sind((long double)(x)))
#define cos(x)        ((double)cosd((long double)(x)))
#define tan(x)        ((double)tand((long double)(x)))
#define asin(x)       ((double)asind((long double)(x)))
#define acos(x)       ((double)acosd((long double)(x)))
#define atan(x)       ((double)atand((long double)(x)))
#define atan2(x,y)    ((double)atan2d((long double)(x), (long double)(y)))
#define frexp(x,y)    ((double)frexpd((long double)(x), y))
#define ldexp(x,y)    ((double)ldexpd((long double)(x), y))
#define log(x)        ((double)logd((long double)(x)))
#define log10(x)      ((double)log10d((long double)(x)))
#define pow(x,y)      ((double)powd((long double)(x), (long double)(y)))
#define exp(x)        ((double)expd((long double)(x)))
#define sinh(x)       ((double)sinhd((long double)(x)))
#define cosh(x)       ((double)coshd((long double)(x)))
#define tanh(x)       ((double)tanhd((long double)(x)))

#endif /* __DOUBLES_ARE_FLOATS__ */


#if defined(__cplusplus)
extern "C" {
#endif

/* long double functions */
extern long double fabsd (long double);
extern long double floord (long double);
extern long double fmodd (long double x, long double y);
extern long double ceild (long double);
extern long double roundd (long double);
extern long double modfd (long double, long double *);
extern long double sqrtd (long double);
extern long double sind (long double);
extern long double cosd (long double);
extern long double tand (long double);
extern long double asind (long double);
extern long double acosd (long double);
extern long double atand (long double);
extern long double atan2d (long double, long double);
extern long double frexpd (long double, int *);
extern long double ldexpd (long double, int);
extern long double logd (long double);
extern long double log10d (long double);
extern long double powd (long double, long double);
extern long double expd (long double);
extern long double sinhd (long double);
extern long double coshd (long double);
extern long double tanhd (long double);

/* float functions */
extern float fabsf (float);
extern float floorf (float);
extern float fmodf (float x, float y);
extern float ceilf (float);
extern float roundf (float);
extern float modff (float, float *);
extern float sqrtf (float);
extern float sinf (float);
extern float cosf (float);
extern float tanf (float);
extern float asinf (float);
extern float acosf (float);
extern float atanf (float);
extern float atan2f (float, float);
extern float frexpf (float, int *);
extern float ldexpf (float, int);
extern float logf (float);
extern float log10f (float);
extern float powf (float, float);
extern float expf (float);
extern float sinhf (float);
extern float coshf (float);
extern float tanhf (float);

#if defined(__cplusplus)
}
#endif


#define _PI         3.14159265358979
#define _TWO_PI     6.28318530717958
#define _HALF_PI    1.570796326794895
#define _E          2.718281828459045

#ifndef __NO_ANSI_EXTENSIONS__
#include <math_ts.h>
#endif

#endif /*__MATH_H*/
