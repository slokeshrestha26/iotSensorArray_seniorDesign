/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_classify_data_info.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Mar-2022 14:42:52
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
      "789ced55cd6ed34010de4091b800e1c2b987082145f222da0357e428c1ad9246c4495a42"
      "096b7b9b9aee4fd85db70e4fc00d6ee551b8c163f034083bc9e6c792"
      "71d4145728cc6576fc79e79b99f57e0605ab5e0000dc0713fbf270e2ef4de3e2d4df02cb"
      "96c40b537f3b116bbb03b696f669fcf3d4bb9c291caa49c010c5b39d",
      "1ea73e434cd9a32106024b4eceb137464e7c826d9fe2d662d088235a5d8066410cc56bf3"
      "14bb67ad8002712ae71592c560368f7729fd6e65cc2369c97924dfdb"
      "14be9f57e4d3f9830c3e8df7dac7b02db19050127e866185bb01c54c49e812242596b085"
      "99cfc576054b7fc0b62d0bfa5c45cf24172f8440a3be1ce313185e20",
      "5f2a07310f0e30c30229dca7a44fb987098c171e312852207bae0f56ec33e9e7efdf1dfb"
      "27af4c07e4c877097f95f2e4d376537c614abe55bfd347297cc5042e"
      "5a9da6fd5ad56aef773be6d073763eee57dddabc8e66064f561d2025ce2bffb794fdabce"
      "b19b92bf98c07bd6a1795c8aee20418ee05c95a0e29c383c8452217d",
      "eb051ec0f27c453012cc67f1b3e8220b589edc6793d3217255ab5337e8fcbfb8661f30a3"
      "0f8debea0c5d9c31ae2d503e91863ca7c63e160c936ac05ce5737663"
      "3afee38a7c3affdb0c3e8d47e7da58f35cc7b383e56878707978d1f1e6a62fc3ef97bdd8"
      "6f8a7ee6cd97975e77c3f6e8e8e5871de435427a60894366917ae5bf",
      "5eeb7c9d94fcc5047e1d7a3d15eaa6c09eef2a2e16eff3a735fb789cd187c6ffa8d7b640"
      "4c9e70b182cefc2d9d5ef73ced0c3e8d5f9b4ecf66169f667e7af2b5"
      "6bbfc9934fdba6f0e5a5cf7bc8b603e47585d350c3dda3e7e1d3675c98ffbe3eff065bbd"
      "34d2",
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
                emlrtMxCreateDoubleScalar(738609.56842592591));
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
