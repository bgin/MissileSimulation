#ifndef _SAWTOOTH_MODULATED_H_
#define _SAWTOOTH_MODULATED_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Modulated Sawtooth signal class - declaration.
@author: Bernard Gingold
@version:  1.0  29/09/2015

*/

#include "WaveformInterface.h"
#include "../MathLib/MathConstants.h"
#include "LibExceptions.h"
#include "Polarization.h"

namespace  radiolocation
{


	class SawtoothMSignal : public  Waveform
	{


	public:

		
		/*
		@Brief: "Main" class Constructor.
		*/
		SawtoothMSignal() = default;

		_Raises_SEH_exception_   SawtoothMSignal(_In_ struct SawtoothMSignalParams const&);

		/*
		@Brief: Copy-Constructor.
		*/
		SawtoothMSignal(_In_ SawtoothMSignal const&);

		/*
		@Brief: Move-Constructor.
		*/
		SawtoothMSignal(_In_ SawtoothMSignal &&);

		/*
		@brief Destructor.
		*/
		~SawtoothMSignal()
		{

		}

		/*
		@Brief: Copy-Assignment operator=
		*/
		SawtoothMSignal&            operator=(_In_ SawtoothMSignal const&);

		/*
		@Brief: Move-Assignment operator=
		*/
		SawtoothMSignal&            operator=(_In_ SawtoothMSignal &&);

		/*
		@Brief: friend operator<<
		*/
		friend  std::ostream&       operator<<(_In_ std::ostream&, _In_ SawtoothMSignal const&);

		/*
		@Brief: Accessor inline functions.
		*/

		/*
		@Brief: Returns this->mSt member variable.
		*/
		_Outptr_opt_result_buffer_(m_samples)		__forceinline    std::vector<std::pair<double, double>>   get_St() const;

		
		/*
		@Brief: Returns this->m_rt member variable.
		*/
		_Outptr_opt_result_buffer_(m_samples) 		__forceinline    std::vector<double>                      get_rt() const;

		/*
		@Brief: Returns pointer const double* to this->m_rt[0]. Assumes length of rt == this->m_samples
		*/
		_Outptr_opt_result_buffer_(m_samples)       __forceinline    const double                            *get_prt() const;
		/*

		/*
		@Brief: Returns const double* pointer to this->m_phit[0].Assumes length of rt == this->m_samples
		*/
		_Outptr_opt_result_buffer_(m_samples)       __forceinline    const  double                           *get_pphit() const;

		/*
		@Brief:  Returns this->m_phit member variable.
		*/
		_Outptr_opt_result_buffer_(m_samples) 		__forceinline    std::vector<double>                      get_phit() const;

		/*
		@Brief: Returns this->m_samples member variable.
		*/
		__forceinline    std::size_t                              get_samples() const;

		/*
		@Brief: Returns  this->m_sinit_time member variable.
		*/
		__forceinline    double                                  get_sinit_time() const;

		/*
		@Brief: Returns   this->_rinit_time  member variable.
		*/
		__forceinline    double                                  get_rinit_time() const;

		/*
		@Brief: Returns   this->m_phinit_time member variable.
		*/
		__forceinline    double                                  get_phinit_time() const;

		/*
		@Brief: Returns   this->m_sinterval member variable.
		*/
		__forceinline    double                                  get_sinterval() const;

		/*
		@Brief: Returns   this->m_rinterval member variable.
		*/
		__forceinline    double                                  get_rinterval() const;

		/*
		@Brief: Returns   this->m_phinterval member variable.
		*/
		__forceinline    double                                  get_phinterval() const;

		/*
		@Brief: Returns   this->m_sfrequency member variable.
		*/
		__forceinline    double                                  get_sfrequency() const;

		/*
		@Brief: Returns   this->m_rfrequency member variable.
		*/
		__forceinline    double                                  get_rfrequency() const;

		/*
		@Brief: Returns   this->m_phfrequency member variable.
		*/
		__forceinline    double                                  get_phfrequency() const;

		/*
		@Brief: Returns   this->m_rwaveform member variable.
		*/
		__forceinline    std::function<double(double)>           get_rwaveform() const;

		/*
		@Brief: Returns   this->m_phwaveform member variable.
		*/
		__forceinline    std::function<double(double)>           get_phwaveform() const;

		
		/*
		@Brief:  Member functions
		*/

		/*
		@Brief: Returns number of cycles of S(t). 
		*/
		__forceinline    double                      St_cycles() const;

		/*
		@Brief: Returns number of cycles of r(t).
		*/
		__forceinline    double                      rt_cycles() const;

		/*
		@Brief: Returns number of cycles of phi(t).
		*/
		__forceinline    double                      phit_cycles() const;

		/*
		@Brief: Returns single pulse width of S(t).
		*/
		__forceinline    double                      St_pulse_width() const;

		/*
		@Brief: Returns single pulse width of r(t).
		*/
		__forceinline    double                      rt_pulse_width() const;

		/*
		@Brief: Returns single pulse width of phi(t).
		*/
		__forceinline    double                      phit_pulse_width() const;

		/*
		@Brief:  Returns polarization vector.
		*/
		__forceinline    JonesVector                 polarization() const;
		/*
		@Brief: Class inherited pure virtual functions.
		*/
#if defined _DEBUG
		virtual            void                      debug_print() const override;
#endif

#if defined  MATHEMATICA_VISUALIZE
		_Raises_SEH_exception_  virtual   void               save_to_file(_In_z_ const char*, _In_z_ const char*, _In_z_ const char*) const;
#endif

		/*
		@Brief: Class implementation of inherited pure virtual function Waveform::quadrature_components_extraction.
		*/
		_Raises_SEH_exception_    virtual           void       quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &, _In_ const int) override;

		/*
		@Brief: Class implementation of inherited pure virtual function Waveform::complex_envelope.
		*/
		_Raises_SEH_exception_    virtual    void       complex_envelope(_In_ std::vector<std::pair<double, double>> &, _Out_ std::vector<double> &) override;

		/*
		@Brief: Class implementation of inherited pure virtual function Waveform::complex_envelope.
		*/
		_Raises_SEH_exception_    virtual    void       analytic_signal(_In_ const std::vector<double> &, _In_ const int) override;


		/*
		@Brief: Class implementation pf inherited pure virtual function Waveform::instantaneous_frequency.
		*/
		_Raises_SEH_exception_     virtual   void       instantaneous_frequency(_Inout_ std::vector<double> &) override;


		virtual                    std::vector<std::pair<double, double>>      pulse_samples() const override;


		virtual                    std::vector<double>                         pulse_phase() const override;

		virtual                    std::size_t                                 pulse_samples_count() const override;


		/*
		 To be implemented later.
		*/
		virtual     void    amplitude_modulation(const double, const double, const double) override;

		virtual     void    frequency_modulation(double, size_t) override;

		virtual     void    phase_modulation(const double, const double, const double, std::function<double(double, double)>&) override;

	protected:

		/*
		@Brief:  Modulated Sawtooth Signal,ie. S(t) = r(t) * (t - floor(t + phi(t)))
		*/
		_Field_size_(m_samples) std::vector<std::pair<double, double>> m_St;

		/*
		@Brief: Amplitude "modulating" signal r(t).
		*/ 
		_Field_size_(m_samples) std::vector<double> m_rt;

		/*
		@Brief: Frequency "modulating" signal phi(t).
 		*/
		_Field_size_(m_samples) std::vector<double> m_phit;

		/*
		@Brief:  Number  of Sawtooth Signal samples
		*/
		std::size_t m_samples;

		/*
		@Brief: Sawtooth signal starting time point S(t0).
		*/
		double  m_sinit_time;

		/*
		@Brief:  r(t) signal starting time point r(t0)
		*/
		double  m_rinit_time;

		/*
		@Brief:  phi(t) signal starting time point phi(t0)
		*/
		double  m_phinit_time;

		/*
		@Brief: S(t) time step increment t0 += value
		*/
		double  m_sinterval;

		/*
		@Brief: r(t) time step increment t0 += value
		*/
		double  m_rinterval;

			/*
		@Brief: phi(t) time step increment t0 += value
		*/
		double  m_phinterval;

		/*
		@Brief: S(t) carrier frequency fc only ilustrative purpose.
		*/
		double m_sfrequency;

		/*
		@Brief: r(t) frequency fr < fc only ilustrative purpose.
		*/
		double  m_rfrequency;

		/*
		@Brief: phi(t) frequency fphi < fc only ilustrative purpose.
		*/
		double  m_phfrequency;

		/*
		@Brief: r(t) waveform generating function for example cos(t + phase).
		*/
		std::function<double(double)> m_rwaveform;

		/*
		@Brief: phi(t) waveform generating function for example exp(t/2)
		*/
		std::function<double(double)> m_phwaveform;

		/*
		@Brief: Polarization vector represented by object of type JonesVector.
		*/
		JonesVector m_polarization;

		/*
		@Brief: Value of 2Pi
		*/
		static const double  TWO_PI;

		/*
		@Brief: Modulated Sawtooth object creating function. Called from the class Constructor.
		*/
		

		_Raises_SEH_exception_      void                         create_signal(_In_ struct SawtoothMSignalParams const&);

		/*
		@Brief: Modulated Sawtooth object copy assignment function. Called from the Constructor.
		*/
		void                          create_signal(_In_ SawtoothMSignal const&);

		/*
		@Brief: Modulated Sawtooth object move assignment function. Called from the Constructor.
		*/
		void                          create_signal(_In_ SawtoothMSignal &&);

		/*
		@Brief: static private function for argument sanity check.
		*/
		static                double        StCycles(_In_ const std::size_t, _In_ const double);

		/*
		@Brief: static private function for argument sanity check.
		*/
		static                double        RtCycles(_In_ const std::size_t, _In_ const double);

		/*
		@Brief: static private function for argument sanity check.
		*/
		static                double        PhitCycles(_In_ const std::size_t, _In_ const double);
	};

	/*
	@Brief: Aggregated parameters structure for SawtoothModulatd Ctor.
	*/

	struct SawtoothMSignalParams
	{
		_In_  std::function<double(double)> rwaveform;
		_In_  std::function<double(double)> phiwaveform;
		_In_  double  sinit_time;
		_In_  double  rinit_time;
		_In_  double  phinit_time;
		_In_  double  sinterval;
		_In_  double  rinterval;
		_In_  double  phinterval;
		_In_  double  sfreq;
		_In_  double  rfreq;
		_In_  double  phfreq;
		_In_  std::size_t  n_samples;
		_In_  int  n_threads;
	};


#include "SawtoothModulated.inl"
}


#endif /*_SAWTOOTH_MODULATED_H_*/