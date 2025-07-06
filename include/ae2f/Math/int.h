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
  unsigned char sign : 1;
  /** @brief From which bit point is the start of the integer. */
  unsigned char vecbegpoint : 3;
} ae2f_MathInt;

#define ae2f_pMathInt ae2f_MathInt *const

#include <ae2f/Pack/End.h>

#endif
