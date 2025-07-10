#ifndef ae2f_Math_Util_h
#define ae2f_Math_Util_h

#include <ae2f/BitVec.h>

/** @brief
 * `b._0` = `a` & 1;	[1nd bit] \n
 * `b._1` = `a` >> 1;	[2nd bit]
 *
 * `__VA_ARGS__` (aka ...) will be stacked after _1. \n
 * `c` stands for custom, which could handle other bits.
 *
 * @param c_sz bit size of `c`
 * */
#define __ae2f_MathUtilFlag2(c_sz, ...)                                        \
  union __ae2f_MathUtilFlag2__##c_sz {                                         \
    unsigned char a : 2;                                                       \
    struct __ae2f_MathUtilFlag2__##c_sz##__C {                                 \
      unsigned char a : 2;                                                     \
      unsigned char c : c_sz;                                                  \
    } c;                                                                       \
    struct __ae2f_MathUtilFlag2__##c_sz##__packer {                            \
      unsigned char _0 : 1;                                                    \
      unsigned char _1 : 1;                                                    \
      __VA_ARGS__                                                              \
    } b;                                                                       \
  }

/** @brief
 * `b._0` = `a` & 1;	[1nd bit] \n
 * `b._1` = `a` >> 1;	[2nd bit]
 * */
typedef __ae2f_MathUtilFlag2(2) ae2f_MathUtilFlag2;

#define __ae2f_MathUtilBVGetRanged(vec, istart, iend)                          \
  _ae2f_BitVecGetRanged((vec), (istart), (iend), unsigned char)

#define __ae2f_MathUtilBVGet(vec, i)                                           \
  __ae2f_MathUtilBVGetRanged((vec), (i), ((i) + 1))

#define __ae2f_MathUtilBVGetArr(vecarr, i)                                     \
  __ae2f_MathUtilBVGet((vecarr)[(i) >> 3], (i) & 7)

#define __ae2f_MathUtilBVSetRanged(vec, istart, iend, val)                     \
  _ae2f_BitVecSetRanged((vec), (istart), (iend), (val), unsigned char)

#define __ae2f_MathUtilBVSet(vec, i, val)                                      \
  __ae2f_MathUtilBVSetRanged(vec, (i), (i) + 1, (val))

#define __ae2f_MathUtilBVSetAssign(vec, i, val)                                \
  ((vec) = (__ae2f_MathUtilBVSet((vec), (i), (val))))

#define __ae2f_MathUtilBVSetAssignO(ivec, ovec, i, val)                        \
  ((ovec) = (__ae2f_MathUtilBVSet((ivec), (i), (val))))

#define __ae2f_MathUtilBVSetAssignArr(vecarr, i, val)                          \
  __ae2f_MathUtilBVSetAssign((vecarr)[(i) >> 3], ((i) & 7), (val))

#define __ae2f_MathUtilBVSetAssignArrO(ivecarr, ovecarr, i, val)               \
  __ae2f_MathUtilBVSetAssignO((ivecarr)[(i) >> 3], (ovecarr)[(i) >> 3],        \
                              ((i) & 7), (val))

#define __ae2f_MathUtilDiff(a, b) ((a) > (b) ? (a) - (b) : (b) - (a))

#include <ae2f/Macro.h>

#if __ae2f_MACRO_GENERATED
#undef __ae2f_MathUtilBVSetAssignArrRanged_imp
#undef __ae2f_MathUtilBVCpy_imp

#else

#define __ae2f_MathUtilBVSetAssignArrRanged_imp                                \
  _ae2f_MathUtilBVSetAssignArrRanged_imp
#define __ae2f_MathUtilBVCpy_imp _ae2f_MathUtilBVCpy_imp
#define GetFunc __ae2f_MathUtilBVGet
#endif

ae2f_MAC(GetFunc, )
    _ae2f_MathUtilBVMask_imp(size_t v, unsigned char *const ovec,
                             const size_t b, const size_t e,
                             const unsigned mask, const unsigned char masklen) {
  for ((v) = (b); (v) < (e); (v)++) {
    __ae2f_MathUtilBVSetAssignArr(ovec, v,
                                  GetFunc(mask, ((v) - (b)) % (masklen)));
  }
}

#define __ae2f_MathUtilBVMask(ovec, b, e, mask, masklen)                       \
  if ((b) < (e)) {                                                             \
    size_t v;                                                                  \
    __ae2f_MathUtilBVMask_imp(__ae2f_MathUtilBVGet, v, ovec, b, e, mask,       \
                              masklen);                                        \
  }

#define __ae2f_MathUtilBVMaskArr(ovec, b, e, mask, masklen)                    \
  if ((b) < (e)) {                                                             \
    size_t v;                                                                  \
    __ae2f_MathUtilBVMask_imp(__ae2f_MathUtilBVGetArr, v, ovec, b, e, mask,    \
                              masklen);                                        \
  }

ae2f_MAC()
    _ae2f_MathUtilBVSetAssignArrRanged_imp(size_t v,
                                           unsigned char *const vecarr,
                                           const size_t b, const size_t e,
                                           const unsigned val) {
  for (v = (b); v < (e); v++) {
    __ae2f_MathUtilBVSetAssignArr(vecarr, v, val);
  }
}

#define __ae2f_MathUtilBVSetAssignArrRanged(vecarr, b, e, val)                 \
  if ((b) < (e)) {                                                             \
    size_t v;                                                                  \
    __ae2f_MathUtilBVSetAssignArrRanged_imp(v, vecarr, b, e, val);             \
  }

ae2f_MAC() _ae2f_MathUtilBVCpy_imp(size_t v_cpy, unsigned char *const ov,
                                   const size_t ovi, char *const iv,
                                   const size_t ivi, const size_t len) {
  v_cpy = 0;
  while (v_cpy < (len)) {
    __ae2f_MathUtilBVSetAssignArr(ov, (ovi) + (v_cpy),
                                  __ae2f_MathUtilBVGetArr(iv, (ivi) + (v_cpy)));
    v_cpy++;
  }
}

#define __ae2f_MathUtilBVCpy(ov, ovi, iv, ivi, len)                            \
  if ((iv) && (ov) && (len)) {                                                 \
    size_t v_cpy;                                                              \
    __ae2f_MathUtilBVCpy_imp(v_cpy, ov, ovi, iv, ivi, len);                    \
  }

ae2f_structdef(union, ae2f_MathUtilIntPacker) {
	uintptr_t m_u;
	intptr_t m_i;
	unsigned char m_b[1];
};

#endif
