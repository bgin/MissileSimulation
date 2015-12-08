
#ifndef _VECTORF64_AVX_TEST_H_
#define _VECTORF64_AVX_TEST_H_

#include <stdlib.h>
#include "Definitions.h"
#include "../MathLib/VectorF64AVX.h"
#include "Utils.h"
namespace test
{
	class VectorF64AVX_Test
	{
	public:

		// Constructors Tests
		// Single object creation.

		void static Test_Default_Constructor();

		void static Test_Static_Array_Arg_Constructor();

		void static Test_One_Arg_Constructor();

		void static Test_Four_Arg_Constructor();

		void static Test_YMM_Arg_Constructor();

		void static Test_YMMi_Arg_Constructor();

		void static Test_Copy_Constructor();

		void static Test_XMM_Arg_Constructor();

		void static Run_Constructor_Tests();

	    // Class member operator tests:
		// S at the end of function name means test against a operator overloaded by scalar argument.
		void static Test_Operator_Assignment();

		void static Test_Operator_Add_Assign();

		void static Test_Operator_Add_AssignS();

		void static Test_Operator_Sub_Assign();

		void static Test_Operator_Sub_AssignS();

		void static Test_Operator_Mul_Assign();

		void static Test_Operator_Mul_AssignS();

		void static Test_Operator_Div_Assign();

		void static Test_Operator_Div_AssignS();

		void static Test_Operator_Equal();

		void static Test_Operator_EqualS();

		void static Test_Operator_InEqual();

		void static Test_Operator_InEqualS();
		/*@param:   void
		* @returns: void
		* Tests whether VecF64AVX vector is equal component-wise to some scalar value.
		* VecF64AVX::operator==(const double) is exercised and tested.
		*/
		//void static Test_Operator_InEqualS();

		void static Run_Operator_Tests();
		
		// Class static operator tests

		/*@param: void
		 *@returns: void
		 * Tests static VecF64AVX::operator+(const __m256d, const __m256d).
		 * Assert_Equal function compares for the equality actual and expected vectors.
		 */
		void static Test_Static_Operator_Add();

		void static Test_Static_Operator_Add_S();

		void static Test_Static_Operator_Sub();

		void static Test_Static_Operator_Sub_S();

		void static Test_Static_Operator_Mul();

		void static Test_Static_Operator_Mul_S();

		void static Test_Static_Operator_Div();

		void static Test_Static_Operator_Div_S();

		void static Test_Static_Operator_Equal();

		void static Test_Static_Operator_EqualS();

		void static Test_Static_Operator_InEqual();

		void static Test_Static_Operator_InEqual_S();

		void static Run_Static_Operator_Tests();

		
		typedef void(*fptr)();
		using FPTR = fptr;
		//void static Run_Static_Operator_Tests(void(*)());

		void static Run_Static_Operator_Tests_V();

		//TO DO
		// Implement later more advanced tests based on std::vector<mathlib::VecF64AVX>.
	private:

		// Private VecF64AVX construction functions.
		static  mathlib::VecF64AVX  VecF64AVX_Create();

		static  mathlib::VecF64AVX  VecF64AVX_Create(const double);

		static  mathlib::VecF64AVX  VecF64AVX_Create(const double, const double, const double, const double);

		static  mathlib::VecF64AVX  VecF64AVX_Create(const double[4]);

		static  mathlib::VecF64AVX  VecF64AVX_Create(const __m256d);

		static  mathlib::VecF64AVX  VecF64AVX_Create(const __m256i);

		static  mathlib::VecF64AVX  VecF64AVX_Create(const __m128d, const __m128d);

		static  mathlib::VecF64AVX  VecF64AVX_Create(const mathlib::VecF64AVX &);
		
	};
}
#endif /*_VECTORF64_AVX_TEST_H_*/