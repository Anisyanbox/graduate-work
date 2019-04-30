/************************************************************************
 *
 * complex.h
 *
 ************************************************************************/

/* Analog DSP extension - 32-bit / 64-bit complex number support */


#pragma once
#ifndef __NO_BUILTIN
#ifdef __llvm__
#pragma clang system_header /* complex.h */
#else
#pragma system_header /* complex.h */
#endif
#endif

#ifdef __llvm__
#define __inline__def	__inline	__attribute__((always_inline))
#else 
#define __inline__def	__inline
#endif


#ifndef __COMPLEX_DEFINED
#define __COMPLEX_DEFINED


#define CREAL(x) ((x).re)
#define CIMAG(x) ((x).im)

#define _COMPLEX_32  _complex_float
#define  COMPLEX_32  _complex_float
#define _COMPLEX_64  _complex_long_double 
#define  COMPLEX_64  _complex_long_double

#ifdef __DOUBLES_ARE_FLOATS__ /* 32-bit doubles */
#define  COMPLEX            _complex_float
#define  complex_double     _complex_float

#else  /* 64-bit doubles */
#define  COMPLEX            _complex_long_double
#define  complex_double     _complex_long_double

#endif

#define complex_float       _complex_float
#define complex_long_double _complex_long_double


typedef struct 
{
    float re;       /*{ Real      }*/
    float im;       /*{ Imaginary }*/
} _complex_float;

typedef struct
{
    long double re;     /*{ Real      }*/
    long double im;     /*{ Imaginary }*/
} _complex_long_double;



#ifdef __cplusplus
extern "C" {
#endif

#pragma linkage_name __cabsf
  float       cabsf(COMPLEX_32 _a);
#pragma linkage_name __normf
  COMPLEX_32  normf(COMPLEX_32 _a);

  //written in asm
  COMPLEX_32  conjf(COMPLEX_32 _a);
//  #pragma always_inline
//  __inline__def COMPLEX_32  conjf(COMPLEX_32 _a)
//  {
//    COMPLEX_32 _c;
//
//    _c.re =  _a.re;
//    _c.im = -_a.im;
//
//    return _c;
//  }

  #pragma always_inline
  __inline__def COMPLEX_32  caddf(COMPLEX_32 _a, COMPLEX_32 _b)
  {
    COMPLEX_32 _c;

    _c.re = _a.re + _b.re;
    _c.im = _a.im + _b.im;

    return _c;
  }

  #pragma always_inline
  __inline__def COMPLEX_32  csubf(COMPLEX_32 _a, COMPLEX_32 _b)
  {
    COMPLEX_32 _c;

    _c.re = _a.re - _b.re;
    _c.im = _a.im - _b.im;

    return _c;
  }

  #pragma always_inline
  __inline__def COMPLEX_32  cmltf(COMPLEX_32 _a, COMPLEX_32 _b)
  {
    COMPLEX_32 _c;

    _c.re = (_a.re * _b.re) - (_a.im * _b.im);
    _c.im = (_a.re * _b.im) + (_a.im * _b.re);

    return _c;
  }

#pragma linkage_name __cdivf
  COMPLEX_32  cdivf(COMPLEX_32 _a, COMPLEX_32 _b);
#pragma linkage_name __cexpf
  COMPLEX_32  cexpf(float _a);
#pragma linkage_name __argf
  float       argf(COMPLEX_32 _a);
#pragma linkage_name _cartesianf
  float       cartesianf(COMPLEX_32 _a, float* _phase);
#pragma linkage_name __polarf
  COMPLEX_32  polarf(float _mag, float _phase);
#pragma linkage_name __cabsd
  long double  cabsd(COMPLEX_64 _a);
#pragma linkage_name _normd
  COMPLEX_64   normd(COMPLEX_64 _a);

  #pragma always_inline
  /*inline*/__inline__def COMPLEX_64  conjd(COMPLEX_64 _a)
  {
    COMPLEX_64 _c;

    _c.re =  _a.re;
    _c.im = -_a.im;

    return _c;
  }  
#pragma linkage_name _caddd
  COMPLEX_64   caddd(COMPLEX_64 _a, COMPLEX_64 _b);
#pragma linkage_name _csubd
  COMPLEX_64   csubd(COMPLEX_64 _a, COMPLEX_64 _b);
#pragma linkage_name _cmltd
  COMPLEX_64   cmltd(COMPLEX_64 _a, COMPLEX_64 _b);
#pragma linkage_name _cdivd
  COMPLEX_64   cdivd(COMPLEX_64 _a, COMPLEX_64 _b);

#pragma linkage_name _cexpd
  COMPLEX_64   cexpd(long double _a);

#pragma linkage_name _argd
  long double  argd(COMPLEX_64 _a);

#pragma linkage_name _cartesiand
  long double  cartesiand(COMPLEX_64 _a, long double* _phase);

#pragma linkage_name _polard
  COMPLEX_64   polard(long double _mag, long double _phase);



  #pragma always_inline
  __inline__def COMPLEX  conj(COMPLEX _a)
  {
    COMPLEX _c;

    _c.re =  _a.re;
    _c.im = -_a.im;

    return _c;
  }


#ifdef __DOUBLES_ARE_FLOATS__ /* 32-bit doubles */

#pragma linkage_name __cabsf
  double   cabs(COMPLEX _a);
#pragma linkage_name __normf
  COMPLEX  norm(COMPLEX _a);

  #pragma always_inline
  __inline__def COMPLEX  cadd(COMPLEX _a, COMPLEX _b)
  {
    COMPLEX _c;

    _c.re = _a.re + _b.re;
    _c.im = _a.im + _b.im;

    return _c;
  }

  #pragma always_inline
  __inline__def COMPLEX  csub(COMPLEX _a, COMPLEX _b)
  {
    COMPLEX _c;

    _c.re = _a.re - _b.re;
    _c.im = _a.im - _b.im;

    return _c;
  }

  #pragma always_inline
  __inline__def COMPLEX  cmlt(COMPLEX _a, COMPLEX _b)
  {
    COMPLEX _c;

    _c.re = (_a.re * _b.re) - (_a.im * _b.im);
    _c.im = (_a.re * _b.im) + (_a.im * _b.re);

    return _c;
  }

#pragma linkage_name __cdivf
  COMPLEX  cdiv(COMPLEX _a, COMPLEX _b);

#pragma linkage_name __cexpf
  COMPLEX  cexp(double _a);

#pragma linkage_name __argf
  double   arg(COMPLEX _a);
#pragma linkage_name __cartesianf
  double   cartesian(COMPLEX _a, double* _phase);
#pragma linkage_name__polarf
  COMPLEX  polar(double _mag, double _phase);

#else /* 64-bit doubles */

#pragma linkage_name __cabsd
  double   cabs(COMPLEX _a);
#pragma linkage_name __normd
  COMPLEX  norm(COMPLEX _a);

#pragma linkage_name __caddd
  COMPLEX  cadd(COMPLEX _a, COMPLEX _b);
#pragma linkage_name __csubd
  COMPLEX  csub(COMPLEX _a, COMPLEX _b);
#pragma linkage_name __cmltd
  COMPLEX  cmlt(COMPLEX _a, COMPLEX _b);
#pragma linkage_name __cdivd
  COMPLEX  cdiv(COMPLEX _a, COMPLEX _b);

#pragma linkage_name __cexpd
  COMPLEX  cexp(double _a);

#pragma linkage_name __argd
  double   arg(COMPLEX _a);
#pragma linkage_name __cartesiand
  double   cartesian(COMPLEX _a, double* _phase);
#pragma linkage_name __polard
  COMPLEX  polar(double _mag, double _phase);

#endif /* __DOUBLES_ARE_FLOATS__ */


#ifdef __cplusplus
}
#endif


#endif /* __COMPLEX_DEFINED */



