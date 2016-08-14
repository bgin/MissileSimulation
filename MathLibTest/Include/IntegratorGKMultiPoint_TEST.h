#ifndef _INTEGRATOR_GK_MULTI_POINT_TEST_H_
#define _INTEGRATOR_GK_MULTI_POINT_TEST_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Integrator Gauss-Kronord Wrapper Test class  - definition.
.
@file IntegratorGKMultiPoint_TEST.h
@author: Bernard Gingold
@version:  1.0  26/10/2015
@description: in QUADRATURE_F77_DECLARATIONS.h
*/

#include "../MathLib/IntegratorGKMultiPoint.h"

namespace  test
{


	class  GaussKronordTests
	{


	public:


		/*
		@brief Test  Gaussian-Kronord 15 points Quadrature.
		Integrand = e^-px dx.

		*/
		void    static GK15ExpFunc1();

		/*
		@brief  Test of Gaussian-Kronord 15-points Quadrature.
		Integrand = dx/1+e^px
		*/
		void    static GK15ExpFunc2();

		/*
		@brief  Test of Gaussian-Kronord 15-points Quadrature.
		Integrand = e^-ux/1+e-x dx
		*/
		void    static GK15ExpFunc3();

		/*
		@brief  Test of Gaussian-Kronrod 15-points Quadrature.
		Integrand = (1 - cos(x))^n*sin(n*x)dx
		*/
		void    static GK15TrigFunc1();

		/*
		@brief  Test of Gaussian-Kronrod 15-points Quadrature.
		Integrand = (sin(nx))/sin(x)dx
		*/
		void    static GK15TrigFunc2();

		/*
		@brief Test runner method.
		*/
		void    static  RunGK15ExpFuncTests();

		/*
		@brief  Test runner method.
		*/
		void    static  RunGK15TrigFuncTests();


	private:

		/*
		@brief Templated static member integral function(real value of Integral(symbolic)).
		*/
		template<typename _Fx, typename _x> __forceinline  static _x  Integral(_Fx fx, const _x x)
		{
			return _Fx(x);
		}

		const static double MACHPREC;
	};
}
#endif  /*_INTEGRATOR_GK_MULTI_POINT_TEST_H_*/