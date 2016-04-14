#ifndef _GR80_GEO_CONSTS_H_08_04_16
#define _GR80_GEO_CONSTS_H_08_04_16

/* Copyright(c) 2015, Bernard Gingold.License: MIT License(http ://www.opensource.org/licenses/mit-license.php)
Geodesic Reference System 80 - Geometric Constants - declaration.

@file GR80GeoConsts.h
@author: Bernard Gingold
@version : 1.0.0  25 / 12 / 2015
@description : GR80GeoConsts.h
@reference Official paper GR - 80 by H.Moritz


*/


namespace   atmosphere {


	/*************************************************
	   Compile time struct templated on type T 
	   contains various Geometric(Geodetic) constants
	*************************************************/

	template<typename T> struct GeoConsts{

		/* Semiminor Axis */
		constexpr  static T b{ 6356752.3141 }; 
		/* Linear Excentricity */
		constexpr  static T E{ 521854.0097 };
		/* Polar radius of curvature */
		constexpr  static T c{ 6399593.6259 };
		/* First excentricity */
		constexpr  static T epower{ 0.00669438002290 };
		/* Second excentricity */
		constexpr  static T e2power{ 0.00673949677548 };
		/* flatening */
		constexpr  static T f{ 0.00335281068118 };
		/* reciprocal flatening*/
		constexpr  static T inv_f{ 298.2572201 };
		/* Meridian Quadrant */
		constexpr  static T Q{ 10001965.7293 };
		/* Mean radius, R1=(2a+b)/3 */
		constexpr  static T R1{ 6371008.7714 };
		/* Radius of surface of same sphere */
		constexpr  static T R2{ 6371007.1810 };
		/* Radius of sphere of same volume */
		constexpr  static T R3{ 6371000.7900 };
		/* Equatoial radius of the Earth */
		constexpr  static T R{ 6378137.0 };
		/* Geocentric gravitational const of the Earth
		including atmosphere in units of m^3*s^-2*/
		constexpr  static T GM{ 3986005.0 * 10.0E+8 };
		/* Dynamical form factor of the Earth,
		excuding permanent tidal deformation */
		constexpr  static T J2{ 108263.0 * 10.0E-8 };
		/* Angular velocity of the Earth in units of rad/s*/
		constexpr  static T omega{ 7292115.0 * 10.0E-11 };
	 };


}
#endif  /*_GR80_GEO_CONSTS_H_08_04_16*/