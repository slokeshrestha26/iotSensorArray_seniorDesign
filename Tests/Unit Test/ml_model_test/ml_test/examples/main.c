/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Mar-2022 14:42:52
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include Files */
#include "main.h"
#include "classify_data.h"
#include "classify_data_terminate.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void argInit_300x1_real_T(double result[300]);

static void argInit_7800x3_real_T(double result[23400]);

static double argInit_real_T(void);

static void main_classify_data(void);

/* Function Definitions */
/*
 * Arguments    : double result[300]
 * Return Type  : void
 */
static void argInit_300x1_real_T(double result[300])
{
  int idx0;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 300; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

/*
 * Arguments    : double result[23400]
 * Return Type  : void
 */
static void argInit_7800x3_real_T(double result[23400])
{
  int idx0;
  int idx1;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 7800; idx0++) {
    for (idx1 = 0; idx1 < 3; idx1++) {
      /* Set the value of the array element.
Change this value to the value that the application requires. */
      result[idx0 + 7800 * idx1] = argInit_real_T();
    }
  }
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_classify_data(void)
{
  static double b_dv[23400];
  double b_dv1[300];
  int pred;
  /* Initialize function 'classify_data' input arguments. */
  /* Initialize function input argument 'dataAcc'. */
  /* Initialize function input argument 'dataHr'. */
  /* Call the entry-point 'classify_data'. */
  argInit_7800x3_real_T(b_dv);
  argInit_300x1_real_T(b_dv1);
  pred = classify_data(b_dv, b_dv1);
}

/*
 * Arguments    : int argc
 *                char **argv
 * Return Type  : int
 */
int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* The initialize function is being called automatically from your entry-point
   * function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_classify_data();
  /* Terminate the application.
You do not need to do this more than one time. */
  classify_data_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
