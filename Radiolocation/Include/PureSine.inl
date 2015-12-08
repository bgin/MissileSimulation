
_Field_size_(m_samples) __forceinline  std::vector<std::pair<double, double>>  radiolocation::PureSineWave::get_sine() const
{
	return this->m_sine;
}

_Field_size_(m_samples) __forceinline  std::vector<double>                     radiolocation::PureSineWave::get_phase() const
{
	return this->m_phase;
}

_Outptr_opt_result_buffer_(m_samples) __forceinline  const   double                         *radiolocation::PureSineWave::get_phase_ptr() const
{
	_Outptr_opt_result_buffer_(m_samples) const double* ptr = &this->m_phase[0];
	return ptr;
}

__forceinline  size_t         radiolocation::PureSineWave::get_samples() const
{
	return this->m_samples;
}

__forceinline  double         radiolocation::PureSineWave::get_init_time() const
{
	return this->m_init_time;
}

__forceinline  double         radiolocation::PureSineWave::get_frequency() const
{
	return this->m_frequency;
}

__forceinline  double         radiolocation::PureSineWave::get_interval() const
{
	return this->m_interval;
}

__forceinline  double        radiolocation::PureSineWave::get_amplitude() const
{
	return this->m_amplitude;
}

__forceinline  JonesVector         radiolocation::PureSineWave::polarization() const
{
	return this->m_polarization;
}


template<typename _Fx, typename... _Ty> __forceinline radiolocation::PureSineWave&  radiolocation::PureSineWave::apply(_In_ _Fx fx, _In_ _Ty&&... ty)
{
	for (std::size_t i{ 0 }; i != this->m_samples; ++i)
	{
		this->m_phase.operator[](i) = fx(std::forward<_Ty>(ty)...);
		this->m_sine.operator[](i) = fx(std::forward<_Ty>(ty)...);
	}
	return *this;
}
