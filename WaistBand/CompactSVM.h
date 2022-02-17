/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * CompactSVM.h
 *
 * Code generation for function 'CompactSVM'
 *
 */

#ifndef COMPACTSVM_H
#define COMPACTSVM_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "classify_data_types.h"

/* Function Declarations */
extern double CompactSVM_kernelScore(const double obj_Alpha[2498], const double
  obj_SupportVectorsT[37470], const double X[15]);
extern double b_CompactSVM_kernelScore(const double obj_Alpha[2377], const
  double obj_SupportVectorsT[35655], const double X[15]);
extern double c_CompactSVM_kernelScore(const double obj_Alpha[6141], const
  double obj_SupportVectorsT[92115], const double X[15]);

#endif

/* End of code generation (CompactSVM.h) */
