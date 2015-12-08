#ifndef _CW_COSINE_H_
#define _CW_COSINE_H_
// Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
// Cosine Waveform signal class.

#include "WaveformInterface.h"
//#include "WaveformPolarization.h"
#include "Polarization.h"
#include "LibExceptions.h"
#include "../MathLib/MathConstants.h"

namespace  radiolocation
{

	class CWCosineSignal : public  Waveform
	{

	public:

		CWCosineSignal() = default;
		
		CWCosineSignal(_In_ struct CWCosineParams const&);

		CWCosineSignal(_In_ const double, _In_ const double, _In_ const double, _In_ const size_t);

		CWCosineSignal(_In_ const CWCosineSignal &);

		CWCosineSignal(_In_ CWCosineSignal &&);

		~CWCosineSignal()
		{

		}


		__forceinline   std::vector<std::pair<double, double>>  get_cos_signal() const;

		__forceinline   std::vector<double>                     get_signal_envelope() const;

		__forceinline   std::vector<double>                     get_phase() const;

		__forceinline   double                                  get_frequency()  const;

		
		__forceinline   double                                  get_env_frequency() const;
		

		__forceinline   double                                  get_interval()  const;

		__forceinline   double                                  get_init_time() const;

		__forceinline   double                                  get_duration() const;

		__forceinline   size_t                                  get_num_samples() const;

		__forceinline   JonesVector                             polarization() const;

		CWCosineSignal &  operator=(_In_ const CWCosineSignal &);

		CWCosineSignal &  operator=(_In_ CWCosineSignal &&);

#if defined MATHEMATICA_VISUALIZE
	virtual  	void                                    save_to_file(const char*,const char*);
#endif

		virtual         void                                    quadrature_components_extraction(std::vector<std::pair<double, double>> &, const int) override;

		virtual         void                                    complex_envelope(std::vector<std::pair<double, double>> &, std::vector<double> &) override;

		virtual         void                                    analytic_signal(const std::vector<double> &, const int) override;

		virtual         std::vector<std::pair<double, double>>   pulse_samples() const override;

		virtual         std::size_t                              pulse_samples_count() const override;

#if defined _DEBUG
		virtual         void                                    debug_print() const override;
#endif
	protected:

	_Field_size_(m_samples)	std::vector<std::pair<double, double>> m_cos_signal;

	_Field_size_(m_samples)	std::vector<double> m_envelope; // signal envelope.

	_Field_size_(m_samples) std::vector<double> m_phase; // phase argument.

		double  m_frequency; // carrier frequency

		double  m_efrequency; // envelope signal frequency

		

		double  m_interval; // samples interval

		double  m_init_time; // starting time-point of samples measurement

		size_t  m_samples; // number of std::pair<double,double> samples

		double  m_duration; // signal duration in ns.

		JonesVector m_polarization; // signal linear polarization.

		const   static double  TWO_PI;

		

		
			
		void    initialize(_In_ struct  CWCosineParams const&);

		void    initialize(_In_ const double, _In_ const double, _In_ const double, _In_ const size_t);

		void    initialize(_In_ const CWCosineSignal &);

		void    initialize(_In_ CWCosineSignal &&);



	};

	struct CWCosineParams
	{
		_In_ std::function<double(double)> envelope;
		_In_ double cfreq;
		_In_ double efreq;
		_In_ double duration;
		_In_ double interval;
		_In_ double start_time;
		_In_ std::size_t n_samples;
		_In_  int  n_threads;
	};

}

#include "CWCosine.inl"
#endif  _CW_COSINE_H_

