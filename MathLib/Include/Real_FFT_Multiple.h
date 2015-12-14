#ifndef _REAL_FFT_MULTIPLE_H_
#define _REAL_FFT_MULTIPLE_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Real FFT forward/backward Direction Multiple  class  - definition.
Wrapper around FFTPACK 5.1 library
@file Real_FFT_Multiple.h
@author: Bernard Gingold
@version:  1.0  26/10/2015
@description F77_FFT_DECLARATIONS.h

*/

#include "MathLibDefinitions.h"
#include "F77_FFT_DECLARATIONS.h"

namespace   mathlib
{

	class RealFFTMultiple
	{


	public:


		/*
		@brief wrapper for F77 RFFTMI routine
		*/
		void    real_fft_multiple_init(int,
			std::vector<float> &,
			int,
			int);


		/*
		@brief  wrapper for F77 RFFTMB routine.

		*/
		void     real_fft_multiple_backward(int,
			int,
			int,
			int,
			std::vector<float> &,
			int,
			std::vector<float> &,
			int,
			std::vector<float> &,
			int,
			int);

		/*
		@brief wrapper for F77 RFFTMF routine.
		*/
		void     real_fft_multiple_forward(int,
			int,
			int,
			int,
			std::vector<float> &,
			int,
			std::vector<float> &,
			int,
			std::vector<float> &,
			int,
			int);


	};

#include "Real_FFT_Multiple.inl"
}
#endif/*_REAL_FFT_MULTIPLE_H_*/