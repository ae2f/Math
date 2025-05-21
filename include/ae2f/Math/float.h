/**
 * @file float.h
 * @brief
 * 2^(`exp`-1) - 1 -> `exp` count of 1's as bits
 */

#ifndef ae2f_Math_float_h
#define ae2f_Math_float_h

#include "./int.h"

#include <ae2f/Pack/Beg.h>

/**
 * @class ae2f_MathFloat
 * @brief
 * This follows IEEE standard.
 */
typedef struct ae2f_MathFloat {
  /** @brief whether has sign or not */
  unsigned sign : 1;

  /** @brief aka stride */
  unsigned bstart : 3;

  /** @brief the size of exponent as bits */
  size_t exp;

  /** @brief the size of mantissa as bits */
  size_t man;
} ae2f_MathFloat;

#define ae2f_MathFloat32_SIGN 1
#define ae2f_MathFloat32_EXP 8
#define ae2f_MathFloat32_MAN 23

#define ae2f_MathFloat64_SIGN 1
#define ae2f_MathFloat64_EXP 11
#define ae2f_MathFloat64_MAN 52

#include <ae2f/Pack/End.h>

#endif
