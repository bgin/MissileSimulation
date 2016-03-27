#ifndef _TYPE_TRAITS_HPP_09_03_16
#define _TYPE_TRAITS_HPP_09_03_16

#include "AtmosphereLibDefs.h"

namespace    atmosphere {

	namespace detail {

		/*-------------------------------------------------*/
		/*------------------- Type Tags ------------------*/
		/*------------------------------------------------*/

		struct double_precision_data {};

		struct single_precision_data {};

		/*--------------------------------------------------*/
		/*------------------- Type Traits ------------------*/
		/*--------------------------------------------------*/



		/*---------------------------------------------------*/
		/*---------------------- Double Precision Traits -----*/
		template<typename T> struct is_double_precision : std::false_type{

		};

		template<> struct is_double_precision<double> : std::true_type{

		};

		template<> struct is_double_precision<const double> : std::true_type{

		};

		template<> struct is_double_precision<double[]> : std::true_type{

		};

		template<> struct is_double_precision<const double[]> : std::true_type{

		};

		template<> struct is_double_precision<double *> : std::true_type{

		};

		template<> struct is_double_precision<const double *> : std::true_type{

		};

		template<> struct is_double_precision<const double * const> : std::true_type{

		};

		template<> struct is_double_precision<float> : std::false_type{

		};

		template<> struct is_double_precision<const float> : std::false_type{

		};

		template<> struct is_double_precision<float[]> : std::false_type{

		};

		template<> struct is_double_precision<const float[]> : std::false_type{

		};

		template<> struct is_double_precision<float *> : std::false_type{

		};

		template<> struct is_double_precision<const float *> : std::false_type{

		};

		template<> struct is_double_precision<const float * const> : std::false_type{

		};


		/*---------------------------------------------------*/
		/*---------------------- Single Precision Traits -----*/
		template<typename T> struct is_single_precision : std::false_type {

		};

		template<> struct is_single_precision<double> : std::false_type{

		};

		template<> struct is_single_precision<const double> : std::false_type{

		};

		template<> struct is_single_precision<double[]> : std::false_type{

		};

		template<> struct is_single_precision<const double[]> : std::false_type{

		};

		template<> struct is_single_precision<double *> : std::false_type{

		};

		template<> struct is_single_precision<const double *> : std::false_type{

		};

		template<> struct is_single_precision<const double * const> : std::false_type{

		};

		template<> struct is_single_precision<float> : std::true_type{

		};

		template<> struct is_single_precision<const float> : std::true_type{

		};

		template<> struct is_single_precision<float[]> : std::true_type{

		};

		template<> struct is_single_precision<const float[]> : std::true_type{

		};

		template<> struct is_single_precision<float *> : std::true_type{

		};

		template<> struct is_single_precision<const float *> : std::true_type{

		};

		template<> struct is_single_precision<const float * const> : std::true_type{

		};

	}
}
#endif /*_TYPE_TRAITS_HPP_09_03_16*/