template<typename _Ty> __forceinline mathlib::BoolRule<_Ty>::BoolRule(const _Ty integr, const _Ty err) : integral(integr), error(err)
{

}

template<typename _Ty> __forceinline  const _Ty mathlib::BoolRule<_Ty>::get_integral() const
{
	return this->integral;
}

template<typename _Ty> __forceinline        _Ty mathlib::BoolRule<_Ty>::get_integral()
{
	return this->integral;
}

template<typename _Ty> __forceinline  const  _Ty mathlib::BoolRule<_Ty>::get_error() const
{
	return this->error;
}

template<typename _Ty> __forceinline         _Ty mathlib::BoolRule<_Ty>::get_error()
{
	return this->error;
}

template<typename _Ty>  template<typename Function> __forceinline mathlib::BoolRule<_Ty> mathlib::BoolRule<_Ty>::integrate(Function f, _Ty a, _Ty b, const int n,const int func_type)
{
	_ASSERT((func_type >= 0) && (func_type <= 1));
	_Ty sum, error, term, h;
	h = (b - a) / (4.0 * static_cast<_Ty>(n - 1));
	term = 0.0222222222 * (2.0 * h);
	if (1 >= n)
	{
		sum = 7.0 * f(a) + 32.0 * (f(a + h) + f(a + 3.0L * h)) + 12.0 * f(a + 2.0L * h) + 7.0 * f(b);
		error = std::numeric_limits<_Ty>::quiet_NaN();
		return mathlib::BoolRule<_Ty>(sum * term, error); // TODO initialize error to return from compute error func.Done!
	}

	sum = 7.0 * f(a) + 32.0 * (f(a + h) + f(a + 3 * h)) + 12.0 * f(a + 2 * h) + 7.0 * f(b);
	for (auto i = 1; i != n - 1; ++i)
	{
		_Ty x = a + 4.0 * h * static_cast<_Ty>(i);
		sum += 14.0 * f(x) + 32.0 * (f(x + h) + f(x + 3 * h)) + 12.0 * f(x + 2 * h);
			
	}
	
	if (func_type == 0)
		error = compute_error(f, a, b, h);
	else if (func_type == 1)
		error = std::numeric_limits<_Ty>::quiet_NaN();
	
	return mathlib::BoolRule<_Ty>((sum * term), error);

}

template<typename _Ty>  template<typename Function> __forceinline  _Ty  mathlib::BoolRule<_Ty>::compute_error(Function f, _Ty a, _Ty b, _Ty h)
{
	
	_Ty error_term = 5.16699735449735e-7 * ((b - a) * (b - a) * (b - a) * (b - a) * (b - a) * (b - a) * (b - a));

	auto deriv1 = mathlib::DyDx<_Ty>::differentiate(f, (0.5 * (b - a)), h);
	for (auto i = 0; i != 5; ++i)
	{
		deriv1 = mathlib::DyDx<_Ty>::differentiate(f, deriv1.get_deriv(), h);
		std::printf("x_deriv=%.15f\n", deriv1.get_deriv());
	}
	/*auto deriv2 = mathlib::DyDx<_Ty>::differentiate(f, deriv1.get_deriv(), h);
	auto deriv3 = mathlib::DyDx<_Ty>::differentiate(f, deriv2.get_deriv(), h);
	auto deriv4 = mathlib::DyDx<_Ty>::differentiate(f, deriv3.get_deriv(), h);
	auto deriv5 = mathlib::DyDx<_Ty>::differentiate(f, deriv4.get_deriv(), h);
	auto deriv6 = mathlib::DyDx<_Ty>::differentiate(f, deriv5.get_deriv(), h);*/

	return error_term * deriv1.get_deriv();
	
	
}


template<typename _Ty> __forceinline  mathlib::BoolQdrtr<_Ty>::BoolQdrtr()
{

}

template<typename _Ty> __forceinline  mathlib::BoolQdrtr<_Ty>::BoolQdrtr(const double aa, const double bb, const int nn, _Ty &func) :
a(aa), b(bb), n(nn), functor(func), integral(std::numeric_limits<double>::quiet_NaN()), error(std::numeric_limits<double>::quiet_NaN())
{
  
}

template<typename _Ty>  __forceinline  mathlib::BoolQdrtr<_Ty>::BoolQdrtr(const mathlib::BoolQdrtr<_Ty> &rhs) : a(rhs.a),
b(rhs.b), n(rhs.n), functor(rhs.functor), integral(rhs.integral), error(rhs.error)
{

}

template<typename _Ty>  __forceinline  mathlib::BoolQdrtr<_Ty> & mathlib::BoolQdrtr<_Ty>::integrate(const int func_type)
{
	_ASSERT((func_type >= 0) && (func_type <= 1));

	double h = 0.0L,term = 0.0L;

	h = (this->b - this->a) / (4.0L * static_cast<double>(this->n - 1));
	term = 0.0222222222 * (2.0 * h);
	if (1 >= this->n)
	{
		this->integral = 7.0L * this->functor(this->a) + 32.0L * (this->functor(a + h) + this->functor(a + 3.0L * h)) + 12.0L * this->functor(a + 2.0L * h) +
			7.0L * this->functor(b);
		this->integral *= term;
		this->error = std::numeric_limits<double>::quiet_NaN();
		return *this;
			
	}

	this->integral = 7.0L * this->functor(this->a) + 32.0L * (this->functor(a + h) + this->functor(a + 3.0L * h)) + 12.0L * this->functor(a + 2.0L * h) +
		7.0L * this->functor(b);
	for (auto i = 1; i != this->n - 1; ++i)
	{
		double x = this->a + 4.0L * h * static_cast<double>(i);
		this->integral += 14.0L * this->functor(x) + 32.0L * (this->functor(x + h) + this->functor(x + 3.0L * h)) + 12.0L * this->functor(x + 2.0L * h);
	}

	
	if (func_type == 0)
		compute_error(h);
	else if (func_type == 1)
		this->error = std::numeric_limits<double>::quiet_NaN();
	
	this->integral = term * this->integral;
	return *this;
}

template<typename _Ty> __forceinline   void  mathlib::BoolQdrtr<_Ty>::compute_error(double h)
{
	double err_trm = 5.16699735449735e-7 * ((this->b - this->a) * (this->b - this->a) * (this->b - this->a) *
		(this->b - this->a) * (this->b - this->a) * (this->b - this->a) * (this->b - this->a));
	auto deriv1 = mathlib::DyDx<double>::differentiate(this->functor, (0.5L * (this->b - this->a)), h);
	auto deriv2 = mathlib::DyDx<double>::differentiate(this->functor, deriv1.get_deriv(), h);
	auto deriv3 = mathlib::DyDx<double>::differentiate(this->functor, deriv2.get_deriv(), h);
	auto deriv4 = mathlib::DyDx<double>::differentiate(this->functor, deriv3.get_deriv(), h);
	auto deriv5 = mathlib::DyDx<double>::differentiate(this->functor, deriv4.get_deriv(), h);
	auto deriv6 = mathlib::DyDx<double>::differentiate(this->functor, deriv5.get_deriv(), h);
	this->error = err_trm * deriv6.get_deriv();
}

template<typename _Ty> __forceinline  double  mathlib::BoolQdrtr<_Ty>::get_a() const
{
	return this->a;
}

template<typename _Ty> __forceinline  double  mathlib::BoolQdrtr<_Ty>::get_b() const
{
	return this->b;
}

template<typename _Ty> __forceinline  double  mathlib::BoolQdrtr<_Ty>::get_error() const
{
	return this->error;
}

template<typename _Ty>  __forceinline  double  mathlib::BoolQdrtr<_Ty>::get_integral() const
{
	return this->integral;
}

template<typename _Ty>  __forceinline  int     mathlib::BoolQdrtr<_Ty>::get_n() const
{
	return this->n;
}
	
