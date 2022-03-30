/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: classify_data_internal_types.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Mar-2022 14:42:52
 */

#ifndef CLASSIFY_DATA_INTERNAL_TYPES_H
#define CLASSIFY_DATA_INTERNAL_TYPES_H

/* Include Files */
#include "classify_data_types.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef enum_c_classreg_learning_coderutils_
#define enum_c_classreg_learning_coderutils_
enum c_classreg_learning_coderutils_
{
  Logit = 0, /* Default value */
  Doublelogit,
  Invlogit,
  Ismax,
  Sign,
  Symmetric,
  Symmetricismax,
  Symmetriclogit,
  Identity
};
#endif /* enum_c_classreg_learning_coderutils_ */
#ifndef typedef_c_classreg_learning_coderutils_
#define typedef_c_classreg_learning_coderutils_
typedef enum c_classreg_learning_coderutils_ c_classreg_learning_coderutils_;
#endif /* typedef_c_classreg_learning_coderutils_ */

#ifndef enum_d_classreg_learning_coderutils_
#define enum_d_classreg_learning_coderutils_
enum d_classreg_learning_coderutils_
{
  linear = 1, /* Default value */
  gaussian = 2,
  rbf = 2,
  polynomial = 3
};
#endif /* enum_d_classreg_learning_coderutils_ */
#ifndef typedef_d_classreg_learning_coderutils_
#define typedef_d_classreg_learning_coderutils_
typedef enum d_classreg_learning_coderutils_ d_classreg_learning_coderutils_;
#endif /* typedef_d_classreg_learning_coderutils_ */

#endif
/*
 * File trailer for classify_data_internal_types.h
 *
 * [EOF]
 */
