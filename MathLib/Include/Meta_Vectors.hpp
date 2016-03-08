#ifndef _META_VECTORS_HPP_
#define _META_VECTORS_HPP_



#include "MathLibDefinitions.h"

namespace   mathlib{

	namespace  meta_prog {



		/*

		               Meta Vectors for small-sized vectors.

		*/

		/*
		@brief    c = a + b
		*/
		template<typename T, int N>  struct VecAdd{

			 std::enable_if<std::is_pointer<T>::value,void>
			 operator()(T* c, T* b, T* a) {

				*c = *a + *b;
				VecAdd<T, N - 1> vec_add;
				vec_add.operator()(c + 1, b + 1, a + 1);
			}
		};

		/*
		 @brief     specialization for the terminating condition.
		*/

		template<typename T>  struct VecAdd<T,0> {

			std::enable_if<std::is_pointer<T>::value, void>
			 operator()(T* c, T* b, T* a) {

				
			}
		};

		/*
		@brief   c = a - b
		*/
		template<typename T, int N> struct VecSub{

			std::enable_if<std::is_same<T,T>::value && std::is_pointer<T>::value, void>
			operator()(T* c, T* b, T* a) {

				*c = *b - *a;

				    VecSub<T, N - 1> vec_sub;
					vec_sub.operator()(c + 1, b + 1, a + 1);
			}
		};

		/*
		@brief      specialization for the terminating condition.
		*/
		template<typename T> struct VecSub<T, 0> {

			std::enable_if<std::is_same<T, T>::value && std::is_pointer<T>::value, void>
			operator()(T* c, T* b, T* a) {

				
			}
		};

		/*
		@brief       c = a * b
		*/
		template<typename T, int N> struct VecMul{

			std::enable_if<std::is_same<T,T>::value && std::is_pointer<T>::value, void>
			operator()(T* c, T* b, T* a) {

				*c = *b * *a;

				    VecMul<T, N - 1> vec_mul;
					vec_mul.operator()(c + 1, b + 1, a + 1);
			}
		};

		/*
		@brief   specialization for the terminating condition.
		*/
		template<typename T>  struct VecMul<T, 0> {

			std::enable_if<std::is_same<T, T>::value && std::is_pointer<T>::value, void>
			operator()(T* c, T* b, T* a) {

				
			}
		};

		/*
		@brief      c = b / a
		*/
		template<typename T, int N>  struct VecDiv {

			std::enable_if<std::is_same<T,T>::value && std::is_pointer<T>::value,void>
			operator()(T* c, T* b, T* a) {

				*c = *b / *a;

				    VecDiv<T, N - 1> vec_div;
					vec_div.operator()(c + 1, b + 1, a + 1);

			}
		};

		/*
		@brief   specialization for the terminating condition.
		*/
		template<typename T>  struct VecDiv<T, 0> {

			std::enable_if<std::is_same<T, T>::value && std::is_pointer<T>::value, void>
			operator()(T* c, T* b, T* a) {

				

			}
		};

		/*
		 @brief     c = b + a, where a is scalar.
		*/
		template<typename T1, typename T2, int N> struct VecSAdd {

			std::enable_if<(std::is_same<T1, T2>::value && std::is_pointer<T1>::value)
			&& std::is_scalar<T2>::value, void>
			operator()(T1* c, T1* b, T2 const a) {

				   *c = *b + a;
				    VecSAdd<T1, T2, N - 1> vecs_add;
					vecs.add.operator()(c + 1, b + 1, a);
			}
		};

		/*
		@brief      specialization for the terminating condition.
		*/
		template<typename T1, typename T2> struct VecSAdd<T1, T2, 0> {

			std::enable_if<(std::is_same<T1, T2>::value && std::is_pointer<T1>::value)
			&& std::is_scalar<T2>::value, void>
			operator()(T1* c, T1* b, T2 const a) {

				
			}
		};

		/*
		brief      c = b - a, where a is scalar.
		*/
		template<typename T1, typename T2, int N> struct VecSSub {

			std::enable_if < (std::is_same<T1, T2>::value && std::is_pointer<T1>::value)
			&& std::is_scalar<T2>::value, void>
			operator()(T1* c, T1* b, T2 const a) {

				*c = *b - a;
				VecSSub<T1, T2, N - 1> vecs_sub;
					vecs_sub.operator()(c + 1, b + 1, a);
			}
		};

		/*
		@brief     specialization for the terminating condition.
		*/
		template<typename T1, typename T2> struct VecSSub<T1,T2,0> {

			std::enable_if < (std::is_same<T1, T2>::value && std::is_pointer<T1>::value)
			&& std::is_scalar<T2>::value, void>
			operator()(T1* c, T1* b, T2 const a) {

				
			}
		};

		/*
		@brief   c = b * a
		*/
		template<typename T1, typename T2, int N> struct VecSMul {

			std::enable_if< (std::is_same<T1,T2>::value && std::is_pointer<T1>::value)
			&& std::is_scalar<T2>::value, void>
			operator()(T1* c, T1* b, T2 const a) {

				*c = *b * a;
				VecSMul<T1, T2, N - 1> vecs_mul;
				vecs_mul.operator()(c + 1, b + 1, a);
			}
		};

		/*
		@brief    specialization for the terminating condition.
		*/
		template<typename T1, typename T2> struct VecSMul<T1, T2, 0> {

			std::enable_if< (std::is_same<T1, T2>::value && std::is_pointer<T1>::value)
			&& std::is_scalar<T2>::value, void>
			operator()(T1* c, T1* b, T2 const a) {

				
			}
		};

		/*
		@brief   c = b / a, where a is scalar.
		*/
		template<typename T1, typename T2, int N> struct VecSDiv {

			std::enable_if< (std::is_same<T1, T2>::value && std::is_pointer<T1>::value)
			&& std::is_scalar<T2>::value, void>
			operator()(T1* c, T1* b, const T2 a) {

				*c = *b / a;
				VecSDiv<T1, T2, N - 1> vecs_div;
				vecs_div.operator()(c + 1, b + 1, a);
			}
		};

		/*
		@brief    specialization for the terminating condition.
		*/
		template<typename T1, typename T2>  struct VecSDiv<T1, T2, 0> {

			std::enable_if< (std::is_same<T1, T2>::value && std::is_pointer<T1>::value)
			&& std::is_scalar<T2>::value, void>
			operator()(T1* c, T1* b, const T2 a) {

				
			}
		};

		/*
		         SIMD Vectorization.
		         AVX based versions.
		       
		*/

		

		/*
		       double version.
			   c[:] = b[:] + a[:]
		*/
		template<int N> struct AVXVecAdd {

			static_assert((N % 4) == 0, "N % 4 != 0");
			void operator()(double* c,  double  *  b, double  * a) {

#ifndef CACHING_STORES
				_mm256_storeu_pd(c, _mm256_add_pd(_mm256_loadu_pd(b), _mm256_loadu_pd(a)));
#else
				_mm256_stream_pd(c, _mm256_add_pd(_mm256_loadu_pd(b), _mm256_loadu_pd(a)));
#endif
				AVXVecAdd<N - 4> avxv_add;
				avxv_add.operator()(c + 4, b + 4, a + 4);
			}

		};

		/*
		@brief     specialization for the terminating condition.
		*/
		template<>  struct AVXVecAdd<0> {

			
		  void	operator()(double* c, double* __restrict b, double* __restrict a) {

				
			}
		};

		/*
		@brief    float version. Non-aligned on 32-bytes boundaries.
		          c[:] = b[:] + a[:]
		*/
		template<int N>  struct AVXF32VecAdd {

			static_assert((N % 8) == 0, "N % 8 != 0");
			void  inline operator()(float* c, float* b, float* a) {
				/*
				   Non-aligned load-store operations.
				*/
#ifndef  CACHING_STORES
				_mm256_storeu_ps(c, _mm256_add_ps(_mm256_loadu_ps(b), _mm256_loadu_ps(a)));
#else
				_mm256_stream_ps(c, _mm256_add_ps(_mm256_loadu_ps(b), _mm256_loadu_ps(a)));
#endif
				AVXF32VecAdd<N - 8> avxf32v_add;
				avxf32v_add.operator()(c + 8, b + 8, a + 8);
			}
		};

		/*
		@brief   terminating condition specialization
		*/
		template<> struct AVXF32VecAdd<0> {

			void  inline operator()(float* c, float* b, float* a) {
				
				
			}
		};

		/*
		@brief    double version.
		          c[:] = b[:] - a[:]
		*/
		template<int N>  struct AVXVecSub {

			static_assert((N % 4) == 0, "Fatal Error: N % 4 != 0");
			void inline operator()(double* c, double* b, double* a) {
				/*
				 unaligned load-store ops. 
				 No-store caching enabled by default.
				*/
#ifndef CACHING_STORES
				_mm256_storeu_pd(c, _mm256_sub_pd(_mm256_loadu_pd(b), _mm256_loadu_pd(a)));
#else
				_mm256_stream_pd(c, _mm256_sub_pd(_mm256_loadu_pd(b), _mm256_loadu_pd(a)));
#endif
				AVXVecSub<N - 4> avxv_sub;
				avxv_sub.operator()(c + 4, b + 4, a + 4);
			}
		};

		/*
		@brief   terminating condition specialization.
		*/
		template<>  struct AVXVecSub<0> {

			void inline operator()(double* c, double* b, double* a) {
				
			}

		};

		/*
		@brief      float version.
		@params     float* c - output pointer.
		@params     float* b - input pointer.
		@params     float* a - input pointer.
		@operation   c[:] = b[:] - a[:]
		*/
		template<int N>   struct AVXF32VecSub {

			static_assert((N % 8) == 0, "Fatal Error: N % 8 != 0");

			void inline operator()(float* c, float* b, float* a) {
				/*
				unaligned load-store ops. 
				No-store caching enabled by default.
				*/
#ifndef  CACHING_STORES
				_mm256_storeu_ps(c, _mm256_sub_ps(_mm256_loadu_ps(b), _mm256_loadu_ps(a)));
#else
				_mm256_stream_ps(c, _mm256_sub_ps(_mm256_loadu_ps(b), _mm256_loadu_ps(a)));
#endif
				AVXF32VecSub<N - 8> avxf32v_sub;
				avxf32v_sub.operator()(c + 8, b + 8, a + 8);
			}
		};

		/*
		@brief   terminating condition specialization.
		*/
		template<>    struct AVXF32VecSub<0> {

			void inline operator()(float* c, float* b, float* a) {
				
			}
		};

		/*
		@brief      double version.
		            c[:] = b[:] * a[:]
		*/
		template<int N>   struct AVXVecMul {

			static_assert((N % 4) == 0, "Fatal Error: N % 4 != 0");
			void inline operator()(double* c, double* b, double* a) {
				/*
				unaligned load-store ops.
				No-store caching enabled by default.
				*/
#ifndef   CACHING_STORES
				_mm256_storeu_pd(c, _mm256_mul_pd(_mm256_loadu_pd(b), _mm256_loadu_pd(a)));
#else
				_mm256_stream_pd(c, _mm256_mul_pd(_mm256_loadu_pd(b), _mm256_loadu_pd(a)));
#endif
				AVXVecMul<N - 4> avxv_mul;
				avxv_mul.operator()(c + 4, b + 4, a + 4);
			}
		};

		/*
		@brief     terminating condition specialization.
		*/
		template<>   struct AVXVecMul<0> {

			void inline operator()(double* c, double* b, double* a) {
				
			}
		};

		/*
		@brief      float version.
		            c[:] = b[:] * a[:]
		*/
		template<int N>   struct AVXF32VecMul {

			static_assert((N % 8) == 0, "Fatal Error: N % 8  != 0");
			void inline  operator()(float* c, float* b, float* a) {
				/*
				unaligned load-store ops.
				No-store caching enabled by default.
				*/
#ifndef  CACHING_STORES
				_mm256_storeu_ps(c, _mm256_mul_ps(_mm256_loadu_ps(b), _mm256_loadu_ps(a)));
#else
				_mm256_stream_ps(c, _mm256_mul_ps(_mm256_loadu_ps(b), _mm256_loadu_ps(a)));
#endif
				AVXF32VecMul<N - 8> avxf32v_mul;
				avxf32v_mul.operator()(c + 8, b + 8, a + 8);
			}
		};

		/*
		@brief   terminating condition specialization
		*/
		template<>     struct AVXF32VecMul<0> {

			void inline operator()(float* c, float* b, float* a) {

			}
		};

		/*
		@brief    double version.
		          c[:] = b[:] / a[:]
		*/
		template<int N>    struct AVXVecDiv {

			static_assert((N % 4) == 0, "Fatal Error: N % 4 != 0");
			void inline operator()(double* c, double* b, double* a) {
				/*
				unaligned load-store ops.
				No-store caching enabled by default.
				*/
#ifndef  CACHING_STORES
				_mm256_storeu_pd(c, _mm256_div_pd(_mm256_loadu_pd(b), _mm256_loadu_pd(a)));
#else
				_mm256_stream_pd(c, _mm256_div_pd(_mm256_loadu_pd(b), _mm256_loadu_pd(a)));
#endif
				AVXVecDiv<N - 4> avxv_div;
				avxv_div.operator()(c + 4, b + 4, a + 4);
			}
		};

		/*
		@brief      terminating condition specialization
		*/
		template<>     struct AVXVecDiv<0> {

			void inline operator()(double* c, double* b, double* a) {

			}
		};

		/*
		@brief       float version.
		             c[0:7] = b[0:7] / a[0:7]
		*/
		template<int N>     struct AVXF32VecDiv {

			static_assert((N % 8) == 0, "Fatal Error: N % 8 != 0");
			void inline operator()(float* c, float* b, float* a) {
				/*
				unaligned load-store ops.
				No-store caching enabled by default.
				*/
#ifndef  CACHING_STORES
				_mm256_storeu_ps(c, _mm256_div_ps(_mm256_loadu_ps(b), _mm256_loadu_ps(a)));
#else
				_mm256_stream_ps(c, _mm256_div_ps(_mm256_loadu_ps(b), _mm256_loadu_ps(a)));
#endif
				AVXF32VecDiv<N - 8> avxf32v_div;
				avxf32v_div.operator()(c + 8, b + 8, a + 8);
			}
		};

		/*
		@brief    terminating condition specialization.
		*/
		template<>     struct AVXF32VecDiv<0> {

			void inline operator()(float* c, float* b, float* a) {

			}
		};

		/*
		@brief    b[:] = sin(a[:])
		          Double specialization.
		*/
		template<int N> struct AVXVecSin{

			static_assert((N % 4) == 0, "Fatal Error: N % 4 != 0");
			void  inline  operator()(double* b, double* a) {
				/*
				unaligned load-store ops.
				No-store caching enabled by default.
				*/
#ifndef  CACHING_STORES
				_mm256_storeu_pd(b, _mm256_sin_pd(_mm256_loadu_pd(a)));
#else
				_mm256_stream_pd(b, _mm256_sin_pd(_mm256_loadu_pd(a)));
#endif
				AVXVecSin<N - 4> avxv_sin;
				avxv_sin.operator()(b + 4, a + 4);
			}
		};

		/*
		@brief    terminating condition specialization.
		*/
		template<>      struct AVXVecSin<0> {

			void inline operator()(double* b, double* a) {}
		};

		/*
		@brief    b[:] = sin(a[:])
		          Float specialization.
		*/
		template<int N>   struct AVXF32VecSin {

			static_assert((N % 8) == 0, "Fatal Error: N % 8 != 0");
			void   inline   operator()(float* b, float* a) {
				/*
				unaligned load-store ops.
				No-store caching enabled by default.
				*/
#ifndef  CACHING_STORES
				_mm256_storeu_ps(b, _mm256_sin_ps(_mm256_loadu_ps(a)));
#else
				_mm256_stream_ps(b, _mm256_sin_ps(_mm256_loadu_ps(a)));
#endif
				AVXF32VecSin<N - 8> avxf32v_sin;
				avxf32v_sin.operator()(b + 8, a + 8);
			}
		};

		/*
		@brief    terminating condition specialization.
		*/
		template<>    struct AVXF32VecSin<0> {

			inline void  operator()(float* b, float* a) {}
		};
		/*
		@brief  Simple print template. Non-compile time version.
		*/
		template<typename T, class VecName, int N> struct VecPrinter {

			std::enable_if<std::is_pointer<T>::value && std::is_floating_point<T>::value,void>
			operator()(T* ptr, const VecName &name) {

				/* By default precision is 16 decimal digits.*/
				for (int i{ 0 }; i != N; ++i)
					std::printf("%s[%d]=%4.16f\n", name.c_str(), i, ptr[i]);
			}
		};
	}
}
#endif /*_META_VECTORS_HPP_*/