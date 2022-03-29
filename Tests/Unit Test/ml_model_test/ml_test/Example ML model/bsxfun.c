/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * bsxfun.c
 *
 * Code generation for function 'bsxfun'
 *
 */

/* Include files */
#include "bsxfun.h"
#include "classify_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void bsxfun(const double a_data[], const int a_size[2], const double b_data[],
            const int b_size[2], double c_data[], int c_size[2])
{
  signed char csz_idx_1;
  int acoef;
  int bcoef;
  int i;
  int k;
  if (b_size[1] == 1) {
    csz_idx_1 = (signed char)a_size[1];
  } else if (a_size[1] == 1) {
    csz_idx_1 = (signed char)b_size[1];
  } else if (a_size[1] == b_size[1]) {
    csz_idx_1 = (signed char)a_size[1];
  } else if (b_size[1] < a_size[1]) {
    csz_idx_1 = (signed char)b_size[1];
  } else {
    csz_idx_1 = (signed char)a_size[1];
  }

  c_size[0] = 1;
  if (b_size[1] == 1) {
    c_size[1] = (signed char)a_size[1];
  } else if (a_size[1] == 1) {
    c_size[1] = (signed char)b_size[1];
  } else if (a_size[1] == b_size[1]) {
    c_size[1] = (signed char)a_size[1];
  } else if (b_size[1] < a_size[1]) {
    c_size[1] = (signed char)b_size[1];
  } else {
    c_size[1] = (signed char)a_size[1];
  }

  if (csz_idx_1 != 0) {
    acoef = (a_size[1] != 1);
    bcoef = (b_size[1] != 1);
    i = csz_idx_1 - 1;
    for (k = 0; k <= i; k++) {
      c_data[k] = a_data[acoef * k] / b_data[bcoef * k];
    }
  }
}

/* End of code generation (bsxfun.c) */
