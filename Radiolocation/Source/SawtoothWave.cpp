/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Sawtooth signal class - implementaion.
@author: Bernard Gingold
@version:  1.0  28/09/2015

*/
#include "SawtoothWave.h"
//#include "../MathLib/MathConstants.h"
#include "../MathLib/Derivative.h"
//#include "LibExceptions.h"

/*
@Brief: Value of 2Pi.
*/
const double radiolocation::SawtoothSignal::TWO_PI{ mathlib::MathConstants::TWO_PI_DBL() };

/*
@Brief: Constructor Creates Pure Sawtooth Wave Signal.
@Params: const double amplitude A, const double initial time point, const double time point interval increment, const double frequency,
const size_t number of samples,const int number of OPENMP threads.

@Returns: Nothing
@Throws: BOOST_THROW_EXCEPTION  when either 0.0 > amplitude || 0 > samples || 0 > n_threads.
*/
_Raises_SEH_exception_ radiolocation::SawtoothSignal::SawtoothSignal(_In_ struct SawtoothSignalParams const& params)
{
	create_signal(params);
}


/*
@Brief: Constructor Copies Pure Sawtooth Wave Signal.
@Params: const SawtoothSignal & reference
@Returns: Nothing
@Throws: no throws.
*/
radiolocation::SawtoothSignal::SawtoothSignal(_In_ SawtoothSignal const& rhs)
{
	create_signal(rhs);
}

/*
@Brief: Constructor Moves Pure Sawtooth Signal.
@Params:  SawtoothSignal && rval reference
@Returns: Nothing
@Throws: no throws.
*/
radiolocation::SawtoothSignal::SawtoothSignal(_In_ SawtoothSignal &&rhs)
{
	create_signal(rhs);
}

/*
@Brief: Member function Constructs Pure Sawtooth Signal. Called from Constructor.
@Params: const double amplitude A, const double frequency, const double initial time point, const double time point interval increment, const size_t number of samples,
const int number of OPENMP threads.
@Returns: Nothing
@Throws: BOOST_THROW_EXCEPTION exception when either 0.0 > amplitude || 0 > samples || 0 > n_threads.
*/

_Raises_SEH_exception_     void         radiolocation::SawtoothSignal::create_signal(_In_ struct SawtoothSignalParams const& params)
	
{
#if defined _DEBUG
	_ASSERTE((0.0 < params.amplitude) && (0 < params.n_samples) && (0 < params.n_threads));
#else
	if ((0.0 >= params.amplitude) || (0 > params.n_samples) || (0 > params.n_threads))
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("SawtoothSignal::create_signal") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	this->m_amplitude = params.amplitude;
	this->m_frequency = params.frequency;
	this->m_init_time = params.init_time;
	this->m_interval = params.interval;
	this->m_samples = params.n_samples;
	this->m_polarization = JonesVector(std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 1.0));
	//Define automatice variables for OPENMP mutli_threading.
	double a_amplitude{ params.amplitude };
	double a_freq{ params.frequency };
	double a_init_time{ params.init_time };
	double a_interval{ params.interval };
	std::size_t a_samples{ params.n_samples };
	
	std::size_t i;
 _Field_size_(a_samples)	std::vector<std::pair<double, double>> a_sawtooth(a_samples);
 _Field_size_(a_samples)	std::vector<double> a_phase(a_samples);
 double delta{ 0.0 }; double t{ 0.0 };
 double inv_samples{ 1.0 / static_cast<double>(a_samples) };
 omp_set_num_threads(params.n_threads);
#if defined OMP_TIMING
 double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t) reduction(+:a_init_time)
 for (i = 0; i < a_samples; ++i)
 {
	 a_init_time += a_interval;
	 delta = static_cast<double>(i)* inv_samples;
	 t = a_init_time * delta;
	 a_phase.operator[](i) = t - std::floor(t);
	 a_sawtooth.operator[](i).operator=({ t, params.amplitude * a_phase.operator[](i) });
 }
#if defined OMP_TIMING
 double end{ wrapp_omp_get_wtime() };
 std::printf("SawtoothSignal::create_signal executed in:%.15fseconds\n", end - start);
#endif
      this->m_phase = std::vector<double>(std::move(a_phase));
	  this->m_sawtooth = std::vector<std::pair<double, double>>(std::move(a_sawtooth));
}

/*
@Brief: Member function Copies Pure SawtoothSignal.
@Params: const SawtoothSignal & reference
@Returns: Nothing
@Throws: no throws.
*/
void                 radiolocation::SawtoothSignal::create_signal(_In_ SawtoothSignal const& rhs)
{
	this->m_amplitude = rhs.m_amplitude;
	this->m_frequency = rhs.m_frequency;
	this->m_init_time = rhs.m_init_time;
	this->m_interval = rhs.m_interval;
	this->m_samples = rhs.m_samples;
	this->m_polarization = JonesVector(rhs.m_polarization);
	this->m_phase = std::vector<double>(rhs.m_phase);
	this->m_sawtooth = std::vector<std::pair<double, double>>(rhs.m_sawtooth);
}

/*
@Brief: Member function moves Pure Sawtooth Signal.
@Params:  SawtoothSignal &&  rval reference
@Returns: Nothing
@Throws: no throws.
*/
void               radiolocation::SawtoothSignal::create_signal(_In_ SawtoothSignal &&rhs)
{
	this->m_amplitude = std::move(rhs.m_amplitude);
	this->m_frequency = std::move(rhs.m_frequency);
	this->m_init_time = std::move(rhs.m_init_time);
	this->m_interval = std::move(rhs.m_interval);
	this->m_samples = std::move(rhs.m_samples);
	this->m_polarization = JonesVector(std::move(rhs.m_polarization));
	this->m_phase = std::vector<double>(std::move(rhs.m_phase));
	this->m_sawtooth = std::vector<std::pair<double, double>>(std::move(rhs.m_sawtooth));
}

/*
@Brief: operator= copy-assignment.
*/
radiolocation::SawtoothSignal&              radiolocation::SawtoothSignal::operator=(_In_ SawtoothSignal const &rhs)
{
	if (this == &rhs) return *this;

	this->m_amplitude = rhs.m_amplitude;
	this->m_frequency = rhs.m_frequency;
	this->m_init_time = rhs.m_init_time;
	this->m_interval = rhs.m_interval;
	this->m_samples = rhs.m_samples;
	this->m_polarization.operator=(rhs.m_polarization);
	this->m_phase.operator=(rhs.m_phase);
	this->m_sawtooth.operator=(rhs.m_sawtooth);
	return *this;
}

radiolocation::SawtoothSignal&              radiolocation::SawtoothSignal::operator=(_In_ SawtoothSignal &&rhs)
{
	if (this == &rhs) return *this;

	this->m_amplitude = std::move(rhs.m_amplitude);
	this->m_frequency = std::move(rhs.m_frequency);
	this->m_init_time = std::move(rhs.m_init_time);
	this->m_interval = std::move(rhs.m_interval);
	this->m_samples = std::move(rhs.m_samples);
	this->m_polarization.operator=(std::move(rhs.m_polarization));
	this->m_phase.operator=(std::move(rhs.m_phase));
	this->m_sawtooth.operator=(std::move(rhs.m_sawtooth));
	return *this;
}

std::ostream&                              radiolocation::operator<<(_In_ std::ostream& os, _In_ SawtoothSignal const& rhs)
{
	std::setprecision(15);
	os.scientific;
	
	for (std::size_t i{ 0 }; i != rhs.m_samples; ++i)
	{
		os << "s(t):" << rhs.m_sawtooth.operator[](i).second << "phi(t):"
			<< rhs.m_phase.operator[](i) << "t:" << rhs.m_sawtooth.operator[](i).first << std::endl;
	}
	return os;
}

/*
@Brief: Returns approximately number of SawtoothSignal cycles
@Params: explicitly operates on member fields.
@Returns: Nothing.
@Throws: no throws
*/
double                                    radiolocation::SawtoothSignal::num_of_cycles() const
{
	return (0.5 * (static_cast<double>(this->m_samples) * this->m_interval));
}

#if defined _DEBUG
/*
@Brief: pure virtual function implemented, displays state of the SawtoothSignal object
@Params: explicitly operates on member fields.
@Returns: Nothing.
@Throws: no throws.
*/
void                radiolocation::SawtoothSignal::debug_print() const
{
	std::printf("SawtoothSignal::debug_print\n");
	std::printf("&this->m_amplitude=%p,this->m_amplitude=%.9f\n", &this->m_amplitude, this->m_amplitude);
	std::printf("&this->m_frequency=%p, this->m_frequency=%.9f\n", &this->m_frequency, this->m_frequency);
	std::printf("&this->m_init_time=%p,this->m_init_time=%.9f\n", &this->m_init_time, this->m_init_time);
	std::printf("&this->m_interval=%p,this->m_interval=%.9f\n", &this->m_interval, this->m_interval);
	std::printf("&this->m_samples=%p,this->m_samples=%d\n", &this->m_samples, this->m_samples);
	std::printf("&this->m_polarization=%p,this->m_polarization=%.9f\n", &this->m_polarization, this->m_polarization.v().imag());
	std::printf("s(t):    |       phi(t):       |         t: \n");
	for (std::size_t i{ 0 }; i != this->m_samples; ++i)
		std::printf("%.10f,%.10f,%.10f\n", this->m_sawtooth[i].second, this->m_phase[i], this->m_sawtooth[i].first);

	std::printf("End of SawtoothSignal context dump\n");
}
#endif

#if defined MATHEMATICA_VISUALIZE
/*
@Brief: Class member function writes  state of the SawtoothSignal object to file.
@Params: explicitly operates on member fields.
@Returns: Nothing.
@Throws: std::runtime_error if fname1 == nullptr || fname2 == nullptr or if fopen_s failed to write to file.
*/
_Raises_SEH_exception_  void           radiolocation::SawtoothSignal::save_to_file(_In_z_ const char* fname1, _In_z_ const char* fname2) const
{
#if defined _DEBUG
	_ASSERTE((nullptr != fname1) && (nullptr != fname2));
#else
	if ((nullptr == fname1) || (nullptr == fname2))
		BOOST_THROW_EXCEPTION(
		invalid_pointer() <<
		boost::errinfo_api_function("SawtoothSignal::save_to_file") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	FILE *fp1, *fp2;
	if ((fopen_s(&fp1, fname1, "wt") != 0) || (fopen_s(&fp2, fname2, "wt") != 0))
	{
		BOOST_THROW_EXCEPTION(
			file_error() <<
			boost::errinfo_api_function("SawtoothSignal::save_to_file") <<
			boost::errinfo_errno(errno) <<
			boost::errinfo_at_line(__LINE__));
	}
	else
	{
		std::printf("Started writing s(t) to file:%s\n", fname1);
		std::printf("Started writing phi(t) to file:%s\n", fname2);
		for (std::size_t i{ 0 }; i != this->m_samples; ++i)
		{
			std::fprintf(fp1, "%.15f,%.15f\n", this->m_sawtooth[i].first, this->m_sawtooth[i].second);
			std::fprintf(fp2, "%.15f,%.15f\n", this->m_sawtooth[i].first, this->m_phase[i]);
		}
		std::printf("Finished writing s(t) to file:%s\n", fname1);
		std::printf("Finished writing phi(t) to file:%s\n", fname2);
		fclose(fp1);
		fclose(fp2);
	}
}

#endif

/*
@Brief: Computes signal IQ Decomposition.
@Params: _Inout_  vector to be initialized with IQ decomposed SawtoothSignal , _In_  number of threads.

@Returns:  by argument std::vector<std::pair<double,double>> IQ initialized with SawtoothSignal IQ decomposition.
@Throws: BOOST_THROW_EXCEPTION when n_threads argument is <= 0 or when vector<std::pair<double,double>> IQ is empty.
*/
_Raises_SEH_exception_  void        radiolocation::SawtoothSignal::quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &IQ, _In_ const int n_threads)
{
#if defined _DEBUG
	_ASSERTE(0 < n_threads);
#else
	if (0 >= n_threads)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("SawtoothSignal::quadrature_components_extraction\n") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	if (!(IQ.empty()))
	{
		// Define automatic variables in order to run OPENMP multi-threading, otherwise OPENMP on class members will not compile.
		std::size_t a_samples{ this->m_samples };
		_Field_size_(a_samples)	std::vector<double> a_cos(a_samples);
		_Field_size_(a_samples) std::vector<double> a_sin(a_samples);
		_Field_size_(a_samples) std::vector<double> a_phase(this->m_phase); // invokes std::vector<double>::vector(const std::vector<double> &)
		_Field_size_(a_samples) std::vector<std::pair<double, double>> a_sawtooth(this->m_sawtooth); // 
		std::size_t i;
		double a_init_time{ this->m_init_time };
		double a_interval{ this->m_interval };
		double delta{ 0.0 }; double t{ 0.0 };
		double inv_samples{ 1.0 / static_cast<double>(a_samples) };
		omp_set_num_threads(n_threads);
#if defined OMP_TIMING
		double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t) reduction(+:a_init_time)
		for (i = 0; i < a_samples; ++i)
		{
			a_init_time += a_interval;
			delta = static_cast<double>(i)* inv_samples;
			t = a_init_time * delta;
			a_cos.operator[](i) = 2.0 * ::cos((TWO_PI * t) + a_phase.operator[](i));
			a_sin.operator[](i) = -2.0 * ::sin((TWO_PI * t) + a_phase.operator[](i));
			IQ.operator[](i).operator=({ a_sawtooth.operator[](i).second * a_cos.operator[](i),
				a_sawtooth.operator[](i).second * a_sin.operator[](i) });
		}
#if defined OMP_TIMING
		double end{ wrapp_omp_get_wtime() };
		std::printf("SawtoothSignal::quadrature_components_extraction executed in:%.15f\n", end - start);
#endif
	}
	else  BOOST_THROW_EXCEPTION(
		empty_vector() <<
		boost::errinfo_api_function("SawtoothSignal::quadrature_components_extraction") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
}

/*
@Brief: Computes signal complex envelope.
@Params: _In_  vector to be initialized with IQ decomposed SawtoothSignal , _Out_
vector to be initialized with computed complex envelope values.

@Returns:  by argument _Out_ std::vector<double>  initialized with complex envelope values.
@Throws: BOOST_THROW_EXCEPTION when IQ is empty and when both vectors size does not match.
*/
_Raises_SEH_exception_  void           radiolocation::SawtoothSignal::complex_envelope(_In_ std::vector<std::pair<double, double>> &IQ, _Out_ std::vector<double> &cenvelope)
{
	if (!(IQ.empty()) && (IQ.size() == cenvelope.size()))
	{
		double j_imag{ j().imag() };
		for (int i{ 0 }; i != IQ.size(); ++i)
			cenvelope.operator[](i) = IQ.operator[](i).first + (j_imag * IQ.operator[](i).second);
	}
	else BOOST_THROW_EXCEPTION(
		empty_vector() <<
		boost::errinfo_api_function("SawtoothSignal::complex_envelope: !!FAILED!!") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
}

/*
@Brief: Computes analytic signal.
@Params: _In_  vector to be initialized with complex envelope SawtoothSignal , _In_ number of OPENMP threads.


@Returns:  Modifies in-place *this.
@Throws: BOOST_THROW_EXCEPTION when complex_envelope is empty and when both vectors size does not match.
*/
_Raises_SEH_exception_  void            radiolocation::SawtoothSignal::analytic_signal(_In_ const std::vector<double> &cenvelope, _In_ const int n_threads)
{
#if defined _DEBUG
	_ASSERTE((this->m_samples == static_cast<std::size_t>(cenvelope.size())) && (0 < n_threads));
#else
	if ((this->m_samples != static_cast<std::size_t>(cenvelope.size())) || (0 >= n_threads))
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("Sawtooth::analytic_signal") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif

	if (!(cenvelope.empty()))
	{
		// Define automatic variables in order to use OPENMP multi-threading where class members are used.
		std::size_t a_samples{ this->m_samples };
		double j_imag{ j().imag() };
		double a_init_time{ this->m_init_time };
		double a_interval{ this->m_interval };
		_Field_size_(a_samples) std::vector<double> a_cos(a_samples);
		_Field_size_(a_samples) std::vector<double> a_sin(a_samples);
		_Field_size_(a_samples) std::vector<double> a_phase(this->m_phase);
		_Field_size_(a_samples) std::vector<std::pair<double, double>> a_sawtooth(a_samples);
		double delta{ 0.0 }; double t{ 0.0 };
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
			a_init_time += a_interval;
			delta = static_cast<double>(i)* inv_samples;
			t = a_init_time * delta;
			a_cos.operator[](i) = ::cos((TWO_PI * t) + a_phase.operator[](i));
			a_sin.operator[](i) = j_imag * ::sin((TWO_PI * t) + a_phase.operator[](i));
			a_sawtooth.operator[](i).operator=({ t, (cenvelope.operator[](i) * a_cos.operator[](i)) +
				(cenvelope.operator[](i) * a_sin.operator[](i)) });
		}
#if defined OMP_TIMING
		double end{ wrapp_omp_get_wtime() };
		std::printf("SawtoothSignal::analytic_signal executed in:%.15fsecond\n", end - start);
#endif
		this->m_sawtooth.operator=(a_sawtooth);
	}
	else BOOST_THROW_EXCEPTION(
		empty_vector() <<
		boost::errinfo_api_function("SawtoothSignal::analytic_signal") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
}

_Raises_SEH_exception_   void           radiolocation::SawtoothSignal::instantaneous_frequency(_Inout_ std::vector<double> &ifreq)
{
#if defined _DEBUG
	_ASSERTE(this->m_samples == static_cast<std::size_t>(ifreq.size()));
#else
	if (this->m_samples != static_cast<std::size_t>(ifreq.size()))
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("SawtoothSignal::instantaneous_frequency") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	double inv_2pi{ mathlib::MathConstants::INV_TWO_PI_DBL() };
	
	for (std::size_t i{ 0 }; i != this->m_samples; ++i)
	{
		double x{ this->m_sawtooth.operator[](i).first };
		auto dt = mathlib::DyDx<double>::differentiate2([&](double arg)->double { return ((TWO_PI * this->get_frequency() * x) +
			this->get_phase()[i]); }, x, x);
		ifreq.operator[](i) = inv_2pi * dt.get_deriv();
	}
}

std::vector<std::pair<double, double>>    radiolocation::SawtoothSignal::pulse_samples() const
{
	return this->get_sawtooth();
}


std::vector<double>                       radiolocation::SawtoothSignal::pulse_phase() const
{
	return this->get_phase();
}

std::size_t                               radiolocation::SawtoothSignal::pulse_samples_count() const
{
	return this->get_samples();
}

/*
@ TODO:
Implement later.
*/

void          radiolocation::SawtoothSignal::amplitude_modulation(const double a, const double b, const double c)
{
	; // To be implemented later
}

void          radiolocation::SawtoothSignal::frequency_modulation(double a, size_t n)
{
	; // To be implemented later.
}

void          radiolocation::SawtoothSignal::phase_modulation(const double a, const double b, const double c, std::function<double(double, double)> &f)
{
	; // To be implemented later.
}