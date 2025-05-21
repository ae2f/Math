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

#define __ae2f_MathFloatMan(reterr, af, af_vec, oi, retoivecidx)               \
  if ((reterr) && *(reterr))                                                   \
    ;                                                                          \
  else if (!((af) && (af_vec) && (oi) && (retoivecidx)))                       \
    ((reterr)) && (*(reterr) = ae2f_errGlob_PTR_IS_NULL);                      \
  else {                                                                       \
    (oi)->sign = 0;                                                            \
    (oi)->vecbegpoint = (af)->bstart;                                          \
    (oi)->sz = (af)->man;                                                      \
    *(retoivecidx) = 0;                                                        \
  }

#define __ae2f_MathFloatExp(reterr, af, af_vec, oi, retoivecidx)               \
  if ((reterr) && *(reterr))                                                   \
    ;                                                                          \
  else if (!((af) && (af_vec) && (oi) && (retoivecidx)))                       \
    ((reterr)) && (*(reterr) = ae2f_errGlob_PTR_IS_NULL);                      \
  else {                                                                       \
    (oi)->sign = 0;                                                            \
    (oi)->vecbegpoint = *(retoivecidx) = ((af)->man + (af)->bstart);           \
    (oi)->sz = (af)->exp;                                                      \
    *(retoivecidx) >>= 3;                                                      \
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
 * @param p_ofloatidx
 * # size_t*
 * */
#define __ae2f_MathFloatNxt(err, idx, ifloat_t, ifloat, ofloat_t, p_ofloatidx) \
  if (((err) && *(err)) || !(idx)) {                                           \
  } else if (!((ifloat_t) && (ifloat) && (ofloat_t) && (ofloatidx))) {         \
    (err) && (*err) = ae2f_errGlob_PTR_IS_NULL;                                \
  } else {                                                                     \
    *(ofloat_t) = *(ifloat_t);                                                 \
    (ofloat_t)->bstart =                                                       \
        ((ifloat_t)->bstart + __ae2f_MathFloatElSz(ifloat_t) * (idx));         \
    *(p_ofloatidx) =                                                           \
        ((ifloat_t)->bstart + __ae2f_MathFloatElSz(ifloat_t) * (idx)) >> 3;    \
  }

/**
 * @macro __ae2f_MathFloatCast
 * @brief
 * `ofloat` = `ifloat`;
 * */
static inline void __ae2f_MathFloatCast(ae2f_err_t *err,
                                        const ae2f_MathFloat *ifloat_t,
                                        ae2f_iMathMem ifloat,
                                        const ae2f_MathFloat *ofloat_t,
                                        ae2f_oMathMem ofloat) {
  if ((err) && *(err))
    ;
  else if (!((ifloat_t) && (ifloat) && (ofloat_t) && (ofloat)))
    (err) && (*(err) = ae2f_errGlob_PTR_IS_NULL);
  else {
    struct __ae2f_MathFloatCastVar_t {
      ae2f_MathInt __ifint[1], __ofint[1];
      size_t ifidx, ofidx;
    } __ae2f_MathFloatCastVar;

    /* sign */
    __ae2f_MathFloatSetSign(ofloat_t, ofloat,
                            __ae2f_MathFloatGetSign(ifloat_t, ifloat));

    /* Exponent */
    __ae2f_MathFloatExp(err, ifloat_t, ifloat, __ae2f_MathFloatCastVar.__ifint,
                        &__ae2f_MathFloatCastVar.ifidx);

    *__ae2f_MathFloatCastVar.__ofint = *__ae2f_MathFloatCastVar.__ifint;
    __ae2f_MathFloatCastVar.__ofint[0].sz--;

    __ae2f_MathIntFill(err, __ae2f_MathFloatCastVar.__ofint,
                       __ae2f_MathFloatCastVar.ofidx + (ofloat), 0b1, 1);

    __ae2f_MathIntSub(err, __ae2f_MathFloatCastVar.__ofint,
                      (ofloat) + __ae2f_MathFloatCastVar.ofidx,
                      __ae2f_MathFloatCastVar.__ifint,
                      (ifloat) + __ae2f_MathFloatCastVar.ifidx,
                      __ae2f_MathFloatCastVar.__ofint,
                      (ofloat) + __ae2f_MathFloatCastVar.ofidx);

    /* Man */
    __ae2f_MathFloatMan(err, ifloat_t, ifloat, __ae2f_MathFloatCastVar.__ifint,
                        &__ae2f_MathFloatCastVar.ifidx);
    __ae2f_MathFloatMan(err, ofloat_t, ofloat, __ae2f_MathFloatCastVar.__ofint,
                        &__ae2f_MathFloatCastVar.ofidx);

    __ae2f_MathIntCast(err, __ae2f_MathFloatCastVar.__ifint,
                       (ifloat) + __ae2f_MathFloatCastVar.ifidx,
                       __ae2f_MathFloatCastVar.__ofint,
                       (ofloat) + __ae2f_MathFloatCastVar.ofidx);
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
