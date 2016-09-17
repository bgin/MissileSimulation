
#include "Slicot_F77_AB01OD.h"

// Implementation.

guidance::slicot_wrappers
::F77_AB01OD::F77_AB01OD(_In_ const unsigned char STAGES,
                         _In_ const unsigned char JOBU,
                         _In_ const unsigned char JOBV,
                         _In_ const int N,
                         _In_ const int M,
                         _In_ const int LDA,
                         _In_ const int LDB,
                         _In_ const int LDU,
                         _In_ const int LDV,
                         _In_ const int NCONT,
                         _In_ const int INDCON,
                         _In_ const double TOL,
                         _In_ const int LDWORK,
                         _In_ const int INFO)
                        :
m_STAGES{ STAGES },
m_JOBU{ JOBU },
m_JOBV{ JOBV },
m_N{ N },
m_M{ M },
m_LDA{ LDA },
m_A(m_LDA * m_N),
m_LDB{ LDB },
m_B(m_LDB * m_M),
m_LDU{ LDU },
m_U(m_LDU * m_N),
m_LDV{ LDV },
m_V(m_LDV * m_M),
m_NCONT{ NCONT },
m_INDCON{ INDCON },
m_KSTAIR(m_N),
m_TOL{ TOL },
m_IWORK(m_M),
m_LDWORK{ LDWORK },
m_DWORK(m_LDWORK),
m_INFO{ INFO } {

#if defined(GUIDANCE_DEBUG_ON)
	std::cerr << "****************************************\n";
	std::cerr << "Debug mode: ON \n";
	std::cerr << "Date: " << this->time_stamp().first << "\n";
	std::cerr << "Time: " << this->time_stamp().second << "\n";
	std::cerr << "Execution inside 15-arg Ctor body of type: " << this->obj_type() << "\n";
	std::cerr << "File: " << __FILE__ << "\n";
	std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
	std::cerr << "Code-line: " << __LINE__ << "\n";
	std::cerr << "Exiting 18-arg Ctor body!! \n";
	std::cerr << "****************************************\n";
#endif
}

guidance::slicot_wrappers
::F77_AB01OD::F77_AB01OD(_In_ const F77_AB01OD &other)
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
m_KSTAIR{ other.m_KSTAIR },
m_TOL{ other.m_TOL },
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
::F77_AB01OD::F77_AB01OD(_In_ F77_AB01OD &&other)
:
m_STAGES{ std::move(other.m_STAGES) },
m_JOBU{ std::move(other.m_JOBU) },
m_JOBV{ std::move(other.m_JOBV) },
m_N{ std::move(other.m_N) },
m_M{ std::move(other.m_M) },
m_LDA{ std::move(other.m_LDA) },
m_A{ std::move(other.m_A) },
m_LDB{ std::move(other.m_LDB) },
m_B{ std::move(other.m_B) },
m_LDU{ std::move(other.m_LDU) },
m_U{ std::move(other.m_U) },
m_LDV{ std::move(other.m_LDV) },
m_V{ std::move(other.m_V) },
m_NCONT{ std::move(other.m_NCONT) },
m_INDCON{ std::move(other.m_INDCON) },
m_KSTAIR{ std::move(other.m_KSTAIR) },
m_TOL{ std::move(other.m_TOL) },
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
::F77_AB01OD::~F77_AB01OD() {

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

guidance::slicot_wrappers::F77_AB01OD & 
guidance::slicot_wrappers::F77_AB01OD::operator=(_In_ const F77_AB01OD &other) {
	if (this == &other) return (*this);
	F77_AB01OD temp{other};
	std::swap(*this,temp);
#if defined(GUIDANCE_DEBUG_ON)
	std::cerr << "****************************************\n";
	std::cerr << "Debug mode: ON \n";
	std::cerr << "Date: " << this->time_stamp().first << "\n";
	std::cerr << "Time: " << this->time_stamp().second << "\n";
	std::cerr << "Execution inside body of Copy-Assign operator of type: " << this->obj_type() << "\n";
	std::cerr << "File: " << __FILE__ << "\n";
	std::cerr << "Virtual address: " << std::hex << "0x" << __FUNCTIONW__ << "\n";
	std::cerr << "Code-line: " << __LINE__ << "\n";
	std::cerr << "Exiting Copy-Assign operator body!! \n";
	std::cerr << "****************************************\n";
#endif
	return (*this);
}

guidance::slicot_wrappers::F77_AB01OD &
guidance::slicot_wrappers::F77_AB01OD::operator=(_In_ F77_AB01OD &&other) {
	if (this == &other) return (*this);
	*this = std::move(other);
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

std::ostream &  guidance::slicot_wrappers::operator<<(_In_ std::ostream &os,
	                  _In_ const guidance::slicot_wrappers::F77_AB01OD &rhs) {

	using namespace std;
	cout << "Dumping context of object: " << rhs.obj_type() << "\n";
	cout << "At date: " << rhs.time_stamp().first << "\n";
	cout << "At time: " << rhs.time_stamp().second << "\n";
	cout << "Array members content first: \n";
	cout << "C-style array traversing in use. \n";
	cout << "Precision fixed at " << 16 << "decimal digits. \n";
	cout << "Input/Output array A:   \n";
	cout << "-----------\n";
	for (int i{ 0 }; i != rhs.m_LDA; ++i) {
		for (int j{ 0 }; j != rhs.m_N; ++j) {
			os << fixed << setprecision(20) << 
				rhs.m_A[i + rhs.m_LDA * j] << "\n";
		}
		os << "\n";
	}
	cout << "--------------\n";
	cout << "Input/Output array B:    \n";
	cout << "---------------\n";
	for (int i{ 0 }; i != rhs.m_LDB; ++i) {
		for (int j{ 0 }; j != rhs.m_M; ++j) {
			os << fixed << setprecision(16) <<
				rhs.m_B[i + rhs.m_LDB * j] << "\n";
		}
		os << "\n";
	}
	cout << "-------------\n";
	cout << "Input/Output array U:    \n";
	cout << "----------------\n";
	for (int i{ 0 }; i != rhs.m_LDU; ++i) {
		for (int j{ 0 }; j != rhs.m_N; ++j) {
			os << fixed << setprecision(16) <<
				rhs.m_U[i + rhs.m_LDU * j] << "\n";
		}
		os << "\n";
	}
	cout << "-------------\n";
	cout << "Output array V:          \n";
	cout << "----------------\n";
	for (int i{ 0 }; i != rhs.m_LDV; ++i) {
		for (int j{ 0 }; j != rhs.m_M; ++j) {
			os << fixed << setprecision(16) <<
				rhs.m_V[i + rhs.m_LDV * j] << "\n";
		}
		os << "\n";
	}
	cout << "--------------\n";
	cout << "Output array KSTAIR:      \n";
	cout << "----------------\n";
	for (int i{ 0 }; i != rhs.m_N; ++i) {
		os << fixed << setprecision(16) <<
			rhs.m_KSTAIR[i] << "\n";
	}
	cout << "-----------------\n";

	cout << "Dumping scalar members: \n";
	os << "STAGES: " << rhs.m_STAGES << "\n";
	os << "JOBU: " << rhs.m_JOBU << "\n";
	os << "JOBV: " << rhs.m_JOBV << "\n";
	os << "N: " << rhs.m_N << "\n";
	os << "M: " << rhs.m_M << "\n";
	os << "LDA: " << rhs.m_LDA << "\n";
	os << "LDB: " << rhs.m_LDB << "\n";
	os << "LDU: " << rhs.m_LDU << "\n";
	os << "LDV: " << rhs.m_LDV << "\n";
	os << "NCONT: " << rhs.m_NCONT << "\n";
	os << "INDCON: " << rhs.m_INDCON << "\n";
	os << "TOL: " << fixed << setprecision(16) << rhs.m_TOL << "\n";
	os << "LDWORK: " << rhs.m_LDWORK << "\n";
	if (rhs.m_INFO == 0)
		os << "Successful exit of AB01OD!! \n";
	else if (rhs.m_INFO < 0)
		os << "Detected illegal value: "  << rhs.m_INFO << "\n";
	 
	cout << "Reached normal end of execution. \n";
	return (os);

}

std::string guidance::slicot_wrappers::F77_AB01OD::obj_type()const {
	return (std::string(typeid(*this).name()));
}

std::string guidance::slicot_wrappers::F77_AB01OD::time_complexity() {
	return (std::string("Complexity of AB01OD  = ~O(N^3) "));
}

std::pair<std::string,std::string> 
guidance::slicot_wrappers::F77_AB01OD::time_stamp() {
	return (std::make_pair(std::string(__DATE__), std::string(__TIME__)));
}
            
