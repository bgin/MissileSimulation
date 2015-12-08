
// Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
// Sine Waveform signal class.

__forceinline   std::vector<std::pair<double, double>>   radiolocation::CWSineSignal::get_sine_signal() const
{
	return this->m_sine_signal;
}


__forceinline   std::vector<double>                      radiolocation::CWSineSignal::get_signal_envelope() const
{
	return this->m_envelope;
}


__forceinline   std::vector<double>                      radiolocation::CWSineSignal::get_phase() const
{
	return this->m_phase;
}

__forceinline   double                                   radiolocation::CWSineSignal::get_init_time() const
{
	return this->m_init_time;
}


__forceinline   double                                   radiolocation::CWSineSignal::get_duration() const
{
	return this->m_duration;
}

__forceinline   double                                   radiolocation::CWSineSignal::get_frequency() const
{
	return this->m_frequency;
}

__forceinline   double                                   radiolocation::CWSineSignal::get_envelop_freq() const
{
	return this->m_envelope_freq;
}

__forceinline   double                                   radiolocation::CWSineSignal::get_interval() const
{
	return this->m_interval;
}

__forceinline   std::size_t                              radiolocation::CWSineSignal::get_samples_count() const
{
	return this->m_samples;
}

__forceinline   radiolocation::JonesVector                      radiolocation::CWSineSignal::polarization() const
{
	return this->m_polarization;
}