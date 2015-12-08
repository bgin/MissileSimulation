
#ifndef _NORMALF64AVX_TEST
#define _NORMALF64AVX_TEST

#include "../MathLib/NormalF64AVX.h"
#include "Definitions.h"
#include "Utils.h"

namespace test
{

	class NormalF64AVX_Test
	{

	public:

      // NormalF64AVX Constructor tests.
      // Single object creation.

		// Test mathlib::NormalF64AVX::NormalF64AVX().
		void static Test_Default_Constructor();

		// Test mathlib::NormalF64AVX::NormalF64AVX(const double [4]).
		void static Test_StArray_Arg_Constructor();

		// Test mathlib::NormalF64AVX::NormalF64AVX(const double).
		void static Test_One_Arg_Constructor();

		// Test mathlib::NormalF64AVX::NormalF64AVX(const double, const double, const double, const double).
		void static Test_Quad_Arg_Constructor();

		// Test mathlib::NormalF64AVX::NormalF64AVX(const __m256d).
		void static Test_YMM_Arg_Constructor();

		// Test mathlib::NormF64AVX::NormF64AVX(const __m256i).
		void static Test_YMMi_Arg_Constructor();

		// Test mathlib::NormF64AVX::NormF64AVX(const mathlib::NormalF64AVX &).
		void static Test_Copy_Constructor();

		// Test mathlib::NormF64AVX::NormF64AVX(const __m128d, const __m128d).
		void static Test_XMM_Arg_Constructor();

		// Wrapper for running test methods.
		void static Run_Constructor_Tests();
		
		// Test class member operators.

		// Test mathlib::NormF64AVX::operator=(const NormF64AVX &).
		static void Test_operator_assign();

		// Test mathlib::NormF64AVX::operator+=(const NormF64AVX &).
		static void Test_operator_add_assign();

		// Test mathlib::NormF64AVX::operator-=(const NormF64AVX &).
		static void Test_operator_sub_assign();
		// Test special member functions.

		void static Test_apply();

		void static Test_apply_to_Vec1D();

		void static Test_apply2();

		void static Run_Member_Functions_Test();

		
		// void(*)() function pointer.
		typedef void(*fptr)();
		using FPTR = fptr;

	private:

		// private creation "factory" methods.

		
		/*
		*@params: void
		*@return: mathlib::NormF64AVX()
		* static "factory" method which returns unnamed NormF64AVX object.
		*
		*/
		static mathlib::NormF64AVX  NormF64AVX_Create();

		/*
		*@params: const double
		*@return: mathlib::NormF64AVX(const double)
		* static "factory" method which returns unnamed NormF64AVX object.
		*
		*/
		static mathlib::NormF64AVX  NormF64AVX_Create(const double);

		/*
		*@params: const double, const double, const double, const double
		*@return: mathlib::NormF64AVX(const double, const double, const double, const double).
		* static "factory" method which returns unnamed NormF64AVX object.
		*
		*/
		static mathlib::NormF64AVX  NormF64AVX_Create(const double, const double, const double, const double);

		/*
		*@params: const double[4]
		*@return: mathlib::NormF64AVX(const double [4]).
		* static "factory" method which returns unnamed NormF64AVX object.
		*
		*/
		static mathlib::NormF64AVX  NormF64AVX_Create(const double[4]);

		/*
		*@params: const __m256d
		*@return: mathlib::NormF64AVX(const __m256d).
		* static "factory" method which returns unnamed NormF64AVX object.
		*
		*/
		static mathlib::NormF64AVX  NormF64AVX_Create(const __m256d);

		/*
		*@params: const __m256i
		*@return: mathlib::NormF64AVX(const __m256i).
		* static "factory" method which returns unnamed NormF64AVX object.
		*
		*/
		static mathlib::NormF64AVX  NormF64AVX_Create(const __m256i);

		/*
		*@params: const __m128d, const __m128d
		*@return: mathlib::NormF64AVX(const __m128d, const __m128d).
		* static "factory" method which returns unnamed NormF64AVX object.
		*
		*/
		static mathlib::NormF64AVX  NormF64AVX_Create(const __m128d, const __m128d);

		/*
		*@params: const mathlib::NormF64AVX &
		*@return: mathlib::NormF64AVX(const mathlib::NormF64AVX &).
		* static "factory" method which returns unnamed NormF64AVX object.
		*
		*/
		static mathlib::NormF64AVX  NormF64AVX_Create(const mathlib::NormF64AVX &);
	};
}
#endif /*_NORMALF64AVX_TEST*/