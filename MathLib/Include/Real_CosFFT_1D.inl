
/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Real Cosine FFT forward/backward Direction 1D class  - wrapper implmentation.
Wrapper around FFTPACK 5.1 library
@file Real_CosFFT_1D.inl
@author: Bernard Gingold
@version:  1.0  26/10/2015
@description: in F77_FFT_DECLARATIONS.h
*/

                                                    


void         mathlib::RealCosFFT1D::real_cos_transf_init(int N, std::vector<float> &WSAVE,
	int LENSAV, int IER)
{
	// Call Fortran COSTI subroutine.
	/*
	@desc  subroutine COST1I initializes array WSAVE for use
         in its companion routines COST1F and COST1B.  The prime factor-
         ization of N together with a tabulation of the trigonometric
         functions are computed and stored in array WSAVE.  Separate
         WSAVE arrays are required for different values of N.
	*/
	COSTI(&N, &WSAVE[0], &LENSAV, &IER);
}

void         mathlib::RealCosFFT1D::real_cos_transf_backward(int N, int INC, std::vector<float> &R,
	int LENR, std::vector<float> &WSAVE, int LENSAV, std::vector<float> &WORK,
	int LENWRK, int IER)
{
	// Call Fortan COST1B subroutine.
	/*
	@desc  routine COST1B computes the one-dimensional Fourier 
          transform of an even sequence within a real array.  This 
          transform is referred to as the backward transform or Fourier 
          synthesis, transforming the sequence from spectral to physical 
          space.
	*/
	COST1B(&N, &INC, &R[0], &LENR, &WSAVE[0], &LENSAV, &WORK[0], &LENWRK, &IER);
}

void         mathlib::RealCosFFT1D::real_cos_transf_forward(int N, int INC, std::vector<float> &R,
	int LENR, std::vector<float> &WSAVE, int LENSAV, std::vector<float> &WORK,
	int LENWRK, int IER)
{
	// Call Fortran COST1F subroutine
	/*
	 @desc  routine COST1F computes the one-dimensional Fourier 
           transform of an even sequence within a real array.  This transform 
           is referred to as the forward transform or Fourier analysis, 
           transforming the sequence from  physical to spectral space.
	*/
	COST1F(&N, &INC, &R[0], &LENR, &WSAVE[0], &LENSAV, &WORK[0], &LENWRK, &IER);
}