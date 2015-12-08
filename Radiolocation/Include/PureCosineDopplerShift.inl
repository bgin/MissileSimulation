/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Cosine Doppler Shift class - accessor implementation.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

__forceinline     std::vector<std::pair<double, double>>    radiolocation::PureCosDopplerShifted::PureCosDopplerShift() const
{
	return this->m_oPureCosDopplerShift;
}

__forceinline     const       double            *radiolocation::PureCosDopplerShifted::PCDopplerShiftArray() const
{
	const double* pPCDS = nullptr;
	pPCDS = &this->m_oPureCosDopplerShift.operator[](0).second;
	return pPCDS;
}

__forceinline     std::vector<double>    radiolocation::PureCosDopplerShifted::PhaseArg() const
{
	return this->m_oPhaseArg;
}

__forceinline     std::size_t            radiolocation::PureCosDopplerShifted::SamplesCount() const
{
	return this->m_uiSamplesCount;
}

__forceinline     double                 radiolocation::PureCosDopplerShifted::Amplitude() const
{
	return this->m_dAmplitude;
}

__forceinline     double                 radiolocation::PureCosDopplerShifted::InitTargetDetRange() const
{
	return this->m_dInitTargetDetRange;
}

__forceinline     double                 radiolocation::PureCosDopplerShifted::DopplerFrequency() const
{
	return this->m_dDopplerFrequency;
}

__forceinline     double                 radiolocation::PureCosDopplerShifted::F0() const
{
	return this->m_dF0;
}

__forceinline     double                 radiolocation::PureCosDopplerShifted::InitTime() const
{
	return this->m_dInitTime;
}

__forceinline     double                 radiolocation::PureCosDopplerShifted::TargetRange() const
{
	return this->m_dTargetRange;
}

__forceinline     double                 radiolocation::PureCosDopplerShifted::TargetVelocity() const
{
	return this->m_dTargetVelocity;
}

__forceinline     double                 radiolocation::PureCosDopplerShifted::TimeStep() const
{
	return this->m_dTimeStep;
}

__forceinline     radiolocation::JonesVector   radiolocation::PureCosDopplerShifted::Polarization() const
{
	return this->m_oPolarization;
}

/*__forceinline     bool                radiolocation::PureCosDopplerShifted::TargetDirection() const
{
	return this->m_bTargetDirection;
}*/

__forceinline       mathlib::VecF64AVX        radiolocation::PureCosDopplerShifted::TargetDirection() const
{
	return this->m_oTargetDirection;
}

__forceinline     double              radiolocation::PureCosDopplerShifted::TargetRadarAngle() const
{
	return this->m_dTargetRadarAngle;
}