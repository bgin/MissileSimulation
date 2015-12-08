
template<typename _Ty> __forceinline mathlib::DyDx<_Ty>::DyDx(const _Ty der, const _Ty err) : deriv(der), error(err)
{
	
}

template<typename _Ty> __forceinline _Ty mathlib::DyDx<_Ty>::get_deriv() const
{
	return this->deriv;
}

template<typename _Ty> __forceinline _Ty mathlib::DyDx<_Ty>::get_error() const
{
	return this->error;
}

/*template<typename _Ty> __forceinline mathlib::DyDx<_Ty>  mathlib::DyDx<_Ty>::test1(const _Ty arg1, const _Ty arg2)
{
	return mathlib::DyDx<_Ty>(arg1, arg2);
}*/


template<typename _Ty> template<typename Function> __forceinline mathlib::DyDx<_Ty> mathlib::DyDx<_Ty>::differentiate(Function f, _Ty x, _Ty h)
{
	const int numtabs = 10;
	const double con = 1.4L, con2 = (con * con);
	const double big_val = DBL_MAX;
	const double safe_val = 2.0L;
	_Ty error, derivative, errort;
	double hh, fac;
	_Ty **a = mathlib::AllocateVec2D<_Ty>::allocate2D(numtabs, numtabs);
	if (a == nullptr) throw std::runtime_error("Failed to allocate memory for array a\n");

	if (h == 0.0) throw std::runtime_error("h cannot be zero\n");

	

	hh = h;
	a[0][0] = (f(x + hh) - f(x - hh)) / (2.0L * hh);
	//std::printf("a[0][0] = %.15f\n", a[0][0]);
	error = big_val;
	for (auto i = 1; i < numtabs; ++i)
	{
		hh /= con;
		a[0][i] = (f(x + hh) - f(x - hh)) / (2.0L*hh);
		//std::printf("a[0][%d]=%.15f\n", i, a[0][i]);
		fac = con2;
		for (auto j = 1; j <= i; ++j)
		{
			a[j][i] = (a[j - 1][i] * fac - a[j - 1][i - 1]) / (fac - 1.0);
			//std::printf("a[%d][%d]=%.15f\n", j, i, a[j][i]);
			fac = con2*fac;
			errort = std::fmax(fabs(a[j][i] - a[j - 1][i]), fabs(a[j][i] - a[j - 1][i - 1]));
			if (errort <= error)
			{
				error = errort;
				derivative = a[j][i];
			}
		}
		if (fabs(a[i][i] - a[i - 1][i - 1]) >= safe_val * error) break;
	}

	mathlib::AllocateVec2D<_Ty>::deallocate2D(a);

	return mathlib::DyDx<_Ty>(derivative, error);
}

template<typename _Ty> template<typename Function> __forceinline mathlib::DyDx<_Ty> mathlib::DyDx<_Ty>::differentiate2(Function f,
	_Ty x,_Ty h)
{
	if (std::fabs(h) < std::numeric_limits<_Ty>::epsilon()) throw std::runtime_error("h cannot be 0.0 in differentiate2\n");
	
	//_Ty temp = x + h;
	// h = temp - x;
	 h = std::sqrt(std::numeric_limits<_Ty>::epsilon()) * (std::fabs(x) + std::sqrt(std::numeric_limits<_Ty>::epsilon()));
	_Ty ans = (f(x + h) - f(x - h)) / (2.0L * h);
	_Ty err = std::numeric_limits<double>::epsilon() * std::fabs((f(x) / h));
	
	return mathlib::DyDx<_Ty>(ans, err);
}