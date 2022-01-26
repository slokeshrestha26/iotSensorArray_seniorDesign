/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * classify_data_initialize.c
 *
 * Code generation for function 'classify_data_initialize'
 *
 */

/* Include files */
#include "classify_data_initialize.h"
#include "classify_data.h"
#include "classify_data_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void classify_data_initialize(void)
{
  rt_InitInfAndNaN();
  isInitialized_classify_data = true;
}

/* End of code generation (classify_data_initialize.c) */
