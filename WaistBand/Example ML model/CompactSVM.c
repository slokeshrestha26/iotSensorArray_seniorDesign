/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * CompactSVM.c
 *
 * Code generation for function 'CompactSVM'
 *
 */

/* Include files */
#include "CompactSVM.h"
#include "Gaussian.h"
#include "classify_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
double CompactSVM_kernelScore(const double obj_Alpha[2498], const double
  obj_SupportVectorsT[37470], const double X[15])
{
  int i2;
  static double svT[37470];
  int ic;
  int i;
  int i1;
  double svInnerProduct[2498];
  double b_X[15];
  double dv[2498];
  double c;
  int iy;
  int k;
  for (i2 = 0; i2 < 37470; i2++) {
    svT[i2] = obj_SupportVectorsT[i2] / 0.97;
  }

  i2 = 1;
  ic = -1;
  for (i = 0; i < 2498; i++) {
    i1 = i2 - 1;
    ic++;
    i2 += 15;
    iy = i1;
    c = 0.0;
    for (k = 0; k < 15; k++) {
      c += svT[i1] * svT[iy];
      i1++;
      iy++;
    }

    svInnerProduct[ic] = c;
  }

  for (i2 = 0; i2 < 15; i2++) {
    b_X[i2] = X[i2] / 0.97;
  }

  Gaussian(svT, svInnerProduct, b_X, dv);
  c = 0.0;
  for (i2 = 0; i2 < 2498; i2++) {
    c += dv[i2] * obj_Alpha[i2];
  }

  return c + 0.390394811702645;
}

double b_CompactSVM_kernelScore(const double obj_Alpha[2377], const double
  obj_SupportVectorsT[35655], const double X[15])
{
  int i2;
  static double svT[35655];
  int ic;
  int i;
  int i1;
  double svInnerProduct[2377];
  double b_X[15];
  double dv[2377];
  double c;
  int iy;
  int k;
  for (i2 = 0; i2 < 35655; i2++) {
    svT[i2] = obj_SupportVectorsT[i2] / 0.97;
  }

  i2 = 1;
  ic = -1;
  for (i = 0; i < 2377; i++) {
    i1 = i2 - 1;
    ic++;
    i2 += 15;
    iy = i1;
    c = 0.0;
    for (k = 0; k < 15; k++) {
      c += svT[i1] * svT[iy];
      i1++;
      iy++;
    }

    svInnerProduct[ic] = c;
  }

  for (i2 = 0; i2 < 15; i2++) {
    b_X[i2] = X[i2] / 0.97;
  }

  b_Gaussian(svT, svInnerProduct, b_X, dv);
  c = 0.0;
  for (i2 = 0; i2 < 2377; i2++) {
    c += dv[i2] * obj_Alpha[i2];
  }

  return c + 0.25485523866027954;
}

double c_CompactSVM_kernelScore(const double obj_Alpha[6141], const double
  obj_SupportVectorsT[92115], const double X[15])
{
  int i2;
  static double svT[92115];
  int ic;
  int i;
  int i1;
  double svInnerProduct[6141];
  double b_X[15];
  double dv[6141];
  double c;
  int iy;
  int k;
  for (i2 = 0; i2 < 92115; i2++) {
    svT[i2] = obj_SupportVectorsT[i2] / 0.97;
  }

  i2 = 1;
  ic = -1;
  for (i = 0; i < 6141; i++) {
    i1 = i2 - 1;
    ic++;
    i2 += 15;
    iy = i1;
    c = 0.0;
    for (k = 0; k < 15; k++) {
      c += svT[i1] * svT[iy];
      i1++;
      iy++;
    }

    svInnerProduct[ic] = c;
  }

  for (i2 = 0; i2 < 15; i2++) {
    b_X[i2] = X[i2] / 0.97;
  }

  c_Gaussian(svT, svInnerProduct, b_X, dv);
  c = 0.0;
  for (i2 = 0; i2 < 6141; i2++) {
    c += dv[i2] * obj_Alpha[i2];
  }

  return c + -0.17725591999165119;
}

/* End of code generation (CompactSVM.c) */
