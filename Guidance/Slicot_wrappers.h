
#ifndef __SLICOT_WRAPPERS_H__
#define __SLICOT_WRAPPERS_H__

// File version granularity
#ifndef SLICOT_WRAPPERS_VERSION_MAJOR
#define SLICOT_WRAPPERS_VERSION_MAJOR 1
#endif

#ifndef SLICOT_WRAPPERS_VERSION_MINOR
#define SLICOT_WRAPPERS_VERSION_MINOR 0
#endif

#ifndef SLICOT_WRAPPERS_PATCH_VERSION
#define SLICOT_WRAPPERS_PATCH_VERSION 0
#endif

#ifndef SLICOT_WRAPPERS_CREATE_DATE
#define SLICOT_WRAPPERS_CREATE_DATE "Date: 2016-09-13 Time: 10:33 AM GMT+2"
#endif

#ifndef SLICOT_WRAPPERS_BUILD_DATE
#define SLICOT_WRAPPERS_BUILD_DATE " "
#endif

/*
     Master header file which "#includes" all 
	 wrappers header files.
*/

#include "Slicot_F77_AB01OD.h"
#include "Slicot_F77_AB01ND.h"
#include "Slicot_F77_AB01MD.h"



#endif /*__SLICOT_WRAPPERS_H__*/