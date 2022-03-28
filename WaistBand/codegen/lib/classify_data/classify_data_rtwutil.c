/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: classify_data_rtwutil.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 20-Mar-2022 19:57:03
 */

/* Include Files */
#include "classify_data_rtwutil.h"
#include "classify_data_types.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static classify_dataTLS *classify_dataTLSGlobal;
#pragma omp threadprivate(classify_dataTLSGlobal)

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void emlrtFreeThreadStackData(void)
{
  int b;
  int i;
  b = omp_get_max_threads();
#pragma omp parallel for schedule(static) num_threads(omp_get_max_threads())

  for (i = 1; i <= b; i++) {
    free(classify_dataTLSGlobal);
  }
}

/*
 * Arguments    : void
 * Return Type  : classify_dataTLS *
 */
classify_dataTLS *emlrtGetThreadStackData(void)
{
  return classify_dataTLSGlobal;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void emlrtInitThreadStackData(void)
{
  int b;
  int i;
  b = omp_get_max_threads();
#pragma omp parallel for schedule(static) num_threads(omp_get_max_threads())

  for (i = 1; i <= b; i++) {
    classify_dataTLSGlobal =
        (classify_dataTLS *)malloc((size_t)1U * sizeof(classify_dataTLS));
  }
}

/*
 * File trailer for classify_data_rtwutil.c
 *
 * [EOF]
 */
