#include "SquareWaveModulated.h"
//#include "../MathLib/MathConstants.h"
#include "../MathLib/Derivative.h"
//#include "LibExceptions.h"
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Square Wave Modulated signal class - implementation.
@author: Bernard Gingold
@version:  1.0  25/09/2015

*/

/*
@Brief: static variable 2*PI 
*/
const  double  radiolocation::SquareWaveMSignal::TWO_PI{ mathlib::MathConstants::TWO_PI_DBL() };

/*
@Brief: Constructor Creates Modulated Square Wave Signal.
@Params: std::function<double(double) generating function, const double envelope initial time point, const double signal initial time point, 
const double time point interval increment,const double envelope increment interval, const double signal initial phase, const size_t number of samples,
const int number of OPENMP threads.
@Returns: Nothing
@Throws: BOOST_THROW_EXCEPTION exception when either sfreq > envfreq || sinterval > einterval || 0 > n_threads.
*/
_Raises_SEH_exception_  radiolocation::SquareWaveMSignal::SquareWaveMSignal(_In_  struct SquareWaveMParams const& p)
{
	create_signal(p);
}

/*
@Brief: Constructor Copies Modulated Square Wave Signal.
@Params: const SquareWaveMSignal & reference
@Returns: Nothing
@Throws: no throws.
*/
radiolocation::SquareWaveMSignal::SquareWaveMSignal(_In_ const SquareWaveMSignal& rhs)
{
	create_signal(rhs);
}

/*
@Brief: Constructor Moves Pure Square Wave Signal.
@Params : SquareWaveSignal && rval reference
@Returns : Nothing
@Throws : no throws.
*/
radiolocation::SquareWaveMSignal::SquareWaveMSignal(_In_ SquareWaveMSignal&& rhs)
{
	create_signal(rhs);
}

/*
@Brief: Member function Constructs Modulated Square Wave Signal. Called from Constructor.
@Params:std::function<double(double) generating function, const double envelope initial time point, const double signal initial time point, 
const double time point interval increment,const double envelope increment interval, const double signal initial phase, const size_t number of samples,
const int number of OPENMP threads.
@Returns: Nothing
@Throws: BOOST_THROW_EXCEPTION exception when either sfreq > envfreq || sinterval > einterval || 0 > n_threads.
*/

_Raises_SEH_exception_   void      radiolocation::SquareWaveMSignal::create_signal(_In_  struct SquareWaveMParams const& p)
{

#if defined _DEBUG
	_ASSERTE((32 <= p.n_samples) && (std::fabs(p.sinterval) > std::fabs(p.einterval)) && (p.n_threads > 0));
#else
	if ( (32 > p.n_samples)|| (std::fabs(p.sinterval) < std::fabs(p.eniterval)) || (0 > n_threads))
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("SquareWaveMSignal::create_signal") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	// Initialize class members:
	this->m_gen_function.operator=(p.gen_function);
	this->m_sfrequency = p.sfreq;
	this->m_envfrequency = p.envfreq;
	this->m_init_phase = p.init_phase;
	this->m_sinit_time = p.sinit_time;
	this->m_einit_time = p.einit_time;
	this->m_sinterval = p.sinterval;
	this->m_einterval = p.einterval;
	this->m_samples = p.n_samples;
	this->m_polarization = JonesVector(std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 1.0));
	// Define automatic variables for OPENMP multi-threading.
	std::function<double(double)> a_gen_function = this->m_gen_function;
	double a_sfreq{ p.sfreq };
	double a_envfreq{ p.envfreq };
	double a_init_phase{ p.init_phase };
	double a_sinit_time{ p.sinit_time };
	double a_einit_time{ p.einit_time };
	double a_sinterval{ p.sinterval };
	double a_einterval{ p.einterval };
    std::size_t a_samples{ p.n_samples };
	std::vector<std::pair<double, double>> a_square_wave(a_samples);
	std::vector<double> a_envelope(a_samples);
	std::vector<double> a_phase(a_samples);
	std::size_t i;
	double t1{ 0.0 }; double t2{ 0.0 }; double delta{ 0.0 };
	double inv_samples{ 1.0 / static_cast<double>(a_samples) };
	omp_set_num_threads(p.n_threads);
#if defined OMP_TIMING
	double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, t1, t2, delta) reduction(+:a_sinit_time) reduction(+:a_einit_time)
	for (i = 0; i < a_samples; ++i)
	{
		a_sinit_time += a_sinterval;
		a_einit_time += a_einterval; // must be: a_einit_time < a_sinit_time in order to preserve smaller frequency of envelope signal r(t).
		delta = static_cast<double>(i) * inv_samples;
		t1 = a_sinit_time * delta;
		t2 = a_einit_time * delta;
		a_envelope.operator[](i) = a_gen_function(TWO_PI * a_envfreq * t2);
		a_phase.operator[](i) = ::sin((TWO_PI * a_sfreq * t1) + a_init_phase);
		a_square_wave.operator[](i).operator=({ t1, a_envelope[i] * (signum(std::floor(a_phase[i]))) });
	}
#if defined OMP_TIMING
	double end{ wrapp_omp_get_wtime() };
	std::printf("SquareWaveMSignal::create_signal executed in:%.15fseconds\n", end - start);
#endif
	this->m_phase = std::vector<double>(std::move(a_phase));
	this->m_envelope = std::vector<double>(std::move(a_envelope));
	this->m_square_wave = std::vector<std::pair<double, double>>(std::move(a_square_wave));
}

/*
@Brief: Member function Copies Modulated Square Wave Signal.
@Params: const SquareWaveSignal & reference
@Returns: initializes *this with the state of const SquareWaveMSignal reference
@Throws: no throws.
*/
void               radiolocation::SquareWaveMSignal::create_signal(_In_ const SquareWaveMSignal &rhs)
{
	this->m_einit_time = rhs.m_einit_time;
	this->m_einterval = rhs.m_einterval;
	this->m_envfrequency = rhs.m_envfrequency;
	this->m_gen_function = rhs.m_gen_function;
	this->m_init_phase = rhs.m_init_phase;
	this->m_samples = rhs.m_samples;
	this->m_sfrequency = rhs.m_sfrequency;
	this->m_sinit_time = rhs.m_sinit_time;
	this->m_sinterval = rhs.m_sinterval;
	this->m_polarization = JonesVector(rhs.m_polarization);
	this->m_envelope = std::vector<double>(rhs.m_phase);
	this->m_phase = std::vector<double>(rhs.m_phase);
	this->m_square_wave = std::vector<std::pair<double, double>>(rhs.m_square_wave);
}

/*
@Brief: Member function moves Modulated Square Wave Signal.
@Params: const SquareWaveMSignal & reference
@Returns: initializes *this with the state and content of the  SquareWaveMSignal rval reference
@Throws: no throws.
*/

void               radiolocation::SquareWaveMSignal::create_signal(_In_ SquareWaveMSignal&& rhs)
{
	this->m_einit_time = std::move(rhs.m_einit_time);
	this->m_einterval = std::move(rhs.m_einterval);
	this->m_envfrequency = std::move(rhs.m_envfrequency);
	this->m_gen_function = std::move(rhs.m_gen_function);
	this->m_init_phase = std::move(rhs.m_init_phase);
	this->m_samples = std::move(rhs.m_samples);
	this->m_sfrequency = std::move(rhs.m_sfrequency);
	this->m_sinit_time = std::move(rhs.m_sinit_time);
	this->m_sinterval = std::move(rhs.m_sinterval);
	this->m_polarization = JonesVector(std::move(rhs.m_polarization));
	this->m_envelope = std::vector<double>(std::move(rhs.m_envelope));
	this->m_phase = std::vector<double>(std::move(rhs.m_phase));
	this->m_square_wave = std::vector<std::pair<double, double>>(std::move(rhs.m_square_wave));
	
}
/*
@Brief: operator copy - assignment
@Params: reference to const SquareWaveMSignal object.
@Returns: Modified *this state.
@Throws: Nothing.
*/
radiolocation::SquareWaveMSignal&          radiolocation::SquareWaveMSignal::operator=(_In_ const SquareWaveMSignal &rhs)
{
	// prevent self-assignment
	if (this == &rhs) return *this;

	this->m_einit_time = rhs.m_einit_time;
	this->m_einterval = rhs.m_einterval;
	this->m_envfrequency = rhs.m_envfrequency;
	this->m_gen_function = rhs.m_gen_function;
	this->m_init_phase = rhs.m_init_phase;
	this->m_samples = rhs.m_samples;
	this->m_sfrequency = rhs.m_sfrequency;
	this->m_sinit_time = rhs.m_sinit_time;
	this->m_sinterval = rhs.m_sinterval;
	this->m_polarization.operator=(rhs.m_polarization);
	this->m_envelope.operator=(rhs.m_envelope);
	this->m_phase.operator=(rhs.m_phase);
	this->m_square_wave.operator=(rhs.m_square_wave);

	return *this;
}



/*
@Brief: operator move - assignment
@Params: rval reference to  SquareWaveMSignal object.
@Returns: Modified *this state.
@Throws: Nothing.
*/
radiolocation::SquareWaveMSignal&            radiolocation::SquareWaveMSignal::operator=(_In_ SquareWaveMSignal &&rhs)
{
	this->m_einit_time = std::move(rhs.m_einit_time);
	this->m_einterval = std::move(rhs.m_einterval);
	this->m_envfrequency = std::move(rhs.m_envfrequency);
	this->m_gen_function = std::move(rhs.m_gen_function);
	this->m_init_phase = std::move(rhs.m_init_phase);
	this->m_samples = std::move(rhs.m_samples);
	this->m_sfrequency = std::move(rhs.m_sfrequency);
	this->m_sinterval = std::move(rhs.m_sinterval);
	this->m_sinit_time = std::move(rhs.m_sinit_time);
	this->m_polarization.operator=(std::move(rhs.m_polarization));
	this->m_envelope.operator=(rhs.m_envelope);
	this->m_phase.operator=(rhs.m_phase);
	this->m_square_wave.operator=(rhs.m_square_wave);

	return *this;
}

/*
@Brief: operator<<
@Params: reference to std::ostream, reference to  SquareWaveMSignal object.
@Returns: reference to std::ostream.
@Throws: Nothing.
*/
std::ostream&            radiolocation::operator<<(_In_ std::ostream& os, _In_ const SquareWaveMSignal &signal)
{
	/*std::for_each(signal.m_square_wave.begin(), signal.m_square_wave.end(), std::ostream_iterator<std::pair<double, double>>(std::cout, "\n"));
	std::for_each(signal.m_envelope.begin(), signal.m_envelope.end(), std::ostream_iterator<double>(std::cout, "\n"));
	std::for_each(signal.m_phase.begin(), signal.m_phase.end(), std::ostream_iterator<double>(std::cout, "\n"));*/
	for (std::size_t i{ 0 }; i != signal.m_samples; ++i)
	{
		std::setprecision(15);
		os.scientific;
		os << "t:" << signal.m_square_wave[i].first << "s(t):" << signal.m_square_wave[i].second << "r(t):" <<
			signal.m_envelope[i] << "phi(t):" << signal.m_phase[i] << std::endl;
	}
	return os;
}

#if defined _DEBUG
/*
@Brief: pure virtual function implemented, displays state of the SquareWaveMSignal object
@Params: explicitly accesses member fields.
@Returns: Nothing.
@Throws: no throws.
*/
void                   radiolocation::SquareWaveMSignal::debug_print() const
{
	std::printf("SquareWaveMSignal::debug_print\n");
	std::printf("&this->m_samples=%p,this->m_samples=%d\n", &this->m_samples, this->m_samples);
	std::printf("&this->m_sfrequency=%p,this->m_samples=%.9f\n", &this->m_sfrequency, this->m_sfrequency);
	std::printf("&this->m_envfrequency=%p,this->m_envfrequency=%.9f\n", &this->m_envfrequency, this->m_envfrequency);
	std::printf("&this->m_init_phase=%p,this->m_init_phase=%.9f\n", &this->m_init_phase, this->m_init_phase);
	std::printf("&this->m_sinit_time=%p,this->m_sinit_time=%.9f\n", &this->m_sinit_time, this->m_sinit_time);
	std::printf("&this->m_einit_time=%p,this->m_einit_time=%.9f\n", &this->m_einit_time, this->m_einit_time);
	std::printf("&this->m_sinterval=%p,this->m_sinterval=%.9f\n", &this->m_sinterval, this->m_sinterval);
	std::printf("&this->m_einterval=%p,this->m_einterval=&.9f\n", &this->m_einterval, this->m_einterval);
	std::printf("&this->m_gen_function=%p\n", &this->m_gen_function);
	std::printf("s(t):     |     r(t):       |        phi(t):         |           t:\n");
	for (size_t i{ 0 }; i != this->m_samples; ++i)
		std::printf("%.10f,%.10f,%.10f,%.10f\n", this->m_square_wave[i].second, this->m_envelope[i], this->m_phase[i], this->m_square_wave[i].first);

	std::printf("End of SquareWaveMSignal content dump\n");
}
#endif

#if  defined  MATHEMATICA_VISUALIZE
/*
@Brief: Class member function writes  state of the SquareWaveMSignal object to files.
@Params : explicitly operates on member fields.
@Returns : Nothing.
@Throws : BOOST_THROW_EXCEPTION if fname1 == nullptr || fname2 == nullptr or if fopen_s failed to write to file.
*/

_Raises_SEH_exception_       void     radiolocation::SquareWaveMSignal::save_to_file(_In_z_ const char* fname1, _In_z_ const char* fname2, _In_z_ const char* fname3) const
{
#if defined  _DEBUG
	_ASSERTE((nullptr != fname1) && (nullptr != fname2) && (nullptr != fname3));
#else
	if ((fname1 == nullptr) || (fname2 == nullptr) || (fname3 == nullptr))
		BOOST_THROW_EXCEPTION(
		invalid_pointer() <<
		boost::errinfo_api_function("SquareWaveMSignal::save_to_file") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif

	FILE *fp1, *fp2, *fp3;
	if ((fopen_s(&fp1, fname1, "wt") != 0) || (fopen_s(&fp2, fname2, "wt") != 0) || (fopen_s(&fp3, fname3, "wt") != 0))
	{
		BOOST_THROW_EXCEPTION(
			file_open_error() <<
			boost::errinfo_api_function("SquareWaveMSignal::save_to_file") <<
			boost::errinfo_errno(errno) <<
			boost::errinfo_at_line(__LINE__));
	}
	else
	{
		std::printf("Started writing this->m_squar_wave to file:%s\n", fname1);
		std::printf("Started writing this->m_envelope to file:%s\n", fname2);
		std::printf("Started writing this->m_phase  to file:%s\n", fname3);
		for (std::size_t i{ 0 }; i != this->m_samples; ++i)
		{
			fprintf(fp1, "%.15f,%.15f\n", this->m_square_wave[i].first, this->m_square_wave[i].second);
			fprintf(fp2, "%.15f,%.15f\n", this->m_square_wave[i].first, this->m_envelope[i]);
			fprintf(fp3, "%.15f,%.15f\n", this->m_square_wave[i].first, this->m_phase[i]);
		}
		std::printf("Finished writing this->m_square_wave to file:%s\n", fname1);
		std::printf("Finished writing this->m_envelope to file:%s\n", fname2);
		std::printf("Finished writing this->m_phase  to file:%s\n", fname3);
		fclose(fp1);
		fclose(fp2);
		fclose(fp3);
	}
}
#endif

/*
@Brief: Computes signal IQ Decomposition.
@Params: _Inout_  vector to be initialized with IQ decomposed SquareWaveMSignal , _In_  number of threads.

@Returns:  by argument std::vector<std::pair<double,double>> IQ initialized with SquareWaveSignal IQ decomposition.
@Throws: std::runtime_error when n_threads argument is <= 0 or when vector<std::pair<double,double>> IQ is empty.
*/
_Raises_SEH_exception_    void          radiolocation::SquareWaveMSignal::quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &IQ, _In_ const int n_threads)
{
#if defined _DEBUG
	_ASSERTE(0 < n_threads);
#else
	if (0 >= n_threads)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("SquareWaveMSignal::quadrature_components_extraction") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	if (!(IQ.empty()))
	{
		size_t a_samples{ this->m_samples };
		std::vector<double> a_cos(a_samples);
		std::vector<double> a_sin(a_samples);
		std::vector<double> a_phase(this->m_phase);
		std::vector<std::pair<double, double>> a_square_wave(this->m_square_wave);
		std::size_t i;
		double a_init_time{ this->m_sinit_time };
		double a_interval{ this->m_sinterval };
		double t{ 0.0 }; double delta{ 0.0 };
		double inv_samples{ 1.0 / static_cast<double>(a_samples) };
		omp_set_num_threads(n_threads);
#if defined OMP_TIMING
		double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, t, delta) reduction(+:a_init_time)
		for (i = 0; i < a_samples; ++i)
		{
			a_init_time += a_interval;
			delta = static_cast<double>(i)* inv_samples;
			t = delta * a_init_time;
			a_cos.operator[](i) = 2.0 * ::cos((TWO_PI * t) + a_phase.operator[](i));
			a_sin.operator[](i) = -2.0 * ::sin((TWO_PI * t) + a_phase.operator[](i));
			// Force compiler to use std::pair<double,double>> &&
			IQ.operator[](i).operator=({ a_square_wave.operator[](i).second * a_cos.operator[](i),
				a_square_wave.operator[](i).second * a_sin.operator[](i) });
		}
#if defined OMP_TIMING
		double end{ wrapp_omp_get_wtime() };
		std::printf("SqureWaveMSignal::quadrature_components_extraction exexuted in:%.15fseconds\n", end - start);
#endif
	}
	else  BOOST_THROW_EXCEPTION(
		empty_vector() <<
		boost::errinfo_api_function("SquareWaveMSignal::quadrature_components_extraction") <<
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
void            radiolocation::SquareWaveMSignal::complex_envelope(_In_ std::vector<std::pair<double, double>> &IQ, _Out_ std::vector<double> &envelope)
{
	if (!(IQ.empty()) && (IQ.size() == envelope.size()))
	{
		double j_imag{ j().imag() };
		for (std::size_t i{ 0 }; i != IQ.size(); ++i)
			envelope.operator[](i) = IQ.operator[](i).first + (j_imag * IQ.operator[](i).second);
	}
	else BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("SquareWaveMSignal::complex_envelope") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
}

/*
@Brief: Computes analytic signal.
@Params: _In_  vector to be initialized with complex envelope ExpChirpSignal , _In_ number of OPENMP threads.


@Returns:  Modifies in-place *this.
@Throws: std::runtime_error when complex_envelope is empty and when both vectors size does not match.
*/
_Raises_SEH_exception_  void  radiolocation::SquareWaveMSignal::analytic_signal(_In_ const std::vector<double> &envelope, _In_ const int n_threads)
{
#if defined _DEBUG
	_ASSERTE((0 < n_threads) && !(envelope.empty()));
#else
	if ((0 > n_threads) || (envelope.empty()))
		BOOST_THROW_EXCEPTION(
		empty_vector() <<
		boost::errinfo_api_function("SquareWaveMSignal::analytic_signal") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	std::size_t a_samples{ this->m_samples };
	double j_imag{ j().imag() };
	double a_freq{ this->m_sfrequency };
	double a_timestep{ this->m_sinit_time };
	double a_interval{ this->m_sinterval };
	std::vector<double> a_cos(a_samples);
	std::vector<double> a_sin(a_samples);
	std::vector<double> a_phase(this->m_phase);
	std::vector<std::pair<double, double>> a_square_wave(a_samples);
	double delta{ 0.0 }; double t{ 0.0 };
	double inv_samples{ 1.0 / static_cast<double>(a_samples)};
	std::size_t i;
	omp_set_num_threads(n_threads);
#if defined OMP_TIMING
	double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, t, delta) reduction(+:a_timestep)
	for (i = 0; i < a_samples; ++i)
	{
		a_timestep += a_interval;
		delta = static_cast<double>(i)* inv_samples;
		t = delta * a_timestep;
		a_cos.operator[](i) = ::cos((TWO_PI * a_freq * t) + a_phase.operator[](i));
		a_sin.operator[](i) = j_imag * ::sin((TWO_PI * a_freq * t) + a_phase.operator[](i));
		a_square_wave.operator[](i).operator=({ t, (envelope[i] * a_cos.operator[](i)) + (envelope[i] * a_sin.operator[](i)) });
	}
#if defined OMP_TIMING
	double end{ wrapp_omp_get_wtime() };
	std::printf("SquareWaveMSignal::analytic_signal executed in:%.15fseconds\n", end - start);
#endif
	//Overwrite current context.
	this->m_square_wave.operator=(a_square_wave);
}

_Raises_SEH_exception_  void     radiolocation::SquareWaveMSignal::instantaneous_frequency(_Inout_ std::vector<double> &ifreq)
{
#if defined _DEBUG
	_ASSERTE(this->m_samples == static_cast<std::size_t>(ifreq.size()));
#else
	if (this->m_samples != static_cast<std::size_t>(ifreq.size()))
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("SquareWaveMSignal::instantaneous_frequency") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	double inv_2pi{ mathlib::MathConstants::INV_TWO_PI_DBL() };
	double efreq{ this->m_sfrequency };
	for (std::size_t i{ 0 }; i != this->m_samples; ++i)
	{
		double x{ this->m_square_wave.operator[](i).first };
		auto dt = mathlib::DyDx<double>::differentiate2([&](double arg)->double { return ((TWO_PI * efreq * x) +
			this->get_phase()[i]); }, x, x);
		ifreq.operator[](i) = inv_2pi * dt.get_deriv();
	}
}

std::vector<std::pair<double, double>>     radiolocation::SquareWaveMSignal::pulse_samples() const
{
	return this->get_m_square_wave();
}

std::vector<double>                        radiolocation::SquareWaveMSignal::pulse_phase() const
{
	return this->get_phase();
}

std::size_t                                radiolocation::SquareWaveMSignal::pulse_samples_count() const
{
	return this->get_samples();
}