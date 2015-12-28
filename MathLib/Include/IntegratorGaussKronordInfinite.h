#ifndef _INTEGRATOR_GAUSS_KRONORD_INFINITE_H_
#define _INTEGRATOR_GAUSS_KRONORD_INFINITE_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
C++ wrapper class for QUADPACK QAGI Integrators -  declaration.

@file IntegratorGaussKronordInfinite.h
@author: Bernard Gingold
@version:  1.0  25/12/2015
@description: QUADRATURE_F77_DECLARATIONS.h
*/

#include "MathLibDefinitions.h"
#include "QUADRATURE_F77_DECLARATIONS.h"

namespace   mathlib
{

	class IntegratorQAGI
	{


	public:

		/*
		@brief  C++ wrapper for F77 QUADPACK QAGI Subroutine.
		@purpose the routine calculates an approximation result to a given
           integral   i = integral of f over (bound,+infinity)
                    or i = integral of f over (-infinity,bound)
                    or i = integral of f over (-infinity,+infinity),
                    hopefully satisfying following claim for accuracy
                    abs(i-result).le.max(epsabs,epsrel*abs(i))
		*/
		void     static  x_qagi(float(*)(float *), float, int, float, float, float, float,
			int, int, int, int, int, std::vector<int> &, std::vector<float> &);

		/*
		@brief  C++ wrapper for F77 QUADPACK QAGIE Subroutine.
		@purpose the routine calculates an approximation result to a given
           integral   i = integral of f over (bound,+infinity)
                    or i = integral of f over (-infinity,bound)
                    or i = integral of f over (-infinity,+infinity),
                    hopefully satisfying following claim for accuracy
                    abs(i-result).le.max(epsabs,epsrel*abs(i))
		*/
		void     static  x_qagie(float(*)(float *), float, float, float, float, int, float, float,
			int, int, std::vector<float> &, std::vector<float> &, std::vector<float> &, std::vector<float> &,
			int, int);

		/*
		@brief  C++ wrapper  for F77 QUADPACK DQAGI Subroutine.
		@purpose the routine calculates an approximation result to a given
           integral   i = integral of f over (bound,+infinity)
           or i = integral of f over (-infinity,bound)
           or i = integral of f over (-infinity,+infinity)
           hopefully satisfying following claim for accuracy
            abs(i-result).le.max(epsabs,epsrel*abs(i)).
		*/
		void     static  x_qagi(double(*)(double *), double, int, double, double, double, double,
			int, int, int, int, int, std::vector<int> &, std::vector<double> &);

		/*
		@brief C++ wrapper for F77 QUADPACK DQAGIE Subroutine.
		@purpose the routine calculates an approximation result to a given
           integral   i = integral of f over (bound,+infinity)
           or i = integral of f over (-infinity,bound)
           or i = integral of f over (-infinity,+infinity)
            hopefully satisfying following claim for accuracy
            abs(i-result).le.max(epsabs,epsrel*abs(i)).
		*/
		void    static  x_qagie(double(*)(double *), double, double, double, double, int, double,
			double, int, int, std::vector<double> &, std::vector<double> &, std::vector<double> &,
			std::vector<double> &, int, int);
	};

#include "IntegratorGaussKronordInfinite.inl"
}
#endif /*_INTEGRATOR_GAUSS_KRONORD_INFINITE_H_*/