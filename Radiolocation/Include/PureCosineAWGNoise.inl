
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Cosine with Additive White Gaussian Noise class- inline functions definition.
@aulthor: Bernard Gingold
@version:  1.0  26/10/2015

*/

__forceinline    std::size_t          radiolocation::PureCosAWGNoise::samples() const
{
	return this->m_samples;
}

__forceinline    std::vector<std::pair<double, double>>  radiolocation::PureCosAWGNoise::CosGaussNoise() const
{
	return this->m_vCosGaussNoise;
}

__forceinline    radiolocation::PureCosineWave           radiolocation::PureCosAWGNoise::CosPulse() const
{
	return this->m_oCosPulse;
}

__forceinline    radiolocation::WGaussianNoise           radiolocation::PureCosAWGNoise::GaussNoise() const
{
	return this->m_oGaussNoise;
}

__forceinline   radiolocation::JonesVector               radiolocation::PureCosAWGNoise::Polarization() const
{
	return this->m_oPolarizationVec;
}

