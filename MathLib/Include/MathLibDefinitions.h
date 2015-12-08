
#ifndef _MATH_LIB_DEFINITIONS_H_
#define _MATH_LIB_DEFINITIONS_H_


#if defined (__INTEL_COMPILER) && (__INTEL_COMPILER) < 1400
#error INTEL Compiler version 14.0 needed for partial support of C++11 and INTEL Compiler 15.0 needed for full support of C++11.
#elif defined (__INTEL_COMPILER) && (__INTEL_COMPILER) < 1000
#error Intel Compiler version 10.0 needed to support at least SSE4.
#elif defined (_MSC_VER) && _MSC_VER < 1500
#error MICROSOFT Visual Studio 2013 Compiler or later is required for MathLib compilation.
#endif



// Force inclusion of Intel Intrinsics: SSE, SSE2, SSE3, SSSE3, SSE4.1, SSE4.2, AVX Header Files.
#if defined (__INTEL_COMPILER) && defined (__AVX__)
#include <immintrin.h>
#elif defined (__SSE4_2__)
#include <nmmintrin.h>
#elif defined (__SSE4_1__)
#include <smmintrin.h>
#elif defined (__SSSE3__)
#include <tmmintrin.h>
#elif defined (__SSE3__)
#include <pmmintrin.h>
#elif defined (__SSE2__)
#include <emmintrin.h>
#elif defined (__SSE__)
#include <xmmintrin.h>
#elif defined (_MSC_VER)
#include <intrin.h>
#endif

// Frequently used STD header files
#include <memory>
#include <iostream>
#include <math.h>
#include <functional>
#include <vector>

#if defined _DEBUG
#include <crtdbg.h>
#ifndef DEBUG_PRINT
// Debug macro
/*#define DEBUG_PRINT(expr, message, arg1, arg2)  \	
do \
{ \
\
\
\
if ((expr) && \
	(1 == _CrtDbgReport(_CRT_ERROR, __FILE__, __LINE__, message, arg1, arg2))) \
	_CrtDbgBreak(); \
} while (0);*/
#endif
#ifndef PRINT_DATA
#define PRINT_DATA 0x0
#endif
#ifndef PRINT_TO_FILE
#define PRINT_TO_FILE 0x0
#endif
#endif
#endif /*_MATH_LIB_DEFINITIONS_H_*/