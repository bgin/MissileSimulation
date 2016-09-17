

//#include "Slicot_F77_AB01MD.h"

// Implementation.

/*guidance::slicot_wrappers
        ::F77_AB01MD
		::F77_AB01MD(_In_ const unsigned char JOBZ,
	                 _In_ const int N,
	                 _In_ const int LDA,
	                 _In_ const int NCONT,
	                 _In_ const int LDZ,
	                 _In_ const double TOL,
	                 _In_ const int LDWORK,
	                 _In_ const int INFO)
	:
m_JOBZ{ JOBZ },
m_N{ N },
m_LDA{LDA},
m_A(m_LDA * m_N),
m_B(m_N),
m_NCONT{ NCONT },
m_LDZ{ LDZ },
m_Z(m_LDZ * m_N),
m_TAU(m_N),
m_TOL{ TOL },
m_LDWORK{ LDWORK },
m_DWORK(m_LDWORK),
m_INFO{ INFO } {

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
}			
			
			
			





guidance::
slicot_wrappers::F77_AB01MD::
F77_AB01MD(_In_ const F77_AB01MD &other)
:
m_JOBZ{ other.m_JOBZ },
m_N{ other.m_N },
m_LDA{ other.m_LDA },
m_A{ other.m_A },
m_B{ other.m_B },
m_NCONT{ other.m_NCONT },
m_LDZ{ other.m_LDZ },
m_Z{ other.m_Z },
m_TAU{ other.m_TAU },
m_TOL{ other.m_TOL },
m_LDWORK{ other.m_LDWORK },
m_DWORK{ other.m_DWORK },
m_INFO{ other.m_INFO } {}


guidance::
slicot_wrappers::F77_AB01MD::
F77_AB01MD(_In_ F77_AB01MD &&other)
:
m_JOBZ{ std::move(other.m_JOBZ) },
m_N{ std::move(other.m_N) },
m_LDA{ std::move(other.m_LDA) },
m_A{ std::move(other.m_A) },
m_B{ std::move(other.m_B) },
m_NCONT{ std::move(other.m_NCONT) },
m_LDZ{ std::move(other.m_LDZ) },
m_Z{ std::move(other.m_Z) },
m_TAU{ std::move(other.m_TAU) },
m_TOL{ std::move(other.m_TOL) },
m_LDWORK{ std::move(other.m_LDWORK) },
m_DWORK{ std::move(other.m_DWORK) },
m_INFO{ std::move(other.m_INFO) } {}

guidance::slicot_wrappers::F77_AB01MD & 
guidance::slicot_wrappers::F77_AB01MD::operator=(_In_ const F77_AB01MD &other) {
	if (this == &other) return (*this);
	    F77_AB01MD temp{other};
	    std::swap(*this,temp);
		return (*this);
}


guidance::slicot_wrappers::F77_AB01MD &
guidance::slicot_wrappers::F77_AB01MD::operator=(_In_ F77_AB01MD &&other) {
	if (this == &other) return (*this);
	*this = std::move(other);
	return (*this);
} 

std::ostream & guidance::slicot_wrappers
                       ::operator<<(_In_ std::ostream &os,
	                                _In_ const guidance::slicot_wrappers::F77_AB01MD &rhs) {
		
			   std::cout << "Dumping object: " << rhs.obj_type() << "context \n";
			   std::cout << "Date: " << __DATE__ << "Time: " << __TIME__ << "\n";
			   std::cout << "Array members content: \n";
			   std::cout << "C-style traversing. \n";
			   std::cout << " A:   \n";
			   std::cout << "-------\n";
			   for (int i{ 0 }; i != rhs.m_LDA; ++i) {
				   for (int j{ 0 }; j != rhs.m_N; ++j) {
					   os << std::fixed << std::setprecision(16) <<
						   rhs.m_A[i + rhs.m_LDA * j] << "\n";
				   }
				   os << "\n";
			   }
			   std::cout << "-------\n";
			   std::cout << "B:      \n";
			   std::cout << "---------\n";
			   for (int i{ 0 }; i != rhs.m_N; ++i) {
				   os << std::fixed << std::setprecision(16) <<
					   rhs.m_B[i] << "\n";
			   }
			   std::cout << "----------\n";

			   if ((rhs.m_JOBZ == 'I') || (rhs.m_JOBZ == 'F')){
			   
			   std::cout << "Z:       \n";
			   std::cout << "----------\n";
			   for (int i{ 0 }; i != rhs.m_LDZ; ++i) {
				   for (int j{ 0 }; j != rhs.m_N; ++j) {
					   os << std::fixed << std::setprecision(16) <<
						   rhs.m_Z[i + rhs.m_LDZ * j] << "\n";
				   }
				   os << "\n";
			   }
			   std::cout << "--------\n";
		  }
			   std::cout << "TAU:     \n";
			   std::cout << "----------\n";
			   for (int i{ 0 }; i != rhs.m_N; ++i) {
				   os << std::fixed << std::setprecision(16) <<
					   rhs.m_TAU[i] << "\n";
			   }
			   std::cout << "----------\n";
			   std::cout << "DWORK:     \n";
			   if (rhs.m_INFO == 0)
				   os << "Optimal value of LDWORK found: "<< std::fixed << std::setprecision(16) << rhs.m_DWORK[1] << "\n";
			   else {
				   for (int i{ 0 }; i != rhs.m_LDWORK; ++i) {
					   os << std::fixed << std::setprecision(16) <<
						   rhs.m_DWORK[i] << "\n";
				   }
			   }
			   std::cout << "---------\n\n";
			   std::cout << "Dumping scalar members: \n";
			   os << "JOBZ: " << rhs.m_JOBZ << "\n";
			   os << "N:    " << rhs.m_N    << "\n";
			   os << "LDA:  " << rhs.m_LDA  << "\n";
			   os << "NCONT: " << rhs.m_NCONT << "\n";
			   os << "LDZ:  " << rhs.m_LDZ << "\n";
			   os << "TOL:  " << std::fixed << std::setprecision(16) << rhs.m_TOL << "\n";
			   os << "LDWORK: " << rhs.m_LDWORK << "\n";
			   os << "INFO: " << rhs.m_INFO << "\n";
			   std::cout << "Reached normal end of  execution. \n";
			   return (os);

			  

}

void guidance::slicot_wrappers::F77_AB01MD::Wrapper_AB01MD() {
     
	AB01MD(&this->m_JOBZ, &this->m_N, &this->m_A[0], &this->m_LDA, &this->m_B[0],
	       &this->m_NCONT, &this->m_Z[0], &this->m_LDZ, &this->m_TAU[0], &this->m_TOL,
		   &this->m_DWORK[0], &this->m_LDWORK, &this->m_INFO);
}

std::string guidance::slicot_wrappers::F77_AB01MD::obj_type()const {
	return (std::string(typeid(*this).name()));
}

std::string guidance::slicot_wrappers::F77_AB01MD::time_complexity()const {
	return (std::string("Complexity of AB01MD = O(N^3) operations."));
}

std::pair<std::string,std::string>
guidance::slicot_wrappers::F77_AB01MD::time_stamp() {
	return (std::make_pair(std::string(__DATE__), std::string(__TIME__)));
}*/



					