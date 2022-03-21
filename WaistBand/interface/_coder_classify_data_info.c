/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_classify_data_info.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 20-Mar-2022 19:57:03
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
      "789ced54cb6ed3401475a0486c80b061dd45c4269207b595608b1225b855d24871929650"
      "dab13d6d87ce23cc4c8ad3154b360876f0117c003b58f20ffc015f81"
      "ed649cc49271d4145728dccdf5f5f1dc731f9e6314ac46c1308cbbc6d8dede1ffb3b93b8"
      "38f1378c794be28589bf9988b5dd32d6e6ce69fcc3c4bb9c29e4ab71",
      "c02045f1498f53cc2053f668800c812427e7c88b90634c908d296acf06cd30a2b519280e"
      "42287cae9c22f7ac3da4863895d30ac96c10cfe328a5dfb58c79242d"
      "398fe477abc2f7e3927c3abf9bc1a7f17ee7007424121248c2cf10a8727748115312b804"
      "4a8924682386b958af22894fd8ba6501cc55f04e72f15408383a9411",
      "3e86c11b88a57220f3002587d42326856aaeafa394baef2dd857d24fbfbf1df95f5f1e3b"
      "79f2fd2cbddfc8934fdb75f1f929f916fd2f1fa4f01513b868775bf6"
      "7355afbfdaea56069eb379b15373ebd33a5a193c59751829715ef9bfa69c5f748ebd94fc"
      "c504deb7f62a07a5e01612e808ce550928ce89c37d2015d4b75ca013",
      "509e3e110405c32c7cc73d244099068e800aa703e8aa76b761d2b88f8f4bf60132fad0b8"
      "aeced4c599516d43858934e5393577906088d486cc5598b36bd3edef"
      "97e4d3f95f66f0693cd86b73c9bd46b303e56078607e78c17a73d397c1b74ffdd0af8a7e"
      "e6cd97975ef7fcce68ffd9eb4de8357dba6b893d669146f5bf5eeb7c",
      "dd94fcc5047e157a3d11ea96401e761517b3f7f9dd927d3ccce843e37fd46b5b40268fb9"
      "584067fe964e2fbb4f3b834fe357a6d3f1ccc26de6a7279f7bf68b3c"
      "f9b4ad0a5f5efabc0d6d7b08bd9e709a6ab0b5ffc47fb4c145e5dfd7e7df27f02e52",
      ""};
  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 4504U, &nameCaptureInfo);
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
          (const char_T
               *)"/Users/sloke/Documents/classes/Senior Design "
                 "II/iotSensorArray_seniorDesign/waistband/classify_data.m"));
  emlrtSetField(xEntryPoints, 0, (const char_T *)"TimeStamp",
                emlrtMxCreateDoubleScalar(738600.74708333332));
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
