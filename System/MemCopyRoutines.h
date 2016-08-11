#ifndef _MEM_COPY_ROUTINES_H_05_04_16
#define _MEM_COPY_ROUTINES_H_05_04_16

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
C++ structs templated on primitive and some of STL container data types -  declaration.

@file MemCopyRoutines.h
@author: Bernard Gingold
@version:  1.0.0  25/12/2015
@description: MemCopyRoutines.h
@reference


*/

#include "SystemLibDefs.h"
#if defined __INTEL_COMPILER
#include <omp.h>
#else
#include <omp.h>
#endif


namespace   internal_system {

	/************************************************
	               Memory transfer routines
	*************************************************/


	/************************************************
	                 SSE  version 
	*************************************************/

	/************************************************
	             Primary template 
				 templated on type T*
	*************************************************/

	template<typename T, const int N>   struct FastSSEMemCpy {

		/*
		     No cache bypass
		*/
		// Unrolled 2x
		static std::enable_if<std::is_pointer<T>::value, void>::type
		sse_mem_cpy2x(_In_ const T* __restrict , _Outptr_ T* __restrict, _In_ const int);

		// Unrolled 4x
		static std::enable_if<std::is_pointer<T>::value, void>::type
		sse_mem_cpy4x(_In_ const T* __restrict , _Outptr_ T* __restrict , _In_ const int);

		// Unrolled 8x
		static std::enable_if<std::is_pointer<T>::value, void>::type
		sse_mem_cpy8x(_In_ const T* __restrict, _Outptr_ T* __restrict, _In_ const int);

#if defined SYSTEM_USE_OPENMP
		// OpenMP version, without unrolling operates on data size larger than L1D cache size
		static std::enable_if<std::is_pointer<T>::value, void>::type
		sse_mem_cpy_mt(_In_ const T* __restrict, _Outptr_ T* __restrict, _In_ const int, _In_ const int);
#endif
#if REGISTER_COUNT == 0xF
		
		// Unroll 16x
		static std::enable_if<std::is_pointer<T>::value,void>::type
		sse_mem_cp16x(_In_ const T* __restrict, _Outptr_ T* __restrict, _In_ const int);
#endif
	};

	/***************************************************
	          single precision specialization
	****************************************************/
	template<>          struct FastSSEMemCpy<float,0> {

		// Unroll 2x
		static auto    sse_mem_cpy_f32(_In_ const float* __restrict, _Outptr_ float* __restrict,
		_In_ const int)->void;

		// Unroll 4x
		static auto    sse_mem_cpy_f324x(_In_ const float* __restrict, _Outptr_ float* __restrict,
			_In_ const int)->void;

		// Unroll 8x
		static auto    sse_mem_cpy_f328x(_In_ const float* __restrict, _Outptr_ float* __restrict,
			_In_ const int)->void;
#if REGISTER_COUNT == 0xF

		//unroll 16x
		auto sse_mem_cpyf3216x(_In_ const float* __restrict, _Outptr_ float* __restrict,
			_In_ const int)->void;
#endif
	};

	/*****************************************************
	           double precision specialization
	******************************************************/
	template<>          struct FastSSEMemCpy<double,0> {

		// Unroll 2x
	      static	auto    sse_mem_cpy_f64(_In_ const double* __restrict, _Outptr_ double* __restrict,
		_In_ const int)->void;

		// Unroll 4x
	     static	auto    sse_mem_cpy_f644x(_In_ const double* __restrict, _Outptr_ double* __restrict,
		_In_ const int)->void;

		// Unroll 8x
	     static	auto    sse_mem_cpy_f648x(_In_ const double* __restrict, _Outptr_ double* __restrict,
		_In_ const int)->void;

#if  REGISTER_COUNT == 0xF

		// Unroll 16x
	     static	auto    sse_mem_cpy_f6416x(_In_ const double* __restrict, _Outptr_ double* __restrict,
			_In_ const int)->void;
#endif
	};

	/********************************************************
	          std::valarray<float> specialization
	*********************************************************/
	template<>          struct FastSSEMemCpy<std::valarray<float>,0> {

		// Unroll 2x
	    static	auto  sse_mem_cpy_valf32(_In_ const std::valarray<float> &, _Out_ std::valarray<float> &)->void;

		// Unroll 4x
	    static	auto  sse_mem_cpy_valf324x(_In_  std::valarray<float> &, _Out_ std::valarray<float> &)->void;

		// Unroll 8x
	    static 	auto  sse_mem_cpy_valf328x(_In_  std::valarray<float> &, _Out_ std::valarray<float> &)->void;

#if  REGISTER_COUNT == 0xF

		// Unroll 16x
	     static	auto sse_mem_cpy_valf3216x(_In_ const std::valarray<float> &, _Out_ std::valarray<float> &)->void;
#endif

	};

	/********************************************************
	          std::valarray<double> specialization
	*********************************************************/
	template<>          struct FastSSEMemCpy<std::valarray<double>,0> {

		// Unroll 2x.
	     static	auto  sse_mem_cpy_valf64(_In_  std::valarray<double> &, _Out_ std::valarray<double> &)->void;

		// Unroll 4x
	     static	auto  sse_mem_cpy_valf644x(_In_  std::valarray<double> &, _Out_ std::valarray<double> &)->void;

		// Unroll 8x
	     static	auto  sse_mem_cpy_valf648x(_In_  std::valarray<double> &, _Out_ std::valarray<double> &)->void;

#if REGISTER_COUNT == 0xF

		// Unroll 16x
	     static	auto  sse_mem_cpy_valf6416x(_In_ const std::valarray<double> &, _Out_ std::valarray<double> &)->void;

#endif
	};

	/********************************************************
	           std::array<float, N> specialization
	*********************************************************/
	template<const int N>                     struct FastSSEMemCpy<std::array<float, N>, 0> {

		// Unroll 2x
	      static	void  sse_mem_cpy_arf32(_In_  std::array<float, N> &, _Out_ std::array<float, N> &);

		// Unroll 4x
	      static	void  sse_mem_cpy_arf324x(_In_ std::array<float, N> &, _Out_ std::array<float, N>&);

		// Unroll 8x
	      static	void  sse_mem_cpy_arf328x(_In_ std::array<float, N> &, _Out_ std::array<float, N>&);

#if  REGISTER_COUNT == 0xF

		// Unroll 16x
	      static	auto  sse_mem_cpy_arf3216x(_In_ std::aray<float,N> &, _Out_ std::array<float, N> &);
#endif
	};

	/**********************************************************
	          std::array<double, N> specialization
	**********************************************************/
	template<const int N>                     struct  FastSSEMemCpy<std::array<double, N>, 0> {

		// Unroll 2x
	     static	void sse_mem_cpy_arf64(_In_ const std::array<double, N> &, _Out_ std::array<double, N> &);

		// Unroll 4x
	      static	void sse_mem_cpy_arf644x(_In_ const std::array<double, N> &, _Out_ std::array<double, N> &);

		// Unroll 8x
	      static	void sse_mem_cpy_arf648x(_In_ const std::array<double, N> &, _Out_ std::array<double, N> &);

#if REGISTER_COUNT == 0xF
		// Unroll 16x
	     static 	auto sse_mem_cpy_arf6416x(_In_ const std::array<double, N> &, _Out_ std::array<double, N> &)->void;
#endif

	};

	/**********************************************************
	          std::vector<float> specialization
	***********************************************************/
	template<>                    struct FastSSEMemCpy<std::vector<float>, 0> {

		// Unroll 2x
	      static	auto sse_mem_cpy_vecf32(_In_ const std::vector<float> &, _Out_ std::vector<float> &)->void;

		// Unroll 4x
	      static	auto sse_mem_cpy_vecf324x(_In_ const std::vector<float> &, _In_ std::vector<float> &)->void;

		// Unroll 8x
	      static	auto sse_mem_cpy_vecf328x(_In_ const std::vector<float> &, _In_ std::vector<float> &)->void;

#if REGISTER_COUNT == 0xF
		// Unroll 16
	      static	auto sse_mem_cpy_vecf3216x(_In_ const std::vector<float> &, _In_ std::vector<float> &)->void;
#endif
	};

	/***********************************************************
	          std::vector<double> specialization
	***********************************************************/
	template<>                    struct FastSSEMemCpy<std::vector<double>, 0> {

		// Unroll 2x
	      static	static auto sse_mem_cpy_vecf64(_In_ const std::vector<double> &, _Out_ std::vector<double> &)->void;

		// Unroll 4x
	      static 	static auto sse_mem_cpy_vecf644x(_In_ const std::vector<double> &, _Out_ std::vector<double> &)->void;

		// Unroll 8x
		static auto sse_mem_cpy_vecf648x(_In_ const std::vector<double> &, _Out_ std::vector<double> &)->void;

#if REGISTER_COUNT == 0xF
		// Unroll 16x
	      static 	auto sse_mem_cpy_cpy_vecf6416x(_In_ const std::vector<double> &, _Out_ std::vector<double> &)->void;
#endif
	};



#include "MemCopyRoutines.inl"
}
#endif /*_MEM_COPY_ROUTINES_H_05_04_16*/
