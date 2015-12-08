#ifndef _BETA_FUNCTIONS_H_
#define _BETA_FUNCTIONS_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Wrapper Class around boost::math::beta functions.
@author: Bernard Gingold
@version:  1.0  15/09/2015
*/

#include "MathLibDefinitions.h"
#include <boost\math\special_functions\beta.hpp>


namespace  mathlib
{

	class BetaFunctionsWrapper
	{

	public:

		/*
		@Brief: Regular Beta Functions. Prevent usage of "result type calcualtion" by enforcing the same type parameter declaration.

		*/

		/*
		@Brief: Regular Beta function wrapper, float "specialization".
		*/
_Maybe_raises_SEH_exception_	__forceinline  static	float   betaf(_In_ const float , _In_ const float );
	/*
	@Brief: Regular Beta function wrapper,  double "specialization".
	*/
_Maybe_raises_SEH_exception_	__forceinline  static   double  betad(_In_ const double, _In_ const double);
	/*
	@Brief: Regular Beta function wrapper, float "specialization" additional Policy argument.
	*/
_Raises_SEH_exception_	template<typename Policy> __forceinline static float betaf(_In_ const float, _In_ const float, const Policy&);
	/*
	@Brief:  Regular Beta function wrapper, double "specialization" additional Policy argument.
	*/
_Raises_SEH_exception_	template<typename Policy> __forceinline static double betad(_In_ const double, _In_ const double, const Policy&);

	/*
	@Brief: Icomplete Beta Functions. Prevent usage of "result type calcualtion" by enforcing the same type parameter declaration.
	*/

	/*
	@Brief: Incomplete Beta Functions wrapper, float "specialization".
	*/
_Maybe_raises_SEH_exception_	__forceinline  static  float    ibetaf(_In_ const float, _In_ const float, _In_ const float);

	/*
	@Brief: Icomplete Beta Functions wrapper, double "specialization".
	*/
_Maybe_raises_SEH_exception_	__forceinline  static  double   ibetad(_In_ const double, _In_ const double, _In_ const double);

	/*
	@Brief: Incomplete Beta function wrapper of ibeta,float "specialization" additional Policy argument.
	*/
 _Raises_SEH_exception_ template<typename Policy> __forceinline  static float ibetaf(_In_ const float, _In_ const float, _In_ const float, _In_ const Policy &);

	/*
	@Brief: Incomplete Beta function wrapper of ibeta, double "specialization" additional Policy argument.
	*/
_Raises_SEH_exception_	template<typename Policy> __forceinline  static double ibetad(_In_ const double, _In_ const double, _In_ const double, _In_ const Policy &);

    /*
    @Brief: Incomplete Beta function wrapper of ibetac, float "specialization".
    */
_Maybe_raises_SEH_exception_	__forceinline  static  float    ibetacf(_In_ const float, _In_ const float, _In_ const float);

   /*
    @:Brief: Incomplete Beta function wrapper of ibetac, float "specialization" , addidtional Policy argument.
   */
_Raises_SEH_exception_   template<typename Policy> __forceinline  static float ibetacf(_In_ const float, _In_ const float, _In_ const float, _In_ const Policy &);

  /*
  @Brief: Incomplete Beta function wrapper of ibetac, double "specialization".
 */
_Maybe_raises_SEH_exception_    __forceinline  static  double    ibetacd(_In_ const double, _In_ const double, _In_ const double);

  /*
  @Brief: Incomplete Beta function wrapper of ibetac, double "specialization", addidtional argument Policy.
  */
_Raises_SEH_exception_    template<typename Policy> __forceinline  static double  ibetacd(_In_ const double, _In_ const double, _In_ const double,
	_In_ const Policy &);

  /*
  @Brief: Incomplete Beta compliment function wrapper of betac, float "specialization".
   */
_Maybe_raises_SEH_exception_   __forceinline   static   float    betacf(_In_ const float, _In_ const float, _In_ const float);

   /*
   @Brief: Incomplete Beta compliment function wrapper of betac, float "specialization", additional Policy argument.

  */
_Raises_SEH_exception_    template<typename Policy> __forceinline  static  float  betacf(_In_ const float, _In_ const float, _In_ const float,
	_In_ const Policy &);

  /*
  @Brief:  Incomplete Beta compliment function wrapper of betac, double "specialization"
  */
_Maybe_raises_SEH_exception_   __forceinline   static  double    betacd(_In_ const double, _In_ const double, _In_ const double);

  /*
  @Brief:  Incomplete Beta compliment function wrapper of betac, double "specialization", addidtional template Policy argument.
  */
_Raises_SEH_exception_    template<typename Policy> __forceinline  static   double betacd(_In_ const double, _In_ const double, _In_ const double,
	_In_ const Policy &);
	};

	/*
		@Brief: Macro like functions for convenience.
		*/

	
	// output should be passed by reference, BETADR(a,b,&output), Beta Double Returns(BETADR)
#define BETADR(a,b,output) \
	\
	double result{ 0.0 }; \
	result = mathlib::BetaFunctionsWrapper::betad(a, b); \
	(*(output)) = result; \

	// output should be passed by reference, BETADR(a,b,&output)
#define BETAFR(a,b,output) \
	float result{ 0.f }; \
	result = mathlib::BetaFunctionsWrapper::betaf(a, b); \
	(*(output)) = result; \

#define  BETADRP(a,b,policy,output) \
	double result{ 0.0 }; \
	result = mathlib::BetaFunctionsWrapper::betad(a, b, policy); \
	(*(output)) = result; \

	/*
	@Brief: Function like Macro wrapps call to mathlib::BetFunctionsWrapper::betaf.
	*/
#define  BETAFRP(a,b,policy,output) \
	float result{ 0.f }; \
	result = mathlib::BetaFunctionsWrapper::betaf(a, b, policy); \
	(*(output)) = result; \
	/*
	@Brief: Function like Macro wrapps call to mathlib::BetFunctionsWrapper::ibetaf.
	*/
#define  IBETAFR(a,b,x,output) \
	float result{ 0.f }; \
	result = mathlib::BetaFunctionsWrapper::ibetaf(a, b, x); \
	(*(output)) = result; \
	/*
	@Brief: Function like Macro wrapps call to mathlib::BetFunctionsWrapper::ibetad.
	*/
#define  IBETADR(a,b,x,output) \
	double result{ 0.0 };  \
	result = mathlib::BetaFunctionsWrapper::ibetad(a, b, x); \
	(*(output)) = result; \
	/*
	@Brief: Function like Macro wrapps call to mathlib::BetFunctionsWrapper::ibetaf, additional template argument Policy.
	*/
#define  IBETADRP(a,b,x,policy,output) \
	double result{ 0.0 }; \
	result = mathlib::BetaFunctionsWrapper::ibetad(a, b, x, policy); \
	(*(output)) = result;  \
	/*
	@Brief: Function like Macro wrapps call to mathlib::BetFunctionsWrapper::ibetad, additional template argument Policy.
	*/
#define   IBETAFRP(a,b,x,policy,output) \
	float result{ 0.f };  \
	result = mathlib::BetaFunctionsWrapper::ibetaf(a, b, x, policy); \
	(*(output)) = result; \
	/*
	@Brief: Function like Macro wrapps call to mathlib::BetFunctionsWrapper::ibetacf.
	*/
#define   IBETACFR(a,b,x,output) \
	float result{ 0.f }; \
	result = mathlib::BetaFunctionsWrapper::ibetacf(a, b, x); \
	(*(output)) = result; \
	/*
	@Brief: Function like Macro wrapps call to mathlib::BetFunctionsWrapper::ibetacf, additional template agument Policy.
	*/
#define   IBETACFRP(a,b,x,policy,output) \
	float result{ 0.f }; \
	result = mathlib::BetaFunctionsWrapper::ibetacf(a, b, x, policy); \
	(*(output)) = result; \
	/*
	@Brief:  Function like Macro wrapps call to mathlib::BetFunctionsWrapper::ibetacd.
	*/
#define   IBETACDR(a,b,x,output) \
	double result{ 0.0 }; \
	result = mathlib::BetaFunctionsWrapper::ibetacd(a, b, x); \
	(*(output)) = result; \
	/*
	@Brief: Function like Macro wrapps call to mathlib::BetFunctionsWrapper::ibetacd, additional template agument Policy.
	*/
#define   IBETACDRP(a,b,x,policy,output) \
	double result{ 0.0 }; \
	result = mathlib::BetaFunctionsWrapper::ibetacd(a, b, x, policy); \
	(*(output)) = result; \
	/*
	@Brief: Function like Macro wrapps call to mathlib::BetFunctionsWrapper::betacf.
	*/
#define   BETACFR(a,b,x,output) \
	float result{ 0.f }; \
	result = mathlib::BetaFunctionsWrapper::betacf(a, b, x); \
	(*(output)) = result; \
	/*
	@Brief: Function like Macro wrapps call to mathlib::BetFunctionsWrapper::betacf, additional template agument Policy.
	*/
#define   BETACFRP(a,b,x,policy,output) \
	float result{ 0.f }; \
	result = mathlib::BetaFunctionsWrapper::betacf(a, b, x, policy); \
	(*(output)) = result; \
	/*
	@Brief: Function like Macro wrapps call to mathlib::BetFunctionsWrapper::betacd.
	*/
#define    BETACDR(a,b,x,output) \
	double result{ 0.0 }; \
	result = mathlib::BetaFunctionsWrapper::betacd(a, b, x); \
	(*(output)) = result; \
	/*
	@Brief: Function like Macro wrapps call to mathlib::BetFunctionsWrapper::betacd, additional template agument Policy.
	*/
#define    BETACDRP(a,b,x,policy,output) \
	double  result{ 0.0 }; \
	result = mathlib::BetaFunctionsWrapper::betacd(a, b, x, policy); \
	(*(output)) = result; \
	/*
	@      End of Functions like Macro definitions
	*/
#include "BetaFunctions.inl"
}
#endif /*_BETA_FUNCTIONS_H_*/