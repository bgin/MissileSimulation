template<typename _Ty> __forceinline  mathlib::Qdrtr8Points<_Ty>::Qdrtr8Points(const _Ty integr, const _Ty err) : integral(integr), error(err)
{

}

template<typename _Ty> template<typename Function> __forceinline  mathlib::Qdrtr8Points<_Ty> mathlib::Qdrtr8Points<_Ty>::integrate(Function f,
	_Ty a, _Ty b, const int n, const int func_type)
{
	_ASSERT((func_type >= 0) && (func_type <= 1));
	_Ty term, h, sum, err, oldsum;
		const double small_eps = 1.0e-8;
		h = (b - a) / (7.0 * static_cast<_Ty>(n - 1));
		term = 4.050925925925e-4 * h;
		if (1 >= n)
		{
			sum = 751.0 * f(a) + 3577.0 * (f(a + h) + f(a + 6.0 * h)) + 1323.0 * (f(a + 2.0 * h) + f(a + 5.0 * h)) + 
				2989.0 * (f(a + 3.0 * h) + f(a + 4.0 * h)) + 751.0 * f(b);
			err = std::numeric_limits<_Ty>::quiet_NaN();
			return mathlib::Qdrtr8Points<_Ty>((sum * term), err);
		}
		oldsum = 1.0e-30;
		sum = 751.0 * f(a) + 3577.0 * (f(a + h) + f(a + 6.0 * h)) + 1323.0 * (f(a + 2.0 * h) + f(a + 5.0 * h)) +
			2989.0 * (f(a + 3.0 * h) + f(a + 4.0 * h)) + 751.0 * f(b);
		for (auto i = 1; i != n - 1; ++i)
		{
			_Ty x = a + 7.0 * h * static_cast<_Ty>(i);
			sum += 1502.0 * f(x) + 3577.0 * (f(x + h) + f(x + 6.0 * h)) + 1323.0 * (f(x + 2.0 * h) + f(x + 5.0 * h)) +
				2809.0 * (f(x + 3.0 + h) + f(x + 4.0 * h));
			if (std::fabs(sum - oldsum) < small_eps * std::fabs(olsdum)) {
				oldsum = sum;
				break;
			}
				
		}
		if (func_type == 0)
			err = compute_error(f, a, b, h);
		else if (func_type == 1)
			err = std::numeric_limits<_Ty>::quiet_NaN();

		return mathlib::Qdrtr8Points<_Ty>(term * sum, err);
}

template<typename _Ty> template<typename Function> __forceinline  _Ty mathlib::Qdrtr8Points<_Ty>::compute_error(Function f, _Ty a, _Ty b, _Ty h)
{
	_Ty err_term = 0.015785108 * (h * h * h  * h  * h * h * h * h  * h);
	const int iter_num = 7;
	auto dx = mathlib::DyDx<_Ty>::differentiate(f, (0.5 * (b - a)), h);
	for (auto i = 0; i != iter_num; ++i) dx = mathlib::DyDx<_Ty>::differentiate(f, dx.get_deriv(), h);

	return err_term * dx.get_deriv;
}

template<typename _Ty> __forceinline  const _Ty  mathlib::Qdrtr8Points<_Ty>::get_integral() const
{
	return this->integral;
}

template<typename _Ty>  __forceinline       _Ty  mathlib::Qdrtr8Points<_Ty>::get_integral()
{
	return this->integral;
}

template<typename _Ty>  __forceinline const  _Ty  mathlib::Qdrtr8Points<_Ty>::get_error() const
{
	return this->error;
}

template<typename _Ty>  __forceinline        _Ty  mathlib::Qdrtr8Points<_Ty>::get_error()
{
	return this->error;
}



template<typename _Ty>  __forceinline  mathlib::NewtonCotes8P<_Ty>::NewtonCotes8P()
{

}

template<typename _Ty>  __forceinline  mathlib::NewtonCotes8P<_Ty>::NewtonCotes8P(const double aa, const double bb, const int nn, _Ty &Func) : a(aa),
b(bb), n(nn), functor(Func), integral(std::numeric_limits<double>::quiet_NaN()), error(std::numeric_limits<double>::quiet_NaN())
{

}

template<typename _Ty>  __forceinline   mathlib::NewtonCotes8P<_Ty>::NewtonCotes8P(const mathlib::NewtonCotes8P<_Ty> &rhs) :
a(rhs.a), b(rhs.b), n(rhs.n), functor(rhs.functor), integral(rhs.integral), error(rhs.error)
{

}

template<typename _Ty>  __forceinline   mathlib::NewtonCotes8P<_Ty> & mathlib::NewtonCotes8P<_Ty>::integrate(const int func_type)
{
	_ASSERT((func_type >= 0) && (func_type <= 1));
	double term, h;
	h = (this->b - this->a) / (7.0L * static_cast<double>(this->n - 1));
	term = 4.050925925925e-4L * h;
	if (1 >= n)
	{
		this->integral = 751.0L * this->functor(this->a) + 3577.0L * (this->functor(this->a + h) + this->functor(this->a + 6.0L * h)) +
			1323.0L * (this->functor(this->a + 2.0L * h) + this->functor(this->a + 5.0L * h)) + 2989.0L * (this->functor(this->a + 3.0L * h) +
			this->functor(this->a + 4.0L * h)) + 751.0L * this->functor(this->b);
		this->error = std::numeric_limits<double>::quiet_NaN();
		return *this;
	}
	this->integral = 751.0L * this->functor(this->a) + 3577.0L * (this->functor(this->a + h) + this->functor(this->a + 6.0L * h)) +
		1323.0L * (this->functor(this->a + 2.0L * h) + this->functor(this->a + 5.0L * h)) + 2989.0L * (this->functor(this->a + 3.0L * h) +
		this->functor(this->a + 4.0L * h)) + 751.0L * this->functor(this->b);
	for (auto i = 1; i != this->n - 1; ++i)
	{
		double x = this->a + 7.0L * h * static_cast<double>(i);
		this->integral += 1502.0L * this->functor(x) + 3577.0L * (this->functor(x + h) + this->functor(x + 6.0L * h)) +
			1323.0L * (this->functor(x + 2.0L * h) + this->functor(x + 5.0L * h)) + 2989.0L * (this->functor(x + 3.0L * h) + this->functor(x + 4.0L * h));
	}

	if (func_type == 0)
		this->compute_error(h);
	else if (func_type == 1)
		this->error = std::numeric_limits<double>::quiet_NaN();

	this->intergal *= term;
	return *this;

}

template<typename _Ty>  __forceinline  void  mathlib::NewtonCotes8P<_Ty>::compute_error(const double h)
{
	double err_term = 0.015785108L * (h * h * h  * h  * h * h * h * h  * h);
	const int num_iters = 7;
	auto dx = mathlib::DyDx<double>::differentiate(this->functor, (0.5L * (this->b - this->a)), h);
	for (auto i = 0; i != num_iters; ++i) dx = mathlib::DyDx<double>::differentiate(this->functor, dx.get_deriv(), h);

	this->error = err_term * dx.get_deriv();
}

template<typename _Ty>  __forceinline  double mathlib::NewtonCotes8P<_Ty>::get_a() const
{
	return this->a;
}

template<typename _Ty>  __forceinline  double mathlib::NewtonCotes8P<_Ty>::get_b() const
{
	return this->b;
}

template<typename _Ty>  __forceinline  double mathlib::NewtonCotes8P<_Ty>::get_integral() const
{
	return this->integral;
}

template<typename _Ty>  __forceinline  double mathlib::NewtonCotes8P<_Ty>::get_error() const
{
	return this->error;
}

template<typename _Ty> __forceinline  std::function<double(double)> mathlib::NewtonCotes8P<_Ty>::get_functor() const
{
	return std::function < double(double)>{this->functor};
}

template<typename _Ty> __forceinline  int  mathlib::NewtonCotes8P<_Ty>::get_n() const
{
	return this->n;
}

