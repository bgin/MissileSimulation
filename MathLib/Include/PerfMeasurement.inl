
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
C++ Performance measurement and timing templated class based upon RDTSC(P) instruction - implementation.

@file PerfMeasurement.inl
@author: Bernard Gingold
@version:  1.0  25/12/2015
@description: PerfMeasurement.h
*/


template<typename _Fx, int I, int J> const int mathlib::PerfTimer<_Fx, I, J>::MAX_RUNS{ 1000 };

template<typename _Fx, int I, int J> const int mathlib::PerfTimer<_Fx, I, J>::MAX_DATUM{ 10000 };



template<typename _Fx, int I, int J> __forceinline  mathlib::PerfTimer<_Fx, I, J>::PerfTimer(_In_ _Fx functor)
{
	// Check if number of tests and datum does not exceed the limit.
	_ASSERT((this->m_iNumRuns <= MAX_RUNS) && (this->m_iDatumSize <= MAX_DATUM));
	volatile unsigned long long TSC_START{ 0 };
	volatile unsigned long long TSC_STOP{ 0 };
	unsigned int  TSC_AUX;
	int dummy[4] = { 0 }; // for serializing cpuid
	int val{ 0 }; // for serializing cpuid.
	this->m_oTimes = std::vector<unsigned long long>(this->m_iNumRuns * this->m_iDatumSize);
	
	

		

	/*
	@brief  Main testing loop.
	*/
	for (int i{ 0 }; i < this->m_iNumRuns; ++i)
	{
		for (int j{ 0 }; j < this->m_iDatumSize; ++j)
		{

			volatile int vi{ 0 };
		 
			 
			__cpuid(dummy, val);
			TSC_START = __rdtsc();
			functor(j);
		 	__cpuid(dummy, val);
		  	TSC_STOP = __rdtsc();
			if ((TSC_STOP - TSC_START) <= 0)
			{
				std::printf("Fatal Error in Timing at i:%u,j:%u, faulted reading(s): TSC_START=%llu,TSC_STOP=%llu, reading delta=%llu\n",
					i, j, TSC_START, TSC_STOP, (TSC_STOP - TSC_START));
				this->m_oTimes.operator[](i * this->m_iDatumSize + j) = 0ULL;
			}
			else
			{
				this->m_oTimes.operator[](i * this->m_iDatumSize + j) = TSC_STOP - TSC_START;
				//std::printf("timer=%llu\n", this->m_oTimes.operator[](i * this->m_iDatumSize + j));
			}
				
		}
	}
}


template<typename _Fx, int I, int J>  __forceinline   mathlib::PerfTimer< _Fx, I, J>::PerfTimer(_In_ PerfTimer const& rhs) :
m_oTimes{ rhs.m_oTimes },
m_iNumRuns{ rhs.m_iNumRuns },
m_iDatumSize{ rhs.m_iDatumSize }
{

}

template<typename _Fx, int I, int J> __forceinline    mathlib::PerfTimer<_Fx, I, J>::PerfTimer(_In_ PerfTimer &&rhs) :
m_oTimes{ std::move(rhs.m_oTimes) },
m_iNumRuns{ std::move(rhs.m_iNumRuns) },
m_iDatumSize{ std::move(rhs.m_iDatumSize) }
{

}


template<typename _Fx, int I, int J> __forceinline mathlib::PerfTimer<_Fx, I, J> &  mathlib::PerfTimer<_Fx, I, J>::operator=(_In_ PerfTimer const& rhs)
{
	if (this == &rhs) return(*this);
	this->m_oTimes.operator=(rhs.m_oTimes);
	this->m_iNumRuns = rhs.m_iNumRuns;
	this->m_iDatumSize = rhs.m_iDatumSize;
	return (*this);
}

template<typename _Fx, int I, int J> __forceinline mathlib::PerfTimer<_Fx, I, J> &  mathlib::PerfTimer<_Fx, I, J>::operator=(_In_ PerfTimer &&rhs)
{
	if (this == &rhs) return(*this);
	this->m_oTimes.operator=(std::move(rhs.m_oTimes));
	this->m_iNumRuns = std::move(rhs.m_iNumRuns);
	this->m_iDatumSize = std::move(rhs.m_iDatumSize);
	return(*this);
}




