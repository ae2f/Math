#include <ae2f/Macro.h>
#include <ae2f/Math/float.imp.h>
#include <stdint.h>
#include <stdio.h>

#define putsprefix ""
#define puts(s) puts(putsprefix " " s)
#define printf(f, ...) printf(putsprefix " " f, __VA_ARGS__)

const ae2f_MathFloat float32header = {.bstart = 0,
                                      .exp = ae2f_MathFloat32_EXP,
                                      .man = ae2f_MathFloat32_MAN,
                                      .sign = ae2f_MathFloat32_SIGN},
                     float64header = {.man = ae2f_MathFloat64_MAN,
                                      .exp = ae2f_MathFloat64_EXP,
                                      .sign = ae2f_MathFloat64_SIGN,
                                      .bstart = 0},
                     float16header = {
                         .man = 10, .exp = 5, .sign = 1, .bstart = 0};

const float TESTA[] = {3, 1, 2, 5, 6, 1, 1, 6},
            TESTB[sizeof(TESTA) / sizeof(TESTA[0])] = {2, 6,  1,   2,
                                                       4, 12, 666, 123213};

typedef union float16buf {
  uint8_t b[4];
} float16buf;
typedef union float32buf {
  float a;
  uint8_t b[1];
} float32buf;
typedef union float64buf {
  double a;
  uint8_t b[1];
} float64buf;

#define floatbuf_A float32buf
#define floatbuf_B float32buf
#define floatbuf_O float32buf

ae2f_MAC(floatbuf_A, floatbuf_B, )
    __TEST_FLOAT_CMP(const float *const TESTA, const float *const TESTB,
                     const int i, const ae2f_MathFloat headA,
                     const ae2f_MathFloat headB, uint32_t *const A) {
  do {
    printf("start: %f %f\n", TESTA[i], TESTB[i]);
    floatbuf_A af;
    floatbuf_B bf;

    af.a = TESTA[i];
    bf.a = TESTB[i];

    ae2f_err_t e;
    ae2f_CmpFunRet_t ret;

    __ae2f_MathFloatCmp(&e, &headA, af.b, &headB, bf.b, &ret);

    if (e) {
      /** error code was not 0. */
      printf("Problem occured: %d\n", e);
      *A = 1;
      break;
    }

    if ((ret < 0) != (TESTA[i] < TESTB[i])) {
      /** unexpected value */
      printf("Expected %d but got %d\n", TESTA[i] < TESTB[i], ret < 0);
      *A = 1;
      break;
    }

    puts("went successful");
  } while (0);
}

ae2f_MAC(floatbuf_A, floatbuf_B, floatbuf_O, )
    __TEST_FLOAT_ADD(const float *const TESTA, const float *const TESTB,
                     const int i, const ae2f_MathFloat headA,
                     const ae2f_MathFloat headB, const ae2f_MathFloat headO,
                     uint32_t *const A) {
  do {
    puts("start");
    ae2f_MathFloat a = headA;
    ae2f_MathFloat b = headB;
    ae2f_MathFloat o = headO;

    floatbuf_A af;
    floatbuf_B bf;
    floatbuf_O of;
    ae2f_err_t e = 0;

    af.a = TESTA[i];
    bf.a = TESTB[i];
    of.a = 0;

    __ae2f_MathFloatAdd((&e), (&a), af.b, (&b), bf.b, (&o), of.b);

    if ((e)) {
      printf("got error %d\n", (e));
      *(A) |= 1;
      continue;
    }

    if (of.a != af.a + bf.a) {
      printf(" Expected %f but got %.3f\n", af.a + bf.a, of.a);
      printf("af: %f %f\n", af.a, TESTA[i]);
      printf("bf: %f %f\n", bf.a, TESTB[i]);

      fputs("o:\t0b", stdout);
      size_t i;
      for (i = __ae2f_MathFloatElSz(&o) - 1; i != -1; i--) {
        fprintf(stdout, "%d", __ae2f_MathUtilBVGetArr(of.b, i));
      }
      fputc('\n', stdout);

      of.a = af.a + bf.a;
      fprintf(stdout, "%.3f:\t0b", of.a);
      for (i = __ae2f_MathFloatElSz(&o) - 1; i != -1; i--) {
        fprintf(stdout, "%d", __ae2f_MathUtilBVGetArr(of.b, i));
      }
      fputc('\n', stdout);

      of.a = TESTA[i];
      fputs("A:\t0b", stdout);
      for (i = __ae2f_MathFloatElSz(&o) - 1; i != -1; i--) {
        fprintf(stdout, "%d", __ae2f_MathUtilBVGetArr(of.b, i));
      }
      fputc('\n', stdout);

      of.a = TESTB[i];
      fputs("B:\t0b", stdout);
      for (i = __ae2f_MathFloatElSz(&o) - 1; i != -1; i--) {
        fprintf(stdout, "%d", __ae2f_MathUtilBVGetArr(of.b, i));
      }
      fputc('\n', stdout);

      fprintf(stdout, "%.3f:\t0b", af.a);
      for (i = __ae2f_MathFloatElSz(&a) - 1; i != -1; i--) {
        fprintf(stdout, "%d", __ae2f_MathUtilBVGetArr(af.b, i));
      }
      fputc('\n', stdout);

      fprintf(stdout, "%.3f:\t0b", bf.a);
      for (i = __ae2f_MathFloatElSz(&b) - 1; i != -1; i--) {
        fprintf(stdout, "%d", __ae2f_MathUtilBVGetArr(bf.b, i));
      }
      fputc('\n', stdout);
      *(A) |= 1;
      continue;
    }

    puts("went successful");
  } while (0);
}
