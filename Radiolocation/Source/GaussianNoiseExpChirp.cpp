
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Exponential Chirp with Additive White Gaussian Noise class - implementation.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/
#include "GaussianNoiseExpChirp.h"

const  double  radiolocation::AWGNExpChirp::PI{ mathlib::MathConstants::PI_DBL() };

const  double  radiolocation::AWGNExpChirp::EPS{ std::numeric_limits<double>::epsilon() };

/*
@brief One-Arg Ctor
*/
radiolocation::AWGNExpChirp::AWGNExpChirp(_In_ struct AWGNEChirpParams const& p) :
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
	this->m_oAWGNEChirp = std::vector<std::pair<double, double>>(this->m_uiSamplesCount);
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
		_mm256_storeu_pd(&this->m_oAWGNEChirp.operator[](i).first, vvu1);
		_mm256_storeu_pd(&this->m_oAWGNEChirp.operator[](i).second, vvr2);
	}

	// Handle scalar version.

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
			this->m_oAWGNEChirp.operator[](i).operator=({ vu1, vr2 });
		}
	}
#if defined DEBUG_TRACE_EXECUTION
	std::printf("AWGNExpChirp::AWGNExpChirp(struct AWGNEChirpParams const&) - Executed in File:%s, at line:%u\n",__FILE__, __LINE__);
#endif
}


/*
@brief Two-Arg Ctor.
*/
_Raises_SEH_exception_  radiolocation::AWGNExpChirp::AWGNExpChirp(_In_ struct AWGNEChirpParams const& p1, _In_  struct ExpChirpParams const& p2) :
m_dMean{ p1.Mean },
m_dVariance{ p1.Variance },
m_oWaveformGenerator{ p1.WaveformGenerator },
m_uiSamplesCount{ p1.SamplesCount },
ExpChirpSignal{ p2 }
{
#if defined _DEBUG
	_ASSERTE(this->m_uiSamplesCount == this->m_samples);
#else
	if (this->m_uiSamplesCount != this->m_samples)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("AWGNExpChirp::AWGNExpChirp: Invalid argument") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	double rv1, rv2;
	std::size_t vecLength;
	auto remainder = this->m_uiSamplesCount % 4;
	if (!remainder)
		vecLength = this->m_uiSamplesCount;
	else
		vecLength = this->m_uiSamplesCount - remainder;

	__m256d vrv1;
	this->m_oAWGNEChirp = std::vector<std::pair<double, double>>(this->m_uiSamplesCount);
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
		_mm256_storeu_pd(&this->m_oAWGNEChirp.operator[](i).first, vvu1);
		_mm256_storeu_pd(&this->m_oAWGNEChirp.operator[](i).second, vvr2);
		_mm256_storeu_pd(&this->m_chirp.operator[](i).second, _mm256_add_pd(_mm256_loadu_pd(&this->m_chirp[i].second), vvr2));
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
			this->m_oAWGNEChirp.operator[](i).operator=({ vu1, vr2 });
			this->m_chirp.operator[](i).second = add(this->m_chirp.operator[](i).second, this->m_oAWGNEChirp.operator[](i).second);
		}
	}
#if defined DEBUG_TRACE_EXECUTION
	std::printf("AWGNExpChirp::AWGNExpChirp(struct AWGNEChirpParams const&, struct ExpChirpParams const&) - Executed in File:%s, at line:%u\n",__FILE__, __LINE__);
#endif
}

/*
@brief Copy-Ctor
*/
radiolocation::AWGNExpChirp::AWGNExpChirp(_In_ AWGNExpChirp const& other) :
m_dMean{ other.m_dMean },
m_dVariance{ other.m_dVariance },
m_oWaveformGenerator{ other.m_oWaveformGenerator },
m_uiSamplesCount{ other.m_uiSamplesCount },
m_oAWGNEChirp{ other.m_oAWGNEChirp }
{
#if defined DEBUG_TRACE_EXECUTION
	std::printf("AWGNExpChirp::AWGNExpChirp(_In_ AWGNExpChirp const& other) - Executed in File:%s, at line:%u\n",__FILE__, __LINE__);
#endif
}

/*
@brief Move-Ctor
*/
radiolocation::AWGNExpChirp::AWGNExpChirp(_In_ AWGNExpChirp &&other) :
m_dMean{ std::move(other.m_dMean) },
m_dVariance{ std::move(other.m_dVariance) },
m_uiSamplesCount{ std::move(other.m_uiSamplesCount) },
m_oWaveformGenerator{ std::move(other.m_oWaveformGenerator) },
m_oAWGNEChirp{ std::move(other.m_oAWGNEChirp) }
{
#if defined DEBUG_TRACE_EXECUTION
	std::printf("AWGNExpChirp::AWGNExpChirp(_In_ AWGNExpChirp &&other) - Executed in File:%s, at line:%u\n",__FILE__, __LINE__);
#endif
}

/*
@brief Copy-Assignment operator.
*/
radiolocation::AWGNExpChirp &         radiolocation::AWGNExpChirp::operator=(_In_ AWGNExpChirp const& other)
{
	if (this == &other) return *this;

#if defined DEBUG_TRACE_EXECUTION
	std::printf("AWGNExpChirp::operator=(_In_ AWGNExpChirp const& other) - Executed in File:%s, at line:%u\n",__FILE__, __LINE__);
#endif
	this->m_dMean = other.m_dMean;
	this->m_dVariance = other.m_dVariance;
	this->m_uiSamplesCount = other.m_uiSamplesCount;
	this->m_oWaveformGenerator.operator=(other.m_oWaveformGenerator);
	this->m_oAWGNEChirp.operator=(other.m_oAWGNEChirp);
	return *this;
}

/*
@brief Move-Assignment operator.
*/
radiolocation::AWGNExpChirp &       radiolocation::AWGNExpChirp::operator=(_In_ AWGNExpChirp &&other)
{
	if (this == &other) return *this;
	
#if defined DEBUG_TRACE_EXECUTION
	std::printf("AWGNExpChirp::operator=(_In_ AWGNExpChirp &&other) - Executed in File:%s, at line:%u\n",__FILE__, __LINE__);
#endif
	this->m_dMean = std::move(other.m_dMean);
	this->m_dVariance = std::move(other.m_dVariance);
	this->m_uiSamplesCount = std::move(other.m_uiSamplesCount);
	this->m_oWaveformGenerator.operator=(std::move(other.m_oWaveformGenerator));
	this->m_oAWGNEChirp.operator=(std::move(other.m_oAWGNEChirp));
	return *this;
}

radiolocation::AWGNExpChirp &          radiolocation::AWGNExpChirp::operator+=(_In_ AWGNExpChirp const& other)
{

	BOOST_ASSERT(this->m_uiSamplesCount == other.m_uiSamplesCount);
	std::size_t vecLength;
	auto remainder = this->m_uiSamplesCount % 4;
	if (!remainder)
		vecLength = this->m_uiSamplesCount;
	else
		vecLength = this->m_uiSamplesCount - remainder;

	for (std::size_t i{ 0 }; i != vecLength; i += 4)
		_mm256_storeu_pd(&this->m_oAWGNEChirp[i].second, _mm256_add_pd(_mm256_loadu_pd(&this->m_oAWGNEChirp[i].second), _mm256_loadu_pd(&other.m_oAWGNEChirp[i].second)));

	if (remainder)
	for (std::size_t i{ vecLength }; i <= (vecLength + remainder); ++i)
		this->m_oAWGNEChirp.operator[](i).second += other.m_oAWGNEChirp.operator[](i).second;

	return *this;
}
	

	



/*
@brief overloaded operator<<
*/
std::ostream &            radiolocation::operator<<(_In_ std::ostream& os, _In_ AWGNExpChirp const& other)
{
	os.scientific;
	std::setprecision(15);
	for (std::size_t i{ 0 }; i != other.m_uiSamplesCount; ++i)
		os << "t=" << other.m_oAWGNEChirp.operator[](i).first << "AWGN(t)=" << other.m_oAWGNEChirp.operator[](i).second << std::endl;
	return os;
}

/*
@brief operator subscript.
*/
std::pair<double, double>       radiolocation::AWGNExpChirp::operator[](_In_ const std::size_t index)
{
	BOOST_ASSERT(index >= 0 && index <= this->m_uiSamplesCount);
	return this->m_oAWGNEChirp.operator[](index);
}

/*
@brief const operator[]() const.
*/
const   std::pair<double, double>           radiolocation::AWGNExpChirp::operator[](_In_ const std::size_t index) const
{
	BOOST_ASSERT(index >= 0 && index <= this->m_uiSamplesCount);
	return this->m_oAWGNEChirp.operator[](index);
}

/*
@brief operator==
*/
_Field_size_(m_uiSamplesCount) std::vector<std::pair<std::size_t, double>>  radiolocation::AWGNExpChirp::operator==(_In_ AWGNExpChirp const& other) const
{
	BOOST_ASSERT(this->m_uiSamplesCount == other.m_uiSamplesCount);
	std::vector<std::pair<std::size_t, double>> vresults;
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
	{
		if ((std::fabs(this->m_oAWGNEChirp[i].second) - std::fabs(other.m_oAWGNEChirp[i].second)) <= EPS)
			vresults.push_back({ i, this->m_oAWGNEChirp[i].second });
		else
			vresults.push_back({ i, this->m_oAWGNEChirp[i].second });
	}
	return vresults;
}

/*
@brief operator!=
*/
_Field_size_(m_uiSamplesCount) std::vector<std::pair<std::size_t, double>>  radiolocation::AWGNExpChirp::operator!=(_In_ AWGNExpChirp const& other) const
{
	BOOST_ASSERT(this->m_uiSamplesCount == other.m_uiSamplesCount);
	std::vector<std::pair<std::size_t, double>> vresults;
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
	{
		if ((std::fabs(this->m_oAWGNEChirp[i].second) - std::fabs(this->m_oAWGNEChirp[i].second)) > EPS)
			vresults.push_back({ i, this->m_oAWGNEChirp[i].second });
		else
			vresults.push_back({ i, this->m_oAWGNEChirp[i].second });
	}
	return vresults;
}

/*
@brief friend operator==
*/
std::vector<__m256d>         radiolocation::operator==(_In_ AWGNExpChirp const& lhs, _In_ AWGNExpChirp const& rhs)
{
	BOOST_ASSERT(lhs.m_uiSamplesCount == rhs.m_uiSamplesCount);
	BOOST_ASSERT(!(lhs.m_uiSamplesCount % 4));
	std::vector<__m256d> vresults;
	for (std::size_t i{ 0 }; i != lhs.m_uiSamplesCount; i += 4)
		vresults.push_back(_mm256_cmp_pd(_mm256_loadu_pd(&lhs.m_oAWGNEChirp[i].second), _mm256_loadu_pd(&rhs.m_oAWGNEChirp[i].second), 0));

	return vresults;

}

/*
@brief friend operator!=
*/
std::vector<__m256d>         radiolocation::operator!=(_In_ AWGNExpChirp const& lhs, _In_ AWGNExpChirp const& rhs)
{
	BOOST_ASSERT(lhs.m_uiSamplesCount == rhs.m_uiSamplesCount);
	BOOST_ASSERT(!(lhs.m_uiSamplesCount % 4));
	std::vector<__m256d> vresults;
	for (std::size_t i{ 0 }; i != lhs.m_uiSamplesCount; i += 4)
		vresults.push_back(_mm256_cmp_pd(_mm256_loadu_pd(&lhs.m_oAWGNEChirp[i].second), _mm256_loadu_pd(&rhs.m_oAWGNEChirp[i].second), 4));

	return vresults;
}

#if defined _DEBUG

void              radiolocation::AWGNExpChirp::debug_print() const
{
	std::printf("%s\n", typeid(this).name());
	std::printf("&this->m_dMean=%p,this->m_dMean=%.9f\n", &this->m_dMean, this->m_dMean);
	std::printf("&this->m_dVariance=%p,this->m_dVariance=%.9f\n", &this->m_dVariance, this->m_dVariance);
	std::printf("&this->m_uiSamplesCount=%p,this->m_uiSamplesCount=%u\n", &this->m_uiSamplesCount, this->m_uiSamplesCount);
	std::printf("&this->m_oWaveformGenerator=%p\n", &this->m_oWaveformGenerator);
	std::printf("t:     |        AWGN(t): \n");
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
		std::printf("%.9f, %.9f\n", this->m_oAWGNEChirp[i].first, this->m_oAWGNEChirp[i].second);

	//Calling base class debug_print.
	std::printf("Base ExpChirpSignal::debug_print: Called\n");
	radiolocation::ExpChirpSignal::debug_print();
}
	

#endif

#if defined  MATHEMATICA_VISUALIZE
void           radiolocation::AWGNExpChirp::save_to_file(_In_z_ const char* fname1, _In_z_ const char* fname2, _In_z_ const char* fname3)
{
	//Calling base.
	// User must call this method on object AWGNExpChirp instantiated by the call to two-arg Ctor.
	radiolocation::ExpChirpSignal::save_to_file(fname1, fname2, fname3);
}
#endif

/*
@brief  Returns single value of Additive White Gaussian Noise.
*/
double                     radiolocation::AWGNEChirpScalar(_In_ struct AWGNEChirpParams const& p)
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

/*
@brief Returns std::vector filled with __m256d unions.
*/
std::vector<__m256d>       radiolocation::AWGNEChirpAVX(_In_ struct AWGNEChirpParams const& p)
{
	BOOST_ASSERT(!(p.SamplesCount % 4));
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	const double PI{ mathlib::MathConstants::PI_DBL() };
	std::vector<__m256d> vresult = std::vector<__m256d>(p.SamplesCount);
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
		vresult.operator[](i) = vvr2;
	}
	return vresult;
}