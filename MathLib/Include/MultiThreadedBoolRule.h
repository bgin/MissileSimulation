#ifndef _MULTI_THREADED_BOOL_RULE_H_
#define _MULTI_THREADED_BOOL_RULE_H_


#include "Integrand.h"

namespace  mathlib
{
	//CRITICAL_SECTION cs3;
	//QdrtrResult qr3;

	class MTBoolQdrtr
	{


	public:

		__forceinline static  DWORD WINAPI  boole_qdrtr(LPVOID);

		__forceinline static  double        run_computation(mathlib::Fx *);
	};

#include "MultiThreadedBoolRule.inl"
}
#endif  /*_MULTI_THREADED_BOOL_RULE_H_*/