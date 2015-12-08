/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Modulated Cosine with Additive White Gaussian Noise class - definition.
@aulthor: Bernard Gingold
@version:  1.0  26/10/2015

*/
#include "GaussianNoiseModCos.h"



const double  radiolocation::AWGNoiseModCos::PI{ mathlib::MathConstants::PI_DBL() };

const double  radiolocation::AWGNoiseModCos::EPS{ std::numeric_limits<double>::epsilon() };

double        radiolocation::AWGNoiseModCos::GND() const
{
	std::clock_t seed{ ::clock() };
	//std::uniform_real_distribution<double> ud{}; std::default_random_engine de(seed);
	//double ret{ RandDistrValue<std::uniform_real_distribution<double>, std::default_random_engine>(ud, de) };
	return std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed)).operator()();
}

  radiolocation::AWGNoiseModCos::AWGNoiseModCos(_In_ struct AWGNMCosParams const& p) : 
	  m_dMean{ p.Mean },
	  m_dVariance{ p.Variance },
m_uiSamplesCount{ p.SamplesCount },
m_oWaveformGenerator{ p.WaveformGenerator }
{

	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	double rv1, rv2;
	auto remainder = this->m_uiSamplesCount % 4;
	std::size_t vecLength;
	if (!remainder)
		vecLength = this->m_uiSamplesCount;
	else
		vecLength = this->m_uiSamplesCount - remainder;

	__m256d vrv1;
	this->m_oAWGNModCos = std::vector<std::pair<double, double>>(this->m_uiSamplesCount);
	for (std::size_t i{ 0 }; i != vecLength; i += 4)
	{
		do
		vrv1 = _mm256_set_pd(rand_gen(), rand_gen(), rand_gen(), rand_gen());
		while (!(_mm256_cmp_pd(vrv1, _mm256_setzero_pd(), 0).m256d_f64));
		__m256d vrv2 = _mm256_set_pd(rand_gen(), rand_gen(), rand_gen(), rand_gen());
		__m256d temp1 = _mm256_set_pd(this->m_oWaveformGenerator(2.0 * PI * vrv2.m256d_f64[0]), this->m_oWaveformGenerator(2.0 * PI * vrv2.m256d_f64[1]),
			this->m_oWaveformGenerator(2.0 * PI * vrv2.m256d_f64[2]), this->m_oWaveformGenerator(2.0 * PI * vrv2.m256d_f64[3]));
		__m256d vvu1 = _mm256_mul_pd(_mm256_sqrt_pd(_mm256_mul_pd(_mm256_set1_pd(-2.0), _mm256_log_pd(vrv1))), temp1);
		__m256d vvr2 = _mm256_mul_pd(_mm256_add_pd(_mm256_set1_pd(this->m_dMean), _mm256_sqrt_pd(_mm256_set1_pd(this->m_dVariance))), vvu1);
		_mm256_storeu_pd(&this->m_oAWGNModCos.operator[](i).first, vvu1);
		_mm256_storeu_pd(&this->m_oAWGNModCos.operator[](i).second, vvr2);
	}

	if (remainder)
	{
		for (std::size_t i{ vecLength }; i <= (vecLength + remainder); ++i)
		{
			do
			rv1 = rand_gen();
			while (rv1 == 0.0);
			rv2 = rand_gen();
			double vu1{ std::sqrt(-2.0 * std::log(rv1)) * this->m_oWaveformGenerator.operator()(2.0 * PI * rv2) };
			double vr2{ this->m_dMean + std::sqrt(this->m_dVariance) * vu1 };
			this->m_oAWGNModCos.operator[](i).operator=({ vu1, vr2 });
		}
	}
}

_Raises_SEH_exception_  radiolocation::AWGNoiseModCos::AWGNoiseModCos(_In_ struct AWGNMCosParams const& p1, _In_ struct CWCosineParams const& p2) :
m_dMean{ p1.Mean },
m_dVariance{ p1.Variance },
m_uiSamplesCount{ p1.SamplesCount },
m_oWaveformGenerator{ p1.WaveformGenerator }, 
CWCosineSignal(p2)
{
#if defined _DEBUG
	_ASSERTE(this->m_uiSamplesCount == this->m_samples);
#else
	if (this->m_uiSamplesCount != this->m_samples)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("AWGNoiseModCos::AWGNoiseModCos: Invalid argument") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif

	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	double rv1, rv2;
	auto remainder = this->m_uiSamplesCount % 4;
	std::size_t vecLength;
	if (!remainder)
		vecLength = this->m_uiSamplesCount;
	else
		vecLength = this->m_uiSamplesCount - remainder;

	__m256d vrv1;
	this->m_oAWGNModCos = std::vector<std::pair<double, double>>(this->m_uiSamplesCount);
	for (std::size_t i{ 0 }; i != vecLength; i += 4)
	{
		do
		vrv1 = _mm256_set_pd(rand_gen(), rand_gen(), rand_gen(), rand_gen());
		while (!(_mm256_cmp_pd(vrv1, _mm256_setzero_pd(), 0).m256d_f64));
		__m256d vrv2 = _mm256_set_pd(rand_gen(), rand_gen(), rand_gen(), rand_gen());
		__m256d temp1 = _mm256_set_pd(this->m_oWaveformGenerator(2.0 * PI * vrv2.m256d_f64[0]), this->m_oWaveformGenerator(2.0 * PI * vrv2.m256d_f64[1]),
			this->m_oWaveformGenerator(2.0 * PI * vrv2.m256d_f64[2]), this->m_oWaveformGenerator(2.0 * PI * vrv2.m256d_f64[3]));
		__m256d vvu1 = _mm256_mul_pd(_mm256_sqrt_pd(_mm256_mul_pd(_mm256_set1_pd(-2.0), _mm256_log_pd(vrv1))), temp1);
		__m256d vvr2 = _mm256_mul_pd(_mm256_add_pd(_mm256_set1_pd(this->m_dMean), _mm256_sqrt_pd(_mm256_set1_pd(this->m_dVariance))), vvu1);
		_mm256_storeu_pd(&this->m_oAWGNModCos.operator[](i).first, vvu1);
		_mm256_storeu_pd(&this->m_oAWGNModCos.operator[](i).second, vvr2);
		_mm256_storeu_pd(&this->m_cos_signal.operator[](i).second, _mm256_add_pd(_mm256_loadu_pd(&this->m_cos_signal.operator[](i).second), vvr2));
	}

	//Scalar remainder version.
	if (remainder)
	{
		std::plus<double> add;
		for (std::size_t i{ vecLength }; i <= (vecLength + remainder); ++i)
		{
			do
			rv1 = rand_gen();
			while (rv1 == 0.0);
			rv2 = rand_gen();
			double vu1{ std::sqrt(-2.0 * std::log(rv1)) * this->m_oWaveformGenerator.operator()(2.0 * PI * rv2) };
			double vr2{ this->m_dMean + std::sqrt(this->m_dVariance) * vu1 };
			this->m_oAWGNModCos.operator[](i).operator=({ vu1, vr2 });
			this->m_cos_signal.operator[](i).second = add(this->m_cos_signal.operator[](i).second, this->m_oAWGNModCos.operator[](i).second);
		}
	}
}

radiolocation::AWGNoiseModCos::AWGNoiseModCos(_In_ AWGNoiseModCos const& other) : 
m_dMean{ other.m_dMean },
m_dVariance{ other.m_dVariance },
m_uiSamplesCount{ other.m_uiSamplesCount }, 
m_oWaveformGenerator{ other.m_oWaveformGenerator },
m_oAWGNModCos{ other.m_oAWGNModCos }
{

}

radiolocation::AWGNoiseModCos::AWGNoiseModCos(_In_ AWGNoiseModCos &&other) : 
m_dMean{ std::move(other.m_dMean) },
m_dVariance{ std::move(other.m_dVariance) },
m_uiSamplesCount{ std::move(other.m_uiSamplesCount) },
m_oWaveformGenerator{ std::move(other.m_oWaveformGenerator) },
m_oAWGNModCos{ std::move(other.m_oAWGNModCos) }
{

}

radiolocation::AWGNoiseModCos &          radiolocation::AWGNoiseModCos::operator=(_In_ AWGNoiseModCos const& other)
{
	if (this == &other) return *this;

	this->m_dMean = other.m_dMean;
	this->m_dVariance = other.m_dVariance;
	this->m_uiSamplesCount = other.m_uiSamplesCount;
	this->m_oWaveformGenerator.operator=(other.m_oWaveformGenerator);
	this->m_oAWGNModCos.operator=(other.m_oAWGNModCos);
	return *this;
}

radiolocation::AWGNoiseModCos  &          radiolocation::AWGNoiseModCos::operator=(_In_ AWGNoiseModCos &&other)
{
	if (this == &other) return *this;

	this->m_dMean = std::move(other.m_dMean);
	this->m_dVariance = std::move(other.m_dVariance);
	this->m_uiSamplesCount = std::move(other.m_uiSamplesCount);
	this->m_oWaveformGenerator.operator=(std::move(other.m_oWaveformGenerator));
	this->m_oAWGNModCos.operator=(std::move(other.m_oAWGNModCos));
	return *this;
}

std::ostream &             radiolocation::operator<<(_In_ std::ostream &os, _In_ AWGNoiseModCos const& rhs)
{
	os.scientific;
	std::setprecision(15);
	for (std::size_t i{ 0 }; i != rhs.m_uiSamplesCount; ++i)
		os << "t=" << rhs.m_oAWGNModCos.operator[](i).first << "AWGNoise(t)=" << rhs.m_oAWGNModCos.operator[](i).second << std::endl;
	return os;
}

double                     radiolocation::AWGNoiseModCos::operator()(_In_ struct AWGNMCosParams const& p) const
{
	double rv1, rv2;
	do
	rv1 = GND();
	while (rv1 == 0.0);
	rv2 = GND();
	double vu1{ std::sqrt(-2.0 * std::log(rv1)) * this->m_oWaveformGenerator.operator()(2.0 * PI * rv2) };
	double vr2{ this->m_dMean + std::sqrt(this->m_dVariance) * vu1 };
	return vr2;
}

std::pair<double, double>      radiolocation::AWGNoiseModCos::operator[](_In_ const std::size_t index)
{
	_ASSERT(index >= 0 && index <= this->m_uiSamplesCount);
	return this->m_oAWGNModCos.operator[](index);
}

const   std::pair<double, double>   radiolocation::AWGNoiseModCos::operator[](_In_ const std::size_t index) const
{
	_ASSERT(index >= 0 && index <= this->m_uiSamplesCount);
	return this->m_oAWGNModCos.operator[](index);
}

std::vector<std::pair<std::size_t, double>>    radiolocation::AWGNoiseModCos::operator==(_In_ AWGNoiseModCos const& other) const
{
	_ASSERT(this->m_uiSamplesCount == other.m_uiSamplesCount);
	std::vector<std::pair<std::size_t, double>> vresults;
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
	{
		if ((std::fabs(this->m_oAWGNModCos[i].second) - std::fabs(other.m_oAWGNModCos[i].second)) <= EPS)
			vresults.push_back({ i, this->m_oAWGNModCos[i].second });
		else
			vresults.push_back({ i, this->m_oAWGNModCos[i].second });
	}
	return vresults;
}

std::vector<std::pair<std::size_t, double>>    radiolocation::AWGNoiseModCos::operator!=(_In_ AWGNoiseModCos const& other) const
{
	_ASSERT(this->m_uiSamplesCount == other.m_uiSamplesCount);
	std::vector<std::pair<std::size_t, double>> vresults;
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
	{
		if ((std::fabs(this->m_oAWGNModCos[i].second) - std::fabs(other.m_oAWGNModCos[i].second)) > EPS)
			vresults.push_back({ i, this->m_oAWGNModCos[i].second });
		else
			vresults.push_back({ i, this->m_oAWGNModCos[i].second });
	}
	return vresults;
}

std::vector<__m256d>           radiolocation::operator==(_In_ AWGNoiseModCos const& lhs, _In_ AWGNoiseModCos const& rhs)
{
	_ASSERT(lhs.m_uiSamplesCount == rhs.m_uiSamplesCount);
	_ASSERT(!(lhs.m_uiSamplesCount % 4));
	std::vector<__m256d> vresults;
	for (std::size_t i{ 0 }; i != lhs.m_uiSamplesCount; i += 4)
		vresults.push_back(_mm256_cmp_pd(_mm256_loadu_pd(&lhs.m_oAWGNModCos[i].second), _mm256_loadu_pd(&rhs.m_oAWGNModCos[i].second), 0));
	return vresults;
}

std::vector<__m256d>           radiolocation::operator!=(_In_ AWGNoiseModCos const& lhs, _In_ AWGNoiseModCos const& rhs)
{
	_ASSERT(lhs.m_uiSamplesCount == rhs.m_uiSamplesCount);
	_ASSERT(!(lhs.m_uiSamplesCount % 4));
	std::vector<__m256d> vresults;
	for (std::size_t i{ 0 }; i != lhs.m_uiSamplesCount; i += 4)
		vresults.push_back(_mm256_cmp_pd(_mm256_loadu_pd(&lhs.m_oAWGNModCos[i].second), _mm256_loadu_pd(&rhs.m_oAWGNModCos[i].second), 4));
	return vresults;
}

#if defined _DEBUG
void               radiolocation::AWGNoiseModCos::debug_print() const
{
	std::printf(" Subclass AWGNoiseModCos::debug_print: Executing\n");
	std::printf("&this->m_dMean=%p,this->m_dMean=%.9f\n", &this->m_dMean, this->m_dMean);
	std::printf("&this->m_dVariance=%p,this->m_dVariance=%.9f\n", &this->m_dVariance, this->m_dVariance);
	std::printf("&this->m_uiSamplesCount=%p,this->m_uiSamplesCount=%u\n", &this->m_uiSamplesCount, this->m_uiSamplesCount);
	std::printf("&this->m_oWaveformGenerator=%p\n", &this->m_oWaveformGenerator);
	std::printf("t=          |         G(t)=  \n");
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
		std::printf("%.9f,  %.9f\n", this->m_oAWGNModCos.operator[](i).first, this->m_oAWGNModCos.operator[](i).second);

	std::printf(" Base CWCosineSignal::debug_print: Executing\n");
	radiolocation::CWCosineSignal::debug_print();
}
#endif

#if defined MATHEMATICA_VISUALIZE
void           radiolocation::AWGNoiseModCos::save_to_file(_In_z_ const char* fn1, _In_z_ const char* fn2)
{
	// Call Base function only when AWGNoiseModCos::AWGNoiseModeCos(_In_ struct AWGNMCosParams const&, _In_ struct CWCosineParams const&) is instantiated.
	radiolocation::CWCosineSignal::save_to_file(fn1, fn2);
}
#endif

