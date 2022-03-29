/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * fft1.c
 *
 * Code generation for function 'fft1'
 *
 */

/* Include files */
#include "fft1.h"
#include "classify_data.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static void b_r2br_r2dit_trig(const creal_T x[32768], const double costab[16385],
  const double sintab[16385], creal_T y[32768]);
static void r2br_r2dit_trig(const creal_T x[19199], const double costab[16385],
  const double sintab[16385], creal_T y[32768]);
static void r2br_r2dit_trig_impl(const creal_T x[28800], int xoffInit, const
  double costab[16385], const double sintab[16385], creal_T y[32768]);

/* Function Definitions */
static void b_r2br_r2dit_trig(const creal_T x[32768], const double costab[16385],
  const double sintab[16385], creal_T y[32768])
{
  int ix;
  int ju;
  int iy;
  int i;
  boolean_T tst;
  double twid_re;
  double temp_re;
  double twid_im;
  int iheight;
  double temp_im;
  double re;
  double im;
  int istart;
  int temp_re_tmp;
  int j;
  int ihi;
  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i < 32767; i++) {
    y[iy] = x[ix];
    iy = 32768;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y[iy] = x[ix];
  for (i = 0; i <= 32766; i += 2) {
    twid_re = y[i + 1].re;
    temp_re = twid_re;
    twid_im = y[i + 1].im;
    temp_im = twid_im;
    re = y[i].re;
    im = y[i].im;
    twid_re = y[i].re - twid_re;
    y[i + 1].re = twid_re;
    twid_im = y[i].im - twid_im;
    y[i + 1].im = twid_im;
    y[i].re = re + temp_re;
    y[i].im = im + temp_im;
  }

  iy = 2;
  ix = 4;
  ju = 8192;
  iheight = 32765;
  while (ju > 0) {
    for (i = 0; i < iheight; i += ix) {
      temp_re_tmp = i + iy;
      temp_re = y[temp_re_tmp].re;
      temp_im = y[temp_re_tmp].im;
      y[temp_re_tmp].re = y[i].re - y[temp_re_tmp].re;
      y[temp_re_tmp].im = y[i].im - y[temp_re_tmp].im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }

    istart = 1;
    for (j = ju; j < 16384; j += ju) {
      twid_re = costab[j];
      twid_im = sintab[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
        temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
        y[temp_re_tmp].re = y[i].re - temp_re;
        y[temp_re_tmp].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    ju /= 2;
    iy = ix;
    ix += ix;
    iheight -= iy;
  }

  for (iy = 0; iy < 32768; iy++) {
    y[iy].re *= 3.0517578125E-5;
    y[iy].im *= 3.0517578125E-5;
  }
}

static void r2br_r2dit_trig(const creal_T x[19199], const double costab[16385],
  const double sintab[16385], creal_T y[32768])
{
  int ix;
  int ju;
  int iy;
  int i;
  boolean_T tst;
  double twid_re;
  double temp_re;
  double twid_im;
  int iheight;
  double temp_im;
  double re;
  double im;
  int istart;
  int temp_re_tmp;
  int j;
  int ihi;
  memset(&y[0], 0, 32768U * sizeof(creal_T));
  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i < 19198; i++) {
    y[iy] = x[ix];
    iy = 32768;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y[iy] = x[ix];
  for (i = 0; i <= 32766; i += 2) {
    twid_re = y[i + 1].re;
    temp_re = twid_re;
    twid_im = y[i + 1].im;
    temp_im = twid_im;
    re = y[i].re;
    im = y[i].im;
    twid_re = y[i].re - twid_re;
    y[i + 1].re = twid_re;
    twid_im = y[i].im - twid_im;
    y[i + 1].im = twid_im;
    y[i].re = re + temp_re;
    y[i].im = im + temp_im;
  }

  iy = 2;
  ix = 4;
  ju = 8192;
  iheight = 32765;
  while (ju > 0) {
    for (i = 0; i < iheight; i += ix) {
      temp_re_tmp = i + iy;
      temp_re = y[temp_re_tmp].re;
      temp_im = y[temp_re_tmp].im;
      y[temp_re_tmp].re = y[i].re - y[temp_re_tmp].re;
      y[temp_re_tmp].im = y[i].im - y[temp_re_tmp].im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }

    istart = 1;
    for (j = ju; j < 16384; j += ju) {
      twid_re = costab[j];
      twid_im = sintab[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
        temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
        y[temp_re_tmp].re = y[i].re - temp_re;
        y[temp_re_tmp].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    ju /= 2;
    iy = ix;
    ix += ix;
    iheight -= iy;
  }
}

static void r2br_r2dit_trig_impl(const creal_T x[28800], int xoffInit, const
  double costab[16385], const double sintab[16385], creal_T y[32768])
{
  int ix;
  int ju;
  int iy;
  int i;
  boolean_T tst;
  double twid_re;
  double temp_re;
  double twid_im;
  int iheight;
  double temp_im;
  double re;
  double im;
  int istart;
  int temp_re_tmp;
  int j;
  int ihi;
  memset(&y[0], 0, 32768U * sizeof(creal_T));
  ix = xoffInit;
  ju = 0;
  iy = 0;
  for (i = 0; i < 9599; i++) {
    y[iy] = x[ix];
    iy = 32768;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y[iy] = x[ix];
  for (i = 0; i <= 32766; i += 2) {
    twid_re = y[i + 1].re;
    temp_re = twid_re;
    twid_im = y[i + 1].im;
    temp_im = twid_im;
    re = y[i].re;
    im = y[i].im;
    twid_re = y[i].re - twid_re;
    y[i + 1].re = twid_re;
    twid_im = y[i].im - twid_im;
    y[i + 1].im = twid_im;
    y[i].re = re + temp_re;
    y[i].im = im + temp_im;
  }

  iy = 2;
  ix = 4;
  ju = 8192;
  iheight = 32765;
  while (ju > 0) {
    for (i = 0; i < iheight; i += ix) {
      temp_re_tmp = i + iy;
      temp_re = y[temp_re_tmp].re;
      temp_im = y[temp_re_tmp].im;
      y[temp_re_tmp].re = y[i].re - y[temp_re_tmp].re;
      y[temp_re_tmp].im = y[i].im - y[temp_re_tmp].im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }

    istart = 1;
    for (j = ju; j < 16384; j += ju) {
      twid_re = costab[j];
      twid_im = sintab[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
        temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
        y[temp_re_tmp].re = y[i].re - temp_re;
        y[temp_re_tmp].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    ju /= 2;
    iy = ix;
    ix += ix;
    iheight -= iy;
  }
}

void b_bluestein(const creal_T x[28800], const double costab[16385], const
                 double sintab[16385], const double costabinv[16385], const
                 double sintabinv[16385], const creal_T wwc[19199], creal_T y
                 [28800])
{
  int chan;
  int yoff;
  int xidx;
  int k;
  static creal_T fv[32768];
  int i;
  static creal_T b_fv[32768];
  double im;
  double d;
  double d1;
  double d2;
  double re;
  for (chan = 0; chan < 3; chan++) {
    yoff = chan * 9600;
    xidx = chan * 9600;
    for (k = 0; k < 9600; k++) {
      i = yoff + k;
      im = wwc[k + 9599].re;
      d = wwc[k + 9599].im;
      y[i].re = im * x[xidx].re + d * x[xidx].im;
      y[i].im = im * x[xidx].im - d * x[xidx].re;
      xidx++;
    }

    r2br_r2dit_trig_impl(y, yoff, costab, sintab, fv);
    r2br_r2dit_trig(wwc, costab, sintab, b_fv);
    for (i = 0; i < 32768; i++) {
      im = fv[i].re * b_fv[i].im + fv[i].im * b_fv[i].re;
      b_fv[i].re = fv[i].re * b_fv[i].re - fv[i].im * b_fv[i].im;
      b_fv[i].im = im;
    }

    b_r2br_r2dit_trig(b_fv, costabinv, sintabinv, fv);
    for (k = 0; k < 9600; k++) {
      im = wwc[k + 9599].re;
      d = wwc[k + 9599].im;
      d1 = fv[k + 9599].re;
      d2 = fv[k + 9599].im;
      re = im * d1 + d * d2;
      im = im * d2 - d * d1;
      y[yoff].re = re;
      y[yoff].im = im;
      y[yoff].re = re;
      y[yoff].im = im;
      if (y[yoff].im == 0.0) {
        re = y[yoff].re / 9600.0;
        im = 0.0;
      } else if (y[yoff].re == 0.0) {
        re = 0.0;
        im = y[yoff].im / 9600.0;
      } else {
        re = y[yoff].re / 9600.0;
        im = y[yoff].im / 9600.0;
      }

      y[yoff].re = re;
      y[yoff].im = im;
      yoff++;
    }
  }
}

void bluestein(const double x[28800], const double costab[16385], const double
               sintab[16385], const double costabinv[16385], const double
               sintabinv[16385], const creal_T wwc[19199], creal_T y[28800])
{
  int chan;
  int yoff;
  int xidx;
  int k;
  static creal_T fv[32768];
  int i;
  static creal_T b_fv[32768];
  double im;
  double d;
  double d1;
  double d2;
  for (chan = 0; chan < 3; chan++) {
    yoff = chan * 9600;
    xidx = chan * 9600;
    for (k = 0; k < 9600; k++) {
      i = yoff + k;
      y[i].re = wwc[k + 9599].re * x[xidx];
      y[i].im = wwc[k + 9599].im * -x[xidx];
      xidx++;
    }

    r2br_r2dit_trig_impl(y, yoff, costab, sintab, fv);
    r2br_r2dit_trig(wwc, costab, sintab, b_fv);
    for (i = 0; i < 32768; i++) {
      im = fv[i].re * b_fv[i].im + fv[i].im * b_fv[i].re;
      b_fv[i].re = fv[i].re * b_fv[i].re - fv[i].im * b_fv[i].im;
      b_fv[i].im = im;
    }

    b_r2br_r2dit_trig(b_fv, costabinv, sintabinv, fv);
    for (k = 0; k < 9600; k++) {
      im = wwc[k + 9599].re;
      d = wwc[k + 9599].im;
      d1 = fv[k + 9599].re;
      d2 = fv[k + 9599].im;
      y[yoff].re = im * d1 + d * d2;
      y[yoff].im = im * d2 - d * d1;
      yoff++;
    }
  }
}

void generate_twiddle_tables(double costab[16385], double sintab[16385], double
  sintabinv[16385])
{
  double costab1q[8193];
  int k;
  double sintabinv_tmp;
  double b_sintabinv_tmp;
  costab1q[0] = 1.0;
  for (k = 0; k < 4096; k++) {
    costab1q[k + 1] = cos(0.00019174759848570515 * ((double)k + 1.0));
  }

  for (k = 0; k < 4095; k++) {
    costab1q[k + 4097] = sin(0.00019174759848570515 * (8192.0 - ((double)k +
      4097.0)));
  }

  costab1q[8192] = 0.0;
  costab[0] = 1.0;
  sintab[0] = 0.0;
  for (k = 0; k < 8192; k++) {
    sintabinv_tmp = costab1q[8191 - k];
    sintabinv[k + 1] = sintabinv_tmp;
    b_sintabinv_tmp = costab1q[k + 1];
    sintabinv[k + 8193] = b_sintabinv_tmp;
    costab[k + 1] = b_sintabinv_tmp;
    sintab[k + 1] = -sintabinv_tmp;
    costab[k + 8193] = -sintabinv_tmp;
    sintab[k + 8193] = -b_sintabinv_tmp;
  }
}

/* End of code generation (fft1.c) */
