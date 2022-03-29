/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_classify_data_info.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Mar-2022 13:32:22
 */

/* Include Files */
#include "_coder_classify_data_info.h"
#include "emlrt.h"
#include "tmwtypes.h"

/* Function Declarations */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo(void);

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : const mxArray *
 */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo(void)
{
  const mxArray *nameCaptureInfo;
  const char_T *data[6] = {
      "789ced55cd6ed34010ded0227101c285730f1597082fa23d708544494d9510296ed2124a"
      "58dbd3d4747fc2eea6383c0137b8c1a37083c7e071b0936c7e2c1947"
      "4d3142612eb3e3cf3bdfccacf7332ad8f50242e80e9ad8e77b137f7b1a17a7fe065ab624"
      "5e98faad446cec26da5eda67f04f53ef09ae21d493801306b39dbe60",
      "01275c3ba30120094ad04bf0c7c85940c10918b41683461cb1ea02340b62285e97cfc1bb"
      "680d1992e76a5e215d0c66f37893d2ef76c63c92969c47f2bd4de1fb"
      "79453e937f98c167f0eed1293e52201556545c00ae086fc8806b853d4a9402855bc00321"
      "772aa0823edfb16d1c081d3d53423e95928c7a6a8c4f60fc9e044abb",
      "84fbb80f1c24d1d063b4c7840f14c70b9f5a8c68943dd7bb2bf699f4f3f76f8dfdc3ad67"
      "2eca91cfd8a6f08529f956fd4eefa7f01513b86cb59bce4b5dabbddd"
      "6f9707bebbf7e1b0ead5e675343378b2ea4029715ef9bfa5ec5f758e9d94fcc504deb58f"
      "cba7bbd11da4c49542e85dac85a0ae08b1d2c4dc7a097d5c9aaf2810",
      "c9031e3f8b2eb2c4a5c97d2e0b36209e6eb5eb169bff17d7ec0367f46170539d658ab3c6"
      "b50d754095a52e9975089203ad0eb9a703c1ff9a8effb8229fc9ff3a"
      "83cfe0d1b936d63cd7f1ec70291a1e5e1e5e74bcb9e9cbe0fb976eec37453ff3e6cb4baf"
      "3be1d1e8e4e0dd1ef11b217b61cb636ed37ae5bf5e9b7ced94fcc504",
      "7e1d7a3d15eaa6043ff0b4908bf7f9e39a7d3cc8e8c3e0bfd56b4712aece845c4167fe94"
      "4eaf7b9e4e069fc1af4da767338b4f333f3df9da715ee5c9676c53f8"
      "f2d2e7e7c47186c4ef48b7a107fb274fc2478f852cfffbfafc0b8b93329f",
      ""};
  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 4520U, &nameCaptureInfo);
  return nameCaptureInfo;
}

/*
 * Arguments    : void
 * Return Type  : mxArray *
 */
mxArray *emlrtMexFcnProperties(void)
{
  mxArray *xEntryPoints;
  mxArray *xInputs;
  mxArray *xResult;
  const char_T *epFieldName[6] = {
      "Name",           "NumberOfInputs", "NumberOfOutputs",
      "ConstantInputs", "FullPath",       "TimeStamp"};
  const char_T *propFieldName[5] = {"Version", "ResolvedFunctions",
                                    "EntryPoints", "CoverageInfo",
                                    "IsPolymorphic"};
  xEntryPoints =
      emlrtCreateStructMatrix(1, 1, 6, (const char_T **)&epFieldName[0]);
  xInputs = emlrtCreateLogicalMatrix(1, 2);
  emlrtSetField(xEntryPoints, 0, (const char_T *)"Name",
                emlrtMxCreateString((const char_T *)"classify_data"));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"NumberOfInputs",
                emlrtMxCreateDoubleScalar(2.0));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"NumberOfOutputs",
                emlrtMxCreateDoubleScalar(1.0));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"ConstantInputs", xInputs);
  emlrtSetField(
      xEntryPoints, 0, (const char_T *)"FullPath",
      emlrtMxCreateString(
          (const char_T *)"/Users/sloke/Documents/classes/Senior Design "
                          "II/iotSensorArray_seniorDesign/waistband/"
                          "generate_ml_model/classify_data.m"));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"TimeStamp",
                emlrtMxCreateDoubleScalar(738609.56135416671));
  xResult =
      emlrtCreateStructMatrix(1, 1, 5, (const char_T **)&propFieldName[0]);
  emlrtSetField(
      xResult, 0, (const char_T *)"Version",
      emlrtMxCreateString((const char_T *)"9.10.0.1739362 (R2021a) Update 5"));
  emlrtSetField(xResult, 0, (const char_T *)"ResolvedFunctions",
                (mxArray *)emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, (const char_T *)"EntryPoints", xEntryPoints);
  return xResult;
}

/*
 * File trailer for _coder_classify_data_info.c
 *
 * [EOF]
 */
