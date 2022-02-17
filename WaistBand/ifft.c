/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * ifft.c
 *
 * Code generation for function 'ifft'
 *
 */

/* Include files */
#include "ifft.h"
#include "classify_data.h"
#include "fft1.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void ifft(const creal_T x[28800], creal_T y[28800])
{
  static double costab[16385];
  static double sintab[16385];
  double sintabinv[16385];
  int idx;
  int rt;
  static creal_T wwc[19199];
  int k;
  int b_y;
  double nt_im;
  double nt_re;
  generate_twiddle_tables(costab, sintab, sintabinv);
  idx = 9598;
  rt = 0;
  wwc[9599].re = 1.0;
  wwc[9599].im = 0.0;
  for (k = 0; k < 9599; k++) {
    b_y = ((k + 1) << 1) - 1;
    if (19200 - rt <= b_y) {
      rt = (b_y + rt) - 19200;
    } else {
      rt += b_y;
    }

    nt_im = 3.1415926535897931 * (double)rt / 9600.0;
    if (nt_im == 0.0) {
      nt_re = 1.0;
      nt_im = 0.0;
    } else {
      nt_re = cos(nt_im);
      nt_im = sin(nt_im);
    }

    wwc[idx].re = nt_re;
    wwc[idx].im = -nt_im;
    idx--;
  }

  idx = 0;
  for (k = 9598; k >= 0; k--) {
    wwc[k + 9600] = wwc[idx];
    idx++;
  }

  b_bluestein(x, costab, sintab, costab, sintabinv, wwc, y);
}

/* End of code generation (ifft.c) */
