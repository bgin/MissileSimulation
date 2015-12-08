__forceinline  std::vector<std::pair<double, double>>  radiolocation::CWCosineSignal::get_cos_signal() const
{
	return this->m_cos_signal;
}

__forceinline  std::vector<double>                     radiolocation::CWCosineSignal::get_signal_envelope() const
{
	return this->m_envelope;
}


__forceinline  std::vector<double>                     radiolocation::CWCosineSignal::get_phase() const
{
	return this->m_phase;
}


__forceinline  double        radiolocation::CWCosineSignal::get_duration() const
{
	return this->m_duration;
}

__forceinline  double        radiolocation::CWCosineSignal::get_frequency() const
{
	return this->m_frequency;
}

__forceinline  double        radiolocation::CWCosineSignal::get_env_frequency() const
{
	return this->m_efrequency;
}

__forceinline  double        radiolocation::CWCosineSignal::get_init_time() const
{
	return this->m_init_time;
}

__forceinline  double        radiolocation::CWCosineSignal::get_interval() const
{
	return this->m_interval;
}



__forceinline   std::size_t  radiolocation::CWCosineSignal::get_num_samples() const
{
	return this->m_samples;
}

__forceinline  radiolocation::JonesVector   radiolocation::CWCosineSignal::polarization() const
{
	return this->m_polarization;
}

// Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
// Cosine Waveform signal class.