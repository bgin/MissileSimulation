
#ifndef __SLICOT_F77_AB04MD_H__
#define __SLICOT_F77_AB04MD_H__

//Code: struct definition: TAB * 2
//Code: members declaration: TAB * 3

// File version granularity
#ifndef SLICOT_F77_AB04MD_VERSION_MAJOR
#define SLICOT_F77_AB04MD_VERSION_MAJOR 1
#endif

#ifndef SLICOT_F77_AB04MD_VERSION_MINOR
#define SLICOT_F77_AB04MD_VERSION_MINOR 0
#endif

#ifndef SLICOT_F77_AB04MD_PATCH_VERSION
#define SLICOT_F77_AB04MD_PATCH_VERSION 0
#endif

#ifndef SLICOT_F77_AB04MD_CREATE_DATE
#define SLICOT_F77_AB04MD_CREATE_DATE "Date: 2016-09-13 Time: 14:49 PM GMT+2"
#endif

#ifndef SLICOT_F77_AB04MD_BUILD_DATE
#define SLICOT_F77_AB04MD_BUILD_DATE " "
#endif

#include "Slicot_F77_Interface.h"
#include "Config.h"
#include <iostream>
#include <string>
#include <iomanip>

namespace guidance {
	namespace slicot_wrappers {




		struct      F77_AB04MD{

			
			// Constructors and Destructor

			// Main Ctor instantiates and 
			// initializes( T{}) array members.
			F77_AB04MD(_In_ const unsigned char,
			           _In_ const int,
					   _In_ const int,
					   _In_ const int,
					   _In_ const double,
					   _In_ const double,
					   _In_ const int,
					   _In_ const int,
					   _In_ const int,
					   _In_ const int,
					   _In_ const int,
					   _In_ const int);

			// Copy-Ctor (deep copy)
			F77_AB04MD(_In_ const F77_AB04MD &);

			// Move-Ctor
			F77_AB04MD(_In_ F77_AB04MD &&);

#if  GUIDANCE_DEFAULT_CXX_VERSION > 199711L
			// Handle absence of default keyword support.
			~F77_AB04MD() = default;
#else
			~F77_AB04MD();
#endif

			// operators

			F77_AB04MD & operator=(_In_ const F77_AB04MD &);

			F77_AB04MD & operator=(_In_ F77_AB04MD &&);

			friend std::ostream & operator<<(_In_ std::ostream &,
			                                 _In_ const F77_AB04MD &);

			// Accessors.
			// Only In/Out and Out array variables.
			// In accessors which return a reference, reference
			// must not outlive the referenced member.

			inline VF64 &  getm_A() {
				return (this->m_A);
			}

			inline VF64 &  getm_B() {
				return (this->m_B);
			}

			inline VF64 &  getm_C() {
				return (this->m_C);
			}

			inline VF64 &  getm_D() {
				return (this->m_D);
			}

			// Member functions.

			// Calls Fortran 77 wrapper AB04MD.
			void Wrapper_AB04MD();

			// object typeid
			std::string obj_type()const;

			// AB04MD Time complexity.
		   static std::string time_complexity();

		   // time stamp function.
		   static std::pair<std::string, std::string> time_stamp();


			// Member variables:
			unsigned char   m_TYPE;

			int             m_N;

			int             m_M;

			int				m_P;

			double          m_ALPHA;

			double          m_BETA;

			int             m_LDA;

	_Inout_ VF64            m_A;

	        int             m_LDB;

	_Inout_ VF64            m_B;

			int             m_LDC;

	_Inout_ VF64            m_C;

			int				m_LDD;

	_Inout_ VF64			m_D;

			VI32			m_IWORK;

			int				m_LDWORK;

			VF64            m_DWORK;

			int             m_INFO;

		};







	}
}


#endif /*__SLICOT_F77_AB04MD_H__*/