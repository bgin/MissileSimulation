
// Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
// Linear Frequency Modulation(Linear Chirp) signal class.

__forceinline   std::vector<std::pair<double, double>>  radiolocation::LinearChirpSignal::get_chirp() const
{
	return this->m_chirp;
}

__forceinline   std::vector<double>                     radiolocation::LinearChirpSignal::get_envelope() const
{
	return  this->m_envelope;
}

__forceinline   std::vector<double>                     radiolocation::LinearChirpSignal::get_phase() const
{
	return this->m_phase;
}

__forceinline   double                                  radiolocation::LinearChirpSignal::get_chirp_rate() const
{
	return this->m_chirp_rate;
}

__forceinline   double                                  radiolocation::LinearChirpSignal::get_envfrequency() const
{
	return this->m_envfrequency;
}

__forceinline   double                                  radiolocation::LinearChirpSignal::get_sfrequency() const
{
	return this->m_sfrequency;
}

__forceinline   double                                  radiolocation::LinearChirpSignal::get_efrequency() const
{
	return this->m_efrequency;
}

__forceinline   double                                  radiolocation::LinearChirpSignal::get_interval() const
{
	return this->m_interval;
}

__forceinline   double                                  radiolocation::LinearChirpSignal::get_itime() const
{
	return this->m_itime;
}

__forceinline   double                                  radiolocation::LinearChirpSignal::get_iphase() const
{
	return this->m_init_phase;
}

__forceinline   std::size_t                             radiolocation::LinearChirpSignal::get_samples() const
{
	return this->m_samples;
}

__forceinline   std::function<double(double)>           radiolocation::LinearChirpSignal::get_sinusoid() const
{
	return this->m_sinusoid;
}

__forceinline  radiolocation::JonesVector                radiolocation::LinearChirpSignal::polarization() const
{
	return this->m_polarization;
}

__forceinline   double                                   radiolocation::LinearChirpSignal::einterval() const
{
	return this->m_einterval;
}

__forceinline   double                                   radiolocation::LinearChirpSignal::einit_time() const
{
	return this->m_einit_time;
}

/*
Brief: Applies functor to each of the vector components of LinearChirpSignal object.
Uses variadic templates.Modifies *this in place.
@Params: lambda functor F, variadic templated rval argument _Fx
@Returns: Nothing
@throws: std::runtime_error when object vectors are empty.
*/
_Raises_SEH_exception_ template<typename F, typename... _Fx>  __forceinline  void  radiolocation::LinearChirpSignal::apply(_In_ F f, _In_ _Fx&&... fx)
{
	if (!(this->m_chirp.empty()) || !(this->m_envelope.empty() ) || !(this->m_phase.empty()))
	{
		for (size_t i = 0; i != this->m_samples; ++i)
		{
			this->m_chirp.operator[](i).second = f(std::forward<_Fx>(fx)...);
			this->m_envelope.operator[](i) = f(std::forward<_Fx>(fx)...);
			this->m_phase.operator[](i) = f(std::forward<_Fx>(fx)...);
		}
	}
	else throw std::runtime_error("Fatal Error in LinearChirpSignal::apply: Empty vectors\n");
}

/*
Brief: Applies 3 functors to each of the vector components of LinearChirpSignal object.
Uses variadic templates.Modifies *this in place.
@Params: lambda functors F1,F2,F3 variadic templated rval argument _Ty&&
@Returns: Nothing
@throws: std::runtime_error when object vectors are empty.
*/
_Raises_SEH_exception_  template<typename F1, typename F2, typename F3, typename... _Ty> __forceinline void radiolocation::LinearChirpSignal::apply(_In_ F1 f1,
	_In_ F2 f2, _In_ F3 f3, _In_ _Ty&&... t)
{
	if (!(this->m_chirp.empty()) || !(this->m_envelope.empty()) || !(this->m_phase.empty()))
	{
		for (size_t i{ 0 }; i != this->m_samples; ++i)
		{
			this->m_chirp.operator[](i).second = f1(std::forward<_Ty>(t)...);
			this->m_envelope.operator[](i) = f2(std::forward<_Ty>(t)...);
			this->m_phase.operator[](i) = f3(std::forward<_Ty>(t)...);
		}
	}
	else throw std::runtime_error("Fatal Error in LinearChirpSignal::apply: Empty vector(s)\n");
}