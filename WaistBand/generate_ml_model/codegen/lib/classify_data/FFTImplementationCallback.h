/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: FFTImplementationCallback.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Mar-2022 14:42:52
 */

#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void c_FFTImplementationCallback_doH(const double x[23400], int xoffInit,
                                     creal_T y[7800], const creal_T wwc[7799],
                                     const double costab[8193],
                                     const double sintab[8193],
                                     const double costabinv[8193],
                                     const double sintabinv[8193]);

void c_FFTImplementationCallback_gen(double costab[8193], double sintab[8193],
                                     double sintabinv[8193]);

void d_FFTImplementationCallback_doH(const double x[300], creal_T y[300],
                                     const creal_T wwc[299],
                                     const double costabinv[513],
                                     const double sintabinv[513]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for FFTImplementationCallback.h
 *
 * [EOF]
 */
