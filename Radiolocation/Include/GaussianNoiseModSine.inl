/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Modulated Sine with Additive White Gaussian Noise class - inline functions definition.
@aulthor: Bernard Gingold
@version:  1.0  26/10/2015

*/

__forceinline       std::function<double(double)>      radiolocation::AWGNoiseModSine::WaveformGenerator() const
{
	return this->m_oWaveformGenerator;
}

__forceinline       std::vector<std::pair<double, double>>   radiolocation::AWGNoiseModSine::AWGNModSine() const
{
	return this->m_oAWGNModSine;
}

__forceinline       std::size_t                              radiolocation::AWGNoiseModSine::Samples() const
{
	return this->m_uiSamples;
}

__forceinline       double                                   radiolocation::AWGNoiseModSine::Mean() const
{
	return this->m_dMean;
}

__forceinline       double                                   radiolocation::AWGNoiseModSine::Variance() const
{
	return this->m_dVariance;
}

__forceinline      const    double                          *radiolocation::AWGNoiseModSine::AWGNModSineArray() const
{
	const double* pAWGNModSine = &this->m_oAWGNModSine[0].second;
	return pAWGNModSine;
}