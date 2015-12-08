
#include "PureSine.h"
#include "../MathLib/MathConstants.h"
#include "../MathLib/Derivative.h"


const double radiolocation::PureSineWave::TWO_PI{ mathlib::MathConstants::TWO_PI_DBL() };

_Raises_SEH_exception_ radiolocation::PureSineWave::PureSineWave(_In_  struct PureSineParams const& params)
	
{
	create_signal(params);
}

_Raises_SEH_exception_ radiolocation::PureSineWave::PureSineWave(_In_ const double init_time, _In_ const double timestep, _In_ const double sfreq, _In_ const std::size_t n_samples)
{
	create_signal(init_time, timestep, sfreq, n_samples);
}


radiolocation::PureSineWave::PureSineWave(_In_ PureSineWave const& rhs)
{
	create_signal(rhs);
}

radiolocation::PureSineWave::PureSineWave(_In_ PureSineWave &&rhs)
{
	create_signal(rhs);
}


_Raises_SEH_exception_  void           radiolocation::PureSineWave::create_signal(_In_ struct PureSineParams const& params)
	
{
#if defined _DEBUG
	_ASSERTE((0.0 < params.init_time) && (0 < params.n_threads) && (32 < params.n_samples));
#else
	if ((0.0 > params.init_time) || (0 > params.n_threads) || (32 > params.n_samples))
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("PureSineWave::create_signal: Failed!!") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	this->m_amplitude = params.amplitude;
	this->m_frequency = params.freq;
	this->m_init_time = params.init_time;
	this->m_interval = params.interval;
	this->m_samples = params.n_samples;
	this->m_polarization = JonesVector(std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 1.0));
	// Define automatic variables for OPENMP multi-threading.
	double a_amplitude{ params.amplitude };
	std::size_t i;
	double a_init_time{ params.init_time };
	double a_interval{ params.interval };
	std::size_t a_samples{ params.n_samples };
	std::vector<std::pair<double, double>> a_sine(a_samples);
	std::vector<double> a_phase(a_samples);
	double delta{ 0.0 }; double t{ 0.0 };
	double inv_samples{ 1.0 / static_cast<double>(a_samples) };
	double real_freq{ n_cycles(a_samples, a_interval) };
	omp_set_num_threads(params.n_threads);
#if defined OMP_TIMING
	double start{ wrapp_omp_get_wtime() };
#endif
#pragma  omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t) reduction(+:a_init_time)
	for (i = 0; i < a_samples; ++i)
	{
		a_init_time += a_interval;
		delta = static_cast<double>(i)* inv_samples;
		t = a_init_time * delta;
		a_phase.operator[](i) = TWO_PI * real_freq * t;
		a_sine.operator[](i).operator=({ t, params.amplitude * ::sin(a_phase.operator[](i)) });
	}
#if defined OMP_TIMING
	double end{ wrapp_omp_get_wtime() };
	std::printf("PureSineWave::create_signal executed in:%.15fseconds\n", end - start);
#endif
	this->m_phase = std::vector<double>(std::move(a_phase));
	this->m_sine = std::vector<std::pair<double, double>>(std::move(a_sine));
}


_Raises_SEH_exception_     void       radiolocation::PureSineWave::create_signal(_In_ const double init_time, _In_ const double timestep, _In_ const double sfreq, _In_ const std::size_t n_samples)
{
#if defined _DEBUG
	_ASSERTE(32 < n_samples);
#else
	if (32 > n_samples)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("PureSineWave::create_signal") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	this->m_amplitude = 0.0;
	this->m_frequency = sfreq;
	this->m_samples = n_samples;
	this->m_init_time = init_time;
	this->m_interval = timestep;
	this->m_polarization = JonesVector();
	const double HALF_PI{ mathlib::MathConstants::HALF_PI_DBL() };
	_Field_size_(this->m_samples) this->m_phase = std::vector<double>(this->m_samples, HALF_PI);
	_Field_size_(this->m_samples) this->m_sine = std::vector<std::pair<double, double>>(this->m_samples);

	for (std::size_t i{ 0 }; i != this->m_samples; ++i)
		this->m_sine.operator[](i).operator=({ static_cast<double>(i), ::sin(this->m_phase.operator[](i)) });

}
	



void                   radiolocation::PureSineWave::create_signal(_In_ PureSineWave const& rhs)
{
	this->m_amplitude = rhs.m_amplitude;
	this->m_frequency = rhs.m_frequency;
	this->m_init_time = rhs.m_init_time;
	this->m_interval = rhs.m_interval;
	this->m_samples = rhs.m_samples;
	this->m_polarization = JonesVector(rhs.m_polarization);
	this->m_phase = std::vector<double>(rhs.m_phase);
	this->m_sine = std::vector<std::pair<double, double>>(rhs.m_sine);
}

void                   radiolocation::PureSineWave::create_signal(_In_ PureSineWave &&rhs)
{
	this->m_amplitude = std::move(rhs.m_amplitude);
	this->m_frequency = std::move(rhs.m_frequency);
	this->m_init_time = std::move(rhs.m_init_time);
	this->m_interval = std::move(rhs.m_interval);
	this->m_samples = std::move(rhs.m_samples);
	this->m_polarization = JonesVector(std::move(rhs.m_polarization));
	this->m_phase = std::vector<double>(std::move(rhs.m_phase));
	this->m_sine = std::vector<std::pair<double, double>>(std::move(rhs.m_sine));
}

radiolocation::PureSineWave&           radiolocation::PureSineWave::operator=(_In_ PureSineWave const& rhs)
{
	if (this == &rhs) return *this;

	this->m_amplitude = rhs.m_amplitude;
	this->m_frequency = rhs.m_frequency;
	this->m_init_time = rhs.m_init_time;
	this->m_interval = rhs.m_interval;
	this->m_samples = rhs.m_samples;
	this->m_polarization.operator=(rhs.m_polarization);
	this->m_phase.operator=(rhs.m_phase);
	this->m_sine.operator=(rhs.m_sine);
	return *this;
}

radiolocation::PureSineWave&           radiolocation::PureSineWave::operator=(_In_ PureSineWave &&rhs)
{
	if (this == &rhs) return *this;

	this->m_amplitude = std::move(rhs.m_amplitude);
	this->m_frequency = std::move(rhs.m_frequency);
	this->m_init_time = std::move(rhs.m_init_time);
	this->m_interval = std::move(rhs.m_interval);
	this->m_samples = std::move(rhs.m_samples);
	this->m_polarization.operator=(std::move(rhs.m_polarization));
	this->m_phase.operator=(std::move(rhs.m_phase));
	this->m_sine.operator=(std::move(rhs.m_sine));
	return *this;
}

std::ostream&                          radiolocation::operator<<(_In_ std::ostream &os, _In_ PureSineWave const& rhs)
{
	std::setprecision(15);
	os.scientific;
	for (std::size_t i{ 0 }; i != rhs.m_samples; ++i)
		os << "sin(phi(t)):" << rhs.m_sine.operator[](i).second << "phi(t):" << rhs.m_phase[i] <<
		"t:" << rhs.m_sine.operator[](i).first << std::endl;
	return os;
}

double                 radiolocation::PureSineWave::n_cycles() const
{
	return (0.5 * (static_cast<double>(this->m_samples) * this->m_interval));
}

double                 radiolocation::PureSineWave::n_cycles(_In_ const std::size_t samples, _In_ const double interval)
{
	return (0.5 * (static_cast<double>(samples)* interval));
}

double                 radiolocation::PureSineWave::cycle_width() const
{
	return ((static_cast<double>(this->m_samples) * this->m_interval) / this->n_cycles());
}

std::vector<std::pair<double, double>>   radiolocation::PureSineWave::pulse_samples() const
{
	return this->get_sine();
}

std::vector<double>                      radiolocation::PureSineWave::pulse_phase() const
{
	return this->get_phase();
}

std::size_t                              radiolocation::PureSineWave::pulse_samples_count() const
{
	return this->get_samples();
}

/*void           radiolocation::PureSineWave::initialize(const size_t cycles, const double step, double start,const double freq)
{
	_ASSERT((0 < cycles) && (std::fabs(step) > std::numeric_limits<double>::epsilon()));
	this->m_num_cycles = cycles;
	this->time_step = step;
	this->frequency = freq;
	double phase = 0.0;
	for (auto i = 0; i != this->m_num_cycles; ++i)
	{
		double delta = static_cast<double>(i + 1) / static_cast<double>(this->m_num_cycles);
		double t = this->time_step * delta;
		phase = PI_TWO * t * (start + (this->frequency - start) * (delta / 2));
		this->m_vec_sine.push_back(std::pair<double, double>(t, amplitude *  ::sin(phase)));
	}
	
}*/


/*void         radiolocation::PureSineWave::amplitude_modulation(const double modulating_amp, const double modulating_freq, const double modulating_phase)
{
	_ASSERT(std::fabs(modulating_amp) < 1.0 && (std::fabs(modulating_freq) < std::fabs(this->frequency)));
	double amplitude_average = 0.5 * (amplitude * modulating_amp);
	for (size_t i = 0; i != this->m_num_cycles; ++i)
	{
		this->m_vec_sine.operator[](i).second += amplitude_average * (::sin(PI_TWO*(this->frequency + modulating_freq)*this->m_vec_sine.operator[](i).first + modulating_phase) +
			::sin(PI_TWO*(this->frequency - modulating_freq)*this->m_vec_sine.operator[](i).first - modulating_phase));
	}
}

void        radiolocation::PureSineWave::phase_modulation(const double mod_amp, const double mod_freq, const double mod_index,
	std::function<double(double,double)> &mod_wave)
{
	_ASSERT(std::fabs(mod_freq) < std::fabs(this->frequency));
	for (size_t i = 0; i != this->m_num_cycles; ++i)
	{
		double temp = this->m_vec_sine.operator[](i).second;
		this->m_vec_sine.operator[](i).second = ::sin(temp + mod_index * mod_wave(mod_freq,mod_amp)); //use capture feature in lambda.
	}
}*/



