#ifndef _ATMOS_PHYS_CONSTANTS_H_14_03_16
#define _ATMOS_PHYS_CONSTANTS_H_14_03_16


/*--------------  Atmosphere Physical Constants ----------------*/
/*
              Compile time struct passed as a template argument 
		      to two classes which implement detailed and simplified
			  atmosphere model.
*/
/*---------------------------------------------------------------*/



namespace    atmosphere {


	template<typename T> struct PhysConsts {
		constexpr static const int NTAB{ 8 };
		constexpr static  T FT2METERS{ 0.3048 };  // mult. ft. to get meters (exact)
		constexpr static  T KELVIN2RANKINE{ 1.8 }; // mult kelvins to get deg R
		constexpr static  T PSF2NSM{ 47.880258 }; // mult lb/sq.ft to get N/sq.m
		constexpr static  T SCF2KCM{ 515.379 };  // mult slugs/cu.ft to get kg/cu.m
		constexpr static  T TZERO{ 288.15 }; // sea level temperature, kelvins
		constexpr static  T PZERO{ 101325.0 }; // sea-level pressure, N/sq.m
		constexpr static  T RHOZERO{ 1.225 };  // sea level density, kg/cu.m
		constexpr static  T AZERO{ 340.294 };   // sea-level speed of sound, m/sec
		constexpr static  T REARTH{ 6369.0 };  // Earth radius.
		constexpr static  T GMR{ 34.163195 };
		const static  T htab[NTAB];
		const static  T ttab[NTAB];
		const static  T ptab[NTAB];
		const  static T gtab[NTAB];

	};

	/*
	 
	       ***********   Metric Viscosity  *************
	    
	*/

	

#include "AtmosPhysConstants.inl"
}
#endif /*_ATMOS_PHYS_CONSTANTS_H_14_03_16*/