/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Radar Range Resolution class - accessors implementation.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

__forceinline    double          radiolocation::RangeResolution::DeltaRange() const
{
	return this->m_dDeltaRange;
}

__forceinline    double          radiolocation::RangeResolution::RangeGate() const
{
	return this->m_dRangeGate;
}

__forceinline    double          radiolocation::RangeResolution::Theta() const
{
	return this->m_dTheta;
}