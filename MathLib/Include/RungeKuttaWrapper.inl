/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Runge-Kutta Wrapper class  - wrapper implementation.
Wrapper around RKSUITE Library.
@file RungeKuttaWrapper.inl
@author: Bernard Gingold
@version:  1.0  26/10/2015
@description: in RungeKutta_F77_Declarations.h
*/

void     mathlib::RungeKuttaSolver::rk_setup(int NEQ, double TSTART,double* YSTART,
	double TEND, double TOL, double* THRES, int METHOD, unsigned char* TASK,
	int ERRASS, double HSTART, double* WORK, int LENWRK, int MESAGE)
{
	// Call F77 SUBROUTINE SETUP.
	
	SETUP(&NEQ, &TSTART, &YSTART[0], &TEND, &TOL, &THRES[0], &METHOD, &TASK[0], &ERRASS, &HSTART, &WORK[0], &LENWRK, &MESAGE);
	
	
}

void     mathlib::RungeKuttaSolver::rk_ut(void(*F)(double * , double *, double *), double TWANT,
	double TGOT, double* YGOT, double* YPGOT, double* YMAX, double* WORK, int UFLAG)
	
{

	// Call F77 SUBROUTINE SETUP.
	UT(F, &TWANT, &TGOT, &YGOT[0], &YPGOT[0], &YMAX[0], &WORK[0], &UFLAG);
	
}

void     mathlib::RungeKuttaSolver::rk_stat(int TOTFCN, int STPCST, double WASTE, int STPSOK, double HNEXT)
{
	// Call F77 SUBROUTINE STAT.
	STAT(&TOTFCN, &STPCST, &WASTE, &STPSOK, &HNEXT);
	std::printf("Total calls of Derivative:%d\n", TOTFCN);
	std::printf("Number of Derivative calls per step:%d\n", STPCST);
	std::printf("The fraction od failed steps:%.15f\n", WASTE);
	std::printf("Number of useful steps:%d\n", STPSOK);
	std::printf("Integrator next step size:%.15f\n", HNEXT);
}

void     mathlib::RungeKuttaSolver::rk_glberr(double* RMSERR, double ERRMAX, double TERRMX, double* WORK)
{
	// Call F77 SUBROUTINE GLBERR.
	GLBERR(&RMSERR[0], &ERRMAX, &TERRMX, &WORK[0]);
}

void     mathlib::RungeKuttaSolver::rk_ct(void(*F)(double *, double *, double *), double TNOW, double* YNOW,
	double* YPNOW, double* WORK, int CFLAG)
{    
	// Call F77 SUBROUTINE CT.
	CT(F, &TNOW, &YNOW[0], &YPNOW[0], &WORK[0], &CFLAG);
	
}

void     mathlib::RungeKuttaSolver::rk_intrp(double TWANT, unsigned char* REQUEST, int NWANT, double* YWANT,
	double* YPWANT, void(*F)(double *, double *, double *), double* WORK, double* WRKINT, int LENINT)
	
{
	// Call F77 SUBROUTINE INTRP
	INTRP(&TWANT, &REQUEST[0], &NWANT, &YWANT[0], &YPWANT[0], F, &WORK[0], &WRKINT[0], &LENINT);
}

void     mathlib::RungeKuttaSolver::rk_reset(double TENDNU)
{
	// Call F77 SUBROUTINE RESET.
	RESET(&TENDNU);
}

void     mathlib::RungeKuttaSolver::rk_envirn(int OUTCH, double MCHEPS, double DWARF)
{
	// Call F77 SUBROUTINE ENVIRN
	ENVIRN(&OUTCH, &MCHEPS, &DWARF);
}




