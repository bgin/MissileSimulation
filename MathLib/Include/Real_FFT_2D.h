#ifndef _REAL_FFT_2D_H_
#define _REAL_FFT_2D_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Real FFT forward/backward Direction 2D class  - definition.
@file:  Real_FFT_2D.h
Wrapper around FFTPACK 5.1 library
@author: Bernard Gingold
@version:  1.0  26/10/2015
@description: file  F77_FFT_DECLARATIONS.h

*/

#include "MathLibDefinitions.h"
#include "F77_FFT_DECLARATIONS.h"

namespace   mathlib
{



	class RealFFT2D
	{
	public:

		/*
		@brief wrapper for F77 RFFT2I routine.
		For description of arguments go to F77_FFT_DECLARATIONS.h file
		*/
		void    real_fft_init2D(int ,
			int ,
			std::vector<float> & , 
			int , 
			int );

		/*
		@brief wrapper for F77 RFFT2B routine
		 4th argument should be vector<float> set to size of LDIMxM
		*/
		void    real_fft_backward2D(int ,
			 int ,
			 int ,
			 std::vector<float> &,
			 std::vector<float> &,
			 int ,
			 std::vector<float> &,
			 int ,
			 int );

		/*
		@brief wrapper for F77 RFFT2F routine
		4th argument should be set to size of LDIMxM
		*/
		void real_fft_forward2D(int ,
			int ,
			int ,
			std::vector<float> &,
			std::vector<float> &,
			int ,
			std::vector<float> &,
			int ,
			int );
	};

#include "Real_FFT_2D.inl"
}
#endif /*_REAL_FFT_2D_H_*/