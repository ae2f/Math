#ifndef ae2f_Math_float_imp_h
#define ae2f_Math_float_imp_h

#include "./Util.auto.h"
#include "./float.h"
#include "./int.auto.h"
#include <ae2f/Macro.h>

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

#define __ae2f_MathFloatBias(_f) ((_f) ? (1ull << ((_f)->exp - 1)) - 1 : 0)

/**
 * @def __ae2f_MathFloatElSz
 * @brief sizeof(`afloat_t`)
 * @returns size_t
 * @param afloat_t
 * # const ae2f_MathFloat*
 * */
#define __ae2f_MathFloatElSz(afloat_t)                                         \
  ((afloat_t)->sign + (afloat_t)->exp + (afloat_t)->man)

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathFloatMan _ae2f_MathFloatMan
#else
#undef __ae2f_MathFloatMan
#endif

ae2f_MAC() _ae2f_MathFloatMan(ae2f_MathMemOutErr reterr,
                              const ae2f_pMathFloat af, ae2f_pMathInt oi) {
  if ((reterr) && *(reterr))
    ;
  else if (!((af) && (oi)))
    ((reterr)) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);
  else if (!(af->exp))
    ((reterr)) && (*(reterr) |= ae2f_errGlob_IMP_NOT_FOUND);
  else {
    (oi)->sign = 0;
    (oi)->vecbegpoint = (af)->bstart;
    (oi)->sz = (af)->man;
  }
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathFloatExp _ae2f_MathFloatExp
#else
#undef __ae2f_MathFloatExp
#endif

ae2f_MAC()
    _ae2f_MathFloatExp(ae2f_MathMemOutErr reterr, const ae2f_pMathFloat af,
                       ae2f_pMathInt oi, size_t *const retoivecidx) {
  if ((reterr) && *(reterr))
    ;
  else if (!((af) && (oi) && (retoivecidx)))
    ((reterr)) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);
  else {
    (oi)->sign = 0;
    (oi)->vecbegpoint = (af)->bstart + (af)->man; /* Start after mantissa */
    (oi)->sz = (af)->exp; /* Include all exponent bits including sign */
    *(retoivecidx) = ((af)->bstart + (af)->man) >>
                     3; /* Convert bit position to byte index */
  }
}

#if __ae2f_MACRO_GENERATED
#undef __ae2f_MathFloatGetExp
#undef __ae2f_MathFloatSetExp
#undef __ae2f_MathFloatSetExpPtr
#else
#define __ae2f_MathFloatGetExp _ae2f_MathFloatGetExp
#define __ae2f_MathFloatSetExp _ae2f_MathFloatSetExp
#define __ae2f_MathFloatSetExpPtr _ae2f_MathFloatSetExpPtr
#endif

ae2f_MAC() _ae2f_MathFloatGetExp(const ae2f_pMathFloat af, ae2f_iMathMem af_vec,
                                 ae2f_oMathMem o_vec) {
  if ((af) && (af_vec) && (o_vec)) {
    __ae2f_MathUtilBVCpy(o_vec, 0, af_vec, (af)->bstart + (af)->man,
                         ae2f_CmpGetLs((sizeof(size_t) << 3), (af)->exp));
  }
}

ae2f_MAC() _ae2f_MathFloatSetExpPtr(const ae2f_pMathFloat af,
                                    ae2f_oMathMem af_vec, ae2f_iMathMem i_vec) {
  if ((af) && (af_vec) && (i_vec)) {
    __ae2f_MathUtilBVCpy(af_vec, (af)->bstart + (af)->man, i_vec, 0,
                         ae2f_CmpGetLs((sizeof(size_t) << 3), (af)->exp));
  }
}

ae2f_MAC() _ae2f_MathFloatSetExp(const ae2f_pMathFloat af, ae2f_oMathMem af_vec,
                                 size_t newexp) {
  typedef union vt_fsexp vt_fsexp_t;
  union vt_fsexp {
    size_t m_a;
    uint8_t m_b[1];
  } v_fsexp = ae2f_RecordMk(vt_fsexp_t, .m_a = (newexp));

  __ae2f_MathFloatSetExpPtr(af, af_vec, v_fsexp.m_b);
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

#if __ae2f_MACRO_GENERATED
#undef __ae2f_MathFloatNxt
#else
#define __ae2f_MathFloatNxt _ae2f_MathFloatNxt
#endif

/**
 * @def __ae2f_MathFloatNxt
 * @brief
 * `ofloat` = `ifloat` + `idx`;
 * */
ae2f_MAC()
    _ae2f_MathFloatNxt(ae2f_MathMemOutErr err, intptr_t idx,
                       const ae2f_pMathFloat ifloat_t, ae2f_pMathFloat ofloat_t,
                       size_t *const p_ofloatidx) {
  if (((err) && *(err)) || !(idx)) {
  } else if (!((ifloat_t) && (ofloat_t) && (p_ofloatidx))) {
    (err) && ((*err) = ae2f_errGlob_PTR_IS_NULL);
  } else {
    *(ofloat_t) = *(ifloat_t);
    (ofloat_t)->bstart = *(p_ofloatidx) =
        ((ifloat_t)->bstart + __ae2f_MathFloatElSz(ifloat_t) * (idx));
    *(p_ofloatidx) >>= 3;
  }
}

#if __ae2f_MACRO_GENERATED
#undef __ae2f_MathFloatCast
#else
#define __ae2f_MathFloatCast _ae2f_MathFloatCast
#endif

/**
 * @def __ae2f_MathFloatCast
 * @brief `ofloat` = `ifloat`;
 * */
ae2f_MAC()
    _ae2f_MathFloatCast(ae2f_MathMemOutErr err, const ae2f_pMathFloat ifloat_t,
                        ae2f_iMathMem ifloat, const ae2f_pMathFloat ofloat_t,
                        ae2f_oMathMem ofloat) {
  if ((err) && *(err))
    ;
  else if (!((ifloat_t) && (ifloat) && (ofloat_t) && (ofloat)))
    (err) && (*(err) = ae2f_errGlob_PTR_IS_NULL);
  else {
    struct __ae2f_MathFloatCastVar_t {
      size_t c1, c2;
      size_t odiv, idiv, idx;
      unsigned sign : 1;
    } __ae2f_MathFloatCastVar;

    __ae2f_MathFloatCastVar.sign =
        __ae2f_MathFloatGetSign(ifloat_t, ifloat); /* sign */
    __ae2f_MathFloatSetSign(ofloat_t, ofloat, __ae2f_MathFloatCastVar.sign);

    /* exp */
    __ae2f_MathFloatCastVar.idx = 0;
    __ae2f_MathFloatCastVar.c1 = (ifloat_t)->exp - 1;
    __ae2f_MathFloatCastVar.c2 = (ofloat_t)->exp - 1;

    __ae2f_MathFloatCastVar.idiv = (ifloat_t)->bstart + (ifloat_t)->man;
    __ae2f_MathFloatCastVar.odiv = (ofloat_t)->bstart + (ofloat_t)->man;

    for (; __ae2f_MathFloatCastVar.idx < __ae2f_MathFloatCastVar.c2;
         __ae2f_MathFloatCastVar.idx++) {
      if (__ae2f_MathFloatCastVar.idx < __ae2f_MathFloatCastVar.c1) {
        __ae2f_MathFloatCastVar.sign =
            (__ae2f_MathUtilBVGetArr((ifloat), __ae2f_MathFloatCastVar.idiv));
      }

      __ae2f_MathUtilBVSetAssignArr((ofloat), __ae2f_MathFloatCastVar.odiv,
                                    __ae2f_MathFloatCastVar.sign);
      __ae2f_MathFloatCastVar.idiv++;
      __ae2f_MathFloatCastVar.odiv++;
    }

    __ae2f_MathFloatCastVar.odiv &= ~0b111;
    __ae2f_MathFloatCastVar.odiv |=
        __ae2f_MathFloatExpGetSign(ifloat_t, ifloat);

    __ae2f_MathFloatExpSetSign(ofloat_t, ofloat,
                               __ae2f_MathFloatCastVar.odiv & 7); /* fraction */

    __ae2f_MathFloatCastVar.idx = 0;
    __ae2f_MathFloatCastVar.c1 = __ae2f_MathFloatCastVar.idiv =
        (ifloat_t)->man - 1;
    __ae2f_MathFloatCastVar.c2 = __ae2f_MathFloatCastVar.odiv =
        (ofloat_t)->man - 1;

    __ae2f_MathFloatCastVar.idiv += (ifloat_t)->bstart;
    __ae2f_MathFloatCastVar.odiv += (ofloat_t)->bstart;

    for (; __ae2f_MathFloatCastVar.idx < __ae2f_MathFloatCastVar.c2;
         __ae2f_MathFloatCastVar.idx++) {
      if (__ae2f_MathFloatCastVar.idiv != (ifloat_t)->bstart - 1) {
        __ae2f_MathUtilBVSetAssignArr(
            (ofloat), __ae2f_MathFloatCastVar.odiv,
            (__ae2f_MathUtilBVGetArr((ifloat), __ae2f_MathFloatCastVar.idiv)));
        __ae2f_MathFloatCastVar.idiv--;
      } else {
        __ae2f_MathUtilBVSetAssignArr((ofloat), __ae2f_MathFloatCastVar.odiv,
                                      0);
      }
      __ae2f_MathFloatCastVar.odiv--;
    }
  }
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathFloatFlip _ae2f_MathFloatFlip
#else
#undef __ae2f_MathFloatFlip
#endif

/**
 * @def __ae2f_MathFloatCast
 * @brief `ofloat` = -`ifloat`;
 * */
ae2f_MAC()
    _ae2f_MathFloatFlip(ae2f_MathMemOutErr err, const ae2f_pMathFloat _if,
                        ae2f_iMathMem _if_vec, const ae2f_pMathFloat _of,
                        ae2f_oMathMem _of_vec) {
  __ae2f_MathFloatCast(err, _if, _if_vec, _of, _of_vec);
  __ae2f_MathFloatFlipSign(_of, _of_vec);
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathFloatMkWhich _ae2f_MathFloatMkWhich
#else
#undef __ae2f_MathFloatMkWhich
#endif

/**
 * @def __ae2f_MathFloatMkWhich
 * @brief
 * */
ae2f_MAC()
    _ae2f_MathFloatMkWhich(ae2f_MathMemOutErr err, const ae2f_pMathFloat _of,
                           ae2f_oMathMem _of_vec,
                           const ae2f_eMathFloatWhich_t which) {
  if ((err) && *(err))
    ;
  else if (!((_of) && (_of_vec)))
    (err) && (*(err) = ae2f_errGlob_PTR_IS_NULL);
  else {
    struct __ae2f_MathFloatMkWhichVar_t {
      size_t i;
      size_t vec;
    } __ae2f_MathFloatMkWhichVar;

    /* Set all bits to 0 first */
    for (__ae2f_MathFloatMkWhichVar.i = 0;
         __ae2f_MathFloatMkWhichVar.i < (_of)->man + (_of)->exp;
         __ae2f_MathFloatMkWhichVar.i++) {
      __ae2f_MathFloatMkWhichVar.vec =
          (_of)->bstart + __ae2f_MathFloatMkWhichVar.i;
      __ae2f_MathUtilBVSetAssignArr((_of_vec), __ae2f_MathFloatMkWhichVar.vec,
                                    0);
    }

    /* Set bits based on which value */
    if (which == ae2f_eMathFloatWhich_NAN) {
      /* Set all exponent bits to 1 */
      for (__ae2f_MathFloatMkWhichVar.i = 0;
           __ae2f_MathFloatMkWhichVar.i < (_of)->exp;
           __ae2f_MathFloatMkWhichVar.i++) {
        __ae2f_MathFloatMkWhichVar.vec =
            (_of)->bstart + (_of)->man + __ae2f_MathFloatMkWhichVar.i;
        __ae2f_MathUtilBVSetAssignArr((_of_vec), __ae2f_MathFloatMkWhichVar.vec,
                                      1);
      }
      /* Set first mantissa bit to 1 */
      __ae2f_MathFloatMkWhichVar.vec = (_of)->bstart;
      __ae2f_MathUtilBVSetAssignArr((_of_vec), __ae2f_MathFloatMkWhichVar.vec,
                                    1);
    } else if (which == ae2f_eMathFloatWhich_INF) {
      /* Set all exponent bits to 1 */
      for (__ae2f_MathFloatMkWhichVar.i = 0;
           __ae2f_MathFloatMkWhichVar.i < (_of)->exp;
           __ae2f_MathFloatMkWhichVar.i++) {
        __ae2f_MathFloatMkWhichVar.vec =
            (_of)->bstart + (_of)->man + __ae2f_MathFloatMkWhichVar.i;
        __ae2f_MathUtilBVSetAssignArr((_of_vec), __ae2f_MathFloatMkWhichVar.vec,
                                      1);
      }
    } else if (which == ae2f_eMathFloatWhich_ONE) {
      /* Set first exponent bit to 1 */
      __ae2f_MathFloatMkWhichVar.vec = (_of)->bstart + (_of)->man;
      __ae2f_MathUtilBVSetAssignArr((_of_vec), __ae2f_MathFloatMkWhichVar.vec,
                                    1);
    }
  }
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

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathFloatGetWhich _ae2f_MathFloatGetWhich
#else
#undef __ae2f_MathFloatGetWhich
#endif

/**
 * @def __ae2f_MathFloatGetWhich
 * */
ae2f_MAC()
    _ae2f_MathFloatGetWhich(ae2f_MathMemOutErr err, const ae2f_pMathFloat _af,
                            ae2f_iMathMem _af_vec,
                            ae2f_eMathFloatWhich_t *const retwhich) {
  if ((err) && *(err))
    ;
  else if (!((_af) && (_af_vec) && (retwhich)))
    (err) && (*(err) = ae2f_errGlob_PTR_IS_NULL);
  else {
    struct __ae2f_MathFloatGetWhichVar_t {
      size_t i;
      size_t vec;
      unsigned all_exp_ones : 1;
      unsigned first_man_one : 1;
      unsigned all_zero : 1;
    } __ae2f_MathFloatGetWhichVar;

    __ae2f_MathFloatGetWhichVar.all_exp_ones = 1;
    __ae2f_MathFloatGetWhichVar.first_man_one = 0;

    /* Check if all exponent bits are 1 */
    for (__ae2f_MathFloatGetWhichVar.i = 0;
         __ae2f_MathFloatGetWhichVar.i < (_af)->exp;
         __ae2f_MathFloatGetWhichVar.i++) {
      __ae2f_MathFloatGetWhichVar.vec =
          (_af)->bstart + (_af)->man + __ae2f_MathFloatGetWhichVar.i;
      if (!__ae2f_MathUtilBVGetArr(_af_vec, __ae2f_MathFloatGetWhichVar.vec)) {
        __ae2f_MathFloatGetWhichVar.all_exp_ones = 0;
        break;
      }
    }

    /* Check if first mantissa bit is 1 */
    __ae2f_MathFloatGetWhichVar.vec = (_af)->bstart;
    __ae2f_MathFloatGetWhichVar.first_man_one =
        __ae2f_MathUtilBVGetArr((_af_vec), __ae2f_MathFloatGetWhichVar.vec);

    /* Determine which value */
    if (__ae2f_MathFloatGetWhichVar.all_exp_ones) {
      if (__ae2f_MathFloatGetWhichVar.first_man_one) {
        *(retwhich) = ae2f_eMathFloatWhich_NAN;
      } else {
        *(retwhich) = ae2f_eMathFloatWhich_INF;
      }

    } else {
      /* Check if it's zero */
      for (__ae2f_MathFloatGetWhichVar.i = 0;
           __ae2f_MathFloatGetWhichVar.i < (_af)->man + (_af)->exp;
           __ae2f_MathFloatGetWhichVar.i++) {
        __ae2f_MathFloatGetWhichVar.vec =
            (_af)->bstart + __ae2f_MathFloatGetWhichVar.i;
        if (__ae2f_MathUtilBVGetArr((_af_vec),
                                    __ae2f_MathFloatGetWhichVar.vec)) {
          __ae2f_MathFloatGetWhichVar.all_zero = 0;
          break;
        }
      }
      if (__ae2f_MathFloatGetWhichVar.all_zero)
        *(retwhich) = ae2f_eMathFloatWhich_NIL;
      else
        *(retwhich) = ae2f_eMathFloatWhich_NUM;
    }
  }
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathFloatNormalise _ae2f_MathFloatNormalise
#else
#undef __ae2f_MathFloatNormalise
#endif

/**
 * @def __ae2f_MathFloatNormalise
 * @brief
 * Normalise `_if`.
 *
 * @param err       {ae2f_err_t*}
 * @param _if       {ae2f_MathFloat*}
 * @param _if_vec   {ae2f_bMathMem}
 */
ae2f_MAC()
    _ae2f_MathFloatNormalise(ae2f_MathMemOutErr err, const ae2f_pMathFloat _if,
                             ae2f_bMathMem _if_vec) {
  struct __ae2f_MathFloatNormaliseVar_t {
    size_t i, shift;
    size_t div, src_div, dst_div, exp_div;
    ae2f_eMathFloatWhich_t which;
  } __ae2f_MathFloatNormaliseVar;

  /* Check for special cases */
  __ae2f_MathFloatNormaliseVar.which = 0;
  __ae2f_MathFloatGetWhich(err, _if, _if_vec,
                           &__ae2f_MathFloatNormaliseVar.which);

  if ((err) && *(err))
    ;
  else if (!((_if) && (_if_vec))) {
    if (err)
      (*err) = ae2f_errGlob_PTR_IS_NULL;
    ;
  } else if (__ae2f_MathFloatNormaliseVar.which &
             (ae2f_eMathFloatWhich_NAN | ae2f_eMathFloatWhich_INF |
              ae2f_eMathFloatWhich_NIL)) {
    ;      /* No normalization needed for special cases */
  } else { /* Find the position of the most significant 1 bit in the mantissa */
    __ae2f_MathFloatNormaliseVar.shift = 0;
    __ae2f_MathFloatNormaliseVar.div = (_if)->bstart;

    /* Search for the first 1 bit in the mantissa */
    for (__ae2f_MathFloatNormaliseVar.i = 0;
         __ae2f_MathFloatNormaliseVar.i < (_if)->man;
         __ae2f_MathFloatNormaliseVar.i++, __ae2f_MathFloatNormaliseVar.div++) {
      if (__ae2f_MathUtilBVGetArr((_if_vec),
                                  __ae2f_MathFloatNormaliseVar.div)) {
        break;
      }
      __ae2f_MathFloatNormaliseVar.shift++;
    } /* If no 1 bit found, the number is zero */
    if (__ae2f_MathFloatNormaliseVar.shift == (_if)->man) {
      __ae2f_MathFloatZero(err, _if, _if_vec);
      ;
    } else {

      /* Shift the mantissa left by 'shift' positions */
      if (__ae2f_MathFloatNormaliseVar.shift > 0) { /* Shift the mantissa */
        for (__ae2f_MathFloatNormaliseVar.i = 0;
             __ae2f_MathFloatNormaliseVar.i <
             (_if)->man - __ae2f_MathFloatNormaliseVar.shift;
             __ae2f_MathFloatNormaliseVar.i++) {
          __ae2f_MathFloatNormaliseVar.src_div =
              (_if)->bstart + __ae2f_MathFloatNormaliseVar.i +
              __ae2f_MathFloatNormaliseVar.shift;
          __ae2f_MathFloatNormaliseVar.dst_div =
              (_if)->bstart + __ae2f_MathFloatNormaliseVar.i;

          __ae2f_MathUtilBVSetAssignArr(
              (_if_vec), __ae2f_MathFloatNormaliseVar.dst_div,
              __ae2f_MathUtilBVGetArr((_if_vec),
                                      __ae2f_MathFloatNormaliseVar.src_div));
        }

        /* Clear the remaining bits */
        for (__ae2f_MathFloatNormaliseVar.i =
                 (_if)->man - __ae2f_MathFloatNormaliseVar.shift;
             __ae2f_MathFloatNormaliseVar.i < (_if)->man;
             __ae2f_MathFloatNormaliseVar.i++) {
          __ae2f_MathFloatNormaliseVar.div =
              (_if)->bstart + __ae2f_MathFloatNormaliseVar.i;
          __ae2f_MathUtilBVSetAssignArr((_if_vec),
                                        __ae2f_MathFloatNormaliseVar.div, 0);
        }

        /* Adjust the exponent */
        __ae2f_MathFloatNormaliseVar.exp_div = (_if)->bstart + (_if)->man;

        /* Subtract shift from exponent */
        for (__ae2f_MathFloatNormaliseVar.i = 0;
             __ae2f_MathFloatNormaliseVar.i < (_if)->exp - 1;
             __ae2f_MathFloatNormaliseVar.i++,
            __ae2f_MathFloatNormaliseVar.exp_div++) {
          if (__ae2f_MathFloatNormaliseVar.shift > 0) {
            if (__ae2f_MathUtilBVGetArr((_if_vec),
                                        __ae2f_MathFloatNormaliseVar.exp_div)) {
              __ae2f_MathUtilBVSetAssignArr(
                  (_if_vec), __ae2f_MathFloatNormaliseVar.exp_div, 0);
              __ae2f_MathFloatNormaliseVar.shift--;
            }
          }
        }
      }
    }
  }
}

#if __ae2f_MACRO_GENERATED
#undef __ae2f_MathFloatCmp
#else
#define __ae2f_MathFloatCmp _ae2f_MathFloatCmp
#endif

/**
 * @macro __ae2f_MathFloatCmp
 * @warning
 * If two are not normalised, it will not work properly.
 *
 * @brief
 * `out` = `a` cmp `b`
 *
 * @return
 * `ae2f_cmpfunret_lislesser`	means `a` < `b` \n
 * `ae2f_cmpfunret_rislesser`	means `a` > `b` \n
 * `ae2f_cmpfunret_equal`	means `a` == `b`
 * */
ae2f_MAC()
    _ae2f_MathFloatCmp(ae2f_MathMemOutErr err, const ae2f_MathFloat *const _af,
                       ae2f_iMathMem _af_vec, const ae2f_pMathFloat _bf,
                       ae2f_iMathMem _bf_vec, ae2f_CmpFunRet_t *const ret) {
  if ((err) && *(err))
    ;
  else if (!((_af) && (_af_vec) && (_bf) && (_bf_vec) && (ret)))
    (err) && (*(err) |= ae2f_errGlob_PTR_IS_NULL);
  else if ((_af)->exp > sizeof(size_t) << 3 || (_bf)->exp > sizeof(size_t) << 3)
    (err) && (*(err) |= ae2f_errGlob_IMP_NOT_FOUND);
  else {
    typedef struct vt_cmp vt_cmp_t;
    struct vt_cmp {
      union vt_cmpexp {
        uintptr_t m_sz;

        /** @brief unbiased */
        intptr_t m_ubias;
        unsigned char m_a[1];
      } m_exp[2];

      size_t m_i, m_c;

      unsigned m_sign : 1;
      unsigned m_av : 1;
      unsigned m_bv : 1;
      ae2f_CmpFunRet_t m_ret : 5;

    } v_cmp = ae2f_RecordMk(vt_cmp_t, 0, );

    if ((v_cmp.m_sign = __ae2f_MathFloatGetSign(_af, _af_vec)) !=
        __ae2f_MathFloatGetSign(_bf, _bf_vec)) {
      *(ret) =
          v_cmp.m_sign ? ae2f_CmpFunRet_LISLESSER : ae2f_CmpFunRet_RISLESSER;
    } else {
      {
        __ae2f_MathFloatGetExp(_af, _af_vec, v_cmp.m_exp[0].m_a);
        __ae2f_MathFloatGetExp(_bf, _bf_vec, v_cmp.m_exp[1].m_a);

        /** unbias */
        v_cmp.m_exp[0].m_ubias -= __ae2f_MathFloatBias(_af);
        v_cmp.m_exp[1].m_ubias -= __ae2f_MathFloatBias(_bf);
      } /** getting exponents */

      do {
        if (v_cmp.m_exp[0].m_ubias != v_cmp.m_exp[1].m_ubias) {
          v_cmp.m_ret = v_cmp.m_exp[0].m_ubias < v_cmp.m_exp[1].m_ubias
                            ? ae2f_CmpFunRet_LISLESSER
                            : ae2f_CmpFunRet_RISLESSER;
          break;
        }

        /**
         * hope exponents are same but bitsize of mantissa could be various.
         * From very left side to 0.
         * */

        v_cmp.m_exp[0].m_sz = (_af)->man;
        v_cmp.m_exp[1].m_sz = (_bf)->man;

        v_cmp.m_i = 0;
        v_cmp.m_c = ae2f_CmpGetGt(v_cmp.m_exp[0].m_sz, v_cmp.m_exp[1].m_sz);

        v_cmp.m_ret = ae2f_CmpFunRet_EQUAL;

        /** Reversly iterating. */
        for (; v_cmp.m_i < v_cmp.m_c; v_cmp.m_i++) {
          v_cmp.m_av = v_cmp.m_i < v_cmp.m_exp[0].m_sz
                           ? __ae2f_MathUtilBVGetArr(
                                 _af_vec, (_af)->bstart + v_cmp.m_exp[0].m_sz -
                                              1 - v_cmp.m_i)
                           : 0;

          v_cmp.m_bv = v_cmp.m_i < v_cmp.m_exp[1].m_sz
                           ? __ae2f_MathUtilBVGetArr(
                                 _bf_vec, (_bf)->bstart + v_cmp.m_exp[1].m_sz -
                                              1 - v_cmp.m_i)
                           : 0;

          if (v_cmp.m_av != v_cmp.m_bv) {
            v_cmp.m_ret = v_cmp.m_bv ? ae2f_CmpFunRet_LISLESSER
                                     : ae2f_CmpFunRet_RISLESSER;
            break;
          }
        }
      } while (0); /** for jump */

      /** Post process */
      *(ret) = *(err) ? 0 : v_cmp.m_sign ? -v_cmp.m_ret : v_cmp.m_ret;
    }
  }
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathFloatAddU _ae2f_MathFloatAddU
#define __ae2f_MathFloatAdd _ae2f_MathFloatAddU
#define __ae2f_MathFloatSubU _ae2f_MathFloatSubU
#define __ae2f_MathFloatSub _ae2f_MathFloatSub

#else
#undef __ae2f_MathFloatAddU
#undef __ae2f_MathFloatAdd
#undef __ae2f_MathFloatSubU
#undef __ae2f_MathFloatSub
#define __ae2f_MathFloatAdd __ae2f_MathFloatAddU
#endif

/**
 * @TODO
 * I don't think this function is complete. \n
 * It will definately stuck on overload.
 *
 * Now, somehow for different structure is being mess.
 *
 * - Additional test case is needed.
 * - When header goes
 *
 * @warning
 * This is for unsigned-normal-only. \n
 * Special values are not handled here.
 *
 * @brief
 * `_of` = `_af` + `_bf`;
 * */
ae2f_MAC()
    _ae2f_MathFloatAddU(ae2f_err_t *const err, const ae2f_MathFloat *const _af,
                        ae2f_iMathMem _af_vec, const ae2f_MathFloat *const _bf,
                        ae2f_iMathMem _bf_vec, ae2f_MathFloat *const _of,
                        ae2f_oMathMem _of_vec) {
  if ((err) && *(err))
    ;
  else if (!((_af) && (_af_vec) && (_bf) && (_bf_vec) && (_of) && (_of_vec)))
    (err) && (*(err) |= ae2f_errGlob_PTR_IS_NULL);
  else if ((_af)->exp > sizeof(size_t) << 3 || (_bf)->exp > sizeof(size_t) << 3)
    (err) && (*(err) |= ae2f_errGlob_IMP_NOT_FOUND);
  else
    do {
      struct vt_add {
        union vt_addexp {
          uintptr_t m_u;
          intptr_t m_i;
          unsigned char m_b[1];
        }

        /**
         * @brief
         * Exponent index and after that: just exponent
         *
         * @details
         * after index 3 could be temporary
         * */
        m_expint[6],
            /** to store each size of mantissas */
            m_mansz[3];

        /**
         * @brief
         * a, b, o
         *
         * @details
         * 0  3:	m_exp \n
         * 3  6:	m_man
         *
         * For 6th index must be a constant.
         * */
        ae2f_MathInt m_exp_man[4];
      } v_addu;

      {
        v_addu.m_expint[0].m_u = __ae2f_MathFloatExpEndIdx(_af);
        v_addu.m_expint[1].m_u = __ae2f_MathFloatExpEndIdx(_bf);
        v_addu.m_expint[2].m_u = __ae2f_MathFloatExpEndIdx(_of);

        __ae2f_MathFloatMan(err, _af, &v_addu.m_exp_man[0]);
        __ae2f_MathFloatMan(err, _bf, &v_addu.m_exp_man[1]);
        __ae2f_MathFloatMan(err, _of, &v_addu.m_exp_man[2]);
      } /** Get mantissas and exponents */

      /**
       * Getting the difference of size as unsigned positive value.
       * Will be used for bit-shifting
       *
       * Perhaps the shift for it is needed for output buffer.
       *
       * Provided it goes positive, value should be traunacted.
       * Provided it goes negative, value should be left-shifted.
       * */
      {
        v_addu.m_mansz[0].m_u = v_addu.m_exp_man[0].sz;
        v_addu.m_mansz[1].m_u = v_addu.m_exp_man[1].sz;

        v_addu.m_mansz[0].m_u -= v_addu.m_exp_man[2].sz;
        v_addu.m_mansz[1].m_u -= v_addu.m_exp_man[2].sz;

        /**
         * For output is not necessary.
         * */
      }

      {
        __ae2f_MathFloatGetExp(_af, _af_vec, v_addu.m_expint[0].m_b);
        __ae2f_MathFloatGetExp(_bf, _bf_vec, v_addu.m_expint[1].m_b);

        v_addu.m_expint[0].m_i -= __ae2f_MathFloatBias(_af);
        v_addu.m_expint[1].m_i -= __ae2f_MathFloatBias(_bf);

        /**
         * greater one and will be first exponent. \n
         * leading one would increment the final when two exponent meets \n
         * 		> (which means no bitshift is needed)
         * */
        v_addu.m_expint[3].m_i =
            ae2f_CmpGetGt(v_addu.m_expint[0].m_i, v_addu.m_expint[1].m_i) +
            __ae2f_MathFloatBias(_of) +
            (v_addu.m_expint[0].m_i == v_addu.m_expint[1].m_i);

        __ae2f_MathFloatSetExpPtr(_of, _of_vec, v_addu.m_expint[3].m_b);

        v_addu.m_expint[3].m_i =
            ae2f_CmpGetGt(v_addu.m_expint[0].m_i, v_addu.m_expint[1].m_i);

        /**
         * Now two of them represents the bitcount to be shifted. \n
         * They are guaranteed to be positive value.
         * */
        v_addu.m_expint[0].m_i =
            v_addu.m_expint[3].m_i - v_addu.m_expint[0].m_i;
        v_addu.m_expint[1].m_i =
            v_addu.m_expint[3].m_i - v_addu.m_expint[1].m_i;
      } /** Unbias exponent */

      /**
       * It needs to be done with right-shifting.
       * Lower one's exponent shall be higher, leaving its fraction
       * right-shifted.
       *
       * Right shifting does not require additional bits copying.
       * It would be granted by simple adjustment of bitstride or something.
       *
       * Challenging is leading one: \n
       * 	> Its value must have been shifted by `m_i` \n
       * 	> from the outside of mantissa bits.
       *
       * When overflown: \n
       * 	>
       * */
      {
        /** Fill with zero */
        __ae2f_MathIntFill(err, &v_addu.m_exp_man[2], (_of_vec), 0, 1);

        if (!(v_addu.m_expint[1].m_i || v_addu.m_expint[0].m_i)) {
          /** two are zero : means leading ones are being ascended */
          v_addu.m_expint[0].m_i++;
          v_addu.m_expint[1].m_i++;
        }

        /**
         * @brief
         * Output fraction configuration
         * Bitshift
         *
         * Leading one.
         * From here, m_expint[3:4] stands for mantissa's index point.
         * m_expint[5] will be temporary.
         * */
        {
          if (v_addu.m_expint[0].m_i) {

            /** when two mantissa goes different,
             * leading one shifted could be somewhere unexpected.
             * */
            __ae2f_MathUtilBVSetAssignArr(
                _of_vec, (_of)->bstart + (_of)->man - v_addu.m_expint[0].m_i,
                (v_addu.m_expint[0].m_u != v_addu.m_expint[1].m_u));
          }
          if (v_addu.m_mansz[0].m_i > 0)
            v_addu.m_expint[0].m_i += v_addu.m_mansz[0].m_u;

          v_addu.m_exp_man[0].sz -= v_addu.m_expint[0].m_i;
          v_addu.m_exp_man[0].vecbegpoint = v_addu.m_expint[3].m_u =
              (v_addu.m_exp_man[0].vecbegpoint) + v_addu.m_expint[0].m_i;

          v_addu.m_expint[3].m_u >>= 3;
        }

        if (v_addu.m_mansz[0].m_i > 0)
          v_addu.m_expint[0].m_i -= v_addu.m_mansz[0].m_u;

        {
          if (v_addu.m_expint[1].m_i) {

            __ae2f_MathUtilBVSetAssignArr(
                _of_vec, (_of)->bstart + (_of)->man - v_addu.m_expint[1].m_i,
                (v_addu.m_expint[0].m_u != v_addu.m_expint[1].m_u));
          }

          if (v_addu.m_mansz[1].m_i > 0)
            v_addu.m_expint[1].m_i += v_addu.m_mansz[1].m_u;

          v_addu.m_exp_man[1].sz -= v_addu.m_expint[1].m_i;
          v_addu.m_exp_man[1].vecbegpoint = v_addu.m_expint[4].m_u =
              (v_addu.m_exp_man[1].vecbegpoint) + v_addu.m_expint[1].m_i;

          v_addu.m_expint[4].m_u >>= 3;
        }
      }

      /**
       * @brief
       * - Make count zeros from right side(whatever) and trim by index
       * - perform add
       * - if the value is not greater than any three of original value, means
       * it has been overflown. bump and bitshift it. (critical?)
       *
       * m_expint[3:4]	: mantissa index point
       * m_expint[5]	: rbitzero size
       * */
      for (v_addu.m_expint[5].m_u = 0;; v_addu.m_expint[5].m_u++) {
        if (v_addu.m_expint[5].m_u == v_addu.m_exp_man[0].sz)
          break;
        if (v_addu.m_expint[5].m_u == v_addu.m_exp_man[1].sz)
          break;
        if (v_addu.m_expint[5].m_u == v_addu.m_exp_man[2].sz)
          break;

        if ((__ae2f_MathUtilBVGetArr((_of_vec),
                                     v_addu.m_exp_man[2].vecbegpoint +
                                         v_addu.m_expint[5].m_u) ||

             __ae2f_MathUtilBVGetArr((_af_vec) + v_addu.m_expint[3].m_u,
                                     v_addu.m_expint[5].m_u +
                                         v_addu.m_exp_man[0].vecbegpoint) ||

             __ae2f_MathUtilBVGetArr((_bf_vec) + v_addu.m_expint[4].m_u,
                                     v_addu.m_expint[5].m_u +
                                         v_addu.m_exp_man[1].vecbegpoint))) {
          break;
        }
      }

      {
        v_addu.m_exp_man[0].sz -= v_addu.m_expint[5].m_u;
        v_addu.m_exp_man[0].vecbegpoint = v_addu.m_expint[3].m_u =
            (v_addu.m_exp_man[0].vecbegpoint) + (v_addu.m_expint[3].m_u << 3) +
            v_addu.m_expint[5].m_u;
        v_addu.m_expint[3].m_u >>= 3;

        v_addu.m_exp_man[1].sz -= v_addu.m_expint[5].m_u;
        v_addu.m_exp_man[1].vecbegpoint = v_addu.m_expint[4].m_u =
            (v_addu.m_exp_man[1].vecbegpoint) + (v_addu.m_expint[4].m_u << 3) +
            v_addu.m_expint[5].m_u;
        v_addu.m_expint[4].m_u >>= 3;

        v_addu.m_exp_man[2].sz -= v_addu.m_expint[5].m_u;

        v_addu.m_exp_man[2].vecbegpoint = v_addu.m_expint[5].m_u =
            (v_addu.m_exp_man[2].vecbegpoint) + v_addu.m_expint[5].m_u;
        v_addu.m_expint[5].m_u >>= 3;
      }

      /**
       * - Make count zeros from right side(whatever) and trim by index
       * - perform add
       * - if the value is not greater than any three of original value, means
       * it has been overflown. bump and bitshift it. (critical?)
       *
       * m_expint[3:4:5]	: mantissa index point
       *
       * Maybe making a temprary integer header would help
       * */
      {
        if (v_addu.m_mansz[0].m_i < 0 || v_addu.m_mansz[1].m_i < 0) {
          /**
           * need to store the mantissa index somewhere
           * expint[0] will store it.
           * */
          v_addu.m_exp_man[3] = v_addu.m_exp_man[2];
          v_addu.m_mansz[2].m_u = v_addu.m_expint[5].m_u;
        }

        if (v_addu.m_mansz[0].m_i < 0) {
          v_addu.m_exp_man[2].sz =
              v_addu.m_exp_man[3].sz + v_addu.m_mansz[0].m_i;

          v_addu.m_exp_man[2].vecbegpoint = v_addu.m_expint[5].m_u =
              v_addu.m_exp_man[3].vecbegpoint + (v_addu.m_mansz[2].m_u << 3) -
              v_addu.m_mansz[0].m_i;

          v_addu.m_expint[5].m_u >>= 3;
        }

        /** O = A + O */
        __ae2f_MathIntAdd(
            err, &v_addu.m_exp_man[0], (_af_vec) + v_addu.m_expint[3].m_u,
            &v_addu.m_exp_man[2], v_addu.m_expint[5].m_u + (_of_vec),
            &v_addu.m_exp_man[2], v_addu.m_expint[5].m_u + (_of_vec));

        if (v_addu.m_mansz[1].m_i < 0) {
          v_addu.m_exp_man[2].sz =
              v_addu.m_exp_man[3].sz + v_addu.m_mansz[1].m_i;

          v_addu.m_exp_man[2].vecbegpoint = v_addu.m_expint[5].m_u =
              v_addu.m_exp_man[3].vecbegpoint + (v_addu.m_mansz[2].m_u << 3) -
              v_addu.m_mansz[1].m_i;

          v_addu.m_expint[5].m_u >>= 3;
        } else if (v_addu.m_mansz[0].m_i < 0) {
          /** Original */
          v_addu.m_exp_man[2] = v_addu.m_exp_man[3];
          v_addu.m_expint[5].m_u = v_addu.m_mansz[2].m_u;
        }

        /** O = O + B */
        __ae2f_MathIntAdd(
            err, &v_addu.m_exp_man[1], (_bf_vec) + v_addu.m_expint[4].m_u,
            &v_addu.m_exp_man[2], v_addu.m_expint[5].m_u + (_of_vec),
            &v_addu.m_exp_man[2], v_addu.m_expint[5].m_u + (_of_vec));
      }

      /**
       * Exception: both have same bit shifted.
       * Leading one must have been moved.
       * */
    } while (0);
}

#endif
