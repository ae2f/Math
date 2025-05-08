#ifndef ae2f_Math_int_imp_h
#define ae2f_Math_int_imp_h

#include "./int.h"
#include <ae2f/BitVec.h>

/**
 * @warning
 * Following names are used in this macro. \n
 * Avoid passing these names to parameter if you could.
 *
 * - __len
 *
 * @brief
 * `_out_int` = `_int`[`_idx`];
 *
 * @param ae2f_err_t* _reterr
 * @param const ae2f_MathInt* _int
 * @param uintptr_t const _int_vec
 * @param intptr_t _idx
 * @param ae2f_MathInt* _out_int
 * @param uintptr_t** _out_int_vec
 * */
#define __ae2f_MathIntNxt(_reterr, _idx, _int, _int_vec, _out_int,             \
                          _out_int_vec)                                        \
  {                                                                            \
    if (!((_int) && (_out_int) && (_int_vec) && (_out_int_vec))) {             \
      if ((_reterr))                                                           \
        *ae2f_reinterpret_cast(ae2f_MathMemOutErr, _reterr) |=                 \
            ae2f_errGlob_PTR_IS_NULL;                                          \
    } else {                                                                   \
      const size_t __len = (_int)->vecbegpoint + (_int)->sz * (_idx);          \
      *(_out_int) = *(_int);                                                   \
      (_out_int)->vecbegpoint = __len & 7;                                     \
      *(_out_int_vec) = (_int_vec) + (__len >> 3);                             \
    }                                                                          \
  }

/**
 * @brief
 * `__i` < 0
 *
 * @param const ae2f_MathInt*	__i
 * @param const ae2f_MathMem	__v
 * */
#define __ae2f_MathIntIsNegative(__i, __v)                                     \
  ((__i) && (__i)->sign && (__v) &&                                            \
   ae2f_BitVecGet((__v)[((__i)->vecbegpoint + (__i)->sz - 1) >> 3],            \
                  ((__i)->vecbegpoint + (__i)->sz - 1) & 7))

/**
 * @warning
 * Following names are used in this macro. \n
 * Avoid passing these names to parameter if you could.
 *
 * - ovecbp
 * - ovecbpq
 * - ovecbpr
 * - ivecbp
 * - ivecbpq
 * - ivecbpr
 * - i
 * - j
 *
 * @brief
 * `__out` = `__in`
 *
 * @param ae2f_MathMemOutErr	reterr
 * @param size_t		count
 * @param const ae2f_MathInt*	__in
 * @param ae2f_iMathMem 	__in_vec
 * @param const ae2f_MathInt*	__out
 * @param ae2f_oMathMem		__out_vec
 *
 * @param ae2f_bMathMem& __i_vec
 * Its type must be an existing variable, sharing a same datatype with
 * `__in_vec`. \n If you're using a function, This could be `NULL` and is
 * encouraged to be.
 *
 * @param ae2f_bMathMem& __o_vec
 * Its type must be an existing variable, sharing a same datatype with
 * `__out_vec` \n If you're using a function, This could be `NULL` and is
 * encouraged to be.
 * */
#define __ae2f_MathIntCast(reterr, count, __in, __in_vec, __out, __out_vec,    \
                           __i_vec, __o_vec)                                   \
  do {                                                                         \
    if ((reterr) && *(reterr))                                                 \
      break;                                                                   \
    if (!(count)) {                                                            \
      break;                                                                   \
    }                                                                          \
    if (!(__in)) {                                                             \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!(__out)) {                                                            \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    if (!(__in_vec)) {                                                         \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!(__out_vec)) {                                                        \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    ae2f_MathInt __i;                                                          \
    ae2f_MathInt __o;                                                          \
                                                                               \
    size_t ovecbp, ovecbpq, ovecbpr                                            \
                                                                               \
        ,                                                                      \
        ivecbp, ivecbpq, ivecbpr                                               \
                                                                               \
        ,                                                                      \
        i, j;                                                                  \
                                                                               \
    for (i = 0; i < (count); i++) {                                            \
      __ae2f_MathIntNxt(0, i, (__in), (__in_vec), &(__i), &(__i_vec));         \
                                                                               \
      __ae2f_MathIntNxt(0, i, (__out), (__out_vec), &(__o), &(__o_vec));       \
                                                                               \
      /** Fill them all without noticing if it's signed */                     \
      for (j = 0;                                                              \
           j < __i.sz - ae2f_static_cast(size_t, __i.sign) && j < __o.sz;      \
           j++) {                                                              \
        ovecbp = __o.vecbegpoint + j;                                          \
        ovecbpq = ovecbp >> 3;                                                 \
        ovecbpr = ovecbp & 7;                                                  \
                                                                               \
        ivecbp = __i.vecbegpoint + j;                                          \
        ivecbpq = ivecbp >> 3;                                                 \
        ivecbpr = ivecbp & 7;                                                  \
                                                                               \
        (__o_vec)[ovecbpq] =                                                   \
            ae2f_BitVecSet((__o_vec)[ovecbpq], ovecbpr /*idx*/                 \
                           ,                                                   \
                           ae2f_BitVecGet((__i_vec)[ivecbpq], ivecbpr));       \
      }                                                                        \
                                                                               \
      /*                                                                       \
       * Rest of them will be zero.                                            \
       * When signed, rest will be filled with sign bit.                       \
       * */                                                                    \
      for (; j < __o.sz; j++) {                                                \
        ovecbp = __o.vecbegpoint + j;                                          \
        ovecbpq = ovecbp >> 3;                                                 \
        ovecbpr = ovecbp & 7;                                                  \
                                                                               \
        ivecbp = __i.vecbegpoint + j;                                          \
        ivecbpq = ivecbp >> 3;                                                 \
        ivecbpr = ivecbp & 7;                                                  \
                                                                               \
        ovecbpq[__o_vec] =                                                     \
            ae2f_BitVecSet(ovecbpq[__o_vec], ovecbpr,                          \
                           __ae2f_MathIntIsNegative(&__i, (__i_vec)));         \
      }                                                                        \
    }                                                                          \
  } while (0)

/**
 * @warning
 * Following names are used in this macro. \n
 * Avoid passing these names to parameter if you could.
 *
 * - buf
 * - ovecbp
 * - ovecbpq
 * - ovecbpr
 * - ivecbp
 * - ivecbpq
 * - ivecbpr
 * - sbit
 * - __i
 * - __o
 * - i
 * - j
 *
 * @brief
 * `__out` = -`__in`
 *
 * @param ae2f_MathMemOutErr	reterr
 * @param size_t		count
 * @param const ae2f_MathInt*	__in
 * @param ae2f_iMathMem		__in_vec
 * @param const ae2f_MathInt*	__out
 * @param ae2f_oMathMem		__out_vec
 *
 * @param ae2f_bMathMem& __i_vec
 * Its type must be an existing variable, sharing a same datatype with
 * `__in_vec`. \n If you're using a function, This could be `NULL` and is
 * encouraged to be.
 *
 * @param ae2f_bMathMem& __o_vec
 * Its type must be an existing variable, sharing a same datatype with
 * `__out_vec` \n If you're using a function, This could be `NULL` and is
 * encouraged to be.
 * */
#define __ae2f_MathIntFlip(reterr, count, __in, __in_vec, __out, __out_vec,    \
                           __i_vec, __o_vec)                                   \
  do {                                                                         \
    if ((reterr) && *(reterr))                                                 \
      break;                                                                   \
                                                                               \
    if (!(__in)) {                                                             \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!(__out)) {                                                            \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    if (!(__in_vec)) {                                                         \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!(__out_vec)) {                                                        \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    /** +1 for second compliment */                                            \
    uint8_t buf = 0b10;                                                        \
                                                                               \
    ae2f_MathInt __i;                                                          \
    ae2f_MathInt __o;                                                          \
                                                                               \
    size_t ovecbp, ovecbpq, ovecbpr                                            \
                                                                               \
        ,                                                                      \
        ivecbp, ivecbpq, ivecbpr                                               \
                                                                               \
        ,                                                                      \
        i, j;                                                                  \
    /** @brief sign bit */                                                     \
    bool sbit;                                                                 \
                                                                               \
    /** Iterates */                                                            \
    for (i = 0; i < (count); i++) {                                            \
      __ae2f_MathIntNxt(0, i, (__in), (__in_vec), &(__i), &(__i_vec));         \
                                                                               \
      __ae2f_MathIntNxt(0, i, (__out), (__out_vec), &(__o), &(__o_vec));       \
      ivecbp = __i.vecbegpoint + __i.sz - 1;                                   \
      ivecbpq = ivecbp >> 3;                                                   \
      ivecbpr = ivecbp & 7;                                                    \
                                                                               \
      sbit = __o.sign && ae2f_BitVecGet((__i_vec)[ivecbpq], ivecbpr);          \
                                                                               \
      for (j = 0; j < __o.sz; j++) {                                           \
        ovecbp = __o.vecbegpoint + j;                                          \
        ovecbpq = ovecbp >> 3;                                                 \
        ovecbpr = ovecbp & 7;                                                  \
                                                                               \
        ivecbp = __i.vecbegpoint + j;                                          \
        ivecbpq = ivecbp >> 3;                                                 \
        ivecbpr = ivecbp & 7;                                                  \
                                                                               \
        buf = !(j < __i.sz ? ae2f_BitVecGet((__i_vec)[ivecbpq], ivecbpr)       \
                           : sbit) /** Compliment 1 */                         \
              + (buf >> 1);                                                    \
                                                                               \
        (__out_vec)[ovecbpq] =                                                 \
            ae2f_BitVecSet((__out_vec)[ovecbpq], ovecbpr, buf & 1);            \
      }                                                                        \
    }                                                                          \
  } while (0)

/**
 * @warning
 * Following names are used in this macro. \n
 * Avoid passing these names to parameter if you could.
 *
 * - buf
 * - __sb2
 * - __a
 * - __b
 * - __o
 * - i
 * - j
 * - ovecbp
 * - ovecbpq
 * - ovecbpr
 * - avecbp
 * - avecbpq
 * - avecbpr
 * - bvecbp
 * - bvecbpq
 * - bvecbpr
 *
 * @brief `_out` = `_a` + `_b`;
 *
 * @param ae2f_MathMemOutErr	reterr
 * @param const ae2f_MathInt*	_a
 * @param ae2f_iMathMem		_a_vec
 * @param const ae2f_MathInt*	_b
 * @param ae2f_iMathMem		_b_vec
 * @param const ae2f_MathInt*	_out
 * @param ae2f_oMathMem		_out_vec
 *
 * @param ae2f_bMathMem&	__av
 * Its type must be an existing variable, sharing a same datatype with `_a_vec`.
 * \n If you're using a function, This could be `NULL` and is encouraged to be.
 *
 * @param ae2f_bMathMem&	__bv
 * Its type must be an existing variable, sharing a same datatype with `_b_vec`.
 * \n If you're using a function, This could be `NULL` and is encouraged to be.
 *
 * @param ae2f_bMathMem&	__ov
 * Its type must be an existing variable, sharing a same datatype with
 * `_out_vec`. \n If you're using a function, This could be `NULL` and is
 * encouraged to be.
 *
 * */
#define __ae2f_MathIntAdd(reterr, count, _a, _a_vec, _b, _b_vec, _out,         \
                          _out_vec, __av, __bv, __ov)                          \
  do {                                                                         \
    if ((reterr) && *(reterr))                                                 \
      break;                                                                   \
                                                                               \
    if (!(_a)) {                                                               \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    if (!(_b)) {                                                               \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    if (!(_out)) {                                                             \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    if (!_a_vec) {                                                             \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    if (!_b_vec) {                                                             \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!_out) {                                                               \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    uint8_t buf = 0 /**                                                        \
                     * 0: a                                                    \
                     * 1: b                                                    \
                     * */                                                      \
        ,                                                                      \
            __sb2 = 0;                                                         \
                                                                               \
    ae2f_MathInt __a, __b, __o;                                                \
                                                                               \
    size_t i, j                                                                \
                                                                               \
        ,                                                                      \
        ovecbp, ovecbpq, ovecbpr                                               \
                                                                               \
        ,                                                                      \
        avecbp, avecbpq, avecbpr                                               \
                                                                               \
        ,                                                                      \
        bvecbp, bvecbpq, bvecbpr;                                              \
                                                                               \
    for (i = 0; i < (count); i++) {                                            \
      __ae2f_MathIntNxt(0, i, (_a), (_a_vec), &(__a), &(__av));                \
                                                                               \
      __ae2f_MathIntNxt(0, i, (_b), (_b_vec), &(__b), &(__bv));                \
                                                                               \
      __ae2f_MathIntNxt(0, i, (_out), (_out_vec), &(__o), &(__ov));            \
                                                                               \
      __sb2 = (__a.sign &&                                                     \
               ae2f_BitVecGet((__av)[(__a.vecbegpoint + __a.sz - 1) >> 3],     \
                              (__a.vecbegpoint + __a.sz - 1) & 7)) |           \
              ((__b.sign &&                                                    \
                ae2f_BitVecGet((__bv)[(__b.vecbegpoint + __b.sz - 1) >> 3],    \
                               (__b.vecbegpoint + __b.sz - 1) & 7))            \
               << 1);                                                          \
                                                                               \
      for (j = 0; j < __o.sz; j++) {                                           \
        avecbp = __a.vecbegpoint + j;                                          \
        avecbpq = avecbp >> 3;                                                 \
        avecbpr = avecbp & 7;                                                  \
                                                                               \
        bvecbp = __b.vecbegpoint + j;                                          \
        bvecbpq = bvecbp >> 3;                                                 \
        bvecbpr = bvecbp & 7;                                                  \
                                                                               \
        ovecbp = __o.vecbegpoint + j;                                          \
        ovecbpq = ovecbp >> 3;                                                 \
        ovecbpr = ovecbp & 7;                                                  \
                                                                               \
        buf = (j < __a.sz ? ae2f_BitVecGet(avecbpq[__av], avecbpr)             \
                          : __sb2 & 1) +                                       \
              (j < __b.sz ? ae2f_BitVecGet(bvecbpq[__bv], bvecbpr)             \
                          : __sb2 >> 1) +                                      \
              (buf >> 1);                                                      \
        ovecbpq[__ov] = ae2f_BitVecSet(ovecbpq[__ov], ovecbpr, buf & 1);       \
      }                                                                        \
    }                                                                          \
  } while (0)

/**
 * @warning
 * Following names are used in this macro. \n
 * Avoid passing these names to parameter if you could.
 *
 * - buf
 * - __sb2
 * - __a
 * - __b
 * - __o
 * - i
 * - j
 * - ovecbp
 * - ovecbpq
 * - ovecbpr
 * - avecbp
 * - avecbpq
 * - avecbpr
 * - bvecbp
 * - bvecbpq
 * - bvecbpr
 *
 * @brief `_out` = `_a` - `_b`;
 *
 * @param ae2f_MathMemOutErr	reterr
 * @param const ae2f_MathInt*	_a
 * @param ae2f_iMathMem		_a_vec
 * @param const ae2f_MathInt*	_b
 * @param ae2f_iMathMem		_b_vec
 * @param const ae2f_MathInt*	_out
 * @param ae2f_oMathMem		_out_vec
 *
 * @param ae2f_bMathMem&	__av
 * Its type must be an existing variable, sharing a same datatype with `_a_vec`.
 * \n If you're using a function, This could be `NULL` and is encouraged to be.
 *
 * @param ae2f_bMathMem&	__bv
 * Its type must be an existing variable, sharing a same datatype with `_b_vec`.
 * \n If you're using a function, This could be `NULL` and is encouraged to be.
 *
 * @param ae2f_bMathMem&	__ov
 * Its type must be an existing variable, sharing a same datatype with
 * `_out_vec`. \n If you're using a function, This could be `NULL` and is
 * encouraged to be.
 *
 * */
#define __ae2f_MathIntSub(reterr, count, _a, _a_vec, _b, _b_vec, _out,         \
                          _out_vec, __av, __bv, __ov)                          \
  do {                                                                         \
    if ((reterr) && *(reterr))                                                 \
      break;                                                                   \
                                                                               \
    if (!(_a)) {                                                               \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    if (!(_b)) {                                                               \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    if (!(_out)) {                                                             \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    if (!_a_vec) {                                                             \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    if (!_b_vec) {                                                             \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!_out) {                                                               \
      if ((reterr))                                                            \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    uint8_t buf = 0b10 /**                                                     \
                        * 0: a                                                 \
                        * 1: b                                                 \
                        * */                                                   \
        ,                                                                      \
            __sb2 = 0;                                                         \
                                                                               \
    ae2f_MathInt __a, __b, __o;                                                \
                                                                               \
    size_t i, j                                                                \
                                                                               \
        ,                                                                      \
        ovecbp, ovecbpq, ovecbpr                                               \
                                                                               \
        ,                                                                      \
        avecbp, avecbpq, avecbpr                                               \
                                                                               \
        ,                                                                      \
        bvecbp, bvecbpq, bvecbpr;                                              \
                                                                               \
    for (i = 0; i < (count); i++) {                                            \
      __ae2f_MathIntNxt(0, i, (_a), (_a_vec), &(__a), &(__av));                \
                                                                               \
      __ae2f_MathIntNxt(0, i, (_b), (_b_vec), &(__b), &(__bv));                \
                                                                               \
      __ae2f_MathIntNxt(0, i, (_out), (_out_vec), &(__o), &(__ov));            \
                                                                               \
      __sb2 = (__a.sign &&                                                     \
               ae2f_BitVecGet((__av)[(__a.vecbegpoint + __a.sz - 1) >> 3],     \
                              (__a.vecbegpoint + __a.sz - 1) & 7)) |           \
              ((__b.sign &&                                                    \
                ae2f_BitVecGet((__bv)[(__b.vecbegpoint + __b.sz - 1) >> 3],    \
                               (__b.vecbegpoint + __b.sz - 1) & 7))            \
               << 1);                                                          \
                                                                               \
      for (j = 0; j < __o.sz; j++) {                                           \
        avecbp = __a.vecbegpoint + j;                                          \
        avecbpq = avecbp >> 3;                                                 \
        avecbpr = avecbp & 7;                                                  \
                                                                               \
        bvecbp = __b.vecbegpoint + j;                                          \
        bvecbpq = bvecbp >> 3;                                                 \
        bvecbpr = bvecbp & 7;                                                  \
                                                                               \
        ovecbp = __o.vecbegpoint + j;                                          \
        ovecbpq = ovecbp >> 3;                                                 \
        ovecbpr = ovecbp & 7;                                                  \
                                                                               \
        buf = (j < __a.sz ? ae2f_BitVecGet(avecbpq[__av], avecbpr)             \
                          : __sb2 & 1) +                                       \
              !(j < __b.sz ? ae2f_BitVecGet(bvecbpq[__bv], bvecbpr)            \
                           : __sb2 >> 1) +                                     \
              (buf >> 1);                                                      \
        ovecbpq[__ov] = ae2f_BitVecSet(ovecbpq[__ov], ovecbpr, buf & 1);       \
      }                                                                        \
    }                                                                          \
  } while (0)

/**
 * @warning
 * Following names are used in this macro. \n
 * Avoid passing these names to parameter if you could.
 *
 * - __a
 * - i
 * - j
 * - abegpq
 * - abegpr
 *
 * @brief
 * `a` = 0;  \n
 * `a` = -1;
 *
 * @param ae2f_MathMemOutErr	reterr
 * @param size_t		count
 * @param ae2f_MathInt*		a
 * @param ae2f_oMathMem		a_vec
 * @param bool			mask
 * @param ae2f_bMathMem&	__a_vec
 * Its type must be an existing variable, sharing a same datatype with `a_vec`.
 * \n If you're using a function, This could be `NULL` and is encouraged to be.
 * */
#define __ae2f_MathIntFill(reterr, count, a, a_vec, mask, __a_vec)             \
  do {                                                                         \
    if ((reterr) && *(reterr))                                                 \
      break;                                                                   \
    if (!(a)) {                                                                \
      if (reterr)                                                              \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!(a_vec)) {                                                            \
      if (reterr)                                                              \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    ae2f_MathInt __a;                                                          \
    size_t abegpq, abegpr, i, j;                                               \
                                                                               \
    for (i = 0; i < (count); i++) {                                            \
      __ae2f_MathIntNxt(0, i, a, a_vec, &__a, &__a_vec);                       \
                                                                               \
      for (j = 0; j < (__a).sz; j++) {                                         \
        abegpq = (__a.vecbegpoint + j) >> 3;                                   \
        abegpr = (__a.vecbegpoint + j) & 7;                                    \
                                                                               \
        (__a_vec)[abegpq] = ae2f_BitVecSet((__a_vec)[abegpq], abegpr, mask);   \
      }                                                                        \
    }                                                                          \
  } while (0)

/**
 * @warning
 * Following names are used in this macro. \n
 * Avoid passing these names to parameter if you could.
 *
 * - _in
 * - c
 * - i
 * - ivecbpq
 * - ivecbpr
 *
 * @brief
 * Compares `in` with 0
 *
 * @return
 * `ae2f_CmpFunRet_LISLESSER`	means `in` < 0 \n
 * `ae2f_CmpFunRet_RISLESSER`	means `in` > 0 \n
 * `ae2f_CmpFunRet_EQUAL`	means `in` == 0
 *
 * @param ae2f_MathMemOutErr	reterr
 * @param size_t		count
 * @param const ae2f_MathInt*	in
 * @param ae2f_iMathMem		in_vec
 * @param ae2f_CmpFunRet_t*	out
 *
 * @param ae2f_bMathMem&	_in_vec
 * Its type must be an existing variable, sharing a same datatype with `in_vec`.
 * \n If you're using a function, This could be `NULL` and is encouraged to be.
 *
 * */
#define __ae2f_MathIntCmpZero(reterr, count, in, in_vec, out, _in_vec)         \
  do {                                                                         \
    if ((reterr) && *(reterr))                                                 \
      break;                                                                   \
    if (!(in)) {                                                               \
      if (reterr)                                                              \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    if (!(out)) {                                                              \
      if (reterr)                                                              \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!in_vec) {                                                             \
      if (reterr)                                                              \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    ae2f_MathInt _in;                                                          \
                                                                               \
    size_t c, i                                                                \
                                                                               \
        ,                                                                      \
        ivecbpr, ivecbpq;                                                      \
                                                                               \
    for (c = 0; c < (count); c++) {                                            \
      __ae2f_MathIntNxt(0, c, in, in_vec, &_in, &_in_vec);                     \
                                                                               \
      if (_in.sign &&                                                          \
          ae2f_BitVecGet((_in_vec)[(_in.vecbegpoint + _in.sz - 1) >> 3],       \
                         (_in.vecbegpoint + _in.sz - 1) & 7)) {                \
        (out)[c] = ae2f_CmpFunRet_LISLESSER;                                   \
        continue;                                                              \
      }                                                                        \
                                                                               \
      for (i = 0; i < _in.sz; i++) {                                           \
        ivecbpr = (_in.vecbegpoint + i) & 7;                                   \
        ivecbpq = (_in.vecbegpoint + i) >> 3;                                  \
                                                                               \
        if (ae2f_BitVecGet((_in_vec)[ivecbpq], ivecbpr)) {                     \
          (out)[c] = ae2f_CmpFunRet_RISLESSER;                                 \
          break;                                                               \
        }                                                                      \
                                                                               \
        (out)[c] = ae2f_CmpFunRet_EQUAL;                                       \
      }                                                                        \
    }                                                                          \
  } while (0)

/**
 * @warning
 * following names are used in this macro. \n
 * avoid passing these names to parameter if you could.
 *
 * - _sign
 * - _sz_gt
 * - inavp
 * - inavpr
 * - inavps
 * - inbvp
 * - inbvpr
 * - inbvps
 * - _cmp
 * - i
 * - c
 *
 * @brief
 * compares `a` with `b`
 *
 * @return
 * `ae2f_cmpfunret_lislesser`	means `a` < `b` \n
 * `ae2f_cmpfunret_rislesser`	means `a` > `b` \n
 * `ae2f_cmpfunret_equal`	means `a` == `b`
 *
 * @param ae2f_mathmemouterr		errret
 * @param size_t			count
 * @param const ae2f_mathint*		a
 * @param ae2f_imathmem			a_vec
 * @param const ae2f_mathint*		b
 * @param ae2f_imathmem			b_vec
 * @param const ae2f_cmpfunret_t*	out
 *
 * @param ae2f_bmathmem*	_a_vec
 * its type must be an existing variable, sharing a same datatype with `a_vec`.
 * \n if you're using a function, this could be `null` and is encouraged to be.
 *
 * @param ae2f_bmathmem&	_b_vec
 * its type must be an existing variable, sharing a same datatype with `b_vec`.
 * \n if you're using a function, this could be `null` and is encouraged to be.
 *
 * */
#define __ae2f_MathIntCmp(errret, count, a, a_vec, b, b_vec, out, _a_vec,      \
                          _b_vec)                                              \
  do {                                                                         \
    if ((errret) && *(errret))                                                 \
      break;                                                                   \
    if (!(out)) {                                                              \
      if (errret)                                                              \
        *(errret) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!(a)) {                                                                \
      if (errret)                                                              \
        *(errret) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!(a_vec)) {                                                            \
      if (errret)                                                              \
        *(errret) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!(b)) {                                                                \
      if (errret)                                                              \
        *(errret) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!(b_vec)) {                                                            \
      if (errret)                                                              \
        *(errret) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    ae2f_MathInt _a = *(a), _b = *(b);                                         \
    if (_a.sz - _a.sign < 1) {                                                 \
      if (errret)                                                              \
        *(errret) |= ae2f_errGlob_WRONG_OPERATION;                             \
      break;                                                                   \
    }                                                                          \
    if (_b.sz - _b.sign < 1) {                                                 \
      if (errret)                                                              \
        *(errret) |= ae2f_errGlob_WRONG_OPERATION;                             \
      break;                                                                   \
    }                                                                          \
    bool _sign = 0;                                                            \
    size_t _sz_gt = _a.sz < _b.sz ? _b.sz : _a.sz, c, i;                       \
    for (c = 0; c < (count); c++) {                                            \
      __ae2f_MathIntNxt(0, c, a, a_vec, &_a, &_a_vec);                         \
      __ae2f_MathIntNxt(0, c, b, b_vec, &_b, &_b_vec);                         \
      c[out] = 0;                                                              \
      if ((_sign =                                                             \
               (_a.sign &&                                                     \
                ae2f_BitVecGet((_a_vec)[(_a.vecbegpoint + _a.sz - 1) >> 3],    \
                               ((_a.vecbegpoint + _a.sz - 1) & 7)))) !=        \
          (_b.sign &&                                                          \
           ae2f_BitVecGet((_b_vec)[(_b.vecbegpoint + _b.sz - 1) >> 3],         \
                          ((_b.vecbegpoint + _b.sz - 1) & 7)))) {              \
        /** Two signs are different */                                         \
        c[out] = _sign /* is sign of a negative */                             \
                     ? ae2f_CmpFunRet_LISLESSER                                \
                     : ae2f_CmpFunRet_RISLESSER;                               \
        continue;                                                              \
      }                                                                        \
      for (i = _sz_gt - 1; i != ae2f_static_cast(size_t, -1); i--) {           \
        const size_t inavp = _a.vecbegpoint + i, inavpr = inavp & 7,           \
                     inavps = inavp >> 3                                       \
                                                                               \
            ,                                                                  \
                     inbvp = _b.vecbegpoint + i, inbvpr = inbvp & 7,           \
                     inbvps = inbvp >> 3;                                      \
        const int8_t _cmp =                                                    \
            ae2f_static_cast(                                                  \
                int8_t, i < _a.sz ? ae2f_BitVecGet((_a_vec)[inavps], inavpr)   \
                                  : _sign) -                                   \
            ae2f_static_cast(                                                  \
                int8_t,                                                        \
                i < _b.sz ? ae2f_BitVecGet((_b_vec)[inbvps], inbvpr) : _sign); \
        /* is abs(a) greater */                                                \
        if (_cmp) {                                                            \
          c[out] = _cmp;                                                       \
          break;                                                               \
        }                                                                      \
      }                                                                        \
    }                                                                          \
  } while (0)

inline static void
__ae2f_MathIntBitL(ae2f_MathMemOutErr reterr, size_t count, size_t bitcount,
                   const ae2f_MathInt *in, ae2f_iMathMem in_vec,
                   const ae2f_MathInt *out, ae2f_oMathMem out_vec,

                   /** Buffer session */
                   ae2f_bMathMem in_vec_buf, ae2f_bMathMem out_vec_buf) {
  if ((reterr) && *(reterr)) {
    return;
  }
  if (!((bitcount) && (count)))
    return;

  if (!(in)) {
    if (reterr)
      *(reterr) |= ae2f_errGlob_PTR_IS_NULL;
    return;
  }
  if (!(in_vec)) {
    if (reterr)
      *(reterr) |= ae2f_errGlob_PTR_IS_NULL;
    return;
  }
  if (!(out)) {
    if (reterr)
      *(reterr) |= ae2f_errGlob_PTR_IS_NULL;
    return;
  }
  if (!(out_vec)) {
    if (reterr)
      *(reterr) |= ae2f_errGlob_PTR_IS_NULL;
    return;
  }

  if (in->sz + (bitcount) < (in)->sz) {
    if (reterr)
      *(reterr) |= ae2f_errGlob_IMP_NOT_FOUND;
    return;
  }

  size_t c, i, osz, _o, _i;
  ae2f_MathInt in_buf;
  ae2f_MathInt out_buf;

  for ((c) = 0; (c) < (count); (c)++) {
    __ae2f_MathIntNxt(0, c, in, in_vec, &(in_buf), &(in_vec_buf));
    __ae2f_MathIntNxt(0, c, out, out_vec, &(out_buf), &(out_vec_buf));

    for ((i) = 0; (i) < (bitcount) && (i) < out_buf.sz; (i)++) {
      _o = ((out_buf).vecbegpoint + i);
      (out_vec_buf)[_o >> 3] =
          ae2f_BitVecSet((out_vec_buf)[_o >> 3], _o & 7, 0);
    }

    for (; (i) < (out_buf).sz && (i) < (in_buf).sz + (bitcount); i++) {
      _o = (out_buf.vecbegpoint + i);
      _i = (in_buf.vecbegpoint + i);

      (out_vec_buf)[_o >> 3] =
          ae2f_BitVecSet((out_vec_buf)[_o >> 3], _o & 7,
                         ae2f_BitVecGet((in_vec_buf)[_i >> 3], _i & 7));
    }

    for (; i < out_buf.sz; i++) {
      _o = ((out_buf).vecbegpoint + i);
      (out_vec_buf)[_o >> 3] =
          ae2f_BitVecSet((out_vec_buf)[_o >> 3], _o & 7, 0);
    }
  }
}

/**
 * @warning
 * following names are used in this macro. \n
 * avoid passing these names to parameter if you could.
 *
 * - i
 * - c
 * - ___a
 * - ___b
 * - ___o
 * - __sign
 *
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
 *
 * @param a_vec_buf	{typeof(a_vec)&}
 * @param b_vec_buf	{typeof(b_vec)&}
 * @param b_vec_buf2	{typeof(b_vec)&}
 * @param o_vec_buf	{typeof(o_vec)&}
 * @param o_vec_buf2	{typeof(o_vec)&}
 * @param o_vec_buf3	{typeof(o_vec)&}
 * */
#define __ae2f_MathIntMul(reterr, count, a, a_vec, b, b_vec, out, out_vec,     \
                          a_vec_buf, b_vec_buf, b_vec_buf2, o_vec_buf,         \
                          o_vec_buf2, o_vec_buf3)                              \
  do {                                                                         \
    if ((reterr) && *(reterr))                                                 \
      break;                                                                   \
                                                                               \
    if (!(a)) {                                                                \
      if (reterr)                                                              \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!(a_vec)) {                                                            \
      if (reterr)                                                              \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!(b)) {                                                                \
      if (reterr)                                                              \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!(b_vec)) {                                                            \
      if (reterr)                                                              \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!(out)) {                                                              \
      if (reterr)                                                              \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
    if (!(out_vec)) {                                                          \
      if (reterr)                                                              \
        *(reterr) |= ae2f_errGlob_PTR_IS_NULL;                                 \
      break;                                                                   \
    }                                                                          \
                                                                               \
    ae2f_MathInt ___a;                                                         \
    ae2f_MathInt ___b;                                                         \
    ae2f_MathInt ___o;                                                         \
                                                                               \
    size_t i, c;                                                               \
    bool __sign;                                                               \
                                                                               \
    __ae2f_MathIntFill(reterr, count, out, out_vec, 0, o_vec_buf);             \
                                                                               \
    for (c = 0; c < (count); c++) {                                            \
      __ae2f_MathIntNxt(0, c, a, a_vec, &___a, &a_vec_buf);                    \
      __ae2f_MathIntNxt(0, c, b, b_vec, &___b, &b_vec_buf);                    \
      __ae2f_MathIntNxt(0, c, out, out_vec, &___o, &o_vec_buf);                \
                                                                               \
      __sign = __ae2f_MathIntIsNegative(&___a, a_vec_buf); /* sign of a */     \
                                                                               \
      i = 0;                                                                   \
      if (__sign) {                                                            \
        __ae2f_MathIntFlip(reterr, 1, &___b, b_vec_buf, &___o, o_vec_buf,      \
                           b_vec_buf2, o_vec_buf2); /* complement 2 */         \
      }                                                                        \
      while (___o.sz && i < ___a.sz - __sign) {                                \
        if (__sign ^ ae2f_BitVecGet(((___a.vecbegpoint + i) >> 3)[a_vec_buf],  \
                                    (___a.vecbegpoint + i) &                   \
                                        7)) { /** Addition (conditional) */    \
                                                                               \
          if (__sign)                                                          \
            __ae2f_MathIntSub(reterr, 1, &___b, b_vec_buf, &___o, o_vec_buf,   \
                              &___o, o_vec_buf, b_vec_buf2, o_vec_buf2,        \
                              o_vec_buf3);                                     \
                                                                               \
          else                                                                 \
            __ae2f_MathIntAdd(reterr, 1, &___b, b_vec_buf, &___o, o_vec_buf,   \
                              &___o, o_vec_buf, b_vec_buf2, o_vec_buf2,        \
                              o_vec_buf3);                                     \
        }                                                                      \
                                                                               \
        /** Increament */                                                      \
        i++;                                                                   \
        ___o.sz--;                                                             \
        ___o.vecbegpoint++;                                                    \
                                                                               \
        if (!(___o.vecbegpoint & 7)) {                                         \
          ___o.vecbegpoint = 0;                                                \
          o_vec_buf++;                                                         \
        }                                                                      \
      }                                                                        \
    }                                                                          \
  } while (0)

#endif
