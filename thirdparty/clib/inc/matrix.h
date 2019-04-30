#pragma once
#ifndef __NO_BUILTIN
#ifdef __llvm__
#pragma clang system_header /* matrix.h */
#else
#pragma system_header /* matrix.h */
#endif
#endif


#ifndef __MATRIX_DEFINED
#define __MATRIX_DEFINED

#include <complex.h>


#ifdef __cplusplus
extern "C" {
#endif

  #pragma linkage_name __matinvf
  float* matinvf(const float _a[], int _n, float _c[] );

  #pragma linkage_name __matsaddf
  void matsaddf(const float _a[], float _b, int _n, int _m, float _c[] );
  #pragma linkage_name __matssubf
  void matssubf(const float _a[], float _b, int _n, int _m, float _c[] );
  #pragma linkage_name __matsmltf
  void matsmltf(const float _a[], float _b, int _n, int _m, float _c[] );

  #pragma linkage_name __matmaddf
  void matmaddf(const float _a[], const float _b[], int _n, int _m, float _c[]);
  #pragma linkage_name __matmsubf
  void matmsubf(const float _a[], const float _b[], int _n, int _m, float _c[]);
  #pragma linkage_name __matmmltf
  void matmmltf(const float _a[], int _n, int _k, const float _b[], 
                      int _m, float _c[]);

  #pragma linkage_name __transpmf
  void transpmf(const float _a[], int _n, int _m, float _c[]);

  #pragma linkage_name __cmatsaddf
  void cmatsaddf(const COMPLEX_32 _a[], COMPLEX_32 _b, 
                       int _n, int _m, COMPLEX_32 _c[] );
  #pragma linkage_name __cmatssubf
  void cmatssubf(const COMPLEX_32 _a[], COMPLEX_32 _b, 
                       int _n, int _m, COMPLEX_32 _c[] );
  #pragma linkage_name __cmatsmltf
  void cmatsmltf(const COMPLEX_32 _a[], COMPLEX_32 _b, 
                       int _n, int _m, COMPLEX_32 _c[] );

  #pragma linkage_name __cmatmaddf
  void cmatmaddf(const COMPLEX_32 _a[], const COMPLEX_32 _b[], 
                       int _n, int _m, COMPLEX_32 _c[] );
  #pragma linkage_name __cmatmsubf
  void cmatmsubf(const COMPLEX_32 _a[], const COMPLEX_32 _b[], 
                       int _n, int _m, COMPLEX_32 _c[]);
  #pragma linkage_name __cmatmmltf
  void cmatmmltf(const COMPLEX_32 _a[], int _n, int _k, const COMPLEX_32 _b[], 
                       int _m, COMPLEX_32 _c[]);

  #pragma linkage_name __matinvd
  long double* matinvd(const long double _a[], int _n, long double _c[] );

  #pragma linkage_name __matsaddd
  void matsaddd(const long double _a[], long double _b, 
                      int _n, int _m, long double _c[] );
  #pragma linkage_name __matssubd
  void matssubd(const long double _a[], long double _b_, 
                      int _n, int _m, long double _c[] );
  #pragma linkage_name __matsmltd
  void matsmltd(const long double _a[], long double _b, 
                      int _n, int _m, long double _c[] ); 

  #pragma linkage_name __matmaddd
  void matmaddd(const long double _a[], const long double _b[], 
                      int _n, int _m, long double _c[] );
  #pragma linkage_name __matmsubd
  void matmsubd(const long double _a[], const long double _b[], 
                      int _n, int _m, long double _c[]);
  #pragma linkage_name __matmmltd
  void matmmltd(const long double _a[], int _n, int _k, const long double _b[], 
                      int _m, long double _c[]);
  #pragma linkage_name __transpmd
  void transpmd(const long double _a[], int _n, int _m, long double _c[]);

  #pragma linkage_name __cmatsaddd
  void cmatsaddd(const COMPLEX_64 _a[], COMPLEX_64 _b, 
                       int _n, int _m, COMPLEX_64 _c[] );
  #pragma linkage_name __cmatssubd
  void cmatssubd(const COMPLEX_64 _a[], COMPLEX_64 _b, 
                       int _n, int _m, COMPLEX_64 _c[] );
  #pragma linkage_name __cmatsmltd
  void cmatsmltd(const COMPLEX_64 _a[], COMPLEX_64 _b, 
                       int _n, int _m, COMPLEX_64 _c[] ); 

  #pragma linkage_name __cmatmaddd
  void cmatmaddd(const COMPLEX_64 _a[], const COMPLEX_64 _b[], 
                       int _n, int _m, COMPLEX_64 _c[] );
  #pragma linkage_name __cmatmsubd
  void cmatmsubd(const COMPLEX_64 _a[], const COMPLEX_64 _b[], 
                       int _n, int _m, COMPLEX_64 _c[]);
  #pragma linkage_name __cmatmmltd
  void cmatmmltd(const COMPLEX_64 _a[], int _n, int _k, const COMPLEX_64 _b[], 
                       int _m, COMPLEX_64 _c[]);


#ifdef __DOUBLES_ARE_FLOATS__ /* 32-bit doubles */
  #pragma linkage_name __matinvf
  double* matinv(const double _a[], int _n, double _c[] );

  #pragma linkage_name __matsaddf
  void matsadd(const double _a[], double _b, int _n, int _m, double _c[] );
  #pragma linkage_name __matssubf
  void matssub(const double _a[], double _b, int _n, int _m, double _c[] );
  #pragma linkage_name __matsmltf
  void matsmlt(const double _a[], double _b, int _n, int _m, double _c[] );

  #pragma linkage_name __matmaddf
  void matmadd(const double _a[], const double _b[], int _n,
                     int _m, double _c[] );
  #pragma linkage_name __matmsubf
  void matmsub(const double _a[], const double _b[],
                     int _n, int _m, double _c[]);
  #pragma linkage_name __matmmltf
  void matmmlt(const double _a[], int _n, int _k, const double _b[],
                     int _m, double _c[]);
  #pragma linkage_name __transpmf
  void transpm(const double _a[], int _n, int _m, double _c[]);

  #pragma linkage_name __cmatsaddf
  void cmatsadd(const COMPLEX _a[], COMPLEX _b, int _n, int _m, COMPLEX _c[] );
  #pragma linkage_name __cmatssubf
  void cmatssub(const COMPLEX _a[], COMPLEX _b, int _n, int _m, COMPLEX _c[] );
  #pragma linkage_name __cmatsmltf
  void cmatsmlt(const COMPLEX _a[], COMPLEX _b, int _n, int _m, COMPLEX _c[] );

  #pragma linkage_name __cmatmaddf
  void cmatmadd(const COMPLEX _a[], const COMPLEX _b[],
                      int _n, int _m, COMPLEX _c[] );
  #pragma linkage_name __cmatmsubf
  void cmatmsub(const COMPLEX _a[], const COMPLEX _b[],
                      int _n, int _m, COMPLEX _c[]);
  #pragma linkage_name __cmatmmltf
  void cmatmmlt(const COMPLEX _a[], int _n, int _k, const COMPLEX _b[],
                      int _m, COMPLEX _c[]);

#else /* 64-bit doubles */
  #pragma linkage_name __matinvd
  double* matinv(const double _a[], int _n, double _c[] );

  #pragma linkage_name __matsaddd
  void matsadd(const double _a[], double _b, int _n, int _m, double _c[] );
  #pragma linkage_name __matssubd
  void matssub(const double _a[], double _b, int _n, int _m, double _c[] );
  #pragma linkage_name __matsmltd
  void matsmlt(const double _a[], double _b, int _n, int _m, double _c[] );

  #pragma linkage_name __matmaddd
  void matmadd(const double _a[], const double _b[], int _n, 
                     int _m, double _c[] );
  #pragma linkage_name __matmsubd
  void matmsub(const double _a[], const double _b[],
                     int _n, int _m, double _c[]);
  #pragma linkage_name __matmmltd
  void matmmlt(const double _a[], int _n, int _k, const double _b[],
                     int _m, double _c[]);
  #pragma linkage_name __transpmd
  void transpm(const double _a[], int _n, int _m, double _c[]);

  #pragma linkage_name __cmatsaddd
  void cmatsadd(const COMPLEX _a[], COMPLEX _b, int _n, int _m, COMPLEX _c[] );
  #pragma linkage_name __cmatssubd
  void cmatssub(const COMPLEX _a[], COMPLEX _b, int _n, int _m, COMPLEX _c[] );
  #pragma linkage_name __cmatsmltd
  void cmatsmlt(const COMPLEX _a[], COMPLEX _b, int _n, int _m, COMPLEX _c[] );

  #pragma linkage_name __cmatmaddd
  void cmatmadd(const COMPLEX _a[], const COMPLEX _b[],
                      int _n, int _m, COMPLEX _c[] );
  #pragma linkage_name __cmatmsubd
  void cmatmsub(const COMPLEX _a[], const COMPLEX _b[],
                      int _n, int _m, COMPLEX _c[]);
  #pragma linkage_name __cmatmmltd
  void cmatmmlt(const COMPLEX _a[], int _n, int _k, const COMPLEX _b[],
                      int _m, COMPLEX _c[]);

#endif /* __DOUBLES_ARE_FLOATS__ */


#ifdef __cplusplus
}
#endif


#endif /* __MATRIX_DEFINED */

