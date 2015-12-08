#ifndef _MULTI_THREADED_TRAPEZOID_H_
#define _MULTI_THREADED_TRAPEZOID_H_

#include "Integrand.h"
namespace mathlib
{

	//This usage is flawed when multiple calls to trpzd_qdrtr are made.
	//CRITICAL_SECTION mutex1;
	//QdrtrResult qr1;
	//
	
	
	class MTTrpzd
	{

	public:

		
		

		__forceinline static DWORD WINAPI  trpzd_qdrtr(LPVOID);

		__forceinline static double  run_computation(mathlib::Fx *);

	
	};

	
#include "MultiThreadedTrapezoid.inl"
}
#endif /*_MULTI_THREADED_TRAPEZOID_H_*/