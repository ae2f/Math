#ifndef ae2f_Math_int_imp_h
#define ae2f_Math_int_imp_h

#include "./Util.h"
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
 * @param _out_int_idx	{size_t*}
 * */
#define __ae2f_MathIntNxt(_reterr, _idx, _int, _int_vec, _out_int,             \
                          _out_int_idx)                                        \
  {                                                                            \
    if (!((_int) && (_out_int) && (_int_vec) && (_out_int_idx))) {             \
      if ((_reterr))                                                           \
        *ae2f_reinterpret_cast(ae2f_MathMemOutErr, _reterr) |=                 \
            ae2f_errGlob_PTR_IS_NULL;                                          \
    } else {                                                                   \
      struct __ae2f_MathIntNxtVar_t {                                          \
        size_t __len;                                                          \
      } __ae2f_MathIntNxtVar;                                                  \
      __ae2f_MathIntNxtVar.__len = (_int)->vecbegpoint + (_int)->sz * (_idx);  \
      *(_out_int) = *(_int);                                                   \
      (_out_int)->vecbegpoint = __ae2f_MathIntNxtVar.__len;                    \
      *(_out_int_idx) = (__ae2f_MathIntNxtVar.__len >> 3);                     \
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
    } else if ((__i_vec) == (__o_vec) &&                                       \
               ((__in) == (__out) ||                                           \
                ((__in)->sz == (__out)->sz && (__in)->sign == (__out)->sign && \
                 (__in)->vecbegpoint == (__out)->vecbegpoint))) {              \
    } else {                                                                   \
      struct __ae2f_MathIntCastVar_t {                                         \
        size_t j;                                                              \
        ae2f_MathUtilDiv8(size_t) ovec, ivec;                                  \
      } __ae2f_MathIntCastVar;                                                 \
      /** Fill them all without noticing if it's signed */                     \
      for (__ae2f_MathIntCastVar.j = 0;                                        \
           __ae2f_MathIntCastVar.j <                                           \
               (__in)->sz - ae2f_static_cast(size_t, (__in)->sign) &&          \
           __ae2f_MathIntCastVar.j < (__out)->sz;                              \
           __ae2f_MathIntCastVar.j++) {                                        \
        __ae2f_MathIntCastVar.ovec.p =                                         \
            (__out)->vecbegpoint + __ae2f_MathIntCastVar.j;                    \
                                                                               \
        __ae2f_MathIntCastVar.ivec.p =                                         \
            (__in)->vecbegpoint + __ae2f_MathIntCastVar.j;                     \
                                                                               \
        (__o_vec)[__ae2f_MathIntCastVar.ovec.b.q] = ae2f_BitVecSet(            \
            (__o_vec)[__ae2f_MathIntCastVar.ovec.b.q],                         \
            __ae2f_MathIntCastVar.ovec.b.r /*idx*/                             \
            ,                                                                  \
            ae2f_BitVecGet((__i_vec)[__ae2f_MathIntCastVar.ivec.b.q],          \
                           __ae2f_MathIntCastVar.ivec.b.r));                   \
      }                                                                        \
                                                                               \
      /*                                                                       \
       * Rest of them will be zero.                                            \
       * When signed, rest will be filled with sign bit.                       \
       * */                                                                    \
      for (; __ae2f_MathIntCastVar.j < (__out)->sz;                            \
           __ae2f_MathIntCastVar.j++) {                                        \
        __ae2f_MathIntCastVar.ovec.p =                                         \
            (__out)->vecbegpoint + __ae2f_MathIntCastVar.j;                    \
                                                                               \
        __ae2f_MathIntCastVar.ivec.p =                                         \
            (__in)->vecbegpoint + __ae2f_MathIntCastVar.j;                     \
                                                                               \
        __ae2f_MathIntCastVar.ovec.b.q[__o_vec] =                              \
            ae2f_BitVecSet(__ae2f_MathIntCastVar.ovec.b.q[__o_vec],            \
                           __ae2f_MathIntCastVar.ovec.b.r,                     \
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
      struct __ae2f_MathIntFlipVar_t {                                         \
        size_t j;                                                              \
        ae2f_MathUtilDiv8(size_t) ovec, ivec;                                  \
        __ae2f_MathUtilFlag2(3, unsigned sbit : 1;) buf;                       \
      } __ae2f_MathIntFlipVar;                                                 \
      /** +1 for second compliment */                                          \
      __ae2f_MathIntFlipVar.buf.a = 0b10;                                      \
      __ae2f_MathIntFlipVar.ivec.p = (__i)->vecbegpoint + (__i)->sz - 1;       \
                                                                               \
      __ae2f_MathIntFlipVar.buf.b.sbit =                                       \
          (__o)->sign &&                                                       \
          ae2f_BitVecGet((__i_vec)[__ae2f_MathIntFlipVar.ivec.b.q],            \
                         __ae2f_MathIntFlipVar.ivec.b.r);                      \
                                                                               \
      for (__ae2f_MathIntFlipVar.j = 0; __ae2f_MathIntFlipVar.j < (__o)->sz;   \
           __ae2f_MathIntFlipVar.j++) {                                        \
        __ae2f_MathIntFlipVar.ovec.p =                                         \
            (__o)->vecbegpoint + __ae2f_MathIntFlipVar.j;                      \
                                                                               \
        __ae2f_MathIntFlipVar.ivec.p =                                         \
            (__i)->vecbegpoint + __ae2f_MathIntFlipVar.j;                      \
                                                                               \
        __ae2f_MathIntFlipVar.buf.a =                                          \
            !(__ae2f_MathIntFlipVar.j < (__i)->sz                              \
                  ? ae2f_BitVecGet((__i_vec)[__ae2f_MathIntFlipVar.ivec.b.q],  \
                                   __ae2f_MathIntFlipVar.ivec.b.r)             \
                  : __ae2f_MathIntFlipVar.buf.b.sbit) /** Compliment 1 */      \
            + (__ae2f_MathIntFlipVar.buf.b._1);                                \
                                                                               \
        (__o_vec)[__ae2f_MathIntFlipVar.ovec.b.q] = ae2f_BitVecSet(            \
            (__o_vec)[__ae2f_MathIntFlipVar.ovec.b.q],                         \
            __ae2f_MathIntFlipVar.ovec.b.r, __ae2f_MathIntFlipVar.buf.b._0);   \
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
      struct __ae2f_MathIntAddVar_t {                                          \
        size_t j;                                                              \
        ae2f_MathUtilDiv8(size_t) ovec, avec, bvec;                            \
        __ae2f_MathUtilFlag2(4, unsigned sb_0 : 1; unsigned sb_1 : 1;) buf;    \
      } __ae2f_MathIntAddVar;                                                  \
      __ae2f_MathIntAddVar.buf.a = 0b00; /**                                   \
                                          * 0: a                               \
                                          * 1: b                               \
                                          * */                                 \
                                                                               \
      __ae2f_MathIntAddVar.buf.b.sb_0 =                                        \
          ((_a)->sign &&                                                       \
           ae2f_BitVecGet((_a_vec)[((_a)->vecbegpoint + (_a)->sz - 1) >> 3],   \
                          ((_a)->vecbegpoint + (_a)->sz - 1) & 7));            \
                                                                               \
      __ae2f_MathIntAddVar.buf.b.sb_1 =                                        \
          (((_b)->sign &&                                                      \
            ae2f_BitVecGet((_b_vec)[((_b)->vecbegpoint + (_b)->sz - 1) >> 3],  \
                           ((_b)->vecbegpoint + (_b)->sz - 1) & 7)));          \
                                                                               \
      for (__ae2f_MathIntAddVar.j = 0; __ae2f_MathIntAddVar.j < (_o)->sz;      \
           __ae2f_MathIntAddVar.j++) {                                         \
        __ae2f_MathIntAddVar.avec.p =                                          \
            (_a)->vecbegpoint + __ae2f_MathIntAddVar.j;                        \
                                                                               \
        __ae2f_MathIntAddVar.bvec.p =                                          \
            (_b)->vecbegpoint + __ae2f_MathIntAddVar.j;                        \
                                                                               \
        __ae2f_MathIntAddVar.ovec.p =                                          \
            (_o)->vecbegpoint + __ae2f_MathIntAddVar.j;                        \
                                                                               \
        __ae2f_MathIntAddVar.buf.a =                                           \
            (__ae2f_MathIntAddVar.j < (_a)->sz                                 \
                 ? ae2f_BitVecGet(__ae2f_MathIntAddVar.avec.b.q[_a_vec],       \
                                  __ae2f_MathIntAddVar.avec.b.r)               \
                 : __ae2f_MathIntAddVar.buf.b.sb_0) +                          \
            (__ae2f_MathIntAddVar.j < (_b)->sz                                 \
                 ? ae2f_BitVecGet(__ae2f_MathIntAddVar.bvec.b.q[_b_vec],       \
                                  __ae2f_MathIntAddVar.bvec.b.r)               \
                 : __ae2f_MathIntAddVar.buf.b.sb_1) +                          \
            (__ae2f_MathIntAddVar.buf.b._1);                                   \
        __ae2f_MathIntAddVar.ovec.b.q[_o_vec] = ae2f_BitVecSet(                \
            __ae2f_MathIntAddVar.ovec.b.q[_o_vec],                             \
            __ae2f_MathIntAddVar.ovec.b.r, __ae2f_MathIntAddVar.buf.b._0);     \
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
      struct __ae2f_MathIntSubVar_t {                                          \
        size_t j;                                                              \
        ae2f_MathUtilDiv8(size_t) ovec, avec, bvec;                            \
        __ae2f_MathUtilFlag2(4, unsigned sb_0 : 1; unsigned sb_1 : 1;) buf;    \
      } __ae2f_MathIntAddVar;                                                  \
      __ae2f_MathIntAddVar.buf.a = 0b10; /**                                   \
                                          * 0: a                               \
                                          * 1: b                               \
                                          * */                                 \
                                                                               \
      __ae2f_MathIntAddVar.buf.b.sb_0 =                                        \
          ((_a)->sign &&                                                       \
           ae2f_BitVecGet((_a_vec)[((_a)->vecbegpoint + (_a)->sz - 1) >> 3],   \
                          ((_a)->vecbegpoint + (_a)->sz - 1) & 7));            \
                                                                               \
      __ae2f_MathIntAddVar.buf.b.sb_1 =                                        \
          (((_b)->sign &&                                                      \
            ae2f_BitVecGet((_b_vec)[((_b)->vecbegpoint + (_b)->sz - 1) >> 3],  \
                           ((_b)->vecbegpoint + (_b)->sz - 1) & 7)));          \
                                                                               \
      for (__ae2f_MathIntAddVar.j = 0; __ae2f_MathIntAddVar.j < (_o)->sz;      \
           __ae2f_MathIntAddVar.j++) {                                         \
        __ae2f_MathIntAddVar.avec.p =                                          \
            (_a)->vecbegpoint + __ae2f_MathIntAddVar.j;                        \
                                                                               \
        __ae2f_MathIntAddVar.bvec.p =                                          \
            (_b)->vecbegpoint + __ae2f_MathIntAddVar.j;                        \
                                                                               \
        __ae2f_MathIntAddVar.ovec.p =                                          \
            (_o)->vecbegpoint + __ae2f_MathIntAddVar.j;                        \
                                                                               \
        __ae2f_MathIntAddVar.buf.a =                                           \
            (__ae2f_MathIntAddVar.j < (_a)->sz                                 \
                 ? ae2f_BitVecGet(__ae2f_MathIntAddVar.avec.b.q[_a_vec],       \
                                  __ae2f_MathIntAddVar.avec.b.r)               \
                 : __ae2f_MathIntAddVar.buf.b.sb_0) +                          \
            !(__ae2f_MathIntAddVar.j < (_b)->sz                                \
                  ? ae2f_BitVecGet(__ae2f_MathIntAddVar.bvec.b.q[_b_vec],      \
                                   __ae2f_MathIntAddVar.bvec.b.r)              \
                  : __ae2f_MathIntAddVar.buf.b.sb_1) +                         \
            (__ae2f_MathIntAddVar.buf.b._1);                                   \
        __ae2f_MathIntAddVar.ovec.b.q[_o_vec] = ae2f_BitVecSet(                \
            __ae2f_MathIntAddVar.ovec.b.q[_o_vec],                             \
            __ae2f_MathIntAddVar.ovec.b.r, __ae2f_MathIntAddVar.buf.b._0);     \
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
#define __ae2f_MathIntFill(reterr, _a, a_vec, mask, masklen)                   \
  {                                                                            \
    if (!(masklen) || (reterr) && *(reterr))                                   \
      ;                                                                        \
    else if (!((_a) && (a_vec)))                                               \
      (reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);                     \
    else {                                                                     \
      struct __ae2f_MathIntFillVar_t {                                         \
        size_t j;                                                              \
        ae2f_MathUtilDiv8(size_t) abeg;                                        \
      } __ae2f_MathIntFillVar;                                                 \
                                                                               \
      for (__ae2f_MathIntFillVar.j = 0; __ae2f_MathIntFillVar.j < (_a)->sz;    \
           __ae2f_MathIntFillVar.j++) {                                        \
        __ae2f_MathIntFillVar.abeg.p =                                         \
            ((_a)->vecbegpoint + __ae2f_MathIntFillVar.j);                     \
                                                                               \
        (a_vec)[__ae2f_MathIntFillVar.abeg.b.q] = ae2f_BitVecSet(              \
            (a_vec)[__ae2f_MathIntFillVar.abeg.b.q],                           \
            __ae2f_MathIntFillVar.abeg.b.r,                                    \
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
      struct __ae2f_MathIntCmpZeroVar_t {                                      \
        size_t i;                                                              \
        ae2f_MathUtilDiv8(size_t) ivec;                                        \
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
          __ae2f_MathIntCmpZeroVar.ivec.p =                                    \
              ((in)->vecbegpoint + __ae2f_MathIntCmpZeroVar.i);                \
                                                                               \
          if ((ae2f_BitVecGet((in_vec)[__ae2f_MathIntCmpZeroVar.ivec.b.q],     \
                              __ae2f_MathIntCmpZeroVar.ivec.b.r))) {           \
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
#define __ae2f_MathIntCmp(errret, _a, a_vec, _b, b_vec, out)                   \
  {                                                                            \
    if ((errret) && *(errret))                                                 \
      ;                                                                        \
    else if (!((out) && (_a) && (a_vec) && (_b) && (b_vec)))                   \
      (errret) && (*(errret) |= ae2f_errGlob_PTR_IS_NULL);                     \
    else if ((_a)->sz - (_a)->sign < 1 || (_b)->sz - (_b)->sign < 1)           \
      (errret) && (*(errret) |= ae2f_errGlob_WRONG_OPERATION);                 \
    else {                                                                     \
      struct __ae2f_MathIntCmpVar_t {                                          \
        size_t sz_gt, i;                                                       \
        ae2f_MathUtilDiv8(size_t) av, bv;                                      \
        unsigned sign : 1;                                                     \
        int cmp : 2;                                                           \
      } __ae2f_MathIntCmpVar;                                                  \
                                                                               \
      __ae2f_MathIntCmpVar.sz_gt = (_a)->sz < (_b)->sz ? (_b)->sz : (_a)->sz;  \
                                                                               \
      *(out) = 0;                                                              \
      if ((__ae2f_MathIntCmpVar.sign =                                         \
               ((_a)->sign &&                                                  \
                ae2f_BitVecGet(                                                \
                    (a_vec)[((_a)->vecbegpoint + (_a)->sz - 1) >> 3],          \
                    (((_a)->vecbegpoint + (_a)->sz - 1) & 7)))) !=             \
          ((_b)->sign &&                                                       \
           ae2f_BitVecGet((b_vec)[((_b)->vecbegpoint + (_b)->sz - 1) >> 3],    \
                          (((_b)->vecbegpoint + (_b)->sz - 1) & 7)))) {        \
        /** Two signs are different */                                         \
        *(out) = __ae2f_MathIntCmpVar.sign /* is sign of a negative */         \
                     ? ae2f_CmpFunRet_LISLESSER                                \
                     : ae2f_CmpFunRet_RISLESSER;                               \
      } else                                                                   \
        for (__ae2f_MathIntCmpVar.i = __ae2f_MathIntCmpVar.sz_gt - 1;          \
             __ae2f_MathIntCmpVar.i != ae2f_static_cast(size_t, -1);           \
             __ae2f_MathIntCmpVar.i--) {                                       \
          __ae2f_MathIntCmpVar.av.p =                                          \
              (_a)->vecbegpoint + __ae2f_MathIntCmpVar.i;                      \
                                                                               \
          __ae2f_MathIntCmpVar.bv.p =                                          \
              (_b)->vecbegpoint + __ae2f_MathIntCmpVar.i;                      \
          __ae2f_MathIntCmpVar.cmp =                                           \
              ae2f_static_cast(                                                \
                  int8_t,                                                      \
                  __ae2f_MathIntCmpVar.i < (_a)->sz                            \
                      ? ae2f_BitVecGet((a_vec)[__ae2f_MathIntCmpVar.av.b.q],   \
                                       __ae2f_MathIntCmpVar.av.b.r)            \
                      : __ae2f_MathIntCmpVar.sign) -                           \
              ae2f_static_cast(                                                \
                  int8_t,                                                      \
                  __ae2f_MathIntCmpVar.i < (_b)->sz                            \
                      ? ae2f_BitVecGet((b_vec)[__ae2f_MathIntCmpVar.bv.b.q],   \
                                       __ae2f_MathIntCmpVar.bv.b.r)            \
                      : __ae2f_MathIntCmpVar.sign);                            \
          /* is abs(_a) greater */                                             \
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
      struct __ae2f_MathIntBitLVar_t {                                         \
        size_t c, i;                                                           \
        ae2f_MathUtilDiv8(size_t) _o, _i;                                      \
      } __ae2f_MathIntBitLVar;                                                 \
      for (__ae2f_MathIntBitLVar.i = 0;                                        \
           __ae2f_MathIntBitLVar.i < (bitcount) &&                             \
           __ae2f_MathIntBitLVar.i < (out)->sz;                                \
           __ae2f_MathIntBitLVar.i++) {                                        \
        __ae2f_MathIntBitLVar._o.a =                                           \
            ((out)->vecbegpoint + __ae2f_MathIntBitLVar.i);                    \
        (out_vec)[__ae2f_MathIntBitLVar._o.b.q] =                              \
            ae2f_BitVecSet((out_vec)[__ae2f_MathIntBitLVar._o.b.q],            \
                           __ae2f_MathIntBitLVar._o.b.r, 0);                   \
      }                                                                        \
      for (; (__ae2f_MathIntBitLVar.i) < (out)->sz &&                          \
             (__ae2f_MathIntBitLVar.i) < (in)->sz + (bitcount);                \
           __ae2f_MathIntBitLVar.i++) {                                        \
        __ae2f_MathIntBitLVar._o.a =                                           \
            (out)->vecbegpoint + __ae2f_MathIntBitLVar.i;                      \
        __ae2f_MathIntBitLVar._i.a =                                           \
            (in)->vecbegpoint + __ae2f_MathIntBitLVar.i;                       \
        (out_vec)[__ae2f_MathIntBitLVar._o.b.q] = ae2f_BitVecSet(              \
            (out_vec)[__ae2f_MathIntBitLVar._o.b.q],                           \
            __ae2f_MathIntBitLVar._o.b.r,                                      \
            ae2f_BitVecGet((in_vec)[__ae2f_MathIntBitLVar._i.b.q],             \
                           __ae2f_MathIntBitLVar._i.b.r));                     \
      }                                                                        \
                                                                               \
      for (; __ae2f_MathIntBitLVar.i < (out)->sz; __ae2f_MathIntBitLVar.i++) { \
        __ae2f_MathIntBitLVar._o.a =                                           \
            ((out)->vecbegpoint + __ae2f_MathIntBitLVar.i);                    \
        (out_vec)[__ae2f_MathIntBitLVar._o.b.q] =                              \
            ae2f_BitVecSet((out_vec)[__ae2f_MathIntBitLVar._o.b.q],            \
                           __ae2f_MathIntBitLVar._o.b.r, 0);                   \
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
#define __ae2f_MathIntMul(reterr, _a, a_vec, _b, b_vec, out, out_vec)          \
  {                                                                            \
    if ((reterr) && *(reterr))                                                 \
      ;                                                                        \
    else if (!((_a) && (a_vec) && (_b) && (b_vec) && (out) && (out_vec)))      \
      (reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);                     \
    else {                                                                     \
      struct __ae2f_MathIntMulVar_t {                                          \
        size_t i, oveci;                                                       \
        ae2f_MathInt o[1];                                                     \
        unsigned sign : 1;                                                     \
      } __mulvar;                                                              \
      __mulvar.sign = __ae2f_MathIntIsNegative(_a, a_vec); /* sign of a */     \
      *__mulvar.o = *(out);                                                    \
                                                                               \
      __mulvar.i = __mulvar.oveci = 0;                                         \
      if (__mulvar.sign) {                                                     \
        __ae2f_MathIntFlip(reterr, _b, b_vec, out,                             \
                           out_vec); /* complement 2 */                        \
      } else {                                                                 \
        __ae2f_MathIntFill(reterr, out, out_vec, 0, 1);                        \
      }                                                                        \
      while ((out)->sz && __mulvar.i < (_a)->sz - __mulvar.sign) {             \
        if (__mulvar.sign ^                                                    \
            ae2f_BitVecGet((((_a)->vecbegpoint + __mulvar.i) >> 3)[(a_vec)],   \
                           ((_a)->vecbegpoint + __mulvar.i) &                  \
                               7)) { /** Addition (conditional) */             \
                                                                               \
          if (__mulvar.sign) {                                                 \
            __ae2f_MathIntSub(reterr, _b, b_vec, __mulvar.o,                   \
                              (out_vec) + __mulvar.oveci, __mulvar.o,          \
                              (out_vec) + __mulvar.oveci);                     \
          }                                                                    \
                                                                               \
          else {                                                               \
            __ae2f_MathIntAdd(reterr, _b, b_vec, __mulvar.o,                   \
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
#define __ae2f_MathIntSz(retsz, _a, a_vec)                                     \
  {                                                                            \
    if (!(retsz))                                                              \
      ;                                                                        \
    else if (!((_a) && (a_vec))) {                                             \
      *(retsz) = -1;                                                           \
    } else {                                                                   \
      struct __ae2f_MathIntSzVar_t {                                           \
        size_t sz;                                                             \
      } __ae2f_MathIntSzVar;                                                   \
      __ae2f_MathIntSzVar.sz = (_a)->sz - 1;                                   \
      for (; __ae2f_MathIntSzVar.sz != ae2f_static_cast(size_t, -1);           \
           __ae2f_MathIntSzVar.sz--) {                                         \
        if (ae2f_BitVecGet(                                                    \
                (a_vec)[(__ae2f_MathIntSzVar.sz + (_a)->vecbegpoint) >> 3],    \
                (__ae2f_MathIntSzVar.sz + (_a)->vecbegpoint) & 7))             \
          break;                                                               \
      }                                                                        \
      *(retsz) = __ae2f_MathIntSzVar.sz + 1;                                   \
    }                                                                          \
  }

/**
 * @macro __ae2f_MathIntNullSz
 * @brief
 * Count of series of null[0]s on right size.
 * @param retsz	{ae2f_err_t}
 * @param _a	{const ae2f_MathInt*}
 * @param a_vec	{ae2f_iMathMem}
 * */
#define __ae2f_MathIntNullSz(retsz, _a, a_vec)                                 \
  {                                                                            \
    if ((retsz)) {                                                             \
      for (*(retsz) = 0;                                                       \
           *(retsz) < (_a)->sz &&                                              \
           !_ae2f_BitVecGetRanged((a_vec)[*(retsz) >> 3], *(retsz) & 7,        \
                                  (*(retsz) & 7) + 1, unsigned char);          \
           *(retsz)++)                                                         \
        ;                                                                      \
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
#define __ae2f_MathIntBump(reterr, bump, _a, a_vec)                            \
  {                                                                            \
    if ((reterr) && *(reterr))                                                 \
      ;                                                                        \
    else if (!((_a) && (a_vec))) {                                             \
      if (reterr)                                                              \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
    } else {                                                                   \
      struct __ae2f_MathIntBumpVar_t {                                         \
        size_t i, j;                                                           \
        uint8_t b, c;                                                          \
      } __ae2f_MathIntBumpVar;                                                 \
                                                                               \
      __ae2f_MathIntBumpVar.b = 0b10;                                          \
                                                                               \
      for (__ae2f_MathIntBumpVar.j = 0; __ae2f_MathIntBumpVar.j < (_a)->sz;    \
           __ae2f_MathIntBumpVar.j++) {                                        \
        __ae2f_MathIntBumpVar.c =                                              \
            a_vec[((_a)->vecbegpoint + __ae2f_MathIntBumpVar.j) >> 3];         \
        __ae2f_MathIntBumpVar.b =                                              \
            (__ae2f_MathIntBumpVar.b >> 1) + !!(bump) +                        \
            ae2f_BitVecGet(__ae2f_MathIntBumpVar.c,                            \
                           ((_a)->vecbegpoint + __ae2f_MathIntBumpVar.j) & 7); \
        (a_vec)[((_a)->vecbegpoint + __ae2f_MathIntBumpVar.j) >> 3] =          \
            ae2f_BitVecSet(__ae2f_MathIntBumpVar.c, ((_a)->vecbegpoint) & 7,   \
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
#define __ae2f_MathIntDivU(reterr, _a, a_vec, prm_b, b_vec, prm_q, q_vec,      \
                           prm_r, r_vec)                                       \
  {                                                                            \
    struct __ae2f_MathIntDivUVar_t {                                           \
      size_t j, ridx2;                                                         \
      ae2f_CmpFunRet_t cmpret;                                                 \
      ae2f_MathInt _r, r2, _b, _q;                                             \
    } __var;                                                                   \
    if ((reterr) && *(reterr))                                                 \
      ;                                                                        \
                                                                               \
    else if (!((_a) && (a_vec) && (prm_b) && (b_vec) && (prm_q) && (q_vec) &&  \
               (prm_r) && (r_vec))) {                                          \
                                                                               \
      if (reterr)                                                              \
        *(reterr) = ae2f_errGlob_PTR_IS_NULL;                                  \
    }                                                                          \
                                                                               \
    else {                                                                     \
      __ae2f_MathIntFill(reterr, prm_q, q_vec, 0, 1);                          \
      __ae2f_MathIntCast(reterr, _a, a_vec, prm_r, r_vec);                     \
                                                                               \
      __var.cmpret = 0;                                                        \
      __var._r = *(prm_r);                                                     \
      __var.r2.sz = (prm_b)->sz;                                               \
      __var.r2.vecbegpoint = 0;                                                \
      __var.r2.sign = 0;                                                       \
      __var._b = *(prm_b);                                                     \
      __var._q = *(prm_q);                                                     \
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
