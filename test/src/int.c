#include <ae2f/Math/int.auto.h>
#include <stdint.h>
#include <stdio.h>



static int flip() {
  {
    ae2f_err_t e = 0;
    uint8_t a = 3, *_buf[2];
    ae2f_MathInt aa;

    aa.sign = 0;
    aa.sz = 8;
    aa.vecbegpoint = 0;

    __ae2f_MathIntFlip(&e, &aa, &a, &aa, &a);
    if ((e)) {
      printf("Test::flip Error occured: %d\n", e);
      return 1;
    };

    if (a != (uint8_t)-3) {
      printf("Test::flip failure. Result went %u vs -3\n", a);
      return 1;
    }

    a = 1;
    aa.sz = 7;
    aa.vecbegpoint = 1;

    __ae2f_MathIntFlip(&e, &aa, &a, &aa, &a);

    if ((e)) {
      printf("Test::flip Error occured %d\n", e);
      return 1;
    }
    if (a != 1) {
      printf("Test::flip failure. Result went %u vs 1\n", a);
      return 1;
    }

  } /* Test for single value */

  puts("Test::flip has succeed.");
  return 0;
}

static int cast() {
  {
    union {
      int8_t i;
      uint8_t v[1];
    } a = {.i = -1};
    union {
      int32_t i;
      uint8_t v[1];
    } b;
    ae2f_err_t e = 0;

    ae2f_MathInt ai, bi;
    ai.sign = 1;
    ai.sz = 8;
    ai.vecbegpoint = 0;

    bi.sign = 1;
    bi.sz = 32;
    bi.vecbegpoint = 0;

    uint8_t *_buf1, *_buf2;

    __ae2f_MathIntCast(&e, &ai, a.v, &bi, b.v);

    if (e) {
      printf("Test::cast Error occured: %d\n", e);
      return 1;
    }

    if (b.i != -1) {
      printf("Test::cast unexpected value %d. Expected -1.\n", b);
      return 1;
    }
  } /* Test for single value */

  puts("Test::cast has succeed.");
  return 0;
}

static int add_sub() {
  {
    union __1 {
      int8_t i;
      uint8_t v[1];
    } a = ae2f_RecordMk(ae2f_WhenC(union) __1, .i = -1);

    union __2 {
      int32_t i;
      uint8_t v[1];
    } b = ae2f_RecordMk(ae2f_WhenC(union) __2, .i = 3);
    ae2f_err_t e = 0;

    ae2f_WhenC(union) __2 o;
    o.i = 4123;

    ae2f_MathInt ai, bi, oi;
    ai.sign = 1;
    ai.sz = 8;
    ai.vecbegpoint = 0;

    bi.sign = 1;
    bi.sz = 32;
    bi.vecbegpoint = 0;

    __ae2f_MathIntAdd(&e, &ai, a.v, &bi, b.v, &bi, o.v);

    if (e) {
      printf("Test::add Error occurred: %d\n", e);
      return 1;
    }

    if (o.i != 2) {
      printf("Test::add Expected 2 but got %d\n", o.i);
      return 1;
    }
  }
  puts("test::add has succeed");

  {
    union __1 {
      int8_t i;
      uint8_t v[1];
    } a = ae2f_RecordMk(ae2f_WhenC(union) __1, -1);

    union __2 {
      int32_t i;
      uint8_t v[1];
    } b = ae2f_RecordMk(ae2f_WhenC(union) __2, 3);
    ae2f_err_t e = 0;

    ae2f_MathInt ai, bi;
    ai.sign = 1;
    ai.sz = 8;
    ai.vecbegpoint = 0;

    bi.sign = 1;
    bi.sz = 32;
    bi.vecbegpoint = 0;

    uint8_t *_buf[3];

    __ae2f_MathIntSub(&e, &ai, a.v, &bi, b.v, &bi, a.v);

    if (e) {
      printf("Test::subtract Error occurred: %d\n", e);
      return 1;
    }

    if (a.i != -4) {
      printf("Test::subtract Expected -4 but got %d\n", b);
      return 1;
    }
  }
  puts("Test::subtract has succeed.");

  return 0;
}

int cmp() {
  {
    union {
      uint8_t b[1];
      int8_t i;
    } a = {.i = -1};
    ae2f_err_t e = 0;

    uint8_t *vec;

    ae2f_MathInt ai;
    ai.sign = 1;
    ai.sz = 8;
    ai.vecbegpoint = 0;

    ae2f_CmpFunRet_t ret;

    __ae2f_MathIntCmpZero(&e, &ai, a.b, &ret);

    if (e) {
      printf("Test::cmp0 returned error: %d\n", e);
      return 1;
    }

    if (ret != ae2f_CmpFunRet_LISLESSER) {
      printf("Test::cmp0 returned unexpected value %d, %d expected.", ret,
             ae2f_CmpFunRet_LISLESSER);
      return 1;
    }

    a.i = 0;
    __ae2f_MathIntCmpZero(&e, &ai, a.b, &ret);

    if ((e)) {
      printf("Test::cmp0 casted error %d\n", e);
      return 1;
    }

    if (ret != ae2f_CmpFunRet_EQUAL) {
      printf("Test::cmp0 returned unexpected value %d, %d expected.", ret,
             ae2f_CmpFunRet_EQUAL);
      return 1;
    }

    a.i = 1;

    __ae2f_MathIntCmpZero(&e, &ai, a.b, &ret);
    if ((e)) {
      printf("Test::cmp0 casted error %d\n", e);
      return 1;
    }

    if (ret != ae2f_CmpFunRet_RISLESSER) {
      printf("Test::cmp0 returned unexpected value %d, %d expected.\n", ret,
             ae2f_CmpFunRet_RISLESSER);
      return 1;
    }
  }
  puts("Test::cmp0 has succeed");

  {
    ae2f_err_t e = 0;
    ae2f_CmpFunRet_t ret;

    union {
      int8_t i;
      uint8_t b[1];
    } a = {.i = -1};
    ae2f_MathInt ai;
    ai.sign = 1;
    ai.sz = 8;
    ai.vecbegpoint = 0; /* Making a number */

    union {
      int16_t i;
      uint8_t b[1];
    } b = {.i = -1};
    ae2f_MathInt bi;
    bi.sign = 1;
    bi.sz = 15;
    bi.vecbegpoint = 0; /* Making a number */

    ae2f_bMathMem __mem[2] = {0, };
    __ae2f_MathIntCmp(&e, &ai, a.b, &bi, b.b, &ret);
    if (e) {
      printf("Test::cmp::equal casted error: %d\n", e);
      return 1;
    }

    if (ret) {
      printf("Test::cmp::equal Unexpected value %d, expected %d\n", ret,
             ae2f_CmpFunRet_EQUAL);
      return 1;
    }

    b.i = 1;
    __ae2f_MathIntCmp(&e, &ai, a.b, &bi, b.b, &ret);
    if ((e)) {
      printf("Test::cmp::equal casted error: %d\n", e);
      return 1;
    }

    if (ret >= 0) {
      printf("Test::cmp::equal You failed on %d - %d\n", a, b);
      printf("Test::cmp::equal Unexpected value %d, expected %d\n", ret,
             ae2f_CmpFunRet_LISLESSER);
      return 1;
    }

    b.i = -300;
    __ae2f_MathIntCmp(&e, &ai, a.b, &bi, b.b, &ret);
    if ((e)) {
      printf("Test::cmp::equal casted error: %d\n", e);
      return 1;
    }

    if (ret <= 0) {
      printf("Test::cmp::equal You failed on %d - %d\n", a, b);
      printf("Test::cmp::equal Unexpected value %d, expected %d\n", ret,
             ae2f_CmpFunRet_RISLESSER);
      return 1;
    }

    a.i = 50;
    b.i = 300;
    __ae2f_MathIntCmp(&e, &ai, a.b, &bi, b.b, &ret);
    if ((e)) {
      printf("Test::cmp::equal casted error: %d\n", e);
      return 1;
    }

    if (ret != ae2f_CmpFunRet_LISLESSER) {
      printf("Test::cmp::equal You failed on %d - %d\n", a, b);
      printf("Test::cmp::equal Unexpected value %d, expected %d\n", ret,
             ae2f_CmpFunRet_LISLESSER);

      return 1;
    }

    a.i = 3;
    b.i = 2;

    __ae2f_MathIntCmp(&e, &ai, a.b, &bi, b.b, &ret);
    if ((e)) {
      printf("Test::cmp::equal casted error: %d\n", e);
      return 1;
    }

    if (ret != ae2f_CmpFunRet_RISLESSER) {
      printf("Test::cmp::equal You failed on %d - %d\n", a, b);
      printf("Test::cmp::equal Unexpected value %d, expected %d\n", ret,
             ae2f_CmpFunRet_RISLESSER);

      return 1;
    }
  }
  puts("Test::cmp::equal has succeed");

  return 0;
}

static int mul() {
  {
    union {
      int8_t i;
      uint8_t b[1];
    } a = {.i = 3};
    union {
      int32_t i;
      uint8_t b[1];
    } b = {.i = 200};
    union {
      int16_t i;
      uint8_t b[1];
    } o = {.i = 0};
    uint64_t buf;

    ae2f_err_t e = 0;

    ae2f_MathInt ai, bi, oi;
    ai.sign = 1;
    ai.sz = 8;
    ai.vecbegpoint = 0;

    bi.sign = 1;
    bi.sz = 32;
    bi.vecbegpoint = 0;

    oi.sign = 1;
    oi.vecbegpoint = 0;
    oi.sz = 16;

    ae2f_bMathMem BUFF[6] = {
        0,
    };

    __ae2f_MathIntMul(&e, &ai, a.b, &bi, b.b, &oi, o.b);
    if (e) {
      printf("Test::mul Error occurred: %d\n", e);
      return 1;
    }

    if (o.i != 600) {
      printf("Test::mul Expected 600 but got %d\n", o.i);
      return 1;
    }

    a.i = 3; /** When a is negative, test goes failed */
    b.i = -2;
    __ae2f_MathIntMul(&e, &ai, a.b, &bi, b.b, &oi, o.b);

    if (e) {
      printf("Test::mul Error occurred: %d\n", e);
      return 1;
    }

    if (o.i != -6) {
      printf("Test::mul Expected -6 but got %d\n", o.i);
      return 1;
    }
  }
  puts("Test::mul has succeed");
  return 0;
}

#if 1
static int div() {
  {
    union {
      int32_t i;
      uint8_t b[1];
    } a = {.i = 10000};
    union {
      int16_t i;
      uint8_t b[1];
    } b = {.i = 7};
    union {
      int16_t i;
      uint8_t b[1];
    } oq = {.i = 0};
    union {
      int32_t i;
      uint8_t b[1];
    } _or = {.i = 0};

    ae2f_err_t e = 0;

    ae2f_MathInt ai, bi, oqi, ori;
    ai.sign = 1;
    ai.sz = 32;
    ai.vecbegpoint = 0;

    bi.sign = 1;
    bi.sz = 16;
    bi.vecbegpoint = 0;

    oqi.sign = 1;
    oqi.vecbegpoint = 0;
    oqi.sz = 16;

    ori.sign = 1;
    ori.vecbegpoint = 0;
    ori.sz = 32;

    ae2f_bMathMem __buf[8] = {
        0,
    };

    __ae2f_MathIntDivU(&e, &ai, a.b, &bi, b.b, &oqi, oq.b, &ori, _or.b);
    printf("A, %d, B: %d, Q: %d, R: %d\n", a.i, b.i, oq.i, _or.i);
    if (e) {
      printf("Test::div+ casted error %d\n", e);
      return 1;
    }

    if (_or.i != a.i % b.i) {
      printf("Test::div+ Expected %d but got %d\n", a.i % b.i, _or.i);
      return 1;
    }

    if (oq.i != a.i / b.i) {
      printf("Test::div+ Expected %d but got %d\n", a.i / b.i, oq.i);
      return 1;
    }

    a.i = 3;
    b.i = 5;
    __ae2f_MathIntDivU(&e, &ai, a.b, &bi, b.b, &oqi, oq.b, &ori, _or.b);

    printf("A, %d, B: %d, Q: %d, R: %d\n", a.i, b.i, oq.i, _or.i);
    if (e) {
      printf("Test::div+ casted error %d\n", e);
      return 1;
    }

    if (_or.i != a.i % b.i) {
      printf("Test::div+ Expected %d but got %d\n", a.i % b.i, _or.i);
      return 1;
    }

    if (oq.i != a.i / b.i) {
      printf("Test::div+ Expected %d but got %d\n", a.i / b.i, oq.i);
      return 1;
    }
  }
  puts("Test::div+ has succeed.");
  return 0;
}
#else
#define div() 1
#endif

int select() {
  {
    union {
      int8_t i;
      uint8_t b[1];
    } a = {.i = 3};
    union {
      int32_t i;
      uint8_t b[1];
    } b = {.i = 200};
    union {
      int16_t i;
      uint8_t b[1];
    } o = {.i = 0};
    uint64_t buf;

    ae2f_err_t e = 0;

    ae2f_MathInt ai, bi, oi;
    ai.sign = 1;
    ai.sz = 8;
    ai.vecbegpoint = 0;

    bi.sign = 1;
    bi.sz = 32;
    bi.vecbegpoint = 0;

    oi.sign = 1;
    oi.vecbegpoint = 0;
    oi.sz = 16;

    __ae2f_MathIntSel(&e, &ai, a.b, &bi, b.b, &oi, o.b, -1);

    if (e) {
      printf("Test::select Error: %d\n", e);
      return 1;
    }
    if (o.i != 3) {
      printf("Test::select expected %d but got %d", 3, o.i);
      return 1;
    }

    __ae2f_MathIntSel(&e, &ai, a.b, &bi, b.b, &oi, o.b, 1);

    if (e) {
      printf("Test::select Error: %d\n", e);
      return 1;
    }
    if (o.i != 200) {
      printf("Test::select expected %d but got %d", 200, o.i);
      return 1;
    }
  }

  puts("Test::select has succeed.");
  return 0;
}

int shiftl() {
  {
    union {
      int8_t i;
      uint8_t b[1];
    } a = {.i = 3};
    union {
      int32_t i;
      uint8_t b[1];
    } b = {.i = 200};
    union {
      int16_t i;
      uint8_t b[1];
    } o = {.i = 0};
    uint64_t buf;

    ae2f_err_t e = 0;

    ae2f_MathInt ai, bi, oi;
    ai.sign = 1;
    ai.sz = 8;
    ai.vecbegpoint = 0;

    bi.sign = 1;
    bi.sz = 32;
    bi.vecbegpoint = 0;

    oi.sign = 1;
    oi.vecbegpoint = 0;
    oi.sz = 16;

    __ae2f_MathIntBitL(&e, 2, &ai, a.b, &oi, o.b);

    if (e) {
      printf("Test::shiftl Error: %d\n", e);
      return 1;
    }
    if (o.i != 12) {
      printf("Test::shiftl expected %d but got %d\n", 12, o.i);
      return 1;
    }

    __ae2f_MathIntBitL(&e, 2, &ai, a.b, &ai, a.b);

    if (e) {
      printf("Test::shiftl Error: %d\n", e);
      return 1;
    }
    if (a.i != 12) {
      printf("Test::shiftl expected %d but got %d\n", 12, a.i);
      return 1;
    }
  }
  puts("test::shiftl has succeed.");
  return 0;
}

int shiftr() {
  {
    union {
      int8_t i;
      uint8_t b[1];
    } a = {.i = 3};
    union {
      int32_t i;
      uint8_t b[1];
    } b = {.i = 200};
    union {
      int16_t i;
      uint8_t b[1];
    } o = {.i = 0};
    uint64_t buf;

    ae2f_err_t e = 0;

    ae2f_MathInt ai, bi, oi;
    ai.sign = 1;
    ai.sz = 8;
    ai.vecbegpoint = 0;

    bi.sign = 1;
    bi.sz = 32;
    bi.vecbegpoint = 0;

    oi.sign = 1;
    oi.vecbegpoint = 0;
    oi.sz = 16;

    __ae2f_MathIntBitR(&e, 1, &ai, a.b, &oi, o.b);

    if (e) {
      printf("Test::shiftl Error: %d\n", e);
      return 1;
    }
    if (o.i != 1) {
      printf("Test::shiftl expected %d but got %d\n", 1, o.i);
      return 1;
    }
  }
  puts("test::shiftl has succeed.");
  return 0;
}

int main() {
  int a = flip() || cast() || add_sub() || cmp() || mul() || div() ||
          select() || shiftl() || shiftr() || 0;

  printf("Final Output: %d\n", a);
  return a; //!(a == 0 || a == -0);
}
