
#ifndef _PHYSICAL_UNITS_H_
#define _PHYSICAL_UNITS_H_

namespace mathlib
{
	template<typename _Ty, int m, int l, int t, int q, int k, int i, int a>
	class PhysUnits
	{

	public:

		//m = mass , l = length, t = time, q = elect charge, k = temperature (kelvin), i = intensity, a = angle.

		_Ty & Value();

		const _Ty & Value() const;

		static PhysUnits unit();

		PhysUnits convert(const PhysUnits&) const;

		// member operators

		PhysUnits & operator+=(const PhysUnits&);

		PhysUnits & operator-=(const PhysUnits&);

		PhysUnits & operator*=(const PhysUnits&);

		PhysUnits & operator/=(const PhysUnits&);

		PhysUnits & operator+=(const _Ty&);

		PhysUnits & operator-=(const _Ty&);

		PhysUnits & operator*=(const _Ty&);

		PhysUnits & operator/=(const _Ty&);

		
	private:

		PhysUnits();

		_Ty value;
	};

    #include "PhysicalUnits.inl"
}
#endif /*_PHYSICAL_UNITS_H_*/