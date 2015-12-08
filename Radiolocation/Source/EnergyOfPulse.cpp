
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pulse Energy class - declaration.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

#include "EnergyOfPulse.h"

radiolocation::PulseEnergy::PulseEnergy() :
m_dPulseEnergy{ 0.0 }
{

}

radiolocation::PulseEnergy::PulseEnergy(_In_ struct PulseAvrgdPowParams const& p) :
PulseAvrgPower{ p },
m_dPulseEnergy{0.0}
{
	this->m_dPulseEnergy = this->m_dPulseAveragedPower * this->m_dInterPulsePeriod;
}

radiolocation::PulseEnergy::PulseEnergy(_In_ PulseEnergy const& other) : 
m_dPulseEnergy{other.m_dPulseEnergy}
{
	
}

radiolocation::PulseEnergy::PulseEnergy(_In_ PulseEnergy &&other) : 
m_dPulseEnergy{ std::move(other.m_dPulseEnergy) }
{
	
}

radiolocation::PulseEnergy &          radiolocation::PulseEnergy::operator=(_In_ PulseEnergy const& other)
{
	if (this == &other) return *this;

	this->m_dPulseEnergy = other.m_dPulseEnergy;
	return *this;
}

radiolocation::PulseEnergy &           radiolocation::PulseEnergy::operator=(_In_ PulseEnergy &&other)
{
	if (this == &other) return *this;

	this->m_dPulseEnergy = std::move(other.m_dPulseEnergy);
	return *this;
}

std::ostream &        radiolocation::operator<<(_In_ std::ostream &os, _In_ PulseEnergy const& rhs)
{
	os.scientific;
	std::setprecision(15);
	os << "PulseEnergy=" << rhs.m_dPulseEnergy << std::endl;
	return os;
}

bool                  radiolocation::PulseEnergy::operator==(_In_ PulseEnergy const& other) const
{
	if ((std::fabs(this->m_dPulseEnergy) - std::fabs(other.m_dPulseEnergy)) <= std::numeric_limits<double>::epsilon())
		return true;
	else
		return false;
}

bool                   radiolocation::PulseEnergy::operator!=(_In_ PulseEnergy const& other) const
{
	if ((std::fabs(this->m_dPulseEnergy) - std::fabs(other.m_dPulseEnergy)) > std::numeric_limits<double>::epsilon())
		return true;
	else
		return false;
}
