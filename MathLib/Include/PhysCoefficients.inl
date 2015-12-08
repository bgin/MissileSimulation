
template<typename _Ty> __forceinline _Ty PhysCoeffs<_Ty>::Drag_Coefficient(const _Ty& radius)
{
	const _Ty six = 6.0;
	const double PI = mathlib::MathConstants::PI_DBL();
	return six * PI * radius;
	
}