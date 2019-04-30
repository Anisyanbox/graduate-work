#pragma once


#ifndef __VECTOR_DEFINED
#define __VECTOR_DEFINED


#include <complex.h>


#ifdef __cplusplus
extern "C" {
#endif

  #pragma linkage_name __vecsaddf
  void vecsaddf(const float _a[], float _b, float _c[], int _n);
  #pragma linkage_name __vecssubf
  void vecssubf(const float _a[], float _b, float _c[], int _n);
  #pragma linkage_name __vecsmltf
  void vecsmltf(const float _a[], float _b, float _c[], int _n);

  #pragma linkage_name __vecvaddf
  void vecvaddf(const float _a[], const float _b[], float _c[], int _n);
  #pragma linkage_name __vecvsubf
  void vecvsubf(const float _a[], const float _b[], float _c[], int _n);
  #pragma linkage_name __vecvmltf
  void vecvmltf(const float _a[], const float _b[], float _c[], int _n);

  #pragma linkage_name __vecdotf
  float vecdotf(const float _a[], const float _b[], int _n);


  #pragma linkage_name __vecsaddd
  void vecsaddd(const long double _a[], long double _b, 
                      long double _c[], int _n);
  #pragma linkage_name __vecssubd
  void vecssubd(const long double _a[], long double _b, 
                      long double _c[], int _n);
  #pragma linkage_name __vecsmltd
  void vecsmltd(const long double _a[], long double _b, 
                      long double _c[], int _n);

  #pragma linkage_name __vecvaddd
  void vecvaddd(const long double _a[], const long double _b[], 
                      long double _c[], int _n);
  #pragma linkage_name __vecvsubd
  void vecvsubd(const long double _a[], const long double _b[], 
                      long double _c[], int _n);
  #pragma linkage_name __vecvmltd
  void vecvmltd(const long double _a[], const long double _b[], 
                      long double _c[], int _n);

  #pragma linkage_name __vecdotd
  long double vecdotd(const long double _a[], const long double _b[], int _n);


  #pragma linkage_name __cvecsaddf
  void cvecsaddf(const COMPLEX_32 _a[], COMPLEX_32 _b, COMPLEX_32 _c[], int _n);
  #pragma linkage_name __cvecssubf
  void cvecssubf(const COMPLEX_32 _a[], COMPLEX_32 _b, COMPLEX_32 _c[], int _n);
  #pragma linkage_name __cvecsmltf
  void cvecsmltf(const COMPLEX_32 _a[], COMPLEX_32 _b, COMPLEX_32 _c[], int _n);

  #pragma linkage_name __cvecvaddf
  void cvecvaddf(const COMPLEX_32 _a[], const COMPLEX_32 _b[], 
                       COMPLEX_32 _c[], int _n);
  #pragma linkage_name __cvecvsubf
  void cvecvsubf(const COMPLEX_32 _a[], const COMPLEX_32 _b[], 
                       COMPLEX_32 _c[], int _n);
  #pragma linkage_name __cvecvmltf
  void cvecvmltf(const COMPLEX_32 _a[], const COMPLEX_32 _b[], 
                       COMPLEX_32 _c[], int _n);

  #pragma linkage_name __cvecdotf
  COMPLEX_32 cvecdotf(const COMPLEX_32 _a[], const COMPLEX_32 _b[], int _n);


  #pragma linkage_name __cvecsaddd
  void cvecsaddd(const COMPLEX_64 _a[], COMPLEX_64 _b, COMPLEX_64 _c[], int _n);
  #pragma linkage_name __cvecssubd
  void cvecssubd(const COMPLEX_64 _a[], COMPLEX_64 _b, COMPLEX_64 _c[], int _n);
  #pragma linkage_name __cvecsmltd
  void cvecsmltd(const COMPLEX_64 _a[], COMPLEX_64 _b, COMPLEX_64 _c[], int _n);

  #pragma linkage_name __cvecvaddd
  void cvecvaddd(const COMPLEX_64 _a[], const COMPLEX_64 _b[], 
                       COMPLEX_64 _c[], int _n);
  #pragma linkage_name __cvecvsubd
  void cvecvsubd(const COMPLEX_64 _a[], const COMPLEX_64 _b[], 
                       COMPLEX_64 _c[], int _n);
  #pragma linkage_name __cvecvmltd
  void cvecvmltd(const COMPLEX_64 _a[], const COMPLEX_64 _b[], 
                       COMPLEX_64 _c[], int _n);

  #pragma linkage_name __cvecdotd
  COMPLEX_64 cvecdotd(const COMPLEX_64 _a[], const COMPLEX_64 _b[], int _n);


#ifdef __DOUBLES_ARE_FLOATS__ /* 32-bit doubles */
  #pragma linkage_name __vecsaddf
  void vecsadd(const double _a[], double _b, double _c[], int _n);
  #pragma linkage_name __vecssubf
  void vecssub(const double _a[], double _b, double _c[], int _n);
  #pragma linkage_name __vecsmltf
  void vecsmlt(const double _a[], double _b, double _c[], int _n);

  #pragma linkage_name __vecvaddf
  void vecvadd(const double _a[], const double _b[], double _c[], int _n);
  #pragma linkage_name __vecvsubf
  void vecvsub(const double _a[], const double _b[], double _c[], int _n);
  #pragma linkage_name __vecvmltf
  void vecvmlt(const double _a[], const double _b[], double _c[], int _n);

  #pragma linkage_name __vecdotf
  double vecdot(const double _a[], const double _b[], int _n);


  #pragma linkage_name __cvecsaddf
  void cvecsadd(const COMPLEX _a[], COMPLEX _b, COMPLEX _c[], int _n);
  #pragma linkage_name __cvecssubf
  void cvecssub(const COMPLEX _a[], COMPLEX _b, COMPLEX _c[], int _n);
  #pragma linkage_name __cvecsmltf
  void cvecsmlt(const COMPLEX _a[], COMPLEX _b, COMPLEX _c[], int _n);

  #pragma linkage_name __cvecvaddf
  void cvecvadd(const COMPLEX _a[], const COMPLEX _b[], COMPLEX _c[], int _n);
  #pragma linkage_name __cvecvsubf
  void cvecvsub(const COMPLEX _a[], const COMPLEX _b[], COMPLEX _c[], int _n);
  #pragma linkage_name __cvecvmltf
  void cvecvmlt(const COMPLEX _a[], const COMPLEX _b[], COMPLEX _c[], int _n);

  #pragma linkage_name __cvecdotf
  COMPLEX cvecdot(const COMPLEX _a[], const COMPLEX _b[], int _n);

#else /* 64-bit doubles */
  #pragma linkage_name __vecsaddd
  void vecsadd(const double _a[], double _b, double _c[], int _n);
  #pragma linkage_name __vecssubd
  void vecssub(const double _a[], double _b, double _c[], int _n);
  #pragma linkage_name __vecsmltd
  void vecsmlt(const double _a[], double _b, double _c[], int _n);

  #pragma linkage_name __vecvaddd
  void vecvadd(const double _a[], const double _b[], double _c[], int _n);
  #pragma linkage_name __vecvsubd
  void vecvsub(const double _a[], const double _b[], double _c[], int _n);
  #pragma linkage_name __vecvmltd
  void vecvmlt(const double _a[], const double _b[], double _c[], int _n);

  #pragma linkage_name __vecdotd
  double vecdot(const double _a[], const double _b[], int _n);


  #pragma linkage_name __cvecsaddd
  void cvecsadd(const COMPLEX _a[], COMPLEX _b, COMPLEX _c[], int _n);
  #pragma linkage_name __cvecssubd
  void cvecssub(const COMPLEX _a[], COMPLEX _b, COMPLEX _c[], int _n);
  #pragma linkage_name __cvecsmltd
  void cvecsmlt(const COMPLEX _a[], COMPLEX _b, COMPLEX _c[], int _n);

  #pragma linkage_name __cvecvaddd
  void cvecvadd(const COMPLEX _a[], const COMPLEX _b[], COMPLEX _c[], int _n);
  #pragma linkage_name __cvecvsubd
  void cvecvsub(const COMPLEX _a[], const COMPLEX _b[], COMPLEX _c[], int _n);
  #pragma linkage_name __cvecvmltd
  void cvecvmlt(const COMPLEX _a[], const COMPLEX _b[], COMPLEX _c[], int _n);

  #pragma linkage_name __cvecdotd
  COMPLEX cvecdot(const COMPLEX _a[], const COMPLEX _b[], int _n);

#endif /* __DOUBLES_ARE_FLOATS__ */


#ifdef __cplusplus
}
#endif


#endif /* __VECTOR_DEFINED */

