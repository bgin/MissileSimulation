#ifndef _INTEGRAND_H_
#define _INTEGRAND_H_

#include <Windows.h>
#include "MathLibDefinitions.h"


namespace mathlib
{
	// struct which represent integrand and various auxiliary variables
	// needed to perform multi-threaded quadrature.
	struct Fx
	{
		std::function<double(double)> fptr;
		
		double a, b;
		unsigned num_steps;
		unsigned int NWorkers;
		unsigned int * Workers;
		DWORD * ThIDArray;
		CRITICAL_SECTION cs;
		double result{ 0.0 };
	};

 __forceinline	void static InitFx(mathlib::Fx *, std::function<double(double)>, double, double, const unsigned int,
	 const unsigned int);

 __forceinline  void static DeallocFx(mathlib::Fx *);

     // Global struct ued to hold the result of Quadrture.
 // This is flawed solution.
	 struct QdrtrResult
	{
		double result ;
	};

#include "Integrand.inl"
}
#endif /*_INTEGRAND_H_*/