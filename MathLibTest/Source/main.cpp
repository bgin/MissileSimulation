
#include <stdio.h>
#include "ConstantsTest.h"
#include "functions_scalar_test.h"
#include "VectorF64AVX_TEST.h"
#include "NormalF64AVX_TEST.h"
#include "../MathLib/MathUtils.h"
//#include "../MathLib/Derivative.h"
//#include "../MathLib/DerivativeAVX.h"
//#include "../MathLib/TrapezoidQuadrature.h"
//#include "../MathLib/BoolCompositeQuadrature.h"
#include "TrapezoidQuadrature_TEST.h"
#include "../MathLib/MultiThreadedTrapezoid.h"
#include "../MathLib/MultiThreadedBoolRule.h"
#include "../MathLib/MultiThreaded7PQuadrature.h"

int main(int argc, char* argv[])
{
     // Comment out/Uncomment Everything to Run All Tests.
	mathlib::Fx integrand;
	integrand.a = 0.0L, integrand.b = 1.0L, integrand.fptr = [](double arg)->double{ return 0.333333333333L * (arg * arg * arg); };
	integrand.num_steps = 1 << 20; 
	double res = mathlib::MTTrpzd::run_computation(&integrand);
	std::printf("res=%.15f\n", res);

	mathlib::Fx integrand2;
	integrand2.a = 0.0L, integrand2.b = 1.0L, integrand2.fptr = [](double arg)->double {return 0.33333333333L * (arg * arg * arg); };
	integrand2.num_steps = 1 << 20;
	double res2 = mathlib::MTBoolQdrtr::run_computation(&integrand2);
	std::printf("res2=%.15f\n", res2);*/
	mathlib::Fx fx1;
	/*fx1.a = 0.0L, fx1.b = 1.0, fx1.fptr = [](double arg)->double{ return 0.33333333333333L * (arg * arg * arg); };
	fx1.num_steps = 1 << 20;
	fx1.NWorkers = 16; 
	fx1.Workers = new unsigned int[fx1.NWorkers]; fx1.ThIDArray = new DWORD[fx1.NWorkers];*/
	mathlib::InitFx(&fx1, [](double arg)->double{ return 0.33333333333L * (arg * arg * arg); }, 0.0L, 1.0L, 8, (1 << 20));
	double res = mathlib::MTTrpzd::run_computation(&fx1);
	std::printf("res=%.15f\n", res);
	mathlib::DeallocFx(&fx1);
	std::printf("pi=%.15f\n",test::ConstantsTestClass::Test_PI_DBL());
	test::TrapezoidQuadratureTest::Run_Trapezoid_Quadrature_Tests();
	test::TrapezoidQuadratureTest::Run_Trapezoid_Varying_Abscissa_Tests();
	test::TrapezoidQuadratureTest::Run_Trapezoid_Varying_Step_Tests();
	test::TrapezoidQuadratureTest::Run_Trapezoid_Varying_Abscissa_Step_Tests();
	
	test::FunctionsScalarTest::Run_Tests();
	test::VectorF64AVX_Test::Run_Constructor_Tests();
	test::VectorF64AVX_Test::Run_Operator_Tests();
	test::VectorF64AVX_Test::Run_Static_Operator_Tests_V();
	test::NormalF64AVX_Test::Run_Constructor_Tests();
	double x = 0.0; double y = 0.01;
	for (auto i = 0; i != 100; ++i)
	{
		std::printf("%d random=%.15f\n", i, test::Utilities::generate_rand_value<double>(0.0L,1.0L));
	}
	std::printf("End of test\n");
	test::NormalF64AVX_Test::Test_apply2();
	auto rand = []()->double{
		return test::Utilities::generate_rand_value<double>(0.0L, 1.0L);
	};
	mathlib::Array1D<double> array1d = mathlib::Array1D<double>(100, rand());
	for (auto i = 0; i != array1d.get_size(); ++i) std::cout << "array1d=" << array1d.get_m_data()[i] << std::endl;
	auto array1d_2 = mathlib::Array1D<double>(100, 0.0L);
	const double arg = 10.0L;
	double arg2 = 10.0L;
	double * a = new double[100];
	array1d_2.apply([=](const double)->double{
		return test::Utilities::generate_rand_value<double>(0.0L, arg);
	}, arg);
	mathlib::Array1D<double>::apply(array1d_2, [=]()->double *{
		
		for (auto i = 0; i != 100; ++i) a[i] = std::sin(static_cast<double>(i));
		return a;
	});
	mathlib::Array1D<double>::debug_print(array1d_2);*/
	

	const double arg = 0.5; const double h = 0.0078125L; // 1/128, 2^-7
	auto res = mathlib::DyDx<double>::differentiate([](double arg)->double{
		return std::sin(arg);
	}, arg, h);
	double d = res.get_deriv(); double d1 = res.get_error();
	std::printf("d=%.15f,d1=%.15f\n", d, d1);
	auto res2 = mathlib::DyDx<double>::differentiate2([](double arg)->double{ // Proper way of passing arguments to lambda.
		return std::sin(arg)  ;
	},arg,h);
	std::printf("deriv=%.15f,err=%.15f\n", res2.get_deriv(),res2.get_error());
	__m256d v_arg = _mm256_set_pd(0.5L, 0.5L, 0.5L, 0.5L); __m256d v_h = _mm256_set1_pd(0.0009765625L);
	auto res3 = mathlib::DyDxAVX::differentiate([](__m256d arg)->__m256d
	{
		return _mm256_sin_pd(arg);
	}, v_arg, v_h);
	double a = 0.0, b = 1.0; const int n = 1024;
	auto res4 = mathlib::TrapezoidRule<double>::integrate([](double arg)->double{
		return 0.3333333333L * (arg * arg * arg);
	}, a, b, n);
	std::printf("Int xdx=%.15f, error=%.15f\n", res4.get_integral(),res4.get_error());
	std::function<double(double)> functor = [](double rad)->double{ return 0.33333333333 * (rad * rad * rad); }; double integr = 0.0;
	mathlib::Trapzd<std::function<double(double)>> integral(a, b, n, functor);
	auto res5 = integral.integrate_refined(std::numeric_limits<double>::epsilon());
	std::printf("refined trpzd=%.15f\n", res5.get_integral());
	
	auto res6 = mathlib::BoolRule<double>::integrate([](double arg)->double
	{
		return 0.3333333333L * (arg * arg * arg);
	}, a, b, n,1);
	std::printf("BoolRule=%.15f, error=%.15f\n", res6.get_integral(), res6.get_error());*/
	
	
	auto res = mathlib::DyDx<double>::test1(0.5, 1.5);
	double d = res.get_deriv(); double d2 = res.get_error();
	std::printf("d=%.15f,d2=%.15f\n", d, d2);
	test::NormalF64AVX_Test::Test_apply();
	mathlib::NormF64AVX n = mathlib::NormF64AVX(3.14);
	const double value = 3.14L;
	mathlib::NormF64AVX res = n * value;
	double dist = res.euclidean_distance();
	std::printf("s1=%.15f, s2=%.15f, dist=%.15f\n", res.get_m_VecF64().m256d_f64[0], res.get_m_VecF64().m256d_f64[1],dist);
	mathlib::TangentF64AVX c, a, b;
	a = mathlib::TangentF64AVX(13.14L); b = mathlib::TangentF64AVX(3.14L);
	
	a = a + b;
	
	__m256d dp = mathlib::TangentF64AVX::dot(a.get_m_VecF64(), b.get_m_VecF64());
	c = b.direction_cosine();
	std::printf("dir_cosines=%.15f\n", b.get_m_VecF64().m256d_f64[0]);
	std::printf("a=%.15f\n", dp.m256d_f64[0]);
	// va = _mm256_set1_pd(3.14L); __m256d vb = _mm256_set1_pd(6.18L);
	// vc = mathlib::NormF64AVX::operator+(va, vb);
	//std::printf("vc=%.15f\n", vc.m256d_f64[0]);
	mathlib::NormalS<double> n1, n2, n3; mathlib::VectorS<double> n4, n5;
	 n2 = mathlib::NormalS<double>(10.5L); n3 = mathlib::NormalS<double>(1.0L);
	 n1 = n3.euclidean_distance();
	//n1 = n2.operator+=(n2);
	std::printf("x=%.9f,y=%.9f,z=%.9f\n", n1.X(), n1.Y(), n1.Z());
	n5 = mathlib::VectorS<double>(1.0L);
	n4 = n5.normalize();
	std::printf("n4.x=%.9f,n4.y=%.9f,n4.z=%.9f\n", n4.X(), n4.Y(), n4.Z());*/
	std::getchar();
	return 0;
}