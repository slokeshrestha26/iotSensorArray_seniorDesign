/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * classify_data.c
 *
 * Code generation for function 'classify_data'
 *
 */

/* Include files */
#include "classify_data.h"
#include "CompactClassificationSVM.h"
#include "classify_data_data.h"
#include "classify_data_initialize.h"
#include "fft.h"
#include "ifft.h"
#include "rt_nonfinite.h"
#include "var.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
/* Function Declarations */
static void gamfitPAL(double x[28800], double sh[3], double sc[3]);
static void get_features(const double data[28800], double features[12]);
static int get_prediction(const double features[15]);
static double rt_hypotd_snf(double u0, double u1);

/* Function Definitions */
static void gamfitPAL(double x[28800], double sh[3], double sc[3])
{
  int i;
  int k;
  int xpageoffset;
  double x_tmp;
  static double b_x[28800];
  static double c_x[28800];
  int b_xpageoffset;
  double d;

  /*  PAL gamfit Estimation Function */
  /*  Estimates the gamma shape and scale parameters of a dataset. */
  /*  Makes any zeros nonzero to prevent invalid logarithmic operations */
  for (i = 0; i < 28800; i++) {
    if (x[i] == 0.0) {
      x[i] = 1.0E-5;
    }
  }

  /*  Calculates variables for closed form gamma parameter estimation */
  for (i = 0; i < 3; i++) {
    xpageoffset = i * 9600;
    x_tmp = x[xpageoffset];
    for (k = 0; k < 9599; k++) {
      x_tmp += x[(xpageoffset + k) + 1];
    }

    sh[i] = x_tmp;
  }

  for (k = 0; k < 28800; k++) {
    x_tmp = log(x[k]);
    b_x[k] = x_tmp;
    c_x[k] = x[k] * x_tmp;
  }

  /*  Estimates closed form shape and scale values */
  for (i = 0; i < 3; i++) {
    xpageoffset = i * 9600;
    b_xpageoffset = i * 9600;
    x_tmp = c_x[xpageoffset];
    d = b_x[b_xpageoffset];
    for (k = 0; k < 9599; k++) {
      x_tmp += c_x[(xpageoffset + k) + 1];
      d += b_x[(b_xpageoffset + k) + 1];
    }

    x_tmp = 9600.0 * x_tmp - d * sh[i];
    sh[i] = 9600.0 * sh[i] / x_tmp;
    x_tmp *= 1.0850694444444445E-8;
    sc[i] = x_tmp;
  }
}

static void get_features(const double data[28800], double features[12])
{
  static creal_T x[28800];
  int j;
  static creal_T b_x[28800];
  int i;
  int xpageoffset;
  int b_i;
  static double amp[28800];
  double shpElem[3];
  double sclElem[3];
  double dv[3];
  double d;

  /*  Get Features Function */
  /*  Returns the features of a 5 minute window of accelerometer data. Input */
  /*  data is assumed to be clean, in matrix form, and 5 minutes long. */
  /*  Performs the Hilbert transformation to get signal amplitudes */
  fft(data, x);
  for (j = 0; j < 3; j++) {
    for (i = 0; i < 4799; i++) {
      xpageoffset = i + 9600 * j;
      b_i = xpageoffset + 1;
      x[b_i].re *= 2.0;
      x[b_i].im *= 2.0;
      xpageoffset += 4801;
      x[xpageoffset].re = 0.0;
      x[xpageoffset].im = 0.0;
    }
  }

  memcpy(&b_x[0], &x[0], 28800U * sizeof(creal_T));
  ifft(b_x, x);
  for (j = 0; j < 28800; j++) {
    amp[j] = rt_hypotd_snf(x[j].re, x[j].im);
  }

  /*  Calculates mean of the data */
  /*  Calculates variance of the data */
  /*  Estimates Gamma shape and scale parameters */
  gamfitPAL(amp, shpElem, sclElem);

  /*  Formats feature vector for machine learning algorithms */
  var(data, dv);
  for (i = 0; i < 3; i++) {
    xpageoffset = i * 9600;
    d = data[xpageoffset];
    for (j = 0; j < 9599; j++) {
      d += data[(xpageoffset + j) + 1];
    }

    features[i] = d / 9600.0;
    features[i + 3] = dv[i];
    features[i + 6] = shpElem[i];
    features[i + 9] = sclElem[i];
  }
}

static int get_prediction(const double features[15])
{
  int prediction;
  double ML_CvNS_Alpha[2498];
  double expl_temp;
  static double ML_CvNS_SupportVectorsT[37470];
  double b_expl_temp;
  double c_expl_temp;
  double ML_CvNS_Mu[15];
  double ML_CvNS_Sigma[15];
  d_classreg_learning_coderutils_ d_expl_temp;
  char ML_CvNS_ClassNames[2];
  int e_expl_temp[2];
  c_classreg_learning_coderutils_ f_expl_temp;
  double ML_CvNS_Prior[2];
  boolean_T g_expl_temp[2];
  double h_expl_temp[4];
  double ML_CvS_Alpha[2377];
  static double ML_CvS_SupportVectorsT[35655];
  double ML_CvS_Mu[15];
  double ML_CvS_Sigma[15];
  char ML_CvS_ClassNames[2];
  double ML_CvS_Prior[2];
  static double ML_SvNS_Alpha[6141];
  static double ML_SvNS_SupportVectorsT[92115];
  double ML_SvNS_Mu[15];
  double ML_SvNS_Sigma[15];
  char ML_SvNS_ClassNames[2];
  double ML_SvNS_Prior[2];
  char pred_CNS;
  char pred_CS;
  char pred_SNS;

  /*  Get Prediction Function */
  /*  Returns the prediction of a 5 minute window for the following categories: */
  /*    Craving      = 1 */
  /*    No Stress    = 2 */
  /*    Stress       = 3 */
  /*    Undetermined = 0 */
  /*  Loads models into the workspace */
  c_CompactClassificationSVM_Comp(ML_CvNS_Alpha, &expl_temp,
    ML_CvNS_SupportVectorsT, &b_expl_temp, &c_expl_temp, ML_CvNS_Mu,
    ML_CvNS_Sigma, &d_expl_temp, ML_CvNS_ClassNames, e_expl_temp, &f_expl_temp,
    ML_CvNS_Prior, g_expl_temp, h_expl_temp);
  d_CompactClassificationSVM_Comp(ML_CvS_Alpha, &expl_temp,
    ML_CvS_SupportVectorsT, &b_expl_temp, &c_expl_temp, ML_CvS_Mu, ML_CvS_Sigma,
    &d_expl_temp, ML_CvS_ClassNames, e_expl_temp, &f_expl_temp, ML_CvS_Prior,
    g_expl_temp, h_expl_temp);
  e_CompactClassificationSVM_Comp(ML_SvNS_Alpha, &expl_temp,
    ML_SvNS_SupportVectorsT, &b_expl_temp, &c_expl_temp, ML_SvNS_Mu,
    ML_SvNS_Sigma, &d_expl_temp, ML_SvNS_ClassNames, e_expl_temp, &f_expl_temp,
    ML_SvNS_Prior, g_expl_temp, h_expl_temp);
  pred_CNS = c_CompactClassificationSVM_pred(ML_CvNS_Alpha,
    ML_CvNS_SupportVectorsT, ML_CvNS_Mu, ML_CvNS_Sigma, ML_CvNS_ClassNames,
    ML_CvNS_Prior, features);

  /*  Predicts Craving vs No Stress */
  pred_CS = d_CompactClassificationSVM_pred(ML_CvS_Alpha, ML_CvS_SupportVectorsT,
    ML_CvS_Mu, ML_CvS_Sigma, ML_CvS_ClassNames, ML_CvS_Prior, features);

  /*  Predicts Craving vs Stress */
  pred_SNS = e_CompactClassificationSVM_pred(ML_SvNS_Alpha,
    ML_SvNS_SupportVectorsT, ML_SvNS_Mu, ML_SvNS_Sigma, ML_SvNS_ClassNames,
    ML_SvNS_Prior, features);

  /*  Predicts Stress vs No Stress */
  /*  Determines dominant prediction using majority-wins rule */
  if (pred_CNS == pred_CS) {
    prediction = 1;

    /*  Craving */
  } else if (pred_CNS == pred_SNS) {
    prediction = 2;

    /*  No Stress */
  } else if (pred_SNS == pred_CS) {
    prediction = 3;

    /*  Stress */
  } else {
    prediction = 0;

    /*  Undetermined */
  }

  return prediction;
}

static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  a = fabs(u0);
  y = fabs(u1);
  if (a < y) {
    a /= y;
    y *= sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = a * sqrt(y * y + 1.0);
  } else {
    if (!rtIsNaN(y)) {
      y = a * 1.4142135623730951;
    }
  }

  return y;
}

int classify_data(double data[28800])
{

  double features[12];
  double new_features[15];
  if (isInitialized_classify_data == false) {
    classify_data_initialize();
  }

  /* CLASSIFY_DATA Classify stress, no stress, and craving accelerometer data. */
  /*    PRED = CLASSIFY_DATA(DATA) returns the class predicted by three machine */
  /*    learning models using the majority wins rule when provided */
  /*    accelerometer data from a Garmin Forerunner watch. The following data */
  /*    features are used by the machine learning models for classification: */
  /*    1. Mean for each axis */
  /*    2. Variance for each axis */
  /*    3. Gamma shape parameter for each axis */
  /*    4. Gamma scale parameter for each axis */
  /*    5. Distance constant D-K for each axis */
  /*  */
  /*    DATA should be a 3-column matrix of accelerometer data representing a */
  /*    five-minute window. */
  /*  */
  /*    PRED will be a numeric value representing the following classes: */
  /*    Craving      = 1 */
  /*    No Stress    = 2 */
  /*    Stress       = 3 */
  /*    Undetermined = 0 */
  /*  */
  /*    For information on the shape and scale values: */
  /*    See also GAMFIT. */
  /*  Authors: Sloke Shrestha, Dr. Premananda Indic, Joshua Stapp */
  /*  The University of Texas at Tyler */
  /*  Department of Electrical Engineering */
  /*  Version 3.0 */
  /*  Classify Data Function */
  /*  Returns the prediction value for a 5 minute data segment after evaluating */
  /*  predictions from 3 machine learning models. */
  /*  Exctracts features from accelerometer data */
  get_features(data, features);

  /*  Maps Garmin features to Empatica E4 format */
  /*  Map Features Function */
  /*  Returns data features mapped from Garmin format to Empatica E4 format. */
  /*  Initializes new feature vector */
  /*  Maps Garmin axis mean features to Empatica E4 format */
  new_features[0] = 1.90770314 * features[0] + 8.04472341;
  new_features[1] = 1.97913774 * features[1] - 1.05064168;
  new_features[2] = 2.0 * features[2] - 4.0;

  /*  Maps Garmin axis variance features to Empatica E4 format */
  new_features[3] = 3.80290914 * features[3] + 14.76397674;
  new_features[4] = 4.3 * features[4] - 2.96821221;
  new_features[5] = 3.25 * features[5] + 4.64261691;

  /*  Maps Garmin axis shape features to Empatica E4 format */
  new_features[6] = 0.9 * features[6];
  new_features[7] = 0.9 * features[7];
  new_features[8] = 0.84 * features[8];

  /*  Maps Garmin axis scale features to Empatica E4 format */
  new_features[9] = 2.15 * features[9];
  new_features[10] = 2.15 * features[10];
  new_features[11] = 2.0 * features[11];

  /*  Calculates new distance constant in the Empatica E4 format */
  new_features[12] = sqrt(new_features[6] * new_features[6] + new_features[9] *
    new_features[9]);
  new_features[13] = sqrt(new_features[7] * new_features[7] + new_features[10] *
    new_features[10]);
  new_features[14] = sqrt(new_features[8] * new_features[8] + new_features[11] *
    new_features[11]);

  /*  Makes predictions using mapped data features */
  return get_prediction(new_features);
}

/* End of code generation (classify_data.c) */
