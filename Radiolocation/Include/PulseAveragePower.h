#ifndef _PULSE_AVERAGE_POWER_H_
#define _PULSE_AVERAGE_POWER_H_


/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pulse Average Power class - declaration.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

#include "RadLibDefs.h"
#include "LibExceptions.h"
#include "../MathLib/SI.h"

namespace    radiolocation
{


	class PulseAvrgPower
	{

	public:

		/*
		@brief Constructors and Destructor.
		*/

		// Zero-Power Pulse.
		PulseAvrgPower();

		PulseAvrgPower(_In_ struct PulseAvrgdPowParams const&);

		PulseAvrgPower(_In_ PulseAvrgPower const&);

		PulseAvrgPower(_In_ PulseAvrgPower &&);

		virtual	~PulseAvrgPower()
		{

		}

		/*
		@brief:  Friend and member operators
		*/

		PulseAvrgPower &      operator=(_In_ PulseAvrgPower const&);

		PulseAvrgPower &      operator=(_In_ PulseAvrgPower &&);

		friend  std::ostream &       operator<<(_In_  std::ostream &, _In_ PulseAvrgPower const&);

		bool        operator==(_In_  PulseAvrgPower const&) const;

		bool        operator!=(_In_  PulseAvrgPower const&) const;

		double &    operator[](_In_ const std::size_t);

		const  double &  operator[](_In_ const std::size_t) const;

		/*
		@brief  accessor functions
		*/

		__forceinline     double      InterPulsePeriod() const;

		__forceinline     double      PulseWidth() const;

		__forceinline     double      PulsePeakPower() const;

		__forceinline     double      PulseAveragedPower() const;


	protected:

		double m_dInterPulsePeriod;

		double m_dPulseWidth;

		double m_dPulsePeakPower;

		double m_dPulseAveragedPower;
	};



	struct PulseAvrgdPowParams
	{
		_In_ double InterPulsePeriod;
		_In_ double PulseWidth;
		_In_ double PulsePeakPower;
	};

#include "PulseAveragePower.inl"
}
#endif /*_PULSE_AVERAGE_POWER_H_*/