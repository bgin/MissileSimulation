#ifndef _GAUSSIAN_NOISE_MOD_COS_H_
#define _GAUSSIAN_NOISE_MOD_COS_H_


/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Modulated Cosine with Additive White Gaussian Noise class - definition.
@aulthor: Bernard Gingold
@version:  1.0  26/10/2015

*/

#include "CWCosine.h"
#include <random>

namespace  radiolocation
{

	class AWGNoiseModCos : public  CWCosineSignal
	{

	public:
		/*
		@brief: Constructors.
		*/
	    AWGNoiseModCos(_In_ struct AWGNMCosParams const&);

		_Raises_SEH_exception_   AWGNoiseModCos(_In_ struct AWGNMCosParams const&, _In_ struct CWCosineParams const&);

		AWGNoiseModCos(_In_ AWGNoiseModCos const&);

		AWGNoiseModCos(_In_ AWGNoiseModCos &&);

		~AWGNoiseModCos()
		{

		}

		/*
		@brief: Member and friend operators.
		*/
		AWGNoiseModCos &    operator=(_In_ AWGNoiseModCos const&);

		AWGNoiseModCos &    operator=(_In_ AWGNoiseModCos &&);

		friend  std::ostream &    operator<<(_In_ std::ostream &, _In_ AWGNoiseModCos const&);

		double                operator()(_In_ AWGNMCosParams const&) const;

		std::pair<double, double>      operator[](_In_ const std::size_t);

		const   std::pair<double, double>    operator[](_In_ const std::size_t) const;

		std::vector<std::pair<std::size_t, double>>   operator==(_In_ AWGNoiseModCos const&) const;

		std::vector<std::pair<std::size_t, double>>    operator!=(_In_ AWGNoiseModCos const&) const;

		friend  std::vector<__m256d>          operator==(_In_ AWGNoiseModCos const&, _In_ AWGNoiseModCos const&);

		friend  std::vector<__m256d>          operator!=(_In_ AWGNoiseModCos const&, _In_ AWGNoiseModCos const&);

		/*
		@brief: Accessor inlined functions.
		*/

		__forceinline    std::function<double(double)>     WaveformGenerator() const;

		_Field_size_(m_uiSamplesCount)  __forceinline   std::vector<std::pair<double, double>>  AWGNModCos() const;

		_Field_size_(m_uiSamplesCount)  __forceinline   const  double        *AWGNModCosArray() const;

		__forceinline       std::size_t                SamplesCount() const;

		__forceinline       double                     Mean() const;

		__forceinline       double                     Variance() const;

#if defined _DEBUG
		/*
		@brief: Must be called on instantiated AWGNoiseModCos(_In_ struct AWGNMCosParams const&, _In_ struct CWCosineParams const&).
		*/
		virtual      void        debug_print() const override;
#endif

#if defined  MATHEMATICA_VISUALIZE
		/*
		@Overrides base CWCosineSignal::save_to_file. Must be called only on object type
		AWGNoiseModCos(_In_ struct AWGNMCosParams const&, _In_ struct CWCosineParams const&).
		*/
		virtual    void         save_to_file(_In_z_ const char*, _In_z_ const char*)  override;
#endif


	private:

		/*
		@brief Noise waveform generator
		*/
		std::function<double(double)> m_oWaveformGenerator;

		/*
		@brief White Gaussian Noise vector
		*/
		_Field_size_(m_uiSamplesCount) std::vector<std::pair<double, double>> m_oAWGNModCos;

		/*
		@brief Number of noise samples.
		*/
		std::size_t  m_uiSamplesCount;

		/*
		@brief: Mean value.
		*/
		double   m_dMean;

		/*
		@brief: Variance value.
		*/
		double   m_dVariance;

		const static double PI;

		const static double EPS;

		/*
		@brief: Returns single value of Normal Distribution.
		*/
		double       GND() const;
	};

	/*
	@brief Aggregated parameters struct for class AWGNModCos.
	*/
	struct AWGNMCosParams
	{
		_In_  std::function<double(double)> WaveformGenerator;
		_In_  std::size_t  SamplesCount;
		_In_  double   Mean;
		_In_  double   Variance;
	};


#include "GaussianNoiseModCos.inl"
}
#endif /*_GAUSSIAN_NOISE_MOD_COS_H_*/