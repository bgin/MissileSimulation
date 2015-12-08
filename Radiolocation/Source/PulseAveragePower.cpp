/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pulse Average Power class - implementation.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

#include "PulseAveragePower.h"

radiolocation::PulseAvrgPower::PulseAvrgPower() :
m_dInterPulsePeriod{ 0.0 },
m_dPulseAveragedPower{ 0.0 },
m_dPulsePeakPower{ 0.0 },
m_dPulseWidth{ 0.0 }
{

}

radiolocation::PulseAvrgPower::PulseAvrgPower(_In_ struct PulseAvrgdPowParams const& p) :
m_dInterPulsePeriod{ p.InterPulsePeriod },
m_dPulsePeakPower{ p.PulsePeakPower },
m_dPulseWidth{ p.PulseWidth }
{
	BOOST_ASSERT(this->m_dPulseWidth > 0.0 || this->m_dInterPulsePeriod > 0.0);
	this->m_dPulseAveragedPower = this->m_dPulsePeakPower * (this->m_dPulseWidth / this->m_dInterPulsePeriod);
}

radiolocation::PulseAvrgPower::PulseAvrgPower(_In_ PulseAvrgPower const& other) :
m_dInterPulsePeriod{ other.m_dInterPulsePeriod },
m_dPulseAveragedPower{ other.m_dPulseAveragedPower },
m_dPulsePeakPower{ other.m_dPulsePeakPower },
m_dPulseWidth{ other.m_dPulseWidth }
{

}

radiolocation::PulseAvrgPower::PulseAvrgPower(_In_ PulseAvrgPower &&other) :
m_dInterPulsePeriod{ std::move(other.m_dInterPulsePeriod) },
m_dPulseAveragedPower{ std::move(other.m_dPulseAveragedPower) },
m_dPulsePeakPower{ std::move(other.m_dPulsePeakPower) },
m_dPulseWidth{ std::move(other.m_dPulseWidth) }
{

}

radiolocation::PulseAvrgPower &          radiolocation::PulseAvrgPower::operator=(_In_ PulseAvrgPower const& other)
{
	if (this == &other) return *this;

	this->m_dInterPulsePeriod = other.m_dInterPulsePeriod;
	this->m_dPulseAveragedPower = other.m_dPulseAveragedPower;
	this->m_dPulsePeakPower = other.m_dPulsePeakPower;
	this->m_dPulseWidth = other.m_dPulseWidth;
	return *this;
}

radiolocation::PulseAvrgPower &           radiolocation::PulseAvrgPower::operator=(_In_ PulseAvrgPower &&other)
{
	if (this == &other) return *this;

	this->m_dInterPulsePeriod = std::move(other.m_dInterPulsePeriod);
	this->m_dPulseAveragedPower = std::move(other.m_dPulseAveragedPower);
	this->m_dPulsePeakPower = std::move(other.m_dPulsePeakPower);
	this->m_dPulseWidth = std::move(other.m_dPulseWidth);
	return *this;
}

std::ostream &           radiolocation::operator<<(_In_ std::ostream &os, _In_ PulseAvrgPower const& rhs)
{
	os.scientific;
	std::setprecision(15);
	os << "InterPulsePeriod=" << rhs.m_dInterPulsePeriod << "PulseAvrgPower=" << rhs.m_dPulseAveragedPower <<
		"PulsePeakPower=" << rhs.m_dPulsePeakPower << "PulseWidth=" << rhs.m_dPulseWidth << std::endl;
	return os;
}

bool               radiolocation::PulseAvrgPower::operator==(_In_ PulseAvrgPower const& other) const
{
	if ((std::fabs(this->m_dPulseAveragedPower) - std::fabs(other.m_dPulseAveragedPower)) <= std::numeric_limits<double>::epsilon())
		return true;
	else
		return false;
}

bool                radiolocation::PulseAvrgPower::operator!=(_In_ PulseAvrgPower const& other) const
{
	if ((std::fabs(this->m_dPulseAveragedPower) - std::fabs(other.m_dPulseAveragedPower)) > std::numeric_limits<double>::epsilon())
		return true;
	else
		return false;
}

double    &         radiolocation::PulseAvrgPower::operator[](_In_ const std::size_t index)
{
	BOOST_ASSERT(index >= 0 && index <= 3);
	return (&this->m_dInterPulsePeriod)[index];
}

const    double   &      radiolocation::PulseAvrgPower::operator[](_In_ const std::size_t index) const
{
	BOOST_ASSERT(index >= 0 && index <= 3);
	return (&this->m_dInterPulsePeriod)[index];
}