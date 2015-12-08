/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pulse Average Power class - accessors definition.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

__forceinline    double     radiolocation::PulseAvrgPower::InterPulsePeriod() const
{
	return this->m_dInterPulsePeriod;
}

__forceinline    double     radiolocation::PulseAvrgPower::PulseWidth() const
{
	return this->m_dPulseWidth;
}

__forceinline    double      radiolocation::PulseAvrgPower::PulsePeakPower() const
{
	return this->m_dPulsePeakPower;
}

__forceinline    double       radiolocation::PulseAvrgPower::PulseAveragedPower() const
{
	return this->m_dPulseAveragedPower;
}