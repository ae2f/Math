/**
 * @file int.h
 * @brief
 * Implementation of this is not supported yet.
 * */

#ifndef ae2f_Math_int_h
#define ae2f_Math_int_h

#include "./Mem.h"

#include <ae2f/Call.h>
#include <ae2f/Cast.h>
#include <ae2f/Cmp.h>
#include <ae2f/errGlob.h>
#include <stddef.h>

#include <ae2f/Pack/Beg.h>

/** @brief The custom integer type. Following 2-complement standards. */
typedef struct ae2f_MathInt {
  /** @brief Whether it has sign bit or not. */
  bool sign : 1;

  /** @brief the size as bits, including the sign */
  size_t sz;

  /** @brief From which bit point is the start of the integer. */
  size_t vecbegpoint : 3;

} ae2f_MathInt;

#include <ae2f/Pack/End.h>

#if 1

/**
 * @brief
 * `_out_int` = `_int`[`_idx`];
 * */
ae2f_extern ae2f_SHAREDCALL const void
ae2f_MathIntNxt(ae2f_MathMemOutErr _reterr, intptr_t _idx,
                const ae2f_MathInt *_int, uintptr_t _int_vec,
                ae2f_MathInt *_out, uintptr_t *_out_int_vec);
/**
 * @brief
 * `__i` < 0
 * */
ae2f_extern ae2f_SHAREDCALL uint8_t
ae2f_MathIntIsNegative(const ae2f_MathInt *_i, ae2f_iMathMem _v);

/**
 * @brief
 * `__out` = -`__in`
 *
 * @param __i_vec_unused
 * This could be `NULL` and is encouraged to be.
 *
 * @param __o_vec_unused
 * This could be `NULL` and is encouraged to be.
 * */
ae2f_extern ae2f_SHAREDCALL void
ae2f_MathIntFlip(ae2f_MathMemOutErr reterr, size_t count,
                 const ae2f_MathInt *__in, ae2f_iMathMem __in_vec,
                 ae2f_MathInt *__out, ae2f_oMathMem __out_vec,
                 ae2f_iMathMem __i_vec_unused, ae2f_oMathMem __o_vec_unused);

/**
 * @brief
 * `__out` = `__in`
 *
 * @param __i_vec_unused
 * This could be `NULL` and is encouraged to be.
 *
 * @param __o_vec_unused
 * This could be `NULL` and is encouraged to be.
 * */
ae2f_extern ae2f_SHAREDCALL void
ae2f_MathIntCast(ae2f_MathMemOutErr errret, size_t count,
                 const ae2f_MathInt *__in, ae2f_iMathMem __in_vec,
                 ae2f_MathInt *__out, ae2f_oMathMem __out_vec,

                 ae2f_iMathMem __i_vec_unused, ae2f_oMathMem __o_vec_unused);

/**
 * @brief `_out` = `_a` + `_b`;
 *
 * @param __av_unused
 * This could be `NULL` and is encouraged to be.
 *
 * @param __bv_unused
 * This could be `NULL` and is encouraged to be.
 *
 * @param __ov_unused
 * This could be `NULL` and is encouraged to be.
 *
 * */
ae2f_extern ae2f_SHAREDCALL void
ae2f_MathIntAdd(ae2f_MathMemOutErr reterr, size_t count, const ae2f_MathInt *_a,
                ae2f_iMathMem _a_vec, const ae2f_MathInt *_b,
                ae2f_iMathMem _b_vec, ae2f_MathInt *_out,
                ae2f_oMathMem _out_vec,

                ae2f_iMathMem __av_unused, ae2f_iMathMem __bv_unused,
                ae2f_oMathMem __ov_unused);

/**
 * @brief `_out` = `_a` - `_b`;
 *
 * @param __av_unused
 * This could be `NULL` and is encouraged to be.
 *
 * @param __bv_unused
 * This could be `NULL` and is encouraged to be.
 *
 * @param __ov_unused
 * This could be `NULL` and is encouraged to be.
 *
 * */
ae2f_extern ae2f_SHAREDCALL void
ae2f_MathIntSub(ae2f_MathMemOutErr reterr, size_t count, const ae2f_MathInt *_a,
                ae2f_iMathMem _a_vec, const ae2f_MathInt *_b,
                ae2f_iMathMem _b_vec, ae2f_MathInt *_out,
                ae2f_oMathMem _out_vec,

                ae2f_iMathMem __av_unused, ae2f_iMathMem __bv_unused,
                ae2f_oMathMem __ov_unused);

/**
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
 * This could be `NULL` and is encouraged to be.
 * */
ae2f_extern ae2f_SHAREDCALL void
ae2f_MathIntFill(ae2f_MathMemOutErr reterr, size_t count, ae2f_MathInt *a,
                 ae2f_oMathMem a_vec, bool mask, ae2f_oMathMem __a_vec);

/**
 * @brief
 * Compares `in` with 0
 *
 * @return
 * `ae2f_CmpFunRet_LISLESSER`	means `in` < 0 \n
 * `ae2f_CmpFunRet_RISLESSER`	means `in` > 0 \n
 * `ae2f_CmpFunRet_EQUAL`	means `in` == 0
 *
 * @param ae2f_bMathMem&	_in_vec
 * This could be `NULL` and is encouraged to be.
 * */
ae2f_extern ae2f_SHAREDCALL void ae2f_MathIntCmpZero(ae2f_MathMemOutErr reterr,
                                                     size_t count,
                                                     const ae2f_MathInt *in,
                                                     ae2f_iMathMem in_vec,
                                                     ae2f_CmpFunRet_t *out,

                                                     ae2f_iMathMem _in_vec);

/**
 * @brief
 * compares `a` with `b`
 *
 * @return
 * `ae2f_cmpfunret_lislesser`	means `a` < `b` \n
 * `ae2f_cmpfunret_rislesser`	means `a` > `b` \n
 * `ae2f_cmpfunret_equal`	means `a` == `b`
 *
 * @param ae2f_bmathmem*	_a_vec
 * This could be `null` and is encouraged to be.
 *
 * @param ae2f_bmathmem&	_b_vec
 * This could be `null` and is encouraged to be.
 *
 * */
ae2f_extern ae2f_SHAREDCALL void
ae2f_MathIntCmp(ae2f_MathMemOutErr errret, size_t count, const ae2f_MathInt *a,
                ae2f_iMathMem a_vec, const ae2f_MathInt *b, ae2f_iMathMem b_vec,
                ae2f_CmpFunRet_t *out, ae2f_iMathMem _a_vec,
                ae2f_iMathMem _b_vec);

/**
 * @brief
 * `out` = `a` * `b`;
 *
 * @param a_vec_buf_unused	{const void*} Unused
 * @param b_vec_buf_unused	{const void*} Unused
 * @param b_vec_buf2_unused	{const void*} Unused
 * @param o_vec_buf_unused	{const void*} Unused
 * @param o_vec_buf2_unused	{const void*} Unused
 * @param o_vec_buf3_unused	{const void*} Unused
 * */
ae2f_extern ae2f_SHAREDCALL void
ae2f_MathIntMul(ae2f_MathMemOutErr reterr, size_t count, const ae2f_MathInt *a,
                ae2f_iMathMem a_vec, const ae2f_MathInt *b, ae2f_iMathMem b_vec,
                const ae2f_MathInt *out, ae2f_oMathMem out_vec,
                ae2f_iMathMem a_vec_buf_unused, ae2f_iMathMem b_vec_buf_unused,
                ae2f_iMathMem b_vec_buf2_unused, ae2f_oMathMem o_vec_buf_unused,
                ae2f_oMathMem o_vec_buf2_unused,
                ae2f_oMathMem o_vec_buf3_unused);

/**
 * @warning
 * It does not handle negative values.
 *
 * @brief
 * Unsigned division
 *
 * `r` = `a`; `q` = `r` / `b`; `r` %= `b`;
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
 * @param a_vec_unused	{const void*}		Unused
 * @param b_vec_unused	{const void*}		Unused
 * @param b_vec_unused2	{const void*}		Unused
 * @param q_vec_unused	{const void*}		Unused
 * @param r_vec_unused	{const void*}		Unused
 * @param r_vec_unused2	{const void*}		Unused
 * @param r_vec_unused3	{const void*}		Unused
 * @param r_vec_unused4	{const void*}		Unused
 * */
ae2f_extern ae2f_SHAREDCALL void ae2f_MathIntDivU(
    ae2f_MathMemOutErr *reterr, size_t count, const ae2f_MathInt *a,
    ae2f_iMathMem a_vec, const ae2f_MathInt *b, ae2f_iMathMem b_vec,
    const ae2f_MathInt *q, ae2f_oMathMem q_vec, const ae2f_MathInt *r,
    ae2f_oMathMem r_vec, ae2f_iMathMem a_vec_unused, ae2f_iMathMem b_vec_unused,
    ae2f_iMathMem b_vec_unused2, ae2f_oMathMem q_vec_unused,
    ae2f_oMathMem r_vec_unused, ae2f_oMathMem r_vec_unused2,
    ae2f_oMathMem r_vec_unused3, ae2f_oMathMem r_vec_unused4);

#endif
#endif
