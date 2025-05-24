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
  /** @brief the size as bits, including the sign bit */
  size_t sz;
  /** @brief Whether it has sign bit or not. */
  unsigned sign : 1;
  /** @brief From which bit point is the start of the integer. */
  unsigned vecbegpoint : 3;
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
                ae2f_MathInt *_out, uintptr_t *_out_int_vec) noexcept;
/**
 * @brief
 * `__i` < 0
 * */
ae2f_extern ae2f_SHAREDCALL uint8_t
ae2f_MathIntIsNegative(const ae2f_MathInt *_i, ae2f_iMathMem _v) noexcept;

/**
 * @brief
 * `__out` = -`__in`
 * */
ae2f_extern ae2f_SHAREDCALL void
ae2f_MathIntFlip(ae2f_MathMemOutErr reterr, const ae2f_MathInt *__in,
                 ae2f_iMathMem __in_vec, ae2f_MathInt *__out,
                 ae2f_oMathMem __out_vec) noexcept;
/**
 * @brief
 * `__out` = `__in`
 * */
ae2f_extern ae2f_SHAREDCALL void
ae2f_MathIntCast(ae2f_MathMemOutErr errret, const ae2f_MathInt *__in,
                 ae2f_iMathMem __in_vec, ae2f_MathInt *__out,
                 ae2f_oMathMem __out_vec) noexcept;

/**
 * @brief `_out` = `_a` + `_b`;
 * */
ae2f_extern ae2f_SHAREDCALL void
ae2f_MathIntAdd(ae2f_MathMemOutErr reterr, const ae2f_MathInt *_a,
                ae2f_iMathMem _a_vec, const ae2f_MathInt *_b,
                ae2f_iMathMem _b_vec, ae2f_MathInt *_out,
                ae2f_oMathMem _out_vec) noexcept;

/**
 * @brief `_out` = `_a` - `_b`;
 * */
ae2f_extern ae2f_SHAREDCALL void
ae2f_MathIntSub(ae2f_MathMemOutErr reterr, const ae2f_MathInt *_a,
                ae2f_iMathMem _a_vec, const ae2f_MathInt *_b,
                ae2f_iMathMem _b_vec, ae2f_MathInt *_out,
                ae2f_oMathMem _out_vec) noexcept;

/**
 * @brief
 * `a` = 0;  \n
 * `a` = -1;
 * */
ae2f_extern ae2f_SHAREDCALL void
ae2f_MathIntFill(ae2f_MathMemOutErr reterr, ae2f_MathInt *a,
                 ae2f_oMathMem a_vec, bool mask, uint8_t masklen) noexcept;

/**
 * @brief
 * Compares `in` with 0
 *
 * @return
 * `ae2f_CmpFunRet_LISLESSER`	means `in` < 0 \n
 * `ae2f_CmpFunRet_RISLESSER`	means `in` > 0 \n
 * `ae2f_CmpFunRet_EQUAL`	means `in` == 0
 * */
ae2f_extern ae2f_SHAREDCALL void
ae2f_MathIntCmpZero(ae2f_MathMemOutErr reterr, const ae2f_MathInt *in,
                    ae2f_iMathMem in_vec, ae2f_CmpFunRet_t *out) noexcept;
/**
 * @brief
 * compares `a` with `b`
 *
 * @return
 * `ae2f_cmpfunret_lislesser`	means `a` < `b` \n
 * `ae2f_cmpfunret_rislesser`	means `a` > `b` \n
 * `ae2f_cmpfunret_equal`	means `a` == `b`
 *
 * */
ae2f_extern ae2f_SHAREDCALL void
ae2f_MathIntCmp(ae2f_MathMemOutErr errret, const ae2f_MathInt *a,
                ae2f_iMathMem a_vec, const ae2f_MathInt *b, ae2f_iMathMem b_vec,
                ae2f_CmpFunRet_t *out) noexcept;
/**
 * @brief
 * `out` = `a` * `b`;
 *
 * */
ae2f_extern ae2f_SHAREDCALL void
ae2f_MathIntMul(ae2f_MathMemOutErr reterr, const ae2f_MathInt *a,
                ae2f_iMathMem a_vec, const ae2f_MathInt *b, ae2f_iMathMem b_vec,
                const ae2f_MathInt *out, ae2f_oMathMem out_vec) noexcept;
/**
 * @warning
 * It does not handle negative values.
 *
 * @brief
 * Unsigned division
 *
 * `r` = `a`; `q` = `r` / `b`; `r` %= `b`;
 * */
ae2f_extern ae2f_SHAREDCALL void ae2f_MathIntDivU(
    ae2f_MathMemOutErr *reterr, const ae2f_MathInt *a, ae2f_iMathMem a_vec,
    const ae2f_MathInt *b, ae2f_iMathMem b_vec, const ae2f_MathInt *q,
    ae2f_oMathMem q_vec, const ae2f_MathInt *r, ae2f_oMathMem r_vec) noexcept;

ae2f_extern ae2f_SHAREDCALL void
ae2f_MathIntSel(ae2f_err_t *err, const ae2f_MathInt *_ai,
                const uint8_t *_ai_vec, const ae2f_MathInt *_bi,
                const uint8_t *_bi_vec, const ae2f_MathInt *_oi,
                uint8_t *_oi_vec, int8_t selector) noexcept;

#endif
#endif
