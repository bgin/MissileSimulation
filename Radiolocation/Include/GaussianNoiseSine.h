#ifndef _GAUSSIAN_NOISE_SINE_H_
#define _GAUSSIAN_NOISE_SINE_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Sine with Additive White Gaussian Noise class - definition.
@aulthor: Bernard Gingold
@version:  1.0  26/10/2015

*/

#include "PureSine.h"
#include <random>

namespace   radiolocation
{

	class AWGNoiseSine : public PureSineWave
	{

	public:

		_Raises_SEH_exception_  AWGNoiseSine(_In_ struct AWGNSineParams const&);

		_Raises_SEH_exception_  AWGNoiseSine(_In_ struct AWGNSineParams const&, _In_ struct PureSineParams const&);

		AWGNoiseSine(_In_  AWGNoiseSine const&);

		AWGNoiseSine(_In_  AWGNoiseSine &&);

		~AWGNoiseSine()
		{

		}

		AWGNoiseSine &     operator=(_In_ AWGNoiseSine const&);

		AWGNoiseSine &     operator=(_In_ AWGNoiseSine &&);

		friend  std::ostream &      operator<<(_In_ std::ostream &, _In_ AWGNoiseSine const&);

		double               operator()(_In_ struct AWGNSineParams const&);

		 std::pair<double,double>              operator[](_In_ const std::size_t);

		const      std::pair<double,double>    operator[](_In_ const std::size_t) const;

		std::vector<std::pair<double, double>>   operator==(_In_ AWGNoiseSine const&) const;

		std::vector<std::pair<double, double>>    operator!=(_In_ AWGNoiseSine const&) const;



		__forceinline     std::function<double(double)>    WaveformGenerator() const;

		__forceinline     std::vector<std::pair<double, double>>  AWGNSine() const;

		__forceinline     const   double                          *AWGNSinArray() const;

		__forceinline     std::size_t    Samples() const;

		__forceinline     double         Mean() const;

		__forceinline     double         Variance() const;


	private:

		std::function<double(double)> m_oWaveformGenerator;

		std::vector<std::pair<double, double>> m_oAWGNSine;

		std::size_t  m_uiSamples;

		double       m_dMean;

		double       m_dVariance;
	};

	/*
	@brief: Aggregated parameters structure for AWGNoiseSine class.
	*/
	struct AWGNSineParams
	{
		_In_ std::function<double(double)> WaveformGenerator;
		_In_ double  Mean;
		_In_ double  Variance;
		_In_ std::size_t  Samples;
	};

#include "GaussianNoiseSine.inl"
}
#endif /*_GAUSSIAN_NOISE_SINE_H_*/