
__forceinline    std::vector<std::pair<double, double>>  radiolocation::PureCosineWave::get_cos() const
{
	return this->m_cos;
}

__forceinline    std::vector<double>                     radiolocation::PureCosineWave::get_phase() const
{
	return this->m_phase;
}

__forceinline    const   double                         *radiolocation::PureCosineWave::get_phase_ptr()
{
	const double* ptr = &this->m_phase[0]; // length of this->m_phase should be passed by the caller.
	return ptr;
}


__forceinline    std::size_t                             radiolocation::PureCosineWave::get_samples() const
{
	return this->m_samples;
}

__forceinline    double                                  radiolocation::PureCosineWave::get_frequency() const
{
	return this->m_frequency;
}

__forceinline    double                                  radiolocation::PureCosineWave::get_time_step() const
{
	return this->m_time_step;
}

__forceinline    double                                  radiolocation::PureCosineWave::get_init_time() const
{
	return this->m_init_time;
}

__forceinline    double                                  radiolocation::PureCosineWave::get_amplitude() const
{
	return this->m_amplitude;
}

__forceinline    radiolocation::JonesVector                     radiolocation::PureCosineWave::polarization() const
{
	return this->m_polarization;
}

template<typename _Fx, typename... _Ty> __forceinline  PureCosineWave&  radiolocation::PureCosineWave::apply(_In_ _Fx fx, _In_ _Ty&&... ty)
{
	for (std::size_t i{ 0 }; i != this->m_samples; ++i)
	{
		this->m_cos.operator[](i) = fx(std::forward<_Ty>(ty)...);
		this->m_phase.operator[](i) = fx(std::forward<_Ty>(ty)...);
	}
	return *this;
}

__forceinline      double               radiolocation::PureCosineWave::n_cycles() const
{
	return (0.5 * (static_cast<double>(this->m_samples) * this->m_time_step));
}


__forceinline    std::function<double(double)>      radiolocation::AWGNoiseCosine::WaveformGenerator() const
{
	return this->m_oWaveformGenerator;
}

__forceinline    std::vector<std::pair<double, double>>  radiolocation::AWGNoiseCosine::AWGNCosine() const
{
	return this->m_AWGNCosine;
}

__forceinline    std::size_t                             radiolocation::AWGNoiseCosine::Samples() const
{
	return this->m_uisamples;
}

__forceinline     double                                 radiolocation::AWGNoiseCosine::Mean() const
{
	return this->m_dmean;
}

__forceinline     double                                 radiolocation::AWGNoiseCosine::Variance() const
{
	return this->m_dvariance;
}