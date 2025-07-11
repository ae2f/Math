#ifndef ae2f_Math_float_imp_h
#define ae2f_Math_float_imp_h

#include "ae2f/Cast.h"
#include "ae2f/Cmp.h"
#include "ae2f/Math/int.h"
#include <ae2f/Math/Util.auto.h>
#include <ae2f/Math/float.h>
#include <ae2f/Math/int.auto.h>

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
#define __ae2f_MathFloatMan_imp _ae2f_MathFloatMan_imp
#endif

ae2f_MAC() _ae2f_MathFloatMan_imp(const ae2f_pMathFloat af, ae2f_pMathInt oi) {
	(oi)->sign = 0;
	(oi)->vecbegpoint = (af)->bstart;
	(oi)->sz = (af)->man;
}

ae2f_MAC() _ae2f_MathFloatMan(ae2f_MathMemOutErr reterr,
		const ae2f_pMathFloat af, ae2f_pMathInt oi) {
	if ((reterr) && *(reterr))
		;
	else if (!((af) && (oi)))
		((reterr)) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL);
	else if (!(af->exp))
		((reterr)) && (*(reterr) |= ae2f_errGlob_IMP_NOT_FOUND);
	else {
		__ae2f_MathFloatMan_imp(af, oi);
	}
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathFloatExp _ae2f_MathFloatExp
#else
#undef __ae2f_MathFloatExp
#endif

ae2f_MAC() _ae2f_MathFloatExp(ae2f_MathMemOutErr reterr, const ae2f_pMathFloat af,
		ae2f_pMathInt oi, size_t *const retoivecidx) 
{
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
#define __ae2f_MathFloatGetExp_imp _ae2f_MathFloatGetExp_imp
#define __ae2f_MathFloatSetExp _ae2f_MathFloatSetExp
#define __ae2f_MathFloatSetExp_imp _ae2f_MathFloatSetExp_imp
#define __ae2f_MathFloatSetExpPtr _ae2f_MathFloatSetExpPtr
#define __ae2f_MathFloatSetExpPtr_imp _ae2f_MathFloatSetExpPtr_imp
#endif

ae2f_MAC() _ae2f_MathFloatGetExp_imp(
		size_t v_gexp
		, const ae2f_pMathFloat af, ae2f_iMathMem af_vec, ae2f_oMathMem o_vec
		) 
{
	__ae2f_MathUtilBVCpy_imp(
			v_gexp, o_vec, 0, af_vec, (af)->bstart + (af)->man
			, ae2f_CmpGetLs(sizeof(size_t) << 3, (af)->exp)
			);
}

ae2f_MAC() _ae2f_MathFloatGetExp(
		const ae2f_pMathFloat af, ae2f_iMathMem af_vec,
		ae2f_oMathMem o_vec
		) 
{
	if ((af) && (af_vec) && (o_vec)) {
		size_t v_gexp;
		__ae2f_MathFloatGetExp_imp(v_gexp, af, af_vec, o_vec);
	}
}

ae2f_MAC() _ae2f_MathFloatSetExpPtr_imp(
		size_t v_sexp
		, const ae2f_pMathFloat af, ae2f_oMathMem af_vec
		, ae2f_iMathMem i_vec
		)
{
	__ae2f_MathUtilBVCpy_imp(
			v_sexp, af_vec, (af)->bstart + (af)->man
			, i_vec, 0, ae2f_CmpGetLs(sizeof(size_t) << 3, (af)->exp)
			);
}

ae2f_MAC() _ae2f_MathFloatSetExpPtr(
		const ae2f_pMathFloat af, ae2f_oMathMem af_vec, ae2f_iMathMem i_vec
		) 
{
	if ((af) && (af_vec) && (i_vec)) {
		size_t v_sexp;
		__ae2f_MathFloatSetExpPtr_imp(v_sexp, af, af_vec, i_vec);
	}
}

ae2f_structdef(struct, ae2f_MathFloatSetExp_t) {
	ae2f_MathUtilIntPacker m_newexp, m_expptrstack;
};

ae2f_MAC() _ae2f_MathFloatSetExp_imp(
		ae2f_MathFloatSetExp_t vf_sexp
		, const ae2f_pMathFloat af, ae2f_oMathMem af_vec
		, const size_t newexp) 
{
	vf_sexp.m_newexp.m_u = newexp;
	__ae2f_MathFloatSetExpPtr_imp(
			vf_sexp.m_expptrstack.m_u
			, af, af_vec, vf_sexp.m_newexp.m_b
			);
}

ae2f_MAC() _ae2f_MathFloatSetExp(
		const ae2f_pMathFloat af, ae2f_oMathMem af_vec
		, const size_t newexp)
{
	if((af) && (af_vec)) {
		ae2f_MathFloatSetExp_t vf_sexp;
		__ae2f_MathFloatSetExp_imp(vf_sexp, af, af_vec, newexp);
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
ae2f_MAC() _ae2f_MathFloatNxt(
		ae2f_MathMemOutErr err, intptr_t idx,
		const ae2f_pMathFloat ifloat_t, ae2f_pMathFloat ofloat_t,
		size_t *const p_ofloatidx) 
{
	if (((err) && *(err)) || !(idx));
	else unless ((ifloat_t) && (ofloat_t) && (p_ofloatidx))
		(err) && ((*err) |= ae2f_errGlob_PTR_IS_NULL);
	else {
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
#define __ae2f_MathFloatCast_imp _ae2f_MathFloatCast_imp
#endif

ae2f_structdef(struct, ae2f_MathFloatCast_t) {
	size_t c1, c2;
	size_t odiv, idiv, idx;
	unsigned char sign : 1;
};

ae2f_MAC() _ae2f_MathFloatCast_imp(ae2f_MathFloatCast_t vf_cast, const ae2f_pMathFloat ifloat_t,
		ae2f_iMathMem ifloat, const ae2f_pMathFloat ofloat_t,
		ae2f_oMathMem ofloat) 
{
	vf_cast.sign =
		__ae2f_MathFloatGetSign(ifloat_t, ifloat); /* sign */
	__ae2f_MathFloatSetSign(ofloat_t, ofloat, vf_cast.sign);

	/* exp */
	vf_cast.idx = 0;
	vf_cast.c1 = (ifloat_t)->exp - 1;
	vf_cast.c2 = (ofloat_t)->exp - 1;

	vf_cast.idiv = (ifloat_t)->bstart + (ifloat_t)->man;
	vf_cast.odiv = (ofloat_t)->bstart + (ofloat_t)->man;

	for (; vf_cast.idx < vf_cast.c2;
			vf_cast.idx++) {
		if (vf_cast.idx < vf_cast.c1) {
			vf_cast.sign =
				(__ae2f_MathUtilBVGetArr((ifloat), vf_cast.idiv));
		}

		__ae2f_MathUtilBVSetAssignArr((ofloat), vf_cast.odiv,
				vf_cast.sign);
		vf_cast.idiv++;
		vf_cast.odiv++;
	}

	vf_cast.odiv &= ~0b111;
	vf_cast.odiv |=
		__ae2f_MathFloatExpGetSign(ifloat_t, ifloat);

	__ae2f_MathFloatExpSetSign(ofloat_t, ofloat,
			vf_cast.odiv & 7); /* fraction */

	vf_cast.idx = 0;
	vf_cast.c1 = vf_cast.idiv =
		(ifloat_t)->man - 1;
	vf_cast.c2 = vf_cast.odiv =
		(ofloat_t)->man - 1;

	vf_cast.idiv += (ifloat_t)->bstart;
	vf_cast.odiv += (ofloat_t)->bstart;

	for (; vf_cast.idx < vf_cast.c2;
			vf_cast.idx++) {
		if (vf_cast.idiv != (ifloat_t)->bstart - 1) {
			__ae2f_MathUtilBVSetAssignArr(
					(ofloat), vf_cast.odiv,
					(__ae2f_MathUtilBVGetArr((ifloat), vf_cast.idiv)));
			vf_cast.idiv--;
		} else {
			__ae2f_MathUtilBVSetAssignArr((ofloat), vf_cast.odiv,
					0);
		}
		vf_cast.odiv--;
	}

}

/**
 * @def __ae2f_MathFloatCast
 * @brief `ofloat` = `ifloat`;
 * */
ae2f_MAC() _ae2f_MathFloatCast(ae2f_MathMemOutErr err, const ae2f_pMathFloat ifloat_t,
		ae2f_iMathMem ifloat, const ae2f_pMathFloat ofloat_t,
		ae2f_oMathMem ofloat) 
{
	if ((err) && *(err))
		;
	else if (!((ifloat_t) && (ifloat) && (ofloat_t) && (ofloat)))
		(err) && (*(err) = ae2f_errGlob_PTR_IS_NULL);
	else {
		ae2f_MathFloatCast_t vf_cast;
		__ae2f_MathFloatCast_imp(vf_cast, ifloat_t, ifloat, ofloat_t, ofloat);
	}
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathFloatFlip _ae2f_MathFloatFlip
#define __ae2f_MathFloatFlip_imp _ae2f_MathFloatFlip_imp
#else
#undef __ae2f_MathFloatFlip
#endif

typedef ae2f_MathFloatCast_t ae2f_MathFloatFlip_t;

ae2f_MAC() _ae2f_MathFloatFlip_imp(
		ae2f_MathFloatCast_t vf_flip, const ae2f_pMathFloat _if,
		ae2f_iMathMem _if_vec, const ae2f_pMathFloat _of,
		ae2f_oMathMem _of_vec)
{
	__ae2f_MathFloatFlip_imp(vf_flip, _if, _if_vec, _of, _of_vec);
	__ae2f_MathFloatFlipSign(_of, _of_vec);
}

/**
 * @def __ae2f_MathFloatCast
 * @brief `ofloat` = -`ifloat`;
 * */
ae2f_MAC() _ae2f_MathFloatFlip(ae2f_MathMemOutErr err, const ae2f_pMathFloat _if,
		ae2f_iMathMem _if_vec, const ae2f_pMathFloat _of,
		ae2f_oMathMem _of_vec) {
	__ae2f_MathFloatCast(err, _if, _if_vec, _of, _of_vec);
	unless(err && *(err)) __ae2f_MathFloatFlipSign(_of, _of_vec);
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathFloatMkWhich _ae2f_MathFloatMkWhich
#define __ae2f_MathFloatMkWhich_imp _ae2f_MathFloatMkWhich_imp
#else
#undef __ae2f_MathFloatMkWhich
#endif

ae2f_structdef(struct, ae2f_MathFloatWhichFlag_t) {
	/** First seen flagbit */
	unsigned char m_expfirst : 1;
	unsigned char m_manfirst : 1;

	/** Is changed from first bit */
	unsigned char m_expch : 1;
	unsigned char m_manch : 1;

	unsigned char m_sign : 1;
};

ae2f_structdef(union, ae2f_MathFloatWhichBuilder_t) {
	ae2f_MathFloatWhichFlag_t m_flag;
	unsigned char m_u : 5;
};

ae2f_structdef(union, ae2f_MathFloatMkWhichStack_t) {
	size_t m_sz;
};

ae2f_structdef(struct, ae2f_MathFloatMkWhich_t) {
	ae2f_MathFloatWhichBuilder_t m_which;
	ae2f_MathFloatMkWhichStack_t m_stack;
};

ae2f_structdef_v(enum, ae2f_eMathFloatWhich, ae2f_eMathFloatWhich) {
	ae2f_eMathFloatWhich_NAN_0 = 0b0011
		, ae2f_eMathFloatWhich_NAN_1 = 0b1011
		, ae2f_eMathFloatWhich_INF = 0b0001
		, ae2f_eMathFloatWhich_NIL = 0b0000
		, ae2f_eMathFloatWhich_ONE = 0b1100
};

ae2f_MAC() _ae2f_MathFloatMkWhich_imp(
		ae2f_MathFloatMkWhich_t vf_mkwhich
		, const ae2f_pMathFloat _of
		, ae2f_oMathMem _of_vec
		, const unsigned char which) 
{
	vf_mkwhich.m_which.m_u = which;

	__ae2f_MathFloatSetSign(_of, _of_vec, vf_mkwhich.m_which.m_flag.m_sign);

	__ae2f_MathUtilBVSetAssignArrRanged_imp(
			vf_mkwhich.m_stack.m_sz
			, _of_vec, (_of)->bstart
			, (_of)->bstart + (_of)->man
			, vf_mkwhich.m_which.m_flag.m_manfirst ^ (vf_mkwhich.m_which.m_flag.m_manch && vf_mkwhich.m_stack.m_sz)
			);

	__ae2f_MathUtilBVSetAssignArrRanged_imp(
			vf_mkwhich.m_stack.m_sz
			, _of_vec
			, vf_mkwhich.m_stack.m_sz
			, (_of)->bstart + (_of)->man + (_of)->exp
			, vf_mkwhich.m_which.m_flag.m_expfirst ^ (vf_mkwhich.m_which.m_flag.m_expch && vf_mkwhich.m_stack.m_sz)
			);
}

/**
 * @def __ae2f_MathFloatMkWhich
 * @brief
 * */
ae2f_MAC() _ae2f_MathFloatMkWhich(ae2f_MathMemOutErr err, const ae2f_pMathFloat _of,
		ae2f_oMathMem _of_vec,
		const unsigned char which) {
	if ((err) && *(err))
		;
	else unless ((_of) && (_of_vec))
		(err) && (*(err) = ae2f_errGlob_PTR_IS_NULL);
	else {
		ae2f_MathFloatMkWhich_t vf_which;
		__ae2f_MathFloatMkWhich_imp(
				vf_which
				, _of
				, _of_vec
				, which
				);
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
#define __ae2f_MathFloatGetWhich_imp _ae2f_MathFloatGetWhich_imp
#else
#undef __ae2f_MathFloatGetWhich
#endif

ae2f_structdef(struct, ae2f_MathFloatGetWhich_t) {
	size_t i;
	size_t vec;

	/** @brief ret */
	ae2f_MathFloatWhichBuilder_t m_build;
};



ae2f_MAC() _ae2f_MathFloatGetWhich_imp(
		ae2f_MathFloatGetWhich_t vf_which
		, const ae2f_pMathFloat _af, ae2f_iMathMem _af_vec
		)
{
	vf_which.m_build.m_flag.m_manfirst = __ae2f_MathUtilBVGetArr(_af_vec, (_af)->bstart);
	vf_which.m_build.m_flag.m_expfirst = __ae2f_MathUtilBVGetArr(_af_vec, (_af)->bstart + (_af)->exp);

	vf_which.m_build.m_flag.m_expch = 0;
	vf_which.m_build.m_flag.m_manch = 0;

	vf_which.m_build.m_flag.m_sign = 0;

	for (
			vf_which.i = 0;
			vf_which.i < (_af)->exp && !vf_which.m_build.m_flag.m_expch;
			vf_which.i++
	    )
	{
		vf_which.vec = (_af)->bstart + (_af)->man + vf_which.i;
		vf_which.m_build.m_flag.m_expch 
			= vf_which.m_build.m_flag.m_expfirst ^ __ae2f_MathUtilBVGetArr(_af_vec, vf_which.vec);
	}

	for (
			vf_which.i = 0;
			vf_which.i < (_af)->man && !vf_which.m_build.m_flag.m_manch;
			vf_which.i++
	    )
	{
		vf_which.vec = (_af)->bstart + vf_which.i;
		vf_which.m_build.m_flag.m_manch 
			= vf_which.m_build.m_flag.m_manfirst ^ __ae2f_MathUtilBVGetArr(_af_vec, vf_which.vec);
	}
}

/**
 * @def __ae2f_MathFloatGetWhich
 * */
ae2f_MAC() _ae2f_MathFloatGetWhich(ae2f_MathMemOutErr err, const ae2f_pMathFloat _af,
		ae2f_iMathMem _af_vec,
		unsigned char *const retwhich) {
	if ((err) && *(err))
		;
	else unless((_af) && (_af_vec) && (retwhich))
		(err) && (*(err) = ae2f_errGlob_PTR_IS_NULL);
	else {
		ae2f_MathFloatGetWhich_t vf_which;
		__ae2f_MathFloatGetWhich_imp(vf_which, _af, _af_vec);
		*retwhich = vf_which.m_build.m_u;
	}
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathFloatNormalise _ae2f_MathFloatNormalise
#define __ae2f_MathFloatNormalise_imp _ae2f_MathFloatNormalise_imp
#else
#undef __ae2f_MathFloatNormalise
#endif

ae2f_structdef(union, ae2f_MathFloatStack_t) {
	ae2f_MathFloatGetWhich_t m_gwhich;
	ae2f_MathFloatMkWhich_t m_mkwhich;
	ae2f_MathFloatCast_t m_cast;
};

ae2f_structdef(struct, ae2f_MathFloatNormalise_t) {
	size_t i, shift;
	size_t div, src_div, dst_div, exp_div;
	ae2f_MathFloatStack_t m_stack;
};

#include <stdio.h>

ae2f_MAC() _ae2f_MathFloatNormalise_imp(
		ae2f_MathFloatNormalise_t vf_norm
		, const ae2f_pMathFloat _if, ae2f_iMathMem _if_vec
		, ae2f_oMathMem _of_vec)
{
	vf_norm = ae2f_RecordMk(ae2f_MathFloatNormalise_t, 0, );

	__ae2f_MathFloatGetWhich_imp(
			vf_norm.m_stack.m_gwhich
			, _if, _if_vec
			);

	__ae2f_MathFloatCast_imp(
			vf_norm.m_stack.m_cast
			, _if, _if_vec
			, _if, _of_vec
			);

	switch(vf_norm.m_stack.m_gwhich.m_build.m_u & 0b1111)
	{
		case ae2f_eMathFloatWhich_NAN_0:
		case ae2f_eMathFloatWhich_NAN_1:
		case ae2f_eMathFloatWhich_NIL:
		case ae2f_eMathFloatWhich_INF:
			break;

		default: 
			{
				vf_norm.shift = 0;
				vf_norm.div = (_if)->bstart;
				/* Search for the first 1 bit in the mantissa */
				for (
						vf_norm.i = 0; 
						vf_norm.i < (_if)->man && !__ae2f_MathUtilBVGetArr((_if_vec), vf_norm.div);
						vf_norm.i++, vf_norm.div++) {
					vf_norm.shift++;
				} /* If no 1 bit found, the number is zero */

				if (vf_norm.shift == (_if)->man) {
					__ae2f_MathFloatMkWhich_imp(
							vf_norm.m_stack.m_mkwhich
							, _if, _of_vec
							, ae2f_eMathFloatWhich_NIL
							);
				} else  {
					/* Shift the mantissa left by 'shift' positions */
					if (vf_norm.shift > 0) { /* Shift the mantissa */
						for (vf_norm.i = 0; vf_norm.i < (_if)->man - vf_norm.shift;
								vf_norm.i++) {
							vf_norm.src_div = (_if)->bstart + vf_norm.i + vf_norm.shift;
							vf_norm.dst_div = (_if)->bstart + vf_norm.i;

							__ae2f_MathUtilBVSetAssignArr(
									(_of_vec), vf_norm.dst_div,
									__ae2f_MathUtilBVGetArr((_if_vec), vf_norm.src_div));
						}

						/* Clear the remaining bits */
						for (vf_norm.i = (_if)->man - vf_norm.shift; vf_norm.i < (_if)->man;
								vf_norm.i++) {
							vf_norm.div = (_if)->bstart + vf_norm.i;
							__ae2f_MathUtilBVSetAssignArr((_of_vec), vf_norm.div, 0);
						}

						/* Adjust the exponent */
						vf_norm.exp_div = (_if)->bstart + (_if)->man;

						/* Subtract shift from exponent */
						for (vf_norm.i = 0; vf_norm.i < (_if)->exp - 1;
								vf_norm.i++, vf_norm.exp_div++) {
							if (vf_norm.shift > 0 && __ae2f_MathUtilBVGetArr((_if_vec), vf_norm.exp_div)) {
								__ae2f_MathUtilBVSetAssignArr((_of_vec), vf_norm.exp_div, 0);
								vf_norm.shift--;
							}
						}
					}
				}
			}
	}
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
ae2f_MAC() _ae2f_MathFloatNormalise(ae2f_MathMemOutErr err, const ae2f_pMathFloat _if,
		ae2f_bMathMem _if_vec) {
	if ((err) && *(err));
	else unless ((_if) && (_if_vec))
		(err) && ((*err) = ae2f_errGlob_PTR_IS_NULL);
	else {
		ae2f_MathFloatNormalise_t vf_norm;
		__ae2f_MathFloatNormalise_imp(
				vf_norm
				, _if, _if_vec, _if_vec
				);
	}
}

#if __ae2f_MACRO_GENERATED
#undef __ae2f_MathFloatCmp
#else
#define __ae2f_MathFloatCmp _ae2f_MathFloatCmp
#define __ae2f_MathFloatCmp_imp _ae2f_MathFloatCmp_imp
#endif

ae2f_structdef(struct, ae2f_MathFloatCmpSignMatch_t) {
	size_t m_i, m_c;
	unsigned char m_sign : 1;
	unsigned char m_av : 1;
	unsigned char m_bv : 1;

	/** @brief return value */
	ae2f_CmpFunRet_t m_ret : 5;
};

ae2f_structdef(union, ae2f_MathFloatCmpStack_t) {
	size_t m_gexp;
	ae2f_MathFloatCmpSignMatch_t m_smatch;
};

ae2f_structdef(struct, ae2f_MathFloatCmp_t) {
	ae2f_MathUtilIntPacker m_exp[2];
	ae2f_MathFloatCmpStack_t m_stack;
};

ae2f_MAC() _ae2f_MathFloatCmp_imp(
		ae2f_MathFloatCmp_t v_cmp
		, const ae2f_MathFloat *const _af, ae2f_iMathMem _af_vec
		, const ae2f_pMathFloat _bf, ae2f_iMathMem _bf_vec
		)
{
	if ((v_cmp.m_stack.m_smatch.m_sign = __ae2f_MathFloatGetSign(_af, _af_vec)) !=
			__ae2f_MathFloatGetSign(_bf, _bf_vec)) {
		v_cmp.m_stack.m_smatch.m_ret = v_cmp.m_stack.m_smatch.m_sign 
			? ae2f_CmpFunRet_LISLESSER : ae2f_CmpFunRet_RISLESSER;
	} else {
		__ae2f_MathFloatGetExp_imp(
				v_cmp.m_stack.m_gexp
				, _af, _af_vec
				, v_cmp.m_exp[0].m_b
				);

		__ae2f_MathFloatGetExp_imp(
				v_cmp.m_stack.m_gexp
				, _bf, _bf_vec
				, v_cmp.m_exp[1].m_b
				);

		/** unbias */
		v_cmp.m_exp[0].m_i -= __ae2f_MathFloatBias(_af);
		v_cmp.m_exp[1].m_i -= __ae2f_MathFloatBias(_bf);
		/** getting exponents */

		if (v_cmp.m_exp[0].m_i != v_cmp.m_exp[1].m_i) {
			v_cmp.m_stack.m_smatch.m_ret = 
				v_cmp.m_exp[0].m_i < v_cmp.m_exp[1].m_i
				? ae2f_CmpFunRet_LISLESSER
				: ae2f_CmpFunRet_RISLESSER;
		} else {
			/**
			 * hope exponents are same but bitsize of mantissa could be various.
			 * From very left side to 0.
			 * */

			v_cmp.m_exp[0].m_u = (_af)->man;
			v_cmp.m_exp[1].m_u = (_bf)->man;

			v_cmp.m_stack.m_smatch.m_i = 0;
			v_cmp.m_stack.m_smatch.m_c = ae2f_CmpGetGt(v_cmp.m_exp[0].m_u, v_cmp.m_exp[1].m_u);

			v_cmp.m_stack.m_smatch.m_ret = ae2f_CmpFunRet_EQUAL;

			v_cmp.m_stack.m_smatch.m_av = 1;
			v_cmp.m_stack.m_smatch.m_bv = 1;

			/** Reversly iterating. */
			for (; 
					v_cmp.m_stack.m_smatch.m_i < v_cmp.m_stack.m_smatch.m_c 
					&& 	v_cmp.m_stack.m_smatch.m_av == v_cmp.m_stack.m_smatch.m_bv; 
					v_cmp.m_stack.m_smatch.m_i++) 
			{
				v_cmp.m_stack.m_smatch.m_av = v_cmp.m_stack.m_smatch.m_i < v_cmp.m_exp[0].m_u
					? __ae2f_MathUtilBVGetArr(
							_af_vec, (_af)->bstart + v_cmp.m_exp[0].m_u -
							1 - v_cmp.m_stack.m_smatch.m_i)
					: 0;

				v_cmp.m_stack.m_smatch.m_bv = v_cmp.m_stack.m_smatch.m_i < v_cmp.m_exp[1].m_u
					? __ae2f_MathUtilBVGetArr(
							_bf_vec, (_bf)->bstart + v_cmp.m_exp[1].m_u -
							1 - v_cmp.m_stack.m_smatch.m_i)
					: 0;
			}

			v_cmp.m_stack.m_smatch.m_ret = (v_cmp.m_stack.m_smatch.m_i < v_cmp.m_stack.m_smatch.m_c);
			v_cmp.m_stack.m_smatch.m_sign ^= !!v_cmp.m_stack.m_smatch.m_bv;
		}; /** for jump */

		/** flip when sign is on */
		v_cmp.m_stack.m_smatch.m_ret = 
			(v_cmp.m_stack.m_smatch.m_ret 
			^ ((v_cmp.m_stack.m_smatch.m_sign) << 5) - v_cmp.m_stack.m_smatch.m_sign)
			+ v_cmp.m_stack.m_smatch.m_sign
			;
	}
}

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
ae2f_MAC() _ae2f_MathFloatCmp(ae2f_MathMemOutErr err, const ae2f_MathFloat *const _af,
		ae2f_iMathMem _af_vec, const ae2f_pMathFloat _bf,
		ae2f_iMathMem _bf_vec, ae2f_CmpFunRet_t *const ret) {
	if ((err) && *(err))
		;
	else unless ((_af) && (_af_vec) && (_bf) && (_bf_vec) && (ret))
		(err) && (*(err) |= ae2f_errGlob_PTR_IS_NULL);
	else if ((_af)->exp > sizeof(size_t) << 3 || (_bf)->exp > sizeof(size_t) << 3)
		(err) && (*(err) |= ae2f_errGlob_IMP_NOT_FOUND);
	else {
		ae2f_MathFloatCmp_t v_cmp = ae2f_RecordMk(ae2f_MathFloatCmp_t, 0, );
		__ae2f_MathFloatCmp_imp(v_cmp, _af, _af_vec, _bf, _bf_vec);
		*(ret) = v_cmp.m_stack.m_smatch.m_ret;
	}
}

#if !__ae2f_MACRO_GENERATED
#define __ae2f_MathFloatAddU _ae2f_MathFloatAddU
#define __ae2f_MathFloatAddU_imp _ae2f_MathFloatAddU_imp
#define __ae2f_MathFloatAdd _ae2f_MathFloatAdd
#define __ae2f_MathFloatSubU _ae2f_MathFloatSubU
#define __ae2f_MathFloatSub _ae2f_MathFloatSub
#endif

/** @TODO remove this later. */
#include <stdio.h>

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
 * `_of` = `_af` - `_bf`;
 * */
ae2f_MAC() _ae2f_MathFloatSubU(ae2f_err_t *const err, const ae2f_MathFloat *const _af,
		ae2f_iMathMem _af_vec, const ae2f_MathFloat *const _bf,
		ae2f_iMathMem _bf_vec, ae2f_MathFloat *const _of,
		ae2f_oMathMem _of_vec) {
	if ((err) && *(err))
		;
	else unless ((_af) && (_af_vec) && (_bf) && (_bf_vec) && (_of) && (_of_vec))
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
					__ae2f_MathFloatBias(_of) -
					(v_addu.m_expint[0].m_i == v_addu.m_expint[1].m_i);

				__ae2f_MathFloatSetExpPtr(_of, _of_vec, v_addu.m_expint[3].m_b);

				if (v_addu.m_expint[0].m_i < v_addu.m_expint[1].m_i) {
					*(err) |= ae2f_errGlob_WRONG_OPERATION | ae2f_errGlob_IMP_NOT_FOUND;
					break;
				}

				v_addu.m_expint[3].m_i = v_addu.m_expint[0].m_i;

				/**
				 * Now two of them represents the bitcount to be shifted. \n
				 * They are guaranteed to be positive value.
				 * */
				v_addu.m_expint[0].m_i = v_addu.m_expint[3].m_i -
					v_addu.m_expint[0].m_i; /* this must be 0. */

				/* this must be a bit count */
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
					/** two are zero : means leading ones are being descended */

					puts("Two are same");

					if (0) {
						v_addu.m_expint[0].m_i--;
						v_addu.m_expint[1].m_i--;
					}
				}

				{
					if (v_addu.m_expint[1].m_i) {
						puts("Two are not same");
						__ae2f_MathUtilBVSetAssignArrRanged(
								_of_vec, (_of)->bstart + (_of)->man - v_addu.m_expint[1].m_i,
								(_of)->bstart + (_of)->man + 1,
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
				__ae2f_MathIntSub(
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

ae2f_structdef(union, ae2f_MathFloatAddUStack_t) {
	size_t m_sz;
	ae2f_MathIntAdd_t m_iadd;
};


ae2f_structdef(struct, ae2f_MathFloatAddU_t) {
	ae2f_MathFloatAddUStack_t m_stack;

	ae2f_MathUtilIntPacker
		/**
		 * @brief
		 * Exponent index and after that: just exponent
		 *
		 * @details
		 * after index 3 could be temporary
		 * */
		m_expint[6]
		/** to store each size of mantissas */
		,m_mansz[3];

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
};

ae2f_MAC() _ae2f_MathFloatAddU_imp(
		ae2f_MathFloatAddU_t v_addu
		, const ae2f_pMathFloat _af, ae2f_iMathMem _af_vec
		, const ae2f_pMathFloat _bf, ae2f_iMathMem _bf_vec
		, ae2f_pMathFloat _of, ae2f_oMathMem _of_vec
		) {
	/** Get mantissas and exponents */
	v_addu.m_expint[0].m_u = __ae2f_MathFloatExpEndIdx(_af);
	v_addu.m_expint[1].m_u = __ae2f_MathFloatExpEndIdx(_bf);
	v_addu.m_expint[2].m_u = __ae2f_MathFloatExpEndIdx(_of);

	__ae2f_MathFloatMan_imp(_af, &v_addu.m_exp_man[0]);
	__ae2f_MathFloatMan_imp(_bf, &v_addu.m_exp_man[1]);
	__ae2f_MathFloatMan_imp(_of, &v_addu.m_exp_man[2]);


	/**
	 * Getting the difference of size as unsigned positive value.
	 * Will be used for bit-shifting
	 *
	 * Perhaps the shift for it is needed for output buffer.
	 *
	 * Provided it goes positive, value should be traunacted.
	 * Provided it goes negative, value should be left-shifted.
	 * */
	v_addu.m_mansz[0].m_u = v_addu.m_exp_man[0].sz;
	v_addu.m_mansz[1].m_u = v_addu.m_exp_man[1].sz;

	v_addu.m_mansz[0].m_u -= v_addu.m_exp_man[2].sz;
	v_addu.m_mansz[1].m_u -= v_addu.m_exp_man[2].sz;


	/** Get and Unbias exponent */
	__ae2f_MathFloatGetExp_imp(
			v_addu.m_stack.m_sz
			, _af, _af_vec, v_addu.m_expint[0].m_b
			);
	__ae2f_MathFloatGetExp_imp(
			v_addu.m_stack.m_sz
			, _bf, _bf_vec, v_addu.m_expint[1].m_b
			);

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

	__ae2f_MathFloatSetExpPtr_imp(
			v_addu.m_stack.m_sz
			,  _of, _of_vec
			, v_addu.m_expint[3].m_b
			);

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

	/** Fill with zero */
	__ae2f_MathIntFill_imp(v_addu.m_stack.m_sz, &v_addu.m_exp_man[2], (_of_vec), 0, 1);

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

	__ae2f_MathIntBitRRef_imp(v_addu.m_expint[3].m_u, &v_addu.m_exp_man[0]
			, v_addu.m_expint[0].m_u, &v_addu.m_exp_man[0]
			);


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

		__ae2f_MathIntBitRRef_imp(v_addu.m_expint[4].m_u, &v_addu.m_exp_man[1]
				, v_addu.m_expint[1].m_i, &v_addu.m_exp_man[1]);
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


	__ae2f_MathIntBitRRef_imp(v_addu.m_stack.m_sz, &v_addu.m_exp_man[0]
			, v_addu.m_expint[5].m_u, &v_addu.m_exp_man[0]);
	v_addu.m_expint[3].m_u += v_addu.m_stack.m_sz;

	__ae2f_MathIntBitRRef_imp(v_addu.m_stack.m_sz, &v_addu.m_exp_man[1]
			, v_addu.m_expint[5].m_u, &v_addu.m_exp_man[1]);
	v_addu.m_expint[4].m_u +=  v_addu.m_stack.m_sz;


	__ae2f_MathIntBitRRef_imp(v_addu.m_expint[5].m_u, &v_addu.m_exp_man[2]
			, v_addu.m_expint[5].m_u, &v_addu.m_exp_man[2]);


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
	if (v_addu.m_mansz[0].m_i < 0 || v_addu.m_mansz[1].m_i < 0) {
		/**
		 * need to store the mantissa index somewhere
		 * expint[0] will store it.
		 * */
		v_addu.m_exp_man[3] = v_addu.m_exp_man[2];
		v_addu.m_mansz[2].m_u = v_addu.m_expint[5].m_u;
	}

	if (v_addu.m_mansz[0].m_i < 0) {
		__ae2f_MathIntBitRRef_imp(v_addu.m_stack.m_sz, &v_addu.m_exp_man[3]
				, v_addu.m_mansz[0].m_i, &v_addu.m_exp_man[2]);
		v_addu.m_expint[5].m_u += v_addu.m_stack.m_sz;
	}

	/** O = A + O */
	__ae2f_MathIntAdd_imp(
			v_addu.m_stack.m_iadd, &v_addu.m_exp_man[0], (_af_vec) + v_addu.m_expint[3].m_u,
			&v_addu.m_exp_man[2], v_addu.m_expint[5].m_u + (_of_vec),
			&v_addu.m_exp_man[2], v_addu.m_expint[5].m_u + (_of_vec));

	if (v_addu.m_mansz[1].m_i < 0) {
		__ae2f_MathIntBitRRef_imp(v_addu.m_stack.m_sz, &v_addu.m_exp_man[3],
				-v_addu.m_mansz[1].m_i, &v_addu.m_exp_man[2]);
		v_addu.m_expint[5].m_u += v_addu.m_stack.m_sz;

	} else if (v_addu.m_mansz[0].m_i < 0) {
		/** Original */
		v_addu.m_exp_man[2] = v_addu.m_exp_man[3];
		v_addu.m_expint[5].m_u = v_addu.m_mansz[2].m_u;
	}

	/** O = O + B */
	__ae2f_MathIntAdd_imp(
			v_addu.m_stack.m_iadd, &v_addu.m_exp_man[1], (_bf_vec) + v_addu.m_expint[4].m_u,
			&v_addu.m_exp_man[2], v_addu.m_expint[5].m_u + (_of_vec),
			&v_addu.m_exp_man[2], v_addu.m_expint[5].m_u + (_of_vec));
}

/**
 * @TODO
 * When unbias exponent is under zero, it will throw exception.
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
ae2f_MAC() _ae2f_MathFloatAddU(
		ae2f_err_t *const err, const ae2f_MathFloat *const _af,
		ae2f_iMathMem _af_vec, const ae2f_MathFloat *const _bf,
		ae2f_iMathMem _bf_vec, ae2f_MathFloat *const _of,
		ae2f_oMathMem _of_vec) {
	if ((err) && *(err))
		;
	else unless ((_af) && (_af_vec) && (_bf) && (_bf_vec) && (_of) && (_of_vec))
		(err) && (*(err) |= ae2f_errGlob_PTR_IS_NULL);
	else if ((_af)->exp > sizeof(size_t) << 3 || (_bf)->exp > sizeof(size_t) << 3)
		(err) && (*(err) |= ae2f_errGlob_IMP_NOT_FOUND);
	else {
		ae2f_MathFloatAddU_t v_addu;
		__ae2f_MathFloatAddU_imp(
				v_addu
				, _af, _af_vec
				, _bf, _bf_vec
				, _of, _of_vec
				);
	};
}

#endif
