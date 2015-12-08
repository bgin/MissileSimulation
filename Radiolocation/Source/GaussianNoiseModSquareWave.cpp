
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Modulated Square Wave with Additive White Gaussian Noise class - definition.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

#include "GaussianNoiseModSquareWave.h"

const  double  radiolocation::AWGNMSquareWave::EPS{ std::numeric_limits<double>::epsilon() };

const  double  radiolocation::AWGNMSquareWave::PI{ mathlib::MathConstants::PI_DBL() };

radiolocation::AWGNMSquareWave::AWGNMSquareWave(_In_  struct AWGNMSWParams const& p) :
m_dMean{ p.Mean },
m_dVariance{ p.Variance },
m_uiSamplesCount{ p.SamplesCount },
m_oWaveformGenerator{ p.WaveformGenerator }
{
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	std::size_t vecLength{ 0 };
	double rv1, rv2;
	auto remainder = this->m_uiSamplesCount % 4;
	if (!remainder)
		vecLength = this->m_uiSamplesCount;
	else
		vecLength = this->m_uiSamplesCount - remainder;
	__m256d vrv1;
	this->m_oAWGNMSquareWave = std::vector<std::pair<double, double>>(this->m_uiSamplesCount);
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
		_mm256_storeu_pd(&this->m_oAWGNMSquareWave.operator[](i).first, vvu1);
		_mm256_storeu_pd(&this->m_oAWGNMSquareWave.operator[](i).second, vvr2);
	}

	if (!remainder)
	{
		for (std::size_t i{ vecLength }; i <= (vecLength + remainder); ++i)
		{
			do
			rv1 = rand_gen();
			while (rv1 == 0.0);
			rv2 = rand_gen();
			double vu1{ std::sqrt(-2.0 * std::log(rv1)) * this->m_oWaveformGenerator.operator()(2.0 * PI * rv2) };
			double vr2{ this->m_dMean + std::sqrt(this->m_dVariance) * vu1 };
			this->m_oAWGNMSquareWave.operator[](i).operator=({ vu1, vr2 });
		}
	}
#if defined DEBUG_TRACE_EXECUTION
	std::printf("AWGNMSquareWave::AWGNMSquareWave(_In_  struct AWGNMSWParams const& p) - Executed: %s,in File:%s, at line:%u\n", __DATE__, __FILE__, __LINE__);
#endif
}

radiolocation::AWGNMSquareWave::AWGNMSquareWave(_In_ struct AWGNMSWParams const& p1, _In_ struct SquareWaveMParams const& p2) :
m_dMean{ p1.Mean },
m_dVariance{ p1.Variance },
m_uiSamplesCount{ p1.SamplesCount },
m_oWaveformGenerator{ p1.WaveformGenerator },
SquareWaveMSignal{ p2 }
{
#if defined _DEBUG
	_ASSERTE(this->m_uiSamplesCount == this->m_samples);
#else
	if (this->m_uiSamplesCount != this->m_samples)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("AWGNMSquareWave::AWGNMSquareWave: Invalid argument") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	std::size_t vecLength{ 0 };
	double rv1, rv2;
	auto remainder = this->m_uiSamplesCount % 4;
	if (!remainder)
		vecLength = this->m_uiSamplesCount;
	else
		vecLength = this->m_uiSamplesCount - remainder;

	__m256d vrv1;
	this->m_oAWGNMSquareWave = std::vector<std::pair<double, double>>(this->m_uiSamplesCount);
	for (std::size_t i{ 0 }; i != vecLength; i += 4)
	{
		do // AVX version.
		vrv1 = _mm256_set_pd(rand_gen(), rand_gen(), rand_gen(), rand_gen());
		while (!(_mm256_cmp_pd(vrv1, _mm256_setzero_pd(), 0).m256d_f64));
		__m256d vrv2 = _mm256_set_pd(rand_gen(), rand_gen(), rand_gen(), rand_gen());
		__m256d temp1 = _mm256_set_pd(this->m_oWaveformGenerator(2.0 * PI * vrv2.m256d_f64[0]), this->m_oWaveformGenerator(2.0 * PI * vrv2.m256d_f64[1]),
			this->m_oWaveformGenerator(2.0 * PI * vrv2.m256d_f64[2]), this->m_oWaveformGenerator(2.0 * PI * vrv2.m256d_f64[3]));
		__m256d vvu1 = _mm256_mul_pd(_mm256_sqrt_pd(_mm256_mul_pd(_mm256_set1_pd(-2.0), _mm256_log_pd(vrv1))), temp1);
		__m256d vvr2 = _mm256_mul_pd(_mm256_add_pd(_mm256_set1_pd(this->m_dMean), _mm256_sqrt_pd(_mm256_set1_pd(this->m_dVariance))), vvu1);
		_mm256_storeu_pd(&this->m_oAWGNMSquareWave.operator[](i).first, vvu1);
		_mm256_storeu_pd(&this->m_oAWGNMSquareWave.operator[](i).second, vvr2);
		_mm256_storeu_pd(&this->m_square_wave.operator[](i).second, _mm256_add_pd(_mm256_loadu_pd(&this->m_square_wave[i].second), vvr2));
	}

	if (!remainder)
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
			this->m_oAWGNMSquareWave.operator[](i).operator=({ vu1, vr2 });
			this->m_square_wave.operator[](i).second = add(this->m_square_wave.operator[](i).second, this->m_oAWGNMSquareWave.operator[](i).second);
		}
	}
#if defined DEBUG_TRACE_EXECUTION
	std::printf("AWGNMSquareWave::AWGNMSquareWave(_In_ struct AWGNMSWParams const& p1, _In_ struct SquareWaveMParams const& p2) - Executed:%s, in File:%s \
								, in line:%u\n", __DATE__, __FILE__, __LINE__);
#endif
}

radiolocation::AWGNMSquareWave::AWGNMSquareWave(_In_ AWGNMSquareWave const& other) :
m_dMean{ other.m_dMean },
m_dVariance{ other.m_dVariance },
m_uiSamplesCount{ other.m_uiSamplesCount },
m_oWaveformGenerator{ other.m_oWaveformGenerator },
m_oAWGNMSquareWave{ other.m_oAWGNMSquareWave }
{
#if defined DEBUG_TRACE_EXECUTION
	std::printf("AWGNMSquareWave::AWGNMSquareWave(_In_ AWGNMSquareWave const& other) - Executed:%s,in File:%s,at line:%u\n", __DATE__, __FILE__, __LINE__);
#endif
}

radiolocation::AWGNMSquareWave::AWGNMSquareWave(_In_ AWGNMSquareWave &&other) :
m_dMean{ std::move(other.m_dMean) },
m_dVariance{ std::move(other.m_dVariance) },
m_uiSamplesCount{ std::move(other.m_uiSamplesCount) },
m_oWaveformGenerator{ std::move(other.m_oWaveformGenerator) },
m_oAWGNMSquareWave{ std::move(other.m_oAWGNMSquareWave) }
{
#if defined DEBUG_TRACE_EXECUTION
	std::printf("AWGNMSquareWave::AWGNMSquareWave(_In_ AWGNMSquareWave && other) - Executed:%s,in File:%s,at line:%u\n", __DATE__, __FILE__, __LINE__);
#endif
}

radiolocation::AWGNMSquareWave &            radiolocation::AWGNMSquareWave::operator=(_In_ AWGNMSquareWave const& other)
{
	if (this == &other) return *this;

#if defined DEBUG_TRACE_EXECUTION
	std::printf("AWGNMSquareWave::operator=(_In_ AWGNMSquareWave const& other) - Executed:%s, in File:%s, at line:%u\n", __DATE__, __FILE__, __LINE__);
#endif
	this->m_dMean = other.m_dMean;
	this->m_dVariance = other.m_dVariance;
	this->m_uiSamplesCount = other.m_uiSamplesCount;
	this->m_oWaveformGenerator.operator=(other.m_oWaveformGenerator);
	if (!(this->m_oAWGNMSquareWave.empty()))
	    this->m_oAWGNMSquareWave.clear();
	this->m_oAWGNMSquareWave.operator=(other.m_oAWGNMSquareWave);
	return *this;
}

radiolocation::AWGNMSquareWave &           radiolocation::AWGNMSquareWave::operator=(_In_ AWGNMSquareWave &&other)
{
	if (this == &other) return *this;

#if defined DEBUG_TRACE_EXECUTION
	std::printf("AWGNMSquareWave::operator=(_In_ AWGNMSquareWave && other) - Executed:%s, in File:%s, at line:%u\n", __DATE__, __FILE__, __LINE__);
#endif
	this->m_dMean = std::move(other.m_dMean);
	this->m_dVariance = std::move(other.m_dVariance);
	this->m_uiSamplesCount = std::move(other.m_uiSamplesCount);
	this->m_oWaveformGenerator.operator=(std::move(other.m_oWaveformGenerator));
	if (!(this->m_oAWGNMSquareWave.empty()))
		this->m_oAWGNMSquareWave.clear();
	this->m_oAWGNMSquareWave.operator=(std::move(other.m_oAWGNMSquareWave));
	return *this;
}

std::ostream &         radiolocation::operator<<(_In_ std::ostream &os, _In_ AWGNMSquareWave const& rhs)
{
	os.scientific;
	std::setprecision(15);
	for (std::size_t i{ 0 }; i != rhs.m_uiSamplesCount; ++i)
		os << "t:" << rhs.m_oAWGNMSquareWave[i].first << "AWGN(t):" << rhs.m_oAWGNMSquareWave[i].second << std::endl;
	return os;
}

std::pair<double, double>       radiolocation::AWGNMSquareWave::operator[](_In_ const std::size_t index)
{
	BOOST_ASSERT(index >= 0 && index <= this->m_uiSamplesCount);
	return this->m_oAWGNMSquareWave.operator[](index);
}

const std::pair<double, double>    radiolocation::AWGNMSquareWave::operator[](_In_ const std::size_t index) const
{
	BOOST_ASSERT(index >= 0 && index <= this->m_uiSamplesCount);
	return this->m_oAWGNMSquareWave.operator[](index);
}

std::vector<std::pair<std::size_t, double>>     radiolocation::AWGNMSquareWave::operator==(_In_ AWGNMSquareWave const& other) const
{
	BOOST_ASSERT(this->m_uiSamplesCount == other.m_uiSamplesCount);
	std::vector<std::pair<std::size_t, double>> vresults;
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
	{
		if ((std::fabs(this->m_oAWGNMSquareWave[i].second) - std::fabs(other.m_oAWGNMSquareWave[i].second)) <= EPS)
			vresults.push_back({ i, this->m_oAWGNMSquareWave[i].second });
		else
			vresults.push_back({ i, this->m_oAWGNMSquareWave[i].second });
	}
	return vresults;
}

std::vector<std::pair<std::size_t, double>>    radiolocation::AWGNMSquareWave::operator!=(_In_ AWGNMSquareWave const& other) const
{
	BOOST_ASSERT(this->m_uiSamplesCount == other.m_uiSamplesCount);
	std::vector<std::pair<std::size_t, double>> vresults;
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
	{
		if ((std::fabs(this->m_oAWGNMSquareWave[i].second) - std::fabs(other.m_oAWGNMSquareWave[i].second)) > EPS)
			vresults.push_back({ i, this->m_oAWGNMSquareWave[i].second });
		else
			vresults.push_back({ i, this->m_oAWGNMSquareWave[i].second });
	}
	return vresults;
}

std::vector<__m256d>    radiolocation::operator==(_In_ AWGNMSquareWave const& lhs, _In_ AWGNMSquareWave const& rhs)
{
	BOOST_ASSERT(lhs.m_uiSamplesCount == rhs.m_uiSamplesCount);
	BOOST_ASSERT(!(lhs.m_uiSamplesCount % 4));
	std::vector<__m256d> vresults;
	for (std::size_t i{ 0 }; i != lhs.m_uiSamplesCount; i += 4)
		vresults.push_back(_mm256_cmp_pd(_mm256_loadu_pd(&lhs.m_oAWGNMSquareWave[i].second), _mm256_loadu_pd(&rhs.m_oAWGNMSquareWave[i].second), 0));
	return vresults;
}

std::vector<__m256d>     radiolocation::operator!=(_In_ AWGNMSquareWave const& lhs, _In_ AWGNMSquareWave const& rhs)
{
	BOOST_ASSERT(lhs.m_uiSamplesCount == rhs.m_uiSamplesCount);
	BOOST_ASSERT(!(lhs.m_uiSamplesCount % 4));
	std::vector<__m256d> vresults;
	for (std::size_t i{ 0 }; i != lhs.m_uiSamplesCount; i += 4)
		vresults.push_back(_mm256_cmp_pd(_mm256_loadu_pd(&lhs.m_oAWGNMSquareWave[i].second), _mm256_loadu_pd(&rhs.m_oAWGNMSquareWave[i].second), 4));
	return vresults;
}

#if defined _DEBUG
void              radiolocation::AWGNMSquareWave::debug_print() const
{
	std::printf("AWGNMSquareWave::debug_print: Executed\n");
	std::printf("&this->m_dMean=%p,this->m_dMean=%.9f\n", &this->m_dMean, this->m_dMean);
	std::printf("&this->m_dVariance=%p,this->m_dVariance=%.9f\n", &this->m_dVariance, this->m_dVariance);
	std::printf("&this->m_uiSampleCount=%p,this->m_uiSamplesCount=%u\n", &this->m_uiSamplesCount, this->m_uiSamplesCount);
	std::printf("&this->m_oWaveformGenerator=%p\n", &this->m_oWaveformGenerator);
	std::printf(" t:     |       AWGN(t): \n");
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
		std::printf("%.9f, %.9f\n", this->m_oAWGNMSquareWave[i].first, this->m_oAWGNMSquareWave[i].second);

	//Call base version.
	radiolocation::SquareWaveMSignal::debug_print();
}
#endif

#if defined MATHEMATICA_VISUALIZE
void     radiolocation::AWGNMSquareWave::save_to_file(_In_z_ const char* fname1, _In_z_ const char* fname2, _In_z_ const char* fname3) const
{
	//Call base version.
	radiolocation::SquareWaveMSignal::save_to_file(fname1, fname2, fname3);
}
#endif

double        radiolocation::AWGNMSWScalar(_In_ struct AWGNMSWParams const& p)
{
	const double PI{ radiolocation::AWGNMSquareWave::PI };
	double rv1, rv2;
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	do
	rv1 = rand_gen();
	while (rv1 == 0.0);
	rv2 = rand_gen();
	double vu1{ std::sqrt(-2.0 * std::log(rv1)) * p.WaveformGenerator.operator()(2.0 * PI * rv2) };
	double vr2{ p.Mean + std::sqrt(p.Variance) * vu1 };
	return vr2;
}

std::vector<__m256d>     radiolocation::AWGNMSWAVX(_In_ struct AWGNMSWParams const& p)
{
	BOOST_ASSERT(!(p.SamplesCount % 4));
	const double PI{ radiolocation::AWGNMSquareWave::PI };
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	__m256d vrv1;
	std::vector<__m256d> vresults(p.SamplesCount);
	for (std::size_t i{ 0 }; i != p.SamplesCount; i += 4)
	{
		do
		vrv1 = _mm256_set_pd(rand_gen(), rand_gen(), rand_gen(), rand_gen());
		while (!(_mm256_cmp_pd(vrv1, _mm256_setzero_pd(), 0).m256d_f64));
		__m256d vrv2 = _mm256_set_pd(rand_gen(), rand_gen(), rand_gen(), rand_gen());
		__m256d temp1 = _mm256_set_pd(p.WaveformGenerator(2.0 * PI * vrv2.m256d_f64[0]), p.WaveformGenerator(2.0 * PI * vrv2.m256d_f64[1]),
			p.WaveformGenerator(2.0 * PI * vrv2.m256d_f64[2]), p.WaveformGenerator(2.0 * PI * vrv2.m256d_f64[3]));
		__m256d vvu1 = _mm256_mul_pd(_mm256_sqrt_pd(_mm256_mul_pd(_mm256_set1_pd(-2.0), _mm256_log_pd(vrv1))), temp1);
		__m256d vvr2 = _mm256_mul_pd(_mm256_add_pd(_mm256_set1_pd(p.Mean), _mm256_sqrt_pd(_mm256_set1_pd(p.Variance))), vvu1);
		vresults.operator[](i) = vvr2;
	}
	return vresults;
}
	



