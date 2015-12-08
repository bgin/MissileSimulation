
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Surface Area Clutter class - implementation.
@aulthor: Bernard Gingold
@version:  1.0  10/11/2015

*/
#include "SurfaceAreaClutterReturn.h"
#include "LibExceptions.h"
#include "../MathLib/MathConstants.h"
namespace rc1 = radiolocation_constants;


radiolocation::SurfaceAreaClutter::SurfaceAreaClutter(_In_ struct SurAreaCluttParams const& p) :
m_dAvrgClutterRCS{ 0.0 },
m_dClutterArea{ 0.0 },
m_dCriticalAngle{ 0.0 },
m_dGrazingAngle{ p.GrazingAngle },
m_dPhaseDifferential{ 0.0 },
m_dSurfaceHeight{ p.SurfaceHeight },
m_dWavelength{ p.Wavelength }
{
#if defined _DEBUG
	_ASSERTE(std::fabs(this->m_dGrazingAngle) > 0.0);
#else
	if (std::fabs(this->m_dGrazingAngle) == 0.0)
		BOOST_THROW_EXCEPTION(invalid_value_arg() <<
		boost::errinfo_api_function("Invalid m_dGrazingAngle in SurfaceAreaClutter::SurfaceAreaClutter") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif

	//Assume that only rough surface is encountered.
	if (RayleighSmoothnessCriteria(this->m_dGrazingAngle, this->m_dSurfaceHeight, this->m_dWavelength))
	{
		this->m_dPhaseDifferential = (mathlib::MathConstants::TWO_PI_DBL() / this->m_dWavelength) *
			2.0 * this->m_dSurfaceHeight * ::sin(this->m_dGrazingAngle);

		this->m_dCriticalAngle = ::asin(this->m_dWavelength / (4.0 * this->m_dSurfaceHeight));
		double sec{ 1.0 / ::cos(this->m_dGrazingAngle) };
		this->m_dClutterArea = p.Range * p.GrazingAngle * 0.5 * rc1::c * p.PulseWidth * sec;
		this->m_dAvrgClutterRCS = p.ClutterScatterCoef * this->m_dClutterArea;
	}
	else BOOST_THROW_EXCEPTION(invalid_value_arg() <<
		boost::errinfo_api_function("Attempt to calculate smooth surface in SurfaceAreaClutter C-tor") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));

}


radiolocation::SurfaceAreaClutter::SurfaceAreaClutter(_In_ SurfaceAreaClutter const& other) :
m_dAvrgClutterRCS{ other.m_dAvrgClutterRCS },
m_dClutterArea{ other.m_dClutterArea },
m_dCriticalAngle{ other.m_dCriticalAngle },
m_dGrazingAngle{ other.m_dGrazingAngle },
m_dPhaseDifferential{ other.m_dPhaseDifferential },
m_dSurfaceHeight{ other.m_dSurfaceHeight },
m_dWavelength{ other.m_dWavelength }
{

}


radiolocation::SurfaceAreaClutter::SurfaceAreaClutter(_In_ SurfaceAreaClutter &&other) :
m_dAvrgClutterRCS{ std::move(other.m_dAvrgClutterRCS) },
m_dClutterArea{ std::move(other.m_dClutterArea) },
m_dCriticalAngle{ std::move(other.m_dCriticalAngle) },
m_dGrazingAngle{ std::move(other.m_dGrazingAngle) },
m_dPhaseDifferential{ std::move(other.m_dPhaseDifferential) },
m_dSurfaceHeight{ std::move(other.m_dSurfaceHeight) },
m_dWavelength{ std::move(other.m_dWavelength) }
{

}


radiolocation::SurfaceAreaClutter::~SurfaceAreaClutter()
{

}


radiolocation::SurfaceAreaClutter &        radiolocation::SurfaceAreaClutter::operator=(_In_ SurfaceAreaClutter const& other)
{
	if (this == &other) return *this;

	this->m_dAvrgClutterRCS = other.m_dAvrgClutterRCS;
	this->m_dClutterArea = other.m_dClutterArea;
	this->m_dCriticalAngle = other.m_dCriticalAngle;
	this->m_dGrazingAngle = other.m_dGrazingAngle;
	this->m_dPhaseDifferential = other.m_dPhaseDifferential;
	this->m_dSurfaceHeight = other.m_dSurfaceHeight;
	this->m_dWavelength = other.m_dWavelength;
	return *this;
}

radiolocation::SurfaceAreaClutter &        radiolocation::SurfaceAreaClutter::operator=(_In_ SurfaceAreaClutter &&other)
{
	if (this == &other) return *this;

	this->m_dAvrgClutterRCS = std::move(other.m_dAvrgClutterRCS);
	this->m_dClutterArea = std::move(other.m_dClutterArea);
	this->m_dCriticalAngle = std::move(other.m_dCriticalAngle);
	this->m_dGrazingAngle = std::move(other.m_dGrazingAngle);
	this->m_dPhaseDifferential = std::move(other.m_dPhaseDifferential);
	this->m_dSurfaceHeight = std::move(other.m_dSurfaceHeight);
	this->m_dWavelength = std::move(other.m_dWavelength);
	return *this;
}

std::ostream &                   radiolocation::operator<<(_In_ std::ostream &os, _In_ SurfaceAreaClutter const& rhs)
{
	os.scientific;
	std::setprecision(15);
	os << "m_dClutterArea:" << rhs.m_dClutterArea << "m_dAvrgClutterRCS:" << rhs.m_dAvrgClutterRCS << "GrazingAngle:" << rhs.m_dGrazingAngle <<
		std::endl;
	return os;
}

double                            radiolocation::SurfaceAreaClutter::operator[](_In_ const std::size_t index)
{
	BOOST_ASSERT_MSG(index >= 0 && index <= 6, "Invalid index in SurfaceAreaClutter::operator[]");
	return (&this->m_dPhaseDifferential)[index];
}

const      double                 radiolocation::SurfaceAreaClutter::operator[](_In_ const std::size_t index) const
{
	BOOST_ASSERT_MSG(index >= 0 && index <= 6, "Invalid index in SurfaceAreaClutter::operator[]");
	return (&this->m_dPhaseDifferential)[index];
}

bool                              radiolocation::SurfaceAreaClutter::operator==(_In_ SurfaceAreaClutter const& other) const
{
	// True if almost equal, otherwise false
	if ((std::fabs(this->m_dAvrgClutterRCS) - std::fabs(other.m_dAvrgClutterRCS)) <= std::numeric_limits<double>::epsilon())
		return true;
	else
		return false;
}

bool                              radiolocation::SurfaceAreaClutter::operator!=(_In_ SurfaceAreaClutter const& other) const
{
	// True if not equal, otherwise false.
	if ((std::fabs(this->m_dAvrgClutterRCS) - std::fabs(other.m_dAvrgClutterRCS)) > std::numeric_limits<double>::epsilon())
		return true;
	else
		return false;
}

bool                               radiolocation::operator==(_In_ SurfaceAreaClutter const& lhs, _In_ SurfaceAreaClutter const& rhs)
{
	if ((std::fabs(lhs.m_dAvrgClutterRCS) - std::fabs(rhs.m_dAvrgClutterRCS) <= std::numeric_limits<double>::epsilon()))
		return true;
	else
		return false;
}

bool                                radiolocation::operator!=(_In_ SurfaceAreaClutter const& lhs, _In_ SurfaceAreaClutter const& rhs)
{
	if ((std::fabs(lhs.m_dAvrgClutterRCS) - std::fabs(rhs.m_dAvrgClutterRCS) > std::numeric_limits<double>::epsilon()))
		return true;
	else
		return false;
}