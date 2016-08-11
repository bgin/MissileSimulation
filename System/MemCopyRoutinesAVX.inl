
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
C++ structs templated on primitive and some of STL container data types -  implementation.
Memory copy routines based on AVX SIMD.
@file MemCopyRoutinesAVX.inl
@author: Bernard Gingold
@version:  1.0.0  25/12/2015
@description: MemCopyRoutinesAVX.h
@reference: none



*/

/*************************************
    Memory Copy routines
	No cache bypass in use.
*************************************/

template<typename T, const int N>   std::enable_if<std::is_pointer<T>::value, void>::type
internal_system::FastAVXMemCpy<T, N>::avx_mem_cpy2x(_In_ const T* __restrict src, _Outptr_ T* __restrict dst, _In_ const int Len) {
#if defined _DEBUG
	_ASSERTE((src != nullptr) && (dst != nullptr) && (Len != 0));
#else
	if ((src == nullptr) || (dst == nullptr) || (Len <= 0))
		throw std::runtime_error(std::string("Invalid input in:") + typeid(FastAVXMemCpy<T, N>).name() + std::string("::avx_mem_cpy_2x\n"));
#endif
	for (int i{ 0 }; i != Len - 2; i += 2) {

		dst[i] = src[i];
		dst[i + 1] = src[i + 1];
	}
}

template<typename T, const int N>  std::enable_if<std::is_pointer<T>::value, void>::type
internal_system::FastAVXMemCpy<T, N>::avx_mem_cpy4x(_In_ const T* __restrict src, _Outptr_ T* __restrict dst, _In_ const int Len) {
#if defined _DEBUG
	_ASSERTE((src != nullptr) && (dst != nullptr) && (Len != 0))
#else
	if((src == nullptr) || (dst == nullptr) || (Len <= 0))
		throw std::runtime_error(std::string("Invalid input in: ") + typeid(FastAVXMemCpy<T, N>).name() + std::string("::avx_mem_cpy_4x\n"));
#endif
	for (int i{ 0 }; i != Len - 4; i += 4) {

		dst[i] = src[i];
		dst[i + 1] = src[i + 1];
		dst[i + 2] = src[i + 2];
		dst[i + 3] = src[i + 3];
	}
}

template<typename T, const int N> std::enable_if<std::is_pointer<T>::value, void>::type
internal_system::FastAVXMemCpy<T, N>::avx_mem_cpy8x(_In_ const T* __restrict src, _Outptr_ T* __restrict dst, _In_ const int Len) {
#if defined _DEBUG
	_ASSERTE((src != nullptr) && (dst != nullptr) && (Len != 0))
#else
	if((src == nullptr) || (dst == nullptr) || (Len <= 0))
		throw std::runtime_error(std::string("Invalid input in: ") + typeid(FastAVXMemCpy<T, N>).name() + std::string("::avx_mem_cpy_8x\n"));
#endif
	for (int i{ 0 }; != Len - 8; i += 8) {

		dst[i] = src[i];
		dst[i + 1] = src[i + 1];
		dst[i + 2] = src[i + 2];
		dst[i + 3] = src[i + 3];
		dst[i + 4] = src[i + 4];
		dst[i + 5] = src[i + 5];
		dst[i + 6] = src[i + 6];
		dst[i + 7] = src[i + 7];
	}
}

#if defined SYSTEM_USE_OPENMP
template<typename T, const int N> std::enable_if<std::is_pointer<T>::value, void>::type
internal_system::FastAVXMemCpy<T, N>::avx_mem_cpy_omp(_In_ const T* __restrict src, _Outptr_ T* __restrict dst, _In_ const int Len, _In_ const int nThreads) {
#if defined _DEBUG
	_ASSERTE((src != nullptr) && (dst != nullptr) && (Len != 0));
#else
	if((src == nullptr) || (dst == nullptr) || (Len <= 0))
		throw std::runtime_error(std::string("Invalid input in: ") + typeid(FastAVXMemCpy<T, N>).name() + std::string("::avx_mem_cpy_omp\n"));
#endif
	::omp_set_num_threads(nThreads);
#pragma omp parallel for
	for (int i = 0; i < Len; ++i)
		dst[i] = src[i];
}
#endif

/***********************************************
     Vectorised versions of FastAVXMemCpy
	 functions.
	              ***Warning!!***
	 Caller must assure than array's Len variable
	 is modulo divisable by 32
************************************************/

auto  internal_system::FastAVXMemCpy<float, 0>::avx_mem_cpy_f32(_In_ const float* __restrict src, _Outptr_ float* __restrict dst, _In_ const int Len)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst, Len);
#else
	g_utils::check_args(src, dst, Len, std::string("Invalid input in: ") + typeid(FastAVXMemCpy<float, 0>).name() + std::string("::avx_mem_cpy_f32\n"));
#endif
	if (Len <= g_utils::L1D_SP_ELEMS) {
		// Prefetch to L1D only
		for (int i{ 0 }; i != Len - 8; i += 8) {
			/* Probably compiler will vectorise
			this code because there is no Flow
			dependency*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T0);
			_mm256_storeu_ps(&dst[i], _mm256_loadu_ps(&src[i]));
		}
	}
	else {
		/* Prefetch to L2 */
		for (int i{ 0 }; i != Len - 8; i += 8) {
			/* Probably compiler will vectorise
			this code because there is no Flow
			dependency*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 2]), _MM_HINT_T1);
			_mm256_storeu_ps(&dst[i], _mm256_loadu_ps(&src[i]));
		}
	}
}

/*************************************************
                   ***Warning!!***
	 Caller must assure than array's Len variable
	 is modulo divisable by 32
*************************************************/
auto  internal_system::FastAVXMemCpy<float, 0>::avx_mem_cpy_f324x(_In_ const float* __restrict src, _Outptr_ float* __restrict dst, _In_ const int Len)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst, Len);
#else
	g_utils::check_args(src, dst, Len, std::string("Invalid input in: ") + typeid(FastAVXMemCpy<float, 0>).name() + std::string("::avx_mem_cpy_f324x\n"));
#endif
	if (Len <= g_utils::L1D_SP_ELEMS) {
		/* Prefetch to L1D only */
		for (int i{ 0 }; i != Len - 32; i += 32) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 4]), _MM_HINT_T0);
			_mm256_storeu_ps(&dst[i], _mm256_loadu_ps(&src[i]));
			_mm256_storeu_ps(&dst[i + 8], _mm256_loadu_ps(&src[i + 8]));
			_mm256_storeu_ps(&dst[i + 16], _mm256_loadu_ps(&src[i + 16]));
			_mm256_storeu_ps(&dst[i + 24], _mm256_loadu_ps(&src[i + 24]));
		}
	
	}
	else {
		/* Prefetch to L2 and L3*/
		for (int i{ 0 }; i != Len - 32; i += 32) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 4]), _MM_HINT_T1 | _MM_HINT_T2);
			_mm256_storeu_ps(&dst[i], _mm256_loadu_ps(&src[i]));
			_mm256_storeu_ps(&dst[i + 8], _mm256_loadu_ps(&src[i + 8]));
			_mm256_storeu_ps(&dst[i + 16], _mm256_loadu_ps(&src[i + 16]));
			_mm256_storeu_ps(&dst[i + 24], _mm256_loadu_ps(&src[i + 24]));
		}
	}
}

/*************************************************
            ***Warning!!***
       Caller must assure than array's Len variable
       is modulo divisable by 32
*************************************************/
auto   internal_system::FastAVXMemCpy<float, 0>::avx_mem_cpy_f328x(_In_ const float* __restrict src, _Outptr_ float* __restrict dst, _In_ const int Len)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst, Len);
#else
	g_utils::check_args(src, dst, Len, std::string("Invalid input in: ") + typeid(FastAVXMemCpy<float, 0>).name() + std::string("::avx_mem_cpy_f328x\n"));
#endif
	if (Len <= g_utils::L1D_SP_ELEMS) {
		/* Prefetch to L1D only */
		for (int i{ 0 }; i != Len - 64; i += 64) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i]), _MM_HINT_T0);
			_mm256_storeu_ps(&dst[i], _mm256_loadu_ps(&src[i]));
			_mm256_storeu_ps(&dst[i + 8], _mm256_loadu_ps(&src[i + 8]));
			_mm256_storeu_ps(&dst[i + 16], _mm256_loadu_ps(&src[i + 16]));
			_mm256_storeu_ps(&dst[i + 24], _mm256_loadu_ps(&src[i + 24]));
			_mm256_storeu_ps(&dst[i + 32], _mm256_loadu_ps(&src[i + 32]));
			_mm256_storeu_ps(&dst[i + 40], _mm256_loadu_ps(&src[i + 40]));
			_mm256_storeu_ps(&dst[i + 48], _mm256_loadu_ps(&src[i + 48]));
			_mm256_storeu_ps(&dst[i + 56], _mm256_loadu_ps(&src[i + 56]));
		}
	}
	else {
		/* Prefetch to L2 */
		for (int i{ 0 }; i != Len - 64; i += 64) {
			/*  Bear in mind that ICC probably will not vectorise
			*  further this loop mainly because of flow dependence
			*   [i], [i + n] on the next iteration.
			*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i]), _MM_HINT_T1);
			_mm256_storeu_ps(&dst[i], _mm256_loadu_ps(&src[i]));
			_mm256_storeu_ps(&dst[i + 8], _mm256_loadu_ps(&src[i + 8]));
			_mm256_storeu_ps(&dst[i + 16], _mm256_loadu_ps(&src[i + 16]));
			_mm256_storeu_ps(&dst[i + 24], _mm256_loadu_ps(&src[i + 24]));
			_mm256_storeu_ps(&dst[i + 32], _mm256_loadu_ps(&src[i + 32]));
			_mm256_storeu_ps(&dst[i + 40], _mm256_loadu_ps(&src[i + 40]));
			_mm256_storeu_ps(&dst[i + 48], _mm256_loadu_ps(&src[i + 48]));
			_mm256_storeu_ps(&dst[i + 56], _mm256_loadu_ps(&src[i + 56]));
		}
	}
}

/*************************************************
                ***Warning!!***
       Caller must assure than array's Len variable
       is modulo divisable by 32
*************************************************/
#if defined SYSTEM_USE_OPENMP
auto   internal_system::FastAVXMemCpy<float, 0>::avx_mem_cpy_f32_omp(_In_ const float* __restrict src, _Outptr_ float* __restrict dst, _In_ const int Len, _In_ const int nThreads)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst, Len);
#else
	g_utils::check_args(src, dst, Len, std::string("Invalid input in: ") + typeid(FastAVXMemCpy<float, 0>).name() + std::string("::avx_mem_cpy_f32_omp\n"));
#endif
	::omp_set_num_threads(nThreads);
#pragma omp parallel for
	for (int i = 0; i < Len - 8; i += 8)
		_mm256_storeu_ps(&dst[i], _mm256_loadu_ps(&src[i]));
}
#endif

/*************************************************
                    ***Warning!!***
         Caller must assure than array's Len variable
            is modulo divisable by 32
*************************************************/

auto  internal_system::FastAVXMemCpy<double, 0>::avx_mem_cpy_f64(_In_ const double* __restrict src, _Outptr_ double* __restrict dst, _In_ const int Len)->void {
#if defined _DEBUG
	g_utils::dbg_asserte(src, dst, Len);
#else
	g_utils::check_args(src, dst, Len, std::string("Invalid input in: ") + typeid(FastAVXMemCpy<double, 0>).name() + std::string("::avx_mem_cpy_f64\n"));
#endif
	if (Len <= g_utils::L1D_DP_ELEMS) {
		/* Prefetch to L1D only */
		for (int i{ 0 }; i != Len - 4; i += 4) {
			/* Probably compiler will vectorise
			this code because there is no Flow
			dependency*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 4]), _MM_HINT_T0);
			_mm256_storeu_pd(&dst[i], _mm256_loadu_pd(&src[i]));
		}
	}
	else {
		/* Prefetch to L2  */
		for (int i{ 0 }; i != Len - 4; i += 4) {
			/* Probably compiler will vectorise
			this code because there is no Flow
			dependency*/
			_mm_prefetch(reinterpret_cast<const char*>(&src[i + 4]), _MM_HINT_T1);
			_mm256_storeu_pd(&dst[i], _mm256_loadu_pd(&src[i]));
		}
	}
	
}

/*************************************************
                ***Warning!!***
     Caller must assure than array's Len variable
      is modulo divisable by 32
*************************************************/
