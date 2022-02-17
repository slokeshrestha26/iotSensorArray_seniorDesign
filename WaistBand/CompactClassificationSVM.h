/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * CompactClassificationSVM.h
 *
 * Code generation for function 'CompactClassificationSVM'
 *
 */

#ifndef COMPACTCLASSIFICATIONSVM_H
#define COMPACTCLASSIFICATIONSVM_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "classify_data_types.h"

/* Function Declarations */
extern void c_CompactClassificationSVM_Comp(double obj_Alpha[2498], double
  *obj_Bias, double obj_SupportVectorsT[37470], double *obj_Scale, double
  *obj_Order, double obj_Mu[15], double obj_Sigma[15],
  d_classreg_learning_coderutils_ *obj_KernelFunction, char obj_ClassNames[2],
  int obj_ClassNamesLength[2], c_classreg_learning_coderutils_
  *obj_ScoreTransform, double obj_Prior[2], boolean_T obj_ClassLogicalIndices[2],
  double obj_Cost[4]);
extern char c_CompactClassificationSVM_pred(const double obj_Alpha[2498], const
  double obj_SupportVectorsT[37470], const double obj_Mu[15], const double
  obj_Sigma[15], const char obj_ClassNames[2], const double obj_Prior[2], const
  double X[15]);
extern void d_CompactClassificationSVM_Comp(double obj_Alpha[2377], double
  *obj_Bias, double obj_SupportVectorsT[35655], double *obj_Scale, double
  *obj_Order, double obj_Mu[15], double obj_Sigma[15],
  d_classreg_learning_coderutils_ *obj_KernelFunction, char obj_ClassNames[2],
  int obj_ClassNamesLength[2], c_classreg_learning_coderutils_
  *obj_ScoreTransform, double obj_Prior[2], boolean_T obj_ClassLogicalIndices[2],
  double obj_Cost[4]);
extern char d_CompactClassificationSVM_pred(const double obj_Alpha[2377], const
  double obj_SupportVectorsT[35655], const double obj_Mu[15], const double
  obj_Sigma[15], const char obj_ClassNames[2], const double obj_Prior[2], const
  double X[15]);
extern void e_CompactClassificationSVM_Comp(double obj_Alpha[6141], double
  *obj_Bias, double obj_SupportVectorsT[92115], double *obj_Scale, double
  *obj_Order, double obj_Mu[15], double obj_Sigma[15],
  d_classreg_learning_coderutils_ *obj_KernelFunction, char obj_ClassNames[2],
  int obj_ClassNamesLength[2], c_classreg_learning_coderutils_
  *obj_ScoreTransform, double obj_Prior[2], boolean_T obj_ClassLogicalIndices[2],
  double obj_Cost[4]);
extern char e_CompactClassificationSVM_pred(const double obj_Alpha[6141], const
  double obj_SupportVectorsT[92115], const double obj_Mu[15], const double
  obj_Sigma[15], const char obj_ClassNames[2], const double obj_Prior[2], const
  double X[15]);

#endif

/* End of code generation (CompactClassificationSVM.h) */
