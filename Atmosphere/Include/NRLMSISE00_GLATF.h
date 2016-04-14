#ifndef _NRLMSIS00_GLATF_17_03_16
#define _NRMLSIS00_GLATF_17_03_16
/* -------------------------------------------------------------------- */
/* ---------  N R L M S I S E - 0 0    M O D E L    2 0 0 1  ---------- */
/* -------------------------------------------------------------------- */

/*  This file is part of C++ port of NRLMSISE-00 implemented in C.
* @File  NRLMSISE00_GLATF.h
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


//#include "AtmosphereLibDefs.h"
#include "TypeTraits.hpp"


namespace ad = atmosphere::detail;

namespace  atmosphere {

	/* ------------------------------------------------------------------- */
	/* ------------------------------ GLATF ------------------------------ */
	/* ------------------------------------------------------------------- */

	template<typename T>  struct GLATF {

		std::enable_if<ad::is_single_precision<T>::value || ad::is_double_precision<T>::value, void>::type
		operator()(_In_ const T, _In_ T*, _In_ T*);
		void t();
	};

#include "NRLMSISE00_GLATF.inl"
}
#endif /*_NRLMSISE00_GLATF_17_03_16*/