#ifndef _BOOL_COMPOSITE_QUADRATURE_H_
#define _BOOL_COMPOSITE_QUADRATURE_H_

#include "MathLibDefinitions.h"
#include "Derivative.h"


namespace mathlib
{

	template<typename _Ty> class BoolRule
	{

	public:
     

		template<typename Function> __forceinline  static BoolRule integrate(Function, _Ty, _Ty, const int,const int);

		__forceinline const _Ty  get_integral() const;

		__forceinline       _Ty  get_integral();

		__forceinline const _Ty  get_error() const;

		__forceinline       _Ty  get_error();

	private:

		_Ty integral;
		_Ty error;

		__forceinline  BoolRule(const _Ty, const _Ty);

		template<typename Function> __forceinline  _Ty static compute_error(Function,_Ty, _Ty, _Ty);
	};


	template<typename _Ty> class BoolQdrtr
	{

	public:

		__forceinline  BoolQdrtr();

		__forceinline  BoolQdrtr(const double, const double, const int, _Ty &functor);

		__forceinline  BoolQdrtr(const BoolQdrtr &);

		__forceinline  BoolQdrtr &  integrate(const int);

		__forceinline  double  get_a() const;

		__forceinline  double  get_b() const;

		__forceinline   double  get_integral() const;

		__forceinline  double  get_error() const;

		__forceinline  int    get_n() const;

	private:

		__forceinline  void compute_error(double);

		double a, b, integral, error;
		int n;
		_Ty &functor;

	};



#include "BoolCompositeQuadrature.inl"
}
#endif /*_BOOL_COMPOSITE_QUADRATURE_H_*/