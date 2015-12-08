
#include "NormalF64AVX_TEST.h"

void test::NormalF64AVX_Test::Test_Default_Constructor()
{
	std::printf("NormF64AVX::NormF64AVX() - Default Constructor Test\n");
	auto test_obj = NormF64AVX_Create();
#if PRINT_TO_CONSOLE
	test::Utilities::debug_print(test_obj, "test_obj");
#endif
}

void test::NormalF64AVX_Test::Test_One_Arg_Constructor()
{
	std::printf("NormF64AVX::NormF64AVX(const double) - One Arg Constructor Test\n");
	auto test_obj = NormF64AVX_Create(1.0L);
#if PRINT_TO_CONSOLE
	test::Utilities::debug_print(test_obj, "test_obj");
#endif
}

void test::NormalF64AVX_Test::Test_Quad_Arg_Constructor()
{
	std::printf("NormF64AVX::NormF64AVX(const double, const double, const double, const double) - Quad Arg Constructor Test\n");
	auto test_obj = NormF64AVX_Create(1.0L, 2.0L, 3.0L, std::numeric_limits<double>::quiet_NaN());
#if PRINT_TO_CONSOLE
	test::Utilities::debug_print(test_obj, "test_obj");
#endif
}

void test::NormalF64AVX_Test::Test_StArray_Arg_Constructor()
{
	std::printf("NormF64AVX::NormF64AVX(const double *) - Static Array Arg Constructor Test\n");
	__declspec(align(64)) const double v[] = { 1.0L, 2.0L, 3.0L, std::numeric_limits<double>::quiet_NaN() };
	auto test_obj = NormF64AVX_Create(v);
#if PRINT_TO_CONSOLE
	test::Utilities::debug_print(test_obj, "test_obj");
#endif
}

void test::NormalF64AVX_Test::Test_YMM_Arg_Constructor()
{
	std::printf("NormF64AVX::NormF64AVX(const __m256d) - __m256d Arg Constructor Test\n");
	const __m256d v = { 1.0L, 2.0L, 3.0L, std::numeric_limits<double>::quiet_NaN() };
	auto test_obj = NormF64AVX_Create(v);
#if PRINT_TO_CONSOLE
	test::Utilities::debug_print(test_obj, "test_obj");
#endif
}

void test::NormalF64AVX_Test::Test_YMMi_Arg_Constructor()
{
	std::printf("NormF64AVX::NormF64AVX(const __m256i) - __m256i Arg Constructor Test\n");
	const __m256i v = _mm256_setr_epi64x(1LL, 2LL, 3LL, 0LL);
	auto test_obj = NormF64AVX_Create(v);
#if PRINT_TO_CONSOLE
	test::Utilities::debug_print(test_obj, "test_obj");
#endif
}

void test::NormalF64AVX_Test::Test_XMM_Arg_Constructor()
{
	std::printf("NormF64AVX::NormF64AVX(const __m128d, const __m128d) - __m128d Arg Constructor Test\n");
	const __m128d v0 = { 1.0L, 2.0L };
	const __m128d v1 = { 3.0L, std::numeric_limits<double>::quiet_NaN() };
	auto test_obj = NormF64AVX_Create(v0, v1);
#if PRINT_TO_CONSOLE
	test::Utilities::debug_print(test_obj, "test_obj");
#endif
}

void test::NormalF64AVX_Test::Test_Copy_Constructor()
{
	std::printf("NormF64AVX::NormF64AVX(const mathlib::NormF64AVX) - Copy Constructor Test\n");
	auto ctest_obj = mathlib::NormF64AVX();
	auto test_obj = NormF64AVX_Create(ctest_obj);
#if PRINT_TO_CONSOLE
	test::Utilities::debug_print(test_obj, "test_obj");
#endif
}

void test::NormalF64AVX_Test::Run_Constructor_Tests()
{
	std::printf("Begin mathlib::NormF64AVX - Constructor Tests\n\n");
	
	std::vector<std::function<void()>> v_pfuncs;
	
	
	v_pfuncs.push_back(Test_Default_Constructor);
	v_pfuncs.push_back(Test_One_Arg_Constructor);
	v_pfuncs.push_back(Test_Quad_Arg_Constructor);
	v_pfuncs.push_back(Test_StArray_Arg_Constructor);
	v_pfuncs.push_back(Test_YMM_Arg_Constructor);
	v_pfuncs.push_back(Test_YMMi_Arg_Constructor);
	v_pfuncs.push_back(Test_XMM_Arg_Constructor);
	v_pfuncs.push_back(Test_Copy_Constructor);
	for (const auto &v : v_pfuncs)
		v.operator()();
	
	
	std::printf("Finished mathlib::NormF64AVX - Constructor Tests\n\n");
}

void test::NormalF64AVX_Test::Test_operator_assign()
{
	std::printf("Begin test of NormF64AVX::operator=(const NormF64AVX &) - operator= Test\n\n");
	auto v0 = NormF64AVX_Create(std::numeric_limits<double>::quiet_NaN(), 3.0L, 2.0L, 1.0L);
	auto expected = NormF64AVX_Create(std::numeric_limits<double>::quiet_NaN(), 3.0L, 2.0L, 1.0L);
	mathlib::NormF64AVX actual;
	actual.operator=(v0);
#if ASSERT_EQUAL

	test::Utilities::Assert_Equal(actual.get_m_VecF64(), expected.get_m_VecF64(), std::numeric_limits<double>::epsilon(),
		"NormF64AVX::operator= Equality_Test");

#endif
	std::printf("Finished test of NormF64AVX::operator=(const NormF64AVX &) - operator= Test\n\n");
}

void test::NormalF64AVX_Test::Test_operator_add_assign()
{
	std::printf("Begin test of NormF64AVX::operator+=(const NormF64AVX &) - operator+= Test\n\n");
	auto v0 = NormF64AVX_Create(std::numeric_limits<double>::quiet_NaN(), 3.0L, 2.0L, 1.0L);
	auto v1 = NormF64AVX_Create(std::numeric_limits<double>::quiet_NaN(), 3.0L, 2.0L, 1.0L);
	auto expected = NormF64AVX_Create(std::numeric_limits<double>::quiet_NaN(), 6.0L, 4.0L, 2.0L);
	mathlib::NormF64AVX actual;
	actual.operator=(v0.operator+=(v1));
#if ASSERT_EQUAL
	test::Utilities::Assert_Equal(actual.get_m_VecF64(), expected.get_m_VecF64(), std::numeric_limits<double>::epsilon(),
		"NormF64AVX::operator+= Equality_Test");
#endif
	std::printf("Finished test of NormF64AVX::operator+=(const NormF64AVX &) - operator+= Test\n\n");
}

void test::NormalF64AVX_Test::Test_operator_sub_assign()
{

}

/*void test::NormalF64AVX_Test::Run_Constructor_Tests2()
{
	std::printf("Begin NormF64AVX Constructor Tests\n");
	std::printf("Calling test methods indirectly\n");
	FPTR fptr_array[] = {
		&Test_Default_Constructor,
		&Test_One_Arg_Constructor,
		&Test_Quad_Arg_Constructor,
		&Test_StArray_Arg_Constructor,
		&Test_YMM_Arg_Constructor,
		&Test_YMMi_Arg_Constructor,
		&Test_XMM_Arg_Constructor,
		&Test_Copy_Constructor
	};
	for (auto i = 0; i != 8; ++i)
	{
		fptr_array[i]();
	}
	std::printf("Finished NormF64AVX Constructor Tests\n");
}*/

void test::NormalF64AVX_Test::Test_apply()
{
	std::printf("Begin test of NormF64AVX::apply(Functions...) \n");
	auto test_obj = NormF64AVX_Create();
	const double arg = 0.5L;
	// Proper way of calling variadic templates: lambdas as a template argument.
	test_obj.apply([=]()->double
	{
		return std::sin(arg);
	}, [=]()->double
	{
		return std::cos(arg);
	}, [=]()->double
	{
		return std::tan(arg);
	});
	test::Utilities::debug_print(test_obj, "test_obj");
	std::printf("Finished test of NormF64AVX::apply(Functions...) \n");
}

void test::NormalF64AVX_Test::Test_apply_to_Vec1D()
{
	std::printf("Begin test of variadic templated NormF64AVX::apply()\n");
	std::vector<mathlib::NormF64AVX> v1d(100, mathlib::NormF64AVX());
	std::printf("Allocating std::vector<mathlib::NormF64AVX> containing: %d elements\n", v1d.size());
		for (auto i = 0; i != v1d.size(); ++i)
		{
			v1d.operator[](i).apply([]()->double
			{  
				return test::Utilities::generate_rand_value<double>(0.0L, 1.0L);
			}, []()->double
			{  
				return test::Utilities::generate_rand_value<double>(0.0L, 1.0L);
			}, []()->double
			{  
				return test::Utilities::generate_rand_value<double>(0.0L, 1.0L);
			});
		}
		for (auto i = 0; i != v1d.size(); ++i)
			test::Utilities::debug_print(v1d.operator[](i), "v1d.operator[](i).obj_test");
		std::printf("Finished test of variadic templated NormF64AVX::apply()\n");

}

void test::NormalF64AVX_Test::Run_Member_Functions_Test()
{
	std::printf("Begin test of NormF64AVX class member functions\n\n");
	
	std::vector<std::function<void(void)>> v_pfunc;
	v_pfunc.push_back(Test_apply);
	v_pfunc.push_back(Test_apply2);
	v_pfunc.push_back(Test_apply_to_Vec1D);
	for (const auto &v : v_pfunc)
		v.operator()();
	

}

void test::NormalF64AVX_Test::Test_apply2()
{
	std::vector<mathlib::NormF64AVX> v1D(100, mathlib::NormF64AVX());
	 mathlib::NormF64AVX::apply2(v1D, []()->double
	{
		return test::Utilities::generate_rand_value<double>(0.0L, 1.0L);
	},[]()->double
	{
		return test::Utilities::generate_rand_value<double>(0.0L, 1.0L);
	}, []()->double
	{
		return test::Utilities::generate_rand_value<double>(0.0L, 1.0L);
	});
	for (auto &v : v1D)
		std::printf("x=%.15f,y=%.15f,z=%.15f,w=%.15f\n", v.get_m_VecF64().m256d_f64[0], v.get_m_VecF64().m256d_f64[1], v.get_m_VecF64().m256d_f64[2], v.get_m_VecF64().m256d_f64[3]);
}

mathlib::NormF64AVX  test::NormalF64AVX_Test::NormF64AVX_Create()
{
	return mathlib::NormF64AVX();
}

mathlib::NormF64AVX  test::NormalF64AVX_Test::NormF64AVX_Create(const double arg)
{
	return mathlib::NormF64AVX(arg);
}

mathlib::NormF64AVX  test::NormalF64AVX_Test::NormF64AVX_Create(const double s0, const double s1, const double s2, const double s3)
	
{
	return mathlib::NormF64AVX(s0, s1, s2, s3);
}

mathlib::NormF64AVX  test::NormalF64AVX_Test::NormF64AVX_Create(const double v[4])
{
	return mathlib::NormF64AVX(v);
}

mathlib::NormF64AVX  test::NormalF64AVX_Test::NormF64AVX_Create(const __m256d v)
{
	return mathlib::NormF64AVX(v);
}

mathlib::NormF64AVX  test::NormalF64AVX_Test::NormF64AVX_Create(const __m256i v)
{
	return mathlib::NormF64AVX(v);
}

mathlib::NormF64AVX  test::NormalF64AVX_Test::NormF64AVX_Create(const __m128d v0, const __m128d v1)
{
	return mathlib::NormF64AVX(v0, v1);
}

mathlib::NormF64AVX  test::NormalF64AVX_Test::NormF64AVX_Create(const mathlib::NormF64AVX &obj)
{
	return mathlib::NormF64AVX(obj);
}