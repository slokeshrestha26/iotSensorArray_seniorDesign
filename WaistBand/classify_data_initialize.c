/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: classify_data_initialize.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 20-Mar-2022 19:57:03
 */

/* Include Files */
#include "classify_data_initialize.h"
#include "classify_data_data.h"
#include "classify_data_rtwutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void classify_data_initialize(void)
{
  omp_init_nest_lock(&emlrtNestLockGlobal);
  emlrtInitThreadStackData();
  isInitialized_classify_data = true;
}

/*
 * File trailer for classify_data_initialize.c
 *
 * [EOF]
 */
