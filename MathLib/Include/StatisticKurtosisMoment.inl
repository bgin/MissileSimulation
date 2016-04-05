/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
C++ Statistic Kurtosis and N-Moment   templated class based upon boost::accumulators library - class  implementation.

@file StatisticKurtosisMoment.inl
@author: Bernard Gingold
@version:  1.0  25/12/2015
@description: StatisticKurtosisMoment.h
*/

template<class Timer, std::size_t N>  mathlib::KurtosisMoment<Timer, N>::KurtosisMoment(_In_ Timer const &timer) : 
m_dKurtosis{ 0.0 },
m_dNMoment{0.0}
{
	this->m_iDatumSize = timer.NumRuns() * timer.DatumSize();
	_ASSERT(this->m_iDatumSize == timer.NumRuns() * timer.DatumSize());
	this->m_vSamples = std::vector<unsigned long long>(this->m_iDatumSize);
	this->m_vSamples.operator=(std::move(timer.Times()));
	for (int i{ 0 }; i != this->m_iDatumSize; ++i){
		
		this->m_oAccKurt(this->m_vSamples.operator[](i));
		this->m_oAccNM(this->m_vSamples.operator[](i));
	}
	this->m_dKurtosis = this->m_oExtrKurt(this->m_oAccKurt);
	this->m_dNMoment = this->m_oExtrNM(this->m_oAccNM);
	std::printf("Kurtosis=%4.16f |  Moment[%d]=%4.16f\n", this->m_dKurtosis,N,this->m_dNMoment);
}

template<class Timer, std::size_t N>  mathlib::KurtosisMoment<Timer, N>::KurtosisMoment(_In_ KurtosisMoment const &rhs) :
m_vSamples{ rhs.m_vSamples },
m_iDatumSize{ rhs.m_DatumSize },
m_dKurtosis{ rhs.m_dKurtosis },
m_dNMoment{ rhs.m_dNMoment },
m_oAccKurt{ rhs.m_oAccKurt },
m_oAccNM{ rhs.m_oAccNM },
m_oExtrKurt{ rhs.m_oExtrKurt },
m_oExtrNM{ rhs.m_oExtrNM }
{

}

template<class Timer, std::size_t N>  mathlib::KurtosisMoment<Timer, N>::KurtosisMoment(_In_ KurtosisMoment &&rhs) :
m_vSamples{ std::move(rhs.m_vSamples) },
m_iDatumSize{ std::move(rhs.m_vSamples) },
m_dKurtosis{ std::move(rhs.m_dKurtosis) },
m_dNMoment{ std::move(rhs.m_dNMoment) },
m_oAccKurt{ std::move(rhs.m_oAccKurt) },
m_oAccNM{ std::move(rhs.m_oAccNM) },
m_oExtrKurt{ std::move(rhs.m_oExtrKurt) },
m_oExtrNM{ std::move(rhs.m_oExtrNM) }
{

}

template<class Timer, std::size_t N> mathlib::KurtosisMoment<Timer, N> &  mathlib::KurtosisMoment<Timer, N>::operator=(_In_ KurtosisMoment const &rhs)
{
	if (this == &rhs) return (*this);

	this->m_vSamples.operator=(rhs.m_vSamples);
	this->m_iDatumSize = rhs.m_iDatumSize;
	this->m_dKurtosis = rhs.m_dKurtosis;
	this->m_dNMoment = rhs.m_dNMoment;
	this->m_oAccKurt = rhs.m_oAccKurt;
	this->m_oAccNM = rhs.m_oAccNM;
	this->m_oExtrKurt = rhs.m_oExtrKurt;
	this->m_oExtrNM = rhs.m_oExtrNM;
	return (*this);
}

template<class Timer, std::size_t N> mathlib::KurtosisMoment<Timer, N> &  mathlib::KurtosisMoment<Timer, N>::operator=(_In_ KurtosisMoment &&rhs)
{
	if (this == &rhs) return (*this);

	this->m_vSamples.operator=(std::move(rhs.m_vSamples));
	this->m_iDatumSize = std::move(rhs.m_iDatumSize);
	this->m_dKurtosis = std::move(rhs.m_dKurtosis);
	this->m_dNMoment = std::move(rhs.m_dNMoment);
	this->m_oAccKurt = std::move(rhs.m_oAccKurt);
	this->m_oAccNM = std::move(rhs.m_oAccNM);
	this->m_oExtrKurt = std::move(rhs.m_oExtrKurt);
	this->m_oExtrNM = std::move(rhs.m_oExtrNM);
	return (*this);
}



template<class Timer, std::size_t N>  std::vector<unsigned long long> &  mathlib::KurtosisMoment<Timer, N>::Samples() const {

	return this->m_vSamples;
}

template<class Timer, std::size_t N>   int          mathlib::KurtosisMoment<Timer, N>::DatumSize() const {

	return this->m_iDatumSize;
}

template<class Timer, std::size_t N>   double       mathlib::KurtosisMoment<Timer, N>::Kurtosis() const {

	return this->m_dKurtosis;
}

template<class Timer, std::size_t N>   double       mathlib::KurtosisMoment<Timer, N>::NMoment() const {

	return this->m_dNMoment;
}