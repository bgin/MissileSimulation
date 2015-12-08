
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Linear Chirp with Additive White Gaussian Noise class - inline functions implementation.
@aulthor: Bernard Gingold
@version:  1.0  26/10/2015

*/

__forceinline     std::function<double(double)>       radiolocation::AWGNoiseLinChirp::WaveformGenerator() const
{
	return this->m_oWaveformGenerator;
}

__forceinline     std::vector<std::pair<double, double>>    radiolocation::AWGNoiseLinChirp::AWGNLChirp() const
{
	return  this->m_oAWGNLChirp;
}

__forceinline     const     double          *radiolocation::AWGNoiseLinChirp::AWGNLChirpArray() const
{
	const double* pAWGNLChirp = &this->m_oAWGNLChirp.operator[](0).second;
	return pAWGNLChirp;
}

__forceinline    std::size_t                radiolocation::AWGNoiseLinChirp::SamplesCount() const
{
	return this->m_uiSamplesCount;
}

__forceinline    double                     radiolocation::AWGNoiseLinChirp::Mean() const
{
	return this->m_dMean;
}

__forceinline    double                     radiolocation::AWGNoiseLinChirp::Variance() const
{
	return this->m_dVariance;
}