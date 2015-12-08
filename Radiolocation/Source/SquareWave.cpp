#include "SquareWave.h"
//#include "../MathLib/MathConstants.h"
#include "../MathLib/Derivative.h"
//#include "LibExceptions.h"
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Square Wave signal class - implementation.
@author: Bernard Gingold
@version:  1.0  19/09/2015

*/

const  double  radiolocation::SquareWaveSignal::TWO_PI{ mathlib::MathConstants::TWO_PI_DBL() };


/*
@Brief: Constructor Creates Pure Square Wave Signal.
@Params: const double amplitude A, const double initial time point, const double time point interval increment, const size_t number of samples,
         const int number of OPENMP threads.
@Returns: Nothing
@Throws: std::runtime_error exception when either 0.0 > amplitude || 0 > samples || 0 > n_threads.
*/
_Raises_SEH_exception_           radiolocation::SquareWaveSignal::SquareWaveSignal(_In_ struct SquareWaveParams const& p)
{
	create_signal(p);
}


/*
@Brief: Constructor Copies Pure Square Wave Signal.
@Params: const SquareWaveSignal & reference
@Returns: Nothing
@Throws: no throws.
*/
radiolocation::SquareWaveSignal::SquareWaveSignal(_In_ const SquareWaveSignal &rhs)
{
	create_signal(rhs);
}

/*
@Brief: Constructor Moves Pure Square Wave Signal.
@Params: Square Wave && rval reference
@Returns: Nothing
@Throws: no throws.
*/
radiolocation::SquareWaveSignal::SquareWaveSignal(_In_ SquareWaveSignal &&rhs)
{
	create_signal(rhs);
}


/*
@Brief: Member function Constructs Pure Square Wave Signal. Called from Constructor.
@Params: const double amplitude A, const double initial time point, const double time point interval increment, const size_t number of samples,
const int number of OPENMP threads.
@Returns: Nothing
@Throws: BOOST_THROW_EXCEPTION exception when either 0.0 > amplitude || 0 > samples || 0 > n_threads.
*/
_Raises_SEH_exception_  void          radiolocation::SquareWaveSignal::create_signal(_In_ struct SquareWaveParams const& p)
{
#if defined _DEBUG
	_ASSERTE((p.amplitude > 0.0) || (p.n_samples >= 32) || (p.n_threads > 0));
#else
	if((0.0 > p.amplitude) || (32 > p.n_samples) || (0 > p.n_threads))
	{
		    BOOST_THROW_EXCEPTION(invalid_value_arg() <<
			boost::errinfo_api_function("SquareWaveSignal::create_signal") <<
			boost::errinfo_errno(errno));
	}
		//throw std::runtime_error("Fatal Error in SquareWaveSignal::create_signal: Invalid argument(s) value\n");
#endif

	this->m_amplitude = p.amplitude;
	this->m_init_time = p.init_time;
	this->m_interval = p.interval;
	this->m_samples = p.n_samples;
	this->m_polarization = JonesVector(std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 1.0));
	//Define automatice variables for OPENMP mutli_threading.
	double a_init_time{ p.init_time };
	double a_interval{ p.interval };
	std::size_t a_samples{ p.n_samples };
	std::size_t i;
    _Field_size_(a_samples)	std::vector<std::pair<double, double>> a_squarewave(a_samples);
    _Field_size_(a_smaples) std::vector<double> a_phase(a_samples);
	double delta{ 0.0 };  double t{ 0.0 };
	double inv_samples{ 1.0 / static_cast<double>(a_samples) };
	//std::printf("inv_samples=%.9f\n", inv_samples);
	omp_set_num_threads(p.n_threads);
#if defined OMP_TIMING
	double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t)  reduction(+:a_init_time)
	for (i = 0; i < a_samples; ++i)
	{
		a_init_time += a_interval;
		delta = static_cast<double>(i) * inv_samples;
		//std::printf("delta=%.9f\n", delta);
		t = a_init_time * delta;
		a_phase.operator[](i) = ::sin(std::floor(TWO_PI * t));
		a_squarewave.operator[](i).operator=({ t, p.amplitude * (signum(a_phase.operator[](i))) });
	}
#if defined OMP_TIMING
	double end{ wrapp_omp_get_wtime() };
	std::printf("SquareWaveSignal::create_signal executed in:%.15fseconds\n", end - start);
#endif
	this->m_squarewave = std::vector<std::pair<double, double>>(std::move(a_squarewave));
	this->m_phase = std::vector<double>(std::move(a_phase));
   

}

/*
@Brief: Member function Copies Pure Square Wave Signal.
@Params: const SquareWaveSignal & reference
@Returns: Nothing
@Throws: no throws.
*/
void             radiolocation::SquareWaveSignal::create_signal(_In_ const SquareWaveSignal &signal)
{
	this->m_amplitude = signal.m_amplitude;
	this->m_init_time = signal.m_init_time;
	this->m_interval = signal.m_interval;
	this->m_samples = signal.m_samples;
	this->m_polarization = JonesVector(signal.m_polarization);
	this->m_phase = std::vector<double>(signal.m_phase);
	this->m_squarewave = std::vector<std::pair<double, double>>(signal.m_squarewave);
}

/*
@Brief: Member function moves Pure Square Wave Signal.
@Params:  SquareWaveSignal &&  rval reference
@Returns: Nothing
@Throws: no throws.
*/
void              radiolocation::SquareWaveSignal::create_signal(_In_ SquareWaveSignal &&signal)
{
	this->m_amplitude = std::move(signal.m_amplitude);
	this->m_init_time = std::move(signal.m_init_time);
	this->m_interval  =  std::move(signal.m_interval);
	this->m_samples = std::move(signal.m_samples);
	this->m_polarization = JonesVector(std::move(signal.m_polarization));
	this->m_phase = std::vector<double>(std::move(signal.m_phase));
	this->m_squarewave = std::vector<std::pair<double, double>>(std::move(signal.m_squarewave));
}


radiolocation::SquareWaveSignal&               radiolocation::SquareWaveSignal::operator=(_In_ const SquareWaveSignal &rhs)
{
	if (this == &rhs) return *this;

	this->m_amplitude = rhs.m_amplitude;
	this->m_init_time = rhs.m_init_time;
	this->m_interval = rhs.m_interval;
	this->m_samples = rhs.m_samples;
	this->m_polarization = rhs.m_polarization;
	this->m_phase.operator=(rhs.m_phase);
	this->m_squarewave.operator=(rhs.m_squarewave);
	return *this;
}

radiolocation::SquareWaveSignal&               radiolocation::SquareWaveSignal::operator=(_In_ SquareWaveSignal &&rhs)
{
	if (this == &rhs) return *this;

	this->m_amplitude = std::move(rhs.m_amplitude);
	this->m_init_time = std::move(rhs.m_init_time);
	this->m_interval = std::move(rhs.m_interval);
	this->m_samples = std::move(rhs.m_samples);
	this->m_polarization = std::move(rhs.m_polarization);
	this->m_phase.operator=(std::move(rhs.m_phase));
	this->m_squarewave.operator=(std::move(rhs.m_squarewave));
	return *this;
}

std::ostream&                                  radiolocation::operator<<(_In_ std::ostream& os, _In_ const SquareWaveSignal &signal)
{
	os.scientific; os.showpoint;
	std::setprecision(15);
	for (std::size_t i{ 0 }; i != signal.m_samples; ++i)
	{
		os << "Phase component:" << signal.m_phase.operator[](i) << std::endl;
		os << "time:" << signal.m_squarewave.operator[](i).first << "Square Wave self:" << signal.m_squarewave.operator[](i).second << std::endl;
	}
	return os;
}

/*
@Brief: Return approximately number of SquareWaveSignal cycles
@Params: explicitly operates on member fields.
@Returns: number of cycles..
@Throws: no throws.
*/
double                        radiolocation::SquareWaveSignal::num_of_cycles() const
{
	return (0.5 * (static_cast<double>(this->m_samples) * this->m_interval));
}

#if defined _DEBUG
/*
@Brief: pure virtual function implemented, displays state of the SquareWaveSignal object
@Params: explicitly operates on member fields.
@Returns: Nothing.
@Throws: no throws.
*/
void                                        radiolocation::SquareWaveSignal::debug_print() const
{
	std::printf("SquareWaveSignal::debug_print\n");
	std::printf("this=%p\n", this);
	std::printf("&this->m_amplitude=%p,this->m_amplitude=.9f\n", &this->m_amplitude, this->m_amplitude);
	std::printf("&this->m_init_time=%p,this->m_init_time=%.9f\n", &this->m_init_time, this->m_init_time);
	std::printf("&this->m_interval=%p,this->m_interval=%.9f\n", &this->m_interval, this->m_interval);
	std::printf("&this->m_samples=%p,this->m_samples=%u\n\n", &this->m_samples, this->m_samples);
	std::printf("SquareWave self:  |    phase arg:   |    t:  \n");
	for (std::size_t i{ 0 }; i != this->m_samples; ++i)
		std::printf("%.9f, %.9f, %.9f\n", this->m_squarewave[i].second, this->m_phase[i], this->m_squarewave[i].first);
		
	std::printf("End of SquareWaveSignal dump\n");
}
#endif

#if defined MATHEMATICA_VISUALIZE

/*
@Brief: Class member function writes  state of the SquareWaveSignal object to file.
@Params: explicitly operates on member fields.
@Returns: Nothing.
@Throws: std::runtime_error if fname1 == nullptr || fname2 == nullptr or if fopen_s failed to write to file.
*/
     _Raises_SEH_exception_ void                                 radiolocation::SquareWaveSignal::save_to_file(_In_z_ const char* fname1, _In_z_ const char* fname2) const
{
#if defined _DEBUG
		 _ASSERTE((nullptr != fname1) || (nullptr != fname2) );
#else
		 if ((nullptr == fname1) || (nullptr == fname2))
			 BOOST_THROW_EXCEPTION(
			 invalid_pointer() <<
			 boost::errinfo_api_function("SquareWaveSignal::save_to_file") <<
			 boost::errinfo_errno(errno) <<
			 boost::errinfo_at_line(__LINE__));
#endif
		 FILE *fp1, *fp2;
		 if ((fopen_s(&fp1, fname1, "wt") != 0) || (fopen_s(&fp2,fname2,"wt") != 0))
		 {
			 
			 BOOST_THROW_EXCEPTION(
				 file_open_error() <<
				 boost::errinfo_api_function("fopen_s") <<
				 boost::errinfo_errno(errno) <<
				 boost::errinfo_at_line(__LINE__));
				
		 }
		 else
		 {
			 std::printf("Started writing s(t) to file:%s\n", fname1);
			 std::printf("Started writing phi(t) to file:%s\n", fname2);
			 for (std::size_t i{ 0 }; i != this->m_samples; ++i)
			 {
				 fprintf(fp1, "%.15f, %.15f\n", this->m_squarewave.operator[](i).first, this->m_squarewave.operator[](i).second);
				 fprintf(fp2, "%.15f, %.15f\n", this->m_squarewave.operator[](i).first, this->m_phase.operator[](i));
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
	 @Params: _Inout_  vector to be initialized with IQ decomposed SquareWaveSignal , _In_  number of threads.

	 @Returns:  by argument std::vector<std::pair<double,double>> IQ initialized with SquareWaveSignal IQ decomposition.
	 @Throws: std::runtime_error when n_threads argument is <= 0 or when vector<std::pair<double,double>> IQ is empty.
	 */
	 _Raises_SEH_exception_   void              radiolocation::SquareWaveSignal::quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &IQ, _In_ const int n_threads)
	 {
#if defined _DEBUG
		 _ASSERTE(0 < n_threads);
#else
		 if (0 >= n_threads)
			 BOOST_THROW_EXCEPTION(
			 invalid_value_arg() <<
			 boost::errinfo_api_function("SquareWaveSignal::quadrature_components_extraction") <<
			 boost::errinfo_errno(errno) <<
			 boost::errinfo_at_line(__LINE__));
#endif

		 if (!(IQ.empty()))
		 {
			
			 std::size_t a_samples{ this->m_samples };
			_Field_size_(a_samples) std::vector<double> a_cos_part(a_samples);
			_Field_size_(a_samples) std::vector<double> a_sin_part(a_samples);
			_Field_size_(a_samples) std::vector<double> a_phase(this->m_phase);
			_Field_size_(a_samples) std::vector<std::pair<double, double>> a_squarewave(this->m_squarewave);
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
				 // Save ~20 cycles on division operation.
				 delta = static_cast<double>(i) * inv_samples;
				 t = delta * a_init_time;
				 a_cos_part.operator[](i) = 2.0 * ::cos((TWO_PI * t) + a_phase.operator[](i));
				 a_sin_part.operator[](i) = -2.0 * ::sin((TWO_PI * t) + a_phase.operator[](i));
				 // Force compiler to use std::pair<double,double>> &&
				 IQ.operator[](i).operator=({ a_squarewave.operator[](i).second * a_cos_part.operator[](i),
					 a_squarewave.operator[](i).second * a_sin_part.operator[](i) });

			 }
#if defined  OMP_TIMING
			 double end{ wrapp_omp_get_wtime() };
			 std::printf("SquareWaveSignal::quadrature_components_extraction executed in:%.15f\n", end - start);
#endif
		 }
		 else BOOST_THROW_EXCEPTION(
			 empty_vector() <<
			 boost::errinfo_api_function("SquareWaveSignal::quadrature_components_extraction") <<
			 boost::errinfo_errno(errno));
	 }


	 /*
	 @Brief: Computes signal complex envelope.
	 @Params: _In_  vector to be initialized with IQ decomposed ExpChirpSignal , _Out_
	 vector to be initialized with computed complex envelope values.

	 @Returns:  by argument _Out_ std::vector<double>  initialized with complex envelope values.
	 @Throws: std::runtime_error when IQ is empty and when both vectors size does not match.
	 */
	 _Raises_SEH_exception_   void   radiolocation::SquareWaveSignal::complex_envelope(_In_ std::vector<std::pair<double, double>> &IQ, _Out_ std::vector<double> &envelope)
	 {
		 if (!(IQ.empty()) && (IQ.size() == envelope.size()))
		 {

			 double j_imag{ j().imag() };
			 for (int i{ 0 }; i != envelope.size(); ++i)
				 envelope.operator[](i) = IQ.operator[](i).first + (j_imag * IQ.operator[](i).second);
		 }
		 else BOOST_THROW_EXCEPTION(
			 empty_vector() <<
			 boost::errinfo_api_function("SquareWaveSignal::complex_envelope") <<
			 boost::errinfo_errno(errno) <<
			 boost::errinfo_at_line(__LINE__));
	 }

	 /*
	 @Brief: Computes analytic signal.
	 @Params: _In_  vector to be initialized with complex envelope SquareWaveSignal , _In_ number of OPENMP threads.


	 @Returns:  Modifies in-place *this.
	 @Throws: std::runtime_error when complex_envelope is empty and when both vectors size does not match.
	 */
	 _Raises_SEH_exception_  void     radiolocation::SquareWaveSignal::analytic_signal(_In_ const std::vector<double> &envelope, _In_ const int n_threads)
	 {
#if defined _DEBUG
		 _ASSERTE((this->m_samples == static_cast<std::size_t>(envelope.size())) && (n_threads > 0));
#else
		 if ((this->m_samples != static_cast<std::size_t>(envelope.size())) || (n_threads <= 0))
			 BOOST_THROW_EXCEPTION(
			 invalid_value_arg() <<
			 boost::errinfo_api_function("SquareWaveSignal::analytic_signal") <<
			 boost::errinfo_errno(errno) <<
			 boost::errinfo_at_line(__LINE__));
#endif
		 
		 if (!(envelope.empty()))
		 {
			 // Define automatic variables in order to use OPENMP multi-threading where class members are used.
			 size_t a_samples{ this->m_samples };
			 double j_imag{ j().imag() };
			 double a_timestep{ this->m_init_time };
			 double a_interval{ this->m_interval };
			_Field_size_(a_samples) std::vector<double> a_cos_part(a_samples);
			_Field_size_(a_samples) std::vector<double> a_sin_part(a_samples);
			_Field_size_(a_samples) std::vector<std::pair<double, double>> a_squarewave(a_samples);
			_Field_size_(a_samples) std::vector<double> a_phase(this->m_phase);
			 double delta{ 0.0 }; double t{ 0.0 };
			 double inv_samples{ 1.0 / static_cast<double>(a_samples) };
			 size_t i;
			 omp_set_num_threads(n_threads);
#if defined OMP_TIMING
			 double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t) reduction(+:a_timestep)
			 for (i = 0; i < a_samples; ++i)
			 {
				 a_timestep += a_interval;
				 delta = static_cast<double>(i)* inv_samples;
				 t = a_timestep * delta;
				 a_cos_part.operator[](i) = ::cos((TWO_PI * t) + a_phase.operator[](i));
				 a_sin_part.operator[](i) = j_imag * ::sin((TWO_PI * t) + a_phase.operator[](i));
				 a_squarewave.operator[](i).operator=({ t, (envelope.operator[](i) * a_cos_part.operator[](i)) +
					 (envelope.operator[](i) * a_sin_part.operator[](i)) });

			 }
#if defined OMP_TIMING
			 double end{ wrapp_omp_get_wtime() };
			 std::printf("SquareWaveSignal::analytic_signal executed in:%.15f\n", end - start);
#endif
			 this->m_squarewave.operator=(a_squarewave);
		 }
		 else BOOST_THROW_EXCEPTION(
			 empty_vector() <<
			 boost::errinfo_api_function("SquareWaveSignal::analytic_signal") <<
			 boost::errinfo_errno(errno) <<
			 boost::errinfo_at_line(__LINE__));
	 }


	 _Raises_SEH_exception_  void   radiolocation::SquareWaveSignal::instantaneous_frequency(_Inout_ std::vector<double> &ifreq)
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
		 double efreq{ 1.0e+5 };
		 for (std::size_t i{ 0 }; i != this->m_samples; ++i)
		 {
			 double x{ this->m_squarewave.operator[](i).first };
			 auto dt = mathlib::DyDx<double>::differentiate2([&](double arg)->double { return ((TWO_PI * efreq * x) +
				 this->get_phase()[i]); }, x, x);
			 ifreq.operator[](i) = inv_2pi * dt.get_deriv();
		 }
	 }

	 std::vector<std::pair<double, double>>    radiolocation::SquareWaveSignal::pulse_samples() const
	 {
		 return this->get_squarewave();
	 }


	 std::vector<double>                       radiolocation::SquareWaveSignal::pulse_phase() const
	 {
		 return this->get_phase();
	 }

	 std::size_t                               radiolocation::SquareWaveSignal::pulse_samples_count() const
	 {
		 return this->get_samples();
	 }
	 /*
	 @ TODO:
	    Implement later.
	 */

	 void          radiolocation::SquareWaveSignal::amplitude_modulation(const double a, const double b, const double c)
	 {
		 ; // To be implemented later
	 }

	 void          radiolocation::SquareWaveSignal::frequency_modulation(double a, size_t n)
	 {
		 ; // To be implemented later.
	 }

	 void          radiolocation::SquareWaveSignal::phase_modulation(const double a, const double b, const double c, std::function<double(double, double)> &f)
	 {
		 ; // To be implemented later.
	 }
