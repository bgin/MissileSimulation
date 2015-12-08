#ifndef _GAUSSIAN_NOISE_SQUARE_WAVE_H_
#define _GAUSSIAN_NOISE_SQUARE_WAVE_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Square Wave with Additive White Gaussian Noise class - definition.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

#include "SquareWave.h"
#include <random>

namespace  radiolocation
{

	class AWGNSquareWave : public  SquareWaveSignal
	{


	public:


		/*
		@brief  Constructors.
		*/

		AWGNSquareWave(_In_  struct AWGNSWParams const&);

		AWGNSquareWave(_In_ struct AWGNSWParams const&, _In_ struct SquareWaveParams const&);

		AWGNSquareWave(_In_ AWGNSquareWave const&);

		AWGNSquareWave(_In_ AWGNSquareWave &&);

		/*
		@brief Destructor.
		*/
		~AWGNSquareWave() {}

		/*
		@brief  Member and friend operators.
		*/

		AWGNSquareWave &       operator=(_In_  AWGNSquareWave const&);

		AWGNSquareWave &       operator=(_In_ AWGNSquareWave &&);

		friend  std::ostream &         operator<<(_In_ std::ostream &, _In_ AWGNSquareWave const&);

		std::pair<double, double>       operator[](_In_ const std::size_t);

		const  std::pair<double, double>    operator[](_In_ const std::size_t) const;

		std::vector<std::pair<std::size_t, double>>      operator==(_In_ AWGNSquareWave const&) const;

		std::vector<std::pair<std::size_t, double>>       operator!=(_In_ AWGNSquareWave const&) const;

		friend   std::vector<__m256d>       operator==(_In_ AWGNSquareWave const& lhs, _In_ AWGNSquareWave const& rhs);

		friend   std::vector<__m256d>       operator!=(_In_ AWGNSquareWave const& lhs, _In_ AWGNSquareWave const& rhs);

		/*
		@brief
		*/

		__forceinline   std::function<double(double)>     WaveformGenerator() const;

		_Field_size_(m_uiSamplesCount)		__forceinline   std::vector<std::pair<double, double>>  AWGNSqWave() const;

	    _Field_size_(m_uiSamplesCount)	__forceinline   const   double         *AWGNSqWaveArray() const;

	   __forceinline std::size_t          SamplesCount() const;

	   __forceinline            double    Mean() const;

	   __forceinline            double    Variance() const;



		/*
		@brief Member and friend functions.
		*/

#if defined   _DEBUG
		virtual    void         debug_print() const override;
#endif

#if defined  MATHEMATICA_VISUALIZE
		virtual    void         save_to_file(_In_z_ const char*, _In_z_ const char*) const;
#endif

		friend     double       AWGNSWaveScalar(_In_ AWGNSWParams const&);

		friend     std::vector<__m256d>   AWGNSWaveAVX(_In_ AWGNSWParams const&);


	private:

		std::function<double(double)> m_oWaveformGenerator;

		_Field_size_(m_uiSamplesCount) std::vector<std::pair<double, double>>  m_oAWGNSquareWave;

		std::size_t  m_uiSamplesCount;

		double  m_dMean;

		double  m_dVariance;

		static const double EPS;

		static const double PI;
	};





	struct AWGNSWParams
	{
		_In_ std::function<double(double)>  WaveformGenerator;
		_In_ std::size_t  SamplesCount;
		_In_ double Mean;
		_In_ double Variance;
	};

#include "GaussianNoiseSquareWave.inl"

}
#endif