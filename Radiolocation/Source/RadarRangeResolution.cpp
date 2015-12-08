/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Radar Range Resolution class - implementation.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/

#include "RadarRangeResolution.h"

radiolocation::RangeResolution::RangeResolution()
{

}

radiolocation::RangeResolution::RangeResolution(_In_ struct RangeResolutionParams const& p) :
m_dDeltaRange{ 0.0 },
m_dRangeGate{ 0.0 },
m_dTheta{ 0.0 }
{
#if defined _DEBUG
	_ASSERTE(p.Rmin < p.Rmax);
#else
	if (p.Rmax < p.Rmin)
		BOOST_THROW_EXCEPTION(invalid_value_arg() <<
		boost::errinfo_api_function("Invalid argument in RangeResolution::RangeResolution") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif

	this->m_dDeltaRange = radiolocation_constants::c / (2.0 * p.BW);
	this->m_dRangeGate = (p.Rmax - p.Rmin) / this->m_dDeltaRange;
	this->m_dTheta = (2.0 * this->m_dDeltaRange) / radiolocation_constants::c;
}

radiolocation::RangeResolution::RangeResolution(_In_ RangeResolution const& other) :
m_dDeltaRange{ other.m_dDeltaRange },
m_dRangeGate{ other.m_dRangeGate },
m_dTheta{ other.m_dTheta }
{

}

radiolocation::RangeResolution::RangeResolution(_In_ RangeResolution &&other) :
m_dDeltaRange{ std::move(other.m_dDeltaRange) },
m_dRangeGate{ std::move(other.m_dRangeGate) },
m_dTheta{ std::move(other.m_dTheta) }
{

}

radiolocation::RangeResolution &       radiolocation::RangeResolution::operator=(_In_ RangeResolution const& other)
{
	if (this == &other) return *this;

	this->m_dDeltaRange = other.m_dDeltaRange;
	this->m_dRangeGate = other.m_dRangeGate;
	this->m_dTheta = other.m_dTheta;
	return *this;
}

radiolocation::RangeResolution &        radiolocation::RangeResolution::operator=(_In_ RangeResolution &&other)
{
	if (this == &other) return *this;

	this->m_dDeltaRange = std::move(other.m_dDeltaRange);
	this->m_dRangeGate = std::move(other.m_dRangeGate);
	this->m_dTheta = std::move(other.m_dTheta);
	return *this;
}

std::ostream &         radiolocation::operator<<(_In_ std::ostream &os, _In_  RangeResolution const& rhs)
{
	os.scientific;
	std::setprecision(15);
	os << "DeltaRange:" << rhs.m_dDeltaRange << "RangeGate:" << rhs.m_dRangeGate << "Theta:" << rhs.m_dTheta << std::endl;
	return os;
}

double &               radiolocation::RangeResolution::operator[](_In_ const std::size_t index)
{
	BOOST_ASSERT_MSG(index >= 0 && index <= 2, "Invalid index in RangeResolution::operator[]");
	return (&this->m_dRangeGate)[index];
}

double  const &        radiolocation::RangeResolution::operator[](_In_ const std::size_t index) const
{
	BOOST_ASSERT_MSG(index >= 0 && index <= 2, "Invalid index in RangeResolution::operator[]");
	return (&this->m_dRangeGate)[index];
}

bool                    radiolocation::RangeResolution::operator==(_In_ RangeResolution const& other) const
{
	const double EPS{ std::numeric_limits<double>::epsilon() };
	if ((std::fabs(this->m_dDeltaRange) - std::fabs(other.m_dDeltaRange)) <= EPS &&
		(std::fabs(this->m_dRangeGate) - std::fabs(other.m_dRangeGate)) <= EPS &&
		(std::fabs(this->m_dTheta) - std::fabs(other.m_dTheta) <= EPS))
		return true;
	else
		return false;
}

bool                     radiolocation::RangeResolution::operator!=(_In_ RangeResolution const& other) const
{
	const double EPS{ std::numeric_limits<double>::epsilon() };
	if ((std::fabs(this->m_dDeltaRange) - std::fabs(other.m_dDeltaRange)) > EPS ||
		(std::fabs(this->m_dRangeGate) - std::fabs(other.m_dRangeGate)) > EPS ||
		(std::fabs(this->m_dTheta) - std::fabs(other.m_dTheta) > EPS))
		return true;
	else
		return false;
}

