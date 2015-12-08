/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Modulated Cosine with Additive White Gaussian Noise class - inline functions definition.
@aulthor: Bernard Gingold
@version:  1.0  26/10/2015

*/

__forceinline      std::function<double(double)>    radiolocation::AWGNoiseModCos::WaveformGenerator() const
{
	return this->m_oWaveformGenerator;
}

__forceinline      std::vector<std::pair<double, double>>   radiolocation::AWGNoiseModCos::AWGNModCos() const
{
	return this->m_oAWGNModCos;
}

__forceinline      std::size_t                              radiolocation::AWGNoiseModCos::SamplesCount() const
{
	return this->m_uiSamplesCount;
}

__forceinline     double                   radiolocation::AWGNoiseModCos::Mean() const
{
	return this->m_dMean;
}

__forceinline     double                   radiolocation::AWGNoiseModCos::Variance() const
{
	return this->m_dVariance;
}

__forceinline     const          double      *radiolocation::AWGNoiseModCos::AWGNModCosArray() const
{
	const double*  pAWGNMCos = &this->m_oAWGNModCos.operator[](0).second;
	return pAWGNMCos;
}