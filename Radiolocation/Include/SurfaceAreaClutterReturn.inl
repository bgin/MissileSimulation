/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Surface Area Clutter class - accessor function implementation.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

__forceinline      double     radiolocation::SurfaceAreaClutter::PhaseDifferential() const
{
	return this->m_dPhaseDifferential;
}

__forceinline      double     radiolocation::SurfaceAreaClutter::ClutterArea() const
{
	return this->m_dClutterArea;
}

__forceinline      double     radiolocation::SurfaceAreaClutter::AvrgClutterRCS() const
{
	return this->m_dAvrgClutterRCS;
}

__forceinline      double     radiolocation::SurfaceAreaClutter::CriticalAngle() const
{
	return this->m_dCriticalAngle;
}

__forceinline      double     radiolocation::SurfaceAreaClutter::GrazingAngle() const
{
	return this->m_dGrazingAngle;
}

__forceinline      double     radiolocation::SurfaceAreaClutter::SurfaceHeight() const
{
	return this->m_dSurfaceHeight;
}

__forceinline      double     radiolocation::SurfaceAreaClutter::Wavelength() const
{
	return this->m_dWavelength;
}