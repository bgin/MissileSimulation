
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Cosine with Additive White Gaussian Noise class- implementation.
@aulthor: Bernard Gingold
@version:  1.0  26/10/2015

*/

#include "PureCosineAWGNoise.h"
#include "LibExceptions.h"

_Raises_SEH_exception_ __thiscall radiolocation::PureCosAWGNoise::PureCosAWGNoise(_In_ struct PureCosineParams const& pcp, _In_ struct WGNoiseParams const& gpp) :m_oCosPulse{ pcp }, m_oGaussNoise{ gpp }

{
#if defined _DEBUG
	_ASSERTE(this->m_oCosPulse.get_samples() == this->m_oGaussNoise.samples());
#else
	if (this->m_oCosPulse.get_samples() != this->m_oGaussNoise.samples())
		BOOST_THROW_EXCEPTION(
		invalid_value_arg() <<
		boost::errinfo_api_function("PureCosAWGNoise::PureCosAWGNoise: Failed") <<
		boost::errinfo_errno(errno) <<
		boost::errinfo_at_line(__LINE__));
#endif
	this->m_samples = this->m_oCosPulse.get_samples();
	this->m_vCosGaussNoise = std::vector<std::pair<double, double>>(this->m_samples);
	this->m_oPolarizationVec = this->m_oCosPulse.polarization();
	std::plus<double> p;
	for (std::size_t i{ 0 }; i != this->m_samples; ++i)
	{
		this->m_vCosGaussNoise.operator[](i).operator=({ this->m_oCosPulse.get_cos()[i].first,
			p(this->m_oCosPulse.get_cos()[i].second, this->m_oGaussNoise.WGNoise()[i].second) });
	}
	
}

__thiscall  radiolocation::PureCosAWGNoise::PureCosAWGNoise(_In_ PureCosAWGNoise const& other) : m_oCosPulse{ other.m_oCosPulse },
m_oGaussNoise{ other.m_oGaussNoise }, m_samples{ other.m_samples }, m_vCosGaussNoise{ other.m_vCosGaussNoise }
{

}

__thiscall  radiolocation::PureCosAWGNoise::PureCosAWGNoise(_In_ PureCosAWGNoise &&other) : m_oCosPulse{ std::move(other.m_oCosPulse) },
m_oGaussNoise{ std::move(other.m_oGaussNoise) }, m_samples{ std::move(other.m_samples) }, m_vCosGaussNoise{ std::move(other.m_vCosGaussNoise) }
{

}

radiolocation::PureCosAWGNoise &        radiolocation::PureCosAWGNoise::operator=(_In_ PureCosAWGNoise const& other)
{
	if (this == &other) return *this;

	this->m_oCosPulse.operator=(other.m_oCosPulse);
	this->m_oGaussNoise.operator=(other.m_oGaussNoise);
	this->m_samples = other.m_samples;
	this->m_oPolarizationVec.operator=(other.m_oPolarizationVec);
	this->m_vCosGaussNoise.operator=(other.m_vCosGaussNoise);
	
	return *this;
}

radiolocation::PureCosAWGNoise &         radiolocation::PureCosAWGNoise::operator=(_In_ PureCosAWGNoise &&other)
{
	if (this == &other) return *this;

	this->m_oCosPulse.operator=(std::move(other.m_oCosPulse));
	this->m_oGaussNoise.operator=(std::move(other.m_oGaussNoise));
	this->m_samples = std::move(other.m_samples);
	this->m_oPolarizationVec.operator=(std::move(other.m_oPolarizationVec));
	this->m_vCosGaussNoise.operator=(std::move(other.m_vCosGaussNoise));
	
	return *this;
}

/*
@brief Displays only Gaussian Noise modulated Cosine vector.
*/
std::ostream  &                           radiolocation::operator<<(_In_ std::ostream &os, _In_ AWGNoiseCosine const& rhs)
{
	os.scientific;
	std::setprecision(15);
	for (std::size_t i{ 0 }; i != rhs.m_uisamples; ++i)
		os << "t=" << rhs.m_cos.operator[](i).first << "Cos(t) + n(t)=" << rhs.m_cos.operator[](i).second << std::endl;
	return os;
}



