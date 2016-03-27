
/*
            ------------      Implementation    ---------------
*/

template<typename T, class PhConstants> inline  atmosphere::AtmModel76Simple<T, PhConstants>::
AtmModel76Simple(_In_ const T Altitude) :
m_Altitude{ Altitude },
m_AtmData{ std::vector<std::pair<std::string, T>>(10) }
{
#if  defined _DEBUG
	_ASSERTE(this->m_Altitude >= static_cast<T>(-1.0) &&
		this->m_Altitude <= static_cast<T>(20.0));
#else
	if (this->m_Altitude < static_cast<T>(-1.0) ||
		this->m_Altitude > static_cast<T>(20.0))
		throw std::runtime_error("Fatal Error in: AtmModel76Simple<T,PhConstants>::AtmModel76Simple(const T)");
#endif
}

template<typename T, class PhConstants> inline atmosphere::AtmModel76Simple<T, PhConstants>::
AtmModel76Simple(_In_ const AtmModel76Simple &rhs) :
m_Altitude{ rhs.m_Altitude },
m_AtmData{ rhs.m_AtmData }
{

}

template<typename T, class PhConstants> inline atmosphere::AtmModel76Simple<T, PhConstants>::
AtmModel76Simple(_In_  AtmModel76Simple &&rhs) :
m_Altitude{ std::move(rhs.m_Altitude) },
m_AtmData{ std::move(rhs.m_AtmData) }
{

}

template<typename T, class PhConstants> inline auto atmosphere::AtmModel76Simple<T, PhConstants>::
operator=(_In_ const AtmModel76Simple &rhs)-> atmosphere::AtmModel76Simple<T, PhConstants> & {

	if (this == &rhs) return (*this);
	this->m_Altitude = rhs.m_Altitude;
	this->m_AtmData.operator=(rhs.m_AtmData);
	return (*this);
}

template<typename T, class PhConstants> inline auto atmosphere::AtmModel76Simple<T, PhConstants>::
operator=(_In_ AtmModel76Simple &&rhs)-> atmosphere::AtmModel76Simple<T, PhConstants> & {

	if (this == &rhs) return (*this);
	this->m_Altitude = std::move(rhs.m_Altitude);
	this->m_AtmData.operator=(std::move(rhs.m_AtmData));
	return (*this);
}

template<typename T, class PhConstants> inline auto atmosphere::AtmModel76Simple<T, PhConstants>::
operator[](_In_ const int index)->std::pair<std::string, T> {

#if defined _DEBUG
	_ASSERTE(index >= 0 && index <= 9);
#else
	if (index < 0 || index > 9)
		throw std::runtime_error("Fatal Error in: AtmModel76Simple<T,PhConstants>::operator[](int)");
#endif
	return (this->m_AtmData.operator[](index));
}

template<typename T, class PhConstants> inline auto atmosphere::AtmModel76Simple<T, PhConstants>::
operator[](_In_ const int index)const-> const std::pair<std::string, T> {

#if defined _DEBUG
	_ASSERTE(index >= 0 && index <= 9);
#else
	if (index < 0 || index > 9)
		throw std::runtime_error("Fatal Error in: AtmModel76Simple<T,PhConstants>::operator[](int)");
#endif
	return (this->m_AtmData.operator[](index));
}

template<typename T, class PhConstants> inline auto atmosphere::AtmModel76Simple<T, PhConstants>::
operator()(_In_ const PhConstants &c)->atmosphere::AtmModel76Simple<T, PhConstants> & {

	this->createAtmosphere(c);
	return (*this);
}

template<typename T, class PhConstants> auto operator<<(_In_ std::ostream &os,
	_In_ const atmosphere::AtmModel76Simple<T, PhConstants> &rhs)->std::ostream & {

	int i_size = static_cast<int>(rhs.m_AtmData.size());
	os << "Atmosphere Model-76(simplified) object state:" << std::endl;
	for (int i{ 0 }; i != i_size; ++i)
		os << rhs.m_AtmData[i].first.c_str() << rhs.m_AtmData[i].second << std::endl;
	return (os);
}


template<typename T, class PhConstants> inline auto atmosphere::AtmModel76Simple<T, PhConstants>::
getAltitude()const->T {

	return (this->m_Altitude);
}

template<typename T, class PhConstants> inline auto atmosphere::AtmModel76Simple<T, PhConstants>::
getAtmData()const->std::vector<std::pair<std::string, T>> {

	return (this->m_AtmData);
}

template<typename T, class PhConstants> inline auto atmosphere::AtmModel76Simple<T, PhConstants>::
createAtmosphere(_In_ const PhConstants &c)->void {

	T sigma, delta, theta;
	T temp, pressure, density, asound;
	T viscosity, kinemat_visc;
	T h = this->m_Altitude * c.REARTH / (this->m_Altitude + c.REARTH);
	if (h < 11.0) {

		theta = (288.15 - 6.5*h) / 288.15;
		delta = pow(theta, c.GMR * 0.15384615384615384);
	}
	else {

		theta = 0.7518653479090751;
		delta = 0.2233611*exp(-c.GMR*(h - 11.0)*0.0046157396722824);
	}
	sigma = delta / theta;
	temp = c.TZERO * theta;
	pressure = c.PZERO * delta;
	density = c.RHOZERO * sigma;
	asound = c.AZERO * std::sqrt(theta);
	atmosphere::MetricViscosity<T> mv;
	viscosity = mv.operator()(theta);
	kinemat_visc = viscosity / density;
	// Fill in read out vector.
	this->m_AtmData.operator[](0).operator=({ std::string("Altitude"), this->m_Altitude });
	this->m_AtmData.operator[](1).operator=({ std::string("Sigma"), sigma });
	this->m_AtmData.operator[](2).operator=({ std::string("Delta"), delta });
	this->m_AtmData.operator[](3).operator=({ std::string("Theta"), theta });
	this->m_AtmData.operator[](4).operator=({ std::string("Temp"), temp });
	this->m_AtmData.operator[](5).operator=({ std::string("Pressure"), pressure });
	this->m_AtmData.operator[](6).operator=({ std::string("Density"), density });
	this->m_AtmData.operator[](7).operator=({ std::string("Sound Speed"), asound });
	this->m_AtmData.operator[](8).operator=({ std::string("Viscosity"), 1.0E+6 * viscosity });
	this->m_AtmData.operator[](9).operator=({ std::string("KViscosity"), kinemat_visc });
}

template<typename T, class PhConstants> auto 
createAtm76Simple(_Inout_ atmosphere::AtmModel76Simple<T, PhConstants>(&AtmSys)[22],_In_ const PhConstants &c, _In_ const int Length)->void {
	constexpr int AtmSysLength{ 22U };
#if defined _DEBUG
	_ASSERTE(Length == AtmSysLength);
#else
	if(Length != AtmSysLength) throw std::runtime_error("Fatal Error in createAtm76Simple(AtmModel76Simple<T,PhConstants>)");
#endif
	for (int i{ 0 }; i != Length; ++i)
		AtmSys[i].createAtmosphere(c);
}

template<typename T, class PhConstants> auto
createAtm76Simple(_Inout_ std::vector<std::unique_ptr<atmosphere::AtmModel76Simple<T, PhConstants>>> &vAtmSys,
   _In_ const PhConstants &c)->void {
	constexpr std::size_t vAtmSysSize{ 22U };
#if defined _DEBUG
	_ASSERTE(vAtmSys.size() == vAtmSysSize);
#else
	if(vAtmSys.size() != vAtmSysSize) throw std::runtime_error("Fatal Error in: createAtm76Simple(std::vector<...> &)");
#endif
	for (std::size_t i{ 0 }; i != vAtmSys.size(); ++i)
		vAtmSys.operator[](i).operator->().createAtmosphere(c);
}