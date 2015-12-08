/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Sine with Additive White Gaussian Noise class- implementation.
@aulthor: Bernard Gingold
@version:  1.0  26/10/2015

*/

#include "GaussianNoiseSine.h"


_Raises_SEH_exception_  radiolocation::AWGNoiseSine::AWGNoiseSine(_In_ struct AWGNSineParams const& p) : m_oWaveformGenerator{ p.WaveformGenerator },
m_uiSamples{ p.Samples }, m_dMean{ p.Mean }, m_dVariance{ p.Variance }
{
#if defined _DEBUG
	_ASSERTE((this->m_dMean > 0.0) && (this->m_dVariance > 0.0));
#else
	if (this->m_dMean < 0.0 || this->m_dVariance < 0.0)
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("AWGNoiseSine::AWGNoiseSine: Invalid argument in Ctor") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif

	double PI{ mathlib::MathConstants::PI_DBL() };
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	double rv1, rv2;
	this->m_oAWGNSine = std::vector<std::pair<double, double>>(this->m_uiSamples);
	for (std::size_t i{ 0 }; i != this->m_uiSamples; ++i)
	{
		do
		rv1 = rand_gen();
		while (rv1 == 0.0);
		rv2 = rand_gen();
		double vu1{ std::sqrt(-2.0 * std::log(rv1)) * this->m_oWaveformGenerator.operator()(2.0 * PI * rv2) };
		double vr2{ this->m_dMean + std::sqrt(this->m_dVariance) * vu1 };
		this->m_oAWGNSine.operator[](i).operator=({ vu1, vr2 });
	}

}

_Raises_SEH_exception_  radiolocation::AWGNoiseSine::AWGNoiseSine(_In_ struct AWGNSineParams const& p1, _In_ struct PureSineParams const& p2) : m_oWaveformGenerator{ p1.WaveformGenerator },
m_uiSamples{ p1.Samples }, m_dMean{ p1.Mean }, m_dVariance{ p1.Variance }, PureSineWave(p2)
{
#if defined _DEBUG
	_ASSERTE((this->m_dMean > 0.0) && (this->m_dVariance > 0.0) && (this->m_uiSamples == this->m_samples));
#else
	if ((this->m_dMean < 0.0) || (this->m_dVariance < 0.0) || (this->m_uiSamples != this->m_samples))
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("AWGNoiseSine::AWGNoiseSine: Invalid argument in Ctor") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	this->m_oAWGNSine = std::vector<std::pair<double, double>>(this->m_uiSamples);
	double PI{ mathlib::MathConstants::PI_DBL() };
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	double rv1, rv2;
	std::plus<double> add;
	for (std::size_t i{ 0 }; i != this->m_uiSamples; ++i)
	{
		do
		rv1 = rand_gen();
		while (rv1 == 0.0);
		rv2 = rand_gen();
		double vu1{ std::sqrt(-2.0 * std::log(rv1)) * this->m_oWaveformGenerator.operator()(2.0 * PI * rv2) };
		double vr2{ this->m_dMean + std::sqrt(this->m_dVariance) * vu1 };
		this->m_oAWGNSine.operator[](i).operator=({ vu1, vr2 });
		// Add element-wise Sine vector to White Gaussian Noise vector.
		this->m_sine.operator[](i).second = add(this->m_sine.operator[](i).second, this->m_oAWGNSine.operator[](i).second);
	}
}

radiolocation::AWGNoiseSine::AWGNoiseSine(_In_  AWGNoiseSine const& rhs) : m_oWaveformGenerator{ rhs.m_oWaveformGenerator }, m_uiSamples{ rhs.m_uiSamples },
m_dMean{ rhs.m_dMean }, m_dVariance{ rhs.m_dVariance }, m_oAWGNSine{ rhs.m_oAWGNSine }
{

}

radiolocation::AWGNoiseSine::AWGNoiseSine(_In_  AWGNoiseSine &&rhs) : m_oWaveformGenerator{ std::move(rhs.m_oWaveformGenerator) }, m_uiSamples{ std::move(rhs.m_uiSamples) },
m_dMean{ std::move(rhs.m_dMean) }, m_dVariance{ std::move(rhs.m_dVariance) }, m_oAWGNSine{ std::move(rhs.m_oAWGNSine) }
{

}

/*
@brief: operator copy assignment, copies only inherited class object.
*/
radiolocation::AWGNoiseSine &              radiolocation::AWGNoiseSine::operator=(_In_ AWGNoiseSine const& other)
{
	//prevent self-assignment
	if (this == &other) return *this;

	this->m_dMean = other.m_dMean;
	this->m_dVariance = other.m_dVariance;
	this->m_oWaveformGenerator.operator=(other.m_oWaveformGenerator);
	this->m_oAWGNSine.operator=(other.m_oAWGNSine);
	this->m_uiSamples = other.m_uiSamples;
	return *this;
}

/*
@brief: operator move-assignment, moves only inherited class object.
*/
radiolocation::AWGNoiseSine &               radiolocation::AWGNoiseSine::operator=(_In_ AWGNoiseSine &&other)
{
	if (this == &other) return *this;

	this->m_dMean = std::move(other.m_dMean);
	this->m_dVariance = std::move(other.m_dVariance);
	this->m_oWaveformGenerator.operator=(std::move(other.m_oWaveformGenerator));
	this->m_uiSamples = std::move(other.m_uiSamples);
	this->m_oAWGNSine.operator=(std::move(other.m_oAWGNSine));
	return *this;
}

std::ostream &                             radiolocation::operator<<(_In_ std::ostream &os, _In_ AWGNoiseSine const& rhs)
{
	os.scientific;
	std::setprecision(15);
	for (std::size_t i{ 0 }; i != rhs.m_uiSamples; ++i)
		os << "t=" << rhs.m_sine.operator[](i).first << "Sin(t) + n(t)=" << rhs.m_sine.operator[](i).second << std::endl;
	return os;
}

/*
@brief: Generates single value of White Gausian Noise. Possible usage as an input to integrator method.
*/
double                                     radiolocation::AWGNoiseSine::operator()(_In_ struct AWGNSineParams const& p)
{
	double PI{ mathlib::MathConstants::PI_DBL() };
	std::clock_t seed{ ::clock() };
	auto rand_gen = std::bind(std::uniform_real_distribution<double>{}, std::default_random_engine(seed));
	double rv1, rv2;
	do
	rv1 = rand_gen();
	while (rv1 == 0.0);
	rv2 = rand_gen();
	double vu1{ std::sqrt(-2.0 * std::log(rv1)) * this->m_oWaveformGenerator.operator()(2.0 * PI * rv2) };
	double vr2{ this->m_dMean + std::sqrt(this->m_dVariance) * vu1 };
	return vr2;
}

std::pair<double, double>                  radiolocation::AWGNoiseSine::operator[](_In_ const std::size_t index)
{
	_ASSERT(index >= 0 && index <= this->m_uiSamples);
	//_mm256_storeu_pd(&this->m_oAWGNSine[0].second, _mm256_loadu_pd(&this->m_oAWGNSine[0].second));
	return this->m_oAWGNSine.operator[](index);
}

const  std::pair<double, double>            radiolocation::AWGNoiseSine::operator[](_In_ const std::size_t index) const
{
	_ASSERT(index >= 0 && index <= this->m_uiSamples);
	return  this->m_oAWGNSine.operator[](index);
}

/*
@brief: Compares for floating point equality this->m_oAWGNSine == other.m_oAWGNSine 
*/
std::vector<std::pair<double, double>>       radiolocation::AWGNoiseSine::operator==(_In_ AWGNoiseSine const& other) const
{
	_ASSERT(this->m_uiSamples == other.m_uiSamples);
	std::vector<std::pair<double, double>> vresult;
	const double EPS{ std::numeric_limits<double>::epsilon() };
	
	for (std::size_t i{ 0 }; i != this->m_uiSamples; ++i)
	{
		if ((std::fabs(this->m_oAWGNSine[i].second) - std::fabs(other.m_oAWGNSine[i].second)) <= EPS)
		{
			//push_back equal pairs
			vresult.push_back({ this->m_oAWGNSine[i].second, other.m_oAWGNSine[i].second });
		}
		else
		{    //push_back  unequal pairs.
			vresult.push_back({ this->m_oAWGNSine[i].second,other.m_oAWGNSine[i].second });
		}
	}
	return vresult;
}

std::vector<std::pair<double, double>>         radiolocation::AWGNoiseSine::operator!=(_In_ AWGNoiseSine const& other) const
{
	_ASSERT(this->m_uiSamples == other.m_uiSamples);
	std::vector<std::pair<double, double>> vresults;
	const double EPS{ std::numeric_limits<double>::epsilon() };

	/*if (this->m_uiSamples % 4 == 0)
	{
		for (std::size_t i{ 0 }; i != this->m_uiSamples; i += 4)
		{
			_mm256_cmp_pd(_mm256_loadu_pd(&this->m_oAWGNSine[i].second), _mm256_loadu_pd(&this->m_oAWGNSine[i].second), 4);
		}
	}*/

	for (std::size_t i{ 0 }; i != this->m_uiSamples; ++i)
	{
		if ((std::fabs(this->m_oAWGNSine[i].second) - std::fabs(other.m_oAWGNSine[i].second)) > EPS)
		{
			//push_back not equal pairs.
			vresults.push_back({ this->m_oAWGNSine[i].second, other.m_oAWGNSine[i].second });
		}
		else
		{  //push_back pairs  equal pairs.
			vresults.push_back({ this->m_oAWGNSine[i].second,other.m_oAWGNSine[i].second });
		}
	}
	return vresults;
}
	

