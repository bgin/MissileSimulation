#ifndef _TRAPEZOID_QUADRATURE_H_
#define _TRAPEZOID_QUADRATURE_H_

#include "MathLibDefinitions.h"
#include "Derivative.h"

namespace  mathlib
{

	template<typename _Ty> class TrapezoidRule
	{


	public:

		template<typename Function> __forceinline static TrapezoidRule integrate(Function, _Ty, _Ty, const int);

		__forceinline const _Ty  get_integral() const;

		__forceinline       _Ty  get_integral();

		__forceinline const  _Ty get_error() const;

		__forceinline       _Ty  get_error();

	private:

		_Ty integral;

		_Ty error;

		__forceinline  TrapezoidRule(const _Ty, const _Ty);

		template<typename Function> __forceinline static _Ty compute_error(Function, _Ty, _Ty, _Ty);
	};

	// Another implementation of templated Trapezoid Quadrature.
	template< typename _Ty> class Trapzd
	{

	public:

		__forceinline Trapzd();

		__forceinline Trapzd(const double, const double, const int,_Ty &functor);

		__forceinline Trapzd(const Trapzd &);

		__forceinline Trapzd & integrate();

		__forceinline Trapzd & integrate_refined(const double);

		__forceinline double get_integral() const;

		__forceinline double get_a() const;

		__forceinline double get_b() const;

		

		__forceinline double get_error() const;

		__forceinline int  get_n() const;

	private:

		__forceinline  void compute_error(double);

		double a, b, integral,error;
		int n;
		_Ty &functor;
	};

#include "TrapezoidQuadrature.inl"
}
#endif /*_TRAPEZOID_QUADRATURE_H_*/