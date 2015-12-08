/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Modulated Sawtooth Wave with Additive White Gaussian Noise class - implementation.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/


#include "GaussianNoiseModSawtooth.h"



const  double  radiolocation::AWGNMSawtooth::EPS{ std::numeric_limits<double>::epsilon() };

const  double  radiolocation::AWGNMSawtooth::PI{ mathlib::MathConstants::PI_DBL() };


radiolocation::AWGNMSawtooth::AWGNMSawtooth(_In_  struct AWGNMSawtoothParams const& p) :
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
	this->m_oAWGNMSawtooth = std::vector<std::pair<double, double>>(this->m_uiSamplesCount);
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
		_mm256_storeu_pd(&this->m_oAWGNMSawtooth.operator[](i).first, vvu1);
		_mm256_storeu_pd(&this->m_oAWGNMSawtooth.operator[](i).second, vvr2);
	}
	//Handle scalar case

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
			this->m_oAWGNMSawtooth.operator[](i).operator=({ vu1, vr2 });
		}
	}
#if defined DEBUG_TRACE_EXECUTION
	std::printf("AWGNMSawtooth::AWGNMSawtooth(_In_  struct AWGNMSawtoothParams const& p) - Executed in File:%s, at line:%u\n ", __FILE__, __LINE__);
#endif
}

_Raises_SEH_exception_   radiolocation::AWGNMSawtooth::AWGNMSawtooth(_In_ struct AWGNMSawtoothParams const& p1, _In_ struct SawtoothMSignalParams const& p2) :
m_dMean{ p1.Mean },
m_dVariance{ p1.Variance },
m_uiSamplesCount{ p1.SamplesCount },
m_oWaveformGenerator{ p1.WaveformGenerator },
SawtoothMSignal{ p2 }
{
#if defined _DEBUG
	_ASSERTE(this->m_uiSamplesCount == this->m_samples);
#else
	if (this->m_uiSamplesCount != this->m_samples)
	BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("AWGNMSawtooth::AWGNMSawtooth: Invalid argument") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	double rv1, rv2;
	std::size_t vecLength{ 0 };
	auto remainder = this->m_uiSamplesCount % 4;
	if (!remainder)
		vecLength = this->m_uiSamplesCount;
	else
		vecLength = this->m_uiSamplesCount - remainder;

	this->m_oAWGNMSawtooth = std::vector<std::pair<double, double>>(this->m_uiSamplesCount);
	__m256d vrv1;
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
		_mm256_storeu_pd(&this->m_oAWGNMSawtooth.operator[](i).first, vvu1);
		_mm256_storeu_pd(&this->m_oAWGNMSawtooth.operator[](i).second, vvr2);
		_mm256_storeu_pd(&this->m_St.operator[](i).second, _mm256_add_pd(_mm256_loadu_pd(&this->m_St[i].second), vvr2));
	}
	//Handle scalar version
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
			this->m_oAWGNMSawtooth.operator[](i).operator=({ vu1, vr2 });
			this->m_St.operator[](i).second = add(this->m_St.operator[](i).second, this->m_oAWGNMSawtooth.operator[](i).second);
		}
	}
#if defined DEBUG_TRACE_EXECUTION
	std::printf("AWGNMSawtooth::AWGNMSawtooth(_In_ struct AWGNMSawtoothParams const& p1, _In_ struct SawtoothMSignalParams const& p2) - Executed \
					  in File:%s, at line:%u\n", __FILE__, __LINE__);
#endif
}

radiolocation::AWGNMSawtooth::AWGNMSawtooth(_In_ AWGNMSawtooth const& other) :
m_dMean{ other.m_dMean },
m_dVariance{ other.m_dVariance },
m_oAWGNMSawtooth{ other.m_oAWGNMSawtooth },
m_oWaveformGenerator{ other.m_oWaveformGenerator },
m_uiSamplesCount{ other.m_uiSamplesCount }
{

}

radiolocation::AWGNMSawtooth::AWGNMSawtooth(_In_ AWGNMSawtooth &&other) :
m_dMean{ std::move(other.m_dMean) },
m_dVariance{ std::move(other.m_dVariance) },
m_oAWGNMSawtooth{ std::move(other.m_oAWGNMSawtooth) },
m_oWaveformGenerator{ std::move(other.m_oWaveformGenerator) },
m_uiSamplesCount{ std::move(other.m_uiSamplesCount) }

{
	
}

radiolocation::AWGNMSawtooth &           radiolocation::AWGNMSawtooth::operator=(_In_ AWGNMSawtooth const& other)
{
	if (this == &other) return *this;

	this->m_dMean = other.m_dMean;
	this->m_dVariance = other.m_dVariance;
	this->m_oAWGNMSawtooth.clear(); //clear current state
	this->m_oAWGNMSawtooth.operator=(other.m_oAWGNMSawtooth);
	this->m_oWaveformGenerator.operator=(other.m_oWaveformGenerator);
	this->m_uiSamplesCount = other.m_uiSamplesCount;
	return *this;
}

radiolocation::AWGNMSawtooth &            radiolocation::AWGNMSawtooth::operator=(_In_ AWGNMSawtooth && other)
{
	if (this == &other) return *this;

	this->m_dMean = std::move(other.m_dMean);
	this->m_dVariance = std::move(other.m_dVariance);
	this->m_oAWGNMSawtooth.clear();
	this->m_oAWGNMSawtooth.operator=(std::move(other.m_oAWGNMSawtooth));
	this->m_oWaveformGenerator.operator=(std::move(other.m_oWaveformGenerator));
	this->m_uiSamplesCount = std::move(other.m_uiSamplesCount);
	return *this;
}

radiolocation::AWGNMSawtooth &             radiolocation::AWGNMSawtooth::operator+=(_In_ AWGNMSawtooth const& other)
{
	BOOST_ASSERT(this->m_uiSamplesCount == other.m_uiSamplesCount);
	std::size_t vecLength{ 0 };
	auto remainder = this->m_uiSamplesCount % 4;
	if (!remainder)
		vecLength = this->m_uiSamplesCount;
	else
		vecLength = this->m_uiSamplesCount - remainder;

	for (std::size_t i{ 0 }; i != vecLength; i += 4)
		_mm256_storeu_pd(&this->m_oAWGNMSawtooth[i].second, _mm256_add_pd(_mm256_loadu_pd(&this->m_oAWGNMSawtooth[i].second), _mm256_loadu_pd(&other.m_oAWGNMSawtooth[i].second)));

	if (remainder)
		for (std::size_t i{ vecLength }; i <= (vecLength + remainder); ++i)
			this->m_oAWGNMSawtooth[i].second += other.m_oAWGNMSawtooth[i].second;

	return *this;

}

std::ostream &                radiolocation::operator<<(_In_ std::ostream &os, _In_ AWGNMSawtooth const& other)
{
	os.scientific;
	std::setprecision(15);
	for (std::size_t i{ 0 }; i != other.m_uiSamplesCount; ++i)
		os << "t:" << other.m_oAWGNMSawtooth[i].first << "AWGN(t):" << other.m_oAWGNMSawtooth[i].second << std::endl;
	return os;
}

std::pair<double, double>       radiolocation::AWGNMSawtooth::operator[](_In_ const std::size_t index)
{
	BOOST_ASSERT(index >= 0 && index <= this->m_uiSamplesCount);
	return this->m_oAWGNMSawtooth.operator[](index);
}

const std::pair<double, double>   radiolocation::AWGNMSawtooth::operator[](_In_ const std::size_t index) const
{
	BOOST_ASSERT(index >= 0 && index <= this->m_uiSamplesCount);
	return this->m_oAWGNMSawtooth.operator[](index);
}

std::vector<std::pair<std::size_t, double>>   radiolocation::AWGNMSawtooth::operator==(_In_ AWGNMSawtooth const& other) const
{
	BOOST_ASSERT(this->m_uiSamplesCount == other.m_uiSamplesCount);
	std::vector<std::pair<std::size_t, double>> vresults;
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
	{
		if ((std::fabs(this->m_oAWGNMSawtooth[i].second) - std::fabs(other.m_oAWGNMSawtooth[i].second)) <= EPS)
			vresults.push_back({ i, this->m_oAWGNMSawtooth[i].second });
		else
			vresults.push_back({ i, this->m_oAWGNMSawtooth[i].second });
	}
	return vresults;
}

std::vector<std::pair<std::size_t, double>>     radiolocation::AWGNMSawtooth::operator!=(_In_ AWGNMSawtooth const& other) const
{
	BOOST_ASSERT(this->m_uiSamplesCount == other.m_uiSamplesCount);
	std::vector<std::pair<std::size_t, double>> vresults;
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
	{
		if ((std::fabs(this->m_oAWGNMSawtooth[i].second) - std::fabs(other.m_oAWGNMSawtooth[i].second)) > EPS)
			vresults.push_back({ i, this->m_oAWGNMSawtooth[i].second });
		else
			vresults.push_back({ i, this->m_oAWGNMSawtooth[i].second });
	}
	return vresults;
}

std::vector<__m256d>            radiolocation::operator==(_In_ AWGNMSawtooth const& lhs, _In_ AWGNMSawtooth const& rhs)
{
	BOOST_ASSERT(lhs.m_uiSamplesCount == rhs.m_uiSamplesCount);
	BOOST_ASSERT(!(lhs.m_uiSamplesCount % 4));
	std::vector<__m256d> vresults;
	for (std::size_t i{ 0 }; i != lhs.m_uiSamplesCount; i += 4)
		vresults.push_back(_mm256_cmp_pd(_mm256_loadu_pd(&lhs.m_oAWGNMSawtooth[i].second), _mm256_loadu_pd(&rhs.m_oAWGNMSawtooth[i].second), 0));

	return vresults;
}

std::vector<__m256d>            radiolocation::operator!=(_In_ AWGNMSawtooth const& lhs, _In_ AWGNMSawtooth const& rhs)
{
	BOOST_ASSERT(lhs.m_uiSamplesCount == rhs.m_uiSamplesCount);
	BOOST_ASSERT(!(lhs.m_uiSamplesCount % 4));
	std::vector<__m256d> vresults;
	for (std::size_t i{ 0 }; i != lhs.m_uiSamplesCount; i += 4)
		vresults.push_back(_mm256_cmp_pd(_mm256_loadu_pd(&lhs.m_oAWGNMSawtooth[i].second), _mm256_loadu_pd(&rhs.m_oAWGNMSawtooth[i].second), 4));

	return vresults;
}

#if defined _DEBUG
void             radiolocation::AWGNMSawtooth::debug_print() const
{
	std::printf("AWGNMSawtooth::debug_print: Executing\n");
	std::printf("&this->m_dMean=%p,this->m_dMean=%.9f\n", &this->m_dMean, this->m_dMean);
	std::printf("&this->m_dVariance=%p,this->m_dVariance=%.9f\n", &this->m_dVariance, this->m_dVariance);
	std::printf("&this->m_uiSamplesCount=%p,this->m_uiSamplesCount=%u\n", &this->m_uiSamplesCount, this->m_uiSamplesCount);
	std::printf("&this->m_oWaveformGenerator=%p\n", &this->m_oWaveformGenerator);
	std::printf(" t:        |         AWGNM(t): \n");
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
		std::printf("%.9f, %.9f\n", this->m_oAWGNMSawtooth[i].first, this->m_oAWGNMSawtooth[i].second);

	radiolocation::SawtoothMSignal::debug_print();
}
#endif

#if defined MATHEMATICA_VISUALIZE
void               radiolocation::AWGNMSawtooth::save_to_file(_In_z_ const char* fname1, _In_z_ const char* fname2, _In_z_ const char* fname3) const
{
	radiolocation::SawtoothMSignal::save_to_file(fname1, fname2, fname3);
}
#endif

double               radiolocation::AWGNMSawtoothScalar(_In_ struct AWGNMSawtoothParams const& p)
{
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	double rv1, rv2;
	do
	rv1 = rand_gen();
	while (rv1 == 0.0);
	rv2 = rand_gen();
	const double PI{ mathlib::MathConstants::PI_DBL() };
	double vu1{ std::sqrt(-2.0 * std::log(rv1)) * p.WaveformGenerator.operator()(2.0 * PI * rv2) };
	double vr2{ p.Mean + std::sqrt(p.Variance) * vu1 };
	return vr2;
	
}

std::vector<__m256d>        radiolocation::AWGNMSawtoothAVX(_In_ struct AWGNMSawtoothParams const& p)
{
	BOOST_ASSERT(!(p.SamplesCount % 4));
	std::vector<__m256d> vresults = std::vector<__m256d>(p.SamplesCount);
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	std::size_t vecLength{ 0 };
	auto remainder = p.SamplesCount % 4;
	const double PI{ mathlib::MathConstants::PI_DBL() };
	__m256d vrv1;
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