
#ifndef __SLICOT_AB01OD_H__
#define __SLICOT_AB01OD_H__

//Code: struct declaration: Tab * 2
//Code: members definition: Tab * 3

// File version granularity
#ifndef SLICOT_AB01OD_VERSION_MAJOR
#define SLICOT_AB01OD_VERSION_MAJOR 1
#endif

#ifndef SLICOT_AB01OD_VERSION_MINOR 
#define SLICOT_AB01OD_VERSION_MINOR 0
#endif

#ifndef SLICOT_AB01OD_PATCH_VERSION
#define SLICOT_AB01OD_PATCH_VERSION 0
#endif

#ifndef SLICOT_AB01OD_CREATE_DATE
#define SLICOT_AB01OD_CREATE_DATE "Date: 2016-09-15 Time: 09:49 AM GMT+2"
#endif

// Set this to successful build date/time.
#ifndef SLICOT_AB01OD_BUILD_DATE
#define SLICOT_AB01OD_BUILD_DATE " "
#endif

#include "Slicot_F77_Interface.h"
#include "Config.h"
#include "std_headers.h"

// Local defines
#define HLINES "---------------------------\n"
#define ELEMS "element's address:   element's value:   \n"
namespace guidance {
	namespace slicot_wrappers {


		template<typename R64 = double,
				 typename I32 = int,
				 typename UC8 = unsigned char>   struct F77_AB01OD{

						

						// Constructors and Destructor.
						// Main Ctor instantiates and 
						// zero-initializes  array members.
					 F77_AB01OD(_In_ const UC8 STAGES,
					            _In_ const UC8 JOBU,
					            _In_ const UC8 JOBV,
					            _In_ const I32 N,
					            _In_ const I32 M,
					            _In_ const I32 LDA,
					            _In_ const I32 LDB,
					            _In_ const I32 LDU,
					            _In_ const I32 LDV,
					            _In_ const I32 NCONT,
					            _In_ const I32 INDCON,
					            _In_ const R64 TOL,
					            _In_ const I32 LDWORK,
					            _In_ const I32 INFO)
					 :

					 m_STAGES{ STAGES },
					 m_JOBU{ JOBU },
					 m_JOBV{ JOBV },
					 m_N{ N },
					 m_M{ M },
					 m_LDA{ LDA },
					 m_A{ new R64[m_LDA * m_N] },
					 m_LDB{ LDB },
					 m_B{ new R64[m_LDB * m_M] },
					 m_LDU{ LDU },
					 m_U{ new R64[m_LDU * m_N] },
					 m_LDV{ LDV },
					 m_V{ new R64[m_LDV * m_M] },
					 m_NCONT{ NCONT },
					 m_INDCON{ INDCON },
					 m_KSTAIR{ new I32[m_N] },
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
									 this->m_A[i + this->m_LDA * j] = 0.0L
								 }
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Constructor: \n";
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
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_B: " << std::hex << this->m_B << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 if (this->m_U != nullptr) {
							 for (I32 i{ 0 }; i != this->m_LDU; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
								 for (I32 j{ 0 }; j != this->m_N; ++j) {
									 this->m_U[i + this->m_LDU * j] = 0.0L;
								 }
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_U: " << std::hex << this->m_U << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 if (this->m_V != nullptr) {
							 for (I32 i{ 0 }; i != this->m_LDV; ++i) {
#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
								 for (I32 j{ 0 }; j != this->m_M; ++j) {
									 this->m_V[i + this->m_LDV * j] = 0.0L;
								 }
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_V: " << std::hex << this->m_V << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 if (this->m_KSTAIRS != nullptr) {
							 for (I32 i{ 0 }; i != this->m_N; ++i) {
								 this->m_KSTAIRS[i] = 0;
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_KSTAIRS: " << std::hex << this->m_KSTAIRS << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 if (this->m_IWORK != nullptr) {
							 for (I32 i{ 0 }; i != this->m_M; ++i) {
								 this->m_IWORK[i] = 0;
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Constructor: \n";
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
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Constructor: \n";
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
						 std::cerr << "Execution inside 1st Constructor body of type: " << this->obj_type() << "\n";
						 std::cerr << "File: " << __FILE__ << "\n";
						 std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
						 std::cerr << "Code-line: " << __LINE__ << "\n";
						 std::cerr << "Exiting 1st Constructor body!! \n";
						 std::cerr << "****************************************\n";
#endif
					 }

					 // Second Constructor fully initializes
					 // an object to be passed later to
					 // AB01OD subroutine.
					 // Notice:
					 // Size of array R64* A must be equal to LDA.
					 // Size of array R64* B must be equal to LDB.
					 // Size of array R64* U must be equal to LDU.
					 // Size of array I32* KSTAIRS must be equal to N.
					 F77_AB01OD(_In_ const UC8 STAGES,
						        _In_ const UC8 JOBU,
						        _In_ const UC8 JOBV,
						        _In_ const I32 N,
						        _In_ const I32 M,
						        _In_ const I32 LDA,
						        _In_ R64* __restrict A,
						        _In_ const I32 LDB,
						        _In_ R64* __restrict B,
						        _In_ const I32 LDU,
						        _In_ R64* __restrict U,
						        _In_ const I32 LDV,
						        _In_ const I32 NCONT,
						        _In_ const I32 INDCON,
						        _In_ I32* __restrict KSTAIRS,
						        _In_ const R64 TOL,
						        _In_ const I32 LDWORK,
						        _In_ const I32 INFO)
						 :
						 m_STAGES{ STAGES },
						 m_JOBU{ JOBU },
						 m_JOBV{ JOBV },
						 m_N{ N },
						 m_M{ M },
						 m_LDA{ LDA },
						 m_A{ new R64[m_LDA * m_N] },
						 m_LDB{ LDB },
						 m_B{ new R64[m_LDB * m_M] },
						 m_LDU{ LDU },
						 m_U{ new R64[m_LDU * m_N] },
						 m_LDV{ LDV },
						 m_LDV{ new R64[m_LDV * m_M] },
						 m_NCONT{ NCONT },
						 m_INDCON{ INDCON },
						 m_KSTAIRS{ new I32[m_N] },
						 m_TOL{ TOL },
						 m_IWORK{ new I32[m_M] },
						 m_LDWORK{ LDWORK },
						 m_DWORK{ new R64[LDWORK] },
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
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD 2nd Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 this->m_A == nullptr ? std::cerr << "Failure allocation in this->m_A: " << std::hex << this->m_A << "\n" : 
								 std::cerr << "this->m_A contains valid address\n";
							 A == nullptr ?  std::cerr << "Failure allocation in A: " << std::hex << A << "\n" : 
								 std::cerr << "A contains valid address\n";
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
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD 2nd Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 this->m_B == nullptr ? std::cerr << "Failure in this->m_B: " << std::hex << this->m_B << "\n" :
								 std::cerr << "this->m_B contains valid address\n";
							 B == nullptr ? std::cerr << "Failure in B: " << std::hex << B << "\n" :
								 std::cerr << "B contains valid address\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1)
						 }
						 if ((this->m_U != nullptr) && (U != nullptr)) {
							 for (I32 i{ 0 }; i != this->m_LDU; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch U:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
								 for (I32 j{ 0 }; j != this->m_N; ++j) {
									 this->m_U[i + this->m_LDU * j] = U[i + this->m_LDU * j];
								 }
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD 2nd Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 this->m_U == nullptr ? std::cerr << "Failure in this->m_U: " << std::hex << this->m_U << "\n" :
								 std::cerr << "this->m_U contains valid address\n";
							 U == nullptr ? std::cerr << "Failure in U: " << std::hex << U << "\n" :
								 std::cerr << "U contains valid address\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1)
						 }
						 if (this->m_V != nullptr) {
							 for (I32 i{ 0 }; i != this->m_LDV; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch this->m_V:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
								 for (I32 j{ 0 }; i != this->m_M; ++j) {
									 this->m_V[i + this->m_LDV * j] = 0.0L;
								 }
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD 2nd Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_U: " << std::hex << this->m_U << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 if ((this->m_KSTAIRS != nullptr) && (KSTAIRS != nullptr)) {
							 if (this->m_STAGES == 'B') {
								 for (I32 i{ 0 }; i != this->m_N; ++i) {
									 this->m_KSTAIRS[i] = KSTAIRS[i];
								 }
							 }
							 else {
								 for (I32 i{ 0 }; i != this->m_N; ++i) {
									 this->m_KSTAIRS[i] = 0;
								 }
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD 2nd Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 this->m_KSTAIRS == nullptr ? std::cerr << "Failure in this->m_KSTAIRS: " << std::hex << this->m_KSTAIRS << "\n" :
								 std::cerr << "this->m_KSTAIRS contains valid address\n";
							 KSTAIRS == nullptr ? std::cerr << "Failure in KSTAIRS: " << std::hex << KSTAIRS << "\n" :
								 std::cerr << "KSTAIRS contains valid address\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1)
						 }
						 if (this->m_IWORK != nullptr) {
							 for (I32 i{ 0 }; i != this->m_M; ++i) {
								 this->m_IWORK[i] = 0;
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD 2nd Constructor: \n";
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
							 for (I32 i{ 0 }; i != this->m_LDWORK; ++i) {
								 this->m_DWORK[i] = 0.0L;
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD 2nd Constructor: \n";
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
						 std::cerr << "Execution inside 2nd Constructor body of type: " << this->obj_type() << "\n";
						 std::cerr << "File: " << __FILE__ << "\n";
						 std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
						 std::cerr << "Code-line: " << __LINE__ << "\n";
						 std::cerr << "Exiting 2nd Constructor body!! \n";
						 std::cerr << "****************************************\n";
#endif
					 }



					 // Copy Constructor implements deep copy.
					 F77_AB01OD(_In_ const F77_AB01OD &other)
						 :
						 m_STAGES{ other.m_STAGES },
						 m_JOBU{ other.m_JOBU },
						 m_JOBV{ other.m_JOBV },
						 m_N{ other.m_N },
						 m_M{ other.m_M },
						 m_LDA{ other.m_LDA },
						 m_A{ new R64[m_LDA * m_N] },
						 m_LDB{ other.m_LDB },
						 m_B{ new R64[m_LDB * m_M] },
						 m_LDU{ other.m_LDU },
						 m_U{ new R64[m_LDU * m_N] },
						 m_LDV{ other.m_LDV },
						 m_V{ new R64[m_LDV * m_M] },
						 m_NCONT{ other.m_NCONT },
						 m_INDCON{ other.m_INDCON },
						 m_KSTAIR{ new I32[m_N] },
						 m_TOL{ other.m_TOL },
						 m_IWORK{ new I32[m_M] },
						 m_LDWORK{ other.m_LDWORK },
						 m_DWORK{ new R64[m_LDWORK] },
						 m_INFO{ other.m_INFO } {


						 if (this->m_A != nullptr) {
							 for (I32 i{ 0 }; i != this->m_LDA; ++i) {
#ifdef ICC_PREFETCH_L1

#pragma prefetch other.m_A:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
								 for (I32 j{ 0 }; k != this->m_N; ++j) {
									 this->m_A[i + this->m_LDA * j] = other.m_A[i + other.m_LDA * j];
								 }
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Copy Constructor: \n";
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
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_B:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
								 for (I32 j{ 0 }; j != this->m_M; ++j) {
									 this->m_B[i + this->m_LDB * j] = other.m_B[i + other.m_LDB * j];
								 }
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Copy Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_B: " << std::hex << this->m_B << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 if (this->m_U != nullptr) {
							 for (I32 i{ 0 }; i != this->m_LDU; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_U:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
								 for (I32 j{ 0 }; j != this->m_N; ++j) {
									 this->m_U[i + this->m_LDU * j] = other.m_U[i + other.m_LDU * j];
								 }
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Copy Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_U: " << std::hex << this->m_U << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 if (this->m_V != nullptr) {
							 for (I32 i{ 0 }; i != this->m_LDV; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_U:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
								 for (I32 j{ 0 }; j != this->m_M; ++j) {
									 this->m_V[i + this->m_LDV * j] = other.m_V[i + other.m_LDV * j];
								 }
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Copy Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_V: " << std::hex << this->m_V << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 if (this->m_KSTAIRS != nullptr) {
							 for (I32 i{ 0 }; i != this->m_N; ++i) {
								 this->m_KSTAIRS[i] = other.m_KSTAIRS[i];
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Copy Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_KSTAIRS: " << std::hex << this->m_KSTAIRS << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 if (this->m_IWORK != nullptr) {
							 for (I32 i{ 0 }; i != this->m_M; ++i) {
								 this->m_IWORK[i] = other.m_IWORK[i];
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Copy Constructor: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "this->m_IWORK: " << std::hex << this->m_IWORK << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_U:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
						 if (this->m_DWORK != nullptr) {
							 for (I32 i{ 0 }; i != this->m_LDWORK; ++i) {
								 this->m_DWORK[i] = other.m_DWORK[i];
							 }
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Copy Constructor: \n";
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
						 std::cerr << "Execution inside Copy-Constructor body of type: " << this->obj_type() << "\n";
						 std::cerr << "File: " << __FILE__ << "\n";
						 std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
						 std::cerr << "Code-line: " << __LINE__ << "\n";
						 std::cerr << "Exiting Copy-Constructor body!! \n";
						 std::cerr << "****************************************\n";
#endif
					 }
					 
					 // Move Constructor implements  shallow copy.
					 F77_AB01OD(_In_ F77_AB01OD &&other)
						 :
						 m_STAGES{ other.m_STAGES },
						 m_JOBU{ other.m_JOBU },
						 m_JOBV{ other.m_JOBV },
						 m_N{ other.m_N },
						 m_M{ other.m_M },
						 m_LDA{ other.m_LDA },
						 m_A{ other.m_A },
						 m_LDB{ other.m_LDB },
						 m_B{ other.m_B },
						 m_LDU{ other.m_LDU },
						 m_U{ other.m_U },
						 m_LDV{ other.m_LDV },
						 m_V{ other.m_V },
						 m_NCONT{ other.m_NCONT },
						 m_INDCON{ other.m_INDCON },
						 m_KSTAIRS{ other.m_KSTAIRS },
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
						 other.m_LDU = 0;
						 other.m_U = nullptr;
						 other.m_LDV = 0;
						 other.m_V = nullptr;
						 other.m_KSTAIRS = nullptr;
						 other.m_IWORK = nullptr;
						 other.m_LDWORK = 0;
						 other.m_DWORK = nullptr;
#if defined(GUIDANCE_DEBUG_ON)
						 std::cerr << "****************************************\n";
						 std::cerr << "Debug mode: ON \n";
						 std::cerr << "Date: " << this->time_stamp().first << "\n";
						 std::cerr << "Time: " << this->time_stamp().second << "\n";
						 std::cerr << "Execution inside Move-Constructor body of type: " << this->obj_type() << "\n";
						 std::cerr << "File: " << __FILE__ << "\n";
						 std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
						 std::cerr << "Code-line: " << __LINE__ << "\n";
						 std::cerr << "Exiting Move-Constructor body!! \n";
						 std::cerr << "****************************************\n";
#endif
					 }

					 // Destructor.
					 ~F77_AB01OD() {

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
						 if (this->m_U) {
							 delete[] this->m_U;
							 this->m_U = nullptr;
							 this->m_LDU = 0;
						 }
						 if (this->m_V) {
							 delete[] this->m_V;
							 this->m_V = nullptr;
							 this->m_LDV = 0;
						 }
						 if (this->m_KSTAIRS) {
							 delete[] this->m_KSTAIRS;
							 this->m_KSTAIRS = nullptr;
						 }
						 if (this->m_IWORK) {
							 delete[] this->m_IWORK;
							 this->m_IWORK = nullptr;
						 }
						 if (this->m_DWORK) {
							 delete[] this->m_DWORK;
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

					 // operators
					 F77_AB01OD &  operator=(_In_ const F77_AB01OD &other) {
						 if (this == &other) return (*this);

						 this->m_STAGES = other.m_STAGES;
						 this->m_JOBU = other.m_JOBU;
						 this->m_JOBV = other.m_JOBV;
						 this->m_N = other.m_N;
						 this->m_M = other.m_M;
						 this->m_LDA = other.m_LDA;
						 R64 *tA = new R64[this->m_LDA * this->m_N];
						 if (tA) {
							 for (I32 i{ 0 }; i != this->m_LDA; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_A:0:L1_VEC_ITERS_SHORT
#endif

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
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Copy-Assign operator: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "tA: " << std::hex << tA << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 this->m_LDB = other.m_LDB;
						 R64 *tB = new R64[this->m_LDB * this->m_M];
						 if (tB) {
							 for (I32 i{ 0 }; i != this->m_LDB; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_B:0:L1_VEC_ITERS_SHORT
#endif

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
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Copy-Assign operator: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "tB: " << std::hex << tB << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 this->m_LDU = other.m_LDU;
						 R64 *tU = new R64[this->m_LDU * this->m_N];
						 if (tU) {
							 for (I32 i{ 0 }; i != this->m_LDU; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_U:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
								 for (I32 j{ 0 }; j != this->m_N; ++j) {
									 tU[i + this->m_LDU * j] = other.m_U[i + other.m_LDU * j];
								 }
							 }
							 delete[] this->m_U;
							 this->m_U = tU;
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Copy-Assign operator: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "tU: " << std::hex << tU << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 this->m_LDV = other.m_LDV;
						 R64 *tV = new R64[this->m_LDV * this->m_M];
						 if (tV) {
							 for (I32 i{ 0 }; i != this->m_LDV; ++i) {
#ifdef ICC_PREFETCH_L1
#pragma prefetch other.m_V:0:L1_VEC_ITERS_SHORT
#endif

#ifdef ICC_AUTO_VECTORISE
#pragma ivdep
#pragma simd
#pragma unroll(4)

#endif
								 for (I32 j{ 0 }; j != this->m_M; ++j) {
									 tV[i + this->m_LDV * j] = other.m_V[i + other.m_LDV * j];
								 }
							 }
							 delete[] this->m_V;
							 this->m_V = tV;
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Copy-Assign operator: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "tV: " << std::hex << tV << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 this->m_NCONT = other.m_NCONT;
						 this->m_INDCON = other.m_INDCON;
						 I32 *tKSTAIRS = new I32[this->m_N];
						 if (tKSTAIRS) {
							 for (I32 i{ 0 }; i != this->m_N; ++i) {
								 tKSTAIRS[i] = other.m_KSTAIRS[i];
							 }
							 delete[] this->m_KSTAIRS;
							 this->m_KSTAIRS = tKSTAIRS;
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Copy-Assign operator: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "tKSTAIRS: " << std::hex << tKSTAIRS << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 this->m_TOL = other.m_TOL;
						 I32 *tIWORK = new I32[this->m_M];
						 if (tIWORK) {
							 for (I32 i{ 0 }; i != this->m_M; ++i) {
								 tIWORK[i] = other.m_IWORK[i];
							 }
							 delete[] this->m_IWORK;
							 this->m_IWORK = tIWORK;
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Copy-Assign operator: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "tIWORK: " << std::hex << tIWORK << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 this->m_LDWORK = other.m_LDWORK;
						 R64 *tDWORK = new R64[this->m_LDWORK];
						 if (tDWORK) {
							 for (I32 i{ 0 }; i != this->m_LDWORK; ++i) {
								 tDWORK[i] = other.m_DWORK[i];
							 }
							 delete[] this->m_DWORK;
							 this->m_DWORK = tDWORK;
						 }
						 else {
							 std::cerr << "Fatal Error: Invalid pointer in F77_AB01OD Copy-Assign operator: \n";
							 std::cerr << "At date: " << __DATE__ << " , " << "At time: " << __TIME__ << "\n";
							 std::cerr << "In file: " << __FILE__ << "\n";
							 std::cerr << "At virtual address: " << "0x" << std::hex << __FUNCTIONW__ << "\n";
							 std::cerr << "In code-line: " << __LINE__ << "\n";
							 std::cerr << "Error details: \n";
							 std::cerr << "tDWORK: " << std::hex << tDWORK << "\n";
							 std::cerr << "Calling std::exit!! \n";
							 std::exit(1);
						 }
						 this->m_INFO = other.m_INFO;
#if defined(GUIDANCE_DEBUG_ON)
						 std::cerr << "****************************************\n";
						 std::cerr << "Debug mode: ON \n";
						 std::cerr << "Date: " << this->time_stamp().first << "\n";
						 std::cerr << "Time: " << this->time_stamp().second << "\n";
						 std::cerr << "Execution inside Copy-Assign operator body of type: " << this->obj_type() << "\n";
						 std::cerr << "File: " << __FILE__ << "\n";
						 std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
						 std::cerr << "Code-line: " << __LINE__ << "\n";
						 std::cerr << "Exiting Copy-Assign operator body!! \n";
						 std::cerr << "****************************************\n";
#endif
						 return (*this);
					 }

					 // Move-Assign operator implements shallow copy.
					 F77_AB01OD &  operator=(_In_ F77_AB01OD &&other) {
						 if (this == &other) return (*this);

						 this->m_STAGES = other.m_STAGES;
						 this->m_JOBU = other.m_JOBU;
						 this->m_JOBV = other.m_JOBV;
						 this->m_N = other.m_N;
						 this->m_M = other.m_M;
						 this->m_LDA = other.m_LDA;
						 delete[] this->m_A;
						 this->m_A = other.m_A;
						 other.m_A = nullptr;
						 other.m_LDA = 0;
						 this->m_LDB = other.m_LDB;
						 delete[] this->m_B;
						 this->m_B = other.m_B;
						 other.m_B = nullptr;
						 other.m_LBA = 0;
						 this->m_LDU = other.m_LDU;
						 delete[] this->m_U;
						 this->m_U = other.m_U;
						 other.m_U = nullptr;
						 other.m_LDU = 0;
						 this->m_LDV = other.m_LDV;
						 delete[] this->m_V;
						 this->m_V = other.m_V;
						 other.m_V = nullptr;
						 other.m_LDV = 0;
						 this->m_NCONT = other.m_NCONT;
						 this->m_INDCON = other.m_INDCON;
						 delete[] this->m_KSTAIRS;
						 this->m_KSTAIRS = other.m_KSTAIRS;
						 other.m_KSTAIRS = nullptr;
						 this->m_TOL = other.m_TOL;
						 delete[] this->m_IWORK;
						 this->m_IWORK = other.m_IWORK;
						 other.m_IWORK = nullptr;
						 this->m_LDWORK = other.m_LDWORK;
						 delete[] this->m_DWORK;
						 this->m_DWORK = other.m_DWORK;
						 other.m_DWORK = nullptr;
						 other.m_LDWORK = 0;
						 this->m_INFO = other.m_INFO;
#if defined(GUIDANCE_DEBUG_ON)
						 std::cerr << "****************************************\n";
						 std::cerr << "Debug mode: ON \n";
						 std::cerr << "Date: " << this->time_stamp().first << "\n";
						 std::cerr << "Time: " << this->time_stamp().second << "\n";
						 std::cerr << "Execution inside Move-Assign operator body of type: " << this->obj_type() << "\n";
						 std::cerr << "File: " << __FILE__ << "\n";
						 std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
						 std::cerr << "Code-line: " << __LINE__ << "\n";
						 std::cerr << "Exiting Move-Assign operator body!! \n";
						 std::cerr << "****************************************\n";
#endif
						 return (*this);
					 }

					 // Accessors.
					 // Only pointers to In/Out member arrays are returned.
					 inline R64*  getm_A() {
						 return (this->m_A);
					 }

					 inline R64*  getm_B() {
						 return (this->m_B);
					 }

					 inline R64*  getm_U() {
						 return (this->m_U);
					 }

					 inline R64*  getm_V() {
						 return (this->m_V);
					 }

					 inline I32*  getm_KSTAIRS() {
						 return (this->m_KSTAIRS);
					 }

					 //Member functions.

					 const std::string  obj_type()const {
						 return (std::string(typeid(*this).name()));
					 }

					 // Creates map of member names and corresponding
					 // addresses. Addresses are converted to decimal
					 // representation.
					 std::map<std::string, std::size_t> name_address_map()const {
						 std::map<std::string,std::size_t> m_map;
						 m_map["this at: "] = reinterpret_cast<std::size_t>(&this);
						 m_map["m_STAGES at: "] = reinterpret_cast<std::size_t>(&this->m_STAGES);
						 m_map["m_JOBU at: "] = reinterpret_cast<std::size_t>(&this->m_JOBU);
						 m_map["m_JOBV at: "] = reinterpret_cast<std::size_t>(&this->m_JOBV);
						 m_map["m_N at: "] = reinterpret_cast<std::size_t>(&this->N);
						 m_map["m_M at: "] = reinterpret_cast<std::size_t>(&this->m_M);
						 m_map["m_LDA at:"] = reinterpret_cast<std::size_t>(&this->m_LDA);
						 m_map["m_A at: "] = reinterpret_cast<std::size_t>(&this->m_A);
						 m_map["m_LDB at: "] = reinterpret_cast<std::size_t>(&this->m_LDB);
						 m_map["m_B at: "] = reinterpret_cast<std::size_t>(&this->m_B);
						 m_map["m_LDU at: "] = reinterpret_cast<std::size_t>(&this->m_LDU);
						 m_map["m_U at: "] = reinterpret_cast<std::size_t>(&this->m_U);
						 m_map["m_LDV at: "] = reinterpret_cast<std::size_t>(&this->m_LDV);
						 m_map["m_V at: "] = reinterpret_cast<std::size_t>(&this->m_V);
						 m_map["m_NCONT at: "] = reinterpret_cast<std::size_t>(&this->m_NCONT);
						 m_map["m_INDCON at: "] = reinterpret_cast<std::size_t>(&this->m_INDCON);
						 m_map["m_KSTAIRS at: "] = reinterpret_cast<std::size_t>(&this->m_KSTAIRS);
						 m_map["m_TOL at: "] = reinterpret_cast<std::size_t>(&this->m_TOL);
						 m_map["m_IWORK at: "] = reinterpret_cast<std::size_t>(&this->m_IWORK);
						 m_map["m_LDWORK at: "] = reinterpret_cast<std::size_t>(&this->m_LDWORK);
						 m_map["m_DWORK at: "] = reinterpret_cast<std::size_t>(&this->m_DWORK);
						 m_map["m_INFO at: "] = reinterpret_cast<std::size_t>(&this->m_INFO);
						 return (m_map);
					 }


					 static const std::string  time_complex() {
						 return (std::string("Complexity of AB01OD = ~O(N^3)"));
					 }

					 static std::pair<std::string, std::string> time_stamp() {
						 return (std::make_pair(std::string(__DATE__), std::string(__TIME__)));
					 }

					 void  Call_AB01OD() {
						// Call F77 AB01OD subroutine.

						 AB01OD(&this->m_STAGES, &this->m_JOBU, &this->m_JOBV, &this->m_N, &this->m_M,
							 &this->m_A[0], &this->m_LDA, &this->m_B[0], &this->m_LDB, &this->m_U[0], &this->m_LDU,
							 &this->m_V[0], &this->m_LDV, &this->m_NCONT, &this->m_INDCON, &this->m_KSTAIRS[0],
							 &this->m_TOL, &this->m_IWORK[0], &this->m_DWORK[0], &this->m_LDWORK, &this->m_INFO);

					 }

#if defined (GUIDANCE_DEBUG_ON)

					 void print_extended_info()const {

						 auto map = this->name_address_map();
						 std::cout << "Extended debug info of " << this->obj_type() << "\n";
						 std::cout << "Collected at date: " << this->time_stamp().first << " at time: " << this->time_stamp().second << "\n";
						 std::cout << "Dumping memory layout of " << this->obj_type() << "\n";
						 std::cout << "member name:      member address:  \n";
						 std::cout << HLINES;
						 for (auto& it : map) {
							 std::cout << it.first << " : " << it.second << "\n";
						 }
						 std::cout << HLINES;
						 std::cout << "Array members content first: \n";
						 std::cout << "Fortran-style array traversing in use. \n";
						 std::cout << "Precision fixed at " << 16 << "decimal digits. \n";
						 std::cout << "Input/Output array m_A:   \n";
						 std::cout << ELEMS;
						 std::cout << HLINES;
						 for (I32 i{ 0 }; i != this->m_LDA; ++i) {
							 for (I32 j{ 0 }; j != this->m_N; ++j) {
								 std::cout << &this->m_A[j + this->m_LDA * i] << " : " <<
									 std::fixed << std::setprecision(16) << this->m_A[j + this->m_LDA * i];
							 }
							 std::cout << "\n";
						 }
						 std::cout << HLINES;
						 std::cout << "\n";
						 std::cout << "Input/Output array m_B:    \n";
						 std::cout << ELEMS;
						 for (I32 i{ 0 }; i != this->m_LDB; ++i) {
							 for (I32 j{ 0 }; j != this->m_M; ++j) {
								 std::cout << &this->m_B[j + this->m_LDB * i] << " : " << std::fixed <<
									 std::setprecision(16) << this->m_B[j + this->m_LDB * i] << "\n";
							 }
							 std::cout << "\n";
						 }
						 std::cout << HLINES;
						 std::cout << "\n";
						 std::cout << "Input/Output array m_U:     \n";
						 std::cout << ELEMS;
						 for (I32 i{ 0 }; i != this->m_LDU; ++i) {
							 for (I32 j{ 0 }; j != this->m_N; ++j) {
								 std::cout << &this->m_U[j + this->m_LDU * i] << " : " << std::fixed <<
									 std::setprecision(16) << this->m_U[j + this->m_LDU * i] << "\n";
							 }
							 std::cout << "\n";
						 }
						 std::cout << HLINES;
						 std::cout << "\n";
						 std::cout << "Output array m_V:          \n";
						 std::cout << ELEMS;
						 for (I32 i{ 0 }; i != this->m_LDV; ++i) {
							 for (I32 j{ 0 }; j != this->m_M; ++j) {
								 std::cout << &this->m_V[j + this->m_LDV * i] << " : " << std::fixed <<
									 std::setprecision(16) << this->m_V[j + this->m_LDV * i] << "\n";
							 }
							 std::cout << "\n";
						 }
						 std::cout << HLINES;
						 std::cout << "\n";
						 std::cout << "Input/Output array m_KSTAIR:  \n";
						 std::cout << ELEMS;
						 for (I32 i{ 0 }; i != this->m_N; ++i) {
							 std::cout << &this->m_KSTAIRS[i] << " : " << this->m_KSTAIRS[i] << "\n";
						 }
						 std::cout << HLINES;
						 std::cout << "\n";
						 if (this->m_STAGES != 'B') {
							 std::cout << "Work array m_IWORK:      \n";
							 std::cout << ELEMS;
							 for (I32 i{ 0 }; i != this->m_M; ++i) {
								 std::cout << &this->m_IWORK[i] << " : " << this->m_IWORK[i] << "\n";
							 }
							 std::cout << HLINES;
							 std::cout << "\n";
						 }
						 std::cout << "Work array m_DWORK:         \n";
						 std::cout << ELEMS;
						 for (I32 i{ 0 }; i != this->m_LDWORK; ++i) {
							 std::cout << &this->m_DWORK[i] << " : " << std::fixed <<
								 std::setprecision(16) << this->m_DWORK[i] << "\n";
						 }
						 std::cout << HLINES;
						 std::cout << "\n";
						 std::cout << "Statistics break-down per array: \n";
						 std::cout << "Dumping m_A statistics. \n";
						 auto felemA = reinterpret_cast<std::size_t>(&this->m_A[0]);
						 auto lelemA = reinterpret_cast<std::size_t>(&this->m_A[this->m_LDA * this->m_N]);
						 std::cout << "Total loop iterations: " << this->m_LDA * this->m_N << " cycles.\n";
						 std::cout << "Base memory address m_A: " << std::hex << "0x" << &this->m_A << "\n";
						 std::cout << "First element stored at: " << std::hex << "0x" << &this->m_A[0] << "\n";
						 std::cout << "Last  element stored at: " << std::hex << "0x" << &this->m_A[this->m_LDA * this->m_N] << "\n";
						 std::cout << "Memory addres space length: " << lelemA - felemA << " bytes.\n";
						 std::cout << "Subtotal memory allocated: " << (static_cast<R64>(this->m_LDA * this->m_N * sizeof(R64)) / 1024.0 << " KiB. \n\n";
						 std::cout << "Dumping m_B statistics. \n";
						 auto felemB = reinterpret_cast<std::size_t>(&this->m_B[0]);
						 auto lelemB = reinterpret_cast<std::size_t>(&this->m_B[this->m_LDB * this->m_M]);
						 std::cout << "Total loop iterations: " << this->m_LDB * this->m_M << "\n";
						 std::cout << "Base memory address m_B: " << std::hex << "0x" << &this->m_B << "\n";
						 std::cout << "First element stored at: " << std::hex << "0x" << &this->m_B[0] << "\n";
						 std::cout << "Last  element stored at: " << std::hex << "0x" << &this->m_B[this->m_LDB * this->m_M] << "\n";
						 std::cout << "Memory address space length: " << lelemB - felemB << " bytes.\n";
						 std::cout << "Subtotal memory allocated: " << (static_cast<R64>(this->m_LDB * this->m_M * sizeof(R64)) / 1024.0 << " KiB. \n\n";
						 std::cout << "Dumping m_U statistics. \n";
						 auto felemU = reinterpret_cast<std::size_t>(&this->m_U[0]);
						 auto lelemU = reinterpret_cast<std::size_t>(&this->m_U[this->m_LDU * this->m_N]);
						 std::cout << "Total loop iterations: " this->m_LDU * this->m_N << " cycles.\n";
						 std::cout << "Base memory address m_U: " << std::hex << "0x" << &this->m_U << "\n";
						 std::cout << "First element stored at: " << std::hex << "0x" << &this->m_U[0] << "\n";
						 std::cout << "Last element stored at : " << std::hex << "0x" << &this->m_U[this->m_LDU * this->m_N] << "\n";
						 std::cout << "Memory address space length: " << lelemU - felemU << " bytes.\n";
						 std::cout << "Subtotal memory allocated: " << (static_cast<R64>(this->m_LDU * this->m_N * sizeof(R64)) / 1024.0 << "Kib. \n\n";
					 }



#endif



						//Member variables:
						UC8   m_STAGES;

						UC8   m_JOBU;

						UC8   m_JOBV;

						I32   m_N;

						I32   m_M;

						I32   m_LDA;

				_Inout_ R64   m_A;

						I32   m_LDB;

				_Inout_ R64   m_B;

						I32   m_LDU;

				_Inout_ R64   m_U;

						I32   m_LDV;

				_Inout_ R64   m_V;

						I32   m_NCONT;

						I32   m_INDCON;

				_Inout_ I32   m_KSTAIRS;

						R64   m_TOL;

						I32   m_IWORK;

						I32   m_LDWORK;

						R64   m_DWORK;

						I32   m_INFO;



				 };


  






	}
}









#endif /*__SLICOT_AB01OD_H__*/