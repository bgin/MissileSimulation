#ifndef _REAL_COSINE_FFT_1D_H_
#define _REAL_COSINE_FFT_1D_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Real Cosine FFT forward/backward Direction 1D class  - wrapper definition.
Wrapper around FFTPACK 5.1 library
@file Real_CosFFT_1D
@author: Bernard Gingold
@version:  1.0  26/10/2015
@description: in F77_FFT_DECLARATIONS.h
*/

#include "MathLibDefinitions.h"
#include "F77_FFT_DECLARATIONS.h"

namespace  mathlib
{

	class RealCosFFT1D
	{

	public:


		/*
		@brief wrapper for F77 COSTI routine.
		*/
		void    real_cos_transf_init(int,
			std::vector<float> &,
			int,
			int);


		/*
		@brief wrapper for F77 COST1B routine.
		*/
		void    real_cos_transf_backward(int,
			int,
			std::vector<float> &,
			int,
			std::vector<float> &,
			int,
			std::vector<float> &,
			int,
			int);

		/*
		@brief wrapper for F77 COST1F routine.
		*/
		void    real_cos_transf_forward(int,
			int,
			std::vector<float> &,
			int,
			std::vector<float> &,
			int,
			std::vector<float> &,
			int,
			int);
	};

#include "Real_CosFFT_1D.inl"
}
#endif /*_REAL_COSINE_FFT_1D_H_*/