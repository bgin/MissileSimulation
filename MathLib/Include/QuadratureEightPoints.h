#ifndef _QUADRATURE_EIGHT_POINTS_H_
#define _QUADRATURE_EIGHT_POINTS_H_

#include "MathLibDefinitions.h"
#include "Derivative.h"

namespace mathlib
{

	template<typename _Ty>  class Qdrtr8Points
	{

	public:

		template<typename Function>  __forceinline static Qdrtr8Points integrate(Function, _Ty, _Ty, const int, const int);

		__forceinline const _Ty  get_integral() const;

		__forceinline       _Ty  get_integral();

		__forceinline const _Ty  get_error() const;

		__forceinline       _Ty  get_error();

	private:

		template<typename Function>  __forceinline static  _Ty compute_error(Function, _Ty, _Ty, _Ty);
		_Ty integral;
		_Ty error;

		__forceinline  Qdrtr8Points(const _Ty, const _Ty);
	};


	template<typename _Ty>  class NewtonCotes8P
	{

	public:

	 __forceinline	NewtonCotes8P();

	 __forceinline  NewtonCotes8P(const double, const double, const int, _Ty &functor);

	 __forceinline  NewtonCotes8P(const NewtonCotes8P &);

	 __forceinline  NewtonCotes8P & integrate(const int);

	 __forceinline  double  get_a() const;

	 __forceinline  double  get_b() const;

	 __forceinline  double  get_integral() const;

	 __forceinline  double  get_error() const;

	 __forceinline  std::function<double(double)> get_functor() const;

	 __forceinline  int     get_n() const;


	private:

		__forceinline  void  compute_error(const double);

		double a, b, error, integral;
		int n;
		_Ty &functor;
	};


#include "QuadratureEightPoints.inl"
}
#endif /*_QUADRATURE_EIGHT_POINTS_H_*/