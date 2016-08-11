#ifndef _TEST_SSE_MEM_CPY_F32_H_10_04_16
#define _TEST_SSE_MEM_CPY_F32_H_10_04_16

#include "../System/MemCopyRoutines.h"
#include "TestUtilities.h"
#include <random>
#include <time.h>
#include <functional>
#include <memory>
#include <iomanip>


namespace  test_internal_system {


	/************************************************
	  Unit tests of single precision specialization
	  of FastSSEMemCpy struct.
	************************************************/

	class  TEST_FastSSEMemCpyF32 {

	public:

		/*******************************************
		  Simple acceptance  Test of sse_mem_cpy_f32 
		  routine.
		********************************************/
	 static	auto    test_sse_mem_cpy_f32()->void;

		/*******************************************
		  Simple  acceptance Test of sse_mem_cpy_f324x 
		  routine.
		********************************************/
	static	auto    test_sse_mem_cpy_f324x()->void;

		/*******************************************
		 Simple acceptance Test of sse_mem_cpy_f328x 
		 routine.
		********************************************/
	static	auto    test_sse_mem_cpy_f328x()->void;
	};

#include "TEST_sse_mem_cpy_f32.inl"
}
#endif /*_TETS_SSE_MEM_CPY_F32_H_10_04_16*/