
#include "ExpChirp.h"

#include "../MathLib/Derivative.h"

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Exponential Frequency Modulation(Exponential Chirp) signal class - implementation.
@author: Bernard Gingold
@version:  1.0  15/09/2015

*/

/*
@Brief: static Value of 2*Pi.
*/
const double  radiolocation::ExpChirpSignal::TWO_PI{ mathlib::MathConstants::TWO_PI_DBL() };


/*
@Brief: Constructor Exponential Chirp Signal.
@Params: std::function<double(double)> & sinusoid, std::function<double(double)> & envelope, const double start frequency, const double end frequency,
const double envelope frequency, const double envelope interval, const double chirp interval, const double initial phase, const double chirp rate,
const double initial time point, const size_t number of samples, const int number of threads
@Returns: Nothing
@Throws: std::runtime_error exception when either sfreq < efreq || envfreq < efreq || 0 < n_samples
*/
radiolocation::ExpChirpSignal::ExpChirpSignal(_In_  struct ExpChirpParams const& params)
{
	create_signal(params);
}

/*
@Brief: Copy-Constructor copies  Exponential Chirp Signal to *this.
@Params: ExpChirpSignal reference
@Returns: Nothing
@Throws: Should not throw an exception.
*/
radiolocation::ExpChirpSignal::ExpChirpSignal(_In_ const ExpChirpSignal &rhs)
{
	create_signal(rhs);
}

/*
@Brief: Move-Constructor moves state of Exponential Chirp Signal to *this.
@Params: ExpChirpSignal rval reference
@Returns: Nothing
@Throws: Should not throw an exception.
*/
radiolocation::ExpChirpSignal::ExpChirpSignal(_In_ ExpChirpSignal &&rhs)
{
	create_signal(rhs);
}

/*
@Brief: Creates Exponential Chirp Signal.
@Params: std::function<double(double)> & sinusoid, std::function<double(double)> & envelope, const double start frequency, const double end frequency,
 const double envelope frequency, const double envelope interval, const double chirp interval, const double initial phase, const double chirp rate,
 const double initial time point, const size_t number of samples, const int number of threads
@Returns: Nothing
@Throws: std::runtime_error exception when either 0.0 > interval || envfreq > efreq || 32 > n_samples
*/

 _Raises_SEH_exception_ void          radiolocation::ExpChirpSignal::create_signal(_In_  struct ExpChirpParams const& params)
{
#if defined _DEBUG
	// run-time debug break-in
	_ASSERTE((0.0 < params.interval ) && (params.envfreq < params.efreq) && (32 < params.n_samples));
#else
	 if ((0.0 > params.interval) && (params.envfreq > params.efreq) && (params.n_samples <= 32))
		 BOOST_THROW_EXCEPTION(
		 invalid_value_arg() <<
		 boost::errinfo_api_function("ExpChirpSignal::create_signal") <<
		 boost::errinfo_errno(errno) <<
		 boost::errinfo_at_line(__LINE__));
#endif

	this->m_sinusoid.operator=(params.sinusoid);
	this->m_sfrequency = params.sfreq;
	this->m_efrequency = params.efreq;
	this->m_envfrequency = params.envfreq;
	this->m_env_interval = params.envinterval;
	this->m_interval = params.interval;
	this->m_init_phase = params.init_phase;
	this->m_chirp_rate = params.chirp_rate;
	this->m_init_time = params.init_time;
	this->m_samples = params.n_samples;
	this->m_polarization = JonesVector(std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 1.0));
	//Define automatic variables for OPENMP multi-threading.
	std::function<double(double)> a_sinusoid = this->m_sinusoid;
	double a_sfreq{ params.sfreq };
	double a_efreq{ params.efreq };
	double a_envfreq{ params.envfreq };
	double a_envinterval{ params.envinterval };
	double a_interval{ params.interval };
	double a_init_phase{ params.init_phase };
	double a_chirp_rate{ params.chirp_rate };
	double a_init_time{ params.init_time };
	std::size_t a_samples{ params.n_samples };
	std::size_t i;
	std::vector<std::pair<double, double>> a_chirp(a_samples);
	std::vector<double> a_envelope(a_samples);
	std::vector<double> a_phase(a_samples);
	double t{ 0.0 }; double t2{ 0.0 }; double delta{ 0.0 }; double env_step{ 0.0 };
	double inv_samples{ 1.0 / static_cast<double>(a_samples) };
	double lnK{ ::log(a_chirp_rate) };
	double inv_lnK{ 1.0 / lnK };
	omp_set_num_threads(params.n_threads);
#if defined OMP_TIMING

	double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t, t2) reduction(+:a_init_time) reduction(+:env_step)
	for (i = 0; i < a_samples; ++i)
	{
		a_init_time += a_interval;
		env_step += a_envinterval;
		delta = static_cast<double>(i)* inv_samples;
		t = a_init_time * delta;
		t2 = env_step * delta;
		a_envelope.operator[](i) = params.envelope(TWO_PI * a_envfreq * t2);
		a_phase.operator[](i) = a_init_phase + (TWO_PI * a_sfreq) * (::pow(a_chirp_rate, t) - 1) * inv_lnK;

		// Force compiler to choose move assignment operator
		a_chirp.operator[](i).operator=({ t, a_envelope.operator[](i) * a_sinusoid(a_phase.operator[](i)) });

	}
#if defined OMP_TIMING
	double end{ wrapp_omp_get_wtime() };
	std::printf("ExpChirpSignal::create_signal executed in:%.15fseconds\n", end - start);
#endif

	this->m_chirp = std::vector<std::pair<double, double>>(std::move(a_chirp));
	this->m_envelope = std::vector<double>(std::move(a_envelope));
	this->m_phase = std::vector<double>(std::move(a_phase));
 }



	





 /*
 @Brief: Performs deep copy of  Exponential Chirp Signal to *this.
 @Params: ExpChirpSignal reference
 @Returns: Nothing
 @Throws: Should not throw an exception.
 */
    void      radiolocation::ExpChirpSignal::create_signal(_In_ const ExpChirpSignal &signal)
 {
	 this->m_sfrequency = signal.m_sfrequency;
	 this->m_efrequency = signal.m_efrequency;
	 this->m_envfrequency = signal.m_envfrequency;
	 this->m_env_interval = signal.m_env_interval;
	 this->m_init_phase = signal.m_init_phase;
	 this->m_init_time = signal.m_init_time;
	 this->m_interval = signal.m_interval;
	 this->m_samples = signal.m_samples;
	 this->m_sinusoid = signal.m_sinusoid;
	 this->m_polarization = JonesVector(signal.m_polarization);
	 this->m_chirp = std::vector<std::pair<double, double>>(signal.m_chirp);
	 this->m_envelope = std::vector<double>(signal.m_envelope);
	 this->m_phase = std::vector<double>(signal.m_phase);
 }

	/*
	@Brief: Moves content of rhs  Exponential Chirp Signal to *this.
	@Params: ExpChirpSignal rval reference
	@Returns: Nothing
	@Throws: Should not throw an exception.
	*/
	void      radiolocation::ExpChirpSignal::create_signal(_In_ ExpChirpSignal &&rhs)
	{
		this->m_efrequency = std::move(rhs.m_efrequency);
		this->m_envfrequency = std::move(rhs.m_envfrequency);
		this->m_chirp_rate = std::move(rhs.m_chirp_rate);
		this->m_env_interval = std::move(rhs.m_env_interval);
		this->m_init_phase = std::move(rhs.m_init_phase);
		this->m_init_time = std::move(rhs.m_init_time);
		this->m_samples = std::move(rhs.m_samples);
		this->m_sinusoid = std::move(rhs.m_sinusoid);
		this->m_sfrequency = std::move(rhs.m_sfrequency);
		this->m_interval = std::move(rhs.m_interval);
		this->m_polarization = JonesVector(std::move(rhs.m_polarization));
		this->m_envelope =  std::vector<double>(std::move(rhs.m_envelope));
		this->m_phase = std::vector<double>(std::move(rhs.m_phase));
		this->m_chirp = std::vector<std::pair<double, double>>(std::move(rhs.m_chirp));
	}

   radiolocation::ExpChirpSignal&          radiolocation::ExpChirpSignal::operator=(_In_ const ExpChirpSignal &rhs)
 {
	 if (this == &rhs) return *this;

	
	
		 this->m_efrequency = rhs.m_efrequency;
		 this->m_sfrequency = rhs.m_sfrequency;
		 this->m_env_interval = rhs.m_env_interval;
		 this->m_envfrequency = rhs.m_envfrequency;
		 this->m_init_phase = rhs.m_init_phase;
		 this->m_init_time = rhs.m_init_time;
		 this->m_interval = rhs.m_interval;
		 this->m_samples = rhs.m_samples;
		 this->m_polarization.operator=(rhs.m_polarization);
		 this->m_sinusoid.operator=(rhs.m_sinusoid);
		 this->m_chirp.operator=(rhs.m_chirp);
		 this->m_envelope.operator=(rhs.m_envelope);
		 this->m_phase.operator=(rhs.m_phase);
		 //std::move(rhs.m_phase.begin(), rhs.m_phase.end(), this->m_phase.begin());
		 return *this;
	 }
	 
		 
		

  radiolocation::ExpChirpSignal&  radiolocation::ExpChirpSignal::operator=(_In_ ExpChirpSignal &&rhs)
 {
	 // prevent self-assignment.
	 if (this == &rhs) return *this;

	 
	
		 this->m_chirp_rate = std::move(rhs.m_chirp_rate);
		 this->m_efrequency = std::move(rhs.m_efrequency);
		 this->m_envfrequency = std::move(rhs.m_envfrequency);
		 this->m_env_interval = std::move(rhs.m_env_interval);
		 this->m_init_phase = std::move(rhs.m_init_phase);
		 this->m_init_time = std::move(rhs.m_init_time);
		 this->m_interval = std::move(rhs.m_interval);
		 this->m_samples = std::move(rhs.m_samples);
		 this->m_sinusoid = std::move(rhs.m_sinusoid);
		 this->m_sfrequency = std::move(rhs.m_sfrequency);
		 this->m_polarization.operator=(std::move(rhs.m_polarization));
		 this->m_chirp.operator=(std::move(rhs.m_chirp));
		 this->m_envelope.operator=(std::move(rhs.m_envelope));
		 this->m_phase.operator=(std::move(rhs.m_phase));

		 return *this;
	 } 
	 
 

 std::ostream&                             radiolocation::operator<<(_In_ std::ostream &os, _In_ const ExpChirpSignal &signal)
 {
	 std::setprecision(15);
	 os.scientific;
	 for (size_t i = 0; i != signal.m_samples; ++i)
	 {
		 os << "chirp t:" << signal.m_chirp.operator[](i).first << "chirp self:" << signal.m_chirp.operator[](i).second << std::endl;
		 os << "envelope:" << signal.m_envelope.operator[](i) << std::endl;
		 os << "phase:" << signal.m_phase.operator[](i) << std::endl;
	 }
	 return os;
 }

 /*
 @Brief: Computes so called chirp rate K, where K = (f1 - f0) / T.
 @Params: explicitly operates on member fields. 
 @Returns: chirp rate coefficient K.
 @Throws: no throws(noexcept)
 */
 double                                    radiolocation::ExpChirpSignal::compute_chirp_rate() const noexcept
 {
	 double K = 0.0;
	 return (K = (this->m_efrequency - this->m_sfrequency) / static_cast<double>(this->m_samples));
 }

#if  defined _DEBUG
 /*
 @Brief: pure virtual function implemented, displays state of the ExpChirpSignal object
 @Params: explicitly operates on member fields.
 @Returns: Nothing.
 @Throws: no throws.
 */
 void                                      radiolocation::ExpChirpSignal::debug_print() const
 {
	 std::printf("ExpChirpSignal::debug_print:\n");
	 std::printf("this=%p\n", this);
	 std::printf("&this->m_sfrequency=%p,this->m_sfrequency=%.9f\n", &this->m_sfrequency, this->m_sfrequency);
	 std::printf("&this->m_efrequency=%p,this->m_efrequency=%.9f\n", &this->m_efrequency, this->m_efrequency);
	 std::printf("&this->m_envfrequency=%p,this->m_envfrequency=%.9f\n", &this->m_envfrequency, this->m_envfrequency);
	 std::printf("&this->m_env_interval=%p,this->m_env_interval=%.9f\n", &this->m_env_interval, this->m_env_interval);
	 std::printf("&this->m_interval=%p,this->m_interval=%.9f\n", &this->m_interval, this->m_interval);
	 std::printf("&this->m_init_phase=%p, this->m_init_phase=%.9f\n", &this->m_init_phase, this->m_init_phase);
	 std::printf("&this->m_chirp_rate=%p,this->m_chirp_rate=%.9f\n", &this->m_chirp_rate, this->m_chirp_rate);
	 std::printf("&this->m_init_time=%p, this->m_init_time=%.9f\n", &this->m_init_time, this->m_init_time);
	 std::printf("&this->m_samples=%p, this->m_samples=%u\n", &this->m_samples, this->m_samples);
	 std::printf("&this->m_sinusoid=%p\n", &this->m_sinusoid);
	 std::printf("&this->m_polarization=%p, this->m_polarization=%.9f\n", &this->m_polarization, this->m_polarization.v().imag());
	 //std::for_each(this->m_chirp.begin(), this->m_chirp.end(), [](double& arg) {  ::sin(arg); });
	 //for (const auto& const v : this->m_chirp)
		// std::printf("v=%.9f\n",v.) 
	 std::printf("chirp self:  |   envelope:   |    phase:   |    t:\n");
	 for (size_t i = 0; i != this->m_samples; ++i)
		 std::printf("%.10f, %.10f, %.10f, %.10f\n", this->m_chirp[i].second, this->m_envelope[i], this->m_phase[i], this->m_chirp[i].first);
	 std::printf("End of ExpChirpSignal state dump\n");
 }
#endif

#if defined  MATHEMATICA_VISUALIZE
 /*
 @Brief: Save the state of ExpChirpSignal object to file.
 @Params: const char* fname1, const char* fname2, const char* fname3
 @Returns: Nothing.
 @Throws: Assertion if one of const char* pointers is invalid.
 */

 _Maybe_raises_SEH_exception_   void              radiolocation::ExpChirpSignal::save_to_file(_In_z_ const char* fname1, _In_z_ const char* fname2, _In_z_ const char* fname3)
 {
	 _ASSERT((nullptr != fname1) || (nullptr != fname2) || (nullptr != fname3));
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
 /*
 @Brief: Computes signal IQ Decomposition.
 @Params: _Inout_  vector to be initialized with IQ decomposed ExpChirpSignal , _In_  number of threads.
 
 @Returns:  by argument std::vector<std::pair<double,double>> IQ initialized with ExpChirpSignal IQ decomposition.
 @Throws: std::runtime_error when n_threads argument is <= 0, or when  or when vector<std::pair<double,double>> IQ is empty.
 */
      _Raises_SEH_exception_   void                      radiolocation::ExpChirpSignal::quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &IQ, _In_ const int n_threads)
 {
#if  defined _DEBUG
	 _ASSERTE(0 < n_threads);
#else
		  if (n_threads <= 0)
			  BOOST_THROW_EXCEPTION(
			  invalid_value_arg() <<
			  boost::errinfo_api_function("ExpChirpSignal::quadrature_components_extraction") <<
			  boost::errinfo_errno(errno) <<
			  boost::errinfo_at_line(__LINE__));
#endif

		  if (!(IQ.empty()))
		  {

			  size_t a_samples = this->m_samples;
			  std::vector<double> a_cos_part(a_samples);
			  std::vector<double> a_sin_part(a_samples);
			  std::vector<double> a_phase(this->m_phase);
			  std::vector<std::pair<double, double>> a_chirp(this->m_chirp);
			  double a_efreq = this->m_efrequency;
			  double a_timestep = this->m_init_time;
			  double a_interval = this->m_interval;
			  size_t i;
			  double inv_samples{ 1.0 / static_cast<double>(a_samples) };
			  double delta{ 0.0 }; double t{ 0.0 };
			  omp_set_num_threads(n_threads);
#if defined OMP_TIMING

			  double start{ wrapp_omp_get_wtime() };
#endif
			  // Prefetching distances should be tested in order to find an optimal distance.
			  // ICC 14 upon compiling these pragma statements classifies them as a warning and disables them
			  // I suppose that the culprit is related to usage of std::vector.
			  /*#pragma prefetch a_cos_part:0:4
			  #pragma prefetch a_cos_part:1:32
			  #pragma prefetch a_sin_part:0:4
			  #pragma prefetch a_sin_part:1:32*/
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t) reduction(+:a_timestep)

			  for (i = 0; i < a_samples; ++i)
			  {
				  a_timestep += a_interval;
				  delta = static_cast<double>(i)* inv_samples;
				  t = a_timestep * delta;
				  a_cos_part.operator[](i) = 2.0 * ::cos((TWO_PI * a_efreq * t) + a_phase.operator[](i));
				  a_sin_part.operator[](i) = -2.0 * ::sin((TWO_PI * a_efreq * t) + a_phase.operator[](i));

				  IQ.operator[](i).operator=({ a_chirp.operator[](i).second * a_cos_part.operator[](i),
					  a_chirp.operator[](i).second * a_sin_part.operator[](i) });
			  }
#if defined OMP_TIMING
			  double end{ wrapp_omp_get_wtime() };
			  std::printf("ExpChirpSignal::quadrature_components_extraction executed in:%.15fseconds\n", end - start);
#endif
		  }
		  else BOOST_THROW_EXCEPTION(
			  empty_vector() <<
			  boost::errinfo_api_function("ExpChirpSignal::quadrature_components_exception") <<
			  boost::errinfo_errno(errno) <<
			  boost::errinfo_at_line(__LINE__));
 }

	  /*
	  @Brief: Computes signal complex envelope.
	  @Params: _In_  vector to be initialized with IQ decomposed ExpChirpSignal , _Out_  
	  vector to be initialized with computed complex envelope values.

	  @Returns:  by argument _Out_ std::vector<double>  initialized with complex envelope values.
	  @Throws: std::runtime_error when IQ is empty and when both vectors size does not match.
	  */

	  _Raises_SEH_exception_  void                 radiolocation::ExpChirpSignal::complex_envelope(_In_ std::vector<std::pair<double, double>> &IQ, _Out_ std::vector<double> &envelope)
	  {
		  if (!(IQ.empty()) && (IQ.size() == envelope.size()))
		  {
			  double j_imag{ j().imag() };
			  //#pragma prefetch IQ:0:4
			  //#pragma prefetch IQ:1:16
			  for (size_t i = 0; i != IQ.size(); ++i)
				  envelope.operator[](i) = IQ.operator[](i).first + (j_imag * IQ.operator[](i).second);


		  }
		  else BOOST_THROW_EXCEPTION(
			  empty_vector() <<
			  boost::errinfo_api_function("ExpChirpSignal::complex_envelope") <<
			  boost::errinfo_errno(errno) <<
			  boost::errinfo_at_line(__LINE__));
	  }

	  /*
	  @Brief: Computes analytic signal.
	  @Params: _In_  vector to be initialized with complex envelope ExpChirpSignal , _In_ number of OPENMP threads.
	  

	  @Returns:  Modifies in-place *this.
	  @Throws: std::runtime_error when complex_envelope is empty and when both vectors size does not match.
	  */

	  _Raises_SEH_exception_     void                     radiolocation::ExpChirpSignal::analytic_signal(_In_ const std::vector<double> &complex_envelope, _In_
		  const int n_threads)
	  {
#if defined _DEBUG
		  _ASSERTE((0 < n_threads) && (this->m_samples == static_cast<std::size_t>(complex_envelope.size())));
#else
		  if ((0 < n_threads) || (this->m_samples != static_cast<std::size_t>(complex_envelope.size())))
			  BOOST_THROW_EXCEPTION(
			  invalid_value_arg() <<
			  boost::errinfo_api_function("ExpChirpSignal::analytic_signal") <<
			  boost::errinfo_errno(errno) <<
			  boost::errinfo_at_line(__LINE__));
#endif
		  if (!(complex_envelope.empty()))
		  {
			  // Define automatic variables in order to use OPENMP multi-threading where class members are used.
			  size_t a_samples{ this->m_samples };
			  double j_imag{ j().imag() };
			  double a_efreq{ this->m_efrequency };
			  double a_timestep{ this->m_init_time };
			  double a_interval{ this->m_interval };
			  std::vector<double> a_cos_part(a_samples);
			  std::vector<double> a_sin_part(a_samples);
			  std::vector<std::pair<double, double>> a_chirp(a_samples);
			  std::vector<double> a_phase(this->m_phase);
			  double delta{ 0.0 }; double t{ 0.0 };
			  double inv_samples{ 1.0 / static_cast<double>(a_samples) };
			  size_t i;
			  omp_set_num_threads(n_threads);
#if defined OMP_TIMING
			  double start{ wrapp_omp_get_wtime() };
#endif
			  // ICC 14 wupon compiling these pragma statements classifies them as a warning and disables them
			  // I suppose that the culprit is related to usage of std::vector.
			  /*#pragma prefetch  a_cos_part:0:4
							#pragma prefetch  a_cos_part:1:32
							#pragma prefetch  a_sin_part:0:4
							#pragma prefetch  a_sin_part:1:32*/
#pragma omp parallel for default(shared)  schedule(runtime) \
	private(i, delta, t) reduction(+:a_timestep)
			  for (i = 0; i < a_samples; ++i)
			  {
				  a_timestep += a_interval;
				  delta = static_cast<double>(i)* inv_samples;
				  t = a_timestep * delta;
				  a_cos_part.operator[](i) = ::cos((TWO_PI * a_efreq * t) + a_phase.operator[](i));
				  a_sin_part.operator[](i) = j_imag * ::sin((TWO_PI * a_efreq * t) + a_phase.operator[](i));
				  a_chirp.operator[](i).operator=({ t, (complex_envelope[i] * a_cos_part[i]) +
					  (complex_envelope[i] * a_sin_part[i]) });
			  }
#if defined OMP_TIMING
			  double end{ wrapp_omp_get_wtime() };
			  std::printf("ExpChirpSignal::analytic_signal executed in:%.15fseconds\n", end - start);
#endif
			  // Overwrite *this with temporary a_chirp.
			  this->m_chirp.operator=(a_chirp);
		  }
		  else BOOST_THROW_EXCEPTION(
			  empty_vector() <<
			  boost::errinfo_api_function("ExpChirpSignal::analytic_signal") <<
			  boost::errinfo_errno(errno) <<
			  boost::errinfo_at_line(__LINE__));
	  }

	 

	  _Raises_SEH_exception_  void   radiolocation::ExpChirpSignal::instantaneous_frequency(_Inout_ std::vector<double> &instfreq)
	  {
#if defined _DEBUG
		  _ASSERTE(this->m_samples == instfreq.size());
#else
		  if (this->m_samples != static_cast<std::size_t>(instfreq.size()))
			  BOOST_THROW_EXCEPTION(
			  invalid_value_arg() <<
			  boost::errinfo_api_function("ExpChirpSignal::instanteanous_frequency") <<
			  boost::errinfo_errno(errno) <<
			  boost::errinfo_at_line(__LINE__));
#endif
		  double inv_2pi{ mathlib::MathConstants::INV_PI_DBL() };
		  double efreq{ this->m_efrequency };
		  for (size_t i{ 0 }; i != this->m_samples; ++i)
		  {
			  double x{ this->m_chirp.operator[](i).first };
			  auto dt = mathlib::DyDx<double>::differentiate2([&](double arg)->double{ return ((TWO_PI*efreq*x)
				  + this->get_phase().operator[](i)); }, x, x);
			  instfreq.operator[](i) = inv_2pi * dt.get_deriv();
		  }
	  }

	  std::vector<std::pair<double, double>>    radiolocation::ExpChirpSignal::pulse_samples() const
	  {
		  return this->get_chirp();
	  }


	  std::vector<double>                       radiolocation::ExpChirpSignal::pulse_phase() const
	  {
		  return this->get_phase();
	  }


	  std::size_t                               radiolocation::ExpChirpSignal::pulse_samples_count() const
	  {
		  return this->get_samples();
	  }


	  void          radiolocation::ExpChirpSignal::amplitude_modulation(const double a, const double b, const double c)
	  {
		  ; // To be implemented later
	  }

	  void          radiolocation::ExpChirpSignal::frequency_modulation(double a, size_t n)
	  {
		  ; // To be implemented later.
	  }

	  void          radiolocation::ExpChirpSignal::phase_modulation(const double a, const double b, const double c, std::function<double(double, double)> &f)
	  {
		  ; // To be implemented later.
	  }