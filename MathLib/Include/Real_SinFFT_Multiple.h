#ifndef _REAL_SIN_FFT_MULTIPLE_H_
#define _REAL_SIN_FFT_MULTIPLE_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Real Sine FFT forward/backward Multiple class  - wrapper definition.
Wrapper around FFTPACK 5.1 library
@file Real_SinFFT_Multiple.h
@author: Bernard Gingold
@version:  1.0  26/10/2015
@description: in F77_FFT_DECLARATIONS.h
*/

#include "MathLibDefinitions.h"
#include "F77_FFT_DECLARATIONS.h"

namespace    mathlib
{


	class RealSinFFTMultiple
	{


	public:


		/*
		@brief  wrapper for F77 SINTMI routine.
		*/
		void   real_sinfft_multiple_init(int,
			std::vector<float> &,
			int,
			int);

		/*
		@brief  wrapper for F77 SINTMB routine.
		*/
		void   real_sinfft_multiple_backward(int,
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
		@brief  wrapper for F77 SINTMF routine.
		*/
		void    real_sinfft_multiple_forward(int,
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

#include "Real_SinFFT_Multiple.inl"
}
#endif /*_REAL_SIN_FFT_MULTIPLE_H_*/