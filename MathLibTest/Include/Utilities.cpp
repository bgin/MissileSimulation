#include "Utils.h"

void test::Utilities::debug_print(const mathlib::VecF64AVX &obj, const char * msg)
{
	
	std::printf("%s.x=%.15f, %s.y=%.15f, %s.z=%.15f, %s.w=%.15f\n\n",msg, obj.get_m_VecF64().m256d_f64[0], msg,obj.get_m_VecF64().m256d_f64[1],
		msg,obj.get_m_VecF64().m256d_f64[2], msg,obj.get_m_VecF64().m256d_f64[3]);
	return;
}

void test::Utilities::debug_print(const mathlib::NormF64AVX &obj, const char *msg)
{
	std::printf("%s.x=%.15f\n",msg, obj.get_m_VecF64().m256d_f64[0]);
	std::printf("%s.y=%.15f\n", msg, obj.get_m_VecF64().m256d_f64[1]);
	std::printf("%s.z=%.15f\n", msg, obj.get_m_VecF64().m256d_f64[2]);
	std::printf("%s.w=%.15f\n", msg, obj.get_m_VecF64().m256d_f64[3]);
	return;
}

void test::Utilities::debug_print(const mathlib::VecF64AVX *obj, const char * msg)
{
	
	std::printf("%s.x=%.15f, %s.y=%.15f, %s.z=%.15f, %s.w=%.15f\n\n", msg,obj->get_m_VecF64().m256d_f64[0], msg,obj->get_m_VecF64().m256d_f64[1],
	  msg,	obj->get_m_VecF64().m256d_f64[2], msg, obj->get_m_VecF64().m256d_f64[3]);
	return;
}

void test::Utilities::debug_print(const mathlib::NormF64AVX *obj, const char * msg)
{
	std::printf("%s.x=%.15f\n", msg, obj->get_m_VecF64().m256d_f64[0]);
	std::printf("%s.y=%.15f\n", msg, obj->get_m_VecF64().m256d_f64[1]);
	std::printf("%s.z=%.15f\n", msg, obj->get_m_VecF64().m256d_f64[2]);
	std::printf("%s.w=%.15f\n", msg, obj->get_m_VecF64().m256d_f64[3]);
	return;
}

void test::Utilities::print_to_file(const mathlib::VecF64AVX &obj, const char *fname)
{
	FILE * fptr;
	if (fopen_s(&fptr, fname, "wt") != 0)
	{
		std::cerr << "fopen_s failed to open file:" << fname << std::endl;
	}
	else
	{
		std::fprintf(fptr, "Dumping Content of VecF64AVX object to file:%s\n", fname);
		std::fprintf(fptr, "obj.x=%.15f, obj.y=%.15f, obj.z=%.15f, obj.w=%.15f\n", obj.get_m_VecF64().m256d_f64[0], obj.get_m_VecF64().m256d_f64[1],
			obj.get_m_VecF64().m256d_f64[2], obj.get_m_VecF64().m256d_f64[3]);

		fclose(fptr);
	}
}

long long test::Utilities::TSC_start()
{
	return _rdtsc();
}

long long test::Utilities::TSC_stop()
{
	return _rdtsc();
}

ULONGLONG test::Utilities::SysTimerStart()
{
	return ::GetTickCount64();
}

ULONGLONG test::Utilities::SysTimerStop()
{
	return ::GetTickCount64();
}

long long test::Utilities::Get_Cpu_Freq()
{
	// Crude approximation of CPU Frequency.
	long long tstamp0 = 0ULL;
	long long tstamp1 = 0ULL;
	tstamp0 = _rdtsc();
	::Sleep(1);
	tstamp1 = _rdtsc();
	return tstamp1 - tstamp0;
}

void  test::Utilities::Set_Cpu_Affinity()
{
	unsigned int affinity_mask = 0x1;
	DWORD_PTR prev_mask;
	HANDLE thHandle = ::GetCurrentThread();
	prev_mask = ::SetThreadAffinityMask(thHandle, affinity_mask);
	if (prev_mask == 0)
		printf("SetThreadAffinityMask failed with an error 0x%x\n", ::GetLastError());
}

void  test::Utilities::Assert_Equal(const __m256d actual, const __m256d expected, const double epsilon, const char *msg)
{
	 
	double abs_delta = std::numeric_limits<double>::quiet_NaN();
	std::printf("%s, epsilon precision=%.19f\n\n",msg, epsilon);
	std::printf("const __m256d actual:                const __m256d expected:\n");
	std::printf("actual.x=%.15f      |            expected.x=%.15f\n", actual.m256d_f64[0], expected.m256d_f64[0]);
	std::printf("actual.y=%.15f      |             expected.y=%.15f\n", actual.m256d_f64[1],expected.m256d_f64[1]);
	std::printf("actual.z=%.15f      |            expected.z=%.15f\n", actual.m256d_f64[2], expected.m256d_f64[2]);
	std::printf("actual.w=%.15f      |            expected.w=%.15f\n", actual.m256d_f64[3], expected.m256d_f64[3]);
	for (auto i = 0; i != vec_length; ++i)
	{
		if ((abs_delta = std::fabs(actual.m256d_f64[i] - expected.m256d_f64[i])) < epsilon)
		{
			
			std::printf("EQUALITY at index=%d\n",i);
			std::printf("actual=%.15f         |     expected=%.15f\n", actual.m256d_f64[i], expected.m256d_f64[i]);
			std::printf("Abs_Delta=%.15f\n", abs_delta);
		}
		else
		{
			std::printf(" Assertion Failed(INEQUALITY)  at index=%d, in function:%s, on loc:%d\n", i,__FUNCTIONW__,__LINE__);
			std::printf("actual=%.15f         |     expected=%.15f\n", actual.m256d_f64[i], expected.m256d_f64[i]);
			std::printf("Abs_Delta=%.15f\n", abs_delta);
		}
	}
	std::printf("Finished Assert_Equal Test\n\n");
}

void test::Utilities::Assert_Equal(const __m256d actual, const double expected, const double epsilon, const char * msg)
{
	double abs_delta = std::numeric_limits<double>::quiet_NaN();
	std::printf("%s, with epsilon precision=%.15f\n", msg, epsilon);
	std::printf("const __m256d actual   |      const double expected\n              ");
	std::printf("actual.x=%.15f         |      expected=%.15f\n", actual.m256d_f64[0], expected);
	std::printf("actual.y=%.15f         |      expected=%.15f\n", actual.m256d_f64[1], expected);
	std::printf("actual.z=%.15f         |      expected=%.15f\n", actual.m256d_f64[2], expected);
	std::printf("actual.w=%.15f         |      expected=%.15f\n", actual.m256d_f64[3], expected);
	for (auto i = 0; i != vec_length; ++i)
	{
		if ((abs_delta = std::fabs(actual.m256d_f64[i] - expected)) < epsilon)
		{
			std::printf("EQUALITY at index=%d\n", i);
			std::printf("actual=%.15f     |      expected=%.15f\n", actual.m256d_f64[i], expected);
			std::printf("Abs_Delta=%.15f\n", abs_delta);
		}
		else
		{
			std::printf("Assertion Failed(INEQUALITY) at index=%.15f, in function:%s, on loc:%d\n", i,__FUNCTIONW__,__LINE__);
			std::printf("actual=%.15f     |      expected=%.15f\n", actual.m256d_f64[i], expected);
			std::printf("Abs_Delta=%.15f\n", abs_delta);
		}
	}
	std::printf("\n\n");
}

void  test::Utilities::Assert_InEqual(const __m256d actual, const __m256d unexpected, const double epsilon, const char * msg)
{
	double abs_delta = std::numeric_limits<double>::quiet_NaN();
	std::printf("%s, epsilon precision=%.15f\n\n", msg, epsilon);
	std::printf("const __m256d actual           |                const __m256d unexpected\n");
	std::printf("actual.x=%.15f                 |                unexpected.x=%.15f\n", actual.m256d_f64[0], unexpected.m256d_f64[0]);
	std::printf("actual.y=%.15f                 |                unexpected.y=%.15f\n", actual.m256d_f64[1], unexpected.m256d_f64[1]);
	std::printf("actual.z=%.15f                 |                unexpected.z=%.15f\n", actual.m256d_f64[2], unexpected.m256d_f64[2]);
	std::printf("actual.w=%.15f                 |                unexpected.w=%.15f\n", actual.m256d_f64[3], unexpected.m256d_f64[3]);
	for (auto i = 0; i != vec_length; ++i)
	{
		if ((abs_delta = std::fabs(actual.m256d_f64[i] - unexpected.m256d_f64[i])) > epsilon)
		{
			std::printf("INEQUALITY at index=%d\n", i);
			std::printf("actual=%.15f           |                unexpected=%.15f\n", actual.m256d_f64[i], unexpected.m256d_f64[i]);
			std::printf("Abs_Delta=%.15f\n", abs_delta);
		}
		else
		{
			std::printf("Assertion Failed(EQUALITY) at index=%d, in function:%s, on loc:%d\n", i,__FUNCTIONW__,__LINE__);
			std::printf("actual=%.15f           |                unexpected=%.15f\n", actual.m256d_f64[i], unexpected.m256d_f64[i]);
			std::printf("Abs_Delta=%.15f\n", abs_delta);
		}
	}
	std::printf("%s\n", msg);
}

void test::Utilities::Assert_InEqual(const __m256d actual, const double unexpected, const double epsilon, const char * msg)
{
	double abs_delta = std::numeric_limits<double>::quiet_NaN();
	std::printf("%s, with epsilon precision=%.15f\n", msg, epsilon);
	std::printf("const __m256d actual   |      const double unexpected\n              ");
	std::printf("actual.x=%.15f         |      unexpected=%.15f\n", actual.m256d_f64[0], unexpected);
	std::printf("actual.y=%.15f         |      unexpected=%.15f\n", actual.m256d_f64[1], unexpected);
	std::printf("actual.z=%.15f         |      unexpected=%.15f\n", actual.m256d_f64[2], unexpected);
	std::printf("actual.w=%.15f         |      unexpected=%.15f\n", actual.m256d_f64[3], unexpected);
	for (auto i = 0; i != vec_length; ++i)
	{
		if ((abs_delta = std::fabs(actual.m256d_f64[i] - unexpected)) > epsilon)
		{
			std::printf("INEQUALITY at index=%d\n", i);
			std::printf("actual=%.15f     |      expected=%.15f\n", actual.m256d_f64[i], unexpected);
			std::printf("Abs_Delta=%.15f\n", abs_delta);
		}
		else
		{
			std::printf("Assertion Failed(EQUALITY) at index=%d, in function:%s, on loc:%d\n", i,__FUNCTIONW__,__LINE__);
			std::printf("actual=%.15f     |      expected=%.15f\n", actual.m256d_f64[i], unexpected);
			std::printf("Abs_Delta=%.15f\n", abs_delta);
		}
	}
	std::printf("%s\n\n", msg);
}