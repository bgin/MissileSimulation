
#ifndef __SLICOT_AB01ND_H__
#define __SLICOT_AB01ND_H__

//Code: struct declaration: Tab * 2
//Code: members definition: Tab * 3

// File version granularity
#ifndef SLICOT_AB01ND_VERSION_MAJOR
#define SLICOT_AB01ND_VERSION_MAJOR 1
#endif

#ifndef SLICOT_AB01ND_VERSION_MINOR
#define SLICOT_AB01ND_VERSION_MINOR 0
#endif

#ifndef SLICOT_AB01ND_PATCH_VERSION
#define SLICOT_AB01ND_PATCH_VERSION 0
#endif

#ifndef SLICOT_AB01ND_CREATE_DATE
#define SLICOT_AB01ND_CREATE_DATE "Date: 2016-09-14 Time: 09:56 AM GMT+2"
#endif

#ifndef SLICOT_AB01ND_BUILD_DATE
#define SLICOT_AB01ND_BUILD_DATE ""
#endif


#include "Slicot_F77_Interface.h"
#include "std_headers.h"
#include "Config.h"

namespace guidance {
	namespace slicot_wrappers {



		template<typename R64 = double,
		         typename I32 = int,
				 typename UC8 = unsigned char>  struct F77_AB01ND{


				 // Constructors and Destructor.

				// First Constructor - members instantiation
				// and null array initialization.
				// Later if needed In/Out arrays must
				// filled with aprropriate data coefficients
				// before calling AB01ND subroutine.

					 F77_AB01ND(_In_ const UC8 JOBZ,
					            _In_ const I32 N,
					            _In_ const I32 M,
					            _In_ const I32 LDA,
					            _In_ const I32 LDB,
					            _In_ const I32 NCONT,
					            _In_ const I32 INDCON,
					            _In_ const I32 LDZ,
					            _In_ const R64 TOL,
					            _In_ const I32 LDWORK,
					            _In_ const I32 INFO)
					 :
					 m_JOBZ{ JOBZ },
					 m_N{ N },
					 m_M{ M },
					 m_LDA{ LDA },
					 m_A{ new R64[m_LDA * m_N] },
					 m_LDB{ LDB },
					 m_B{ new R64[m_LDB * m_M] },
					 m_NCONT{ NCONT },
					 m_INDCON{ INDCON },
					 m_NBLK{ new I32[m_N] },
					 m_LDZ{ LDZ },
					 m_Z{ new R64[m_LDZ * m_N] },
					 m_TAU{ new R64[m_N] },
					 m_TOL{ TOL },
					 m_IWORK{ new I32[m_M] },
					 m_LDWORK{ LDWORK },
					 m_DWORK{ new R64[m_LDWORK] },
					 m_INFO{ INFO } {

						 if (this->m_A != nullptr) {
							 for (I32 i{ 0 }; i != this->m_LDA; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
								 for (I32 j{ 0 }; j != this->m_N; ++j) {
									 this->m_A[i + this->m_LDA * j] = 0.0L;
								 }
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_A: " << std::hex << this->m_A << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 if (this->m_B != nullptr) {
							 for (I32 i{ 0 }; i != this->m_LDB; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
								 for (I32 j{ 0 }; j != this->m_M; ++j) {
									 this->m_B[i + this->m_LDB * j] = 0.0L;
								 }
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_B: " << std::hex << this->m_B << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 if (this->m_NBLK != nullptr) {
							 for (I32 i{ 0 }; i != this->m_N; ++i) {
								 this->m_NBLK[i] = 0;
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_NBLK: " << std::hex << this->m_NBLK << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 if (this->m_Z != nullptr) {
							 for (I32 i{ 0 }; i != this->m_LDZ; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
								 for (I32 j{ 0 }; j != this->m_N; ++j) {
									 this->m_Z[i + this->m_LDZ * j] = 0.0L;
								 }
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_Z: " << std::hex << this->m_Z << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 if (this->m_TAU != nullptr) {
							 for (I32 i{ 0 }; i != this->m_N; ++i) {
								 this->m_TAU[i] = 0.0L;
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_TAU: " << std::hex << this->m_TAU << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 if (this->m_IWORK != nullptr) {
							 for (I32 i{ 0 }; i != this->m_M; ++i) {
								 this->m_IWORK[i] = 0;
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_IWORK: " << std::hex << this->m_IWORK << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 if (this->m_DWORK != nullptr) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
							 for (I32 i{ 0 }; i != this->m_LDWORK; ++i) {
								 this->m_DWORK[i] = 0.0L;
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_DWORK: " << std::hex << this->m_DWORK << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
#if defined(GUIDANCE_DEBUG_ON)
						 std::cerr << "****************************************\n";
						 std::cerr << "Debug mode: ON \n";
						 std::cerr << "Date: " << this->time_stamp().first << "\n";
						 std::cerr << "Time: " << this->time_stamp().second << "\n";
						 std::cerr << "Execution inside 1st Ctor body of type: " << this->obj_type() << "\n";
						 std::cerr << "File: " << __FILE__ << "\n";
						 std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
						 std::cerr << "Code-line: " << __LINE__ << "\n";
						 std::cerr << "Exiting 1st Ctor body!! \n";
						 std::cerr << "****************************************\n\n";
#endif
			 }

			 // Second Constructor fully initializes
			 // an object to be passed later to
			 // AB01ND subroutine.
			 // Notice:
			 // Size of array R64* A must be equal to LDA.
			 // Size of array R64* B must be equal to LDB.

			 F77_AB01ND(_In_  const UC8 JOBZ,
				        _In_  const I32 N,
				        _In_  const I32 M,
				        _In_  const I32 LDA,
				        _In_  R64 * __restrict A,
				        _In_  const I32 LDB,
				        _In_  R64 * __restrict B,
				        _In_  const I32 NCONT,
				        _In_  const I32 INDCON,
				        _In_  const I32 LDZ,
				        _In_  const R64 TOL,
				        _In_  const I32 LDWORK,
				        _In_  const I32 INFO)
				 :
				 m_JOBZ{ JOBZ },
				 m_N{ N },
				 m_M{ M },
				 m_LDA{ LDA },
				 m_A{ new R64[m_LDA * m_N] },
				 m_LDB{ LDB },
				 m_B{ new R64[m_LDB * m_M] },
				 m_NCONT{ NCONT },
				 m_INDCON{ INDCON },
				 m_NBLK{ new I32[m_N] },
				 m_LDZ{ LDZ },
				 m_Z{ new R64[m_LDZ * m_N] },
				 m_TAU{ new R64[m_N] },
				 m_TOL{ TOL },
				 m_IWORK{ new I32[m_N] },
				 m_LDWORK{ LDWORK },
				 m_DWORK{ new R64[m_LDWORK] },
				 m_INFO{ INFO } {

				 
				 if ((this->m_A != nullptr) && (A != nullptr)) {
					 for (I32 i{ 0 }; i != this->m_LDA; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch A:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (I32 j{ 0 }; j != this->m_N; ++j) {
							 this->m_A[i + this->m_LDA * j] = A[i + this->m_LDA * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND 2nd Constructor: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "this->m_A: " << std::hex << this->m_A << "\n";
					 std::cerr << "A: " << std::hex << A << "\n";
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 if ((this->m_B != nullptr) && (B != nullptr)) {
					 for (I32 i{ 0 }; i != this->m_LDB; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch B:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (I32 j{ 0 }; j != this->m_M; ++j) {
							 this->m_B[i + this->m_LDB * j] = B[i + this->m_LDB * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND 2nd Constructor: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "this->m_B: " << std::hex << this->m_B << "\n";
					 std::cerr << "B: " << std::hex << B << "\n";
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 if (this->m_NBLK != nullptr) {
					 for (I32 i{ 0 }; i != this->m_N; ++i) {
						 this->m_NBLK[i] = 0;
					 }
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND 2nd Constructor: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "this->m_NBLK: " << std::hex << this->m_NBLK << "\n";
					
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 if (this->m_Z != nullptr) {
					 for (I32 i{ 0 }; i != this->m_LDZ; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch this->m_Z:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 for (I32 j{ 0 }; j != this->m_N; ++j) {
							 this->m_Z[i + this->m_LDZ * j] = 0.0L;
						 }
					 }
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND 2nd Constructor: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "this->m_Z: " << std::hex << this->m_Z << "\n";

					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 if (this->m_TAU != nullptr) {
					 for (I32 i{ 0 }; i != this->m_N; ++i) {
						 this->m_TAU[i] = 0.0L;
					 }
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND 2nd Constructor: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "this->m_TAU: " << std::hex << this->m_TAU << "\n";

					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 if (this->m_IWORK != nullptr) {
					 for (I32 i{ 0 }; i != this->m_M; ++i) {
						 this->m_IWORK[i] = 0;
					 }
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND 2nd Constructor: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "this->m_IWORK: " << std::hex << this->m_IWORK << "\n";

					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 if (this->m_DWORK != nullptr) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch this->m_DWORK:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
					 for (I32 i{ 0 }; i != this->m_LDWORK; ++i) {
						 this->m_DWORK[i] = 0.0L;
					 }
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND 2nd Constructor: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "this->m_LDWORK: " << std::hex << this->m_LDWORK << "\n";

					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
#if defined(GUIDANCE_DEBUG_ON)
				 std::cerr << "****************************************\n";
				 std::cerr << "Debug mode: ON \n";
				 std::cerr << "Date: " << this->time_stamp().first << "\n";
				 std::cerr << "Time: " << this->time_stamp().second << "\n";
				 std::cerr << "Execution inside 2nd Ctor body of type: " << this->obj_type() << "\n";
				 std::cerr << "File: " << __FILE__ << "\n";
				 std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
				 std::cerr << "Code-line: " << __LINE__ << "\n";
				 std::cerr << "Exiting 2nd Ctor body!! \n";
				 std::cerr << "****************************************\n\n";
#endif

			 }
					
					// Copy Constructor (deep copy).
					 
			 F77_AB01ND(_In_ const F77_AB01ND &other)
				       :
				 m_JOBZ{ other.m_JOBZ },
				 m_N{ other.m_N },
				 m_M{ other.m_M },
				 m_LDA{ other.m_LDA },
				 m_A{ new R64[m_LDA * m_N] },
				 m_LDB{ other.m_LDB },
				 m_B{ new R64[m_LDB * m_M] },
				 m_NCONT{ other.m_NCONT },
				 m_INDCON{ other.m_INDCON },
				 m_NBLK{ new I32[m_N] },
				 m_LDZ{ other.m_LDZ },
				 m_Z{ new R64[m_LDZ * m_N] },
				 m_TAU{ new R64[m_N] },
				 m_TOL{ other.m_TOL },
				 m_IWORK{ new I32[m_N] },
				 m_LDWORK{ other.m_LDWORK },
				 m_DWORK{ new R64[m_LDWORK] },
				 m_INFO{ other.m_INFO } {

				 if (this->m_A != nullptr) {
					 for (I32 i{ 0 }; i != this->m_LDA; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
						 for (I32 j{ 0 }; j != this->m_N; ++j) {
							 this->m_A[i + this->m_LDA * j] = other.m_A[i + other.m_LDA * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Copy-Constructor: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "this->m_A: " << std::hex << this->m_A << "\n";
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 if (this->m_B != nullptr) {
					 for (I32 i{ 0 }; i != this->m_LDB; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
						 for (I32 j{ 0 }; j != this->m_M; ++j) {
							 this->m_B[i + this->m_LDB * j] * other.m_B[i + other.m_LDB * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Copy-Constructor: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "this->m_B: " << std::hex << this->m_B << "\n";
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 if (this->m_NBLK != nullptr) {
					 for (I32 i{ 0 }; i != this->m_N; ++i) {
						 this->m_NBLK[i] = other.m_NBLK[i];
					 }
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Copy-Constructor: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "this->m_NBLK: " << std::hex << this->m_NBLK << "\n";
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 if (this->m_Z != nullptr) {
					 for (I32 i{ 0 }; i != this->m_LDZ; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
						 for (I32 j{ 0 }; j != this->m_N; ++j) {
							 this->m_Z[i + this->m_LDZ * j] = other.m_Z[i + other.m_LDZ * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Copy-Constructor: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "this->m_Z: " << std::hex << this->m_Z << "\n";
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 if (this->m_TAU != nullptr) {
					 for (I32 i{ 0 }; i != this->m_N; ++i) {
						 this->m_TAU[i] = other.m_TAU[i];
					 }
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Copy-Constructor: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "this->m_TAU: " << std::hex << this->m_TAU << "\n";
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 if (this->m_IWORK != nullptr) {
					 for (I32 i{ 0 }; i != this->m_M; ++i) {
						 this->m_IWORK[i] = other.m_IWORK[i];
					 }
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Copy-Constructor: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "this->m_IWORK: " << std::hex << this->m_IWORK << "\n";
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 if (this->m_DWORK != nullptr) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
					 for (I32 i{ 0 }; i != this->m_LDWORK; ++i) {
						 this->m_DWORK[i] = other.m_DWORK[i];
					 }
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Copy-Constructor: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "this->m_DWORK: " << std::hex << this->m_DWORK << "\n";
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
#if defined(GUIDANCE_DEBUG_ON)
				 std::cerr << "****************************************\n";
				 std::cerr << "Debug mode: ON \n";
				 std::cerr << "Date: " << this->timestamp().first << "\n";
				 std::cerr << "Time: " << this->timestamp().second << "\n";
				 std::cerr << "Execution inside Copy-Constructor body of type: " << this->obj_type() << "\n";
				 std::cerr << "File: " << __FILE__ << "\n";
				 std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
				 std::cerr << "Code-line: " << __LINE__ << "\n";
				 std::cerr << "Exiting Copy-Constructor body!! \n";
				 std::cerr << "****************************************\n";
#endif
			 }

			 // Move Constructor (shallow copy).
			 F77_AB01ND(_In_ F77_AB01ND &&other)
				 :
				 m_JOBZ{ other.m_JOBZ },
				 m_N{ other.m_N },
				 m_M{ other.m_M },
				 m_LDA{ other.m_LDA },
				 m_A{ other.m_A },
				 m_LDB{ other.m_LDB },
				 m_B{ other.m_B },
				 m_NCONT{ other.m_NCONT },
				 m_INDCONT{ other.m_INDCONT },
				 m_NBLK{ other.m_NBLK },
				 m_LDZ{ other.m_LDZ },
				 m_Z{ other.m_Z },
				 m_TAU{ other.m_TAU },
				 m_TOL{ other.m_TOL },
				 m_IWORK{ other.m_IWORK },
				 m_LDWORK{ other.m_LDWORK },
				 m_DWORK{ other.m_DWORK },
				 m_INFO{ other.m_INFO } {

				 other.m_N = 0;
				 other.m_M = 0;
				 other.m_LDA = 0;
				 other.m_A = nullptr;
				 other.m_LDB = 0;
				 other.m_B = nullptr;
				 other.m_NBLK = nullptr;
				 other.m_LDZ = 0;
				 other.m_Z = nullptr;
				 other.m_TAU = nullptr;
				 other.m_IWORK = nullptr;
				 other.m_LDWORK = 0;
				 other.m_DWORK = nullptr;
#if defined(GUIDANCE_DEBUG_ON)
				 std::cerr << "****************************************\n";
				 std::cerr << "Debug mode: ON \n";
				 std::cerr << "Date: " << this->timestamp().first << "\n";
				 std::cerr << "Time: " << this->timestamp().second << "\n";
				 std::cerr << "Execution inside Move-Constructor body of type: " << this->obj_type() << "\n";
				 std::cerr << "File: " << __FILE__ << "\n";
				 std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
				 std::cerr << "Code-line: " << __LINE__ << "\n";
				 std::cerr << "Exiting Move-Constructor body!! \n";
				 std::cerr << "****************************************\n";
#endif
			 }

			 // Destructor
			 ~F77_AB01ND() {

				 if (this->m_A){
				    delete[]this->m_A; 
					this->m_A = nullptr;
					this->m_LDA = 0;
					}

				 if (this->m_B) {
				    delete[]this->m_B; 
					this->m_B = nullptr;
					this->m_LDB = 0;
					}

				 if (this->m_NBLK){ 
				    delete[]this->m_NBLK; 
					this->m_NBLK = nullptr;
					}

				 if (this->m_Z) {
					 delete[]this->m_Z;
					 this->m_Z = nullptr;
					 this->m_LDZ = 0;
				 }

				 if (this->m_TAU) {
					 delete[]this->m_TAU;
					 this->m_TAU = nullptr;
				 }

				 if (this->m_IWORK) {
					 delete[]this->m_IWORK;
					 this->m_IWORK = nullptr;
				 }

				 if (this->m_DWORK) {
					 delete[]this->m_DWORK;
					 this->m_DWORK = nullptr;
					 this->m_LDWORK = 0;
				 }

#if defined(GUIDANCE_DEBUG_ON)
				 std::cerr << "****************************************\n";
				 std::cerr << "Debug mode: ON \n";
				 std::cerr << "Date: " << this->time_stamp().first << "\n";
				 std::cerr << "Time: " << this->time_stamp().second << "\n";
				 std::cerr << "Execution inside Destructor body of type: " << this->obj_type() << "\n";
				 std::cerr << "File: " << __FILE__ << "\n";
				 std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
				 std::cerr << "Code-line: " << __LINE__ << "\n";
				 std::cerr << "Exiting Destructor body!! \n";
				 std::cerr << "****************************************\n";
#endif

			 }


			 // operator copy-assign implements (deep copy).
			 F77_AB01ND &  operator=(_In_ const F77_AB01ND other) {
				 if (this == &other) return (*this);

				 this->m_JOBZ = other.m_JOBZ;
				 this->m_N = other.m_N;
				 this->m_M = other.m_M;
				 this->m_LDA = other.m_LDA;
				 R64 *tA = new R64[this->m_LDA * this->m_N];
				 if (tA) {
					 for (I32 i{ 0 }; i != this->m_LDA; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
						 for (I32 j{ 0 }; j != this->m_N; ++j) {
							 tA[i + this->m_LDA * j] = other.m_A[i + other.m_LDA * j];
						 }
					 }
					 delete[] this->m_A;
					 this->m_A = tA;

				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Copy-Assign operator: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "tA: " << std::hex << tA << "\n";
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 this->m_LDB = other.m_LDB;
				 R64* tB = new R64[this->m_LDB * this->m_M];
				 if (tB) {
					 for (I32 i{ 0 }; i != this->m_LDB; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
						 for (I32 j{ 0 }; j != this->m_M; ++j) {
							 tB[i + this->m_LDB * j] = other.m_B[i + other.m_LDB * j];
						 }
					 }
					 delete[] this->m_B;
					 this->m_B = tB;
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Copy-Assign operator: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "tB: " << std::hex << tB << "\n";
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 this->m_NCONT = other.m_NCONT;
				 this->m_INDCON = other.m_INDCON;
				 I32* tNBLK = new I32[this->mN];
				 if (tNBLK) {
					 for (I32 i{ 0 }; i != this->m_N; ++i) {
						 tNBLK[i] = other.m_NBLK[i];
					 }
					 delete[] this->m_NBLK;
					 this->m_NBLK = tNBLK;
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Copy-Assign operator: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "tNBLK: " << std::hex << tNBLK << "\n";
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 this->m_LDZ = other.m_LDZ;
				 R64* tZ = new R64[this->m_LDZ * this->m_N];
				 if (tZ) {
					 for (I32 i{ 0 }; i != this->m_LDZ; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
						 for (I32 j{ 0 }; j != this->m_N; ++j) {
							 tZ[i + this->m_LDZ * j] = other.m_Z[i + other.m_LDZ * j];
						 }
					 }
					 delete[] this->m_Z;
					 this->m_Z = tZ;
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Copy-Assign operator: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "tZ: " << std::hex << tZ << "\n";
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 R64* tTAU = new R64[this->m_N];
				 if (tTAU) {
					 for (I32 i{ 0 }; i != this->m_N; ++i) {
						 tTAU[i] = other.m_TAU[i];
					 }
					 delete[] this->m_TAU;
					 this->m_TAU = tTAU;
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Copy-Assign operator: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "tTAU: " << std::hex << tTAU << "\n";
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 this->m_TOL = other.m_TOL;
				 I32* tIWORK = new I32[this->m_M];
				 if (tIWORK) {
					 for (I32 i{ 0 }; i != this->m_M; ++i) {
						 tIWORK[i] = other.m_IWORK[i];
					 }
					 delete[] this->m_IWORK;
					 this->m_IWORK = tIWORK;
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Copy-Assign operator: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "tIWORK: " << std::hex << tIWORK << "\n";
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 this->m_LDWORK = other.m_LDWORK;
				 R64* tDWORK = new R64[this->m_LDWORK];
				 if (tDWORK) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
					 for (I32 i{ 0 }; i != this->m_LDWORK; ++i) {
						 tDWORK[i] = other.m_DWORK[i];
					 }
					 delete[] this->m_DWORK;
					 this->m_DWORK = tDWORK;
				 }
				 else {
					 std::cerr << "Fatal Error: Invalid pointer in F77_AB01ND Copy-Assign operator: \n";
					 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
					 std::cerr << "In file: " << __FILE__ << "\n";
					 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
					 std::cerr << "In code-line: " << __LINE__ << "\n";
					 std::cerr << "Error details: \n";
					 std::cerr << "tDWORK: " << std::hex << tDWORK << "\n";
					 std::cerr << "Calling std::exit!! \n";
					 std::exit(1)
				 }
				 this->m_INFO = other.m_INFO;
#if defined(GUIDANCE_DEBUG_ON)
				 std::cerr << "****************************************\n";
				 std::cerr << "Debug mode: ON \n";
				 std::cerr << "Date: " << this->timestamp().first << "\n";
				 std::cerr << "Time: " << this->timestamp().second << "\n";
				 std::cerr << "Execution inside body of Copy-Assign operator of type: " << this->obj_type() << "\n";
				 std::cerr << "File: " << __FILE__ << "\n";
				 std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
				 std::cerr << "Code-line: " << __LINE__ << "\n";
				 std::cerr << "Exiting  body of Copy-Assign operator !! \n";
				 std::cerr << "****************************************\n";
#endif
				 return (*this);
			 }

			 // Move-Assign operator implements shallow copy.
			 F77_AB01ND &  operator=(_In_ F77_AB01ND &&other) {
				 if (this == &other) return (*this);

				 this->m_JOBZ = other.m_JOBZ;
				 this->m_N = other.m_N;
				 this->m_M = other.m_M;
				 this->m_LDA = other.m_LDA;
				 delete[] this->m_A;
				 this->m_A = other.m_A;
				 other.m_A = nullptr;
				 other.m_LDA = 0;
				 other.m_N = nullptr;
				 this->m_LDB = other.m_LDB;
				 delete[] this->m_B;
				 this->m_B = other.m_B;
				 other.m_B = nullptr;
				 other.m_LDB = 0;
				 this->m_NCONT = other.m_NCONT;
				 this->m_INDCON = other.m_INDCON;
				 delete[] this->m_NBLK;
				 this->m_NBLK = other.m_NBLK;
				 other.m_NBLK = nullptr;
				 this->m_LDZ = other.m_LDZ;
				 delete[] this->m_Z;
				 this->m_Z = other.m_Z;
				 other.m_Z = nullptr;
				 other.m_LDZ = 0;
				 delete[] this->m_TAU;
				 this->m_TAU = other.m_TAU;
				 other.m_TAU = nullptr;
				 this->m_TOL = other.m_TOL;
				 delete[] this->m_IWORK;
				 this->m_IWORK = other.m_IWORK;
				 other.m_IWORK = nullptr;
				 this->m_LDWORK = other.m_LDWORK;
				 delete[] this->m_DWORK;
				 this->m_DWORK = other.m_DWORK;
				 other.m_LDWORK = 0;
				 other.m_DWORK = nullptr;
				 this->m_INFO = other.m_INFO;
#if defined(GUIDANCE_DEBUG_ON)
				 std::cerr << "****************************************\n";
				 std::cerr << "Debug mode: ON \n";
				 std::cerr << "Date: " << this->timestamp().first << "\n";
				 std::cerr << "Time: " << this->timestamp().second << "\n";
				 std::cerr << "Execution inside body of Move-Assign operator of type: " << this->obj_type() << "\n";
				 std::cerr << "File: " << __FILE__ << "\n";
				 std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
				 std::cerr << "Code-line: " << __LINE__ << "\n";
				 std::cerr << "Exiting  body of Move-Assign operator !! \n";
				 std::cerr << "****************************************\n";
#endif			
				 return (*this);
			 }

			// Extended debug info.
#ifdef GUIDANCE_DEBUG_ON

			 void  print_extended_info()const {

				 std::cout << "Dumping context of object: " << this->obj_type() << "\n";
				 std::cout << "At date: " << this->time_stamp().first << "\n";
				 std::cout << "At time: " << this->time_stamp().second << "\n";
				 auto map = this->name_address_map();
				 std::cout << "Memory layout of " << this->obj_type() << "\n";
				 std::cout << "member name:     memeber address:  \n";
				 std::cout << HLINES;
				 for (auto& it : map) {
					 std::cout << it.first << " : " <<  it.second << "\n";
				 }
				 std::cout << HLINES;
				 std::cout << "Array members content first: \n";
				 std::cout << "Fortran-style array traversing in use. \n";
				 std::cout << "Precision fixed at " << 16 << "decimal digits. \n";
				 std::cout << "Input/Output array m_A:   \n";
				 std::cout << "element's address:    element's value:   \n";
				 for (I32 i{ 0 }; i != this->m_LDA; ++i) {
					 for (I32 j{ 0 }; j != this->m_N; ++j) {
						 std::cout << &this->m_A[j + this->m_LDA * i] << std::fixed <<
							 std::setprecision(16) << this->m_A[j + this->m_LDA * i] << "\n";
					 }
					 std::cout << "\n";
				 }
				 std::cout << "--------------------\n\n";
				 std::cout << "Input/Output array m_B:    \n";
				 std::cout << "element's address:     element's value:  \n";
				 for (I32 i{ 0 }; i != this->m_LDB; ++i) {
					 for (I32 j{ 0 }; j != this->m_M; ++j) {
						 std::cout << &this->m_B[j + this->m_LDB * i] << std::fixed <<
							 std::setprecision(16) << this->m_B[j + this->m_LDB * i] << "\n";
					 }
					 std::cout << "\n";
				 }
				 std::cout << "--------------------\n\n";
				 std::cout << "Ouput array m_NBLK:   \n";
				 std::cout << "element's address:     element's value:  \n";
				 for (I32 i{ 0 }; i != this->m_N; ++i) {
					 std::cout << &this->m_NBLK[i] << this->m_NBLK[i] << "\n";
				 }
				 std::cout "------------------------\n\n";
				 std::cout << "Output array m_Z:            \n";
				 std::cout << "element's address:     element's value:   \n";
				 for (I32 i{ 0 }; i != this->m_LDZ; ++i) {
					 for (I32 j{ 0 }; j != this->m_N; ++j) {
						 std::cout << &this->m_Z[j + this->m_LDZ * i] << std::fixed <<
							 std::setprecision(16) << this->m_Z[j + this->m_LDZ * i] << "\n";
					 }
					 std::cout << "\n";
				 }
				 std::cout << "-----------------------\n\n";
				 std::cout << "Output array m_TAU:      \n";
				 std::cout << "element's address      element's value:   \n";
				 for (I32 i{ 0 }; i != this->m_N; ++i) {
					 std::cout << &this->m_TAU[i] << 
						 std::fixed << std::setprecision(16) << this->m_TAU[i] << "\n";
				 }
				 std::cout << "------------------------\n\n";
				 std::cout << "Work array m_IWORK:     \n";
				 std::cout << "element's address:     element's value:    \n";
				 for (I32 i{ 0 }; i != this->m_M; ++i) {
					 std::cout << &this->m_IWORK[i] << this->m_IWORK[i] << "\n";
				 }
				 std::cout << "------------------------\n\n";
				 std::cout << "Work array m_DWORK:     \n";
				 std::cout << "element's address:     element's value:    \n";
				 for (I32 i{ 0 }; i != this->m_LDWORK; ++i) {
					 std::cout << &this->m_DWORK[i] << std::fixed <<
						 std::setprecision(16) << this->m_DWORK[i] << "\n";
				 }
				 std::cout << "------------------------\n\n";
				 std::cout << "Statistics:  \n\n";
				 std::cout << "Dumping m_A statistics. \n";
				 auto felemA = reinterpret_cast<std::size_t>(&this->m_A[0]);
				 auto lelemA = reinterpret_cast<std::size_t>(&this->m_A[this->m_LDA * this->m_N]);
				 std::cout << "Total loop iterations: " << this->m_LDA * this->m_N << "\n";
				 std::cout << "Base memory address m_A: " << std::hex << "0x" << &this->m_A << "\n";
				 std::cout << "First element stored at: " << std::hex << "0x" << &this->m_A[0] << "\n";
				 std::cout << "Last  element stored at: " << std::hex << "0x" << &this->m_A[this->m_LDA * this->m_N] << "\n";
				 std::cout << "Memory addres space: " << lelemA - felemA << "\n";
				 std::cout << "Subtotal memory allocated: " << static_cast<R64>((this->m_LDA * this->m_N * sizeof(R64)) / 1024.0 << " KiB. \n\n";
				 std::cout << "Dumping m_B statistics. \n";
				 std::cout << "Total loop iterations: " << this->m_LDB * this->m_M<< "\n";
				 std::cout << "Base memory address m_A: " << std::hex << "0x" << &this->m_B << "\n";
				 std::cout << "First element stored at: " << std::hex << "0x" << &this->m_B[0] << "\n";
				 std::cout << "Last  element stored at: " << std::hex << "0x" << &this->m_B[this->m_LDB * this->m_M] << "\n";
				 std::cout << "Subtotal memory allocated: " << static_cast<R64>((this->m_LDB * this->m_M * sizeof(R64)) / 1024.0 << " KiB. \n\n";
				 std::cout << "Dumping m_NBLK statistics. \n";
				 std::cout << "Total loop iterations: " << this->m_N << "\n";
				 std::cout << "Base memory address m_NLBK: " << std::hex << "0x" << &this->m_NBLK << "\n";
				 std::cout << "First element stored at: " << std::hex << "0x" << &this->m_NBLK[0] << "\n";
				 std::cout << "Last element stored at: " << std::hex << "0x" << &this->m_NBLK[this->m_N] << "\n";
				 std::cout << "Subtotal memory allocated: " << static_cast<R64>(this->m_N * sizeof(I32)) / 1024.0 << " KiB. \n\n";
			 }

#endif

			

			 // Accessors.
			 // Only In/Out pointers to array members are returned.

			 inline  R64*	getm_A() {
				 return (this->m_A);
			 }

			 inline  R64*   getm_B() {
				 return (this->m_B);
			 }

			 inline I32     getm_NCONT() {
				 return (this->m_NCONT);
			 }

			 inline I32     getm_INDCON() {
				 return (this->m_INDCON);
			 }

			 inline I32*    getm_NBLK() {
				 return (this->m_NBLK);
			 }

			 inline R64*    getm_Z() {
				 return (this->m_Z);
			 }

			 inline R64*    getm_TAU() {
				 return (this->m_TAU);
			 }

			 // Member functions, mainly helpers.

			 const std::string  obj_type()const {
				 return (std::string{ typeid(*this).name() });
			 }

			 static const std::string time_complex() {
				 return (std::string{ "Complexity of AB01ND = ~O(N^3)" });
			 }

			 static std::pair<std::string, std::string> time_stamp() {
				 return (std::make_pair(std::string{ __DATE__ }, std::string{__TIME__}));
			 }

			 // Creates struct members name - address map.
			 std::map<std::string, std::size_t> name_address_map()const {
					std::map<std::string,std::size_t> addr_map;
					addr_map["this at: "] = reinterpret_cast<std::size_t>(&this);
					addr_map["this->m_JOBZ at: "] = reinterpret_cast<std::size_t>(&this->m_JOBZ);
					addr_map["this->m_N at: "] = reinterpret_cast<std::size_t>(&this->m_N);
					addr_map["this->m_M at: "] = reinterpret_cast<std::size_t>(&this->m_M);
					addr_map["this->m_LDA at: "] = reinterpret_cast<std::size_t>(&this->m_LDA);
					addr_map["this->m_A at: "] = reinterpret_cast<std::size_t>(&this->m_A);
					addr_map["this->m_LDB at: "] = reinterpret_cast<std::size_t>(&this->m_LDB);
					addr_map["this->m_B at: "] = reinterpret_cast<std::size_t>(&this->m_B);
					addr_map["this->m_NCONT at: "] = reinterpret_cast<std::size_t>(&this->m_NCONT);
					addr_map["this->m_INDCON at: "] = reinterpret_cast<std::size_t>(&this->m_INDCON);
					addr_map["this->m_NBLK at: "] = reinterpret_cast<std::size_t>(&this->m_NBLK);
					addr_map["this->m_LDZ at: "] = reinterpret_cast<std::size_t>(&this->m_LDZ);
					addr_map["this->m_Z at: "] = reinterpret_cast<std::size_t>(&this->m_Z);
					addr_map["this->m_TAU: "] = reinterpret_cast<std::size_t>(&this->m_TAU);
					addr_map["this->m_TOL at: "] = reinterpret_cast<std::size_t>(&this->m_TOL);
					addr_map["this->m_IWORK at: "] = reinterpret_cast<std::size_t>(&this->m_IWORK);
					addr_map["this->m_LDWORK at: "] = reinterpret_cast<std::size_t>(&this->m_LDWORK);
					addr_map["this->m_DWORK at: "] = reinterpret_cast<std::size_t>(&this->m_DWORK);
					addr_map["this->m_INFO at: "] = reinterpret_cast<std::size_t>(&this->m_INFO);
					return (addr_map);
					

			 }

			 // Initialize input arrays A and B.
			 // Dimension: Arrays A and B must have a size
			 // equal to members m_LDA * m_N and m_LDB * m_M.
			 void  init_input_arrays(_In_ R64* __restrict A,
									 _In_ R64* __restrict B){
									 
									
					
				 if (A && B) {
					 for (I32 i{ 0 }; i != this->m_LDA; ++i) {
						 for (I32 j{ 0 }; j != this->m_N; ++j) {
							 this->m_A[i + this->m_LDA * j] = A[i + this->m_LDA * j];
						 }
					 }

					 for (I32 i{ 0 }; i != this->m_LDB; ++i) {
						 for (I32 j{ 0 }; j != this->m_M; ++j) {
							 this->m_B[i + this->m_LDB * j] = A[i + this->m_LDB * j];
						 }
					 }
				 }
				 else {
					 std::cerr << "Fatal error in F77_AB01ND::init_input_arrays!! \n";
					 A == nullptr ? std::cerr << "A contains invalid mem address: " << std::hex << "0x" << A << "\n" : 
						 std::cerr << "A constains valid mem address: " << std::hex << "0x"<< A << "\n";
					 B == nullptr ? std::cerr << "B contains invalid mem address: " << std::hex  << "0x" << B << "\n" : 
						 std::cerr << "B contains valid mem address: " << std::hex << "0x" << B << "\n";
					 std::cerr << "Calling exit... \n";
					 std::exit(1);
				 }
			 }

			 void    Call_AB01ND() {
				 // Call F77 AB01ND subroutine.
				 AB01ND(&this->m_JOBZ, &this->m_N, &this->m_M, &this->m_A[0], &this->m_LDA,
					 &this->m_B[0], &this->m_LDB, &this->m_NCONT, &this->m_INDCON, &this->m_NBLK[0],
					 &this->m_Z[0], &this->m_LDZ, &this->m_TAU[0], &this->m_TOL, &this->m_IWORK[0],
					 &this->m_DWORK[0], &this->m_LDWORK, &this->m_INFO);
			 }
			 

					



				 //Member variables:

				 UC8   m_JOBZ;

				 I32   m_N;

				 I32   m_M;

				 I32   m_LDA;

		_Inout_  R64*   m_A;
					
				 I32    m_LDB;

		_Inout_  R64*   m_B;

		_Out_    I32    m_NCONT;

		_Out_    I32    m_INDCON;

		_Out_    I32*   m_NBLK;

				 I32    m_LDZ;

		_Out_    R64*   m_Z;

		_Out_    R64*   m_TAU;

				 R64    m_TOL;

				 I32*   m_IWORK;

				 I32    m_LDWORK;

				 R64*   m_DWORK;

				 I32    m_INFO;






		 };

	}
}




#endif /*__SLICOT_AB01ND_H__*/