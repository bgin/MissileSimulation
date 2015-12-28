#ifndef _INTEGRATOR_GAUSS_KRONORD_END_SINGULARITIES_H_
#define _INTEGRATOR_GAUSS_KRONORD_END_SINGULARITIES_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
C++ wrapper class for QUADPACK QAGS Integrators -  declaration.

@file IntegratorGKronordEndSingularity.h
@author: Bernard Gingold
@version:  1.0  25/12/2015
@description: QUADRATURE_F77_DECLARATIONS.h
*/

#include "MathLibDefinitions.h"
#include "QUADRATURE_F77_DECLARATIONS.h"

namespace   mathlib
{

	class IntegratorQAGS
	{

	public:

		/*
		@brief C++ SP (float) wrapper for F77 QUADPACK QAGS Subroutine.
		@purpose the routine calculates an approximation result to a given
            definite integral  i = integral of f over (a,b),
            hopefully satisfying following claim for accuracy
            abs(i-result).le.max(epsabs,epsrel*abs(i)).
		*/
		void    static  x_qags(float(*)(float *), float, float, float, float, float, float, int, int,
			int, int, int, std::vector<int> &, std::vector<float> &);

		/*
		@brief  C++ SP (float) wrapper for F77 QUADPACK QAGSE Subroutine.
		@purpose the routine calculates an approximation result to a given
            definite integral  i = integral of f over (a,b),
            hopefully satisfying following claim for accuracy
            abs(i-result).le.max(epsabs,epsrel*abs(i)).
		*/
		void    static  x_qagse(float(*)(float *), float, float, float, float, int, float, float, int, int,
			std::vector<float> &, std::vector<float> &, std::vector<float> &, std::vector<float> &, std::vector<int> &, int);

		/*
		@brief  C++ DP (double) wrapper for F77 QUADPACK DQAGS Subroutine.
		@purpose the routine calculates an approximation result to a given
            definite integral  i = integral of f over (a,b),
            hopefully satisfying following claim for accuracy
            abs(i-result).le.max(epsabs,epsrel*abs(i)).
		*/
		void     static  x_qags(double(*)(double *), double, double, double, double, double, double, int,
			int, int, int, int, std::vector<int> &, std::vector<double> &);

		/*
		@brief  C++ DP (double) wrapper for F77 QUADPACK DQAGSE Subroutine.
		@purpose the routine calculates an approximation result to a given
		definite integral  i = integral of f over (a,b),
		hopefully satisfying following claim for accuracy
		abs(i-result).le.max(epsabs,epsrel*abs(i)).
		*/
		void    static  x_qagse(double(*)(double *), double, double, double, double, int, double, double, int,
			int, std::vector<double> &, std::vector<double> &, std::vector<double> &, std::vector<double> &, std::vector<int> &, int);
	};


#include "IntegratorGKronordEndSingularity.inl"
}

#endif /*_INTEGRATOR_GAUSS_KRONORD_END_SINGULARITIES_H_*/