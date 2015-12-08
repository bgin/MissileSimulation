
#ifndef _COMPOSED_UNITS_H_
#define _COMPOSED_UNITS_H_

#include "FundamentalPhysUnits.h"

namespace mathlib
{
	

	template<typename _Ty> class CompUnits : public FundamentalUnits<_Ty>
	{
	public:

		typedef mathlib::PhysUnits<_Ty, 0, 1, -1, 0, 0, 0, 0> Velocity;

		typedef mathlib::PhysUnits<_Ty, 0, 1, -2, 0, 0, 0, 0> Acceleration;

		typedef mathlib::PhysUnits<_Ty, 1, 1, -2, 0, 0, 0, 0> Force;

		typedef mathlib::PhysUnits<_Ty, 1, 2, -2, 0, 0, 0, 0> Energy;

		typedef mathlib::PhysUnits<_Ty, 0, 0,  1, 0, 0, 0, 1> AngularVelocity;

		typedef mathlib::PhysUnits<_Ty, 0, 0,  1, 0, 0, 0, -2> AngularAcceleration;

		typedef mathlib::PhysUnits<_Ty, 0, 1, -1, 0, 0, 0, 0> MagnitudeAngVelocity;

		typedef mathlib::PhysUnits<_Ty, 0, 1, -1, 0, 0, 0, 0> CurvilinearVelocity;

		typedef mathlib::PhysUnits<_Ty, 0, 1, -2, 0, 0, 0, 0> CurvilinearAcceleration;

		typedef mathlib::PhysUnits<_Ty, 1, 1, -1, 0, 0, 0, 0> LinearMomentum;

		typedef mathlib::PhysUnits<_Ty, 1, 1, -2, 0, 0, 0, 0> Weight;

		typedef mathlib::PhysUnits<_Ty, 1, -1, -1, 0, 0, 0, 0> Viscosity;

		typedef mathlib::PhysUnits<_Ty, 1, 1, -2, 0, 0, 0, 0> TangentialForce;

		typedef mathlib::PhysUnits<_Ty, 1, 1, -2, 0, 0, 0, 0> Torque;

		typedef mathlib::PhysUnits<_Ty, 1, 2, -2, 0, 0, 0, 0> Work;

		typedef mathlib::PhysUnits<_Ty, 1, 2, -3, 0, 0, 0, 0> Power;

		typedef mathlib::PhysUnits<_Ty, -1, 3, -2, 0, 0, 0, 0> Gravitation;

		typedef mathlib::PhysUnits<_Ty, 0, 2, -2, 0, 0, 0, 0> GravitationalPotential;

		typedef mathlib::PhysUnits<_Ty, 1, -3, -2, 0, 0, 0, 0> Pressure;

		typedef mathlib::PhysUnits<_Ty, 1, 2, -2, 0, 0, 0, 0>     Calorie;
		
		
	};


}
#endif /*_COMPOSED_UNITS_H_*/