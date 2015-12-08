
template<typename _Ty> __forceinline  mathlib::VectorS<_Ty>::VectorS() : x(0.0), y(0.0), z(0.0)
{
	
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty>::VectorS(const _Ty val) : x(val), y(val), z(val)
{

}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty>::VectorS(const _Ty val_x, const _Ty val_y, const _Ty val_z) :
x(val_x), y(val_y), z(val_z)
{

}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty>::VectorS(const _Ty v[3]) : x(v[0]), y(v[1]), z(v[2])
{

}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty>::VectorS(const VectorS &v) : x(v.x), y(v.y), z(v.z)
{
	
}

template<typename _Ty> __forceinline  _Ty &  mathlib::VectorS<_Ty>::X() 
{
	return this->x;
}


template<typename _Ty> __forceinline  const _Ty & mathlib::VectorS<_Ty>::X() const
{
	return this->x;
}

template<typename _Ty> __forceinline  _Ty &  mathlib::VectorS<_Ty>::Y()
{
	return this->y;
}

template<typename _Ty> __forceinline  const _Ty & mathlib::VectorS<_Ty>::Y() const
{
	return this->y;
}

template<typename _Ty> __forceinline  _Ty &  mathlib::VectorS<_Ty>::Z() 
{
	return this->z;
}

template<typename _Ty> __forceinline  const _Ty & mathlib::VectorS<_Ty>::Z() const
{
	return this->z;
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty> &  mathlib::VectorS<_Ty>::operator=(const VectorS<_Ty> &v)
{
	if (this == &v) return *this;

	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty> &  mathlib::VectorS<_Ty>::operator+=(const VectorS<_Ty> &v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;

	return *this;
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty> &  mathlib::VectorS<_Ty>::operator+=(const _Ty s)
{
	this->x += s;
	this->y += s;
	this->z += s;

	return *this;
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty>   mathlib::VectorS<_Ty>::operator+(const VectorS<_Ty> &v)
{

	return VectorS(this->x + v.x, this->y + v.y, this->z + v.z);
}



template<typename _Ty> __forceinline  mathlib::VectorS<_Ty> &  mathlib::VectorS<_Ty>::operator-=(const VectorS<_Ty> &v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;

	return *this;
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty> &  mathlib::VectorS<_Ty>::operator-=(const _Ty s)
{
	this->x -= s;
	this->y -= s;
	this->z -= s;

	return *this;
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty>    mathlib::VectorS<_Ty>::operator-(const VectorS<_Ty> &v)
{
	return VectorS(this->x - v.x, this->y - v.y, this->z - v.z);
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty>    mathlib::VectorS<_Ty>::operator-() const
{
	return VectorS(-this->x, -this->y, -this->z);
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty> &  mathlib::VectorS<_Ty>::operator*=(const VectorS<_Ty> &v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;

	return *this;
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty> &  mathlib::VectorS<_Ty>::operator*=(const _Ty s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	return *this;
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty>    mathlib::VectorS<_Ty>::operator*(const  VectorS<_Ty> &v)
{
	return VectorS(this->x * v.x, this->y * v.y, this->y * v.z);
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty> &  mathlib::VectorS<_Ty>::operator/=(const VectorS<_Ty> &v)
{
	_Ty invx = 1.0 / v.x; _Ty invy = 1.0 / v.y; _Ty invz = 1.0 / v.z;

	this->x *= invx;
	this->y *= invy;
	this->z *= invz;

	return *this;
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty> &  mathlib::VectorS<_Ty>::operator/=(const _Ty s)
{
	_Ty invx = 1.0 / s; _Ty invy = invx; _Ty invz = invx;
	this->x *= invx;
	this->y *= invy;
	this->z *= invz;
	return *this;
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty>    mathlib::VectorS<_Ty>::operator/(const  VectorS<_Ty> &v)
{
	_Ty invx = 1.0 / v.x; _Ty invy = 1.0 / v.y; _Ty invz = 1.0 / v.z;
	return VectorS(this->x * invx, this->y * invy, this->z * invz);
}

template<typename _Ty> __forceinline  bool    mathlib::VectorS<_Ty>::operator==(const VectorS<_Ty> &v)
{
	if (((std::fabs(this->x - v.x)) < std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(this->y - v.y)) < std::numeric_limits<_Ty>::epsilon())
		&& ((std::fabs(this->z - v.z)) < std::numeric_limits<_Ty>::epsilon()))
	{
		return true;
	}
}

template<typename _Ty> __forceinline  bool    mathlib::VectorS<_Ty>::operator!=(const VectorS<_Ty> &v)
{
	if (((std::fabs(this->x - v.x)) > std::numeric_limits<_Ty>::epsilon()) || ((std::fabs(this->y - v.y)) > std::numeric_limits<_Ty>::epsilon())
		|| ((std::fabs(this->z - v.z)) > std::numeric_limits<_Ty>::epsilon()))
	{
		return true;
	}
}

template<typename _Ty> __forceinline  bool    mathlib::VectorS<_Ty>::operator==(const _Ty s)
{
	if (((std::fabs(this->x - s)) < std::numeric_limits<_Ty>::epsilon()) || ((std::fabs(this->y - s)) < std::numeric_limits<_Ty>::epsilon())
		|| ((std::fabs(this->z - s)) < std::numeric_limits<_Ty>::epsilon()))
	{
		return true;
	}
}

template<typename _Ty> __forceinline  bool    mathlib::VectorS<_Ty>::operator!=(const _Ty s)
{
	if (((std::fabs(this->x - s)) > std::numeric_limits<_Ty>::epsilon()) || ((std::fabs(this->y - s)) > std::numeric_limits<_Ty>::epsilon())
		|| ((std::fabs(this->z - s)) > std::numeric_limits<_Ty>::epsilon()))
	{
		return true;
	}
}

template<typename _Ty> __forceinline  _Ty &   mathlib::VectorS<_Ty>::operator[](const int index)
{
#if defined _DEBUG
	_ASSERTE(index >= 0 && index <= 2);
#endif

	_ASSERT(index >= 0 && index <= 2);
	return (&x)[index];
}

template<typename _Ty> __forceinline  const _Ty & mathlib::VectorS<_Ty>::operator[](const int index) const
{
#if defined _DEBUG
	_ASSERTE(index >= 0 && index <= 2);
#endif

	_ASSERT(index >= 0 && index <= 2);
	return (&x)[index];
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty> &  mathlib::VectorS<_Ty>::operator++()
{
	this->x += 1.0; this->y += 1.0; this->z += 1.0;
	return *this;
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty> &  mathlib::VectorS<_Ty>::operator--()
{
	 this->x -= 1.0; this->y -= 1.0; this->z -= 1.0;
	 return *this;
}

// Special member functions.

template<typename _Ty> __forceinline  _Ty    mathlib::VectorS<_Ty>::euclidean_distance()
{
	return (this->x * this->y) + (this->y * this->y) + (this->z * this->z);
}

template<typename _Ty> __forceinline  _Ty    mathlib::VectorS<_Ty>::sqrt_euclidean_distance()
{
	return std::sqrt(this->euclidean_distance());
}

template<typename _Ty> __forceinline  _Ty    mathlib::VectorS<_Ty>::sqrt_euclidean_distance(const VectorS<_Ty> &v)
{
	return std::sqrt(euclidean_distance(v));
}

template<typename _Ty> __forceinline  _Ty    mathlib::VectorS<_Ty>::sqrt_euclidean_distance(const _Ty s0, const _Ty s1, const _Ty s2)
{
	return std::sqrt(euclidean_distance(s0, s1, s2));
}

template<typename _Ty> __forceinline  _Ty    mathlib::VectorS<_Ty>::euclidean_distance(const VectorS<_Ty> &v)
{
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

template<typename _Ty> __forceinline  _Ty    mathlib::VectorS<_Ty>::euclidean_distance(const _Ty s0, const _Ty s1, const _Ty s2)
{
	return (s0 * s0) + (s1 * s1) + (s2 * s2);
}

template<typename _Ty> __forceinline  _Ty    mathlib::VectorS<_Ty>::dot(const VectorS<_Ty> &v) const
{
	return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
}

template<typename _Ty> __forceinline  _Ty    mathlib::VectorS<_Ty>::dot(const VectorS<_Ty> &v0, const VectorS<_Ty> &v1)
{
	return (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z);
}

template<typename _Ty> __forceinline  _Ty    mathlib::VectorS<_Ty>::dot(const _Ty s0, const _Ty s1, const _Ty s2, const _Ty s3, const _Ty s4, const _Ty s5)
{
	return (s0 * s3) + (s1 * s4) + (s2 * s5);
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty> &  mathlib::VectorS<_Ty>::cross(const VectorS<_Ty> &v0)
{
	// Coordinate-Dependent.
	this->x = (this->y * v0.z) - (this->z * v0.y);
	this->y = (this->z * v0.x) - (this->x * v0.z);
	this->z = (this->x * v0.y) - (this->y * v0.x);
	return *this;
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty>   mathlib::VectorS<_Ty>::cross(const VectorS<_Ty> &v0, const VectorS<_Ty> &v1)
{
	return VectorS<_Ty>(((v0.y * v1.z) - (v0.z * v1.y)), ((v0.z * v1.x) - (v0.x * v1.z)), ((v0.x * v1.y) - (v0.y * v1.x)));
}

template<typename _Ty> __forceinline   _Ty   mathlib::VectorS<_Ty>::triple_scalar_product(const VectorS<_Ty> &v1, const VectorS<_Ty> &v2)
{
	this->x = this->x * ((v1.y * v2.z) - (v1.z * v2.y));
	this->y = this->y * ((v1.z * v2.x) - (v1.x * v2.z));
	this->z = this->z * ((v1.x * v2.y) - (v1.y * v2.x));
	return this->x + this->y * this->z;
}

template<typename _Ty> __forceinline   _Ty   mathlib::VectorS<_Ty>::triple_scalar_product(const VectorS<_Ty> &v0, const VectorS<_Ty> &v1, const VectorS<_Ty> &v2)
{
	v0.x = v0.x * ((v1.y * v2.z) - (v1.z * v2.y));
	v0.y = v0.y * ((v1.z * v2.x) - (v1.x * v2.z));
	v0.z = v0.z * ((v1.x * v2.y) - (v1.y * v2.x));
	return v0.x + v0.y + v0.z;
}

template<typename _Ty>  __forceinline        mathlib::VectorS<_Ty> &  mathlib::VectorS<_Ty>::normalize()
{
	
	return this->operator/=(this->euclidean_distance());
}

template<typename _Ty>  __forceinline        mathlib::VectorS<_Ty>    mathlib::VectorS<_Ty>::normalize(const VectorS<_Ty> &v)
{
	return v / v.euclidean_distance();
}

template<typename _Ty>  __forceinline        bool                     mathlib::VectorS<_Ty>::has_nan(const _Ty s0, const _Ty s1, const _Ty s2)
{
	return std::isnan<_Ty>(s0) || std::isnan<_Ty>(s1) || std::isnan<_Ty>(s2);
}

template<typename _Ty>  __forceinline        bool                     mathlib::VectorS<_Ty>::has_nan(const _Ty s0)
{
	return std::isnan<_Ty>(s0);
}

template<typename _Ty>  __forceinline       bool                      mathlib::VectorS<_Ty>::is_zero(const _Ty s0, const _Ty s1, const _Ty s2)
{
	if (((std::fabs(s0)) < std::numeric_limits<_Ty>::epsilon()) || ((std::fabs(s1)) < std::numeric_limits<_Ty>::epsilon())
		|| ((std::fabs(s2)) < std::numeric_limits<_Ty>::epsilon()))
		return true;
	else
		return false;
}

template<typename _Ty>  __forceinline      bool                       mathlib::VectorS<_Ty>::is_zero(const _Ty s0)
{
	if ((std::fabs(s0)) < std::numeric_limits<_Ty>::epsilon())
		return true;
	else
		return false;
}

// Non-member operators
template<typename _Ty> __forceinline  mathlib::VectorS<_Ty>  operator+(const VectorS<_Ty> &lhs, const VectorS<_Ty> &rhs)
{
	return VectorS<_Ty>(lhs.X() + rhs.X(), lhs.Y() + rhs.Y(), lhs.Z() + rhs.Z());
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty>  operator-(const VectorS<_Ty> &lhs, const VectorS<_Ty> &rhs)
{
	return VectorS<_Ty>(lhs.X() - rhs.X(), lhs.Y() - rhs.Y(), lhs.Z() - rhs.Z());
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty>  operator*(const VectorS<_Ty> &lhs, const VectorS<_Ty> &rhs)
{
	return VectorS<_Ty>(lhs.X() * rhs.X(), lhs.Y() * rhs.Y(), lhs.Z() * rhs.Z());
}

template<typename _Ty> __forceinline  mathlib::VectorS<_Ty>  operator/(const VectorS<_Ty> &lhs, const VectorS<_Ty> &rhs)
{
	
	return VectorS<_Ty>(lhs.X() / rhs.X(), lhs.Y() / rhs.Y(), lhs.Z() / rhs.Z());
}

template<typename _Ty> __forceinline  bool                   operator==(const VectorS<_Ty> &lhs, const VectorS<_Ty> &rhs)
{
	if (((std::fabs(lhs.X() - rhs.X())) < std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(lhs.Y() - rhs.Y())) < std::numeric_limits<_Ty>::epsilon())
		&& ((std::fabs(lhs.Z() - rhs.Z())) < std::numeric_limits<_Ty>::epsilon()))
	    {
			return true;
		}
}

template<typename _Ty> __forceinline  bool                   operator!=(const VectorS<_Ty> &lhs, const VectorS<_Ty> &rhs)
{
	if (((std::fabs(lhs.X() - rhs.X())) > std::numeric_limits<_Ty>::epsilon()) || ((std::fabs(lhs.Y() - rhs.Y())) > std::numeric_limits<_Ty>::epsilon())
		|| ((std::fabs(lhs.Z() - rhs.Z())) > std::numeric_limits<_Ty>::epsilon()))
	{
		return true;
	}
}

template<typename _Ty> __forceinline   mathlib::VectorS<_Ty>  operator+(const VectorS<_Ty> &lhs, const _Ty rhs)
{
	return VectorS<_Ty>(lhs.X() + rhs, lhs.Y() + rhs, lhs.Z() + rhs);
}

template<typename _Ty> __forceinline   mathlib::VectorS<_Ty>  operator-(const VectorS<_Ty> &lhs, const _Ty rhs)
{
	return VectorS<_Ty>(lhs.X() - rhs, lhs.Y() - rhs, lhs.Z() - rhs);
}
