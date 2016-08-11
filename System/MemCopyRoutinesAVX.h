
#ifndef _MEM_COPY_ROUTINES_AVX_H_04_14_16
#define _MEM_COPY_ROUTINES_AVX_H_04_14_16

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
C++ structs templated on primitive and some of STL container data types -  declaration.
Memory copy routines based on AVX SIMD.
@file MemCopyRoutinesAVX.h
@author: Bernard Gingold
@version:  1.0.0  25/12/2015
@description: MemCopyRoutinesAVX.h
@reference: none



*/

#include "SystemLibDefs.h"
#if defined __INTEL_COMPILER
#include <omp.h>
#else
#include <omp.h>
#endif

namespace internal_system {

	/*********************************************
	  Declarations of various memory copy
	  routines templated on type T and specialized
	  on STL containers
	**********************************************/

	/************************************************
	             AVX  versions
	*************************************************/

	/************************************************
	             Primary template
	             templated on type T*
	*************************************************/

	template<typename T, const int N>   struct FastAVXMemCpy {

		/*
		      No Cache bypass
		*/

		/* 2x unroll by default */
		std::enable_if<std::is_pointer<T>::value, void>::type
		avx_mem_cpy2x(_In_ const T* __restrict, _Outptr_ T* __restrict, _In_ const int) noexcept(false);

		/* 4x unroll */
		std::enable_if<std::is_pointer<T>::value, void>::type
		avx_mem_cpy4x(_In_ const T* __restrict, _Outptr_ T* __restrict, _In_ const int);

		/* 8x unroll */
		std::enable_if<std::is_pointer<T>::value, void>::type
		avx_mem_cpy8x(_In_ const T* __restrict, _Outptr_ T* __restrict, _In_ const int);

		/* OpenMP based version */
#if defined SYSTEM_USE_OPENMP
		std::enable_if<std::is_pointer<T>::value, void>::type
		avx_mem_cpy_omp(_In_ const T* __restrict, _Outptr_ T* __restrict, _In_ const int, _In_ const int);
#endif

#if REGISTER_COUNT == 0xF
		std::enable_if<std::is_pointer<T>::value, void>::type
		avx_mem_cpy16x(_In_ const T* __restrict, _Outptr_ T* __restrict, _In_ const int);
#endif
	};

	/***************************************************
	          single precision specialization
	****************************************************/

	template<>   struct FastAVXMemCpy<float, 0> {

		/* Unroll 2x */
		static auto  avx_mem_cpy_f32(_In_ const float* __restrict, _Outptr_ float* __restrict, _In_ const int)->void;

		/* Unroll 4x */
		static auto  avx_mem_cpy_f324x(_In_ const float* __restrict, _Outptr_ float* __restrict, _In_ const int)->void;

		/* Unroll 8x */
		static auto  avx_mem_cpy_f328x(_In_ const float* __restrict, _Outptr_ float* __restrict, _In_ const int)->void;

#if defined SYSTEM_USE_OPENMP
		/* OpenMP version without unrolling */
		static auto  avx_mem_cpy_f32_omp(_In_ const float* __restrict, _Outptr_ float* __restrict, _In_ const int, _In_ const int)->void;
#endif

		/* Unroll 16x */
#if defined REGISTER_COUNT == 0xF
		static auto  avx_mem_cpy_f3216x(_In_ const float* __restrict, _Outptr_ float* __restrict, _In_ const int)->void;
#endif

	};

	/*****************************************************
	         double precision specialization
	******************************************************/
	template<>     struct FastAVXMemCpy<double, 0> {

		/* Unroll 2x */
		static auto  avx_mem_cpy_f64(_In_ const double* __restrict, _Outptr_ double* __restrict, _In_ const int)->void;

		/* Unroll 4x */
		static auto  avx_mem_cpy_f644x(_In_ const double* __restrict, _Outptr_ double* __restrict, _In_ const int)->void;

		/* Unroll 8x */
		static auto  avx_mem_cpy_f648x(_In_ const double* __restrict, _Outptr_ double* __restrict, _In_ const int)->void;

		
#if defined SYSTEM_USE_OPENMP
		/* OpenMP version without unrolling */
		static auto  avx_mem_cpy_f64_omp(_In_ const double* __restrict, _Outptr_ double* __restrict, _In_ const int, _In_ const int)->void;
#endif

		/* Unroll 16x */
#if REGISTER_COUNT == 0xF
		static auto  avx_mem_cpy_f6416x(_In_ const double* __restrict, _Outptr_ double* _restrict, _In_ const int)->void;
#endif
		
	};

	/********************************************************
	           std::valarray<float> specialization
	*********************************************************/

	template<>   struct  FastAVXMemCpy<std::valarray<float>, 0> {

		/* Unroll 2x */
		static  auto  avx_mem_cpy_valf32(_In_ const std::valarray<float> &, _Outptr_ std::valarray<float> &)->void;

		/* Unroll 4x */
		static  auto  avx_mem_cpy_valf324x(_In_ const std::valarray<float> &, _Outptr_ std::valarray<float> &)->void;

		/* Unroll 8x */
		static  auto  avx_mem_cpy_valf328x(_In_ const std::valarray<float> &, _Outptr_ std::valarray<float> &)->void;

#if defined SYSTEM_USE_OPENMP
		/* Use OpenMP without unrolling */
		static  auto  avx_mem_cpy_valf32_omp(_In_ const std::valarray<float> &, _Outptr_ std::valarray<float> &, _In_ const int)->void;
#endif

		/* Unroll 16x */
#if REGISTER_COUNT == 0xF
		static  auto  avx_mem_cpy_valf3216x(_In_ const std::valarray<float> &, _Outptr_ std::valarray<float> & )->void;
#endif
	};

	/********************************************************
	          std::valarray<double> specialization
	*********************************************************/
	template<>     struct FastAVXMemCpy<std::valarray<double>, 0> {

		/* Unroll 2x */
		static  auto  avx_mem_cpy_valf64(_In_ const std::valarray<double> &, _Outptr_ std::valarray<double> &)->void;

		/* Unroll 4x */
		static  auto  avx_mem_cpy_valf644x(_In_ const std::valarray<double> &, _Outptr_ std::valarray<double> &)->void;

		/* Unroll 8x */
		static  auto  avx_mem_cpy_valf648x(_In_ const std::valarray<double> &, _Outptr_ std::valarray<double> &)->void;

#if defined SYSTEM_USE_OPENMP
		/* Uses OpenMP without unrolling */
		static  auto  avx_mem_cpy_valf64_omp(_In_ const std::valarray<double> &, _Outptr_ std::valarray<double> &, _In_ const int)->void;
#endif

		/* Unroll 16x if defined x86-64*/
#if  REGISTER_COUNT == 0xF
		static  auto  avx_mem_cpy_valf6416x(_In_ const std::valarray<double> &, _Outptr_ std::valarray<double> &)->void;
#endif
	};

	/********************************************************
	           std::array<float, N> specialization
	*********************************************************/
	template<const int N>   struct FastAVXMemCpy<std::array<float, N>, 0> {

		/* Unroll 2x */
		static  auto  avx_mem_cpy_arf32(_In_ const std::array<float, N> &, _Out_ std::array<float, N> &)->void;

		/* Unroll 4x */
		static  auto  avx_mem_cpy_arf324x(_In_ const std::array<float, N> &, _Out_ std::array<float, N> &)->void;

		/* Unroll 8x */
		static  auto  avx_mem_cpy_arf328x(_In_ const std::array<float, N> &, _Out_ std::array<float, N> &)->void;
		
#if defined SYSTEM_USE_OPENMP
		/* Uses OpenMP without unrolling */
		static  auto  avx_mem_cpy_arf32_omp(_In_ const std::array<float, N> &, _Out_ std::array<float, N> &, _In_ const int)->void;
#endif

#if REGISTER_COUNT == 0xF

		/* Unroll 16x if defined __WIN64*/
		static  auto  avx_mem_cpy_arf3216x(_In_ const std::array<float, N> &, _Out_ std::array<float, N> &)->void;
#endif
	};

	/********************************************************
	           std::array<double, N> specialization
	*********************************************************/
	template<const int N>   struct FastAVXMemCpy<std::array<double, N>, 0> {

		/* Unroll 2x */
		auto  static  avx_mem_cpy_arf64(_In_ const std::array<double, N> &, _Out_ std::array<double, N> &)->void;

		/* Unroll 4x */
		auto  static  avx_mem_cpy_arf644x(_In_ const std::array<double, N> &, _Out_ std::array<double, N> &)->void;

		/* Unroll 8x */
		auto  static  avx_mem_cpy_arf648x(_In_ const std::array<double, N> &, _Out_ std::array<double, N> &)->void;

#if defined SYSTEM_USE_OPENMP

		/* Uses OpenMP without unrolling */
		auto  static  avx_mem_cpy_f64_omp(_In_ const std::array<double, N> &, _Out_ std::array<double, N> &)->void;
#endif

#if REGISTER_COUNT == 0xF

		/* Unroll 16x */
		auto  static avx_mem_cpy_f6416x(_In_ const std::array<double,N> &, _Out_ std::array<double,N> &)->void;
#endif
	};

	/**********************************************************
	            std::vector<float> specialization
	***********************************************************/
	template<>    struct  FastAVXMemCpy<std::vector<float>, 0> {

		/* Unroll 2x */
		auto  static  avx_mem_cpy_vecf32(_In_ const std::vector<float> &, _Out_ std::vector<float> &)->void;

		/* Unroll 4x */
		auto  static  avx_mem_cpy_vecf324x(_In_ const std::vector<float> &, _Out_ std::vector<float> &)->void;

		/* Unroll 8x */
		auto  static  avx_mem_cpy_vecf328x(_In_ const std::vector<float> &, _Out_ std::vector<float> &)->void;

#if defined SYSTEM_USE_OPENMP

		/* Uses OpenMP without unrolling */
		auto  static  avx_mem_cpy_vecf32_omp(_In_ const std::vector<float> &, _Out_ std::vector<float> &, _In_ const int)->void;
#endif

#if  REGISTER_COUNT == 0xF

		/* Unroll 16x */
		auto  static  avx_mem_cpy_vecf3216x(_In_ const std::vector<float> &, _Out_ std::vector<float> &)->void;
#endif 
	};

	/**********************************************************
	         std::vector<double> specialization
	***********************************************************/
	template<>    struct FastAVXMemCpy<std::vector<double>, 0> {

		/* Unroll 2x */
		auto  static  avx_mem_cpy_vecf64(_In_ const std::vector<double> &, _Out_ std::vector<double> &)->void;

		/* Unroll 4x */
		auto  static  avx_mem_cpy_vecf644x(_In_ const std::vector<double> &, _Out_ std::vector<double> &)->void;

		/* Unroll 8x */
		auto  static  avx_mem_cpy_vecf648x(_In_ const std::vector<double> &, _Out_ std::vector<double> &)->void;

#if defined SYSTEM_USE_OPENMP

		/* Uses OpenMP without unrolling */
		auto  static  avx_mem_cpy_vecf64_omp(_In_ const std::vector<double> &, _Out_ std::vector<double> &, _In_ const int)->void;
#endif

#if  REGISTER_COUNT == 0xF

		/* Unroll 16x */
		auto  static  avx_mem_cpy_vecf6416x(_In_ const std::vector<double> &, _Out_ std::vector<double> &)->void;
#endif 
	};

#include "MemCopyRoutinesAVX.inl"
}
#endif /*_MEM_COPY_ROUTINES_AVX_H_04_14_16*/