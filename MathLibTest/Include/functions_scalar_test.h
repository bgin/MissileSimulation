#ifndef _FUNCTIONS_SCALAR_TEST_H_
#define _FUNCTIONS_SCALAR_TEST_H_

#include "../MathLib/functions_scalar.h"
#include <random>
namespace test
{
	class FunctionsScalarTest
	{
	public:

		static void Test_fastsin();

		static void Test_fastcot();

		static void Test_fastcos();

		static void Run_Tests();
	private:

		template<typename _T> static _T random_value(const _T&, const _T&);
	};
}
#endif /*_FUNCTIONS_SCALAR_TEST_H_*/