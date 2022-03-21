/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: classify_data.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 20-Mar-2022 19:57:03
 */

/* Include Files */
#include "classify_data.h"
#include "CompactClassificationSVM.h"
#include "FFTImplementationCallback.h"
#include "classify_data_data.h"
#include "classify_data_initialize.h"
#include "classify_data_internal_types.h"
#include "combineVectorElements.h"
#include "hilbert.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static int get_prediction(const double features[20]);

static double rt_hypotd_snf(double u0, double u1);

/* Function Definitions */
/*
 * Returns the prediction of a 5 minute window for the following categories:
 *    Stress = 1
 *    No Stress = 0
 *
 * Arguments    : const double features[20]
 * Return Type  : int
 */
static int get_prediction(const double features[20])
{
  static double ml_SupportVectorsT[129940];
  static double ml_Alpha[6497];
  double ml_Mu[20];
  double ml_Sigma[20];
  double h_expl_temp[4];
  double ml_ClassNames[2];
  double ml_Prior[2];
  double b_expl_temp;
  double c_expl_temp;
  double expl_temp;
  int e_expl_temp[2];
  int i_expl_temp;
  int prediction;
  bool g_expl_temp[2];
  c_classreg_learning_coderutils_ f_expl_temp;
  d_classreg_learning_coderutils_ d_expl_temp;
  /*  Get Prediction Function */
  /*  raw model output:  */
  /*    No Stress    = 2 */
  /*    Stress       = 3 */
  /*  Loads models into the workspace */
  c_CompactClassificationSVM_Comp(
      ml_Alpha, &expl_temp, ml_SupportVectorsT, &b_expl_temp, &c_expl_temp,
      ml_Mu, ml_Sigma, &d_expl_temp, ml_ClassNames, e_expl_temp, &f_expl_temp,
      ml_Prior, g_expl_temp, h_expl_temp);
  expl_temp = c_CompactClassificationSVM_pred(ml_Alpha, ml_SupportVectorsT,
                                              ml_Mu, ml_Sigma, ml_ClassNames,
                                              ml_Prior, features);
  /*  Predicts Stress vs No Stress */
  /*  Determines dominant prediction using majority-wins rule */
  expl_temp = trunc(expl_temp);
  if (rtIsNaN(expl_temp) || rtIsInf(expl_temp)) {
    expl_temp = 0.0;
  } else {
    expl_temp = fmod(expl_temp, 256.0);
  }
  if (expl_temp < 0.0) {
    i_expl_temp = (signed char)-(signed char)(unsigned char)-expl_temp;
  } else {
    i_expl_temp = (signed char)(unsigned char)expl_temp;
  }
  if ((unsigned char)i_expl_temp == 3) {
    prediction = 1;
    /*  Stress */
  } else {
    prediction = 0;
    /*  No Stress */
  }
  return prediction;
}

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_hypotd_snf(double u0, double u1)
{
  double a;
  double y;
  a = fabs(u0);
  y = fabs(u1);
  if (a < y) {
    a /= y;
    y *= sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = a * sqrt(y * y + 1.0);
  } else if (!rtIsNaN(y)) {
    y = a * 1.4142135623730951;
  }
  return y;
}

/*
 * Returns the prediction value for a 5 minute data segment after evaluating
 *  predictions from 1 machine learning model.
 *
 * Arguments    : const double dataAcc[23400]
 *                const double dataHr[300]
 * Return Type  : int
 */
int classify_data(const double dataAcc[23400], const double dataHr[300])
{
  static creal_T b_x[23400];
  static creal_T x[23400];
  static double amp[23400];
  static double d_x[23400];
  static double costab[8193];
  static double sintab[8193];
  static double sintabinv[8193];
  static double xv[7800];
  creal_T c_x[300];
  double ampHr[300];
  double e_x[300];
  double c_y[20];
  double b_y[3];
  double den[3];
  double sumX[3];
  double varAxis[3];
  double bsum;
  double d;
  double t;
  double varHr;
  double xbar;
  double y;
  int hi;
  int i;
  int j;
  int p;
  int xblockoffset;
  if (!isInitialized_classify_data) {
    classify_data_initialize();
  }
  /* CLASSIFY_DATA Classify stress, no stress from accelerometer and heart rate
   */
  /*  data. */
  /*    PRED = CLASSIFY_DATA(DATA) returns 1 if stress is predicted by machine
   */
  /*    learning algorithm. */
  /*  Authors: Sloke Shrestha, Dr. Premananda Indic, Joshua Stapp */
  /*  The University of Texas at Tyler */
  /*  Department of Electrical Engineering */
  /*  Version 4.0 */
  /*  Classify Data Function */
  /*  Exctracts features from accelerometer data */
  /*  Returns the features of a 5 minute window of accelerometer data (dataACC)
   * and heart rate data. Input */
  /*  data is assumed to be clean, in matrix form, and 5 minutes long. */
  /*  Get Features Function */
  /*  Performs the Hilbert transformation to get signal amplitudes */
  c_FFTImplementationCallback_gen(costab, sintab, sintabinv);
  c_FFTImplementationCallback_dob(dataAcc, costab, sintab, sintabinv, x);
  for (j = 0; j < 3; j++) {
    for (i = 0; i < 3899; i++) {
      xblockoffset = i + 7800 * j;
      x[xblockoffset + 1].re *= 2.0;
      x[xblockoffset + 1].im *= 2.0;
      x[xblockoffset + 3901].re = 0.0;
      x[xblockoffset + 3901].im = 0.0;
    }
  }
  c_FFTImplementationCallback_gen(costab, sintab, sintabinv);
  memcpy(&b_x[0], &x[0], 23400U * sizeof(creal_T));
  d_FFTImplementationCallback_dob(b_x, costab, sintab, sintabinv, x);
  for (j = 0; j < 23400; j++) {
    amp[j] = rt_hypotd_snf(x[j].re, x[j].im);
  }
  hilbert(dataHr, c_x);
  for (j = 0; j < 300; j++) {
    ampHr[j] = rt_hypotd_snf(c_x[j].re, c_x[j].im);
  }
  /*  Calculates mean of the data */
  y = dataHr[0];
  for (j = 0; j < 299; j++) {
    y += dataHr[j + 1];
  }
  /*  Calculates variance of the data */
  for (p = 0; p < 3; p++) {
    j = p * 7800;
    memcpy(&xv[0], &dataAcc[j], 7800U * sizeof(double));
    xbar = xv[0];
    for (j = 0; j < 1023; j++) {
      xbar += xv[j + 1];
    }
    for (i = 0; i < 7; i++) {
      xblockoffset = (i + 1) << 10;
      bsum = xv[xblockoffset];
      if (i + 2 == 8) {
        hi = 632;
      } else {
        hi = 1024;
      }
      for (j = 2; j <= hi; j++) {
        bsum += xv[(xblockoffset + j) - 1];
      }
      xbar += bsum;
    }
    xbar /= 7800.0;
    bsum = 0.0;
    for (j = 0; j < 7800; j++) {
      t = xv[j] - xbar;
      bsum += t * t;
    }
    varAxis[p] = bsum / 7799.0;
  }
  xbar = dataHr[0];
  for (j = 0; j < 299; j++) {
    xbar += dataHr[j + 1];
  }
  xbar /= 300.0;
  varHr = 0.0;
  for (j = 0; j < 300; j++) {
    t = dataHr[j] - xbar;
    varHr += t * t;
  }
  varHr /= 299.0;
  /*  Estimates Gamma shape and scale parameters */
  /*  Estimates the gamma shape and scale parameters of a dataset. */
  /*  PAL gamfit Estimation Function */
  /*  Makes any zeros nonzero to prevent invalid logarithmic operations */
  for (i = 0; i < 23400; i++) {
    if (amp[i] == 0.0) {
      amp[i] = 1.0E-5;
    }
  }
  /*  Calculates variables for closed form gamma parameter estimation */
  combineVectorElements(amp, sumX);
  for (j = 0; j < 23400; j++) {
    d = amp[j];
    bsum = log(d);
    d_x[j] = d * bsum;
    amp[j] = bsum;
  }
  combineVectorElements(d_x, den);
  combineVectorElements(amp, b_y);
  /*  Estimates closed form shape and scale values */
  d = 7800.0 * den[0] - b_y[0] * sumX[0];
  sumX[0] = 7800.0 * sumX[0] / d;
  d *= 1.6436554898093361E-8;
  den[0] = d;
  d = 7800.0 * den[1] - b_y[1] * sumX[1];
  sumX[1] = 7800.0 * sumX[1] / d;
  d *= 1.6436554898093361E-8;
  den[1] = d;
  d = 7800.0 * den[2] - b_y[2] * sumX[2];
  sumX[2] = 7800.0 * sumX[2] / d;
  d *= 1.6436554898093361E-8;
  /*  Estimates the gamma shape and scale parameters of a dataset. */
  /*  PAL gamfit Estimation Function */
  /*  Makes any zeros nonzero to prevent invalid logarithmic operations */
  for (i = 0; i < 300; i++) {
    if (ampHr[i] == 0.0) {
      ampHr[i] = 1.0E-5;
    }
  }
  /*  Calculates variables for closed form gamma parameter estimation */
  xbar = ampHr[0];
  for (j = 0; j < 299; j++) {
    xbar += ampHr[j + 1];
  }
  for (j = 0; j < 300; j++) {
    bsum = ampHr[j];
    e_x[j] = bsum * log(bsum);
  }
  bsum = e_x[0];
  for (j = 0; j < 299; j++) {
    bsum += e_x[j + 1];
  }
  for (j = 0; j < 300; j++) {
    ampHr[j] = log(ampHr[j]);
  }
  t = ampHr[0];
  for (j = 0; j < 299; j++) {
    t += ampHr[j + 1];
  }
  bsum = 300.0 * bsum - t * xbar;
  /*  Estimates closed form shape and scale values */
  t = 300.0 * xbar / bsum;
  bsum *= 1.1111111111111112E-5;
  /* dist vecotr */
  /*  Formats feature vector for machine learning algorithms */
  /*  Makes predictions using mapped data features */
  combineVectorElements(dataAcc, b_y);
  c_y[0] = b_y[0] / 7800.0;
  c_y[3] = varAxis[0];
  c_y[6] = sumX[0];
  c_y[9] = den[0];
  c_y[12] = sqrt(sumX[0] * sumX[0] + den[0] * den[0]);
  c_y[1] = b_y[1] / 7800.0;
  c_y[4] = varAxis[1];
  c_y[7] = sumX[1];
  c_y[10] = den[1];
  c_y[13] = sqrt(sumX[1] * sumX[1] + den[1] * den[1]);
  c_y[2] = b_y[2] / 7800.0;
  c_y[5] = varAxis[2];
  c_y[8] = sumX[2];
  c_y[11] = d;
  c_y[14] = sqrt(sumX[2] * sumX[2] + d * d);
  c_y[15] = y / 300.0;
  c_y[16] = varHr;
  c_y[17] = t;
  c_y[18] = bsum;
  c_y[19] = sqrt(t * t + bsum * bsum);
  return get_prediction(c_y);
}

/*
 * File trailer for classify_data.c
 *
 * [EOF]
 */
