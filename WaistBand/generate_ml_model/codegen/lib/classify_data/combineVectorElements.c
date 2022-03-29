/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: combineVectorElements.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Mar-2022 13:32:22
 */

/* Include Files */
#include "combineVectorElements.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const double x[23400]
 *                double y[3]
 * Return Type  : void
 */
void combineVectorElements(const double x[23400], double y[3])
{
  double bsum;
  int hi;
  int ib;
  int k;
  int xblockoffset;
  int xi;
  int xpageoffset;
  for (xi = 0; xi < 3; xi++) {
    xpageoffset = xi * 7800;
    bsum = x[xpageoffset];
    for (k = 0; k < 1023; k++) {
      bsum += x[(xpageoffset + k) + 1];
    }
    y[xi] = bsum;
    for (ib = 0; ib < 7; ib++) {
      xblockoffset = xpageoffset + ((ib + 1) << 10);
      bsum = x[xblockoffset];
      if (ib + 2 == 8) {
        hi = 632;
      } else {
        hi = 1024;
      }
      for (k = 2; k <= hi; k++) {
        bsum += x[(xblockoffset + k) - 1];
      }
      y[xi] += bsum;
    }
  }
}

/*
 * File trailer for combineVectorElements.c
 *
 * [EOF]
 */
