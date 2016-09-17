
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
#define CONFIG_CREATE_DATE "Date: 2016-09-12 Time: 17:19 PM GMT + 2"
#endif

// Set this value to successful build date/time.
#ifndef CONFIG_BUILD_DATE
#define CONFIG_BUILD_DATE " "
#endif

/* Start of Compiler specific declarations.*/

/* Compiler supported CPP version
as reported by reading __cplusplus macro def.*/
#if defined (__cplusplus) 
#define GUIDANCE_LIB_CXX_98 199711L
#define GUIDANCE_LIB_CXX_11 201103L
#define GUIDANCE_LIB_CXX_14 201402L
#endif

/* Deteremine current version supported by ICC.*/
#if defined (__cplusplus) && !defined   (__INTEL_CXX11_MODE__)
#if GUIDANCE_LIB_CXX_98 < GUIDANCE_LIB_CXX_11
#define GUIDANCE_DEFAULT_CXX_VERSION 199711L
#else
#define GUIDANCE_DEFAULT_CXX_VERSION 201103L
#endif
#endif

// Is Intel Compiler choosen as default
// library compiler?

#if defined __INTEL_COMPILER
#define GUIDANCE_COMPILED_BY_ICC
#else
#define GUIDANCE_COMPILED_BY_MSVC
#endif

/* Is 64bit mode current? */

#if (defined (_M_AMD64) || defined (_M_X64_) || defined (__amd64) ) \
	&& !defined (__x86_64__)
#define __x86_64__ 1
#endif


/* Determine architectural support for full set
of GP registers*/
#if __x86_64__ == 1
#define GUIDANCE_HAS_FULL_GPR_SET 16
#elif __x86_64__ == 0
#define GUIDANCE_HAS_FULL_GPR_SET 8
#else
#error "ERROR: Cannot determine 32bit or 64bit mode!! "
#endif

/* Determine architectural support for full set
of SIMD registers*/
#if __x86_64__ == 1
#define GUIDANCE_HAS_FULL_SIMD_REG_SET 32
#elif __x86_64__ == 0
#define GUIDANCE_HAS_FULL_SIMD_REG_SET 16
#else
#error "ERROR: Cannot determine 32bit or 64bit mode!! "
#endif

/*
  Compiler optimization settings.
*/
#ifdef GUIDANCE_COMPILED_BY_ICC
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
#if defined (GUIDANCE_COMPILED_BY_ICC)
#include <omp.h>
#elif defined (GUIDANCE_COMPILED_BY_MSVC)
#include <omp.h>
#else
#error "UNsupported Compiler version"
#endif
#endif

/*
  Intel MKL support.
  Include all headers - master header file.
*/
#if !defined(USE_MKL)
#define USE_MKL 0x1
#if defined (GUIDANCE_COMPILED_BY_ICC)
//Include all headers - master header file.
//#include <mkl.h>
#else
#error "Unsupported Compiler - cannot include MKL headers"
#endif
#endif

// Debug mode.
#if defined(_DEBUG)
#define GUIDANCE_DEBUG_ON 0x1
#undef _DEBUG
#endif

/*
 Auto-vectorisation.
*/
#ifdef GUIDANCE_COMPILED_BY_ICC
#define ICC_AUTO_VECTORISE 0x1
#endif

/*
	Compiler software prefetching.
*/

#ifdef GUIDANCE_COMPILED_BY_ICC
#define ICC_PREFETCH_L1 0x1
#define ICC_PREFETCH_L2 0x2
#define ICC_PREFETCH_L3 0x3
#define ICC_PREFETCH_NTA 0x4
#endif

#if defined ICC_PREFETCH_L1
#define L1_VEC_ITERS_SHORT  0x4
#define L1_VEC_ITERS_LONG   0x8
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



#endif /*__CONFIG_H__*/