#ifndef _RADAR_RANGE_RESOLUTION_H_
#define _RADAR_RANGE_RESOLUTION_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Radar Range Resolution class - declaration.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

#include "RadLibDefs.h"
#include "LibExceptions.h"

namespace   radiolocation
{


	class RangeResolution
	{

	public:

		/*
		@brief Constructors and Destructor.
		*/

		//Zero-Range.
		RangeResolution();

		RangeResolution(_In_ struct RangeResolutionParams const&);

		RangeResolution(_In_ RangeResolution const&);

		RangeResolution(_In_ RangeResolution &&);

		~RangeResolution() {}

		/*
		@brief Friend and member operators
		*/
       
		RangeResolution &        operator=(_In_ RangeResolution const&);

		RangeResolution &        operator=(_In_ RangeResolution &&);

		friend  std::ostream &   operator<<(_In_ std::ostream &, _In_ RangeResolution const&);

		double &                 operator[](_In_ const std::size_t);

		double const &           operator[](_In_ const std::size_t) const;

		bool                     operator==(_In_ RangeResolution const&) const;

		bool                     operator!=(_In_ RangeResolution const&) const;

		/*
		@brief accessor inline functions.
		*/

		__forceinline            double    RangeGate() const;

		__forceinline            double    DeltaRange() const;

		__forceinline            double    Theta() const;


	private:

		double m_dRangeGate;

		// Max range resolution in meters.
		double m_dDeltaRange; 

		// Max time resolutions of two echo returns in microseconds.
		double m_dTheta;

		
	};


	struct RangeResolutionParams
	{
		_In_ double Rmin;
		_In_ double Rmax;
		_In_ double t1;
		_In_ double t2;
		_In_ double BW; //BandWidth
	};
#include "RadarRangeResolution.inl"
}
#endif  /*_RADAR_RANGE_RESOLUTION_H_*/