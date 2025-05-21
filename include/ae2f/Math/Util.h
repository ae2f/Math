#ifndef ae2f_Math_Util_h
#define ae2f_Math_Util_h

/**
 * @brief
 * `b.r` = `p` % 8;	[remainder] \n
 * `b.q` = `p` / 8;	[quotient]
 *
 * @tparam uint_t is unsigned int type.
 * */
#define ae2f_MathUtilDiv8(uint_t)                                              \
  union __ae2f_MathUtilDiv8__##uint_t {                                                                      \
    uint_t p;                                                                  \
    struct {                                                                   \
      unsigned r : 3;                                                          \
      uint_t q : (sizeof(uint_t) << 3) - 3;                                    \
    } b;                                                                       \
  }

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
  union __ae2f_MathUtilFlag2__##c_sz {                                                                      \
    unsigned a : 2;                                                            \
    unsigned c : c_sz;                                                         \
    struct {                                                                   \
      unsigned _0 : 1;                                                         \
      unsigned _1 : 1;                                                         \
      __VA_ARGS__                                                              \
    } b;                                                                       \
  }

/** @brief
 * `b._0` = `a` & 1;	[1nd bit] \n
 * `b._1` = `a` >> 1;	[2nd bit]
 * */
typedef __ae2f_MathUtilFlag2(2) ae2f_MathUtilFlag2;

#endif
