#ifndef ae2f_Math_int_imp_h
#define ae2f_Math_int_imp_h

#include "ae2f/Cmp/Fun.h"
#include "ae2f/errGlob.h"
#include <ae2f/Math/Util.auto.h>
#include <ae2f/Math/int.h>

#include <ae2f/Macro.h>

#include <ae2f/BitVec.h>

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
	 __ae2f_MathUtilBVGet((__v)[((__i)->vecbegpoint + (__i)->sz - 1) >> 3],      \
		 ((__i)->vecbegpoint + (__i)->sz - 1) & 7))

#define __ae2f_MathIntTmp ae2f_RecordMk(ae2f_MathInt, 0, )

#define __ae2f_MathIntNxtHead(_int, _idx)                                      \
	((_int)                                                                      \
	 ? ae2f_RecordMk(                                                        \
		 ae2f_MathInt, ae2f_static_cast(size_t, (_int)->sz), (_int)->sign, \
		 ae2f_static_cast(                                                 \
			 size_t, ((_int)->sz * (_idx)) +                               \
			 ae2f_static_cast(size_t, (_int)->vecbegpoint)))   \
			 : ae2f_RecordMk(ae2f_MathInt, 0ull, 0ull, 0ull))

#define __ae2f_MathIntNxtIdx(_int, _idx)                                       \
	((_int) ? ((_int)->vecbegpoint + ((_int)->sz * (_idx))) >> 3 : 0)

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathIntNxt _ae2f_MathIntNxt
#else
#undef __ae2f_MathIntNxt
#endif

/**
 * @brief
 * `_out_int` = `_int`[`_idx`];
 * */
ae2f_MAC() _ae2f_MathIntNxt(ae2f_err_t *_reterr, const ae2f_MathInt *_int,
		intptr_t _idx, ae2f_MathInt *_out_int,
		size_t *_out_int_idx) {
	if ((_reterr) && *(_reterr))
		;
	else if (!_int)
		(_reterr) && (*(_reterr) |= ae2f_errGlob_PTR_IS_NULL);
	else {
		if (_out_int) {
			*(_out_int) = __ae2f_MathIntNxtHead(_int, _idx);
		}

		(_out_int_idx) && (*(_out_int_idx) = ae2f_static_cast(size_t, __ae2f_MathIntNxtIdx(_int, _idx)));
	}
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathIntCast _ae2f_MathIntCast
#define __ae2f_MathIntCast_imp _ae2f_MathIntCast_imp
#else
#undef __ae2f_MathIntCast
#undef __ae2f_MathIntCast_imp
#endif

typedef struct ae2f_MathIntCast_t {
	size_t j;
	size_t ovec, ivec;
} ae2f_MathIntCast_t;

/**
 * @def
 * __ae2f_MathIntCast_imp
 *
 * @brief
 * Contains pure implementation of `__ae2f_MathIntCast`
 *
 * @warning
 * It contains no exception verifier.
 *
 * @param vi_cast
 * The stack that is needed.
 * */
ae2f_MAC() _ae2f_MathIntCast_imp(ae2f_MathIntCast_t vi_cast,
		const ae2f_MathInt *const __prm_in,
		ae2f_iMathMem __i_vec, const ae2f_pMathInt __prm_out,
		ae2f_oMathMem __o_vec) {
	/** Fill them all without noticing if it's signed */
	vi_cast = ae2f_RecordMk(ae2f_MathIntCast_t, 0, );

	for (; vi_cast.j <
			(__prm_in)->sz - ae2f_static_cast(size_t, (__prm_in)->sign) &&
			vi_cast.j < (__prm_out)->sz;
			vi_cast.j++) 
	{
		vi_cast.ovec = (__prm_out)->vecbegpoint + vi_cast.j;
		vi_cast.ivec = (__prm_in)->vecbegpoint + vi_cast.j;
		__ae2f_MathUtilBVSetAssignArr(
				__o_vec, vi_cast.ovec, __ae2f_MathUtilBVGetArr(__i_vec, vi_cast.ivec));
	}

	/*                                                                       
	 * Rest of them will be zero.                                            
	 * When signed, rest will be filled with sign bit.                       
	 * */
	for (; vi_cast.j < (__prm_out)->sz; vi_cast.j++) {
		vi_cast.ovec = (__prm_out)->vecbegpoint + vi_cast.j;
		vi_cast.ivec = (__prm_in)->vecbegpoint + vi_cast.j;

		__ae2f_MathUtilBVSetAssignArr(__o_vec, vi_cast.ovec,
				__ae2f_MathIntIsNegative(__prm_in, __i_vec));
	}
}

/**
 * @macro
 * __ae2f_MathIntCast
 *
 * @brief
 * `__prm_out` = `__prm_in`
 *
 * */
ae2f_MAC() _ae2f_MathIntCast(
		ae2f_err_t *const reterr
		, const ae2f_MathInt *const __prm_in
		, ae2f_iMathMem __i_vec
		, const ae2f_MathInt *const __prm_out
		, ae2f_oMathMem __o_vec) 
{
	if ((reterr) && *(reterr))
		;
	else if (!((__prm_in) && (__prm_out) && (__i_vec) && (__o_vec))) {
		if ((reterr))
			(*(reterr)) |= ae2f_errGlob_PTR_IS_NULL;
	} else if ((__i_vec) == (__o_vec) &&
			((__prm_in) == (__prm_out) ||
			 ((__prm_in)->sz == (__prm_out)->sz &&
			  (__prm_in)->sign == (__prm_out)->sign &&
			  (__prm_in)->vecbegpoint == (__prm_out)->vecbegpoint))) {
	} else {
		ae2f_MathIntCast_t vi_cast;
		__ae2f_MathIntCast_imp(vi_cast, __prm_in, __i_vec, __prm_out, __o_vec);
	}
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathIntFlip _ae2f_MathIntFlip
#define __ae2f_MathIntFlip_imp _ae2f_MathIntFlip_imp
#else
#undef __ae2f_MathIntFlip
#undef __ae2f_MathIntFlip_imp
#endif

typedef struct ae2f_MathIntFlip_t {
	size_t j;
	size_t ovec, ivec;
	__ae2f_MathUtilFlag2(3, unsigned sbit : 1;) buf;
} ae2f_MathIntFlip_t;

ae2f_MAC() _ae2f_MathIntFlip_imp(ae2f_MathIntFlip_t vi_flip,
		const ae2f_MathInt *const __i, ae2f_iMathMem __i_vec,
		const ae2f_MathInt *const __o,
		ae2f_oMathMem __o_vec) {
	/** +1 for second compliment */
	vi_flip.buf.a = 0b10;
	vi_flip.ivec = (__i)->vecbegpoint + (__i)->sz - 1;

	vi_flip.buf.b.sbit =
		(__o)->sign && __ae2f_MathUtilBVGetArr(__i_vec, vi_flip.ivec);

	for (vi_flip.j = 0; vi_flip.j < (__o)->sz; vi_flip.j++) {
		vi_flip.ovec = (__o)->vecbegpoint + vi_flip.j;
		vi_flip.ivec = (__i)->vecbegpoint + vi_flip.j;

		vi_flip.buf.a = !(vi_flip.j < (__i)->sz
				? __ae2f_MathUtilBVGetArr((__i_vec), vi_flip.ivec)
				: vi_flip.buf.b.sbit) /** Compliment 1 */
			+ (vi_flip.buf.b._1);

		__ae2f_MathUtilBVSetAssignArr(__o_vec, vi_flip.ovec, vi_flip.buf.b._0);
	}
}

/**
 * @macro __ae2f_MathIntFlip
 *
 * @brief
 * `__o` = -`__i`
 * */
	ae2f_MAC()
_ae2f_MathIntFlip(ae2f_MathMemOutErr reterr, const ae2f_MathInt *const __i,
		ae2f_iMathMem __i_vec, const ae2f_MathInt *const __o,
		ae2f_oMathMem __o_vec) 
{
	if ((reterr) && *(reterr))
		;
	else if (!(__i)) {
		if ((reterr))
			*(reterr) |= ae2f_errGlob_PTR_IS_NULL;
	} else if (!(__o)) {
		if ((reterr))
			*(reterr) |= ae2f_errGlob_PTR_IS_NULL;
	} else if (!(__i_vec)) {
		if ((reterr))
			*(reterr) |= ae2f_errGlob_PTR_IS_NULL;
	} else if (!(__o_vec)) {
		if ((reterr))
			*(reterr) |= ae2f_errGlob_PTR_IS_NULL;
	} else {
		ae2f_MathIntFlip_t vi_flip;
		__ae2f_MathIntFlip_imp(vi_flip, __i, __i_vec, __o, __o_vec);
	}
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathIntAdd _ae2f_MathIntAdd
#define __ae2f_MathIntAdd_imp _ae2f_MathIntAdd_imp
#else
#undef __ae2f_MathIntAdd
#undef __ae2f_MathIntAdd_imp
#endif

typedef struct ae2f_MathIntAdd_t {
	size_t j;
	size_t ovec, avec, bvec;
	__ae2f_MathUtilFlag2(4, unsigned char sb_0 : 1; unsigned char sb_1 : 1;) buf;
} ae2f_MathIntAdd_t;

ae2f_MAC()
	_ae2f_MathIntAdd_imp(ae2f_MathIntAdd_t vi_add, const ae2f_MathInt *const _a,
			ae2f_iMathMem _a_vec, const ae2f_MathInt *const _b,
			ae2f_iMathMem _b_vec, const ae2f_MathInt *const _o,
			ae2f_oMathMem _o_vec) {
		vi_add.buf.a = 0b00; /**
				      * 0: a
				      * 1: b
				      * */

		vi_add.buf.b.sb_0 =
			((_a)->sign &&
			 __ae2f_MathUtilBVGetArr((_a_vec), ((_a)->vecbegpoint + (_a)->sz - 1)));

		vi_add.buf.b.sb_1 =
			(((_b)->sign &&
			  __ae2f_MathUtilBVGetArr((_b_vec), ((_b)->vecbegpoint + (_b)->sz - 1))));

		for (vi_add.j = 0; vi_add.j < (_o)->sz; vi_add.j++) {
			vi_add.avec = (_a)->vecbegpoint + vi_add.j;
			vi_add.bvec = (_b)->vecbegpoint + vi_add.j;
			vi_add.ovec = (_o)->vecbegpoint + vi_add.j;

			vi_add.buf.c.a =
				(vi_add.j < (_a)->sz ? __ae2f_MathUtilBVGetArr(_a_vec, vi_add.avec)
				 : vi_add.buf.b.sb_0) +
				(vi_add.j < (_b)->sz ? __ae2f_MathUtilBVGetArr(_b_vec, vi_add.bvec)
				 : vi_add.buf.b.sb_1) +
				(vi_add.buf.b._1);

			__ae2f_MathUtilBVSetAssignArr(_o_vec, vi_add.ovec, vi_add.buf.b._0);
		}
	}

/**
 * @macro __ae2f_MathIntAdd
 * @brief `_out` = `_a` + `_b`;
 * */
ae2f_MAC() _ae2f_MathIntAdd(ae2f_err_t *reterr, const ae2f_MathInt *const _a,
		ae2f_iMathMem _a_vec, const ae2f_MathInt *const _b,
		ae2f_iMathMem _b_vec, const ae2f_MathInt *const _o,
		ae2f_oMathMem _o_vec) {
	if (((reterr) && *(reterr)))
		;
	else if (!((_a) && (_b) && (_o) && (_a_vec) && (_b_vec) && (_o_vec))) {
		((reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL));
	} else {
		ae2f_MathIntAdd_t vi_add;
		__ae2f_MathIntAdd_imp(vi_add, _a, _a_vec, _b, _b_vec, _o, _o_vec);
	}
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathIntSub _ae2f_MathIntSub
#define __ae2f_MathIntSub_imp _ae2f_MathIntSub_imp
#else
#undef __ae2f_MathIntSub
#undef __ae2f_MathIntSub_imp
#endif

typedef ae2f_MathIntAdd_t ae2f_MathIntSub_t;

ae2f_MAC()
	_ae2f_MathIntSub_imp(ae2f_MathIntSub_t vi_sub, const ae2f_MathInt *const _a,
			ae2f_iMathMem _a_vec, const ae2f_MathInt *const _b,
			ae2f_iMathMem _b_vec, const ae2f_MathInt *const _o,
			ae2f_oMathMem _o_vec) {
		vi_sub.buf.a = 0b10; /**
				      * 0: a
				      * 1: b
				      * */

		vi_sub.buf.b.sb_0 =
			((_a)->sign &&
			 __ae2f_MathUtilBVGetArr((_a_vec), ((_a)->vecbegpoint + (_a)->sz - 1)));

		vi_sub.buf.b.sb_1 =
			(((_b)->sign &&
			  __ae2f_MathUtilBVGetArr((_b_vec), ((_b)->vecbegpoint + (_b)->sz - 1))));

		for (vi_sub.j = 0; vi_sub.j < (_o)->sz; vi_sub.j++) {
			vi_sub.avec = (_a)->vecbegpoint + vi_sub.j;
			vi_sub.bvec = (_b)->vecbegpoint + vi_sub.j;
			vi_sub.ovec = (_o)->vecbegpoint + vi_sub.j;

			vi_sub.buf.a =
				(vi_sub.j < (_a)->sz ? __ae2f_MathUtilBVGetArr(_a_vec, vi_sub.avec)
				 : vi_sub.buf.b.sb_0) +
				!(vi_sub.j < (_b)->sz ? __ae2f_MathUtilBVGetArr(_b_vec, vi_sub.bvec)
						: vi_sub.buf.b.sb_1) +
				(vi_sub.buf.b._1);

			__ae2f_MathUtilBVSetAssignArr(_o_vec, vi_sub.ovec, vi_sub.buf.b._0);
		}
	}

/**
 * @macro __ae2f_MathIntSub
 * @brief `_out` = `_a` - `_b`;
 * */
ae2f_MAC()
	_ae2f_MathIntSub(ae2f_MathMemOutErr reterr, const ae2f_MathInt *const _a,
			ae2f_iMathMem _a_vec, const ae2f_MathInt *const _b,
			ae2f_iMathMem _b_vec, const ae2f_MathInt *const _o,
			ae2f_oMathMem _o_vec) {
		if (((reterr) && *(reterr)))
			;
		else if (!((_a) && (_b) && (_o) && (_a_vec) && (_b_vec) && (_o_vec))) {
			((reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL));
		} else {
			ae2f_MathIntSub_t vi_sub;
			__ae2f_MathIntSub_imp(vi_sub, _a, _a_vec, _b, _b_vec, _o, _o_vec);
		}
	}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathIntFill _ae2f_MathIntFill
#define __ae2f_MathIntFill_imp _ae2f_MathIntFill_imp
#else
#undef __ae2f_MathIntFill_imp
#endif

ae2f_MAC()
	_ae2f_MathIntFill_imp(size_t v, const ae2f_pMathInt _a, ae2f_oMathMem a_vec,
			unsigned mask, unsigned char masklen) {
		__ae2f_MathUtilBVMask_imp(__ae2f_MathUtilBVGet, v, a_vec, (_a)->vecbegpoint,
				(_a)->vecbegpoint + (_a)->sz, mask, masklen);
	}

/**
 * @macro __ae2f_MathIntFill
 * @brief
 * `a` = 0;  \n
 * `a` = -1;
 * */
ae2f_MAC() _ae2f_MathIntFill(ae2f_MathMemOutErr reterr,
		const ae2f_MathInt *const _a, ae2f_oMathMem a_vec,
		unsigned mask, unsigned char masklen) {
	if (!(masklen) || (reterr) && *(reterr))
		;
	else if (!((_a) && (a_vec)))
		(reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);
	else if ((_a)->vecbegpoint + (_a)->sz < (_a)->vecbegpoint)
		(reterr) && (*(reterr) |= ae2f_errGlob_WRONG_OPERATION);
	else {
		size_t v;
		__ae2f_MathIntFill_imp(v, _a, a_vec, mask, masklen);
	}
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathIntCmpZero _ae2f_MathIntCmpZero
#define __ae2f_MathIntCmpZero_imp _ae2f_MathIntCmpZero_imp
#define __ae2f_MathIntCmpZeroU_imp _ae2f_MathIntCmpZeroU_imp
#else
#undef __ae2f_MathIntCmpZero
#undef __ae2f_MathIntCmpZero_imp
#undef __ae2f_MathIntCmpZeroU_imp
#endif

typedef struct ae2f_MathIntCmpZeroU_t {
	size_t m_i;
	ae2f_CmpFunRet_t m_out;
} ae2f_MathIntCmpZeroU_t;

ae2f_MAC() _ae2f_MathIntCmpZeroU_imp(ae2f_MathIntCmpZeroU_t vi_cmpz,
		const ae2f_MathInt *const in,
		ae2f_iMathMem in_vec) {
	for (
			vi_cmpz.m_i = 0; 
			vi_cmpz.m_i < (in)->sz && !__ae2f_MathUtilBVGetArr(
				in_vec, vi_cmpz.m_i + (in)->vecbegpoint);
			vi_cmpz.m_i++);

	vi_cmpz.m_out = ae2f_CmpFunRet_RISLESSER * (vi_cmpz.m_i < (in)->sz);

}

ae2f_MAC() _ae2f_MathIntCmpZero_imp(ae2f_MathIntCmpZeroU_t vi_cmpz,
		const ae2f_MathInt *const in,
		ae2f_iMathMem in_vec) {
	if ((in)->sign && __ae2f_MathUtilBVGetArr((in_vec), ((in)->vecbegpoint + (in)->sz - 1))) {
		vi_cmpz.m_out = ae2f_CmpFunRet_LISLESSER;
	} else {
		__ae2f_MathIntCmpZeroU_imp(vi_cmpz, in, in_vec);
	}
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
 * */
ae2f_MAC()
_ae2f_MathIntCmpZero(ae2f_MathMemOutErr reterr,
		const ae2f_MathInt *const in, ae2f_iMathMem in_vec,
		ae2f_CmpFunRet_t *const out)
{
	if (!(out) || ((reterr) && *(reterr)))
		;
	else unless ((in) && (in_vec)) {
		(reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);
	} else {
		if ((in)->sign && __ae2f_MathUtilBVGetArr((in_vec), ((in)->vecbegpoint + (in)->sz - 1))) 
		{
			*(out) = ae2f_CmpFunRet_LISLESSER;
		} else {
			ae2f_MathIntCmpZeroU_t vi_cmpz;
			__ae2f_MathIntCmpZeroU_imp(vi_cmpz, in, in_vec);
			*(out) = vi_cmpz.m_out;
		}
	}
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathIntCmp _ae2f_MathIntCmp
#define __ae2f_MathIntCmp_imp _ae2f_MathIntCmp_imp
#else
#undef __ae2f_MathIntCmp
#undef __ae2f_MathIntCmp_imp
#endif

typedef struct ae2f_MathIntCmp_t {
	size_t sz_gt, i;
	size_t av, bv;
	unsigned char sign : 1;

	/** output */
	ae2f_CmpFunRet_t m_out : 2;
} ae2f_MathIntCmp_t;

ae2f_MAC() _ae2f_MathIntCmp_imp(ae2f_MathIntCmp_t vi_cmp, const ae2f_MathInt *const _a,
			ae2f_iMathMem a_vec, const ae2f_MathInt *const _b,
			ae2f_iMathMem b_vec) {
	vi_cmp.sz_gt = (_a)->sz < (_b)->sz ? (_b)->sz : (_a)->sz;
	vi_cmp.m_out = 0;
	if ((vi_cmp.sign =
				((_a)->sign && __ae2f_MathUtilBVGetArr(
					(a_vec), ((_a)->vecbegpoint + (_a)->sz - 1)))) !=
			((_b)->sign &&
			 __ae2f_MathUtilBVGetArr((b_vec), ((_b)->vecbegpoint + (_b)->sz -
					 1)))) 
	{/** Two signs are different */
		vi_cmp.m_out = vi_cmp.sign                   /* is sign of a negative */
			? ae2f_CmpFunRet_LISLESSER
			: ae2f_CmpFunRet_RISLESSER;
	} else {
		vi_cmp.m_out = 0;
		for (
				vi_cmp.i = vi_cmp.sz_gt - 1; 
				vi_cmp.i != ae2f_static_cast(size_t, -1) && !vi_cmp.m_out;
				vi_cmp.i--) 
		{
			vi_cmp.av = (_a)->vecbegpoint + vi_cmp.i;
			vi_cmp.bv = (_b)->vecbegpoint + vi_cmp.i;

			vi_cmp.m_out =
				ae2f_static_cast(int8_t,
						vi_cmp.i < (_a)->sz
						? __ae2f_MathUtilBVGetArr((a_vec), vi_cmp.av)
						: vi_cmp.sign) -
				ae2f_static_cast(int8_t,
						vi_cmp.i < (_b)->sz
						? __ae2f_MathUtilBVGetArr((b_vec), vi_cmp.bv)
						: vi_cmp.sign); /* is abs(_a) greater */
		}
	}
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
 * */
ae2f_MAC()
	_ae2f_MathIntCmp(ae2f_MathMemOutErr errret, const ae2f_MathInt *const _a,
			ae2f_iMathMem a_vec, const ae2f_MathInt *const _b,
			ae2f_iMathMem b_vec, ae2f_CmpFunRet_t *const out) {
		if ((errret) && *(errret))
			;
		else if (!((out) && (_a) && (a_vec) && (_b) && (b_vec)))
			(errret) && (*(errret) |= ae2f_errGlob_PTR_IS_NULL);
		else if ((_a)->sz - (_a)->sign < 1 || (_b)->sz - (_b)->sign < 1)
			(errret) && (*(errret) |= ae2f_errGlob_WRONG_OPERATION);
		else {
			ae2f_MathIntCmp_t vi_cmp;
			__ae2f_MathIntCmp_imp(vi_cmp, _a, a_vec, _b, b_vec);
			*(out) = vi_cmp.m_out;
		}
	}

#if __ae2f_MACRO_GENERATED
#undef __ae2f_MathIntBitL
#undef __ae2f_MathIntBitL_imp
#undef __ae2f_MathIntBitR
#undef __ae2f_MathIntBitR_imp
#undef __ae2f_MathIntBitRRefA
#undef __ae2f_MathIntBitRRef
#undef __ae2f_MathIntBitRRef_imp
#else
#define __ae2f_MathIntBitL _ae2f_MathIntBitL
#define __ae2f_MathIntBitL_imp _ae2f_MathIntBitL_imp
#define __ae2f_MathIntBitR _ae2f_MathIntBitR
#define __ae2f_MathIntBitR_imp _ae2f_MathIntBitR_imp
#define __ae2f_MathIntBitRRefA _ae2f_MathIntBitRRefA
#define __ae2f_MathIntBitRRef _ae2f_MathIntBitRRef
#define __ae2f_MathIntBitRRef_imp(...) _ae2f_MathIntBitRRef_imp(__VA_ARGS__)
#endif

/**
 * @param v_bitrh output pointer padding index
 * */
ae2f_MAC()
	_ae2f_MathIntBitRRef_imp(size_t v_bitrh, const ae2f_pMathInt _ai,
			size_t bitcount, ae2f_pMathInt _oi) {
		if (bitcount) {
			(_oi)->sign = (_ai)->sign;
			(_oi)->sz = (_ai)->sz - (bitcount);
			(_oi)->vecbegpoint = v_bitrh = (_oi)->vecbegpoint + (bitcount);
			v_bitrh >>= 3;
		} else {
			*(_oi) = *(_ai);
			v_bitrh = 0;
		}
	}

/**
 * @def __ae2f_MathIntBitRRef
 * @brief
 * `_oi` = `_ai` << `bitcount`;
 *
 * @param _oiidx
 * Unlike __ae2f_MathIntBitRRefA, the stored original value will be
 * initialised.
 * */
ae2f_MAC() _ae2f_MathIntBitRRef(ae2f_MathMemOutErr err, const ae2f_pMathInt _ai,
		size_t bitcount, ae2f_pMathInt _oi,
		size_t *const _oiidx) {
	if ((err) && *(err))
		;
	else if ((_ai) && (_oi) && (_oiidx)) {
		size_t v_bitrh;
		__ae2f_MathIntBitRRef_imp(v_bitrh, _ai, bitcount, _oi);
		*(_oiidx) = v_bitrh;
	} else
		(err) && (*(err) |= ae2f_errGlob_PTR_IS_NULL);
}

/**
 * @def __ae2f_MathIntBitRRefA
 * @brief
 * `_oi` = `_ai` << `bitcount`;
 *
 * @param _oiidx
 * The pointer where the additional byte padding for adding to the original
 * vector pointer.
 *
 * The result will be added with its stored original value, not initialised.
 * For zeroing version, use __ae2f_MathIntBitRHeader.
 * */
ae2f_MAC() _ae2f_MathIntBitRRefA(ae2f_MathMemOutErr err,
		const ae2f_pMathInt _ai, size_t bitcount,
		ae2f_pMathInt _oi, size_t *const _oiidx) {

	if ((err) && *(err))
		;
	else if ((_ai) && (_oi) && (_oiidx)) {
		size_t v_bitrh;
		__ae2f_MathIntBitRRef_imp(v_bitrh, _ai, bitcount, _oi);
		*(_oiidx) += v_bitrh;
	} else
		(err) && (*(err) |= ae2f_errGlob_PTR_IS_NULL);
}

ae2f_MAC()
	_ae2f_MathIntBitL_imp(size_t vi_bitl, size_t bitcount,
			const ae2f_MathInt *const in, ae2f_iMathMem in_vec,
			const ae2f_MathInt *const out,
			ae2f_oMathMem out_vec) 
{
	for(vi_bitl = (out)->sz; vi_bitl != -1 && (in)->sz + (bitcount) <= vi_bitl; vi_bitl--)
		__ae2f_MathUtilBVSetAssignArr(out_vec, vi_bitl, 0);

	for (; vi_bitl != -1 && vi_bitl >= (bitcount); vi_bitl--)
		__ae2f_MathUtilBVSetAssignArr(
				out_vec, vi_bitl,
				__ae2f_MathUtilBVGetArr(in_vec, vi_bitl - (bitcount)));

	for(; vi_bitl != -1; vi_bitl--) 
		__ae2f_MathUtilBVSetAssignArr(out_vec, vi_bitl, 0);

}

/**
 * @macro __ae2f_MathIntBitL
 * @brief
 * `out` = `in` << `bitcount`;
 * */
ae2f_MAC()
	_ae2f_MathIntBitL(ae2f_MathMemOutErr reterr, size_t bitcount,
			const ae2f_MathInt *const in, ae2f_iMathMem in_vec,
			const ae2f_MathInt *const out, ae2f_oMathMem out_vec) {
		if (!(bitcount) && (reterr) && *(reterr))
			;
		else unless ((in) && (in_vec) && (out) && (out_vec))
			(reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);
		else if ((in)->sz + (bitcount) < (in)->sz)
			(reterr) && (*(reterr) |= ae2f_errGlob_WRONG_OPERATION);
		else {
			size_t vi_bitl;
			__ae2f_MathIntBitL_imp(vi_bitl, bitcount, in, in_vec, out, out_vec);
		}
	}

typedef struct ae2f_MathIntBitR_t {
	size_t c, i;
	size_t _o, _i;
} ae2f_MathIntBitR_t;

ae2f_MAC()
	_ae2f_MathIntBitR_imp(ae2f_MathIntBitR_t vi_bitr, size_t bitcount,
			const ae2f_MathInt *const in, ae2f_iMathMem in_vec,
			const ae2f_MathInt *out, ae2f_oMathMem out_vec) {
		for (vi_bitr.i = 0;
				vi_bitr.i < (out)->sz && vi_bitr.i + (bitcount) < (in)->sz;
				vi_bitr.i++) 
		{
			vi_bitr._o = (out)->vecbegpoint + vi_bitr.i;
			vi_bitr._i = (in)->vecbegpoint + (vi_bitr.i + (bitcount));

			__ae2f_MathUtilBVSetAssignArr(
					(out_vec), vi_bitr._o, __ae2f_MathUtilBVGetArr((in_vec), vi_bitr._i));
		}

		/* Then fill remaining bits with zeros */
		for (; vi_bitr.i < (out)->sz; vi_bitr.i++) {
			vi_bitr._o = ((out)->vecbegpoint + vi_bitr.i);
			__ae2f_MathUtilBVSetAssignArr((out_vec), vi_bitr._o, 0);
		}
	}

/**
 * @macro __ae2f_MathIntBitR
 * @brief
 * `out` = `in` >> `bitcount`;
 * @param reterr	{ae2f_err_t*}
 * @param bitcount	{intptr_t}
 * @param in		{const ae2f_MathInt*}
 * @param in_vec	{ae2f_iMathMem}
 * @param out		{const ae2f_MathInt*}
 * @param out_vec	{ae2f_oMathMem}
 * */
ae2f_MAC() _ae2f_MathIntBitR(ae2f_MathMemOutErr reterr, size_t bitcount,
		const ae2f_MathInt *const in, ae2f_iMathMem in_vec,
		const ae2f_MathInt *out, ae2f_oMathMem out_vec) {
	if (!(bitcount) && (reterr) && *(reterr))
		;
	else unless ((in) && (in_vec) && (out) && (out_vec))
		(reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);
	else if ((in)->sz < (bitcount))
		(reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);
	else {
		/* First copy the input bits shifted right */
		ae2f_MathIntBitR_t vi_bitr;
		__ae2f_MathIntBitR_imp(vi_bitr, bitcount, in, in_vec, out, out_vec);
	}
}

#if __ae2f_MACRO_GENERATED
#undef __ae2f_MathIntShiftL_imp
#undef __ae2f_MathIntShiftR_imp
#undef __ae2f_MathIntShiftL
#undef __ae2f_MathIntShiftR
#else
#define __ae2f_MathIntShiftL_imp _ae2f_MathIntShiftL_imp
#define __ae2f_MathIntShiftR_imp _ae2f_MathIntShiftR_imp
#define __ae2f_MathIntShiftL _ae2f_MathIntShiftL
#define __ae2f_MathIntShiftR _ae2f_MathIntShiftR
#endif

typedef union ae2f_MathIntBitShift_t {
	ae2f_MathIntBitR_t m_r;
	size_t m_l;
} ae2f_MathIntBitShift_t;

ae2f_MAC()
	_ae2f_MathIntShiftL_imp(ae2f_MathIntBitShift_t vi_shift, intptr_t bitcount,
			const ae2f_MathInt *const in, ae2f_iMathMem in_vec,
			const ae2f_MathInt *out, ae2f_oMathMem out_vec) {
		if (bitcount > 0)
			__ae2f_MathIntBitL_imp(vi_shift.m_l, ae2f_static_cast(size_t, bitcount), in,
					in_vec, out, out_vec);
		else if (bitcount < 0)
			__ae2f_MathIntBitR_imp(vi_shift.m_r, ae2f_static_cast(size_t, -bitcount),
					in, in_vec, out, out_vec);
	}

ae2f_MAC() _ae2f_MathIntShiftL(ae2f_MathMemOutErr err, intptr_t bitcount,
		const ae2f_pMathInt in, ae2f_iMathMem in_vec,
		const ae2f_pMathInt out, ae2f_oMathMem out_vec) {
	if ((err) && *(err))
		;
	else unless ((in) && (in_vec) && (out) && (out_vec))
		(err) && (*(err) |= ae2f_errGlob_PTR_IS_NULL);
	else {
		ae2f_MathIntBitShift_t vi_shift;
		__ae2f_MathIntShiftL_imp(vi_shift, bitcount, in, in_vec, out, out_vec);
	}
}

ae2f_MAC()
	_ae2f_MathIntShiftR_imp(ae2f_MathIntBitShift_t vi_shift, intptr_t bitcount,
			const ae2f_MathInt *const in, ae2f_iMathMem in_vec,
			const ae2f_MathInt *out, ae2f_oMathMem out_vec) {
		if (bitcount > 0)
			__ae2f_MathIntBitR_imp(vi_shift.m_r, ae2f_static_cast(size_t, bitcount), in,
					in_vec, out, out_vec);
		else if (bitcount < 0)
			__ae2f_MathIntBitL_imp(vi_shift.m_l, ae2f_static_cast(size_t, -bitcount),
					in, in_vec, out, out_vec);
	}

ae2f_MAC() _ae2f_MathIntShiftR(ae2f_MathMemOutErr err, intptr_t bitcount,
		const ae2f_pMathInt in, ae2f_iMathMem in_vec,
		const ae2f_pMathInt out, ae2f_oMathMem out_vec) {
	if ((err) && *(err))
		;
	else unless ((in) && (in_vec) && (out) && (out_vec))
		(err) && (*(err) |= ae2f_errGlob_PTR_IS_NULL);
	else {
		ae2f_MathIntBitShift_t vi_shift;
		__ae2f_MathIntShiftR_imp(vi_shift, bitcount, in, in_vec, out, out_vec);
	}
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathIntMul _ae2f_MathIntMul
#define __ae2f_MathIntMul_imp _ae2f_MathIntMul_imp
#else
#undef __ae2f_MathIntMul
#undef __ae2f_MathIntMul_imp
#endif

typedef union ae2f_MathIntMulStack_t {
	ae2f_MathIntCast_t m_cast;
	ae2f_MathIntFlip_t m_flip;
	size_t m_szneeded;
	ae2f_MathIntAdd_t m_addsub;
} ae2f_MathIntMulStack_t;

typedef struct ae2f_MathIntMul_t {
	size_t i, oveci;
	ae2f_MathInt o[1];
	unsigned char sign : 1;
	ae2f_MathIntMulStack_t m_stack;
} ae2f_MathIntMul_t;

ae2f_MAC()
	_ae2f_MathIntMul_imp(ae2f_MathIntMul_t vi_mul, const ae2f_MathInt *const _a,
			ae2f_iMathMem a_vec, const ae2f_MathInt *const _b,
			ae2f_iMathMem b_vec, const ae2f_MathInt *const out,
			ae2f_oMathMem out_vec) {
		vi_mul.sign = __ae2f_MathIntIsNegative(_a, a_vec); /* sign of a */
		*vi_mul.o = *(out);

		vi_mul.i = vi_mul.oveci = 0;
		if (vi_mul.sign) {
			__ae2f_MathIntFlip_imp(vi_mul.m_stack.m_flip, _b, b_vec, out,
					out_vec); /* complement 2 */
		} else {
			__ae2f_MathIntFill_imp(vi_mul.m_stack.m_szneeded, out, out_vec, 0, 1);
		}
		while ((out)->sz && vi_mul.i < (_a)->sz - vi_mul.sign) {
			if (vi_mul.sign ^ __ae2f_MathUtilBVGetArr(
						(a_vec), ((_a)->vecbegpoint +
							vi_mul.i))) { /** Addition (conditional) */

				if (vi_mul.sign) {
					__ae2f_MathIntSub_imp(vi_mul.m_stack.m_addsub, _b, b_vec, vi_mul.o,
							(out_vec) + vi_mul.oveci, vi_mul.o,
							(out_vec) + vi_mul.oveci);
				}

				else {
					__ae2f_MathIntAdd_imp(vi_mul.m_stack.m_addsub, _b, b_vec, vi_mul.o,
							(out_vec) + vi_mul.oveci, vi_mul.o,
							(out_vec) + vi_mul.oveci);
				}
			}

			/** Increament */
			vi_mul.i++;
			(vi_mul.o)->sz--;
			(vi_mul.o)->vecbegpoint++;

			if (!((vi_mul.o)->vecbegpoint & 7)) {
				(vi_mul.o)->vecbegpoint = 0;
				vi_mul.oveci++;
			}
		}
	}

/**
 * @macro __ae2f_MathIntMul
 * @brief
 * `out` = `a` * `b`;
 * */
	ae2f_MAC()
_ae2f_MathIntMul(ae2f_MathMemOutErr reterr, const ae2f_MathInt *const _a,
		ae2f_iMathMem a_vec, const ae2f_MathInt *const _b,
		ae2f_iMathMem b_vec, const ae2f_MathInt *const out,
		ae2f_oMathMem out_vec)

{
	if ((reterr) && *(reterr))
		;
	else unless ((_a) && (a_vec) && (_b) && (b_vec) && (out) && (out_vec))
		(reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);
	else {
		ae2f_MathIntMul_t vi_mul;
		__ae2f_MathIntMul_imp(vi_mul, _a, a_vec, _b, b_vec, out, out_vec);
	}
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathIntSz _ae2f_MathIntSz
#define __ae2f_MathIntSz_imp _ae2f_MathIntSz_imp
#else
#undef __ae2f_MathIntSz_imp
#endif

/**
 * @param v_sz output
 * */
ae2f_MAC()
	_ae2f_MathIntSz_imp(size_t v_sz,
			const ae2f_MathInt *const _a, ae2f_iMathMem a_vec) {
		v_sz = (_a)->sz - 1;
		for (; 
				v_sz != 
					ae2f_static_cast(size_t, -1) 
				&& 	!__ae2f_MathUtilBVGetArr((a_vec), (v_sz + (_a)->vecbegpoint)); 
				v_sz--
				);
		v_sz++;
	}

/**
 * @macro __ae2f_MathIntSz
 * @brief retsz = sizeof(`a`);
 * @param retsz	{size_t*}
 * @param a	{const ae2f_MathInt}
 * @param a_vec	{ae2f_iMathMem}
 * */
ae2f_MAC() _ae2f_MathIntSz(size_t *const retsz, const ae2f_MathInt *const _a,
		ae2f_iMathMem a_vec) {
	if (!(retsz))
		;
	else if (!((_a) && (a_vec))) {
		*(retsz) = -1;
	} else {
		size_t v_sz;
		__ae2f_MathIntSz_imp(v_sz, _a, a_vec);
		*retsz = v_sz;
	}
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathIntNullSz _ae2f_MathIntNullSz
#define __ae2f_MathIntNullSz_imp _ae2f_MathIntNullSz_imp
#endif

ae2f_MAC() _ae2f_MathIntNullSz_imp(size_t v_nullsz, const ae2f_pMathInt _a, ae2f_iMathMem a_vec)
{
	for (v_nullsz = 0;
			v_nullsz < (_a)->sz &&
			!__ae2f_MathUtilBVGetArr((a_vec), v_nullsz);
			(v_nullsz)++)
		;
}

/**
 * @macro __ae2f_MathIntNullSz
 * @brief
 * Count of series of null[0]s on right size.
 * */
ae2f_MAC()
	_ae2f_MathIntNullSz(size_t *const retsz, const ae2f_MathInt *const _a,
			ae2f_iMathMem a_vec) {
		if ((retsz)) {
			size_t v_nullsz;
			__ae2f_MathIntNullSz_imp(v_nullsz, _a, a_vec);
			*(retsz) = v_nullsz;
		}
	}

#define ae2f_MathIntBump_POSITIVE 0
#define ae2f_MathIntBump_NEGATIVE 1

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathIntBumpO _ae2f_MathIntBumpO
#define __ae2f_MathIntBumpO_imp _ae2f_MathIntBumpO_imp
#else
#undef __ae2f_MathIntBumpO
#undef __ae2f_MathIntBumpO_imp
#endif

typedef ae2f_MathIntSub_t ae2f_MathIntBumpO_t;

ae2f_MAC() _ae2f_MathIntBumpO_imp(
		ae2f_MathIntSub_t vi_bump
		, const unsigned char bump
		, const ae2f_MathInt *const _a, ae2f_iMathMem a_vec
		, ae2f_oMathMem o_vec
		) {
	vi_bump.buf.a = 0;
	for (vi_bump.j = 0; vi_bump.j < (_a)->sz; vi_bump.j++) {
		vi_bump.avec = (_a)->vecbegpoint + vi_bump.j;
		vi_bump.buf.c.a =
			(vi_bump.j < (_a)->sz 
			 ? __ae2f_MathUtilBVGetArr(a_vec, vi_bump.avec)
			 : vi_bump.buf.b.sb_0) + (vi_bump.j ? (bump) : 1) + (vi_bump.buf.b._1);

		__ae2f_MathUtilBVSetAssignArr(o_vec, vi_bump.avec, vi_bump.buf.b._0);
	}
}

/**
 * @macro	__ae2f_MathIntBump
 * @brief
 * if (`bump`) `a`--; else `a`++;
 * */
ae2f_MAC() _ae2f_MathIntBumpO(
		ae2f_MathMemOutErr reterr, const unsigned char bump
		,const ae2f_MathInt *const _a, ae2f_iMathMem a_vec
		,ae2f_oMathMem o_vec) 
{
	if (((reterr) && *(reterr)))
		;
	else unless ((_a) && (a_vec) && (o_vec)) {
		((reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL));
	} else {
		ae2f_MathIntSub_t vi_bump;
		__ae2f_MathIntBumpO_imp(vi_bump, bump, _a, a_vec, o_vec);
	}
}

#if 1
#undef __ae2f_MathIntBump
#define __ae2f_MathIntBump(reterr, bump, _a, a_vec)                            \
	__ae2f_MathIntBumpO(reterr, bump, _a, a_vec, a_vec)
#endif

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathIntDivU _ae2f_MathIntDivU
#define __ae2f_MathIntDivU_imp _ae2f_MathIntDivU_imp
#else
#undef __ae2f_MathIntDivU
#undef __ae2f_MathIntDivU_imp
#endif

typedef union ae2f_MathIntDivUStack_t {
	ae2f_MathIntFlip_t m_flip;
	ae2f_MathIntCast_t m_cast;
	ae2f_MathIntCmpZeroU_t m_cmpzu;
	ae2f_MathIntCmp_t m_cmp;
	ae2f_MathIntSub_t m_sub;
	size_t m_sz;
} ae2f_MathIntDivUStack_t;

typedef struct ae2f_MathIntDivU_t {
	size_t j, ridx2;
	ae2f_MathInt _r, r2, _b, _q;
	ae2f_err_t m_reterr;
	ae2f_MathIntDivUStack_t m_stack;
} ae2f_MathIntDivU_t;

ae2f_MAC() _ae2f_MathIntDivU_imp(ae2f_MathIntDivU_t vi_divu,
		const ae2f_MathInt *const _a, ae2f_iMathMem a_vec,
		const ae2f_MathInt *const prm_b, ae2f_iMathMem b_vec,
		const ae2f_MathInt *const prm_q, ae2f_oMathMem q_vec,
		const ae2f_MathInt *prm_r, ae2f_oMathMem r_vec) {
	__ae2f_MathIntFill_imp(vi_divu.m_stack.m_sz, prm_q, q_vec, 0, 1);
	__ae2f_MathIntCast_imp(vi_divu.m_stack.m_cast, _a, a_vec, prm_r, r_vec);

	vi_divu._r = *(prm_r);
	vi_divu.r2.sz = (prm_b)->sz;
	vi_divu.r2.vecbegpoint = 0;
	vi_divu.r2.sign = 0;
	vi_divu._b = *(prm_b);
	vi_divu._q = *(prm_q);
	vi_divu.m_reterr = 0;

	__ae2f_MathIntCmpZero_imp(vi_divu.m_stack.m_cmpzu, &vi_divu._b, b_vec);

	if (!vi_divu.m_stack.m_cmpzu.m_out) {
		/*`b` is zero. terminating... */
		vi_divu.m_reterr = ae2f_errGlob_WRONG_OPERATION;
	} else {
		vi_divu._b.sign = vi_divu._r.sign = vi_divu._q.sign = 0;
		__ae2f_MathIntSz_imp(vi_divu._r.sz, &vi_divu._r,
				r_vec);
		__ae2f_MathIntSz_imp(vi_divu._b.sz, &vi_divu._b,
				b_vec);
		if (vi_divu._b.sz <= vi_divu._r.sz)
			for (vi_divu.j = vi_divu._r.sz - vi_divu._b.sz - 1;
					vi_divu.j != ae2f_static_cast(size_t, -1); vi_divu.j--) {
				vi_divu.r2.vecbegpoint =
					(ae2f_static_cast(uint8_t, vi_divu._r.vecbegpoint) + vi_divu.j) & 7;
				vi_divu.ridx2 =
					((vi_divu._r.vecbegpoint + vi_divu.j) >> 3); /* b cmp r2 */
				__ae2f_MathIntCmp_imp(
						vi_divu.m_stack.m_cmp, &vi_divu._b, b_vec, &vi_divu.r2,
						(r_vec) + vi_divu.ridx2); /* if b <= r2: r2 -= b; */

				if ((vi_divu.m_stack.m_cmp.m_out) <= 0) {
					__ae2f_MathIntSub_imp(vi_divu.m_stack.m_sub, &vi_divu.r2,
							(r_vec) + vi_divu.ridx2, &vi_divu._b, b_vec,
							&vi_divu.r2, (r_vec) + vi_divu.ridx2);

					/** q */
					if (vi_divu.j < vi_divu._q.sz) {
						(q_vec)[(vi_divu._q.vecbegpoint + vi_divu.j) >> 3] |=
							1 << ((vi_divu._q.vecbegpoint + vi_divu.j) & 7);
					}
				}
			}
	}
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
 * */
ae2f_MAC()
	_ae2f_MathIntDivU(ae2f_MathMemOutErr reterr, const ae2f_MathInt *const _a,
			ae2f_iMathMem a_vec, const ae2f_MathInt *const prm_b,
			ae2f_iMathMem b_vec, const ae2f_MathInt *const prm_q,
			ae2f_oMathMem q_vec, const ae2f_MathInt *prm_r,
			ae2f_oMathMem r_vec) {
		if ((reterr) && *(reterr))
			;
		else unless ((_a) && (a_vec) && (prm_b) && (b_vec) && (prm_q) && (q_vec) &&
				(prm_r) && (r_vec)) {
			if (reterr)
				*(reterr) |= ae2f_errGlob_PTR_IS_NULL;
		} else {
			ae2f_MathIntDivU_t vi_divu;
			__ae2f_MathIntDivU_imp(vi_divu, _a, a_vec, prm_b, b_vec, prm_q, q_vec,
					prm_r, r_vec);
			(reterr) && vi_divu.m_reterr && (*(reterr) |= vi_divu.m_reterr);
		}
	}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathIntSel _ae2f_MathIntSel
#define __ae2f_MathIntSel_imp _ae2f_MathIntSel_imp
#define __ae2f_MathIntAbs _ae2f_MathIntAbs
#define __ae2f_MathIntAbs_imp _ae2f_MathIntAbs_imp
#else
#undef __ae2f_MathIntSel
#undef __ae2f_MathIntSel_imp
#undef __ae2f_MathIntAbs
#undef __ae2f_MathIntAbs_imp
#endif

typedef union ae2f_MathIntSet_t {
	ae2f_MathIntCast_t m_cast;
	ae2f_MathIntCmp_t m_cmp;
} ae2f_MathIntSel_t;


ae2f_MAC() _ae2f_MathIntSel_imp(ae2f_MathIntSel_t vi_sel, const ae2f_MathInt *const _ai,
		ae2f_iMathMem _ai_vec, const ae2f_MathInt *const _bi,
		ae2f_iMathMem _bi_vec, const ae2f_MathInt *const _oi,
		ae2f_oMathMem _oi_vec, signed selector) 
{
	__ae2f_MathIntCmp_imp(vi_sel.m_cmp, _ai, _ai_vec, _bi, _bi_vec);
	if (selector < 0 == vi_sel.m_cmp.m_out < 0) {
		__ae2f_MathIntCast_imp(vi_sel.m_cast, _ai, _ai_vec, _oi, _oi_vec);
	} else {
		__ae2f_MathIntCast_imp(vi_sel.m_cast, _bi, _bi_vec, _oi, _oi_vec);
	}
}


ae2f_MAC() _ae2f_MathIntSel(ae2f_MathMemOutErr err, const ae2f_MathInt *const _ai,
		ae2f_iMathMem _ai_vec, const ae2f_MathInt *const _bi,
		ae2f_iMathMem _bi_vec, const ae2f_MathInt *const _oi,
		ae2f_oMathMem _oi_vec, signed selector) 
{
	if ((err) && *(err))
		;
	else unless((_ai) && (_ai_vec) && (_bi) && (_bi_vec) && (_oi) && (_oi_vec));
	else 
	{
		ae2f_MathIntSel_t vi_sel;
		__ae2f_MathIntSel_imp(
				vi_sel
				, _ai
				, _ai_vec
				, _bi
				, _bi_vec
				, _oi
				, _oi_vec
				, selector
				);
	}
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathIntAbs  _ae2f_MathIntAbs
#define __ae2f_MathIntAbs_imp  _ae2f_MathIntAbs_imp
#define __ae2f_MathIntDiff  _ae2f_MathIntDiff
#define __ae2f_MathIntDiff_imp  _ae2f_MathIntDiff_imp
#endif

ae2f_structdef(union, ae2f_MathIntAbs_t) {
	ae2f_MathIntFlip_t m_flip;
	ae2f_MathIntCast_t m_cast;
};

ae2f_MAC() _ae2f_MathIntAbs_imp(
		ae2f_MathIntAbs_t vi_abs
		, const ae2f_MathInt *const prm_in
		, ae2f_iMathMem prm_in_vec
		, const ae2f_MathInt *const prm_out
		, ae2f_oMathMem prm_out_vec) 
{
	if (__ae2f_MathIntIsNegative(prm_in, prm_in_vec)) {
		__ae2f_MathIntFlip_imp(vi_abs.m_flip, prm_in, prm_in_vec, prm_out, prm_out_vec);
	} else {
		__ae2f_MathIntCast_imp(vi_abs.m_cast, prm_in, prm_in_vec, prm_out, prm_out_vec);
	}
}

ae2f_MAC() _ae2f_MathIntAbs(ae2f_MathMemOutErr err, const ae2f_MathInt *const prm_in,
		ae2f_iMathMem prm_in_vec,
		const ae2f_MathInt *const prm_out,
		ae2f_oMathMem prm_out_vec)
{
	if ((err) && *(err))
		;
	else unless((prm_in) && (prm_in_vec) && (prm_out) && (prm_out_vec))
		(err) && (*(err) |= ae2f_errGlob_PTR_IS_NULL);
	else {
		ae2f_MathIntAbs_t vi_abs;
		__ae2f_MathIntAbs_imp(vi_abs, prm_in, prm_in_vec, prm_out, prm_out_vec);
	}
}

ae2f_structdef(union, ae2f_MathIntDiff_t) {
	ae2f_MathIntCmp_t m_cmp;
	ae2f_MathIntSub_t m_sub;
};

ae2f_MAC() _ae2f_MathIntDiff_imp(
		ae2f_MathIntDiff_t vi_diff, const ae2f_pMathInt prm_a,
		ae2f_iMathMem prm_a_vec, const ae2f_MathInt *const prm_b,
		ae2f_iMathMem prm_b_vec, const ae2f_MathInt *const prm_o,
		ae2f_oMathMem prm_o_vec)
{
	__ae2f_MathIntCmp_imp(vi_diff.m_cmp, prm_a, prm_a_vec, prm_b, prm_b_vec);

	if (vi_diff.m_cmp.m_out < 0) {
		__ae2f_MathIntSub_imp(vi_diff.m_sub, prm_b, prm_b_vec
				, prm_a, prm_a_vec, prm_o
				, prm_o_vec
				);
	} else {
		__ae2f_MathIntSub_imp(vi_diff.m_sub, prm_a, prm_a_vec
				, prm_b, prm_b_vec, prm_o
				, prm_o_vec
				);
	}
}

ae2f_MAC() _ae2f_MathIntDiff(
		ae2f_MathMemOutErr err, const ae2f_MathInt *const prm_a,
		ae2f_iMathMem prm_a_vec, const ae2f_MathInt *const prm_b,
		ae2f_iMathMem prm_b_vec, const ae2f_MathInt *const prm_o,
		ae2f_oMathMem prm_o_vec) 
{
	if ((err) && *(err))
		;
	else unless((prm_a) && (prm_a_vec) && (prm_b) && (prm_b_vec) && (prm_o) && (prm_o_vec))
		(err) && (*(err) |= ae2f_errGlob_PTR_IS_NULL);
	else {
		ae2f_MathIntDiff_t vi_diff;
		__ae2f_MathIntDiff_imp(vi_diff, prm_a, prm_a_vec, prm_b, prm_b_vec, prm_o, prm_o_vec);
	}
}

#if __ae2f_MACRO_GENERATED
#undef __ae2f_MathIntBumpShifted
#undef __ae2f_MathIntBumpShifted_imp
#else
#define __ae2f_MathIntBumpShifted _ae2f_MathIntBumpShifted
#define __ae2f_MathIntBumpShifted_imp _ae2f_MathIntBumpShifted_imp
#endif

ae2f_structdef(union, ae2f_MathIntBumpShiftedStack_t) {
	ae2f_MathIntBumpO_t m_bump;
	size_t m_bitrref;
};

ae2f_structdef(struct, ae2f_MathIntBumpShifted_t) {
	ae2f_MathIntBumpShiftedStack_t m_stack;
	ae2f_MathInt m_ai_tmp;
};

ae2f_MAC() _ae2f_MathIntBumpShifted_imp(ae2f_MathIntBumpShifted_t vi_bumpsh, const ae2f_pMathInt _ai,
		ae2f_iMathMem _ai_vec, ae2f_oMathMem _oi_vec,
		unsigned char bump, size_t bitcount) 
{
	if (bitcount) {
		__ae2f_MathIntBitRRef_imp(vi_bumpsh.m_stack.m_bitrref, _ai, bitcount, &vi_bumpsh.m_ai_tmp);
		__ae2f_MathIntBumpO_imp(vi_bumpsh.m_stack.m_bump, bump, &vi_bumpsh.m_ai_tmp, _oi_vec, _oi_vec);

	} else {
		__ae2f_MathIntBumpO_imp(vi_bumpsh.m_stack.m_bump, bump, _ai, _oi_vec, _oi_vec);
	}
}

ae2f_MAC() _ae2f_MathIntBumpShifted(
		ae2f_MathMemOutErr err
		, const ae2f_pMathInt _ai
		, ae2f_iMathMem _ai_vec, ae2f_oMathMem _oi_vec
		, unsigned char bump, size_t bitcount)
{
	if((err) && *(err));
	else unless((_ai) && (_ai_vec) && (_oi_vec)) 
		(err) && (*(err) |= ae2f_errGlob_PTR_IS_NULL);
	else {
		ae2f_MathIntBumpShifted_t vi_bumpsh;
		__ae2f_MathIntBumpShifted_imp(vi_bumpsh, _ai, _ai_vec, _oi_vec, bump, bitcount);
	}
}

#endif
