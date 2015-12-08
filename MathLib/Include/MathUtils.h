#ifndef _MATH_UTILS_H_
#define _MATH_UTILS_H_
#include "MathLibDefinitions.h"

namespace mathlib
{
	template<typename _Ty>  class Array1D
	{

	public:

	 __forceinline	Array1D();

	 __forceinline	Array1D(const int);

	 __forceinline  Array1D(const int, const _Ty);

	

	__forceinline	Array1D(const _Ty *, const int);

	__forceinline	Array1D( Array1D const&);

	__forceinline	Array1D(Array1D &&);


	__forceinline	~Array1D();

	__forceinline	_Ty * get_m_data();

	__forceinline	const _Ty * get_m_data() const;

	__forceinline   const int   get_size() const;


	template<typename Function> __forceinline void apply(Function,const _Ty);

	template<typename... Function> __forceinline void apply(Function...);

	// Works with arrays only. Returns pointer to an array.
	template<typename Function> __forceinline static void apply(Array1D &, Function);
#if defined _DEBUG
	__forceinline static void debug_print(const Array1D &);
#endif
	private:

		_Ty * m_data;
		 int size;
		
	};

	template<typename _Ty> class AllocateVec1D
	{
        
	public:

		__forceinline static	_Ty *   allocate1D(const int);

		__forceinline static    void    deallocate1D(_Ty *);
	};


	template<typename _Ty> class AllocateVec2D
	{
	public:

		// slow version.
		__forceinline static  _Ty   **  allocate2D(const int, const int);

		__forceinline static  _Ty   **  allocate2D_fast(const int, const int);

		__forceinline static   void     deallocate2D(_Ty **);
	};

	template<typename _Ty> class AllocateVec3D
	{
	public:

		// slow version
		__forceinline static  _Ty ***  allocate3D(const int, const int, const int);

		__forceinline static  _Ty ***  allocate3D_fast(const int, const int, const int);

		__forceinline static   void    deallocate3D(_Ty ***);
	};

	/*
	@brief Displays hex encoding of floating-point number
	*/

	union FPNumber
	{
		double d;
	    unsigned	char  c[8];
	};

	__forceinline  static  void   DisplayFPNumber( union FPNumber const&);

#include "MathUtils.inl"
}
#endif /*_MATH_UTILS_H_*/