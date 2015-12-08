#ifndef _ENERGY_OF_PULSE_H_
#define _ENERGY_OF_PULSE_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pulse Energy class - declaration.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

#include "PulseAveragePower.h"

namespace radiolocation
{

	class PulseEnergy : private PulseAvrgPower
	{

	public:

		/*
		@brief Constructors and Destructor.
		*/
		PulseEnergy();

		PulseEnergy(_In_ struct PulseAvrgdPowParams const&);

		PulseEnergy(_In_ PulseEnergy const&);

		PulseEnergy(_In_ PulseEnergy &&);

		~PulseEnergy() {}
		

		

		/*
		@brief Friend and member operators.
		*/

		PulseEnergy &         operator=(_In_ PulseEnergy const&);

		PulseEnergy &         operator=(_In_ PulseEnergy &&);

		friend	std::ostream &    operator<<(_In_ std::ostream &os, _In_ PulseEnergy const&);

		bool             operator==(_In_ PulseEnergy const&) const;

		bool             operator!=(_In_ PulseEnergy const&) const;

		/*
		@brief accessor method.
		*/

		__forceinline      double   PulseEnrg() const;

		// Return pulse energy in units of joule.
		__forceinline      mathlib::SIUnits<double>::Work  PulseEnrgSI() const;

	private:

		double m_dPulseEnergy;
	};

#include "EnergyOfPulse.inl"
}

#endif /*_ENERGY_OF_PULSE_H_*/

