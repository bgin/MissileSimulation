#ifndef _NRLMSISE00_SPLINE_INTEGRATORS_H_21_03_16
#define _NRLMSISE00_SPLINE_INTEGRATORS_H_21_03_16


#include "TypeTraits.hpp"

namespace ad = atmosphere::detail;
namespace  atmosphere {

	/* ------------------------------------------------------------------- */
	/* ------------------------------- SPLINI ---------------------------- */
	/* ------------------------------------------------------------------- */
	template<typename T> struct SPLINE_INTEGRATOR {
               
		static std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value, void>::type
		splinint(_In_ const T*, _In_ const T*, _In_ const T*, _In_ const int, _In_ const T, _Out_ T*)noexcept(false);

	};

	/* ------------------------------------------------------------------- */
	/* ------------------------------- SPLINT ---------------------------- */
	/* ------------------------------------------------------------------- */
	template<typename T> struct SPLINE_INTERPOLATOR {

		static std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value, void>::type
		splinterp(_In_ const T*, _In_ const T*, _In_ const T*, _In_ const int, _In_ const T, _Out_  T*)noexcept(false);
	};

	/* ------------------------------------------------------------------- */
	/* ------------------------------- SPLINE ---------------------------- */
	/* ------------------------------------------------------------------- */
	template<typename T> struct SPLINE_CUBIC_DERIV {

		static std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value, void>::type
		splinderiv(_In_ const T*, _In_ const T*, _In_ const int, _In_ const T, _In_ const T, _Out_ T*)noexcept(false);
	};
#include "NRLMSISE00_SPLINE_INTEGRATORS.inl"
}
#endif /*_NRLMSISE00_SPLINE_INTEGRATORS_H_21_03_16*/