/**
 * @file float.h
 * @brief
 * 2^(`exp`-1) - 1 -> `exp - 1` count of 1's as bits
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
  /** @brief the size of exponent as bits */
  size_t exp;

  /** @brief the size of mantissa as bits */
  size_t man;

  /** @brief whether has sign or not */
  unsigned sign : 1;

  /** @brief aka stride */
  unsigned bstart : 3;
} ae2f_MathFloat;

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

/**
 * @brief
 * `ofloat` = `ifloat`;
 * */
ae2f_extern ae2f_SHAREDEXPORT void
ae2f_MathFloatCast(ae2f_err_t *err, const ae2f_MathFloat *ifloat_t,
                   ae2f_iMathMem ifloat, const ae2f_MathFloat *ofloat_t,
                   ae2f_oMathMem ofloat);

/**
 * @brief
 * `ofloat` = -`ifloat`;
 * */
ae2f_extern ae2f_SHAREDEXPORT void ae2f_MathFloatFlip(ae2f_err_t *err,
                                                      const ae2f_MathFloat *_if,
                                                      ae2f_iMathMem _if_vec,
                                                      const ae2f_MathFloat *_of,
                                                      ae2f_oMathMem _of_vec);

ae2f_extern ae2f_SHAREDCALL void
ae2f_MathFloatCheck(ae2f_err_t *err, ae2f_eMathFloatWhich_t *retwhich,
                    ae2f_MathFloat *_af, ae2f_iMathMem _af_vec);

/** @brief Normalise `_if`  */
ae2f_extern ae2f_SHAREDEXPORT void __ae2f_MathFloatNormalise(ae2f_err_t *err,
                                                             ae2f_MathFloat *_if,
                                                             ae2f_bMathMem _if_vec);
#endif
