/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
C++ wrapper class for QUADPACK QAGS Integrators -  implementation.

@file IntegratorGKronordEndSingularity.inl
@author: Bernard Gingold
@version:  1.0  25/12/2015
@description: QUADRATURE_F77_DECLARATIONS.h
*/

void               mathlib::IntegratorQAGS::x_qags(float(*f)(float *), float a, float b, float epsabs, float epsrel, float result,
	float abserr, int neval, int ier, int limit, int lenw, int last, std::vector<int> &iwork, std::vector<float> &work)
{
	QAGS(f, &a, &b, &epsabs, &epsrel, &result, &abserr, &neval, &ier, &limit, &lenw, &last, &iwork[0], &work[0]);
}

void               mathlib::IntegratorQAGS::x_qagse(float(*f)(float *), float a, float b, float epsabs, float epsrel, int limit,
	float result, float abserr, int neval, int ier, std::vector<float> &alist, std::vector<float> &blist, std::vector<float> &rlist,
	std::vector<float> &elist, std::vector<int> &iord, int last)
{
	QAGSE(f, &a, &b, &epsabs, &epsrel, &limit, &result, &abserr, &neval, &ier, &alist[0], &blist[0], &rlist[0], &elist[0],
		&iord[0], &last);
}

void               mathlib::IntegratorQAGS::x_qags(double(*f)(double *), double a, double b, double epsabs, double epsrel, double result,
	double abserr, int neval, int ier, int limit, int lenw, int last, std::vector<int> &iwork, std::vector<double> &work)
{
	DQAGS(f, &a, &b, &epsabs, &epsrel, &result, &abserr, &neval, &ier, &limit, &lenw, &last, &iwork[0], &work[0]);
}

void               mathlib::IntegratorQAGS::x_qagse(double(*f)(double *), double a, double b, double epsabs, double epsrel, int limit,
	double result, double abserr, int neval, int ier, std::vector<double> &alist, std::vector<double> &blist, std::vector<double> &rlist,
	std::vector<double> &elist, std::vector<int> &iord, int last)
{
	DQAGSE(f, &a, &b, &epsabs, &epsrel, &limit, &result, &abserr, &neval, &ier, &alist[0], &blist[0], &rlist[0], &elist[0], &iord[0], &last);
}