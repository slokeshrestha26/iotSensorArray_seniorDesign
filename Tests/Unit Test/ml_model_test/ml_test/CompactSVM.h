/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: CompactSVM.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Mar-2022 14:42:52
 */

#ifndef COMPACTSVM_H
#define COMPACTSVM_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
double CompactSVM_score(const double obj_Alpha[6497],
                        const double obj_SupportVectorsT[129940],
                        const double obj_Mu[20], const double obj_Sigma[20],
                        const double Xin[20]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for CompactSVM.h
 *
 * [EOF]
 */
