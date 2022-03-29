/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Gaussian.c
 *
 * Code generation for function 'Gaussian'
 *
 */

/* Include files */
#include "Gaussian.h"
#include "classify_data.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void Gaussian(const double svT[37470], const double svInnerProduct[2498], const
              double x[15], double kernelProduct[2498])
{
  int k;
  double b_x;
  int i;
  double y[2498];
  for (k = 0; k < 2498; k++) {
    b_x = 0.0;
    for (i = 0; i < 15; i++) {
      b_x += -2.0 * x[i] * svT[i + 15 * k];
    }

    y[k] = b_x;
  }

  b_x = 0.0;
  for (k = 0; k < 15; k++) {
    b_x += x[k] * x[k];
  }

  for (k = 0; k < 2498; k++) {
    kernelProduct[k] = exp(-((y[k] + b_x) + svInnerProduct[k]));
  }
}

void b_Gaussian(const double svT[35655], const double svInnerProduct[2377],
                const double x[15], double kernelProduct[2377])
{
  int k;
  double b_x;
  int i;
  double y[2377];
  for (k = 0; k < 2377; k++) {
    b_x = 0.0;
    for (i = 0; i < 15; i++) {
      b_x += -2.0 * x[i] * svT[i + 15 * k];
    }

    y[k] = b_x;
  }

  b_x = 0.0;
  for (k = 0; k < 15; k++) {
    b_x += x[k] * x[k];
  }

  for (k = 0; k < 2377; k++) {
    kernelProduct[k] = exp(-((y[k] + b_x) + svInnerProduct[k]));
  }
}

void c_Gaussian(const double svT[92115], const double svInnerProduct[6141],
                const double x[15], double kernelProduct[6141])
{
  int k;
  double b_x;
  int i;
  double y[6141];
  for (k = 0; k < 6141; k++) {
    b_x = 0.0;
    for (i = 0; i < 15; i++) {
      b_x += -2.0 * x[i] * svT[i + 15 * k];
    }

    y[k] = b_x;
  }

  b_x = 0.0;
  for (k = 0; k < 15; k++) {
    b_x += x[k] * x[k];
  }

  for (k = 0; k < 6141; k++) {
    kernelProduct[k] = exp(-((y[k] + b_x) + svInnerProduct[k]));
  }
}

/* End of code generation (Gaussian.c) */
