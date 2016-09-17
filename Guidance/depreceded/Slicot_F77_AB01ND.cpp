
#include "Slicot_F77_AB01ND.h"

// Implementation.

guidance::slicot_wrappers
::F77_AB01ND::F77_AB01ND(_In_ const unsigned char JOBZ,
                         _In_ const int N,
                         _In_ const int M,
                         _In_ const int LDA,
                         _In_ const int LDB,
                         _In_ const int NCONT,
                         _In_ const int INDCON,
                         _In_ const int LDZ,
                         _In_ const double TOL,
                         _In_ const int LDWORK,
                         _In_ const int INFO)
:
m_JOBZ{ JOBZ },
m_N{ N },
m_M{ M },
m_LDA{ LDA },
m_A(m_LDA * m_N),
m_LDB{ LDB },
m_B(m_LDB * m_M),
m_NCONT{ NCONT },
m_INDCON{ INDCON },
m_NBLK(m_N),
m_LDZ{ LDZ },
m_Z(m_LDZ * m_N),
m_TAU(m_N),
m_TOL{ TOL },
m_IWORK(m_M),
m_LDWORK{ LDWORK },
m_DWORK(m_LDWORK),
m_INFO{ INFO } {

#if defined(GUIDANCE_DEBUG_ON)
	std::cerr << "****************************************\n";
	std::cerr << "Debug mode: ON \n";
	std::cerr << "Date: " << this->timestamp().first << "\n";
	std::cerr << "Time: " << this->timestamp().second << "\n";
	std::cerr << "Execution inside 11-arg Ctor body of type: " << this->obj_type() << "\n";
	std::cerr << "File: " << __FILE__ << "\n";
	std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
	std::cerr << "Code-line: " << __LINE__ << "\n";
	std::cerr << "Exiting 18-arg Ctor body!! \n";
	std::cerr << "****************************************\n";
#endif
}

guidance::slicot_wrappers
::F77_AB01ND::F77_AB01ND(_In_ const F77_AB01ND &other)
:
m_JOBZ{ other.m_JOBZ },
m_N{ other.m_N },
m_M{ other.m_M },
m_LDA{ other.m_LDA },
m_A{ other.m_A },
m_LDB{ other.m_LDB },
m_B{ other.m_B },
m_NCONT{ other.m_NCONT },
m_INDCON{ other.m_INDCON },
m_NBLK{ other.m_NBLK },
m_LDZ{ other.m_LDZ },
m_Z{ other.m_Z },
m_TAU{ other.m_TAU },
m_TOL{ other.m_TOL },
m_IWORK{ other.m_IWORK },
m_LDWORK{ other.m_LDWORK },
m_DWORK{ other.m_DWORK },
m_INFO{ other.m_INFO } {
 
#if defined(GUIDANCE_DEBUG_ON)
	std::cerr << "****************************************\n";
	std::cerr << "Debug mode: ON \n";
	std::cerr << "Date: " << this->timestamp().first << "\n";
	std::cerr << "Time: " << this->timestamp().second << "\n";
	std::cerr << "Execution inside Copy-Ctor body of type: " << this->obj_type() << "\n";
	std::cerr << "File: " << __FILE__ << "\n";
	std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
	std::cerr << "Code-line: " << __LINE__ << "\n";
	std::cerr << "Exiting Copy-Ctor body!! \n";
	std::cerr << "****************************************\n";
#endif
}

guidance::slicot_wrappers
::F77_AB01ND::F77_AB01ND(_In_ F77_AB01ND &&other)
:
m_JOBZ{ std::move(other.m_JOBZ) },
m_N{ std::move(other.m_N) },
m_M{ std::move(other.m_M) },
m_LDA{ std::move(other.m_LDA) },
m_A{ std::move(other.m_A) },
m_LDB{ std::move(other.m_LDB) },
m_B{ std::move(other.m_B) },
m_NCONT{ std::move(other.m_NCONT) },
m_INDCON{ std::move(other.m_INDCON) },
m_NBLK{ std::move(other.m_NBLK) },
m_LDZ{ std::move(other.m_LDZ) },
m_Z{ std::move(other.m_Z) },
m_TAU{ std::move(other.m_TAU) },
m_TOL{ std::move(other.m_TOL) },
m_IWORK{ std::move(other.m_IWORK) },
m_LDWORK{ std::move(other.m_LDWORK) },
m_DWORK{ std::move(other.m_DWORK) },
m_INFO{ std::move(other.m_INFO) } {

#if defined(GUIDANCE_DEBUG_ON)
	std::cerr << "****************************************\n";
	std::cerr << "Debug mode: ON \n";
	std::cerr << "Date: " << this->timestamp().first << "\n";
	std::cerr << "Time: " << this->timestamp().second << "\n";
	std::cerr << "Execution inside Move-Ctor body of type: " << this->obj_type() << "\n";
	std::cerr << "File: " << __FILE__ << "\n";
	std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
	std::cerr << "Code-line: " << __LINE__ << "\n";
	std::cerr << "Exiting Move-Ctor body!! \n";
	std::cerr << "****************************************\n";
#endif
}

guidance::slicot_wrappers::F77_AB01ND & 
guidance::slicot_wrappers::F77_AB01ND::operator=(_In_ const F77_AB01ND &other) {
	if (this == &other) return (*this);
	F77_AB01ND temp{other};
	std::swap(*this,temp);
#if defined(GUIDANCE_DEBUG_ON)
	std::cerr << "****************************************\n";
	std::cerr << "Debug mode: ON \n";
	std::cerr << "Date: " << this->timestamp().first << "\n";
	std::cerr << "Time: " << this->timestamp().second << "\n";
	std::cerr << "Execution inside body of Copy-Assign operator of type: " << this->obj_type() << "\n";
	std::cerr << "File: " << __FILE__ << "\n";
	std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
	std::cerr << "Code-line: " << __LINE__ << "\n";
	std::cerr << "Exiting Copy-Assign operator body!! \n";
	std::cerr << "****************************************\n";
#endif
	return (*this);
}

guidance::slicot_wrappers::F77_AB01ND &
guidance::slicot_wrappers::F77_AB01ND::operator=(_In_ F77_AB01ND &&other) {
	if (this == &other) return (*this);
	*this = std::move(other);
#if defined(GUIDANCE_DEBUG_ON)
	std::cerr << "****************************************\n";
	std::cerr << "Debug mode: ON \n";
	std::cerr << "Date: " << this->timestamp().first << "\n";
	std::cerr << "Time: " << this->timestamp().second << "\n";
	std::cerr << "Execution inside body of Move-Assign operator of type: " << this->obj_type() << "\n";
	std::cerr << "File: " << __FILE__ << "\n";
	std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
	std::cerr << "Code-line: " << __LINE__ << "\n";
	std::cerr << "Exiting Move-Assign operator body!! \n";
	std::cerr << "****************************************\n";
#endif
	return (*this);
}

std::ostream &  guidance::slicot_wrappers::operator<<(_In_ std::ostream &os,
	                   _In_ const guidance::slicot_wrappers::F77_AB01ND &rhs) {
				
	std::cout << "Dumping context of object: " << rhs.obj_type() << "\n";
	std::cout << "At date: " << rhs.timestamp().first << "\n";
	std::cout << "At time: " << rhs.timestamp().second << "\n";
	std::cout << "Array members content first: \n";
	std::cout << "C-style array traversing in use. \n";
	std::cout << "Precision fixed at " << 16 << "decimal digits. \n";
	std::cout << "Input/Output array A:   \n";
	std::cout << "-----------\n";
	for (int i{ 0 }; i != rhs.m_LDA; ++i) {
		for (int j{ 0 }; j != rhs.m_N; ++j) {
			os << std::fixed << std::setprecision(16) <<
				rhs.m_A[i + rhs.m_LDA * j] << "\n";
		}
		os << "\n";
	}
	std::cout << "------------\n";
	std::cout << "Input/Ouput array B:      \n";
	std::cout << "-------------\n";
	for (int i{ 0 }; i != rhs.m_LDB; ++i) {
		for (int j{ 0 }; j != rhs.m_M; ++j) {
			os << std::fixed << std::setprecision(16) <<
				rhs.m_B[i + rhs.m_LDB * j] << "\n";
		}
		os << "\n";
	}
	std::cout << "-------------\n";
	std::cout << "Output array NBLK:         \n";
	std::cout << "-------------\n";
	for (int i{ 0 }; i != rhs.m_N; ++i) {
		os << rhs.m_NBLK[i] << "\n";
			
	}
	std::cout << "--------------\n";
	std::cout << "Output array  Z:            \n";
	std::cout << "--------------\n";
	for (int i{ 0 }; i != rhs.m_LDZ; ++i) {
		for (int j{ 0 }; j != rhs.m_N; ++j) {
			os << std::fixed << std::setprecision(16) <<
				rhs.m_Z[i + rhs.m_LDZ * j] << "\n";
		}
		os << "\n";
	}
	std::cout << "--------------\n";
	std::cout << "Output array TAU:            \n";
	std::cout << "--------------\n";
	for (int i{ 0 }; i != rhs.m_N; ++i) {
		os << std::fixed << std::setprecision(16) <<
			rhs.m_TAU[i] << "\n";
	}
	std::cout << "--------------\n";
	if (rhs.m_INFO == 0){
		os << "Optimal LDWORK value found: " << 
		std::fixed << std::setprecision(16) << rhs.m_DWORK[1] << "\n";
   }
	else {
		std::cout << "Work array DWORK:        \n";
		std::cout << "-------------\n";
		for (int i{ 0 }; i != rhs.m_LDWORK; ++i) {
			os << std::fixed << std::setprecision(16) <<
				rhs.m_DWORK[i] << "\n";
		}
	}
	std::cout << "----------------\n\n";
	std::cout << "Dumping scalar members: \n";
	os << "JOBZ: " << rhs.m_JOBZ << "\n";
	os << "N: " << rhs.m_N << "\n";
	os << "M: " << rhs.m_M << "\n";
	os << "LDA: " << rhs.m_LDA << "\n";
	os << "LDB: " << rhs.m_LDB << "\n";
	os << "NCONT: " << rhs.m_NCONT << "\n";
	os << "INDCON: " << rhs.m_INDCON << "\n";
	os << "LDZ: " << rhs.m_LDZ << "\n";
	os << "TOL: " << std::fixed << std::setprecision(16) << 
		rhs.m_TOL << "\n";
	os << "LDWORK: " << rhs.m_LDWORK << "\n";
	os << "INFO: " << rhs.m_INFO << "\n";
	std::cout << "Reached normal end of execution. \n";
	std::cout << "Date: " << rhs.timestamp().first << "\n";
	std::cout << "Time: " << rhs.timestamp().second << "\n";
	return (os);

}

void        guidance::slicot_wrappers::F77_AB01ND::Wrapper_AB01ND() {
			// Call F77 AB01ND subroutine.
	AB01ND(&this->m_JOBZ, &this->m_N, &this->m_M, &this->m_A[0], &this->m_LDA,
		&this->m_B[0], &this->m_LDB, &this->m_NCONT, &this->m_INDCON, &this->m_NBLK[0],
		&this->m_Z[0], &this->m_LDZ, &this->m_TAU[0], &this->m_TOL, &this->m_IWORK[0],
		&this->m_DWORK[0], &this->m_LDWORK, &this->m_INFO);
}

std::string guidance::slicot_wrappers::F77_AB01ND::obj_type() const {
	return (std::string(typeid(*this).name()));
}

std::string guidance::slicot_wrappers::F77_AB01ND::time_complexity() {
	return (std::string("Complexity of AB01ND = O(N^3)"));
}

std::pair<std::string,std::string>
guidance::slicot_wrappers::F77_AB01ND::timestamp() {
	return (std::make_pair(std::string(__DATE__), std::string(__TIME__)));
}
