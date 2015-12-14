
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Real Sine FFT forward/backward Direction 1D class  - wrapper implementation.
Wrapper around FFTPACK 5.1 library
@file Real_SinFFT_1D.inl
@author: Bernard Gingold
@version:  1.0  26/10/2015
@description: in F77_FFT_DECLARATIONS.h
*/

void     mathlib::RealSinFFT1D::real_sinfft_init1D(int N, std::vector<float> &WSAVE,
	int LENSAV, int IER)
{
	// Call Fortran SINT1 routine.
	SINT1I(&N, &WSAVE[0], &LENSAV, &IER);
}

void      mathlib::RealSinFFT1D::real_sinfft_backward1D(int N, int INC, std::vector<float> &R,
	int LENR, std::vector<float> &WSAVE, int LENSAV, std::vector<float> &WORK,
	int LENWRK, int IER)
{
	// Call Fortran SINT1B routine.
	SINT1B(&N, &INC, &R[0], &LENR, &WSAVE[0], &LENSAV, &WORK[0], &LENWRK, &IER);
}

void      mathlib::RealSinFFT1D::real_sinfft_forward1D(int N, int INC, std::vector<float> &R,
	int LENR, std::vector<float> &WSAVE, int LENSAV, std::vector<float> &WORK,
	int LENWRK, int IER)
{
	// Call Fortran SINT1F routine.
	SINT1F(&N, &INC, &R[0], &LENR, &WSAVE[0], &LENSAV, &WORK[0], &LENWRK, &IER);
}

