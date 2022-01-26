/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * var.c
 *
 * Code generation for function 'var'
 *
 */

/* Include files */
#include "var.h"
#include "classify_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void var(const double x[28800], double y[3])
{
  int p;
  short tunableEnvironment_idx_0;
  int k;
  double xbar;
  double xv[9600];
  double yv;
  double t;
  for (p = 0; p < 3; p++) {
    tunableEnvironment_idx_0 = (short)(p * 9600 + 1);
    for (k = 0; k < 9600; k++) {
      xv[k] = x[(tunableEnvironment_idx_0 + k) - 1];
    }

    xbar = xv[0];
    for (k = 0; k < 9599; k++) {
      xbar += xv[k + 1];
    }

    xbar /= 9600.0;
    yv = 0.0;
    for (k = 0; k < 9600; k++) {
      t = xv[k] - xbar;
      yv += t * t;
    }

    y[p] = yv / 9599.0;
  }
}

/* End of code generation (var.c) */
