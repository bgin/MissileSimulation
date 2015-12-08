#ifndef _RANGE_MEASUREMENT_H_
#define _RANGE_MEASUREMENT_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Range Measurement class - definition.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/
#include "RadLibDefs.h"
#include "LibExceptions.h"


namespace  radiolocation
{

	class RangeToTarget
	{

	public:

		/*
		brief Constructors and Destructor.
		*/

		// zero range.
		RangeToTarget();

		RangeToTarget(_In_ const double);

		RangeToTarget(_In_ const double, _In_ const double);

		RangeToTarget(_In_ RangeToTarget const&);

		RangeToTarget(_In_ RangeToTarget &&);

		~RangeToTarget() {};

		/*
		@brief member and friend operators
		*/

		RangeToTarget &       operator=(_In_ RangeToTarget const&);

		RangeToTarget &       operator=(_In_ RangeToTarget &&);

		friend  std::ostream &     operator<<(_In_ std::ostream &, _In_ RangeToTarget const&);

		bool          operator==(_In_ RangeToTarget const&) const;

		bool          operator!=(_In_ RangeToTarget const&) const;

		double        operator[](_In_ const std::size_t);

		const         double     operator[](_In_ const std::size_t) const;

		/*
		@brief inline accessor methods.
		*/

	__forceinline 	double      DeltaTime() const;

	__forceinline   double      Range() const;



	private:

		static const double m_sC;

		double  m_dDeltaTime;

		double  m_dRange;
	};

#include "RangeMeasurement.inl"
}
#endif /*_RANGE_MEASUREMENT_H_*/