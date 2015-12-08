#ifndef _WHITE_GAUSSIAN_NOISE_H_
#define _WHITE_GAUSSIAN_NOISE_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
White Gaussian Noise class- definition
@aulthor: Bernard Gingold
@version:  1.0  26/10/2015

*/

#include "RadLibDefs.h"
namespace  radiolocation
{


	class WGaussianNoise
	{


	public:

		/*
		@Brief: Constructors.
		*/
		WGaussianNoise(_In_ struct WGNoiseParams const&);

		WGaussianNoise(_In_  WGaussianNoise const&);

		WGaussianNoise(_In_  WGaussianNoise&&);

		~WGaussianNoise() = default;

		/*
		@Brief: operators
		*/

		WGaussianNoise &       operator=(_In_ WGaussianNoise const&);

		WGaussianNoise &       operator=(_In_ WGaussianNoise &&);

		friend  std::ostream&    operator<<(_In_ std::ostream&, _In_ WGaussianNoise const&);

		/*
		@Brief: Class accessor methods.
		*/

		__forceinline     std::size_t       samples() const;

		__forceinline     std::vector<std::pair<double, double>> WGNoise() const;

		__forceinline     double            mean() const;

		__forceinline     double            variance() const;

		__forceinline     std::function<double(double)>   WaveformGenerator() const;


#if defined _DEBUG
		void               debug_print() const;
#endif

	private:

		/*
		@Brief: Number of noise vector samples.
		*/
		std::size_t  m_samples;

		/*
		@Brief: White Gaussian Noise vector.
		Contains std::pair.first = normal unit random variables vector, std::pair.second = normal random variables vector.
		*/
		_Field_size_(m_samples) std::vector<std::pair<double, double>> m_oWGNoise; // White Gaussian Noise vector

		/*
		@Brief: mean value.
		*/
		double  m_mean;

		/*
		@Brief: variance value.
		*/
		double  m_variance;

		/*
        @Brief: Noise waveform generator.
		*/
		std::function<double(double)> m_oWaveformGenerator;



	};


	struct WGNoiseParams
	{
		_In_ std::function<double(double)> WaveformGenerator;
		_In_ double mean;
		_In_ double variance;
		_In_ std::size_t n_samples;
	};

#include "WhiteGaussianNoise.inl"
}

#endif /*_WHITE_GAUSSIAN_NOISE_H_*/