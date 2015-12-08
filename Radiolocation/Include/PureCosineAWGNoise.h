#ifndef _PURE_COSINE_AWG_NOISE_H_
#define _PURE_COSINE_AWG_NOISE_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Pure Cosine with Additive White Gaussian Noise class- definition
@aulthor: Bernard Gingold
@version:  1.0  26/10/2015

*/

#include "PureCosine.h"
#include "WhiteGaussianNoise.h"

namespace   radiolocation
{

	class PureCosAWGNoise
	{

		_Raises_SEH_exception_  __thiscall  PureCosAWGNoise(_In_ struct PureCosineParams const&, _In_ struct WGNoiseParams const&);

		__thiscall  PureCosAWGNoise(_In_  PureCosAWGNoise const&);

		__thiscall  PureCosAWGNoise(_In_  PureCosAWGNoise &&);

		__thiscall  ~PureCosAWGNoise() = default;

		PureCosAWGNoise &  __thiscall operator=(_In_ PureCosAWGNoise const&);

		PureCosAWGNoise &  __thiscall operator=(_In_ PureCosAWGNoise &&);

		friend  std::ostream &   operator<<(_In_ std::ostream&, _In_ PureCosAWGNoise const&);

		__forceinline   std::size_t     samples() const;

		__forceinline   std::vector<std::pair<double, double>>  CosGaussNoise() const;

		__forceinline   PureCosineWave   CosPulse() const;

		__forceinline   WGaussianNoise   GaussNoise() const;

		__forceinline   JonesVector      Polarization() const;

		



	private:

		std::size_t  m_samples;

		_Field_size_(m_samples) std::vector<std::pair<double, double>> m_vCosGaussNoise;

		radiolocation::PureCosineWave  m_oCosPulse;

		radiolocation::WGaussianNoise  m_oGaussNoise;

		JonesVector m_oPolarizationVec;

		
	};


#include "PureCosineAWGNoise.inl"
}
#endif  /*_PURE_COSINE_AWG_NOISE_H_*/