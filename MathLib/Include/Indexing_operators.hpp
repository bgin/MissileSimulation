
#ifndef __INDEXING_OPERATORS_HPP__
#define __INDEXING_OPERATORS_HPP__

//Code: Function definitions Col 8(Tab*2)
//Code: Function variables Col 32 (Tab*8)

// File version granularity.

#ifndef INDEXING_OPERATORS_VERSION_MAJOR
#define INDEXING_OPERATORS_VERSION_MAJOR 1
#endif

#ifndef INDEXING_OPERATORS_VERSION_MINOR
#define INDEXONG_OPERATORS_VERSION_MINOR 0
#endif

#ifndef INDEXING_OPERATORS_PATCH_VERSION
#define INDEXING_OPERATORS_PATCH_VERSION 0
#endif

#ifndef INDEXING_OPERATORS_CREATE_DATE
#define INDEXING_OPERATORS_CREATE_DATE "Date: 2016-08-30 Time: 15:16 PM GMT+2"
#endif

// Set this value to successful build date/time.
#ifndef INDEXING_OPERATORS_BUILD_DATE
#define INDEXING_OPERATORS_BUILD_DATE ""
#endif

#include <type_traits>

namespace mathlib {
	namespace operators {



		enum class ArrayDimension : unsigned int{

		        DIM_1D = 1U,

				DIM_2D = 2U,

				DIM_3D = 3U,

				DIM_4D = 4U,

				DIM_5D = 5U,

				DIM_6D = 6U,

				DIM_7D = 7U,

				DIM_8D = 8U,

				DIM_9D = 9U,

				DIM_10D = 10U
		};


		
	    
	   template<typename Index_t,
		         typename = std::enable_if<std::is_integral<Index_t>::
				            value && !std::is_floating_point<Index_t>::value>::type> struct Subscriptor1D {

								Subscriptor1D() = default;

								__forceinline auto operator()(_In_ Index_t i)->Index_t { return (i); }

								inline constexpr Index_t dim(){ return static_cast<Index_t>(ArrayDimension::DIM_1D); }

				 };

		template<typename Index_t,
		          typename = std::enable_if<std::is_integral<Index_t>::
				             value && !std::is_floating_point<Index_t>::value>::type> struct Subscriptor2D {

								 Subscriptor2D() = default;

								__forceinline auto operator()(_In_ Index_t i,
									                          _In_ const Index_t isize,
									                          _In_ Index_t j)->Index_t {

									 return (i + isize * j);
								 }

							    inline constexpr Index_t dim() { return (static_cast<Index_t>(ArrayDimension::DIM_2D)); }
				  };

		template<typename Index_t,
		          typename = std::enable_if<std::is_integral<Index_t>::
				             value && !std::is_floating_point<Index_t>::value>::type> struct Subscriptor3D {

								 Subscriptor3D() = default;

								__forceinline auto operator()(_In_ Index_t i,
									             _In_ const Index_t isize,
									             _In_ Index_t j,
									             _In_ const Index_t jsize,
									             _In_ Index_t k)->Index_t {

									 return (i + isize * (j + jsize * k));
								 }

								inline constexpr Index_t dim() { return (static_cast<Index_t>(ArrayDimension::DIM_3D)); }
				  };

		template<typename Index_t,
		          typename = std::enable_if<std::is_integral<Index_t>::
				             value && !std::is_floating_point<Index_t>::value>::type> struct Subscriptor4D {

								 Subscriptor4D() = default;

								__forceinline auto operator()(_In_ Index_t i,
									                          _In_ const Index_t isize,
									                          _In_ Index_t j,
									                          _In_ const Index_t jsize,
									                          _In_ Index_t k,
									                          _In_ const Index_t ksize,
									                          _In_ Index_t l)->Index_t {

									 return (i + isize * (j + jsize * (k + ksize * l)));
								 }

								inline constexpr Index_t dim() { return (static_cast<Index_t>(ArrayDimension::DIM_4D)) };
				  };

		template<typename Index_t,
		          typename = std::enable_if<std::is_integral<Index_t>::
				             value && !std::is_floating_point<Index_t>::value>::type> struct Subscriptor5D {

								 Subscriptor5D() = default;

								 __forceinline auto operator()(_In_ Index_t i,
									                           _In_ const Index_t isize,
									                           _In_ Index_t j,
									                           _In_ const Index_t jsize,
									                           _In_ Index_t k,
									                           _In_ const Index_t ksize,
									                           _In_ Index_t l,
									                           _In_ const Index_t lsize,
									                           _In_ Index_t m)->Index_t {


									 return (i + isize * (j + jsize * (k + ksize * (l + lsize * m))));
								 }

								 inline constexpr Index_t dim() { return (static_cast<Index_t>(ArrayDimension::DIM_5D)) };
				  };

		template<typename Index_t,
		          typename = std::enable_if<std::is_integral<Index_t>::
				             value && !std::is_floating_point<Index_t>::value>::type> struct Subscriptor6D {

								 Subscriptor6D() = default;

								 __forceinline auto operator()(_In_ Index_t i,
									                           _In_ const Index_t isize,
									                           _In_ Index_t j,
									                           _In_ const Index_t jsize,
									                           _In_ Index_t k,
									                           _In_ const Index_t ksize,
									                           _In_ Index_t l,
									                           _In_ const Index_t lsize,
									                           _In_ Index_t m,
									                           _In_ const Index_t msize,
									                           _In_ Index_t n)->Index_t {

									 return (i + isize * (j + jsize * (k + ksize * (l + lsize * (m + msize * n)))));
								 }

								 inline constexpr Index_t dim() { return (static_cast<Index_t>(ArrayDimension::DIM_6D)) };
				  };

		template<typename Index_t,
		          typename = std::enable_if<std::is_integral<Index_t>::
				             value && !std::is_floating_point<Index_t>::value>::type> struct Subscriptor7D {

								 Subscriptor7D() = default;

								 __forceinline auto operator()(_In_ Index_t i,
									                           _In_ const Index_t isize,
									                           _In_ Index_t j,
									                           _In_ const Index_t jsize,
									                           _In_ Index_t k,
									                           _In_ const Index_t ksize,
									                           _In_ Index_t l,
									                           _In_ const Index_t lsize,
									                           _In_ Index_t m,
									                           _In_ const Index_t msize,
									                           _In_ Index_t n,
									                           _In_ const Index_t nsize,
									                           _In_ Index_t p)->Index_t {

									 return (i + isize * (j + jsize * (k + ksize * (l + lsize * 
									                                  (m + msize * (n + nsize * p))))));

                                   }
								   
								 inline constexpr Index_t dim() { return (static_cast<Index_t>(ArrayDimension::DIM_7D)); }
				  };

		template<typename Index_t,
		          typename = std::enable_if<std::is_integral<Index_t>::
				              value && !std::is_floating_point<Index_t>::value>::type> struct Subscriptor8D {

								  Subscriptor8D() = default;

								  __forceinline auto operator()(_In_ Index_t i,
									                            _In_ const Index_t isize,
									                            _In_ Index_t j,
									                            _In_ const Index_t jsize,
									                            _In_ Index_t k,
									                            _In_ const Index_t ksize,
									                            _In_ Index_t l,
									                            _In_ const Index_t lsize,
									                            _In_ Index_t m,
									                            _In_ const Index_t msize,
									                            _In_ Index_t n,
									                            _In_ const Index_t nsize,
									                            _In_ Index_t p,
									                            _In_ const Index_t psize,
									                            _In_ Index_t r)->Index_t {

									  return (i + isize * (j + jsize * (k + ksize * (l + lsize * 
									                      (m + msize * (n + nsize * (p + psize * r)))))));
								  }

								  inline constexpr Index_t dim() { return (static_cast<Index_t>(ArrayDimension::DIM_8D)); }
				  };

		template<typename Index_t,
		          typename = std::enable_if<std::is_integral<Index_t>::
				               value && !std::is_floating_point<Index_t>::value>::type> struct Subscriptor9D {

								   Subscriptor9D() = default;

								   __forceinline auto operator()(_In_ Index_t i,
									                             _In_ const Index_t isize,
									                             _In_ Index_t j,
									                             _In_ const Index_t jsize,
									                             _In_ Index_t k,
									                             _In_ const Index_t ksize,
									                             _In_ Index_t l,
									                             _In_ const Index_t lsize,
									                             _In_ Index_t m,
									                             _In_ const Index_t msize,
									                             _In_ Index_t n,
									                             _In_ const Index_t nsize,
									                             _In_ Index_t p,
									                             _In_ const psize,
									                             _In_ Index_t r,
									                             _In_ const Index_t rsize,
									                             _In_ Index_t q)->Index_t {

									   return (i + isize * (j + jsize * (k + ksize * (l + lsize * (m + msize * 
									                                     (n + nsize * (p + psize * (r + rsize * q))))))));
								   }

								   inline constexpr Index_t dim() { return (static_cast<Index_t>(ArrayDimension::DIM_9D)); }
				 };

		template<typename Index_t,
		         typename = std::enable_if<std::is_integral<Index_t>::
				             value && !std::is_floating_point<Index_t>::value>::type> struct Subscriptor10D{

								 Subscriptor10D() = default;

								 __forceinline auto operator()(_In_ Index_t i,
									                           _In_ const Index_t isize,
									                           _In_ Index_t j,
									                           _In_ const Index_t jsize,
									                           _In_ Index_t k,
									                           _In_ const Index_t ksize,
									                           _In_ Index_t l,
									                           _In_ const Index_t lsize,
									                           _In_ Index_t m,
									                           _In_ const Index_t msize,
									                           _In_ Index_t n,
									                           _In_ const Index_t nsize,
									                           _In_ Index_t p,
									                           _In_ const Index_t psize,
									                           _In_ Index_t r,
									                           _In_ const Index_t rsize,
									                           _In_ Index_t q,
									                           _In_ const Index_t qsize,
									                           _In_ Index_t s)->Index_t {

									 return (i + isize * (j + jsize * (k + ksize * (l + lsize * (m + msize *
									                     (n + nsize * (p + psize * (r + rsize * (q + qsize + s))))))));
								 }

								 inline constexpr Index_t dim() { return (static_cast<Index_t>(ArrayDimension::DIM_10D)); }
				 };

		

	}
}



#endif /*__INDEXING_OPERATORS_HPP__*/