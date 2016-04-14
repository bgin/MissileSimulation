#ifndef _NRLMSISE00_GLOBE7_H_25_03_16
#define _NRLMSISE00_GLOBE7_H_25_03_16

/* -------------------------------------------------------------------- */
/* ---------  N R L M S I S E - 0 0    M O D E L    2 0 0 1  ---------- */
/* -------------------------------------------------------------------- */

/*  This file is part of C++ port of NRLMSISE-00 implemented in C.
* @File  NRLMSISE00_GLOBE7.h
* The NRLMSISE-00 model was developed by Mike Picone, Alan Hedin, and
* Doug Drob. They also wrote a NRLMSISE-00 distribution package in
* FORTRAN which is available at
* http://uap-www.nrl.navy.mil/models_web/msis/msis_home.htm
*
* Dominik Brodowski implemented and maintains this C version. You can
* reach him at mail@brodo.de. See the file "DOCUMENTATION" for details,
* and check http://www.brodo.de/english/pub/nrlmsise/index.html for
* updated releases of this package.
*
* Adapted from the work of Dominik Brodowski by Bernard Gingold.
*/

#include "AtmosphereLibDefs.h"
#include "NRLMSISE00_INOUT.h"
#include "NRLMSISE00_SHARED.h"
#include "TypeTraits.hpp"

namespace ad = atmosphere::detail;
namespace amg = atmosphere::nrlmsise00_globals;

namespace  atmosphere {


	/* ------------------------------------------------------------------- */
	/* ------------------------------- GLOBE7 ---------------------------- */
	/* ------------------------------------------------------------------- */


	template<typename T, class INPUT = atmosphere::NRLMSISE_INPUT<T>, 
	class FLAGS = atmosphere::NRLMSISE_FLAGS<T>> struct GLOBE7 {

		/*    3hr Magnetic activity functions */
		/*    Eq. A24d */
		static std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value, T>::type
		g0(_In_ const T, _In_ const T*);

		/*    Eq. A24c */
		static std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value, T>::type
			sumex(_In_ const T);

		/*    Eq. A24a */
		static std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value, T>::type
			sg0(_In_ const T, _In_ const T*, _In_ const AP_VALUES<T> &);

		static std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value, T>::type
			fglobe7(_In_ const T*, _In_ const INPUT &, _In_ const FLAGS &);
	};


	/* ------------------------------------------------------------------- */
	/* ------------------------------- GLOB7S ---------------------------- */
	/* ------------------------------------------------------------------- */
	template<typename T, class INPUT = atmosphere::NRLMSISE_INPUT<T>,
	class FLAGS = atmosphere::NRLMSISE_FLAGS < T >> struct GLOBE7S {

		/*    VERSION OF GLOBE FOR LOWER ATMOSPHERE 10/26/99
		*/
		static std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value, T>::type
		fglobe7s(_In_ T*, _In_ const INPUT &, _In_ const FLAGS &);
	};

#include "NRLMSISE00_GLOBE7.inl"
}
#endif /*_NRLMSISE00_GLOBE7_H_25_03_16*/