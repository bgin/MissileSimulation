#ifndef _STATISTIC_KURTOSIS_MOMENT_H_
#define _STATISTIC_KURTOSIS_MOMENT_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
C++ Statistic Kurtosis and N-Moment   templated class based upon boost::accumulators library - clas  declaration.

@file StatisticKurtosisMoment.h
@author: Bernard Gingold
@version:  1.0  25/12/2015
@description: ExtendedPSquare.h
*/

#include "MathLibDefinitions.h"
#include <boost\accumulators\accumulators.hpp>
#include <boost\accumulators\statistics\stats.hpp>
#include <boost\accumulators\statistics\kurtosis.hpp>
#include <boost\accumulators\statistics\moment.hpp>

using namespace boost::accumulators;


namespace mathlib
{

	/*
	@brief Template parameter Timer is for timer object, argument std::size_t N is for N-moment.
	*/
	template<class Timer, std::size_t N> class KurtosisMoment
	{


	public:


		/*
		@brief Defaulted default Ctor
		*/
		KurtosisMoment() = delete;

		/*
		@brief  "Main" class Ctor.
		*/
		KurtosisMoment(_In_ Timer const&);

		/*
		@brief  Copy-Ctor.
		*/
		KurtosisMoment(_In_ KurtosisMoment const&);

		/*
		@brief  Move-Ctor.
		*/
		KurtosisMoment(_In_ KurtosisMoment &&);

		/*
		@brief  Dtor
		*/
		~KurtosisMoment() = default;

		/*
		         ***  Member and friend operators ***
		*/

		/*
		@brief       operator= copy-assign.
		*/
		KurtosisMoment &        operator=(_In_ KurtosisMoment const&);

		/*
		@brief       operator=  move-assign.
		*/
		KurtosisMoment &        operator=(_In_ KurtosisMoment &&);

		

		/* 
		          *** Member access functions ***
		*/

		/*
		@brief   Returns this->m_vSamples.
		*/
		std::vector<unsigned long long> &     Samples() const;

		/*
		@brief   Returns this->m_iDatumSize.
		*/
		__forceinline   int            DatumSize() const;

		/*
		@brief   Returns  this->m_dKurtosis.
		*/
		__forceinline   double         Kurtosis() const;

		/*
		@brief   Returns  this->m_dNMoment.
		*/
		__forceinline   double         NMoment() const;

		


	private:

		/*
		@brief  Vector of time samples, class variable this->m_vSamples.
		*/
		std::vector<unsigned long long> m_vSamples;

		/*
		@brief  time samples datum size, class variable this->m_iDatumSize.
		*/
		int    m_iDatumSize;

		/*
		@brief  Kurtosis value, class variable this->m_dKurtosis.
		*/
		double m_dKurtosis;

		/*
		@brief  N-moment value, class variable this->m_dNMoment.
		*/
		double m_dNMoment;

		/*
		@brief  Accumulator object for Kurtosis computation, class variable this->m_oAccKurt
		*/
		accumulator_set<unsigned long long, stats<tag::kurtosis>> m_oAccKurt;

		/*
		@brief  Accumulator object for N-moment computation, class variable this->m_oAccNM.
		*/
		accumulator_set< unsigned long long, stats<tag::moment<N>>> m_oAccNM;

		/*
		@brief  Extractor object for tag::kurtosis, class variable this->m_oExtrKurt.
		*/
		extractor<tag::kurtosis>  m_oExtrKurt;

		/*
		@brief  Extractor object for tag::moment<N>, class variable this->m_oExtrNM.
		*/
		extractor<tag::moment<N>> m_oExtrNM;
	};



#include "StatisticKurtosisMoment.inl"
}

#endif /*_STATISTIC_KURTOSIS_MOMENT_H_*/