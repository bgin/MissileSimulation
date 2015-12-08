/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Linear Chirp with Additive White Gaussian Noise class -  class implementation.
@aulthor: Bernard Gingold
@version:  1.0  26/10/2015

*/


#include "GaussianNoiseLinChirp.h"

const   double   radiolocation::AWGNoiseLinChirp::PI{ mathlib::MathConstants::PI_DBL() };

const   double   radiolocation::AWGNoiseLinChirp::EPS{ std::numeric_limits<double>::epsilon() };

radiolocation::AWGNoiseLinChirp::AWGNoiseLinChirp(_In_  struct AWGNLChirpParams const& p) : m_dMean{ p.Mean }, m_dVariance{ p.Variance },
m_uiSamplesCount{ p.SamplesCount }, m_oWaveformGenerator{ p.WaveformGenerator }
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
	this->m_oAWGNLChirp = std::vector<std::pair<double, double>>(this->m_uiSamplesCount);
	// Vector version.
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
		_mm256_storeu_pd(&this->m_oAWGNLChirp.operator[](i).first, vvu1);
		_mm256_storeu_pd(&this->m_oAWGNLChirp.operator[](i).second, vvr2);
	}

	// Handle scalar remainder.
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
			this->m_oAWGNLChirp.operator[](i).operator=({ vu1, vr2 });
		}
	}
}

_Raises_SEH_exception_   radiolocation::AWGNoiseLinChirp::AWGNoiseLinChirp(_In_ struct AWGNLChirpParams const& p1, _In_ struct LinChirpParams const& p2) :
m_dMean{ p1.Mean }, m_dVariance{ p1.Variance }, m_uiSamplesCount{ p1.SamplesCount }, m_oWaveformGenerator{ p1.WaveformGenerator }, LinearChirpSignal(p2)
{
#if defined _DEBUG
	_ASSERTE(this->m_uiSamplesCount == this->m_samples);
#else
	if (this->m_uiSamplesCount != this->m_samples)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("AWGNoiseLinChirp::AWGNoiseLinChirp:") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif

	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	auto remainder = this->m_uiSamplesCount % 4;
	std::size_t vecLength;
	double rv1, rv2;
	if (!remainder)
		vecLength = this->m_uiSamplesCount;
	else
		vecLength = this->m_uiSamplesCount - remainder;

	__m256d vrv1;
	this->m_oAWGNLChirp = std::vector<std::pair<double, double>>(this->m_uiSamplesCount);
	for (std::size_t i{ 0 }; i != vecLength; i += 4)
	{
		// Vector case.
		do
		vrv1 = _mm256_set_pd(rand_gen(), rand_gen(), rand_gen(), rand_gen());
		while (!(_mm256_cmp_pd(vrv1, _mm256_setzero_pd(), 0).m256d_f64));
		__m256d vrv2 = _mm256_set_pd(rand_gen(), rand_gen(), rand_gen(), rand_gen());
		__m256d temp1 = _mm256_set_pd(this->m_oWaveformGenerator(2.0 * PI * vrv2.m256d_f64[0]), this->m_oWaveformGenerator(2.0 * PI * vrv2.m256d_f64[1]),
			this->m_oWaveformGenerator(2.0 * PI * vrv2.m256d_f64[2]), this->m_oWaveformGenerator(2.0 * PI * vrv2.m256d_f64[3]));
		__m256d vvu1 = _mm256_mul_pd(_mm256_sqrt_pd(_mm256_mul_pd(_mm256_set1_pd(-2.0), _mm256_log_pd(vrv1))), temp1);
		__m256d vvr2 = _mm256_mul_pd(_mm256_add_pd(_mm256_set1_pd(this->m_dMean), _mm256_sqrt_pd(_mm256_set1_pd(this->m_dVariance))), vvu1);
		_mm256_storeu_pd(&this->m_oAWGNLChirp.operator[](i).first, vvu1);
		_mm256_storeu_pd(&this->m_oAWGNLChirp.operator[](i).second, vvr2);
		_mm256_storeu_pd(&this->m_chirp.operator[](i).second, _mm256_add_pd(_mm256_loadu_pd(&this->m_chirp[i].second), vvr2));
	}

	// Handle scalar case.
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
			this->m_oAWGNLChirp.operator[](i).operator=({ vu1, vr2 });
			this->m_chirp.operator[](i).second = add(this->m_chirp.operator[](i).second, this->m_oAWGNLChirp.operator[](i).second);
		}
	}
}

radiolocation::AWGNoiseLinChirp::AWGNoiseLinChirp(_In_ AWGNoiseLinChirp const& other) :
m_dMean{ other.m_dMean },
m_dVariance{ other.m_dVariance },
m_uiSamplesCount{ other.m_uiSamplesCount }, 
m_oWaveformGenerator{ other.m_oWaveformGenerator },
m_oAWGNLChirp{ other.m_oAWGNLChirp }
{

}

radiolocation::AWGNoiseLinChirp::AWGNoiseLinChirp(_In_ AWGNoiseLinChirp &&other) :
m_dMean{ std::move(other.m_dMean) },
m_dVariance{ std::move(other.m_dVariance) },
m_uiSamplesCount{ std::move(other.m_uiSamplesCount) },
m_oWaveformGenerator{ std::move(other.m_oWaveformGenerator) },
m_oAWGNLChirp{ std::move(other.m_oAWGNLChirp) }
{

}

radiolocation::AWGNoiseLinChirp &            radiolocation::AWGNoiseLinChirp::operator=(_In_ AWGNoiseLinChirp const& other)
{
	if (this == &other) return *this;

	this->m_dMean = other.m_dMean;
	this->m_dVariance = other.m_dVariance;
	this->m_oWaveformGenerator.operator=( other.m_oWaveformGenerator);
	this->m_uiSamplesCount = other.m_uiSamplesCount;
	this->m_oAWGNLChirp.operator=(other.m_oAWGNLChirp);
	return *this;
}

radiolocation::AWGNoiseLinChirp  &           radiolocation::AWGNoiseLinChirp::operator=(_In_ AWGNoiseLinChirp &&other)
{
	if (this == &other) return *this;

	this->m_dMean = std::move(other.m_dMean);
	this->m_dVariance = std::move(other.m_dVariance);
	this->m_oWaveformGenerator.operator=(std::move(other.m_oWaveformGenerator));
	this->m_uiSamplesCount = std::move(other.m_uiSamplesCount);
	this->m_oAWGNLChirp.operator=(std::move(other.m_oAWGNLChirp));
	return *this;
}

std::ostream   &                   radiolocation::operator<<(_In_ std::ostream& os, _In_ AWGNoiseLinChirp const& other)
{
	os.scientific;
	std::setprecision(15);
	for (std::size_t i{ 0 }; i != other.m_uiSamplesCount; ++i)
		os << "t=" << other.m_oAWGNLChirp.operator[](i).first << "Gauss(t)=" << other.m_oAWGNLChirp.operator[](i).second << std::endl;
	return os;
 }



std::pair<double, double>          radiolocation::AWGNoiseLinChirp::operator[](_In_ const std::size_t index)
{
	_ASSERT(index >= 0 && index <= this->m_uiSamplesCount);
	return this->m_oAWGNLChirp.operator[](index);
}

const  std::pair<double, double>    radiolocation::AWGNoiseLinChirp::operator[](_In_ const std::size_t index) const
{
	_ASSERT(index >= 0 && index <= this->m_uiSamplesCount);
	return this->m_oAWGNLChirp.operator[](index);
}

std::vector<std::pair<std::size_t, double>>          radiolocation::AWGNoiseLinChirp::operator==(_In_ AWGNoiseLinChirp const& other) const
{
	_ASSERT(this->m_uiSamplesCount == other.m_uiSamplesCount);
	std::vector<std::pair<std::size_t, double>> vresults;
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
	{
		if ((std::fabs(this->m_oAWGNLChirp[i].second) - std::fabs(other.m_oAWGNLChirp[i].second)) <= EPS)
			vresults.push_back({ i, this->m_oAWGNLChirp[i].second });
		else
			vresults.push_back({ i, this->m_oAWGNLChirp[i].second });
	}
	return vresults;
}

std::vector<std::pair<std::size_t, double>>           radiolocation::AWGNoiseLinChirp::operator!=(_In_ AWGNoiseLinChirp const& other) const
{
	_ASSERT(this->m_uiSamplesCount == other.m_uiSamplesCount);
	std::vector<std::pair<std::size_t, double>> vresults;
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
	{
		if ((std::fabs(this->m_oAWGNLChirp[i].second) - std::fabs(other.m_oAWGNLChirp[i].second)) > EPS)
			vresults.push_back({ i, this->m_oAWGNLChirp[i].second });
		else
			vresults.push_back({ i, this->m_oAWGNLChirp[i].second });
	}
	return vresults;
}



std::vector<__m256d>             radiolocation::AWGNLChirpAVX(_In_ struct AWGNLChirpParams const& p)
{
	_ASSERT(!(p.SamplesCount % 4));

	std::clock_t seed{ ::clock() };
	const double PI{ mathlib::MathConstants::PI_DBL() };
	 auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	std::vector<__m256d> vresult(p.SamplesCount);
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
		vresult.operator[](i) =  vvr2 ;
	}
	return vresult;
}

double              radiolocation::AWGNLChirpScalar(_In_ struct AWGNLChirpParams const& p)
{
	double rv1, rv2;
	std::clock_t seed{ ::clock() };
	auto gen_rand = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	const double PI{ mathlib::MathConstants::PI_DBL() };
	do
	rv1 = gen_rand();
	while (rv1 == 0.0);
	rv2 = gen_rand();
	double vu1{ std::sqrt(-2.0 * std::log(rv1)) * p.WaveformGenerator.operator()(2.0 * PI * rv2) };
	double vr2{ p.Mean + std::sqrt(p.Variance) * vu1 };
	return vr2;
}

#if defined _DEBUG
void               radiolocation::AWGNoiseLinChirp::debug_print() const
{
	std::printf("AWGNoiseLinChirp::debug_print: Executing\n");
	std::printf("&this->m_dMean=%p,this->m_dMean=%.9f\n", &this->m_dMean, this->m_dMean);
	std::printf("&this->m_dVariance=%p,this->m_dVariance=%.9f\n", &this->m_dVariance, this->m_dVariance);
	std::printf("&this->m_uiSamplesCount=%p,this->m_uiSamplesCount=%u\n", &this->m_uiSamplesCount, this->m_uiSamplesCount);
	std::printf("&this->m_oWaveformGenerator=%p\n", &this->m_oWaveformGenerator);
	std::printf("t:       |         AWGN(t):        \n");
	for (std::size_t i{ 0 }; i != this->m_uiSamplesCount; ++i)
		std::printf("%.9f,%.9f\n", this->m_oAWGNLChirp.operator[](i).first, this->m_oAWGNLChirp.operator[](i).second);
	std::printf(" Base LinearChirpSignal::debug_print: Executing\n");
	radiolocation::LinearChirpSignal::debug_print();
}
#endif

#if defined MATHEMATICA_VISUALIZE
void               radiolocation::AWGNoiseLinChirp::save_to_file(_In_z_ const char* fname1, _In_z_ const char* fname2, _In_z_ const char* fname3)
{
	//Call base LinearChirpSignal::save_to_file 
	//on AWGNoiseLinChirp(_In_ struct AWGNLChirpParams const&, _In_ struct LinChirpParams const&) instantiated object.
	radiolocation::LinearChirpSignal::save_to_file(fname1, fname2, fname3);
}
#endif
