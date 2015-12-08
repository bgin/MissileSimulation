#include "CWCosine.h"
#include "LibExceptions.h"

// Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
// Cosine Waveform signal class - implementation.


const double  radiolocation::CWCosineSignal::TWO_PI{ mathlib::MathConstants::TWO_PI_DBL() };



radiolocation::CWCosineSignal::CWCosineSignal(_In_ struct CWCosineParams const& params)
{
	initialize(params);
}


radiolocation::CWCosineSignal::CWCosineSignal(_In_ const double init_time, _In_ const double interval, _In_ const double sfreq, _In_ const size_t n_samples)
{
	initialize(init_time, interval, sfreq, n_samples);
}


radiolocation::CWCosineSignal::CWCosineSignal(const CWCosineSignal &rhs)
{
	initialize(rhs);
}

radiolocation::CWCosineSignal::CWCosineSignal(_In_ CWCosineSignal &&rhs)
{
	initialize(rhs);
}


void     radiolocation::CWCosineSignal::initialize(_In_  struct CWCosineParams const& params)
{
#if defined _DEBUG
	_ASSERTE((0.0 < params.cfreq) && (0.0 <= params.interval) && (32 < params.n_samples));
#else
	if ((0.0 > params.cfreq) &&  (0.0 >= params.interval) && (32 > params.n_samples))
		throw std::runtime_error("Fatal Error in CWCosineSignal::initialize: Invalid Argument(s) passed\n");
#endif

	this->m_duration = params.duration;
	this->m_frequency = params.cfreq;
	this->m_efrequency = params.efreq;
	this->m_init_time = params.start_time;
	this->m_interval = params.interval;
	this->m_polarization = JonesVector(std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 1.0));
	this->m_samples = params.n_samples;

	// Copy class variables to local variables in order to run successfully OPENMP multi-threading
	
		double a_cfreq = this->m_frequency;
		double a_efreq = this->m_efrequency;
		size_t a_samples = this->m_samples;
		double a_stime = this->m_init_time;
		double a_interval = this->m_interval;
		size_t i;
		std::vector<double> a_envelope(a_samples);
		std::vector<std::pair<double, double>> a_cossignal(a_samples);
		std::vector<double> a_phase(a_samples);
		double delta{ 0.0 }; double t{ 0.0 }; double t2{ 0.0 };
		double inv_samples{ 1.0 / static_cast<double>(a_samples) };

		omp_set_num_threads(params.n_threads);
#if defined OMP_TIMING
	double	start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t, t2) reduction(+:a_stime)
		for (i = 0; i < a_samples; ++i)
		{
			a_stime += a_interval;
			delta = static_cast<double>(i)  * inv_samples;
			t = a_stime * delta;
			t2 = a_stime + delta;
			//double arg = ((TWO_PI * a_efreq * t2) + (0.25 * TWO_PI));
			a_envelope.operator[](i) = params.envelope((TWO_PI * a_efreq * t2) + (0.25 * TWO_PI));
			//std::pair<double, double> values(a_stime, a_esignal.operator[](i) * ::cos((TWO_PI* a_cfreq * t) + (0.10 * TWO_PI)));
			a_phase.operator[](i) = ((TWO_PI * params.cfreq * t) + 0.10 * TWO_PI);
			a_cossignal.operator[](i).operator=({ t, a_envelope[i] * ::cos(a_phase.operator[](i)) });
		}

#if defined OMP_TIMING
		double	end{ wrapp_omp_get_wtime() };
		std::printf("CWCosineSignal::initialize executed in:%.15fseconds\n", end - start);
#endif
		this->m_envelope = std::vector<double>(std::move(a_envelope));
		this->m_phase = std::vector<double>(std::move(a_phase));
		this->m_cos_signal = std::vector<std::pair<double, double>>(std::move(a_cossignal));


	
}

void      radiolocation::CWCosineSignal::initialize(_In_ const double init_time, _In_ const double interval, _In_ const double sfreq, _In_ const size_t n_samples)
{
#if defined _DEBUG
	_ASSERTE(32 < n_samples);
#else
	if (32 > n_samples)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("CWCosineSignal::initialize: Failure") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif

	this->m_duration = 0.0;
	this->m_efrequency = 0.0;
	this->m_samples = n_samples;
	this->m_frequency = sfreq;
	this->m_init_time = init_time;
	this->m_interval = interval;
	this->m_polarization = JonesVector();
	const double HALF_PI{ mathlib::MathConstants::HALF_PI_DBL() };
	_Field_size_(this->m_samples) this->m_envelope = std::vector<double>(this->m_samples, 0.0);
	_Field_size_(this->m_samples) this->m_phase = std::vector<double>(this->m_samples, HALF_PI);
	_Field_size_(this->m_samples) this->m_cos_signal = std::vector<std::pair<double, double>>(this->m_samples);

	for (std::size_t i{ 0 }; i != this->m_samples; ++i)
		this->m_cos_signal.operator[](i).operator=({ static_cast<double>(i), this->m_envelope[i] * ::cos(this->m_phase[i]) });
}
		
	



void      radiolocation::CWCosineSignal::initialize(const CWCosineSignal &rhs)
{
	this->m_duration = rhs.m_duration;
	this->m_frequency = rhs.m_frequency;
	this->m_efrequency = rhs.m_efrequency;
	this->m_init_time = rhs.m_init_time;
	this->m_interval = rhs.m_interval;
	this->m_polarization = JonesVector(rhs.m_polarization);
	this->m_samples = rhs.m_samples;
	this->m_envelope = std::vector<double>(rhs.m_envelope);
	this->m_phase = std::vector<double>(rhs.m_phase);
	this->m_cos_signal = std::vector<std::pair<double, double>>(rhs.m_cos_signal);
}

void      radiolocation::CWCosineSignal::initialize(_In_ CWCosineSignal &&rhs)
{
	this->m_duration = std::move(rhs.m_duration);
	this->m_efrequency = std::move(rhs.m_efrequency);
	this->m_frequency = std::move(rhs.m_frequency);
	this->m_init_time = std::move(rhs.m_init_time);
	this->m_samples = std::move(rhs.m_samples);
	this->m_polarization = JonesVector(std::move(rhs.m_polarization));
	this->m_interval = std::move(rhs.m_interval);
	this->m_envelope = std::vector<double>(std::move(rhs.m_envelope));
	this->m_phase = std::vector<double>(std::move(rhs.m_phase));
	this->m_cos_signal = std::vector<std::pair<double, double>>(std::move(rhs.m_cos_signal));
}

radiolocation::CWCosineSignal &  radiolocation::CWCosineSignal::operator=(_In_ const CWCosineSignal &rhs)
{
	if (this == &rhs) return *this;

	this->m_duration = rhs.m_duration;
	this->m_efrequency = rhs.m_efrequency;
	this->m_frequency = rhs.m_frequency;
	this->m_init_time = rhs.m_init_time;
	this->m_interval = rhs.m_interval;
	this->m_samples = rhs.m_samples;
	this->m_polarization.operator=(rhs.m_polarization);
	this->m_envelope.operator=( rhs.m_envelope);
	this->m_phase.operator=(rhs.m_phase);
	this->m_cos_signal.operator=(rhs.m_cos_signal);
	
	return *this;
	
}

radiolocation::CWCosineSignal &        radiolocation::CWCosineSignal::operator=(_In_ CWCosineSignal &&rhs)
{
	if (this == &rhs) return *this;

	this->m_duration = std::move(rhs.m_duration);
	this->m_efrequency = std::move(rhs.m_efrequency);
	this->m_frequency = std::move(rhs.m_frequency);
	this->m_init_time = std::move(rhs.m_init_time);
	this->m_interval = std::move(rhs.m_interval);
	this->m_polarization.operator=( std::move(rhs.m_polarization));
	this->m_samples = std::move(rhs.m_samples);
	this->m_phase.operator=(std::move(rhs.m_phase));
	this->m_envelope.operator=(std::move(rhs.m_envelope));
	this->m_cos_signal.operator=(std::move(rhs.m_cos_signal));

	return *this;
}

// Perform IQ Decomposition. Employ OPENMP multi-threading for IQ decomposition computation.
void        radiolocation::CWCosineSignal::quadrature_components_extraction(std::vector<std::pair<double, double>> &IQ, const int n_threads)
{
	if (!IQ.empty())
	{
		_ASSERT(0 < n_threads);
		// Define automatic variables in order to use OPENMP on class members.
		std::size_t a_samples{ this->m_samples };
		std::vector<double> a_cos_part(a_samples);
		std::vector<double> a_sin_part(a_samples);
		std::vector<std::pair<double, double>> a_cosine(this->m_cos_signal);
		double a_interval{ this->m_interval };
		double a_cfreq{ this->m_frequency };
		double inv_samples{ static_cast<double>((1 / a_samples)) };
		double step{ 0.0 }; double delta{ 0.0 }; double t{ 0.0 };
		std::size_t i;
		omp_set_num_threads(n_threads);
#if defined OMP_TIMING
		double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t)  reduction(+:step)
		for (i = 0; i < a_samples; ++i)
		{
			step += a_interval;
			delta = static_cast<double>(i)* inv_samples;
			t = step * delta;
			a_cos_part.operator[](i) = 2.0 * ::cos(TWO_PI * a_cfreq * t);
			a_sin_part.operator[](i) = -2.0 * ::sin(TWO_PI * a_cfreq * t);

			IQ.operator[](i).operator=({ a_cosine.operator[](i).second * a_cos_part.operator[](i),
				a_cosine.operator[](i).second * a_sin_part.operator[](i) });
		}
#if defined OMP_TIMING
		double	end{ wrapp_omp_get_wtime() };
		std::printf("CWCosineSignal::quadrature_components_extraction executed in:%.15fseconds\n", end - start);
#endif
	}
	else  BOOST_THROW_EXCEPTION(
		empty_vector() <<
		boost::errinfo_api_function("CWSineSignal::quadrature_components_extraction: Empty vector") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
		
}

// Compute complex envelope.
void        radiolocation::CWCosineSignal::complex_envelope(std::vector<std::pair<double, double>> &IQComponents, std::vector<double> &cmplx_envlp)
{
	if (!IQComponents.empty())
	{
		double j_imag{ j().imag() };
		// Not much work here in order to justify OPENMP multi-threading
		for (size_t i = 0; i != this->m_samples; ++i)
			cmplx_envlp.push_back(IQComponents.operator[](i).first + (j_imag * IQComponents.operator[](i).second));
	}
	else  throw std::runtime_error("Fatal Error in CWCosineSignal::complex_envelope: Empty vector!!\n");
	
}

void        radiolocation::CWCosineSignal::analytic_signal(const std::vector<double> &cmplx_envlp, const int n_threads)
{
	if (!cmplx_envlp.empty())
	{
		// TO DO:
		// Implement single thread block if small number of samples has been set.
		_ASSERT(0 < n_threads);
		// Define automatic variables for OPENMP multi-threading.
		std::size_t a_samples = this->m_samples;
		std::vector<double> a_sin_part(a_samples);
		std::vector<double> a_cos_part(a_samples);
		std::vector<std::pair<double, double>> a_cosine(this->m_cos_signal);
		double a_interval = this->m_interval;
		double a_cfreq = this->m_frequency;
		double step{ 0.0 }; double delta{ 0.0 }; double t{ 0.0 };
		
		size_t i;
		double j_imag{ j().imag() };
		omp_set_num_threads(n_threads);
#if defined OMP_TIMING
		double	start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, t, delta) reduction(+:step)
		for (i = 0; i < a_samples; ++i)
		{
			step += a_interval;
			delta = static_cast<double>(i) / static_cast<double>(a_samples);
			t = step * delta;
			a_cos_part.operator[](i) = ::cos(TWO_PI * a_cfreq * t);
			a_sin_part.operator[](i) = j_imag * ::sin(TWO_PI * a_cfreq * t);
			a_cosine.operator[](i).second = (cmplx_envlp.operator[](i) * a_cos_part.operator[](i) +
				cmplx_envlp.operator[](i) * a_sin_part.operator[](i));
		}
		this->m_cos_signal.operator=(a_cosine);
#if defined OMP_TIMING
		double	end{ wrapp_omp_get_wtime() };
		std::printf("CWCosineSignal::analytic_signal executed in:%.15fseconds\n", end - start);
#endif
	}
	else  throw std::runtime_error("Fatal Error in CWCosineSignal::analytic_signal: Empty vector!!\n");
}

std::vector<std::pair<double, double>>    radiolocation::CWCosineSignal::pulse_samples() const
{
	return this->get_cos_signal();
}

std::size_t                               radiolocation::CWCosineSignal::pulse_samples_count() const
{
	return this->get_num_samples();
}


#if defined _DEBUG
void        radiolocation::CWCosineSignal::debug_print() const
{
	std::printf("CWCosineSignal::debug_print\n");
	std::printf("CWCosineSignal object content:\n\n");
	std::printf("&CWCosineSignal=%p\n", this);
	std::printf("&this->m_frequency=%p,this->m_frequency=%.15f\n", &this->m_frequency,this->m_frequency);
	std::printf("&this->m_efrequency=%p,this->m_efreqency=%.15f\n", &this->m_efrequency,this->m_efrequency);
	std::printf("&this->m_duration=%p,this->m_duration=%.15f\n", &this->m_duration,this->m_duration);
	std::printf("&this->m_samples=%p,this->m_samples=%ull\n", &this->m_samples,this->m_samples);
	std::printf("&this->m_init_time=%p,this->m_init_time=%.15f\n", &this->m_init_time,this->m_init_time);
	std::printf("&this->m_interval=%p,this->m_interval=%.15f\n", &this->m_interval,this->m_interval);
	std::printf("r(t): |   s(t):   |      phi(t):    t:\n");
	for (size_t i = 0; i != this->m_samples; ++i)
	{
		std::printf(" %.15f, %.15f, %.15f,   %.9f\n", this->m_envelope[i], this->m_cos_signal[i].second,this->m_phase[i], this->m_cos_signal[i].first);
	}
	std::printf("End of CWCosineSignal object dump\n");
}
#endif

#if defined  MATHEMATICA_VISUALIZE
void        radiolocation::CWCosineSignal::save_to_file(const char* fname1,const char* fname2)
{
#if defined _DEBUG
	_ASSERTE((nullptr != fname1) && (nullptr != fname2));
#else
	if((nullptr == fname1) || (nullptr == fname2)) throw std::runtime_error("Fatal Error in CWCosineSignal::save_to_file: NULL POINTER\n");
#endif

	FILE *fp1, *fp2;
	if (fopen_s(&fp1, fname1, "wt") != 0)
	{
		std::printf("Failed to open file:%s, ...returning\n", fname1);
		return;
	}
	else
	{
		std::printf("Started writing dump of this->m_cos_signal to file:%s\n ", fname1);
		for (size_t i = 0; i != this->m_samples; ++i)
			fprintf(fp1, "%.9f,%.9f\n", this->m_cos_signal[i].first, this->m_cos_signal[i].second);

		std::printf("Finished writing dump of this->m_cos_signal to file:%s\n", fname1);
		fclose(fp1);
	}

	if (fopen_s(&fp2, fname2, "wt") != 0)
	{
		std::printf("Failed to open file:%s, ...returning\n", fname2);
		return;
	}
	else
	{
		std::printf("Started writing dump of this->m_envelope to file:%s\n", fname2);
		for (size_t i = 0; i != this->m_samples; ++i)
			fprintf(fp2, "%.9f,%.9f\n", this->m_cos_signal[i].first, this->m_envelope[i]);

		std::printf("Finished writing dump of this->m_envelope to file:%s\n", fname2);
		fclose(fp2);
	}
}

#endif