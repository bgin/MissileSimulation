#include "PureCosine.h"
#include "../MathLib/MathConstants.h"
#include "../MathLib/Derivative.h"
#include "LibExceptions.h"
#include <random>







const double  radiolocation::PureCosineWave::TWO_PI{ mathlib::MathConstants::TWO_PI_DBL() };



_Raises_SEH_exception_ radiolocation::PureCosineWave::PureCosineWave(_In_  struct PureCosineParams const& params)
{
	create_signal(params);
}

_Raises_SEH_exception_  radiolocation::PureCosineWave::PureCosineWave(_In_  const double init_time, _In_ const double timestep, _In_ const double sfreq, _In_ const std::size_t samples)
{
	create_signal(init_time, timestep, sfreq, samples);
}


__thiscall radiolocation::PureCosineWave::PureCosineWave(_In_ PureCosineWave const& rhs)
{
	create_signal(rhs);
}

__thiscall radiolocation::PureCosineWave::PureCosineWave(_In_ PureCosineWave &&rhs)
{
	create_signal(rhs);
}


_Raises_SEH_exception_   void         __thiscall  radiolocation::PureCosineWave::create_signal(_In_ struct PureCosineParams const& params)
	
{
#if defined _DEBUG
	_ASSERTE((0.0 < params.amplitude) && (2 < params.n_samples) && (0 < params.n_threads));
#else
	if ((0.0 >= params.amplitude) && (2 > params.n_samples) && (0 > params.n_threads))
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("PureCosineWave::create_signal: Failed!!") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	this->m_amplitude = params.amplitude;
	this->m_frequency = params.sfreq;
	this->m_init_time = params.init_time;
	this->m_time_step = params.timestep;
	this->m_samples = params.n_samples;
	// Vertical linear polarization by default.
	this->m_polarization = JonesVector(std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 1.0));
	//Define automatic variables for OPENMP multi-threading.
	double a_amplitude{ params.amplitude };
	double a_init_time{ params.init_time };
	double a_timestep{ params.timestep };
	std::size_t a_samples{ params.n_samples };
	_Field_size_(a_samples) std::vector<std::pair<double, double>> a_cos(a_samples);
	_Field_size_(a_samples) std::vector<double> a_phase(a_samples);
	std::size_t i;
	double delta{ 0.0 }; double t{ 0.0 };
	double sig_freq{ n_cycles(a_samples, a_timestep) };
	double inv_samples{ 1.0 / static_cast<double>(a_samples) };
	omp_set_num_threads(params.n_threads);
#if defined OMP_TIMING
	double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t) reduction(+:a_init_time)
	for (i = 0; i < a_samples; ++i)
	{
		a_init_time += a_timestep;
		delta = static_cast<double>(i) * inv_samples;
		t = a_init_time * delta;
		a_phase.operator[](i) = TWO_PI * sig_freq * t;
		a_cos.operator[](i).operator=({ t, a_amplitude * ::cos(a_phase.operator[](i)) });
	}
#if defined OMP_TIMING
	double end{ wrapp_omp_get_wtime() };
	std::printf("PureCosineWave::create_signal executed in:%.15fseconds\n", end - start);
#endif
	this->m_phase = std::vector<double>(std::move(a_phase));
	this->m_cos = std::vector<std::pair<double, double>>(std::move(a_cos));
}

/*
@Brief: Create zero amplitude signal.
  Used to simulate period of no transmission in pulse train.
*/
_Raises_SEH_exception_   void                     radiolocation::PureCosineWave::create_signal(_In_ const double init_time, _In_ const double time_step,_In_ const double sfreq, _In_ const std::size_t samples)
{
#if defined _DEBUG
	_ASSERTE(32 < samples);
#else
	if (32 >= samples)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("PureCosineWave::create_signal: Failed") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	this->m_amplitude = 0.0;
	this->m_frequency = sfreq;
	this->m_init_time = init_time;
	this->m_samples = samples;
	this->m_time_step = time_step;
	this->m_polarization = JonesVector(); // Null vector by default.
	const double HALF_PI{ mathlib::MathConstants::HALF_PI_DBL() };
	_Field_size_(this->m_samples) this->m_phase = std::vector<double>(this->m_samples,HALF_PI);
	_Field_size_(this->m_samples) this->m_cos = std::vector<std::pair<double, double>>(this->m_samples);
	
	for (std::size_t i{ 0 }; i != this->m_samples; ++i)
	{
		this->m_cos.operator[](i).operator=({ static_cast<double>(i), ::cos(this->m_phase.operator[](i)) });
		std::printf("Sanity Check of result = %.9f\n", this->m_cos[i].second);
	}
	
#if defined _DEBUG
	std::printf("PureCosine::create_signal\n");
#endif
}


void                     radiolocation::PureCosineWave::create_signal(_In_ PureCosineWave const& rhs)
{
	this->m_amplitude = rhs.m_amplitude;
	this->m_frequency = rhs.m_frequency;
	this->m_init_time = rhs.m_init_time;
	this->m_samples = rhs.m_samples;
	this->m_time_step = rhs.m_time_step;
	this->m_polarization = JonesVector(rhs.m_polarization);
	this->m_phase = std::vector<double>(rhs.m_phase);
	this->m_cos = std::vector<std::pair<double, double>>(rhs.m_cos);
}


void                     radiolocation::PureCosineWave::create_signal(_In_ PureCosineWave &&rhs)
{
	this->m_amplitude = std::move(rhs.m_amplitude);
	this->m_frequency = std::move(rhs.m_frequency);
	this->m_init_time = std::move(rhs.m_init_time);
	this->m_samples = std::move(rhs.m_samples);
	this->m_time_step = std::move(rhs.m_time_step);
	this->m_polarization = JonesVector(std::move(rhs.m_polarization));
	this->m_phase = std::vector<double>(std::move(rhs.m_phase));
	this->m_cos = std::vector<std::pair<double, double>>(std::move(rhs.m_cos));
}


radiolocation::PureCosineWave&         radiolocation::PureCosineWave::operator=(_In_ PureCosineWave const& rhs)
{
	if (this == &rhs) return *this;

	this->m_amplitude = rhs.m_amplitude;
	this->m_frequency = rhs.m_frequency;
	this->m_init_time = rhs.m_init_time;
	this->m_time_step = rhs.m_time_step;
	this->m_samples = rhs.m_samples;
	this->m_polarization.operator=(rhs.m_polarization);
	this->m_phase.operator=(rhs.m_phase);
	this->m_cos.operator=(rhs.m_cos);

	return *this;
}


radiolocation::PureCosineWave&        radiolocation::PureCosineWave::operator=(_In_ PureCosineWave &&rhs)
{
	if (this == &rhs) return *this;

	this->m_amplitude = std::move(rhs.m_amplitude);
	this->m_frequency = std::move(rhs.m_frequency);
	this->m_init_time = std::move(rhs.m_init_time);
	this->m_samples = std::move(rhs.m_samples);
	this->m_time_step = std::move(rhs.m_time_step);
	this->m_polarization = std::move(rhs.m_polarization);
	this->m_phase.operator=(std::move(rhs.m_phase));
	this->m_cos.operator=(std::move(rhs.m_cos));

	return *this;
}

double                 radiolocation::PureCosineWave::n_cycles(_In_ const std::size_t samples, _In_ const double timestep)
{
	return (0.5 * static_cast<double>(samples)* timestep);
}

#if defined _DEBUG
void                  radiolocation::PureCosineWave::debug_print() const
{
	std::printf("PureCosineWave::debug_print\n");
	std::printf("&this->m_amplitude=%p,this->m_amplitude=%.9f\n", &this->m_amplitude, this->m_amplitude);
	std::printf("&this->m_frequency=%p,this->m_frequency=%.9f\n", &this->m_frequency, this->m_frequency);
	std::printf("&this->m_init_time=%p,this->m_init_time=%.9f\n", &this->m_init_time, this->m_init_time);
	std::printf("&this->m_time_step=%p,this->m_time_step=%.9f\n", &this->m_time_step, this->m_time_step);
	std::printf("&this->m_samples=%p,this->m_samples=%u\n", &this->m_samples, this->m_samples);
	std::printf("cos(phase(t)):     |       phase(t):     |         t:\n");
	for (std::size_t i{ 0 }; i != this->m_samples; ++i)
		std::printf("%.10f,%.10f,%.10f\n", this->m_cos[i].second, this->m_phase[i], this->m_cos[i].first);
	std::printf("End of PureCosineWave context dump\n");
}
#endif

#if defined MATHEMATICA_VISUALIZE
_Raises_SEH_exception_   void       radiolocation::PureCosineWave::save_to_file(_In_z_ const char* fname1, _In_z_ const char* fname2)
{
#if defined _DEBUG
	_ASSERTE((nullptr != fname1) && (nullptr != fname2));
#else
	if ((nullptr == fname1) || (nullptr == fname2))
		BOOST_THROW_EXCEPTION(
		invalid_pointer() <<
		boost::errinfo_api_function("PureCosineWave::save_to_file") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	FILE *fp1, *fp2;
	if ((fopen_s(&fp1, fname1, "wt") != 0) && (fopen_s(&fp2, fname2, "wt") != 0))
	{
		BOOST_THROW_EXCEPTION(
			file_error() <<
			boost::errinfo_api_function("PureCosineWave::save_to_file: Failed\n") <<
			boost::errinfo_errno(errno) <<
			boost::errinfo_at_line(__LINE__));
	}
	else
	{
		std::printf("Started writing cos(phase(t)) to file:%s\n", fname1);
		std::printf("Started writing phase(t) to file:%s\n", fname2);
		for (std::size_t i{ 0 }; i != this->m_samples; ++i)
		{
			std::fprintf(fp1, "%.15f,%.15f\n", this->m_cos.operator[](i).first, this->m_cos.operator[](i).second);
			//std::fprintf(fp2, "%.15f,%.15f\n", this->m_cos.operator[](i).first, this->m_phase.operator[](i));
		}
		std::printf("Finished writing cos(phase(t)) to file:%s\n", fname1);
		std::printf("Finished writing phase(t) to file:%s\n", fname2);
		fclose(fp1);
		fclose(fp2);
	}
}
#endif
/*
@Brief: Computes signal IQ Decomposition.
@Params: _Inout_  vector to be initialized with IQ decomposed PureCosineWave , _In_  number of threads.

@Returns:  by argument std::vector<std::pair<double,double>> IQ initialized with ExpChirpSignal IQ decomposition.
@Throws: std::runtime_error when n_threads argument is <= 0, or when  or when vector<std::pair<double,double>> IQ is empty.
*/
_Raises_SEH_exception_    void            radiolocation::PureCosineWave::quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &IQ, _In_ const int n_threads)
{
#if defined _DEBUG
	_ASSERTE(0 <= n_threads);
#else
	if (0 >= n_threads)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("PureCosineWave::quadrature_components_extraction: Failed\n") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));

#endif
	if (!(IQ.empty()))
	{
		std::size_t a_samples{ this->m_samples };
		_Field_size_(a_samples) std::vector<double> a_sine(a_samples);
		_Field_size_(a_samples) std::vector<double> a_cos(a_samples);
		_Field_size_(a_samples) std::vector<double> a_phase(this->m_phase);
		_Field_size_(a_samples) std::vector<std::pair<double, double>> a_signal(this->m_cos);
		std::size_t i;
		double sfreq{ this->n_cycles() };
		double a_init_time{ this->m_init_time };
		double a_timestep{ this->m_time_step };
		double inv_samples{ 1.0 / static_cast<double>(a_samples) };
		double delta{ 0.0 }; double t{ 0.0 };
		omp_set_num_threads(n_threads);
#if defined OMP_TIMING
		double start{ wrapp_omp_get_wtime() };
#endif
#pragma  omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t) reduction(+:a_init_time)
		for (i = 0; i < a_samples; ++i)
		{
			a_init_time += a_timestep;
			delta = static_cast<double>(i)* inv_samples;
			t = a_init_time * delta;
			a_cos.operator[](i) = 2.0 * ::cos((TWO_PI * sfreq * t) + a_phase.operator[](i));
			a_sine.operator[](i) = -2.0 * ::sin((TWO_PI * sfreq * t) + a_phase.operator[](i));
			IQ.operator[](i).operator=({ a_signal.operator[](i).second * a_cos.operator[](i),
				a_signal.operator[](i).second * a_sine.operator[](i) });

		}
#if defined OMP_TIMING
		double end{ wrapp_omp_get_wtime() };
		std::printf("PureCosineWave::quadrature_components_extraction executed in:%.15fseconds\n", end - start);

#endif
	}
	else BOOST_THROW_EXCEPTION(
		empty_vector() <<
		boost::errinfo_api_function("PureCosineWave::quadrature_components_exctraction") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
}

/*
@Brief: Computes signal complex envelope.
@Params: _In_  vector to be initialized with IQ decomposed PureCosineWave , _Out_
vector to be initialized with computed complex envelope values.

@Returns:  by argument _Out_ std::vector<double>  initialized with complex envelope values.
@Throws: std::runtime_error when IQ is empty and when both vectors size does not match.
*/
_Raises_SEH_exception_   void          radiolocation::PureCosineWave::complex_envelope(_In_ std::vector<std::pair<double, double>> &IQ, _Out_ std::vector<double> &cenvelope)
{
	if (!(IQ.empty()) && (IQ.size() == cenvelope.size()))
	{
		double j_imag{ j().imag() };
		for (int i{ 0 }; i != IQ.size(); ++i)
			cenvelope.operator[](i) = IQ.operator[](i).first + (j_imag * IQ.operator[](i).second);
	}
	else
		BOOST_THROW_EXCEPTION(
		empty_vector() <<
		boost::errinfo_api_function("PureCosineWave::complex_envelope") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
}

_Raises_SEH_exception_   void        radiolocation::PureCosineWave::analytic_signal(_In_ const std::vector<double> &cenvelope, _In_ const int n_threads)
{
#if defined _DEBUG
	_ASSERTE((0 < n_threads) && (this->m_samples == static_cast<std::size_t>(cenvelope.size())));
#else
	if ((0 >= n_threads) || (this->m_samples != static_cast<std::size_t>(cenvelope.size())))
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("PureCosineWave::analytic_wave") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	if (!(cenvelope.empty()))
	{
		std::size_t a_samples{ this->m_samples };
		double j_imag{ j().imag() };
		double cos_freq{ this->n_cycles() };
		double a_init_time{ this->m_init_time };
		double a_timestep{ this->m_time_step };
		_Field_size_(a_samples)	std::vector<double> a_cos(a_samples);
		_Field_size_(a_samples) std::vector<double> a_sine(a_samples);
		_Field_size_(a_samples) std::vector<std::pair<double, double>> a_signal(a_samples);
		_Field_size_(a_samples) std::vector<double> a_phase(this->m_phase);
		double  delta{ 0.0 }; double t{ 0.0 };
		double inv_samples{ 1.0 / static_cast<double>(a_samples) };
		std::size_t i;
		omp_set_num_threads(n_threads);
#if defined OMP_TIMING
		double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t) reduction(+:a_init_time)
		for (i = 0; i < a_samples; ++i)
		{
			a_init_time += a_timestep;
			delta = static_cast<double>(i)* inv_samples;
			t = a_init_time * delta;
			a_cos.operator[](i) = ::cos((TWO_PI * cos_freq * t) + a_phase.operator[](i));
			a_sine.operator[](i) = j_imag * ::sin((TWO_PI * cos_freq * t) + a_phase.operator[](i));
			a_signal.operator[](i).operator=({ t, (cenvelope.operator[](i) * a_cos.operator[](i)) +
				(cenvelope.operator[](i) * a_sine.operator[](i)) });
		}
#if defined OMP_TIMING
		double end{ wrapp_omp_get_wtime() };
		std::printf("PureCosineWave::analytic_signal executed in:%.15f\n", end - start);
#endif
		this->m_cos.operator=(std::move(a_signal));
	}
	else BOOST_THROW_EXCEPTION(
		empty_vector() <<
		boost::errinfo_api_function("PureCosineWave::analytic_signal: Failed") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
}

_Raises_SEH_exception_   void               radiolocation::PureCosineWave::instantaneous_frequency(_Inout_ std::vector<double> &ifrequency)
{
#if defined _DEBUG
	_ASSERTE(this->m_samples == static_cast<std::size_t>(ifrequency.size()));
#else
	if (this->m_samples != static_cast<std::size_t>(ifrequency.size()))
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("PureCosineWave::instantenous_frequency: Failed") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif

	double inv_2pi{ mathlib::MathConstants::INV_TWO_PI_DBL() };
	for (std::size_t i{ 0 }; i != this->m_samples; ++i)
	{
		double x{ this->m_cos.operator[](i).first };
		auto dt = mathlib::DyDx<double>::differentiate2([&](double arg)->double { return ((TWO_PI * this->get_frequency() * x) +
			this->get_phase()[i]); }, x, x);
		ifrequency.operator[](i) = inv_2pi * dt.get_deriv();
	}
}


std::vector<std::pair<double, double>>     radiolocation::PureCosineWave::pulse_samples() const
{
	return this->get_cos();
}

std::vector<double>                        radiolocation::PureCosineWave::pulse_phase() const
{
	return  this->get_phase();
}

std::size_t                                radiolocation::PureCosineWave::pulse_samples_count() const
{
	return this->get_samples();
}



void          radiolocation::PureCosineWave::amplitude_modulation(const double a, const double b, const double c)
{
	; // To be implemented later
}

void          radiolocation::PureCosineWave::frequency_modulation(double a, size_t n)
{
	; // To be implemented later.
}

void          radiolocation::PureCosineWave::phase_modulation(const double a, const double b, const double c, std::function<double(double, double)> &f)
{
	; // To be implemented later.
}


/*
@Brief: Derived Class implementation
*/

//Create White Gaussian Noise only.
radiolocation::AWGNoiseCosine::AWGNoiseCosine(_In_ struct AWGNCosParams const& p) :
m_oWaveformGenerator{p.WaveformGenerator}, 
m_uisamples{ p.samples },
m_dmean{ p.mean }, 
m_dvariance{ p.variance }
{
	double PI{ mathlib::MathConstants::PI_DBL() };
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	double rv1, rv2;
	//this->m_oWaveformGenerator = p.WaveformGenerator;
	this->m_AWGNCosine = std::vector<std::pair<double, double>>(this->m_uisamples);
	for (std::size_t i{ 0 }; i != this->m_uisamples; ++i)
	{
		do
		rv1 = rand_gen();
		while (rv1 == 0.0);
		rv2 = rand_gen();
		double vu1{ std::sqrt(-2.0 * std::log(rv1)) * this->m_oWaveformGenerator.operator()(2.0 * PI * rv2) };
		double vr2{ this->m_dmean + std::sqrt(this->m_dvariance) * vu1 };
		this->m_AWGNCosine.operator[](i).operator=({ vu1, vr2 });

	}
	std::printf("AWGNoiseCosine::AWGNoiseCosine called\n");
}

// Create Cosine Wave object with Additive White Gaussian Noise. 
_Raises_SEH_exception_ radiolocation::AWGNoiseCosine::AWGNoiseCosine(_In_ struct PureCosineParams const& p1, _In_ AWGNCosParams const& p2) : 
m_uisamples{ p2.samples },
m_dmean{ p2.mean }, 
m_dvariance{ p2.variance }, 
m_oWaveformGenerator{ p2.WaveformGenerator }, 
PureCosineWave(p1)
{
	//this->m_uisamples = p2.samples;
	//this->m_dmean = p2.mean;
	//this->m_dvariance = p2.variance;
	//this->m_oWaveformGenerator = p2.WaveformGenerator;
#if defined _DEBUG
	_ASSERTE(this->m_samples == this->m_uisamples);
#else
	if (this->m_samples != this->m_uisamples)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("AWGNoiseCosine::AWGNoiseCosine: Invalid argument failure") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	this->m_AWGNCosine = std::vector<std::pair<double, double>>(this->m_uisamples);
	
	double PI{ mathlib::MathConstants::PI_DBL() };
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	double rv1, rv2;
	std::plus<double> add;
	for (std::size_t i{ 0 }; i != this->m_uisamples; ++i)
	{
		do
		rv1 = rand_gen();
		while (rv1 == 0.0);
		rv2 = rand_gen();
		double vu1{ std::sqrt(-2.0 * std::log(rv1)) * this->m_oWaveformGenerator.operator()(2.0 * PI * rv2) };
		double vr2{ this->m_dmean + std::sqrt(this->m_dvariance) * vu1 };
		this->m_AWGNCosine.operator[](i).operator=({ vu1, vr2 });
		this->m_cos.operator[](i).second = add.operator()(this->m_cos.operator[](i).second, this->m_AWGNCosine.operator[](i).second);
		//std::printf("m_cos=%.9f\n", this->m_cos.operator[](i).second);
	}
}

radiolocation::AWGNoiseCosine::AWGNoiseCosine(_In_ AWGNoiseCosine && other) :
m_dmean{ std::move(other.m_dmean) },
m_dvariance{ std::move(other.m_dvariance) },
m_uisamples{ std::move(other.m_uisamples) }, 
m_oWaveformGenerator{std::move(other.m_oWaveformGenerator)}, 
m_AWGNCosine{ std::move(other.m_AWGNCosine) }
{

}

radiolocation::AWGNoiseCosine::AWGNoiseCosine(_In_ AWGNoiseCosine const& other) : 
m_dmean{ other.m_dmean }, 
m_dvariance{ other.m_dvariance },
m_uisamples{ other.m_uisamples },
m_oWaveformGenerator{ other.m_oWaveformGenerator }, 
m_AWGNCosine{ other.m_AWGNCosine }
{

}


radiolocation::AWGNoiseCosine &            radiolocation::AWGNoiseCosine::operator=(_In_ AWGNoiseCosine const& other)
{
	if (this == &other) return *this;

	this->m_dmean = other.m_dmean;
	this->m_dvariance = other.m_dvariance;
	this->m_uisamples = other.m_uisamples;
	this->m_oWaveformGenerator.operator=(other.m_oWaveformGenerator);
	this->m_AWGNCosine.operator=(other.m_AWGNCosine);
	return *this;
}

radiolocation::AWGNoiseCosine &           radiolocation::AWGNoiseCosine::operator=(_In_ AWGNoiseCosine &&other)
{
	if (this == &other) return *this;

	this->m_dmean = std::move(other.m_dmean);
	this->m_dvariance = std::move(other.m_dvariance);
	this->m_uisamples = std::move(other.m_uisamples);
	this->m_oWaveformGenerator.operator=(std::move(other.m_oWaveformGenerator));
	this->m_AWGNCosine.operator=(std::move(other.m_AWGNCosine));
	return *this;
}

double                                     radiolocation::AWGNoiseCosine::operator()(_In_ struct AWGNCosParams const& p) const
{
	double PI{ mathlib::MathConstants::PI_DBL() };
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	double rv1;
	do
	rv1 = rand_gen();
	while (rv1 == 0.0); // Prevent rv1 == 0.0;
	double rv2{ rand_gen() };
	double vu1{ std::sqrt(-2.0 * std::log(rv1)) * p.WaveformGenerator.operator()(2.0 * PI * rv2) };
	double vr2{ p.mean + std::sqrt(p.variance)  * vu1 };
	return vr2;
}

std::pair<double, double>                  radiolocation::AWGNoiseCosine::operator[](_In_ const std::size_t index)
{
	_ASSERT(index >= 0 && index <= this->m_uisamples);
	return this->m_AWGNCosine.operator[](index);
}

const   std::pair<double, double>           radiolocation::AWGNoiseCosine::operator[](_In_ const std::size_t index) const
{
	_ASSERT(index >= 0 && index <= this->m_uisamples);
	return this->m_AWGNCosine.operator[](index);
}



/*void   radiolocation::PureCosineWave::amplitude_modulation(const double modulating_amp, const double freq,const double phase)
{
	_ASSERT((std::fabs(modulating_amp) < 1.0) && (std::fabs(freq) < std::fabs(this->m_frequency)));
	
	double amplitude_average = 0.5 * (amplitude * modulating_amp);
	for (size_t i = 0; i != this->m_samples; ++i)
	{
		this->m_vec_cos.operator[](i).second += amplitude_average * (::sin(PI_TWO*(this->m_frequency + freq)*this->m_vec_cos.operator[](i).first + phase) +
			::cos(PI_TWO*(this->m_frequency - freq)*this->m_vec_cos.operator[](i).first - phase));
	}
}

void   radiolocation::PureCosineWave::phase_modulation(const double mod_amp, const double mod_freq, const double mod_index,
	std::function<double(double, double)> &mod_wave)
{
	_ASSERT(std::fabs(mod_freq) < std::fabs(this->m_frequency));
	for (size_t i = 0; i != this->m_samples; ++i)
	{
		double temp = this->m_vec_cos.operator[](i).second;
		this->m_vec_cos.operator[](i).second = ::cos(temp + mod_index * mod_wave(mod_freq, mod_amp));
	}
}*/