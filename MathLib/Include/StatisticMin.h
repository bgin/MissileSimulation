
#ifndef _STATISTIC_MIN_H_
#define _STATISTIC_MIN_H_

#include "MathLibDefinitions.h"
#include "PerfMeasurement.h"
#include <boost\accumulators\statistics\stats.hpp>
#include <boost\accumulators\statistics\max.hpp>
#include <boost\accumulators\statistics\min.hpp>
#include <boost\accumulators\statistics\mean.hpp>
#include <boost\accumulators\statistics\error_of.hpp>
#include <boost\accumulators\statistics\error_of_mean.hpp>

#include <algorithm>

using namespace boost::accumulators;



namespace  mathlib
{


	template<typename Timer>  class DatumMinMax
	{


	    public:


			/*
			@brief   Class Ctor.
			*/
			__forceinline   DatumMinMax(_In_ Timer const&);

			/*
			@brief   Class Dtor.
			*/
			__forceinline   ~DatumMinMax() = default;
			
			 
			/*
			@brief      operator= copy-assignment.
			*/

			__forceinline   DatumMinMax &          operator=(_In_ DatumMinMax const&);

			/*
			@brief       operator= move-assignment.
			*/
			__forceinline   DatumMinMax &          operator=(_In_ DatumMinMax &&);

			/*
			        **** Accessor functions ****
		    */

			/*
			@brief   Returns class member variable this->m_iDataSize
			*/
			__forceinline  int                 DataSize() const;

			/*
			@brief   Returns class member variable this->m_uDataSetMax.
			*/
			__forceinline   unsigned long long  DataSetMax() const;

			/*
			@brief   Returns class member variable this->m_uDataSetMin.
			*/
			__forceinline   unsigned long long  DataSetMin() const;

			/*
			@brief   Returns  class member variable this->m_dDataSetMean
			*/
			__forceinline   double              DataSetMean() const;

			/*
			@brief   Returns  class member variable this->m_dErrorMean
			*/
			__forceinline   double              DataSetErrorMean() const;
			/*
			@brief   Returns class member variable this->m_oTimeSamples.
			*/
			__forceinline   std::vector<unsigned long long>   TimeSamples() const;

			/*
			@brief   Returns C-style const pointer to this->m_oTimeSamples container.
			         m_iDataSize is the C-style array Length.
			*/
			__forceinline   const  unsigned long long     *CArray() const;
			

			/*
			        **** Member functions ****
			*/

			/*
			@brief   Returns Maximum and Minimum , Mean and Error of Mean of Timing samples population.
			*/
			__forceinline  void     compute_minmax();

			

	   private:

		   /*
		   @brief  Container object for the time samples.
		   */
		   std::vector<unsigned long long> m_oTimeSamples;

		   /*
		   @brief  Accumulator object for max value.
		   */
		   accumulator_set<unsigned long long, stats<tag::max,tag::min,tag::mean,tag::error_of<tag::mean>>> m_oSamplesMaximum;

		  

		   /*
		   @brief  Size of Datum
		   */
		   int  m_iDataSize;

		   /*
		   @brief  Maximum of Time samples population.
		   */
		   unsigned long long m_uDataSetMax;

		   /*
		   @brief   Minimum of Time Samples population.
		   */
		   unsigned long long m_uDataSetMin;

		   /*
		   @brief   Mean of Time samples population.
		   */
		   double             m_dMean;

		   /*
		   @brief   Erro of Mean value.
		   */
		   double             m_dErrorMean;
		   /*
		   @brief  Returns Maximum value of population.
		   */
		   unsigned long long    getMaximum();

		   /*
		   @brief  Returns Minimum value of population.
		   */
		   unsigned long long    getMinimum();

		   /*
		   @brief  Returns Mean    value of population.
		   */
		   double                getMean();

		   /*
		   @brief  Returns Error of Mean.
		   */
		   double                getErrorMean();
		   

	};


	
#include "StatisticMin.inl"
}
#endif /*_STATISTIC_MIN_H_*/