/**
 * @file float.h
 * @brief
 * 2^(`exp`-1) - 1 -> `exp - 1` count of 1's as bits
 */

#ifndef ae2f_Math_float_h
#define ae2f_Math_float_h

#include <ae2f/Pack/Beg.h>
#include <stddef.h>

typedef struct ae2f_MathFloat ae2f_MathFloat;

/**
 * @class ae2f_MathFloat
 * @brief
 * This follows IEEE standard.
 */
struct ae2f_MathFloat {
  /** @brief the size of exponent as bits */
  size_t exp;

  /** @brief the size of mantissa as bits */
  size_t man;

  /** @brief whether has sign or not */
  unsigned sign : 1;

  /** @brief aka stride */
  unsigned bstart : 3;
};

#define ae2f_pMathFloat ae2f_MathFloat *const

#include <ae2f/Pack/End.h>

#define ae2f_MathFloat32_SIGN 1
#define ae2f_MathFloat32_EXP 8
#define ae2f_MathFloat32_MAN 23

#define ae2f_MathFloat64_SIGN 1
#define ae2f_MathFloat64_EXP 11
#define ae2f_MathFloat64_MAN 52


#endif
