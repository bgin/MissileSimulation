#ifndef _VECTOR_F64_AVX_H_
#define _VECTOR_F64_AVX_H_

#include "MathLibDefinitions.h"

namespace mathlib
{
	class VecF64AVX
	{

	public:

	  __forceinline	    VecF64AVX();

	  __forceinline     VecF64AVX( const double[4]);

	  __forceinline     VecF64AVX(const double, const double, const double, const double);

	  //__forceinline     VecF64AVX(const double(&)[4]);

	  __forceinline     VecF64AVX(const double);

	  __forceinline     VecF64AVX(const __m256d);

	  __forceinline     VecF64AVX(const __m256i);

	  __forceinline     VecF64AVX(const VecF64AVX&);

	  __forceinline     VecF64AVX(const __m128d, const __m128d);

	  // getters
	const  __m256d __forceinline get_m_VecF64() const;

	__m256d  __forceinline get_m_VecF64();


	__m128d  __forceinline get_low_part() const;

	__m128d   __forceinline get_hi_part()  const;

	// Load-Store Functions
	__forceinline    VecF64AVX &   load_a(const double *);

	__forceinline    VecF64AVX &   load_u(const double *);

	__forceinline    void          store_a(double *) const;

	__forceinline    void          store_u(double *) const;

	__forceinline    void          stream_store(double *) const;

	__forceinline    double        extract_scalar(unsigned int) const;

	__forceinline  friend std::ostream&  operator<<(std::ostream& , const VecF64AVX &);
	
	// Special member functions
	__forceinline   VecF64AVX &  dot(const VecF64AVX&, const VecF64AVX&);

	__forceinline  static  __m256d      dot(const __m256d, const __m256d);

	__forceinline  static  __m256d      abs_dot(const  __m256d, const __m256d);

	__forceinline  double euclidean_distance();

	__forceinline  double euclidean_distance2();

	__forceinline  double sqrt_euclidean_distance();

	__forceinline  VecF64AVX & cross(const VecF64AVX &, const VecF64AVX &);

	__forceinline  static  __m256d   cross(const __m256d, const __m256d);

	__forceinline  VecF64AVX &  direction_cosine();

	__forceinline  VecF64AVX & Normalize();

	__forceinline  static  double triple_scalar_prod(const __m256d, const __m256d, const __m256d);

	template<typename Function>  __forceinline VecF64AVX & apply(Function, const double);

	template<typename Function>  __forceinline VecF64AVX & apply(Function, const double, const double, const double, const double);

	template<typename F1, typename F2, typename F3> __forceinline VecF64AVX & apply(F1, F2, F3, const double, const double, const double);

	template<typename...  Functions> __forceinline VecF64AVX & apply(Functions...); // Variadic Templates.

	template<typename...  Functions> __forceinline static void apply(std::vector<mathlib::VecF64AVX> &, Functions...);
	
	
	// Member operators

	__forceinline   VecF64AVX & operator=(const VecF64AVX &);

	__forceinline  VecF64AVX & operator=(const __m256d & rhs);

	__forceinline  VecF64AVX & operator+=(const VecF64AVX &);

	__forceinline  VecF64AVX & operator-=(const VecF64AVX &);

	__forceinline  VecF64AVX & operator*=(const VecF64AVX &);

	__forceinline  VecF64AVX & operator/=(const VecF64AVX &);

	__forceinline  VecF64AVX & operator|=(const VecF64AVX &);

	__forceinline  VecF64AVX & operator&=(const VecF64AVX &);

	__forceinline  VecF64AVX & operator^=(const VecF64AVX &);

	__forceinline  VecF64AVX    operator==(const VecF64AVX &);

	__forceinline  VecF64AVX    operator!=(const VecF64AVX &);

	__forceinline  VecF64AVX & operator+=(const double);

	__forceinline  VecF64AVX & operator-=(const double);

	__forceinline  VecF64AVX & operator*=(const double);

	__forceinline  VecF64AVX & operator/=(const double);

	__forceinline  VecF64AVX  operator==(const double);

	__forceinline  VecF64AVX  operator!=(const double);

	__forceinline  double      operator[](unsigned int) const;

	 operator struct __m256d () const;

	 static __forceinline  __m256d   operator+(const __m256d, const __m256d);

	 static __forceinline  __m256d   operator-(const __m256d, const __m256d);

	 static __forceinline  __m256d   operator*(const __m256d, const __m256d);

	 static __forceinline  __m256d   operator/(const __m256d, const __m256d);

	 static __forceinline __m256d    operator==(const __m256d, const __m256d);

	 static __forceinline __m256d    operator!=(const __m256d, const __m256d);

	 static __forceinline __m256d    operator+(const __m256d, const double);

	 static __forceinline __m256d    operator-(const __m256d, const double);

	 static __forceinline __m256d    operator*(const __m256d, const double);

	 static __forceinline __m256d    operator/(const __m256d, const double);

	 static __forceinline __m256d    operator==(const __m256d, const double);

	 static __forceinline __m256d    operator!=(const __m256d, const double);

	 static __forceinline __m256d    operator+(const double, const __m256d);

	 static __forceinline __m256d    operator-(const double, const __m256d);

	 static __forceinline __m256d    operator*(const double, const __m256d);

	 static __forceinline __m256d    operator/(const double, const __m256d);

	 static __forceinline __m256d    operator==(const double, const __m256d);

	 static __forceinline __m256d    operator!=(const double, const __m256d);
	 
	
	protected:

		__m256d m_VecF64;
	};

	// Special selection specific vector function.
	static __forceinline  __m256d Select_Vector(const __m256d, const __m256d, const __m256d);

	static __forceinline  __m256  Select_Vector(const __m256, const __m256, const __m256);

	static __forceinline  __m256d Coalesce_Vector( __m256d, const __m128d, const int);

	static __forceinline  __m256  Coalesce_Vector( __m256, const __m128, const int);

	static __forceinline  void    Coalesce_Vector(__m256d, const __m128d, const __m128d);

	static __forceinline  __m128d  Extract_Vector(__m256d, const int);

	static __forceinline  __m128   Extract_Vector(__m256, const int);

	static __forceinline  __m256d  Normalize(const __m256d);
	// Non member operators

	static __forceinline  VecF64AVX operator+(VecF64AVX &lhs, const VecF64AVX &rhs);

	static __forceinline  VecF64AVX operator-( VecF64AVX &lhs, const VecF64AVX &rhs);

	static __forceinline  VecF64AVX operator*(VecF64AVX &lhs, const VecF64AVX &rhs);

	static __forceinline  VecF64AVX operator/(const VecF64AVX &, const VecF64AVX &);

	static __forceinline  VecF64AVX operator==(const VecF64AVX &, const VecF64AVX &);
	
	static __forceinline  VecF64AVX operator!=(const VecF64AVX &, const VecF64AVX &);

	static __forceinline  VecF64AVX operator+(const double, const VecF64AVX &);

	static __forceinline  VecF64AVX operator-(const double, const VecF64AVX &);

	static __forceinline  VecF64AVX operator*(const double, const VecF64AVX &);

	static __forceinline  VecF64AVX operator/(const double, const VecF64AVX &);

	static __forceinline  VecF64AVX operator==(const double, const VecF64AVX &);

	static __forceinline  VecF64AVX operator!=(const double, const VecF64AVX &);

	static __forceinline  VecF64AVX operator+(const VecF64AVX &, const double);

#include "VectorF64AVX.inl"
}
#endif /*_VECTOR_F64_AVX_H_*/