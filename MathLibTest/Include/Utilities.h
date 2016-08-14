#ifndef _UTILS_H_
#define _UTILS_H_
 
//#include "../MathLib/VectorF64AVX.h"
//#include "../MathLib/NormalF64AVX.h"
//#include "../MathLib/Tangent.h"
#include <chrono>
#include <random>
#include "VectorF64AVX_TEST.h"
#include "NormalF64AVX_TEST.h"
#include "Definitions.h"
namespace test
{
	class Utilities
	{

	public:

		// Print to Console and Print to File
		static void debug_print(const mathlib::VecF64AVX &, const char *);

		static void debug_print(const mathlib::VecF64AVX *, const char *);

		static void print_to_file(const mathlib::VecF64AVX &, const char *);

		static void debug_print(const mathlib::NormF64AVX &, const char *);

		static void debug_print(const mathlib::NormF64AVX *, const char *);

		//static void debug_print(const mathlib::NormF64AVX &);

		//static void debug_print(const mathlib::NormF64AVX *);

		//static void debug_print(const mathlib::TangentF64AVX &);

		//static void debug_print(const mathlib::TangentF64AVX *);

         
		// Time measurement functions:

		//High precision TSC timers.
#if defined HIGH_PREC_TIMING
		static long long  TSC_start();

		static long long  TSC_stop();
#endif
		// System Timer Based
#if _WIN32 

		static ULONGLONG SysTimerStart();

		static ULONGLONG SysTimerStop();

		
#endif
		//Miscellaneous functions
		static long long Get_Cpu_Freq();

		static void      Set_Cpu_Affinity();

		static void      Assert_Equal(const __m256d, const __m256d, const double, const char *);

		static void      Assert_Equal(const __m256d, const double, const double, const char *);

		static void      Assert_InEqual(const __m256d, const __m256d, const double, const char *);

		static void      Assert_InEqual(const __m256d, const double, const double, const char *);

		static const int vec_length = 4;

		
		
		// Random Number Generating Functions.
		template<typename _Ty> inline static  _Ty generate_rand_value(const _Ty lo, const _Ty hi)
		{
			_ASSERT(std::fabs(lo) < std::fabs(hi));
			unsigned int status;
				unsigned int seed;
			status = _rdrand32_step(&seed);
			if (!status) throw std::runtime_error(std::string("_rdrand32_step failed"));
			std::default_random_engine dre(seed);
			std::uniform_real_distribution<_Ty> ud( lo, hi);
			return ud.operator()(dre);

		}

		template<typename _Ty, typename Engine> inline static  _Ty generate_rand_value(Engine engine, const _Ty lo, const _Ty hi)
		{
			_ASSERT(std::fabs(lo) < std::fabs(hi));
			std::uniform_real_distribution<_Ty> ud(lo, hi);
			return ud.operator()(engine);
		}

		template<typename _Ty, typename Distribution, typename Engine> inline static _Ty generate_rand_value(Distribution distr, Engine eng,
			const _Ty lo, const _Ty hi)
		{
			_ASSERT(std::fabs(lo) < std::fabs(hi));
			return distr(eng);
		}
	};

	
}
#endif