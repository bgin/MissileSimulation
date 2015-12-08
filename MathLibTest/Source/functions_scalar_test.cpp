
#include "functions_scalar_test.h"

void test::FunctionsScalarTest::Test_fastsin()
{
	
	std::printf("Floating-Point Double Precision Argument Test of fastsin()\n");
	double rand_arg1 = test::FunctionsScalarTest::random_value<double>(0.0L, 1.0L);
	std::enable_if<std::is_floating_point<double>::value, double>::type s1 = mathlib::FastScalarFunctions<double>::fastsin(rand_arg1);
	std::printf("fastsin(%.15f) = %.15f\n",rand_arg1 ,s1);
	std::printf("Floating-Point Single Precision Argument Test\n");
	float rand_arg2 = test::FunctionsScalarTest::random_value<float>(0.f, 1.f);
	std::enable_if<std::is_floating_point<float>::value, float>::type s2 = mathlib::FastScalarFunctions<float>::fastsin(rand_arg2);
	std::printf("fastsin(%.9f) = %.9f\n",rand_arg2, s2);
	
	
}

void test::FunctionsScalarTest::Test_fastcot()
{
	std::printf("Floating-Point Double Precision Argument Test of fastcot()\n");
	double rand_arg1 = test::FunctionsScalarTest::random_value<double>(0.0L, 3.14L);
	std::enable_if<std::is_floating_point<double>::value, double>::type s1 = mathlib::FastScalarFunctions<double>::fastcot(rand_arg1);
	std::printf("fastcot(%.15f) = %.15f\n", rand_arg1, s1);
	std::printf("Floating-Point Single Precision Argument Test\n");
	float rand_arg2 = test::FunctionsScalarTest::random_value<float>(0.f, 3.14f);
	std::enable_if<std::is_floating_point<float>::value, float>::type s2 = mathlib::FastScalarFunctions<float>::fastcot(rand_arg2);
	std::printf("fastcot(%.9f) = %.9f\n",rand_arg2, s2);
}

void test::FunctionsScalarTest::Test_fastcos()
{
	std::printf("Floating-Point Double Precision Argument Test of fastcos()\n");
	double rand_arg1 = test::FunctionsScalarTest::random_value<double>(0.0L, 1.57L);
	std::enable_if<std::is_floating_point<double>::value, double>::type s1 = mathlib::FastScalarFunctions<double>::fastcos(rand_arg1);
	std::printf("fastcos(%.15f) = %.15f\n", rand_arg1, s1);
	std::printf("Floating-Point Single Precision Argument Test\n");
	float rand_arg2 = test::FunctionsScalarTest::random_value<float>(0.f, 1.57f);
	std::enable_if<std::is_floating_point<float>::value, float>::type  s2  =   mathlib::FastScalarFunctions<float>::fastcos(rand_arg2);
	std::printf("fastcos(%.9f) = %.9f\n", rand_arg2, s2);
}

void test::FunctionsScalarTest::Run_Tests()
{
	test::FunctionsScalarTest::Test_fastsin();
	test::FunctionsScalarTest::Test_fastcos();
	test::FunctionsScalarTest::Test_fastcot();
}


template<typename _T> _T test::FunctionsScalarTest::random_value(const _T& lo, const _T& hi)
{
#if defined _DEBUG
	_ASSERTE((std::fabs(hi)) > (std::fabs(lo)));
#else
	if(std::fabs(hi) < std::fabs(lo))
	{
		throw std::runtime_error("FATAL ERROR in FunctionScalarTest::random_value - hi < lo\n");
	}
#endif

	std::uniform_real_distribution<_T> ud(lo, hi);
	std::knuth_b kb;
	return ud.operator()(kb);
}