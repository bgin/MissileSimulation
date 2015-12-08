#ifndef _TANGENT_H_
#define _TANGENT_H_

#include "VectorF64AVX.h"
namespace mathlib
{
	class TangentF64AVX : public VecF64AVX
	{
	public :

		 // Constructors
		__forceinline   TangentF64AVX();

		__forceinline   TangentF64AVX(const double);

		__forceinline   TangentF64AVX(const double[4]);

		__forceinline   TangentF64AVX(const double, const double, const double, const double);

		__forceinline   TangentF64AVX(const __m256d);

		__forceinline   TangentF64AVX(const __m256i);

		__forceinline   TangentF64AVX(const __m128d, const __m128d);

		__forceinline   TangentF64AVX(const TangentF64AVX &);

		// Member operators

		__forceinline   TangentF64AVX & operator=(const TangentF64AVX &);

		__forceinline   TangentF64AVX & operator+=(const TangentF64AVX &);

		__forceinline   TangentF64AVX & operator-=(const TangentF64AVX &);

		__forceinline   TangentF64AVX & operator*=(const TangentF64AVX &);

		__forceinline   TangentF64AVX & operator/=(const TangentF64AVX &);

		__forceinline   TangentF64AVX & operator==(const TangentF64AVX &);

		__forceinline   TangentF64AVX & operator!=(const TangentF64AVX &);

		__forceinline   TangentF64AVX & operator+=(const double);

		__forceinline   TangentF64AVX & operator-=(const double);

		__forceinline   TangentF64AVX & operator*=(const double);

		__forceinline   TangentF64AVX & operator/=(const double);

		__forceinline   TangentF64AVX & operator==(const double);

		__forceinline   TangentF64AVX & operator!=(const double);

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

		__forceinline static __m256d operator+(const double, const  __m256d);

		__forceinline static __m256d operator*(const double, const  __m256d);

		__forceinline static __m256d operator-(const double, const  __m256d);

		__forceinline static __m256d operator/(const double, const  __m256d);

		__forceinline static __m256d operator==(const double, const __m256d);

		__forceinline static __m256d operator!=(const double, const __m256d);

		// Special member functions.

		__forceinline   TangentF64AVX & dot(const TangentF64AVX &, const TangentF64AVX &);

		__forceinline  static  __m256d         dot(const __m256d, const __m256d);

		__forceinline  TangentF64AVX  & abs_dot(const TangentF64AVX &, const TangentF64AVX &);

		__forceinline  static  __m256d  abs_dot(const __m256d, const __m256d);

		__forceinline  static  __m256d         cross(const __m256d, const __m256d);

		__forceinline  static  double   triple_scalar_prod(const __m256d, const __m256d, const __m256d);

		__forceinline  TangentF64AVX  & direction_cosine();

		__forceinline  TangentF64AVX   & Normalize();

		__forceinline   double          euclidean_distance();

		__forceinline   double          sqrt_euclidean_distance();
	};

	// Non-member operators.
	__forceinline    static TangentF64AVX  operator+(const TangentF64AVX &, const TangentF64AVX &);

	__forceinline    static TangentF64AVX  operator-(const TangentF64AVX &, const TangentF64AVX &);

	__forceinline    static TangentF64AVX  operator*(const TangentF64AVX &, const TangentF64AVX &);

	__forceinline    static TangentF64AVX  operator/(const TangentF64AVX &, const TangentF64AVX &);

	__forceinline    static TangentF64AVX  operator==(const TangentF64AVX &, const TangentF64AVX &);

	__forceinline    static TangentF64AVX  operator!=(const TangentF64AVX &, const TangentF64AVX &);

	__forceinline    static TangentF64AVX  operator+(const  double, const TangentF64AVX &);

	__forceinline    static TangentF64AVX  operator-(const double,  const TangentF64AVX &);

	__forceinline    static TangentF64AVX  operator*(const double,  const TangentF64AVX &);

	__forceinline    static TangentF64AVX  operator/(const double, const TangentF64AVX &);

	__forceinline    static TangentF64AVX  operator==(const double, const TangentF64AVX &);

	__forceinline    static TangentF64AVX  operator!=(const double, const TangentF64AVX &);

	__forceinline    static TangentF64AVX  operator+(const TangentF64AVX &, const double);

	__forceinline    static TangentF64AVX  operator-(const TangentF64AVX &, const double);

	__forceinline    static TangentF64AVX  operator*(const TangentF64AVX &, const double);

	__forceinline    static TangentF64AVX  operator/(const TangentF64AVX &, const double);

	__forceinline    static TangentF64AVX  operator==(const TangentF64AVX &, const double);

	__forceinline    static TangentF64AVX  operator!=(const TangentF64AVX &, const double);

#include "Tangent.inl"
}
#endif /*_TANGENT_H_*/