/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * fft1.h
 *
 * Code generation for function 'fft1'
 *
 */

#ifndef FFT1_H
#define FFT1_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "classify_data_types.h"

/* Function Declarations */
extern void b_bluestein(const creal_T x[28800], const double costab[16385],
  const double sintab[16385], const double costabinv[16385], const double
  sintabinv[16385], const creal_T wwc[19199], creal_T y[28800]);
extern void bluestein(const double x[28800], const double costab[16385], const
                      double sintab[16385], const double costabinv[16385], const
                      double sintabinv[16385], const creal_T wwc[19199], creal_T
                      y[28800]);
extern void generate_twiddle_tables(double costab[16385], double sintab[16385],
  double sintabinv[16385]);

#endif

/* End of code generation (fft1.h) */
