/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
C++ wrapper class for QUADPACK QAGP Integrators -  implementation.

@file IntegratorGaussKronordSingularity.inl
@author: Bernard Gingold
@version:  1.0  25/12/2015
@description: QUADRATURE_F77_DECLARATIONS.h
*/

void        mathlib::IntegratorQAGP::x_qagp(float(*f)(float *), float a, float b, int npts2, std::vector<float> &points, float epsabs,
	float epsrel, float result, float abserr, int neval, int ier, int leniw, int lenw, int last, std::vector<int> &iwork,
	std::vector<float> &work)
{
	QAGP(f, &a, &b, &npts2, &points[0], &epsabs, &epsrel, &result, &abserr, &neval, &ier, &leniw, &lenw, &last, &iwork[0], &work[0]);
}

void        mathlib::IntegratorQAGP::x_qagpe(float(*f)(float *), float a, float b, int npts2, std::vector<float> &points, float epsabs,
	float epsrel, int limit, float result, float abserr, int neval, int ier, std::vector<float> &alist, std::vector<float> &blist,
	std::vector<float> &rlist, std::vector<float> &elist, std::vector<float> &pts, std::vector<int> &level, std::vector<int> &ndin,
	int iord, int last)
{
	QAGPE(f, &a, &b, &npts2, &points[0], &epsabs, &epsrel, &limit, &result, &abserr, &neval, &ier, &alist[0], &blist[0], &rlist[0],
		&elist[0], &pts[0], &level[0], &ndin[0], &iord, &last);
}

void         mathlib::IntegratorQAGP::x_qagp(double(*f)(double *), double a, double b, int npts2, std::vector<double> &points, double epsabs,
	double epsrel, double result, double abserr, int neval, int ier, int leniw, int lenw, int last, std::vector<int> &iwork,
	std::vector<double> &work)
{
	DQAGP(f, &a, &b, &npts2, &points[0], &epsabs, &epsrel, &result, &abserr, &neval, &ier, &leniw, &lenw, &last, &iwork[0], &work[0]);
}

void         mathlib::IntegratorQAGP::x_qagpe(double(*f)(double *), double a, double b, int npts2, std::vector<double> &points, double epsabs,
	double epsrel, int limit, double result, double abserr, int neval, int ier, std::vector<double> &alist, std::vector<double> &blist,
	std::vector<double> &rlist, std::vector<double> &elist, std::vector<double> &pts, std::vector<int> &level, std::vector<int> &ndin,
	int iord, int last)
{
	DQAGPE(f, &a, &b, &npts2, &points[0], &epsabs, &epsrel, &limit, &result, &abserr, &neval, &ier, &alist[0], &blist[0],
		&rlist[0], &elist[0], &pts[0], &level[0], &ndin[0], &iord, &last);
}