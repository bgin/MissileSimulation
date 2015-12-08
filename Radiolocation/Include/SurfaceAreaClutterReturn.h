#ifndef _SURFACE_AREA_CLUTTER_RETURN_H_
#define _SURFACE_AREA_CLUTTER_RETURN_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Surface Area Clutter class - declaration.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

#include "RadLibDefs.h"

namespace  radiolocation
{

	class SurfaceAreaClutter
	{

		/*
		@brief  Constructors and Destructor.
		*/

		SurfaceAreaClutter(_In_ struct SurAreaCluttParams const&);

		SurfaceAreaClutter(_In_  SurfaceAreaClutter const&);

		SurfaceAreaClutter(_In_  SurfaceAreaClutter &&);

		~SurfaceAreaClutter();


		/*
		@brief Friend and member operators
		*/

		SurfaceAreaClutter &        operator=(_In_ SurfaceAreaClutter const&);

		SurfaceAreaClutter &        operator=(_In_ SurfaceAreaClutter &&);

	   friend	std::ostream &              operator<<(_In_ std::ostream &, _In_ SurfaceAreaClutter const&);

	   double                       operator[](_In_ const std::size_t);

	   const    double              operator[](_In_ const std::size_t) const;

	   bool                         operator==(_In_ SurfaceAreaClutter const&) const;

	   bool                         operator!=(_In_ SurfaceAreaClutter const&) const;

	   friend   bool                operator==(_In_ SurfaceAreaClutter const&, _In_ SurfaceAreaClutter const&);

	   friend   bool                operator!=(_In_ SurfaceAreaClutter const&, _In_ SurfaceAreaClutter const&);

	   /*
	   @brief   accessor inline functions.
	   */

	   __forceinline    double      PhaseDifferential() const;

	   __forceinline    double      CriticalAngle() const;

	   __forceinline    double      SurfaceHeight() const;

	   __forceinline    double      ClutterArea() const;

	   __forceinline    double      AvrgClutterRCS() const;

	   __forceinline    double      Wavelength() const;

	   __forceinline   double       GrazingAngle() const;



	private:

		double m_dPhaseDifferential;

		double m_dCriticalAngle;

		double m_dSurfaceHeight;

		double m_dClutterArea;

		double m_dAvrgClutterRCS;

		double m_dWavelength;

		double m_dGrazingAngle;
	};


	struct SurAreaCluttParams
	{
		_In_ double  SurfaceHeight;
		_In_ double  Wavelength;
		_In_ double  GrazingAngle;
		_In_ double  Range;
		_In_ double  PulseWidth;
		_In_ double  Three_db_beamwidth;
		_In_ double  ClutterScatterCoef;
	};



#include "SurfaceAreaClutterReturn.inl"
}

#endif /*_SURFACE_AREA_CLUTTER_RETURN_H_*/