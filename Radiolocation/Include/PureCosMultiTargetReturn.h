#ifndef _PURE_COS_MULTI_TARGET_RETURN_H_
#define _PURE_COS_MULTI_TARGET_RETURN_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Cosine Multiple Target Return class - declaration.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

#include "PureCosine.h"

namespace   radiolocation
{


	class  PCWaveTwoTargetReturn : public  PureCosineWave
	{


	public:

		/*
		@brief Constructors and Destructor.
		*/
		PCWaveTwoTargetReturn(_In_ struct PureCosineParams const&, _In_  struct PCTTRParams const&);

		PCWaveTwoTargetReturn(_In_  PCWaveTwoTargetReturn const&);

		PCWaveTwoTargetReturn(_In_  PCWaveTwoTargetReturn &&);

		~PCWaveTwoTargetReturn();

		/*
		@brief  Friend and member operators
		*/

		PCWaveTwoTargetReturn &        operator=(_In_ PCWaveTwoTargetReturn const&);

		PCWaveTwoTargetReturn &        operator=(_In_ PCWaveTwoTargetReturn &&);

	    friend	std::ostream &                 operator<<(_In_ std::ostream &, _In_ PCWaveTwoTargetReturn const&);

		std::pair<double, double>       operator[](_In_ const std::size_t);

		const  std::pair<double, double>   operator[](_In_ const std::size_t) const;

		std::vector<std::pair<std::size_t, double>>   operator==(_In_ PCWaveTwoTargetReturn const&) const;

		std::vector<std::pair<std::size_t, double>>    operator!=(_In_ PCWaveTwoTargetReturn const&) const;

		

		/*
		@brief  acessor methods.
		*/

		__forceinline    std::vector<std::pair<double, double>>  PCTwoTargetReturn() const;

		__forceinline    std::vector<double>      Phase() const;

		__forceinline    std::size_t              SamplesCount() const;

		__forceinline    double                   Amplitude1() const;

		__forceinline    double                   Amplitude2() const;

		__forceinline    double                   CentralFrequency() const;

		__forceinline    double                   Target1Range() const;

		__forceinline    double                   Target2Range() const;

		__forceinline    double                   ToA1() const;

		__forceinline    double                   ToA2() const;

		__forceinline    double                   TwoTargetRCS() const;

		__forceinline    double                   Psi() const;


#if defined _DEBUG
		virtual     void         debug_print() const override;
#endif

#if  defined MATHEMATICA_VISUALIZE
		void                save_to_file(_In_z_ const char*, _In_z_ const char*) const;
#endif

		// Return single sample of Received Cosine Waveform.
		double              GenerateWaveformSample(_In_ const double, _In_ const double, _In_ const double) const;

		virtual    std::vector<std::pair<double, double>>   pulse_samples() const override
		{
			return this->PCTwoTargetReturn();
		}

		virtual   std::vector<double>   pulse_phase() const override
		{
			return this->Phase();
		}

		virtual    std::size_t           pulse_samples_count() const override
		{
			return this->SamplesCount();
		}

		_Raises_SEH_exception_  virtual    void      quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &, _In_ const int) override;

	    _Raises_SEH_exception_	virtual    void      analytic_signal(_In_ std::vector<double> const&, _In_ const int) override;


	private:

		_Field_size_(m_uiSamplesCount) std::vector<std::pair<double, double>> m_oPCTwoTargetReturn;

		_Field_size_(m_uiSamplesCount) std::vector<double>  m_oPhase;

		std::size_t m_uiSamplesCount;

		double  m_dAmplitude1;

		double  m_dAmplitude2;

		double  m_dCentralFrequency;

		double  m_dTarget1Range;

		double  m_dTraget2Range;

		double  m_dToA1;

		double  m_dToA2;

		double  m_dTwoTargetRCS;

		double  m_dPsi;

	};


	struct  PCTTRParams
	{
		_In_  double  Target1Range;
		_In_  double  Target2Range;
		_In_  double  Ampitude1;
		_In_  double  Amplitude2;
		_In_  int     nThreads;
	};

#include "PureCosMultiTargetReturn.inl"
}

#endif /*_PURE_COS_MULTI_TARGET_RETURN_H_*/