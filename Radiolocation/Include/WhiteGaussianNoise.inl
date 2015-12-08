
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
White Gaussian Noise class- inline functions implementation.
@aulthor: Bernard Gingold
@version:  1.0  26/10/2015

*/

__forceinline    std::size_t             radiolocation::WGaussianNoise::samples() const
{
	return this->m_samples;
}

__forceinline    std::vector<std::pair<double, double>>  radiolocation::WGaussianNoise::WGNoise() const
{
	return this->m_oWGNoise;
}

__forceinline    double                  radiolocation::WGaussianNoise::mean() const
{
	return this->m_mean;
}

__forceinline    double                  radiolocation::WGaussianNoise::variance() const
{
	return this->m_variance;
}

__forceinline    std::function<double(double)>      radiolocation::WGaussianNoise::WaveformGenerator() const
{
	return this->m_oWaveformGenerator;
}