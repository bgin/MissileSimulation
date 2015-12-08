#ifndef _DERIVATIVE_AVX_H_
#define _DERIVATIVE_AVX_H_
#include "MathLibDefinitions.h"

namespace mathlib
{

	 class DyDxAVX
	{

	public:

		template<typename Functions> __forceinline static DyDxAVX differentiate(Functions, __m256d, __m256d );

	__forceinline	const __m256d  get_derivative() const;

	__forceinline	__m256d        get_derivative();

	__forceinline	const __m256d  get_error() const;

	__forceinline	__m256d        get_error();

	private:

		__m256d derivative;
		__m256d error;

		__forceinline  DyDxAVX(const __m256d, const __m256d);

	};

#include "DerivativeAVX.inl"
}
#endif /*_DERIVATIVE_AVX_H_*/