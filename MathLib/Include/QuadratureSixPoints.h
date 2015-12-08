
#ifndef _QUADRATURE_SIX_POINTS_H_
#define _QUADRATURE_SIX_POINTS_H_

#include "MathLibDefinitions.h"
#include "Derivative.h"
namespace  mathlib
{
	template<typename _Ty>  class QdrtrSixPoints
	{

	public:

		template<typename Function> __forceinline  static QdrtrSixPoints integrate(Function, _Ty, _Ty, const int,const int);

		__forceinline  const _Ty  get_integral() const;

		__forceinline        _Ty  get_integral();

		__forceinline  const _Ty  get_error()  const;

		__forceinline        _Ty  get_error();

	private:

		template<typename Function> __forceinline static _Ty compute_error(Function, _Ty, _Ty, _Ty);

		_Ty integral;
		_Ty error;

		__forceinline QdrtrSixPoints(const _Ty, const _Ty);
	};

	template<typename _Ty> class  NewtonCotes6P
	{

	public:

		__forceinline NewtonCotes6P();

		__forceinline NewtonCotes6P(const double, const double, const int, _Ty &functor);

		__forceinline NewtonCotes6P(const NewtonCotes6P &);

		__forceinline  NewtonCotes6P &  integrate(const int);

		__forceinline  double  get_a() const;

		__forceinline  double  get_b() const;

		__forceinline  double  get_integral() const;

		__forceinline  double  get_error() const;

		__forceinline  int     get_n() const;

		


	private:

		__forceinline  void  compute_error(double);
		double a, b, integral, error;
		int n;
		_Ty &functor;
	};


#include "QuadratureSixPoints.inl"
}
#endif /*_QUADRATURE_SIX_POINTS_H_*/