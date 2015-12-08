
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pulse Energy class - declaration.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

__forceinline      double       radiolocation::PulseEnergy::PulseEnrg() const
{
	return this->m_dPulseEnergy;
}

__forceinline      mathlib::SIUnits<double>::Work  radiolocation::PulseEnergy::PulseEnrgSI() const
{
	return mathlib::SIUnits<double>::joule.operator*=(this->PulseEnrg());
}