#ifndef _SINUSC_FUNCTIONS_H_
#define _SINUSC_FUNCTIONS_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Wrapper Class around boost::math::sinc functions.
@author: Bernard Gingold
@version:  1.0  23/09/2015
*/

#include "MathLibDefinitions.h"
#include <boost\math\special_functions\sinc.hpp>
#include <boost\math\special_functions\sinhc.hpp>

namespace  mathlib
{

	class SinCFunctionsWrapper
	{

	public:

		/*
		@Brief: Function wrapper around boost::math::sinc_pi, float "specialization".
		*/
		_Maybe_raises_SEH_exception_  __forceinline  static  float  sinc_pif(_In_ const float);

		/*
		@Brief:  Function wrapper around boost::math::sinc_pi, float "specialization", additional templated argument Policy.
		
		*/
		_Raises_SEH_exception_    template<typename Policy> __forceinline  static  float sinc_pif(_In_ const float, _In_ const Policy &);

		/*
		@Brief: Function wrapper around boost::math::sinc_pi, double "specialization".
		*/
		_Maybe_raises_SEH_exception_  __forceinline  static  double  sinc_pid(_In_ const double);

		/*
		@Brief:  Function wrapper around boost::math::sinc_pi, double "specialization", additional templated argument Policy.
		*/
		_Raises_SEH_exception_    template<typename Policy>  __forceinline  static double  sinc_pid(_In_ const double, _In_ const Policy &);

		/*
		@Brief:  Function wrapper around boost::math::sinhc_pi, float "specialization".
		*/
		_Maybe_raises_SEH_exception_ __forceinline  static float sinhc_pif(_In_ const float);

		/*
		@Brief: Function wrapper around boost::math::sinhc_pi, float "specialization", additional templated argument Policy.
		*/
		_Raises_SEH_exception_ template<typename Policy> __forceinline static float sinhc_pif(_In_ const float, _In_ const Policy &);

		/*
		@Brief:  Function wrapper around boost::math::sinhc_pi, double "specialization".
		*/
		_Maybe_raises_SEH_exception_ __forceinline  static double sinhc_pid(_In_ const double);

		/*
		@Brief: Function wrapper around boost::math::sinhc_pi, float "specialization", additional templated argument Policy.
		*/
		_Raises_SEH_exception_ template<typename Policy> __forceinline static double sinhc_pid(_In_ const double x, _In_ const Policy &);

		
	};

	/*
	@Brief: Useful Functions like Macros
	*/

#define  SINCPIFR(x,output) \
	float result{ 0.f }; \
	result = mathlib::SinCFunctionsWrapper::sinc_pif(x); \
	(*(output)) = result; \

#define  SINCPIFRP(x,policy,output) \
	float result{ 0.f }; \
	result = mathlib::SinCFunctionsWrapper::sinc_pif(x, policy); \
	(*(output)) = result; \

#define   SINCPIDR(x,output) \
	double result{ 0.0 }; \
	result = mathlib::SinCFunctionsWrapper::sinc_pid(x); \
	(*(output)) = result; \

#define   SINCPIDRP(x,policy,output) \
	double result{ 0.0 }; \
	result = mathlib::SinCFunctionsWrapper::sinc_pid(x, policy); \
	(*(output)) = result; \

#define    SINHCPIFR(x,output) \
	float result{ 0.f }; \
	result = mathlib::SinCFunctionsWrapper::sinhc_pif(x); \
	(*(output)) = result; \

#define    SINHCPIFRP(x,policy,output) \
	float result{ 0.f }; \
	result = mathlib::SinCFunctionsWrapper::sinhc_pif(x, policy); \
	(*(output)) = result; \

#define    SINHCPIDR(x,output) \
	double  result{ 0.0 }; \
	result = mathlib::SinCFunctionsWrapper::sinhc_pid(x); \
	(*(output)) = result; \

#define    SINHCPIDRP(x,policy,output) \
	double  result{ 0.0 }; \
	result = mathlib::SinCFunctionsWrapper::sinhc_pid(x,policy); \
	(*(output)) = result; \

	/*
	@ Brief: End of Macro definitions
	*/
#include "SinusCFunctions.inl"
}
#endif /*_SINUSC_FUNCTIONS_H_*/