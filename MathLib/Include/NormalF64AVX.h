
#ifndef _NORMAL_F64_AVX_H_
#define _NORMAL_F64_AVX_H_

#include "VectorF64AVX.h"

namespace mathlib
{
	
	class NormF64AVX : public VecF64AVX
	{

	public:

		// Constructors
	  __forceinline	NormF64AVX();

	  __forceinline	NormF64AVX(const double);

	  __forceinline	NormF64AVX(const double[4]);

	  __forceinline NormF64AVX(const double, const double, const double, const double);

	  __forceinline NormF64AVX(const __m256d);

	  __forceinline NormF64AVX(const __m256i);

	  __forceinline NormF64AVX(const __m128d, const __m128d);

	  __forceinline NormF64AVX(const NormF64AVX &);


	  // member operators.
	  __forceinline  NormF64AVX & operator=(const NormF64AVX &);

	  __forceinline  NormF64AVX & operator+=(const NormF64AVX &);

	  __forceinline  NormF64AVX & operator-=(const NormF64AVX &);
		
	  __forceinline  NormF64AVX & operator*=(const NormF64AVX &);

	  __forceinline  NormF64AVX & operator/=(const NormF64AVX &);

	  __forceinline  NormF64AVX   operator==(const NormF64AVX &);

	  __forceinline  NormF64AVX   operator!=(const NormF64AVX &);

	  __forceinline  NormF64AVX & operator+=(const double);

	  __forceinline  NormF64AVX & operator-=(const double);

	  __forceinline  NormF64AVX & operator*=(const double);

	  __forceinline  NormF64AVX & operator/=(const double);

	  __forceinline  NormF64AVX   operator==(const double);

	  __forceinline  NormF64AVX   operator!=(const double);

	  __forceinline static __m256d operator+(const __m256d, const __m256d);

	  __forceinline static __m256d operator-(const __m256d, const __m256d);

	  __forceinline static __m256d operator*(const __m256d, const __m256d);

	  __forceinline static __m256d operator/(const __m256d, const __m256d);

	  __forceinline static __m256d operator==(const __m256d, const __m256d);

	  __forceinline static __m256d operator!=(const __m256d, const __m256d);

	  __forceinline static __m256d operator+(const  __m256d, const double);

	  __forceinline static __m256d operator-(const  __m256d, const double);

	  __forceinline static __m256d operator*(const  __m256d, const double);

	  __forceinline static __m256d operator/(const  __m256d, const double);

	  __forceinline static __m256d operator==(const __m256d, const double);

	  __forceinline static __m256d operator!=(const __m256d, const double);

	  __forceinline static __m256d operator+(const  double, const  __m256d);

	  __forceinline static __m256d operator-(const  double, const  __m256d);

	  __forceinline static __m256d operator*(const  double, const  __m256d);

	  __forceinline static __m256d operator/(const  double, const  __m256d);

	  __forceinline static __m256d operator==(const double, const  __m256d);

	  __forceinline static __m256d operator!=(const double, const  __m256d);

	 

	  // Special member functions.
	  __forceinline NormF64AVX & dot(const NormF64AVX &, const NormF64AVX &);

	  __forceinline NormF64AVX & abs_dot(const NormF64AVX &, const NormF64AVX &);

	  __forceinline static __m256d abs_dot(const __m256d, const __m256d);

	  __forceinline static double  triple_scalar_prod(const __m256d, const __m256d, const __m256d);

	  __forceinline static __m256d cross(const __m256d, const __m256d);

	  __forceinline double euclidean_distance();

	  __forceinline double sqrt_euclidean_distance();

	  __forceinline NormF64AVX & Normalize();

	  template<typename... Function> __forceinline NormF64AVX & apply(Function ...);

	  template<typename... Function> __forceinline static void apply2(std::vector<mathlib::NormF64AVX> &, Function ...);
	};

	// Non-member operators.

	

	__forceinline   static NormF64AVX  operator+(const NormF64AVX &, const NormF64AVX &);

	__forceinline   static NormF64AVX  operator-(const NormF64AVX &, const NormF64AVX &);

	__forceinline   static NormF64AVX  operator*(const NormF64AVX &, const NormF64AVX &);

	__forceinline   static NormF64AVX operator/(const  NormF64AVX &, const NormF64AVX &);

	__forceinline   static NormF64AVX operator==(const NormF64AVX &, const NormF64AVX &);

	__forceinline   static NormF64AVX operator!=(const NormF64AVX &, const NormF64AVX &);

	__forceinline   static NormF64AVX operator+(const  NormF64AVX &, const double);

	__forceinline   static NormF64AVX operator-(const  NormF64AVX &, const double);

	__forceinline   static NormF64AVX operator*(const  NormF64AVX &, const double);

	__forceinline   static NormF64AVX operator/(const  NormF64AVX &, const double);

	__forceinline   static NormF64AVX operator==(const NormF64AVX &, const double);

	__forceinline   static NormF64AVX operator!=(const NormF64AVX &, const double);

	__forceinline   static NormF64AVX operator+(const double, const NormF64AVX &);

	__forceinline   static NormF64AVX operator-(const double, const NormF64AVX &);

	__forceinline   static NormF64AVX operator*(const double, const NormF64AVX &);

	__forceinline   static NormF64AVX operator/(const double, const NormF64AVX &);

	__forceinline   static NormF64AVX operator==(const double, const NormF64AVX &);

	__forceinline   static NormF64AVX operator!=(const double, const NormF64AVX &);

#include "NormalF64AVX.inl"
}
#endif /*_NORMAL_F64_AVX_H_*/