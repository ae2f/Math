

#include <stdio.h>

#include <ae2f/Math/float.auto.h>

#define putsprefix ""
#define puts(s) puts(putsprefix " " s)
#define printf(f, ...) printf(putsprefix f, __VA_ARGS__)

const ae2f_MathFloat float32header = {.bstart = 0,
                                      .exp = ae2f_MathFloat32_EXP,
                                      .man = ae2f_MathFloat32_MAN,
                                      .sign = ae2f_MathFloat32_SIGN},
                     float64header = {.man = ae2f_MathFloat64_MAN,
                                      .exp = ae2f_MathFloat64_EXP,
                                      .sign = ae2f_MathFloat64_SIGN,
                                      .bstart = 0},
                     float16header = {
                         .man = 10, .exp = 5, .sign = 1, .bstart = 6};

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

#define EPSILON 0.0001
#define DIFFSQR(a, b) (((((a) - (b)) * ((a) - (b)))) > (EPSILON))

static uint64_t castftof() {
  {
    ae2f_MathFloat a, b, c;
    float32buf af;
    float32buf bf;
    float16buf cf;

    puts("[castf32tof32] start");

    af.a = 134;

    a = float32header;
    b = float32header;
    c = float16header;

    ae2f_err_t e = 0;
    __ae2f_MathFloatCast(&e, &a, af.b, &c, cf.b);
    __ae2f_MathFloatCast(&e, &c, cf.b, &b, bf.b);

    if (e) {
      printf("[castf32tof32] got error %d\n", e);
      return 1;
    }
    if (DIFFSQR(bf.a, af.a)) {
      printf("[castf32tof32] Expected %f but got %f\n", af.a, bf.a);
      printf("%u %u %u %u\n", af.b[0], af.b[1], af.b[2], af.b[3]);
      printf("%u %u %u %u\n", bf.b[0], bf.b[1], bf.b[2], bf.b[3]);
      return 1;
    }

    puts("[castf32tof32] went successful.");
  }

  {
    ae2f_MathFloat a, b;
    float64buf af;
    float64buf bf;

    puts("[castf64tof64] start");

    a = float64header;
    b = float64header;

    ae2f_err_t e = 0;

    af.a = 3;
    __ae2f_MathFloatCast(&e, &a, af.b, &b, bf.b);

    printf("[castf64tof64] Expected %f and got %f\n", af.a, bf.a);

    if (e) {
      printf("[castf64tof64] got error %d\n", e);
      return 1;
    }
    if (DIFFSQR(bf.a, af.a)) {
      printf("[castf64tof64] Expected %f but got %f\n", af.a, bf.a);
      printf("%u %u %u %u %u %u %u %u\n", af.b[0], af.b[1], af.b[2], af.b[3],
             af.b[4], af.b[5], af.b[6], af.b[7]);
      printf("%u %u %u %u %u %u %u %u\n", bf.b[0], bf.b[1], bf.b[2], bf.b[3],
             bf.b[4], bf.b[5], bf.b[6], bf.b[7]);
      return 1;
    }

    af.a = 0.06;
    __ae2f_MathFloatCast(&e, &a, af.b, &b, bf.b);

    if (e) {
      printf("[castf64tof64] got error %d\n", e);
      return 1;
    }
    if (DIFFSQR(bf.a, af.a)) {
      printf("[castf64tof64] Expected %f but got %f\n", af.a, bf.a);
      printf("%u %u %u %u %u %u %u %u\n", af.b[0], af.b[1], af.b[2], af.b[3],
             af.b[4], af.b[5], af.b[6], af.b[7]);
      printf("%u %u %u %u %u %u %u %u\n", bf.b[0], bf.b[1], bf.b[2], bf.b[3],
             bf.b[4], bf.b[5], bf.b[6], bf.b[7]);
      return 1;
    }

    puts("[castf64tof64] went successful.");
  }

  {
    ae2f_MathFloat a, b;
    float64buf af;
    float32buf bf;

    puts("[castf64tof32] start");

    a = float64header;
    b = float32header;

    ae2f_err_t e = 0;

    af.a = 134;

    __ae2f_MathFloatCast(&e, &a, af.b, &b, bf.b);
    printf("[castf64tof32] Expected %f and got %f\n", af.a, bf.a);

    if (e) {
      printf("[castf64tof32] got error %d\n", e);
      return 1;
    }
    if (DIFFSQR(bf.a, af.a)) {
      printf("[castf64tof32] Expected %f but got %f\n", af.a, bf.a);
      return 1;
    }

    af.a = 0.0023;

    __ae2f_MathFloatCast(&e, &a, af.b, &b, bf.b);
    printf("[castf64tof32] Expected %f and got %f\n", af.a, bf.a);
    if (e) {
      printf("[castf64tof32] got error %d\n", e);
      return 1;
    }
    if (DIFFSQR(bf.a, af.a)) {
      printf("[castf64tof32] Expected %f but got %f\n", af.a, bf.a);
      return 1;
    }

    af.a = -0.0023;

    __ae2f_MathFloatCast(&e, &a, af.b, &b, bf.b);
    printf("[castf64tof32] Expected %f and got %f\n", af.a, bf.a);
    if (e) {
      printf("[castf64tof32] got error %d\n", e);
      return 1;
    }
    if (DIFFSQR(bf.a, af.a)) {
      printf("[castf64tof32] Expected %f but got %f\n", af.a, bf.a);
      return 1;
    }

    puts("[castf64tof32] went successful.");
  }

  {
    ae2f_MathFloat a, b;
    float32buf af;
    float64buf bf;

    puts("[castf32tof64] start");

    a = float32header;
    b = float64header;

    ae2f_err_t e = 0;

    af.a = 134;

    __ae2f_MathFloatCast(&e, &a, af.b, &b, bf.b);
    printf("[castf32tof64] Expected %f and got %f\n", af.a, bf.a);
    if (e) {
      printf("[castf32tof64] got error %d\n", e);
      return 1;
    }
    if (DIFFSQR(bf.a, af.a)) {
      printf("[castf32tof64] Expected %f but got %f\n", af.a, bf.a);
      return 1;
    }

    af.a = 0.001;
    bf.a = 0;
    __ae2f_MathFloatCast(&e, &a, (const unsigned char *)af.b, &b, bf.b);
    printf("%u %u %u %u\n", af.b[0], af.b[1], af.b[2], af.b[3]);
    printf("%u %u %u %u %u %u %u %u\n", bf.b[0], bf.b[1], bf.b[2], bf.b[3],
           bf.b[4], bf.b[5], bf.b[6], bf.b[7]);

    printf("[castf32tof64] Expected %f and got %f\n", af.a, bf.a);

    if (e) {
      printf("[castf32tof64] got error %d\n", e);
      return 1;
    }
    if (DIFFSQR(bf.a, af.a)) {
      printf("[castf32tof64] Expected %f but got %f\n", af.a, bf.a);
      return 1;
    }

    puts("[castf32tof64] went successful.");
  }

  return 0;
}

static uint64_t flip() {
  {
    ae2f_MathFloat a, b;
    float32buf af;
    float32buf bf;

    puts("[flipf32tof32] start");

    af.a = 134;

    a = float32header;
    b = float32header;

    ae2f_err_t e = 0;
    __ae2f_MathFloatFlip(&e, &a, af.b, &b, bf.b);

    if (e) {
      printf("[flipf32tof32] got error %d\n", e);
      return 2;
    }
    if (DIFFSQR(bf.a, -af.a)) {
      printf("[flipf32tof32] Expected %f but got %f\n", -af.a, bf.a);
      printf("%u %u %u %u\n", af.b[0], af.b[1], af.b[2], af.b[3]);
      printf("%u %u %u %u\n", bf.b[0], bf.b[1], bf.b[2], bf.b[3]);
      return 2;
    }

    puts("[flipf32tof32] went successful.");
  }

  {
    ae2f_MathFloat a, b;
    float64buf af;
    float64buf bf;

    puts("[flipf64tof64] start");

    a = float64header;
    b = float64header;

    ae2f_err_t e = 0;

    af.a = 3;
    __ae2f_MathFloatFlip(&e, &a, af.b, &b, bf.b);

    printf("[flipf64tof64] Expected %f and got %f\n", -af.a, bf.a);

    if (e) {
      printf("[flipf64tof64] got error %d\n", e);
      return 2;
    }
    if (DIFFSQR(bf.a, -af.a)) {
      printf("[flipf64tof64] Expected %f but got %f\n", -af.a, bf.a);
      return 2;
    }

    af.a = 0.06;
    __ae2f_MathFloatFlip(&e, &a, af.b, &b, bf.b);

    if (e) {
      printf("[flipf64tof64] got error %d\n", e);
      return 2;
    }
    if (DIFFSQR(bf.a, -af.a)) {
      printf("[flipf64tof64] Expected %f but got %f\n", -af.a, bf.a);
      printf("%u %u %u %u %u %u %u %u\n", af.b[0], af.b[1], af.b[2], af.b[3],
             af.b[4], af.b[5], af.b[6], af.b[7]);
      printf("%u %u %u %u %u %u %u %u\n", bf.b[0], bf.b[1], bf.b[2], bf.b[3],
             bf.b[4], bf.b[5], bf.b[6], bf.b[7]);
      return 2;
    }

    puts("[flipf64tof64] went successful.");
  }

  {
    ae2f_MathFloat a, b;
    float64buf af;
    float32buf bf;

    puts("[flipf64tof32] start");

    a = float64header;
    b = float32header;

    ae2f_err_t e = 0;

    af.a = 134;

    __ae2f_MathFloatFlip(&e, &a, af.b, &b, bf.b);
    printf("[flipf64tof32] Expected %f and got %f\n", -af.a, bf.a);

    if (e) {
      printf("[flipf64tof32] got error %d\n", e);
      return 1;
    }
    if (DIFFSQR(bf.a, -af.a)) {
      printf("[flipf64tof32] Expected %f but got %f\n", -af.a, bf.a);
      return 1;
    }

    af.a = 0.0023;

    __ae2f_MathFloatFlip(&e, &a, af.b, &b, bf.b);
    printf("[flipf64tof32] Expected %f and got %f\n", -af.a, bf.a);
    if (e) {
      printf("[flipf64tof32] got error %d\n", e);
      return 1;
    }
    if (DIFFSQR(bf.a, -af.a)) {
      printf("[flipf64tof32] Expected %f but got %f\n", -af.a, bf.a);
      return 1;
    }

    af.a = -0.0023;

    __ae2f_MathFloatFlip(&e, &a, af.b, &b, bf.b);
    printf("[flipf64tof32] Expected %f and got %f\n", -af.a, bf.a);
    if (e) {
      printf("[flipf64tof32] got error %d\n", e);
      return 1;
    }
    if (DIFFSQR(bf.a, -af.a)) {
      printf("[flipf64tof32] Expected %f but got %f\n", -af.a, bf.a);
      return 1;
    }

    puts("[flipf64tof32] went successful.");
  }

  {
    ae2f_MathFloat a, b;
    float32buf af;
    float64buf bf;

    puts("[flipf32tof64] start");

    a = float32header;
    b = float64header;

    ae2f_err_t e = 0;

    af.a = 134;

    __ae2f_MathFloatFlip(&e, &a, af.b, &b, bf.b);
    printf("[flipf32tof64] Expected %f and got %f\n", -af.a, bf.a);
    if (e) {
      printf("[flipf32tof64] got error %d\n", e);
      return 1;
    }
    if (DIFFSQR(bf.a, -af.a)) {
      printf("[flipf32tof64] Expected %f but got %f\n", -af.a, bf.a);
      return 1;
    }

    af.a = 0.001;
    bf.a = 0;
    __ae2f_MathFloatFlip(&e, &a, (const unsigned char *)af.b, &b, bf.b);
    printf("%u %u %u %u\n", af.b[0], af.b[1], af.b[2], af.b[3]);
    printf("%u %u %u %u %u %u %u %u\n", bf.b[0], bf.b[1], bf.b[2], bf.b[3],
           bf.b[4], bf.b[5], bf.b[6], bf.b[7]);

    printf("[flipf32tof64] Expected %f and got %f\n", -af.a, bf.a);

    if (e) {
      printf("[flipf32tof64] got error %d\n", e);
      return 1;
    }
    if (DIFFSQR(bf.a, -af.a)) {
      printf("[flipf32tof64] Expected %f but got %f\n", -af.a, bf.a);
      return 1;
    }

    puts("[flipf32tof64] went successful.");
  }

  return 0;
}

static uint64_t normalise() {
  {
    puts("[normalise32] start");
    ae2f_MathFloat a = float32header;
    float32buf af;

    af.a = 134;

    ae2f_err_t e = 0;
    __ae2f_MathFloatNormalise(&e, &a, af.b);

    if (e) {
      printf("[normalise32] got error %d\n", e);
      return 1;
    }

    if (af.a != 134) {
      printf("[normalise32] Expected %f but got %f\n", 134, af.a);
      return 1;
    }

    puts("[normalise32] went successful");
  }

  {
    puts("[normalise64] start");
    ae2f_err_t e = 0;
    ae2f_MathFloat a = float64header;
    float64buf af;

    af.a = 134;
    __ae2f_MathFloatNormalise(&e, &a, af.b);

    if (e) {
      printf("[normalise64] got error %d\n", e);
      return 1;
    }

    if (af.a != 134) {
      printf("[normalise64] Expected %f but got %f\n", 134, af.a);
      return 1;
    }

    puts("[normalise64] went successful");
  }
  return 0;
}

static uint64_t add() {
  {
#define putsprefix "[f32addf32f32]"
    puts("start");
    ae2f_MathFloat a = float32header;
    ae2f_MathFloat b = float32header;
    ae2f_MathFloat o = float32header;

    float32buf af, bf, of;
    ae2f_err_t e = 0;

    af.a = 3;
    bf.a = 7;
    of.a = 0;

    __ae2f_MathFloatAdd((&e), (&a), af.b, (&b), bf.b, (&o), of.b);

    if (e) {
      printf("got error %d\n", e);
      return 1;
    }

    if (of.a != af.a + bf.a) {
      printf(" Expected %f but got %.3f\n", af.a + bf.a, of.a);
      printf("af: %f\n", af.a);
      printf("bf: %f\n", bf.a);

      fputs("o:\t0b", stdout);
      for (size_t i = __ae2f_MathFloatElSz(&o) - 1; i != -1; i--) {
        fprintf(stdout, "%d", __ae2f_MathUtilBVGetArr(of.b, i));
      }
      fputc('\n', stdout);

      of.a = af.a + bf.a;
      fprintf(stdout, "%.3f:\t0b", of.a);
      for (size_t i = __ae2f_MathFloatElSz(&o) - 1; i != -1; i--) {
        fprintf(stdout, "%d", __ae2f_MathUtilBVGetArr(of.b, i));
      }
      fputc('\n', stdout);

      of.a = 0.;
      fputs("0:\t0b", stdout);
      for (size_t i = __ae2f_MathFloatElSz(&o) - 1; i != -1; i--) {
        fprintf(stdout, "%d", __ae2f_MathUtilBVGetArr(of.b, i));
      }
      fputc('\n', stdout);

      of.a = af.a;
      fprintf(stdout, "%.3f:\t0b", af.a);
      for (size_t i = __ae2f_MathFloatElSz(&o) - 1; i != -1; i--) {
        fprintf(stdout, "%d", __ae2f_MathUtilBVGetArr(of.b, i));
      }
      fputc('\n', stdout);

      of.a = bf.a;
      fprintf(stdout, "%.3f:\t0b", bf.a);
      for (size_t i = __ae2f_MathFloatElSz(&o) - 1; i != -1; i--) {
        fprintf(stdout, "%d", __ae2f_MathUtilBVGetArr(of.b, i));
      }
      fputc('\n', stdout);
      return 1;
    }

    puts("went successful");
  }

  return 0;
}

int main() { return castftof() | flip() | normalise() & add(); }
