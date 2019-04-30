/************************************************************************
 *
 * window.h
 *
 ************************************************************************/

/* Analog DSP extension - Window generators */

#pragma once
#ifndef __NO_BUILTIN
#pragma system_header /* window.h */
#endif

#ifndef __WINDOW_INCLUDED
#define __WINDOW_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#pragma linkage_name __gen_bartlett
void gen_bartlett(float _w[], int _a, int _n);

#pragma linkage_name __gen_blackman
void gen_blackman(float _w[], int _a, int _n);

#pragma linkage_name __gen_gaussian
void gen_gaussian(float _w[], float _alpha, int _a, int _n);

#pragma linkage_name __gen_hamming
void gen_hamming(float _w[], int _a, int _n);

#pragma linkage_name __gen_hanning
void gen_hanning(float _w[], int _a, int _n);

#pragma linkage_name __gen_harris
void gen_harris(float _w[], int _a, int _n);

#pragma linkage_name __gen_kaiser
void gen_kaiser(float _w[], float _beta, int _a, int _n);

#pragma linkage_name __gen_rectangular
void gen_rectangular(float _w[], int _a, int _n);

#pragma linkage_name __gen_triangle
void gen_triangle(float _w[], int _a, int _n);

#pragma linkage_name __gen_hanning
void gen_vonhann(float _w[], int _a, int _n);

#ifdef __cplusplus
}
#endif

#endif /* __WINDOW_INCLUDED */

