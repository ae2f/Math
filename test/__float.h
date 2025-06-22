#include <ae2f/Macro.h>
#include <ae2f/Math/float.auto.h>
#include <stdint.h>
#include <stdio.h>
    
#define floatbuf_A float32buf
#define floatbuf_B float32buf
#define floatbuf_O float32buf

    ae2f_MAC(floatbuf_A, floatbuf_B, floatbuf_O,) __TEST_FLOAT_ADD(
      const float* const TESTA, 
      const float* const TESTB, 
      const int i, 
      const ae2f_MathFloat headA, 
      const ae2f_MathFloat headB, 
      const ae2f_MathFloat headO,
      uint32_t* const A
    ) {
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

      if (e) {
        printf("got error %d\n", e);
        *(A) |= 1;
        continue;
      }

      if (of.a != af.a + bf.a) {
        printf(" Expected %f but got %.3f\n", af.a + bf.a, of.a);
        printf("af: %f\n", af.a);
        printf("bf: %f\n", bf.a);

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
    } while(0);
  }

