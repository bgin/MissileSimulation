/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Square Wave Modulated signal class - inline functions implementation.
@author: Bernard Gingold
@version:  1.0  25/09/2015

*/


/*
Brief: SquareWaveMSignal member getter function which returns class variable m_square_wave.
Resulting Square Wave Modulating signal.
@Params: None
@Returns: this->m_square_wave member variable.
@throws: Nothing
*/
_Outptr_opt_result_buffer_(m_samples) __forceinline     std::vector<std::pair<double, double>>  radiolocation::SquareWaveMSignal::get_m_square_wave() const
{
	return this->m_square_wave;
}

/*
Brief: SquareWaveMSignal member getter function which returns class variable m_envelope
Sine phase argument.
@Params: None
@Returns: this->m_envelope member variable.
@throws: Nothing
*/
_Outptr_opt_result_buffer_(m_samples) __forceinline      std::vector<double>                    radiolocation::SquareWaveMSignal::get_envelope() const
{
	return this->m_envelope;
}


/*
Brief: SquareWaveMSignal member getter function which returns class variable m_phase
Sine phase argument.
@Params: None
@Returns: this->m_phase member variable.
@throws: Nothing
*/
_Outptr_opt_result_buffer_(m_samples) __forceinline      std::vector<double>                    radiolocation::SquareWaveMSignal::get_phase() const
{
	return this->m_phase;
}


/*
Brief: SquareWaveMSignal member getter function which returns class variable m_samples
       Signal number of samples
@Params: None
@Returns: this->m_samples member variable.
@throws: Nothing
*/
__forceinline               std::size_t               radiolocation::SquareWaveMSignal::get_samples() const
{
	return this->m_samples;
}

/*
Brief: SquareWaveMSignal member getter function which returns class variable m_sfrequency.
       Signal frequency.
@Params: None
@Returns: this->m_sfrequency member variable.
@throws: Nothing
*/
__forceinline                double                   radiolocation::SquareWaveMSignal::get_sfrequency() const
{
	return  this->m_sfrequency;
}

/*
Brief: SquareWaveMSignal member getter function which returns class variable m_envfrequency
       Modulating envelope signal frequency.
@Params: None
@Returns: this->m_envfrequency member variable.
@throws: Nothing
*/
__forceinline                 double                   radiolocation::SquareWaveMSignal::get_envfrequency() const
{
	return this->m_envfrequency;
}

/*
Brief: SquareWaveMSignal member getter function which returns class variable m_init_phase.
       signal initial phase, ie. sine wave generating function initial phase.
@Params: None
@Returns: this->m_init_phase member variable.
@throws: Nothing
*/
__forceinline                double                    radiolocation::SquareWaveMSignal::get_init_phase() const
{
	return this->m_init_phase;
}

/*
Brief: SquareWaveMSignal member getter function which returns class variable m_sinit_time
signal starting time , ie t0.
@Params: None
@Returns: this->m_sinit_time member variable.
@throws: Nothing
*/
__forceinline                double                    radiolocation::SquareWaveMSignal::get_sinit_time() const
{
	return this->m_sinit_time;
}

/*
Brief: SquareWaveMSignal member getter function which returns class variable m_einit_time
envelope starting time , ie t0.
@Params: None
@Returns: this->m_einit_time member variable.
@throws: Nothing
*/
__forceinline                double                    radiolocation::SquareWaveMSignal::get_einit_time() const
{
	return this->m_einit_time;
}

/*
Brief: SquareWaveMSignal member getter function which returns class variable m_sinterval
signal time step interval.
@Params: None
@Returns: this->m_sinterval member variable.
@throws: Nothing
*/
__forceinline                double                   radiolocation::SquareWaveMSignal::get_sinterval() const
{
	return this->m_sinterval;
}

/*
Brief: SquareWaveMSignal member getter function which returns class variable m_einterval
envelope time step interval, must be more than signal interval, in order to generate lower frequency modulating envelope.
@Params: None
@Returns: this->m_einterval member variable.
@throws: Nothing
*/
__forceinline               double                    radiolocation::SquareWaveMSignal::get_einterval() const
{
	return this->m_einterval;
}

/*
Brief: SquareWaveMSignal member getter function which returns class variable m_gen_function
envelope waveform generating function.
@Params: None
@Returns: this->m_gen_function member variable.
@throws: Nothing
*/
__forceinline              std::function<double(double)>   radiolocation::SquareWaveMSignal::get_gen_function() const
{
	return this->m_gen_function;
}

/*
Brief: Applies 3 functors to each of the vector components of SquareWaveMSignal object.
Uses variadic templates.Modifies *this in place.
@Params: lambda functor _Fx1, _Fx2, _Fx3 and variadic templated argument _Ty.
@Returns: Nothing
@throws: BOOST_THROW_EXCEPTION(empty_vector())
*/
_Raises_SEH_exception_ template<typename _Fx1, typename _Fx2, typename _Fx3, typename... _Ty> __forceinline  void  radiolocation::SquareWaveMSignal::apply(_In_ _Fx1 fx1,
	_In_ _Fx2 fx2, _In_ _Fx3 fx3, _In_ _Ty&&... ty)
{
	if (!(this->m_square_wave.empty()) && !(this->m_envelope.empty()) && !(this->m_phase.empty()))
	{
		for (std::size_t i{ 0 }; i != this->m_samples; ++i)
		{
			this->m_square_wave.operator[](i).second = fx1(std::forward<_Ty>(ty)...);
			this->m_phase.operator[](i) = fx2(std::forward<_Ty>(ty)...);
			this->m_envelope.operator[](i) = fx3(std::forward<_Ty>(ty)...);
		}
	
	}
	else  throw std::invalid_argument("Fatal Error in SquareWaveMSignal::apply: Empty vector\n"); /*BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("SquareWaveMSignal::apply") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));*/
}

/*
Brief: Applies 3 functors to each of the vector components of SquareWaveMSignal object.
Uses std::for_each.Modifies *this in place.
@Params: lambda functor _Fx1, _Fx2, _Fx3 and  templated argument _Ty.
@Returns: Nothing
@throws: BOOST_THROW_EXCEPTION(empty_vector())
*/
_Raises_SEH_exception_ template<typename _Fx1, typename _Fx2, typename _Fx3, typename _Ty> __forceinline  void radiolocation::SquareWaveMSignal::apply(_In_ _Fx1 fx1, _In_ const _Ty& ty1,
	_In_ _Fx2 fx2, _In_ const _Ty& ty2, _In_ _Fx3 fx3, _In_ const _Ty& ty3)
{
	if (!(this->m_square_wave.empty()) && !(this->m_envelope.empty()) && !(this->m_phase.empty()))
	{
		// Lambda with std::pair<double,double> should passed as a functor.
		std::for_each(this->m_square_wave.begin(), this->m_square_wave.end(), _Fx1(ty1));
		std::for_each(this->m_envelope.begin(), this->m_envelope.end(), _Fx2(ty2));
		std::for_each(this->m_phase.begin(), this->m_phase.end(), _Fx3(ty3));
	}
	else BOOST_THROW_EXCEPTION(
		empty_vector() <<
		boost::errinfo_api_function("SquareWaveMSignal::apply") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
}

/*
Brief: Applies lambda functor to each of the vector components of SquareWaveMSignal object.
Uses std::for_each.
@Params: reference to SquareWaveMSignal object, lambda functor _Fx
@Returns: Nothing
@throws: BOOST_THROW_EXCEPTION(empty_vector())
*/
template<typename _Fx>  __forceinline   void     radiolocation::SquareWaveMSignal::apply(_Inout_ SquareWaveMSignal &rhs, _In_ _Fx fx)
{
	std::for_each(rhs.m_square_wave.begin(), rhs.m_square_wave.end(), fx);
	std::for_each(rhs.m_phase.begin(), rhs.m_phase.end(), fx);
	std::for_each(rhs.m_envelope.begin(), rhs.m_phase.end(), fx);
}