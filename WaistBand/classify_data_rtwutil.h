/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: classify_data_rtwutil.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 20-Mar-2022 19:57:03
 */

#ifndef CLASSIFY_DATA_RTWUTIL_H
#define CLASSIFY_DATA_RTWUTIL_H

/* Include Files */
#include "classify_data_types.h"
#include "rtwtypes.h"
#include "omp.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void emlrtFreeThreadStackData(void);

extern classify_dataTLS *emlrtGetThreadStackData(void);

extern void emlrtInitThreadStackData(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for classify_data_rtwutil.h
 *
 * [EOF]
 */
