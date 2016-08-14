
#include "IntegratorGKMultiPoint_TEST.h"
#include "../MathLib/MathConstants.h"
#include "../MathLib/MathUtils.h"

namespace gk_test_aux
{

	static  const char QUADFAIL[] = "***Warning*** - Quadrature Approx Failed!!";

	static  const char QUADSUCC[] = "Quadrature Approx Succeded!!";

	static  const char NPREC[] = "Not Sufficient Precision - lacks ~8 digits of Precision";

	static   const char SPREC[] = "Sufficient Precision";

	static  const float FPREC{ 23 * ::log10f(static_cast<float>(2)) };

	static  const double DPREC{ 53 *  ::log10(static_cast<double>(2)) };

}

const double test::GaussKronordTests::MACHPREC{ 15.9546 };

void          test::GaussKronordTests::GK15ExpFunc1()
{
	std::printf("*****Test of Numerical Quadrature - Integrand [e^-px, p > 0]*****\n");
	std::printf("Precision of arguments:%.10f\n", gk_test_aux::FPREC);
	std::printf("Initializing variables.... ");
	float f_a{ 0.f }; float f_b{ 1.f }; float f_p{ 1.f };
	double d_a{ 0.0 }; double d_b{ 1.0 }; double d_p{ 1.0 };
	
	unsigned long long start1, end1, start2, end2;
	//const char MEQ[] = "Results Equal"; const char MUEQ[] = "Results InEqual";
	std::printf("Done\n");
	std::printf("lower limit a=%.9f\n", f_a);
	std::printf("upper limit b=%.9f\n", f_b);
	std::printf("variable    p=%.9f\n", f_p);
	
	const float numres{ 0.6321205588f };
	std::printf("Started crude timing, TSC used, no affinity set\n");
	start1 = __rdtsc();
	auto Qres1 = mathlib::IntegratorQK::x_qk15([](float* x)->float{float f_p{ 1.f }; return ::exp(-(f_p* *x)); }, f_a, f_b);
	end1 = __rdtsc();
	if ((end1 - start1) > 0)
	{
		std::printf("start time=%lluCycles\n", start1);
		std::printf("end   time=%lluCycles\n", end1);
		std::printf("x_qk15 executed in:%lluCycles\n", (end1 - start1));
	}
	std::printf("Results  Quadrature Comparison FP-32\n\n");
	std::printf("%s\n", mathlib::FP_Compare(numres, std::get<0>(Qres1)) ? gk_test_aux::QUADSUCC : gk_test_aux::QUADFAIL);
	std::printf("Mathematica 10 NIntegrate   |      QUADPACK QK15      |       Abs(delta)    |  MACHPREC - Abs(delta)\n");
	std::printf("  %.9f          %.9f                 %.9f         %.9f\n", numres, std::get<0>(Qres1), std::fabs(numres - std::get<0>(Qres1)),
		std::fabsf(numres - std::get<0>(Qres1)) > EPS_FLT ? MACHPREC - std::fabs(numres - std::get<0>(Qres1)):0.f);
	std::printf("--------------------------------------------------------------\n ");
	std::printf("QK15 - Abs Error=%.9f\n",std::get<1>(Qres1));
	std::printf("QK15 - approx to Integral j=%.9f\n",std::get<2>(Qres1));
	std::printf("QK15 - approx to Integral  abs(f-i/(b-a))=%.9f\n",std::get<3>(Qres1));
	std::printf("QK15 - End of FP-32 Test\n\n");
	std::printf("Start of FP-64 Precision Test\n");
	std::printf("lower limit a=%.17f\n", d_a);
	std::printf("upper limit b=%.17f\n", d_b);
	std::printf("variable    p=%.19f\n", d_p);
	const double d_numres{ 0.63212055882855768 };
	std::printf("Started crude timing, TSC used, no affinity set\n");
	start2 = __rdtsc();
	auto Qres2 = mathlib::IntegratorQK::x_qk15([](double* x)->double{double p{ 1.0 }; return ::exp(-(p * *x)); }, d_a, d_b);
	end2 = __rdtsc();
	if ((end2 - start2) > 0)
	{
		std::printf("start time=%lluCycles\n", start2);
		std::printf("end   time=%lluCycles\n", end2);
		std::printf("x_qk15 executed in:%lluCycles\n", (end2 - start2));
	}
	std::printf("Results  Quadrature Comparison FP-64\n\n");
	std::printf("%s\n\n", mathlib::FP_Compare(d_numres,std::get<0>(Qres2)) ? gk_test_aux::QUADSUCC : gk_test_aux::QUADFAIL);
	std::printf("Mathematica 10 NIntegrate		|      QUADPACK DQK15			|       Abs(delta)    |      MACHPREC - Abs(delta)\n");
	std::printf("%.17f       %.17f             %.17f             %.17f\n", d_numres, std::get<0>(Qres2), std::fabs(d_numres - std::get<0>(Qres2)),
		std::fabs(d_numres - std::get<0>(Qres2)) > EPS_DBL ? MACHPREC - ::log10(std::fabs(d_numres - std::get<0>(Qres2))):0.0);
	//std::printf("%s\n",std::fabs(d_numres - std::get<0>(Qres2)) <= std::numeric_limits<double>::epsilon() ? MEQ : MUEQ);
	std::printf("----------------------------------------------------------------\n");
	std::printf("DQK15 - abs error=%.17f\n", std::get<1>(Qres2));
	std::printf("DQK15 - approx to Integral j=%.17f\n", std::get<2>(Qres2));
	std::printf("DQK15 - approx to Integral abs(f-i/(b-a))=%.17f\n", std::get<3>(Qres2));
	std::printf("DQK15 - End of FP-64 Test\n\n");
	
}

void           test::GaussKronordTests::GK15ExpFunc2()
{
	std::printf("*****Test of Numerical Quadrature - Integrand [dx/1+e^px, p > 0]*****\n");
	std::printf("Precsion of arguments:%.10f\n", gk_test_aux::FPREC);
	std::printf("Initializing variables.... ");
	float f_a{ 0.f }; float f_b{ 1.f }; float f_p{ 0.5f };
	double d_a{ 0.0 }; double d_b{ 1.0 }; double d_p{ 0.5 };
	unsigned long long start1, start2, stop1, stop2;
	std::printf("Done\n");
	std::printf("lower limit a=%.9f\n", f_a);
	std::printf("upper limit b=%.9f\n", f_b);
	std::printf("variable    p=%.9f\n", f_p);
	const float numres{ 0.4381403928f };
	std::printf("Started crude timing, TSC used, no affinity set\n");
	start1 = __rdtsc();
	auto Qresf = mathlib::IntegratorQK::x_qk15([](float* x)->float{ float p{ 0.5f }; return 1.f / (1.f + ::exp(p * *x)); }, f_a, f_b);
	stop1 =  __rdtsc();
	if ((stop1 - start1) > 0)
	{
		std::printf("start1=%lluCycles\n", start1);
		std::printf("stop1 =%lluCycles\n", stop1);
		std::printf("x_qk15 excuted in:%lluCycles\n", stop1 - start1);
	}
	std::printf("Results  Quadrature Comparison FP-32\n\n");
	std::printf("%s\n", mathlib::FP_Compare(numres, std::get<0>(Qresf)) ? gk_test_aux::QUADSUCC : gk_test_aux::QUADFAIL);
	std::printf("Mathematica 10 NIntegrate   |      QUADPACK QK15      |       Abs(delta)    |  MACHPREC - Abs(delta)\n");
	std::printf(" %.9f,             %.9f,            %.9f,               %.9f\n", numres, std::get<0>(Qresf), std::fabsf(numres - std::get<0>(Qresf)),
		std::fabsf(numres - std::get<0>(Qresf)) > EPS_FLT ? MACHPREC - ::log10f(std::fabsf(numres - std::get<0>(Qresf))) : 0.f);
	std::printf("--------------------------------------------------------------\n ");
	std::printf("QK15 Abs error=%.9f\n", std::get<1>(Qresf));
	std::printf("QK15 approx to Integral j=%.9f\n", std::get<2>(Qresf));
	std::printf("QK15 approx to Integral abs(f-i/(b-a))=%.9f\n\n", std::get<3>(Qresf));
	
	std::printf("Precision of arguments=%.17f\n", gk_test_aux::DPREC);
	std::printf("lower limit a=%.17f\n", d_a);
	std::printf("upper limit b=%.17f\n", d_b);
	std::printf("variable    p=%.17f\n", d_p);
	const double d_numres{ 0.43814039275967725 };
	std::printf("Started crude timing, TSC used, no affinity set\n");
	start2 = __rdtsc();
	auto Qresd = mathlib::IntegratorQK::x_qk15([](double* x)->double{double p{ 0.5 }; return 1.0 / (1.0 + ::exp(p * *x)); }, d_a, d_b);
	stop2 = __rdtsc();
	if ((stop2 - start2) > 0)
	{
		std::printf("start2=%lluCycles\n", start2);
		std::printf("stop2 =%lluCycles\n", stop2);
		std::printf("x_qk15 executed in:%lluCycles\n", stop2 - start2);
	}
	std::printf("Results  Quadrature Comparison FP-64\n\n");
	std::printf("%s\n\n", mathlib::FP_Compare(d_numres,std::get<0>(Qresd)) ? gk_test_aux::QUADSUCC : gk_test_aux::QUADFAIL);
	std::printf("Mathematica 10 NIntegrate   |      QUADPACK QK15      |       Abs(delta)    |  MACHPREC - Abs(delta)\n");
	std::printf("%.16f,        %.16f,       %.16f,         %.16f\n", d_numres, std::get<0>(Qresd), std::fabs(d_numres - std::get<0>(Qresd)),
		std::fabs(d_numres - std::get<0>(Qresd)) > EPS_DBL ? MACHPREC - (-1.0 * ::log10(std::fabs(d_numres - std::get<0>(Qresd)))) : 0.0);
	std::printf("--------------------------------------------------------------\n ");
	std::printf("DQK15         Abs error=%.17f\n", std::get<1>(Qresd));
	std::printf("DQK15 approx Integral j=%.17f\n", std::get<2>(Qresd));
	std::printf("DQK15 aaprox Integral abs(f-i/(b-a))=%.17f\n", std::get<3>(Qresd));
	std::printf("DQK15 - End of FP-64 Test\n\n");
}

void           test::GaussKronordTests::GK15ExpFunc3()
{
	std::printf("*****Numerical Integration of Integrand = [e^-ux/1+e-x, u > 0.0]*****\n");
	std::printf("Precsion of arguments:%.10f\n", gk_test_aux::FPREC);
	std::printf("Initializing variables.... ");
	float f_a{ 99.f }; float f_b{ 100.f }; float f_u{ 0.33f };
	double d_a{ 99.0 }; double d_b{ 100.0 }; double d_u{ 0.33 };
	unsigned long long start1, start2, stop1, stop2;
	
	std::printf("Done\n");
	std::printf("lower limit a=%.9f\n", f_a);
	std::printf("upper limit b=%.9f\n", f_b);
	std::printf("variable    u=%.9f\n", f_u);
	const float f_numres{ 5.519624233e-15f };
	std::printf("Started crude timing, TSC used, no affinity set\n");
	start1 = __rdtsc();
	auto Qresf = mathlib::IntegratorQK::x_qk15([](float* x)->float{float u{ 0.33f }; return ::exp(-(u * *x)) / (1.f + ::exp(-*x)); }, f_a, f_b);
	stop1 = __rdtsc();
	if ((stop1 - start1) > 0)
	{
		std::printf("start1=%lluCycles\n", start1);
		std::printf("stop1 =%lluCycles\n", stop1);
		std::printf("x_qk15 executed in=%llu\n", stop1 - start1);
	}
	std::printf("Results  Quadrature Comparison FP-32\n\n");
	std::printf("%s\n", mathlib::FP_Compare(f_numres, std::get<0>(Qresf)) ? gk_test_aux::QUADSUCC : gk_test_aux::QUADFAIL);
	std::printf("Mathematica 10 NIntegrate   |      QUADPACK QK15      |       Abs(delta)    |  MACHPREC - Abs(delta)\n");
	std::printf("%.9f                     %.9f               %.9f                  %.9f\n", f_numres, std::get<0>(Qresf), std::fabsf(f_numres - std::get<0>(Qresf)), 
		std::fabsf(f_numres - std::get<0>(Qresf)) > EPS_FLT ? MACHPREC - ::log10f(std::fabsf(f_numres - std::get<0>(Qresf))) : 0.f);	
	std::printf("%s\n", std::fabs(std::get<0>(Qresf)) < EPS_FLT ? gk_test_aux::NPREC : gk_test_aux::SPREC);
	std::printf("--------------------------------------------------------------\n ");
	std::printf("QK15 Abs error=%.9f\n", std::get<1>(Qresf));
	std::printf("QK15 approx Integral j=%.9f\n", std::get<2>(Qresf));
	std::printf("QK15 approx Integral abs(f-i/(b-a))=%.9f\n\n", std::get<3>(Qresf));
	std::printf("Precision of arguments=%.17f\n", gk_test_aux::DPREC);
	std::printf("lower limit a=%.17f\n", d_a);
	std::printf("upper limit b=%.17f\n", d_b);
	std::printf("variable    u=%.17f\n", d_u);
	const double d_numres{ 5.5196242329603281e-15 };
	std::printf("Started crude timing, TSC used, no affinity set\n");
	start2 = __rdtsc();
	auto  Qresd = mathlib::IntegratorQK::x_qk15([](double* x)->double{ double u{ 0.33 }; return ::exp(-(u * *x)) / (1.0 + ::exp(-*x)); }, d_a, d_b);
	stop2 = __rdtsc();
	if ((stop2 - start2) > 0)
	{
		std::printf("start2=%lluCycles\n", start2);
		std::printf("stop2 =%lluCycles\n", stop2);
		std::printf("x_qk15 executed in=%lluCycles\n", stop2 - start2);
	}
	std::printf("Results  Quadrature Comparison FP-64\n\n");
	std::printf("%s\n\n", mathlib::FP_Compare(d_numres,std::get<0>(Qresd)) ? gk_test_aux::QUADSUCC : gk_test_aux::QUADFAIL);
	std::printf("Mathematica 10 NIntegrate   |            QUADPACK QK15      |                Abs(delta)    |                                   MACHPREC - Abs(delta)\n");
	std::printf("%.30f               %.30f               %.30f                    %.30f\n", d_numres, std::get<0>(Qresd), std::fabs(d_numres - std::get<0>(Qresd)),
		std::fabs(d_numres - std::get<0>(Qresd)) > EPS_DBL ? MACHPREC - (-1.0 * ::log10(std::fabs(d_numres - std::get<0>(Qresd)))) : 0.0);	
	std::printf("DQK15 Abs error=%.30f\n", std::get<1>(Qresd));
	std::printf("DQK15 approx of Integral j=%.30f\n", std::get<2>(Qresd));
	std::printf("DQK15 approx of Integral  abs(f-i/(b-a))=%.30f\n", std::get<3>(Qresd));
	std::printf("DQK15 - End of FP-64 Test\n\n");

}

void           test::GaussKronordTests::GK15TrigFunc1()
{
	std::printf("*****Numerical Integration of Integrand = [1-cos(x))^n*sin(n*x)dx]*****\n");
	std::printf("Precsion of arguments:%.10f\n", gk_test_aux::FPREC);
	std::printf("Initializing variables.... ");
	float f_a{ 0.f }; float f_b{ mathlib::MathConstants::TWO_PI_FLT() }; float f_n{ 10.f };
	double d_a{ 0.0 }; double d_b{ mathlib::MathConstants::TWO_PI_DBL() }; double d_n{ 10.0 };
	unsigned long long start1, start2, stop1, stop2;
#if 0
	std::printf("Done\n");
	std::printf("lower limit a=%.9f\n", f_a);
	std::printf("upper limit b=%.9f\n", f_b);
	std::printf("variable    n=%.9f\n", f_n);
	const float f_numres{ 1.385110395e-36f };
	const double d_numres{ 1.3851103921886892012e-36 };
	std::printf("Started crude timing, TSC used, no affinity set\n");
	start1 = __rdtsc();
	auto Qresf = mathlib::IntegratorQK::x_qk15([](float* x)->float{ float n{ 10.f }; return ::pow((1 - ::cos(*x)), n) * ::sin(n* *x); }, f_a, f_b);
	stop1 = __rdtsc();
	if ((stop1 - start1) > 0)
	{
		std::printf("start1=%lluCycles\n", start1);
		std::printf("stop1 =%lluCycles\n", stop1);
		std::printf("x_qk15 executed in:%lluCycles\n",stop1 - start1);
	}
	std::printf("Results  Quadrature Comparison FP-32\n\n");
	std::printf("Mathematica 10 NIntegrate   |      QUADPACK QK15      |       Abs(delta)    |  MACHPREC - Abs(delta)\n");
	std::printf(" %.9f           %.9f               %.9f               %.9f\n", f_numres, std::get<0>(Qresf), std::fabsf(f_numres - std::get<0>(Qresf)), 
		std::fabsf(f_numres - std::get<0>(Qresf)) > std::numeric_limits<float>::epsilon() ? MACHPREC - ::log10f(std::fabsf(f_numres - std::get<0>(Qresf))) : 0.f);
	std::printf("%s\n", std::fabs(std::get<0>(Qresf)) < std::numeric_limits<float>::epsilon() ? NPREC : SPREC);
	std::printf("QK15 Abs error=%.9f\n", std::get<1>(Qresf));
	std::printf("QK15 approx Integral of j=%.9f\n", std::get<2>(Qresf));
	std::printf("QK15 approx Integral abs(f-i/(b-a))=%.9f\n\n", std::get<3>(Qresf));
#endif
	std::printf("Precision of arguments=%.17f\n", gk_test_aux::DPREC);
	std::printf("lower limit a=%.17f\n", d_a);
	std::printf("upper limit b=%.17f\n", d_b);
	std::printf("variable    n=%.17f\n", d_n);
	/*
	@ This should fail mainly because the result < EPS_DOUBLE.
	*/
	const double d_numres{ 1.3851103921886892012e-36 };
	std::printf("Started crude timing, TSC used, no affinity set\n");
	start2 = __rdtsc();
	auto Qresd = mathlib::IntegratorQK::x_qk15([](double* x)->double{ double n{ 10.0 }; return ::pow((1 - ::cos(*x)), n) * ::sin(n* *x); }, d_a, d_b);
	stop2 = __rdtsc();
	if ((stop2 - start2) > 0)
	{
		std::printf("start2=%lluCycles\n", start2);
		std::printf("stop2 =%lluCycles\n", stop2);
		std::printf("x_qk15 executed in:%lluCycles\n", stop2 - start2);
	}
	std::printf("Results  Quadrature Comparison FP-64\n\n");
	std::printf("%s\n\n", mathlib::FP_Compare(d_numres,std::get<0>(Qresd)) ? gk_test_aux::QUADSUCC : gk_test_aux::QUADFAIL);
	std::printf("Mathematica 10 NIntegrate   |      QUADPACK QK15      |          Abs(delta)    |                       MACHPREC - Abs(delta)\n");
	std::printf(" %.45f,         %.45f,            %.30f,             %.30f\n", d_numres, std::get<0>(Qresd), std::fabs(d_numres - std::get<0>(Qresd)),
		std::fabs(d_numres - std::get<0>(Qresd)) > EPS_DBL ? MACHPREC - (-1.0 * ::log10(std::fabs(d_numres - std::get<0>(Qresd)))) : 0.0);
	
	std::printf("DQK15 Abs error=%.30f\n", std::get<1>(Qresd));
	std::printf("DQK15 approx Integral j=%.30f\n", std::get<2>(Qresd));
	std::printf("DQK15 approx Integral abs(f-i/(b-a))=%.30f\n", std::get<3>(Qresd));
	std::printf("DQK15 - End of Test\n\n");
}

void           test::GaussKronordTests::GK15TrigFunc2()
{
	std::printf("****Numerical Integration of Integrand = [sin(nx)/sin(x)dx]*****\n");
	std::printf("Precsion of arguments:%.10f\n", gk_test_aux::FPREC);
	std::printf("Initializing variables.... ");
	const float f_a{ 0.f }; const float f_b{ mathlib::MathConstants::PI_FLT() }; const float f_n{ 3.f };
	const double d_a{ 0.0 }; const double d_b{ mathlib::MathConstants::PI_DBL() }; const double d_n{ 3.0 };
	unsigned long long start1, start2, stop1, stop2;
	std::printf("lower limit a=%.9f\n", f_a);
	std::printf("upper limit b=%.9f\n", f_b);
	std::printf("variable    n=%.9f\n", f_n);
	const float f_numres{ 3.141592654F };
	const double d_numres{ 3.14159265358979323 };
	std::printf("Started crude timing, TSC used, no affinity set\n");
	start1 = __rdtsc();
	auto Qresf = mathlib::IntegratorQK::x_qk15([](float* x)->float{ float n{ 3.f }; return ::sin(n * *x) / sin(*x); }, f_a, f_b);
	stop1 = __rdtsc();
	if ((stop1 - start1) > 0)
	{
		std::printf("start1=%lluCycles\n", start1);
		std::printf("stop1 =%lluCycles\n", stop1);
		std::printf("x_qk15 executed in:%lluCycles\n", stop1 - start1);
	}
	std::printf("Results  Quadrature Comparison FP-32\n\n");
	std::printf("%s\n",mathlib::FP_Compare(f_numres,std::get<0>(Qresf)) ? gk_test_aux::QUADSUCC : gk_test_aux::QUADFAIL);
	std::printf("Mathematica 10 NIntegrate   |      QUADPACK QK15      |       Abs(delta)    |  MACHPREC - Abs(delta)\n");
	std::printf("%.9f                   %.9f                  %.9f                      %.9f\n", f_numres, std::get<0>(Qresf), std::fabsf(std::get<0>(Qresf)-f_numres),
		std::fabsf(f_numres - std::get<0>(Qresf)) > EPS_FLT ? MACHPREC - ::log10f(std::fabsf(f_numres - std::get<0>(Qresf))) : 0.f);
	std::printf("%s\n", std::fabs(std::get<0>(Qresf)) <  EPS_FLT ? gk_test_aux::NPREC : gk_test_aux::SPREC);
	std::printf("QK15 Abs error=%.9f\n", std::get<1>(Qresf));
	std::printf("QK15 approx Integral of j=%.9f\n", std::get<2>(Qresf));
	std::printf("QK15 approx Integral abs(f-i/(b-a))=%.9f\n\n", std::get<3>(Qresf));
	std::printf("Precision of arguments=%.17f\n", gk_test_aux::DPREC);
	std::printf("lower limit a=%.17f\n", d_a);
	std::printf("upper limit b=%.17f\n", d_b);
	std::printf("variable    n=%.17f\n", d_n);
	start2 = __rdtsc();
	auto Qresd = mathlib::IntegratorQK::x_qk15([](double* x)->double{ double n{ 3.0 }; return ::sin(n * *x) / ::sin(*x); }, d_a, d_b);
	stop2 = __rdtsc();
	if ((stop2 - start2) > 0)
	{
		std::printf("start2=%lluCycles\n", start2);
		std::printf("stop2 =%lluCycles\n", stop2);
		std::printf("x_qk15 executed in:%lluCycles\n", stop2 - start2);
	}
	std::printf("Results  Quadrature Comparison FP-64\n\n");
	std::printf("%s\n\n", mathlib::FP_Compare(d_numres,std::get<0>(Qresd)) ? gk_test_aux::QUADSUCC : gk_test_aux::QUADFAIL);
	std::printf("Mathematica 10 NIntegrate   |      QUADPACK QK15      |          Abs(delta)    |                       MACHPREC - Abs(delta)\n");
	std::printf(" %.17f         %.17f                %.17f                     %.17f\n", d_numres, std::get<0>(Qresd), std::fabs(d_numres - std::get<0>(Qresd)),
		std::fabs(d_numres - std::get<0>(Qresd)) > EPS_DBL ? MACHPREC - (-1.0 * ::log10(std::fabs(d_numres - std::get<0>(Qresd)))) : 0.0);
	std::printf("DQK15 Abs error=%.17f\n", std::get<1>(Qresd));
	std::printf("DQK15 approx Integral j=%.17f\n", std::get<2>(Qresd));
	std::printf("DQK15 approx Integral abs(f-i/(b-a))=%.17f\n", std::get<3>(Qresd));
	std::printf("DQK15 - End of Test\n\n");
}


void           test::GaussKronordTests::RunGK15ExpFuncTests()
{
	GK15ExpFunc1();
	GK15ExpFunc2();
	GK15ExpFunc3();
}

void           test::GaussKronordTests::RunGK15TrigFuncTests()
{
	GK15TrigFunc1();
	GK15TrigFunc2();
}