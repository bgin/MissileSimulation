
#include "VectorF64AVX_TEST.h"

 void test::VectorF64AVX_Test::Test_Default_Constructor()
{
	 std::printf("VectorF64AVX::VectorF64AVX() #Test:\n\n");
	 mathlib::VecF64AVX test_obj1 = VecF64AVX_Create();
#if PRINT_TO_CONSOLE
	 test::Utilities::debug_print(test_obj1,"test_obj1");
#endif
}

 void test::VectorF64AVX_Test::Test_Static_Array_Arg_Constructor()
 {
	 std::printf("VectorF64AVX::VectorF64AVX(const double [4]) #Test:\n\n");
	 __declspec(align(64)) double arg[4] = { 1.0L, 1.0L, 1.0L, 0.0L };
	 auto &ref = arg;
	 mathlib::VecF64AVX test_obj2 = VecF64AVX_Create(ref);
#if PRINT_TO_CONSOLE
	 test::Utilities::debug_print(test_obj2,"test_obj2");
#endif
 }

 void test::VectorF64AVX_Test::Test_One_Arg_Constructor()
 {
	 std::printf("VectorF64AVX::VectorF64AVX(const double) #Test:\n\n");
	 const double arg = 1.0L;
	 mathlib::VecF64AVX test_obj3 = VecF64AVX_Create(arg);
#if PRINT_TO_CONSOLE
	 test::Utilities::debug_print(test_obj3,"test_obj3");
#endif
 }

 void test::VectorF64AVX_Test::Test_Four_Arg_Constructor()
 {
	 std::printf("VectorF64AVX::VectorF64AVX(const double, const double, const double, const double) #Test:\n\n");
	 const double arg1 = 1.0L; const double arg2 = 1.0L; const double arg3 = 1.0L; const double arg4 = 0.0L;
	 mathlib::VecF64AVX test_obj4 = VecF64AVX_Create(arg1,arg2,arg3,arg4);
#if PRINT_TO_CONSOLE
	 test::Utilities::debug_print(test_obj4,"test_obj4");
#endif
 }

 void test::VectorF64AVX_Test::Test_YMM_Arg_Constructor()
 {
	 std::printf("VectorF64AVX::VectorF64AVX(const __m256d) #Test:\n\n");
	 const __m256d xmm0 = { 1.0L, 1.0L, 1.0L, 0.0L };
	 mathlib::VecF64AVX test_obj5 = VecF64AVX_Create(xmm0);
#if PRINT_TO_CONSOLE
	 test::Utilities::debug_print(test_obj5,"test_obj5");
#endif
 }

 void test::VectorF64AVX_Test::Test_YMMi_Arg_Constructor()
 {
	 std::printf("VectorF64AVX::VectorF64AVX(const __m256i) #Test:\n\n");
	 const __m256i xmm0 = _mm256_setr_epi64x(1LL, 1LL, 1LL, 0LL);
	 mathlib::VecF64AVX test_obj6 = VecF64AVX_Create(xmm0);
#if PRINT_TO_CONSOLE
	 test::Utilities::debug_print(test_obj6,"test_obj6");
#endif
 }

 void test::VectorF64AVX_Test::Test_Copy_Constructor()
 {
	 std::printf("VectorF64AVX::VectorF64AVX(const VectorF64AVX &) #Test:\n\n");
	 const double arg = 1.0L;
	 const mathlib::VecF64AVX test_obj7 = VecF64AVX_Create(arg);
	 mathlib::VecF64AVX test_obj8 = VecF64AVX_Create(test_obj7);
#if PRINT_TO_CONSOLE
	 test::Utilities::debug_print(test_obj7,"test_obj7");
	 test::Utilities::debug_print(test_obj8,"test_obj8");
#endif
 }

 void test::VectorF64AVX_Test::Test_XMM_Arg_Constructor()
 {
	 std::printf("VectorF64AVX::VectorF64AVX(const __m128d, const __m128d) #Test:\n\n");
	 const __m128d xmm0 = { 1.0L, 1.0L };
	 const __m128d xmm1 = { 1.0L, 0.0L };
	 mathlib::VecF64AVX test_obj9 = VecF64AVX_Create(xmm0,xmm1);
#if PRINT_TO_CONSOLE
	 test::Utilities::debug_print(test_obj9,"test_obj9");
#endif
 }

 void test::VectorF64AVX_Test::Run_Constructor_Tests()
 {
	 std::printf("VecF64AVX Constructor Tests started\n");
	 Test_Default_Constructor();
	 Test_One_Arg_Constructor();
	 Test_Four_Arg_Constructor();
	 Test_Static_Array_Arg_Constructor();
	 Test_XMM_Arg_Constructor();
	 Test_YMM_Arg_Constructor();
	 Test_YMMi_Arg_Constructor();
	 Test_Copy_Constructor();
	 std::printf("VecF64AVX Constructor Tests finished\n");
 }

 void test::VectorF64AVX_Test::Test_Operator_Assignment()
 {
	 std::printf("VecF64AVX::operator=(const VecF64AVX &) #Test:\n\n");
	 mathlib::VecF64AVX test_obj1 = VecF64AVX_Create();
	 mathlib::VecF64AVX test_obj2 = VecF64AVX_Create(test::Utilities::generate_rand_value<double>(10.0, 20.0));
	 test_obj1.operator=(test_obj2);
#if PRINT_TO_CONSOLE
	 test::Utilities::debug_print(test_obj1,"test_obj1");
	 test::Utilities::debug_print(test_obj2,"test_obj2");
#endif
 }

 void test::VectorF64AVX_Test::Test_Operator_Add_Assign()
 {
	 std::printf("VecF64AVX::operator+=(const VecF64AVX &) #Test:\n\n");
	 mathlib::VecF64AVX test_obj1 = VecF64AVX_Create(1.0L, 1.0L, 1.0L, 0.0L);
	 mathlib::VecF64AVX test_obj2 = VecF64AVX_Create(1.0L, 1.0L, 1.0L, 0.0L);
	 mathlib::VecF64AVX test_obj3;
	 test_obj3.operator=(test_obj1.operator+=(test_obj2));
#if PRINT_TO_CONSOLE
	 
	 test::Utilities::debug_print(test_obj1,"test_obj1");
	 test::Utilities::debug_print(test_obj2,"test_obj2");
	 test::Utilities::debug_print(test_obj3,"test_obj3");
#endif
#if ASSERT_EQUAL
	 test::Utilities::Assert_Equal(test_obj3.get_m_VecF64(), test_obj2.get_m_VecF64(), std::numeric_limits<double>::epsilon(), "VecF64AVX::operator+=()EQUALITY_TEST");
#endif
 }

 void test::VectorF64AVX_Test::Test_Operator_Add_AssignS()
 {
	 std::printf("VecF64AVX::operator+=(const double) Test\n\n");
	 mathlib::VecF64AVX test_obj1 = VecF64AVX_Create(1.0L, 1.0L, 1.0L, 0.0L);
	 mathlib::VecF64AVX test_obj2;
	 test_obj2.operator=(test_obj1.operator+=(1.0L));
#if PRINT_TO_CONSOLE
	 test::Utilities::debug_print(test_obj1, "test_obj1");
	 test::Utilities::debug_print(test_obj2, "test_obj2");
#endif
 }

 void test::VectorF64AVX_Test::Test_Operator_Sub_Assign()
 {
	 std::printf("VecF64AVX::operator-=(const VecF64AVX &) #Test:\n\n");
	 mathlib::VecF64AVX test_obj1 = VecF64AVX_Create(1.0L, 1.0L, 1.0L, 0.0L);
	 mathlib::VecF64AVX test_obj2 = VecF64AVX_Create(2.0L, 2.0L, 2.0L, 0.0L);
	 mathlib::VecF64AVX test_obj3;
	 test_obj3.operator=(test_obj2.operator-=(test_obj1));
#if ASSERT_EQUAL
	 test::Utilities::Assert_Equal(test_obj3.get_m_VecF64(), test_obj1.get_m_VecF64(), std::numeric_limits<double>::epsilon(), "VecF64AVX::operator-=()EQUALITY_TEST");
#endif
 }

 void test::VectorF64AVX_Test::Test_Operator_Sub_AssignS()
 {
	 std::printf("VecF64AVX::operator-=(const double) #Test:\n\n");
	 const __m256d arg = { 1.0L, 1.0L, 1.0L, 0.0L };
	 mathlib::VecF64AVX test_obj1 = VecF64AVX_Create(2.0L);
	 mathlib::VecF64AVX test_obj2;
	 test_obj2.operator=(test_obj1.operator-=(arg));
#if ASSERT_EQUAL
	 test::Utilities::Assert_Equal(test_obj2.get_m_VecF64(), arg, std::numeric_limits<double>::epsilon(), "VecF64AVX::operator-=()EQUALITY_TEST");
#endif
 }

 void test::VectorF64AVX_Test::Test_Operator_Mul_Assign()
 {
	 std::printf("VecF64AVX::operator*=(const VecF64AVX &) #Test\n\n");
	 mathlib::VecF64AVX  test_obj1 = VecF64AVX_Create(1.0L, 2.0L, 3.0L, 0.0L);
	 mathlib::VecF64AVX  test_obj2 = VecF64AVX_Create(2.0L, 2.0L, 2.0L, 0.0L);
	 mathlib::VecF64AVX  test_obj3;
	 test_obj3.operator=(test_obj2.operator*=(test_obj1));
#if ASSERT_EQUAL
	 test::Utilities::Assert_Equal(test_obj3.get_m_VecF64(), test_obj2.get_m_VecF64(), std::numeric_limits<double>::epsilon(), "VecF64AVX::operator*=(VecF64AVX &)EQUALITY_TEST");
#endif
 }

 void test::VectorF64AVX_Test::Test_Operator_Mul_AssignS()
 {
	 std::printf("VecF64AVX::operator*=(const double) #Test:\n\n");
	 const double arg = 1.0L;
	 mathlib::VecF64AVX test_obj1 = VecF64AVX_Create(0.0L, 2.0L, 2.0L, 2.0L);
	 mathlib::VecF64AVX test_obj2;
	 test_obj2.operator=(test_obj1.operator*=(arg));
#if ASSERT_EQUAL
	 test::Utilities::Assert_Equal(test_obj2.get_m_VecF64(), test_obj1.get_m_VecF64(), std::numeric_limits<double>::epsilon(), "VecF64AVX::operator*=(double)EQUALITY_TEST");
#endif
 }

 void test::VectorF64AVX_Test::Test_Operator_Div_Assign()
 {
	 std::printf("VecF64AVX::operator/=(const VecF64AVX &) #Test:\n\n");
	 mathlib::VecF64AVX test_obj1 = VecF64AVX_Create(1.0L, 2.0L, 2.0L, 2.0L);
	 mathlib::VecF64AVX test_obj2 = VecF64AVX_Create(1.0L, 8.0L, 4.0L, 2.0L);
	 mathlib::VecF64AVX test_obj3;
	 test_obj3.operator=(test_obj2.operator/=(test_obj1));
#if ASSERT_EQUAL
	 test::Utilities::Assert_Equal(test_obj3.get_m_VecF64(), test_obj2.get_m_VecF64(), std::numeric_limits<double>::epsilon(), "VecF64AVX::operator/=(VecF64AVX &)EQUALITY_TEST");
#endif
 }

 void test::VectorF64AVX_Test::Test_Operator_Div_AssignS()
 {
	 std::printf("VecF64AVX::operator/=(const double) #Test:\n\n");
	 const double arg = 2.0L;
	 mathlib::VecF64AVX test_obj1 = VecF64AVX_Create(1.0L, 8.0L, 4.0L, 2.0L);
	 mathlib::VecF64AVX test_obj2;
	 test_obj2.operator=(test_obj1.operator/=(arg));
#if ASSERT_EQUAL
	 test::Utilities::Assert_Equal(test_obj2.get_m_VecF64(), test_obj1.get_m_VecF64(), std::numeric_limits<double>::epsilon(), "VecF64AVX::operator/=(double)EQUALITY_TEST");
#endif
 }

 void test::VectorF64AVX_Test::Test_Operator_Equal()
 {
	 std::printf("VecF64AVX::operator==(const VecF64AVX &) #Test:\n\n");
	 mathlib::VecF64AVX test_obj1 = VecF64AVX_Create(0.0L, 1.0L, 1.0L, 1.0L);
	 mathlib::VecF64AVX test_obj2 = VecF64AVX_Create(0.0L, 1.0L, 1.0L, 1.0L);
	 mathlib::VecF64AVX test_obj3;
	 test_obj3.operator=(test_obj2.operator==(test_obj1));
	 for (auto i = 0; i != test::Utilities::vec_length; ++i)
	 {
		 if (test_obj3.get_m_VecF64().m256d_f64[i])
		 {
			 std::printf("Objects are Equal\n");
			 std::printf("test_obj1=%.15f    |       test_obj2=%.15f\n", test_obj1.get_m_VecF64().m256d_f64[i], test_obj2.get_m_VecF64().m256d_f64[i]);
			 std::printf("test_obj3=%d\n", test_obj3.get_m_VecF64().m256d_f64[i]);
		 }
		 else
		 {
			 std::printf("Objects are not Equal\n");
			 std::printf("test_obj1=%.15f    |       test_obj2=%.15f\n", test_obj1.get_m_VecF64().m256d_f64[i], test_obj2.get_m_VecF64().m256d_f64[i]);
			 std::printf("test_obj3=%d\n", test_obj3.get_m_VecF64().m256d_f64[i]);
		 }
	 }
 }

 void test::VectorF64AVX_Test::Test_Operator_EqualS()
 {
	 std::printf("VecF64AVX::operator==(const double) #Test:\n\n");
	 mathlib::VecF64AVX test_obj1 = VecF64AVX_Create(1.0L);
	 const double test_val = 1.0L;
	 mathlib::VecF64AVX test_obj2; // Ones-filled object, result of call to _mm256_cmp_pd();
	 test_obj2.operator=(test_obj1.operator==(test_val));
	 for (auto i = 0; i != test::Utilities::vec_length; ++i)
	 {
		 if (test_obj2.get_m_VecF64().m256d_f64[i])
		 {
			 std::printf("Objects are Equal\n");
			 std::printf("test_obj1=%.15f    |       test_val=%.15f\n", test_obj1.get_m_VecF64().m256d_f64[i], test_val);
			 std::printf("test_obj2=%d\n", test_obj2.operator[](i));
		 }
		 else
		 {
			 std::printf("Objects are not Equal\n");
			 std::printf("test_obj1=%.15f    |       test_val=%.15f\n", test_obj1.get_m_VecF64().m256d_f64[i], test_val);
			 std::printf("test_obj2=%d\n", test_obj2.operator[](i));
		 }
	 }
 }

 void test::VectorF64AVX_Test::Test_Operator_InEqual()
 {
	 std::printf("VecF64AVX::operator!=(const VecF64AVX &) #Test:\n\n");
	 auto test_obj1 = VecF64AVX_Create(std::numeric_limits<double>::quiet_NaN(), 1.0L, 2.0L, 3.0L);
	 auto test_obj2 = VecF64AVX_Create(std::numeric_limits<double>::quiet_NaN(), 1.5L, 2.5L, 3.5L);
	 mathlib::VecF64AVX test_obj3;
	 test_obj3.operator=(test_obj1.operator!=(test_obj2));
	 for (auto i = 0; i != test::Utilities::vec_length; ++i)
	 {
		 if (!(test_obj3.get_m_VecF64().m256d_f64[i]))
		 {
			 std::printf("Objects are not Equal\n");
			 std::printf("test_obj1=%.15f    |     test_obj2=%.15f\n", test_obj1.get_m_VecF64().m256d_f64[i], test_obj2.get_m_VecF64().m256d_f64[i]);
			 std::printf("Dumping test_obj3=%d\n", test_obj3.get_m_VecF64().m256d_f64[i]);
		 }
		 else
		 {
			 std::printf("Objects are Equal\n"); 
			 // Expected equality of NaN components.
			 std::printf("test_obj1=%.15f    |     test_obj2=%.15f\n", test_obj1.get_m_VecF64().m256d_f64[i], test_obj2.get_m_VecF64().m256d_f64[i]);
			 std::printf("Dumping test_obj3=%d\n", test_obj3.get_m_VecF64().m256d_f64[i]);
		 }
	 }
 }

 void test::VectorF64AVX_Test::Test_Operator_InEqualS()
 {
	 std::printf("VecF64AVX::operator!=(const double) #Test:\n\n");
	 const double arg = 0.5L;
	 auto test_obj1 = VecF64AVX_Create(std::numeric_limits<double>::quiet_NaN(), 1.0L, 2.0L, 3.0L);
	 mathlib::VecF64AVX test_obj2;
	 mathlib::VecF64AVX test_obj3 = VecF64AVX_Create();
	 test_obj3.apply([=](const double)->double
	 {   //<lambda []double (double)->double>
		 return std::sin(arg);
	 },arg);
	 test_obj3.apply([=]()->double
	 {
		 return std::sin(arg);
	 }, [=]()->double
	 {
		 return std::cos(arg);
	 }, [=]()->double
	 {
		 return std::tan(arg);
	 });
	 test_obj2.operator=(test_obj1.operator!=(arg));
	 for (auto i = 0; i != test::Utilities::vec_length; ++i)
	 {
		 if (!(test_obj2.get_m_VecF64().m256d_f64[i]))
		 {
			 std::printf("Objects are not Equal\n");
			 std::printf("test_obj1=%.15f    |     arg=%.15f\n", test_obj1.get_m_VecF64().m256d_f64[i], arg);
			 std::printf("Dumping test_obj2=%d\n", test_obj2.get_m_VecF64().m256d_f64[i]);
		 }
		 else
		 {
			 std::printf("Objects are Equal\n");
			 std::printf("test_obj1=%.15f    |     arg=%.15f\n", test_obj1.get_m_VecF64().m256d_f64[i], arg);
			 std::printf("Dumping test_obj2=%d\n", test_obj2.get_m_VecF64().m256d_f64[i]);
		 }
	 }
 }

 void test::VectorF64AVX_Test::Run_Operator_Tests()
 {
	 std::printf("VecF64AVX operator tests started\n\n");
	 Test_Operator_Add_Assign();
	 Test_Operator_Sub_Assign();
	 Test_Operator_Sub_AssignS();
	 Test_Operator_Mul_Assign();
	 Test_Operator_Mul_AssignS();
	 Test_Operator_Div_Assign();
	 Test_Operator_Div_AssignS();
	 Test_Operator_Equal();
	 Test_Operator_EqualS();
	 Test_Operator_InEqual();
	 Test_Operator_InEqualS();
	 std::printf("VecF64AVX operator tests finished\n\n");
 }

 // Static operator test implementation.

 void test::VectorF64AVX_Test::Test_Static_Operator_Add()
 {
	 std::printf("static VecF64AVX::operator+(__m256d,__m256d) #Test:\n\n");
	 const __m256d addend1 = { std::numeric_limits<double>::quiet_NaN(), 3.0L, 2.0L, 1.0L };
	 const __m256d addend2 = { std::numeric_limits<double>::quiet_NaN(), 3.0L, 2.0L, 1.0L };
	 const __m256d expected = { std::numeric_limits<double>::quiet_NaN(), 6.0L, 4.0L, 2.0L };
	 __m256d actual;
	actual = mathlib::VecF64AVX::operator+(addend1, addend2);
#if ASSERT_EQUAL
	test::Utilities::Assert_Equal(actual, expected, std::numeric_limits<double>::epsilon(), "VecF64AVX::operator+()EQUALITY_TEST");
#endif
 }

 void test::VectorF64AVX_Test::Test_Static_Operator_Add_S()
 {
	 std::printf("static VecF64AVX::operator+(const double, const __m256d) #Test:\n\n");
	 
	 const __m256d addend1 = { std::numeric_limits<double>::quiet_NaN(), 3.0L,2.0L,1.0L };
	 const double addend2 = 0.5L;
	 const __m256d expected = { std::numeric_limits<double>::quiet_NaN(), 3.5L, 2.5L, 1.5L };
	 __m256d actual = mathlib::VecF64AVX::operator+(addend2, addend1);
#if ASSERT_EQUAL
	 test::Utilities::Assert_Equal(actual, expected, std::numeric_limits<double>::epsilon(), "VecF64AVX::operator+()EQUALITY_TEST");
#endif
 }

 void test::VectorF64AVX_Test::Test_Static_Operator_Sub()
 {
	 std::printf("static VecF64AVX::operator-(const __m256d, const __m256d) #Test:\n\n");
	 const __m256d subtrahend1 = { std::numeric_limits<double>::quiet_NaN(), 1.0L, 1.0L, 1.0L };
	 const __m256d subtrahend2 = { std::numeric_limits<double>::quiet_NaN(), 3.0L, 3.0L, 3.0L };
	 const __m256d expected = { std::numeric_limits<double>::epsilon(), 2.0L, 2.0L, 2.0L };
	 __m256d actual = mathlib::VecF64AVX::operator-(subtrahend2, subtrahend1);
#if ASSERT_EQUAL
	 test::Utilities::Assert_Equal(expected, actual, std::numeric_limits<double>::epsilon(), "VecF64AVX::operator-()EQUALITY_TEST");
#endif
 }

 void test::VectorF64AVX_Test::Test_Static_Operator_Sub_S()
 {
	 std::printf("static VecF64AVX::operator-(const double, const __m256d) #Test:\n\n");
	 const __m256d subtrahend1 = { std::numeric_limits<double>::quiet_NaN(), 1.0L, 1.0L, 1.0L };
	 const double subtrahend2 = 3.0;
	 const __m256d expected = { std::numeric_limits<double>::quiet_NaN(), 2.0L, 2.0L, 2.0L };
	 __m256d actual = mathlib::VecF64AVX::operator-(subtrahend2, subtrahend1);
#if ASSERT_EQUAL
	 test::Utilities::Assert_Equal(actual, expected, std::numeric_limits<double>::epsilon(), "VecF64AVX::operator-()EQUALITY_TEST");
#endif
 }

 void test::VectorF64AVX_Test::Test_Static_Operator_Mul()
 {
	 std::printf("static VecF64AVX::operator*(const __m256d, const __m256d) #Test:\n\n");
	 const __m256d multiplicant = { std::numeric_limits<double>::quiet_NaN(), 2.0L, 2.0L, 2.0L };
	 const __m256d multiplicant2 = { std::numeric_limits<double>::quiet_NaN(), 2.0L, 2.0L, 2.0L };
	 const __m256d expected = { std::numeric_limits<double>::quiet_NaN(), 4.0L, 4.0L, 4.0L };
	 __m256d actual = mathlib::VecF64AVX::operator*(multiplicant2, multiplicant);
#if ASSERT_EQUAL
	 test::Utilities::Assert_Equal(actual, expected, std::numeric_limits<double>::epsilon(), "VecF64AVX::operator*()EQUALITY_TEST");
#endif
 }

 void test::VectorF64AVX_Test::Test_Static_Operator_Mul_S()
 {
	 std::printf("static VecF64AVX::operator*(const double, const __m256d) #Test:\n\n");
	 const __m256d multiplicant1 = { std::numeric_limits<double>::quiet_NaN(), 2.0L, 2.0L, 2.0L };
	 const double multiplicant2 = 2.0L;
	 const __m256d expected = { std::numeric_limits<double>::quiet_NaN(), 4.0L, 4.0L, 4.0L };
	 __m256d actual = mathlib::VecF64AVX::operator*(multiplicant2, multiplicant1);
	
#if ASSERT_EQUAL
	 test::Utilities::Assert_Equal(actual, expected, std::numeric_limits<double>::epsilon(), "VecF64AVX::operator*()EQUALITY_TEST");
#endif
 }

 void test::VectorF64AVX_Test::Test_Static_Operator_Div()
 {
	 std::printf("static VecF64AVX::operator/(const __m256d, const __m256d) #Test:\n\n");
	 const __m256d divident = { std::numeric_limits<double>::quiet_NaN(), 2.0L, 2.0L, 2.0L };
	 const __m256d divisor = { std::numeric_limits<double>::quiet_NaN(), 4.0L, 4.0L, 4.0L };
	 const __m256d expected = { std::numeric_limits<double>::quiet_NaN(), 2.0L, 2.0L, 2.0L };
	 __m256d actual = mathlib::VecF64AVX::operator/(divisor, divident);
#if ASSERT_EQUAL
	 test::Utilities::Assert_Equal(actual, expected, std::numeric_limits<double>::epsilon(), "VecF64AVX::operator/()EQUALITY_TEST");
#endif
 }

 void test::VectorF64AVX_Test::Test_Static_Operator_Div_S()
 {
	 std::printf("static VecF64AVX::operator/(const double, const __m256d) #Test:\n\n");
	 const __m256d divident = { std::numeric_limits<double>::quiet_NaN(), 2.0L, 2.0L, 2.0L };
	 const double divisor = 4.0L;
	 const __m256d expected = { std::numeric_limits<double>::quiet_NaN(), 2.0L, 2.0L, 2.0L };
	 __m256d actual = mathlib::VecF64AVX::operator/(divisor, divident);
#if ASSERT_EQUAL
	 test::Utilities::Assert_Equal(actual, expected, std::numeric_limits<double>::epsilon(), "VecF64AVX::operator/()EQUALITY_TEST");
#endif
 }

 void test::VectorF64AVX_Test::Test_Static_Operator_Equal()
 {
	 std::printf("static VecF64AVX::operator==(const __m256d, const __m256d) #Test:\n\n");
	 const __m256d operand1 = { std::numeric_limits<double>::quiet_NaN(), 1.0L, 1.0L, 1.0L };
	 const __m256d operand2 = { std::numeric_limits<double>::quiet_NaN(), 1.0L, 1.0L, 1.0L };
	 __m256d result = mathlib::VecF64AVX::operator==(operand1, operand2);
	 for (auto i = 0; i != test::Utilities::vec_length; ++i)
	 {
		 if (result.m256d_f64[i])
		 {
			 std::printf("Vectors are Equal\n");
			 std::printf("Dumping operand1=%.15f    |       Dumping operand2=%.15f\n", operand1.m256d_f64[i], operand2.m256d_f64[i]);
			 std::printf("vector of results=%d\n", result.m256d_f64[i]);
		 }
		 else
		 {
			 std::printf("Vectors are not Equal\n");
			 std::printf("Dumping operand1=%.15f    |       Dumping operand2=%.15f\n", operand1.m256d_f64[i], operand2.m256d_f64[i]);
			 std::printf("vector of results=%d\n", result.m256d_f64[i]);
		 }
	 }
 }

 void test::VectorF64AVX_Test::Test_Static_Operator_EqualS()
 {
	 std::printf("static VecF64AVX::operator==(const double, const __m256d) #Test:\n\n");
	 const double operand1 = 1.0L;
	 const __m256d operand2 = { std::numeric_limits<double>::quiet_NaN(), 1.0L, 1.0L, 1.0L };
	 __m256d result = mathlib::VecF64AVX::operator==(operand1, operand2);
	 for (auto i = 0; i != test::Utilities::vec_length; ++i)
	 {
		 if (result.m256d_f64[i])
		 {
			 std::printf("operand1 and operand2 component-wise are equal\n");
			 std::printf("Dumping... operand1=%.15f   |     Dumping... operand2=%.15f\n", operand1, operand2.m256d_f64[i]);
			 std::printf("Dumping vector of results=%d\n", result.m256d_f64[i]);
		 }
		 else
		 {
			 std::printf("operand1 and operand2 component-wise are not equal\n");
			 std::printf("Dumping... operand1=%.15f   |     Dumping... operand2=%.15f\n", operand1, operand2.m256d_f64[i]);
			 std::printf("Dumping vector of results=%d\n", result.m256d_f64[i]);
		 }
	 }
 }

 void test::VectorF64AVX_Test::Test_Static_Operator_InEqual()
 {
	 std::printf("static VecF64AVX::operator!=(const __m256d, const __m256d) #Test:\n\n");
	 const __m256d operand1 = { std::numeric_limits<double>::quiet_NaN(), 0.0L, 0.0L, 0.0L };
	 const __m256d operand2 = { std::numeric_limits<double>::quiet_NaN(), 1.0L, 1.0L, 1.0L };
	 __m256d result = mathlib::VecF64AVX::operator!=(operand1, operand2);
	 for (auto i = 0; i != test::Utilities::vec_length; ++i)
	 {
		 if (!(result.m256d_f64[i]))
		 {
			 std::printf("operand1 and operand2 are not equal component-wise\n");
			 std::printf("Dumping scalars component-wise...\n");
			 std::printf("operand1=%.15f     |       operand2=%.15f\n", operand1.m256d_f64[i], operand2.m256d_f64[2]);
			 std::printf("vector of results=%d\n", result.m256d_f64[i]);
		 }
		 else
		 {
			 std::printf("operand1 and operand2 are equal component-wise\n");
			 std::printf("Dumping scalars component-wise...\n");
			 std::printf("operand1=%.15f     |       operand2=%.15f\n", operand1.m256d_f64[i], operand2.m256d_f64[2]);
			 std::printf("vector of results=%d\n", result.m256d_f64[i]);
		 }
	 }
 }

 void test::VectorF64AVX_Test::Test_Static_Operator_InEqual_S()
 {
	 std::printf("static VecF64AVX::operator!=(const double, const __m256d) #Test:\n\n");
	 const double operand1 = 1.0L;
	 const __m256d operand2 = { std::numeric_limits<double>::quiet_NaN(), 0.0L, 0.0L, 0.0L };
	 __m256d result = mathlib::VecF64AVX::operator!=(operand1, operand2);
	 for (auto i = 0; i != test::Utilities::vec_length; ++i)
	 {
		 if (!(result.m256d_f64[i]))
		 {
			 std::printf("operand1 and operand2 are not equal component-wise\n");
			 std::printf("Dumping scalars component-wise...\n");
			 std::printf("operand1=%.15f     |       operand2=%.15f\n", operand1, operand2.m256d_f64[i]);
			 std::printf("vector of results=%d\n", result.m256d_f64[i]);
		 }
		 else
		 {
			 std::printf("operand1 and operand2 are equal component-wise\n");
			 std::printf("Dumping scalars component-wise...\n");
			 std::printf("operand1=%.15f     |       operand2=%.15f\n", operand1, operand2.m256d_f64[i]);
			 std::printf("vector of results=%d\n", result.m256d_f64[i]);
		 }
	 }
 }

 void test::VectorF64AVX_Test::Run_Static_Operator_Tests()
 {
	 std::printf("Started static VecF64AVX operator Tests\n");
	 Test_Static_Operator_Add();
	 Test_Static_Operator_Add_S();
	 Test_Static_Operator_Sub();
	 Test_Static_Operator_Sub_S();
	 Test_Static_Operator_Mul();
	 Test_Static_Operator_Mul_S();
	 Test_Static_Operator_Div();
	 Test_Static_Operator_Div_S();
	 Test_Static_Operator_Equal();
	 Test_Static_Operator_EqualS();
	 Test_Static_Operator_InEqual();
	 Test_Static_Operator_InEqual_S();
	 std::printf("Finished static VecF64AVX operator Tests\n");
 }

 /*void test::VectorF64AVX_Test::Run_Static_Operator_Tests(void(*pFunc)())
 {
	 std::vector<void(*)()> vptr(8);
	 vptr.push_back(&Test_Operator_Div_Assign);
	 vptr[0]();
	 std::printf("Started static VecF64AVX operator Tests\n");
	 std::printf("Calling test methods indirectly\n");
	 pFunc();
	 std::printf("Finished static VecF64AVX operator Tests\n");
 }*/

 void test::VectorF64AVX_Test::Run_Static_Operator_Tests_V()
 {
	 std::printf("Started static VecF64AVX operator Tests\n");
	 std::printf("Calling test methods indirectly\n");
	// void(*ptr)();
	 //ptr = &Test_Static_Operator_Add;
	// ptr();
	 FPTR ar_fptrs[12];
	 const int ar_fptrs_len = 12;
	 ar_fptrs[0] = &Test_Static_Operator_Add;
	 ar_fptrs[1] = &Test_Static_Operator_Add_S;
	 ar_fptrs[2] = &Test_Static_Operator_Sub;
	 ar_fptrs[3] = &Test_Static_Operator_Sub_S;
	 ar_fptrs[4] = &Test_Static_Operator_Mul;
	 ar_fptrs[5] = &Test_Static_Operator_Mul_S;
	 ar_fptrs[6] = &Test_Static_Operator_Div;
	 ar_fptrs[7] = &Test_Static_Operator_Div_S;
	 ar_fptrs[8] = &Test_Static_Operator_Equal;
	 ar_fptrs[9] = &Test_Static_Operator_EqualS;
	 ar_fptrs[10] = &Test_Static_Operator_InEqual;
	 ar_fptrs[11] = &Test_Static_Operator_InEqual_S;

	 for (auto i = 0; i != ar_fptrs_len; ++i)
		 ar_fptrs[i]();

	 std::printf("Finished static VecF64AVX operator Tests\n");
 }
 // Helper functions.
 /*void test::VectorF64AVX_Test::debug_print(mathlib::VecF64AVX &obj)
 {
	 std::printf("obj.x=%.15f, obj.y=%.15f, obj.z=%.15f, obj.w=%.15f\n", obj.get_m_VecF64().m256d_f64[0], obj.get_m_VecF64().m256d_f64[1],
		 obj.get_m_VecF64().m256d_f64[2], obj.get_m_VecF64().m256d_f64[3]);
	 return;
 }*/

 /*void test::VectorF64AVX_Test::debug_print(mathlib::VecF64AVX *obj)
 {
	 std::printf("obj.x=%.15f, obj.y=%.15f, obj.z=%.15f, obj.w=%.15f\n", obj->get_m_VecF64().m256d_f64[0], obj->get_m_VecF64().m256d_f64[1],
		 obj->get_m_VecF64().m256d_f64[2], obj->get_m_VecF64().m256d_f64[3]);
	 return;
 }*/

 mathlib::VecF64AVX  test::VectorF64AVX_Test::VecF64AVX_Create()
 {
	 return mathlib::VecF64AVX();
 }

 mathlib::VecF64AVX  test::VectorF64AVX_Test::VecF64AVX_Create(const double arg)
 {
	 return mathlib::VecF64AVX(arg);
 }

 mathlib::VecF64AVX  test::VectorF64AVX_Test::VecF64AVX_Create(const double s0, const double s1, const double s2, const double s3)
 {
	 return mathlib::VecF64AVX(s0, s1, s2, s3);
 }

 mathlib::VecF64AVX  test::VectorF64AVX_Test::VecF64AVX_Create(const double v[4])
 {
	 return mathlib::VecF64AVX(v);
 }

 mathlib::VecF64AVX  test::VectorF64AVX_Test::VecF64AVX_Create(const __m256d v)
 {
	 return mathlib::VecF64AVX(v);
 }

 mathlib::VecF64AVX  test::VectorF64AVX_Test::VecF64AVX_Create(const __m256i v)
 {
	 return mathlib::VecF64AVX(v);
 }

 mathlib::VecF64AVX  test::VectorF64AVX_Test::VecF64AVX_Create(const __m128d v0, const __m128d v1)
 {
	 return mathlib::VecF64AVX(v0, v1);
 }

 mathlib::VecF64AVX  test::VectorF64AVX_Test::VecF64AVX_Create(const mathlib::VecF64AVX &obj)
 {
	 return mathlib::VecF64AVX(obj);
 }