#ifndef _GAUSSIAN_NOISE_EXP_CHIRP_H_
#define _GAUSSIAN_NOISE_EXP_CHIRP_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Exponential Chirp with Additive White Gaussian Noise class - definition.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

#include "ExpChirp.h"
#include <random>

namespace   radiolocation
{


	class AWGNExpChirp : public  ExpChirpSignal
	{


	public:

		/*
		@brief Class Constructors and Destructor.
		*/
		AWGNExpChirp(_In_ struct AWGNEChirpParams const&);

	_Raises_SEH_exception_	AWGNExpChirp(_In_ struct AWGNEChirpParams const&, _In_ struct ExpChirpParams const&);

		AWGNExpChirp(_In_ AWGNExpChirp const&);

		AWGNExpChirp(_In_ AWGNExpChirp &&);

		~AWGNExpChirp()
		{

		}

		/*
		@brief Class member and friend operators.
		*/

		AWGNExpChirp &       operator=(_In_ AWGNExpChirp const&);

		AWGNExpChirp &       operator=(_In_ AWGNExpChirp &&);

		AWGNExpChirp &       operator+=(_In_ AWGNExpChirp const&);

		friend  std::ostream &   operator<<(_In_ std::ostream &, _In_ AWGNExpChirp const&);

		std::pair<double, double>   operator[](_In_ const std::size_t);

		const  std::pair<double, double>   operator[](_In_ const std::size_t) const;

		_Field_size_(m_uiSamplesCount) std::vector<std::pair<std::size_t, double>>  operator==(_In_ AWGNExpChirp const&) const;

		_Field_size_(m_uiSamplesCount) std::vector<std::pair<std::size_t, double>>   operator!=(_In_ AWGNExpChirp const&) const;

		friend  std::vector<__m256d>   operator==(_In_ AWGNExpChirp const&, _In_ AWGNExpChirp const&);

		friend  std::vector<__m256d>   operator!=(_In_ AWGNExpChirp const&, _In_ AWGNExpChirp const&);

		//friend  AWGNExpChirp    operator+(_In_ AWGNExpChirp const&, _In_ AWGNExpChirp const&);

		/*
		@brief Accessor inlined functions.
		*/

	__forceinline	std::function<double(double)>  WaveformGenerator() const;

    __forceinline 	_Field_size_(m_uiSamplsCount)	std::vector<std::pair<double, double>>  AWGNEChirp() const;

    __forceinline	_Outptr_result_buffer_(m_uiSamplesCount)  const  double       *AWGNEChirpArray() const;

	__forceinline 	std::size_t    SamplesCount() const;

	__forceinline	double         Mean() const;

	__forceinline	double         Variance() const;

	/*
	@brief Member and friend functions.
	*/
#if defined _DEBUG
	virtual    void      debug_print() const override;
#endif

#if defined  MATHEMATICA_VISUALIZE
	virtual    void      save_to_file(_In_z_ const char*, _In_z_ const char*, _In_z_ const char*) override;
#endif

	
	friend  double   AWGNEChirpScalar(_In_ struct AWGNEChirpParams const&);

	friend  std::vector<__m256d>   AWGNEChirpAVX(_In_ struct AWGNEChirpParams const&);

	private:

		std::function<double(double)> m_oWaveformGenerator;

		_Field_size_(m_uiSamplesCount) std::vector<std::pair<double,double>> m_oAWGNEChirp;

		std::size_t m_uiSamplesCount;

		double    m_dMean;

		double    m_dVariance;

		static const double PI;

		static const double EPS;
	};



	struct  AWGNEChirpParams
	{
		_In_ std::function<double(double)> WaveformGenerator;
		_In_ double Mean;
		_In_ double Variance;
		_In_ std::size_t SamplesCount;
	};

#include "GaussianNoiseExpChirp.inl"
}
#endif /*_GAUSSIAN_NOISE_EXP_CHIRP_H_*/