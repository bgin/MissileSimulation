
template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>::TangentS<_Ty>() : mathlib::VectorS<_Ty>()
{

}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>::TangentS<_Ty>(const _Ty s) : mathlib::VectorS<_Ty>(s)
{

}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>::TangentS<_Ty>(const _Ty s0, const _Ty s1, const _Ty s2) : mathlib::VectorS<_Ty>(s0, s1, s2)
{

}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>::TangentS<_Ty>(const _Ty v[3]) : mathlib::VectorS<_Ty>(v)
{

}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>::TangentS<_Ty>(const TangentS<_Ty> &other) : x(other.x), y(other.y), z(other.z)
{
	
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>::TangentS<_Ty>(const VectorS<_Ty> &other) : x(other.x), y(other.y), z(other.z)
{

}

// Member operators implementation:

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty> &  mathlib::TangentS<_Ty>::operator=(const TangentS<_Ty> const &other)
{
	if (this == &rhs) return *this;

	this->x = other.x;
	this->y = other.y;
	this->z = other.z;

	return *this;
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty> &  mathlib::TangentS<_Ty>::operator+=(const TangentS<_Ty> const &other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty> &  mathlib::TangentS<_Ty>::operator+=(const VectorS<_Ty> const &other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty> &  mathlib::TangentS<_Ty>::operator+=(const _Ty s)
{
	this->x += s;
	this->y += s;
	this->z += s;
	return *this;
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>    mathlib::TangentS<_Ty>::operator+(const TangentS<_Ty> const &v)
{
	return TangentS<_Ty>(this->x + v.x, this->y + v.y, this->z + v.z);
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>    mathlib::TangentS<_Ty>::operator+(const VectorS<_Ty> const &v)
{
	return TangentS<_Ty>(this->x + v.x, this->y + v.y, this->z + v.z);
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>    mathlib::TangentS<_Ty>::operator+(const _Ty s)
{
	return TangentS<_Ty>(this->x + s, this->y + s, this->z + s);
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty> &  mathlib::TangentS<_Ty>::operator-=(const TangentS<_Ty> const &other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty> &  mathlib::TangentS<_Ty>::operator-=(const VectorS<_Ty> const &other)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty> &  mathlib::TangentS<_Ty>::operator-=(const _Ty s)
{
	this->x -= s;
	this->y -= s;
	this->z -= s;
	return *this;
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>    mathlib::TangentS<_Ty>::operator-(const TangentS<_Ty> const &v)
{
	return TangentS<_Ty>(this->x - v.x, this->y - v.y, this->z - v.z);
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>    mathlib::TangentS<_Ty>::operator-(const VectorS<_Ty>  const &v)
{
	return TangentS<_Ty>(this->x - v.x, this->y - v.y, this->z - v.z);
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>    mathlib::TangentS<_Ty>::operator-(const _Ty s)
{
	return TangentS<_Ty>(this->x - s, this->y - s, this->z - s);
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>  &  mathlib::TangentS<_Ty>::operator*=(const TangentS<_Ty> const &other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	return *this;
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>  &  mathlib::TangentS<_Ty>::operator*=(const VectorS<_Ty> const &other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	return *this;
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>  &  mathlib::TangentS<_Ty>::operator*=(const _Ty s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	return *this;
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>     mathlib::TangentS<_Ty>::operator*(const TangentS<_Ty> const &v)
{
	return TangentS<_Ty>(this->x * v.x, this->y * v.y, this->z * v.z);
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>     mathlib::TangentS<_Ty>::operator*(const VectorS<_Ty> const&v)
{
	return TangentS<_Ty>(this->x * v.x, this->y * v.y, this->z * v.z);
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>     mathlib::TangentS<_Ty>::operator*(const _Ty s)
{
	return TangentS<_Ty>(this->x * s, this->y * s, this->z * s);
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty> &   mathlib::TangentS<_Ty>::operator/=(const TangentS const &other)
{
#if defined _DEBUG
	_ASSERTE(!has_nan(other.x, other.y, other.z));
#endif
	_ASSERT(!has_nan(other.x, other.y, other.z));
	_Ty invx = 1.0 / other.x; _Ty invy = 1.0 / other.y; _Ty invz = 1.0 / other.z;
	this->x *= invx;
	this->y *= invy;
	this->z *= invz;
	return *this;
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty> &    mathlib::TangentS<_Ty>::operator/=(const VectorS<_Ty> const &other)
{
#if defined _DEBUG
	_ASSERTE(!has_nan(other.x, other.y, other.z));
#endif
	_ASSERT(!has_nan(other.x, other.y, other.z));
	_Ty invx = 1.0 / other.x; _Ty invy = 1.0 / other.y; _Ty invz = 1.0 / other.z;
	this->x *= invx;
	this->y *= invy;
	this->z *= invz;
	return *this;
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty> &     mathlib::TangentS<_Ty>::operator/=(const _Ty s)
{
#if defined _DEBUG
	_ASSERTE(!has_nan(s));
#endif
	_ASSERT(!has_nan(s));
	_Ty invx = 1.0 / s; _Ty invy = invx; _Ty invz = invx;
	this->x *= invx;
	this->y *= invy;
	this->z *= invz;
	return *this;
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>       mathlib::TangentS<_Ty>::operator/(const TangentS<_Ty> const &v)
{
#if defined _DEBUG
	_ASSERTE(!has_nan(v.x, v.y, v.z));
#endif
	_ASSERT(!has_nan(v.x, v.y, v.z));
	_Ty invx = 1.0 / v.x; _Ty invy = 1.0 / v.y; _Ty invz = 1.0 / v.z;

	return TangentS<_Ty>(this->x * invx, this->y * invy, this->z * v.z);

}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>       mathlib::TangentS<_Ty>::operator/(const VectorS<_Ty> const &v)
{
#if defined _DEBUG
	_ASSERTE(!has_nan(v.x, v.y, v.z));
#endif
	_ASSERT(!has_nan(v.x, v.y, v.z));
	_Ty invx = 1.0 / v.x; _Ty invy = 1.0 / v.y; _Ty invz = 1.0 / v.z;
	return TangentS<_Ty>(this->x * invx, this->y * invy, this->z * invz);
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>       mathlib::TangentS<_Ty>::operator/(const _Ty s)
{
#if defined _DEBUG
	_ASSERTE(!has_nan(s));
#endif
	_ASSERT(!has_nan(s));
	_Ty invx = 1.0 / s; _Ty invy = invx; _Ty invz = invx;
	return TangentS<_Ty>(this->x * invx, this->y * invy, this->z * invz);
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>       mathlib::TangentS<_Ty>::operator-() const
{
	return TangentS<_Ty>(-this->x, -this->y, -this->z);
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty> &     mathlib::TangentS<_Ty>::operator++()
{
	this->x += 1.0;
	this->y += 1.0;
	this->z += 1.0;
	return *this;
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty> &     mathlib::TangentS<_Ty>::operator--()
{
	this->x -= 1.0;
	this->y -= 1.0;
	this->z -= 1.0;
	return *this;
}

template<typename _Ty>  __forceinline  bool                         mathlib::TangentS<_Ty>::operator==(const TangentS<_Ty> const &other)
{
	if (((std::fabs(this->x - other.x)) < std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(this->y - other.y)) < std::numeric_limits<_Ty>::epsilon())
		&& ((std::fabs(this->z - other.z)) < std::numeric_limits<_Ty>::epsilon()))
		return true;
	else
		return false;
}

template<typename _Ty>  __forceinline bool                          mathlib::TangentS<_Ty>::operator==(const VectorS<_Ty> const &other)
{
	if (((std::fabs(this->x - other.x)) < std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(this->y - other.y)) < std::numeric_limits<_Ty>::epsilon())
		&& ((std::fabs(this->z - other.z)) < std::numeric_limits<_Ty>::epsilon()))
		return true;
	else
		return false;
}

template<typename _Ty>  __forceinline bool                          mathlib::TangentS<_Ty>::operator==(const _Ty s)
{
	if (((std::fabs(this->x - s)) < std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(this->y - s)) < std::numeric_limits<_Ty>::epsilon())
		&& ((std::fabs(this->z - s)) < std::numeric_limits<_Ty>::epsilon()))
		return true;
	else
		return false;
}

template<typename _Ty>  __forceinline bool                          mathlib::TangentS<_Ty>::operator!=(const TangentS<_Ty> const &other)
{
	if (((std::fabs(this->x - other.x)) > std::numeric_limits<_Ty>::epsilon()) || ((std::fabs(this->y - other.y)) > std::numeric_limits<_Ty>::epsilon())
		|| ((std::fabs(this->z - other.z)) > std::numeric_limits<_Ty>::epsilon()))
		return true;
	else
		return false;
}

template<typename _Ty>  __forceinline bool                          mathlib::TangentS<_Ty>::operator!=(const VectorS<_Ty> const &other)
{
	if (((std::fabs(this->x - other.x)) > std::numeric_limits<_Ty>::epsilon()) || ((std::fabs(this->y - other.y)) > std::numeric_limits<_Ty>::epsilon())
		|| ((std::fabs(this->z - other.z)) > std::numeric_limits<_Ty>::epsilon()))
		return true;
	else
		return false;
}

template<typename _Ty>  __forceinline bool                          mathlib::TangentS<_Ty>::operator!=(const _Ty s)
{
	// True when this->x - s > epsilon, otherwise false
	if (((std::fabs(this->x - s)) > std::numeric_limits<_Ty>::epsilon()) || ((std::fabs(this->y - s)) > std::numeric_limits<_Ty>::epsilon())
		|| ((std::fabs(this->z - s)) > std::numeric_limits<_Ty>::epsilon()))
		return true;
	else
		return false;
}

// Special member functions implementation:

template<typename _Ty>  __forceinline  _Ty  mathlib::TangentS<_Ty>::euclidean_distance()
{
	return mathlib::VectorS<_Ty>::euclidean_distance();
}

template<typename _Ty>  __forceinline  _Ty  mathlib::TangentS<_Ty>::euclidean_distance(const TangentS<_Ty> &v)
{
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

template<typename _Ty>  __forceinline  _Ty  mathlib::TangentS<_Ty>::euclidean_distance(const _Ty s0, const _Ty s1, const _Ty s2)
{
	return mathlib::VectorS<_Ty>::euclidean_distance(s0, s1, s2);
}

template<typename _Ty>  __forceinline  _Ty  mathlib::TangentS<_Ty>::sqrt_euclidean_distance()
{
	return mathlib::VectorS<_Ty>::sqrt_euclidean_distance();
}

template<typename _Ty>  __forceinline  _Ty  mathlib::TangentS<_Ty>::sqrt_euclidean_distance(const TangentS<_Ty> &v)
{
	return std::sqrt(euclidean_distance(v));
}

template<typename _Ty>  __forceinline  _Ty  mathlib::TangentS<_Ty>::sqrt_euclidean_distance(const _Ty s0, const _Ty s1, const _Ty s2)
{
	return mathlib::VectorS<_Ty>::sqrt_euclidean_distance(s0, s1, s2);
}

template<typename _Ty>  __forceinline  _Ty  mathlib::TangentS<_Ty>::dot(const TangentS<_Ty> &lhs, const TangentS<_Ty> &rhs)
{
	return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

template<typename _Ty>  __forceinline  _Ty  mathlib::TangentS<_Ty>::dot(const TangentS<_Ty> &lhs, const TangentS<_Ty> &rhs)
{
	return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

template<typename _Ty>  __forceinline  _Ty  mathlib::TangentS<_Ty>::dot(const TangentS<_Ty> &other)
{
	return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty> &  mathlib::TangentS<_Ty>::cross(const TangentS<_Ty> &v0)
{
	this->x = (this->y * v0.z) - (this->z * v0.y);
	this->y = (this->z * v0.x) - (this->x * v0.z);
	this->z = (this->x * v0.y) - (this->y * v0.x);
	return *this;
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>    mathlib::TangentS<_Ty>::cross(const TangentS<_Ty> &v0, const TangentS<_Ty> &v1)
{
	return TangentS<_Ty>((v0.y * v1.z) - (v1.z * v0.y), (v0.z * v1.x) - (v1.x * v0.z), (v0.x * v1.y) - (v0.y * v1.x));
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>    mathlib::TangentS<_Ty>::cross(const TangentS<_Ty> &v0, const VectorS<_Ty> &v1)
{
	return TangentS<_Ty>((v0.y * v1.z) - (v1.z * v0.y), (v0.z * v1.x) - (v1.x * v0.z), (v0.x * v1.y) - (v0.y * v1.x));
}

template<typename _Ty>  __forceinline   _Ty       mathlib::TangentS<_Ty>::triple_scalar_product(const TangentS<_Ty> &v1, const TangentS<_Ty> &v2)
{
	this->x = this->x * ((v1.y * v2.z) - (v1.z * v2.y));
	this->y = this->y * ((v1.z * v2.x) - (v1.x * v2.z));
	this->z = this->z * ((v1.x * v2.y) - (v1.y * v2.x));
	return this->x + this->y * this->z;
}

template<typename _Ty>  __forceinline   _Ty       mathlib::TangentS<_Ty>::triple_scalar_product(const TangentS<_Ty> &v0, const TangentS<_Ty> &v1,
	const TangentS<_Ty> &v2)
{
	v0.x = v0.x * ((v1.y * v2.z) - (v1.z * v2.y));
	v0.y = v0.y * ((v1.z * v2.x) - (v1.x * v2.z));
	v0.z = v0.z * ((v1.x * v2.y) - (v1.y * v2.x));
	return v0.x + v0.y + v0.z;
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty> &       mathlib::TangentS<_Ty>::normalize()
{
	return this->operator/=(this->euclidean_distance());
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>         mathlib::TangentS<_Ty>::normalize(const TangentS<_Ty> &v)
{
	return v.operator/(v.euclidean_distance());
}

// Non-member operators implementation:

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>      operator+(const TangentS<_Ty> const &lhs, const TangentS<_Ty> const &rhs)
{
	return TangentS<_Ty>(lhs.X() + rhs.X(), lhs.Y() + rhs.Y(), lhs.Z() + rhs.Z());
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>      operator+(const TangentS<_Ty> const &lhs, const VectorS<_Ty> const &rhs)
{
	return TangentS<_Ty>(lhs.X() + rhs.X(), lhs.Y() + rhs.Y(), lhs.Z() + rhs.Z());
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>      operator+(const TangentS<_Ty> const &lhs, const _Ty rhs)
{
	return TangentS<_Ty>(lhs.X() + rhs, lhs.Y() + rhs, lhs.Z() + rhs);
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>      operator+(const _Ty lhs, const TangentS<_Ty> const &rhs)
{
	return TangentS<_Ty>(lhs + rhs.X(), lhs + rhs.Y(), lhs + rhs.Z());
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>      operator-(const TangentS<_Ty> const &lhs, const TangentS<_Ty> const &rhs)
{
	return TangentS<_Ty>(lhs.X() - rhs.X(), lhs.Y() - rhs.Y(), lhs.Z() - rhs.Z());
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>      operator-(const TangentS<_Ty> const &lhs, const VectorS<_Ty> const &rhs)
{
	return TangentS<_Ty>(lhs.X() - rhs.X(), lhs.Y() - rhs.Y(), lhs.Z() - rhs.Z());
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>      operator-(const TangentS<_Ty> const &lhs, const _Ty rhs)
{
	return TangentS<_Ty>(lhs.X() - rhs, lhs.Y() - rhs, lhs.Z() - rhs);
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>      operator-(const _Ty lhs, const TangentS<_Ty> const &rhs)
{
	return TangentS<_Ty>(lhs - rhs.X(), lhs - rhs.Y(), lhs - rhs.Z());
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>      operator*(const TangentS<_Ty> const &lhs, const TangentS<_Ty> const &rhs)
{
	return TangentS<_Ty>(lhs.X() * rhs.X(), lhs.Y() * rhs.Y(), lhs.Z() * rhs.Z());
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>      operator*(const TangentS<_Ty> const &lhs, const VectorS<_Ty> const &rhs)
{
	return TangentS<_Ty>(lhs.X() * rhs.X(), lhs.Y() * rhs.Y(), lhs.Z() * rhs.Z());
}

template<typename _Ty>  __forceinline  mathlib::TangentS<_Ty>      operator*(const TangentS<_Ty> const &lhs, const _Ty rhs)
{
	return TangentS<_Ty>(lhs.X * rhs, lhs.Y() * rhs, lhs.Z() * rhs);
}