
#include "Slicot_F77_AB04MD.h"

// Implementation.

guidance::slicot_wrappers
::F77_AB04MD::F77_AB04MD(_In_ const unsigned char TYPE,
                         _In_ const int N,
                         _In_ const int M,
                         _In_ const int P,
                         _In_ const double ALPHA,
                         _In_ const double BETA,
                         _In_ const int LDA,
                         _In_ const int LDB,
                         _In_ const int LDC,
                         _In_ const int LDD,
                        _In_ const int LDWORK,
                        _In_ const int INFO)
       :
m_TYPE{ TYPE },
m_N{ N },
m_M{ M },
m_P{ P },
m_ALPHA{ ALPHA },
m_BETA{ BETA },
m_LDA{ LDA },
m_A(m_LDA * m_N),
m_LDB{ LDB },
m_B(m_LDB * m_M),
m_LDC{ LDC },
m_C(m_LDC * m_N),
m_LDD{ LDD },
m_D(m_LDD * m_M),
m_IWORK(m_N),
m_LDWORK{ LDWORK },
m_DWORK(m_LDWORK),
m_INFO{ INFO } {

#if defined(GUIDANCE_DEBUG_ON)
	std::cerr << "****************************************\n";
	std::cerr << "Debug mode: ON \n";
	std::cerr << "Date: " << this->time_stamp().first << "\n";
	std::cerr << "Time: " << this->time_stamp().second << "\n";
	std::cerr << "Execution inside 12-arg Ctor body of type: " << this->obj_type() << "\n";
	std::cerr << "File: " << __FILE__ << "\n";
	std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
	std::cerr << "Code-line: " << __LINE__ << "\n";
	std::cerr << "Exiting 12-arg Ctor body!! \n";
	std::cerr << "****************************************\n";
#endif
}

guidance::slicot_wrappers
::F77_AB04MD::F77_AB04MD(_In_ const F77_AB04MD &other)
:
m_TYPE{ other.m_TYPE },
m_N{ other.m_N },
m_M{ other.m_M },
m_P{ other.m_P },
m_ALPHA{ other.m_ALPHA },
m_BETA{ other.m_BETA },
m_LDA{ other.m_LDA },
m_A{ other.m_A },
m_LDB{ other.m_LDB },
m_B{ other.m_B },
m_LDC{ other.m_LDC },
m_C{ other.m_C },
m_LDD{ other.m_LDD },
m_D{ other.m_D },
m_IWORK{ other.m_IWORK },
m_LDWORK{ other.m_LDWORK },
m_DWORK{ other.m_DWORK },
m_INFO{ other.m_INFO } {

#if defined(GUIDANCE_DEBUG_ON)
	std::cerr << "****************************************\n";
	std::cerr << "Debug mode: ON \n";
	std::cerr << "Date: " << this->time_stamp().first << "\n";
	std::cerr << "Time: " << this->time_stamp().second << "\n";
	std::cerr << "Execution inside Copy - Ctor body of type: " << this->obj_type() << "\n";
	std::cerr << "File: " << __FILE__ << "\n";
	std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
	std::cerr << "Code-line: " << __LINE__ << "\n";
	std::cerr << "Exiting Copy - Ctor body!! \n";
	std::cerr << "****************************************\n";
#endif
}

guidance::slicot_wrappers
::F77_AB04MD::F77_AB04MD(_In_ F77_AB04MD &&other)
:
m_TYPE{ std::move(other.m_TYPE) },
m_N{ std::move(other.m_N) },
m_M{ std::move(other.m_M) },
m_P{ std::move(other.m_P) },
m_ALPHA{ std::move(other.m_ALPHA )},
m_BETA{ std::move(other.m_BETA) },
m_LDA{ std::move(other.m_LDA) },
m_A{ std::move(other.m_A) },
m_LDB{ std::move(other.m_LDB) },
m_B{ std::move(other.m_B) },
m_LDC{ std::move(other.m_LDC) },
m_C{ std::move(other.m_C) },
m_LDD{ std::move(other.m_LDD) },
m_D{ std::move(other.m_D) },
m_IWORK{ std::move(other.m_IWORK) },
m_LDWORK{ std::move(other.m_LDWORK) },
m_DWORK{ std::move(other.m_DWORK) },
m_INFO{ std::move(other.m_INFO) } {

#if defined(GUIDANCE_DEBUG_ON)
	std::cerr << "****************************************\n";
	std::cerr << "Debug mode: ON \n";
	std::cerr << "Date: " << this->time_stamp().first << "\n";
	std::cerr << "Time: " << this->time_stamp().second << "\n";
	std::cerr << "Execution inside Move - Ctor body of type: " << this->obj_type() << "\n";
	std::cerr << "File: " << __FILE__ << "\n";
	std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
	std::cerr << "Code-line: " << __LINE__ << "\n";
	std::cerr << "Exiting Move - Ctor body!! \n";
	std::cerr << "****************************************\n";
#endif
}

#if GUIDANCE_DEFAULT_CXX_VERSION > 199711L

#else
guidance::slicot_wrappers
::F77_AB04MD::~F77_AB04MD() {

#if defined(GUIDANCE_DEBUG_ON)
	std::cerr << "****************************************\n";
	std::cerr << "Debug mode: ON \n";
	std::cerr << "Date: " << this->time_stamp().first << "\n";
	std::cerr << "Time: " << this->time_stamp().second << "\n";
	std::cerr << "Execution inside Dtor body of type: " << this->obj_type() << "\n";
	std::cerr << "File: " << __FILE__ << "\n";
	std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
	std::cerr << "Code-line: " << __LINE__ << "\n";
	std::cerr << "Exiting Dtor body!! \n";
	std::cerr << "****************************************\n";
#endif
}
#endif

guidance::slicot_wrappers::F77_AB04MD &
guidance::slicot_wrappers::F77_AB04MD::operator=(_In_ const F77_AB04MD &other) {
	if (this == &other) return (*this);
	F77_AB04MD temp{other};
	std::swap(*this,temp);
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
