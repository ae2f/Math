#include <stdio.h>
#include <ae2f/Math/int.imp.h>

static int flip() {
	{
		ae2f_err_t e;
		uint8_t a = 3, 
			*_buf[2];
		ae2f_MathInt aa;

		aa.sign = 0;
		aa.sz = 8;
		aa.vecbegpoint = 0;

		__ae2f_MathIntFlip(
				&e
				, 1
				, &aa
				, &a
				, &aa
				, &a
				, _buf[0]
				, _buf[1]
				);
		if((e))
		{
			printf("Test::flip Error occured: %d\n", e);
			return 1;
		};

		if(a != (uint8_t)-3) 
		{
			printf("Test::flip failure. Result went %u vs -3\n", a);
			return 1;
		}

		a = 1;
		aa.sz = 7;
		aa.vecbegpoint = 1;

		__ae2f_MathIntFlip(
				&e
				, 1
				, &aa
				, &a
				, &aa
				, &a
				, _buf[0]
				, _buf[1]
				);

		if((e)) 
		{
			printf("Test::flip Error occured %d\n", e);
			return 1;
		}
		if(a != 1)
		{
			printf("Test::flip failure. Result went %u vs 1\n", a);
			return 1;
		}

	} /* Test for single value */

	puts("Test::flip has succeed.");
	return 0;
}

static int cast() {
	{
		union { int8_t i; uint8_t v[1]; } a = { .i = -1 };
		union { int32_t i; uint8_t v[1]; } b;
		ae2f_err_t e;

		ae2f_MathInt ai, bi;
		ai.sign = 1;
		ai.sz = 8;
		ai.vecbegpoint = 0;

		bi.sign = 1;
		bi.sz = 32;
		bi.vecbegpoint = 0;

		uint8_t
			* _buf1
			, * _buf2;

		__ae2f_MathIntCast(
				&e
				, 1
				, &ai
				, a.v
				, &bi
				, b.v
				, _buf1
				, _buf2
				);

		if(e)
		{
			printf(
					"Test::cast Error occured: %d\n"
					, e
					);
			return 1;
		}

		if(b.i != -1)
		{
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
		} a = ae2f_RecordMk(
				union __1
				, -1
				);

		union __2 {
			int32_t i; 
			uint8_t v[1]; 
		} b = ae2f_RecordMk(
				union __2
				, 3
				);
		ae2f_err_t e;

		ae2f_MathInt ai, bi;
		ai.sign = 1;
		ai.sz = 8;
		ai.vecbegpoint = 0;

		bi.sign = 1;
		bi.sz = 32;
		bi.vecbegpoint = 0;

		uint8_t* _buf[3];

		__ae2f_MathIntAdd(
				&e
				, 1
				, &ai
				, a.v
				, &bi
				, b.v
				, &bi
				, b.v
				, _buf[0]
				, _buf[1]
				, _buf[2]
				);

		if(e) {
			printf("Test::add Error occurred: %d\n", e);
			return 1;
		}

		if(b.i != 2)
		{
			printf("Test::add Expected 2 but got %d\n", b);
			return 1;
		}
	} puts("test::add has succeed");

	{
		union __1 {
			int8_t i;
			uint8_t v[1];
		} a = ae2f_RecordMk(
				union __1
				, -1
				);

		union __2 {
			int32_t i; 
			uint8_t v[1]; 
		} b = ae2f_RecordMk(
				union __2
				, 3
				);
		ae2f_err_t e;

		ae2f_MathInt ai, bi;
		ai.sign = 1;
		ai.sz = 8;
		ai.vecbegpoint = 0;

		bi.sign = 1;
		bi.sz = 32;
		bi.vecbegpoint = 0;

		uint8_t* _buf[3];

		__ae2f_MathIntSub(
				&e
				, 1
				, &ai
				, a.v
				, &bi
				, b.v
				, &bi
				, b.v
				, _buf[0]
				, _buf[1]
				, _buf[2]
				);

		if(e) {
			printf("Test::subtract Error occurred: %d\n", e);
			return 1;
		}

		if(b.i != -4)
		{
			printf("Test::subtract Expected -4 but got %d\n", b);
			return 1;
		}
	} puts("Test::subtract has succeed.");

	return 0;
}

int cmp() {
	{
		int8_t a = -1;
		ae2f_err_t e;

		ae2f_MathInt ai;
		ai.sign = 1;
		ai.sz = 8;
		ai.vec = (uint8_t*)&a;
		ai.vecbegpoint = 0;

		ae2f_CmpFunRet_t ret;
		if((e = __ae2f_MathIntCmpZero(1, &ai, &ret)))
		{
			printf("Test::cmp0 casted error %d\n", e);
			return 1;
		}

		if(ret != ae2f_CmpFunRet_LISLESSER)
		{
			printf(
					"Test::cmp0 returned unexpected value %d, %d expected."
					, ret
					, ae2f_CmpFunRet_LISLESSER
					);
			return 1;
		}

		a = 0;

		if((e = __ae2f_MathIntCmpZero(1, &ai, &ret)))
		{
			printf("Test::cmp0 casted error %d\n", e);
			return 1;
		}

		if(ret != ae2f_CmpFunRet_EQUAL)
		{
			printf(
					"Test::cmp0 returned unexpected value %d, %d expected."
					, ret
					, ae2f_CmpFunRet_EQUAL
					);
			return 1;
		}

		a = 1;

		if((e = __ae2f_MathIntCmpZero(1, &ai, &ret)))
		{
			printf("Test::cmp0 casted error %d\n", e);
			return 1;
		}

		if(ret != ae2f_CmpFunRet_RISLESSER)
		{
			printf(
					"Test::cmp0 returned unexpected value %d, %d expected.\n"
					, ret
					, ae2f_CmpFunRet_RISLESSER
					);
			return 1;
		}

	} puts("Test::cmp0 has succeed");


	{
		ae2f_err_t e;
		ae2f_CmpFunRet_t ret;

		int8_t a = -1;
		ae2f_MathInt ai;
		ai.sign = 1;
		ai.sz = 8;
		ai.vec = (uint8_t*)&a;
		ai.vecbegpoint = 0; /* Making a number */

		int16_t b = -1;
		ae2f_MathInt bi;
		bi.sign = 1;
		bi.sz = 15;
		bi.vec = (uint8_t*)&b;
		bi.vecbegpoint = 0; /* Making a number */


		if((e = __ae2f_MathIntCmp(1, &ai, &bi, &ret)))
		{
			printf("Test::cmp::equal casted error: %d\n", e);
			return 1;
		}

		if(ret)
		{
			printf(
					"Test::cmp::equal Unexpected value %d, expected %d\n"
					, ret, ae2f_CmpFunRet_EQUAL
					);
			return 1;
		}

		b = 1;
		if((e = __ae2f_MathIntCmp(1, &ai, &bi, &ret)))
		{
			printf("Test::cmp::equal casted error: %d\n", e);
			return 1;
		}

		if(ret >= 0)
		{
			printf("Test::cmp::equal You failed on %d - %d\n", a, b);
			printf(
					"Test::cmp::equal Unexpected value %d, expected %d\n"
					, ret, ae2f_CmpFunRet_LISLESSER
					);
			return 1;
		}

		b = -300;
		if((e = __ae2f_MathIntCmp(1, &ai, &bi, &ret)))
		{
			printf("Test::cmp::equal casted error: %d\n", e);
			return 1;
		}

		if(ret <= 0)
		{

			printf("Test::cmp::equal You failed on %d - %d\n", a, b);
			printf(
					"Test::cmp::equal Unexpected value %d, expected %d\n"
					, ret, ae2f_CmpFunRet_RISLESSER
					);
			return 1;
		}

		a = 50;
		b = 300;

		if((e = __ae2f_MathIntCmp(1, &ai, &bi, &ret)))
		{
			printf("Test::cmp::equal casted error: %d\n", e);
			return 1;
		}


		if(ret != ae2f_CmpFunRet_LISLESSER)
		{
			printf("Test::cmp::equal You failed on %d - %d\n", a, b);
			printf(
					"Test::cmp::equal Unexpected value %d, expected %d\n"
					, ret, ae2f_CmpFunRet_LISLESSER
					);

			return 1;

		}

		a = 3;
		b = 2;

		if((e = __ae2f_MathIntCmp(1, &ai, &bi, &ret)))
		{
			printf("Test::cmp::equal casted error: %d\n", e);
			return 1;
		}


		if(ret != ae2f_CmpFunRet_RISLESSER)
		{
			printf("Test::cmp::equal You failed on %d - %d\n", a, b);
			printf(
					"Test::cmp::equal Unexpected value %d, expected %d\n"
					, ret, ae2f_CmpFunRet_RISLESSER
					);

			return 1;
		}


	} puts("Test::cmp::equal has succeed");

	return 0;
}

static int mul() {
	{
		int8_t a = -3;
		int32_t b = 200;
		uint64_t buf;

		ae2f_err_t e;

		ae2f_MathInt ai, bi;
		ai.sign = 1;
		ai.sz = 8;
		ai.vec = (uint8_t*)&a;
		ai.vecbegpoint = 0;

		bi.sign = 1;
		bi.sz = 32;
		bi.vec = (uint8_t*)&b;
		bi.vecbegpoint = 0;

		e = __ae2f_MathIntMul(
				1
				, &ai
				, &bi
				, &bi
				, (ae2f_MathMem)&buf
				);

		if(e) {
			printf("Test::mul Error occurred: %d\n", e);
			return 1;
		}

		if(b != -600)
		{
			printf("Test::mul Expected -200 but got %d\n", b);
			return 1;
		}
	} puts("Test::mul has succeed");
	return 0;
}

int main() {
	return 
		flip() 
		|| cast() 
		|| add_sub() 
		|| cmp()
		|| mul()
		;
}
