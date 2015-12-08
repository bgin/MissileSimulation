
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Exponential Chirp with Additive White Gaussian Noise class - inline functions implementation.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

__forceinline  std::function<double(double)>   radiolocation::AWGNExpChirp::WaveformGenerator() const
{
	return this->m_oWaveformGenerator;
}

__forceinline  std::vector<std::pair<double, double>>   radiolocation::AWGNExpChirp::AWGNEChirp() const
{
	return this->m_oAWGNEChirp;
}

__forceinline  const  double     *radiolocation::AWGNExpChirp::AWGNEChirpArray() const
{
	const double* pAWGNEChirp = &this->m_oAWGNEChirp.operator[](0).second;
	return pAWGNEChirp;
}

__forceinline   std::size_t       radiolocation::AWGNExpChirp::SamplesCount() const
{
	return this->m_uiSamplesCount;
}

__forceinline   double            radiolocation::AWGNExpChirp::Mean() const
{
	return this->m_dMean;
}

__forceinline   double            radiolocation::AWGNExpChirp::Variance() const
{
	return this->m_dVariance;
}