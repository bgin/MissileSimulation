
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Range to Target class - implementation.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/
#include "RangeMeasurement.h"

const  double  radiolocation::RangeToTarget::m_sC{ 3.0 * 1.0e+8 };

radiolocation::RangeToTarget::RangeToTarget() :
m_dDeltaTime{ 0.0 },
m_dRange{ 0.0 }
{

}

radiolocation::RangeToTarget::RangeToTarget(_In_ const double deltaTime) : 
m_dDeltaTime{deltaTime}
{
	// This C-tor computes radar echo return distance.
	BOOST_ASSERT_MSG(deltaTime > 0.0, "DeltaTime <= 0.0 in RangeToTarget::RangeToTarget");
	this->m_dRange = RangeToTarget::m_sC * this->m_dDeltaTime * 0.5;
}

radiolocation::RangeToTarget::RangeToTarget(_In_ const double deltaTime, _In_ const double pulseRepInterval) :
m_dDeltaTime{ deltaTime }
{
	// This C-tor computes radar ambiguity echo return distance.
	BOOST_ASSERT_MSG(deltaTime > 0.0 || pulseRepInterval > 0.0, "DeltaTime <= 0.0 || pulseRepInterval <= 0.0 in RangeToTarget::RangeToTarget");
	this->m_dRange = RangeToTarget::m_sC * (this->m_dDeltaTime + pulseRepInterval) * 0.5;
		
}

radiolocation::RangeToTarget::RangeToTarget(_In_ RangeToTarget const& other) :
m_dDeltaTime{ other.m_dDeltaTime },
m_dRange{ other.m_dRange }
{

}

radiolocation::RangeToTarget::RangeToTarget(_In_ RangeToTarget &&other) :
m_dDeltaTime{ std::move(other.m_dDeltaTime) },
m_dRange{ std::move(other.m_dRange) }
{

}

radiolocation::RangeToTarget &       radiolocation::RangeToTarget::operator=(_In_ RangeToTarget const& other)
{
	if (this == &other) return *this;

	this->m_dDeltaTime = other.m_dDeltaTime;
	this->m_dRange = other.m_dRange;
	return *this;
}

radiolocation::RangeToTarget &       radiolocation::RangeToTarget::operator=(_In_ RangeToTarget &&other)
{
	if (this == &other) return *this;

	this->m_dDeltaTime = std::move(other.m_dDeltaTime);
	this->m_dRange = std::move(other.m_dRange);
	return *this;
}

std::ostream &        radiolocation::operator<<(_In_ std::ostream &os, _In_ RangeToTarget const& rhs)
{
	os.scientific;
	std::setprecision(15);
	os << "Range=" << rhs.m_dRange << "TimeDelta=" << rhs.m_dDeltaTime << std::endl;
	return os;
}

bool                  radiolocation::RangeToTarget::operator==(_In_ RangeToTarget const& other) const
{
	if ((std::fabs(this->m_dRange) - std::fabs(other.m_dRange)) <= std::numeric_limits<double>::epsilon())
		return true;
	else
		return false;
}

bool                  radiolocation::RangeToTarget::operator!=(_In_ RangeToTarget const& other) const
{
	if ((std::fabs(this->m_dRange) - std::fabs(other.m_dRange)) > std::numeric_limits<double>::epsilon())
		return true;
	else
		return false;
}

double                 radiolocation::RangeToTarget::operator[](_In_ const std::size_t index)
{
	BOOST_ASSERT(index >= 0 && index <= 1);
	return (&this->m_dRange)[index];
}

const      double        radiolocation::RangeToTarget::operator[](_In_ const std::size_t index) const
{
	BOOST_ASSERT(index >= 0 && index <= 1);
	return (&this->m_dRange)[index];
}