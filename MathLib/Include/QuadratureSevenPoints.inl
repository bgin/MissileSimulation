template<typename _Ty> __forceinline mathlib::Qdrtr7Points<_Ty>::Qdrtr7Points(const _Ty integr, const _Ty err) : integral(integr), error(err)
{

}

template<typename _Ty>  template<typename Function> __forceinline  mathlib::Qdrtr7Points<_Ty>  mathlib::Qdrtr7Points<_Ty>::integrate(Function f, _Ty a, _Ty b,
	const int n, const int func_type)
{
	_ASSERT((func_type >= 0) && (func_type <= 1));
	_Ty sum, err, term, h;
	h = (b - a) / (6.0 * static_cast<_Ty>(n - 1));
	term = 0.00714285714 * h;

	if (1 >= n)
	{
		sum = 41.0 * f(a) + 216.0 * (f(a + h) + f(a + 5.0 * h)) + 27.0 * f((a + 2.0 * h) + f(a + 4.0 * h) +
			272.0 * f(a + 3.0 * h) + 41.0 * f(b);
		
		err = std::numeric_limits<_Ty>::quiet_NaN();
		return mathlib::Qdrtr7Points<_Ty>(sum * term, err);
	}
	sum = 41.0 * f(a) + 216.0 * (f(a + h) + f(a + 5.0 * h)) + 27.0 * f((a + 2.0 * h) + f(a + 4.0 * h) +
		272.0 * f(a + 3.0 * h) + 41.0 * f(b);
	for (auto i = 1; i != n - 1; ++i)
	{
		_Ty x = a + 6.0 * h * static_cast<_Ty>(i);
		sum += 82.0 * f(x) + 216.0 * (f(x + h) + f(x + 5.0 * h)) + 27.0 * (f(x + 2.0 * h) + f(x + 4.0 * h)) +
			272.0 * f(x + 3.0 * h);
	}

	if (func_type == 0)
		compute_error(f, a, b, h);
	else if (func_type == 1)
		err = std::numeric_limits<_Ty>::quiet_NaN();

	return mathlib::Qdrtr7Points<_Ty>(sum * term, err);
}

template<typename _Ty> template<typename Function> __forceinline _Ty mathlib::Qdrtr7Points<_Ty>::compute_error(Function f, _Ty a, _Ty b, _Ty h)
{
	_Ty err_term = 0.0064285714 * (h * h * h * h * h * h * h * h * h);
	const num_iter = 6;
	auto dx = mathlib::DyDx<_Ty>::differentiate(f, (0.5 * (b - a)), h);
	for (auto i = 0; i != num_iter; ++i) dx = mathlib::DyDx<_Ty>::differentiate(f, dx.get_deriv(), h);

	return err_term * dx.get_deriv();
}

template<typename _Ty>  __forceinline  const  _Ty  mathlib::Qdrtr7Points<_Ty>::get_integral() const
{
	return this->integral;
}

template<typename _Ty>  __forceinline         _Ty  mathlib::Qdrtr7Points<_Ty>::get_integral()
{
	return this->integral;
}

template<typename _Ty>  __forceinline  const   _Ty  mathlib::Qdrtr7Points<_Ty>::get_error() const
{
	return this->error;
}

template<typename _Ty>  __forceinline          _Ty  mathlib::Qdrtr7Points<_Ty>::get_error()
{
	return this->error;
}



template<typename _Ty>  __forceinline mathlib::NewtonCotes7P<_Ty>::NewtonCotes7P()
{

}

template<typename _Ty>  __forceinline mathlib::NewtonCotes7P<_Ty>::NewtonCotes7P(const double aa, const double bb, const int nn,
	_Ty &Func) : a(aa), b(bb), n(nn), functor(Func), integral(std::numeric_limits<double>::quiet_NaN()), error(std::numeric_limits<double>::quiet_NaN())
{

}

template<typename _Ty>  __forceinline mathlib::NewtonCotes7P<_Ty>::NewtonCotes7P(const mathlib::NewtonCotes7P<_Ty> &rhs) : a(rhs.a),
b(rhs.b), n(rhs.n), functor(rhs.functor), integral(rhs.integral), error(rhs.error)
{

}

template<typename _Ty>  __forceinline mathlib::NewtonCotes7P<_Ty> & mathlib::NewtonCotes7P<_Ty>::integrate(const int func_type)
{
	_ASSERT((func_type >= 0) && (func_type <= 1));
	double h(0.0L), term(0.0L);
	h = (this->b - this->a) / (6.0L * static_cast<double>(this->n - 1));
	term = 0.00714285714L * h;
	if (1 >= this->n)
	{
		this->integral = 41.0L * this->functor(this->a) + 216.0L * (this->functor(this->a + h) + this->functor(this->a + 5.0L * h)) +
			27.0L * (this->functor(this->a + 2.0L * h) + this->functor(this->a + 4.0L * h)) + 272.0L * this->functor(this->a + 4.0L * h) +
			41.0L * this->functor(this->b);
		this->integral *= term;
		this->error = std::numeric_limits<double>::quiet_NaN();
		return *this;
	}

	this->integral = 41.0L * this->functor(this->a) + 216.0L * (this->functor(this->a + h) + this->functor(this->a + 5.0L * h)) +
		27.0L * (this->functor(this->a + 2.0L * h) + this->functor(this->a + 4.0L * h)) + 272.0L * this->functor(this->a + 4.0L * h) +
		41.0L * this->functor(this->b);
	for (auto i = 1; i != this->n - 1; ++i)
	{
		double x = this->a + 6.0L * h * static_cast<double>(i);
		this->integral += 82.0L * this->functor(x) + 216.0L * (this->functor(x + h) + this->functor(x + 5.0L * h)) +
			27.0L * (this->functor(x + 2.0L * h) + this->functor(x + 4.0L * h)) + 272.0L * this->functor(this->a + 4.0L * h);
	}

	if (func_type == 0)
		compute_error(h);
	else if (func_type == 1)
		this->error = std::numeric_limits<double>::quiet_NaN();

	this->integral *= term;
	return *this;
}

template<typename _Ty> __forceinline  void  mathlib::NewtonCotes7P<_Ty>::compute_error(const double h)
{
	double err_trm = 0.0064285714L * (h * h * h * h * h * h * h);
	const int num_iters = 6;
	auto dx = mathlib::DyDx<double>::differentiate(this->functor, (0.5L * (this->b - this->a)), h);
	for (auto i = 0; i != num_iters; ++i) dx = mathlib::DyDx<double>::differentiate(this->functor, dx.get_deriv(), h);

	this->error = err_trm * dx.get_deriv();
}

template<typename _Ty>  __forceinline  std::function<double(double)> mathlib::NewtonCotes7P<_Ty>::get_functor() const
{
	return std::function<double(double)>{this->functor};
}

template<typename _Ty>  __forceinline  double  mathlib::NewtonCotes7P<_Ty>::get_a() const
{
	return this->a;
}

template<typename _Ty>  __forceinline  double  mathlib::NewtonCotes7P<_Ty>::get_b() const
{
	return this->b;
}

template<typename _Ty>  __forceinline  double  mathlib::NewtonCotes7P<_Ty>::get_integral() const
{
	return this->integral;
}

template<typename _Ty>  __forceinline  double  mathlib::NewtonCotes7P<_Ty>::get_error() const
{
	return this->error;
}

template<typename _Ty>  __forceinline  int     mathlib::NewtonCotes7P<_Ty>::get_n() const
{
	return this->n;
}