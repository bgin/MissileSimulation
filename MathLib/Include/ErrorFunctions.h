#ifndef _ERROR_FUNCTIONS_H_
#define _ERROR_FUNCTIONS_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Wrapper Class around boost::math::erf functions.
@author: Bernard Gingold
@version:  1.0  27/09/2015
*/

#include "MathLibDefinitions.h"
#include <boost\math\special_functions\erf.hpp>

namespace  mathlib
{

	class ErrorFunctionsWrapper
	{

	public:

		/*
		@Brief: Error function wrapper, float "specialization".
		*/
		_Maybe_raises_SEH_exception_  __forceinline  static  float erff(_In_ const float);

		/*
		@Brief: Error function wrapper, float "specialization", additional templated argument Policy
		*/
		_Raises_SEH_exception_ template<typename Policy> __forceinline static  float erff(_In_ const float, _In_ const Policy &);

		/*
		@Brief: Error function wrapper, double "specialization".
		*/
		_Maybe_raises_SEH_exception_  __forceinline   static  double  erfd(_In_ const double);

		/*
		@Brief: Error function wrapper, double "specialization", additional templated argument Policy.
		*/
		_Raises_SEH_exception_ template<typename Policy> __forceinline static double erfd(_In_ const double, _In_ const Policy &);

		/*
		Brief: Error function complement, float "specialization".
		*/
		_Maybe_raises_SEH_exception_ __forceinline  static  float  erfcf(_In_ const float);

		/*
		@Brief: Error function complement, float "specialization", additional templated argument Policy.
		*/
		_Raises_SEH_exception_ template<typename Policy> __forceinline  static float erfcf(_In_ const float a, _In_ const Policy &);

		/*
		@Brief: Error function complement, double "specialization".
		*/
		_Maybe_raises_SEH_exception_ __forceinline  static double  erfcd(_In_ const double);

		/*
		@Brief: Error function complement, double "specialization", additional templated argument Policy.
		*/
		_Raises_SEH_exception_ template<typename Policy> __forceinline  static  double  erfcd(_In_ const double, _In_ const Policy &);


		/*
		 Error Functions Inverse.
		*/


		/*
		@Brief: Error function inverse, erf_inv, float "specialization".
		*/
		_Maybe_raises_SEH_exception_ __forceinline  static  float erff_inv(_In_ const float);

		/*
		@Brief: Error function inverse, float "specialization", additional templated argument Policy.
		*/
		_Raises_SEH_exception_ template<typename Policy> __forceinline static float erff_inv(_In_ const float, _In_ const Policy &);

		/*
		@Brief: Error function inverse, erv_inv, double "specialization".
		*/
		_Maybe_raises_SEH_exception_ __forceinline  static double  erfd_inv(_In_ const double);

		/*
		@Brief: Error function inverse: erf_inv, double "specialization" additional templated argument Policy.
		*/
		_Raises_SEH_exception_ template<typename Policy> __forceinline static double erfd_inv(_In_ const double, _In_ const Policy &);

		/*
		@Brief: Error function inverse complement: erfc_inv, float "specialization".
		*/
		_Maybe_raises_SEH_exception_ __forceinline  static float erfcf_inv(_In_ const float);

		/*
		@Brief: Error function inverse complement: erfc_inv, float "specialization" additional templated argument Policy.
		*/
		_Raises_SEH_exception_ template<typename Policy> __forceinline  static float erfcf_inv(_In_ const float, _In_ const Policy &);

		/*
		@Brief: Error function inverse complement: erfc_inv, double "specialization".
		
		*/
		_Maybe_raises_SEH_exception_ __forceinline  static double erfcd_inv(_In_ const double);

		/*
		@Brief: Error function inverse complement: erfc_inv, double "specialization" additional templated argument Policy.
		*/
		_Raises_SEH_exception_ template<typename Policy> __forceinline static double erfcd_inv(_In_ const double, _In_ const Policy &);
	};

	/*
	@Brief:  Useful Macro like functions.
	*/

#define ERFFR(a,output)  \
	float result{ 0.f }; \
	result = mathlib::ErrorFunctionsWrapper::erff(a); \
	(*(output)) = result; \

#define ERFFRP(a,policy,output) \
	float result{ 0.f }; \
	result = mathlib::ErrorFunctionsWrapper::erff(a, policy); \
	(*(output)) = result; \

#define ERFDR(a,output) \
	double result{ 0.0 }; \
	result = mathlib::ErrorFunctionsWrapper::erfd(a); \
	(*(output)) = result; \

#define ERFDRP(a,policy,output) \
	double result{ 0.0 }; \
	result = mathlib::ErrorFunctionsWrapper::erfd(a, policy) \
	(*(output)) = result; \

#define ERFCFR(a,output) \
	float result{ 0.f }; \
	result = mathlib::ErrorFunctionsWrapper::erfcf(a); \
	(*(output)) = result; \

#define ERFCFRP(a,policy,output) \
	float result{ 0.f }; \
	result = mathlib::ErrorFunctionsWrapper::erfcf(a, policy); \
	(*(output)) = result; \

#define ERFCDR(a,output) \
	double result{ 0.0 }; \
	result = mathlib::ErrorFunctionsWrapper::erfcd(a); \
	(*(output)) = result; \

#define ERFCDRP(a,policy,output) \
	double result{ 0.0 }; \
	result = mathlib::ErrorFunctionsWrapper::erfcd(a, policy); \
	(*(output)) = result; \

	/*
	Error Function inverse complement macros.
	*/

#define ERFFIR(a,output) \
	float result{ 0.f }; \
	result = mathlib::ErrorFunctionsWrapper::erff_inv(a); \
	(*(output)) = result; \

#define ERFFIRP(a,policy,output) \
	float result{ 0.f }; \
	result = mathlib::ErrorFunctionsWrapper::erff_inv(a, policy); \
	(*(output)) = result; \

#define ERFDIR(a,output) \
	double result{ 0.0 }; \
	result = mathlib::ErrorFunctionsWrapper::erfd_inv(a); \
	(*(output)) = result; \

#define ERFDIRP(a,policy,output) \
	double result{ 0.0 }; \
	result = mathlib::ErrorFunctionsWrapper::erfd_inv(a, policy); \
	(*(output)) = result; \

#define ERFCFIR(a,output) \
	float result{ 0.f }; \
	result = mathlib::ErrorFunctionsWrapper::erfcf_inv(a); \
	(*(output)) = result; \

#define ERFCFIRP(a,policy,output) \
	float result{ 0.f }; \
	result = mathlib::ErrorFunctionsWrapper::erfcf_inv(a, policy); \
	(*(output)) = result; \

#define ERFCDIR(a,output) \
	double result{ 0.0 }; \
	result = mathlib::ErrorFunctionsWrapper::erfcd_inv(a); \
	(*(output)) = result; \

#define ERFCDIRP(a,policy,output) \
	double result{ 0.0 }; \
	result = mathlib::ErrorFunctionsWrapper::erfcd_inv(a, policy); \
	(*(output)) = result; \

#include "ErrorFunctions.inl"
}
#endif /*_ERROR_FUNCTIONS_H_*/