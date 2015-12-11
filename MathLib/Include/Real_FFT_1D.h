#ifndef _REAL_FFT_1D_H_
#define _REAL_FFT_1D_H_

#include "MathLibDefinitions.h"
#include "F77_FFT_DECLARATIONS.h"

namespace   mathlib
{



	class  RealFFT1D
	{

	public:

		static	void    real_fft_init1D(int, 
		std::vector<float> &,
		int, 
		int);

		static  void    real_fft_backward1D(int,
			int, 
			std::vector<float> &, 
			int, 
			std::vector<float> &, 
			int, 
			std::vector<float> &, 
			int, 
			int);

		static  void    real_fft__forward1D(int,
			int,
			std::vector<float> &,
			int,
			std::vector<float> &,
			int, 
			std::vector<float> &, 
			int, 
			int);
	};

#include "Real_FFT_1D.inl"
}
#endif /*_REAL_FFT-1D_H_*/