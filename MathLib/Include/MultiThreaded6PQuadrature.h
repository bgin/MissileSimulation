#ifndef _MULTI_THREADED_6P_QUADRATURE_H_
#define _MULTI_THREADED_6P_QUADRATURE_H_


#include "Integrand.h"


namespace mathlib
{
	//CRITICAL_SECTION cs4;
	//QdrtrResult qr4;

	class MTNewtonCotes6P
	{

	public:

		__forceinline  static  DWORD WINAPI  nc6p_qdrtr(LPVOID);

		__forceinline  static  double        run_computation(mathlib::Fx *);
	};

#include "MultiThreaded6PQuadrature.inl"
}
#endif /*_MULTI_THREADED_6P_QUADRATURE_H_*/