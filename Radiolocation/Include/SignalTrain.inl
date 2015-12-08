
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pulse Train and PulseTrainS classes - inline functions implementation.
@author: Bernard Gingold
@version:  1.0  08/10/2015

*/





__forceinline    std::map<std::string, std::vector<radiolocation::Waveform*>>  radiolocation::PulseTrain::pulse_train() const
{
	return this->m_pulse_train;
}

__forceinline    std::vector<radiolocation::Waveform*>  radiolocation::PulseTrain::v() const
{
	return this->m_v;
}

__forceinline    std::size_t                            radiolocation::PulseTrain::pulses() const
{
	return this->m_pulses;
}

__forceinline    double                                 radiolocation::PulseTrain::duty_cycle() const
{
	return this->m_duty_cycle;
}

__forceinline    double                                 radiolocation::PulseTrain::time_delay() const
{
	return this->m_time_delay;
}

__forceinline    std::string                            radiolocation::PulseTrain::type() const
{
	return this->m_type;
}

__forceinline    mathlib::VecF64AVX                     radiolocation::PulseTrain::propagation_vector() const
{
	return this->m_propagation_vector;
}



template<typename T> __forceinline   void               radiolocation::PulseTrain::delete_signal_pointers(T const* ptr)
{
	delete ptr;
}

/*
@Brief: Static pulse train "factory".
*/
template<typename _Fx> std::map<std::string, std::vector<radiolocation::Waveform*>> radiolocation::PulseTrain::pulse_train_factory(_In_ _Fx fx, _In_
	std::string& type, _In_ std::size_t n_pulses)
{
	_ASSERT(2 < n_pulses);
	std::map<std::string, std::vector<Waveform*>> m;
	std::vector<Waveform*> v;
	for (std::size_t i{ 0 }; i != n_pulses; ++i)
		v.push_back(fx());
	m.insert(std::make_pair(type, v));
	return m;
	

}


__forceinline      std::map<std::string, std::vector<radiolocation::Waveform*>>  radiolocation::PulseTrainS::PulseTrain() const
{
	return this->m_oPulseTrain;
}

__forceinline      std::vector<radiolocation::Waveform*>   radiolocation::PulseTrainS::Pulses() const
{
	return this->m_oPulses;
}

__forceinline      std::size_t           radiolocation::PulseTrainS::NumOfPulses() const
{
	return this->m_uiNumOfPulses;
}

__forceinline      double                radiolocation::PulseTrainS::DutyCycle() const
{
	return this->m_dDutyCycle;
}

__forceinline       double               radiolocation::PulseTrainS::TimeDelay() const
{
	return this->m_dTimeDelay;
}

__forceinline       std::size_t          radiolocation::PulseTrainS::PulseIndexI() const
{
	return this->m_uiPulseIndexI;
}

__forceinline       std::size_t           radiolocation::PulseTrainS::PulseIndexJ() const
{
	return this->m_uiPulseIndexJ;
}

__forceinline       mathlib::VecF64AVX       radiolocation::PulseTrainS::PropagationVector() const
{
	return this->m_oPropagationVector;
}

__forceinline       radiolocation::JonesVector       *radiolocation::PulseTrainS::PulseTrainPolarization() const
{
	return this->m_oPulseTrainPolarization;
}

__forceinline       std::string         radiolocation::PulseTrainS::PulseType() const
{
	return this->m_oPulseType;
}

template<typename _Fx>   std::map<std::string, std::vector<radiolocation::Waveform*>> radiolocation::PulseTrainS::PulseTrainFactory(_In_ _Fx fx, _In_
	std::string const& type, _In_ const std::size_t num_pulses)
{
	BOOST_ASSERT(2 < num_pulses);
	std::map<std::string, std::vector<radiolocation::Waveform*>> pulse_train;
	std::vector<radiolocation::Waveform*> vpulses;
	for (std::size_t i{ 0 }; i != num_pulses; ++i)
		vpulses.push_back(fx());
	pulse_train.insert(std::make_pair( type, vpulses));
	return pulse_train;
	
}