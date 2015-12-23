#ifndef _RUNGE_KUTTA_WRAPPER_TEST_H_
#define _RUNGE_KUTTA_WRAPPER_TEST_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Runge-Kutta Wrapper Test class  - definition.
.
@file RungeKuttaWrapper_TEST.h
@author: Bernard Gingold
@version:  1.0  26/10/2015
@description: in RungeKutta_F77_Declarations.h
*/

//#include "../MathLib/RungeKuttaWrapper.h"
#include <vector>

#include "../MathLib/RungeKutta_F77_Declarations.h"

namespace  test
{


	struct BPARAM
	{
		double B;
	};

	class RKWTest
	{

	public:

		static void  Test1_RungeKutta();

		static void  Test2_RungeKutta();

		static void  Test3_RungeKutta();

		static void  Test4_RungeKutta();

		static void  Run_Tests();


	 static 	void DerivY(double *, double *, double *);

	
	private:

		static   void    perf(unsigned long long*, unsigned long long*, int, const char*);

		static   void    perf(std::vector<unsigned long long> &, std::vector<unsigned long long> &, std::string const&);
	};
}
#endif /*_RUNGE_KUTTA_WRAPPER_TEST_H_*/