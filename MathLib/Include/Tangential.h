
#ifndef _TANGENTIAL_H_ 
#define _TANGENTIAL_H_

#include "Vector.h"

namespace mathlib
{
	template<typename _Ty> class TangentS : public VectorS<_Ty>
	{
         

	public:

	  __forceinline 	TangentS();

	  __forceinline     TangentS(const _Ty);

	  __forceinline     TangentS(const _Ty, const _Ty, const _Ty);

	  __forceinline     TangentS(const _Ty [3]);

	  __forceinline     TangentS(const TangentS &);

	  __forceinline   explicit  TangentS(const VectorS &);

	  // Member operators:

	  __forceinline    TangentS &  operator=(const TangentS const&);

	  __forceinline    TangentS &  operator+=(const TangentS const&);

	  __forceinline    TangentS &  operator+=(const VectorS const&);

	  __forceinline    TangentS &  operator+=(const _Ty);

	  __forceinline    TangentS    operator+(const TangentS const&);
     
	  __forceinline    TangentS    operator+(const VectorS const&);

	  __forceinline    TangentS    operator+(const _Ty);

	  __forceinline    TangentS &  operator-=(const TangentS const&);

	  __forceinline    TangentS &  operator-=(const VectorS const&);

	  __forceinline    TangentS &  operator-=(const _Ty);

	  __forceinline    TangentS    operator-(const TangentS const&);

	  __forceinline    TangentS    operator-(const VectorS const&);

	  __forceinline    TangentS    operator-(const _Ty);

	  __forceinline    TangentS  &  operator*=(const TangentS const&);

	  __forceinline    TangentS  &  operator*=(const VectorS const&);

	  __forceinline    TangentS  & operator*=(const _Ty);

	  __forceinline    TangentS    operator*(const TangentS const&);

	  __forceinline    TangentS    operator*(const VectorS const&);

	  __forceinline    TangentS    operator*(const _Ty);

	  __forceinline    TangentS  &  operator/=(const TangentS const&);

	  __forceinline    TangentS  &  operator/=(const VectorS const&);

	  __forceinline    TangentS  &  operator/=(const _Ty);

	  __forceinline    TangentS     operator/(const TangentS const&);

	  __forceinline    TangentS     operator/(const VectorS const&);

	  __forceinline    TangentS     operator/(const _Ty);

	  __forceinline    TangentS     operator-() const;

	  __forceinline    TangentS  &   operator++();

	  __forceinline    TangentS  &   operator--();

	  __forceinline    bool          operator==(const TangentS const&);

	  __forceinline    bool          operator==(const VectorS  const&);

	  __forceinline    bool          operator==(const _Ty);

	  __forceinline    bool          operator!=(const TangentS const&);

	  __forceinline    bool          operator!=(const VectorS const&);

	  __forceinline    bool          operator!=(const _Ty);
		  
	  // Special member functions:

	  __forceinline  _Ty  euclidean_distance();

	  static __forceinline  _Ty  euclidean_distance(const TangentS &);

	  static __forceinline  _Ty  euclidean_distance(const _Ty, const _Ty, const _Ty);

	  __forceinline  _Ty  sqrt_euclidean_distance();

	  static __forceinline  _Ty   sqrt_euclidean_distance(const TangentS &);

	  static __forceinline  _Ty   sqrt_euclidean_distance(const _Ty, const _Ty, const _Ty);

	  __forceinline  _Ty   dot(const TangentS &);

	  static __forceinline  _Ty   dot(const TangentS &, const TangentS &);

	  static __forceinline  _Ty   dot(const TangentS &, const VectorS &);

	  __forceinline         TangentS &  cross(const TangentS &);

	  static __forceinline  TangentS    cross(const TangentS &, const TangentS &);

	  static __forceinline  TangentS    cross(const TangentS &, const VectorS &);

	  __forceinline          _Ty   triple_scalar_product(const TangentS &, const TangentS &);

	  static __forceinline   _Ty   triple_scalar_product(const TangentS &, const TangentS &, const TangentS &);

	  __forceinline         TangentS &  normalize();

	  static __forceinline  TangentS  normalize(const TangentS &);
		 
	};

		// Non-member operators:

		template<typename _Ty> __forceinline  TangentS<_Ty>    operator+(const TangentS<_Ty> const&, const TangentS<_Ty> const&);

		template<typename _Ty> __forceinline  TangentS<_Ty>    operator+(const TangentS<_Ty> const&, const VectorS<_Ty> const&);

		template<typename _Ty> __forceinline  TangentS<_Ty>    operator+(const TangentS<_Ty> const&, const _Ty);

		template<typename _Ty> __forceinline  TangentS<_Ty>    operator+(const _Ty, const TangentS<_Ty> const &);

		template<typename _Ty> __forceinline  TangentS<_Ty>    operator-(const TangentS<_Ty> const&, const TangentS<_Ty> const&);

		template<typename _Ty> __forceinline  TangentS<_Ty>    operator-(const TangentS<_Ty> const&, const VectorS<_Ty> const&);

		template<typename _Ty> __forceinline  TangentS<_Ty>    operator-(const TangentS<_Ty> const&, const _Ty);

		template<typename _Ty> __forceinline  TangentS<_Ty>    operator-(const _Ty, const TangentS<_Ty> const&);

		template<typename _Ty> __forceinline  TangentS<_Ty>    operator*(const TangentS<_Ty> const&, const TangentS<_Ty> const&);

		template<typename _Ty> __forceinline  TangentS<_Ty>    operator*(const TangentS<_Ty> const&, const VectorS<_Ty> const&);

		template<typename _Ty> __forceinline  TangentS<_Ty>    operator*(const TangentS<_Ty> const&, const _Ty);



#include "Tangential.inl"
}
#endif /*_TANGENTIAL_H_*/