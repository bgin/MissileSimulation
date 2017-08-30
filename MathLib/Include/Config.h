
#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifndef CONFIG_VERSION_MAJOR
#define CONFIG_VERSION_MAJOR 1
#endif

#ifndef CONFIG_VERSION_MINOR
#define CONFIG_VERSION_MINOR 0
#endif

#ifndef CONFIG_PATCH_VERSION
#define CONFIG_PATCH_VERSION 0
#endif

#ifndef CONFIG_CREATE_DATE
#define CONFIG_CREATE_DATE "Date: 2016-08-29 Time: 09:39 AM"
#endif

/* Set this value to successful build date/time.*/
#ifndef CONFIG_BUILD_DATE
#define CONFIG_BUILD_DATE " "
#endif


/* Start of Compiler specific declarations.*/

/* Compiler supported CPP version
as reported by reading __cplusplus macro def.*/
#if defined (__cplusplus) 
#define MATH_LIB_CXX_98 199711L
#define MATH_LIB_CXX_11 201103L
#define MATH_LIB_CXX_14 201402L
#endif

/* Deteremine current version supported by ICC.*/
#if defined (__cplusplus) && !defined   (__INTEL_CXX11_MODE__)
#if MATH_LIB_CXX_98 < MATH_LIB_CXX_11
#define MATH_LIB_DEFAULT_CXX_VERSION 199711L
#else
#define MATH_LIB_DEFAULT_CXX_VERSION 201103L
#endif
#endif

// Is Intel Compiler choosen as default
// library compiler?

#if defined __INTEL_COMPILER
#define MATH_LIB_COMPILED_BY_ICC 0x1
#else
#define MATH_LIB_COMPILED_BY_MSVC 0x0
#endif

/* Is 64bit mode current? */

#if (defined (_M_AMD64) || defined (_M_X64_) || defined (__amd64) ) \
	&& !defined (__x86_64__)
#define __x86_64__ 1
#endif


/* Determine architectural support for full set
of GP registers*/
#if __x86_64__ == 1
#define MATHLIB_HAS_FULL_GPR_SET 16
#elif __x86_64__ == 0
#define MATHLIB_HAS_FULL_GPR_SET 8
#else
#error "ERROR: Cannot determine 32bit or 64bit mode!! "
#endif

/* Determine architectural support for full set
of SIMD registers*/
#if __x86_64__ == 1
#define MATHLIB_HAS_FULL_SIMD_REG_SET 32
#elif __x86_64__ == 0
#define MATHLIBLIB_HAS_FULL_SIMD_REG_SET 16
#else
#error "ERROR: Cannot determine 32bit or 64bit mode!! "
#endif

/* Fixing problem of defined in WinDef macros:
1) min.
2) max.
*/

#if defined _MSC_VER
#if defined (_WINDEF_) && defined (min) && defined (max)
#undef min
#undef max
#endif
#if !defined NOMINMAX
#define NOMINMAX
#endif
#endif


/*
Compiler optimization settings.
*/
#ifdef MATH_LIB_COMPILED_BY_ICC
#if !defined(NO_OTIMIZATION)
#define NO_OPTIMIZATION 0x0
#if !defined(OPTIMIZATION_O1)
#define OPTIMIZATION_01 0x1
#if !defined(OPTIMIZATION_O2)
#define OPTIMIZATION_02 0x2
#if !defined(OPTIMIZATION_O3)
#define OPTIMIZATION_O3 0x3
#endif
#endif
#endif
#endif
#endif

/*
Using OpenMP.
*/
#if !defined(USE_OPENMP)
#define USE_OPENMP 0x1
#if defined (MATH_LIB_COMPILED_BY_ICC)
#include <omp.h>
#elif defined (MATH_LIB_COMPILED_BY_MSVC)
#include <omp.h>
#else
#error "UNsupported Compiler version"
#endif
#endif

#if defined (USE_OPENMP) && \
USE_OPENMP == 1
#define OMP_VER_10 10
#define OMP_VER_20 20
#define OMP_VER_30 30
#define OMP_VER_40 40
#define OMP_VER_45 45
#define OMP_CURR_VER 40
#endif



/*
Intel MKL support.
Include all headers - master header file.
*/
#if !defined(USE_MKL)
#define USE_MKL 0x1
#if defined (MATH_LIB_COMPILED_BY_ICC)
//Include all headers - master header file.
#include <mkl.h>
#else
#error "Unsupported Compiler - cannot include MKL headers"
#endif
#endif

// Debug mode.
#if defined(_DEBUG)
#define MATH_LIB_DEBUG_ON 0x1
#undef _DEBUG
#endif

#if defined (MATH_LIB_DEBUG_ON)
#define DEBUG_VERBOSE 0x1
#else
#define DEBUG_VERBOSE 0x0
#endif

/*
Auto-vectorisation.
*/
#ifdef MATH_LIB_COMPILED_BY_ICC
#define ICC_AUTO_VECTORISE 0x1
#else
#define ICC_AUTO_VECTORISE 0x0
#endif


/*
Compiler software prefetching.
*/

#ifdef MATH_LIB_COMPILED_BY_ICC
#define ICC_PREFETCH_L1 0x1
#define ICC_PREFETCH_L2 0x2
#define ICC_PREFETCH_L3 0x3
#define ICC_PREFETCH_NTA 0x4
#endif

#if defined ICC_PREFETCH_L1
#define L1_VEC_ITERS_SHORT  0x4
#define L1_VEC_ITERS_LONG   0x8
#endif

/* Manual unrolling settings */
#if defined (MATH_LIB_COMPILED_BY_ICC) && \
	MATH_LIB_COMPILED_BY_ICC == 1
#define USE_MANUAL_UNROLLING 0x1
#else
#define USE_MANUAL_UNROLLING 0x0
#error "ERROR: Cannot Detect Intel Compiler!!"
#endif

#if defined (USE_MANUAL_UNROLLING) && \
	USE_MANUAL_UNROLLING == 1
#define UNROLL_2X  0x2
#define UNROLL_4X  0x4
#define UNROLL_8X  0x8
#if __x86_64__ == 1
#define UNROLL_16X  0x10
#define UNROLL_32X  0x20
#endif
#endif

/* Software Prefetching distances */
#if defined(MATH_LIB_COMPILED_BY_ICC) && \
	MATH_LIB_COMPILED_BY_ICC == 1
#define USE_SOFT_PREFETCHING 0x1
#else
#define USE_SOFT_PREFETCHING 0x0
#error "ERROR: Cannot Detect Intel Compiler!!"
#endif

#if defined (USE_SOFT_PREFETCHING) && \
	USE_SOFT_PREFETCHING == 1
#define PREFETCH_TO_L1D 0x1
#define PREFETCH_TO_L2  0x2
#define PREFETCH_TO_L3  0x3
/* Prefetching in terms of loop cycles no.*/
#define PREFETCH_L1_NCYCLES 0x1
#define PREFETCH_L2_NCYCLES 0x2
#define PREFETCH_L3_NCYCLES 0x3
#else
#error "ERROR: Cannot proceed , probably invalid Compiler!!"
#endif

// Set this value to accordingly to your machine CPU.
#if defined (PREFETCH_TO_L1D)
constexpr int L1_MAX_SP{ 8000 };
constexpr int L1_MAX_DP{ 4000 };
#endif

// Set this value to accordingly to your machine CPU.
#if defined (PREFETCH_TO_L2)
constexpr int L2_MAX_SP{ 8 * L1_MAX_SP };
constexpr int L2_MAX_DP{ 8 * L1_MAX_DP };
#endif

// Set this value to accordingly to your machine CPU.
#if defined (PREFETCH_TO_L3)
constexpr int L3_MAX_SP{ 1572864 };
constexpr int L3_MAX_DP{ 786432 };
#endif

/* You should test these values on your machine!!*/
#if defined (PREFETCH_L1_NCYCLES)
constexpr int L1_NCYCLES{ 4 };
#endif

/* You should test these values on your machine!!*/
#if defined (PREFETCH_L2_NCYCLES)
constexpr int L2_NCYCLES{ 8 };
#endif

/* You should test these values on your machine!!*/
#if defined (PREFETCH_L3_NCYCLES)
constexpr int L3_NCYCLES{ 16 };
#endif



// Memory alignment values.
#if defined (MATH_LIB_COMPILED_BY_ICC) && \
	MATH_LIB_COMPILED_BY_ICC == 1
#ifndef _MM_MALLOC_ALIGNED_
#define _MM_MALLOC_ALIGNED_
#else
#undef _MM_MALLOC_ALIGNED_
#error "ERROR: Cannot Detect Intel Compiler!!"
#endif
#endif

#if defined (_MM_MALLOC_ALIGNED_)
constexpr int align16B{ 16 };
constexpr int align32B{ 32 };
#endif

// Local defines used mainly for printing:
#define HLINES "---------------------------\n"
#define ELEMS "element's address:   element's value:   \n"


// Emulate Fortran 'OPTIONAL' keyword.
#ifndef FORTRAN_OPTIONAL
#define FORTRAN_OPTIONAL
#endif


#endif /*__CONFIG_H__*/