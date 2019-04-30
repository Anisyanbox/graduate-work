#pragma once
#ifndef __NO_BUILTIN
#ifdef __llvm__
#pragma clang system_header /* filter.h */
#else
#pragma system_header /* filter.h */
#endif
#endif


#ifndef __FILTER_DEFINED
#define __FILTER_DEFINED


/***************************

  Part 1:  Filters

  **************************/

/*_____________________________________________________________________

  Purpose     :  Filter structure for FIR filter functions.
  Description :  This FIR filter structure contains information 
                 regarding the state of the FIR filter.
                 Use the function fir_init() to populate the
                 FIR filter structure.
  _____________________________________________________________________
*/
typedef struct
{
  float *h;    /*{ filter coefficients            }*/
  float *d;    /*{ start of delay line            }*/
  float *p;    /*{ read/write pointer             }*/
  int k;       /*{ number of coefficients         }*/
  int l;       /*{ interpolation/decimation index }*/
} _fir_state;

#define fir_state _fir_state

#define fir_init(state, coeffs, delay, ncoeffs, index) \
    (state).h = (coeffs);  \
    (state).d = (delay);   \
    (state).p = (delay);   \
    (state).k = (ncoeffs); \
    (state).l = (index)

/*_____________________________________________________________________

  Purpose     :  Filter structure for IIR filter functions.
  Description :  This IIR filter structure contains information 
                 regarding the state of the IIR filter.
                 Use the function iir_init() to populate the 
                 IIR filter structure.
  _____________________________________________________________________
*/
typedef struct
{
  float *c;    /*{ coefficients                   }*/
  float *d;    /*{ start of delay line            }*/
  int k;       /*{ number of bi-quad stages       }*/
} _iir_state;

#define iir_state _iir_state

#define iir_init(state, coeffs, delay, stages) \
    (state).c = (coeffs);  \
    (state).d = (delay);   \
    (state).k = (stages)


#ifdef __cplusplus
extern "C" {
#endif

  #pragma linkage_name __fir
  void fir(const float _x[], float _y[], int _n, _fir_state *_s);
  #pragma linkage_name __fir_decima
  void fir_decima(const float _x[], float _y[], int _n, _fir_state *_s);
  #pragma linkage_name __fir_interp
  void fir_interp(const float _x[], float _y[], int _n, _fir_state *_s);

  #pragma linkage_name __iir
  void iir(const float _x[], float _y[], int _n, _iir_state *_s);

#ifdef __cplusplus
}
#endif


/***************************

  Part 2:  FFT

  **************************/

#include <complex.h>

#ifdef __cplusplus
  extern "C" {
#endif

  #pragma linkage_name __twidfft
  void twidfft(COMPLEX_32 *_w, int _n);

  #pragma linkage_name __cfft
  void cfft(
      const COMPLEX_32 _in[],   /* (i) - pointer to input data      */
      COMPLEX_32 _t[],          /* (o) - pointer to working buffer  */
      COMPLEX_32 _out[],        /* (o) - pointer to output data     */
      const COMPLEX_32 _w[],    /* (i) - pointer to twiddle table   */
      int _wst,                 /* (i) - fft stride                 */
      int _n                    /* (i) - fft resolution             */
  );
  #pragma linkage_name __rfft
  void rfft(
      const float _in[],        /* (i) - pointer to real input data */
      COMPLEX_32 _t[],          /* (o) - pointer to working buffer  */
      COMPLEX_32 _out[],        /* (o) - pointer to output data     */
      const COMPLEX_32 _w[],    /* (i) - pointer to twiddle table   */
      int _wst,                 /* (i) - fft stride                 */
      int _n                    /* (i) - fft resolution             */
  );
  #pragma linkage_name __ifft
  void ifft(
      const COMPLEX_32 _in[],   /* (i) - pointer to input data      */
      COMPLEX_32 _t[],          /* (o) - pointer to working buffer  */
      COMPLEX_32 _out[],        /* (o) - pointer to output data     */
      const COMPLEX_32 _w[],    /* (i) - pointer to twiddle table   */
      int _wst,                 /* (i) - fft stride                 */
      int _n                    /* (i) - fft resolution             */
  );
  #pragma linkage_name __cfft2d
  void cfft2d(
      const COMPLEX_32 *_in,    /* (i) - pointer to input data      */
      COMPLEX_32 *_t,           /* (o) - pointer to working buffer  */
      COMPLEX_32 *_out,         /* (o) - pointer to output data     */
      const COMPLEX_32 _w[],    /* (i) - pointer to twiddle table   */
      int _wst,                 /* (i) - fft stride                 */
      int _n                    /* (i) - fft resolution             */
  );
  #pragma linkage_name __rfft2d
  void rfft2d(
      const float  *_in,        /* (i) - pointer to real input data */
      COMPLEX_32 *_t,           /* (o) - pointer to working buffer  */
      COMPLEX_32 *_out,         /* (o) - pointer to output data     */
      const COMPLEX_32 _w[],    /* (i) - pointer to twiddle table   */
      int _wst,                 /* (i) - fft stride                 */
      int _n                    /* (i) - fft resolution             */
  );
  #pragma linkage_name __ifft2d
  void ifft2d(
      const COMPLEX_32 *_in,    /* (i) - pointer to input data      */
      COMPLEX_32 *_t,           /* (o) - pointer to working buffer  */
      COMPLEX_32 *_out,         /* (o) - pointer to output data     */
      const COMPLEX_32 _w[],    /* (i) - pointer to twiddle table   */
      int _wst,                 /* (i) - fft stride                 */
      int _n                    /* (i) - fft resolution             */
  );

  #pragma linkage_name __twidfftf
  void twidfftf(COMPLEX_32 *_w, int _n);


  #pragma linkage_name __cfftf
  void cfftf(
      const _COMPLEX_32 _in[],  /* (i) - pointer to input data      */
      COMPLEX_32 _out[],        /* (o) - pointer to output data     */
      const COMPLEX_32 _w[],    /* (i) - pointer to twiddle table   */
      int _wst,                 /* (i) - fft stride                 */
      int _n                    /* (i) - fft resolution             */
  );
  #pragma linkage_name __rfftf
  void rfftf(
      const float _in[],        /* (i) - pointer to real input data */
      COMPLEX_32 _out[],        /* (o) - pointer to output data     */
      const COMPLEX_32 _w[],    /* (i) - pointer to twiddle table   */
      int _wst,                 /* (i) - fft stride                 */
      int _n                    /* (i) - fft resolution             */
  );

  #pragma linkage_name __cfft_mag
  void cfft_mag(const COMPLEX_32 _in[], float _out[], int _fftsize);

  #pragma linkage_name __rfft_mag
  void rfft_mag(const COMPLEX_32 _in[], float _out[], int _fftsize);

  #pragma linkage_name __rfftf_mag
  void rfftf_mag(const COMPLEX_32 _in[], float _out[], int _fftsize);


/***************************

  Part 3: Convolution

  **************************/

  #pragma linkage_name __convolve
  void convolve(const float _a[], int _n, const float _b[], 
                      int _m, float _c[]);
  #pragma linkage_name __conv2d
  void conv2d(const float *_a, int _na, int _ma, const float *_b, 
                      int _nb, int _mb, float *_c );


/***************************

  Part 4:  Companding

  **************************/

  #pragma linkage_name __mu_compress
  void mu_compress(const int _a[], int _b[], int _n);
  #pragma linkage_name __mu_expand
  void mu_expand(const int _a[], int _b[], int _n);
  #pragma linkage_name __a_compress
  void a_compress(const int _a[], int _b[], int _n);
  #pragma linkage_name __a_expand
  void a_expand(const int _a[], int _b[], int _n);


#ifdef __cplusplus
  }
#endif


#endif /* __FILTER_DEFINED */

