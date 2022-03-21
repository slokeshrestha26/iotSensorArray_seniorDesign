/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: CompactClassificationSVM.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 20-Mar-2022 19:57:03
 */

#ifndef COMPACTCLASSIFICATIONSVM_H
#define COMPACTCLASSIFICATIONSVM_H

/* Include Files */
#include "classify_data_internal_types.h"
#include "rtwtypes.h"
#include "omp.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void c_CompactClassificationSVM_Comp(
    double obj_Alpha[6497], double *obj_Bias,
    double obj_SupportVectorsT[129940], double *obj_Scale, double *obj_Order,
    double obj_Mu[20], double obj_Sigma[20],
    d_classreg_learning_coderutils_ *obj_KernelFunction,
    double obj_ClassNames[2], int obj_ClassNamesLength[2],
    c_classreg_learning_coderutils_ *obj_ScoreTransform, double obj_Prior[2],
    bool obj_ClassLogicalIndices[2], double obj_Cost[4]);

double c_CompactClassificationSVM_pred(const double obj_Alpha[6497],
                                       const double obj_SupportVectorsT[129940],
                                       const double obj_Mu[20],
                                       const double obj_Sigma[20],
                                       const double obj_ClassNames[2],
                                       const double obj_Prior[2],
                                       const double Xin[20]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for CompactClassificationSVM.h
 *
 * [EOF]
 */
