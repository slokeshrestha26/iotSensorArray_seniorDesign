/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: classify_data_types.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 20-Mar-2022 19:57:03
 */

#ifndef CLASSIFY_DATA_TYPES_H
#define CLASSIFY_DATA_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_classify_dataTLS
#define typedef_classify_dataTLS
typedef struct {
  union {
    struct {
      creal_T fy[16384];
      creal_T fv[16384];
    } f0;
    struct {
      creal_T fy[8192];
      creal_T fv[8192];
      double costab[7801];
      double sintab[7801];
      creal_T reconVar1[3900];
      creal_T ytmp[3900];
      creal_T reconVar2[3900];
    } f1;
  } u1;
} classify_dataTLS;
#endif /* typedef_classify_dataTLS */

#endif
/*
 * File trailer for classify_data_types.h
 *
 * [EOF]
 */
