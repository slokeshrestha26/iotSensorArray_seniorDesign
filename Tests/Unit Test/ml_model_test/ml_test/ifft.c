/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ifft.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Mar-2022 14:42:52
 */

/* Include Files */
#include "ifft.h"
#include "FFTImplementationCallback.h"
#include "classify_data_data.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const creal_T x[23400]
 *                creal_T y[23400]
 * Return Type  : void
 */
void ifft(const creal_T x[23400], creal_T y[23400])
{
  static creal_T fv[16384];
  static creal_T fy[16384];
  static creal_T wwc[15599];
  static double costab[8193];
  double sintab[8193];
  double sintabinv[8193];
  double d;
  double d1;
  double im;
  double nt_im;
  double nt_re;
  double twid_im;
  double twid_re;
  int chan;
  int i;
  int iheight;
  int ihi;
  int istart;
  int j;
  int k;
  int nt_re_tmp;
  int rt;
  int xidx;
  bool tst;
  c_FFTImplementationCallback_gen(costab, sintab, sintabinv);
  rt = 0;
  wwc[7799].re = 1.0;
  wwc[7799].im = 0.0;
  for (k = 0; k < 7799; k++) {
    xidx = ((k + 1) << 1) - 1;
    if (15600 - rt <= xidx) {
      rt = (xidx + rt) - 15600;
    } else {
      rt += xidx;
    }
    nt_im = 3.1415926535897931 * (double)rt / 7800.0;
    if (nt_im == 0.0) {
      nt_re = 1.0;
      nt_im = 0.0;
    } else {
      nt_re = cos(nt_im);
      nt_im = sin(nt_im);
    }
    wwc[7798 - k].re = nt_re;
    wwc[7798 - k].im = -nt_im;
  }
  for (k = 7798; k >= 0; k--) {
    wwc[k + 7800] = wwc[7798 - k];
  }
  for (chan = 0; chan < 3; chan++) {
    xidx = chan * 7800;
    for (k = 0; k < 7800; k++) {
      rt = xidx + k;
      twid_re = x[rt].re;
      im = x[rt].im;
      rt = k + 7800 * chan;
      d = wwc[k + 7799].re;
      d1 = wwc[k + 7799].im;
      y[rt].re = d * twid_re + d1 * im;
      y[rt].im = d * im - d1 * twid_re;
    }
    memset(&fy[0], 0, 16384U * sizeof(creal_T));
    rt = 0;
    xidx = 0;
    for (i = 0; i < 7799; i++) {
      fy[rt] = y[i + 7800 * chan];
      rt = 16384;
      tst = true;
      while (tst) {
        rt >>= 1;
        xidx ^= rt;
        tst = ((xidx & rt) == 0);
      }
      rt = xidx;
    }
    fy[rt] = y[7800 * chan + 7799];
    for (i = 0; i <= 16382; i += 2) {
      d = fy[i + 1].re;
      nt_re = d;
      d1 = fy[i + 1].im;
      nt_im = d1;
      twid_re = fy[i].re;
      im = fy[i].im;
      d = twid_re - d;
      fy[i + 1].re = d;
      d1 = im - d1;
      fy[i + 1].im = d1;
      fy[i].re = twid_re + nt_re;
      fy[i].im = im + nt_im;
    }
    rt = 2;
    xidx = 4;
    k = 4096;
    iheight = 16381;
    while (k > 0) {
      for (i = 0; i < iheight; i += xidx) {
        nt_re_tmp = i + rt;
        nt_re = fy[nt_re_tmp].re;
        nt_im = fy[nt_re_tmp].im;
        fy[nt_re_tmp].re = fy[i].re - nt_re;
        fy[nt_re_tmp].im = fy[i].im - nt_im;
        fy[i].re += nt_re;
        fy[i].im += nt_im;
      }
      istart = 1;
      for (j = k; j < 8192; j += k) {
        twid_re = costab[j];
        twid_im = sintab[j];
        i = istart;
        ihi = istart + iheight;
        while (i < ihi) {
          nt_re_tmp = i + rt;
          nt_re = twid_re * fy[nt_re_tmp].re - twid_im * fy[nt_re_tmp].im;
          nt_im = twid_re * fy[nt_re_tmp].im + twid_im * fy[nt_re_tmp].re;
          fy[nt_re_tmp].re = fy[i].re - nt_re;
          fy[nt_re_tmp].im = fy[i].im - nt_im;
          fy[i].re += nt_re;
          fy[i].im += nt_im;
          i += xidx;
        }
        istart++;
      }
      k /= 2;
      rt = xidx;
      xidx += xidx;
      iheight -= rt;
    }
    memset(&fv[0], 0, 16384U * sizeof(creal_T));
    rt = 0;
    xidx = 0;
    for (i = 0; i < 15598; i++) {
      fv[rt] = wwc[i];
      rt = 16384;
      tst = true;
      while (tst) {
        rt >>= 1;
        xidx ^= rt;
        tst = ((xidx & rt) == 0);
      }
      rt = xidx;
    }
    fv[rt] = wwc[15598];
    for (i = 0; i <= 16382; i += 2) {
      d = fv[i + 1].re;
      nt_re = d;
      d1 = fv[i + 1].im;
      nt_im = d1;
      twid_re = fv[i].re;
      im = fv[i].im;
      d = twid_re - d;
      fv[i + 1].re = d;
      d1 = im - d1;
      fv[i + 1].im = d1;
      fv[i].re = twid_re + nt_re;
      fv[i].im = im + nt_im;
    }
    rt = 2;
    xidx = 4;
    k = 4096;
    iheight = 16381;
    while (k > 0) {
      for (i = 0; i < iheight; i += xidx) {
        nt_re_tmp = i + rt;
        nt_re = fv[nt_re_tmp].re;
        nt_im = fv[nt_re_tmp].im;
        fv[nt_re_tmp].re = fv[i].re - nt_re;
        fv[nt_re_tmp].im = fv[i].im - nt_im;
        fv[i].re += nt_re;
        fv[i].im += nt_im;
      }
      istart = 1;
      for (j = k; j < 8192; j += k) {
        twid_re = costab[j];
        twid_im = sintab[j];
        i = istart;
        ihi = istart + iheight;
        while (i < ihi) {
          nt_re_tmp = i + rt;
          nt_re = twid_re * fv[nt_re_tmp].re - twid_im * fv[nt_re_tmp].im;
          nt_im = twid_re * fv[nt_re_tmp].im + twid_im * fv[nt_re_tmp].re;
          fv[nt_re_tmp].re = fv[i].re - nt_re;
          fv[nt_re_tmp].im = fv[i].im - nt_im;
          fv[i].re += nt_re;
          fv[i].im += nt_im;
          i += xidx;
        }
        istart++;
      }
      k /= 2;
      rt = xidx;
      xidx += xidx;
      iheight -= rt;
    }
    for (rt = 0; rt < 16384; rt++) {
      d = fy[rt].re;
      d1 = fy[rt].im;
      twid_re = fv[rt].im;
      twid_im = fv[rt].re;
      im = d * twid_re + d1 * twid_im;
      d = d * twid_im - d1 * twid_re;
      fy[rt].re = d;
      fy[rt].im = im;
    }
    rt = 0;
    xidx = 0;
    for (i = 0; i < 16383; i++) {
      fv[rt] = fy[i];
      rt = 16384;
      tst = true;
      while (tst) {
        rt >>= 1;
        xidx ^= rt;
        tst = ((xidx & rt) == 0);
      }
      rt = xidx;
    }
    fv[rt] = fy[16383];
    for (i = 0; i <= 16382; i += 2) {
      d = fv[i + 1].re;
      nt_re = d;
      d1 = fv[i + 1].im;
      nt_im = d1;
      twid_re = fv[i].re;
      im = fv[i].im;
      d = twid_re - d;
      fv[i + 1].re = d;
      d1 = im - d1;
      fv[i + 1].im = d1;
      fv[i].re = twid_re + nt_re;
      fv[i].im = im + nt_im;
    }
    rt = 2;
    xidx = 4;
    k = 4096;
    iheight = 16381;
    while (k > 0) {
      for (i = 0; i < iheight; i += xidx) {
        nt_re_tmp = i + rt;
        nt_re = fv[nt_re_tmp].re;
        nt_im = fv[nt_re_tmp].im;
        fv[nt_re_tmp].re = fv[i].re - nt_re;
        fv[nt_re_tmp].im = fv[i].im - nt_im;
        fv[i].re += nt_re;
        fv[i].im += nt_im;
      }
      istart = 1;
      for (j = k; j < 8192; j += k) {
        twid_re = costab[j];
        twid_im = sintabinv[j];
        i = istart;
        ihi = istart + iheight;
        while (i < ihi) {
          nt_re_tmp = i + rt;
          nt_re = twid_re * fv[nt_re_tmp].re - twid_im * fv[nt_re_tmp].im;
          nt_im = twid_re * fv[nt_re_tmp].im + twid_im * fv[nt_re_tmp].re;
          fv[nt_re_tmp].re = fv[i].re - nt_re;
          fv[nt_re_tmp].im = fv[i].im - nt_im;
          fv[i].re += nt_re;
          fv[i].im += nt_im;
          i += xidx;
        }
        istart++;
      }
      k /= 2;
      rt = xidx;
      xidx += xidx;
      iheight -= rt;
    }
    for (rt = 0; rt < 16384; rt++) {
      fv[rt].re *= 6.103515625E-5;
      fv[rt].im *= 6.103515625E-5;
    }
    for (k = 0; k < 7800; k++) {
      d = wwc[k + 7799].re;
      d1 = wwc[k + 7799].im;
      twid_re = fv[k + 7799].re;
      twid_im = fv[k + 7799].im;
      nt_re = d * twid_re + d1 * twid_im;
      twid_re = d * twid_im - d1 * twid_re;
      if (twid_re == 0.0) {
        rt = k + 7800 * chan;
        y[rt].re = nt_re / 7800.0;
        y[rt].im = 0.0;
      } else if (nt_re == 0.0) {
        rt = k + 7800 * chan;
        y[rt].re = 0.0;
        y[rt].im = twid_re / 7800.0;
      } else {
        rt = k + 7800 * chan;
        y[rt].re = nt_re / 7800.0;
        y[rt].im = twid_re / 7800.0;
      }
    }
  }
}

/*
 * File trailer for ifft.c
 *
 * [EOF]
 */
