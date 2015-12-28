/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
C++ wrapper class for QUADPACK QAGI Integrators - implementation.

@file IntegratorGaussKronordInfinite.inl
@author: Bernard Gingold
@version:  1.0  25/12/2015
@description: QUADRATURE_F77_DECLARATIONS.h
*/

void    mathlib::IntegratorQAGI::x_qagi(float(*f)(float *), float bound, int inf, float epsabs, float epsrel, float result,
	float abserr, int neval, int ier, int limit, int lenw, int last, std::vector<int> &iwork, std::vector<float> &work)
{
	QAGI(f, &bound, &inf, &epsabs, &epsrel, &result, &abserr, &neval, &ier, &limit, &lenw,  &last, &iwork[0], &work[0]);
}


void    mathlib::IntegratorQAGI::x_qagie(float(*f)(float *), float bound, float inf, float epsabs, float epsrel, int limit,
	float result, float abserr, int neval, int ier, std::vector<float> &alist, std::vector<float> &blist, std::vector<float> &rlist,
	std::vector<float> &elist, int iord, int last)
{
	QAGIE(f, &bound, &inf, &epsabs, &epsrel, &limit, &result, &abserr, &neval, &ier, &alist[0], &blist[0], &rlist[0], &elist[0], &iord, &last);
}

void    mathlib::IntegratorQAGI::x_qagi(double(*f)(double *), double bound, int inf, double epsabs, double epsrel, double result,
	double abserr, int neval, int ier, int limit, int lenw, int last, std::vector<int> &iwork, std::vector<double> &work)
{
	DQAGI(f, &bound, &inf, &epsabs, &epsrel, &result, &abserr, &neval, &ier, &limit, &lenw, &last, &iwork[0], &work[0]);
}

void    mathlib::IntegratorQAGI::x_qagie(double(*f)(double *), double bound, double inf, double epsabs, double epsrel, int limit,
	double result, double abserr, int neval, int ier, std::vector<double> &alist, std::vector<double> &blist, std::vector<double> &rlist,
	std::vector<double> &elist, int iord, int last)
{
	DQAGIE(f, &bound, &inf, &epsabs, &epsrel, &limit, &result, &abserr, &neval, &ier, &alist[0], &blist[0], &rlist[0], &elist[0], &iord, &last);
}