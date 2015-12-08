
#ifndef _DERIVATIVE_H_
#define _DERIVATIVE_H_

#include "MathUtils.h"
#include <limits>

namespace mathlib
{

	template<typename _Ty> class DyDx
	{
	public:

		template<typename Function> __forceinline static DyDx  differentiate(Function, _Ty, _Ty);

		template<typename Function> __forceinline static DyDx  differentiate2(Function, _Ty,_Ty);

		__forceinline _Ty get_deriv() const;

		__forceinline _Ty get_error() const;

		//__forceinline static DyDx test1(const _Ty, const _Ty);
	private:

		_Ty deriv;
		_Ty error;

	 __forceinline	DyDx(const _Ty, const _Ty);
	};

#include "Derivative.inl"
}
#endif /*_DERIVATIVE_H_*/