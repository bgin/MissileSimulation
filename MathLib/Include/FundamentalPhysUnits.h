
#ifndef _FUNDAMENTAL_PHYS_UNITS_H_
#define _FUNDAMENTAL_PHYS_UNITS_H_

#include "PhysicalUnits.h"

namespace mathlib
{
	template<typename _Ty> class FundamentalUnits 
	{

	public:

		typedef mathlib::PhysUnits<_Ty, 1, 0, 0, 0, 0, 0, 0> Mass;

		typedef mathlib::PhysUnits<_Ty, 0, 1, 0, 0, 0, 0, 0> Length;

		typedef mathlib::PhysUnits<_Ty, 0, 0, 1, 0, 0, 0, 0> Time;

		typedef mathlib::PhysUnits<_Ty, 0, 0, 0, 1, 0, 0, 0> Charge;

		typedef mathlib::PhysUnits<_Ty, 0, 0, 0, 0, 1, 0, 0> Temperatue;

		typedef mathlib::PhysUnits<_Ty, 0, 0, 0, 0, 0, 1, 0> Intensity;

		typedef mathlib::PhysUnits<_Ty, 0, 0, 0, 0, 0, 0, 1> Angle;

	};
}
#endif /*_FUNDAMENTAL_PHYS_UNITS_H_*/