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
    (oi)->sz = (af)->exp - 1;                                                  \
    *(retoivecidx) >>= 3;                                                      \
  }

#define __ae2f_MathFloatExpEndIdx(af) ((af)->man + (af)->exp + (af)->bstart - 1)

#define __ae2f_MathFloatExpGetSign(af, af_vec)                                 \
  ((af) && (af_vec)                                                            \
       ? (ae2f_BitVecGet((af_vec)[__ae2f_MathFloatExpEndIdx(af) >> 3],         \
                         (__ae2f_MathFloatExpEndIdx(af) & 7)))                 \
       : 0)

#define __ae2f_MathFloatExpSetSign(af, af_vec, mask)                           \
  ((af) && (af_vec)                                                            \
       ? ((af_vec)[__ae2f_MathFloatExpEndIdx(af) >> 3] =                       \
              (ae2f_BitVecSet((af_vec)[__ae2f_MathFloatExpEndIdx(af) >> 3],    \
                              (__ae2f_MathFloatExpEndIdx(af) & 7), mask)))     \
       : 0)

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
    (ofloat_t)->bstart = *(p_ofloatidx) =                                      \
        ((ifloat_t)->bstart + __ae2f_MathFloatElSz(ifloat_t) * (idx));         \
    *(p_ofloatidx) >>= 3;                                                      \
  }

/**
 * @macro __ae2f_MathFloatCast
 * @brief `ofloat` = `ifloat`;
 *
 * @param err 		{ae2f_err_t*}
 * @param ifloat_t	{const ae2f_MathFloat*}
 * @param ifloat	{ae2f_iMathMem}
 * @param ofloat_t	{const ae2f_MathFloat*}
 * @param ofloat	{ae2f_oMathMem}
 * */
#define __ae2f_MathFloatCast(err, ifloat_t, ifloat, ofloat_t, ofloat)          \
  {                                                                            \
    if ((err) && *(err))                                                       \
      ;                                                                        \
    else if (!((ifloat_t) && (ifloat) && (ofloat_t) && (ofloat)))              \
      (err) && (*(err) = ae2f_errGlob_PTR_IS_NULL);                            \
    else {                                                                     \
      struct __ae2f_MathFloatCastVar_t {                                       \
        size_t c1, c2;                                                         \
        ae2f_MathUtilDiv8(size_t) odiv, idiv, idx;                             \
        unsigned sign : 1;                                                     \
      } __ae2f_MathFloatCastVar;                                               \
                                                                               \
      /* sign */                                                               \
      __ae2f_MathFloatSetSign(ofloat_t, ofloat,                                \
                              __ae2f_MathFloatGetSign(ifloat_t, ifloat));      \
                                                                               \
      /* exp */                                                                \
      __ae2f_MathFloatCastVar.idx.p = 0;                                       \
      __ae2f_MathFloatCastVar.c1 = (ifloat_t)->exp - 1;                        \
      __ae2f_MathFloatCastVar.c2 = (ofloat_t)->exp - 1;                        \
                                                                               \
      __ae2f_MathFloatCastVar.idiv.p = (ifloat_t)->bstart + (ifloat_t)->man;   \
      __ae2f_MathFloatCastVar.odiv.p = (ofloat_t)->bstart + (ofloat_t)->man;   \
                                                                               \
      for (; __ae2f_MathFloatCastVar.idx.p < __ae2f_MathFloatCastVar.c2;       \
           __ae2f_MathFloatCastVar.idx.p++) {                                  \
                                                                               \
        ((ofloat)[__ae2f_MathFloatCastVar.odiv.b.q]) = ae2f_BitVecSet(         \
            (ofloat)[__ae2f_MathFloatCastVar.odiv.b.q],                        \
            __ae2f_MathFloatCastVar.odiv.b.r,                                  \
            (__ae2f_MathFloatCastVar.idx.p < __ae2f_MathFloatCastVar.c1        \
                 ? (__ae2f_MathFloatCastVar.sign = (ae2f_BitVecGet(            \
                        (ifloat)[__ae2f_MathFloatCastVar.idiv.b.q],            \
                        __ae2f_MathFloatCastVar.idiv.b.r)))                    \
                 : __ae2f_MathFloatCastVar.sign));                             \
        __ae2f_MathFloatCastVar.idiv.p++;                                      \
        __ae2f_MathFloatCastVar.odiv.p++;                                      \
      }                                                                        \
                                                                               \
      __ae2f_MathFloatCastVar.odiv.b.r =                                       \
          __ae2f_MathFloatExpGetSign(ifloat_t, ifloat);                        \
                                                                               \
      __ae2f_MathFloatExpSetSign(ofloat_t, ofloat,                             \
                                 __ae2f_MathFloatCastVar.odiv.b.r);            \
      /* fraction */                                                           \
      __ae2f_MathFloatCastVar.idx.p = 0;                                       \
      __ae2f_MathFloatCastVar.c1 = __ae2f_MathFloatCastVar.idiv.p =            \
          (ifloat_t)->man - 1;                                                 \
      __ae2f_MathFloatCastVar.c2 = __ae2f_MathFloatCastVar.odiv.p =            \
          (ofloat_t)->man - 1;                                                 \
                                                                               \
      __ae2f_MathFloatCastVar.idiv.p += (ifloat_t)->bstart;                    \
      __ae2f_MathFloatCastVar.odiv.p += (ofloat_t)->bstart;                    \
                                                                               \
      for (; __ae2f_MathFloatCastVar.idx.p < __ae2f_MathFloatCastVar.c2;       \
           __ae2f_MathFloatCastVar.idx.p++) {                                  \
        if (__ae2f_MathFloatCastVar.idiv.p != (ifloat_t)->bstart - 1) {        \
          (ofloat)[__ae2f_MathFloatCastVar.odiv.b.q] = ae2f_BitVecSet(         \
              (ofloat)[__ae2f_MathFloatCastVar.odiv.b.q],                      \
              __ae2f_MathFloatCastVar.odiv.b.r,                                \
              (ae2f_BitVecGet((ifloat)[__ae2f_MathFloatCastVar.idiv.b.q],      \
                              __ae2f_MathFloatCastVar.idiv.b.r)));             \
          __ae2f_MathFloatCastVar.idiv.p--;                                    \
        } else {                                                               \
          (ofloat)[__ae2f_MathFloatCastVar.odiv.b.q] =                         \
              ae2f_BitVecSet((ofloat)[__ae2f_MathFloatCastVar.odiv.b.q],       \
                             __ae2f_MathFloatCastVar.odiv.b.r, 0);             \
        }                                                                      \
        __ae2f_MathFloatCastVar.odiv.p--;                                      \
        /* if (__ae2f_MathFloatCastVar.idiv.p == (ifloat_t)->bstart - 1)       \
          __ae2f_MathFloatCastVar.idiv.p += __ae2f_MathFloatCastVar.c1 - 1; */ \
      }                                                                        \
    }                                                                          \
  }

/**
 * @macro __ae2f_MathFloatCast
 * @brief
 * `ofloat` = `ifloat`;
 * */
static inline void ae2f_MathFloatCast(ae2f_err_t *err,
                                      const ae2f_MathFloat *ifloat_t,
                                      ae2f_iMathMem ifloat,
                                      const ae2f_MathFloat *ofloat_t,
                                      ae2f_oMathMem ofloat);

#endif
