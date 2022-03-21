/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: CompactSVM.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 20-Mar-2022 19:57:03
 */

/* Include Files */
#include "CompactSVM.h"
#include "Gaussian.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Declarations */
static void CompactSVM_normalize(const double obj_Mu[20],
                                 const double obj_Sigma[20], double Xin[20]);

/* Function Definitions */
/*
 * Arguments    : const double obj_Mu[20]
 *                const double obj_Sigma[20]
 *                double Xin[20]
 * Return Type  : void
 */
static void CompactSVM_normalize(const double obj_Mu[20],
                                 const double obj_Sigma[20], double Xin[20])
{
  double c_tmp_data[20];
  int acoef;
  int bcoef;
  int k;
  int partialTrueCount;
  int tmp_size_idx_1;
  int trueCount;
  signed char b_tmp_data[20];
  signed char tmp_data[20];
  bool x[20];
  bool exitg1;
  bool y;
  for (partialTrueCount = 0; partialTrueCount < 20; partialTrueCount++) {
    x[partialTrueCount] = (obj_Mu[partialTrueCount] == 0.0);
  }
  y = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= 19)) {
    if (!x[k]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!y) {
    for (k = 0; k < 20; k++) {
      Xin[k] -= obj_Mu[k];
    }
  }
  for (partialTrueCount = 0; partialTrueCount < 20; partialTrueCount++) {
    x[partialTrueCount] = (obj_Sigma[partialTrueCount] == 1.0);
  }
  y = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= 19)) {
    if (!x[k]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (!y) {
    trueCount = 0;
    partialTrueCount = 0;
    for (k = 0; k < 20; k++) {
      if (obj_Sigma[k] > 0.0) {
        trueCount++;
        tmp_data[partialTrueCount] = (signed char)(k + 1);
        partialTrueCount++;
      }
    }
    tmp_size_idx_1 = (signed char)trueCount;
    if ((signed char)trueCount != 0) {
      acoef = (trueCount != 1);
      bcoef = (trueCount != 1);
      partialTrueCount = (signed char)trueCount - 1;
      for (k = 0; k <= partialTrueCount; k++) {
        c_tmp_data[k] =
            Xin[tmp_data[acoef * k] - 1] / obj_Sigma[tmp_data[bcoef * k] - 1];
      }
    }
    partialTrueCount = 0;
    for (k = 0; k < 20; k++) {
      if (obj_Sigma[k] > 0.0) {
        b_tmp_data[partialTrueCount] = (signed char)(k + 1);
        partialTrueCount++;
      }
    }
    for (partialTrueCount = 0; partialTrueCount < tmp_size_idx_1;
         partialTrueCount++) {
      Xin[b_tmp_data[partialTrueCount] - 1] = c_tmp_data[partialTrueCount];
    }
  }
}

/*
 * Arguments    : const double obj_Alpha[6497]
 *                const double obj_SupportVectorsT[129940]
 *                const double obj_Mu[20]
 *                const double obj_Sigma[20]
 *                const double Xin[20]
 * Return Type  : double
 */
double CompactSVM_score(const double obj_Alpha[6497],
                        const double obj_SupportVectorsT[129940],
                        const double obj_Mu[20], const double obj_Sigma[20],
                        const double Xin[20])
{
  static double svT[129940];
  double b_dv1[6497];
  double svInnerProduct[6497];
  double b_dv[20];
  double c;
  double c_tmp;
  int i;
  int i1;
  int i2;
  int k;
  for (i2 = 0; i2 < 129940; i2++) {
    svT[i2] = obj_SupportVectorsT[i2] / 1.1;
  }
  i2 = 1;
  for (i = 0; i < 6497; i++) {
    i1 = i2 - 1;
    i2 += 20;
    c = 0.0;
    for (k = 0; k < 20; k++) {
      c_tmp = svT[i1 + k];
      c += c_tmp * c_tmp;
    }
    svInnerProduct[i] = c;
  }
  memcpy(&b_dv[0], &Xin[0], 20U * sizeof(double));
  CompactSVM_normalize(obj_Mu, obj_Sigma, b_dv);
  for (i2 = 0; i2 < 20; i2++) {
    b_dv[i2] /= 1.1;
  }
  Gaussian(svT, svInnerProduct, b_dv, b_dv1);
  c = 0.0;
  for (i2 = 0; i2 < 6497; i2++) {
    c += b_dv1[i2] * obj_Alpha[i2];
  }
  return c + -0.17431100833569818;
}

/*
 * File trailer for CompactSVM.c
 *
 * [EOF]
 */
