/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: classify_data.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Mar-2022 14:42:52
 */

/* Include Files */
#include "classify_data.h"
#include "CompactClassificationSVM.h"
#include "FFTImplementationCallback.h"
#include "classify_data_internal_types.h"
#include "combineVectorElements.h"
#include "hilbert.h"
#include "ifft.h"
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
  static double ML_SupportVectorsT[129940];
  static double ML_Alpha[6497];
  double ML_Mu[20];
  double ML_Sigma[20];
  double h_expl_temp[4];
  double ML_ClassNames[2];
  double ML_Prior[2];
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
      ML_Alpha, &expl_temp, ML_SupportVectorsT, &b_expl_temp, &c_expl_temp,
      ML_Mu, ML_Sigma, &d_expl_temp, ML_ClassNames, e_expl_temp, &f_expl_temp,
      ML_Prior, g_expl_temp, h_expl_temp);
  expl_temp = c_CompactClassificationSVM_pred(ML_Alpha, ML_SupportVectorsT,
                                              ML_Mu, ML_Sigma, ML_ClassNames,
                                              ML_Prior, features);
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
 *  predictions from 3 machine learning models.
 *
 * Arguments    : const double dataAcc[23400]
 *                const double dataHr[300]
 * Return Type  : int
 */
int classify_data(const double dataAcc[23400], const double dataHr[300])
{
  static creal_T b_x[23400];
  static creal_T x[23400];
  static creal_T wwc[7799];
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
  double d;
  double nt_im;
  double nt_re;
  double varHr;
  double xbar;
  double y;
  int hi;
  int k;
  int p;
  int rt;
  int xblockoffset;
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
  rt = 0;
  wwc[3899].re = 1.0;
  wwc[3899].im = 0.0;
  for (k = 0; k < 3899; k++) {
    xblockoffset = ((k + 1) << 1) - 1;
    if (7800 - rt <= xblockoffset) {
      rt = (xblockoffset + rt) - 7800;
    } else {
      rt += xblockoffset;
    }
    nt_im = -3.1415926535897931 * (double)rt / 3900.0;
    if (nt_im == 0.0) {
      nt_re = 1.0;
      nt_im = 0.0;
    } else {
      nt_re = cos(nt_im);
      nt_im = sin(nt_im);
    }
    wwc[3898 - k].re = nt_re;
    wwc[3898 - k].im = -nt_im;
  }
  for (k = 3898; k >= 0; k--) {
    wwc[k + 3900] = wwc[3898 - k];
  }
  c_FFTImplementationCallback_doH(dataAcc, 0, *(creal_T(*)[7800]) & x[0], wwc,
                                  costab, sintab, costab, sintabinv);
  c_FFTImplementationCallback_doH(dataAcc, 7800, *(creal_T(*)[7800]) & x[7800],
                                  wwc, costab, sintab, costab, sintabinv);
  c_FFTImplementationCallback_doH(dataAcc, 15600,
                                  *(creal_T(*)[7800]) & x[15600], wwc, costab,
                                  sintab, costab, sintabinv);
  for (rt = 0; rt < 3; rt++) {
    for (xblockoffset = 0; xblockoffset < 3899; xblockoffset++) {
      hi = xblockoffset + 7800 * rt;
      x[hi + 1].re *= 2.0;
      x[hi + 1].im *= 2.0;
      x[hi + 3901].re = 0.0;
      x[hi + 3901].im = 0.0;
    }
  }
  memcpy(&b_x[0], &x[0], 23400U * sizeof(creal_T));
  ifft(b_x, x);
  for (k = 0; k < 23400; k++) {
    amp[k] = rt_hypotd_snf(x[k].re, x[k].im);
  }
  hilbert(dataHr, c_x);
  for (k = 0; k < 300; k++) {
    ampHr[k] = rt_hypotd_snf(c_x[k].re, c_x[k].im);
  }
  /*  Calculates mean of the data */
  y = dataHr[0];
  for (k = 0; k < 299; k++) {
    y += dataHr[k + 1];
  }
  /*  Calculates variance of the data */
  for (p = 0; p < 3; p++) {
    rt = p * 7800;
    memcpy(&xv[0], &dataAcc[rt], 7800U * sizeof(double));
    xbar = xv[0];
    for (k = 0; k < 1023; k++) {
      xbar += xv[k + 1];
    }
    for (rt = 0; rt < 7; rt++) {
      xblockoffset = (rt + 1) << 10;
      nt_re = xv[xblockoffset];
      if (rt + 2 == 8) {
        hi = 632;
      } else {
        hi = 1024;
      }
      for (k = 2; k <= hi; k++) {
        nt_re += xv[(xblockoffset + k) - 1];
      }
      xbar += nt_re;
    }
    xbar /= 7800.0;
    nt_re = 0.0;
    for (k = 0; k < 7800; k++) {
      nt_im = xv[k] - xbar;
      nt_re += nt_im * nt_im;
    }
    varAxis[p] = nt_re / 7799.0;
  }
  xbar = dataHr[0];
  for (k = 0; k < 299; k++) {
    xbar += dataHr[k + 1];
  }
  xbar /= 300.0;
  varHr = 0.0;
  for (k = 0; k < 300; k++) {
    nt_im = dataHr[k] - xbar;
    varHr += nt_im * nt_im;
  }
  varHr /= 299.0;
  /*  Estimates Gamma shape and scale parameters */
  /*  Estimates the gamma shape and scale parameters of a dataset. */
  /*  PAL gamfit Estimation Function */
  /*  Makes any zeros nonzero to prevent invalid logarithmic operations */
  for (xblockoffset = 0; xblockoffset < 23400; xblockoffset++) {
    if (amp[xblockoffset] == 0.0) {
      amp[xblockoffset] = 1.0E-5;
    }
  }
  /*  Calculates variables for closed form gamma parameter estimation */
  combineVectorElements(amp, sumX);
  for (k = 0; k < 23400; k++) {
    d = amp[k];
    nt_re = log(d);
    d_x[k] = d * nt_re;
    amp[k] = nt_re;
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
  for (xblockoffset = 0; xblockoffset < 300; xblockoffset++) {
    if (ampHr[xblockoffset] == 0.0) {
      ampHr[xblockoffset] = 1.0E-5;
    }
  }
  /*  Calculates variables for closed form gamma parameter estimation */
  xbar = ampHr[0];
  for (k = 0; k < 299; k++) {
    xbar += ampHr[k + 1];
  }
  for (k = 0; k < 300; k++) {
    nt_re = ampHr[k];
    e_x[k] = nt_re * log(nt_re);
  }
  nt_re = e_x[0];
  for (k = 0; k < 299; k++) {
    nt_re += e_x[k + 1];
  }
  for (k = 0; k < 300; k++) {
    ampHr[k] = log(ampHr[k]);
  }
  nt_im = ampHr[0];
  for (k = 0; k < 299; k++) {
    nt_im += ampHr[k + 1];
  }
  nt_re = 300.0 * nt_re - nt_im * xbar;
  /*  Estimates closed form shape and scale values */
  nt_im = 300.0 * xbar / nt_re;
  nt_re *= 1.1111111111111112E-5;
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
  c_y[17] = nt_im;
  c_y[18] = nt_re;
  c_y[19] = sqrt(nt_im * nt_im + nt_re * nt_re);
  return get_prediction(c_y);
}

/*
 * File trailer for classify_data.c
 *
 * [EOF]
 */
