/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * classify_data_types.h
 *
 * Code generation for function 'classify_data_types'
 *
 */

#ifndef CLASSIFY_DATA_TYPES_H
#define CLASSIFY_DATA_TYPES_H

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef enum_c_classreg_learning_coderutils_
#define enum_c_classreg_learning_coderutils_

enum c_classreg_learning_coderutils_
{
  Logit = 0,                           /* Default value */
  Doublelogit,
  Invlogit,
  Ismax,
  Sign,
  Symmetric,
  Symmetricismax,
  Symmetriclogit,
  Identity
};

#endif                                 /*enum_c_classreg_learning_coderutils_*/

#ifndef typedef_c_classreg_learning_coderutils_
#define typedef_c_classreg_learning_coderutils_

typedef enum c_classreg_learning_coderutils_ c_classreg_learning_coderutils_;

#endif                                 /*typedef_c_classreg_learning_coderutils_*/

#ifndef enum_d_classreg_learning_coderutils_
#define enum_d_classreg_learning_coderutils_

enum d_classreg_learning_coderutils_
{
  linear = 1,                          /* Default value */
  gaussian = 2,
  rbf = 2,
  polynomial = 3
};

#endif                                 /*enum_d_classreg_learning_coderutils_*/

#ifndef typedef_d_classreg_learning_coderutils_
#define typedef_d_classreg_learning_coderutils_

typedef enum d_classreg_learning_coderutils_ d_classreg_learning_coderutils_;

#endif                                 /*typedef_d_classreg_learning_coderutils_*/
#endif

/* End of code generation (classify_data_types.h) */
