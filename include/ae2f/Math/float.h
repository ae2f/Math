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
  bool sign : 1;

  /** @brief aka stride */
  size_t bstart : 3;

  /** @brief the size of exponent as bits */
  size_t exp;

  /** @brief the size of mantissa as bits */
  size_t man;
} ae2f_MathFloat;

#include <ae2f/Pack/End.h>

#endif
