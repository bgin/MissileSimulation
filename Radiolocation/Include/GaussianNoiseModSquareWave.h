#ifndef _GAUSSIAN_NOISE_MOD_SQUARE_WAVE_H_
#define _GAUSSIAN_NOISE_MOD_SQUARE_WAVE_H_


/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Modulated Square Wave with Additive White Gaussian Noise class - definition.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

#include "SquareWaveModulated.h"
#include <random>

namespace radiolocation
{

	class AWGNMSquareWave : public  SquareWaveMSignal
	{



	public:

		/*
		@brief  Constructors.
		*/
		AWGNMSquareWave(_In_  struct AWGNMSWParams const&);

		AWGNMSquareWave(_In_  struct AWGNMSWParams const&, _In_ struct SquareWaveMParams const&);

		AWGNMSquareWave(_In_  AWGNMSquareWave const&);

		AWGNMSquareWave(_In_  AWGNMSquareWave &&);

		/*
		@brief Destructor.
		*/
		~AWGNMSquareWave() {};

		/*
		@brief Member and friend operators
		*/

		AWGNMSquareWave &   operator=(_In_ AWGNMSquareWave const&);

		AWGNMSquareWave &   operator=(_In_ AWGNMSquareWave &&);

		friend  std::ostream &      operator<<(_In_ std::ostream &, _In_ AWGNMSquareWave const&);

		std::pair<double, double>   operator[](_In_ const std::size_t);

		const std::pair<double, double>  operator[](_In_ const std::size_t) const;

		std::vector<std::pair<std::size_t, double>>   operator==(_In_ AWGNMSquareWave const&) const;

		std::vector<std::pair<std::size_t, double>>    operator!=(_In_ AWGNMSquareWave const&) const;

		friend  std::vector<__m256d>       operator==(_In_ AWGNMSquareWave const&, _In_ AWGNMSquareWave const&);

		friend  std::vector<__m256d>       operator!=(_In_ AWGNMSquareWave const&, _In_ AWGNMSquareWave const&);

		/*
		brief  Accessor functions.
		*/

		__forceinline  std::function<double(double)>   WaveformGenerator() const;

		_Field_size_(m_uiSamplesCount) __forceinline  std::vector<std::pair<double, double>>  AWGNMSW() const;

		_Field_size_(m_uiSamplesCount) __forceinline  const  double   *AWGNMSWArray() const;

		__forceinline   std::size_t   SamplesCount() const;

		__forceinline   double        Mean() const;

		__forceinline   double        Variance() const;

		/*
		@brief Member and friend functions.
		*/
#if defined _DEBUG
		virtual    void         debug_print() const override;
#endif

#if defined MATHEMATICA_VISUALIZE
		virtual  void           save_to_file(_In_z_ const char*, _In_z_ const char*, _In_z_ const char*) const;
#endif

		friend    double AWGNMSWScalar(_In_ struct AWGNMSWParams const&);

		friend    std::vector<__m256d>  AWGNMSWAVX(_In_ struct AWGNMSWParams const&);

	private:

		/*
		@brief class members.
		*/
		std::function<double(double)> m_oWaveformGenerator;

		_Field_size_(m_uiSamplesCount) std::vector<std::pair<double, double>>  m_oAWGNMSquareWave;

		std::size_t      m_uiSamplesCount;

		double           m_dMean;

		double           m_dVariance;

		static const double  EPS;

		static const double  PI;
	};



	struct AWGNMSWParams
	{
		_In_ std::function<double(double)> WaveformGenerator;
		_In_ std::size_t SamplesCount;
		_In_ double Mean;
		_In_ double Variance;
	};

#include "GaussianNoiseModSquareWave.inl"
}

#endif /*_GAUSSIAN_NOISE_MOD_SQUARE_WAVE_H_*/