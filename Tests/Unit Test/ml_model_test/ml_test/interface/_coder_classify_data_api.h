/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_classify_data_api.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Mar-2022 13:32:22
 */

#ifndef _CODER_CLASSIFY_DATA_API_H
#define _CODER_CLASSIFY_DATA_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
int32_T classify_data(real_T dataAcc[23400], real_T dataHr[3800]);

void classify_data_api(const mxArray *const prhs[2], const mxArray **plhs);

void classify_data_atexit(void);

void classify_data_initialize(void);

void classify_data_terminate(void);

void classify_data_xil_shutdown(void);

void classify_data_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_classify_data_api.h
 *
 * [EOF]
 */
