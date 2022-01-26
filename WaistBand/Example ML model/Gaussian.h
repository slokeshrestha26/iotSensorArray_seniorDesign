/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Gaussian.h
 *
 * Code generation for function 'Gaussian'
 *
 */

#ifndef GAUSSIAN_H
#define GAUSSIAN_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "classify_data_types.h"

/* Function Declarations */
extern void Gaussian(const double svT[37470], const double svInnerProduct[2498],
                     const double x[15], double kernelProduct[2498]);
extern void b_Gaussian(const double svT[35655], const double svInnerProduct[2377],
  const double x[15], double kernelProduct[2377]);
extern void c_Gaussian(const double svT[92115], const double svInnerProduct[6141],
  const double x[15], double kernelProduct[6141]);

#endif

/* End of code generation (Gaussian.h) */
