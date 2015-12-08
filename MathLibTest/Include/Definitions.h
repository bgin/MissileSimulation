#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#define PRINT_TO_CONSOLE 0x1
#define PRINT_TO_FILE    0x1
#define ASSERT_EQUAL 0x1
#define ASSERT_INEQUAL 0x1
#if defined ASSERT_EQUAL && defined ASSERT_INEQUAL
#undef PRINT_TO_CONSOLE
#endif




#define SMALL_NUM_ITERS 10
#define MED_NUM_ITERS   1000
#define LARGE_NUM_ITERS 1000000

#define HIGH_PREC_TIMING 0x1

#if defined _WIN32 || defined _WIN64
#include <Windows.h>
#define MED_PREC_TIMING  0x2
#endif
#define LOW_PREC_TIMING  
#if defined LOW_PREC_TIMING
#define CRUDE_SAMPLING 0x1
#else
#define ACCURATE_SAMPLING 0x1
#endif

#endif /*_DEFINITIONS_H_*/