
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Sine with Additive White Gaussian Noise class- inline functions implementation.
@author: Bernard Gingold
@version:  1.0  26/10/2015

*/

__forceinline  std::function<double(double)>     radiolocation::AWGNoiseSine::WaveformGenerator() const
{
	return this->m_oWaveformGenerator;
}

__forceinline  std::vector<std::pair<double, double>>     radiolocation::AWGNoiseSine::AWGNSine() const
{
	return this->m_oAWGNSine;
}

__forceinline  const    double                            *radiolocation::AWGNoiseSine::AWGNSinArray() const
{
	const double*  pAWGNSine = &this->m_oAWGNSine[0].second; //Take precaution because of scope of *this. Do not return AWGNSinArray from the function where
	// *this was instantiated.
	return pAWGNSine;
}

__forceinline   std::size_t                               radiolocation::AWGNoiseSine::Samples() const
{
	return this->m_uiSamples;
}

__forceinline   double                                   radiolocation::AWGNoiseSine::Mean() const
{
	return this->m_dMean;
}

__forceinline   double                                    radiolocation::AWGNoiseSine::Variance() const
{
	return this->m_dVariance;
}