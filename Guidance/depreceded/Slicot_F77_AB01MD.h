/*#ifndef __SLICOT_F77_AB01MD_H__
#define __SLICOT_F77_AB01MD_H__

//Code: struct declaration: Tab * 2
//Code: members declaration: Tab * 3

// File version granularity
#ifndef SLICOT_F77_AB01MD_VERSION_MAJOR
#define SLICOT_F77_AB01MD_VERSION_MAJOR 1
#endif

#ifndef SLICOT_F77_AB01MD_VERSION_MINOR
#define SLICOT_F77_AB01MD_VERSION_MINOR 0
#endif

#ifndef SLICOT_F77_AB01MD_PATCH_VERSION
#define SLICOT_F77_AB01MD_PATCH_VERSION 0
#endif

#ifndef SLICOT_F77_AB01MD_CREATE_DATE 
#define SLICOT_F77_AB01MD_CREATE_DATE "Date: 2016-09-11 Time: 15:45 PM GMT+2, Author: Bernard Gingold"
#endif

// Set this value to successful build date/time.
#ifndef SLICOT_F77_AB01MD_BUILD_DATE
#define SLICOT_F77_AB01MD_BUILD_DATE " "
#endif*/

//#include "Slicot_F77_Interface.h"

//#include <valarray>
//#include <iostream>
//#include <string>
//#include <iomanip>



		/*
		Low level C++ wrapper for SLICOT subroutine: AB01MD.

		*/

	/*	struct     F77_AB01MD {




			// Main Constructor.
			// Member initialization only.

			F77_AB01MD(_In_ const unsigned char,
			           _In_ const int,
			           _In_ const int,
			           _In_ const int,
			           _In_ const int,
			           _In_ const double,
			           _In_ const int,
			           _In_ const int);

			F77_AB01MD(_In_ const F77_AB01MD &);

			F77_AB01MD(_In_ F77_AB01MD &&);

			~F77_AB01MD() = default;

			// operators

			F77_AB01MD & operator=(_In_ const F77_AB01MD &);

			F77_AB01MD & operator=(_In_ F77_AB01MD &&);

			friend std::ostream & operator<<(_In_ std::ostream &, 
			                                 _In_ const F77_AB01MD &);

			// Accessors
			// Return only Input/Output and Ouput members.

			inline  std::valarray<double> & getm_A() {
				return (this->m_A);
			}

			inline std::valarray<double> & getm_B() {
				return (this->m_B);
			}

			inline int getm_NCONT()const {
				return (this->m_NCONT);
			}

			inline std::valarray<double> & getm_Z() {
				return (this->m_Z);
			}

			inline std::valarray<double> & getm_TAU() {
				return (this->m_TAU);
			}


			// Member functions.

			void  Wrapper_AB01MD();

			std::string obj_type()const;

			std::string time_complexity()const;

			static std::pair<std::string, std::string> time_stamp();

			// Members variables.

			unsigned char m_JOBZ;

		_In_	int        m_N;

		_In_    int        m_LDA;

		_Inout_	std::valarray<double> m_A;

		_Inout_ std::valarray<double> m_B;

		_Out_	int           m_NCONT;

		_In_	int           m_LDZ;

		_Out_	std::valarray<double> m_Z;

		_Out_	std::valarray<double> m_TAU;

			double        m_TOL;

			int           m_LDWORK;

			std::valarray<double> m_DWORK;

			int           m_INFO;

		};





	}
}*/


