#ifndef _GAUSSIAN_NOISE_MOD_SAWTOOTH_H_
#define _GAUSSIAN_NOISE_MOD_SAWTOOTH_H_


/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Modulated Sawtooth Wave with Additive White Gaussian Noise class - definition.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

#include "SawtoothModulated.h"
#include <random>

namespace     radiolocation
{


	class AWGNMSawtooth : public  SawtoothMSignal
	{

		/*
		@brief Constructors.
		*/

		AWGNMSawtooth(_In_ struct AWGNMSawtoothParams const&);

		AWGNMSawtooth(_In_ struct AWGNMSawtoothParams const&, _In_ struct SawtoothMSignalParams const&);

		AWGNMSawtooth(_In_  AWGNMSawtooth const&);

		AWGNMSawtooth(_In_ AWGNMSawtooth &&);

		/*
		@brief Destructor.
		*/
		~AWGNMSawtooth() {}
		
		
		

		/*
		@brief Member and friend operators.
		*/
		AWGNMSawtooth &        operator=(_In_ AWGNMSawtooth const&);

		AWGNMSawtooth &        operator=(_In_ AWGNMSawtooth &&);

		friend   std::ostream &         operator<<(_In_ std::ostream &, _In_ AWGNMSawtooth const&);

		std::pair<double, double>        operator[](_In_ const std::size_t);

		const   std::pair<double, double>   operator[](_In_ const std::size_t) const;

		AWGNMSawtooth &            operator+=(_In_ AWGNMSawtooth const&);

		std::vector<std::pair<std::size_t, double>>    operator==(_In_ AWGNMSawtooth const&) const;

		std::vector<std::pair<std::size_t, double>>     operator!=(_In_ AWGNMSawtooth const&) const;

		friend std::vector<__m256d>           operator==(_In_ AWGNMSawtooth const&, _In_ AWGNMSawtooth const&);

		friend std::vector<__m256d>           operator!=(_In_ AWGNMSawtooth const&, _In_ AWGNMSawtooth const&);

		/*
		@brief Inline accessor functions.
		*/
		
		__forceinline  std::function<double(double)>    WaveformGenerator() const;

		__forceinline  _Field_size_(m_uiSamplesCount)  std::vector<std::pair<double, double>> AWGNModSawtooth() const;

		__forceinline  _Field_size_(m_uiSamplesCount)  const  double      *AWGNMSawtoothArray() const;

		__forceinline   std::size_t       SamplesCount() const;

		__forceinline   double            Mean() const;

		__forceinline   double            Variance() const;

		/*
		@brief Member and friend functions.
		*/

#if defined _DEBUG
		virtual    void            debug_print() const override;
#endif

#if defined MATHEMATICA_VISUALIZE
		virtual    void            save_to_file(_In_z_ const char*, _In_z_ const char*, _In_z_ const char*) const override;
#endif

		friend    double            AWGNMSawtoothScalar(_In_ struct AWGNMSawtoothParams const&);

		friend    std::vector<__m256d>       AWGNMSawtoothAVX(_In_ struct AWGNMSawtoothParams const&);

	private:

		std::function<double(double)> m_oWaveformGenerator;

		_Field_size_(m_uiSamplesCount) std::vector<std::pair<double, double>> m_oAWGNMSawtooth;

		std::size_t    m_uiSamplesCount;

		double         m_dMean;

		double         m_dVariance;

		static  const  double  EPS;

		static  const  double  PI;
	};


	struct AWGNMSawtoothParams
	{
		_In_  std::function<double(double)> WaveformGenerator;
		_In_  double  Mean;
		_In_  double  Variance;
		_In_  std::size_t SamplesCount;
	};

#include "GaussianNoiseModSawtooth.inl"
}
#endif  /*_GAUSSIAN_NOISE_MOD_SAWTOOTH_H_*/