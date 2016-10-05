
#ifndef __SLICOT_AB05MD_H__
#define __SLICOT_AB05MD_H__

//File version granularity
#ifndef SLICOT_AB05MD_VERSION_MAJOR
#define SLICOT_AB05MD_VERSION_MAJOR 1
#endif

#ifndef SLICOT_ABO5MD_VERSION_MINOR
#define SLICOT_AB05MD_VERSION_MINOR 0
#endif

#ifndef SLICOT_AB05MD_PATCH_VERSION
#define SLICOT_AB05MD_PATCH_VERSION 0
#endif

#ifndef SLICOT_AB05MD_CREATE_DATE
#define SLICOT_AB05MD_CREATE_DATE "Date: 30-09-2016 , Time: 11:50 AM GMT+2"
#endif

// Set this value to successful build date/time.
#ifndef SLICOT_AB05MD_BUILD_DATE
#define SLICOT_AB05MD_BUILD_DATE ""
#endif

#ifndef SLICOT_AB05MD_AUTHOR
#define SLICOT_AB05MD_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif


#include "Slicot_F77_Interface.h"
#include "std_headers.h"
#include "Config.h"



namespace guidance {
	namespace slicot_wrappers {



		template<typename R64 = double,
				 typename I32 = int,
				 typename UC8 = unsigned char>  struct F77_AB05MD {


					 /*******************************
					   Constructors and Destructor.
					 ********************************/

					 /*
					   @Purpose:
									Default Constructor explicitly default.
									Notice: 
									         Must not be used directly.
					 */
					 F77_AB05MD() = default;

					 /*
					   @Purpose:
									1st "main" Constructor responsible for
									scalar and array member initialization
									and memory allocation. Array members
									are zero-initialized. 
									Input arrays upon call to F77 subroutine
									should be set to specific value be external
									routine.
					 */
					 F77_AB05MD(_In_ const UC8 UPLO,
						 _In_ const UC8 OVER,
						 _In_ const I32 N1,
						 _In_ const I32 M1,
						 _In_ const I32 P1,
						 _In_ const I32 N2,
						 _In_ const I32 P2,
						 _In_ const I32 LDA1,
						 _In_ const I32 LDB1,
						 _In_ const I32 LDC1,
						 _In_ const I32 LDD1,
						 _In_ const I32 LDA2,
						 _In_ const I32 LDB2,
						 _In_ const I32 LDC2,
						 _In_ const I32 LDD2,
						 _In_ const I32 N,
						 _In_ const I32 LDA,
						 _In_ const I32 LDB,
						 _In_ const I32 LDC,
						 _In_ const I32 LDD,
						 _In_ const I32 LDWORK,
						 _In_ const I32 INFO)
						 :
					 m_UPLO{ UPLO },
					 m_OVER{ OVER },
					 m_N1{ N1 },
					 m_M1{ M1 },
					 m_P1{ P1 },
					 m_N2{ N2 },
					 m_P2{ P2 },
					 m_LDA1{ LDA1 },
					 m_A1{ new R64[m_LDA1 * m_N1] },
					 m_LDB1{ LDB1 },
					 m_B1{ new R64[m_LDB1 * m_M1] },
					 m_LDC1{ LDC1 },
					 m_C1{ new R64[m_LDC1 * m_N1] },
					 m_LDD1{ LDD1 },
					 m_D1{ new R64[m_LDD1 * m_M1] },
					 m_LDA2{ LDA2 },
					 m_A2{ new R64[m_LDA2 * m_N2] },
					 m_LDB2{ LDB2 },
					 m_B2{ new R64[m_LDB2 * m_P1] },
					 m_LDC2{ LDC2 },
					 m_C2{ new R64[m_LDC2 * m_N2] },
					 m_LDD2{ LDD2 },
					 m_D2{ new R64[m_LDD2 * m_P1] },
					 m_N{ N },
					 m_LDA{ LDA },
					 m_A{ new R64[m_LDA * (m_N1 + m_N2)] },
					 m_LDB{ LDB },
					 m_B{ new R64[m_LDB * m_M1] },
					 m_LDC{ LDC },
					 m_C{ new R64[m_LDC * (m_N1 + m_N2)] },
					 m_LDD{ LDD },
					 m_D{ new R64[m_LDD * m_M1] },
					 m_LDWORK{ LDWORK },
					 m_DWORK{ new R64[m_LDWORK] },
					 m_INFO{ INFO } {

						 if (this->m_A1){
							 for (int i{ 0 }; i != this->m_LDA1; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif

								 for (int j{ 0 }; j != this->m_N1; ++j) {
									 this->m_A1[i + this->m_LDA1 * j] = 0.0;
								 }
							 }
						 }
						 else {
							 std::cerr << __DATE__ << ":" << __TIME__ << " FATAL ERROR: Invalid pointer in F77_AB05MD !!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "**** ERROR DETAILS ****\n";
							 std::cerr << "Value of m_A1=" << std::hex << "0x" << this->m_A1 << "\n";
							 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
							 std::exit(-1);
						 }
						 if (this->m_B1) {
							 for (int i{ 0 }; i != this->m_LDB1; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
								 for (int j{ 0 }; j != this->m_M1; ++j) {
									 this->m_B1[i + this->m_LDB1 * j] = 0.0;
								 }
							 }
						 }
						 else {
							 std::cerr << __DATE__ << ":" << __TIME__ << " FATAL ERROR: Invalid pointer in F77_AB05MD !!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "**** ERROR DETAILS ****\n";
							 std::cerr << "Value of m_B1=" << std::hex << "0x" << this->m_B1 << "\n";
							 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
							 std::exit(-1);
						 }
						 if (this->m_C1) {
							 for (int i{ 0 }; i != this->m_LDC1; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
								 for (int j{ 0 }; j != this->m_N1; ++j) {
									 this->m_C1[i + this->m_LDC1 * j] = 0.0;
								 }
							 }
						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in F77_AB05MD !!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "**** ERROR DETAILS ****\n";
							 std::cerr << "Value of m_C1=" << std::hex << "0x" << this->m_C1 << "\n";
							 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
							 std::exit(-1);
						 }
						 if (this->m_D1) {
							 for (int i{ 0 }; i != this->m_LDD1; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
								 for (int j{ 0 }; j != this->m_M1; ++j) {
									 this->m_D1[i + this->m_LDD1 * j] = 0.0;
								 }
							 }
						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in F77_AB05MD !!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "**** ERROR DETAILS ****\n";
							 std::cerr << "Value of m_D1=" << std::hex << "0x" << this->m_D1 << "\n";
							 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
							 std::exit(-1);
						 }
						 if (this->m_A2) {
							 for (int i{ 0 }; i != this->m_LDA2; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
								 for (int j{ 0 }; j != this->m_N2; ++j) {
									 this->m_A2[i + this->m_LDA2 * j] = 0.0;
								 }
							 }
						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in F77_AB05MD !!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "**** ERROR DETAILS ****\n";
							 std::cerr << "Value of m_A2=" << std::hex << "0x" << this->m_A2 << "\n";
							 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
							 std::exit(-1);
						 }
						 if (this->m_B2) {
							 for (int i{ 0 }; i != this->m_LDB2; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
								 for (int j{ 0 }; j != this->m_P1; ++j) {
									 this->m_B2[i + this->m_LDB2 * j] = 0.0;
								 }
							 }
						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in F77_AB05MD !!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "**** ERROR DETAILS ****\n";
							 std::cerr << "Value of m_B2=" << std::hex << "0x" << this->m_B2 << "\n";
							 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
							 std::exit(-1);
						 }
						 if (this->m_C2) {
							 for (int i{ 0 }; i != this->m_LDC2; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
								 for (int j{ 0 }; j != this->m_N2; ++j) {
									 this->m_C2[i + this->m_LDC2 * j] = 0.0;
								 }
							 }
						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in F77_AB05MD !!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "**** ERROR DETAILS ****\n";
							 std::cerr << "Value of m_C2=" << std::hex << "0x" << this->m_C2 << "\n";
							 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
							 std::exit(-1);
						 }
						 if (this->m_D2) {
							 for (int i{ 0 }; i != this->m_LDD2; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
								 for (int j{ 0 }; j != this->m_P1; ++j) {
									 this->m_D2[i + this->m_LDD2 * j] = 0.0;
								 }
							 }
						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in F77_AB05MD !!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "**** ERROR DETAILS ****\n";
							 std::cerr << "Value of m_D2=" << std::hex << "0x" << this->m_D2 << "\n";
							 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
							 std::exit(-1);
						 }
						 if (this->m_A) {
							 for (int i{ 0 }; i != this->m_LDA; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
								 for (int j{ 0 }; j != (this->m_N1 + this->m_N2); ++j) {
									 this->m_A[i + this->m_LDA * j] = 0.0;
								 }
							 }
						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in F77_AB05MD !!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "**** ERROR DETAILS ****\n";
							 std::cerr << "Value of m_A=" << std::hex << "0x" << this->m_A << "\n";
							 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
							 std::exit(-1);
						 }
						 if (this->m_B) {
							 for (int i{ 0 }; i != this->m_LDB; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
								 for (int j{ 0 }; j != this->m_M1; ++j) {
									 this->m_B[i + this->m_LDB * j] = 0.0;
								 }
							 }
						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in F77_AB05MD !!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "**** ERROR DETAILS ****\n";
							 std::cerr << "Value of m_B=" << std::hex << "0x" << this->m_B << "\n";
							 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
							 std::exit(-1);
						 }
						 if (this->m_C) {
							 for (int i{ 0 }; i != this->m_LDC; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
								 for (int j{ 0 }; j != (this->m_N1 + this->m_N2); ++j) {
									 this->m_C[i + this->m_LDC * j] = 0.0;
								 }
							 }
						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in F77_AB05MD !!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "**** ERROR DETAILS ****\n";
							 std::cerr << "Value of m_C=" << std::hex << "0x" << this->m_C << "\n";
							 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
							 std::exit(-1);
						 }
						 if (this->m_D) {
							 for (int i{ 0 }; i != this->m_LDD; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
								 for (int j{ 0 }; j != this->m_M1; ++j) {
									 this->m_D[i + this->m_LDD * j] = 0.0;
								 }
							 }
						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in F77_AB05MD !!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "**** ERROR DETAILS ****\n";
							 std::cerr << "Value of m_D=" << std::hex << "0x" << this->m_D << "\n";
							 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
							 std::exit(-1);
						 }
						 if (this->m_DWORK) {
							 for (int i{ 0 }; i != this->m_LDWORK; ++i) {
								 this->m_DWORK[i] = 0.0;
							 }
						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in F77_AB05MD !!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "**** ERROR DETAILS ****\n";
							 std::cerr << "Value of m_DWORK=" << std::hex << "0x" << this->m_DWORK << "\n";
							 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
							 std::exit(-1);
						 }
			 }

			         /*
					   @Purpose:
								2nd "main" Constructor which is responsible
								for initialization of scalar and array members.
								Client code is responsible for proper initia-
								lization of system input array which are
								hereafter copied to array members.
			         */
			 F77_AB05MD(_In_ const UC8 UPLO,
					    _In_ const UC8 OVER,
				        _In_ const I32 N1,
				        _In_ const I32 M1,
				        _In_ const I32 P1,
				        _In_ const I32 N2,
				        _In_ const I32 P2,
				        _In_ const I32 LDA1,
				        _In_ R64* __restrict A1,
				        _In_ const I32 LDB1,
				        _In_ R64* __restrict B1,
				        _In_ const I32 LDC1,
				        _In_ R64* __restrict C1,
				        _In_ const I32 LDD1,
				        _In_ R64* __restrict D1,
				        _In_ const I32 LDA2,
				        _In_ R64* __restrict A2,
				        _In_ const I32 LDB2,
				        _In_ R64* __restrict B2,
				        _In_ const I32 LDC2,
				        _In_ R64* __restrict C2,
				        _In_ const I32 LDD2,
				        _In_ R64* __restrict D2,
				        _In_ const I32 N,
				        _In_ const I32 LDA,
				        _In_ const I32 LDB,
				        _In_ const I32 LDC,
				        _In_ const I32 LDD,
				        _In_ const I32 LDWORK,
				        _In_ const I32 INFO)
				 :
			     m_UPLO{ UPLO },
				 m_OVER{ OVER },
				 m_N1{ N1 },
				 m_M1{ M1 },
				 m_P1{ P1 },
				 m_N2{ N2 },
				 m_P2{ P2 },
				 m_LDA1{ LDA1 },
				 m_A1{ new R64[m_LDA1 * m_N1] },
				 m_LDB1{ LDB1 },
				 m_B1{ new R64[m_LDB1 * m_M1] },
				 m_LDC1{ LDC1 },
				 m_C1{ new R64[m_LDC1 * m_N1] },
				 m_LDD1{ LDD1 },
				 m_D1{ new R64[m_LDD1 * m_M1] },
				 m_LDA2{ LDA2 },
				 m_A2{ new R64[m_LDA2 * m_N2] },
				 m_LDB2{ LDB2 },
				 m_B2{ new R64[m_LDB2 * m_P1] },
				 m_LDC2{ LDC2 },
				 m_C2{ new R64[m_LDC2 * m_N2] },
				 m_LDD2{ LDD2 },
				 m_D2{ new R64[m_LDD2 * m_P1] },
				 m_N{ N },
				 m_LDA{ LDA },
				 m_A{ new R64[m_LDA * (m_N1 + m_N2)] },
				 m_LDB{ LDB },
				 m_B{ new R64[m_LDB * m_M1] },
				 m_LDC{ LDC },
				 m_C{ new R64[m_LDC * (m_N1 + m_N2)] },
				 m_LDD{ LDD },
				 m_D{ new R64[m_LDD * m_M1] },
				 m_LDWORK{ LDWORK },
				 m_DWORK{ new R64[m_LDWORK] },
				 m_INFO{ INFO } {

				 if (this->m_A1 && A1) {
					 for (int i{ 0 }; i != this->m_LDA1; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch A1:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_N1; ++j) {
							 this->m_A1[i + this->m_LDA1 * j] = A1[i + this->m_LDA1 * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in 2nd Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 this->m_A1 == nullptr ? std::cerr << "m_A1 contains invalid memory address: " << std::hex << "0x" << m_A1 << "\n" : 
						 std::cerr << "m_A1 contains valid memory address: " << std::hex << "0x" << m_A1 << "\n";
					 A1 == nullptr ? std::cerr << "A1 contains invalid memory address: " << std::hex << "0x" << A1 << "\n" : 
						 std::cerr << "A1 contains valid memory address: " << std::hex << "0x" << A1 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_B1 && B1) {
					 for (int i{ 0 }; i != this->m_LDB1; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch B1:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_M1; ++j) {
							 this->m_B1[i + this->m_LDB1 * j] = B1[i + this->m_LDB1 * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in 2nd Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 this->m_B1 == nullptr ? std::cerr << "m_B1 contains invalid memory address: " << std::hex << "0x" << m_B1 << "\n" : 
						 std::cerr << "m_B1 contains valid memory address: " << std::hex << "0x" << m_B1 << "\n";
					 B1 == nullptr ? std::cerr << "B1 contains invalid memory address: " << std::hex << "0x" << B1 << "\n" : 
						 std::cerr << "B1 contains valid memory address: " << std::hex << "0x" << B1 << "\n";
					 std::cerr << "Cannot recover -- calling exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_C1 && C1) {
					 for (int i{ 0 }; i != this->m_LDC1; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch C1:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_N1; ++j) {
							 this->m_C1[i + this->m_LDC1 * j] = C1[i + this->m_LDC1 * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in 2nd Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 this->m_C1 == nullptr ? std::cerr << "m_C1 contains invalid memory address: " << std::hex << "0x" << m_C1 << "\n" : 
											 std::cerr << "m_C1 contains valid memory address: " << std::hex << "0x" << m_C1 << "\n";
					 C1 == nullptr ? std::cerr << "C1 contains invalid memory address: " << std::hex << "0x" << C1 << "\n" : 
									 std::cerr << "C1 contains valid memory address: " << std::hex << "0x" << C1 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_D1 && D1) {
					 for (int i{ 0 }; i != this->m_LDD1; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch D1:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_M1; ++j) {
							 this->m_D1[i + this->m_LDD1 * j] = D1[i + this->m_LDD1 *j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in 2nd Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 this->m_D1 == nullptr ? std::cerr << "m_D1 contains invalid memory address: " << std::hex << "0x" << m_D1 << "\n" : 
						 std::cerr << "m_D1 contains valid memory address: " << std::hex << "0x" << m_D1 << "\n";
					 D1 == nullptr ? std::cerr << "D1 contains invalid memory address: " << std::hex << "0x" << D1 << "\n" : 
						 std::cerr << "D1 contains valid memory address: " << std::hex << "0x" << D1 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_A2 && A2) {
					 for (int i{ 0 }; i != this->m_LDA2; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch A2:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_N2; ++j) {
							 this->m_A2[i + this->m_LDA2 * j] = A2[i + this->m_LDA2 * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in 2nd Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 this->m_A2 == nullptr ? std::cerr << "m_A2 contains invalid memory address: " << std::hex << "0x" << m_A2 << "\n" : 
						 std::cerr << "m_A2 contains valid memory address: " << std::hex << "0x" << m_A2 << "\n";
					 A2 == nullptr ? std::cerr << "A2 contains invalid memory address: " << std::hex << "0x" << A2 << "\n" : 
						 std::cerr << "A2 contains valid memory address: " << std::hex << "0x" << A2 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_B2 && B2) {
					 for (int i{ 0 }; i != this->m_LDB2; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch B2:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_P1; ++j) {
							 this->m_B2[i + this->m_LDB2 * j] = B2[i + this->m_LDB2 * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in 2nd Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 this->m_B2 == nullptr ? std::cerr << "m_B2 contains invalid memory address: " << std::hex << "0x" << m_B2 << "\n" : 
						 std::cerr << "m_B2 contains valid memory address: " << std::hex << "0x" << m_B2 << "\n";
					 B2 == nullptr ? std::cerr << "B2 contains invalid memory address: " << std::hex << "0x" << B2 << "\n" : 
						 std::cerr << "B2 contains valid memory address: " << std::hex << "0x" << B2 << "\n";
					 std::cerr << "Cannot recover -- calling std::hex(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_C2 && C2) {
					 for (int i{ 0 }; i != this->m_LDC2; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch C2:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_N2; ++j) {
							 this->m_C2[i + this->m_LDC2 * j] = C2[i + this->m_LDC2 * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in 2nd Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 this->m_C2 == nullptr ? std::cerr << "m_C2 contains invalid memory address: " << std::hex << "0x" << m_C2 << "\n" : 
						                     std::cerr << "m_C2 contains valid memory address: " << std::hex << "0x" << m_C2 << "\n";
					 C2 == nullptr ? std::cerr << "C2 contains invalid memory address: " << std::hex << "0x" << C2 << "\n" : 
									 std::cerr << "C2 contains valid memory address: " << std::hex << "0x" << C2 << "\n";
					 std::cerr << "Cannot recover -- calling std::hex(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_D2 && D2) {
					 for (int i{ 0 }; i != this->m_LDD2; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch D2:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_P1; ++j) {
							 this->m_D2[i + this->m_LDD2 * j] = D2[i + this->m_LDD2 * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in 2nd Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 this->m_D2 == nullptr ? std::cerr << "m_D2 contains invalid memory address: " << std::hex << "0x" << m_D2 << "\n" : 
						 std::cerr << "m_D2 contains valid memory address: " << std::hex << "0x" << m_D2 << "\n";
					 D2 == nullptr ? std::cerr << "D2 contains invalid memory address: " << std::hex << "0x" << D2 << "\n" : 
						 std::cerr << "D2 contains valid memory address: " << std::hex << "0x" << D2 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_A) {
					 for (int i{ 0 }; i != this->m_LDA; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif

						 for (int j{ 0 }; j != (this->m_N1 + this->m_N2); ++j) {
							 this->m_A[i + this->m_LDA * j] = 0.0;
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in 2nd Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 this->m_A == nullptr ? std::cerr << "m_A contains invalid memory address: " << std::hex << "0x" << m_A << "\n" : 
											std::cerr << "m_A contains valid memory address: " << std::hex << "0x" << m_A << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_B) {
					 for (int i{ 0 }; i != this->m_LDB; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
						 for (int j{ 0 }; j != this->m_M1; ++j) {
							 this->m_B[i + this->m_LDB * j] = 0.0;
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in 2nd Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 this->m_B == nullptr ? std::cerr << "m_B contains invalid memory address: " << std::hex << "0x" << m_B << "\n" :
						 std::cerr << "m_B contains valid memory address: " << std::hex << "0x" << m_B << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_C) {
					 for (int i{ 0 }; i != this->m_LDC; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
						 for (int j{ 0 }; j != (this->m_N1 + this->m_N2); ++j) {
							 this->m_C[i + this->m_LDC * j] = 0.0;
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in 2nd Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 this->m_C == nullptr ? std::cerr << "m_C contains invalid memory address: " << std::hex << "0x" << m_C << "\n" : 
						 std::cerr << "m_C contains valid memory address: " << std::hex << "0x" << m_C << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_D) {
					 for (int i{ 0 }; i != this->m_LDD; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
						 for (int j{ 0 }; j != this->m_M1; ++j) {
							 this->m_D[i + this->m_LDD * j] = 0.0;
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in 2nd Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 this->m_D == nullptr ? std::cerr << "m_D contains invalid memory address: " << std::hex << "0x" << m_D << "\n" : 
						 std::cerr << "m_D contains valid memory address: " << std::hex << "0x" << m_D << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_DWORK) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
					 for (int i{ 0 }; i != this->m_LDWORK; ++i) {
						 this->m_DWORK[i] = 0.0;
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in 2nd Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 this->m_DWORK == nullptr ? std::cerr << "m_DWORK contains invalid address: " << std::hex << "0x" << m_DWORK << "\n" : 
						 std::cerr << "m_DWORK contains valid address: " << std::hex << "0x" << m_DWORK << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
			 }

					/*
					  @Purpose:
								Copy Constructor implements deep copy semantics.
					*/
			 F77_AB05MD(_In_ const F77_AB05MD &other)
				 :
				 m_UPLO{ other.m_UPLO },
				 m_OVER{ other.m_OVER },
				 m_N1{ other.m_N1 },
				 m_M1{ other.m_M1 },
				 m_P1{ other.m_P1 },
				 m_N2{ other.m_N2 },
				 m_P2{ other.m_P2 },
				 m_LDA1{ other.m_LDA1 },
				 m_A1{ new R64[m_LDA1 * m_N1] },
				 m_LDB1{ other.m_LDB1 },
				 m_B1{ new R64[m_LDB1 * m_M1] },
				 m_LDC1{ other.m_LDC1 },
				 m_C1{ new R64[m_LDC1 * m_N1] },
				 m_LDD1{ other.m_LDD1 },
				 m_D1{ new R64[m_LDD1 * m_M1] },
				 m_LDA2{ other.m_LDA2 },
				 m_A2{ new R64[m_LDA2 * m_N2] },
				 m_LDB2{ other.m_LDB2 },
				 m_B2{ new R64[m_LDB2 * m_P1] },
				 m_LDC2{ other.m_LDC2 },
				 m_C2{ new R64[m_LDC2 * m_N2] },
				 m_LDD2{ other.m_LDD2 },
				 m_D2{ new R64[m_LDD2 * m_P1] },
				 m_N{ other.m_N },
				 m_LDA{ other.m_LDA },
				 m_A{ new R64[m_LDA * (m_N1 + m_N2)] },
				 m_LDB{ other.m_LDB },
				 m_B{ new R64[m_LDB * m_M1] },
				 m_LDC{ other.m_LDC },
				 m_C{ new R64[m_LDC * (m_N1 + m_N2)] },
				 m_LDD{ other.m_LDD },
				 m_D{ new R64[m_LDD * m_M1] },
				 m_LDWORK{ other.m_LDWORK },
				 m_DWORK{ new R64[m_LDWORK] },
				 m_INFO{ other.m_INFO } {

				 if (this->m_A1) {
					 for (int i{ 0 }; i != this->m_LDA1; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_A1:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_N1; ++j) {
							 this->m_A1[i + this->m_LDA1 * j] = other.m_A1[i + this->m_LDA1 * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of m_A1=" << std::hex << "0x" << m_A1 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_B1) {
					 for (int i{ 0 }; i != this->m_LDB1; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_B1:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_M1; ++j) {
							 this->m_B1[i + this->m_LDB1 * j] = other.m_B1[i + this->m_LDB1 * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of m_B1=" << std::hex << "0x" << m_B1 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_C1) {
					 for (int i{ 0 }; i != this->m_LDC1; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_C1:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_N1; ++j) {
							 this->m_C1[i + this->m_LDC1 * j] = other.m_C1[i + this->m_LDC1 * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of m_C1=" << std::hex << "0x" << m_C1 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_D1) {
					 for (int i{ 0 }; i != this->m_LDD1; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_D1:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_M1; ++j) {
							 this->m_D1[i + this->m_LDD1 * j] = other.m_D1[i + this->m_LDD1 * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of m_D1=" << std::hex << "0x" << m_D1 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_A2) {
					 for (int i{ 0 }; i != this->m_LDA2; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_A2:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_N2; ++j) {
							 this->m_A2[i + this->m_LDA2 * j] = other.m_A2[i + this->m_LDA2 * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of m_A2=" << std::hex << "0x" << m_A2 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_B2) {
					 for (int i{ 0 }; i != this->m_LDB2; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_B2:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_P1; ++j) {
							 this->m_B2[i + this->m_LDB2 * j] = other.m_B2[i + this->m_LDB2 * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of m_B2=" << std::hex << "0x" << m_B2 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_C2) {
					 for (int i{ 0 }; i != this->m_LDC2; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_C2:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_N2; ++j) {
							 this->m_C2[i + this->m_LDC2 * j] = other.m_C2[i + this->m_LDC2 * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of m_C2=" << std::hex << "0x" << m_C2 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_D2) {
					 for (int i{ 0 }; i != this->m_LDD2; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_D2:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_P1; ++j) {
							 this->m_D2[i + this->m_LDD2 * j] = other.m_D2[i + this->m_LDD2 * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of m_D2=" << std::hex << "0x" << m_D2 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_A) {
					 for (int i{ 0 }; i != this->m_LDA; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_A:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != (this->m_N1 + this->m_N2); ++j) {
							 this->m_A[i + this->m_LDA * j] = other.m_A[i + this->m_LDA * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of m_A=" << std::hex << "0x" << m_A << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_B) {
					 for (int i{ 0 }; i != this->m_LDB; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_B:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_M1; ++j) {
							 this->m_B[i + this->m_LDB * j] = other.m_B[i + this->m_LDB * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of m_B=" << std::hex << "0x" << m_B << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_C) {
					 for (int i{ 0 }; i != this->m_LDC; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_C:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != (this->m_N1 + this->m_N2); ++j) {
							 this->m_C[i + this->m_LDC * j] = other.m_C[i + this->m_LDC * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of m_C=" << std::hex << "0x" << m_C << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_D) {
					 for (int i{ 0 }; i != this->m_LDD; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_D:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_M1; ++j) {
							 this->m_D[i + this->m_LDD * j] = other.m_D[i + this->m_LDD * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of m_D=" << std::hex << "0x" << m_D << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 if (this->m_DWORK) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_DWORK:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
					 for (int i{ 0 }; i != this->m_LDWORK; ++i) {
						 this->m_DWORK[i] = other.m_DWORK[i];
					 }
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Ctor of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of m_DWORK=" << std::hex << "0x" << m_DWORK << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
			 }


					 /*
					   @Purpose:
									Move Constructor implements shallow copy semantics.
					 */
			 F77_AB05MD(_In_ F77_AB05MD &&other)
				 :
				 m_UPLO{ other.m_UPLO },
				 m_OVER{ other.m_OVER },
				 m_N1{ other.m_N1 },
				 m_M1{ other.m_M1 },
				 m_P1{ other.m_P1 },
				 m_N2{ other.m_N2 },
				 m_P2{ other.m_P2 },
				 m_LDA1{ other.m_LDA1 },
				 m_A1{ other.m_A1 },
				 m_LDB1{ other.m_LDB1 },
				 m_B1{ other.m_B1 },
				 m_LDC1{ other.m_LDC1 },
				 m_C1{ other.m_C1 },
				 m_LDD1{ other.m_LDD1 },
				 m_D1{ other.m_D1 },
				 m_LDA2{ other.m_LDA2 },
				 m_A2{ other.m_A2 },
				 m_LDB2{ other.m_LDB2 },
				 m_B2{ other.m_B2 },
				 m_LDC2{ other.m_LDC2 },
				 m_C2{ other.m_C2 },
				 m_LDD2{ other.m_LDD2 },
				 m_D2{ other.m_D2 },
				 m_N{ other.m_N },
				 m_LDA{ other.m_LDA },
				 m_A{ other.m_A },
				 m_LDB{ other.m_LDB },
				 m_B{ other.m_B },
				 m_LDC{ other.m_LDC },
				 m_C{ other.m_C },
				 m_LDD{ other.m_LDD },
				 m_D{ other.m_D },
				 m_LDWORK{ other.m_LDWORK },
				 m_DWORK{ other.m_DWORK },
				 m_INFO{ other.m_INFO } {

				 other.m_N1 = 0;
				 other.m_M1 = 0;
				 other.m_P1 = 0;
				 other.m_N2 = 0;
				 other.m_P2 = 0;
				 other.m_LDA1 = 0;
				 other.m_A1 = nullptr;
				 other.m_LDB1 = 0;
				 other.m_B1 = nullptr;
				 other.m_LDC1 = 0;
				 other.m_C1 = nullptr;
				 other.m_LDD1 = 0;
				 other.m_D1 = nullptr;
				 other.m_LDA2 = 0;
				 other.m_A2 = nullptr;
				 other.m_LDB2 = 0;
				 other.m_B2 = nullptr;
				 other.m_LDC2 = 0;
				 other.m_C2 = nullptr;
				 other.m_LDD2 = 0;
				 other.m_D2 = nullptr;
				 other.m_LDA = 0;
				 other.m_A = nullptr;
				 other.m_LDB = 0;
				 other.m_B = nullptr;
				 other.m_LDC = 0;
				 other.m_C = nullptr;
				 other.m_LDD = 0;
				 other.m_D = nullptr;
				 other.m_LDWORK = 0;
				 other.m_DWORK = nullptr;

			 }

					/*
					   @Purpose:
								Class Destructor.
					 */
			 ~F77_AB05MD() {
				 if (this->m_A1){
					 delete[] this->m_A1;
					 this->m_A1 = nullptr;
					 this->m_LDA1 = 0;
				 }
				 if (this->m_B1) {
					 delete[] this->m_B1;
					 this->m_B1 = nullptr;
					 this->m_LDB1 = 0;
				 }
				 if (this->m_C1) {
					 delete[] this->m_C1;
					 this->m_C1 = nullptr;
					 this->m_LDC1 = 0;
				 }
				 if (this->m_D1) {
					 delete[] this->m_D1;
					 this->m_D1 = nullptr;
					 this->m_LDD1 = 0;
				 }
				 if (this->m_A2) {
					 delete[] this->m_A2;
					 this->m_A2 = nullptr;
					 this->m_LDA2 = 0;
				 }
				 if (this->m_B2) {
					 delete[] this->m_B2;
					 this->m_B2 = nullptr;
					 this->m_LDB2 = 0;
				 }
				 if (this->m_C2) {
					 delete[] this->m_C2;
					 this->m_C2 = nullptr;
					 this->m_LDC2 = 0;
				 }
				 if (this->m_D2) {
					 delete[] this->m_D2;
					 this->m_D2 = nullptr;
					 this->m_LDD2 = 0;
				 }
				 if (this->m_A) {
					 delete[] this->m_A;
					 this->m_A = nullptr;
					 this->m_LDA = 0;
				 }
				 if (this->m_B) {
					 delete[] this->m_B;
					 this->m_B = nullptr;
					 this->m_LDB = 0;
				 }
				 if (this->m_C) {
					 delete[] this->m_C;
					 this->m_C = nullptr;
					 this->m_LDC = 0;
				 }
				 if (this->m_D) {
					 delete[] this->m_D;
					 this->m_D = nullptr;
					 this->m_LDD = 0;
				 }
				 if (this->m_DWORK) {
					 delete[] this->m_DWORK;
					 this->m_DWORK = nullptr;
					 this->m_LDWORK = 0;
				 }
			 }

					 /*
					   @Purpose:
									Copy Constructor implements deep copy semantics.
					 */
			 F77_AB05MD &  operator=(_In_ const F77_AB05MD &other) {
				 if (this == &other) return (*this);

				 this->m_N1 = other.m_N1;
				 this->m_M1 = other.m_M1;
				 this->m_P1 = other.m_P1;
				 this->m_N2 = other.m_N2;
				 this->m_P2 = other.m_P2;
				 this->m_LDA1 = other.m_LDA1;
				 R64* __restrict tA1 = new R64[this->m_LDA1 * this->m_N1];
				 if (tA1) {
					 for (int i{ 0 }; i != this->m_LDA1; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_A1:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_N1; ++j) {
							 tA1[i + this->m_LDA1 * j] = other.m_A1[i + other.m_LDA1 * j];
						 }
					 }
					 delete[] this->m_A1;
					 this->m_A1 = tA1;
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Operator of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of tA1=" << std::hex << "0x" << tA1 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 this->m_LDB1 = other.m_LDB1;
				 R64* __restrict tB1 = new R64[this->m_LDB1 * m_M1];
				 if (tB1) {
					 for (int i{ 0 }; i != this->m_LDB1; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_B1:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_M1; ++j) {
							 tB1[i + this->m_LDB1 * j] = other.m_B1[i + other.m_LDB1 * j];
						 }
					 }
					 delete[] this->m_B1;
					 this->m_B1 = tB1;
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Operator of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of tB1=" << std::hex << "0x" << tB1 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 this->m_LDC1 = other.m_LDC1;
				 R64* __restrict tC1 = new R64[this->m_LDC1 * this->m_N1];
				 if (tC1) {
					 for (int i{ 0 }; i != this->m_LDC1; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_C1:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_N1; ++j) {
							 tC1[i + this->m_LDC1 * j] = other.m_C1[i + other.m_LDC1 * j];
						 }
					 }
					 delete[] this->m_C1;
					 this->m_C1 = tC1;
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Operator of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of tC1=" << std::hex << "0x" << tC1 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 this->m_LDD1 = other.m_LDD1;
				 R64* __restrict tD1 = new R64[this->m_LDD1 * this->m_M1];
				 if (tD1) {
					 for (int i{ 0 }; i != this->m_LDD1; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_D1:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_M1; ++j) {
							 tD1[i + this->m_LDD1 * j] = other.m_D1[i + other.m_LDD1 * j];
						 }
					 }
					 delete[] this->m_D1;
					 this->m_D1 = tD1;
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Operator of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of tD1=" << std::hex << "0x" << tD1 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 this->m_LDA2 = other.m_LDA2;
				 R64* __restrict tA2 = new R64[this->m_LDA2 * this->m_N2];
				 if (tA2) {
					 for (int i{ 0 }; i != this->m_LDA2; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_A2:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_N2; ++j) {
							 tA2[i + this->m_LDA2 * j] = other.m_A2[i + other.m_LDA2 * j];
						 }
					 }
					 delete[] this->m_A2;
					 this->m_A2 = tA2;
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Operator of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of tA2=" << std::hex << "0x" << tA2 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 this->m_LDB2 = other.m_LDB2;
				 R64* __restrict tB2 = new R64[this->m_LDB2 * this->m_P1];
				 if (tB2) {
					 for (int i{ 0 }; i != this->m_LDB2; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_B2:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_P1; ++j) {
							 tB2[i + this->m_LDB2 * j] = other.m_B2[i + other.m_LDB2 * j];
						 }
					 }
					 delete[] this->m_B2;
					 this->m_B2 = tB2;
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Operator of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of tB2=" << std::hex << "0x" << tB2 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 this->m_LDC2 = other.m_LDC2;
				 R64* __restrict tC2 = new R64[this->m_LDC2 * this->m_N2];
				 if (tC2) {
					 for (int i{ 0 }; i != this->m_LDC2; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_C2:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_N2; ++j) {
							 tC2[i + this->m_LDC2 * j] = other.m_C2[i + other.m_LDC2 * j];
						 }
					 }
					 delete[] this->m_C2;
					 this->m_C2 = tC2;
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Operator of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of tC2=" << std::hex << "0x" << tC2 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 this->m_LDD2 = other.m_LDD2;
				 R64* __restrict tD2 = new R64[this->m_LDD2 * this->m_P1];
				 if (tD2) {
					 for (int i{ 0 }; i != this->m_LDD2; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_D2:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_P1; ++j) {
							 tD2[i + this->m_LDD2 * j] = other.m_D2[i + other.m_LDD2 * j];
						 }
					 }
					 delete[] this->m_D2;
					 this->m_D2 = tD2;
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Operator of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of tD2=" << std::hex << "0x" << tD2 << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 this->m_LDA = other.m_LDA;
				 R64* __restrict tA = new R64[this->m_LDA * (this->m_N1 + this->m_N2)];
				 if (tA) {
					 for (int i{ 0 }; i != this->m_LDA; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_A:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != (this->m_N1 + this->m_N2); ++j) {
							 tA[i + this->m_LDA * j] = other.m_A[i + other.m_LDA * j];
						 }
					 }
					 delete[] this->m_A;
					 this->m_A = tA;
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Operator of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of tA=" << std::hex << "0x" << tA << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 this->m_LDB = other.m_LDB;
				 R64* __restrict tB = new R64[this->m_LDB * this->m_M1];
				 if (tB) {
					 for (int i{ 0 }; i != this->m_LDB; ++j) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_B:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_M1; ++j) {
							 tB[i + this->m_LDB * j] = other.m_B[i + other.m_LDB * j];
						 }
					 }
					 delete[] this->m_B;
					 this->m_B = tB;
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Operator of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of tB=" << std::hex << "0x" << tB << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 this->m_LDC = other.m_LDC;
				 R64* __restrict tC = new R64[this->m_LDC * (this->m_N1 + this->m_N2)];
				 if (tC) {
					 for (int i{ 0 }; i != this->m_LDC; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_C:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != (this->m_N1 + this->m_N2); ++j) {
							 tC[i + this->m_LDC * j] = other.m_C[i + other.m_LDC * j];
						 }
					 }
					 delete[] this->m_C;
					 this->m_C = tC;
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Operator of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of tC=" << std::hex << "0x" << tC << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 this->m_LDD = other.m_LDD;
				 R64* __restrict tD = new R64[this->m_LDD * this->m_M1];
				 if (tD) {
					 for (int i{ 0 }; i != this->m_LDD; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_D:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (int j{ 0 }; j != this->m_M1; ++j) {
							 tD[i + this->m_LDD * j] = other.m_D[i + other.m_LDD * j];
						 }
					 }
					 delete[] this->m_D;
					 this->m_D = tD;
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Operator of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of tD=" << std::hex << "0x" << tD << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 this->m_LDWORK = other.m_LDWORK;
				 R64* __restrict tDWORK = new R64[this->m_LDWORK];
				 if (tDWORK) {
					 for (int i{ 0 }; i != this->m_LDWORK; ++i) {
						 tDWORK[i] = other.m_DWORK[i];
					 }
					 delete[] this->m_DWORK;
					 this->m_DWORK = tDWORK;
				 }
				 else {
					 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << " FATAL ERROR: Invalid pointer in Copy Operator of F77_AB05MD !!\n";
					 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					 std::cerr << "**** ERROR DETAILS ****\n";
					 std::cerr << "Value of tDWORK=" << std::hex << "0x" << tDWORK << "\n";
					 std::cerr << "Cannot recover -- calling std::exit(-1)!!\n";
					 std::exit(-1);
				 }
				 this->m_INFO = other.m_INFO;
				 return (*this);
			 }

					 /*
					   @Purpose:
									Move Operator implements shallow copy semantics.
					 */
			 F77_AB05MD &  operator=(_In_ F77_AB05MD &&other) {
				 if (this == &other) return (*this);

				 this->m_N1 = other.m_N1;
				 this->m_M1 = other.m_M1;
				 this->m_P1 = other.m_P1;
				 this->m_N2 = other.m_N2;
				 this->m_P2 = other.m_P2;
				 this->m_LDA1 = other.m_LDA1;
				 this->m_A1 = other.m_A1;
				 other.m_LDA1 = 0;
				 other.m_A = nullptr;
				 this->m_LDB1 = other.m_LDB1;
				 this->m_B1 = other.m_B1;
				 other.m_LDB1 = 0;
				 other.m_B1 = nullptr;
				 this->m_LDC1 = other.m_LDC1;
				 this->m_C1 = other.m_C1;
				 other.m_LDC1 = 0;
				 other.m_C1 = nullptr;
				 this->m_LDD1 = other.m_LDD1;
				 this->m_D1 = other.m_D1;
				 other.m_LDD1 = 0;
				 other.m_D1 = nullptr;
				 this->m_LDA2 = other.m_LDA2;
				 this->m_A2 = other.m_A2;
				 other.m_LDA2 = 0;
				 other.m_A2 = nullptr;
				 this->m_LDB2 = other.m_LDB2;
				 this->m_B2 = other.m_B2;
				 other.m_LDB2 = 0;
				 other.m_B2 = nullptr;
				 this->m_LDC2 = other.m_LDC2;
				 this->m_C2 = other.m_C2;
				 other.m_LDC2 = 0;
				 other.m_C2 = nullptr;
				 this->m_LDD2 = other.m_LDD2;
				 this->m_D2 = other.m_D2;
				 other.m_LDD2 = 0;
				 other.m_D2 = nullptr;
				 this->m_N = other.m_N;
				 this->m_LDA = other.m_LDA;
				 this->m_A = other.m_A;
				 other.m_LDA = 0;
				 other.m_A = nullptr;
				 this->m_LDB = other.m_LDB;
				 this->m_B = other.m_B;
				 other.m_LDB = 0;
				 other.m_B = nullptr;
				 this->m_LDC = other.m_LDC;
				 this->m_C = other.m_C;
				 other.m_LDC = 0;
				 other.m_C = nullptr;
				 this->m_LDD = other.m_LDD;
				 this->m_D = other.m_D;
				 other.m_LDD = 0;
				 other.m_D = nullptr;
				 this->m_LDWORK = other.m_LDWORK;
				 this->m_DWORK = other.m_DWORK;
				 other.m_LDWORK = 0;
				 other.m_DWORK = nullptr;
				 this->m_INFO = other.m_INFO;
				 return (*this);
			 }



					/*
					  @Purpose:
									Calls Fortran AB05MD subroutine.
					*/
			 void  call_AB05MD() {
					
				 AB05MD(&this->m_A,&this->m_OVER,&this->m_N1,&this->m_M1,&this->m_P1,&this->m_N2,&this->m_P2,
					 &this->m_A1[0], &this->m_LDA1, &this->m_B1[0], &this->m_LDB1, &this->m_C1[0],&this->m_LDC1,
					 &this->m_D1[0], &this->m_LDD1, &this->m_A2[0], &this->m_LDA2, &this->m_B2[0],&this->m_LDB2,
					 &this->m_C2[0], &this->m_LDC2, &this->m_D2[0], &this->m_LDD2[0], &this->m_N, &this->m_A[0],
					 &this->m_LDA, &this->m_B[0], &this->m_LDB, &this->m_C[0], &this->m_LDC, &this->m_D[0],
					 &this->m_LDD, &this->m_DWORK[0], &this->m_LDWORK[0],&this->m_INFO);
			 }

					 /*
					   @Purpose:
									Member variables.
					 */

					 // Mode parameters:

					 UC8  m_UPLO;

					 UC8  m_OVER;

					 // Input/Output parameters:

					 I32  m_N1;

					 I32  m_M1;

					 I32  m_P1;

					 I32  m_N2;

					 I32  m_P2;

					 I32  m_LDA1;

				_In_ R64* __restrict m_A1;
					
					 I32  m_LDB1;

				_In_ R64* __restrict m_B1;

					 I32  m_LDC1;

				_In_ R64* __restrict m_C1;

					 I32  m_LDD1;

				_In_ R64* __restrict m_D1;

				     I32  m_LDA2;

				_In_ R64* __restrict m_A2;

					 I32  m_LDB2;

				_In_ R64* __restrict m_B2;

					 I32  m_LDC2;

				_In_ R64* __restrict m_C2;

					 I32  m_LDD2;

				_In_ R64* __restrict m_D2;

			   _Out_ I32 m_N;

					 I32 m_LDA;

			   _Out_ R64* __restrict m_A;

					 I32 m_LDB;

			   _Out_ R64* __restrict m_B;

					 I32 m_LDC;

			   _Out_ R64* __restrict m_C;

					 I32 m_LDD;

			   _Out_ R64* __restrict m_D;

					 // Workspace.

				     I32 m_LDWORK;

					 R64* __restrict m_DWORK;

					 // Error indicator.

					 I32 m_INFO;
	};






	}
}

#endif /*__SLICOT_ABO5MD_H__*/