/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Modulated Sawtooth Wave with Additive White Gaussian Noise class - inline functions definition.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

__forceinline   std::function<double(double)>     radiolocation::AWGNMSawtooth::WaveformGenerator() const
{
	return this->m_oWaveformGenerator;
}

__forceinline   std::vector<std::pair<double, double>>      radiolocation::AWGNMSawtooth::AWGNModSawtooth() const
{
	return this->m_oAWGNMSawtooth;
}

__forceinline    const      double             *radiolocation::AWGNMSawtooth::AWGNMSawtoothArray() const
{
	const double*  pAWGNMSawtooth = nullptr;
	pAWGNMSawtooth = &this->m_oAWGNMSawtooth.operator[](0).second;
	return pAWGNMSawtooth;
}

__forceinline   std::size_t              radiolocation::AWGNMSawtooth::SamplesCount() const
{
	return this->m_uiSamplesCount;
}

__forceinline    double                  radiolocation::AWGNMSawtooth::Mean() const
{
	return this->m_dMean;
}

__forceinline    double                  radiolocation::AWGNMSawtooth::Variance() const
{
	return this->m_dVariance;
}
