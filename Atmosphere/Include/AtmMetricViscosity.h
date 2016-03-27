#ifndef _ATM_METRIC_VISCOSITY_H_15_03_16
#define _ATM_METRIC_VISCOSITY_H_15_03_16


        /*---------------------------------------------------------*/
        /*-------------- Metric Viscosity Computation -------------*/
       /*----------------------------------------------------------*/

#include "TypeTraits.hpp"

// for convenience usage only.
namespace ad = atmosphere::detail;


namespace  atmosphere {

	

	/*
	     MetricViscosity struct templated on parameter T.

	*/

	template<typename T>  struct MetricViscosity {

		// prevent instantiation on type T different than floating-point single or double precision.
		inline std::enable_if<ad::is_double_precision<T>::value || ad::is_single_precision<T>::value, T>::type
		operator()(const T);
	};

#include "AtmMetricViscosity.inl"
}
#endif /*_ATM_METRIC_VISCOSITY_H_15_03_16*/