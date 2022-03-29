/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: Gaussian.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Mar-2022 13:32:22
 */

#ifndef GAUSSIAN_H
#define GAUSSIAN_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void Gaussian(const double svT[129940], const double svInnerProduct[6497],
              const double x[20], double kernelProduct[6497]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for Gaussian.h
 *
 * [EOF]
 */
