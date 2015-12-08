/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pulse Train  class - implementation.
@author: Bernard Gingold
@version:  1.0  08/10/2015

*/

#include "SignalTrain.h"
#include "LibExceptions.h"





radiolocation::PulseTrain::PulseTrain(std::size_t n_pulses, std::string& type, std::function<Waveform*()> signal) : 
m_pulses(n_pulses),
m_type(type),
m_duty_cycle(0.0),
m_time_delay(0.0)
{
	_ASSERT(2 < n_pulses);
	for (std::size_t i{ 0 }; i != this->m_pulses; ++i)
		this->m_v.push_back(signal());
	this->m_pulse_train.insert(std::make_pair(this->m_type, this->m_v));
}

_Raises_SEH_exception_ radiolocation::PulseTrain::PulseTrain(_In_ struct ArgumentPayload ap) :
m_pulses{ ap.arg12 },
m_type{ ap.arg13 },
m_duty_cycle{ 0.0 },
m_time_delay{ 0.0 },
m_propagation_vector{ ap.varg1, ap.varg2, ap.varg3, 0.0 }
{
#if defined _DEBUG
	_ASSERTE(2 < ap.arg12);
#else
	if (2 > ap.arg12)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("PulseTrain::PulseTrain: Failed") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	for (std::size_t i{ 0 }; i != this->m_pulses; ++i)
		this->m_v.push_back(ap.signal1());
	this->m_pulse_train.insert(std::make_pair(this->m_type, this->m_v));
}

_Raises_SEH_exception_ radiolocation::PulseTrain::PulseTrain(_In_ struct ArgumentPayload ap, _In_ const double time_delay, _In_ const double duty_cycle) :
m_pulses(ap.arg12),
m_type(ap.arg13), 
m_duty_cycle(duty_cycle),
m_time_delay(time_delay),
m_propagation_vector(ap.varg1, ap.varg2, ap.varg3, 0.0)
{
#if defined _DEBUG
	_ASSERTE(2 < ap.arg12);
#else
	if (2 > ap.arg12)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("PulseTrain::PulseTrain: Failed") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	for (std::size_t i{ 0 }; i != this->m_pulses; i += 2)
		this->m_v.push_back(ap.signal1());

	for (std::size_t j{ 1 }; j != this->m_pulses; j += 2)
		this->m_v.push_back(ap.signal2());
	
	this->m_pulse_train.insert(std::make_pair(this->m_type, this->m_v));
}

radiolocation::PulseTrain::PulseTrain(_In_ PulseTrain const& rhs) : 
m_pulses(rhs.m_pulses),
m_type(rhs.m_type), 
m_duty_cycle(rhs.m_duty_cycle),
m_propagation_vector(rhs.m_propagation_vector),
m_v(rhs.m_v),
m_pulse_train(rhs.m_pulse_train)
{
	
}

radiolocation::PulseTrain::~PulseTrain()
{
	
	for (std::size_t i{ 0 }; i != this->m_pulses; ++i)
	if (this->m_v.operator[](i))
	{
		delete this->m_v.operator[](i);
		this->m_v.operator[](i) = nullptr;
		std::cout << "PulseTrain::~PulseTrain() - Executed\n";
	}
}

radiolocation::PulseTrain::PulseTrain(_In_ PulseTrain &&rhs) : 
m_pulses(std::move(rhs.m_pulses)), 
m_type(std::move(rhs.m_type)),
m_duty_cycle(std::move(rhs.m_duty_cycle)),
m_propagation_vector(std::move(rhs.m_propagation_vector)), 
m_v(std::move(rhs.m_v)), 
m_pulse_train(std::move(rhs.m_pulse_train))
{

}

radiolocation::PulseTrain&        radiolocation::PulseTrain::operator=(_In_ PulseTrain const& rhs)
{
	if (this == &rhs) return *this;

	this->m_duty_cycle = rhs.m_duty_cycle;
	this->m_propagation_vector = rhs.m_propagation_vector;
	this->m_pulses = rhs.m_pulses;
	this->m_time_delay = rhs.m_time_delay;
	this->m_type = rhs.m_type;
	this->m_v = rhs.m_v;
	this->m_pulse_train.operator=( rhs.m_pulse_train);
	return *this;
}

radiolocation::PulseTrain&        radiolocation::PulseTrain::operator=(_In_ PulseTrain &&rhs)
{
	if (this == &rhs) return *this;

	this->m_duty_cycle = std::move(rhs.m_duty_cycle);
	this->m_pulses = std::move(rhs.m_pulses);
	this->m_time_delay = std::move(rhs.m_time_delay);
	this->m_type = std::move(rhs.m_type);
	this->m_v = std::move(rhs.m_v);
	this->m_propagation_vector = std::move(rhs.m_propagation_vector);
	this->m_pulse_train = std::move(rhs.m_pulse_train);
	return *this;
}


std::ostream&                    radiolocation::operator<<(_In_ std::ostream& os, _In_ PulseTrain const& pulse_train)
{
	for (std::size_t i{ 0 }; i != pulse_train.m_pulses; ++i)
	{
		os << "Pulse type: " << pulse_train.m_type.c_str() << "Pulse position: " << i << std::endl;
		for (std::size_t j{ 0 }; j !=  pulse_train.pulse_train()[pulse_train.m_type].operator[](i)->pulse_samples_count(); ++j)
		{
			os << "s(t):" << pulse_train.pulse_train()[pulse_train.m_type].operator[](i)->pulse_samples().operator[](j).second <<
				"t:" << pulse_train.pulse_train()[pulse_train.m_type].operator[](i)->pulse_samples().operator[](j).first <<
				"phi(t): " << pulse_train.pulse_train()[pulse_train.m_type].operator[](i)->pulse_phase().operator[](j) << std::endl;
		}
	}
	return os;
}



/*
@brief PulseTrainS implementation
*/


_Raises_SEH_exception_   radiolocation::PulseTrainS::PulseTrainS(_In_ struct ArgumentPayload const& p) :
m_dDutyCycle{ 0.0 },
m_dTimeDelay{ 0.0 },
m_oPropagationVector{ 0.0, p.varg3, p.varg2, p.varg1 },
m_uiNumOfPulses{ p.arg12 },
m_oPulseType{ p.arg13 },
m_oPulseTrainPolarization{ new radiolocation::JonesVector[p.arg12] },
m_uiPulseIndexI{ 0 },
m_uiPulseIndexJ{0}
{
#if defined _DEBUG
	_ASSERTE(2 < this->m_uiNumOfPulses);
#else
	if (2 > this->m_uiNumOfPulses)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("PulseTrainS::PulseTrainS: Invalid number of pulses") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif

	for (std::size_t i{ 0 }; i != this->m_uiNumOfPulses; ++i)
		this->m_oPulseTrainPolarization[i] = radiolocation::JonesVector(std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 1.0));
	for (std::size_t i{ this->m_uiPulseIndexI }; i != this->m_uiNumOfPulses; ++i)
		this->m_oPulses.push_back(p.signal1());
	this->m_oPulseTrain.insert(std::make_pair(this->m_oPulseType, this->m_oPulses));
}

_Raises_SEH_exception_   radiolocation::PulseTrainS::PulseTrainS(_In_ struct ArgumentPayload const& p, _In_ const double DutyCycle, _In_ const double TimeDelay) :
m_dDutyCycle{ DutyCycle },
m_dTimeDelay{ TimeDelay },
m_oPropagationVector{ 0.0, p.varg3, p.varg2, p.varg1 },
m_uiNumOfPulses{ p.arg12 },
m_oPulseType{ p.arg13 },
m_oPulseTrainPolarization{ new radiolocation::JonesVector[p.arg12] },
m_uiPulseIndexI{ p.PulseIndexI },
m_uiPulseIndexJ{ p.PulseIndexJ }
{
#if defined _DEBUG
	_ASSERTE(2 < this->m_uiNumOfPulses);
#else
	if (2 > this->m_uiNumOfPulses)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("PulseTrainS::PulseTrainS: Invalid number of pulses") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	for (std::size_t i{ 0 }; i != this->m_uiNumOfPulses; ++i)
		this->m_oPulseTrainPolarization[i] = radiolocation::JonesVector(std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 1.0));
	//even index
	for (std::size_t i{ this->m_uiPulseIndexI }; i != this->m_uiNumOfPulses; i += 2)
		this->m_oPulses.push_back(p.signal1());
	//odd index
	for (std::size_t j{ this->m_uiPulseIndexJ }; j != this->m_uiNumOfPulses; j += 2)
		this->m_oPulses.push_back(p.signal2());
	this->m_oPulseTrain.insert(std::make_pair(this->m_oPulseType, this->m_oPulses));
}

radiolocation::PulseTrainS::PulseTrainS(_In_ PulseTrainS const& other) :
m_dDutyCycle{ other.m_dDutyCycle },
m_dTimeDelay{ other.m_dTimeDelay },
m_oPropagationVector{ other.m_oPropagationVector },
m_oPulseTrainPolarization{ new radiolocation::JonesVector[other.m_uiNumOfPulses] },
m_oPulses{ other.m_oPulses },
m_oPulseTrain{ other.m_oPulseTrain },
m_oPulseType{other.m_oPulseType},
m_uiNumOfPulses{ other.m_uiNumOfPulses },
m_uiPulseIndexI{ other.m_uiPulseIndexI },
m_uiPulseIndexJ{ other.m_uiPulseIndexJ }
{
	std::copy(other.m_oPulseTrainPolarization, other.m_oPulseTrainPolarization + other.m_uiNumOfPulses, this->m_oPulseTrainPolarization);
}

radiolocation::PulseTrainS::PulseTrainS(_In_ PulseTrainS &&other) :
m_dDutyCycle{ std::move(other.m_dDutyCycle) },
m_dTimeDelay{ std::move(other.m_dTimeDelay) },
m_oPropagationVector{ std::move(other.m_oPropagationVector) },
m_oPulseTrainPolarization{ new radiolocation::JonesVector[std::move(other.m_uiNumOfPulses)] },
m_oPulses{ std::move(other.m_oPulses) },
m_oPulseTrain{ std::move(other.m_oPulseTrain) },
m_oPulseType{ std::move(other.m_oPulseType) },
m_uiNumOfPulses{ std::move(other.m_uiNumOfPulses) },
m_uiPulseIndexI{ std::move(other.m_uiPulseIndexI) },
m_uiPulseIndexJ{ std::move(other.m_uiPulseIndexJ) }
{
	std::copy(other.m_oPulseTrainPolarization, other.m_oPulseTrainPolarization + other.m_uiNumOfPulses, this->m_oPulseTrainPolarization);
}

radiolocation::PulseTrainS::~PulseTrainS()
{
	for (std::size_t i{ this->m_uiPulseIndexI }; i != this->m_uiNumOfPulses; ++i)
	if (this->m_oPulses.operator[](i))
	{
		delete this->m_oPulses.operator[](i);
		this->m_oPulses.operator[](i) = nullptr;
		
	}
	if (this->m_oPulseTrainPolarization)
	{
		delete[] this->m_oPulseTrainPolarization;
		this->m_oPulseTrainPolarization = nullptr;
	}
}
		
	


radiolocation::PulseTrainS &             radiolocation::PulseTrainS::operator=(_In_ PulseTrainS const& other)
{
	if (this == &other) return *this;

	BOOST_ASSERT(this->m_uiNumOfPulses == other.m_uiNumOfPulses);
	this->m_dDutyCycle = other.m_dDutyCycle;
	this->m_dTimeDelay = other.m_dTimeDelay;
	this->m_oPropagationVector.operator=(other.m_oPropagationVector);
	
	this->m_oPulses.operator=(other.m_oPulses);
	this->m_oPulseTrain.operator=(other.m_oPulseTrain);
	this->m_oPulseType.operator=(other.m_oPulseType);
	this->m_uiNumOfPulses = other.m_uiNumOfPulses;
	this->m_uiPulseIndexI = other.m_uiPulseIndexI;
	this->m_uiPulseIndexJ = other.m_uiPulseIndexJ;
	std::copy(other.m_oPulseTrainPolarization, other.m_oPulseTrainPolarization + other.m_uiNumOfPulses, this->m_oPulseTrainPolarization);
	return *this;
}

radiolocation::PulseTrainS &             radiolocation::PulseTrainS::operator=(_In_ PulseTrainS &&other)
{
	if (this == &other) return *this;

	BOOST_ASSERT(this->m_uiNumOfPulses == other.m_uiNumOfPulses);
	this->m_dDutyCycle = std::move(other.m_dDutyCycle);
	this->m_dTimeDelay = std::move(other.m_dTimeDelay);
	this->m_oPropagationVector.operator=(std::move(other.m_oPropagationVector));
	
	this->m_oPulses.operator=(std::move(other.m_oPulses));
	this->m_oPulseTrain.operator=(std::move(other.m_oPulseTrain));
	this->m_oPulseType.operator=(std::move(other.m_oPulseType));
	this->m_uiNumOfPulses = std::move(other.m_uiNumOfPulses);
	this->m_uiPulseIndexI = std::move(other.m_uiPulseIndexI);
	this->m_uiPulseIndexJ = std::move(other.m_uiPulseIndexJ);
	std::move(other.m_oPulseTrainPolarization, other.m_oPulseTrainPolarization + other.m_uiNumOfPulses, this->m_oPulseTrainPolarization);
	return *this;
}

radiolocation::Waveform*           radiolocation::PulseTrainS::operator[](_In_ const std::size_t index)
{
	BOOST_ASSERT(index >= 0 && index <= this->m_uiNumOfPulses);
	return this->m_oPulses.operator[](index);
}


const   radiolocation::Waveform*           radiolocation::PulseTrainS::operator[](_In_ const std::size_t index) const
{
	BOOST_ASSERT(index >= 0 && index <= this->m_uiNumOfPulses);
	return this->m_oPulses.operator[](index);
}

std::ostream &                     radiolocation::operator<<(_In_ std::ostream &os, _In_ PulseTrainS const& rhs)
{
	os.scientific;
	std::setprecision(15);
	for (std::size_t i{ 0 }; i != rhs.m_uiNumOfPulses; ++i)
	{
		os << "PulseType:" << rhs.m_oPulseType.c_str() << "at index:" << i << std::endl;
		for (std::size_t i{ 0 }; i != rhs.PulseTrain()[rhs.m_oPulseType].operator[](i)->pulse_samples_count(); ++i)
		{
			os << "s(phi(t)):" << rhs.PulseTrain()[rhs.m_oPulseType].operator[](i)->pulse_samples().operator[](i).second <<
				"t:" << rhs.PulseTrain()[rhs.m_oPulseType].operator[](i)->pulse_samples().operator[](i).first <<
				"phi(t):" << rhs.PulseTrain()[rhs.m_oPulseType].operator[](i)->pulse_phase().operator[](i) << std::endl;
		}
	}
	return os;
}

#if defined  _DEBUG

void                  radiolocation::PulseTrainS::debug_print() const
{
	std::printf("PulseTrainS::debug_print\n");
	std::printf("&this->m_dDutyCycle=%p,this->m_dDutyCycle=%.9f\n", &this->m_dDutyCycle, this->m_dDutyCycle);
	std::printf("&this->m_dTimeDelay=%p, this->m_dTimeDelay=%.9f\n", &this->m_dTimeDelay, this->m_dTimeDelay);
	std::printf("&this->m_oPropagationVector=%p\n", &this->m_oPropagationVector);
	std::printf("&this->m_oPulseTrainPolarization=%p\n", &this->m_oPulseTrainPolarization);
	std::printf("&this->m_oPulses=%p\n", &this->m_oPulses);
	std::printf("&this->m_PulseType=%p,this->m_PulseType=%s\n", &this->m_oPulseType, this->m_oPulseType.c_str());
	std::printf("&this->m_oPulseTrain=%p\n", &this->m_oPulseTrain);
	std::printf("&this->m_oNumOfPulses=%p,this->m_oNumOfPulses=%u\n", &this->m_uiNumOfPulses, this->m_uiNumOfPulses);
	std::printf("&this->m_uiPulseIndexI=%p,this->m_uiPulseIndexI=%u\n", &this->m_uiPulseIndexI, this->m_uiPulseIndexI);
	std::printf("&this->m_uiPulseIndexJ=%p,this->m_uiPulseIndexJ=%u\n", &this->m_uiPulseIndexJ, this->m_uiPulseIndexJ);
	std::cout << *this << std::endl;
}
#endif
