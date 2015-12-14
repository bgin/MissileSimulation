/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Real Sine FFT forward/backward Multiple class  - wrapper implementation.
Wrapper around FFTPACK 5.1 library
@file Real_SinFFT_Multiple.inl
@author: Bernard Gingold
@version:  1.0  26/10/2015
@description: in F77_FFT_DECLARATIONS.h
*/

void      mathlib::RealSinFFTMultiple::real_sinfft_multiple_init(int N, std::vector<float> &WSAVE,
	int LENSAV, int IER)
{
	// Call Fortran SINTMI subroutine.
	SINTMI(&N, &WSAVE[0], &LENSAV, &IER);
}

void      mathlib::RealSinFFTMultiple::real_sinfft_multiple_backward(int LOT, int JUMP, int N, int INC,
	std::vector<float> &R, int LENR, std::vector<float> &WSAVE, int LENSAV,
	std::vector<float> &WORK, int LENWRK, int IER)
{
	// Call Fortran SINTMB subroutine.
	SINTMB(&LOT, &JUMP, &N, &INC, &R[0], &LENR, &WSAVE[0], &LENSAV, &WORK[0], &LENWRK, &IER);
}

void      mathlib::RealSinFFTMultiple::real_sinfft_multiple_forward(int LOT, int JUMP, int N, int INC,
	std::vector<float> &R, int LENR, std::vector<float> &WSAVE, int LENSAV,
	std::vector<float> &WORK, int LENWRK, int IER)
{
	// Call Fortran SINTMF subroutine.
	SINTMF(&LOT, &JUMP, &N, &INC, &R[0], &LENR, &WSAVE[0], &LENSAV, &WORK[0], &LENWRK, &IER);
}