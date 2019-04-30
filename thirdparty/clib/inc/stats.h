#pragma once



#ifndef __STATS_DEFINED
#define __STATS_DEFINED


#ifdef __cplusplus
extern "C" {
#endif

  #pragma linkage_name __autocohf
  void  autocohf  (const float *_a, int _n, int _m, float *_c);
  #pragma linkage_name __autocorrf
  void  autocorrf (const float *_a, int _n, int _m, float *_c);
  #pragma linkage_name __crosscohf
  void  crosscohf (const float *_a, const float *_b, int _n, int _m, float *_c);
  #pragma linkage_name __crosscorrf
  void  crosscorrf(const float *_a, const float *_b, int _n, int _m, float *_c);

  #pragma linkage_name __histogramf
  void  histogramf(const float *_a, int _n, float _max, float _min, 
                         int *_c, int _m);

  #pragma linkage_name __meanf
  float meanf(const float *_a, int _n);
  #pragma linkage_name __rmsf
  float rmsf (const float *_a, int _n);
  #pragma linkage_name __varf
  float varf (const float *_a, int _n);
  
  #pragma linkage_name __zero_crossf
  int   zero_crossf(const float *_a, int _n);


  #pragma linkage_name __autocohd
  void  autocohd (const long double *_a, int _n, int _m, long double *_c);
  #pragma linkage_name __autocorrd
  void  autocorrd (const long double *_a, int _n, int _m, long double *_c);
  #pragma linkage_name __crosscohd
  void  crosscohd (const long double *_a, const long double *_b, 
                         int _n, int _m, long double *_c);
  #pragma linkage_name __crosscorrd
  void  crosscorrd(const long double *_a, const long double *_b, 
                         int _n, int _m, long double *_c);

  #pragma linkage_name __histogramd
  void  histogramd(const long double *_a, int _n, long double _max, 
                         long double _min, int *_c, int _m);

  #pragma linkage_name __meand
  long double meand(const long double *_a, int _n);
  #pragma linkage_name __rmsd
  long double rmsd (const long double *_a, int _n);
  #pragma linkage_name __vard
  long double vard (const long double *_a, int _n);

  #pragma linkage_name __zero_crossd
  int   zero_crossd(const long double *_a, int _n);


#ifdef __DOUBLES_ARE_FLOATS__ /* 32-bit doubles */                             
  #pragma linkage_name __autocohf
  void  autocoh  (const double *_a, int _n, int _m, double *_c);
  #pragma linkage_name __autocorrf
  void  autocorr (const double *_a, int _n, int _m, double *_c);
  #pragma linkage_name __crosscohf
  void  crosscoh (const double *_a, const double *_b,
                         int _n, int _m, double *_c);
  #pragma linkage_name __crosscorrf
  void  crosscorr(const double *_a, const double *_b,
                         int _n, int _m, double *_c);

  #pragma linkage_name __histogramf
  void  histogram(const double *_a, int _n, double _max,
                         double _min, int *_c, int _m);

  #pragma linkage_name __meanf
  double mean(const double *_a, int _n);
  #pragma linkage_name __rmsf
  double rms (const double *_a, int _n);
  #pragma linkage_name __varf
  double var (const double *_a, int _n);

  #pragma linkage_name __zero_crossf
  int   zero_cross(const double *_a, int _n);

#else /* 64-bit doubles */
  #pragma linkage_name __autocohd
  void  autocoh  (const double *_a, int _n, int _m, double *_c);
  #pragma linkage_name __autocorrd
  void  autocorr (const double *_a, int _n, int _m, double *_c);
  #pragma linkage_name __crosscohd
  void  crosscoh (const double *_a, const double *_b, 
                         int _n, int _m, double *_c);
  #pragma linkage_name __crosscorrd
  void  crosscorr(const double *_a, const double *_b,
                         int _n, int _m, double *_c);

  #pragma linkage_name __histogramd
  void  histogram(const double *_a, int _n, double _max,
                         double _min, int *_c, int _m);

  #pragma linkage_name __meand
  double mean(const double *_a, int _n);
  #pragma linkage_name __rmsd
  double rms (const double *_a, int _n);
  #pragma linkage_name __vard
  double var (const double *_a, int _n);

  #pragma linkage_name __zero_crossd
  int   zero_cross(const double *_a, int _n);

#endif /* __DOUBLES_ARE_FLOATS__ */


#ifdef __cplusplus
}
#endif


#endif /* __STATS_DEFINED */

