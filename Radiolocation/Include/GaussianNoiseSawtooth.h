#ifndef _GAUSSIAN_NOISE_SAWTOOTH_H_
#define _GAUSSIAN_NOISE_SAWTOOTH_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Sawtooth Wave with Additive White Gaussian Noise class - definition.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

#include "SawtoothWave.h"
#include <random>

namespace  radiolocation
{


	class AWGNSawtooth : public SawtoothSignal
	{

      

	public:

		/*
		@brief Ctors and Dtor.
		*/

		AWGNSawtooth(_In_ struct AWGNSawtoothParams const&);

		AWGNSawtooth(_In_ struct AWGNSawtoothParams const&, _In_ SawtoothSignalParams const&);

		AWGNSawtooth(_In_ AWGNSawtooth const&);

		AWGNSawtooth(_In_ AWGNSawtooth &&);

		~AWGNSawtooth() {}
		

		

		/*
		@brief member and friend operators.
		*/

		AWGNSawtooth &       operator=(_In_ AWGNSawtooth const&);

		AWGNSawtooth &       operator=(_In_ AWGNSawtooth &&);

		AWGNSawtooth &       operator+=(_In_ AWGNSawtooth const&);

		friend  std::ostream &            operator<<(_In_ std::ostream &, _In_ AWGNSawtooth const&);

		std::pair<double, double>     operator[](_In_ const std::size_t);

		const  std::pair<double, double>   operator[](_In_ const std::size_t) const;

		_Field_size_(m_uiSamplesCount) std::vector<std::pair<std::size_t, double>>   operator==(_In_ AWGNSawtooth const&) const;

		_Field_size_(m_uiSamplesCount) std::vector<std::pair<std::size_t, double>>    operator!=(_In_ AWGNSawtooth const&) const;

		friend     std::vector<__m256d>     operator==(_In_ AWGNSawtooth const&, _In_ AWGNSawtooth const&);

		friend     std::vector<__m256d>     operator!=(_In_ AWGNSawtooth const&, _In_ AWGNSawtooth const&);

		/*
		"brief Accessor inline functions.
		*/

		__forceinline  std::function<double(double)>   WaveformGenerator() const;

	    __forceinline	_Field_size_(m_uiSamplesCount) std::vector<std::pair<double, double>>  AWGNoSawtooth() const;

	    __forceinline	_Outptr_result_buffer_(m_uiSamplesCount) const double        *AWGNoSawtoothArray() const;

		__forceinline	std::size_t       SamplesCount() const;

		__forceinline   double            Mean() const;

		__forceinline   double            Variance() const;


		/*
		@brief Member and friend functions.
		*/

#if defined _DEBUG
		virtual    void          debug_print() const override;
#endif

#if defined MATHEMATICA_VISUALIZE
		virtual      void        save_to_file(_In_z_ const char*, _In_z_ const char*) const override;
#endif

		friend       double      AWGNSawtoothScalar(_In_ struct AWGNSawtoothParams const&);

		friend       std::vector<__m256d>    AWGNSawtoothAVX(_In_ struct AWGNSawtoothParams const&);

	private:

		std::function<double(double)> m_oWaveformGenerator;

		_Field_size_(m_uiSamplesCount) std::vector<std::pair<double, double>> m_oAWGNoSawtooth;

		std::size_t  m_uiSamplesCount;

		double  m_dMean;

		double  m_dVariance;

		static const double PI;

		static const double EPS;
	};





	struct AWGNSawtoothParams
	{
		_In_ std::function<double(double)> WaveformGenerator;
		_In_ std::size_t SamplesCount;
		_In_ double Mean;
		_In_ double Variance;
	};


#include "GaussianNoiseSawtooth.inl"
}

#endif /*_GAUSSIAN_NOISE_SAWTOOTH_H_*/