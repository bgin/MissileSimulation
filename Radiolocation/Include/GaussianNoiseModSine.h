#ifndef _GAUSSIAN_NOISE_MOD_SINE_H_
#define _GAUSSIAN_NOISE_MOD_SINE_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Modulated Sine with Additive White Gaussian Noise class - definition.
@aulthor: Bernard Gingold
@version:  1.0  26/10/2015

*/

#include "CWSine.h"
#include <random>


namespace   radiolocation
{


	class AWGNoiseModSine : public CWSineSignal
	{


	public:

		_Raises_SEH_exception_	AWGNoiseModSine(_In_ struct AWGNModSineParams const&);

		_Raises_SEH_exception_  AWGNoiseModSine(_In_ struct AWGNModSineParams const&, _In_ struct CWSineParams const&);

		AWGNoiseModSine(_In_ AWGNoiseModSine const&);

		AWGNoiseModSine(_In_ AWGNoiseModSine &&);

		~AWGNoiseModSine()
		{

		}

		AWGNoiseModSine &    operator=(_In_ AWGNoiseModSine const&);

		AWGNoiseModSine &    operator=(_In_ AWGNoiseModSine &&);

		friend  std::ostream    &        operator<<(_In_ std::ostream &, _In_ AWGNoiseModSine const&);

		double               operator()(_In_ AWGNModSineParams const&) const;

		std::pair<double, double>      operator[](_In_ const std::size_t);

		const  std::pair<double, double>  operator[](_In_ const std::size_t) const;

	_Field_size_(m_uiSamples)	std::vector<std::pair<std::size_t, double>>   operator==(_In_ AWGNoiseModSine const&) const;

	_Field_size_(m_uiSamples)	std::vector<std::pair<std::size_t, double>>    operator!=(_In_ AWGNoiseModSine const&) const;

	/*
	@brief  Accessor inline functions.
	*/
		__forceinline   std::function<double(double)>    WaveformGenerator() const;

	_Field_size_(m_uiSamples)	__forceinline   std::vector<std::pair<double, double>>  AWGNModSine() const;

		__forceinline   const    double                        *AWGNModSineArray() const;

		__forceinline   std::size_t        Samples() const;

		__forceinline   double             Mean() const;

		__forceinline   double             Variance() const;

	_Raises_SEH_exception_	virtual             void               analytic_signal(_In_ std::vector<double> const&, _In_ const int) override;

		

	friend	std::vector<__m256d>   operator==(_In_ AWGNoiseModSine const&, _In_ AWGNoiseModSine const&);

	friend  std::vector<__m256d>   operator!=(_In_ AWGNoiseModSine const&, _In_ AWGNoiseModSine const&);

#if defined _DEBUG
	virtual   void    debug_print() const override;
#endif

#if defined MATHEMATICA_VISUALIZE
	/*
	@brief Calls base version only on instantiated  AWGNoiseModSine(_In_ struct AWGNModSineParams const&, _In_ struct CWSineParams const&);
	*/
	virtual   void    save_to_file(_In_z_ const char*, _In_z_ const char*) const override;
#endif

	private:

		std::function<double(double)> m_oWaveformGenerator;

	_Field_size_(m_uiSamples)	std::vector<std::pair<double, double>> m_oAWGNModSine;

		std::size_t  m_uiSamples;

		double  m_dMean;

		double  m_dVariance;

		const static double PI;

		const static double EPS;

		double       gaussian_uniform_distr() const;
	};


	struct AWGNModSineParams
	{
		_In_ std::function<double(double)> WaveformGenerator;
		_In_ std::size_t Samples;
		_In_ double Mean;
		_In_ double Variance;
	};

#include "GaussianNoiseModSine.inl"
}
#endif /*_GAUSSIAN_NOISE_MOD_SINE_H_*/