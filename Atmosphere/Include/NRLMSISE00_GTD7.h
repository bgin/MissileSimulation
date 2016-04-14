#ifndef _NRLMSISE00_GTD7_H_26_03_16
#define _NRLMSISE00_GTD7_H_26_03_16

/* -------------------------------------------------------------------- */
/* ---------  N R L M S I S E - 0 0    M O D E L    2 0 0 1  ---------- */
/* -------------------------------------------------------------------- */

/*  This file is part of C++ port of NRLMSISE-00 implemented in C.
* @File  NRLMSISE00_GTD7.h
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
* Adapted from the work of Dominik Brodowski by Bernard Gingold
*/

#include "AtmosphereLibDefs.h"
#include "NRLMSISE00_INOUT.h"
#include "NRLMSISE00_SHARED.h"
#include "NRLMSISE00_GLATF.h"
#include "NRLMSISE00_DENSITY.h"
#include "NRLMSISE00_GLOBE7.h"
#include "NRLMSISE00_SCLAHDNET.h"
#include "NRLMSISE00_CCOR.h"
#include "AtmosphereData.h"
#include "TypeTraits.hpp"

//namespace ad = atmosphere::detail;
namespace amg = atmosphere::nrlmsise00_globals;

namespace  atmosphere {

	

	template<typename T, class INPUT = atmosphere::NRLMSISE_INPUT<T>,
		class FLAGS = atmosphere::NRLMSISE_FLAGS<T>, class OUTPUT = 
			atmosphere::NRLMSISE_OUTPUT<T>, class SPLINE = atmosphere::SPLINE_CUBIC_DERIV<T>,
		class SPLINT = atmosphere::SPLINE_INTERPOLATOR<T >, class SPLINI =
			atmosphere::SPLINE_INTEGRATOR<T>> struct GTD7 {

				/* TSELEC function */
				static auto  tselec(_In_ FLAGS &)->void;
				/* ------------------------------------------------------------------- */
				/* ------------------------------- GTD7 ------------------------------ */
				/* ------------------------------------------------------------------- */
				static std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value, void>::type
					fgtd7(_In_ INPUT &, _In_ const FLAGS &, _Out_ OUTPUT &);

				/*     Thermospheric portion of NRLMSISE-00
				*     See GTD7 for more extensive comments
				*     alt > 72.5 km!
				*/
				 static std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value, void>::type
					fgts7(_In_ INPUT &, _In_ const FLAGS &, _In_ OUTPUT &);
				 /* ------------------------------------------------------------------- */
				 /* ------------------------------- GTD7D ----------------------------- */
				 /* ------------------------------------------------------------------- */
				 static std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value, void>::type
					 fgtd7d(_In_ INPUT &, _In_ const FLAGS &, _Out_ OUTPUT &);
				 /* ------------------------------------------------------------------- */
				 /* -------------------------------- GHP7 ----------------------------- */
				 /* ------------------------------------------------------------------- */
				 static std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value, void>::type
					 fghp7(_In_ INPUT &, _In_ const FLAGS &, _Out_ OUTPUT &, _In_ T);
				
				
			};
#include "NRLMSISE00_GTD7.inl"
}
#endif /*_NRLMSISE00_GTD7_H_26_03_16*/