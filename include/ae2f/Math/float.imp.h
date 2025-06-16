#ifndef ae2f_Math_float_imp_h
#define ae2f_Math_float_imp_h

#include "./int.auto.h"

#include "./float.h"
#include "./int.auto.h"

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

#define __ae2f_MathFloatMan _ae2f_MathFloatMan

ae2f_MAC() _ae2f_MathFloatMan(ae2f_MathMemOutErr reterr,
                              const ae2f_pMathFloat af, ae2f_pMathInt oi) {
  if ((reterr) && *(reterr))
    ;
  else if (!((af) && (oi)))
    ((reterr)) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);
  else {
    (oi)->sign = 0;
    (oi)->vecbegpoint = (af)->bstart;
    (oi)->sz = (af)->man;
  }
}

#define __ae2f_MathFloatExp _ae2f_MathFloatExp

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

#define __ae2f_MathFloatExpEndIdx(af) ((af)->man + (af)->exp + (af)->bstart - 1)

#define __ae2f_MathFloatExpGetSign(af, af_vec)                                 \
  ((af) && (af_vec)                                                            \
       ? (__ae2f_MathUtilBVGetArr((af_vec), (__ae2f_MathFloatExpEndIdx(af))))  \
       : 0)

#define __ae2f_MathFloatExpSetSign(af, af_vec, mask)                           \
  ((af) && (af_vec) ? __ae2f_MathUtilBVSetAssignArr(                           \
                          (af_vec), (__ae2f_MathFloatExpEndIdx(af)), !!(mask)) \
                    : 0)

#define __ae2f_MathFloatNxt _ae2f_MathFloatNxt

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

#define __ae2f_MathFloatCast _ae2f_MathFloatCast

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

#define __ae2f_MathFloatFlip _ae2f_MathFloatFlip

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

#define __ae2f_MathFloatMkWhich _ae2f_MathFloatMkWhich

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

/**
 * @def __ae2f_MathFloatGetWhich
 * */
#define __ae2f_MathFloatGetWhich _ae2f_MathFloatGetWhich

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

#define __ae2f_MathFloatNormalise _ae2f_MathFloatNormalise

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

#include <stdio.h>

#define __ae2f_MathFloatAdd _ae2f_MathFloatAdd

/**
 * @brief
 * `_of` = `_af` + `_bf`;
 * */
ae2f_MAC() _ae2f_MathFloatAdd(ae2f_err_t *err, const ae2f_MathFloat *_af,
                              ae2f_iMathMem _af_vec, const ae2f_MathFloat *_bf,
                              ae2f_iMathMem _bf_vec, ae2f_MathFloat *_of,
                              ae2f_oMathMem _of_vec) {
  if (!(err)) {
  } else if (!((_af) && (_af_vec) && (_bf) && (_bf_vec) && (_of) &&
               (_of_vec))) {
    *(err) |= ae2f_errGlob_PTR_IS_NULL;
  } else if (!(*(err))) {
    struct FREF {
      size_t m_midx;

      ae2f_MathInt m_man[1];
      ae2f_MathInt m_exp[1];
    } v_af, v_bf, v_of;

    typedef struct VAR VAR;
    struct VAR {
      const ae2f_MathInt m_size[1];
      union IB {
        uintptr_t a;
        intptr_t i;
        unsigned char b[1];
      } m_bexp, m_aexp, m_oexp;
    } var = ae2f_RecordMk(
        VAR, ae2f_RecordMk(ae2f_MathInt, sizeof(size_t) << 3, 0, 0), 0, );

    __ae2f_MathFloatMan(err, _af, v_af.m_man);
    __ae2f_MathFloatMan(err, _bf, v_bf.m_man);
    __ae2f_MathFloatMan(err, _of, v_of.m_man);

    __ae2f_MathFloatExp(err, _af, v_af.m_exp, &v_af.m_midx);
    __ae2f_MathFloatExp(err, _bf, v_bf.m_exp, &v_bf.m_midx);
    __ae2f_MathFloatExp(err, _of, v_of.m_exp, &v_of.m_midx);

    if (v_af.m_exp[0].sz > sizeof(void *) << 3) {
      *(err) |= ae2f_errGlob_IMP_NOT_FOUND;
    }

    if (v_bf.m_exp[0].sz > sizeof(void *) << 3) {
      *(err) |= ae2f_errGlob_IMP_NOT_FOUND;
    }

    __ae2f_MathIntCast(err, v_af.m_exp, (_af_vec) + v_af.m_midx, var.m_size,
                       var.m_aexp.b);
    __ae2f_MathIntCast(err, v_bf.m_exp, (_bf_vec) + v_bf.m_midx, var.m_size,
                       var.m_bexp.b);

    var.m_aexp.a -= (1 << ((_af)->exp - 1)) - 1;
    var.m_bexp.a -= (1 << ((_bf)->exp - 1)) - 1;

    if (var.m_aexp.a > var.m_bexp.a) {
      __ae2f_MathIntBitR(err, (var.m_aexp.a - var.m_bexp.a), v_bf.m_man,
                         (_bf_vec), v_of.m_man, (_of_vec));
      v_of.m_man->sz += 1;

      if (__ae2f_MathFloatGetSign(_bf, _bf_vec) !=
          __ae2f_MathFloatGetSign(_af, _af_vec)) {
        __ae2f_MathIntSub(err, v_bf.m_man, (_bf_vec), v_of.m_man, (_of_vec),
                          v_of.m_man, _of_vec);
      } else {
        puts("skldfjklsdfjklsdf");
        __ae2f_MathIntAdd(err, v_bf.m_man, (_bf_vec), v_of.m_man, (_of_vec),
                          v_of.m_man, _of_vec);
      }

      if (__ae2f_MathUtilBVGetArr(_of_vec, (v_of.m_man->sz - 1))) {
        __ae2f_MathIntBitR(err, 1 /**why the fuck */, v_of.m_man, _of_vec,
                           v_of.m_man, _of_vec);
        var.m_oexp.a = 1;
      } else {
        var.m_oexp.a = 0;
      }

      var.m_oexp.a += var.m_bexp.a + (1 << ((_of)->exp - 1)) - 1;
    } else {
      __ae2f_MathIntBitR(err, (var.m_bexp.a - var.m_aexp.a), v_af.m_man,
                         (_af_vec), v_of.m_man, (_of_vec));
      v_of.m_man->sz += 1;

      if (__ae2f_MathFloatGetSign(_bf, _bf_vec) !=
          __ae2f_MathFloatGetSign(_af, _af_vec)) {
        __ae2f_MathIntSub(err, v_of.m_man, (_of_vec), v_bf.m_man, (_bf_vec),
                          v_of.m_man, _of_vec);
      } else {
        puts("skldfjklsdfjklsdf");
        __ae2f_MathIntAdd(err, v_of.m_man, (_of_vec), v_bf.m_man, (_bf_vec),
                          v_of.m_man, _of_vec);
      }

      if (__ae2f_MathUtilBVGetArr(_of_vec, (v_of.m_man->sz - 1))) {
        __ae2f_MathIntBitR(err, 1 /**why the fuck */, v_of.m_man, _of_vec,
                           v_of.m_man, _of_vec);
        var.m_oexp.a = 1;
      } else {
        var.m_oexp.a = 0;
      }

      var.m_oexp.a += var.m_bexp.a + ((1 << ((_of)->exp - 1)) - 1);
    }

    __ae2f_MathIntCast(err, var.m_size, var.m_oexp.b, v_of.m_exp,
                       (_of_vec) + v_of.m_midx);

    /* __ae2f_MathFloatNormalise(err, _of, _of_vec); */
  }
}

#endif
