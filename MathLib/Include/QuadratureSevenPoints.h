
#ifndef _QUADRATURE_SEVEN_POINTS_H_
#define _QUADRATURE_SEVEN_POINTS_H_

#include "MathLibDefinitions.h"
#include "Derivative.h"

namespace  mathlib
{

	template<typename _Ty>  class Qdrtr7Points
	{

	public:

		template<typename Function>  __forceinline  static Qdrtr7Points  integrate(Function, _Ty, _Ty, const int, const int);

		__forceinline const  _Ty  get_error() const;

		__forceinline        _Ty  get_error();

		__forceinline const  _Ty  get_integral() const;

		__forceinline        _Ty  get_integral();

	private:

		_Ty integral;
		_Ty error;
		__forceinline Qdrtr7Points(const _Ty, const _Ty);

		template<typename Function> __forceinline static _Ty compute_error(Function, _Ty, _Ty, _Ty);
	};

	template<typename _Ty>  class NewtonCotes7P
	{

	public:

		__forceinline  NewtonCotes7P();

		__forceinline  NewtonCotes7P(const double, const double, const int, _Ty &functor);

		__forceinline  NewtonCotes7P(const NewtonCotes7P &);

		__forceinline  NewtonCotes7P & integrate(const int);

		__forceinline  std::function<double(double)> get_functor() const;

		__forceinline  double  get_a() const;

		__forceinline  double  get_b() const;

		__forceinline  double  get_integral() const;

		__forceinline  double  get_error() const;

		__forceinline   int     get_n() const;

		

	private:

		__forceinline void  compute_error(const double);
		double a, b, integral, error;
		int n;
		_Ty &functor;
	};


#include "QuadratureSevenPoints.inl"
}
#endif /*_QUADRATURE_SEVEN_POINTS_H_*/