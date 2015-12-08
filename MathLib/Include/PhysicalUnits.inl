
template<typename _Ty, int m, int l, int t, int q, int k, int i, int a> PhysUnits<_Ty, m, l, t, q, k, i, a>::PhysUnits() :value(1.0)
{

}

template<typename _Ty, int m, int l, int t, int q, int k, int i, int a> PhysUnits<_Ty,m,l,t,q,k,i,a> PhysUnits<_Ty, m, l, t, q, k, i, a>::unit()
{
	return PhysUnits();
}

template<typename _Ty, int m, int l, int t, int q, int k, int i, int a> _Ty & PhysUnits<_Ty, m, l, t, q, k, i, a>::Value()
{
	return value;
}

template<typename _Ty, int m, int l, int t, int q, int k, int i, int a> const _Ty & PhysUnits<_Ty, m, l, t, q, k, i, a>::Value() const
{
	return value;
}

template<typename _Ty, int m, int l, int t, int q, int k, int i, int a> PhysUnits<_Ty,m,l,t,q,k,i,a>& PhysUnits<_Ty,m,
	l, t, q, k, i, a>::operator+=(const PhysUnits<_Ty, m, l, t, q, k, i, a>& rhs)
{
		this->value += rhs.value;
		return *this;
	}

template<typename _Ty, int m, int l, int t, int q, int k, int i, int a> PhysUnits<_Ty,m,l,t,q,k,i,a>& PhysUnits<_Ty,m,
	l, t, q, k, i, a>::operator-=(const PhysUnits<_Ty, m, l, t, q, k, i, a>& rhs)
{
		this->value -= rhs.value;
		return *this;

	}

template<typename _Ty, int m, int l, int t, int q, int k, int i, int a> PhysUnits<_Ty,m,l,t,q,k,i,a>& PhysUnits<_Ty,m,
	l, t, q, k, i, a>::operator*=(const PhysUnits<_Ty, m, l, t, q, k, i, a>& rhs)
{
		this->value *= rhs.value;
		return *this;
	}

template<typename _Ty, int m, int l, int t, int q, int k, int i, int a> PhysUnits<_Ty,m,l,t,q,k,i,a>& PhysUnits<_Ty,m,
	l, t, q, k, i, a>::operator/=(const PhysUnits<_Ty, m, l, t, q, k, i, a>& rhs)
{
		this->value /= rhs.value;
		return *this;
	}

template<typename _Ty, int m, int l, int t, int q, int k, int i, int a> PhysUnits<_Ty,m,l,t,q,k,i,a>& PhysUnits<_Ty,m,
	l, t, q, k, i, a>::operator+=(const _Ty& val)
{
		this->value += val;
		return *this;
	}

template<typename _Ty, int m, int l, int t, int q, int k, int i, int a> PhysUnits<_Ty,m,l,t,q,k,i,a>& PhysUnits<_Ty,m,
	l, t, q, k, i, a>::operator-=(const _Ty& val)
{
		this->value -= val;
		return *this;
	}

template<typename _Ty, int m, int l, int t, int q, int k, int i, int a> PhysUnits<_Ty,m,l,t,q,k,i,a>& PhysUnits<_Ty,m,
	l, t, q, k, i, a>::operator*=(const _Ty& val)
{
		this->value *= val;
		return *this;
	}

template<typename _Ty, int m, int l, int t, int q, int k, int i, int a> PhysUnits<_Ty,m,l,t,q,k,i,a>& PhysUnits<_Ty,m,
	l, t, q, k, i, a>::operator/=(const _Ty& val)
{
		this->value /= val;
		return *this;
	}

template<typename _Ty, int m, int l, int t, int q, int k, int i, int a> PhysUnits<_Ty,m,l,t,q,k,i,a> PhysUnits<_Ty,m,
	l, t, q, k, i, a>::convert(const PhysUnits<_Ty, m, l, t, q, k, i, a>& rhs) const
{
		return this->value / rhs * unit();
	}