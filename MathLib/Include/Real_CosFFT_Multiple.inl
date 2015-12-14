
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Real Cosine FFT forward/backward Direction 1D class  - wrapper implementation.
Wrapper around FFTPACK 5.1 library
@file Real_CosFFT_Multiple.inl
@author: Bernard Gingold
@version:  1.0  26/10/2015
@description: in F77_FFT_DECLARATIONS.h
*/


void          mathlib::RealCosFFTMultiple::real_cosfft_multiple_init(int N, std::vector<float> &WSAVE,
	int LENSAV, int IER)
{
	// Call Fortran COSTMI subroutine.
	COSTMI(&N, &WSAVE[0], &LENSAV, &IER);
}

void          mathlib::RealCosFFTMultiple::real_cosfft_multiple_backward(int LOT, int JUMP, int N, int INC,
	std::vector<float> &R, int LENR, std::vector<float> &WSAVE, int LENSAV,
	std::vector<float> &WORK, int LENWRK, int IER)
{
	// Call Fortran COSTMB routine.
	COSTMB(&LOT, &JUMP, &N, &INC, &R[0], &LENR, &WSAVE[0], &LENSAV, &WORK[0], &LENWRK, &IER);
}

void          mathlib::RealCosFFTMultiple::real_cosfft_multiple_forward(int LOT, int JUMP, int N, int INC,
	std::vector<float> &R, int LENR, std::vector<float> &WSAVE, int LENSAV,
	std::vector<float> &WORK, int LENWRK, int IER)
{
	COSTMF(&LOT, &JUMP, &N, &INC, &R[0], &LENR, &WSAVE[0], &LENSAV, &WORK[0], &LENWRK, &IER);
}
