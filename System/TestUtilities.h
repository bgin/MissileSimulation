#ifndef _TEST_UTILS_H_10_04_16
#define _TEST_UTILS_H_10_04_16

namespace  test_internal_system {

	namespace  utilities {


		/***********************************************
		               Prints data array
		************************************************/
		auto  printData(_In_ const float*, _In_ const int)->void;

		/***********************************************
		      Overloaded templated on type Container 
			  version of printData
		************************************************/
		template<class Container>  void  printData(_In_ const Container&);



#include "TestUtilities.inl"

	}

}



#endif /*_TEST_UTILS_H_10_04_16*/