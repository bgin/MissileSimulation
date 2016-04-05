
#ifndef _PERF_MEASUREMENT_H_
#define _PERF_MEASUREMENT_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
C++ Performance measurement and timing templated class based upon RDTSC(P) instruction - declaration.

@file PerfMeasurement.h
@author: Bernard Gingold
@version:  1.0  25/12/2015
@description: PerfMeasurement.h
*/
#include "MathLibDefinitions.h"
#include <boost/accumulators/accumulators.hpp>


using namespace boost::accumulators;

namespace  mathlib
{


	template<typename _Fx, int I, int J>   class PerfTimer
	{




	public:

		/*
		@brief "Main" C-tor responsible for the call to timed function.
		  template parameter _Fx is passed to the constructor. This 
		  parameter (lambda functor) contains call to timed function.
		*/
	__forceinline 	PerfTimer(_In_ _Fx);

		/*
		@brief  D-tor (default)
		*/
	__forceinline 	~PerfTimer() = default;

	    
	   /*
	   @brief  Copy-Ctor.
	   */
	__forceinline   PerfTimer(_In_ PerfTimer const&);

	  /*
	  @brief   Move-Ctor.
	  */
	 __forceinline   PerfTimer(_In_ PerfTimer &&);


	    /*
	    @brief     Member  operators
	    */

	    /*
	    @brief     copy-assignment operator=
	    */
	  __forceinline  PerfTimer &         operator=(_In_ PerfTimer const&);
 
	    /*
	    @brief      move-asignment  operator=
	    */
	   __forceinline  PerfTimer &         operator=(_In_ PerfTimer &&);
		/*
		@brief  Accessor functions
		*/

		/*
		@brief  Returns this->m_oTimes vector filled with the timing samples.
		*/
		__forceinline   std::vector<unsigned long long>  Times() const;

		/*
		@brief   Returns this->m_iNumRuns member variable.
		*/
		__forceinline   int                              NumRuns() const;

		/*
		@brief   Returns  this->m_iDatumSize  member variable.
		*/
		__forceinline   int                              DatumSize() const;



	public:


		/*
		@brief  Vector containing accurate time samples of type unsigned long long.
		*/
		std::vector<unsigned long long>  m_oTimes;

		/*
		@brief  Number of outer loop iterations.
		*/
		int m_iNumRuns = I;

		/*
		@brief  Number of inner loop iterations.
		*/
		int m_iDatumSize = J;

		/*
		@brief  Maximum number of timing test runs. The value of MAX_RUNS is 1000.
		*/
		const static int MAX_RUNS;

		/*
		@brief  Maximum  number of timed function calls. The value is 10000.
		*/
		const static int MAX_DATUM;
	};



	



#include "PerfMeasurement.inl"
}

#endif   /*_PERF_MEASUREMENT_H_*/