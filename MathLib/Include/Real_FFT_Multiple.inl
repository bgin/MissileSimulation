
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Real FFT forward/backward Direction Multiple  class  - implementation.
Wrapper around FFTPACK 5.1 library
@file Real_FFT_Multiple.h
@author: Bernard Gingold
@version:  1.0  26/10/2015
@description F77_FFT_DECLARATIONS.h

*/

void      mathlib::RealFFTMultiple::real_fft_multiple_init(int N, std::vector<float> &WSAVE,
	int LENSAV, int IER)
{
	RFFTMI(&N, &WSAVE[0], &LENSAV, &IER);
}


void      mathlib::RealFFTMultiple::real_fft_multiple_backward(int LOT, int JUMP, int N, int INC,
	std::vector<float> &R, int LENR, std::vector<float> &WSAVE, int LENSAV,
	std::vector<float> &WORK, int LENWRK, int IER)
{
	RFFTMB(&LOT, &JUMP, &N, &INC, &R[0], &LENR, &WSAVE[0], &LENSAV, &WORK[0], &LENWRK, &IER);
}


void       mathlib::RealFFTMultiple::real_fft_multiple_forward(int LOT, int JUMP, int N, int INC,
	std::vector<float> &R, int LENR, std::vector<float> &WSAVE, int LENSAV,
	std::vector<float> &WORK, int LENWRK, int IER)
{
	RFFTMF(&LOT, &JUMP, &N, &INC, &R[0], &LENR, &WSAVE[0], &LENSAV, &WORK[0], &LENWRK, &IER);
}