#ifndef _SYSTEM_LIB_DEFS_H_05_04_16
#define _SYSTEM_LIB_DEFS_H_05_04_16

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Header file for System library definitions -  declaration.

@file System.h
@author: Bernard Gingold
@version:  1.0  25/12/2015
@description: System.h
@reference  


*/

// Do not check for CPU architecture default to AVX.
#if defined (__INTEL_COMPILER)
#include <immintrin.h>
#else
#include <intrin.h>
#endif
#if  defined _WIN32
#define REGISTER_COUNT 0x8
#else
#define REGISTER_COUNT 0xF
#endif

// Frequently used header files
#include <Windows.h>
#include <iostream>
#include <string>
#include <type_traits>
#include <array>
#include <vector>
#include <valarray>

#ifndef DEBUG_STACK_WALK
#define DEBUG_STACK_WALK 0x1
#endif

// For stack walker utility.
#if defined _DEBUG && defined DEBUG_STACK_WALK
#include <crtdbg.h>
#include <DbgHelp.h>
#endif

#define L1_CACHE_SIZE 8000
#define L1_LOOP_SIZE 0x1F40

#ifndef SYSTEM_USE_OPENMP
#define SYSTEM_USE_OPENMP 0x1
#include <omp.h>
#endif

// Utility routines

namespace g_utils {


	/*
	            Returns exact type of instantiated template argument.

	*/
	template<typename Obj> const std::string  GetTypeName(_In_ const Obj &obj) {

		return std::string(typeid(obj).name());
	}

	/*
	           Wrapper around _ASSERTE macro
	*/
	void     dbg_asserte(_In_ const void* __restrict src, _Outptr_ void* __restrict dest, _In_ const int Length) {
		_ASSERTE((src != nullptr) && (dest != nullptr) && (Length != 0));
	}

	/*
	          Overloaded templated version.
			  Expected that during instantiation Container will have size() member function.
	*/
	template<class Container>  void dbg_asserte(_In_ const Container& c1, _Out_ Container& c2) {
		_ASSERTE((c1.size() > 0 && c2.size() > 0) && (c1.size() == c2.size()));
	}

	/*
	         Checks for args correctnes , throws if false.
	*/
	void     check_args(_In_ const void* __restrict src, _Outptr_ void* __restrict dest, _In_ const int Length,
		_In_ const std::string& msg) {

			if ((src == nullptr) || (dest == nullptr) || (Length == 0))
				throw std::runtime_error(msg);
	}

	/*
	         Overloaded templated version.
			 Expected that during instantiation Container will have size() member function.

	*/
	template<class Container> void check_args(_In_ const Container& c1, _Out_ Container& c2, const std::string& msg) {
		
		if ((c1.size() <= 0 || c2.size() <= 0) || (c1.size() != c2.size()))
			throw std::runtime_error(msg);
	}

	

	/*
	L1D Cache size in no of single precision values.
	*/
	constexpr  size_t L1D_SP_ELEMS{ 8000 };

	/*
	L1D Cache size in no. of double precision values.
	*/
	constexpr  size_t L1D_DP_ELEMS{ 4000 };
}


#endif /*_SYSTEM_LIB_DEFS_H_05_04_16*/