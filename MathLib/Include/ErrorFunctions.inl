/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Wrapper Class around boost::math::erf functions.
@author: Bernard Gingold
@version:  1.0  27/09/2015
*/

_Maybe_raises_SEH_exception_  __forceinline   float  mathlib::ErrorFunctionsWrapper::erff(_In_ const float a)
{
	return boost::math::erf(a);
}

_Raises_SEH_exception_ template<typename Policy> __forceinline  float mathlib::ErrorFunctionsWrapper::erff(_In_ const float a, _In_ const Policy &pol)
{
	return boost::math::erf(a, pol);
}

_Maybe_raises_SEH_exception_  __forceinline   double  mathlib::ErrorFunctionsWrapper::erfd(_In_ const double a)
{
	return boost::math::erf(a);
}

_Raises_SEH_exception_  template<typename Policy> __forceinline  double mathlib::ErrorFunctionsWrapper::erfd(_In_ const double a, _In_ const Policy &pol)
{
	return boost::math::erf(a, pol);
}

_Maybe_raises_SEH_exception_  __forceinline  float  mathlib::ErrorFunctionsWrapper::erfcf(_In_ const float a)
{
	return boost::math::erfc(a);
}

_Raises_SEH_exception_  template<typename Policy> __forceinline float mathlib::ErrorFunctionsWrapper::erfcf(_In_ const float a, _In_ const Policy &pol)
{
	return boost::math::erfc(a, pol);
}

_Maybe_raises_SEH_exception_  __forceinline  double  mathlib::ErrorFunctionsWrapper::erfcd(_In_ const double a)
{
	return boost::math::erfc(a);
}

_Raises_SEH_exception_  template<typename Policy> __forceinline  double  mathlib::ErrorFunctionsWrapper::erfcd(_In_ const double a, _In_ const Policy &pol)
{
	return boost::math::erfc(a, pol);
}

_Maybe_raises_SEH_exception_ __forceinline  float  mathlib::ErrorFunctionsWrapper::erff_inv(_In_ const float a)
{
	return boost::math::erf_inv(a);
}

_Raises_SEH_exception_ template<typename Policy> __forceinline  float  mathlib::ErrorFunctionsWrapper::erff_inv(_In_ const float a, _In_ const Policy &pol)
{
	return boost::math::erf_inv(a, pol);
}

_Maybe_raises_SEH_exception_ __forceinline  double mathlib::ErrorFunctionsWrapper::erfd_inv(_In_ const double a)
{
	return boost::math::erf_inv(a);
}

_Raises_SEH_exception_ template<typename Policy> __forceinline double mathlib::ErrorFunctionsWrapper::erfd_inv(_In_ const double a, _In_ const Policy &pol)
{
	return boost::math::erf_inv(a, pol);
}

_Maybe_raises_SEH_exception_ __forceinline  float mathlib::ErrorFunctionsWrapper::erfcf_inv(_In_ const float a)
{
	return boost::math::erfc_inv(a);
}

_Raises_SEH_exception_  template<typename Policy> __forceinline float mathlib::ErrorFunctionsWrapper::erfcf_inv(_In_ const float a, _In_ const Policy &pol)
{
	return boost::math::erfc_inv(a, pol);
}

_Maybe_raises_SEH_exception_ __forceinline  double  mathlib::ErrorFunctionsWrapper::erfcd_inv(_In_ const double a)
{
	return boost::math::erfc_inv(a);
}

_Raises_SEH_exception_  template<typename Policy> __forceinline  double mathlib::ErrorFunctionsWrapper::erfcd_inv(_In_ const double a, _In_ const Policy &pol)
{
	return boost::math::erfc_inv(a, pol);
}