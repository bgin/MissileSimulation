#ifndef _STATISTIC_TAIL_QUANTILE_H_
#define _STATISTIC_TAIL_QUANTILE_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
C++ Statistic Tail Quantile   templated class based upon boost::accumulators library - clas  declaration.

@file StatisticTailQuantile.h
@author: Bernard Gingold
@version:  1.0  25/12/2015
@description: StatisticTailQuantile.h
*/

#include "MathLibDefinitions.h"

#include <boost\accumulators\accumulators.hpp>
#include <boost\accumulators\statistics\stats.hpp>
#include <boost\accumulators\statistics\tail_quantile.hpp>

using namespace boost::accumulators;


namespace  mathlib
{

	/*
	@brief   Templated class TailQuantile with following template args: class Timer, int Cache_Size, class Probs
	*/

	template<class Timer, int Cache_Size, class Probs>  class TailQuantile 
	{


	public:

		
		/*
		@brief   Deleted defaulted Ctor.
		*/

		TailQuantile() = delete;

		/*
		@brief    "Main" class Ctor.
		*/
		TailQuantile(_In_ Timer const&, _In_ Probs const&);

		/*
		@brief    Copy-Ctor.
		*/
		TailQuantile(_In_ TailQuantile const&);

		/*
		@brief    Move-Ctor.
		*/
		TailQuantile(_In_ TailQuantile &&);

		/*
		@brief    Dtor.
		*/
		~TailQuantile() = default;

		/*
		      ***  Class member operators ***
			  
		*/

		/*
		@brief   operator= , copy-assign rhs to *this.
		*/
		TailQuantile &     operator=(_In_ TailQuantile const&);

		/*
		@brief   operator=,  move-asign rhs to *this.
		*/
		TailQuantile &     operator=(_In_ TailQuantile &&);


		/*
		      ***  Class  member accessor method  ***
		*/

		/*
		@brief     Returns this->m_vSamples variable.
		*/
		std::vector<unsigned long long>       Samples() const;

		/*
		@brief     Returns  this->m_iDatumSize variable.
		*/
		__forceinline    int               DatumSize() const;

		/*
		@brief     Returns  this->m_vRResult variable.
		*/
		std::vector<double>               RResult() const;

		/*
		@brief     Returns  this->m_vLResult.
		*/
		std::vector<double>               LResult() const;


	private:

		/*
		@brief    Vector of time samples, class variable m_vSamples.
		*/
		std::vector<unsigned long long> m_vSamples;

		/*
		@brief    Size of samples set, class variable m_iDatumSize
		*/
		int               m_iDatumSize;

		/*
		@brief    Vector of right tail quantile results, class variable m_vRResults.
		*/
		std::vector<double>  m_vRResults;

		/*
		@brief    Vector of left tail quantile results, class variable m_vLResults.
		*/
		std::vector<double>  m_vLResults;
		/*
		@brief     Accumulator object computes right tail quantile, class variable m_oAccRTQ.
		*/
		accumulator_set<unsigned long long, stats<tag::quantile>> m_oAccRTQ;

		/*
		@brief     Accumulator object computes left tail quantile, class variable m_oAccLTQ.
		*/
		accumulator_set<unsigned long long, stats<tag::quantile>>  m_oAccLTQ;

		/*
		@brief     Extractor object, class variable m_oExtrTQ.
		*/
		extractor<tag::quantile>   m_oExtrTQ;


	};

#include "StatisticTailQuantile.inl"
}



#endif /*_STATISTIC_TAIL_QUANTILE_H_*/