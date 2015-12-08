/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Modulated Square Wave with Additive White Gaussian Noise class - definition.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

__forceinline   std::function<double(double)>     radiolocation::AWGNMSquareWave::WaveformGenerator() const
{
	return this->m_oWaveformGenerator;
}

__forceinline   std::vector<std::pair<double, double>>   radiolocation::AWGNMSquareWave::AWGNMSW() const
{
	return this->m_oAWGNMSquareWave;
}

__forceinline   const    double        *radiolocation::AWGNMSquareWave::AWGNMSWArray() const
{
	const double* pAWGNMSW = nullptr;
	pAWGNMSW = &this->m_oAWGNMSquareWave.operator[](0).second;
	return pAWGNMSW;
}

__forceinline    std::size_t      radiolocation::AWGNMSquareWave::SamplesCount() const
{
	return this->m_uiSamplesCount;
}

__forceinline    double           radiolocation::AWGNMSquareWave::Mean() const
{
	return this->m_dMean;
}

__forceinline   double            radiolocation::AWGNMSquareWave::Variance() const
{
	return this->m_dVariance;
}