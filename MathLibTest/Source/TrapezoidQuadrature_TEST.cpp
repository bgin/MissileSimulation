#include "TrapezoidQuadrature_TEST.h"

void test::TrapezoidQuadratureTest::Test_Trapezoid_Quadrature()
{
	std::printf("Beginning test of Trapezoid Quadrature\n");
	std::printf("First Run: Numerical Quadrature of polynomial based Integrals...\n\n");
	const double a = 0.0L, b = 1.0L;
	const int num_steps = 1024;
	std::printf("Test #1\n");
	std::printf("Test of Integral type: Int [x dx]\n");
	std::printf("abscissas: a=%.15f,b=%.15f\n", a, b);
	std::printf("Number of steps=%d\n", num_steps);
	std::printf("Actual value=%.15f\n", (Integral([](const double arg)->double
	{
		return 0.5L * (arg * arg);
	}, b) - Integral([](const double arg)->double
	{
		return 0.5L * (arg * arg);
	},a)));
	
	auto result1 = mathlib::TrapezoidRule<double>::integrate([](double arg)->double
	{
		return arg;
	}, a, b, num_steps);
	std::printf("Result from TrapezoidRule::integrate=%.15f\n\n", result1.get_integral());
	
	std::printf("Test #2\n");
	std::printf("Test of Integral type: Int [x^2 dx]\n");
	std::printf("abscissas: a=%.15f,b=%.15f\n", a, b);
	std::printf("Number of steps=%d\n", num_steps);
	double reference_value = Integral([](const double arg)->double
	{
		return 0.3L * (arg * arg * arg);
	}, b) - Integral([](const double arg)->double
	{
		return 0.3L * (arg * arg * arg);
	}, a);
	std::printf("Actual value=%.15f\n", reference_value);
	auto result2 = mathlib::TrapezoidRule<double>::integrate([](double arg)->double
	{
		return arg * arg;
	}, a, b, num_steps);
	std::printf("Result from TrapezoidRule::integrate=%.15f\n", result2.get_integral());
	std::printf("Results Delta=%.15f\n\n", std::fabs(result2.get_integral()) - std::fabs(reference_value));

	std::printf("Test #3\n");
	std::printf("Test of Integral type: Int [x^3/3 dx]\n");
	std::printf("abscissas: a=%.15f,b=%.15f\n", a, b);
	std::printf("Number of steps=%d\n", num_steps);
	auto reference_value2 = Integral([](const double arg)->double
	{
		return 0.083333333333333L * (arg * arg * arg * arg);
	}, b) - Integral([](const double arg)->double
	{
		return 0.083333333333333L * (arg * arg * arg * arg);
	}, a);
	std::printf("Actual value=%.15f\n", reference_value2);
	auto result3 = mathlib::TrapezoidRule<double>::integrate([](double arg)->double
	{
		return 0.33333333333333333L * (arg * arg * arg);
	}, a, b, num_steps);
	std::printf("Result from TrapezoidRule::integrate=%.15f\n", result3.get_integral());
	std::printf("Results Delta=%.15f\n\n", std::fabs(result3.get_integral()) - std::fabs(reference_value2));

	std::printf("Test #4\n");
	std::printf("Test of Integral of type: Int [x^5/3 dx]\n");
	std::printf("abscissas: a=%.15f,b=%.15f\n", a, b);
	std::printf("Number of steps=%d\n", num_steps);
	auto reference_value3 = Integral([](const double arg)->double
	{
		return 0.055555555555555L * (arg * arg * arg * arg * arg * arg);
	}, b) - Integral([](const double arg)->double
	{
		return 0.055555555555555L * (arg * arg * arg * arg * arg * arg);
	}, a);
	std::printf("Actual value=%.15f\n", reference_value3);
	auto result4 = mathlib::TrapezoidRule<double>::integrate([](double arg)->double
	{
		return 0.33333333333333333L * (arg * arg * arg * arg * arg);
	}, a, b, num_steps);
	std::printf("Result from TrapezoidRule::integrate=%.15f\n", result4.get_integral());
	std::printf("Results Delta=%.15f\n\n", std::fabs(result4.get_integral()) - std::fabs(reference_value3));
}

void  test::TrapezoidQuadratureTest::Test_Trapezoid_Quadrature_Varying_Abscissas()
{
	std::printf("Beginning test of Trapezoid Quadrature\n");
	std::printf("First Run: Numerical Quadrature of polynomial based Integrals...\n");
	std::printf("Testing convergence on varying abscissa, with fixed number of steps\n\n");
	const int num_steps = 1024,num_iters = 100;
	std::vector<double> ref_values;
	std::vector<double> qdrtr_values;
	std::vector<std::pair<double, double>> abscissa_values;
	std::vector<double> qdrtr_error;
	double a = 0.0L, b = 1.0L;
	double incr_a = 0.1L; double incr_b = 0.4L;
	std::printf("Test #1\n");
	std::printf("Test of Integral of type:[x^3/3 dx]\n\n");
	std::printf("Number of loop iterations=%d\n", num_iters);
	std::printf("Number of steps=%d\n", num_steps);
	std::printf("abscissa a=%.15f, increment by: %.15f\n", a, incr_a);
	std::printf("abscissa b=%.15f, increment by: %.15f\n", b, incr_b);
	for (auto i = 0; i != num_iters; ++i)
	{
		b += incr_b;
		a += incr_a;
		ref_values.push_back((Integral([](const double arg)->double
		{
			return 0.083333333333333L * (arg * arg * arg * arg);
		}, b) - Integral([](const double arg)->double
		{
			return 0.083333333333333L * (arg * arg * arg * arg);
		}, a)));

		qdrtr_values.push_back(mathlib::TrapezoidRule<double>::integrate([](double arg)->double
		{
			return 0.33333333333333333L * (arg * arg * arg);
		}, a, b, num_steps).get_integral() );

		qdrtr_error.push_back(mathlib::TrapezoidRule<double>::integrate([](double arg)->double
		{
			return 0.33333333333333333L * (arg * arg * arg);
		}, a, b, num_steps).get_error());

		abscissa_values.push_back(std::pair<double,double>(a, b));
	}

	std::printf("Dumping the results...\n\n");
	std::printf("Ref_value:         Quadrature approx:        Delta:          Error:     \n");
	for (auto i = 0; i != num_iters; ++i)
	{
		std::printf("#%d, %.15f %.15f %.15f %.15f\n",i, ref_values.operator[](i), qdrtr_values.operator[](i),
			(qdrtr_values.operator[](i) - ref_values.operator[](i)),qdrtr_error.operator[](i));
		std::printf("abscissa a=%.9f   b=%.9f\n", abscissa_values.operator[](i).first, abscissa_values.operator[](i).second);
	}
	std::printf("Finished Test\n\n");
}

void  test::TrapezoidQuadratureTest::Test_Trapezoid_Quadrature_Varying_Steps(double a, double b)
{
	std::printf("Beginning test of Trapezoid Quadrature\n");
	std::printf("First Run: Numerical Quadrature of polynomial based Integrals...\n");
	std::printf("Testing quadrature convergence, varying interval, varying number of steps\n\n");
	
	const int num_iters = 20;
	std::vector<double> ref_values;
	std::vector<double> qdrtr_values;
	std::vector<double> qdrtr_err;
	unsigned int num_steps = 2;
	unsigned int steps_vals[20];
	std::printf("Test #1\n");
	std::printf("Test of Integral of type:[x^3/3 dx]\n");
	std::printf("Number of loop iterations=%d\n", num_iters);
	std::printf("Starting abscissa(varying) a=%.15f,b=%.15f\n", a, b);
	for (auto i = 0; i != num_iters; ++i)
	{
		num_steps <<= 1;
		steps_vals[i] = num_steps;
		ref_values.push_back((Integral([](const double arg)->double
		{
			return 0.083333333333333L * (arg * arg * arg * arg);
		}, b) - Integral([](const double arg)->double
		{
			return 0.083333333333333L * (arg * arg * arg * arg);
		}, a)));
		qdrtr_values.push_back(mathlib::TrapezoidRule<double>::integrate([](double arg)->double
		{
			return 0.333333333333333L * (arg * arg * arg);
		}, a, b, num_steps).get_integral());
		qdrtr_err.push_back(mathlib::TrapezoidRule<double>::integrate([](double arg)->double
		{
			return 0.333333333333333L * (arg * arg * arg);
		}, a, b, num_steps).get_error());
	}
	std::printf("Dumping the results...\n\n");
	std::printf("#Steps:    Ref_value:    Quadrature_approx:     Delta:       Error:     \n");
	for (auto i = 0; i != num_iters; ++i)
	{
		std::printf("#%d, %.15f %.15f %.15f %.15f\n", steps_vals[i], ref_values.operator[](i), qdrtr_values.operator[](i),
			(qdrtr_values.operator[](i) - ref_values.operator[](i)), qdrtr_err.operator[](i));
	}
	std::printf("Finished Test\n\n");
}

void  test::TrapezoidQuadratureTest::Test_Trapezoid_Quadrature_Varying_Steps()
{
	std::printf("Beginning test of Trapezoid Quadrature\n");
	std::printf("First Run: Numerical Quadrature of polynomial based Integrals...\n");
	std::printf("Testing quadrature convergence, fixed abscissa, varying number of steps\n\n");
	const double a = 0.0L, b = 1.0L;
	const int num_iters = 20;
	std::vector<double> ref_values;
	std::vector<double> qdrtr_values;
	std::vector<double> qdrtr_err;
	unsigned int num_steps = 2; 
	unsigned int steps_vals[20];
	std::printf("Test #1\n");
	std::printf("Test of Integral of type:[x^3/3 dx]\n");
	std::printf("Number of loop iterations=%d\n", num_iters);
	std::printf("Starting abscissa(fixed) a=%.15f,b=%.15f\n", a, b);
	for (auto i = 0; i != num_iters; ++i)
	{
		num_steps <<= 1;
		steps_vals[i] = num_steps;
		ref_values.push_back((Integral([](const double arg)->double
		{
			return 0.083333333333333L * (arg * arg * arg * arg);
		}, b) - Integral([](const double arg)->double
		{
			return 0.083333333333333L * (arg * arg * arg * arg);
		}, a)));
		qdrtr_values.push_back(mathlib::TrapezoidRule<double>::integrate([](double arg)->double
		{
			return 0.333333333333333L * (arg * arg * arg);
		}, a, b, num_steps).get_integral());
		qdrtr_err.push_back(mathlib::TrapezoidRule<double>::integrate([](double arg)->double
		{
			return 0.333333333333333L * (arg * arg * arg);
		}, a, b, num_steps).get_error());
	}
	std::printf("Dumping the results...\n\n");
	std::printf("#Steps:    Ref_value:    Quadrature_approx:     Delta:       Error:     \n");
	for (auto i = 0; i != num_iters; ++i)
	{
		std::printf("#%d, %.15f %.15f %.15f %.15f\n", steps_vals[i], ref_values.operator[](i), qdrtr_values.operator[](i),
			(qdrtr_values.operator[](i) - ref_values.operator[](i)), qdrtr_err.operator[](i));
	}
	std::printf("Finished Test\n\n");
}

// To be used only with small step size because of int overflow.
void  test::TrapezoidQuadratureTest::Test_Trapezoid_Quadrature_Varying_Abscissa_Steps()
{
	std::printf("Beginning test of Trapezoid Quadrature\n");
	std::printf("First Run: Numerical Quadrature of polynomial based Integrals...\n");
	std::printf("Testing Quadrature convergence, varying steps, varying abscissa range\n\n");
	const int num_iters_range = 10;
	const int num_iters_step = 10;
	 double a = 0.0L, b = 1.0L;
	double incra = 0.5L, incrb = 0.5L;
	unsigned int num_steps = 2;
	unsigned int steps_values[num_iters_step * 10];
	std::vector<double> ref_values;
	std::vector<double> qdrtr_values;
	std::vector<double> qdrtr_err;
	std::vector<std::pair<double, double>> abscssa_values;
	std::printf("Test #1\n");
	std::printf("Test of Integral of type:[x^3/3 dx]\n");
	std::printf("Number of abscissa range iterations=%d\n", num_iters_range);
	std::printf("Number of steps per abscissa range=%d\n", num_iters_step);
	std::printf("Starting abscissa range: a=%.15f increment by:%.15f\n", a,incra);
	std::printf("Starting abscissa range: b=%.15f increment by:%.15f\n", b, incrb);
	for (auto i = 0; i != num_iters_range; ++i)
	{
		a += incra;
		b += incrb;
		abscssa_values.push_back(std::pair<double, double>(a, b));
		for (auto j = 0; j != num_iters_step; ++j)
		{
			num_steps <<= 1;
			std::printf("num_steps=%d\n", num_steps);
			steps_values[j] = num_steps;
			ref_values.push_back((Integral([](const double arg)->double{
				return 0.083333333333333L * (arg * arg * arg * arg);
			}, b) - Integral([](const double arg)->double
			{
				 return 0.083333333333333L * (arg * arg * arg * arg);
			}, a)));
			qdrtr_values.push_back(mathlib::TrapezoidRule<double>::integrate([](double arg)->double
			{
				return 0.333333333333333L * (arg * arg * arg);
			}, a, b, num_steps).get_integral());
			qdrtr_err.push_back(mathlib::TrapezoidRule<double>::integrate([](double arg)->double
			{
				return 0.333333333333333L * (arg * arg * arg);
			}, a, b, num_steps).get_error());
		}
	}
	std::printf("Dumping results...\n\n");
	std::printf("Interval:   Ref_Value:   Quadrature_approx:    Delta:    Error: \n");
	for (auto i = 0; i != num_iters_range; ++i)
	{
		std::printf("%.9f-%.9f\n", abscssa_values.operator[](i).first, abscssa_values.operator[](i).second);
		for (auto j = 0; j != num_iters_step; ++j)
		{
			std::printf("%d,%.15f,%.15f,%.15f,%.15f\n",steps_values[j], ref_values.operator[](j), qdrtr_values.operator[](j),
				(qdrtr_values.operator[](j) - ref_values.operator[](j)), qdrtr_err.operator[](j));
		}
	}
	
}

void  test::TrapezoidQuadratureTest::Test_Trapezoid_Quadrature_Transc()
{
	std::printf("Begin Test of Trapezoid Quadrature\n");
	std::printf("Second Run: Numerical Quadrature of Transcendental Functions\n");
	std::printf("Testing Quadrature convergence, fixed interval, fixed steps number\n");
	const double a = 0.0L, b = 1.0L;
	const int num_steps = 1 << 20;
	std::printf("Test #1\n");
	std::printf("Quadrature approximation of PDF function\n");
	std::printf("abscissa: a=%.15f, b=%.15f\n", a, b);
	std::printf("Number of quadrature steps=%d\n", num_steps);


}

void  test::TrapezoidQuadratureTest::Run_Trapezoid_Quadrature_Tests()
{
	Test_Trapezoid_Quadrature();
}

void  test::TrapezoidQuadratureTest::Run_Trapezoid_Varying_Abscissa_Tests()
{
	Test_Trapezoid_Quadrature_Varying_Abscissas();
}

void  test::TrapezoidQuadratureTest::Run_Trapezoid_Varying_Step_Tests()
{
	Test_Trapezoid_Quadrature_Varying_Steps();
}

void  test::TrapezoidQuadratureTest::Run_Trapezoid_Varying_Abscissa_Step_Tests()
{
	unsigned int num_iters_range = 10;
	double a = 0.0L, b = 1.0L, incr = 0.5L;
	
	for (auto i = 0; i != num_iters_range; ++i)
	{
		a += incr;
		b += incr;
		
		Test_Trapezoid_Quadrature_Varying_Steps(a, b);
		
		
	}
}