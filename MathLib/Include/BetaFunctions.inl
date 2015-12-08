/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Wrapper Class around boost::math::beta functions.
@author: Bernard Gingold
@version:  1.0  15/09/2015
*/

_Maybe_raises_SEH_exception_  __forceinline  float  mathlib::BetaFunctionsWrapper::betaf(_In_ const float a, _In_ const float b)
{
	return boost::math::beta(a, b);
}

_Maybe_raises_SEH_exception_ __forceinline  double  mathlib::BetaFunctionsWrapper::betad(_In_ const double a, _In_ const double b)
{
	return boost::math::beta(a, b);
}

_Raises_SEH_exception_  template<typename Policy> __forceinline  float  mathlib::BetaFunctionsWrapper::betaf(_In_ const float a, _In_ const float b, _In_ const Policy& policy)
{
	return boost::math::beta(a, b, policy);
}

_Raises_SEH_exception_  template<typename Policy> __forceinline  double mathlib::BetaFunctionsWrapper::betad(_In_ const double a, _In_ const double b, _In_ const Policy& policy)
{
	return boost::math::beta(a, b, policy);
}

_Maybe_raises_SEH_exception_ __forceinline   float   mathlib::BetaFunctionsWrapper::ibetaf(_In_ const float a, _In_ const float b, _In_ const float x)
{
	return boost::math::ibeta<float,float,float>(a, b, x);
}

_Maybe_raises_SEH_exception_ __forceinline   double  mathlib::BetaFunctionsWrapper::ibetad(_In_ const double a, _In_ const double b, _In_ const double x)
{
	return boost::math::ibeta<double, double, double>(a, b, x);
}

_Raises_SEH_exception_ template<typename Policy> __forceinline  float  mathlib::BetaFunctionsWrapper::ibetaf(_In_ const float a, _In_ const float b, _In_ const float x,
	_In_ const Policy &policy)
{
	return boost::math::ibeta(a, b, x, policy);
}

_Raises_SEH_exception_ template<typename Policy> __forceinline  double mathlib::BetaFunctionsWrapper::ibetad(_In_ const double a, _In_ const double b, _In_ const double x,
	_In_ const Policy &policy)
{
	return boost::math::ibeta(a, b, x, policy);
}

_Maybe_raises_SEH_exception_  __forceinline   float    mathlib::BetaFunctionsWrapper::ibetacf(_In_ const float a, _In_ const float b, _In_ const float x)
{
	return boost::math::ibetac(a, b, x);
}

_Raises_SEH_exception_ template<typename Policy> __forceinline  float   mathlib::BetaFunctionsWrapper::ibetacf(_In_ const float a, _In_ const float b, _In_ const float x,
	_In_ const Policy &policy)
{
	return boost::math::ibetac(a, b, x, policy);
}

_Maybe_raises_SEH_exception_ __forceinline    double   mathlib::BetaFunctionsWrapper::ibetacd(_In_ const double a, _In_ const double b, _In_ const double x)
{
	return boost::math::ibetac(a, b, x);
}

_Raises_SEH_exception_ template<typename Policy> __forceinline   double  mathlib::BetaFunctionsWrapper::ibetacd(_In_ const double a, _In_ const double b, _In_ const double x,
	_In_ const Policy &policy)
{
	return boost::math::ibetac(a, b, x, policy);
}

_Maybe_raises_SEH_exception_  __forceinline   float     mathlib::BetaFunctionsWrapper::betacf(_In_ const float a, _In_ const float b, _In_ const float x)
{
	return boost::math::betac(a, b, x);
}

_Raises_SEH_exception_  template<typename Policy> __forceinline  float   mathlib::BetaFunctionsWrapper::betacf(_In_ const float a, _In_ const float b, _In_ const float x,
	_In_ const Policy &policy)
{
	return boost::math::betac(a, b, x, policy);
}

_Maybe_raises_SEH_exception_   __forceinline   double    mathlib::BetaFunctionsWrapper::betacd(_In_ const double a, _In_ const double b, _In_ const double x)
{
	return boost::math::betac(a, b, x);
}

_Raises_SEH_exception_  template<typename Policy> __forceinline  double   mathlib::BetaFunctionsWrapper::betacd(_In_ const double a, _In_ const double b, _In_ const double x,
	_In_ const Policy &policy)
{
	return boost::math::ibetac(a, b, x, policy);
}