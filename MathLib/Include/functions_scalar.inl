

template<typename _Ty> __forceinline  std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type FastScalarFunctions<_Ty>::fastcot(const _Ty& arg)
{
#if defined _DEBUG
	_ASSERTE(std::is_floating_point<_Ty>::value);
#else
	if(!std::is_floating_point<_Ty>::value)
	{
		throw std::runtime_error(std::string("Expected Floating-Point Value in FastScalarFunctions::fastcot\n"));
	}
#endif

	
	if ((std::fabs(arg)) > mathlib::MathConstants::PI_DBL())
	{
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1 = std::numeric_limits<double>::quiet_NaN();
		return s1;
	}
	else if ((std::fabs(-arg)) > mathlib::MathConstants::PI_DBL())
	{
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1 = std::numeric_limits<double>::quiet_NaN();
		return s1;
	}
	else
	{
		_Ty sum;
		const auto coeff1 = (-0.333333333333333333333333);
		const auto coeff2 = (-0.022222222222222222222222);
		const auto coeff3 = (-0.002116402116402116402116);
		const auto coeff4 = (-0.000211640211640211640211);
		const auto coeff5 = (-0.000021377799155576933354);
		const auto coeff6 = (-2.16440428080639720851361e-6);
		const auto coeff7 = (-2.19259478518737777997037e-7);
		const auto coeff8 = (-2.22146087899796790760584e-8);
		const auto coeff9 = (-2.25078465168089928542084E-9);
		const auto coeff10 = (-2.28051512045921828658638e-10);
		const auto coeff11 = (-2.31064325990026240965325e-11);
		const auto coeff12 = (-2.34117068198248839592094e-12);
		_Ty invx = 1.0 / arg;
		_Ty sqrd_x = arg * arg;
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1;
	    s1 = invx + arg * (coeff1 + sqrd_x * (coeff2 + sqrd_x * (coeff3 + sqrd_x * (coeff4 + sqrd_x * (coeff5 + sqrd_x * (coeff6 + sqrd_x * (coeff7 + sqrd_x *
			(coeff8 + sqrd_x * (coeff9 + sqrd_x * (coeff10 + sqrd_x * (coeff1 + sqrd_x * (coeff12 + sqrd_x))))))))))));
		return s1;
	}
	
}

template<typename _Ty> __forceinline  std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type FastScalarFunctions<_Ty>::fastsin(const _Ty& arg)
{
#if defined _DEBUG
	_ASSERTE(std::is_floating_point<_Ty>::value);
#else
	if(!std::is_floating_point<_Ty>::value)
	{
		throw std::runtime_error(std::string("Expected Floating-Point Value in FastScalarFunctions::fastsin\n"));
	}
#endif

	if ((std::fabs(arg)) > mathlib::MathConstants::HALF_PI_DBL())
	{
		std::enable_if < std::is_floating_point<_Ty>::value, _Ty>::type s1 = ::sin(arg);
		return s1;
	}
	else if ((std::fabs(-arg)) > mathlib::MathConstants::HALF_PI_DBL())
	{
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1 = ::sin(-arg);
		return s1;
	}
	else
	{
		
		const auto coeff1 = -0.16666666666666666;
		const auto coeff2 = 0.00833333333333333;
		const auto coeff3 = -1.9841269841269841e-4;
		const auto coeff4 = 2.75573192239858906e-6;
		const auto coeff5 = -2.5052108385441718e-8;
		const auto coeff6 = 1.60590438368216145e-10;
		const auto coeff7 = -7.6471637318198164e-13;
		const auto coeff8 = 2.81145725434552076e-15;
		const auto coeff9 = -8.2206352466243297e-18;
		const auto coeff10 = 1.95729410633912612e-20;
		const auto coeff11 = -3.8681701706306840e-23;
		_Ty sqrd_arg = arg * arg;
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1;
		s1 = arg + arg * sqrd_arg * (coeff1 + sqrd_arg * (coeff2 + sqrd_arg * (coeff3 + sqrd_arg * (coeff4 + sqrd_arg * (coeff5 + sqrd_arg * (coeff6 + sqrd_arg
			* (coeff7 + sqrd_arg * (coeff8 + sqrd_arg * (coeff9 + sqrd_arg * (coeff10 + sqrd_arg * (coeff11 + sqrd_arg)))))))))));
		
		return s1;
	}
	
}

template<typename _Ty> __forceinline  std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type FastScalarFunctions<_Ty>::fastcos(const _Ty& arg)
{

	if ((std::fabs(arg)) > mathlib::MathConstants::HALF_PI_DBL())
	{
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1 = ::cos(arg);
		return s1;
	}
	else if ((std::fabs(arg)) < std::numeric_limits<_Ty>::epsilon())
	{
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1 = ::cos(arg);
		return s1;
	}
	else
	{
		const _Ty coeff1 = -0.50000000000000000;
		const _Ty coeff2 = 0.041666666666666666;
		const _Ty coeff3 = -0.00138888888888888;
		const _Ty coeff4 = 0.000024801587301587;
		const _Ty coeff5 = -2.75573192239858906e-7;
		const _Ty coeff6 = 2.087675698786809897e-9;
		const _Ty coeff7 = -1.14707455977297247e-11;
		const _Ty coeff8 = 4.77947733238738529e-14;
		const _Ty coeff9 = -1.56192069685862264e-16;
		const _Ty coeff10 = 4.11031762331216485e-19;
		const _Ty coeff11 = -8.8967913924505732e-22;
		const _Ty one = 1.0e+0;
		_Ty sqrd_arg = arg * arg;
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1;
		s1 = one + sqrd_arg * (coeff1 + sqrd_arg * (coeff2 + sqrd_arg * (coeff3 + sqrd_arg * (coeff4 + sqrd_arg * (coeff5 + sqrd_arg * (coeff6 + sqrd_arg *
			(coeff7 + sqrd_arg * (coeff8 + sqrd_arg * (coeff9 + sqrd_arg * (coeff10 + sqrd_arg * (coeff11 + sqrd_arg)))))))))));
		return s1;
 	}
}

template<typename _Ty> __forceinline  std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type FastScalarFunctions<_Ty>::fasttan(const _Ty& arg)
{
	if ((std::fabs(arg)) > mathlib::MathConstants::HALF_PI_DBL())
	{
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1 = std::tan(arg);
		return s1;
	}
	else if ((std::fabs(arg)) < std::numeric_limits<_Ty>::epsilon())
	{
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1 = std::tan(arg);
		return s1;
	}
	else
	{
		const _Ty coeff1 = 0.33333333333333333;
		const _Ty coeff2 = 0.13333333333333333;
		const _Ty coeff3 = 0.05396825396825396;
		const _Ty  coeff4 = 0.02186948853615520;
		const _Ty coeff5 = 0.00886323552990219;
		const _Ty coeff6 = 0.00359212803657248;
		const _Ty coeff7 = 0.00145583438705131;
		const _Ty coeff8 = 0.00059002744094558;
		const _Ty coeff9 = 0.00023912911424355;
		const _Ty coeff10 = 0.0000969153795692;
		const _Ty coeff11 = 0.00003927832388331;
		_Ty sqrd_arg = arg * arg;
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1;
		s1 = arg + arg * sqrd_arg * (coeff1 + sqrd_arg * (coeff2 + sqrd_arg * (coeff3 + sqrd_arg * (coeff4 + sqrd_arg * (coeff5 + sqrd_arg *
			(coeff6 + sqrd_arg * (coeff7 + sqrd_arg * (coeff8 + sqrd_org * (coeff9 + sqrd_arg * (coeff10 + sqrd_arg * (coeff11 + sqrd_arg)))))))))));
		return s1;
	}
}

template<typename _Ty>  __forceinline  std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type FastScalarFunctions<_Ty>::fastexp(const _Ty& arg)
{
	if ((std::fabs(arg)) < 3.0)
	{
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1 = std::exp(arg);
		return s1;
	}
	else
	{
		const _Ty coeff1 = 1.0e+00;
		const _Ty coeff2 = 0.5;
		const _Ty coeff3 = 0.166666666666666666;
		const _Ty coeff4 = 0.041666666666666666;
		const _Ty coeff5 = 0.008333333333333333;
		const _Ty coeff6 = 0.001388888888888888;
		const _Ty coeff7 = 0.001388888888888888;
		const _Ty coeff8 = 0.000198412698412698;
		const _Ty coeff9 = 0.000024801587301587;
		const _Ty coeff10 = 2.755731922398589065e-6;
		const _Ty coeff11 = 2.755731922398589065e-7;
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1;
		s1 = 1.0 + arg * coeff1 + arg * (coeff2 + arg * (coeff3 + arg * (coeff4 + arg * (coeff5 + arg * (coeff6 + arg * (coeff7 + arg * (
			coeff8 + arg * (coeff9 + arg * (coeff10 + arg * (coeff11 + arg))))))))));
		return s1;
	}
}

template<typename _Ty> __forceinline  std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type FastScalarFunctions<_Ty>::fastcsc(const _Ty& arg)
{
	if ((std::fabs(arg) > mathlib::MathConstants::PI_DBL()))
	{
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1 = std::numeric_limits<_Ty>::quiet_NaN();
		return s1;
	}
	else if (arg < mathlib::MathConstants::NEG_PI_DBL())
	{
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1 = std::numeric_limits<_Ty>::quiet_NaN();
		return s1;
	}
	else
	{
		const _Ty coeff1 = 0.166666666666666;
		const _Ty coeff2 = 0.019444444444444;
		const _Ty coeff3 = 0.002050264550264;
		const _Ty coeff4 = 0.000209986772486;
		const _Ty coeff5 = 0.000021336045641;
		const _Ty coeff6 = 2.163347442778659e-6;
		const _Ty coeff7 = 2.192327134456764e-7;
		const _Ty coeff8 = 2.2213930853920414e-8;
		const _Ty coeff9 = 2.2507674795567867e-9;
		const _Ty coeff10 = 2.280510770721821e-10;
		const _Ty coeff11 = 2.310642158099696e-11;
		_Ty inv = 1.0 / arg;
		_Ty sqrd = arg * arg;
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1;
		s1 = inv + arg * (coeff1 + sqrd * (coeff2 + sqrd * (coeff3 + sqrd * (coeff4 + sqrd * (coeff5 + sqrd * (coeff6 + sqrd * (coeff7 + sqrd * (
			coeff8 + sqrd * (coeff9 + sqrd * (coeff10 + sqrd * (coeff11 + sqrd)))))))))));
		return s1;
		
	}
}

template<typename _Ty> __forceinline  std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type  FastScalarFunctions<_Ty>::fastsec(const _Ty& arg)
{
	if ((std::fabs(arg)) > mathlib::MathConstants::HALF_PI_DBL())
	{
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1 = std::numeric_limits<_Ty>::quiet_NaN();
		return s1;
	}
	else if (arg < mathlib::MathConstants::NEG_HALF_PI_DBL())
	{
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1 = std::numeric_limits<_Ty>::quiet_NaN();
		return s1;
	}
	else
	{
		const _Ty coeff1 = 0.500000000000000;
		const _Ty coeff2 = 0.208333333333333;
		const _Ty coeff3 = 0.084722222222222;
		const _Ty coeff4 = 0.034350198412698;
		const _Ty coeff5 = 0.013922233245149;
		const _Ty coeff6 = 0.005642496810031;
		const _Ty coeff7 = 0.002286819095164;
		const _Ty coeff8 = 0.000926812927377;
		const _Ty coeff9 = 0.000375623133852;
		const _Ty coeff10 = 0.00015223432221;
		const _Ty coeff11 = 0.00006169824687;
		_Ty sqrd = arg * arg;
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1;
		s1 = 1.0 + sqrd * (coeff1 + sqrd * (coeff2 + sqrd * (coeff3 + sqrd * (coeff + sqrd * (coeff5 + sqrd * (coeff6 + sqrd * (coeff7 + sqrd * (
			coeff8 + sqrd * (coeff9 + sqrd * (coeff10 + sqrd * (coeff11 + sqrd))))))))))));
		return s1;
		
	}
}

template<typename _Ty> __forceinline std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type FastScalarFunctions<_Ty>::fastarcsin(const _Ty& arg)
{
	if ((std::fabs(arg)) > 1.0)
	{
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1 = std::numeric_limits<_Ty>::quiet_NaN();
		return s1;
	}
	else if (arg < -1.0)
	{
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1 = std::numeric_limits<_Ty>::quiet_NaN();
		return s1;
	}
	else
	{
		const _Ty coeff1 = 0.16666666666666666;
		const _Ty coeff2 = 0.07500000000000000;
		const _Ty coeff3 = 0.04464285714285714;
		const _Ty coeff4 = 0.03038194444444444;
		const _Ty coeff5 = 0.02237215909090909;
		const _Ty coeff6 = 0.01735276442307692;
		const _Ty coeff7 = 0.01396484375000000;
		const _Ty coeff8 = 0.01155180089613970;
		const _Ty coeff9 = 0.00976160952919407;
		const _Ty coeff10 = 0.0083903358096168;
		const _Ty coeff11 = 0.0073125258735988;
		_Ty sqrd = arg * arg;
		std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type s1;
		s1 = arg + arg * sqrd * (coeff1 + sqrd * (coeff2 + sqrd * (coeff3 + sqrd * (coeff4 + sqrd * (coeff5 + sqrd * (coeff6 + sqrd * (coeff7 +
			sqrd * (coeff8 + sqrd * (coeff9 + sqrd * (coeff10 + sqrd * (coeff11 + sqrd)))))))))));
		return s1;
	}
}

