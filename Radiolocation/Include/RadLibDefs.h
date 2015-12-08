
#ifndef _RADLIB_DEFS_H_
#define _RADLIB_DEFS_H_

#include <vector>
#include <functional>
#include <complex>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <xmmintrin.h>

#ifndef USE_OPENMP
#define USE_OPENMP
#include <omp.h>
#endif

#ifndef USE_VECTORIZATION
#define USE_VECTORIZATION 0x1
#endif

#ifndef USE_WIN_THREADS
#define USE_WIN_THREADS
#include <Windows.h>
#endif

#if defined USE_OPENMP
#undef USE_WIN_THREADS
#endif
#define DEBUG_VERBOSE 0x1
#define MATHEMATICA_VISUALIZE 0x1 // undef if Mathematica Data Visualization is not used.

#if defined _DEBUG
#ifndef OMP_TIMING
#define OMP_TIMING 0x1
#endif
#endif

#ifndef DEBUG_SHOW_DATA
#define DEBUG_SHOW_DATA 0x1
#endif
// Library global functions and variables.

#ifndef DEBUG_TRACE_EXECUTION
#define DEBUG_TRACE_EXECUTION 0x1
#endif

// Save data to file and use later to construct resulting waveform in Mathematica.





static   void  save_file(_In_ std::vector<std::pair<double, double>> &v, const char* fname1, const char* fname2)
{
	_ASSERT((nullptr != fname1) && (nullptr != fname2));

	FILE* fp1, *fp2;
	if (fopen_s(&fp1, fname1, "wt") != 0)
	{
		std::printf("Failed to open file:%s, ...returning\n", fname1);
		return;
	}
	else
	{
		std::printf("Writing to file:%s first component\n", fname1);
		for (size_t i = 0; i != v.size(); ++i)
			fprintf(fp1, "%d,%.9f\n", i, v[i].first);

		std::printf("Finished writing first component to file:%s\n", fname1);
		fclose(fp1);
	}

	if (fopen_s(&fp2, fname2, "wt") != 0)
	{
		std::printf("Failed to open file:%s, ...returning\n", fname2);
		return;
	}
	else
	{
		std::printf("Writing to file:%s second component\n", fname2);
		for (size_t i = 0; i != v.size(); ++i)
			fprintf(fp1, "%d,%.9f\n", i, v[i].second);

		std::printf("Finished writing second component to file:%s\n", fname2);
		fclose(fp2);
	}
}

// Save data to file and use later to construct resulting waveform in Mathematica.
static    void    save_file(_In_ std::vector<double> &v, const char* fname)
{
	_ASSERT(nullptr != fname);

	FILE* fp;
	if (fopen_s(&fp, fname, "wt") != 0)
	{
		std::printf("Failed to open file:%s, ...returning\n", fname);
		return;
	}
	else
	{
		
		std::printf("Started writing the content of vector to file:%s\n", fname);
		for (size_t i{ 0 }; i != v.size(); ++i)
			fprintf(fp, "%d,%.9f\n",i,v.operator[](i));

		std::printf("Finished writing the content of vector to file:%s\n", fname);
		fclose(fp);
	}
}

// Imaginary j.
static  std::complex<double>  j()
{
	std::complex<double> i = -1;
	return std::sqrt(i);
}

// Wrapper around omp_get_wtick() function.

static  double  wrapp_omp_get_wtick()
{
	return omp_get_wtick();
}

// Wrapper around omp_get_wtime() function.

static double   wrapp_omp_get_wtime()
{
	return omp_get_wtime();
}

__forceinline   static  double  signum(_In_ const double arg)
{
	const double fp_zero{ 0.0 };
	/*if (arg > fp_zero)
		return 1.0;
	else if (arg == fp_zero)
		return 0.0;
	else if (arg < fp_zero)
		return -1.0;*/
	return ((arg > fp_zero) ? 1.0 : ((arg < fp_zero) ? -1.0 : 0.0));
}
	


/*
Brief: Applies 1 functors to  std::vector<std::pair<>> component of ExpChirpSignal object.
Uses variadic templates.
@Params: lambda functor F , variadic templated argument _Ty , std::vector<std::pair<>> v
@Returns: std::vector v1 passed as an arguments.
@throws: std::runtime_error when vector is empty.
*/
_Raises_SEH_exception_  template<typename F, typename... _Ty> __forceinline static void  apply_to(_In_ F f, _In_ _Ty&&... t, _Inout_ std::vector<std::pair<double, double>> &v)
{
	if (!(v.empty()))
	{
		std::vector<std::pair<double, double>>::iterator iter;
		for (iter = v.begin(); iter != v.end(); ++iter)
		{
			iter->first = f(std::forward<_Ty>(t)...);
			iter->second = f(std::forward<_Ty>(t)...);
		}
			
		
	}
	else throw std::runtime_error("Fatal Error in radiolocation::apply_to: Empty vector\n");
}

/*
Brief: Applies 3 functors to each of the vector components of ExpChirpSignal object.
Uses variadic templates.User must pass vectors of the same size.
@Params: lambda functors F1,F2,F3 , variadic templated argument _Ty and v1,v2,v3 std::vector
@Returns: std::vector v1,std::vector v2, std::vector v3 passed as an arguments.
@throws: std::runtime_error when  vectors are empty.
*/
_Raises_SEH_exception_  template<typename F1, typename F2, typename F3, typename... _Ty> __forceinline static void apply_to(_In_ F1 f1, _In_ F2 f2, _In_ F3 f3,
	_In_ _Ty&&... t, std::vector<std::pair<double, double>> &v1, std::vector<double> &v2, std::vector<double> &v3)
{
	
	if (!(v1.empty()) || !(v2.empty()) || !(v3.empty()))
	{
		for (size_t i{ 0 }; i != v1.size(); ++i)
		{
			// Should return argument only
			v1.operator[](i).first = f1(std::forward<_Ty>(t)...);
			v1.operator[](i).second = f1(std::forward<_Ty>(t)...);
			v2.operator[](i) = f2(std::forward<_Ty>(t)...);
			v3.operator[](i) = f3(std::forward<_Ty>(t)...);
		}
	}
	else std::runtime_error("Fatal Error in radiolocation::apply_to: Empty vector(s)\n");
}

/*
"brief: Generate Gaussian Random value.
*/

template<typename Distribution, typename Engine> double  RandDistrValue(_In_ Distribution distro, _In_ Engine eng)
{
	return std::bind(distro, eng).operator()();
}

__forceinline  bool    RayleighSmoothnessCriteria(_In_ const double GrazingAngle, _In_ const double AvrgHeight, _In_ const double Gamma)
{
	//Surface is smooth when the Rayleigh Criteria is less than Pi/2
	const double four_pi{ 4.0 *3.14159265358979 };
	const double half_pi{ 0.5 *3.14159265358979 };
	// return true if smooth, otherwise return false;.
	return  std::fabs((four_pi * AvrgHeight / Gamma) * ::sin(GrazingAngle)) < half_pi ? true : false;
}

namespace radiolocation_constants
{


	static const double c{ 3.12 * 1.0e+8 };

	static const double TWOPI{ 2.0 * 3.1415926535897932e+00 };

	static const double inv_c{ 1.0 / c };
}

#endif  /*_RADLIB_DEFS_H_*/