
#ifndef __SLICOT_AB01MD_H__
#define __SLICOT_AB01MD_H__

// File version granularity.
#ifndef SLICOT_AB01MD_VERSION_MAJOR
#define SLICOT_AB01MD_VERSION_MAJOR 1
#endif

#ifndef SLICOT_AB01MD_VERSION_MINOR
#define SLICOT_AB01MD_VERSION_MINOR 0
#endif

#ifndef SLICOT_AB01MD_PATCH_VERSION
#define SLICOT_AB01MD_PATCH_VERSION 0
#endif

#ifndef SLICOT_AB01MD_CREATE_DATE
#define SLICOT_AB01MD_CREATE_DATE "Date: 2016-09-13 Time: 18:27 PM GMT+2"
#endif

#ifndef SLICOT_AB01MD_BUILD_DATE
#define SLICOT_AB01MD_BUILD_DATE " "
#endif

#include "Slicot_F77_Interface.h"
#include <iostream>
#include <string>
#include <iomanip>

namespace guidance {
	namespace slicot_wrappers {


		struct    F77_AB01MD {

			F77_AB01MD(_In_ const unsigned char JOBZ,
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
			m_LDA{ LDA },
			m_A(m_LDA * m_N),
			m_B(m_N),
			m_NCONT{ NCONT },
			m_LDZ{ LDZ },
			m_Z(m_LDZ * m_N),
			m_TAU(m_N),
			m_TOL{ TOL },
			m_LDWORK{ LDWORK },
			m_DWORK(m_LDWORK),
			m_INFO{ INFO } {}


			void  Call_AB01MD() {

				AB01MD(&this->m_JOBZ, &this->m_N, &this->m_A[0], &this->m_LDA, &this->m_B[0],
					&this->m_NCONT, &this->m_Z[0], &this->m_LDZ, &this->m_TAU[0], &this->m_TOL,
					&this->m_DWORK[0], &this->m_LDWORK, &this->m_INFO);
			}
			
			unsigned char m_JOBZ;

			_In_	int        m_N;

			_In_    int        m_LDA;

			_Inout_	VF64       m_A;

			_Inout_ VF64       m_B;

			_Out_	int        m_NCONT;

			_In_	int        m_LDZ;

			_Out_	VF64       m_Z;

			_Out_	VF64       m_TAU;

			double             m_TOL;

			int                m_LDWORK;

			VF64               m_DWORK;

			int                m_INFO;

		};


		/*
		     
		*/
	}
}

#endif   /*__SLICOT_ABO1MD_H__*/