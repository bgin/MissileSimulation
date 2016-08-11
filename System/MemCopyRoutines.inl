
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
C++ structs templated on primitive and some of STL container data types -  implementation.

@file MemCopyRoutines.h
@author: Bernard Gingold
@version:  1.0.0  25/12/2015
@description: MemCopyRoutines.h
@reference: None


*/

/*
                Simple memory copy routines
				Without cache bypassing.
*/

/*
         Warning!!
		 Caller must assure that Length is divisable by 16.
*/
template<typename T, const int N> std::enable_if<std::is_pointer<T>::value,void>::type
internal_system::FastSSEMemCpy<T, N>::sse_mem_cpy2x(_In_ const T* __restrict src, _Outptr_ T* __restrict dst, _In_ const int Len) {

#if defined _DEBUG
	// SFINAE in use here!!
	//g_utils::dbg_asserte(src, dst, Len);
	_ASSERTE((src != nullptr) && (dst != nullptr) && (Len > 0));
#else
	
	//g_utils::check_args(src, dst, std::string("Invalid input argument(s) in sse_mem_cpy2x"));
	if (src == nullptr || dest == nullptr || Len <= 0)
		throw std::runtime_error("Invalid input in sse_mem_cpy2x");
#endif

	// Trivial copy routine.
	/* Unrolled 2x */
	for (int i{ 0 }; i != Len - 2; i += 2) {

		dst[i] = src[i];
		dst[i + 1] = src[i + 1];
	}
	
}

template<typename T, const int N>  std::enable_if<std::is_pointer<T>::value,void>::type
internal_system::FastSSEMemCpy<T, N>::sse_mem_cpy4x(_In_ const T* __restrict source, _Outptr_ T* __restrict dest, _In_ const int Length) {

#if defined _DEBUG
	_ASSERTE((source != nullptr) && (dest != nullptr) && (Length != 0));
#else
	if ((source == nullptr) || (dest == nullptr) || (Length <= 0))
		throw std::runtime_error("Invalid argument in sse_mem_cpy4x\n");
#endif

	/* Simple copy routine unrolled 4x*/
	for (int i{ 0 }; i != Length - 4; i += 4) {

		dest[i] = source[i];
		dest[i + 1] = source[i + 1];
		dest[i + 2] = source[i + 2];
		dest[i + 3] = source[i + 3];
	}
}

template<typename T, const int N> std::enable_if<std::is_pointer<T>::value, void>::type
internal_system::FastSSEMemCpy<T, N>::sse_mem_cpy8x(_In_ const T* __restrict source, _Outptr_ T* __restrict dest, _In_ const int Length) {
#if defined _DEBUG
	_ASSERTE((source != nullptr) && (dest != nullptr) && (Length != 0));
#else
	if ((source == nullptr) || (dest == nullptr) || (Length <= 0))
		throw std::runtime_error("Invalid argument in sse_mem_cpy8x\n");
#endif

	/* Simple copy routine unrolled 8x */
	for (int i{ 0 }; i != Length - 8; i += 8) {

		dest[i] = source[i];
		dest[i + 1] = source[i + 1];
		dest[i + 2] = source[i + 2];
		dest[i + 3] = source[i + 3];
		dest[i + 4] = source[i + 4];
		dest[i + 5] = source[i + 5];
		dest[i + 6] = source[i + 6];
		dest[i + 7] = source[i + 7];
	}
}

#if defined SYSTEM_USE_OPENMP
 template<typename T, const int N> std::enable_if<std::is_pointer<T>::value, void>::type
	 internal_system::FastSSEMemCpy<T, N>::sse_mem_cpy_mt(_In_ const T* __restrict src, _Outptr_ T* __restrict dst, _In_ const int nThreads,
	 _In_ const int Length) {
#if defined _DEBUG
		 _ASSERTE((src != nullptr) && (dst != nullptr) && (Length != 0));
#else
		 if ((src == nullptr) || (dst == nullptr) || (Length <= 0))
			 throw std::runtime_error("Invalid argument in sse_mem_cpy_mt\n");
#endif
		 /* Use OpenMP for array size > 8000 elements. */

		 ::omp_set_num_threads(nThreads);
#pragma omp parallel for 
		 for (int i = 0; i < Length; ++i)
			 dst[i] = src[i];
	 }
#endif


/*
            Warning!!
           Caller must assure that Length is divisable by 16.
*/

auto   internal_system::FastSSEMemCpy<float, 0>::sse_mem_cpy_f32(_In_ const float* __restrict source, _Outptr_ float* __restrict dest, const int Length)->void {

#if defined _DEBUG
	g_utils::dbg_asserte(source, dest, Length);
#else
	g_utils::check_args(source, dest, Length,std::string("Invalid input in sse_mem_cpy_f32"));
#endif

	if (Length <= static_cast<int>(g_utils::L1D_SP_ELEMS)) {
		//Prefetch to L1D only.
		for (int i{ 0 }; i != Length - 8; i += 8) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + 4] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&source[i + 2]), _MM_HINT_T0);
			_mm_storeu_ps(&dest[i], _mm_loadu_ps(&source[i]));
			_mm_storeu_ps(&dest[i + 4], _mm_loadu_ps(&source[i + 4]));
		}

	}
	else {
		// Prefetch to L2 only.
		for (int i{ 0 }; i != Length - 8; i += 8) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + 4] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char *>(&source[i + 2]), _MM_HINT_T1);
			_mm_storeu_ps(&dest[i], _mm_loadu_ps(&source[i]));
			_mm_storeu_ps(&dest[i + 4], _mm_loadu_ps(&source[i + 4]));
		}
	}

}

/*
                       Warning!!
                       Caller must assure that Length is divisable by 16.
*/
auto   internal_system::FastSSEMemCpy<float, 0>::sse_mem_cpy_f324x(_In_ const float* __restrict src, _Outptr_ float* __restrict dest, _In_ const int Length)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dest, Length);
#else
	g_utils::check_args(src, dest, Length, std::string("Invalid input in sse_mem_cpy_f324x"));
#endif
	
	if (Length <= static_cast<int>(g_utils::L1D_SP_ELEMS)) {
		// Prefetch to L1D only.
		for (int i{ 0 }; i != Length - 16; i += 16) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + 4] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T0);
			_mm_storeu_ps(&dest[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dest[i + 4], _mm_loadu_ps(&src[i + 4]));
			_mm_storeu_ps(&dest[i + 8], _mm_loadu_ps(&src[i + 8]));
			_mm_storeu_ps(&dest[i + 12], _mm_loadu_ps(&src[i + 12]));
		}
	}
	else {
		// Prefetch to L2 ony.
		for (int i{ 0 }; i != Length - 16; i += 16) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + 4] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T1);
			_mm_storeu_ps(&dest[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dest[i + 4], _mm_loadu_ps(&src[i + 4]));
			_mm_storeu_ps(&dest[i + 8], _mm_loadu_ps(&src[i + 8]));
			_mm_storeu_ps(&dest[i + 12], _mm_loadu_ps(&src[i + 12]));
		}
	}
}

/*
                          Warning!!
                          Caller must assure that Length is divisable by 16.
*/
auto   internal_system::FastSSEMemCpy<float, 0>::sse_mem_cpy_f328x(_In_ const float* __restrict src, _Outptr_ float* __restrict dest, _In_ const int Length)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dest, Length);
#else
	g_utils::check_args(src,dest,Length,std::string("Invalid input in sse_mem_cpy_f328x"));
#endif
	if (Length <= static_cast<int>(g_utils::L1D_SP_ELEMS)) {
		// Prefetch to L1D.
		for (int i{ 0 }; i != Lengt - 32; i += 32) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + 4] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T0);
			_mm_storeu_ps(&dest[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dest[i + 4], _mm_loadu_ps(&src[i + 4]));
			_mm_storeu_ps(&dest[i + 8], _mm_loadu_ps(&src[i + 8]));
			_mm_storeu_ps(&dest[i + 12], _mm_loadu_ps(&src[i + 12]));
			_mm_storeu_ps(&dest[i + 16], _mm_loadu_ps(&src[i + 16]));
			_mm_storeu_ps(&dest[i + 20], _mm_loadu_ps(&src[i + 20]));
			_mm_storeu_ps(&dest[i + 24], _mm_loadu_ps(&src[i + 24]));
			_mm_storeu_ps(&dest[i + 28], _mm_loadu_ps(&src[i + 28]));
		}
	}
	else {
		// Prefetch to L2.
		
		for (int i{ 0 }; i != Length - 32; i += 32) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + 4] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T0);
			_mm_storeu_ps(&dest[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dest[i + 4], _mm_loadu_ps(&src[i + 4]));
			_mm_storeu_ps(&dest[i + 8], _mm_loadu_ps(&src[i + 8]));
			_mm_storeu_ps(&dest[i + 12], _mm_loadu_ps(&src[i + 12]));
			_mm_storeu_ps(&dest[i + 16], _mm_loadu_ps(&src[i + 16]));
			_mm_storeu_ps(&dest[i + 20], _mm_loadu_ps(&src[i + 20]));
			_mm_storeu_ps(&dest[i + 24], _mm_loadu_ps(&src[i + 24]));
			_mm_storeu_ps(&dest[i + 28], _mm_loadu_ps(&src[i + 28]));
		}
	}

}
/*
                             Warning!!
                             Caller must assure that Length is divisable by 16.
*/

auto   internal_system::FastSSEMemCpy<double, 0>::sse_mem_cpy_f64(_In_ const double* __restrict src, _Outptr_ double* __restrict dest, _In_ const int Length)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dest, Length);
#else
	g_utils::check_args(src, dest, Length, std::string{ "Invalid argument in sse_mem_cpy_f64" });
#endif
	
	if (Length <= static_cast<int>(g_utils::L1D_DP_ELEMS)) {
		// Prefetch to L1D only.
		for (int i{ 0 }; i != Length - 4; i += 4) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + 4] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T0);
			_mm_storeu_pd(&dest[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dest[i + 2], _mm_loadu_pd(&src[i + 2]));

		}
	}
	else {
		// Prefetch to L2 only.
		for (int i{ 0 }; i != Length - 4; i += 4) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + 4] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T1);
			_mm_storeu_pd(&dest[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dest[i + 2], _mm_loadu_pd(&src[i + 2]));
		}
	}
}

/*
                         Warning!!
                         Caller must assure that Length is divisable by 16.
*/
auto   internal_system::FastSSEMemCpy<double, 0>::sse_mem_cpy_f644x(_In_ const double* __restrict src, _Outptr_ double* __restrict dest, _In_ const int Length)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dest, Length);
#else
	g_utils::check_args(src, dest, Length, std::string{ "Invalid argument in sse_mem_cpy_f644x" });
#endif
	
	if (Length <= static_cast<int>(g_utils::L1D_DP_ELEMS)) {
		// Prefetch to L1D.
		for (int i{ 0 }; i != Length - 8; i += 8) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + 4] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T0);
			_mm_storeu_pd(&dest[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dest[i + 2], _mm_loadu_pd(&src[i + 2]));
			_mm_storeu_pd(&dest[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dest[i + 6], _mm_loadu_pd(&src[i + 6]));
			
		}
	}
	else {
		// Prefetch to L2 only.
		for (int i{ 0 }; i != Length - 8; i += 8) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + 4] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T1);
			_mm_storeu_pd(&dest[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dest[i + 2], _mm_loadu_pd(&src[i + 2]));
			_mm_storeu_pd(&dest[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dest[i + 6], _mm_loadu_pd(&src[i + 6]));

		}
	}
}

/*
                           Warning!!
                           Caller must assure that Length is divisable by 16.
*/
auto   internal_system::FastSSEMemCpy<double, 0>::sse_mem_cpy_f648x(_In_ const double* __restrict src, _Outptr_ double* dest, _In_ const int Length)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dest, Length);
#else
	g_utils::check_args(src, dest, Length, std::string{ "Invalid argument in sse_mem_cpy_f648x" });
#endif
	
	if (Length <= static_cast<int>(g_utils::L1D_DP_ELEMS)) {
		// Prefetch to L1D only
		for (int i{ 0 }; i != Length - 16; i += 16) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + 4] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T0);
			_mm_storeu_pd(&dest[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dest[i + 2], _mm_loadu_pd(&src[i + 2]));
			_mm_storeu_pd(&dest[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dest[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dest[i + 6], _mm_loadu_pd(&src[i + 6]));
			_mm_storeu_pd(&dest[i + 8], _mm_loadu_pd(&src[i + 8]));
			_mm_storeu_pd(&dest[i + 10], _mm_loadu_pd(&src[i + 10]));
			_mm_storeu_pd(&dest[i + 12], _mm_loadu_pd(&src[i + 12]));
		}
	}
	else {
		// Prefetch to L2 only.
		for (int i{ 0 }; i != Length - 16; i += 16) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + 4] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T1);
			_mm_storeu_pd(&dest[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dest[i + 2], _mm_loadu_pd(&src[i + 2]));
			_mm_storeu_pd(&dest[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dest[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dest[i + 6], _mm_loadu_pd(&src[i + 6]));
			_mm_storeu_pd(&dest[i + 8], _mm_loadu_pd(&src[i + 8]));
			_mm_storeu_pd(&dest[i + 10], _mm_loadu_pd(&src[i + 10]));
			_mm_storeu_pd(&dest[i + 12], _mm_loadu_pd(&src[i + 12]));
		}
	}
}

/*
                 Warning !!
				 Assumes that src and dest are unaligned on 16-bytes.
				 Should be not any penalty for unaligned access by calling
				 _mm_storeu_ps intrinsc function.
*/
auto    internal_system::FastSSEMemCpy<std::valarray<float>, 0>::sse_mem_cpy_valf32(_In_ const std::valarray<float> &src, _Out_ std::valarray<float> &dest)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dest);
#else
	g_utils::check_args(src,dest,std::string("Invalid argument(s) in sse_mem_cpy_valf32"));
#endif
	for (std::size_t i{ 0 }; i != src.size() - 8; i += 8) {
		/*  Bear in mind that ICC probably will not vectorise 
		 *  further this loop mainly because of flow dependence
		 *   [i], [i + 4] on the next iteration.
		 */
		_mm_storeu_ps(&dest[i], _mm_loadu_ps(&src[i]));
		_mm_storeu_ps(&dest[i + 4], _mm_loadu_ps(&src[i + 4]));
	}
}

/*
                 Warning !!
           Assumes that src and dest are unaligned on 16-bytes.
           Should be not any penalty for unaligned access by calling
          _mm_storeu_ps intrinsc function.
*/
auto    internal_system::FastSSEMemCpy<std::valarray<float>, 0>::sse_mem_cpy_valf324x(_In_  std::valarray<float>& src, _Out_ std::valarray<float>& dest)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dest);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_valf324x"));
#endif
	if (src.size() <= g_utils::L1D_SP_ELEMS) {
		for (std::size_t i{ 0 }; i != src.size() - 16; i += 16) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + 4] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i]), _MM_HINT_T0);
			_mm_storeu_ps(&dest[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dest[i + 4], _mm_loadu_ps(&src[i + 4]));
			_mm_storeu_ps(&dest[i + 8], _mm_loadu_ps(&src[i + 8]));
			_mm_storeu_ps(&dest[i + 12], _mm_loadu_ps(&src[i + 12]));
		}
	}
	else {
		for (std::size_t i{ 0 }; i != src.size() - 16; i += 16) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + 4] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i]), _MM_HINT_T1);
			_mm_storeu_ps(&dest[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dest[i + 4], _mm_loadu_ps(&src[i + 4]));
			_mm_storeu_ps(&dest[i + 8], _mm_loadu_ps(&src[i + 8]));
			_mm_storeu_ps(&dest[i + 12], _mm_loadu_ps(&src[i + 12]));
		}
	}
}

/*
                    Warning !!
              Assumes that src and dest are unaligned on 16-bytes.
              Should be not any penalty for unaligned access by calling
              _mm_storeu_ps intrinsc function.
*/
auto    internal_system::FastSSEMemCpy<std::valarray<float>, 0>::sse_mem_cpy_valf328x(_In_ std::valarray<float>& src, _Out_ std::valarray<float>& dest)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dest);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_valf328x"));
#endif
	
	if (src.size() <= g_utils::L1D_SP_ELEMS){
		for (std::size_t i{ 0 }; i != src.size() - 32; i += 32) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			*/

			_mm_prefetch(reinterpret_cast<const char*>(&src[i]), _MM_HINT_T0);
			_mm_storeu_ps(&dest[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dest[i + 4], _mm_loadu_ps(&src[i + 4]));
			_mm_storeu_ps(&dest[i + 8], _mm_loadu_ps(&src[i + 8]));
			_mm_storeu_ps(&dest[i + 12], _mm_loadu_ps(&src[i + 12]));
			_mm_storeu_ps(&dest[i + 16], _mm_loadu_ps(&src[i + 16]));
			_mm_storeu_ps(&dest[i + 20], _mm_loadu_ps(&src[i + 20]));
			_mm_storeu_ps(&dest[i + 24], _mm_loadu_ps(&src[i + 24]));
			_mm_storeu_ps(&dest[i + 28], _mm_loadu_ps(&src[i + 28]));
		}
	}
	else{
		omp_set_num_threads(4);
#pragma omp parallel for if(src.size() > (1 << 24)) 
		for (std::size_t i{ 0 }; i != src.size() - 32; i += 32) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i]), _MM_HINT_T1);
			
			_mm_storeu_ps(&dest[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dest[i + 4], _mm_loadu_ps(&src[i + 4]));
			_mm_storeu_ps(&dest[i + 8], _mm_loadu_ps(&src[i + 8]));
			_mm_storeu_ps(&dest[i + 12], _mm_loadu_ps(&src[i + 12]));
			_mm_storeu_ps(&dest[i + 16], _mm_loadu_ps(&src[i + 16]));
			_mm_storeu_ps(&dest[i + 20], _mm_loadu_ps(&src[i + 20]));
			_mm_storeu_ps(&dest[i + 24], _mm_loadu_ps(&src[i + 24]));
			_mm_storeu_ps(&dest[i + 28], _mm_loadu_ps(&src[i + 28]));
		}
	}
}

/*
                          Warning !!
               Assumes that src and dest are unaligned on 16-bytes.
               Should be not any penalty for unaligned access by calling
               _mm_storeu_ps intrinsc function.
*/
auto   internal_system::FastSSEMemCpy<std::valarray<double>, 0>::sse_mem_cpy_valf64(_In_ std::valarray<double>& src, _Out_ std::valarray<double>& dst)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_valf64"));
#endif
	// Prefetch to L1D
	if (src.size() <= g_utils::L1D_SP_ELEMS){
		for (std::size_t i{ 0 }; i != src.size() - 4; i += 4) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			    Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i]), _MM_HINT_T0);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
		}
	}
	else{
		// Prefetch to L2D
		for (std::size_t i{ 0 }; i != src.size() - 4; i += 4) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			   Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i]), _MM_HINT_T1);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
		}
	}
}

/*
                     Warning !!
            Assumes that src and dest are unaligned on 16-bytes.
            Should be not any penalty for unaligned access by calling
            _mm_storeu_pd intrinsc function.
*/
auto   internal_system::FastSSEMemCpy<std::valarray<double>, 0>::sse_mem_cpy_valf644x(_In_ std::valarray<double>& src, _Out_ std::valarray<double>& dst)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_valf644x"));
#endif
	// Prefetch tp L1D.
	if (src.size() <= g_utils::L1D_SP_ELEMS) {
		for (std::size_t i{ 0 }; i != src.size() - 8; i += 8) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			  Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 8]), _MM_HINT_T0);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
			_mm_storeu_pd(&dst[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dst[i + 6], _mm_loadu_pd(&src[i + 6]));
			
		}
	}
	else {
		 // Prefetch to L2D.
		// Attempt to use OpenMP for large data set i.e large that 1 << 24 elements.
		omp_set_num_threads(4);
#pragma omp parallel for if(src.size() >= (1 << 24)) 
		for (std::size_t i{ 0 }; i != src.size() - 8; i += 8) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			   Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 8]), _MM_HINT_T1);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
			_mm_storeu_pd(&dst[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dst[i + 6], _mm_loadu_pd(&src[i + 6]));
		}
	}
}
/*
                       Warning !!
          Assumes that src and dest are unaligned on 16-bytes.
          Should be not any penalty for unaligned access by calling
         _mm_storeu_pd intrinsc function.
*/
auto    internal_system::FastSSEMemCpy<std::valarray<double>, 0>::sse_mem_cpy_valf648x(_In_ std::valarray<double>& src, _Out_ std::valarray<double>& dst)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_valf648x"));
#endif
	
	if (src.size() <= g_utils::L1D_SP_ELEMS){
		for (std::size_t i{ 0 }; i != src.size() - 16; i += 16) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 8]), _MM_HINT_T0);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
			_mm_storeu_pd(&dst[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dst[i + 6], _mm_loadu_pd(&src[i + 6]));
			_mm_storeu_pd(&dst[i + 8], _mm_loadu_pd(&src[i + 8]));
			_mm_storeu_pd(&dst[i + 10], _mm_loadu_pd(&src[i + 10]));
			_mm_storeu_pd(&dst[i + 12], _mm_loadu_pd(&src[i + 12]));
			_mm_storeu_pd(&dst[i + 14], _mm_loadu_pd(&src[i + 14]));
		}
	}
	else {
		// Prefetch to L2D.
		// Uses OpenMP for data set larger than 1 << 24.
		omp_set_num_threads(4);
#pragma omp parallel for if(src.size() >= (1 << 24))
		for (std::size_t i{ 0 }; i != src.size() - 16; i += 16) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			  Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 8]), _MM_HINT_T1);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
			_mm_storeu_pd(&dst[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dst[i + 6], _mm_loadu_pd(&src[i + 6]));
			_mm_storeu_pd(&dst[i + 8], _mm_loadu_pd(&src[i + 8]));
			_mm_storeu_pd(&dst[i + 10], _mm_loadu_pd(&src[i + 10]));
			_mm_storeu_pd(&dst[i + 12], _mm_loadu_pd(&src[i + 12]));
			_mm_storeu_pd(&dst[i + 14], _mm_loadu_pd(&src[i + 14]));
		}
	}
}

/*
                      Warning !!
        Assumes that src and dest are unaligned on 16-bytes.
        Should be not any penalty for unaligned access by calling
        _mm_storeu_pd intrinsc function.
*/

template<const int N>  void internal_system::FastSSEMemCpy<std::array<float, N>, 0>::sse_mem_cpy_arf32(_In_ std::array<float, N>& src, _Out_ std::array<float, N>& dst) {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_arf32"));
#endif
	// Prefetch L1D 
	if (src.size() <= g_utils::L1D_SP_ELEMS) {
		for (std::size_t i{ 0 }; i != src.size() - 8; i += 8) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i]), _MM_HINT_T0);
			_mm_storeu_ps(&dst[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dst[i + 4], _mm_loadu_ps(&src[i + 4]));
		}
	}
	else {
		// Prefetch to L2D
		for (std::size_t i{ 0 }; i != src.size() - 8; i += 8) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 4]), _MM_HINT_T1);
			_mm_storeu_ps(&dst[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dst[i + 4], _mm_loadu_ps(&src[i + 4]));
		}
	}
}

/*
                       Warning !!
           Assumes that src and dest are unaligned on 16-bytes.
           Should be not any penalty for unaligned access by calling
          _mm_storeu_pd intrinsc function.
*/
template<const int N> void internal_system::FastSSEMemCpy<std::array<float, N>, 0>::sse_mem_cpy_arf324x(_In_ std::array<float, N>& src, _In_ std::array<float, N>& dst) {

#if defined _DEBUG
	g_utils::dbg_asserte(src, dst);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_arf324x"));
#endif
	if (src.size() <= g_utils::L1D_SP_ELEMS) {
		// Prefetch to L1D only.
		for (std::size_t i{ 0 }; i != src.size() - 16; i += 16) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i]), _MM_HINT_T0);
			_mm_storeu_ps(&dst[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dst[i + 4], _mm_loadu_ps(&src[i + 4]));
			_mm_storeu_ps(&dst[i + 8], _mm_loadu_ps(&src[i + 8]));
			_mm_storeu_ps(&dst[i + 12], _mm_loadu_ps(&src[i + 12]));
		}
	}
	else {
		// Prefetch to L2D only.
		// Use OpenMP for data set larger than 1 << 24 elements.
		omp_set_num_threads(4);
#pragma omp parallel for if(src.size() >= (1 << 24))
		for (std::size_t i{ 0 }; i != src.size() - 16; i += 16) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T1);
			_mm_storeu_ps(&dst[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dst[i + 4], _mm_loadu_ps(&src[i + 4]));
			_mm_storeu_ps(&dst[i + 8], _mm_loadu_ps(&src[i + 8]));
			_mm_storeu_ps(&dst[i + 12], _mm_loadu_ps(&src[i + 12]));
		}
	}

}

/*
                      Warning !!
           Assumes that src and dest are unaligned on 16-bytes.
           Should be not any penalty for unaligned access by calling
           _mm_storeu_pd intrinsc function.
*/
template<const int N>  void  internal_system::FastSSEMemCpy<std::array<float, N>, 0>::sse_mem_cpy_arf328x(_In_ std::array<float, N>& src, _In_ std::array<float, N>& dst) {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_arf324x"));
#endif
	if (src.size() <= g_utils::L1D_SP_ELEMS) {
		// Prefetch L1D only.
		for (std::size_t i{ 0 }; i != src.size() - 32; i += 32){
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T0);
			_mm_storeu_ps(&dst[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dst[i + 4], _mm_loadu_ps(&src[i + 4]);
			_mm_storeu_ps(&dst[i + 8], _mm_loadu_ps(&src[i + 8]));
			_mm_storeu_ps(&dst[i + 12], _mm_loadu_ps(&src[i + 12]));
			_mm_storeu_ps(&dst[i + 16], _mm_loadu_ps(&src[i + 16]));
			_mm_storeu_ps(&dst[i + 20], _mm_loadu_ps(&src[i + 20]));
			_mm_storeu_ps(&dst[i + 24], _mm_loadu_ps(&src[i + 24]));
			_mm_storeu_ps(&dst[i + 28], _mm_loadu_ps(&src[i + 28]));
		}
	}
	else {
		// Prefetch to L2D only.
		// Use OpenMP for data sets larger than 1 << 24.
		omp_set_num_threads(4);
#pragma omp parallel for if(src.size() >= (1 << 24))
		for (std::size_t i{ 0 }; i != src.size() - 32; i += 32) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T1);
			_mm_storeu_ps(&dst[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dst[i + 4], _mm_loadu_ps(&src[i + 4]);
			_mm_storeu_ps(&dst[i + 8], _mm_loadu_ps(&src[i + 8]));
			_mm_storeu_ps(&dst[i + 12], _mm_loadu_ps(&src[i + 12]));
			_mm_storeu_ps(&dst[i + 16], _mm_loadu_ps(&src[i + 16]));
			_mm_storeu_ps(&dst[i + 20], _mm_loadu_ps(&src[i + 20]));
			_mm_storeu_ps(&dst[i + 24], _mm_loadu_ps(&src[i + 24]));
			_mm_storeu_ps(&dst[i + 28], _mm_loadu_ps(&src[i + 28]));
		}
	}
}

/*
                      Warning !!
            Assumes that src and dest are unaligned on 16-bytes.
            Should be not any penalty for unaligned access by calling
            _mm_storeu_pd intrinsc function.
*/
template<const int N>  void  internal_system::FastSSEMemCpy<std::array<double, N>, 0>::sse_mem_cpy_arf64(_In_ const std::array<double, N> &src, _Out_ std::array<double, N> &dst) {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_arf64"));
#endif
	if (src.size() <= g_utils::L1D_DP_ELEMS) {
		// Prefetch to L1D only.
		for (std::size_t i{ 0 }; i != src.size() - 4; i += 4) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T0);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
		}
	}
	else {
		//Prefetch to L2D
		for (std::size_t i{ 0 }; i != src.size() - 4; i += 4) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T1);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
		}
	}
}

/*
                             Warning !!
               Assumes that src and dest are unaligned on 16-bytes.
               Should be not any penalty for unaligned access by calling
              _mm_storeu_pd intrinsc function.
*/
template<const int N>  void  internal_system::FastSSEMemCpy<std::array<double, N>, 0>::sse_mem_cpy_arf644x(_In_ const std::array<double, N> &src, _In_ std::array<double, N> &dst) {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_arf644x"));
#endif
	if (src.size() <= g_utils::L1D_DP_ELEMS) {
		// Prefetch to L1D only.
		for (std::size_t i{ 0 }; i != src.size() - 8; i += 8) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i+2]), _MM_HINT_T0);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
			_mm_storeu_pd(&dst[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dst[i + 6], _mm_loadu_pd(&src[i + 6]));
		}
	}
	else {
		// Prefetch to L2D.
		for (std::size_t i{ 0 }; i != src.size() - 8; i += 8) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T1);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
			_mm_storeu_pd(&dst[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dst[i + 6], _mm_loadu_pd(&src[i + 6]));
		}
	}
}

/*
                         Warning !!
               Assumes that src and dest are unaligned on 16-bytes.
               Should be not any penalty for unaligned access by calling
               _mm_storeu_pd intrinsc function.
*/
template<const int N> void  internal_system::FastSSEMemCpy<std::array<double, N>, 0>::sse_mem_cpy_arf648x(_In_ const std::array<double, N> &src, _In_ std::array<double, N> &dst) {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_arf648x"));
#endif
	if (src.size() <= g_utils::L1D_DP_ELEMS) {
		// Prefetch to L1D only.
		for (std::size_t i{ 0 }; i != src.size() - 16; i += 16) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2], _MM_HINT_T0);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
			_mm_storeu_pd(&dst[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dst[i + 6], _mm_loadu_pd(&src[i + 6]));
			_mm_storeu_pd(&dst[i + 8], _mm_loadu_pd(&src[i + 8]));
			_mm_storeu_pd(&dst[i + 10], _mm_loadu_pd(&src[i + 10]));
			_mm_storeu_pd(&dst[i + 12], _mm_loadu_pd(&dst[i + 12]));
			_mm_storeu_pd(&dst[i + 14], _mm_loadu_pd(&dst[i + 14]));
		}
	}
	else {
		// Prefetch to L2D only.
		for (std::size_t i{ 0 }; i != src.size() - 16; i += 16) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T1);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
			_mm_storeu_pd(&dst[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dst[i + 6], _mm_loadu_pd(&src[i + 6]));
			_mm_storeu_pd(&dst[i + 8], _mm_loadu_pd(&src[i + 8]));
			_mm_storeu_pd(&dst[i + 10], _mm_loadu_pd(&src[i + 10]));
			_mm_storeu_pd(&dst[i + 12], _mm_loadu_pd(&src[i + 12]));
			_mm_storeu_pd(&dst[i + 14], _mm_loadu_pd(&src[i + 14]));
		}
	}
}

/*
                      Warning !!
            Assumes that src and dest are unaligned on 16-bytes.
            Should be not any penalty for unaligned access by calling
           _mm_storeu_pd intrinsc function.
*/
auto    internal_system::FastSSEMemCpy<std::vector<float>, 0>::sse_mem_cpy_vecf32(_In_ const std::vector<float> &src, _Out_ std::vector<float> &dst)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_vecf32"));
#endif
	if (src.size() <= g_utils::L1D_SP_ELEMS) {
		//Prefetch to L1D
		for (std::size_t i{ 0 }; i != src.size() - 8; i += 8) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T0);
			_mm_storeu_ps(&dst[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dst[i + 4], _mm_loadu_ps(&src[i + 4]));
		}
	}
	else {
		// Prefetch L2D only.
		for (std::size_t i{ 0 }; i != src.size() - 8; i += 8) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T1);
			_mm_storeu_ps(&dst[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dst[i + 4], _mm_loadu_ps(&src[i + 4]));
		}
	}
}

/*
                       Warning !!
           Assumes that src and dest are unaligned on 16-bytes.
           Should be not any penalty for unaligned access by calling
           _mm_storeu_pd intrinsc function.
*/
auto     internal_system::FastSSEMemCpy<std::vector<float>, 0>::sse_mem_cpy_vecf324x(_In_ const std::vector<float> &src, _In_ std::vector<float> &dst)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_vecf324x"));
#endif
	if (src.size() <= g_utils::L1D_SP_ELEMS) {
		// Prefetch to L1D only.
		for (std::size_t i{ 0 }; i != src.size() - 8; i += 16) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T0);
			_mm_storeu_ps(&dst[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dst[i + 4], _mm_loadu_ps(&src[i + 4]));
			_mm_storeu_ps(&dst[i + 8], _mm_loadu_ps(&src[i + 8]));
			_mm_storeu_ps(&dst[i + 12], _mm_loadu_ps(&src[i + 12]));
		}
	}
	else {
		// Prefetch to L2D
		for (std::size_t i{ 0 }; i != src.size() - 16; i += 16) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T1);
			_mm_storeu_ps(&dst[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dst[i + 4], _mm_loadu_ps(&src[i + 4]));
			_mm_storeu_ps(&dst[i + 8], _mm_loadu_ps(&src[i + 8]));
			_mm_storeu_ps(&dst[i + 12], _mm_loadu_ps(&src[i + 12]));
		}
	}
}

/*
                     Warning !!
             Assumes that src and dest are unaligned on 16-bytes.
             Should be not any penalty for unaligned access by calling
             _mm_storeu_pd intrinsc function.
*/
auto     internal_system::FastSSEMemCpy<std::vector<float>, 0>::sse_mem_cpy_vecf328x(_In_ const std::vector<float> &src, _Out_ std::vector<float> &dst)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_vecf328x"));
#endif
	if (src.size() <= g_utils::L1D_SP_ELEMS) {
		//Prefetch to L1D only
		for (std::size_t i{ 0 }; i != src.size() - 32; i += 32) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i]), _MM_HINT_T0);
			_mm_storeu_ps(&dst[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dst[i + 4], _mm_loadu_ps(&src[i + 4]));
			_mm_storeu_ps(&dst[i + 8], _mm_loadu_ps(&src[i + 8]));
			_mm_storeu_ps(&dst[i + 12], _mm_loadu_ps(&src[i + 12]));
			_mm_storeu_ps(&dst[i + 16], _mm_loadu_ps(&src[i + 16]));
			_mm_storeu_ps(&dst[i + 20], _mm_loadu_ps(&src[i + 20]));
			_mm_storeu_ps(&dst[i + 24], _mm_loadu_ps(&src[i + 24]));
			_mm_storeu_ps(&dst[i + 28], _mm_loadu_ps(&src[i + 28]));
		}
	}
	else {
		// Prefetch to L2D only.
		for (std::size_t i{ 0 }; i != src.size() - 32; i += 32) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i]), _MM_HINT_T1);
			_mm_storeu_ps(&dst[i], _mm_loadu_ps(&src[i]));
			_mm_storeu_ps(&dst[i + 4], _mm_loadu_ps(&src[i + 4]));
			_mm_storeu_ps(&dst[i + 8], _mm_loadu_ps(&src[i + 8]));
			_mm_storeu_ps(&dst[i + 12], _mm_loadu_ps(&src[i + 12]));
			_mm_storeu_ps(&dst[i + 16], _mm_loadu_ps(&src[i + 16]));
			_mm_storeu_ps(&dst[i + 20], _mm_loadu_ps(&src[i + 20]));
			_mm_storeu_ps(&dst[i + 24], _mm_loadu_ps(&src[i + 24]));
			_mm_storeu_ps(&dst[i + 28], _mm_loadu_ps(&src[i + 28]));
		}
	}
}

/*
                        Warning !!
        Assumes that src and dest are unaligned on 16-bytes.
        Should be not any penalty for unaligned access by calling
       _mm_storeu_pd(ps) intrinsc function.
*/
auto     internal_system::FastSSEMemCpy<std::vector<double>, 0>::sse_mem_cpy_vecf64(_In_ const std::vector<double> &src, _Out_ std::vector<double> &dst)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_vecf64"));
#endif
	if (src.size() <= g_utils::L1D_DP_ELEMS) {
		// Prefetch to L1D only.
		for (std::size_t i{ 0 }; i != src.size() - 4; i += 4) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T0);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
		}
	}
	else {
		// Prefetch to L2D only.
		for (std::size_t i{ 0 }; i != src.size() - 4; i += 4) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T1);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
		}
	}
}

/*
                      Warning !!
            Assumes that src and dest are unaligned on 16-bytes.
            Should be not any penalty for unaligned access by calling
            _mm_storeu_pd(ps) intrinsc function.
*/
auto     internal_system::FastSSEMemCpy<std::vector<double>, 0>::sse_mem_cpy_vecf644x(_In_ const std::vector<double> &src, _Out_ std::vector<double> &dst)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_vecf644x"));
#endif
	if (src.size() <= g_utils::L1D_DP_ELEMS) {
		// Prefetch to L1D only.
		for (std::size_t i{ 0 }; i != src.size() - 8; i += 8) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T0);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
			_mm_storeu_pd(&dst[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dst[i + 6], _mm_loadu_pd(&src[i + 6]));
		}
	}
	else {
		// Prefetch to L2D only.
		for (std::size_t i{ 0 }; i != src.size() - 8; i += 8) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T1);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
			_mm_storeu_pd(&dst[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dst[i + 6], _mm_loadu_pd(&src[i + 6]));
		}
	}
}

/*
                    Warning !!
            Assumes that src and dest are unaligned on 16-bytes.
            Should be not any penalty for unaligned access by calling
           _mm_storeu_pd(ps) intrinsc function.
*/
auto      internal_system::FastSSEMemCpy<std::vector<double>, 0>::sse_mem_cpy_vecf648x(_In_ const std::vector<double> &src, _Out_ std::vector<double> &dst)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst);
#else
	g_utils::check_args(src, dest, std::string("Invalid argument(s) in sse_mem_cpy_vecf648x"));
#endif
	if (src.size() <= g_utils::L1D_DP_ELEMS) {
		// Prefetch to L1D only.
		for (std::size_t i{ 0 }; i != src.size() - 16; i += 16) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T0);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
			_mm_storeu_pd(&dst[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dst[i + 6], _mm_loadu_pd(&src[i + 6]));
			_mm_storeu_pd(&dst[i + 8], _mm_loadu_pd(&src[i + 8]));
			_mm_storeu_pd(&dst[i + 10], _mm_loadu_pd(&src[i + 10]));
			_mm_storeu_pd(&dst[i + 12], _mm_loadu_pd(&src[i + 12]));
			_mm_storeu_pd(&dst[i + 14], _mm_loadu_pd(&src[i + 14]));
		}
	}
	else {
		// Prefetch to L2D only.
		for (std::size_t i{ 0 }; i != src.size() - 16; i += 16) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			Compiler warning will be issued.*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T1);
			_mm_storeu_pd(&dst[i], _mm_loadu_pd(&src[i]));
			_mm_storeu_pd(&dst[i + 2], _mm_loadu_pd(&src[i + 2]));
			_mm_storeu_pd(&dst[i + 4], _mm_loadu_pd(&src[i + 4]));
			_mm_storeu_pd(&dst[i + 6], _mm_loadu_pd(&src[i + 6]));
			_mm_storeu_pd(&dst[i + 8], _mm_loadu_pd(&src[i + 8]));
			_mm_storeu_pd(&dst[i + 10], _mm_loadu_pd(&src[i + 10]));
			_mm_storeu_pd(&dst[i + 12], _mm_loadu_pd(&src[i + 12]));
			_mm_storeu_pd(&dst[i + 14], _mm_loadu_pd(&src[i + 14]));
		}
	}
}
