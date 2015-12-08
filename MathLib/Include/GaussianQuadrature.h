#ifndef _GAUSSIAN_QUADRATURE_H_
#define _GAUSSIAN_QUADRATURE_H_

#include "MathLibDefinitions.h"
#include "Derivative.h"

namespace mathlib
{

	template<typename _Ty> class GaussianQdrtr
	{

	public:

		template<typename Function> __forceinline static GaussianQdrtr integrate(Function f, _Ty, _Ty);

		__forceinline  _Ty  get_integral() const;

		__forceinline  _Ty  get_error() const;

	private:

		template<typename Function> __forceinline  static _Ty compute_error();

		_Ty integral;
		_Ty error;

		__forceinline GaussianQdrtr(const _Ty, const _Ty);
	};

	template<typename _Ty>  class GaussQuadrature
	{


	public:

	__forceinline	 GaussQuadrature();

	__forceinline    GaussQuadrature(const double, const double, _Ty &functor);

	__forceinline    GaussQuadrature(const GaussQuadrature &);

	__forceinline    GaussQuadrature & integrate();

	__forceinline    double             get_a() const;

	__forceinline    double             get_b() const;

	__forceinline    double             get_integral() const;

	__forceinline    std::function<double(double)> get_functor() const;

	private:

		double a, b, integral;
		_Ty &functor;
	};

#include "GaussianQuadrature.inl"
}
#endif /*_GAUSSIAN_QUADRATURE_H_*/