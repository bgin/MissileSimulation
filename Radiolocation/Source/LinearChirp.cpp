#include "LinearChirp.h"
//#include "../MathLib/MathConstants.h"
#include "../MathLib/Derivative.h"


/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Linear Frequency Modulation(Linear Chirp) signal class - implementation.
@author: Bernard Gingold
@version:  1.0  13/09/2015

*/

const  double  radiolocation::LinearChirpSignal::TWO_PI{ mathlib::MathConstants::TWO_PI_DBL() };



radiolocation::LinearChirpSignal::LinearChirpSignal(_In_  struct LinChirpParams const& params)
{
	initialize(params);
}



radiolocation::LinearChirpSignal::LinearChirpSignal(_In_ const LinearChirpSignal &rhs)
{
	initialize(rhs);
}


radiolocation::LinearChirpSignal::LinearChirpSignal(_In_ LinearChirpSignal &&rhs)
{
	initialize(rhs);
}


double         radiolocation::LinearChirpSignal::compute_chirp_rate() const noexcept
{
	double K = 0.0;
	return (K = (this->m_efrequency - this->m_sfrequency) / static_cast<double>(this->m_samples));
}


_Raises_SEH_exception_ void           radiolocation::LinearChirpSignal::initialize(_In_  struct LinChirpParams const& params)
{
#if defined _DEBUG
	_ASSERTE((std::fabs(params.einterval) < std::fabs(params.interval)) && (0.0 < params.interval) && (params.n_samples >= 32));
#else
	if ((std::fabs(params.einterval) < std::fabs(params.interval)) && (0.0 > params.interval) && (32 > params.n_samples))
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("LinearChirpSignal::initialize") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	this->m_sinusoid = params.sinusoid;
	this->m_chirp_rate = params.chirp_rate;
	this->m_efrequency = params.efreq;
	this->m_envfrequency = params.envfreq;
	this->m_init_phase = params.init_phase;
	this->m_itime = params.init_time;
	this->m_einit_time = params.einit_time;
	this->m_einterval = params.einterval;
	this->m_sfrequency = params.sfreq;
	this->m_interval = params.interval;
	this->m_samples = params.n_samples;
	this->m_polarization = JonesVector(std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 1.0));
	// Declare automatic variables for calling OPENMP multi-threading.
	double a_chirp_rate{ this->m_chirp_rate };
	double a_efreq{ this->m_efrequency };
	double a_envfreq{ this->m_envfrequency };
	double a_init_phase{ this->m_init_phase };
	double a_init_time{ this->m_itime };
	double a_sfreq{ this->m_sfrequency };
	double a_interval{ this->m_interval };
	double a_einterval{ this->m_einterval };
	double a_einit_time{ this->m_einit_time };
	double t{ 0.0 }; double t2{ 0.0 };  double delta{ 0.0 };


	std::function<double(double)> a_sinusoid = this->m_sinusoid;
	std::size_t a_samples{ this->m_samples };
	std::size_t i;
	std::vector<std::pair<double, double>> a_chirp(a_samples);
	std::vector<double> a_envelope(a_samples);
	std::vector<double> a_phase(a_samples);
	double step{ 0.0 };
	double inv_samples{ 1.0 / static_cast<double>(a_samples) };

	omp_set_num_threads(params.n_threads);
#if defined OMP_TIMING

	double start{ wrapp_omp_get_wtime() };
#endif
	// For optimal resulting LFM waveform use single thread (Disable OPENMP).
	// TO DO Fix multi-threading issues.
#pragma omp parallel for default(shared)  schedule(runtime) 	\
	private(i, delta, t, t2) reduction(+:a_init_time) reduction(+:a_einit_time)


	for (i = 0; i < a_samples; ++i)
	{
		// Create envelope vector.

		a_init_time += a_interval; // Here a_init_time must be greater when compared to step, a_init_time > step.
		a_einit_time += a_einterval;
		delta = static_cast<double>(i)* inv_samples;
		t = a_init_time * delta;
		t2 = a_einit_time * delta;
		a_envelope.operator[](i) = params.envelope(TWO_PI * a_envfreq * t2);
		// For some reason ICC 14 can't properly compile following code (K*Pi*t^2) + (2Pi*F0*t)+phi0
		// The result is similiar to linear function instead of expected quadratic one.I suspect that destructive
		// register usage could cause that.
		// Create phase argument.
		a_phase.operator[](i) = 0.5 * a_chirp_rate * t * t;	  //(0.5 * a_chirp_rate * t * t  + a_sfreq) * TWO_PI + a_init_phase;
		a_chirp.operator[](i).operator=({ t, a_envelope.operator[](i) * a_sinusoid(a_phase.operator[](i)) });
	}
#if defined OMP_TIMING
	double end{ wrapp_omp_get_wtime() };
	std::printf("LinearChirpSignal::initialize executed in:%.15fseconds\n", end - start);
#endif
	this->m_envelope = std::vector<double>(std::move(a_envelope));
	this->m_phase = std::vector<double>(std::move(a_phase));
	this->m_chirp = std::vector<std::pair<double, double>>(std::move(a_chirp));
}
		
	







  void             radiolocation::LinearChirpSignal::initialize(_In_ const LinearChirpSignal &rhs)
{

	this->m_chirp_rate = rhs.m_chirp_rate;
	this->m_efrequency = rhs.m_efrequency;
	this->m_envfrequency = rhs.m_envfrequency;
	this->m_init_phase = rhs.m_init_phase;
	this->m_interval = rhs.m_interval;
	this->m_itime = rhs.m_itime;
	this->m_einit_time = rhs.m_einit_time;
	this->m_einterval = rhs.m_einterval;
	this->m_sfrequency = rhs.m_sfrequency;
	this->m_sinusoid = rhs.m_sinusoid;
	this->m_samples = rhs.m_samples;
	this->m_polarization = JonesVector(rhs.m_polarization);
	this->m_envelope = std::vector<double>(rhs.m_envelope);
	this->m_phase = std::vector<double>(rhs.m_phase);
	this->m_chirp = std::vector<std::pair<double, double>>(rhs.m_chirp);
}

  void               radiolocation::LinearChirpSignal::initialize(_In_ LinearChirpSignal &&rhs)
  {
	  this->m_chirp_rate = std::move(rhs.m_chirp_rate);
	  this->m_efrequency = std::move(rhs.m_efrequency);
	  this->m_envfrequency = std::move(rhs.m_envfrequency);
	  this->m_init_phase = std::move(rhs.m_init_phase);
	  this->m_interval = std::move(rhs.m_interval);
	  this->m_itime = std::move(rhs.m_itime);
	  this->m_einit_time = std::move(rhs.m_einit_time);
	  this->m_einterval = std::move(rhs.m_einterval);
	  this->m_samples = std::move(rhs.m_samples);
	  this->m_sfrequency = std::move(rhs.m_sfrequency);
	  this->m_sinusoid = std::move(rhs.m_sinusoid);
	  this->m_polarization = JonesVector(std::move(rhs.m_polarization));
	  this->m_phase = std::vector<double>(std::move(rhs.m_phase));
	  this->m_envelope = std::vector<double>(std::move(rhs.m_envelope));
	  this->m_chirp = std::vector<std::pair<double, double>>(std::move(rhs.m_chirp));
  }

 radiolocation::LinearChirpSignal &   radiolocation::LinearChirpSignal::operator=(_In_ const LinearChirpSignal &rhs)
{
	if (this == &rhs) return *this;

	// Overwrite current object context with rhs context.
	
	
		this->m_chirp_rate = rhs.m_chirp_rate;
		this->m_efrequency = rhs.m_efrequency;
		this->m_envfrequency = rhs.m_envfrequency;
		this->m_init_phase = rhs.m_init_phase;
		this->m_interval = rhs.m_interval;
		this->m_itime = rhs.m_itime;
		this->m_einit_time = rhs.m_einit_time;
		this->m_einterval = rhs.m_einterval;
		this->m_samples = rhs.m_samples;
		this->m_polarization = rhs.m_polarization;
		this->m_sinusoid = rhs.m_sinusoid;
		this->m_sfrequency = rhs.m_sfrequency;
		this->m_chirp = rhs.m_chirp;
		this->m_envelope = rhs.m_envelope;
		this->m_phase = rhs.m_phase;
		return *this;
	}
	 
	
	

 radiolocation::LinearChirpSignal&     radiolocation::LinearChirpSignal::operator=(_In_ LinearChirpSignal &&rhs)
{
	if (this == &rhs) return *this;

	
		this->m_chirp_rate = std::move(rhs.m_chirp_rate);
		this->m_efrequency = std::move(rhs.m_efrequency);
		this->m_envfrequency = std::move(rhs.m_envfrequency);
		this->m_init_phase = std::move(rhs.m_init_phase);
		this->m_interval = std::move(rhs.m_interval);
		this->m_itime = std::move(rhs.m_itime);
		this->m_einit_time = std::move(rhs.m_einit_time);
		this->m_einterval = std::move(rhs.m_einterval);
		this->m_samples = std::move(rhs.m_samples);
		this->m_polarization = std::move(rhs.m_polarization);
		this->m_sfrequency = std::move(rhs.m_sfrequency);
		this->m_sinusoid = std::move(rhs.m_sinusoid);
		this->m_envelope.operator=(rhs.m_envelope);
		this->m_phase.operator=(rhs.m_phase);
		this->m_chirp.operator=(rhs.m_chirp);
		return *this;
	}
	


std::ostream &              radiolocation::operator<<(_In_ std::ostream &os, _In_ const LinearChirpSignal &signal)
{
	
	for (size_t i = 0; i != signal.m_samples; ++i)
	{
		os << "chirp t:" << signal.m_chirp.operator[](i).first << "chirp self:" << signal.m_chirp.operator[](i).second << std::endl;
		os << "envelope:" << signal.m_envelope.operator[](i) << std::endl;
		os << "phase:" << signal.m_phase.operator[](i) << std::endl;
 	}

	return os;
}


#if defined _DEBUG
void              radiolocation::LinearChirpSignal::debug_print() const
{
	std::printf("LinearChirpSignal::debug_print: \n");
	std::printf("this=%p\n", this);
	std::printf("&this->m_chirp_rate=%p,this->m_chirp_rate=%.9f\n", &this->m_chirp_rate, this->m_chirp_rate);
	std::printf("&this->m_efrequency=%p,this->m_efrequency=%.9f\n", &this->m_efrequency, this->m_efrequency);
	std::printf("&this->m_envfrequency=%p,this->m_envfrequency=%.9f\n", &this->m_envfrequency, this->m_envfrequency);
	std::printf("&this->m_sfrequency=%p,this->m_sfrequency=%.9f\n", &this->m_sfrequency, this->m_sfrequency);
	std::printf("&this->m_interval=%p,this->m_interval=%.9f\n", &this->m_interval, this->m_interval);
	std::printf("&this->m_init_phase=%p,this->m_init_phase=%.9f\n", &this->m_init_phase, this->m_init_phase);
	std::printf("&this->m_itime=%p,this->m_itime=%.9f\n", &this->m_itime, this->m_itime);
	std::printf("&this->m_samples=%p,this->m_samples=%u\n", &this->m_samples, this->m_samples);
	std::printf("&this->m_sinusoid=%p\n", &this->m_sinusoid);
	std::printf("&this->m_polarization=%p, this->m_polarization=%.9f\n", &this->m_polarization, this->m_polarization.v().imag());
	std::printf("chirp self:   |    envelope:    |    phase:    |     t: \n");
	for (size_t i = 0; i != this->m_samples; ++i)
		std::printf("%.9f, %.9f, %.9f, %.9f\n", this->m_chirp[i].second, this->m_envelope[i], this->m_phase[i], this->m_chirp[i].first);

	
	std::printf("End of LinearChirpSignal content dump\n\n");
}
#endif

 _Raises_SEH_exception_  void               radiolocation::LinearChirpSignal::quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &IQ, _In_ const int n_threads)
{
#if defined _DEBUG
	_ASSERTE(0 < n_threads);
#else
	 if(n_threads <= 0)
		 throw std::runtime_error("Fatal Error in LinearChirpSignal::quadrature_components_extraction: Invalid n_threads size\n");
#endif
	 size_t a_samples{ this->m_samples };
	std::vector<double> z1t(a_samples);
	std::vector<double> z2t(a_samples);
	std::vector<double> a_phase(this->m_phase); //phase argument.
	std::vector<std::pair<double, double>> a_chirp(this->m_chirp); // copy content of this->m_chirp to temporary vector
	double a_efreq{ this->m_efrequency };
	double a_timestep{ this->m_itime };
	double a_interval{ this->m_interval };
	size_t i;
	double delta{ 0.0 }; double t{ 0.0 };
	double inv_samples{ 1.0 / static_cast<double>(a_samples) };
	omp_set_num_threads(n_threads);
#if defined OMP_TIMING

	double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t)  reduction(+:a_timestep)
	for (i = 0; i < a_samples; ++i)
	{ 
		// Fixed an error with sin/cos function argument.
		a_timestep += a_interval; // time step interval
		delta = static_cast<double>(i) * inv_samples; // delta
		t = a_timestep * delta; // running time argument
		z1t.operator[](i) = 2.0 * ::cos((TWO_PI * a_efreq * t) + a_phase.operator[](i)); // Create IQ cos part.
		z2t.operator[](i) = -2.0 * ::sin((TWO_PI * a_efreq * t) + a_phase.operator[](i)); // Create IQ sine part.
		//std::pair<double, double> element(a_chirp.operator[](i).second * z1t.operator[](i), a_chirp.operator[](i).second *
			//z2t.operator[](i));
		// Use initializer list
		IQ.operator[](i).operator=({ a_chirp.operator[](i).second * z1t.operator[](i), a_chirp.operator[](i).second *
			z2t.operator[](i) });
	}
#if defined OMP_TIMING
	double end{ wrapp_omp_get_wtime() };
	std::printf("LinearChirpSignal::quadrature_components_extraction executed in:%.15f\n", end - start);
#endif
	// automatic vectors deallocated here!
		
}

 _Raises_SEH_exception_ void               radiolocation::LinearChirpSignal::complex_envelope(_In_ std::vector<std::pair<double, double>> &IQcomponents, _Out_ std::vector<double> &envelope)
	
{
	
	if (!(IQcomponents.empty()) && (IQcomponents.size() == envelope.size()))
	{

		// Serial loop not much use for multi-threading here.
		double j_imag{ j().imag() };
//#pragma prefetch  IQcomponents:0:4
//#pragma prefetch  IQcomponents:1:32
		for (size_t i = 0; i != this->m_samples; ++i)
		{
			envelope.operator[](i) = IQcomponents.operator[](i).first + (j_imag * IQcomponents.operator[](i).second);
		}

	}
	else
		throw std::runtime_error("Fatal Error in LinearChirpSignal::complex_envelope: Empty vector\n");
}



_Raises_SEH_exception_    void               radiolocation::LinearChirpSignal::analytic_signal(_In_ const std::vector<double> &complex_envlp,
	_In_ const int n_threads)
{
	_ASSERT((0 < n_threads) && (this->m_samples == complex_envlp.size()));
	if (!complex_envlp.empty())
	{
		// Define automatic variables in order to use OPENMP multi-threading where class members are used.
		size_t a_samples{ this->m_samples };
		double j_imag{ j().imag() };
		double a_efreq{ this->m_efrequency };
		double a_timestep{ this->m_itime };
		double a_interval{ this->m_interval };
		size_t i;
		std::vector<double> a_cos_part(a_samples);
		std::vector<double> a_sin_part(a_samples);
		std::vector<std::pair<double, double>> a_chirp(a_samples);
		std::vector<double> a_phase(this->m_phase);
		double delta{ 0.0 }; double t{ 0.0 };
		double inv_samples{ 1.0 / static_cast<double>(a_samples) };
		omp_set_num_threads(n_threads);
#if defined OMP_TIMING
		
		double	start{ wrapp_omp_get_wtime() }; // Warning !! Crude time performance measurement.
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t) reduction(+:a_timestep)
		
		for (i = 0; i < a_samples; ++i)
		{
			a_timestep += a_interval;
			delta = static_cast<double>(i)  * inv_samples;
			t = a_timestep * delta;
			a_cos_part.operator[](i) = ::cos((TWO_PI * a_efreq * t) + a_phase.operator[](i));
			a_sin_part.operator[](i) = j_imag * ::sin((TWO_PI * a_efreq * t) + a_phase.operator[](i));
			// Use std::pair Move Constructor and Move assignment.
			a_chirp.operator[](i).operator=({ t, (complex_envlp[i] * a_cos_part[i]) + (complex_envlp[i] * a_sin_part[i]) });
		}
#if defined OMP_TIMING
		double end{ wrapp_omp_get_wtime() };
		std::printf("LinearChirpSignal::analytic_signal executed in:%.15fseconds\n", end - start);
#endif
		// Overwrite *this with analytic signal(a_chirp).
		this->m_chirp = a_chirp;
	}
	else  throw std::runtime_error("Fatal Error in LinearChirpSignal::analytic_signal: Empty vector!!\n");
}

   _Maybe_raises_SEH_exception_  void               radiolocation::LinearChirpSignal::instantaneous_frequency(std::vector<double> &instfreq)
{
	   _ASSERT(this->m_samples == instfreq.size());
	   double inv_2pi{ mathlib::MathConstants::INV_PI_DBL() }; // 1/2Pi
	   double efreq{ this->m_efrequency };
	for (size_t i = 0; i != this->m_samples; ++i)
	{
		double x{ this->m_chirp[i].first }; // Should x = h be made less than x?
		
		auto dt = mathlib::DyDx<double>::differentiate2([&](double x)->double{ return((TWO_PI*efreq*x) +
			this->get_phase()[i]); }, x, x);
		instfreq[i] = inv_2pi * dt.get_deriv();
	}

}

   std::vector<std::pair<double, double>>       radiolocation::LinearChirpSignal::pulse_samples() const 
   {
	   return  this->get_chirp();
   }


   std::vector<double>                          radiolocation::LinearChirpSignal::pulse_phase() const
   {
	   return this->get_phase();
   }


   std::size_t                                  radiolocation::LinearChirpSignal::pulse_samples_count() const
   {
	   return  this->get_samples();
   }



void          radiolocation::LinearChirpSignal::amplitude_modulation(const double a, const double b, const double c)
{
	//boost::multi_array<Waveform*, 1U> SigTrain;
	//SigTrain(boost::extents[100]);
	//SigTrain[0] = new LinearChirpSignal();
	//SigTrain[0]->
	; // To be implemented later
}

void          radiolocation::LinearChirpSignal::frequency_modulation(double a, size_t n)
{
	; // To be implemented later.
}

void          radiolocation::LinearChirpSignal::phase_modulation(const double a, const double b, const double c, std::function<double(double, double)> &f)
{
	; // To be implemented later.
}


void                radiolocation::LinearChirpSignal::save_to_file(const char *fname)
{
	_ASSERT(nullptr != fname);
	FILE* fp;
	if (fopen_s(&fp, fname, "wt") != 0)
	{
		printf("Failed to open %s: file... exiting\n", fname);
		return;
	}
	else
	{
		fprintf(fp, "Dumping LinearChirpSignal object state to file:%s\n", fname);
		fprintf(fp, "this=%p\n", this);
		fprintf(fp,"&this->m_chirp_rate=%p,this->m_chirp_rate=%.9f\n", &this->m_chirp_rate, this->m_chirp_rate);
		fprintf(fp,"&this->m_efrequency=%p,this->m_efrequency=%.9f\n", &this->m_efrequency, this->m_efrequency);
		fprintf(fp,"&this->m_envfrequency=%p,this->m_envfrequency=%.9f\n", &this->m_envfrequency, this->m_envfrequency);
		fprintf(fp,"&this->m_sfrequency=%p,this->m_sfrequency=%.9f\n", &this->m_sfrequency, this->m_sfrequency);
		fprintf(fp,"&this->m_interval=%p,this->m_interval=%.9f\n", &this->m_interval, this->m_interval);
		fprintf(fp,"&this->m_init_phase=%p,this->m_init_phase=%.9f\n", &this->m_init_phase, this->m_init_phase);
		fprintf(fp,"&this->m_itime=%p,this->m_itime=%.9f\n", &this->m_itime, this->m_itime);
		fprintf(fp,"&this->m_samples=%p,this->m_samples=%u\n", &this->m_samples, this->m_samples);
		fprintf(fp, "chirp self:  |  envelope:    |      phase:      |    t:\n ");
		for (size_t i = 0; i != this->m_samples; ++i)
			fprintf(fp, "#%d,%.9f,%.9f,%.9f,%.9f\n",i, this->m_chirp[i].second, this->m_envelope[i], this->m_phase, this->m_chirp[i].first);
		
		fprintf(fp, "Finished dumping LinearChirpSignal object state to file:%s\n", fname);
		fclose(fp);
	}
}

#if defined  MATHEMATICA_VISUALIZE

  _Maybe_raises_SEH_exception_    void                                radiolocation::LinearChirpSignal::save_to_file(_In_z_ const char* fname1, _In_z_ const char* fname2, _In_z_ const char* fname3)
{
	_ASSERT((nullptr != fname1) && (nullptr != fname2) && (nullptr != fname3));
	
	
	
	FILE* fp1, *fp2, *fp3;
	if (fopen_s(&fp1, fname1, "wt") != 0)
	{
		std::printf("Failed to open file:%s, ...returning\n", fname1);
		return;
	}
	else
	{
		std::printf("Beginning dump of this->m_chirp, writing to file:%s\n", fname1);
		for (size_t i = 0; i != this->m_samples; ++i)
			fprintf(fp1, "%.9f,%.9f\n", this->m_chirp[i].first, this->m_chirp[i].second);

		std::printf("Finished writing dump of this->m_chirp to file:%s\n", fname1);
		fclose(fp1);
	}

	if (fopen_s(&fp2, fname2, "wt") != 0)
	{
		std::printf("Failed to open file:%s, ...returning\n", fname2);
		return;
	}
	else
	{
		std::printf("Beginning dump of this->m_envelope, writing to file:%s\n", fname2);
		for (size_t i = 0; i != this->m_samples; ++i)
			fprintf(fp2, "%.9f,%.9f\n", this->m_chirp[i].first, this->m_envelope[i]);

		std::printf("Finished writing dump of this->m_envelope to file:%s\n", fname2);
		fclose(fp2);
	}

	if (fopen_s(&fp3, fname3, "wt") != 0)
	{
		std::printf("Failed to open file:%s, ...returning\n", fname3);
		return;
	}
	else
	{
		std::printf("Beginning dump of this->m_phase, writing to file:%s\n", fname3);
		for (size_t i = 0; i != this->m_samples; ++i)
			fprintf(fp3, "%.9f,%.9f\n", this->m_chirp[i].first, this->m_phase[i]);

		std::printf("Finished writing dump of this-m_phase to file:%s\n", fname3);
		fclose(fp3);
	}
}
#endif