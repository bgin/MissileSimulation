/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Modulated Sine with Additive White Gaussian Noise class - implementation.
@aulthor: Bernard Gingold
@version:  1.0  26/10/2015

*/
#include "GaussianNoiseModSine.h"


const double  radiolocation::AWGNoiseModSine::PI{ mathlib::MathConstants::PI_DBL() };

const double  radiolocation::AWGNoiseModSine::EPS{ std::numeric_limits<double>::epsilon() };

double        radiolocation::AWGNoiseModSine::gaussian_uniform_distr() const
{
	std::clock_t seed{ ::clock() }; 
	return std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed)).operator()();
}
/*
@brief: Create Additive White Gaussian Noise only.
*/
_Raises_SEH_exception_    radiolocation::AWGNoiseModSine::AWGNoiseModSine(_In_ struct AWGNModSineParams const& p) : m_dMean{ p.Mean }, m_dVariance{ p.Variance },
m_uiSamples{ p.Samples }, m_oWaveformGenerator{ p.WaveformGenerator }
{


	//double PI{ mathlib::MathConstants::PI_DBL() };
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	double rv1, rv2;
	auto remainder = this->m_uiSamples % 4;
	
	std::size_t vecLength;
	if (!remainder)
		vecLength = this->m_uiSamples;
	else
		vecLength = this->m_uiSamples - remainder;
	//Vector version.
	__m256d vrv1;
	this->m_oAWGNModSine = std::vector<std::pair<double, double>>(this->m_uiSamples);
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
		std::printf("v0=%.9f,v1=%.9f,v2=%.9f,v3=%.9f\n", vvr2.m256d_f64[0], vvr2.m256d_f64[1], vvr2.m256d_f64[2], vvr2.m256d_f64[3]);
		_mm256_storeu_pd(&this->m_oAWGNModSine.operator[](i).first, vvu1);
		_mm256_storeu_pd(&this->m_oAWGNModSine.operator[](i).second, vvr2);

	}
	// Handle remainder scalar version.
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
			//std::printf("vr2=%.9f\n", vr2);
			this->m_oAWGNModSine.operator[](i).operator=({ vu1, vr2 });
		}
	}

}

	




	


	




	

	


	


_Raises_SEH_exception_   radiolocation::AWGNoiseModSine::AWGNoiseModSine(_In_ struct AWGNModSineParams const& p1, _In_ struct CWSineParams const& p2) : m_dMean{ p1.Mean },
m_dVariance{ p1.Variance }, m_uiSamples{ p1.Samples }, m_oWaveformGenerator{ p1.WaveformGenerator }, CWSineSignal(p2)
{
#if defined _DEBUG
	_ASSERTE(this->m_uiSamples == this->m_samples);
#else
	if (this->m_uiSamples != this->m_samples)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("AWGNoiseModSine::AWGNoiseSine: Invalid argument(s)") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));

#endif
	//double PI{ mathlib::MathConstants::PI_DBL() };
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	double rv1, rv2;
	auto remainder = this->m_uiSamples % 4;
	std::size_t vecLength;
	if (!remainder)
		vecLength = this->m_uiSamples;
	else
		vecLength = this->m_uiSamples - remainder;
		
	
	
		// Vector AVX version.
		__m256d vrv1;
		this->m_oAWGNModSine = std::vector<std::pair<double, double>>(this->m_uiSamples);
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
			_mm256_storeu_pd(&this->m_oAWGNModSine.operator[](i).first, vvu1);
			_mm256_storeu_pd(&this->m_oAWGNModSine.operator[](i).second, vvr2);
			_mm256_storeu_pd(&this->m_sine_signal.operator[](i).second, _mm256_add_pd(_mm256_loadu_pd(&this->m_sine_signal.operator[](i).second), vvr2));
		}
	

	
		// Scalar remainder.
		
		
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
				this->m_oAWGNModSine.operator[](i).operator=({ vu1, vr2 });
				this->m_sine_signal.operator[](i).second = add(this->m_sine_signal.operator[](i).second, this->m_oAWGNModSine.operator[](i).second);
			}
		}
}

radiolocation::AWGNoiseModSine::AWGNoiseModSine(_In_ AWGNoiseModSine const& other) : m_dMean{ other.m_dMean },
m_dVariance{ other.m_dVariance },
m_oAWGNModSine{ other.m_oAWGNModSine },
m_oWaveformGenerator{ other.m_oWaveformGenerator }, 
m_uiSamples{ other.m_uiSamples }
{

}

radiolocation::AWGNoiseModSine::AWGNoiseModSine(_In_  AWGNoiseModSine &&other) : 
m_dMean{ std::move(other.m_dMean) },
m_dVariance{ std::move(other.m_dVariance) },
m_oAWGNModSine{ std::move(other.m_oAWGNModSine) },
m_oWaveformGenerator{ std::move(other.m_oWaveformGenerator) }, 
m_uiSamples{ std::move(other.m_uiSamples) }
{

}

radiolocation::AWGNoiseModSine &           radiolocation::AWGNoiseModSine::operator=(_In_ AWGNoiseModSine const& other)
{
	if (this == &other) return *this;

	this->m_dMean = other.m_dMean;
	this->m_dVariance = other.m_dVariance;
	this->m_oWaveformGenerator.operator=( other.m_oWaveformGenerator);
	this->m_oAWGNModSine.operator=(other.m_oAWGNModSine);
	this->m_uiSamples = other.m_uiSamples;
	return *this;
}

radiolocation::AWGNoiseModSine &           radiolocation::AWGNoiseModSine::operator=(_In_ AWGNoiseModSine &&other)
{
	if (this == &other) return *this;

	this->m_dMean = std::move(other.m_dMean);
	this->m_dVariance = std::move(other.m_dVariance);
	this->m_oWaveformGenerator.operator=(std::move(other.m_oWaveformGenerator));
	this->m_oAWGNModSine.operator=(std::move(other.m_oAWGNModSine));
	this->m_uiSamples = std::move(other.m_uiSamples);
	return *this;
}

std::ostream &                        radiolocation::operator<<(_In_ std::ostream &os, _In_ AWGNoiseModSine const& other)
{
	os.scientific;
	std::setprecision(15);
	for (std::size_t i{ 0 }; i != other.m_uiSamples; ++i)
		os << "t=" << other.m_oAWGNModSine[i].first << " Gauss(t)=" << other.m_oAWGNModSine[i].second << std::endl;
	return os;
}

double                                radiolocation::AWGNoiseModSine::operator()(_In_ struct AWGNModSineParams const& p) const
{
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	double rv1, rv2;
	do
	rv1 = rand_gen();
	while (rv1 == 0.0); //Prevent rv1 == 0.0.
	rv2 = rand_gen();
	double vu1{ std::sqrt(-2.0 * std::log(rv1)) * this->m_oWaveformGenerator.operator()(2.0 * PI * rv2) };
	double vr2{ this->m_dMean + std::sqrt(this->m_dVariance) * vu1 };
	return rv2;
}

std::pair<double, double>              radiolocation::AWGNoiseModSine::operator[](const std::size_t index)
{
	_ASSERT(index >= 0 && index <= this->m_uiSamples);
	return this->m_oAWGNModSine.operator[](index);
}

const  std::pair<double, double>        radiolocation::AWGNoiseModSine::operator[](const std::size_t index) const
{
	_ASSERT(index >= 0 && index <= this->m_uiSamples);
	return this->m_oAWGNModSine.operator[](index);
}

std::vector<std::pair<std::size_t, double>>   radiolocation::AWGNoiseModSine::operator==(_In_ AWGNoiseModSine const& other) const
{
	_ASSERT(this->m_uiSamples == other.m_uiSamples);
	std::vector<std::pair<std::size_t, double>> vresults;
	for (std::size_t i{ 0 }; i != this->m_uiSamples; ++i)
	{
		if ((std::fabs(this->m_oAWGNModSine[i].second) - std::fabs(other.m_oAWGNModSine[i].second)) <= EPS)
			vresults.push_back({ i, this->m_oAWGNModSine[i].second }); // push_back index and value of equals components.
		else
			vresults.push_back({ i, this->m_oAWGNModSine[i].second }); // push_back index and value of inequals components.
	}
	return vresults;
}

std::vector<std::pair<std::size_t, double>>    radiolocation::AWGNoiseModSine::operator!=(_In_ AWGNoiseModSine const& other) const
{
	_ASSERT(this->m_uiSamples == other.m_uiSamples);
	std::vector<std::pair<std::size_t, double>> vresults;
	for (std::size_t i{ 0 }; i != this->m_uiSamples; ++i)
	{
		if ((std::fabs(this->m_oAWGNModSine[i].second) - std::fabs(other.m_oAWGNModSine[i].second)) > EPS)
			vresults.push_back({ i, this->m_oAWGNModSine[i].second }); // push_back index and values of inequal components.
		else
			vresults.push_back({ i, this->m_oAWGNModSine[i].second }); // push_back index and values of equal components.
	}
	return vresults;
}

std::vector<__m256d>                            radiolocation::operator==(_In_ AWGNoiseModSine const& lhs, _In_ AWGNoiseModSine const& rhs)
{
	_ASSERT(lhs.m_uiSamples == rhs.m_uiSamples);
	_ASSERT(!(lhs.m_uiSamples % 4));
	std::vector<__m256d> vresults;
	for (std::size_t i{ 0 }; i != lhs.m_uiSamples; i += 4)
		vresults.push_back(_mm256_cmp_pd(_mm256_loadu_pd(&lhs.m_oAWGNModSine[i].second), _mm256_loadu_pd(&rhs.m_oAWGNModSine[i].second), 0));
	
	return vresults;
}

std::vector<__m256d>                           radiolocation::operator!=(_In_ AWGNoiseModSine const& lhs, _In_ AWGNoiseModSine const& rhs)
{
	_ASSERT(lhs.m_uiSamples == rhs.m_uiSamples);
	_ASSERT(!(lhs.m_uiSamples % 4));
	std::vector<__m256d> vresults;
	for (std::size_t i{ 0 }; i != lhs.m_uiSamples; i += 4)
		vresults.push_back(_mm256_cmp_pd(_mm256_loadu_pd(&lhs.m_oAWGNModSine[i].second), _mm256_loadu_pd(&rhs.m_oAWGNModSine[i].second), 4));

	return vresults;
}

_Raises_SEH_exception_    void            radiolocation::AWGNoiseModSine::analytic_signal(_In_ std::vector<double> const& envelope, _In_ const int n_threads)
{
	/*
	@brief: Call base class function.This virtual function should be called on the object contructed by double argument Constructor.
	*/
	radiolocation::CWSineSignal::analytic_signal(envelope, n_threads);
}

#if defined _DEBUG
void              radiolocation::AWGNoiseModSine::debug_print() const
{
	std::printf("AWGNoiseModSine::debug_print - Executed\n");
	std::printf("&this->m_dMean=%p,this->m_dMean=%.9f\n", &this->m_dMean, this->m_dMean);
	std::printf("&this->m_dVariance=%p,this->m_dVariance=%.9f\n", &this->m_dVariance, this->m_dVariance);
	std::printf("this->m_uiSamples=%p,this->m_uiSamples=%u\n", &this->m_uiSamples, this->m_uiSamples);
	std::printf("&this->m_oWaveformGenerator=%p\n", &this->m_oWaveformGenerator);
	std::printf(" Arg t:        |          Gauss(t) \n");
	for (std::size_t i{ 0 }; i != this->m_uiSamples; ++i)
		std::printf("%.9f, %.9f\n", this->m_oAWGNModSine[i].first, this->m_oAWGNModSine[i].second);

	std::printf("Calling base version\n");
	radiolocation::CWSineSignal::debug_print();
}
#endif

#if defined MATHEMATICA_VISUALIZE
void             radiolocation::AWGNoiseModSine::save_to_file(_In_z_ const char* fname1, _In_z_ const char* fname2) const
{
	radiolocation::CWSineSignal::save_to_file(fname1, fname2);
}
#endif