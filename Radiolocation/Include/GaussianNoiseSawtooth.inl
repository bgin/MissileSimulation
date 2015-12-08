
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Sawtooth Wave with Additive White Gaussian Noise class - inline functions definitions.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

__forceinline     std::function<double(double)>    radiolocation::AWGNSawtooth::WaveformGenerator() const
{
	return this->m_oWaveformGenerator;
}

__forceinline     std::vector<std::pair<double, double>>    radiolocation::AWGNSawtooth::AWGNoSawtooth() const
{
	return this->m_oAWGNoSawtooth;
}

__forceinline      const    double             *radiolocation::AWGNSawtooth::AWGNoSawtoothArray() const
{
	// Ensure that this is been used in current scope.
	const double* pAWGNSawtooth = &this->m_oAWGNoSawtooth.operator[](0).second;
	return pAWGNSawtooth;
}

__forceinline    std::size_t                     radiolocation::AWGNSawtooth::SamplesCount() const
{
	return this->m_uiSamplesCount;
}

__forceinline    double                          radiolocation::AWGNSawtooth::Mean() const
{
	return this->m_dMean;
}

__forceinline    double                          radiolocation::AWGNSawtooth::Variance() const
{
	return this->m_dVariance;
}