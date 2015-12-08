/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Square Wave with Additive White Gaussian Noise class - inline functions definition.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

__forceinline      std::function<double(double)>     radiolocation::AWGNSquareWave::WaveformGenerator()const
{
	return this->m_oWaveformGenerator;
}

__forceinline      std::vector<std::pair<double, double>>  radiolocation::AWGNSquareWave::AWGNSqWave() const
{
	return this->m_oAWGNSquareWave;
}

__forceinline      const  double        *radiolocation::AWGNSquareWave::AWGNSqWaveArray() const
{
	const double* pAWGNSquareWave = nullptr;
	pAWGNSquareWave = &this->m_oAWGNSquareWave.operator[](0).second;
	return pAWGNSquareWave;
}

__forceinline     std::size_t             radiolocation::AWGNSquareWave::SamplesCount() const
{
	return this->m_uiSamplesCount;
}

__forceinline      double                 radiolocation::AWGNSquareWave::Mean() const
{
	return this->m_dMean;
}

__forceinline      double                 radiolocation::AWGNSquareWave::Variance() const
{
	return this->m_dVariance;
}

