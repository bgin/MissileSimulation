#ifndef _RUNGE_KUTTA_WRAPPER_H_
#define _RUNGE_KUTTA_WRAPPER_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Runge-Kutta Wrapper class  - wrapper definitions.
Wrapper around RKSUITE Library.
@file RungeKuttaWrapper.h
@author: Bernard Gingold
@version:  1.0  26/10/2015
@description: in RungeKutta_F77_Declarations.h
*/

#include "MathLibDefinitions.h"
#include "RungeKutta_F77_Declarations.h"

namespace   mathlib
{

	class RungeKuttaSolver
	{

	public:


		/*
		@brief C++ wrapper for Fortran 77 SUBROUTINE SETUP(NEQ,TSTART,YSTART,TEND,TOL,THRES,METHOD,TASK,
                     ERRASS,HSTART,WORK,LENWRK,MESAGE)
		*/
		static void 	rk_setup(int, double, double *,
			double, double, double *, int,
			unsigned char *, int, double, double *,
			int, int);

		/*
		@brief C++ wrapper for Fortran 77 SUBROUTINE UT(F,TWANT,TGOT,YGOT,YPGOT,YMAX,WORK,UFLAG)
		*/
	 static 	void    rk_ut(void(*)(double * , double *, double *), double, double,
		 double *, double *, double *, double *, int);
			

		/*
		@brief C++ wrapper for Fortran 77  SUBROUTINE STAT(TOTFCN,STPCST,WASTE,STPSOK,HNEXT)
		*/
		static void   rk_stat(int, int, double, int, double);

		/*
		@brief  C++ wrapper for Fortran 77   SUBROUTINE GLBERR(RMSERR,ERRMAX,TERRMX,WORK)
		
		*/
		static void   rk_glberr(double *, double, double,
			double *);

		/*
		@brief C++ wrapper for Fortran 77 SUBROUTINE CT(F,TNOW,YNOW,YPNOW,WORK,CFLAG)
		*/
		static void   rk_ct(void(*)(double * , double *, double *), double,
			double *, double *, double *, int);

		/*
		@brief C++ wrapper for Fortran 77 SUBROUTINE INTRP(TWANT,REQEST,NWANT,YWANT,YPWANT,F,WORK,WRKINT,
                      LENINT)
		*/
		static void    rk_intrp(double, unsigned char *, int, double *,
			double *, void(*)(double * , double *, double *),
			double *, double *, int);

		/*
		@brief C++ wrapper for Fortran 77 SUBROUTINE RESET(TENDNU)
		*/
	static 	void    rk_reset(double);

		/*
		@brief  C++ wrapper for Fortran 77 SUBROUTINE ENVIRN(OUTCH,MCHEPS,DWARF)
		*/
		static void     rk_envirn(int, double, double);
	};

#include "RungeKuttaWrapper.inl"
}
#endif /*_RUNGE_KUTTA_WRAPPER_H_*/