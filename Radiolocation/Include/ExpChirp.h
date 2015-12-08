
#ifndef _EXP_CHIRP_H_
#define _EXP_CHIRP_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
   Exponential Frequency Modulation(Exponential Chirp) signal class.
@author: Bernard Gingold
@version:  1.0  15/09/2015

*/

#include "WaveformInterface.h"
#include "Polarization.h"
#include "../MathLib/MathConstants.h"
#include "LibExceptions.h"

namespace  radiolocation
{


	class ExpChirpSignal : public  Waveform
	{


	public:

		ExpChirpSignal() = default;

		/*
		@Brief: Class Constructor.
		*/
		

		ExpChirpSignal(_In_  struct ExpChirpParams const&);
		/*
		@Brief: Deep Copy-Constructor.
		*/
		ExpChirpSignal(_In_ const ExpChirpSignal &);

		/*
		@Brief: Move Constructor.
		*/
		ExpChirpSignal(_In_  ExpChirpSignal &&);

		/*
		@Brief: Class Destructor explicitly default
		*/
		~ExpChirpSignal() = default;

		/*
		@Brief: Getter member function returns m_chirp vector.
		*/
		__forceinline  std::vector<std::pair<double, double>>  get_chirp() const noexcept;

		/*
		@Brief: Getter member function returns m_envelope vector.
		*/
		__forceinline  std::vector<double>                     get_envelope() const;
		/*
		@Brief: Getter member function returns m_phase vector.
		*/
		__forceinline  std::vector<double>                     get_phase() const;
		/*
		@Brief: Getter member function returns m_sfrequency.
		*/
		__forceinline  double                                  get_sfrequency() const;

		__forceinline  double                                  get_efrequency() const;

		__forceinline  double                                  get_envfrequency() const;

		__forceinline  double                                  get_envinterval() const;

		__forceinline  double                                  get_interval() const;

		__forceinline  double                                  get_init_phase() const;

		__forceinline  double                                  get_chirp_rate() const;

		__forceinline  double                                  get_init_time() const;

		__forceinline  size_t                                  get_samples() const;

		__forceinline  std::function<double(double)>           get_sinusoid() const;

		__forceinline  JonesVector                             polarization() const;
		         
		/*
	 	@Brief: class member operator assignment.
		*/
		_Check_return_    _Raises_SEH_exception_     ExpChirpSignal &                                       operator=(_In_ const ExpChirpSignal &);

		/*
		@Brief: class member move assignment operator.
		*/
		_Check_return_   _Raises_SEH_exception_      ExpChirpSignal &                                       operator=(_In_ ExpChirpSignal &&);

				 /*
				 @Brief: friend operator ostream.
				 */
		  friend   std::ostream &                                       operator<<(_In_ std::ostream &,_In_ const ExpChirpSignal &);


		  /*
		  @Brief: Computes Chirp Signal so called chirp rate.
		  */
		  double                                       compute_chirp_rate() const noexcept;

#if defined  _DEBUG
		  /*
		  @Brief: pure virtual function which displays debug info about first class object.
		  */
		  virtual       void                          debug_print() const override;
#endif

#if defined MATHEMATICA_VISUALIZE

		virtual   void          save_to_file(_In_z_ const char*,_In_z_ const char*, _In_z_ const char*);
#endif

		  /*
		  @Brief: Applies single functor to each of the vector components of ExpChirpSignal object.
		          Uses variadic templates and forwarding.Modifies *this in place.
		  */
		  _Raises_SEH_exception_	  template<typename F, typename ..._Fx> __forceinline  void  apply(_In_ F, _In_ _Fx&& ...);

		  
		  /*
		  @Brief: Applies three functors to each of the vector components of ExpChirpSignal object.
		           Uses variadic templates and forwarding. Modifies *this in place.
		  */
		  _Raises_SEH_exception_      template<typename F1, typename F2, typename F3, typename ..._Ty> __forceinline  void apply(_In_ F1, _In_ F2, _In_ F3, _In_ _Ty&& ...);

		  /*
		  @Brief: Implementation of class inherited pure virtual functions.
		  */

		  /*
		  @Brief: Class implementation of inherited pure virtual function Waveform::quadrature_components_extraction.
		  */
	_Raises_SEH_exception_	  virtual       void                           quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &, _In_ const int) override;
	/*
	@Brief: Class implementation of inherited pure virtual function Waveform::complex_envelope.
	*/
	_Raises_SEH_exception_    virtual       void                           complex_envelope(_In_ std::vector<std::pair<double, double>> &, _Out_ std::vector<double> &) override;
	/*
	@Brief: Class implementation of inherited pure virtual function Waveform::analytic_signal.
	*/
	_Raises_SEH_exception_    virtual       void                           analytic_signal(_In_ const std::vector<double> &, _In_ const int) override;
	/*
	@Brief: Class implementation pf inherited pure virtual function Waveform::instantaneous_frequency.
	*/
   _Raises_SEH_exception_	virtual       void                           instantaneous_frequency(_Inout_ std::vector<double> &) override;

   virtual std::vector<std::pair<double, double>>           pulse_samples() const override;


   virtual std::vector<double>                              pulse_phase() const override;


   virtual std::size_t                                      pulse_samples_count() const override;

   virtual     void    amplitude_modulation(const double, const double, const double) override;

   virtual     void    frequency_modulation(double, size_t) override;

   virtual     void    phase_modulation(const double, const double, const double, std::function<double(double, double)>&) override;


	protected:

		// Exponential Chirp Signal s(t).
	_Field_size_(m_samples)	std::vector<std::pair<double, double>> m_chirp; 

		// Amplitude envelope r(t).
	_Field_size_(m_samples)	std::vector<double> m_envelope; 

		// phase function ph(t).
	_Field_size_(m_samples)	std::vector<double> m_phase; 

		// Chirp start frequency (f0).
		double  m_sfrequency; 

		// Chirp end frequency (f1).
		double  m_efrequency; 

		// envelope frequency (fe) where f0 < fe < f1.
		double  m_envfrequency; 

		// envelope signal time step increment. Should be less than chirp signal time step increment.
		double  m_env_interval; 

		// Chirp signal time step increment.
		double  m_interval; 

		// Chirp signal initial phase in radians.
		double  m_init_phase; 

		// Chirp rate = [f1-f0/T].
		double  m_chirp_rate; 

		// Chirp signal starting time point.
		double  m_init_time; 

		// number of samples.
		size_t m_samples; 

		// envelope signal generating function.
		std::function<double(double)> m_sinusoid;  

		// Polarization vector.
		JonesVector  m_polarization;

		// static const TWO_PI
		static const double TWO_PI;
		/*
		@Brief Creates Exponential Chirp Signal object. This function is called from class Constructor.
		*/
	

	_Raises_SEH_exception_  void    create_signal(_In_  struct ExpChirpParams const&);

		/*
		@Brief Deep copy of ExpChirpSignal. Called from Copy-Constructor.
		*/
		void    create_signal(_In_ const ExpChirpSignal &);
		/*
		@Brief: Moves content from rhs to *this. Called from Move Constructor.
		*/
		void    create_signal(_In_ ExpChirpSignal &&);

	};

	struct  ExpChirpParams
	{
		_In_  std::function<double(double)> sinusoid; //phase waveform generating function.
		_In_  std::function<double(double)> envelope; // envelope waveform generating function.
		_In_  double sfreq;
		_In_  double efreq;
		_In_  double  envfreq;
		_In_  double envinterval;
		_In_  double interval;
		_In_  double init_phase;
		_In_  double chirp_rate;
		_In_  double init_time;
		_In_  std::size_t n_samples;
		_In_  int  n_threads;
	};


#include "ExpChirp.inl"
}
#endif /*_EXP_CHIRP_H_*/