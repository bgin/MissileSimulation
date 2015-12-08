
#ifndef _SI_H_
#define _SI_H_

#include "ComposedUnits.h"
namespace mathlib
{
	template<typename _Ty> class SIUnits : public CompUnits<_Ty>
	{
	public:

		static const Mass kilogram;

		static const Length meter;

		static const Force newton;

		static const Time second;

		static const Acceleration meter_per_sec2;

		static const Viscosity poise;

		static const Pressure pasc;
			

		static  Work joule;

		static const Power watt;

		static const Gravitation g;

		static const Weight weight;

		static const Temperatue temp;

		static       Calorie cal;

	   __forceinline static	mathlib::PhysUnits<double, 1, 2, -2, 0, 0, 0, 0> calorie()
		{
			return mathlib::SIUnits<double>::joule.operator*=(4.1840);
		}

	};
}
#endif /*_SI_H_*/