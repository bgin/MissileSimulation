#ifndef _SAWTOOTH_WAVE_H_
#define _SAWTOOT_WAVE_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Sawtooth signal class - declaration.
@author: Bernard Gingold
@version:  1.0  28/09/2015

*/

#include "WaveformInterface.h"
#include "../MathLib/MathConstants.h"
#include "LibExceptions.h"
#include "Polarization.h"

namespace   radiolocation
{

	class SawtoothSignal : public   Waveform
	{

	public:


		/*
		@brief Explicitly default Ctor.
		*/
		SawtoothSignal() = default;
		/*
		@Brief: "Main" class Constructor.
		*/
		

		_Raises_SEH_exception_  SawtoothSignal(_In_ struct SawtoothSignalParams const&);
		/*
		@Brief: Copy-Constructor.
		*/
		SawtoothSignal(_In_ SawtoothSignal const&);

		/*
		@Brief: Move-Constructor.
		*/
		SawtoothSignal(_In_ SawtoothSignal &&);

		/*
		@Brief: Class Destructor explicitly default.
		*/
		~SawtoothSignal()
		{

		}

		/*
		@Brief: Inline member accessor functions.
		*/

		/*
		@Brief: Returns Sawtooth Signal vector component.
		*/
		_Outptr_opt_result_buffer_(m_samples)	__forceinline  std::vector<std::pair<double, double>>  get_sawtooth() const;

		/*
		@Brief: Returns Sawtooth Signal phase.
		*/
		_Outptr_opt_result_buffer_(m_samples)	__forceinline   std::vector<double>                    get_phase() const;

		/*
		@Brief: Returns number of samples.
		*/
		__forceinline   std::size_t                            get_samples() const;

		/*
		@Brief: Returns Sawtooth amplitude (scalar value)
		*/
		__forceinline   double                                 get_amplitude() const;

		/*
		@Brief: Return Sawtooth initial time(t0).
		*/
		__forceinline   double                                 get_init_time() const;

		/*
		@Brief: Returns Sawtooth phase step increment phi(t).
		*/
		__forceinline   double                                 get_interval() const;

		/*
		@Brief: Returns Sawtooth frequency.
		*/
		__forceinline   double                                 get_frequency() const;
		/*
		@Brief: Returns C-style pointer to phase vector ie. to  m_phase[0].
		*/
		_Outptr_opt_result_buffer_(m_samples)	__forceinline   const double                           *get_phase_ptr() const;

		/*
		@Brief: Returns Polarization vector set to linear vertical polarization by default.
		*/
		__forceinline   JonesVector                           polarization() const;

		/*
		@Brief: Copy-Assignment operator=.
		*/
		SawtoothSignal&                                        operator=(_In_ SawtoothSignal const&);

		/*
		@Brief: Move-Assignment operator=.
		*/
		SawtoothSignal&                                        operator=(_In_ SawtoothSignal &&);

		/*
		@Brief: friend operator<<
		*/
		friend  std::ostream&                                  operator<<(_In_ std::ostream&, _In_ const SawtoothSignal &);

		/*
		@Brief: Member functions
		*/

		/*
		@Brief: Applies single functor to each of the vector components of SawtoothSignal object.
		Uses variadic templates and forwarding.Modifies *this in place.
		*/
	_Raises_SEH_exception_	template<typename _Fx, typename... _Ty> __forceinline  void  apply(_In_ _Fx, _In_ _Ty&&...);

	/*
	@Brief: Return approximately number of cycles
	*/
	double                               num_of_cycles() const;
		/*
		@Brief: Implementation of class inherited pure virtual functions.
		*/
#if defined _DEBUG

	/*
	@ Pure virtual function debug_print implementation
	*/
	virtual          void             debug_print() const override;
#endif 

#if defined MATHEMATICA_VISUALIZE
	/*
	@Brief: Writes content of SquareWaveSignal to file.
	*/
	_Raises_SEH_exception_  virtual  void        save_to_file(_In_z_ const char*, _In_z_ const char*) const;
#endif

	/*
	@Brief: Class implementation of inherited pure virtual function Waveform::quadrature_components_extraction.
	*/
	_Raises_SEH_exception_   virtual     void       quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &, _In_ const int) override;

	/*
	@Brief: Class implementation of inherited pure virtual function Waveform::complex_envelope.
	*/
	_Raises_SEH_exception_    virtual    void       complex_envelope(_In_ std::vector<std::pair<double, double>> &, _Out_ std::vector<double> &) override;

	/*
	@Brief: Class implementation of inherited pure virtual function Waveform::analytic_signal.
	*/
	_Raises_SEH_exception_    virtual    void       analytic_signal(_In_ const std::vector<double> &, _In_ const int) override;


	/*
	@Brief: Class implementation pf inherited pure virtual function Waveform::instantaneous_frequency.
	*/
	_Raises_SEH_exception_     virtual   void       instantaneous_frequency(_Inout_ std::vector<double> &) override;


	virtual     std::vector<std::pair<double, double>>    pulse_samples() const override;


	virtual     std::vector<double>                       pulse_phase() const override;


	virtual     std::size_t                               pulse_samples_count() const override;


	virtual     void    amplitude_modulation(const double, const double, const double) override;

	virtual     void    frequency_modulation(double, size_t) override;

	virtual     void    phase_modulation(const double, const double, const double, std::function<double(double, double)>&) override;
	
	protected:

		/*
		@Brief: Sawtooth Waveform Signal.
		*/
		_Field_size_(m_samples) std::vector<std::pair<double, double>> m_sawtooth;

		/*
		@Brief: Sawtooth Signal phase , phi(t)
		*/
		_Field_size_(m_samples) std::vector<double> m_phase;
			/*
			@Brief: Number of samples.
			*/
			std::size_t m_samples;
			/*
			@Brief: Sawtooth amplitude(scalar value).
			*/
			double m_amplitude;
			/*
			@Brief: Sawtooth start time of the signal.
			*/
			double m_init_time;
			/*
			@Brief: Sawtooth argument increment step.
			*/
			double m_interval;

			/*
			@Brief: Sawtooth frequency
			*/
			double m_frequency;

			/*
			@Brief: Plarization vector.
			*/

			JonesVector  m_polarization;

			/*
			@Brief: Creates Sawtooth Wave signal. Called from Constructor.
			*/
			

			_Raises_SEH_exception_ void   create_signal(_In_ struct SawtoothSignalParams const&);

			/*
			@Brief Copies content of const Sawtooth object, passed by reference. Called from the Copy-Constructor.
			*/
			void                          create_signal(_In_ SawtoothSignal const&);

			/*
			@Brief: Moves content of SawTooth object passed by value. Called from Move-Constructor.
			*/
			void                          create_signal(_In_ SawtoothSignal &&);

			static const double TWO_PI;
	};

	struct SawtoothSignalParams
	{
		_In_ double amplitude;
		_In_ double frequency;
		_In_ double init_time;
		_In_ double interval;
		_In_ std::size_t n_samples;
		_In_ std::size_t n_threads;
	};

#include "SawtoothWave.inl"
}
#endif /*_SAWTOOTH_WAVE_H_*/