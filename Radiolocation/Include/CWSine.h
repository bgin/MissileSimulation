#ifndef _CW_SINE_H_
#define _CW_SINE_H_
// Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
// Sine Waveform signal class.

#include "WaveformInterface.h"
#include "Polarization.h"
#include "LibExceptions.h"
#include "../MathLib/MathConstants.h"

namespace  radiolocation
{

	class  CWSineSignal : public  Waveform
	{

	public:

		CWSineSignal() = default;

		CWSineSignal(_In_  struct CWSineParams const&);
			
		CWSineSignal(_In_ const double, _In_ const double, _In_ const double, _In_ size_t);

		CWSineSignal(_In_ const CWSineSignal &);

		CWSineSignal(_In_ CWSineSignal &&);

		

		~CWSineSignal()
		{

		}

		__forceinline   std::vector<std::pair<double, double>>  get_sine_signal() const;

		__forceinline   std::vector<double>                     get_signal_envelope() const;

		__forceinline   std::vector<double>                     get_phase() const;

		__forceinline   double                                  get_frequency() const;

		__forceinline   double                                  get_envelop_freq() const;

		__forceinline   double                                  get_init_time() const;

		__forceinline   double                                  get_interval() const;

		__forceinline   size_t                                  get_samples_count() const;

		__forceinline   double                                  get_duration()  const;

		__forceinline   JonesVector                             polarization() const;

	

		CWSineSignal &  operator=(const CWSineSignal &);

		CWSineSignal &  operator=(_In_ CWSineSignal &&);


#if defined MATHEMATICA_VISUALIZE
	virtual	void    save_to_file(_In_z_ const char*,_In_z_ const char*) const;
#endif

	virtual 	void    quadrature_components_extraction(std::vector<std::pair<double,double>> &, const int) override;


	virtual 	void    complex_envelope(std::vector<std::pair<double, double>> &, std::vector<double> &) override;

	virtual 	void    analytic_signal( const std::vector<double> &, const int) override;

	virtual     void    amplitude_modulation(const double, const double, const double) override;

	virtual     void    frequency_modulation(double, size_t) override;

	virtual     void    phase_modulation(const double, const double, const double, std::function<double(double, double)>&) override;

	virtual     void    instantaneous_frequency(std::vector<double> &) override;

	virtual     std::vector<std::pair<double, double>>    pulse_samples() const override;

	virtual     std::vector<double>  pulse_phase() const override;

	virtual     std::size_t          pulse_samples_count() const override;

#if defined _DEBUG
	virtual     void    debug_print() const override;

#endif
	const static double TWO_PI;

	protected:

		std::vector<std::pair<double, double>> m_sine_signal;

		std::vector<double> m_envelope;

		std::vector<double> m_phase;

		double m_frequency;

		double m_envelope_freq;

		double m_init_time; // initial starting time of signal.

		double m_interval; //time interval increment.

		double m_duration;

		JonesVector  m_polarization; // polarization vector.

		size_t  m_samples; // number of waveform samples

		

		

		

	  

		

		void   initialize(_In_  struct CWSineParams const&);
			
		void   initialize(_In_ const double, _In_ const double, _In_ const double, _In_ const size_t);

		void   initialize(const CWSineSignal &);

		void   initialize(_In_  CWSineSignal &&);

		
	};

	struct  CWSineParams
	{
		_In_  std::function<double(double)> envelope;
		_In_  double  start_time;
		_In_  double  efreq;
		_In_  double  sfreq;
		_In_  double  duration;
		_In_  double  interval;
		_In_  std::size_t n_samples;
		_In_  int   n_threads;
	};

#include "CWSine.inl"
}
#endif  /*_CW_SINE_H_*/