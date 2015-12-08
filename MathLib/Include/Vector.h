
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "MathLibDefinitions.h"
namespace mathlib
{
	
	template<typename _Ty> class VectorS
	{

	public:

		// Class Constructors
	__forceinline	VectorS();

	__forceinline	VectorS(const _Ty);

	__forceinline	VectorS(const _Ty, const _Ty, const _Ty);

	__forceinline	VectorS(const _Ty[3]);

	__forceinline	VectorS(const VectorS &);

	// Getters.
	__forceinline  _Ty & X();

	__forceinline const _Ty & X() const;

	__forceinline  _Ty & Y();

	__forceinline const _Ty & Y() const;

	__forceinline  _Ty & Z();

	__forceinline const _Ty & Z() const;

	
	// Member operators.

	__forceinline   VectorS & operator=(const VectorS &);

	__forceinline   VectorS & operator+=(const VectorS &);

	__forceinline   VectorS & operator+=(const _Ty);

	__forceinline   VectorS   operator+(const VectorS &);

	
	__forceinline   VectorS & operator-=(const VectorS &);

	__forceinline   VectorS & operator-=(const _Ty);

	__forceinline   VectorS   operator-(const  VectorS &);

	__forceinline   VectorS   operator-() const;

	__forceinline   VectorS & operator*=(const VectorS &);

	__forceinline   VectorS & operator*=(const _Ty);

	__forceinline   VectorS   operator*(const  VectorS &);

	__forceinline   VectorS & operator/=(const VectorS &);

	__forceinline   VectorS & operator/=(const _Ty);

	__forceinline   VectorS   operator/(const  VectorS &);

	__forceinline   bool      operator==(const VectorS &);

	__forceinline   bool      operator==(const _Ty);

	__forceinline   bool      operator!=(const _Ty);

	__forceinline   bool      operator!=(const VectorS &);

	__forceinline   _Ty &     operator[](const int);

	__forceinline  const _Ty & operator[](const int) const;

	__forceinline  VectorS  &  operator++();

	__forceinline  VectorS  &  operator--();
	
	// Special member functions.

	__forceinline  _Ty  euclidean_distance();

	__forceinline  _Ty  sqrt_euclidean_distance();

	static __forceinline  _Ty  sqrt_euclidean_distance(const VectorS &);

	static __forceinline  _Ty  sqrt_euclidean_distance(const _Ty, const _Ty, const _Ty);

	static __forceinline  _Ty  euclidean_distance(const VectorS &);

	static __forceinline  _Ty  euclidean_distance(const _Ty, const _Ty, const _Ty);

	__forceinline  _Ty  dot(const VectorS &) const;

	static  __forceinline  _Ty dot(const VectorS &, const VectorS &);

	static  __forceinline  _Ty dot(const _Ty, const _Ty, const _Ty, const _Ty, const _Ty, const _Ty);

	__forceinline  VectorS &  cross(const VectorS &);

	static  __forceinline VectorS  cross(const VectorS &, const VectorS &);

	__forceinline  _Ty  triple_scalar_product(const VectorS &, const VectorS &);

	static  __forceinline  _Ty triple_scalar_product(const VectorS &, const VectorS &, const VectorS &);

	__forceinline  VectorS & normalize();

	static  __forceinline  VectorS normalize(const VectorS &);

	static  __forceinline  bool  has_nan(const _Ty, const _Ty, const _Ty);

	static  __forceinline  bool  has_nan(const _Ty);

	static  __forceinline  bool  is_zero(const _Ty, const _Ty, const _Ty);

	static  __forceinline  bool  is_zero(const _Ty);
	protected:

		_Ty x, y, z;
	};

	// Non-member operators

	template<typename _Ty> __forceinline  VectorS<_Ty>  operator+(const VectorS<_Ty> &, const VectorS<_Ty> &);
	
	template<typename _Ty> __forceinline  VectorS<_Ty>  operator-(const VectorS<_Ty> &, const VectorS<_Ty> &);

	template<typename _Ty> __forceinline  VectorS<_Ty>  operator*(const VectorS<_Ty> &, const VectorS<_Ty> &);

	template<typename _Ty> __forceinline  VectorS<_Ty>  operator/(const VectorS<_Ty> &, const VectorS<_Ty> &);

	template<typename _Ty> __forceinline  bool          operator==(const VectorS<_Ty> &, const VectorS<_Ty> &);

	template<typename _Ty> __forceinline  bool          operator!=(const VectorS<_Ty> &, const VectorS<_Ty> &);

	template<typename _Ty> __forceinline  VectorS<_Ty>  operator+(const VectorS<_Ty> &, const _Ty);

	template<typename _Ty> __forceinline  VectorS<_Ty>  operator-(const VectorS<_Ty> &, const _Ty);

	template<typename _Ty> __forceinline  VectorS<_Ty>  operator*(const VectorS<_Ty> &, const _Ty);


#include "Vector.inl"
}
#endif /*_VECTOR_*/