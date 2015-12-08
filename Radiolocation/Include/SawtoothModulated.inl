
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Modulated Sawtooth signal class - inline functions implementation.
@author: Bernard Gingold
@version:  1.0  29/09/2015

*/

/*
Brief: Modulated Sawtooth Wave member getter function which returns class variable m_St.
Resulting Modulated Sawtooth Wave signal.
@Params: None
@Returns: this->m_St member variable.
@throws: Nothing
*/
_Outptr_opt_result_buffer_(m_samples) __forceinline     std::vector<std::pair<double, double>>   radiolocation::SawtoothMSignal::get_St() const
{
	return this->m_St;
}

/*
Brief: Modulated Sawtooth member getter function which returns class variable m_rt
modulating envelope argument.
@Params: None
@Returns: this->m_rt member variable.
@throws: Nothing
*/
_Outptr_opt_result_buffer_(m_samples) __forceinline     std::vector<double>                      radiolocation::SawtoothMSignal::get_rt() const
{
	return this->m_rt;
}

/*
Brief: Modulated Sawtooth member getter function which returns const double* pointer to class variable m_rt

@Params: None
@Returns: const double* pointer to &this->m_rt[0].Pass this->m_samples as a resulting array length.
@throws: Nothing
*/
_Outptr_opt_result_buffer_(m_samples) __forceinline     const double                            *radiolocation::SawtoothMSignal::get_prt() const
{
	const double* p_to_rt = &this->m_rt[0]; //Always pass length of m_rt.
	return p_to_rt;
}

/*
Brief: Modulated Sawtooth member getter function which returns class variable m_phit
modulating phase argument.
@Params: None
@Returns: this->m_phit member variable.
@throws: Nothing
*/
_Outptr_opt_result_buffer_(m_samples) __forceinline     std::vector<double>                      radiolocation::SawtoothMSignal::get_phit() const
{
	return this->m_phit;
}

/*
Brief: Modulated Sawtooth member getter function which returns const double* pointer to class variable m_phit

@Params: None
@Returns: const double* pointer to &this->m_phit[0].Pass this->m_samples as a resulting array length.
@throws: Nothing
*/
_Outptr_opt_result_buffer_(m_samples) __forceinline    const    double                          *radiolocation::SawtoothMSignal::get_pphit() const
{
	const double* p_to_phit = &this->m_phit[0];//Always pass length of m_phit.
	return p_to_phit;
}

/*
Brief: Modulated Sawtooth member getter function which returns class variable m_samples.
Number of waveform samples.
@Params: None
@Returns: this->m_samples member variable.
@throws: Nothing
*/
__forceinline                        std::size_t                       radiolocation::SawtoothMSignal::get_samples() const
{
	return this->m_samples;
}

/*
Brief: Modulated Sawtooth member getter function which returns class variable m_sinit_time.
initial time point of S(t).
@Params: None
@Returns: this->m_sinit_time member variable.
@throws: Nothing
*/
__forceinline                        double                           radiolocation::SawtoothMSignal::get_sinit_time() const
{
	return this->m_sinit_time;
}


/*
Brief: Modulated Sawtooth member getter function which returns class variable m_rinit_time.
initial time point of r(t).
@Params: None
@Returns: this->m_rinit_time member variable.
@throws: Nothing
*/
__forceinline                        double                           radiolocation::SawtoothMSignal::get_rinit_time() const
{
	return this->m_rinit_time;
}

/*
Brief: Modulated Sawtooth member getter function which returns class variable m_phinit_time.
initial time point of phi(t).
@Params: None
@Returns: this->m_phinit_time member variable.
@throws: Nothing
*/
__forceinline                        double                          radiolocation::SawtoothMSignal::get_phinit_time() const
{
	return this->m_phinit_time;
}

/*
Brief: Modulated Sawtooth member getter function which returns class variable m_sinterval.
initial time point increment of S(t)
@Params: None
@Returns: this->m_sinterval member variable.
@throws: Nothing
*/
__forceinline                         double                          radiolocation::SawtoothMSignal::get_sinterval() const
{
	return this->m_sinterval;
}

/*
Brief: Sawtooth member getter function which returns class variable m_rinterval.
initial time point increment of r(t).
@Params: None
@Returns: this->m_interval member variable.
@throws: Nothing
*/
__forceinline                        double                          radiolocation::SawtoothMSignal::get_rinterval() const
{
	return this->m_rinterval;
}

/*
Brief: Sawtooth member getter function which returns class variable m_phinterval.
initial time point increment of phi(t)
@Params: None
@Returns: this->m_phinterval member variable.
@throws: Nothing
*/
__forceinline                       double                           radiolocation::SawtoothMSignal::get_phinterval() const
{
	return this->m_phinterval;
}

/*
Brief: Sawtooth member getter function which returns class variable m_sfrequency.
Modulated Sawtooth frequency ie. not real signal frequency which is impossible to implement because of time-space constaints.
"Real" implemented frequency depends on  0.5 * (this->m_samples * this->m_sinterval)
@Params: None
@Returns: this->m_sfrequency member variable.
@throws: Nothing
*/
__forceinline                       double                          radiolocation::SawtoothMSignal::get_sfrequency() const
{
	return this->m_sfrequency;
}

/*
Brief: Sawtooth member getter function which returns class variable m_rfrequency.
Modulated Sawtooth frequency ie. not real signal frequency which is impossible to implement because of time-space constaints.
"Real" implemented frequency depends on  0.5 * (this->m_samples * this->m_sinterval)
@Params: None
@Returns: this->m_rfrequency member variable.
@throws: Nothing
*/
__forceinline                      double                           radiolocation::SawtoothMSignal::get_rfrequency() const
{
	return this->m_rfrequency;
}

/*
Brief: Sawtooth member getter function which returns class variable m_phfrequency.
Modulated Sawtooth frequency ie. not real signal frequency which is impossible to implement because of time-space constaints.
"Real" implemented frequency depends on  0.5 * (this->m_samples * this->m_sinterval)
@Params: None
@Returns: this->m_phfrequency member variable.
@throws: Nothing
*/
__forceinline                     double                             radiolocation::SawtoothMSignal::get_phfrequency() const
{
	return this->m_phfrequency;
}

/*
Brief: Sawtooth member getter function which returns class variable m_rwaveform.
Modulated Sawtooth r(t) waveform generator.

@Params: None
@Returns: this->m_rwaveform member variable.
@throws: Nothing
*/
__forceinline                     std::function<double(double)>     radiolocation::SawtoothMSignal::get_rwaveform() const
{
	return  this->m_rwaveform;
}

/*
Brief: Sawtooth member getter function which returns class variable m_phwaveform.
Modulated Sawtooth phi(t) waveform generator.

@Params: None
@Returns: this->m_phwaveform member variable.
@throws: Nothing
*/
__forceinline                    std::function<double(double)>      radiolocation::SawtoothMSignal::get_phwaveform() const
{
	return this->m_phwaveform;
}

/*
@Brief: Polarization vector.
*/
__forceinline                    JonesVector                        radiolocation::SawtoothMSignal::polarization() const
{
	return this->m_polarization;
}

/*
Brief: Sawtooth member  function which returns number of S(t) cycles.


@Params: None
@Returns: number of cycles of S(t) Sawtooth waveform.
@throws: Nothing
*/
__forceinline                     double                            radiolocation::SawtoothMSignal::St_cycles() const
{
	return (0.5 * (static_cast<double>(this->m_samples) * this->m_sinterval));
}

/*
Brief: Sawtooth member  function which returns number of r(t) cycles.


@Params: None
@Returns: number of cycles of r(t) envelope modulating waveform.
@throws: Nothing
*/
__forceinline                    double                               radiolocation::SawtoothMSignal::rt_cycles() const
{
	return (0.5 * (static_cast<double>(this->m_samples) * this->m_rinterval));
}

/*
Brief: Sawtooth member  function which returns number of phi(t) cycles.


@Params: None
@Returns: number of cycles of phi(t) phase modulating waveform.
@throws: Nothing
*/
__forceinline                    double                                radiolocation::SawtoothMSignal::phit_cycles() const
{
	return (0.5 * (static_cast<double>(this->m_samples) * this->m_phinterval));
}

/*
Brief: Modulated Sawtooth member  function which returns single S(t) pulse width.


@Params: None
@Returns: Single S(t) pulse width.
@throws: Nothing
*/
__forceinline                    double                                radiolocation::SawtoothMSignal::St_pulse_width() const
{
	
	return ((static_cast<double>(this->m_samples) * this->m_sinterval) / this->St_cycles());
	
}

/*
Brief: Modulated Sawtooth member  function which returns single r(t) pulse width.


@Params: None
@Returns: Single r(t) pulse width.
@throws: Nothing
*/
__forceinline                   double                                 radiolocation::SawtoothMSignal::rt_pulse_width() const
{
	return ((static_cast<double>(this->m_samples) * this->m_rinterval) / this->rt_cycles());
}

/*
Brief: Modulated Sawtooth member  function which returns single phi(t) pulse width.


@Params: None
@Returns: Single phi(t) pulse width.
@throws: Nothing
*/
__forceinline                   double                                 radiolocation::SawtoothMSignal::phit_pulse_width() const
{
	return ((static_cast<double>(this->m_samples) * this->m_phinterval) / this->phit_cycles());
}