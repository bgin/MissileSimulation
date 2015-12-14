#ifndef _REAL_COSINE_FFT_MULTIPLE_H_
#define _REAL_COSINE_FFT_MULTIPLE_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Real Cosine FFT forward/backward Direction 1D class  - wrapper definition.
Wrapper around FFTPACK 5.1 library
@file Real_CosFFT_Multiple.h
@author: Bernard Gingold
@version:  1.0  26/10/2015
@description: in F77_FFT_DECLARATIONS.h
*/

#include "MathLibDefinitions.h"
#include "F77_FFT_DECLARATIONS.h"

namespace   mathlib
{


	class RealCosFFTMultiple
	{

	public:


		/*
		@brief  wrapper for F77 COSTMI routine.
		*/
		void    real_cosfft_multiple_init(int,
			std::vector<float> &,
			int,
			int);


		/*
		@brief  wrapper  for F77 COSTMB routine.
		*/
		void     real_cosfft_multiple_backward(int,
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
		@brief   wrapper  for F77 COSTMF routine.
		*/
		void     real_cosfft_multiple_forward(int,
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

#include "Real_CosFFT_Multiple.inl"
}

#endif /*_REAL_COSINE_FFT_MULTIPLE_H_*/