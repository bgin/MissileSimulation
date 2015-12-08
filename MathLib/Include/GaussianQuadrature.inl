template<typename _Ty> __forceinline  mathlib::GaussianQdrtr<_Ty>::GaussianQdrtr(const _Ty integr, const _Ty err) : integral(integr),
error(err)
{

}

template<typename _Ty>  template<typename Function> __forceinline  mathlib::GaussianQdrtr<_Ty> mathlib::GaussianQdrtr<_Ty>::integrate(Function f,
	_Ty a, _Ty b)
{
	_Ty sum = 0.0 , err = std::numeric_limits<_Ty>::quiet_NaN();
	static const _Ty x_vals[] = {
		0.1488743389816, 0.4333953941292,
		0.6794095682990, 0.8650633666889,
		0.9739065285171
	};
	static const _Ty w_vals[] = {
		0.2955242247147, 0.26926671930999,
		0.2190863625159, 0.14945134915058,
		0.0666713443086
	};
	_Ty arg_m = 0.5 * (b - a);
	_Ty arg_r = 0.5 * (b + a);
	const int num_iter = 5;
	for (auto i = 0; i != num_iter; ++i)
	{
		_Ty x = arg_r * x_vals[i];
		sum += w_vals[i] * (f(arg_m + x) + f(arg_m - x));
	}

	return mathlib::GaussianQdrtr<_Ty>((sum * arg_r), err);
}

template<typename _Ty> __forceinline  _Ty mathlib::GaussianQdrtr<_Ty>::get_integral() const
{
	return this->integral;
}

template<typename _Ty> __forceinline  _Ty mathlib::GaussianQdrtr<_Ty>::get_error() const
{
	return this->error;
}


template<typename _Ty>  __forceinline  mathlib::GaussQuadrature<_Ty>::GaussQuadrature()
{

}

template<typename _Ty>  __forceinline  mathlib::GaussQuadrature<_Ty>::GaussQuadrature(const double aa, const double bb, _Ty &Func) : a(aa),
b(bb), functor(Func), integral(std::numeric_limits<double>::quiet_NaN())
{

}

template<typename _Ty>  __forceinline  mathlib::GaussQuadrature<_Ty>::GaussQuadrature(const mathlib::GaussQuadrature<_Ty> &rhs) : a(rhs.a),
b(rhs.b), functor(rhs.functor), integral(rhs.integral)
{

}

template<typename _Ty>  __forceinline mathlib::GaussQuadrature<_Ty> & mathlib::GaussQuadrature<_Ty>::integrate()
{
	static const double x[] =
	{
		0.1488743389816L, 0.4333953941292L,
		0.6794095682990L, 0.8650633666889L,
		0.9739065285171L
	};
	static const double w[] =
	{
		0.2955242247147L, 0.26926671930999L,
		0.2190863625159L, 0.14945134915058L,
		0.0666713443086L
	};
	double arg_m = 0.5L * (this->b - this->a);
	double arg_r = 0.5L * (this->b + this->a);
	const int num_iter = 5;

	for (auto i = 0; i != num_iter; ++i)
	{
		double x = arg_r * x[i];
		this->integral += w[i] * (this->functor(arg_m + x) + this->functor(arg_m - x));
	}
	this->integral *= arg_r;
	return *this;
}


template<typename _Ty>  __forceinline  double  mathlib::GaussQuadrature<_Ty>::get_a() const
{
	return this->a;
}

template<typename _Ty>  __forceinline  double  mathlib::GaussQuadrature<_Ty>::get_b() const
{
	return this->b;
}

template<typename _Ty>  __forceinline  double  mathlib::GaussQuadrature<_Ty>::get_integral() const
{
	return this->integral;
}

template<typename _Ty>  __forceinline  std::function<double(double)> mathlib::GaussQuadrature<_Ty>::get_functor() const
{
	return std::function<double(double)>{this->functor};
}
