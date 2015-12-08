/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Cosine Multiple Target Return class - implementation.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

#include "PureCosMultiTargetReturn.h"
#include "../MathLib/MathConstants.h"
#include "LibExceptions.h"

namespace rc2 = radiolocation_constants;

radiolocation::PCWaveTwoTargetReturn::PCWaveTwoTargetReturn(_In_ struct PureCosineParams const& p1, _In_ struct PCTTRParams const& p2) : 
PureCosineWave{ p1 },
m_dAmplitude1{ p2.Ampitude1 },
m_dAmplitude2{ p2.Amplitude2 },
m_dCentralFrequency{ this->m_frequency },
m_uiSamplesCount{this->m_samples},
m_dTarget1Range{ p2.Target1Range },
m_dTraget2Range{ p2.Target2Range },
m_dPsi{0.0},
m_dTwoTargetRCS{0.0}
{
	//this->m_oPCTwoTargetReturn = std::vector<std::pair<double, double>>(this->m_uiSamplesCount);
	//this->m_oPhase = std::vector<double>(this->m_uiSamplesCount);

	// automatic variables for OPENMP Multithreading.
	std::size_t a_SamplesCount{ this->m_uiSamplesCount };
	std::vector<std::pair<double, double>> a_PCTTR(a_SamplesCount);
	std::vector<std::pair<double, double>> a_PCTx(this->m_cos);
	std::vector<double> a_PhaseTx(this->m_phase);
	std::vector<double> a_PhaseRx(a_SamplesCount);
	std::size_t i;
	this->m_dToA1 =  2.0 * this->m_dTarget1Range * rc2::inv_c;
	this->m_dToA2 = 2.0 * this->m_dTraget2Range * rc2::inv_c;
	double phi{ (this->m_dCentralFrequency * this->m_dToA1) - (this->m_dCentralFrequency * this->m_dToA2) };
	double sum_amplitudes{ this->m_dAmplitude1 + this->m_dAmplitude2 };
	double diff_amplitudes{ this->m_dAmplitude1 - this->m_dAmplitude2 };
	double psi_term1{ this->m_dCentralFrequency * (this->m_dToA1 + this->m_dToA2) * 0.5 };
	double psi_term2{ ::atan((sum_amplitudes / diff_amplitudes) * ::tan(0.5*phi)) };
	this->m_dPsi =  psi_term1 + psi_term2;
	double Amplitude1Squared{ this->m_dAmplitude1 * this->m_dAmplitude1 };
	double Amplitude2Squared{ this->m_dAmplitude2 * this->m_dAmplitude2 };
	double Eret{ std::sqrt(Amplitude1Squared + Amplitude2Squared + 2.0 * this->m_dAmplitude1 * this->m_dAmplitude2 * ::cos(phi)) };
	double t2{ 0.0 }; double delta{ 0.0 };
	double InvSamplesCount{ 1.0 / static_cast<double>(this->m_uiSamplesCount) };
	double InitTime{ 0.0 };
	omp_set_num_threads(p2.nThreads);
#if defined OMP_TIMING
	double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, t2, delta) reduction(+:InitTime)
	for ( i = 0; i < a_SamplesCount; ++i)
	{
		InitTime += this->m_dPsi;
		delta = static_cast<double>(i)* InvSamplesCount;
		t2 = delta * InitTime;
		a_PhaseRx.operator[](i) = a_PhaseTx.operator[](i) - t2;
		//this->m_oPhase.operator[](i) = this->m_phase.operator[](i) - t2;
		//this->m_oPCTwoTargetReturn.operator[](i).operator=({ this->m_cos.operator[](i).first, Eret * ::cos(this->m_oPhase.operator[](i)) });
		a_PCTTR.operator[](i).operator=({ a_PCTx.operator[](i).first, Eret * ::cos(a_PhaseRx.operator[](i)) });
	}
#if defined OMP_TIMING
	double end{ wrapp_omp_get_wtime() };
	std::printf("PCWaveTwoTargetReturn C-tor executed in: %.9fsecond\n", end - start);
#endif
	this->m_oPhase = std::vector<double>(std::move(a_PhaseRx));
	this->m_oPCTwoTargetReturn = std::vector<std::pair<double, double>>(std::move(a_PCTTR));
	double Esent{ this->m_amplitude * this->m_amplitude };
	this->m_dTwoTargetRCS = 4.0 * mathlib::MathConstants::PI_DBL() * this->m_dTarget1Range * this->m_dTraget2Range * (Eret / Esent);
}


radiolocation::PCWaveTwoTargetReturn::PCWaveTwoTargetReturn(_In_ PCWaveTwoTargetReturn const& other) :
m_dAmplitude1{ other.m_dAmplitude1 },
m_dAmplitude2{ other.m_dAmplitude2 },
m_dCentralFrequency{ other.m_dCentralFrequency },
m_dTarget1Range{ other.m_dTarget1Range },
m_dToA1{ other.m_dToA1 },
m_dToA2{ other.m_dToA2 },
m_dTraget2Range{ other.m_dTraget2Range },
m_dTwoTargetRCS{ other.m_dTwoTargetRCS },
m_dPsi{other.m_dPsi},
m_uiSamplesCount{other.m_uiSamplesCount},
m_oPCTwoTargetReturn{ other.m_oPCTwoTargetReturn },
m_oPhase{ other.m_oPhase }
{

}

radiolocation::PCWaveTwoTargetReturn::PCWaveTwoTargetReturn(_In_ PCWaveTwoTargetReturn &&other) :
m_dAmplitude1{ std::move(other.m_dAmplitude1) },
m_dAmplitude2{ std::move(other.m_dAmplitude2) },
m_dCentralFrequency{ std::move(other.m_dCentralFrequency) },
m_dTarget1Range{ std::move(other.m_dTarget1Range) },
m_dToA1{ std::move(other.m_dToA1) },
m_dToA2{ std::move(other.m_dToA2) },
m_dTraget2Range{ std::move(other.m_dTraget2Range) },
m_dTwoTargetRCS{ std::move(other.m_dTwoTargetRCS) },
m_dPsi{ std::move(other.m_dPsi) },
m_uiSamplesCount{ std::move(other.m_uiSamplesCount) },
m_oPCTwoTargetReturn{ std::move(other.m_oPCTwoTargetReturn) },
m_oPhase{ std::move(other.m_oPhase) }
{

}

radiolocation::PCWaveTwoTargetReturn::~PCWaveTwoTargetReturn()
{

}

radiolocation::PCWaveTwoTargetReturn &      radiolocation::PCWaveTwoTargetReturn::operator=(_In_ PCWaveTwoTargetReturn const& other)
{
	if (this == &other) return *this;

	this->m_dAmplitude1 = other.m_dAmplitude1;
	this->m_dAmplitude2 = other.m_dAmplitude2;
	this->m_dCentralFrequency = other.m_dCentralFrequency;
	this->m_dTarget1Range = other.m_dTarget1Range;
	this->m_dToA1 = other.m_dToA1;
	this->m_dToA2 = other.m_dToA2;
	this->m_dTraget2Range = other.m_dTraget2Range;
	this->m_dTwoTargetRCS = other.m_dTwoTargetRCS;
	this->m_dPsi = other.m_dPsi;
	this->m_uiSamplesCount = other.m_uiSamplesCount;
	if (!(this->m_oPCTwoTargetReturn.empty())) this->m_oPCTwoTargetReturn.clear();
		
	this->m_oPCTwoTargetReturn.operator=(other.m_oPCTwoTargetReturn);
	if (!(this->m_oPhase.empty())) this->m_oPhase.clear();
		
	this->m_oPhase.operator=(other.m_oPhase);
	return *this;
}

radiolocation::PCWaveTwoTargetReturn &       radiolocation::PCWaveTwoTargetReturn::operator=(_In_ PCWaveTwoTargetReturn &&other)
{
	if (this == &other) return *this;

	this->m_dAmplitude1 = std::move(other.m_dAmplitude1);
	this->m_dAmplitude2 = std::move(other.m_dAmplitude2);
	this->m_dCentralFrequency = std::move(other.m_dCentralFrequency);
	this->m_dTarget1Range = std::move(other.m_dTarget1Range);
	this->m_dToA1 = std::move(other.m_dToA1);
	this->m_dToA2 = std::move(other.m_dToA2);
	this->m_dTraget2Range = std::move(other.m_dTraget2Range);
	this->m_dTwoTargetRCS = std::move(other.m_dTwoTargetRCS);
	this->m_dPsi = std::move(other.m_dPsi);
	this->m_uiSamplesCount = std::move(other.m_uiSamplesCount);
	if (!(this->m_oPCTwoTargetReturn.empty())) this->m_oPCTwoTargetReturn.clear();

	this->m_oPCTwoTargetReturn.operator=(std::move(other.m_oPCTwoTargetReturn));
	if (!(this->m_oPhase.empty())) this->m_oPhase.clear();

	this->m_oPhase.operator=(std::move(other.m_oPhase));
	return *this;
}

std::ostream &           radiolocation::operator<<(_In_ std::ostream &os, _In_ PCWaveTwoTargetReturn const& rhs)
{
	os.scientific;
	for (std::size_t i{ 0 }; i != rhs.m_uiSamplesCount; ++i)
		os << "S(phi(t))ret:" << rhs.m_oPCTwoTargetReturn[i].second << "phi(t):" << rhs.m_oPhase.operator[](i) << "t:" << rhs.m_oPCTwoTargetReturn[i].first << std::endl;
	return os;
}

std::pair<double, double>  radiolocation::PCWaveTwoTargetReturn::operator[](_In_ const std::size_t index)
{
	BOOST_ASSERT_MSG(index >= 0 && index <= this->m_uiSamplesCount, "Invalid index in PCWaveTwoTargetReturn::operator[]");
	return this->m_oPCTwoTargetReturn.operator[](index);
}

const std::pair<double, double>     radiolocation::PCWaveTwoTargetReturn::operator[](_In_ const std::size_t index) const
{
	BOOST_ASSERT_MSG(index >= 0 && index <= this->m_uiSamplesCount, "Invalid index in PCWaveTwoTargetReturn::operator[]");
	return this->m_oPCTwoTargetReturn.operator[](index);
}

std::vector<std::pair<std::size_t, double>>     radiolocation::PCWaveTwoTargetReturn::operator==(_In_ PCWaveTwoTargetReturn const& other) const
{
	BOOST_ASSERT_MSG(this->m_uiSamplesCount == other.m_uiSamplesCount, "Invalid data size in PCWaveTwoTargetReturn::operator==");
	std::vector<std::pair<std::size_t, double>> vresults;
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
	{
		if ((std::fabs(this->m_oPCTwoTargetReturn[i].second) - std::fabs(other.m_oPCTwoTargetReturn[i].second)) <=
			std::numeric_limits<double>::epsilon())
			vresults.push_back({ i, this->m_oPCTwoTargetReturn[i].second });
		else
			vresults.push_back({ i, this->m_oPCTwoTargetReturn[i].second });
	}
	return vresults;
}

std::vector<std::pair<std::size_t, double>>       radiolocation::PCWaveTwoTargetReturn::operator!=(_In_ PCWaveTwoTargetReturn const& other) const
{
	BOOST_ASSERT_MSG(this->m_uiSamplesCount == other.m_uiSamplesCount, "Invalid data size in PCWaveTwoTargetReturn::operator!=");
	std::vector<std::pair<std::size_t, double>> vresults;
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
	{
		if ((std::fabs(this->m_oPCTwoTargetReturn[i].second) - std::fabs(other.m_oPCTwoTargetReturn[i].second)) >
			std::numeric_limits<double>::epsilon())
			vresults.push_back({ i, this->m_oPCTwoTargetReturn[i].second });
		else
			vresults.push_back({ i, this->m_oPCTwoTargetReturn[i].second });
	}
	return vresults;
}

#if defined _DEBUG
void              radiolocation::PCWaveTwoTargetReturn::debug_print() const
{
	std::printf("PCWaveTwoTargetReturn::debug_print: Executed\n");
	std::printf("&this->m_dAmplitude1=%p,this->m_dAmplitude1=%.9f\n", &this->m_dAmplitude1, this->m_dAmplitude1);
	std::printf("&this->m_dAmplitude2=%p,this->m_dAmplitude2=%.9f\n", &this->m_dAmplitude2, this->m_dAmplitude2);
	std::printf("&this->m_dCentralFrequency=%p,this->m_dCentralFrequency=%.9f\n", &this->m_dCentralFrequency, this->m_dCentralFrequency);
	std::printf("&this->m_dTarget1Range=%p,this->m_dTarget1Range=%.9f\n", &this->m_dTarget1Range, this->m_dTarget1Range);
	std::printf("&this->m_dTraget2Range=%p,this->m_dTarget2Range=%.9f\n", &this->m_dTraget2Range, this->m_dTraget2Range);
	std::printf("&this->m_dToA1=%p,this->m_dToA1=%.9f\n", &this->m_dToA1, this->m_dToA1);
	std::printf("&this->m_dToA2=%p,this->m_dToA2=%.9f\n", &this->m_dToA2, this->m_dToA2);
	std::printf("&this->m_dTwoTargetRCS=%p,this->m_dTwoTargetRCS=%.9f\n", &this->m_dTwoTargetRCS, this->m_dTwoTargetRCS);
	std::printf("&this->m_dPsi=%p,this->m_dPsi=%.9f\n", &this->m_dPsi, this->m_dPsi);
	std::printf("&this->m_uiSamplesCount=%p,this->m_uiSamplesCount=%u\n", &this->m_uiSamplesCount, this->m_uiSamplesCount);
	std::printf(" S(phi(t)):        |         phi(t):           |             t:\n");
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
		std::printf("%.15f,%.15f,%.15f\n", this->m_oPCTwoTargetReturn[i].second, this->m_oPhase[i], this->m_oPCTwoTargetReturn[i].first);

	radiolocation::PureCosineWave::debug_print();

}
#endif

#if defined MATHEMATICA_VISUALIZE
void                  radiolocation::PCWaveTwoTargetReturn::save_to_file(_In_z_ const char* fname1, _In_z_ const char* fname2) const
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
			boost::errinfo_api_function("Failed open file in PCwaveTwoTargetReturn::save_to_file") <<
			boost::errinfo_errno(errno) <<
			boost::errinfo_at_line(__LINE__));
	}
	else
	{
		std::printf("Writing content of S(phi(t) to file:%s\n", fname1);
		std::printf("Writing content of phi(t) to file:%s\n", fname2);
		for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
		{
			std::fprintf(fp1, "%.15f,%.15f\n", this->m_oPCTwoTargetReturn.operator[](i).first, this->m_oPCTwoTargetReturn.operator[](i).second);
			//std::fprintf(fp2, "%.15f,%.15f\n", this->m_oPCTwoTargetReturn.operator[](i).first, this->m_oPhase.operator[](i));
		}
		std::printf("Finished writing the content of S(phi(t)) to file:%s\n", fname1);
		std::printf("Finished writing the content of phi(t) to file:%s\n", fname2);
		fclose(fp1);
		fclose(fp2);
	}

}
#endif

double           radiolocation::PCWaveTwoTargetReturn::GenerateWaveformSample(_In_ const double timestep,_In_ const double arg, _In_ const double psi) const
{
	//first compute base object Phase argument:
	double sampleTx{ 0.0 }; double sampleRx{ 0.0 };
	double start_time{ this->m_init_time };
	double time_incr{ start_time += timestep };
	double t1{ time_incr * arg };
	sampleTx = this->m_amplitude * ::cos(t1 * radiolocation::PureCosineWave::TWO_PI * this->m_frequency);
	// compute derived object Phase argument(received signal).
	double start_time2{ this->m_init_time };
	double time_incr2{ start_time2 += psi };
	double t2{ time_incr2 * arg };
	double phi{ (this->m_dCentralFrequency * this->m_dToA1) - (this->m_dCentralFrequency * this->m_dToA2) };
	double Amplitude1Squared{ this->m_dAmplitude1 * this->m_dAmplitude1 };
	double Amplitude2Squared{ this->m_dAmplitude2 * this->m_dAmplitude2 };
	double Eret{ std::sqrt(Amplitude1Squared + Amplitude2Squared + 2.0 * this->m_dAmplitude1 * this->m_dAmplitude2 * ::cos(phi)) };
	sampleRx = Eret * ::cos(sampleTx - t2);
	return sampleRx;
}

void             radiolocation::PCWaveTwoTargetReturn::quadrature_components_extraction(_Inout_ std::vector<std::pair<double, double>> &IQ, _In_ const int nThreads)
{
#if defined _DEBUG
	_ASSERTE(0 <= nThreads);
#else
	if (0 >= nThreads)
		BOOST_THROW_EXCEPTION(invalid_value_arg() <<
		boost::errinfo_api_function("Invalid argument in PCWaveTwoTargetReturn::quadrature_components_extraction") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	if (!(IQ.empty()))
	{
		std::size_t a_SamplesCount{ this->m_uiSamplesCount };
		_Field_size_(a_SamplesCount) std::vector<double> a_Cos(a_SamplesCount);
		_Field_size_(a_SamplesCount) std::vector<double> a_Sin(a_SamplesCount);
		_Field_size_(a_SamplesCount) std::vector<double> a_PhaseTx(this->m_oPhase);
		_Field_size_(a_SamplesCount) std::vector<std::pair<double, double>> a_PCTTR(this->m_oPCTwoTargetReturn);
		std::size_t i;
		double CentralFrequency{ this->m_dCentralFrequency };
		// start extaction from time t = 0.0.
		double a_InitTime{ 0.0 };
		double a_TimeStep{ this->m_dPsi };
		double InvSamplesCount{ 1.0 / static_cast<double>(a_SamplesCount) };
		double delta{ 0.0 }; double t{ 0.0 };
		omp_set_num_threads(nThreads);
#if defined OMP_TIMING
		double start{ wrapp_omp_get_wtime() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, t, delta) rduction(+:a_InitTime)
		for (i = 0; i < a_SamplesCount; ++i)
		{
			a_InitTime += a_TimeStep;
			delta = static_cast<double>(i)* InvSamplesCount;
			t = a_InitTime * delta;
			a_Cos.operator[](i) = 2.0 * ::cos((radiolocation::PureCosineWave::TWO_PI*CentralFrequency*t) + a_PhaseTx.operator[](i));
			a_Sin.operator[](i) = -2.0 * ::sin((radiolocation::PureCosineWave::TWO_PI*CentralFrequency*t) + a_PhaseTx.operator[](i));
			IQ.operator[](i).operator=({ a_PCTTR.operator[](i).second * a_Cos.operator[](i),
				a_PCTTR.operator[](i).second * a_Sin.operator[](i) });
		}
#if defined OMP_TIMING
		double end{ wrapp_omp_get_wtime() };
		std::printf("PCWaveTwoTragetReturn::quadrature_components_extraction executed in:%.9fseconds\n", end - start);
#endif
	}
	else BOOST_THROW_EXCEPTION(
		empty_vector() <<
		boost::errinfo_api_function("Empty vector in PCWaveTwoTragetReturn::quadrature_components_extraction ") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));

}

void             radiolocation::PCWaveTwoTargetReturn::analytic_signal(_In_ std::vector<double> const& cenvelope, _In_ const int nThreads)
{
#if defined _DEBUG
	_ASSERTE((0 < nThreads) && (this->m_uiSamplesCount == static_cast<std::size_t>(cenvelope.size())));
#else
	if ((0 > nThreads) && (this->m_uiSamplesCount != static_cast<std::size_t>(cenvelope.size())))
		BOOST_THROW_EXCEPTION(invalid_value_arg() <<
		boost::errinfo_api_function("Invalid argument in PCWaveTwoTargetReturn::analytic_signal") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif

	if (!(cenvelope.empty()))
	{
		std::size_t a_SamplesCount{ this->m_uiSamplesCount };
		double j_imag{ j().imag() };
		double a_CentralFrequency{ this->m_dCentralFrequency };
		double a_InitTime{ 0.0 };
		double a_TimeStep{ this->m_dPsi };
		_Field_size_(a_SamplesCount) std::vector<double> a_Cos(a_SamplesCount);
		_Field_size_(a_SamplesCount) std::vector<double> a_Sin(a_SamplesCount);
		_Field_size_(a_SamplesCount) std::vector<std::pair<double, double>> a_PCTTR(a_SamplesCount);
		_Field_size_(a_SamplesCount) std::vector<double> a_PhaseRx(this->m_oPhase);
		double delta{ 0.0 }; double t{ 0.0 };
		double InvSamplesCount{ 1.0 / static_cast<double>(a_SamplesCount) };
		std::size_t i;
		omp_set_num_threads(nThreads);
#if defined OMP_TIMING
		double start{ wrapp_omp_get_wtick() };
#endif
#pragma omp parallel for default(shared) schedule(runtime) \
	private(i, delta, t) reduction(+:a_InitTime)
		for (i = 0; i < a_SamplesCount; ++i)
		{
			a_InitTime += a_TimeStep;
			delta = static_cast<double>(i)* InvSamplesCount;
			t = a_InitTime * delta;
			a_Cos.operator[](i) = ::cos((radiolocation::PureCosineWave::TWO_PI * a_CentralFrequency * t) + a_PhaseRx.operator[](i));
			a_Sin.operator[](i) = j_imag * ::sin((radiolocation::PureCosineWave::TWO_PI * a_CentralFrequency * t) + a_PhaseRx.operator[](i));
			a_PCTTR.operator[](i).operator=({ t, (cenvelope.operator[](i) * a_Cos.operator[](i)) +
				(cenvelope.operator[](i) * a_Sin.operator[](i)) });
		}
#if defined OMP_TIMING
		double end{ wrapp_omp_get_wtime() };
		std::printf("PCwaveTwoTargetReturn::analytic_signal executed in:%.9fseconds\n", end - start);
#endif
		this->m_oPCTwoTargetReturn.operator=(std::move(a_PCTTR));
	}
	else BOOST_THROW_EXCEPTION(empty_vector() <<
		boost::errinfo_api_function("Empty vector in PCWaveTwoTargetReturn::analytic_signal") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
}



	

	