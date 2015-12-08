#ifndef _MULTI_THREADED_7P_QUADRATURE_H_
#define _MULTI_THREADED_7P_QUADRATURE_H_

#include "Integrand.h"

namespace mathlib
{


	//CRITICAL_SECTION cs5;
	//QdrtrResult qr5;

	class MTNewtonCotes7P
	{

	public:

		__forceinline  static  DWORD WINAPI  nc7p_qdrtr(LPVOID);

		__forceinline  static  double        run_computation(mathlib::Fx *);
	};

#include "MultiThreaded7PQuadrature.inl"
}
#endif  /*_MULTI_THREADED_7P_QUADRATURE_H_*/