
#ifndef _NORMAL_H_
#define _NORMAL_H_

#include "Vector.h"
namespace mathlib
{
	template<typename _Ty> class NormalS : public VectorS<_Ty>
	{

	public:

	__forceinline 	NormalS();

	__forceinline   NormalS(const _Ty);

	__forceinline   NormalS(const _Ty, const _Ty, const _Ty);

	__forceinline   NormalS(const _Ty[3]);

	__forceinline   NormalS(const NormalS &);

	__forceinline  explicit NormalS(const VectorS &);

	// Member operators.

	__forceinline   NormalS & operator=(const NormalS &);

	__forceinline   NormalS & operator+=(const NormalS &);

	__forceinline   NormalS & operator+=(const _Ty);

	__forceinline   NormalS   operator+(const NormalS &);

	__forceinline   NormalS   operator+(const VectorS &);

	__forceinline   NormalS & operator-=(const NormalS &);

	__forceinline   NormalS & operator-=(const _Ty);

	__forceinline   NormalS   operator-(const NormalS &);

	__forceinline   NormalS   operator-(const VectorS &);

	__forceinline   NormalS & operator*=(const NormalS &);

	__forceinline   NormalS & operator*=(const _Ty);

	__forceinline   NormalS   operator*(const NormalS &);

	__forceinline   NormalS   operator*(const VectorS &);

	__forceinline   NormalS & operator/=(const NormalS &);

	__forceinline   NormalS & operator/=(const _Ty);

	__forceinline   NormalS   operator/(const NormalS &);

	__forceinline   NormalS   operator/(const VectorS &);

	__forceinline   NormalS   operator-() const;

	__forceinline   bool      operator==(const NormalS &);

	__forceinline   bool      operator!=(const NormalS &);

	__forceinline   bool      operator==(const _Ty);

	__forceinline   bool      operator!=(const _Ty);

	__forceinline   bool      operator==(const VectorS &);

	__forceinline   bool      operator!=(const VectorS &);

	__forceinline   operator VectorS () const;
	// Special member functions.

	__forceinline   _Ty         euclidean_distance();

	static  __forceinline  _Ty  euclidean_distance(const NormalS &);

	static  __forceinline  _Ty  euclidean_distance(const _Ty, const _Ty, const _Ty);

	__forceinline   _Ty         sqrt_euclidean_distance();

	static __forceinline   _Ty  sqrt_euclidean_distance(const NormalS &);

	static __forceinline   _Ty  sqrt_euclidean_distance(const _Ty, const _Ty, const _Ty);

	__forceinline   _Ty         dot(const NormalS &);

	static __forceinline   _Ty  dot(const NormalS &, const NormalS &);

	static __forceinline   _Ty  dot(const NormalS &, const VectorS &);

	static __forceinline   _Ty  dot(const _Ty, const _Ty, const _Ty, const _Ty, const _Ty, const _Ty);

	__forceinline      NormalS & cross(const NormalS &);

	static __forceinline NormalS cross(const NormalS &, const NormalS &);

	static __forceinline NormalS cross(const NormalS &, const VectorS &);

	__forceinline          _Ty   triple_scalar_product(const NormalS &, const NormalS &);

	static __forceinline   _Ty   triple_scalar_product(const NormalS &, const NormalS &, const NormalS &);

	__forceinline       NormalS & normalize();

	static __forceinline NormalS  normalize(const NormalS &);

	};

		//Non-member static operators
		template<typename _Ty> __forceinline  NormalS<_Ty>  operator+(const NormalS<_Ty> &, const NormalS<_Ty> &);

		template<typename _Ty> __forceinline  NormalS<_Ty>  operator+(const NormalS<_Ty> &, const VectorS<_Ty> &);

		template<typename _Ty> __forceinline  NormalS<_Ty>  operator+(const NormalS<_Ty> &, const _Ty);

		template<typename _Ty> __forceinline  NormalS<_Ty>  operator+(const _Ty, const NormalS<_Ty> &);

		template<typename _Ty> __forceinline  NormalS<_Ty>  operator-(const NormalS<_Ty> &, const NormalS<_Ty> &);

		template<typename _Ty> __forceinline  NormalS<_Ty>  operator-(const NormalS<_Ty> &, const VectorS<_Ty> &);

		template<typename _Ty> __forceinline  NormalS<_Ty>  operator-(const NormalS<_Ty> &, const _Ty);

		template<typename _Ty> __forceinline  NormalS<_Ty>  operator-(const _Ty, const NormalS<_Ty> &);

		template<typename _Ty> __forceinline  NormalS<_Ty>  operator*(const NormalS<_Ty> &, const NormalS<_Ty> &);

		template<typename _Ty> __forceinline  NormalS<_Ty>  operator*(const NormalS<_Ty> &, const VectorS<_Ty> &);

		template<typename _Ty> __forceinline  NormalS<_Ty>  operator*(const NormalS<_Ty> &, const _Ty);

		template<typename _Ty> __forceinline  NormalS<_Ty>  operator*(const _Ty, const NormalS<_Ty> &);

		template<typename _Ty> __forceinline  NormalS<_Ty>  operator/(const NormalS<_Ty> &, const NormalS<_Ty> &);

		template<typename _Ty> __forceinline  NormalS<_Ty>  operator/(const NormalS<_Ty> &, const VectorS<_Ty> &);

		template<typename _Ty> __forceinline  NormalS<_Ty>  operator/(const NormalS<_Ty> &, const _Ty);

		template<typename _Ty> __forceinline  NormalS<_Ty>  operator/(const _Ty, const NormalS<_Ty> &);

		template<typename _Ty> __forceinline  bool          operator==(const NormalS<_Ty> &, const NormalS<_Ty> &);

		template<typename _Ty> __forceinline  bool          operator==(const NormalS<_Ty> &, const VectorS<_Ty> &);

		template<typename _Ty> __forceinline  bool          operator==(const NormalS<_Ty> &, const _Ty);

		template<typename _Ty> __forceinline  bool          operator==(const _Ty, const NormalS<_Ty> &);

		template<typename _Ty> __forceinline  bool          operator!=(const NormalS<_Ty> &, const NormalS<_Ty> &);

		template<typename _Ty> __forceinline  bool          operator!=(const NormalS<_Ty> &, const VectorS<_Ty> &);

		template<typename _Ty> __forceinline  bool          operator!=(const NormalS<_Ty> &, const _Ty);

		template<typename _Ty> __forceinline  bool          operator!=(const _Ty, const NormalS<_Ty> &);

#include "Normal.inl"
}
#endif  /*_NORMAL_H_*/