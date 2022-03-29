/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: Gaussian.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Mar-2022 13:32:22
 */

/* Include Files */
#include "Gaussian.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const double svT[129940]
 *                const double svInnerProduct[6497]
 *                const double x[20]
 *                double kernelProduct[6497]
 * Return Type  : void
 */
void Gaussian(const double svT[129940], const double svInnerProduct[6497],
              const double x[20], double kernelProduct[6497])
{
  double y[6497];
  double b_x;
  double d;
  int i;
  int k;
  for (k = 0; k < 6497; k++) {
    d = 0.0;
    for (i = 0; i < 20; i++) {
      d += -2.0 * x[i] * svT[i + 20 * k];
    }
    y[k] = d;
  }
  b_x = 0.0;
  for (k = 0; k < 20; k++) {
    d = x[k];
    b_x += d * d;
  }
  for (k = 0; k < 6497; k++) {
    kernelProduct[k] = exp(-((y[k] + b_x) + svInnerProduct[k]));
  }
}

/*
 * File trailer for Gaussian.c
 *
 * [EOF]
 */
