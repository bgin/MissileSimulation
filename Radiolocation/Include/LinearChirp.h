#ifndef _LINEAR_CHIRP_H_
#define _LINEAR_CHIRP_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Linear Frequency Modulation(Linear Chirp) signal class - declaration.
@author: Bernard Gingold
@version:  1.0  13/09/2015

*/
#include "WaveformInterface.h"
#include "../MathLib/MathConstants.h"
#include "Polarization.h"
#include "LibExceptions.h"

namespace radiolocation
{

	class LinearChirpSignal : public Waveform
	{

	public:
		//LinearChirpSignal() = default;

		LinearChirpSignal() = default;

		LinearChirpSignal(_In_  struct LinChirpParams const&);
		
		LinearChirpSignal(_In_ const LinearChirpSignal &);

		LinearChirpSignal(_In_ LinearChirpSignal &&);

		~LinearChirpSignal()
		{

		}
		

		


		__forceinline    std::vector<std::pair<double, double>>  get_chirp() const;

		__forceinline    std::vector<double>                     get_envelope() const;

		__forceinline    std::vector<double>                     get_phase() const;

		__forceinline    double                                  get_sfrequency() const;

		__forceinline    double                                  get_efrequency() const;

		__forceinline    double                                  get_iphase() const;

		__forceinline    double                                  get_itime() const;

		__forceinline    double                                  get_interval() const;

		__forceinline    double                                  get_chirp_rate() const;

		__forceinline    double                                  get_envfrequency() const;

		__forceinline    std::function<double(double)>  get_sinusoid() const;

		__forceinline    std::size_t                             get_samples() const;

		__forceinline    JonesVector                             polarization() const;

		__forceinline    double                                  einit_time() const;

		__forceinline    double                                   einterval() const;

		LinearChirpSignal &                                      operator=(_In_ const LinearChirpSignal &);

	    LinearChirpSignal &                                      operator=(_In_ LinearChirpSignal &&);

		friend	std::ostream &                                       operator<<(_In_ std::ostream &, _In_ const LinearChirpSignal &);

		void                                                      save_to_file(const char *);

#if defined  MATHEMATICA_VISUALIZE
	_Maybe_raises_SEH_exception_	virtual      void                                                      save_to_file(_In_z_ const char*, _In_z_ const char*, _In_z_ const char*);
#endif

		const static double TWO_PI;
#if defined _DEBUG
		virtual      void                                        debug_print() const  override;
#endif

		/*
		@Brief: Applies variadic template functor to this LinearChirpSignal vectors.
		*/
		_Raises_SEH_exception_   template<typename F, typename... _Fx>  __forceinline  void  apply(_In_ F, _In_ _Fx&&... );

		/*
		@Brief: Applies 3 variadic template functors to  LinearChirpSignal vectors.
		*/
		_Raises_SEH_exception_   template<typename F1, typename F2, typename F3, typename... _Ty> __forceinline void apply(_In_ F1, _In_ F2, _In_ F3, _In_ _Ty&&...);


		/*
		@Brief: Class implementation of inherited pure virtual function Waveform::quadrature_components_extraction.
		*/
_Raises_SEH_exception_		virtual      void                                        quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &, _In_ const int) override;
/*
@Brief: Class implementation of inherited pure virtual function Waveform::complex_envelope.
*/
_Raises_SEH_exception_		virtual      void                                        complex_envelope(_In_ std::vector<std::pair<double, double>> &, _Out_ std::vector<double> &) override;
/*
@Brief: Class implementation of inherited pure virtual function Waveform::analytic_signal.
*/
_Raises_SEH_exception_		virtual      void                                        analytic_signal(_In_ const std::vector<double> &, _In_ const int) override;
/*
@Brief: Class implementation pf inherited pure virtual function Waveform::instantaneous_frequency.
*/
_Maybe_raises_SEH_exception_		virtual      void                                        instantaneous_frequency(_Inout_ std::vector<double> &) override;

                                    virtual            std::vector<std::pair<double, double>>     pulse_samples() const override;

									virtual            std::vector<double>                        pulse_phase() const override;

									virtual            std::size_t                                pulse_samples_count() const override;


		virtual     void    amplitude_modulation(const double, const double, const double) override;

		virtual     void    frequency_modulation(double, size_t) override;

		virtual     void    phase_modulation(const double, const double, const double, std::function<double(double, double)>&) override;

	protected:

	_Field_size_(m_samples)	std::vector<std::pair<double, double>> m_chirp; // Linear Chirp signal s(t).

	_Field_size_(m_samples)	std::vector<double> m_envelope; // Amplitude envelope r(t).

	_Field_size_(m_samples)	std::vector<double> m_phase; // phase function ph(t).

		double  m_sfrequency; //starting frequency

		double  m_efrequency; // final frequency

		double  m_envfrequency; // envelope frequency, m_envfrequency < m_efrequency

		double  m_chirp_rate; // chirp rate

		double  m_init_phase; // initial phase

		std::function<double(double)> m_sinusoid; // carrier sinusoid.

		std::size_t  m_samples; // number of samples.

		double  m_itime; // initial time point.

		double  m_interval; // time point increment interval.

		double  m_einterval; // modulating envelope increment rate;

		double  m_einit_time; // modulating envelope starting time point.

		JonesVector m_polarization; // Polarization vector.

		double  compute_chirp_rate() const; // compute chirp rate K.

	

	_Raises_SEH_exception_  void  initialize(_In_  struct LinChirpParams const&);

		void  initialize(_In_ const LinearChirpSignal &);


		void  initialize(_In_ LinearChirpSignal &&);

		

	};

	struct LinChirpParams
	{
		_In_  std::function<double(double)> sinusoid;
		_In_  std::function<double(double)> envelope;
		_In_  double  sfreq;
		_In_  double  efreq;
		_In_  double  envfreq;
		_In_  double  chirp_rate;
		_In_  double  init_phase;
		_In_  double  init_time;
		_In_  double  einit_time;
		_In_  double  interval;
		_In_  double  einterval;
		_In_  std::size_t  n_samples;
		_In_  int  n_threads;
	};

#include "LinearChirp.inl"
}
#endif  /*_LINEAR_CHIRP_H_*/