
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Square Wave signal class.
@author: Bernard Gingold
@version:  1.0  19/09/2015

*/

/*
Brief: SquareWave member getter function which returns class variable m_squarewave.
        Resulting Square Wave signal.
@Params: None
@Returns: this->m_squarewave member variable.
@throws: Nothing
*/
_Outptr_opt_result_buffer_(m_samples)  __forceinline      std::vector<std::pair<double, double>>   radiolocation::SquareWaveSignal::get_squarewave() const
{
	return this->m_squarewave;
}


/*
Brief: SquareWave member getter function which returns class variable m_phase.
       Sine phase argument.
@Params: None
@Returns: this->m_phase member variable.
@throws: Nothing
*/
_Outptr_opt_result_buffer_(m_samples)   __forceinline      std::vector<double>                      radiolocation::SquareWaveSignal::get_phase() const
{
	return this->m_phase;
}

/*
Brief: SquareWave member getter function which returns C-style pointer to m_phase[0].
 Assume double* C_ptr size == this->m_samples.
@Params: None
@Returns: double* C_ptr variable.
@throws: Nothing
*/
_Outptr_opt_result_buffer_(m_samples)    __forceinline    const  double                                  *radiolocation::SquareWaveSignal::get_phase_ptr() const
{
	// Assume size of C_ptr == this->m_samples.
	const double* C_ptr =  &this->m_phase[0];
	return C_ptr;
}

/*
Brief: SquareWave member getter function which returns class variable m_init_time.
       initial time point of sine wave.
@Params: None
@Returns: this->m_init_time member variable.
@throws: Nothing
*/
__forceinline           double                                   radiolocation::SquareWaveSignal::get_init_time() const
{
	return this->m_init_time;
}

/*
Brief: SquareWave member getter function which returns class variable m_interval.
initial time point increment
@Params: None
@Returns: this->m_interval member variable.
@throws: Nothing
*/
__forceinline           double                                   radiolocation::SquareWaveSignal::get_interval() const
{
	return this->m_interval;
}

/*
Brief: SquareWave member getter function which returns class variable m_amplitude.
       Scalar value of amplitude.
@Params: None
@Returns: this->m_amplitude member variable.
@throws: Nothing
*/
__forceinline           double                                   radiolocation::SquareWaveSignal::get_amplitude() const
{
	return this->m_amplitude;
}

/*
Brief: SquareWave member getter function which returns class variable m_samples.
       Number of waveform samples.
@Params: None
@Returns: this->m_samples member variable.
@throws: Nothing
*/
__forceinline           std::size_t                              radiolocation::SquareWaveSignal::get_samples() const
{
	return this->m_samples;
}

__forceinline           JonesVector                              radiolocation::SquareWaveSignal::polarization() const
{
	return this->m_polarization;
}


/*
Brief: Applies functor to each of the vector components of SquareWaveSignal object.
Uses variadic templates.Modifies *this in place.
@Params: lambda functor _Fx and variadic templated argument _Ty.
@Returns: Nothing
@throws: std::runtime_error when object vectors are empty.
*/
  _Raises_SEH_exception_ template<typename _Fx, typename... _Ty> __forceinline   void   radiolocation::SquareWaveSignal::apply(_In_ _Fx fx, _In_ _Ty&&... ty)
{
	  if (!(this->m_squarewave.empty()) && !(this->m_phase.empty()))
	  {
		  for (std::size_t i{ 0 }; i != this->m_samples; ++i)
		  {
			  this->m_squarewave.operator[](i).second = fx(std::forward<_Ty>(ty)...);
			  this->m_phase.operator[](i) = fx(std::forward<_Ty>(ty)...);
		  }
	  }
	  else  throw std::runtime_error("Fatal Error in SquareWaveSignal::apply: Empty vector(s) \n");
}