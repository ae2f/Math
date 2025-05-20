#ifndef ae2f_Math_float_imp_h
#define ae2f_Math_float_imp_h

#include "./float.h"
#include "./int.imp.h"

/**
 * @macro __ae2f_MathFloatGetSign
 * @brief Gets a sign bit
 * @returns bool
 * @param afloat_t
 * # const ae2f_MathFloat*
 * @param afloat
 * # ae2f_iMathMem
 * */
#define __ae2f_MathFloatGetSign(afloat_t, afloat)                              \
  ((afloat) && (afloat_t) && (afloat_t)->sign &&                               \
   ae2f_BitVecGet((((afloat_t)->exp + (afloat_t)->man) >> 3)[afloat],          \
                  (((afloat_t)->exp + (afloat_t)->man) & 7)))

/**
 * @macro __ae2f_MathFloatSetSign
 * @brief Sets a sign bit
 * @returns void
 * @param afloat_t
 * # const ae2f_MathFloat*
 * @param afloat
 * # ae2f_oMathMem
 * */
#define __ae2f_MathFloatSetSign(afloat_t, afloat, _sign_bit)                   \
  ((afloat_t)->sign && (afloat) && (afloat_t)) &&                              \
      ((((afloat_t)->exp + (afloat_t)->man) >> 3)[afloat] = ae2f_BitVecSet(    \
           (((afloat_t)->exp + (afloat_t)->man) >> 3)[afloat],                 \
           (((afloat_t)->exp + (afloat_t)->man) & 7), _sign_bit))

/**
 * @macro __ae2f_MathFloatElSz
 * @brief sizeof(`afloat_t`)
 * @returns size_t
 * @param afloat_t
 * # const ae2f_MathFloat*
 * */
#define __ae2f_MathFloatElSz(afloat_t)                                         \
  ((afloat_t)->sign + (afloat_t)->exp + (afloat_t)->man)

#define __ae2f_MathFloatMan(reterr, af, af_vec, oi, oi_vec_ptr)                \
  if ((reterr) && *(reterr))                                                   \
    ;                                                                          \
  else if (!((af) && (af_vec) && (oi) && (oi_vec_ptr)))                        \
    ((reterr)) && (*(reterr) = ae2f_errGlob_PTR_IS_NULL);                      \
  else {                                                                       \
    (oi)->sign = 0;                                                            \
    (oi)->vecbegpoint = (af)->bstart;                                          \
    (oi)->sz = (af)->man;                                                      \
    *(oi_vec_ptr) = (af_vec);                                                  \
  }

#define __ae2f_MathFloatExp(reterr, af, af_vec, oi, oi_vec_ptr)                \
  if ((reterr) && *(reterr))                                                   \
    ;                                                                          \
  else if (!((af) && (af_vec) && (oi) && (oi_vec_ptr)))                        \
    ((reterr)) && (*(reterr) = ae2f_errGlob_PTR_IS_NULL);                      \
  else {                                                                       \
    (oi)->sign = 0;                                                            \
    (oi)->vecbegpoint = ((af)->man + (af)->bstart);                            \
    (oi)->sz = (af)->exp;                                                      \
    *(oi_vec_ptr) = (af_vec);                                                  \
  }

/**
 * @macro __ae2f_MathFloatNxt
 * @brief
 * `ofloat` = `ifloat` + `idx`;
 * @returns void
 * @param ifloat_t
 * # const ae2f_MathFloat*
 * @param ifloat
 * # ae2f_bMathMem
 * @param ofloat_t
 * # ae2f_MathFloat*
 * @param p_ofloat
 * # typeof(ifloat)*
 * */
#define __ae2f_MathFloatNxt(err, idx, ifloat_t, ifloat, ofloat_t, p_ofloat)    \
  if (((err) && *(err)) || !(idx)) {                                           \
  } else if (!((ifloat_t) && (ifloat) && (ofloat_t) && (ofloat))) {            \
    (err) && (*err) = ae2f_errGlob_PTR_IS_NULL;                                \
  } else {                                                                     \
    *(ofloat_t) = *(ifloat_t);                                                 \
    (ofloat_t)->bstart =                                                       \
        ((ifloat_t)->bstart + __ae2f_MathFloatElSz(ifloat_t) * (idx)) & 7;     \
    *(p_ofloat) = (ifloat) + ((ifloat_t)->bstart +                             \
                              __ae2f_MathFloatElSz(ifloat_t) * (idx)) >>       \
                  3;                                                           \
  }

inline void ae2f_MathFloatCast(ae2f_err_t *err, const ae2f_MathFloat *ifloat_t,
                               ae2f_iMathMem ifloat,
                               const ae2f_MathFloat *ofloat_t,
                               ae2f_oMathMem ofloat) {
  if ((err) && *(err))
    ;
  else if (!((ifloat_t) && (ifloat) && (ofloat_t) && (ofloat)))
    (err) && (*(err) = ae2f_errGlob_PTR_IS_NULL);
  else {
    /* sign */
    __ae2f_MathFloatSetSign(ofloat_t, ofloat,
                            __ae2f_MathFloatGetSign(ifloat_t, ifloat));

    /* Exponent */
  }
}

/**
 * @macro __ae2f_MathIntToFloat
 * `ofloat_t` `ofloat` = `iint`;
 *
 * @param err
 * */
#define __ae2f_MathIntToFloat(err, iint_t, iint, ofloat_t, ofloat)             \
  do {                                                                         \
    if ((err) && *(err)) /* When err is not 0 */                               \
      break;                                                                   \
    if (!((iint_t) && (iint) && (ofloat_t) && (ofloat))) {                     \
      if (err) /* When four are null */                                        \
        *(err) |= ae2f_errGlob_PTR_IS_NULL;                                    \
      break;                                                                   \
    }                                                                          \
  } while (0)

#endif
