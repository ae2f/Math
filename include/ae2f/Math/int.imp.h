#ifndef ae2f_Math_int_imp_h
#define ae2f_Math_int_imp_h

#include "./int.h"
#include <ae2f/BitVec.h>

/**
 * @brief
 * `_out_int` = `_int`[`_idx`];
 *
 * @param _reterr	{ae2f_err_t*}
 * @param _int		{const ae2f_MathInt*}
 * @param _int_vec	{ae2f_bmathMem}
 * @param _idx		{intptr_t}
 * @param _out_int	{ae2f_MathInt*}
 * @param _out_int_vec	{typeof(_int_vec)*}
 * */
#define __ae2f_MathIntNxt(_reterr, _idx, _int, _int_vec, _out_int,             \
                          _out_int_vec)                                        \
  {                                                                            \
    if (!((_int) && (_out_int) && (_int_vec) && (_out_int_vec))) {             \
      if ((_reterr))                                                           \
        *ae2f_reinterpret_cast(ae2f_MathMemOutErr, _reterr) |=                 \
            ae2f_errGlob_PTR_IS_NULL;                                          \
    } else {                                                                   \
      struct {                                                                 \
        size_t __len;                                                          \
      } __ae2f_MathIntNxtVar;                                                  \
      __ae2f_MathIntNxtVar.__len = (_int)->vecbegpoint + (_int)->sz * (_idx);  \
      *(_out_int) = *(_int);                                                   \
      (_out_int)->vecbegpoint = __ae2f_MathIntNxtVar.__len & 7;                \
      *(_out_int_vec) = (_int_vec) + (__ae2f_MathIntNxtVar.__len >> 3);        \
    }                                                                          \
  }

/**
 * @brief
 * `__i` < 0
 *
 * @returns bool
 * @param __i	{const ae2f_MathInt*}
 * @param __v	{ae2f_iMathMem}
 * */
#define __ae2f_MathIntIsNegative(__i, __v)                                     \
  ((__i) && (__i)->sign && (__v) &&                                            \
   ae2f_BitVecGet((__v)[((__i)->vecbegpoint + (__i)->sz - 1) >> 3],            \
                  ((__i)->vecbegpoint + (__i)->sz - 1) & 7))

/**
 * @macro
 * __ae2f_MathIntCast
 *
 * @brief
 * `__out` = `__in`
 *
 * @param reterr	{ae2f_err_t*}
 * @param __in		{const ae2f_MathInt*}
 * @param __i_vec	{ae2f_iMathMem}
 * @param __out		{const ae2f_MathInt*}
 * @param __o_vec	{ae2f_oMathMem}
 *
 * */
#define __ae2f_MathIntCast(reterr, __in, __i_vec, __out, __o_vec)              \
  {                                                                            \
    if ((reterr) && *(reterr))                                                 \
      ;                                                                        \
    else if (!((__in) && (__out) && (__i_vec) && (__o_vec))) {                 \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
    } else {                                                                   \
      struct {                                                                 \
        size_t ovecbp;                                                         \
        size_t ovecbpq;                                                        \
        size_t ivecbp;                                                         \
        size_t ivecbpq;                                                        \
        size_t j;                                                              \
        uint8_t ivecbpr : 3;                                                   \
        uint8_t ovecbpr : 3;                                                   \
      } __ae2f_MathIntCastVar;                                                 \
      /** Fill them all without noticing if it's signed */                     \
      for (__ae2f_MathIntCastVar.j = 0;                                        \
           __ae2f_MathIntCastVar.j <                                           \
               (__in)->sz - ae2f_static_cast(size_t, (__in)->sign) &&          \
           __ae2f_MathIntCastVar.j < (__out)->sz;                              \
           __ae2f_MathIntCastVar.j++) {                                        \
        __ae2f_MathIntCastVar.ovecbp =                                         \
            (__out)->vecbegpoint + __ae2f_MathIntCastVar.j;                    \
        __ae2f_MathIntCastVar.ovecbpq = __ae2f_MathIntCastVar.ovecbp >> 3;     \
        __ae2f_MathIntCastVar.ovecbpr = __ae2f_MathIntCastVar.ovecbp & 7;      \
                                                                               \
        __ae2f_MathIntCastVar.ivecbp =                                         \
            (__in)->vecbegpoint + __ae2f_MathIntCastVar.j;                     \
        __ae2f_MathIntCastVar.ivecbpq = __ae2f_MathIntCastVar.ivecbp >> 3;     \
        __ae2f_MathIntCastVar.ivecbpr = __ae2f_MathIntCastVar.ivecbp & 7;      \
                                                                               \
        (__o_vec)[__ae2f_MathIntCastVar.ovecbpq] = ae2f_BitVecSet(             \
            (__o_vec)[__ae2f_MathIntCastVar.ovecbpq],                          \
            __ae2f_MathIntCastVar.ovecbpr /*idx*/                              \
            ,                                                                  \
            ae2f_BitVecGet((__i_vec)[__ae2f_MathIntCastVar.ivecbpq],           \
                           __ae2f_MathIntCastVar.ivecbpr));                    \
      }                                                                        \
                                                                               \
      /*                                                                       \
       * Rest of them will be zero.                                            \
       * When signed, rest will be filled with sign bit.                       \
       * */                                                                    \
      for (; __ae2f_MathIntCastVar.j < (__out)->sz;                            \
           __ae2f_MathIntCastVar.j++) {                                        \
        __ae2f_MathIntCastVar.ovecbp =                                         \
            (__out)->vecbegpoint + __ae2f_MathIntCastVar.j;                    \
        __ae2f_MathIntCastVar.ovecbpq = __ae2f_MathIntCastVar.ovecbp >> 3;     \
        __ae2f_MathIntCastVar.ovecbpr = __ae2f_MathIntCastVar.ovecbp & 7;      \
                                                                               \
        __ae2f_MathIntCastVar.ivecbp =                                         \
            (__in)->vecbegpoint + __ae2f_MathIntCastVar.j;                     \
        __ae2f_MathIntCastVar.ivecbpq = __ae2f_MathIntCastVar.ivecbp >> 3;     \
        __ae2f_MathIntCastVar.ivecbpr = __ae2f_MathIntCastVar.ivecbp & 7;      \
                                                                               \
        __ae2f_MathIntCastVar.ovecbpq[__o_vec] =                               \
            ae2f_BitVecSet(__ae2f_MathIntCastVar.ovecbpq[__o_vec],             \
                           __ae2f_MathIntCastVar.ovecbpr,                      \
                           __ae2f_MathIntIsNegative(__in, (__i_vec)));         \
      }                                                                        \
    }                                                                          \
  }

/**
 * @macro __ae2f_MathIntFlip
 *
 * @brief
 * `__o` = -`__i`
 *
 * @param ae2f_MathMemOutErr	reterr
 * @param size_t		count
 * @param const ae2f_MathInt*	__i
 * @param ae2f_iMathMem		__i_vec
 * @param const ae2f_MathInt*	__o
 * @param ae2f_oMathMem		__o_vec
 * */
#define __ae2f_MathIntFlip(reterr, __i, __i_vec, __o, __o_vec)                 \
  {                                                                            \
    if ((reterr) && *(reterr))                                                 \
      ;                                                                        \
    else if (!(__i)) {                                                         \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
    } else if (!(__o)) {                                                       \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
    } else if (!(__i_vec)) {                                                   \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
    } else if (!(__o_vec)) {                                                   \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
    } else {                                                                   \
      struct {                                                                 \
        size_t ovecbp;                                                         \
        size_t ovecbpq;                                                        \
        size_t ivecbp;                                                         \
        size_t ivecbpq;                                                        \
        size_t j;                                                              \
        uint8_t buf : 2;                                                       \
        bool sbit : 1;                                                         \
        uint8_t ovecbpr : 3;                                                   \
        uint8_t ivecbpr : 3;                                                   \
      } __ae2f_MathIntFlipVar;                                                 \
      /** +1 for second compliment */                                          \
      __ae2f_MathIntFlipVar.buf = 0b10;                                        \
      __ae2f_MathIntFlipVar.ivecbp = (__i)->vecbegpoint + (__i)->sz - 1;       \
      __ae2f_MathIntFlipVar.ivecbpq = __ae2f_MathIntFlipVar.ivecbp >> 3;       \
      __ae2f_MathIntFlipVar.ivecbpr = __ae2f_MathIntFlipVar.ivecbp & 7;        \
                                                                               \
      __ae2f_MathIntFlipVar.sbit =                                             \
          (__o)->sign &&                                                       \
          ae2f_BitVecGet((__i_vec)[__ae2f_MathIntFlipVar.ivecbpq],             \
                         __ae2f_MathIntFlipVar.ivecbpr);                       \
                                                                               \
      for (__ae2f_MathIntFlipVar.j = 0; __ae2f_MathIntFlipVar.j < (__o)->sz;   \
           __ae2f_MathIntFlipVar.j++) {                                        \
        __ae2f_MathIntFlipVar.ovecbp =                                         \
            (__o)->vecbegpoint + __ae2f_MathIntFlipVar.j;                      \
        __ae2f_MathIntFlipVar.ovecbpq = __ae2f_MathIntFlipVar.ovecbp >> 3;     \
        __ae2f_MathIntFlipVar.ovecbpr = __ae2f_MathIntFlipVar.ovecbp & 7;      \
                                                                               \
        __ae2f_MathIntFlipVar.ivecbp =                                         \
            (__i)->vecbegpoint + __ae2f_MathIntFlipVar.j;                      \
        __ae2f_MathIntFlipVar.ivecbpq = __ae2f_MathIntFlipVar.ivecbp >> 3;     \
        __ae2f_MathIntFlipVar.ivecbpr = __ae2f_MathIntFlipVar.ivecbp & 7;      \
                                                                               \
        __ae2f_MathIntFlipVar.buf =                                            \
            !(__ae2f_MathIntFlipVar.j < (__i)->sz                              \
                  ? ae2f_BitVecGet((__i_vec)[__ae2f_MathIntFlipVar.ivecbpq],   \
                                   __ae2f_MathIntFlipVar.ivecbpr)              \
                  : __ae2f_MathIntFlipVar.sbit) /** Compliment 1 */            \
            + (__ae2f_MathIntFlipVar.buf >> 1);                                \
                                                                               \
        (__o_vec)[__ae2f_MathIntFlipVar.ovecbpq] = ae2f_BitVecSet(             \
            (__o_vec)[__ae2f_MathIntFlipVar.ovecbpq],                          \
            __ae2f_MathIntFlipVar.ovecbpr, __ae2f_MathIntFlipVar.buf & 1);     \
      }                                                                        \
    }                                                                          \
  }

/**
 * @macro __ae2f_MathIntAdd
 * @brief `_out` = `_a` + `_b`;
 *
 * @param reterr	{ae2f_err_t*}
 * @param _a		{const ae2f_MathInt*}
 * @param _a_vec	{ae2f_iMathMem}
 * @param _b		{const ae2f_MathInt*}
 * @param _b_vec	{ae2f_iMathMem}
 * @param _o		{const ae2f_MathInt*}
 * @param _o_vec	{ae2f_oMathMem}
 * */
#define __ae2f_MathIntAdd(reterr, _a, _a_vec, _b, _b_vec, _o, _o_vec)          \
  {                                                                            \
    if (!(_o) || ((reterr) && *(reterr)))                                      \
      ;                                                                        \
    else if (!((_a) && (_b) && (_o) && (_a_vec) && (_b_vec))) {                \
      ((reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL));                   \
    } else {                                                                   \
      struct {                                                                 \
        size_t j, ovecbp, ovecbpq, avecbp, avecbpq, bvecbp, bvecbpq;           \
        uint8_t buf : 2;                                                       \
        uint8_t sb2 : 2;                                                       \
        uint8_t ovecbpr : 3;                                                   \
        uint8_t avecbpr : 3;                                                   \
        uint8_t bvecbpr : 3;                                                   \
      } __ae2f_MathIntAddVar;                                                  \
      __ae2f_MathIntAddVar.buf = 0b00 /**                                      \
                                       * 0: a                                  \
                                       * 1: b                                  \
                                       * */                                    \
          ,                                                                    \
      __ae2f_MathIntAddVar.sb2 = 0;                                            \
                                                                               \
      __ae2f_MathIntAddVar.sb2 =                                               \
          ((_a)->sign &&                                                       \
           ae2f_BitVecGet((_a_vec)[((_a)->vecbegpoint + (_a)->sz - 1) >> 3],   \
                          ((_a)->vecbegpoint + (_a)->sz - 1) & 7)) |           \
          (((_b)->sign &&                                                      \
            ae2f_BitVecGet((_b_vec)[((_b)->vecbegpoint + (_b)->sz - 1) >> 3],  \
                           ((_b)->vecbegpoint + (_b)->sz - 1) & 7))            \
           << 1);                                                              \
                                                                               \
      for (__ae2f_MathIntAddVar.j = 0; __ae2f_MathIntAddVar.j < (_o)->sz;      \
           __ae2f_MathIntAddVar.j++) {                                         \
        __ae2f_MathIntAddVar.avecbp =                                          \
            (_a)->vecbegpoint + __ae2f_MathIntAddVar.j;                        \
        __ae2f_MathIntAddVar.avecbpq = __ae2f_MathIntAddVar.avecbp >> 3;       \
        __ae2f_MathIntAddVar.avecbpr = __ae2f_MathIntAddVar.avecbp & 7;        \
                                                                               \
        __ae2f_MathIntAddVar.bvecbp =                                          \
            (_b)->vecbegpoint + __ae2f_MathIntAddVar.j;                        \
        __ae2f_MathIntAddVar.bvecbpq = __ae2f_MathIntAddVar.bvecbp >> 3;       \
        __ae2f_MathIntAddVar.bvecbpr = __ae2f_MathIntAddVar.bvecbp & 7;        \
                                                                               \
        __ae2f_MathIntAddVar.ovecbp =                                          \
            (_o)->vecbegpoint + __ae2f_MathIntAddVar.j;                        \
        __ae2f_MathIntAddVar.ovecbpq = __ae2f_MathIntAddVar.ovecbp >> 3;       \
        __ae2f_MathIntAddVar.ovecbpr = __ae2f_MathIntAddVar.ovecbp & 7;        \
                                                                               \
        __ae2f_MathIntAddVar.buf =                                             \
            (__ae2f_MathIntAddVar.j < (_a)->sz                                 \
                 ? ae2f_BitVecGet(__ae2f_MathIntAddVar.avecbpq[_a_vec],        \
                                  __ae2f_MathIntAddVar.avecbpr)                \
                 : __ae2f_MathIntAddVar.sb2 & 1) +                             \
            (__ae2f_MathIntAddVar.j < (_b)->sz                                 \
                 ? ae2f_BitVecGet(__ae2f_MathIntAddVar.bvecbpq[_b_vec],        \
                                  __ae2f_MathIntAddVar.bvecbpr)                \
                 : __ae2f_MathIntAddVar.sb2 >> 1) +                            \
            (__ae2f_MathIntAddVar.buf >> 1);                                   \
        __ae2f_MathIntAddVar.ovecbpq[_o_vec] = ae2f_BitVecSet(                 \
            __ae2f_MathIntAddVar.ovecbpq[_o_vec],                              \
            __ae2f_MathIntAddVar.ovecbpr, __ae2f_MathIntAddVar.buf & 1);       \
      }                                                                        \
    }                                                                          \
  }

/**
 * @macro __ae2f_MathIntSub
 * @brief `_out` = `_a` - `_b`;
 *
 * @param reterr	{ae2f_err_t*}
 * @param _a		{const ae2f_MathInt*}
 * @param _a_vec	{ae2f_iMathMem}
 * @param _b		{const ae2f_MathInt*}
 * @param _b_vec	{ae2f_iMathMem}
 * @param _o		{const ae2f_MathInt*}
 * @param _o_vec	{ae2f_oMathMem}
 * */

#define __ae2f_MathIntSub(reterr, _a, _a_vec, _b, _b_vec, _o, _o_vec)          \
  {                                                                            \
    if (!(_o) || ((reterr) && *(reterr)))                                      \
      ;                                                                        \
    else if (!((_a) && (_b) && (_o) && (_a_vec) && (_b_vec))) {                \
      ((reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL));                   \
    } else {                                                                   \
      struct {                                                                 \
        size_t j, ovecbp, ovecbpq, avecbp, avecbpq, bvecbp, bvecbpq;           \
        uint8_t buf : 2;                                                       \
        uint8_t sb2 : 2;                                                       \
        uint8_t ovecbpr : 3;                                                   \
        uint8_t avecbpr : 3;                                                   \
        uint8_t bvecbpr : 3;                                                   \
      } __ae2f_MathIntSubVar;                                                  \
      __ae2f_MathIntSubVar.buf = 0b10; /**                                     \
                                        * 0: a                                 \
                                        * 1: b, +1                             \
                                        * */                                   \
                                                                               \
      __ae2f_MathIntSubVar.sb2 =                                               \
          ((_a)->sign &&                                                       \
           ae2f_BitVecGet((_a_vec)[((_a)->vecbegpoint + (_a)->sz - 1) >> 3],   \
                          ((_a)->vecbegpoint + (_a)->sz - 1) & 7)) |           \
          (((_b)->sign &&                                                      \
            ae2f_BitVecGet((_b_vec)[((_b)->vecbegpoint + (_b)->sz - 1) >> 3],  \
                           ((_b)->vecbegpoint + (_b)->sz - 1) & 7))            \
           << 1);                                                              \
                                                                               \
      for (__ae2f_MathIntSubVar.j = 0; __ae2f_MathIntSubVar.j < (_o)->sz;      \
           __ae2f_MathIntSubVar.j++) {                                         \
        __ae2f_MathIntSubVar.avecbp =                                          \
            (_a)->vecbegpoint + __ae2f_MathIntSubVar.j;                        \
        __ae2f_MathIntSubVar.avecbpq = __ae2f_MathIntSubVar.avecbp >> 3;       \
        __ae2f_MathIntSubVar.avecbpr = __ae2f_MathIntSubVar.avecbp & 7;        \
                                                                               \
        __ae2f_MathIntSubVar.bvecbp =                                          \
            (_b)->vecbegpoint + __ae2f_MathIntSubVar.j;                        \
        __ae2f_MathIntSubVar.bvecbpq = __ae2f_MathIntSubVar.bvecbp >> 3;       \
        __ae2f_MathIntSubVar.bvecbpr = __ae2f_MathIntSubVar.bvecbp & 7;        \
                                                                               \
        __ae2f_MathIntSubVar.ovecbp =                                          \
            (_o)->vecbegpoint + __ae2f_MathIntSubVar.j;                        \
        __ae2f_MathIntSubVar.ovecbpq = __ae2f_MathIntSubVar.ovecbp >> 3;       \
        __ae2f_MathIntSubVar.ovecbpr = __ae2f_MathIntSubVar.ovecbp & 7;        \
                                                                               \
        __ae2f_MathIntSubVar.buf =                                             \
            (__ae2f_MathIntSubVar.j < (_a)->sz                                 \
                 ? ae2f_BitVecGet(__ae2f_MathIntSubVar.avecbpq[_a_vec],        \
                                  __ae2f_MathIntSubVar.avecbpr)                \
                 : __ae2f_MathIntSubVar.sb2 & 1) +                             \
            !(__ae2f_MathIntSubVar.j < (_b)->sz                                \
                  ? ae2f_BitVecGet(__ae2f_MathIntSubVar.bvecbpq[_b_vec],       \
                                   __ae2f_MathIntSubVar.bvecbpr)               \
                  : __ae2f_MathIntSubVar.sb2 >> 1) /* ~`b` */                  \
            + (__ae2f_MathIntSubVar.buf >> 1);                                 \
        __ae2f_MathIntSubVar.ovecbpq[_o_vec] = ae2f_BitVecSet(                 \
            __ae2f_MathIntSubVar.ovecbpq[_o_vec],                              \
            __ae2f_MathIntSubVar.ovecbpr, __ae2f_MathIntSubVar.buf & 1);       \
      }                                                                        \
    }                                                                          \
  }

/**
 * @macro __ae2f_MathIntFill
 * @brief
 * `a` = 0;  \n
 * `a` = -1;
 *
 * @param reterr	{ae2f_err_t*}
 * @param a		{const ae2f_MathInt*}
 * @param a_vec		{ae2f_oMathMem}
 * @param mask		{uint}
 * @param masklen	{uint8_t}
 * */
#define __ae2f_MathIntFill(reterr, a, a_vec, mask, masklen)                    \
  {                                                                            \
    if (!(masklen) || (reterr) && *(reterr))                                   \
      ;                                                                        \
    else if (!((a) && (a_vec)))                                                \
      (reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);                     \
    else {                                                                     \
      struct {                                                                 \
        size_t abegpq, i, j;                                                   \
        uint8_t abegpr : 3;                                                    \
      } __ae2f_MathIntFillVar;                                                 \
                                                                               \
      for (__ae2f_MathIntFillVar.j = 0; __ae2f_MathIntFillVar.j < (a)->sz;     \
           __ae2f_MathIntFillVar.j++) {                                        \
        __ae2f_MathIntFillVar.abegpq =                                         \
            ((a)->vecbegpoint + __ae2f_MathIntFillVar.j) >> 3;                 \
        __ae2f_MathIntFillVar.abegpr =                                         \
            ((a)->vecbegpoint + __ae2f_MathIntFillVar.j) & 7;                  \
                                                                               \
        (a_vec)[__ae2f_MathIntFillVar.abegpq] = ae2f_BitVecSet(                \
            (a_vec)[__ae2f_MathIntFillVar.abegpq],                             \
            __ae2f_MathIntFillVar.abegpr,                                      \
            ae2f_BitVecGet(mask, __ae2f_MathIntFillVar.j % (masklen)));        \
      }                                                                        \
    }                                                                          \
  }

/**
 * @macro __ae2f_MathIntCmpZero
 * @brief
 * `out` = `in` cmp 0
 *
 * @return
 * `ae2f_CmpFunRet_LISLESSER`	means `in` < 0 \n
 * `ae2f_CmpFunRet_RISLESSER`	means `in` > 0 \n
 * `ae2f_CmpFunRet_EQUAL`	means `in` == 0
 *
 * @param reterr	{ae2f_err_t*}
 * @param in		{const ae2f_MathInt*}
 * @param in_vec	{ae2f_iMathMem}
 * @param out		{ae2f_CmpFunRet_t*}
 * */
#define __ae2f_MathIntCmpZero(reterr, in, in_vec, out)                         \
  {                                                                            \
    if (!(out) || ((reterr) && *(reterr)))                                     \
      ;                                                                        \
    else if (!((in) && (in_vec))) {                                            \
      (reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);                     \
    } else {                                                                   \
      struct {                                                                 \
        size_t i, ivecbpq;                                                     \
        uint8_t ivecbpr : 3;                                                   \
      } __ae2f_MathIntCmpZeroVar;                                              \
                                                                               \
      if ((in)->sign &&                                                        \
          ae2f_BitVecGet((in_vec)[((in)->vecbegpoint + (in)->sz - 1) >> 3],    \
                         ((in)->vecbegpoint + (in)->sz - 1) & 7)) {            \
        *(out) = ae2f_CmpFunRet_LISLESSER;                                     \
      } else {                                                                 \
                                                                               \
        *(out) = ae2f_CmpFunRet_EQUAL;                                         \
        for (__ae2f_MathIntCmpZeroVar.i = 0;                                   \
             __ae2f_MathIntCmpZeroVar.i < (in)->sz;                            \
             __ae2f_MathIntCmpZeroVar.i++) {                                   \
          bool _ = 0;                                                          \
          __ae2f_MathIntCmpZeroVar.ivecbpr =                                   \
              ((in)->vecbegpoint + __ae2f_MathIntCmpZeroVar.i) & 7;            \
          __ae2f_MathIntCmpZeroVar.ivecbpq =                                   \
              ((in)->vecbegpoint + __ae2f_MathIntCmpZeroVar.i) >> 3;           \
                                                                               \
          if ((_ = ae2f_BitVecGet((in_vec)[__ae2f_MathIntCmpZeroVar.ivecbpq],  \
                                  __ae2f_MathIntCmpZeroVar.ivecbpr))) {        \
            *(out) = ae2f_CmpFunRet_RISLESSER;                                 \
            break;                                                             \
          }                                                                    \
        }                                                                      \
      }                                                                        \
    }                                                                          \
  }

/**
 * @macro __ae2f_MathIntCmp
 * @brief
 * `out` = `a` cmp `b`
 *
 * @return
 * `ae2f_cmpfunret_lislesser`	means `a` < `b` \n
 * `ae2f_cmpfunret_rislesser`	means `a` > `b` \n
 * `ae2f_cmpfunret_equal`	means `a` == `b`
 *
 * @param reterr	{ae2f_err_t*}
 * @param a		{const ae2f_MathInt*}
 * @param a_vec		{ae2f_iMathMem}
 * @param b		{const ae2f_MathInt*}
 * @param b_vec		{ae2f_iMathMem}
 * @param out		{ae2f_CmpFunRet_t*}
 * */
#define __ae2f_MathIntCmp(errret, a, a_vec, b, b_vec, out)                     \
  {                                                                            \
    if ((errret) && *(errret))                                                 \
      ;                                                                        \
    else if (!((out) && (a) && (a_vec) && (b) && (b_vec)))                     \
      (errret) && (*(errret) |= ae2f_errGlob_PTR_IS_NULL);                     \
    else if ((a)->sz - (a)->sign < 1 || (b)->sz - (b)->sign < 1)               \
      (errret) && (*(errret) |= ae2f_errGlob_WRONG_OPERATION);                 \
    else {                                                                     \
      struct {                                                                 \
        size_t sz_gt, i, avpq, bvpq, avp, bvp;                                 \
        int8_t cmp;                                                            \
        uint8_t sign : 2;                                                      \
        uint8_t avpr : 3;                                                      \
        uint8_t bvpr : 3;                                                      \
      } __ae2f_MathIntCmpVar;                                                  \
                                                                               \
      __ae2f_MathIntCmpVar.sign = 0;                                           \
      __ae2f_MathIntCmpVar.sz_gt = (a)->sz < (b)->sz ? (b)->sz : (a)->sz;      \
                                                                               \
      *(out) = 0;                                                              \
      if ((__ae2f_MathIntCmpVar.sign =                                         \
               ((a)->sign &&                                                   \
                ae2f_BitVecGet((a_vec)[((a)->vecbegpoint + (a)->sz - 1) >> 3], \
                               (((a)->vecbegpoint + (a)->sz - 1) & 7)))) !=    \
          ((b)->sign &&                                                        \
           ae2f_BitVecGet((b_vec)[((b)->vecbegpoint + (b)->sz - 1) >> 3],      \
                          (((b)->vecbegpoint + (b)->sz - 1) & 7)))) {          \
        /** Two signs are different */                                         \
        *(out) = __ae2f_MathIntCmpVar.sign /* is sign of a negative */         \
                     ? ae2f_CmpFunRet_LISLESSER                                \
                     : ae2f_CmpFunRet_RISLESSER;                               \
      } else                                                                   \
        for (__ae2f_MathIntCmpVar.i = __ae2f_MathIntCmpVar.sz_gt - 1;          \
             __ae2f_MathIntCmpVar.i != ae2f_static_cast(size_t, -1);           \
             __ae2f_MathIntCmpVar.i--) {                                       \
          __ae2f_MathIntCmpVar.avp =                                           \
              (a)->vecbegpoint + __ae2f_MathIntCmpVar.i,                       \
          __ae2f_MathIntCmpVar.avpr = __ae2f_MathIntCmpVar.avp & 7,            \
          __ae2f_MathIntCmpVar.avpq = __ae2f_MathIntCmpVar.avpr >> 3           \
                                                                               \
              ,                                                                \
          __ae2f_MathIntCmpVar.bvp =                                           \
              (b)->vecbegpoint + __ae2f_MathIntCmpVar.i,                       \
          __ae2f_MathIntCmpVar.bvpr = __ae2f_MathIntCmpVar.bvp & 7,            \
          __ae2f_MathIntCmpVar.bvpq = __ae2f_MathIntCmpVar.bvp >> 3;           \
          __ae2f_MathIntCmpVar.cmp =                                           \
              ae2f_static_cast(                                                \
                  int8_t,                                                      \
                  __ae2f_MathIntCmpVar.i < (a)->sz                             \
                      ? ae2f_BitVecGet((a_vec)[__ae2f_MathIntCmpVar.avpq],     \
                                       __ae2f_MathIntCmpVar.avpr)              \
                      : __ae2f_MathIntCmpVar.sign) -                           \
              ae2f_static_cast(                                                \
                  int8_t,                                                      \
                  __ae2f_MathIntCmpVar.i < (b)->sz                             \
                      ? ae2f_BitVecGet((b_vec)[__ae2f_MathIntCmpVar.bvpq],     \
                                       __ae2f_MathIntCmpVar.bvpr)              \
                      : __ae2f_MathIntCmpVar.sign);                            \
          /* is abs(a) greater */                                              \
          if (__ae2f_MathIntCmpVar.cmp) {                                      \
            *(out) = __ae2f_MathIntCmpVar.cmp;                                 \
            break;                                                             \
          }                                                                    \
        }                                                                      \
    }                                                                          \
  }

/**
 * @macro __ae2f_MathIntBitL
 * @brief
 * `in` << `bitcount`;
 * @param reterr	{ae2f_err_t*}
 * @param bitcount	{intptr_t}
 * @param in		{const ae2f_MathInt*}
 * @param in_vec	{ae2f_iMathMem}
 * @param out		{const ae2f_MathInt*}
 * @param out_vec	{ae2f_oMathMem}
 * */
#define __ae2f_MathIntBitL(reterr, bitcount, in, in_vec, out, out_vec)         \
  {                                                                            \
    if (!(bitcount) && (reterr) && *(reterr))                                  \
      ;                                                                        \
    else if (!((in) && (in_vec) && (out) && (out_vec)))                        \
      (reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);                     \
    else if ((in)->sz + (bitcount) < (in)->sz)                                 \
      (reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);                     \
    else {                                                                     \
      struct {                                                                 \
        size_t c, i, osz, _o, _i;                                              \
      } __ae2f_MathIntBitLVar;                                                 \
      for (__ae2f_MathIntBitLVar.i = 0;                                        \
           __ae2f_MathIntBitLVar.i < (bitcount) &&                             \
           __ae2f_MathIntBitLVar.i < (out)->sz;                                \
           __ae2f_MathIntBitLVar.i++) {                                        \
        __ae2f_MathIntBitLVar._o =                                             \
            ((out)->vecbegpoint + __ae2f_MathIntBitLVar.i);                    \
        (out_vec)[__ae2f_MathIntBitLVar._o >> 3] =                             \
            ae2f_BitVecSet((out_vec)[__ae2f_MathIntBitLVar._o >> 3],           \
                           __ae2f_MathIntBitLVar._o & 7, 0);                   \
      }                                                                        \
      for (; (__ae2f_MathIntBitLVar.i) < (out)->sz &&                          \
             (__ae2f_MathIntBitLVar.i) < (in)->sz + (bitcount);                \
           __ae2f_MathIntBitLVar.i++) {                                        \
        __ae2f_MathIntBitLVar._o =                                             \
            (out)->vecbegpoint + __ae2f_MathIntBitLVar.i;                      \
        __ae2f_MathIntBitLVar._i =                                             \
            (in)->vecbegpoint + __ae2f_MathIntBitLVar.i;                       \
        (out_vec)[__ae2f_MathIntBitLVar._o >> 3] = ae2f_BitVecSet(             \
            (out_vec)[__ae2f_MathIntBitLVar._o >> 3],                          \
            __ae2f_MathIntBitLVar._o & 7,                                      \
            ae2f_BitVecGet((in_vec)[__ae2f_MathIntBitLVar._i >> 3],            \
                           __ae2f_MathIntBitLVar._i & 7));                     \
      }                                                                        \
                                                                               \
      for (; __ae2f_MathIntBitLVar.i < (out)->sz; __ae2f_MathIntBitLVar.i++) { \
        __ae2f_MathIntBitLVar._o =                                             \
            ((out)->vecbegpoint + __ae2f_MathIntBitLVar.i);                    \
        (out_vec)[__ae2f_MathIntBitLVar._o >> 3] =                             \
            ae2f_BitVecSet((out_vec)[__ae2f_MathIntBitLVar._o >> 3],           \
                           __ae2f_MathIntBitLVar._o & 7, 0);                   \
      }                                                                        \
    }                                                                          \
  }

/**
 * @macro __ae2f_MathIntMul
 * @brief
 * `out` = `a` * `b`;
 *
 * @param reterr	{ae2f_MathMemOutErr}
 * @param count		{size_t}
 * @param a		{const ae2f_MathInt*}
 * @param a_vec		{ae2f_iMathMem}
 * @param b		{const ae2f_MathInt*}
 * @param b_vec		{ae2f_iMathMem}
 * @param out		{const ae2f_MathInt*}
 * @param out_vec	{ae2f_oMathMem}
 * */
#define __ae2f_MathIntMul(reterr, a, a_vec, b, b_vec, out, out_vec)            \
  {                                                                            \
    if ((reterr) && *(reterr))                                                 \
      ;                                                                        \
    else if (!((a) && (a_vec) && (b) && (b_vec) && (out) && (out_vec)))        \
      (reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);                     \
    else {                                                                     \
      struct {                                                                 \
        size_t i, oveci;                                                       \
        bool sign;                                                             \
        ae2f_MathInt o[1];                                                     \
      } __mulvar;                                                              \
      __mulvar.sign = __ae2f_MathIntIsNegative(a, a_vec); /* sign of a */      \
      *__mulvar.o = *(out);                                                    \
                                                                               \
      __mulvar.i = __mulvar.oveci = 0;                                         \
      if (__mulvar.sign) {                                                     \
        __ae2f_MathIntFlip(reterr, b, b_vec, out, out_vec); /* complement 2 */ \
      } else {                                                                 \
        __ae2f_MathIntFill(reterr, out, out_vec, 0, 1);                        \
      }                                                                        \
      while ((out)->sz && __mulvar.i < (a)->sz - __mulvar.sign) {              \
        if (__mulvar.sign ^                                                    \
            ae2f_BitVecGet((((a)->vecbegpoint + __mulvar.i) >> 3)[(a_vec)],    \
                           ((a)->vecbegpoint + __mulvar.i) &                   \
                               7)) { /** Addition (conditional) */             \
                                                                               \
          if (__mulvar.sign) {                                                 \
            __ae2f_MathIntSub(reterr, b, b_vec, __mulvar.o,                    \
                              (out_vec) + __mulvar.oveci, __mulvar.o,          \
                              (out_vec) + __mulvar.oveci);                     \
          }                                                                    \
                                                                               \
          else {                                                               \
            __ae2f_MathIntAdd(reterr, b, b_vec, __mulvar.o,                    \
                              (out_vec) + __mulvar.oveci, __mulvar.o,          \
                              (out_vec) + __mulvar.oveci);                     \
          }                                                                    \
        }                                                                      \
                                                                               \
        /** Increament */                                                      \
        __mulvar.i++;                                                          \
        (__mulvar.o)->sz--;                                                    \
        (__mulvar.o)->vecbegpoint++;                                           \
                                                                               \
        if (!((__mulvar.o)->vecbegpoint & 7)) {                                \
          (__mulvar.o)->vecbegpoint = 0;                                       \
          __mulvar.oveci++;                                                    \
        }                                                                      \
      }                                                                        \
    }                                                                          \
  }

/**
 * @macro __ae2f_MathIntSz
 * @brief retsz = sizeof(`a`);
 * @param retsz	{size_t*}
 * @param a	{const ae2f_MathInt}
 * @param a_vec	{ae2f_iMathMem}
 * */
#define __ae2f_MathIntSz(retsz, a, a_vec)                                      \
  {                                                                            \
    if (!(retsz))                                                              \
      ;                                                                        \
    else if (!((a) && (a_vec))) {                                              \
      *(retsz) = -1;                                                           \
    } else {                                                                   \
      struct {                                                                 \
        size_t sz;                                                             \
      } __ae2f_MathIntSzVar;                                                   \
      __ae2f_MathIntSzVar.sz = (a)->sz - 1;                                    \
      for (; __ae2f_MathIntSzVar.sz != ae2f_static_cast(size_t, -1);           \
           __ae2f_MathIntSzVar.sz--) {                                         \
        if (ae2f_BitVecGet(                                                    \
                (a_vec)[(__ae2f_MathIntSzVar.sz + (a)->vecbegpoint) >> 3],     \
                (__ae2f_MathIntSzVar.sz + (a)->vecbegpoint) & 7))              \
          break;                                                               \
      }                                                                        \
      *(retsz) = __ae2f_MathIntSzVar.sz + 1;                                   \
    }                                                                          \
  }

#define ae2f_MathIntBump_POSITIVE 0
#define ae2f_MathIntBump_NEGATIVE 1

/**
 * @macro	__ae2f_MathIntBump
 * @brief
 * if (`bump`) `a`--; else `a`++;
 * @param reterr	{ae2f_err_t*}
 * @param bump		{uint8_t}
 * @param a		{const ae2f_MathInt*}
 * @param a_vec		{ae2f_oMathMem}
 * */
#define __ae2f_MathIntBump(reterr, bump, a, a_vec)                             \
  {                                                                            \
    if ((reterr) && *(reterr))                                                 \
      ;                                                                        \
    else if (!((a) && (a_vec))) {                                              \
      if (reterr)                                                              \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
    } else {                                                                   \
      struct {                                                                 \
        size_t i, j;                                                           \
        uint8_t b, c;                                                          \
      } __ae2f_MathIntBumpVar;                                                 \
                                                                               \
      __ae2f_MathIntBumpVar.b = 0b10;                                          \
                                                                               \
      for (__ae2f_MathIntBumpVar.j = 0; __ae2f_MathIntBumpVar.j < (a)->sz;     \
           __ae2f_MathIntBumpVar.j++) {                                        \
        __ae2f_MathIntBumpVar.c =                                              \
            a_vec[((a)->vecbegpoint + __ae2f_MathIntBumpVar.j) >> 3];          \
        __ae2f_MathIntBumpVar.b =                                              \
            (__ae2f_MathIntBumpVar.b >> 1) + !!(bump) +                        \
            ae2f_BitVecGet(__ae2f_MathIntBumpVar.c,                            \
                           ((a)->vecbegpoint + __ae2f_MathIntBumpVar.j) & 7);  \
        (a_vec)[((a)->vecbegpoint + __ae2f_MathIntBumpVar.j) >> 3] =           \
            ae2f_BitVecSet(__ae2f_MathIntBumpVar.c, ((a)->vecbegpoint) & 7,    \
                           __ae2f_MathIntBumpVar.b & 1);                       \
      }                                                                        \
    }                                                                          \
  }

/**
 * @warning
 * It does not handle negative values.
 *
 * @brief
 * Unsigned division
 *
 * `r` = `a`; `q` = `r` / `b`; `r` %=
 * `b`;
 *
 * @param reterr	{ae2f_MathMemOutErr}
 * @param count		{size_t}
 * @param a		{const ae2f_MathInt*}
 * @param a_vec		{ae2f_iMathMem}
 * @param b		{const ae2f_MathInt*}
 * @param b_vec		{ae2f_iMathMem}
 * @param q		{const ae2f_MathInt*}
 * @param q_vec		{ae2f_oMathMem}
 * @param r		{const ae2f_MathInt*}
 * @param r_vec		{ae2f_oMathMem}
 * */
#define __ae2f_MathIntDivU(reterr, a, a_vec, b, b_vec, q, q_vec, r, r_vec)     \
  {                                                                            \
    struct {                                                                   \
      size_t j, ridx2;                                                         \
      ae2f_CmpFunRet_t cmpret;                                                 \
      ae2f_MathInt _r, r2, _b, _q;                                             \
    } __var;                                                                   \
    if ((reterr) && *(reterr))                                                 \
      ;                                                                        \
                                                                               \
    else if (!((a) && (a_vec) && (b) && (b_vec) && (q) && (q_vec) && (r) &&    \
               (r_vec))) {                                                     \
                                                                               \
      if (reterr)                                                              \
        *(reterr) = ae2f_errGlob_PTR_IS_NULL;                                  \
    }                                                                          \
                                                                               \
    else {                                                                     \
      __ae2f_MathIntFill(reterr, q, q_vec, 0, 1);                              \
      __ae2f_MathIntCast(reterr, a, a_vec, r, r_vec);                          \
                                                                               \
      __var.cmpret = 0;                                                        \
      __var._r = *(r);                                                         \
      __var.r2 = ae2f_RecordMk(ae2f_MathInt, 0, 0, (b)->sz);                   \
      __var._b = *(b);                                                         \
      __var._q = *(q);                                                         \
      __ae2f_MathIntCmpZero(reterr, &__var._b, b_vec, &__var.cmpret);          \
      if (!__var.cmpret) /* `b` is zero.                                       \
      terminating...                                                           \
      */                                                                       \
      {                                                                        \
        (reterr) && (*(reterr) |= ae2f_errGlob_WRONG_OPERATION);               \
      } else {                                                                 \
        __var._b.sign = __var._r.sign = __var._q.sign = 0;                     \
        __ae2f_MathIntSz(&__var._r.sz, &__var._r, r_vec);                      \
        __ae2f_MathIntSz(&__var._b.sz, &__var._b, b_vec);                      \
        if (__var._b.sz <= __var._r.sz)                                        \
          for (__var.j = __var._r.sz - __var._b.sz - 1;                        \
               __var.j != ae2f_static_cast(size_t, -1); __var.j--) {           \
            __var.r2.vecbegpoint =                                             \
                (ae2f_static_cast(uint8_t, __var._r.vecbegpoint) + __var.j) &  \
                7;                                                             \
            __var.ridx2 = ((__var._r.vecbegpoint + __var.j) >> 3);             \
            /* b cmp r2 */                                                     \
            __ae2f_MathIntCmp(reterr, &__var._b, b_vec, &__var.r2,             \
                              (r_vec) + __var.ridx2, &__var.cmpret);           \
            /* if b <= r2: r2 -= b; */                                         \
            if ((__var.cmpret) <= 0) {                                         \
              __ae2f_MathIntSub(reterr, &__var.r2, (r_vec) + __var.ridx2,      \
                                &__var._b, b_vec, &__var.r2,                   \
                                (r_vec) + __var.ridx2);                        \
                                                                               \
              /** q */                                                         \
              if (__var.j < __var._q.sz) {                                     \
                (q_vec)[(__var._q.vecbegpoint + __var.j) >> 3] |=              \
                    1 << ((__var._q.vecbegpoint + __var.j) & 7);               \
              }                                                                \
            }                                                                  \
          }                                                                    \
      }                                                                        \
    }                                                                          \
  }

#endif
