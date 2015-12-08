/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Cosine Doppler Shift class - implementation.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/
#include "PureCosineDopplerShift.h"
#include "LibExceptions.h"
#include "../MathLib/MathConstants.h"
#include "../MathLib/Derivative.h"





radiolocation::PureCosDopplerShifted::PureCosDopplerShifted(_In_ struct PCDSParams const& p) :
m_dAmplitude{ p.Amplitude },
m_dF0{ p.Frequency },
m_dInitTime{ p.InitTime },
m_dTargetRange{ p.Range },
m_dTargetVelocity{ p.Velocity },
m_dTimeStep{ p.TimeStep },
m_uiSamplesCount{ p.SamplesCount },
m_oPolarization{ radiolocation::JonesVector(std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 1.0)) },
m_oTargetDirection{0.0,0.0,p.TargetDirection,std::numeric_limits<double>::quiet_NaN()},
m_dTargetRadarAngle{ p.TragetRadarAngle }
{
#if defined _DEBUG
	_ASSERTE(this->m_dTimeStep > 0.0 && this->m_uiSamplesCount > 32);
#else
	if (0.0 > this->m_dTimeStep || 32 > this->m_uiSamplesCount)
		BOOST_THROW_EXCEPTION(invalid_value_arg() <<
		boost::errinfo_api_function("Invalid argument in PureCosDopplerShift") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif

	//define automatic variables for OPENMP multithreading.
	double a_Amplitude{ this->m_dAmplitude };
	double a_InitTime{ this->m_dInitTime };
	double a_TimeStep{ this->m_dTimeStep };
	double a_TargetVelocity{ this->m_dTargetVelocity };
	double a_TargetRange{ this->m_dTargetRange };
	std::size_t a_SamplesCount{ this->m_uiSamplesCount };
	std::size_t i;
	_Field_size_(a_SamplesCount) std::vector<std::pair<double, double>> a_PCDS(a_SamplesCount);
	_Field_size_(a_SamplesCount) std::vector<double>  a_PhaseArg(a_SamplesCount);
	double delta{ 0.0 }; double t{ 0.0 };
	double InvSamplesCount{ 1.0 / static_cast<double>(a_SamplesCount) };
	double a_F0{ this->m_dF0 };
	omp_set_num_threads(p.ThreadCount);
#if defined OMP_TIMING
	double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t) reduction(+:a_TimeStep)
	for (i = 0; i < a_SamplesCount; ++i)
	{
		a_InitTime += a_TimeStep;
		delta = static_cast<double>(i)* InvSamplesCount;
		t = a_InitTime * delta;
		a_PhaseArg.operator[](i) = radiolocation_constants::TWOPI *(a_F0 * t - (a_F0 * 2.0*a_TargetRange * radiolocation_constants::inv_c) +
			(2.0 * a_F0 * a_TargetVelocity * t * radiolocation_constants::inv_c));
		a_PCDS.operator[](i).operator=({ t, a_Amplitude * ::cos(a_PhaseArg.operator[](i)) });
	}
#if defined OMP_TIMING
	double end{ wrapp_omp_get_wtime() };
	std::printf("PureCosineDopplerShift C-tor executed in:%.15fseconds\n", (end - start));
#endif

	this->m_dInitTargetDetRange = (radiolocation_constants::TWOPI * this->m_dF0 * 2.0 * this->m_dTargetRange) / radiolocation_constants::c;
	double gamma = this->m_dF0 / radiolocation_constants::c;
	// x == -1.0 for incoming direction, x == 1.0 for outgoing direction.
	if (std::fabs(this->m_dTargetRadarAngle) == 0.0)
		this->m_oTargetDirection.operator[](0) < 0.0 ? this->m_dDopplerFrequency = (2.0 * this->m_dF0 * this->m_dTargetVelocity) / radiolocation_constants::c :
		this->m_dDopplerFrequency = -(2.0 * this->m_dF0 * this->m_dTargetVelocity) / radiolocation_constants::c;
	else
		this->m_oTargetDirection.operator[](0) < 0.0 ? this->m_dDopplerFrequency = (2.0 * this->m_dTargetVelocity * ::cos(this->m_dTargetRadarAngle)) / gamma :
		this->m_dDopplerFrequency = -(2.0 * this->m_dTargetVelocity * ::cos(this->m_dTargetRadarAngle)) / gamma;

	this->m_oPureCosDopplerShift = std::vector<std::pair<double, double>>(std::move(a_PCDS));
	this->m_oPhaseArg = std::vector<double>(std::move(a_PhaseArg));

}


radiolocation::PureCosDopplerShifted::PureCosDopplerShifted(_In_ PureCosDopplerShifted const& other) :
m_oTargetDirection{ other.m_oTargetDirection },
m_dAmplitude{ other.m_dAmplitude },
m_dDopplerFrequency{ other.m_dDopplerFrequency },
m_dF0{ other.m_dF0 },
m_dInitTargetDetRange{ other.m_dInitTargetDetRange },
m_dInitTime{ other.m_dInitTime },
m_dTargetRadarAngle{ other.m_dTargetRadarAngle },
m_dTargetVelocity{ other.m_dTargetVelocity },
m_dTargetRange{ other.m_dTargetRange },
m_dTimeStep{ other.m_dTimeStep },
m_oPhaseArg{ other.m_oPhaseArg },
m_oPolarization{ other.m_oPolarization },
m_oPureCosDopplerShift{ other.m_oPureCosDopplerShift },
m_uiSamplesCount{ other.m_uiSamplesCount }
{

}

radiolocation::PureCosDopplerShifted::PureCosDopplerShifted(_In_ PureCosDopplerShifted &&other) :
m_oTargetDirection{ std::move(other.m_oTargetDirection) },
m_dAmplitude{ std::move(other.m_dAmplitude) },
m_dDopplerFrequency{ std::move(other.m_dDopplerFrequency) },
m_dF0{ std::move(other.m_dF0) },
m_dInitTargetDetRange{ std::move(other.m_dInitTargetDetRange) },
m_dInitTime{ std::move(other.m_dInitTime) },
m_dTargetRadarAngle{ std::move(other.m_dTargetRadarAngle) },
m_dTargetRange{ std::move(other.m_dTargetRange) },
m_dTargetVelocity{ std::move(other.m_dTargetVelocity) },
m_dTimeStep{ std::move(other.m_dTimeStep) },
m_oPhaseArg{ std::move(other.m_oPhaseArg) },
m_oPolarization{ std::move(other.m_oPolarization) },
m_oPureCosDopplerShift{ std::move(other.m_oPureCosDopplerShift) },
m_uiSamplesCount{ std::move(other.m_uiSamplesCount) }
{

}

radiolocation::PureCosDopplerShifted::~PureCosDopplerShifted()
{

}

radiolocation::PureCosDopplerShifted &        radiolocation::PureCosDopplerShifted::operator=(_In_ PureCosDopplerShifted const& other)
{
	if (this == &other) return *this;

	this->m_oTargetDirection.operator=( other.m_oTargetDirection);
	this->m_dAmplitude = other.m_dAmplitude;
	this->m_dDopplerFrequency = other.m_dDopplerFrequency;
	this->m_dF0 = other.m_dF0;
	this->m_dInitTargetDetRange = other.m_dInitTargetDetRange;
	this->m_dInitTime = other.m_dInitTime;
	this->m_dTargetRadarAngle = other.m_dTargetRadarAngle;
	this->m_dTargetRange = other.m_dTargetRange;
	this->m_dTargetVelocity = other.m_dTargetVelocity;
	this->m_dTimeStep = other.m_dTimeStep;
	if (!(this->m_oPhaseArg.empty()))
		this->m_oPhaseArg.clear();
	this->m_oPhaseArg.operator=(other.m_oPhaseArg);
	if (!(this->m_oPureCosDopplerShift.empty()))
		this->m_oPureCosDopplerShift.clear();
	this->m_oPureCosDopplerShift.operator=(other.m_oPureCosDopplerShift);
	this->m_oPolarization.operator=(other.m_oPolarization);
	this->m_uiSamplesCount = other.m_uiSamplesCount;
	return *this;
}

radiolocation::PureCosDopplerShifted &             radiolocation::PureCosDopplerShifted::operator=(_In_ PureCosDopplerShifted && other)
{
	if (this == &other) return *this;

	this->m_oTargetDirection.operator=( std::move(other.m_oTargetDirection));
	this->m_dAmplitude = std::move(other.m_dAmplitude);
	this->m_dDopplerFrequency = std::move(other.m_dDopplerFrequency);
	this->m_dF0 = std::move(other.m_dF0);
	this->m_dInitTargetDetRange = std::move(other.m_dInitTargetDetRange);
	this->m_dInitTime = std::move(other.m_dInitTime);
	this->m_dTargetRadarAngle = std::move(other.m_dTargetRadarAngle);
	this->m_dTargetRange = std::move(other.m_dTargetRange);
	this->m_dTargetVelocity = std::move(other.m_dTargetVelocity);
	this->m_dTimeStep = std::move(other.m_dTimeStep);
	this->m_oPolarization.operator=(std::move(other.m_oPolarization));
	if (!(this->m_oPhaseArg.empty()))
		this->m_oPhaseArg.clear();
	this->m_oPhaseArg.operator=(std::move(other.m_oPhaseArg));
	if (!(this->m_oPureCosDopplerShift.empty()))
		this->m_oPureCosDopplerShift.clear();
	this->m_oPureCosDopplerShift.operator=(std::move(other.m_oPureCosDopplerShift));
	this->m_uiSamplesCount = std::move(other.m_uiSamplesCount);
	return *this;
}

std::ostream &            radiolocation::operator<<(_In_ std::ostream &os, _In_ PureCosDopplerShifted const& rhs)
{
	os.scientific;
	std::setprecision(15);
	os << "DopplerFrequency:" << rhs.m_dDopplerFrequency << "InitTargetDetRange:" << rhs.m_dInitTargetDetRange << std::endl;
	for (std::size_t i{ 0 }; i != rhs.m_uiSamplesCount; ++i)
		os << "S(phi(t)):" << rhs.m_oPureCosDopplerShift.operator[](i).second << "phi(t):" << rhs.m_oPhaseArg.operator[](i) <<
		"t:" << rhs.m_oPureCosDopplerShift.operator[](i).first << std::endl;
	return os;
}

std::pair<double, double>      radiolocation::PureCosDopplerShifted::operator[](_In_ const std::size_t index)
{
	BOOST_ASSERT_MSG(index >= 0 && index <= this->m_uiSamplesCount, "Index out of bound in PureCosDopplerShifted::operator[]");
	return this->m_oPureCosDopplerShift.operator[](index);
}

const  std::pair<double, double>    radiolocation::PureCosDopplerShifted::operator[](_In_ const std::size_t index) const
{
	BOOST_ASSERT_MSG(index >= 0 && index <= this->m_uiSamplesCount, "Index out of bound in PureCosDopplerShifted::operator[] const");
	return this->m_oPureCosDopplerShift.operator[](index);
}
	
std::vector<std::pair<std::size_t, double>>    radiolocation::PureCosDopplerShifted::operator==(_In_ PureCosDopplerShifted const& other) const
{
	BOOST_ASSERT_MSG(this->m_uiSamplesCount == other.m_uiSamplesCount, "Invalid SamplesCount in PureCosDopplerShifted::operator==");
	std::vector<std::pair<std::size_t, double>> vresults;
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
	{
		if ((std::fabs(this->m_oPureCosDopplerShift[i].second) - std::fabs(other.m_oPureCosDopplerShift[i].second)) <= std::numeric_limits<double>::epsilon())
			vresults.push_back({ i, this->m_oPureCosDopplerShift[i].second }); // push_back almost equal values
		else
			vresults.push_back({ i, this->m_oPureCosDopplerShift[i].second }); // push_back not equal values
	}
	return vresults;
}


std::vector<std::pair<std::size_t, double>>    radiolocation::PureCosDopplerShifted::operator!=(_In_ PureCosDopplerShifted const& other) const
{
	BOOST_ASSERT_MSG(this->m_uiSamplesCount == other.m_uiSamplesCount, "Invalid SamplesCount in PureCosDopplerShifted::operator!=");
	std::vector<std::pair<std::size_t, double>> vresults;
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
	{
		if ((std::fabs(this->m_oPureCosDopplerShift[i].second) - std::fabs(other.m_oPureCosDopplerShift[i].second)) > std::numeric_limits<double>::epsilon())
			vresults.push_back({ i, this->m_oPureCosDopplerShift[i].second }); // push_back not equal values
		else
			vresults.push_back({ i, this->m_oPureCosDopplerShift[i].second }); // push_back almost equal values
	}
	return vresults;
}

std::vector<std::pair<double, double>>      radiolocation::operator==(_In_ PureCosDopplerShifted const& lhs, _In_ PureCosDopplerShifted const& rhs)
{
	BOOST_ASSERT_MSG(lhs.m_uiSamplesCount == rhs.m_uiSamplesCount, "Invalid SamplesCount in radiolocation::operator==");
	std::vector<std::pair<double, double>> vresults;
	for (std::size_t i{ 0 }; i != lhs.m_uiSamplesCount; ++i)
	{
		if ((std::fabs(lhs.m_oPureCosDopplerShift[i].second) - std::fabs(rhs.m_oPureCosDopplerShift[i].second)) <= std::numeric_limits<double>::epsilon())
			vresults.push_back({ lhs.m_oPureCosDopplerShift[i].second, rhs.m_oPureCosDopplerShift[i].second }); // push_back almost equal pairs.
		else
			vresults.push_back({lhs.m_oPureCosDopplerShift[i].second, rhs.m_oPureCosDopplerShift[i].second }); // push_back non equal pairs.
	}
	return vresults;
}

std::vector<std::pair<double, double>>        radiolocation::operator!=(_In_ PureCosDopplerShifted const& lhs, _In_ PureCosDopplerShifted const& rhs)
{
	BOOST_ASSERT_MSG(lhs.m_uiSamplesCount == rhs.m_uiSamplesCount, "Invalid SamplesCount in radiolocation::operator!=");
	std::vector<std::pair<double, double>> vresults;
	for (std::size_t i{ 0 }; i != lhs.m_uiSamplesCount; ++i)
	{
		if ((std::fabs(lhs.m_oPureCosDopplerShift[i].second) - std::fabs(rhs.m_oPureCosDopplerShift[i].second)) > std::numeric_limits<double>::epsilon())
			vresults.push_back({ lhs.m_oPureCosDopplerShift[i].second, rhs.m_oPureCosDopplerShift[i].second }); // push_back not equal pairs.
		else
			vresults.push_back({ lhs.m_oPureCosDopplerShift[i].second, rhs.m_oPureCosDopplerShift[i].second }); // push_back almost equal pairs.
	}
	return vresults;
}

#if defined  _DEBUG
void             radiolocation::PureCosDopplerShifted::debug_print() const
{
	std::printf("PureCosDopplerShifted::debug_print: Executed\n");
	std::printf("&this->m_dAmplitude=%p,this->m_dAmplitude=%.9f\n", &this->m_dAmplitude, this->m_dAmplitude);
	std::printf("&this->m_dDopplerFrequency=%p, this->m_dDopplerFrequency=%.9f\n", &this->m_dDopplerFrequency, this->m_dDopplerFrequency);
	std::printf("&this->m_dF0=%p,this->m_dF0=%.9f\n", &this->m_dF0, this->m_dF0);
	std::printf("&this->m_dInitTargetDetRange=%p,this->m_dInitTargetDetRange=%.9f\n", &this->m_dInitTargetDetRange, this->m_dInitTargetDetRange);
	std::printf("&this->m_dInitTime=%p,this->m_dInitTime=%.9f\n", &this->m_dInitTime, this->m_dInitTime);
	std::printf("&this->m_dTargetRadarAngle=%p,this->m_dTargetRadarAngle=%.9f\n", &this->m_dTargetRadarAngle, this->m_dTargetRadarAngle);
	std::printf("&this->m_dTargetRange=%p,this->m_dTargetRange=%.9f\n", &this->m_dTargetRange, this->m_dTargetRange);
	std::printf("&this->m_dTargetVelocity=%p,this->m_dTargetVelocity=%.9f\n", &this->m_dTargetVelocity, this->m_dTargetVelocity);
	std::printf("&this->_dTimeStep=%p,this->m_dTimeStep=%.9f\n", &this->m_dTimeStep, this->m_dTimeStep);
	std::printf("&this->m_dPolarization=%p,this->m_oPolarization=%.9f\n", &this->m_oPolarization,this->m_oPolarization.v().imag());
	std::printf("&this->m_uiSamplesCount=%p,this->m_uiSamplesCount=%u\n", &this->m_uiSamplesCount, this->m_uiSamplesCount);
	std::printf("&this->m_oTargetDirection=%p,this->m_oTargetDirection=%.9f\n", &this->m_oTargetDirection, this->m_oTargetDirection.operator[](0));
	std::printf(" S(phi(t)):    |        phi(t):       |         t:  \n");
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
		std::printf("%.9f, %.9f, %.9f\n", this->m_oPureCosDopplerShift[i].second, this->m_oPhaseArg[i], this->m_oPureCosDopplerShift[i].first);
}
#endif

#if defined MATHEMATICA_VISUALIZE
void              radiolocation::PureCosDopplerShifted::save_to_file(_In_z_ const char* fname1, _In_z_ const char* fname2) const
{
#if  defined _DEBUG
	_ASSERTE(fname1 != nullptr && fname2 != nullptr);
#else
	if (fname1 == nullptr || fname2 == nullptr)
		BOOST_THROW_EXCEPTION(invalid_pointer() <<
		boost::errinfo_api_function("Invalid Pointer in PureCosDopplerShifted::save_to_file") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	FILE *fp1, *fp2;
	if ((fopen_s(&fp1, fname1, "wt") != 0) && (fopen_s(&fp2, fname2, "wt") != 0))
	{
		BOOST_THROW_EXCEPTION( 
			file_error() <<
			boost::errinfo_api_function("Failed open file in PureCosDopplerShift::save_to_file") <<
			boost::errinfo_errno(errno) <<
			boost::errinfo_at_line(__LINE__));
	}
	else
	{
		std::printf("Writing content of S(phi(t) to file:%s\n", fname1);
		std::printf("Writing content of phi(t) to file:%s\n", fname2);
		for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
		{
			std::fprintf(fp1, "%.15f,%.15f\n", this->m_oPureCosDopplerShift.operator[](i).first, this->m_oPureCosDopplerShift.operator[](i).second);
			std::fprintf(fp2, "%.15f,%.15f\n", this->m_oPureCosDopplerShift.operator[](i).first, this->m_oPhaseArg.operator[](i));
		}
		std::printf("Finished writing the content of Cos(phi(t)) to file:%s\n", fname1);
		std::printf("Finished writing the content of phi(t) to file:%s\n", fname2);
		fclose(fp1);
		fclose(fp2);
	}
}
#endif

void                    radiolocation::PureCosDopplerShifted::quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &IQ, _In_ const int nThreads)
{
#if !defined _DEBUG
	_ASSERTE(0 < nThreads);
#else
	if (0 > nThreads)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("Invalid arg in PureCosDopplerShifted::quadrature_components_extraction") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	if (!(IQ.empty()))
	{
		std::size_t a_SamplesCount{ this->m_uiSamplesCount };
		_Field_size_(a_SamplesCount) std::vector<double> a_Sin(a_SamplesCount);
		_Field_size_(a_SamplesCount) std::vector<double> a_Cos(a_SamplesCount);
		_Field_size_(a_SamplesCount) std::vector<double> a_Phi(this->m_oPhaseArg);
		_Field_size_(a_SamplesCount) std::vector<std::pair<double, double>> a_CDS(this->m_oPureCosDopplerShift);
		std::size_t i;
		double  a_F0{ this->m_dF0 };
		double  a_InitTime{ this->m_dInitTime };
		double  a_TimeStep{ this->m_dTimeStep };
		double  InvSamplesCount{ 1.0 / static_cast<double>(a_SamplesCount) };
		double Delta{ 0.0 }; double t{ 0.0 };
		omp_set_num_threads(nThreads);
#if defined OMP_TIMING
		double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp  parallel for default(shared) schedule(runtime) \
	private(i, Delta, t) reduction(+:a_InitTime)
		for (i = 0; i < a_SamplesCount; ++i)
		{
			a_InitTime += a_TimeStep;
			Delta = static_cast<double>(i)* InvSamplesCount;
			t = a_InitTime * Delta;
			a_Cos.operator[](i) = 2.0 * ::cos((radiolocation_constants::TWOPI * a_F0 * t) + a_Phi.operator[](i));
			a_Sin.operator[](i) = -2.0 * ::sin((radiolocation_constants::TWOPI * a_F0 * t) + a_Phi.operator[](i));
			IQ.operator[](i).operator=({ a_CDS.operator[](i).second * a_Cos.operator[](i), a_CDS.operator[](i).second *
				a_Sin.operator[](i) });
		}
#if defined OMP_TIMING
		double end{ wrapp_omp_get_wtime() };
		std::printf("PureCosDopplerShifted::quadrature_components_extraction - Executed in %.9fseconds\n", end - start);
#endif

	}
	else BOOST_THROW_EXCEPTION(empty_vector() <<
		boost::errinfo_api_function("Empty vector in PureCosDopplerShifted::quadrature_components_extraction") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
}

_Raises_SEH_exception_   void         radiolocation::PureCosDopplerShifted::complex_envelope(_In_ std::vector<std::pair<double, double>> &IQ, _Out_ std::vector<double> &complex_env)
{
	if ((!(IQ.empty()) && (complex_env.size() == IQ.size())))
	{
		double j_imag{ j().imag() };
		for (int i{ 0 }; i != IQ.size(); ++i)
			complex_env.operator[](i) = IQ.operator[](i).first + (j_imag * IQ.operator[](i).second);
	}
	else BOOST_THROW_EXCEPTION(empty_vector() <<
		boost::errinfo_api_function("Empty vector in PureCosDopplerShifted::complex_envelop") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
}

_Raises_SEH_exception_    void         radiolocation::PureCosDopplerShifted::analytic_signal(_In_ std::vector<double> const& complex_env, _In_ const int nThreads)
{
#if defined _DEBUG
	_ASSERTE((0 < nThreads) && (this->m_uiSamplesCount == static_cast<std::size_t>(complex_env.size())));
#else
	if ((0 > nThreads) || (this->m_uiSamplesCount != static_cast<std::size_t>(complex_env.size())))
		BOOST_THROW_EXCEPTION(invalid_value_arg() <<
		boost::errinfo_api_function("Invalid arg in PureCosDopplerShifted::analytic_signal") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	if (!(complex_env.empty()))
	{
		std::size_t a_SamplesCount{ this->m_uiSamplesCount };
		double j_imag{ j().imag() };
		double a_F0{ this->m_dF0 };
		double a_InitTime{ this->m_dInitTime };
		double a_TimeStep{ this->m_dTimeStep };
		_Field_size_(a_SamplesCount) std::vector<double> a_Sin(a_SamplesCount);
		_Field_size_(a_SamplesCount) std::vector<double> a_Cos(a_SamplesCount);
		_Field_size_(a_SamplesCount) std::vector<std::pair<double, double>> a_CDS(a_SamplesCount);
		_Field_size_(a_SamplesCount) std::vector<double> a_Phi(this->m_oPhaseArg);
		double delta{ 0.0 }; double t{ 0.0 };
		double InvSamplesCount{ 1.0 / static_cast<double>(a_SamplesCount) };
		std::size_t i;
		omp_set_num_threads(nThreads);
#if defined OMP_TIMING
		double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp  parallel for default(shared) schedule(runtime) \
	private(i, delta, t) reduction(+:a_InitTime)
		for (i = 0; i < a_SamplesCount; ++i)
		{
			a_InitTime += a_TimeStep;
			delta = static_cast<double>(i)* InvSamplesCount;
			t = delta * a_InitTime;
			a_Cos.operator[](i) = ::cos((radiolocation_constants::TWOPI * a_F0* t) + a_Phi.operator[](i));
			a_Sin.operator[](i) = j_imag * ::sin((radiolocation_constants::TWOPI * a_F0 * t) + a_Phi.operator[](i));
			a_CDS.operator[](i).operator=({ t, (complex_env.operator[](i) * a_Cos.operator[](i)) +
				(complex_env.operator[](i) *	a_Sin.operator[](i)) });
		}
#if defined OMP_TIMING
		double end{ wrapp_omp_get_wtime() };
		std::printf("PureCosDopplerShifted::analytic_signal - Executed in %.9fseconds\n", end - start);
#endif
		this->m_oPureCosDopplerShift.operator=(std::move(a_CDS));
	}
	else  BOOST_THROW_EXCEPTION(invalid_value_arg() <<
		boost::errinfo_api_function("Invalid arg in PureCosDopplerShifted::analytic_signal") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
}

_Raises_SEH_exception_    void     radiolocation::PureCosDopplerShifted::instantaneous_frequency(_Inout_ std::vector<double> &InstFrequency)
{
#if defined _DEBUG
	_ASSERTE(this->m_uiSamplesCount == static_cast<std::size_t>(InstFrequency.size()));
#else
	if (this->m_uiSamplesCount != static_cast<std::size_t>(InstFrequency.size()))
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("Invalid arg in PureCosDopplerShifted::instantenous_frequency") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif

	double inv_2pi{ mathlib::MathConstants::INV_TWO_PI_DBL() };
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
	{
		double x{ this->m_oPureCosDopplerShift.operator[](i).first };
		auto dt = mathlib::DyDx<double>::differentiate2([&](double arg)->double{return ((radiolocation_constants::TWOPI*this->F0()*x) +
			this->PhaseArg()[i]); }, x, x);
		InstFrequency.operator[](i) = inv_2pi * dt.get_deriv();
	}
}

std::vector<std::pair<double, double>>   radiolocation::PureCosDopplerShifted::pulse_samples() const
{
	return this->PureCosDopplerShift();
}

std::vector<double>                      radiolocation::PureCosDopplerShifted::pulse_phase() const
{
	return this->PhaseArg();
}

std::size_t                              radiolocation::PureCosDopplerShifted::pulse_samples_count() const
{
	return this->SamplesCount();
}

void          radiolocation::PureCosDopplerShifted::amplitude_modulation(const double a, const double b, const double c)
{
	; // To be implemented later
}

void          radiolocation::PureCosDopplerShifted::frequency_modulation(double a, size_t n)
{
	; // To be implemented later.
}

void          radiolocation::PureCosDopplerShifted::phase_modulation(const double a, const double b, const double c, std::function<double(double, double)> &f)
{
	; // To be implemented later.
}