

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Wrapper Class around boost::math::sinc functions.
@author: Bernard Gingold
@version:  1.0  23/09/2015
*/

_Maybe_raises_SEH_exception_   __forceinline   float  mathlib::SinCFunctionsWrapper::sinc_pif(_In_ const float x)
{
	return boost::math::sinc_pi(x);
}

_Raises_SEH_exception_  template<typename Policy>  __forceinline  float mathlib::SinCFunctionsWrapper::sinc_pif(_In_ const float x, _In_ const Policy &pol)
{
	return boost::math::sinc_pi(x, pol);
}

_Maybe_raises_SEH_exception_   __forceinline    double  mathlib::SinCFunctionsWrapper::sinc_pid(_In_ const double x)
{
	return boost::math::sinc_pi(x);
}

_Raises_SEH_exception_   template<typename Policy> __forceinline  double  mathlib::SinCFunctionsWrapper::sinc_pid(_In_ const double x, _In_ const Policy &pol)
{
	return boost::math::sinc_pi(x, pol);
}

_Maybe_raises_SEH_exception_  __forceinline  float  mathlib::SinCFunctionsWrapper::sinhc_pif(_In_ const float x)
{
	return boost::math::sinhc_pi(x);
}

_Raises_SEH_exception_  template<typename Policy> __forceinline  float  mathlib::SinCFunctionsWrapper::sinhc_pif(_In_ const float x, _In_ const Policy &pol)
{
	return boost::math::sinhc_pi(x, pol);
}

_Maybe_raises_SEH_exception_  __forceinline  double  mathlib::SinCFunctionsWrapper::sinhc_pid(_In_ const double x)
{
	return boost::math::sinhc_pi(x);
}

_Raises_SEH_exception_  template<typename Policy> __forceinline  double  mathlib::SinCFunctionsWrapper::sinhc_pid(_In_ const double x, _In_ const Policy &pol)
{
	return boost::math::sinhc_pi(x, pol);
}