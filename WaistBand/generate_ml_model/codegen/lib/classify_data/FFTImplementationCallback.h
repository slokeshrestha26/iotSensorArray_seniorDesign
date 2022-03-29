/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: FFTImplementationCallback.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Mar-2022 13:32:22
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

void d_FFTImplementationCallback_doH(const double x[3800], creal_T y[3800],
                                     const creal_T wwc[3799],
                                     const double costabinv[4097],
                                     const double sintabinv[4097]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for FFTImplementationCallback.h
 *
 * [EOF]
 */
