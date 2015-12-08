#ifndef _TRAPEZOID_QUADRATURE_TEST_H_
#define _TRAPEZOID_QUADRATURE_TEST_H_

#include "../MathLib/TrapezoidQuadrature.h"

namespace test
{
	class TrapezoidQuadratureTest
	{


	public:

		template<typename Function> __forceinline static double Integral(Function, const double);

		// Test Quadrature of simple polynomial Integrals:
		// x dx, x^2 dx , x3/3 dx , etc....
		void  static  Test_Trapezoid_Quadrature();

		// Test Quadrature of simple polynomial Integrals:
		// x dx, x^2 dx , x3/3 dx , etc....
		// Varying number of quadrature steps.
		void  static  Test_Trapezoid_Quadrature_Varying_Steps();

		// Test Quadrature of simple polynomial Integrals:
		// x dx, x^2 dx , x3/3 dx , etc....
		// Varying number of quadrature steps and interval ranges.
		void  static  Test_Trapezoid_Quadrature_Varying_Steps(double, double);

		// Test Quadrature of simple polynomial Integrals:
		// x dx, x^2 dx , x3/3 dx , etc....
		// Varying number of quadrature steps and abscissa range.
		// Should be used only with small step size(overflow!!).
		void  static  Test_Trapezoid_Quadrature_Varying_Abscissa_Steps();

		// Test Quadrature of simple polynomial Integrals:
		// x dx, x^2 dx , x3/3 dx , etc....
		// Varying abscissa range per loop iteration.
		void  static  Test_Trapezoid_Quadrature_Varying_Abscissas();


		// Test Quadrature of transcendental function Integrals.
		void  static  Test_Trapezoid_Quadrature_Transc();

		// Test Quadrature of transcendental function Integrals.
	    // Varying abscissa range per loop iteration
		void  static  Test_Trapezoid_Quadrature_Transc_Var_Abscissa();

		// Test Quadrature of transcendental function Integrals.
		// Varying number of quadrature steps.
		void  static  Test_Trapezoid_Quadrature_Transc_Var_Steps();

		

		

		void  static  Run_Trapezoid_Quadrature_Tests();

		void  static  Run_Trapezoid_Varying_Abscissa_Tests();

		void  static  Run_Trapezoid_Varying_Step_Tests();
		
		void  static  Run_Trapezoid_Varying_Abscissa_Step_Tests();
	};

#include "TrapezoidQuadrature_TEST.inl"
}
#endif /*_TRAPEZOID_QUADRATURE_TEST_H_*/