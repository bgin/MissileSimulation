#ifndef _MULTI_THREADED_8P_QUADRATURE_H_
#define _MULTI_THREADED_8P_QUADRATURE_H_


#include "Integrand.h"

namespace  mathlib
{

	//CRITICAL_SECTION cs6;
	//QdrtrResult      qr6;

	class MTNewtonCotes8P
	{

	public:


		__forceinline static  DWORD WINAPI nc8p_qdrtr(LPVOID);

		__forceinline static  double       run_computation(mathlib::Fx *);

	};

#include "MultiThreaded8PQuadrature.inl"
}
#endif /*_MULTI_THREADED_8P_QUADRATURE_H_*/