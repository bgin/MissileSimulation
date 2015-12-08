template<typename _Ty> __forceinline mathlib::QdrtrSixPoints<_Ty>::QdrtrSixPoints(const _Ty integr, const _Ty err) : integral(integr), error(err)
{

}

template<typename _Ty> template<typename Function> __forceinline  mathlib::QdrtrSixPoints<_Ty> mathlib::QdrtrSixPoints<_Ty>::integrate(Function f,
	_Ty a, _Ty  b, const int n, const int func_type)
{
	_ASSERT((func_type >= 0) && (func_type <= 1));
	_Ty sum, err, term, h;

	h = (b - a) / (5.0 * static_cast<_Ty>(n - 1));
	term = 0.00347222222222222L * (5.0 * h);
	if (1 >= n)
	{
		sum = 19.0 * f(a) + 75.0 * (f(a + h) + f(a + 4.0 * h)) + 50.0 * (f(a + 2.0 * h) + f(a + 3.0 * h)) + 19.0 * f(b);
		err = std::numeric_limits<_Ty>::quiet_NaN();
		return mathlib::QdrtrSixPoints<_Ty>((term * sum), error);
	}

	sum = 19.0 * f(a) + 75.0 * (f(a + h) + f(a + 4.0 * h)) + 50.0 * (f(a + 2.0 * h) + f(a + 3.0 * h)) + 19.0 * f(b);
	for (auto i = 1; i != n - 1; ++i)
	{
		_Ty x = a + 5 * h * static_cast<_Ty>(i);
		sum += 38.0 * f(x) + 75.0 * (f(x + h) + f(x + 4.0 * h)) + 50.0 * (f(x + 2.0 * h) + f(x + 3.0 * h));
	}

	if (func_type == 0)
		err = compute_error(f, a, b, h);
	else if (func_type == 1)
		err = std::numeric_limits<_Ty>::quiet_NaN();

	return mathlib::QdrtrSixPoints<_Ty>((term * sum), err);
}

template<typename _Ty> template<typename Function> __forceinline  _Ty mathlib::QdrtrSixPoints<_Ty>::compute_error(Function f, _Ty a, _Ty b, _Ty h)
{
	_Ty err_term = 0.02273478835978L * (h * h * h * h * h * h * h);
	const int num_iter = 5;
	auto drvtv = mathlib::DyDx<_Ty>::differentiate(f, (0.5 * (b - a)), h);
	for (auto int = 0; i != num_iter; ++i) drvtv = mathlib::DyDx<_Ty>::differentiate(f, drvtv.get_deriv(), h);

	return err_term * drvtv.get_deriv();

}

template<typename _Ty>  __forceinline  const _Ty mathlib::QdrtrSixPoints<_Ty>::get_integral() const
{
	return this->integral();
}

template<typename _Ty>  __forceinline        _Ty mathlib::QdrtrSixPoints<_Ty>::get_integral()
{
	return this->integral;
}

template<typename _Ty>  __forceinline  const  _Ty mathlib::QdrtrSixPoints<_Ty>::get_error() const
{
	return this->error;
}

template<typename _Ty>  __forceinline         _Ty mathlib::QdrtrSixPoints<_Ty>::get_error()
{
	return this->error;
}


// NewtonCotes6P implementation
template<typename _Ty> __forceinline  mathlib::NewtonCotes6P<_Ty>::NewtonCotes6P()
{

}

template<typename _Ty> __forceinline  mathlib::NewtonCotes6P<_Ty>::NewtonCotes6P(const double aa, const double bb, const int nn, _Ty &Func) :
a(aa), b(bb), n(nn), integral(std::numeric_limits<double>::quiet_NaN()), error(std::numeric_limits<double>::quiet_NaN()), functor(Func)
{

}

template<typename _Ty> __forceinline  mathlib::NewtonCotes6P<_Ty>::NewtonCotes6P(const mathlib::NewtonCotes6P<_Ty> &rhs) :
a(rhs.a), b(rhs.b), n(rhs.n), integral(rhs.integral), error(rhs.integral), functor(rhs.functor)
{

}

template<typename _Ty> __forceinline  mathlib::NewtonCotes6P<_Ty> &  mathlib::NewtonCotes6P<_Ty>::integrate(const int func_type)
{
	_ASSERT((func_type >= 0) && (func_type <= 1));
	double h = 0.0L, term = 0.0L;
	h = (this->b - this->a) / (5.0L * static_cast<double>(this->n - 1));
	term = 0.00347222222222222L * (5.0L * h);
	if (1 >= n)
	{
		this->integral = 19.0L * this->functor(this->a) + 75.0 * (this->functor(this->a + h) + this->functor(this->a + 4.0L * h)) +
			50.0L * (this->functor(this->a + 2.0L * h) + this->functor(this->a + 3.0L * h)) + 19.0L * this->functor(b);
		this->integral = this->integral * term;
		this->error = std::numeric_limits<double>::quiet_NaN();
		return *this;
	}
	this->integral = 19.0L * this->functor(this->a) + 75.0 * (this->functor(this->a + h) + this->functor(this->a + 4.0L * h)) +
		50.0L * (this->functor(this->a + 2.0L * h) + this->functor(this->a + 3.0L * h)) + 19.0L * this->functor(b);
	for (auto i = 1; i != this->n - 1; ++i)
	{
		double x = this->a + 5.0L * h * static_cast<double>(i);
		this->integral += 38.0L * this->functor(x) + 75.0L * (this->functor(x + h) + this->functor(x + 4.0L * h)) +
			50.0L * (this->functor(x + 2.0L * h) + this->functor(x + 3.0L * h));
	}

	/*
     * if 0 call compute_error on polynomial of degree > 6, and on transcendental functions,
	 * otherwise assign quietNaN to this->error member variable.
	 * Not sure how to proceed when integrand does not have 6th derivative.
     */
	if (func_type == 0) 
		this->compute_error(h);
	else if (func_type == 1)
		this->error = std::numeric_limits<double>::quiet_NaN();

	this->integral *= term;
	return *this;
}

template<typename _Ty> __forceinline  void mathlib::NewtonCotes6P<_Ty>::compute_error(double h)
{
	double err_term = 0.02273478835978L * ((this->b - this->a) * (this->b - this->a) * (this->b - this->a) * (this->b - this->a) *
		(this->b - this->a) * (this->b - this->a) * (this->b * this->a));
	const int num_iter = 5;
	auto deriv = mathlib::DyDx<double>::differentiate(this->functor, (0.5L * (this->b - this->a)), h);
	for (auto i = 0; i != num_iter; ++i) deriv = mathlib::DyDx<double>::differentiate(this->functor, deriv.get_deriv(), h);
	this->error *= err_term;
}

template<typename _Ty>  __forceinline  double mathlib::NewtonCotes6P<_Ty>::get_a() const
{
	return this->a;
}
	
template<typename _Ty>  __forceinline  double mathlib::NewtonCotes6P<_Ty>::get_b() const
{
	return this->b;
}

template<typename _Ty>  __forceinline  double mathlib::NewtonCotes6P<_Ty>::get_integral() const
{
	return this->integral;
}

template<typename _Ty>  __forceinline  double mathlib::NewtonCotes6P<_Ty>::get_error() const
{
	return this->error;
}

template<typename _Ty>  __forceinline  int    mathlib::NewtonCotes6P<_Ty>::get_n() const
{
	return this->n;
}


	
