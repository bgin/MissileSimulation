#ifndef _FUNCTIONS_SCALAR_H_
#define _FUNCTIONS_SCALAR_H_

#include <type_traits>

#include "MathLibDefinitions.h"
#include "MathConstants.h"

namespace mathlib
{
	template<typename _Ty> class FastScalarFunctions
	{


	public:

		__forceinline static std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type fastcot(const _Ty&);

		__forceinline static std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type fastsin(const _Ty&);

		__forceinline static std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type fastcos(const _Ty&);

		__forceinline static std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type fasttan(const _Ty&);

		__forceinline static std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type fastexp(const _Ty&);

		__forceinline static std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type fastcsc(const _Ty&);

		__forceinline static std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type fastsec(const _Ty&);

		__forceinline static std::enable_if<std::is_floating_point<_Ty>::value, _Ty>::type fastarcsin(const _Ty&);

		  
	};


#include "functions_scalar.inl"

}

#endif /*_FUNCTIONS_SCALAR_H_*/