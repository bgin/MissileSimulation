
#ifndef __MACROS_H__
#define __MACROS_H__

//File granularity version.
#ifndef MACROS_VERSION_MAJOR 
#define MACROS_VERSION_MAJOR 1
#endif

#ifndef MACROS_VERSION_MINOR 
#define MACROS_VERSION_MINOR 0
#endif

#ifndef MACROS_PATCH_VERSION
#define MACROS_PATCH_VERSION 0
#endif

#ifndef MACROS_CREATE_DATE
#define MACROS_CREATE_DATE "Date: 2016-09-17 Time: 15:38 PM GMT+2"
#endif

// Set this value to successful build date/time.
#ifndef MACROS_BUILD_DATE
#define MACROS_BUILD_DATE ""
#endif

#include "SlicotAB01ND.h"
#include "SlicotAB01OD.h"

using namespace guidance::slicot_wrappers;

// This parametrized macros is expanded to AB01ND Constructor call.

#define CONSTRUCT_AB01ND_1(JOBZ,N,M,LDA,LDB,NCONT,INDCON,LDZ,TOL,LDWORK,INFO) F77_AB01ND<> obj{JOBZ,N,M,LDA,LDB,NCONT, \
																								INDCON, LDZ, TOL, LDWORK, INFO};

#define CONSTRUCT_AB01ND_2(JOBZ,N,M,LDA,A,LDB,B,NCONT,INDCON,LDZ,TOL,LDWORK,INFO) F77_AB01ND<> obj2{JOBZ,N,M,LDA,A,LDB,B,NCONT,\
	INDCON, LDZ, TOL, LDWORK, INFO};

#define CONSTRUCT_INIT_AB01ND_1(JOBZ,N,M,LDA,A,LDB,B,NCONT,INDCON,LDZ,TOL,LDWORK,INFO) \
	    F77_AB01ND<> obj3{JOBZ,N,M,LDA,LDB,NCONT,INDCON,LDZ,TOL,LDWORK,INFO};        \
		obj3.init_input_arrays(A,B) \

#endif /*__MACROS_H__*/