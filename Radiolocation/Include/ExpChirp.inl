
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
 Linear Frequency Modulation(Exponential Chirp) signal class.
 @author: Bernard Gingold
 @version:  1.0  15/09/2015

 */


 

/*
*Brief: ExpChirpSignal member getter function which returns class variable m_chirp.
*@Params: None
*@Returns: this->m_chirp member variable.
*@throws: Nothing
*/

__forceinline    std::vector<std::pair<double, double>>  radiolocation::ExpChirpSignal::get_chirp() const
{
	return this->m_chirp;
}

/*
*Brief: ExpChirpSignal member getter function which returns class variable m_envelope.
*@Params: None
*@Returns: this->m_envelope member variable.
*@throws: Nothing
*/

__forceinline     std::vector<double>                     radiolocation::ExpChirpSignal::get_envelope() const
{
	return this->m_envelope;
}

/*
*Brief: ExpChirpSignal member getter function which returns class variable m_phase.
*@Params: None
*@Returns: this->m_phase member variable.
*@throws: Nothing
*/

__forceinline     std::vector<double>                    radiolocation::ExpChirpSignal::get_phase() const
{
	return this->m_phase;
}

/*
*Brief: ExpChirpSignal member getter function which returns class variable m_sfrequency.
* Chirp signal start sweep frequency.
*@Params: None
*@Returns: this->m_sfrequency member variable.
*@throws: Nothing
*/

__forceinline    double                                   radiolocation::ExpChirpSignal::get_sfrequency() const
{
	return this->m_sfrequency;
}

/*
Brief: ExpChirpSignal member getter function which returns class variable m_efrequency.
 Chirp signal final sweep frequency.
@Params: None
@Returns: this->m_efrequency member variable.
@throws: Nothing
*/

__forceinline    double                                    radiolocation::ExpChirpSignal::get_efrequency() const
{
	return this->m_efrequency;
}

/*
Brief: ExpChirpSignal member getter function which returns class variable m_envfrequency.
 Chirp envelope  frequency.
@Params: None
@Returns: this->m_envfrequency member variable.
@throws: Nothing
*/

__forceinline    double                                    radiolocation::ExpChirpSignal::get_envfrequency() const
{
	return this->m_envfrequency;
}

/*
Brief: ExpChirpSignal member getter function which returns class variable m_envinterval.
Chirp envelope  time step increment should be less than Chirp signal time step increment.
@Params: None
@Returns: this->m_envinterval member variable.
@throws: Nothing
*/

__forceinline   double                                     radiolocation::ExpChirpSignal::get_envinterval() const
{
	return this->m_env_interval;
}

/*
Brief: ExpChirpSignal member getter function which returns class variable m_interval.
Chirp  time step increment.
@Params: None
@Returns: this->m_interval member variable.
@throws: Nothing
*/

__forceinline   double                                     radiolocation::ExpChirpSignal::get_interval() const
{
	return  this->m_interval;
}

/*
Brief: ExpChirpSignal member getter function which returns class variable m_init_phase.
Chirp  signal initial phase.
@Params: None
@Returns: this->m_init_phase member variable.
@throws: Nothing
*/

__forceinline   double                                     radiolocation::ExpChirpSignal::get_init_phase() const
{
	return  this->m_init_phase;
}

/*
Brief: ExpChirpSignal member getter function which returns class variable m_chirp_rate.
Chirp  signal chirp rate K = f1 - f0 / T.
@Params: None
@Returns: this->m_chirp_rate member variable.
@throws: Nothing
*/

__forceinline    double                                     radiolocation::ExpChirpSignal::get_chirp_rate() const
{
	return  this->m_chirp_rate;
}

/*
Brief: ExpChirpSignal member getter function which returns class variable m_init_time.
Chirp  signal starting(initial) time point.
@Params: None
@Returns: this->m_init_time member variable.
@throws: Nothing
*/

__forceinline    double                                     radiolocation::ExpChirpSignal::get_init_time() const
{
	return  this->m_init_time;
}

/*
Brief: ExpChirpSignal member getter function which returns class variable m_samples.
Chirp  signal number of samples.
@Params: None
@Returns: this->m_samples member variable.
@throws: Nothing
*/

__forceinline   size_t                                     radiolocation::ExpChirpSignal::get_samples() const
{
	return this->m_samples;
}

/*
Brief: ExpChirpSignal member getter function which returns class variable m_sinusoid.
Chirp  signal generating function.
@Params: None
@Returns: this->m_sinusoid member variable.
@throws: Nothing
*/

__forceinline    std::function<double(double)>             radiolocation::ExpChirpSignal::get_sinusoid() const
{
	return this->m_sinusoid;
}


__forceinline    radiolocation::JonesVector                               radiolocation::ExpChirpSignal::polarization() const
{
	return this->m_polarization;
}

/*
Brief: Applies functor to each of the vector components of ExpChirpSignal object.
Uses variadic templates.Modifies *this in place.
@Params: lambda functor F and variadic templated argument _Fx.
@Returns: Nothing
@throws: std::runtime_error when object vectors are empty.
*/
_Raises_SEH_exception_   template<typename F, typename... _Fx> __forceinline void  radiolocation::ExpChirpSignal::apply(_In_ F f, _In_ _Fx&&... fx)
{
	if (!(this->m_chirp.empty()) || !(this->m_envelope.empty()) || !(this->m_phase.empty()))
	{
		for (size_t i = 0; i != this->m_samples; ++i)
		{
			this->m_chirp.operator[](i).second = f(std::forward<_Fx>(fx)...);
			this->m_envelope.operator[](i) =  f(std::forward<_Fx>(fx )...);
			this->m_phase.operator[](i) = f(std::forward<_Fx>(fx)...);

			
		}
	}
	else throw std::runtime_error("Fatal Error in ExpChirpSignal::apply: Empty vector\n");
}

/*
Brief: Applies 3 functors to each of the vector components of ExpChirpSignal object.
Uses variadic templates.Modifies *this in place.
@Params: lambda functors F1,F2,F3 and variadic templated argument _Ty.
@Returns: Nothing
@throws: std::runtime_error when object vectors are empty.
*/
_Raises_SEH_exception_   template<typename F1, typename F2, typename F3, typename... _Ty> __forceinline  void  radiolocation::ExpChirpSignal::apply(_In_ F1 f1,
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
	else  throw std::runtime_error("Fatal Error in ExpChirpSignal::apply: Empty vector\n");
}