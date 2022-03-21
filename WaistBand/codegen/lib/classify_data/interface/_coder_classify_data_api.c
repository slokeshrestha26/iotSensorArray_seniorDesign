/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_classify_data_api.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 20-Mar-2022 19:57:03
 */

/* Include Files */
#include "_coder_classify_data_api.h"
#include "_coder_classify_data_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;

emlrtContext emlrtContextGlobal = {
    true,                                                 /* bFirstTime */
    false,                                                /* bInitialized */
    131610U,                                              /* fVersionInfo */
    NULL,                                                 /* fErrorFunction */
    "classify_data",                                      /* fFunctionName */
    NULL,                                                 /* fRTCallStack */
    false,                                                /* bDebugMode */
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, /* fSigWrd */
    NULL                                                  /* fSigMem */
};

/* Function Declarations */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[23400];

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *dataHr,
                                   const char_T *identifier))[300];

static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[300];

static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[23400];

static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *dataAcc,
                                 const char_T *identifier))[23400];

static const mxArray *emlrt_marshallOut(const int32_T u);

static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[300];

/* Function Definitions */
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[23400]
 */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[23400]
{
  real_T(*y)[23400];
  y = e_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *dataHr
 *                const char_T *identifier
 * Return Type  : real_T (*)[300]
 */
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *dataHr,
                                   const char_T *identifier))[300]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[300];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(dataHr), &thisId);
  emlrtDestroyArray(&dataHr);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[300]
 */
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[300]
{
  real_T(*y)[300];
  y = f_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[23400]
 */
static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[23400]
{
  static const int32_T dims[2] = {7800, 3};
  real_T(*ret)[23400];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  ret = (real_T(*)[23400])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *dataAcc
 *                const char_T *identifier
 * Return Type  : real_T (*)[23400]
 */
static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *dataAcc,
                                 const char_T *identifier))[23400]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[23400];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(dataAcc), &thisId);
  emlrtDestroyArray(&dataAcc);
  return y;
}

/*
 * Arguments    : const int32_T u
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const int32_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *(int32_T *)emlrtMxGetData(m) = u;
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[300]
 */
static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[300]
{
  static const int32_T dims = 300;
  real_T(*ret)[300];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 1U, (void *)&dims);
  ret = (real_T(*)[300])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const mxArray * const prhs[2]
 *                const mxArray **plhs
 * Return Type  : void
 */
void classify_data_api(const mxArray *const prhs[2], const mxArray **plhs)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  real_T(*dataAcc)[23400];
  real_T(*dataHr)[300];
  int32_T pred;
  st.tls = emlrtRootTLSGlobal;
  /* Marshall function inputs */
  dataAcc = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "dataAcc");
  dataHr = c_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "dataHr");
  /* Invoke the target function */
  pred = classify_data(*dataAcc, *dataHr);
  /* Marshall function outputs */
  *plhs = emlrt_marshallOut(pred);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void classify_data_atexit(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  classify_data_xil_terminate();
  classify_data_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void classify_data_initialize(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void classify_data_terminate(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_classify_data_api.c
 *
 * [EOF]
 */
