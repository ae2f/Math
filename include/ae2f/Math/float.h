/**
 * @file float.h
 * @brief
 * 2^(`exp`-1) - 1 -> `exp - 1` count of 1's as bits
 */

#ifndef ae2f_Math_float_h
#define ae2f_Math_float_h

#include "./int.h"

#include <ae2f/Pack/Beg.h>

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

typedef enum ae2f_eMathFloatWhich {
  /** @brief NaN */
  ae2f_eMathFloatWhich_NAN = 0b011,
  /** @brief Infinity */
  ae2f_eMathFloatWhich_INF = 0b010,

  /** @brief Number (mantissa) */
  ae2f_eMathFloatWhich_NUM = 0b001,

  /** @brief Number, 1. */
  ae2f_eMathFloatWhich_ONE = 0b001,

  /** @brief 0 */
  ae2f_eMathFloatWhich_NIL = 0b000,

  /** @brief Sign bit */
  ae2f_eMathFloatWhich_SGN = 0b100,
} ae2f_eMathFloatWhich;

typedef unsigned char ae2f_eMathFloatWhich_t;

#endif
