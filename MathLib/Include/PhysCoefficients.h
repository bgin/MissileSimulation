#ifndef _PHYS_COEFFICIENTS_H_
#define _PHYS_COEFFICIENTS_H_

#include "SI.h"
#include "MathConstants.h"
namespace mathlib
{
	template<typename _Ty> class PhysCoeffs : public SIUnits<_Ty>
	{

	public:

		_Ty __forceinline static Drag_Coefficient(const _Ty&);

		
	};

#include "PhysCoefficients.inl"
}
#endif /*_PHYS_COEFFICIENTS_H_*/