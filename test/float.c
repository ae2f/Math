#include <ae2f/Math/float.imp.h>
#include <stdio.h>

const ae2f_MathFloat float32header = {.bstart = 0,
                                      .exp = ae2f_MathFloat32_EXP,
                                      .man = ae2f_MathFloat32_MAN,
                                      .sign = ae2f_MathFloat32_SIGN},
                     float64header = {.man = ae2f_MathFloat64_MAN,
                                      .exp = ae2f_MathFloat64_EXP,
                                      .sign = ae2f_MathFloat64_SIGN,
                                      .bstart = 0};

typedef union float32buf {
  float a;
  uint8_t b[1];
} float32buf;
typedef union float64buf {
  double a;
  uint8_t b[1];
} float64buf;

#define EPSILON 0.0001
#define DIFFSQR(a, b) (((a) - (b)) * ((a) - (b)))

static uint64_t castftof() {
  {
    ae2f_MathFloat a, b;
    float32buf af;
    float32buf bf;

    puts("[castf32tof32] start");

    af.a = 134;

    a = float32header;
    b = float32header;

    ae2f_err_t e = 0;
    __ae2f_MathFloatCast(&e, &a, af.b, &b, bf.b);

    if (e) {
      printf("[castf32tof32] got error %d\n", e);
      return 1;
    }
    if (DIFFSQR(bf.a, af.a)) {
      printf("[castf32tof32] Expected %f but got %f\n", af.a, bf.a);
      printf("[castf32tof32] %f / %f -> %f\n", af.a, bf.a, af.a / bf.a);
      return 1;
    }

    puts("[castf32tof32] went successful.");
  }

  {
    ae2f_MathFloat a, b;
    float64buf af;
    float64buf bf;

    puts("[castf64tof64] start");

    af.a = 134;

    a = float64header;
    b = float64header;

    ae2f_err_t e = 0;
    uint8_t *buf[2];

    __ae2f_MathFloatCast(&e, &a, af.b, &b, bf.b);

    if (e) {
      printf("[castf64tof64] got error %d\n", e);
      return 1;
    }
    if (DIFFSQR(bf.a, af.a)) {
      printf("[castf64tof64] Expected %f but got %f\n", af.a, bf.a);
      return 1;
    }

    puts("[castf64tof64] went successful.");
  }

  {
    ae2f_MathFloat a, b;
    float64buf af;
    float32buf bf;

    puts("[castf64tof32] start");

    af.a = 134;

    a = float64header;
    b = float32header;

    ae2f_err_t e = 0;
    uint8_t *buf[2];

    __ae2f_MathFloatCast(&e, &a, af.b, &b, bf.b);

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

  return 0;
}

int main() { return castftof(); }
