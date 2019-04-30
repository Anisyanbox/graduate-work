
#ifndef __MATH_TS_H
#define __MATH_TS_H

/* double constants and functions (via macros) */
#if __DOUBLES_ARE_FLOATS__

#define favg(x, y)		 ((double)favgf((float)(x), (float)(y)))
#define fclip(x, y)		 ((double)fclipf((float)(x), (float)(y)))
#define fmax(x, y)       ((double)fmaxf((float)(x), (float)(y)))
#define fmin(x, y)       ((double)fminf((float)(x), (float)(y)))
#define sign(x, y)       ((double)copysignf((float)(x), (float)(y)))
#define copysign(x, y)   ((double)copysignf((float)(x), (float)(y)))
#define isinf(x)			 isinff((float)(x))
#define cot(x)			 ((double)cotf((float)(x)))
#define alog(x)			 ((double)alogf((float)(x)))
#define alog10(x)	     ((double)alog10f((float)(x)))


#else /* !__DOUBLES_ARE_FLOATS__ */

#define favg(x, y)		 ((double)favgd((long double)(x), (long double)(y)))
#define fclip(x, y)		 ((double)fclipd((long double)(x), (long double)(y)))
#define fmax(x, y)       ((double)fmaxd((long double)(x), (long double)(y)))
#define fmin(x, y)       ((double)fmind((long double)(x), (long double)(y)))
#define sign(x, y)       ((double)copysignd((long double)(x), (long double)(y)))
#define copysign(x, y)   ((double)copysignd((long double)(x), (long double)(y)))
#define isinf(x)			 isinfd((long double)(x))
#define cot(x)		     ((double)cotd((long double)(x)))
#define alog(x)			 ((double)alogd((long double)(x)))
#define alog10(x)	     ((double)alog10d((long double)(x)))


#endif /* __DOUBLES_ARE_FLOATS__ */

double rsqrt(double);

#if defined(__cplusplus)
extern "C" {
#endif

	/* long double functions */
	extern long double favgd(long double, long double);
	extern long double fclipd(long double, long double);
	extern long double fmaxd(long double, long double);
	extern long double fmind(long double, long double);
	extern long double copysignd(long double, long double);
	
	extern int isinfd(long double);

	extern long double cotd(long double);

	extern long double rsqrtd(long double);

#define alogd(x) expd((x))
#define alog10d(x) expd((x) * 2.302585092994046e+0L)  // * ln(10)

	/* float functions */
	extern float favgf(float, float);
	extern float fclipf(float, float);
#define fmaxf(a, b) __builtin_fmaxf((a), (b))
#define fminf(a, b) __builtin_fminf((a), (b))
	extern float copysignf(float, float);
	
	extern int isinff(float);

	extern float cotf(float);

	extern float rsqrtf(float);

#define alogf(x) expf((x))
#define alog10f(x) expf((x) * 2.302585092994046)  // * ln(10)


#if defined(__cplusplus)
}
#endif


#endif /*__MATH_TS_H*/