
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Modulated Sawtooth signal class - implementation.
@author: Bernard Gingold
@version:  1.0  29/09/2015

*/
#include "SawtoothModulated.h"
//#include "../MathLib/MathConstants.h"
#include "../MathLib/Derivative.h"
//#include "LibExceptions.h"

/*
@Brief: Value of 2Pi.
*/
const double  radiolocation::SawtoothMSignal::TWO_PI{ mathlib::MathConstants::TWO_PI_DBL() };

/*
@Brief: Constructor Creates Modulated Sawtooth Wave Signal.
@Params: std::function r(t)waveform generator, std::function phi(t) waveform generator, const double sinit_time , const double rinit_time, const double phinit_time,
const double sinterval, const double rinterval, const double phinterval, const double simulated real frequency of s(t), const double simulated real frequency of r(t),
const double simulated real frequency phi(t).
const size_t number of samples,const int number of OPENMP threads.

@Returns: Nothing
@Throws: BOOST_THROW_EXCEPTION  when either r(t) modelled frequency > s(t) || phi(t) modelled frequency > s(t).
*/
_Raises_SEH_exception_   radiolocation::SawtoothMSignal::SawtoothMSignal(_In_ struct SawtoothMSignalParams const& params)
	
	
{
	create_signal(params);
}

/*
@Brief: Constructor Copies Modulated Sawtooth Wave Signal.
@Params : const SawtoothMSignal & reference
@Returns : Nothing
@Throws : no throws.
*/
                  radiolocation::SawtoothMSignal::SawtoothMSignal(_In_ SawtoothMSignal const& rhs)
                 {
					  create_signal(rhs);
                 }

				  /*
				  @Brief: Constructor moves Modulated Sawtooth Signal.
				  @Params:  SawtoothMSignal &&  rval reference
				  @Returns: Nothing
				  @Throws: no throws.
				  */
				  radiolocation::SawtoothMSignal::SawtoothMSignal(_In_ SawtoothMSignal &&rhs)
				  {
					  create_signal(rhs);
				  }

				  /*
				  @Brief: operator= copy-assignment.
				  */
				  radiolocation::SawtoothMSignal&              radiolocation::SawtoothMSignal::operator=(_In_ SawtoothMSignal const& rhs)
				  {
					  if (this == &rhs) return *this;

					  this->m_phfrequency = rhs.m_phfrequency;
					  this->m_phinit_time = rhs.m_phinit_time;
					  this->m_phinterval = rhs.m_phinterval;
					  this->m_phwaveform = rhs.m_phwaveform;
					  this->m_rfrequency = rhs.m_rfrequency;
					  this->m_rinit_time = rhs.m_rinit_time;
					  this->m_rinterval = rhs.m_rinterval;
					  this->m_rwaveform = rhs.m_rwaveform;
					  this->m_samples = rhs.m_samples;
					  this->m_sfrequency = rhs.m_sfrequency;
					  this->m_sinit_time = rhs.m_sinit_time;
					  this->m_sinterval = rhs.m_sinterval;
					  this->m_polarization.operator=(rhs.m_polarization);
					  this->m_phit.operator=(rhs.m_phit);
					  this->m_rt.operator=(rhs.m_rt);
					  this->m_St.operator=(rhs.m_St);
					  return *this;
				  }

				  /*
				  @Brief: operator= move-assignment.
				  */

/*
@Brief: Member function Constructs Modulated Sawtooth Signal. Called from Constructor.
@Params: std::function r(t)waveform generator, std::function phi(t) waveform generator, const double sinit_time , const double rinit_time, const double phinit_time,
const double sinterval, const double rinterval, const double phinterval, const double simulated real frequency of s(t), const double simulated real frequency of r(t),
const double simulated real frequency phi(t).
const size_t number of samples,const int number of OPENMP threads.

@Returns: Nothing
@Throws: BOOST_THROW_EXCEPTION  when either r(t) modelled frequency > s(t) || phi(t) modelled frequency > s(t).
*/
_Raises_SEH_exception_   void               radiolocation::SawtoothMSignal::create_signal(_In_ struct SawtoothMSignalParams const& params)

	
{
#if defined _DEBUG
	_ASSERTE((RtCycles(params.n_samples,params.rinterval) < StCycles(params.n_samples,params.sinterval)) && (PhitCycles(params.n_samples,params.phinterval) < StCycles(params.n_samples,params.sinterval)));
#else
	if ((RtCycles(n_samples, rinterval) > StCycles(n_samples, sinterval)) ||
		((PhitCycles(n_samples, phinterval) > StCycles(n_samples, sinterval))))
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("SawtoothMSignal::create_signal") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	this->m_rwaveform.operator=(params.rwaveform);
	this->m_phwaveform.operator=(params.phiwaveform);
	this->m_sinit_time = params.sinit_time;
	this->m_rinit_time = params.rinit_time;
	this->m_phinit_time = params.phinit_time;
	this->m_sinterval = params.sinterval;
	this->m_rinterval = params.rinterval;
	this->m_phinterval = params.phinterval;
	this->m_sfrequency = params.sfreq;
	this->m_rfrequency = params.rfreq;
	this->m_phfrequency = params.phfreq;
	this->m_samples = params.n_samples;
	this->m_polarization = JonesVector(std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 1.0));
	//Define automatice variables for OPENMP mutli_threading.
	std::function<double(double)> a_rwaveform = params.rwaveform;
	std::function<double(double)> a_phwaveform = params.phiwaveform;
	double a_sinit_time{ params.sinit_time };
	double a_rinit_time{ params.rinit_time };
	double a_phinit_time{ params.phinit_time };
	double a_sinterval{ params.sinterval };
	double a_rinterval{ params.rinterval };
	double a_phinterval{ params.phinterval };
	double a_sfreq{ params.sfreq };
	double a_rfreq{ params.rfreq };
	double a_phfreq{ params.phfreq };
	std::size_t i;
	std::size_t a_samples{ params.n_samples };
	_Field_size_(a_samples) std::vector<std::pair<double, double>> a_St(a_samples);
	_Field_size_(a_samples) std::vector<double> a_rt(a_samples);
	_Field_size_(a_samples) std::vector<double> a_phit(a_samples);
	double delta{ 0.0 }; double t1{ 0.0 }; double t2{ 0.0 }; double t3{ 0.0 };
	double inv_samples{ 1.0 / static_cast<double>(a_samples) };
	omp_set_num_threads(params.n_threads);
#if defined OMP_TIMING
	double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t1, t2, t3) reduction(+:a_sinit_time) reduction(+:a_rinit_time) reduction(+:a_phinit_time)
	for (i = 0; i < a_samples; ++i)
	{
		a_sinit_time += a_sinterval;
		a_rinit_time += a_rinterval;
		a_phinit_time += a_phinterval;
		delta = static_cast<double>(i) * inv_samples;
		t1 = a_sinit_time * delta;
		t2 = a_rinit_time * delta;
		t3 = a_phinit_time * delta;
		a_rt.operator[](i) = a_rwaveform(TWO_PI * RtCycles(a_samples,a_rinterval)* t2);
		a_phit.operator[](i) = a_phwaveform(-(TWO_PI * PhitCycles(a_samples,a_phinterval)  * t3));
		a_St.operator[](i).operator=({ t1, a_rt.operator[](i) * (t1 - std::floor(t1 + a_phit.operator[](i))) });
	}
#if defined OMP_TIMING
	double end{ wrapp_omp_get_wtime() };
	std::printf("SawtoothMSignal::create_signal executed in:%.15fseconds\n", end - start);
#endif
	this->m_rt = std::vector<double>(std::move(a_rt));
	this->m_phit = std::vector<double>(std::move(a_phit));
	this->m_St = std::vector<std::pair<double, double>>(std::move(a_St));
}

/*
@Brief: Member function Copies Modulated SawtoothSignal.
@Params: const SawtoothMSignal & reference
@Returns: Nothing
@Throws: no throws.
*/
void                 radiolocation::SawtoothMSignal::create_signal(_In_ SawtoothMSignal const& rhs)
{
	this->m_phfrequency = rhs.m_phfrequency;
	this->m_phinit_time = rhs.m_phinit_time;
	this->m_phinterval = rhs.m_phinterval;
	this->m_phwaveform = rhs.m_phwaveform;
	this->m_rfrequency = rhs.m_rfrequency;
	this->m_rinit_time = rhs.m_rinit_time;
	this->m_rinterval = rhs.m_rinterval;
	this->m_rwaveform = rhs.m_rwaveform;
	this->m_samples = rhs.m_samples;
	this->m_sfrequency = rhs.m_sfrequency;
	this->m_sinit_time = rhs.m_sinit_time;
	this->m_sinterval = rhs.m_sinterval;
	this->m_polarization = JonesVector(rhs.m_polarization);
	this->m_phit = std::vector<double>(rhs.m_phit);
	this->m_rt = std::vector<double>(rhs.m_rt);
	this->m_St = std::vector<std::pair<double, double>>(rhs.m_St);
}

/*
@Brief: Member function moves Modulated Sawtooth Signal.
@Params:  SawtoothMSignal &&  rval reference
@Returns: Nothing
@Throws: no throws.
*/
void                    radiolocation::SawtoothMSignal::create_signal(_In_ SawtoothMSignal &&rhs)
{
	this->m_phfrequency = std::move(rhs.m_phfrequency);
	this->m_phinit_time = std::move(rhs.m_phinit_time);
	this->m_phinterval = std::move(rhs.m_phinterval);
	this->m_phwaveform = std::move(rhs.m_phwaveform);
	this->m_rfrequency = std::move(rhs.m_rfrequency);
	this->m_rinit_time = std::move(rhs.m_rinit_time);
	this->m_rinterval = std::move(rhs.m_rinterval);
	this->m_rwaveform = std::move(rhs.m_rwaveform);
	this->m_samples = std::move(rhs.m_samples);
	this->m_sfrequency = std::move(rhs.m_sfrequency);
	this->m_sinit_time = std::move(rhs.m_sinit_time);
	this->m_sinterval = std::move(rhs.m_sinterval);
	this->m_polarization = JonesVector(std::move(rhs.m_polarization));
	this->m_phit = std::vector<double>(rhs.m_phit);
	this->m_rt = std::vector<double>(rhs.m_rt);
	this->m_St = std::vector<std::pair<double, double>>(rhs.m_St);
}

/*
@Brief: std::ostream& operator<<
*/
std::ostream&                        radiolocation::operator<<(_In_ std::ostream& os, _In_ SawtoothMSignal const& rhs)
{
	std::setprecision(15);
	os.scientific;
	for (std::size_t i{ 0 }; i != rhs.m_samples; ++i)
	{
		os << "S(t):" << rhs.m_St[i].second << "r(t):" << rhs.m_rt[i] << "phi(t)" << rhs.m_phit[i] <<
			"t:" << rhs.m_St[i].first << std::endl;
 	}
	return os;
}

/*
@Brief: Pure virtual functions implementation
*/

#if defined _DEBUG

/*
@Brief: pure virtual function implemented, displays state of the SawtoothMSignal object
@Params: explicitly operates on member fields.
@Returns: Nothing.
@Throws: no throws.
*/
void                        radiolocation::SawtoothMSignal::debug_print() const
{
	std::printf("SawtoothMSignal::debug_print\n");
	std::printf("&this->m_samples=%p,this->m_samples=%u\n", &this->m_samples, this->m_samples);
	std::printf("&this->m_sinit_time=%p,this->m_sinit_time=%.9f\n", &this->m_sinit_time, this->m_sinit_time);
	std::printf("&this->m_rinit_time=%p,this->m_rinit_time=%.9f\n", &this->m_rinit_time, this->m_rinit_time);
	std::printf("&this->m_phinit_time=%p, this->m_phinit_time=%.9f\n", &this->m_phinit_time, this->m_phinit_time);
	std::printf("&this->m_sinterval=%p,this->m_sinterval=%.9f\n", &this->m_sinterval, this->m_sinterval);
	std::printf("&this->m_rinterval=%p,this->m_rinterval=%.9f\n", &this->m_rinterval, this->m_rinterval);
	std::printf("&this->m_phinterval=%p,this->m_phinterval=%.9f\n", &this->m_phinterval, this->m_phinterval);
	std::printf("&this->m_sfrequency=%p,this->m_sfrequency=%.9f\n", &this->m_sfrequency, this->m_sfrequency);
	std::printf("&this->m_rfrequency=%p,this->m_rfrequency=%.9f\n", &this->m_rfrequency, this->m_rfrequency);
	std::printf("&this->m_phifrequency=%p,this->m_phifrequency=%.9f\n", &this->m_phfrequency, this->m_phfrequency);
	std::printf("&this->m_rwaveform=%p, &this->m_phwaveform=%p\n", &this->m_rwaveform, &this->m_phwaveform);
	std::printf("S(t):    |     r(t):       |     phi(t):      |       t:\n");
	for (std::size_t i{ 0 }; i != this->m_samples; ++i)
		std::printf("%.9f,%.9f,%.9f,%.9f\n", this->m_St[i].second, this->m_rt[i], this->m_phit[i], this->m_St[i].first);
	std::printf("End of SawtoothMSignal context dump\n");
}
#endif

#if defined MATHEMATICA_VISUALIZE

/*
@Brief: Class member function writes  state of the SawtoothMSignal object to file.
@Params: explicitly operates on member fields.
@Returns: Nothing.
@Throws: std::runtime_error if fname1 == nullptr || fname2 == nullptr or if fopen_s failed to write to file.
*/
_Raises_SEH_exception_          void                  radiolocation::SawtoothMSignal::save_to_file(_In_z_ const char* fn1, _In_z_ const char* fn2, _In_z_ const char* fn3) const
{
#if defined _DEBUG
	_ASSERTE((fn1 != nullptr) && (fn2 != nullptr) && (fn3 != nullptr));
#else
	if ((nullptr == fn1) || (nullptr == fn2) || (nullptr == fn3))
		BOOST_THROW_EXCEPTION(
		invalid_pointer() <<
		boost::errinfo_api_function("SawtoothMSignal::save_to_file") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	FILE *fp1, *fp2, *fp3;
	if ((fopen_s(&fp1, fn1, "wt") != 0) && (fopen_s(&fp2, fn2, "wt") != 0) && (fopen_s(&fp3, fn3, "wt") != 0))
	{
		BOOST_THROW_EXCEPTION(
			file_error() <<
			boost::errinfo_api_function("SawtoothMSignal::save_to_file") <<
			boost::errinfo_errno(errno) <<
			boost::errinfo_at_line(__LINE__));
	}
	else
	{
		std::printf("Started writing S(t) to file:%s\n", fn1);
		std::printf("Started writing r(t) to file:%s\n", fn2);
		std::printf("Started writing phi(t) to file:%s\n", fn3);
		for (std::size_t i{ 0 }; i != this->m_samples; ++i)
		{
			fprintf(fp1, "%.15f,%.15f\n", this->m_St.operator[](i).first, this->m_St.operator[](i).second);
			//fprintf(fp2, "%.15f,%.15f\n", this->m_St.operator[](i).first, this->m_rt.operator[](i));
			//fprintf(fp3, "%.15f,%.15f\n", this->m_St.operator[](i).first, this->m_phit.operator[](i));
		}
		std::printf("Finished writing S(t) to file:%s\n", fn1);
		std::printf("Finished writing r(t) to file:%s\n", fn2);
		std::printf("Finished writing phi(t) to file:%s\n", fn3);
		fclose(fp1);
		fclose(fp2);
		fclose(fp3);
	}
}
#endif

/*
@Brief: Computes signal IQ Decomposition.
@Params: _Inout_  vector to be initialized with IQ decomposed SawtoothMSignal , _In_  number of threads.

@Returns:  by argument std::vector<std::pair<double,double>> IQ initialized with SawtoothSignal IQ decomposition.
@Throws: BOOST_THROW_EXCEPTION when n_threads argument is <= 0 or when vector<std::pair<double,double>> IQ is empty.
*/
_Raises_SEH_exception_   void              radiolocation::SawtoothMSignal::quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &IQ, _In_ const int n_threads)
{
#if defined _DEBUG
	_ASSERTE(0 < n_threads);
#else
	if (0 > n_threads)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("SawtoothMSignal::quadrature_components_extraction") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif

	if (!(IQ.empty()))
	{
		// Define automatic variables in order to run OPENMP multi-threading, otherwise OPENMP on class members will not compile.
		std::size_t a_samples{ this->m_samples };
		_Field_size_(a_samples) std::vector<double> a_sin(a_samples);
		_Field_size_(a_samples) std::vector<double> a_cos(a_samples);
		_Field_size_(a_samples) std::vector<double> a_phi(this->m_phit);
		_Field_size_(a_samples) std::vector<std::pair<double, double>> a_St(this->m_St);
		std::size_t i;
		double a_init_time{ this->m_sinit_time };
		double a_timestep{ this->m_sinterval };
		double a_sfreq{ this->m_sfrequency };
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
			a_init_time += a_timestep;
			delta = static_cast<double>(i)* inv_samples;
			t = a_init_time * delta;
			a_cos.operator[](i) = 2.0 * ::cos((TWO_PI * a_sfreq * t) + a_phi.operator[](i));
			a_sin.operator[](i) = -2.0 * ::sin((TWO_PI * a_sfreq * t) + a_phi.operator[](i));
			IQ.operator[](i).operator=({ a_St.operator[](i).second * a_cos.operator[](i),
				a_St.operator[](i).second * a_sin.operator[](i) });
		}
#if defined OMP_TIMING
		double end{ wrapp_omp_get_wtime() };
		std::printf("SawtoothMSignal::quadrature_components_extraction executed in:%.15fseconds\n", end - start);
#endif
	}
	else  BOOST_THROW_EXCEPTION(
		empty_vector() <<
		boost::errinfo_api_function("SawtoothMSignal::quadrature_components_extraction: Failed") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
}

/*
@Brief: Computes signal complex envelope.
@Params: _In_  vector to be initialized with IQ decomposed SawtoothMSignal , _Out_
vector to be initialized with computed complex envelope values.

@Returns:  by argument _Out_ std::vector<double>  initialized with complex envelope values.
@Throws: BOOST_THROW_EXCEPTION when IQ is empty and when both vectors size does not match.
*/
_Raises_SEH_exception_  void            radiolocation::SawtoothMSignal::complex_envelope(_In_ std::vector<std::pair<double, double>> &IQ, _Out_ std::vector<double> &cenvelope)
{
	if (!(IQ.empty()) && (IQ.size() == cenvelope.size()))
	{
		double j_imag{ j().imag() };
		for (int i{ 0 }; i != IQ.size(); ++i)
			cenvelope.operator[](i) = IQ.operator[](i).first + (j_imag * IQ.operator[](i).second);
	}
	else BOOST_THROW_EXCEPTION(
		empty_vector() <<
		boost::errinfo_api_function("SawtoothMSignal::complex_envelope: !!FAILED!!") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
}

/*
@Brief: Computes analytic signal.
@Params: _In_  vector to be initialized with complex envelope SawtoothMSignal , _In_ number of OPENMP threads.


@Returns:  Modifies in-place *this.
@Throws: BOOST_THROW_EXCEPTION when complex_envelope is empty and when both vectors size does not match.
*/
_Raises_SEH_exception_  void        radiolocation::SawtoothMSignal::analytic_signal(_In_ const std::vector<double> &cenvelope, _In_ const int n_threads)
{
#if defined _DEBUG
	_ASSERTE((this->m_samples == static_cast<std::size_t>(cenvelope.size())) && (0 < n_threads));
#else
	if ((this->m_samples != static_cast<std::size_t>(cenvelope.size())) || (0 >= n_threads))
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("SawtoothMSignal::analytic_signal; Failed!!") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	if (!(cenvelope.empty()))
	{
		// Define automatic variables in order to use OPENMP multi-threading where class members are used.
		std::size_t a_samples{ this->m_samples };
		double j_imag{ j().imag() };
		_Field_size_(a_samples) std::vector<double> a_cos(a_samples);
		_Field_size_(a_samples) std::vector<double> a_sin(a_samples);
		_Field_size_(a_samples) std::vector<double> a_phi(this->m_phit);
		_Field_size_(a_samples) std::vector<std::pair<double, double>> a_St(a_samples);
		double a_init_time{ this->m_sinit_time };
		double a_timestep{ this->m_sinterval };
		double t{ 0.0 }; double delta{ 0.0 };
		double a_sfreq{ this->m_sfrequency };
		std::size_t i;
		double inv_samples{ 1.0 / static_cast<double>(a_samples) };
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
			a_cos.operator[](i) = ::cos((TWO_PI * a_sfreq * t) + a_phi.operator[](i));
			a_sin.operator[](i) = j_imag * ::sin((TWO_PI * a_sfreq * t) + a_phi.operator[](i));
			a_St.operator[](i).operator=({ t, (cenvelope.operator[](i) * a_cos.operator[](i)) +
				(cenvelope.operator[](i) * a_sin.operator[](i)) });
		}
#if defined OMP_TIMING
		double end{ wrapp_omp_get_wtime() };
		std::printf("SawtoothMSignal::analytic_signal executed in:%.15fseconds\n", end - start);
#endif
		this->m_St.operator=(std::move(a_St));
	}
	else BOOST_THROW_EXCEPTION(
		empty_vector() <<
		boost::errinfo_api_function("SawtoothMSignal::analytic_signal: Failed!!") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
}

/*
@Brief: Computes signal instantaneous frequency.
*/
_Raises_SEH_exception_  void         radiolocation::SawtoothMSignal::instantaneous_frequency(_Inout_ std::vector<double> &ifreq)
{
#if defined _DEBUG
	_ASSERTE(this->m_samples == static_cast<std::size_t>(ifreq.size()));
#else
	if (this->m_samples != static_cast<std::size_t>(ifreq.size()))
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("SawtoothMSignal::instantaneous_frequency") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	double inv_2pi{ mathlib::MathConstants::INV_TWO_PI_DBL() };
	for (std::size_t i{ 0 }; i != this->m_samples; ++i)
	{
		double x{ this->m_St.operator[](i).first };
		auto dt = mathlib::DyDx<double>::differentiate2([&](double arg)->double { return ((TWO_PI * this->get_sfrequency() * x) +
			this->get_phit()[i]); }, x, x);
		ifreq.operator[](i) = inv_2pi * dt.get_deriv();
	}
}

std::vector<std::pair<double, double>>      radiolocation::SawtoothMSignal::pulse_samples() const
{
	return this->get_St();
}

std::vector<double>                         radiolocation::SawtoothMSignal::pulse_phase() const
{
	return this->get_phit();
}

std::size_t                                 radiolocation::SawtoothMSignal::pulse_samples_count() const
{
	return  this->get_samples();
}


/*
@ TODO:
Implement later.
*/

void          radiolocation::SawtoothMSignal::amplitude_modulation(const double a, const double b, const double c)
{
	; // To be implemented later
}

void          radiolocation::SawtoothMSignal::frequency_modulation(double a, size_t n)
{
	; // To be implemented later.
}

void          radiolocation::SawtoothMSignal::phase_modulation(const double a, const double b, const double c, std::function<double(double, double)> &f)
{
	; // To be implemented later.
}

/*
Brief: Sawtooth static function which returns number of S(t) cycles.


@Params: None
@Returns: number of cycles of S(t) Sawtooth waveform.
@throws: Nothing
*/
double                   radiolocation::SawtoothMSignal::StCycles(_In_ const std::size_t samples, _In_ const double interval)
{
	return (0.5 * (static_cast<double>(samples) * interval));
}

/*
Brief: Sawtooth static function which returns number of r(t) cycles.


@Params: None
@Returns: number of cycles of r(t) Sawtooth waveform.
@throws: Nothing
*/
double                   radiolocation::SawtoothMSignal::RtCycles(_In_ const std::size_t samples, _In_ const double interval)
{
	return (0.5 * (static_cast<double>(samples)* interval));
}

/*
Brief: Sawtooth static function which returns number of phi(t) cycles.


@Params: None
@Returns: number of cycles of phi(t) Sawtooth waveform.
@throws: Nothing
*/
double                    radiolocation::SawtoothMSignal::PhitCycles(_In_ const std::size_t samples, _In_ const double interval)
{
	return (0.5 * (static_cast<double>(samples) * interval));
}