#ifndef _GR80_PHY_CONSTS_H_09_04_16
#define _GR80_PHY_CONSTS_H_09_04_16

/* Copyright(c) 2015, Bernard Gingold.License: MIT License(http ://www.opensource.org/licenses/mit-license.php)
Geodesic Reference System 80 - Derived Physical Constants - declaration.

@file GR80PhyConsts.h
@author: Bernard Gingold
@version : 1.0.0  25 / 12 / 2015
@description : GR80PhyConsts.h
@reference Official paper GR - 80 by H.Moritz


*/

namespace  atmosphere {


	/*******************************************
	Compile time struct templated on type T,
	contains various physical constants.
	********************************************/
	template<typename T>struct DerivedPhyConsts {

		/* U0 - normal potential at elipsoid in units: m^2*1/s^2 */
		constexpr  static T U0{ 6263686.0850 * 10.0 };
		/* Spherical harmonic coefficient */
		constexpr  static T J4{ -0.00000237091222 };
		/* Spherical harmonic coefficient*/
		constexpr  static T J6{ 0.00000000608347 };
		/* Spherical harmonic coefficient */
		constexpr  static T J8{ -0.00000000001427 };
		/* Value of m, m = omega^2*a^2*b/GM */
		constexpr  static T m{ 0.00344978600308 };
		/* Normal gravity at equator in ms^-2*/
		constexpr  static T gEq{ 9.7803267715 };
		/* Normal gravity at pole in ms^-2*/
		constexpr  static T gP{ 9.8321863685 };
		/* Value of f*, f* = (gp - gEq)/gEq */
		constexpr  static T f{ 0.005302440112 };
		/* Value of k, k = (b*gp - agEq)/agEq */
		constexpr  static T k{ 0.001931851353 };
		/* Mass of Earth in kg */
		constexpr  static T M{ 5.97219 * 1.000000000000000000000000E+24 };
		
	};


             
}
#endif /*_GR80_PHY_CONSTS_H_09_04_16*/