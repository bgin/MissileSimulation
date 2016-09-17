
#ifndef __SLICOT_F77_AB01OD_H__
#define __SLICOT_F77_AB01OD_H__

//Code: struct declaration: Tab*2
//Code: members definition: Tab*3

// File granularity version.
#ifndef SLICOT_F77_AB01OD_VERSION_MAJOR
#define SLICOT_F77_AB01OD_VERSION_MAJOR 1
#endif

#ifndef SLICOT_F77_AB01OD_VERSION_MINOR
#define SLICOT_F77_AB01OD_VERSION_MINOR 0
#endif

#ifndef SLICOT_F77_AB01OD_PATCH_VERSION
#define SLICOT_F77_AB01OD_PATCH_VERSION 0
#endif

#ifndef SLICOT_F77_AB01OD_CREATE_DATE
#define SLICOT_F77_AB01OD_CREATE_DATE "Date: 2016-09-12 Time: 17:10 PM GMT + 2"
#endif

#ifndef SLICOT_F77_AB01OD_BUILD_DATE
#define SLICOT_F77_AB01OD_BUILD_DATE " "
#endif


#include "Slicot_F77_Interface.h"
#include "Config.h" // for handling C++11 default keyword.
#include <string>
#include <iostream>
#include <iomanip>

namespace guidance {
	namespace slicot_wrappers {


		struct    F77_AB01OD{

			
			// Constructors and Destructor.

			// Main Ctor instantiates and 
			// initializes( T{}) array members.
			F77_AB01OD(_In_ const unsigned char, //STAGES
			           _In_ const unsigned char, // JOBU
					   _In_ const unsigned char, // JOBV
					   _In_ const int, // N
					   _In_ const int, // M
					   _In_ const int, // LDA
					   _In_ const int, // LDB
					   _In_ const int, // LDU
					   _In_ const int, // LDV
					   _In_ const int, // NCONT
					   _In_ const int, // INDCON
					   _In_ const double, // TOL
					   _In_ const int, // LDWORK
					   _In_ const int ); // INFP

			// Copy-Ctor (deep copy)
			F77_AB01OD(_In_ const F77_AB01OD &);

			// Move-Ctor
			F77_AB01OD(_In_ F77_AB01OD &&);

			// Dtor
#if GUIDANCE_DEFAULT_CXX_VERSION > 199711L
			~F77_AB01OD() = default;
#else
			~F77_AB01OD();
#endif

			// operators:

			F77_AB01OD &  operator=(_In_ const F77_AB01OD &);

			F77_AB01OD &  operator=(_In_ F77_AB01OD &&);

			friend std::ostream & operator<<(_In_ std::ostream &,
			                                 _In_ const F77_AB01OD &);

			// Accessors.
			// Only In/Out and Out array variables.
			// In accessors which return a reference, reference
			// must not outlive the referenced member.

			inline VF64 &   getm_A() {
				return (this->m_A);
			}

			inline VF64 &   getm_B() {
				return (this->m_B);
			}

			inline VF64 &   getm_U() {
				return (this->m_U);
			}

			inline VF64 &   getm_V() {
				return (this->m_V);
			}

			inline VI32 &   getm_KSTAIR() {
				return (this->m_KSTAIR);
			}


			// Member  functions.

			// Fortran AB01OD subroutine caller.
			void Wrapper_AB01OD();

			// Object type info.
			std::string obj_type()const;

			// AB01OD time complexity.
			// Returns string initialized
			// with time complexity value.
			static std::string time_complexity();

			// Time stamp helper function.
			static std::pair<std::string, std::string> time_stamp();



			// Member variables:
			unsigned char      m_STAGES;

			unsigned char      m_JOBU;

			unsigned char      m_JOBV;

			int                m_N;

			int				   m_M;

			int                m_LDA;

	_Inout_ VF64			   m_A;

			int				   m_LDB;

	_Inout_ VF64               m_B;

			int				   m_LDU;

	_Inout_ VF64               m_U;

			int                m_LDV;

   _Out_    VF64               m_V;

			int				   m_NCONT;

			int                m_INDCON;

   _Inout_  VI32               m_KSTAIR;

			double             m_TOL;

			VI32               m_IWORK;

			int                m_LDWORK;

			VF64               m_DWORK;

			int                m_INFO;




		};

	}
}

#endif /*__SLICOT_F77_AB01OD_H__*/