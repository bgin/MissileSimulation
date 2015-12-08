/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Sawtooth signal class - inline functions implementation.
@author: Bernard Gingold
@version:  1.0  28/09/2015

*/

/*
Brief: SawtoothEave member getter function which returns class variable m_sawtooth.
Resulting Sawtooth Wave signal.
@Params: None
@Returns: this->m_sawtooth member variable.
@throws: Nothing
*/
_Outptr_opt_result_buffer_(m_samples)  __forceinline   std::vector<std::pair<double, double>>  radiolocation::SawtoothSignal::get_sawtooth() const
{
	return this->m_sawtooth;
}

/*
Brief: Sawtooth member getter function which returns class variable m_phase.
phase argument.
@Params: None
@Returns: this->m_phase member variable.
@throws: Nothing
*/
_Outptr_opt_result_buffer_(m_samples) __forceinline    std::vector<double>                     radiolocation::SawtoothSignal::get_phase() const
{
	return this->m_phase;
}

/*
Brief: Sawtooth member getter function which returns class variable m_samples.
Number of waveform samples.
@Params: None
@Returns: this->m_samples member variable.
@throws: Nothing
*/
__forceinline      std::size_t         radiolocation::SawtoothSignal::get_samples() const
{
	return this->m_samples;
}

/*
Brief: Sawtooth member getter function which returns class variable m_amplitude.
Scalar value of amplitude.
@Params: None
@Returns: this->m_amplitude member variable.
@throws: Nothing
*/
__forceinline      double              radiolocation::SawtoothSignal::get_amplitude() const
{
	return this->m_amplitude;
}

/*
Brief: Sawtooth member getter function which returns class variable m_init_time.
initial time point of SqureWave.
@Params: None
@Returns: this->m_init_time member variable.
@throws: Nothing
*/
__forceinline    double                 radiolocation::SawtoothSignal::get_init_time() const
{
	return this->m_init_time;
}

/*
Brief: Sawtooth member getter function which returns class variable m_interval.
initial time point increment
@Params: None
@Returns: this->m_interval member variable.
@throws: Nothing
*/
__forceinline    double                  radiolocation::SawtoothSignal::get_interval() const
{
	return this->m_interval;
}

/*
Brief: Sawtooth member getter function which returns C-style pointer to m_phase[0].
Assume double* C_ptr size == this->m_samples.
@Params: None
@Returns: double* C_ptr variable.
@throws: Nothing
*/
_Outptr_opt_result_buffer_(m_samples) __forceinline  const double    *radiolocation::SawtoothSignal::get_phase_ptr() const
{
	const double* rptr = &this->m_phase[0];
	return rptr;
}

/*
Brief: Sawtooth member getter function which returns class variable m_frequency.
Sawtooth frequency ie. not real signal frequency.
@Params: None
@Returns: this->m_frequency member variable.
@throws: Nothing
*/
__forceinline      double          radiolocation::SawtoothSignal::get_frequency() const
{
	return this->m_frequency;
}

/*
@Brief:  Polarization vector set to fixed veritcal linear polarization
*/
__forceinline      JonesVector     radiolocation::SawtoothSignal::polarization() const
{
	return this->m_polarization;
}

/*
Brief: Applies functor to each of the vector components of Sawtooth Signal object.
Uses variadic templates.Modifies *this in place.
@Params: lambda functor _Fx and variadic templated argument _Ty.
@Returns: Nothing
@throws: BOOST_THROW_EXCEPTION(empty_vector()) when object vectors are empty.
*/
_Raises_SEH_exception_ template<typename _Fx, typename... _Ty> __forceinline  void  radiolocation::SawtoothSignal::apply(_In_ _Fx fx, _In_ _Ty&&... ty)
{
	if (!(this->m_sawtooth.empty()) && !(this->m_phase.empty()))
	{
		for (std::size_t i{ 0 }; i != this->m_samples; ++i)
		{
			this->m_sawtooth.operator[](i) = fx(std::forward<_Ty>(ty)...);
			this->m_phase.operator[](i) = fx(std::forward<_Ty>(ty)...);
		}
	}
	else throw std::runtime_error("Fatal Error in SawtoothSignal::apply: Empty vector(s) \n");
}