#include "CWSine.h"
//#include "../MathLib/MathConstants.h"


// Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
// Cosine Waveform signal class - implementation.

const double  radiolocation::CWSineSignal::TWO_PI = mathlib::MathConstants::TWO_PI_DBL();





radiolocation::CWSineSignal::CWSineSignal(_In_  struct CWSineParams const& params)
	
{
	initialize(params);
}


radiolocation::CWSineSignal::CWSineSignal(_In_ const double init_time, _In_ const double interval, _In_ const double sfreq, _In_ const std::size_t n_samples)
{
	initialize(init_time, interval, sfreq, n_samples);
}


radiolocation::CWSineSignal::CWSineSignal(_In_ const CWSineSignal &rhs)
{
	initialize(rhs);
}


radiolocation::CWSineSignal::CWSineSignal(_In_ CWSineSignal &&other)
{
	initialize(other);
}


radiolocation::CWSineSignal &  radiolocation::CWSineSignal::operator=(_In_ const CWSineSignal &rhs)
{
	if (this == &rhs) return *this;

	
	
	this->m_duration = rhs.m_duration;
	this->m_samples = rhs.m_samples;
	this->m_frequency = rhs.m_frequency;
	this->m_envelope_freq = rhs.m_envelope_freq;
	this->m_interval = rhs.m_interval;
	this->m_init_time = rhs.m_init_time;
	this->m_polarization = rhs.m_polarization;
	this->m_phase = rhs.m_phase;
	this->m_sine_signal = rhs.m_sine_signal;
	this->m_envelope = rhs.m_envelope;
	
	return *this;

	
}

radiolocation::CWSineSignal  &       radiolocation::CWSineSignal::operator=(_In_ CWSineSignal &&other)
{
	if (this == &other) return *this;

	this->m_duration = std::move(other.m_duration);
	this->m_envelope.operator=(std::move(other.m_envelope));
	this->m_envelope_freq = std::move(other.m_envelope_freq);
	this->m_frequency = std::move(other.m_frequency);
	this->m_init_time = std::move(other.m_init_time);
	this->m_interval = std::move(other.m_interval);
	this->m_phase.operator=(std::move(other.m_phase));
	this->m_polarization.operator=(std::move(other.m_polarization));
	this->m_samples = std::move(other.m_samples);
	this->m_sine_signal.operator=(std::move(other.m_sine_signal));

	return *this;
}

void          radiolocation::CWSineSignal::initialize(_In_  struct CWSineParams const& params)

{
	_ASSERT((0.0 < params.interval) && (32 < params.n_samples) && (0 < params.n_threads));


	this->m_duration = params.duration;
	this->m_frequency = params.sfreq;
	this->m_envelope_freq = params.efreq;

	this->m_polarization = JonesVector(std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 1.0));
	this->m_init_time = params.start_time;
	this->m_interval = params.interval;
	this->m_samples = params.n_samples; // number of std::pair<double,double> objects.
	// declaring local variables in order to be used by OPENMP.
	double s_time = this->m_init_time;
	double inter = this->m_interval;
	size_t samples = this->m_samples;
	double efreq = this->m_envelope_freq;
	double cfreq = this->m_frequency;
	std::vector<std::pair<double, double>> vsin(samples);
	std::vector<double> venv(samples);
	std::vector<double> a_phase(samples);

	size_t i;
	double delta{ 0.0 }; double t2{ 0.0 }; double t{ 0.0 };
	double inv_samples{ 1.0 / static_cast<double>(samples) };
	omp_set_num_threads(params.n_threads);
	double start{ wrapp_omp_get_wtime() };
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t, t2)  reduction(+:s_time)

	for (i = 0; i < samples; ++i)
	{
		s_time += inter;

		delta = static_cast<double>(i)* inv_samples;

		t = s_time * delta;

		t2 = s_time + delta;

		venv.operator[](i) = params.envelope((TWO_PI * efreq * t2) + (0.25 * TWO_PI));
		a_phase.operator[](i) = (TWO_PI * cfreq * t) + (0.10 * TWO_PI);
		vsin.operator[](i).operator=({ t, venv.operator[](i) * ::sin(a_phase.operator[](i)) });


		//arg = ((TWO_PI * efreq * t2) + (0.25 * TWO_PI)); //was two_pi * efreq * s_time + 0.25


	}

#if defined OMP_TIMING
	double end{ wrapp_omp_get_wtime() };
	std::printf("CWSineSignal::initialize executed in:%.15fseconds\n", end - start);
#endif
	this->m_envelope = std::vector<double>(std::move(venv));
	this->m_phase = std::vector<double>(std::move(a_phase));
	this->m_sine_signal = std::vector<std::pair<double, double>>(std::move(vsin));
}



void          radiolocation::CWSineSignal::initialize(_In_ const double init_time, _In_ const double interval, _In_ const double sfreq, _In_ const std::size_t n_samples)
{
#if defined _DEBUG
	_ASSERTE(32 < n_samples);
#else
	BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("CWSineSignal::initialize: Failed") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif

	this->m_duration = 0.0;
	this->m_envelope_freq = 0.0;
	this->m_frequency = sfreq;
	this->m_init_time = init_time;
	this->m_interval = interval;
	this->m_samples = n_samples;
	this->m_polarization = JonesVector();
	_Field_size_(this->m_samples) this->m_envelope = std::vector<double>(this->m_samples, 0.0);
	_Field_size_(this->m_samples) this->m_phase = std::vector<double>(this->m_samples, 0.0);
	_Field_size_(this->m_samples) this->m_sine_signal = std::vector<std::pair<double, double>>(this->m_samples);

	for (std::size_t i{ 0 }; i != this->m_samples; ++i)
		this->m_sine_signal.operator[](i).operator=({ static_cast<double>(i), this->m_envelope[i] * ::sin(this->m_phase[i]) });

}
	









	

	


void           radiolocation::CWSineSignal::initialize(_In_ const CWSineSignal &rhs)
{
	
	
	this->m_duration = rhs.m_duration;
	this->m_samples = rhs.m_samples;
	this->m_frequency = rhs.m_frequency;
	this->m_envelope_freq = rhs.m_envelope_freq;
	this->m_interval = rhs.m_interval;
	this->m_init_time = rhs.m_init_time;
	this->m_polarization = JonesVector(rhs.m_polarization);
	this->m_phase = std::vector<double>(rhs.m_phase);
	this->m_envelope = std::vector<double>(rhs.m_envelope);
	this->m_sine_signal = std::vector<std::pair<double, double>>(rhs.m_sine_signal);
}

void        radiolocation::CWSineSignal::initialize(_In_  CWSineSignal &&other)
{
	this->m_duration = std::move(other.m_duration);
	this->m_envelope.operator=(std::move(other.m_envelope));
	this->m_envelope_freq = std::move(other.m_envelope_freq);
	this->m_frequency = std::move(other.m_frequency);
	this->m_init_time = std::move(other.m_init_time);
	this->m_interval = std::move(other.m_interval);
	this->m_phase = std::vector<double>(std::move(other.m_phase));
	this->m_polarization = JonesVector(std::move(other.m_polarization));
	this->m_samples = std::move(other.m_samples);
	this->m_sine_signal = std::vector<std::pair<double,double>>(std::move(other.m_sine_signal));
}




void       radiolocation::CWSineSignal::quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &qdrtr_cmpnts, _In_  const int n_threads)
{
	if (!qdrtr_cmpnts.empty()){
		_ASSERT(0 < n_threads);
		// Define automatic variables for OPENMP multi-threading.
		std::size_t a_samples = this->m_samples;
		std::vector<double> cos_part(a_samples, 0.0); // initializing sine and cosine components(multipliers) of decomposed signal.
		std::vector<double> sine_part(a_samples, 0.0);// initializing sine and cosine components(multipliers) of decomposed signal.
		std::vector<std::pair<double, double>> a_sine(this->m_sine_signal); // automatic copy of this->m_sine_signal.
		double a_interval = this->m_interval;
		double a_cfreq = this->m_frequency;
		double start, end;
		double step = 0.0; double delta = 0.0; double t = 0.0;
		size_t i;

		omp_set_num_threads(n_threads);
#if defined OMP_TIMING

		start = wrapp_omp_get_wtime();
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t)  reduction(+:step)

		for (i = 0; i < a_samples; ++i)
		{
			step += a_interval;
			delta = static_cast<double>(i) / static_cast<double>(a_samples);
			t = step * delta;
			cos_part.operator[](i) = 2.0 * ::cos(TWO_PI * a_cfreq * t);
			sine_part.operator[](i) = -2.0 * ::sin(TWO_PI * a_cfreq * t);
			std::pair<double, double> element(a_sine.operator[](i).second * cos_part.operator[](i),
				a_sine.operator[](i).second * sine_part.operator[](i));
			qdrtr_cmpnts[i] = element;

		}

#if defined OMP_TIMING
		end = wrapp_omp_get_wtime();
		std::printf("CWSineSignal::quadrature_component_extraction executed in: %.15fsec\n", end - start);
#endif
	}
	else throw std::runtime_error("Fatal Error in CWSineSignal::quadrature_components_extraction: Empty vector\n");

}

	


 void        radiolocation::CWSineSignal::complex_envelope(std::vector<std::pair<double, double>> &qdrtr_cmpnts, std::vector<double> &cmplx_envlp)
	
 {
	 double j_imag = j().imag();
	 for (size_t i = 0; i != this->m_samples; ++i)
	 { // Not much work here to justify use of multi-threading.
		 cmplx_envlp.push_back(qdrtr_cmpnts.operator[](i).first + (j_imag * qdrtr_cmpnts.operator[](i).second));
	 }
 }

 
 // Compute analytic signal. this get overwritten with the result.
 void         radiolocation::CWSineSignal::analytic_signal(const std::vector<double> &cmplx_envlp, const int n_threads)
 {
	 // TO DO:
	 // Implement single thread block if small number of samples has been set.
	 if (!cmplx_envlp.empty()){
		 _ASSERT(0 < n_threads);
		 // Prepare automatic variable for OMP multi-threading.
		 size_t a_samples = this->m_samples;
		 std::vector<double> sin_part(a_samples, 0.0);
		 std::vector<double> cos_part(a_samples, 0.0);
		 std::vector<std::pair<double, double>> a_sine(this->m_sine_signal);
		 double a_cfreq = this->m_frequency;
		 double a_interval = this->m_interval;
		 double step = 0.0; double delta = 0.0; double t = 0.0;
		 size_t i;
		 double j_imag = j().imag();
		 double start, end;
		
		 omp_set_num_threads(n_threads);
#if defined OMP_TIMING
		 start = wrapp_omp_get_wtime();
#endif
#pragma omp parallel for default(shared)  schedule(runtime) \
	private(i, delta, t)  reduction(+:step)
		 for ( i = 0; i < a_samples; ++i)
		 {
			 step += a_interval;
			 delta = static_cast<double>(i) / static_cast<double>(a_samples);
			 t = step * delta;
			 sin_part.operator[](i) = j_imag * ::sin(TWO_PI * a_cfreq * t);
			 cos_part.operator[](i) = ::cos(TWO_PI * a_cfreq * t);
			 a_sine.operator[](i).second = (cmplx_envlp[i] * cos_part[i]) + (cmplx_envlp[i] * sin_part[i]);
		 }
		
		 this->m_sine_signal = a_sine;
#if defined OMP_TIMING
		 end = wrapp_omp_get_wtime();
		 std::printf("CWSineSignal::analytic_signal executed in %.15fsecond\n", end - start);
#endif
		/* for (size_t i = 0; i != this->m_samples; ++i)
		 {
			 this->m_sine_signal.operator[](i).second = (cmplx_envlp.operator[](i) * cos_part.operator[](i)) + (cmplx_envlp.operator[](i) * sin_part.operator[](i));
		 }*/
	 }
	 else  throw std::runtime_error("Fatal Error in CWSineSignal::analytic_signal: Empty vector\n");
		 
 }

 std::vector<std::pair<double, double>>    radiolocation::CWSineSignal::pulse_samples() const
 {
	 return  this->get_sine_signal();
 }

 std::vector<double>                       radiolocation::CWSineSignal::pulse_phase() const
 {
	 return this->get_phase();
 }

 std::size_t                               radiolocation::CWSineSignal::pulse_samples_count() const
 {
	 return this->get_samples_count();
 }


 void          radiolocation::CWSineSignal::amplitude_modulation(const double a, const double b, const double c)
 {
	 ; // To be implemented later
 }

 void          radiolocation::CWSineSignal::frequency_modulation(double a, size_t n)
 {
	 ; // To be implemented later.
 }

 void          radiolocation::CWSineSignal::phase_modulation(const double a, const double b, const double c, std::function<double(double, double)> &f)
 {
	 ; // To be implemented later.
 }

 void          radiolocation::CWSineSignal::instantaneous_frequency(std::vector<double> &instfreq)
 {
	 ; // To be implemented later.
 }

#if defined _DEBUG
 void          radiolocation::CWSineSignal::debug_print() const
 {
	 std::printf("CWSineSignal::debug_print: \n");
	 
	 std::printf("this=%p\n", this);
	 std::printf("&this->m_frequency=%p,this->m_frequency=%.9f\n", &this->m_frequency, this->m_frequency);
	 std::printf("&this->m_envelope_freq=%p,this->m_envelope_freq=%.9f\n", &this->m_envelope_freq, this->m_envelope_freq);
	 std::printf("&this->m_duration=%p,this->m_duration=%.15f\n", &this->m_duration, this->m_duration);
	 std::printf("&this->m_init_time=%p, this->m_init_time=%.15f\n", &this->m_init_time, this->m_init_time);
	 std::printf("&this->m_interval=%p, this->m_interval=%.15f\n", &this->m_interval, this->m_interval);
	 std::printf("&this->m_samples=%p, this->m_samples=%u\n", &this->m_samples, this->m_samples);
	 std::printf("&this->m_envelope=%p\n", &this->m_envelope);
	 std::printf("&this->m_phase=%p\n", &this->m_phase);
	 std::printf("&this->m_sine_signal=%p\n", &this->m_sine_signal);
	 std::printf("r(t): |     s(t): |     phi(t): |  t:  \n");
	 for (size_t i = 0; i != this->m_samples; ++i)
	 {
		 std::printf("%.15f,%.15f, %.15f, %.15f\n",i, this->m_envelope[i], this->m_sine_signal[i].second, this->m_phase[i], this->m_sine_signal[i].first);
	 }
	 std::printf("End of CWSineSignal object dump\n");
 }
#endif

#if  defined MATHEMATICA_VISUALIZE
 void                radiolocation::CWSineSignal::save_to_file(const char *fname, const char* fname2) const
 {
#if defined _DEBUG
	 _ASSERTE((nullptr != fname) && (nullptr != fname2));
#else
	 if((nullptr == fname1) || (nullptr == fname2)) throw std::runtime_error("Fatal Error in CWSineSignal::save_to_file: NULL POINTER\n");
#endif
	 FILE* fp, *fp2;
	 if (fopen_s(&fp, fname, "wt") != 0)
	 {
		 printf("Failed to open %s: file... exiting\n", fname);
		 return;
	 }
	 else
	 {
		 std::printf("Begining dump of this->m_sine_signal to file:%s\n", fname);
		
		for (size_t i = 0; i != this->m_samples; ++i)
		 {
			 fprintf(fp, "%.15f, %.15f\n", this->m_sine_signal[i].first, this->m_sine_signal[i].second );
		 }
		
		 std::printf("Completed dump of this->m_sine_signal to file:%s\n", fname);
		
		fclose(fp);
	 }

	 if (fopen_s(&fp2, fname2, "wt") != 0)
	 {
		 std::printf("Failed to open file: %s, ...returning\n", fname2);
		 return;
	 }
	 else
	 {
		 std::printf("Beginning dump of this->m_envelope component to file:%s\n", fname2);
		 for (size_t i = 0; i != this->m_samples; ++i)
		 {
			 fprintf(fp2, "%.15f,%.15f\n", this->m_sine_signal[i].first, this->m_envelope[i]);
		 }
		 std::printf("Completed dump of this->m_envelope to file:%s", fname2);
		 fclose(fp2);
	 }
 }
#endif