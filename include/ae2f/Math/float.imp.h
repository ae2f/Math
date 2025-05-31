#ifndef ae2f_Math_float_imp_h
#define ae2f_Math_float_imp_h

#include "./float.h"
#include "./int.imp.h"

/**
 * @def __ae2f_MathFloatGetSign
 * @brief Gets a sign bit
 * @returns bool
 * @param afloat_t
 * # const ae2f_MathFloat*
 * @param afloat
 * # ae2f_iMathMem
 * */
#define __ae2f_MathFloatGetSign(afloat_t, afloat)                              \
  ((afloat) && (afloat_t) && (afloat_t)->sign &&                               \
   __ae2f_MathUtilBVGetArr(afloat, (((afloat_t)->exp + (afloat_t)->man))))

/**
 * @def __ae2f_MathFloatSetSign
 * @brief Sets a sign bit
 * @param afloat_t
 * # const ae2f_MathFloat*
 * @param afloat
 * # ae2f_oMathMem
 * */
#define __ae2f_MathFloatSetSign(afloat_t, afloat, _sign_bit)                   \
  ((afloat) && (afloat_t) && (afloat_t)->sign &&                               \
   __ae2f_MathUtilBVSetAssignArr(afloat, ((afloat_t)->exp + (afloat_t)->man),  \
                                 (_sign_bit)))

/**
 * @def __ae2f_MathFloatFlipSign
 * @brief Flips a sign bit
 * @param afloat_t 	{const ae2f_MathFloat*}
 * @param afloat	{ae2f_oMathMem}
 * */
#define __ae2f_MathFloatFlipSign(afloat_t, afloat)                             \
  __ae2f_MathFloatSetSign(afloat_t, afloat,                                    \
                          !__ae2f_MathFloatGetSign(afloat_t, afloat))

/**
 * @def __ae2f_MathFloatElSz
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
       ? (__ae2f_MathUtilBVGetArr((af_vec), (__ae2f_MathFloatExpEndIdx(af))))  \
       : 0)

#define __ae2f_MathFloatExpSetSign(af, af_vec, mask)                           \
  ((af) && (af_vec) ? __ae2f_MathUtilBVSetAssignArr(                           \
                          (af_vec), (__ae2f_MathFloatExpEndIdx(af)), !!(mask)) \
                    : 0)

/**
 * @def __ae2f_MathFloatNxt
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
 * @def __ae2f_MathFloatCast
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
      __ae2f_MathFloatCastVar.sign =                                           \
          __ae2f_MathFloatGetSign(ifloat_t, ifloat);                           \
      /* sign */                                                               \
      __ae2f_MathFloatSetSign(ofloat_t, ofloat, __ae2f_MathFloatCastVar.sign); \
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
        if (__ae2f_MathFloatCastVar.idx.p < __ae2f_MathFloatCastVar.c1) {      \
          __ae2f_MathFloatCastVar.sign = (__ae2f_MathUtilBVGet(                \
              (ifloat)[__ae2f_MathFloatCastVar.idiv.b.q],                      \
              __ae2f_MathFloatCastVar.idiv.b.r));                              \
        }                                                                      \
                                                                               \
        __ae2f_MathUtilBVSetAssign((ofloat)[__ae2f_MathFloatCastVar.odiv.b.q], \
                                   __ae2f_MathFloatCastVar.odiv.b.r,           \
                                   __ae2f_MathFloatCastVar.sign);              \
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
          __ae2f_MathUtilBVSetAssign(                                          \
              (ofloat)[__ae2f_MathFloatCastVar.odiv.b.q],                      \
              __ae2f_MathFloatCastVar.odiv.b.r,                                \
              (__ae2f_MathUtilBVGet(                                           \
                  (ifloat)[__ae2f_MathFloatCastVar.idiv.b.q],                  \
                  __ae2f_MathFloatCastVar.idiv.b.r)));                         \
          __ae2f_MathFloatCastVar.idiv.p--;                                    \
        } else {                                                               \
          __ae2f_MathUtilBVSetAssign(                                          \
              (ofloat)[__ae2f_MathFloatCastVar.odiv.b.q],                      \
              __ae2f_MathFloatCastVar.odiv.b.r, 0);                            \
        }                                                                      \
        __ae2f_MathFloatCastVar.odiv.p--;                                      \
      }                                                                        \
    }                                                                          \
  }

/**
 * @def __ae2f_MathFloatCast
 * @brief `ofloat` = -`ifloat`;
 *
 * @param err 		{ae2f_err_t*}
 * @param _if		{const ae2f_MathFloat*}
 * @param _if_vec	{ae2f_iMathMem}
 * @param _of		{const ae2f_MathFloat*}
 * @param _of_vec	{ae2f_oMathMem}
 * */
#define __ae2f_MathFloatFlip(err, _if, _if_vec, _of, _of_vec)                  \
  __ae2f_MathFloatCast(err, _if, _if_vec, _of, _of_vec);                       \
  __ae2f_MathFloatFlipSign(_of, _of_vec);

/**
 * @def			__ae2f_MathFloatMkWhich
 * @param err		{ae2f_err_t*}
 * @param _of		{const ae2f_MathFloat*}
 * @param _of_vec	{ae2f_oMathMem}
 * @param which		{ae2f_eMathFloatWhich_t}
 * */
#define __ae2f_MathFloatMkWhich(err, _of, _of_vec, which)                      \
  if ((err) && (*err))                                                         \
    ;                                                                          \
  if (!((_of) && (_of_vec)))                                                   \
    (err) && (*(err) = ae2f_errGlob_PTR_IS_NULL);                              \
  else {                                                                       \
    struct __ae2f_MathFloatCastNanVar_t {                                      \
      size_t c, beg, end;                                                      \
      ae2f_MathUtilDiv8(size_t) i;                                             \
    } __ae2f_MathFloatCastNanVar;                                              \
    __ae2f_MathFloatCastNanVar.i.p = __ae2f_MathFloatCastNanVar.c =            \
        __ae2f_MathFloatCastNanVar.beg = __ae2f_MathFloatCastNanVar.end =      \
            (_of)->bstart;                                                     \
    __ae2f_MathFloatCastNanVar.beg = __ae2f_MathFloatCastNanVar.end =          \
        __ae2f_MathFloatCastNanVar.beg + (_of)->man;                           \
    for (; __ae2f_MathFloatCastNanVar.i.p < __ae2f_MathFloatCastNanVar.c;      \
         __ae2f_MathFloatCastNanVar.i.p++) {                                   \
      __ae2f_MathUtilBVSetAssign(                                              \
          (_of_vec)[__ae2f_MathFloatCastNanVar.i.b.q],                         \
          __ae2f_MathFloatCastNanVar.i.b.r,                                    \
          (__ae2f_MathFloatCastNanVar.i.p < __ae2f_MathFloatCastNanVar.end &&  \
           __ae2f_MathFloatCastNanVar.beg < __ae2f_MathFloatCastNanVar.i.p) && \
              ((which) & ae2f_eMathFloatWhich_INF));                           \
      __ae2f_MathFloatSetSign(_of, _of_vec,                                    \
                              (which) & ae2f_eMathFloatWhich_SGN);             \
      *(_of_vec) |= (which) & ae2f_eMathFloatWhich_ONE;                        \
    }                                                                          \
  }

/**
 * @def __ae2f_MathFloatInf
 * @brief
 * `_of` = 0;
 *
 * @param err		{ae2f_err_t*}
 * @param _of		{const ae2f_MathFloat*}
 * @param _of_vec	{ae2f_oMathMem}
 * */
#define __ae2f_MathFloatZero(err, _of, _of_vec)                                \
  __ae2f_MathFloatMkWhich(err, _of, _of_vec, ae2f_eMathFloatWhich_NIL)

/**
 * @def __ae2f_MathFloatInf
 * @brief
 * `_of` = inf;
 *
 * @param err		{ae2f_err_t*}
 * @param _of		{const ae2f_MathFloat*}
 * @param _of_vec	{ae2f_oMathMem}
 * */
#define __ae2f_MathFloatInf(err, _of, _of_vec)                                 \
  __ae2f_MathFloatMkWhich(err, _of, _of_vec, ae2f_eMathFloatWhich_INF)

/**
 * @def __ae2f_MathFloatNaN
 * @brief
 * `_of` = nan;
 *
 * @param err		{ae2f_err_t*}
 * @param _of		{const ae2f_MathInt*}
 * @param _of_vec	{ae2f_oMathMem}
 * */
#define __ae2f_MathFloatNaN(err, _of, _of_vec)                                 \
  __ae2f_MathFloatMkWhich(err, _of, _of_vec, ae2f_eMathFloatWhich_NAN)

/**
 * @def __ae2f_MathFloatGetWhich
 * @param err		{ae2f_err_t*}
 * @param _af		{const ae2f_MathFloat*}
 * @param _af_vec	{ae2f_iMathMem}
 * @param retwhich	{ae2f_eMathFloatWhich_t*}
 * */
#define __ae2f_MathFloatGetWhich(err, _af, _af_vec, retwhich)                  \
  {                                                                            \
    if ((err) && *(err))                                                       \
      ;                                                                        \
    else if (!(retwhich))                                                      \
      ;                                                                        \
    else if (!((_af) && (_af_vec)))                                            \
      (err) && (*(err) = ae2f_errGlob_PTR_IS_NULL);                            \
    else {                                                                     \
      struct __ae2f_MathFloatCheckVar_t {                                      \
        size_t i;                                                              \
        ae2f_MathUtilDiv8(size_t) ii;                                          \
        __ae2f_MathUtilFlag2(3, unsigned _2 : 1;) flags;                       \
      } __ae2f_MathFloatCheckVar;                                              \
                                                                               \
      __ae2f_MathFloatCheckVar.flags.b._0 = 0; /** num */                      \
      __ae2f_MathFloatCheckVar.flags.b._1 = 1; /** inf */                      \
      __ae2f_MathFloatCheckVar.flags.b._2 =                                    \
          __ae2f_MathFloatGetSign(_af, _af_vec); /** sign */                   \
                                                                               \
      __ae2f_MathFloatCheckVar.ii.p = (_af)->bstart;                           \
      for (__ae2f_MathFloatCheckVar.i = 0;                                     \
           __ae2f_MathFloatCheckVar.i < (_af)->man;                            \
           __ae2f_MathFloatCheckVar.i++, __ae2f_MathFloatCheckVar.ii.p++)      \
        if (__ae2f_MathUtilBVGet((_af_vec)[__ae2f_MathFloatCheckVar.ii.b.q],   \
                                 __ae2f_MathFloatCheckVar.ii.b.r)) {           \
          __ae2f_MathFloatCheckVar.flags.b._0 = 1;                             \
          break;                                                               \
        }                                                                      \
                                                                               \
      for (; __ae2f_MathFloatCheckVar.i < (_af)->exp;                          \
           __ae2f_MathFloatCheckVar.i++, __ae2f_MathFloatCheckVar.ii.p++)      \
        if (!__ae2f_MathUtilBVGet((_af_vec)[__ae2f_MathFloatCheckVar.ii.b.q],  \
                                  __ae2f_MathFloatCheckVar.ii.b.r)) {          \
          __ae2f_MathFloatCheckVar.flags.b._1 = 0;                             \
          break;                                                               \
        }                                                                      \
                                                                               \
      *(retwhich) |= __ae2f_MathFloatCheckVar.flags.a;                         \
    }                                                                          \
  }

/**
 * @def __ae2f_MathFloatNormalise
 * @brief
 * Normalise `_if`.
 *
 * @param err       {ae2f_err_t*}
 * @param _if       {ae2f_MathFloat*}
 * @param _if_vec   {ae2f_bMathMem}
 */
#define __ae2f_MathFloatNormalise(err, _if, _if_vec)                           \
  {                                                                            \
    struct __ae2f_MathFloatNormaliseVar_t {                                    \
      size_t i, shift;                                                         \
      ae2f_MathUtilDiv8(size_t) div, src_div, dst_div, exp_div;                \
      ae2f_eMathFloatWhich_t which;                                            \
    } __ae2f_MathFloatNormaliseVar;                                            \
                                                                               \
    /* Check for special cases */                                              \
    __ae2f_MathFloatNormaliseVar.which = 0;                                    \
    __ae2f_MathFloatGetWhich(err, _if, _if_vec,                                \
                             &__ae2f_MathFloatNormaliseVar.which);             \
                                                                               \
    if ((err) && *(err))                                                       \
      ;                                                                        \
    else if (!((_if) && (_if_vec))) {                                          \
      if (err)                                                                 \
        (*err) = ae2f_errGlob_PTR_IS_NULL;                                     \
      ;                                                                        \
    } else if (__ae2f_MathFloatNormaliseVar.which &                            \
               (ae2f_eMathFloatWhich_NAN | ae2f_eMathFloatWhich_INF |          \
                ae2f_eMathFloatWhich_NIL)) {                                   \
      ; /* No normalization needed for special cases */                        \
    } else {                                                                   \
      /* Find the position of the most significant 1 bit in the mantissa */    \
      __ae2f_MathFloatNormaliseVar.shift = 0;                                  \
      __ae2f_MathFloatNormaliseVar.div.p = (_if)->bstart;                      \
                                                                               \
      /* Search for the first 1 bit in the mantissa */                         \
      for (__ae2f_MathFloatNormaliseVar.i = 0;                                 \
           __ae2f_MathFloatNormaliseVar.i < (_if)->man;                        \
           __ae2f_MathFloatNormaliseVar.i++,                                   \
          __ae2f_MathFloatNormaliseVar.div.p++) {                              \
        if (__ae2f_MathUtilBVGet(                                              \
                (_if_vec)[__ae2f_MathFloatNormaliseVar.div.b.q],               \
                __ae2f_MathFloatNormaliseVar.div.b.r)) {                       \
          break;                                                               \
        }                                                                      \
        __ae2f_MathFloatNormaliseVar.shift++;                                  \
      }                                                                        \
      /* If no 1 bit found, the number is zero */                              \
      if (__ae2f_MathFloatNormaliseVar.shift == (_if)->man) {                  \
        __ae2f_MathFloatZero(err, _if, _if_vec);                               \
        ;                                                                      \
      } else {                                                                 \
                                                                               \
        /* Shift the mantissa left by 'shift' positions */                     \
        if (__ae2f_MathFloatNormaliseVar.shift > 0) {                          \
          /* Shift the mantissa */                                             \
          for (__ae2f_MathFloatNormaliseVar.i = 0;                             \
               __ae2f_MathFloatNormaliseVar.i <                                \
               (_if)->man - __ae2f_MathFloatNormaliseVar.shift;                \
               __ae2f_MathFloatNormaliseVar.i++) {                             \
            __ae2f_MathFloatNormaliseVar.src_div.p =                           \
                (_if)->bstart + __ae2f_MathFloatNormaliseVar.i +               \
                __ae2f_MathFloatNormaliseVar.shift;                            \
            __ae2f_MathFloatNormaliseVar.dst_div.p =                           \
                (_if)->bstart + __ae2f_MathFloatNormaliseVar.i;                \
                                                                               \
            __ae2f_MathUtilBVSetAssign(                                        \
                (_if_vec)[__ae2f_MathFloatNormaliseVar.dst_div.b.q],           \
                __ae2f_MathFloatNormaliseVar.dst_div.b.r,                      \
                __ae2f_MathUtilBVGet(                                          \
                    (_if_vec)[__ae2f_MathFloatNormaliseVar.src_div.b.q],       \
                    __ae2f_MathFloatNormaliseVar.src_div.b.r));                \
          }                                                                    \
                                                                               \
          /* Clear the remaining bits */                                       \
          for (__ae2f_MathFloatNormaliseVar.i =                                \
                   (_if)->man - __ae2f_MathFloatNormaliseVar.shift;            \
               __ae2f_MathFloatNormaliseVar.i < (_if)->man;                    \
               __ae2f_MathFloatNormaliseVar.i++) {                             \
            __ae2f_MathFloatNormaliseVar.div.p =                               \
                (_if)->bstart + __ae2f_MathFloatNormaliseVar.i;                \
            __ae2f_MathUtilBVSetAssign(                                        \
                (_if_vec)[__ae2f_MathFloatNormaliseVar.div.b.q],               \
                __ae2f_MathFloatNormaliseVar.div.b.r, 0);                      \
          }                                                                    \
                                                                               \
          /* Adjust the exponent */                                            \
          __ae2f_MathFloatNormaliseVar.exp_div.p = (_if)->bstart + (_if)->man; \
                                                                               \
          /* Subtract shift from exponent */                                   \
          for (__ae2f_MathFloatNormaliseVar.i = 0;                             \
               __ae2f_MathFloatNormaliseVar.i < (_if)->exp - 1;                \
               __ae2f_MathFloatNormaliseVar.i++,                               \
              __ae2f_MathFloatNormaliseVar.exp_div.p++) {                      \
            if (__ae2f_MathFloatNormaliseVar.shift > 0) {                      \
              if (__ae2f_MathUtilBVGet(                                        \
                      (_if_vec)[__ae2f_MathFloatNormaliseVar.exp_div.b.q],     \
                      __ae2f_MathFloatNormaliseVar.exp_div.b.r)) {             \
                __ae2f_MathUtilBVSetAssign(                                    \
                    (_if_vec)[__ae2f_MathFloatNormaliseVar.exp_div.b.q],       \
                    __ae2f_MathFloatNormaliseVar.exp_div.b.r, 0);              \
                __ae2f_MathFloatNormaliseVar.shift--;                          \
              }                                                                \
            }                                                                  \
          }                                                                    \
        }                                                                      \
      }                                                                        \
    }                                                                          \
  }

/**
 * @brief
 * `_of` = `_af` + `_bf`;
 *
 * @param err		{ae2f_err_t*}
 * @param _af		{const ae2f_MathFloat*}
 * @param _af_vec	{ae2f_iMathMem}
 * @param _bf		{const ae2f_MathFloat*}
 * @param _bf_vec	{ae2f_iMathMem}
 * @param _of		{const ae2f_MathFloat*}
 * @param _of_vec	{ae2f_oMathMem}
 * */
static inline void
__ae2f_MathFloatAdd(ae2f_err_t *err, const ae2f_MathFloat *_af,
                    ae2f_iMathMem _af_vec, const ae2f_MathFloat *_bf,
                    ae2f_iMathMem _bf_vec, const ae2f_MathFloat *_of,
                    ae2f_oMathMem _of_vec) {
  ae2f_eMathFloatWhich_t whicha, whichb;
  ae2f_MathInt inta, intb;
  size_t intaidx = 0, intbidx = 0;

  whicha = whichb = 0;

  if ((err) && *(err))
    ;
  else {
    switch (whicha | whichb) {
    case ae2f_eMathFloatWhich_INF:
      if (whichb == whicha) {
        if ((whicha ^ whichb) & ae2f_eMathFloatWhich_SGN) {
        case ae2f_eMathFloatWhich_NAN:
        default:
          __ae2f_MathFloatNaN(err, _of, _of_vec);
          break;
        } else {
          __ae2f_MathFloatCast(err, _bf, _bf_vec, _of, _of_vec);
        }
        break;
      } else {
        if (whicha == ae2f_eMathFloatWhich_INF) {
          __ae2f_MathFloatCast(err, _af, _af_vec, _of, _of_vec);
        } else {
          __ae2f_MathFloatCast(err, _bf, _bf_vec, _of, _of_vec);
        }
        break;
      }

    case ae2f_eMathFloatWhich_NIL:
      __ae2f_MathFloatZero(err, _of, _of_vec);
      break;

    case ae2f_eMathFloatWhich_NUM:
    {
      struct __ae2f_MathFloatAddVar_t {
        ae2f_MathInt inta, intb;
        size_t intaidx, intbidx;
        size_t expa, expb;
        int signa, signb;
        size_t shift;
        ae2f_MathInt aligned_a, aligned_b;
      } var;

      /* Get mantissa parts */
      __ae2f_MathFloatMan(err, _af, _af_vec, &var.inta, &var.intaidx);
      __ae2f_MathFloatMan(err, _bf, _bf_vec, &var.intb, &var.intbidx);

      /* Get exponents */
      __ae2f_MathFloatExp(err, _af, _af_vec, &var.inta, &var.intaidx);
      __ae2f_MathFloatExp(err, _bf, _bf_vec, &var.intb, &var.intbidx);

      /* Get signs */
      var.signa = __ae2f_MathFloatGetSign(_af, _af_vec);
      var.signb = __ae2f_MathFloatGetSign(_bf, _bf_vec);

      /* Get exponent values */
      var.expa = var.intaidx;
      var.expb = var.intbidx;

      /* Create aligned mantissas */
      var.aligned_a = var.inta;
      var.aligned_b = var.intb;

      /* Align mantissas based on exponent difference */
      if (var.expa > var.expb) {
        var.shift = var.expa - var.expb;
        /* Shift b's mantissa right by adjusting size and using BitL */
        var.aligned_b.sz = var.intb.sz - var.shift;
        __ae2f_MathIntBitL(err, var.shift, &var.intb, _bf_vec, &var.aligned_b, _of_vec);
      } else if (var.expb > var.expa) {
        var.shift = var.expb - var.expa;
        /* Shift a's mantissa right by adjusting size and using BitL */
        var.aligned_a.sz = var.inta.sz - var.shift;
        __ae2f_MathIntBitL(err, var.shift, &var.inta, _af_vec, &var.aligned_a, _of_vec);
      }

      /* Add mantissas */
      __ae2f_MathIntAdd(err, &var.aligned_a, _af_vec, &var.aligned_b, _bf_vec, &var.inta, _of_vec);

      /* Copy result to output */
      __ae2f_MathFloatCast(err, _af, _of_vec, _of, _of_vec);

      /* Set sign based on addition result */
      __ae2f_MathFloatSetSign(_of, _of_vec, var.inta.sign);

      /* Normalize result */
      __ae2f_MathFloatNormalise(err, _of, _of_vec);
    }
      break;
    }
  }
}

#endif
