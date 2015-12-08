
template<typename _Ty> __forceinline mathlib::TrapezoidRule<_Ty>::TrapezoidRule(const _Ty integr, const _Ty err) : integral(integr), error(err)
{

}

template<typename _Ty> __forceinline  const _Ty mathlib::TrapezoidRule<_Ty>::get_integral() const
{
	return this->integral;
}

template<typename _Ty> __forceinline       _Ty  mathlib::TrapezoidRule<_Ty>::get_integral()
{
	return this->integral;
}

template<typename _Ty> __forceinline  const _Ty mathlib::TrapezoidRule<_Ty>::get_error() const
{
	return this->error;
}

template<typename _Ty> __forceinline       _Ty  mathlib::TrapezoidRule<_Ty>::get_error()
{
	return this->error;
}

template<typename _Ty> template<typename Function> __forceinline mathlib::TrapezoidRule<_Ty>  mathlib::TrapezoidRule<_Ty>::integrate(Function f,
	_Ty a, _Ty b, const int n)
{
	_Ty sum, err, h, term;
	if (1 >= n)
	{
		sum = 0.5 * (b - a) * (f(a) + f(b)); err = std::numeric_limits<_Ty>::quiet_NaN();
		return mathlib::TrapezoidRule<_Ty>(sum, err);
	}

	h = (b - a) / static_cast<_Ty>(n);
	sum = 0.5 * (f(a) + f(b));
	for (auto i = 1; i != n; ++i)
	{
		_Ty x = a + h * i;
		sum += f(x);
	}
	
	/*term = 0.08333333333 * ((b - a) * (b - a) * (b - a));
	auto deriv1 = mathlib::DyDx<_Ty>::differentiate(f, (0.5 * (b - a)),h );
	auto deriv2 = mathlib::DyDx<_Ty>::differentiate(f, deriv1.get_deriv(),h );*/
	err = compute_error(f, h, a, b);
	return mathlib::TrapezoidRule<_Ty>((sum * h), err);


}

template<typename _Ty> template<typename Function> __forceinline _Ty mathlib::TrapezoidRule<_Ty>::compute_error(Function f, _Ty h, _Ty a, _Ty b)
{
	_Ty error_term = 0.0833333333333 * (h * h * h);
	auto deriv1 = mathlib::DyDx<_Ty>::differentiate(f, (0.5 * (b - a)), h);
	auto deriv2 = mathlib::DyDx<_Ty>::differentiate(f, deriv1.get_deriv(), h);
	return  error_term * deriv2.get_deriv();
}

template<typename _Ty> __forceinline mathlib::Trapzd<_Ty>::Trapzd()
{

}

template<typename _Ty> __forceinline mathlib::Trapzd<_Ty>::Trapzd(const double aa, const double bb, const int nn,  _Ty &func) :
a(aa), b(bb), integral(std::numeric_limits<double>::quiet_NaN()),error(std::numeric_limits<double>::quiet_NaN()),n(nn), functor(func)
{

}

template<typename _Ty> __forceinline  mathlib::Trapzd<_Ty>::Trapzd(const mathlib::Trapzd<_Ty> &rhs) : a(rhs.a), b(rhs.b), integral(rhs.integral),
error(rhs.error), n(rhs.n), functor(rhs.functor)
{

}

template<typename _Ty> __forceinline mathlib::Trapzd<_Ty> &  mathlib::Trapzd<_Ty>::integrate()
{
	double  h;
	if (1 >= this->n)
	{
		this->integral = 0.5L * (this->b - this->a) * (this->functor(a) + this->functor(b));
		
		return *this;
		 
	}

	h = (this->b - this->a) / static_cast<double>(this->n);
	this->integral = 0.5L * (this->functor(a) + this->functor(b));
	for (auto i = 1; i != this->n; ++i)
	{
		double x = this->a + h * i;
		this->integral += this->functor(x);
	}
	this->integral = this->integral * h;
	compute_error(h);
	//std::printf("integral=%.15f\n", this->integral);
	return *this;
}

// Should be used on not smooth functions.
template<typename _Ty> __forceinline mathlib::Trapzd<_Ty> & mathlib::Trapzd<_Ty>::integrate_refined(const double eps)
{
	const int max_iter = 20;
	
	double oldintgrl = std::numeric_limits<double>::quiet_NaN(), crrntintgrl = 0.0L;
	for (auto i = 0; i != max_iter; ++i)
	{
		this->integrate();
		crrntintgrl = this->get_integral();
		if (i > 10)
		if ((std::fabs(crrntintgrl - oldintgrl)) < (eps * std::fabs(oldintgrl)) ||
			(oldintgrl == 0.0L && crrntintgrl == 0.0L)) return *this;
		std::printf("integral=%.15f, old_integral=%.15f\n", crrntintgrl, oldintgrl);
		oldintgrl = crrntintgrl;
		
	}
	throw std::runtime_error("Too many steps in order for convergence\n");
}

template<typename _Ty> __forceinline  double  mathlib::Trapzd<_Ty>::get_a() const
{
	return this->a;
}

template<typename _Ty> __forceinline  double  mathlib::Trapzd<_Ty>::get_b() const
{
	return this->b;
}

template<typename _Ty> __forceinline  double  mathlib::Trapzd<_Ty>::get_error() const
{
	return this->error;
}

template<typename _Ty> __forceinline  double  mathlib::Trapzd<_Ty>::get_integral() const
{
	return this->integral;
}

template<typename _Ty> __forceinline int  mathlib::Trapzd<_Ty>::get_n() const
{
	return this->n;
}

template<typename _Ty> __forceinline  void  mathlib::Trapzd<_Ty>::compute_error(double h)
{
	double term = 0.0833333333333 * ((this->b - this->a) * (this->b - this->a) * (this->b - this->a));
	auto deriv1 = mathlib::DyDx<double>::differentiate(this->functor, 0.5L * (this->b - this->a), h);
	auto deriv2 = mathlib::DyDx<double>::differentiate(this->functor, deriv1.get_deriv(), h);
	this->error = -term * deriv2.get_deriv();
	std::printf("error=%.15f\n", this->error);
}

	



