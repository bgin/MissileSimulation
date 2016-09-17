
#ifndef __SLICOT_F77_AB01ND_H__
#define __SLICOT_F77_AB01ND_H__

//Code: struct definition: TAB * 2
//Code: members declaration: TAB * 3

// File granularity version
#ifndef SLICOT_F77_AB01ND_VERSION_MAJOR 
#define SLICOT_F77_AB01ND_VERSION_MAJOR 1
#endif

#ifndef SLICOT_F77_AB01ND_VERSION_MINOR
#define SLICOT_F77_AB01ND_VERSION_MINOR 0
#endif

#ifndef SLICOT_F77_AB01ND_PATCH_VERSION
#define SLICOT_F77_AB01ND_PATCH_VERSION 0
#endif

#ifndef SLICOT_F77_AB01ND_CREATE_DATE
#define SLICOT_F77_AB01ND_CREATE_DATE "Date: 2016-09-12 Time: 11:34 AM GMT + 2"
#endif

// Set this value to successfull build date/time.
#ifndef SLICOT_F77_AB01ND_BUILD_DATE
#define SLICOT_F77_AB01ND_BUILD_DATE " "
#endif

#include "Slicot_F77_Interface.h"
#include "Config.h"

#include <iostream>
#include <string>
#include <iomanip>


namespace guidance {
	namespace slicot_wrappers {


		/*
		Low level C++ wrapper for SLICOT subroutine: AB01ND.

		*/

		struct    F77_AB01ND{

			
			// Constructors and Destructor.

			// Main Constructor - members instantiation
			// and initialization.
			F77_AB01ND(_In_ const unsigned char , //JOBZ
			           _In_ const int, //N
					   _In_ const int, //m
					   _In_ const int, //LDA
					   _In_ const int, //LDB
					   _In_ const int, //NCONT
					   _In_ const int, //INDCON
					   _In_ const int, //LDZ
					   _In_ const double, //TOL
					   _In_ const int, //LDWORK 
					   _In_ const int ); //INFO

			F77_AB01ND(_In_ const F77_AB01ND &);

			F77_AB01ND(_In_ F77_AB01ND &&);

#if GUIDANCE_DEFAULT_CXX_VERSION > 199711L
			~F77_AB01ND() = default;
#else
			~F77_AB01ND() {}
#endif


			// operators

			F77_AB01ND &  operator=(_In_ const F77_AB01ND &);

			F77_AB01ND &  operator=(_In_ F77_AB01ND &&);

			friend std::ostream &  operator<<(_In_ std::ostream &,
			                                  _In_ const F77_AB01ND &);

			// Accessors.
			// Provided only accessors for Input/Output members.
			// In accessors which return a reference, reference
			// must not outlive the referenced member.

			inline VF64  &   getm_A() {
				return (this->m_A);
			}

			inline VF64  &  getm_B() {
				return (this->m_B);
			}

			inline int     getm_NCONT() {
				return (this->m_NCONT);
			}

			inline int     getm_INDCON() {
				return (this->m_INDCON);
			}

			inline VI32  &  getm_NBLK() {
				return (this->m_NBLK);
			}

			inline VF64 &   getm_Z() {
				return (this->m_Z);
			}

			inline VF64 &    getm_TAU() {
				return (this->m_TAU);
			}

			// Member functions.

			// Fortran subroutine caller.
			void   Wrapper_AB01ND();

			// Object typeinfo
			std::string obj_type()const;

			// AB01ND time complexity.
			static std::string time_complexity();

			// time stamp function.
			static std::pair<std::string, std::string> timestamp();
				  

			// Member variables.

			unsigned char m_JOBZ;

			int           m_N;

			int           m_M;

			int           m_LDA;

	_Inout_	VF64          m_A;

			int           m_LDB;

	_Inout_	VF64          m_B;

	_Out_   int           m_NCONT;

	_Out_   int           m_INDCON;

	_Out_	VI32          m_NBLK;

			int           m_LDZ;

	_Out_   VF64          m_Z;

	_Out_	VF64          m_TAU;

			double        m_TOL;

			VI32          m_IWORK;

			int           m_LDWORK;

			VF64          m_DWORK;

			int           m_INFO;


			


		};





	}
}




#endif /*__SLICOT_F77_AB01ND_H__*/