#ifndef _GAUSSIAN_NOISE_LIN_CHIRP_H_
#define _GAUSSIAN_NOISE_LIN_CHIRP_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Linear Chirp with Additive White Gaussian Noise class - definition.
@aulthor: Bernard Gingold
@version:  1.0  26/10/2015

*/

#include "LinearChirp.h"
#include  <random>

namespace   radiolocation
{


	class AWGNoiseLinChirp : public  LinearChirpSignal
	{

	public:

		/*
		@brief  Constructors.
		*/
		AWGNoiseLinChirp(_In_ struct AWGNLChirpParams const&);

	_Raises_SEH_exception_	AWGNoiseLinChirp(_In_ struct AWGNLChirpParams const&, _In_ struct LinChirpParams const&);

		AWGNoiseLinChirp(_In_  AWGNoiseLinChirp const&);

		AWGNoiseLinChirp(_In_ AWGNoiseLinChirp &&);

		/*
		@brief Destructor.
		*/
		~AWGNoiseLinChirp()
		{

		}

		/*
		@brief Class and friend operators.
		*/
		AWGNoiseLinChirp &         operator=(_In_ AWGNoiseLinChirp const&);

		AWGNoiseLinChirp &         operator=(_In_ AWGNoiseLinChirp &&);

		friend	std::ostream &         operator<<(_In_ std::ostream &, _In_ AWGNoiseLinChirp const&);

		

		std::pair<double, double>    operator[](_In_ const std::size_t);

		const  std::pair<double, double>   operator[](_In_ const std::size_t) const;

	_Field_size_(m_uiSamplesCount)	std::vector<std::pair<std::size_t, double>>     operator==(_In_ AWGNoiseLinChirp const&) const;

	_Field_size_(m_uiSamplesCount)	std::vector<std::pair<std::size_t, double>>      operator!=(_In_ AWGNoiseLinChirp const&) const;

		friend  std::vector<__m256d>         operator==(_In_ AWGNoiseLinChirp const&, _In_ AWGNoiseLinChirp const&);

		friend  std::vector<__m256d>         operator!=(_In_ AWGNoiseLinChirp const&, _In_ AWGNoiseLinChirp const&);

		/*
		'brief Accessor inlined functions.
		*/

	__forceinline 	std::function<double(double)>       WaveformGenerator() const;

 _Field_size_(m_uiSamplesCount)	__forceinline   std::vector<std::pair<double, double>>   AWGNLChirp() const;

 _Outptr_opt_result_z_  	__forceinline   const    double           *AWGNLChirpArray() const;

      

	__forceinline   std::size_t       SamplesCount() const;

	__forceinline   double            Mean() const;

	__forceinline   double            Variance() const;

	/*
	@brief  Member and friend functions.
	*/

#if defined _DEBUG
	virtual    void          debug_print() const override;
#endif

#if defined MATHEMATICA_VISUALIZE
	_Maybe_raises_SEH_exception_  virtual    void          save_to_file(_In_z_ const char*, _In_z_ const char*, _In_z_ const char*) override;
#endif


	friend   std::vector<__m256d>     AWGNLChirpAVX(_In_ struct AWGNLChirpParams const&);

	friend   double                   AWGNLChirpScalar(_In_ struct AWGNLChirpParams const&);


	private:

		std::function<double(double)> m_oWaveformGenerator;

		_Field_size_(m_uiSamplesCount) std::vector<std::pair<double, double>> m_oAWGNLChirp;

		std::size_t  m_uiSamplesCount;

		double    m_dMean;

		double    m_dVariance;

		static const double PI;

		static const double EPS;
	};


	struct AWGNLChirpParams
	{
		_In_ std::function<double(double)> WaveformGenerator;
		_In_ double  Mean;
		_In_ double  Variance;
		_In_ std::size_t  SamplesCount;
	};

#include "GaussianNoiseLinChirp.inl"
}

#endif /*_GAUSSIAN_NOISE_LIN_CHIRP_H_*/