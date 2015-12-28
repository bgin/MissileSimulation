#ifndef _INTEGRATOR_GAUSS_KRONORD_SINGULARITY_H_
#define _INTEGRATOR_GAUSS_KRONORD_SINGULARITY_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
C++ wrapper class for QUADPACK QAGP Integrators -  declaration.

@file IntegratorGaussKronordSingularity.h
@author: Bernard Gingold
@version:  1.0  25/12/2015
@description: QUADRATURE_F77_DECLARATIONS.h
*/

#include "MathLibDefinitions.h"
#include "QUADRATURE_F77_DECLARATIONS.h"


namespace    mathlib
{

	class IntegratorQAGP
	{

	public:

		/*
		@brief  C++ SP float wrapper for F77 QUADPACK QAGP Subroutine. 
		@purpose the routine calculates an approximation result to a given
            definite integral i = integral of f over (a,b),
            hopefully satisfying following claim for accuracy
            break points of the integration interval, where local
            difficulties of the integrand may occur(e.g. singularities,
            discontinuities), are provided by the user.
		*/
		void    static    x_qagp(float(*)(float *), float, float, int, std::vector<float> &, float, float,
			float, float, int, int, int, int, int, std::vector<int> &, std::vector<float> &);

		/*
		@brief  C++ SP (float) wrapper for F77 QUADPACK QAGPE Subroutine.
		@purpose the routine calculates an approximation result to a given
            definite integral i = integral of f over (a,b),
            hopefully satisfying following claim for accuracy
            break points of the integration interval, where local
            difficulties of the integrand may occur(e.g. singularities,
            discontinuities), are provided by the user.
		*/
		void     static    x_qagpe(float(*)(float *), float, float, int, std::vector<float> &, float, float, int,
			float, float, int, int, std::vector<float> &, std::vector<float> &, std::vector<float> &, std::vector<float> &,
			std::vector<float> &, std::vector<int> &, std::vector<int> &, int, int);

		/*
		@brief  C++ DP (double) wrapper for F77 QUADPACK QAGP Subroutine.
		@purpose the routine calculates an approximation result to a given
            definite integral i = integral of f over (a,b),
            hopefully satisfying following claim for accuracy
            break points of the integration interval, where local
            difficulties of the integrand may occur(e.g. singularities,
            discontinuities), are provided by the user.
		*/
		void     static  x_qagp(double(*)(double *), double, double, int, std::vector<double> &, double, double,
			double, double, int, int, int, int, int, std::vector<int> &, std::vector<double> &);

		/*
		@brief  C++ DP (double) wrapper for F77 QUADPACK QAGPE Subroutine.
		@purpose the routine calculates an approximation result to a given
            definite integral i = integral of f over (a,b),
            hopefully satisfying following claim for accuracy
            break points of the integration interval, where local
            difficulties of the integrand may occur(e.g. singularities,
            discontinuities), are provided by the user.
		*/
		void      static  x_qagpe(double(*)(double *), double, double, int, std::vector<double> &, double, double, int,
			double, double, int, int, std::vector<double> &, std::vector<double> &, std::vector<double> &, std::vector<double> &,
			std::vector<double> &, std::vector<int> &, std::vector<int> &, int, int);
	};

#include "IntegratorGaussKronordSingularity.inl"
}
#endif /*_INTEGRATOR_GAUSS_KRONORD_SINGULARITY_H_*/