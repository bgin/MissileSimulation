#ifndef _SIGNAL_TRAIN_H_
#define _SIGNAL_TRAIN_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pulse Train  class - definition
@aulthor: Bernard Gingold
@version:  1.0  08/10/2015

*/
#include <map>

#include "WaveformInterface.h"
#include "../MathLib/VectorF64AVX.h"
#include "Polarization.h"





	
	
	

		

		
		
		
		

		

		

		

		


		

	


        
	

		


    
		
	namespace radiolocation
	{



	

	
	
	


	 class PulseTrain
	{


	public:

	_Raises_SEH_exception_	PulseTrain(_In_ struct ArgumentPayload);

	_Raises_SEH_exception_  PulseTrain(_In_ struct ArgumentPayload, _In_ const double, _In_ const double);

		PulseTrain(_In_ std::size_t, _In_ std::string&, _In_ std::function<Waveform*()>);

		PulseTrain(_In_ std::size_t, _In_  std::string&, _In_ std::function<Waveform*()>, _In_ std::function<Waveform*()>);

		PulseTrain(_In_ PulseTrain const&);

		PulseTrain(_In_ PulseTrain &&);

		PulseTrain&             operator=(_In_ PulseTrain const&);

		PulseTrain&             operator=(_In_ PulseTrain &&);

		friend    std::ostream&    operator<<(_In_ std::ostream&, _In_  PulseTrain const&);

		~PulseTrain();

		__forceinline   std::map<std::string, std::vector<Waveform*>>  pulse_train() const;

		__forceinline   std::vector<Waveform*>  v() const;

		__forceinline   std::size_t             pulses() const;

		__forceinline   double                  time_delay() const;

		__forceinline   double                  duty_cycle() const;

		__forceinline   std::string             type() const;

		__forceinline   mathlib::VecF64AVX      propagation_vector() const;

	


		template<typename T> static __forceinline void    delete_signal_pointers(_In_z_ T const*);

		template<typename _Fx> static std::map<std::string, std::vector<Waveform*>> pulse_train_factory(_In_ _Fx, _In_ std::string&, _In_ std::size_t);

		
		
	private:

		std::size_t m_pulses;

	_Field_size_(m_pulses)	std::map<std::string, std::vector<Waveform*>> m_pulse_train;

	_Field_size_(m_pulses)	std::vector<Waveform*> m_v;

		double m_time_delay;

		double m_duty_cycle;

		mathlib::VecF64AVX m_propagation_vector;

		std::string m_type;

		//std::vector<JonesVector> m_oPulsePolarizationVector;
		//radiolocation::JonesVector m_oPolarVector;
		
		
	};

	 
	  class PulseTrainS
	 {

	 public:

		 

		
		 _Raises_SEH_exception_  PulseTrainS(_In_ struct ArgumentPayload const&);
		
		 _Raises_SEH_exception_  PulseTrainS(_In_ struct ArgumentPayload const&, _In_ const double, _In_ const double);

		 PulseTrainS(_In_ PulseTrainS const&);

		 PulseTrainS(_In_ PulseTrainS &&);

		 ~PulseTrainS();
		

		

		 PulseTrainS &           operator=(_In_  PulseTrainS const&);

		 PulseTrainS &           operator=(_In_  PulseTrainS &&);

		 friend    std::ostream &        operator<<(_In_ std::ostream&, _In_ PulseTrainS const&);

		 Waveform*            operator[](_In_ const std::size_t);

		 const  Waveform*     operator[](_In_ const std::size_t) const;
		
		

#if defined _DEBUG
		 void                     debug_print() const;
#endif

		 template<typename _Fx> static  std::map<std::string, std::vector<Waveform*>>  PulseTrainFactory(_In_ _Fx, _In_ std::string const&,
			 _In_ const std::size_t);
		
		

		__forceinline  _Field_size_(m_uiNumOfPulses) std::map<std::string, std::vector<Waveform*>>  PulseTrain() const;

		__forceinline _Field_size_(m_uiNumOfPulses) std::vector<Waveform*> Pulses() const;

		__forceinline                               std::size_t  NumOfPulses() const;

		__forceinline                               double       TimeDelay() const;

		__forceinline                               double       DutyCycle() const;

		__forceinline                               std::size_t  PulseIndexI() const;

		__forceinline                               std::size_t  PulseIndexJ() const;

		__forceinline                               mathlib::VecF64AVX  PropagationVector() const;

		__forceinline                               radiolocation::JonesVector   *PulseTrainPolarization() const;

		__forceinline                               std::string               PulseType() const;


	 private:

		 std::size_t m_uiNumOfPulses;

		 _Field_size_(m_uiNumOfPulses) std::map < std::string, std::vector<Waveform*>> m_oPulseTrain;

		 _Field_size_(m_uiNumOfPulses) std::vector<Waveform*> m_oPulses;

		 double  m_dTimeDelay;

		 double  m_dDutyCycle;

		 std::size_t  m_uiPulseIndexI;

		 std::size_t  m_uiPulseIndexJ;

		 mathlib::VecF64AVX m_oPropagationVector;

		
		 JonesVector*  m_oPulseTrainPolarization;
		 std::string  m_oPulseType;
	 }; 
	 
	 


	 /*
	 @Brief: POD structure for holding various Signals parameters.
	 */
	 struct ArgumentPayload
	 {
		
		 _In_ double varg1; // Propagation vector argument x.
		 _In_ double varg2; // Propagation vector argument y.
		 _In_ double varg3; // Propagation vector argument z.
		 _In_ std::size_t PulseIndexI;// loop start index i.
		 _In_ std::size_t PulseIndexJ;// loop start index j.
		
		 _In_ std::size_t arg12; // number of train pulses.
		 _In_ std::function<double(double)>  wave_generator1;
		 _In_ std::function<double(double)>  wave_generator2;
		 _In_ std::function<radiolocation::Waveform*()> signal1; // polymorphic Signal pulse
		 _In_ std::function<radiolocation::Waveform*()> signal2; // polymorphic Signal time delay between subsequent pulsese
		// _In_ std::function<boost::scoped_ptr<radiolocation::Waveform>()> signal3; // safe version of signal1
		// _In_ std::function<boost::scoped_ptr<radiolocation::Waveform>()> signal4; // safe version of signal2
		 _In_ std::string arg13;// pulse type
	 };

#include "SignalTrain.inl"
}

#endif _SIGNAL_TRAIN_H_