/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Cosine Multiple Target Return class - accessor implementation.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

__forceinline      std::vector<std::pair<double, double>>   radiolocation::PCWaveTwoTargetReturn::PCTwoTargetReturn() const
{
	return this->m_oPCTwoTargetReturn;
}

__forceinline      std::vector<double>                      radiolocation::PCWaveTwoTargetReturn::Phase() const
{
	return this->m_oPhase;
}

__forceinline      std::size_t           radiolocation::PCWaveTwoTargetReturn::SamplesCount() const
{
	return this->m_uiSamplesCount;
}

__forceinline      double                radiolocation::PCWaveTwoTargetReturn::Amplitude1() const
{
	return this->m_dAmplitude1;
}

__forceinline      double                radiolocation::PCWaveTwoTargetReturn::Amplitude2() const
{
	return this->m_dAmplitude2;
}

__forceinline      double                radiolocation::PCWaveTwoTargetReturn::CentralFrequency() const
{
	return this->m_dCentralFrequency;
}

__forceinline      double                radiolocation::PCWaveTwoTargetReturn::Target1Range() const
{
	return this->m_dTarget1Range;
}

__forceinline      double                radiolocation::PCWaveTwoTargetReturn::Target2Range() const
{
	return this->m_dTraget2Range;
}

__forceinline      double                radiolocation::PCWaveTwoTargetReturn::ToA1() const
{
	return this->m_dToA1;
}

__forceinline      double                radiolocation::PCWaveTwoTargetReturn::ToA2() const
{
	return this->m_dToA2;
}

__forceinline      double                radiolocation::PCWaveTwoTargetReturn::TwoTargetRCS() const
{
	return this->m_dTwoTargetRCS;
}

__forceinline      double                radiolocation::PCWaveTwoTargetReturn::Psi() const
{
	return this->m_dPsi;
}