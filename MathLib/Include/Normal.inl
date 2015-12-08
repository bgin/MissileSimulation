
template<typename _Ty> __forceinline  mathlib::NormalS<_Ty>::NormalS<_Ty>() : mathlib::VectorS<_Ty>()
{

}

	template<typename _Ty> __forceinline  mathlib::NormalS<_Ty>::NormalS<_Ty>(const _Ty s) : mathlib::VectorS<_Ty>(s)
	{

	}

	template<typename _Ty>  __forceinline   mathlib::NormalS<_Ty>::NormalS<_Ty>(const _Ty s0, const _Ty s1, const _Ty s2) : mathlib::VectorS<_Ty>(s0, s1, s2)
	{

	}

	template<typename _Ty>  __forceinline   mathlib::NormalS<_Ty>::NormalS<_Ty>(const _Ty v[3]) : mathlib::VectorS<_Ty>(v)
	{

	}

	template<typename _Ty>  __forceinline   mathlib::NormalS<_Ty>::NormalS<_Ty>(const NormalS<_Ty> &lhs) : x(lhs.x), y(lhs.y), z(lhs.z)
	{

	}

	template<typename _Ty>  __forceinline   mathlib::NormalS<_Ty>::NormalS<_Ty>(const VectorS<_Ty> &lhs) : x(lhs.x), y(lhs.y), z(lhs.z)
	{

	}

	// Member operators implementation.

	template<typename _Ty>  __forceinline   mathlib::NormalS<_Ty> &  mathlib::NormalS<_Ty>::operator=(const NormalS &lhs)
	{
		if (this == &lhs) return *this;

		this->x = lhs.x;
		this->y = lhs.y;
		this->z = lhs.z;

		return *this;
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty> &   mathlib::NormalS<_Ty>::operator+=(const NormalS &lhs)
	{
		this->x += lhs.x;
		this->y += lhs.y;
		this->z += lhs.z;
		return *this;
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty> &   mathlib::NormalS<_Ty>::operator+=(const _Ty s)
	{
		this->x += s;
		this->y += s;
		this->z += s;
		return *this;
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>     mathlib::NormalS<_Ty>::operator+(const NormalS &lhs)
	{
		return NormalS(this->x + lhs.x, this->y + lhs.y, this->z + lhs.z);
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>     mathlib::NormalS<_Ty>::operator+(const VectorS<_Ty> &lhs)
	{
		return NormalS(this->x + lhs.x, this->y + lhs.y, this->z + lhs.z);
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty> &   mathlib::NormalS<_Ty>::operator-=(const NormalS &lhs)
	{
		this->x -= lhs.x;
		this->y -= lhs.y;
		this->z -= lhs.z;
		return *this;
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty> &   mathlib::NormalS<_Ty>::operator-=(const _Ty s)
	{
		this->x -= s;
		this->y -= s;
		this->z -= s;
		return *this;
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>    mathlib::NormalS<_Ty>::operator-(const NormalS &lhs)
	{
		return NormalS(this->x - lhs.x, this->y - lhs.y, this->z - lhs.z);
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>    mathlib::NormalS<_Ty>::operator-(const VectorS<_Ty> &lhs)
	{
		return NormalS(this->x - lhs.x, this->y - lhs.y, this->z - lhs.z);
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty> &  mathlib::NormalS<_Ty>::operator*=(const NormalS &lhs)
	{
		this->x *= lhs.x;
		this->y *= lhs.y;
		this->z *= lhs.z;
		return *this;
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty> &  mathlib::NormalS<_Ty>::operator*=(const _Ty s)
	{
		this->x *= s;
		this->y *= s;
		this->z *= s;
		return *this;
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>    mathlib::NormalS<_Ty>::operator*(const NormalS &lhs)
	{
		return NormalS(this->x * lhs.x, this->y * lhs.y, this->z * lhs.z);
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>    mathlib::NormalS<_Ty>::operator*(const VectorS<_Ty> &lhs)
	{
		return NormalS(this->x * lhs.x, this->y * lhs.y, this->z * lhs.z);
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty> &  mathlib::NormalS<_Ty>::operator/=(const NormalS &lhs)
	{
#if defined _DEBUG
		_ASSERTE(((std::fabs(lhs.x)) > std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(lhs.y)) > std::numeric_limits<_Ty>::epsilon())
			&& ((std::fabs(lhs.z)) > std::numeric_limits<_Ty>::epsilon()));
#endif
		_ASSERT(((std::fabs(lhs.x)) > std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(lhs.y)) > std::numeric_limits<_Ty>::epsilon())
			&& ((std::fabs(lhs.z)) > std::numeric_limits<_Ty>::epsilon()));
		_Ty invx = 1.0 / lhs.x; _Ty invy = 1.0 / lhs.y; _Ty invz = 1.0 / lhs.z;
		this->x *= invx;
		this->y *= invy;
		this->z *= invz;
		return *this;
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty> &   mathlib::NormalS<_Ty>::operator/=(const _Ty s)
	{
#if defined _DEBUG
		_ASSERTE(((std::fabs(lhs.x)) > std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(lhs.y)) > std::numeric_limits<_Ty>::epsilon())
			&& ((std::fabs(lhs.z)) > std::numeric_limits<_Ty>::epsilon()));
#endif
		_ASSERT(((std::fabs(lhs.x)) > std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(lhs.y)) > std::numeric_limits<_Ty>::epsilon())
			&& ((std::fabs(lhs.z)) > std::numeric_limits<_Ty>::epsilon()));

		_Ty invx = 1.0 / s; _Ty invy = invx; _Ty invz = invx;
		this->x *= invx;
		this->y *= invy;
		this->z *= invz;
		return *this;
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>     mathlib::NormalS<_Ty>::operator/(const NormalS &lhs)
	{
#if defined _DEBUG
		_ASSERTE(((std::fabs(lhs.x)) > std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(lhs.y)) > std::numeric_limits<_Ty>::epsilon())
			&& ((std::fabs(lhs.z)) > std::numeric_limits<_Ty>::epsilon()));
#endif
		_ASSERT(((std::fabs(lhs.x)) > std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(lhs.y)) > std::numeric_limits<_Ty>::epsilon())
			&& ((std::fabs(lhs.z)) > std::numeric_limits<_Ty>::epsilon()));
		_Ty invx = 1.0 / lhs.x; _Ty invy = 1.0 / lhs.y; _Ty invz = 1.0 / lhs.z;
		return NormalS(this->x * invx, this->y * invy, this->z * invz);
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>     mathlib::NormalS<_Ty>::operator/(const VectorS<_Ty> &lhs)
	{
#if defined _DEBUG
		_ASSERTE(((std::fabs(lhs.x)) > std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(lhs.y)) > std::numeric_limits<_Ty>::epsilon())
			&& ((std::fabs(lhs.z)) > std::numeric_limits<_Ty>::epsilon()));
#endif
		_ASSERT(((std::fabs(lhs.x)) > std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(lhs.y)) > std::numeric_limits<_Ty>::epsilon())
			&& ((std::fabs(lhs.z)) > std::numeric_limits<_Ty>::epsilon()));
		_Ty invx = 1.0 / lhs.x; _Ty invy = 1.0 / lhs.y; _Ty invz = 1.0 / lhs.z;
		return NormalS(this->x * invx, this->y * invy, this->z * invz);
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>     mathlib::NormalS<_Ty>::operator-() const
	{
		return NormalS(-this->x, -this->y, -this->z);
	}

	template<typename _Ty>  __forceinline  bool                      mathlib::NormalS<_Ty>::operator==(const NormalS &lhs)
	{
		if (((std::fabs(this->x - lhs.x)) < std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(this->y - lhs.y)) < std::numeric_limits<_Ty>::epsilon())
			&& ((std::fabs(this->z - lhs.z)) < std::numeric_limits<_Ty>::epsilon()))
		{
			return true;
		}
	}

	template<typename _Ty>  __forceinline  bool                      mathlib::NormalS<_Ty>::operator!=(const NormalS &lhs)
	{
		if (((std::fabs(this->x - lhs.x)) > std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(this->y - lhs.y)) > std::numeric_limits<_Ty>::epsilon())
			&& ((std::fabs(this->z - lhs.z)) > std::numeric_limits<_Ty>::epsilon()))
		{
			return true;
		}
	}

	template<typename _Ty>  __forceinline  bool                       mathlib::NormalS<_Ty>::operator==(const _Ty s)
	{
		if (((std::fabs(this->x - s)) < std::numeric_limits<_Ty>::epsilon()) || ((std::fabs(this->y - s)) < std::numeric_limits<_Ty>::epsilon())
			|| ((std::fabs(this->z - s)) < std::numeric_limits<_Ty>::epsilon()))
		{
			return true;
		}
	}

	template<typename _Ty>  __forceinline  bool                       mathlib::NormalS<_Ty>::operator!=(const _Ty s)
	{
		if (((std::fabs(this->x - s)) > std::numeric_limits<_Ty>::epsilon()) || ((std::fabs(this->y - s)) > std::numeric_limits<_Ty>::epsilon())
			|| ((std::fabs(this->z - s)) > std::numeric_limits<_Ty>::epsilon()))
		{
			return true;
		}
	}

	template<typename _Ty>  __forceinline  bool                       mathlib::NormalS<_Ty>::operator==(const VectorS<_Ty> &lhs)
	{
		if (((std::fabs(this->x - lhs.x)) < std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(this->y - lhs.y)) < std::numeric_limits<_Ty>::epsilon())
			&& ((std::fabs(this->z - lhs.z)) < std::numeric_limits<_Ty>::epsilon()))
		{
			return true;
		}
	}

	template<typename _Ty>  __forceinline  bool                       mathlib::NormalS<_Ty>::operator!=(const VectorS<_Ty> &lhs)
	{
		if (((std::fabs(this->x - lhs.x)) > std::numeric_limits<_Ty>::epsilon()) || ((std::fabs(this->y - lhs.y)) > std::numeric_limits<_Ty>::epsilon())
			|| ((std::fabs(this->z - lhs.z)) > std::numeric_limits<_Ty>::epsilon()))
		{
			return true;
		}
	}

	template<typename _Ty> __forceinline  mathlib::NormalS<_Ty>::operator mathlib::VectorS<_Ty>() const
	{
		return *this;
	}

	// Special member functions:

	template<typename _Ty>  __forceinline  _Ty                        mathlib::NormalS<_Ty>::euclidean_distance()
	{
		return mathlib::VectorS<_Ty>::euclidean_distance();
	}

	template<typename _Ty>  __forceinline  _Ty                        mathlib::NormalS<_Ty>::euclidean_distance(const NormalS<_Ty> &v)
	{
		return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	}

	template<typename _Ty>  __forceinline  _Ty                        mathlib::NormalS<_Ty>::euclidean_distance(const _Ty s0, const _Ty s1, const _Ty s2)
	{
		return mathlib::VectorS<_Ty>::euclidean_distance(s0, s1, s2);
	}

	template<typename _Ty>  __forceinline  _Ty                        mathlib::NormalS<_Ty>::sqrt_euclidean_distance()
	{
		return mathlib::VectorS<_Ty>::sqrt_euclidean_distance();
	}

	template<typename _Ty>  __forceinline  _Ty                        mathlib::NormalS<_Ty>::sqrt_euclidean_distance(const NormalS<_Ty> &v)
	{
		return std::sqrt(euclidean_distance(v));
	}

	template<typename _Ty>  __forceinline  _Ty                        mathlib::NormalS<_Ty>::sqrt_euclidean_distance(const _Ty s0, const _Ty s1, const _Ty s2)
	{
		return mathlib::VectorS<_Ty>::sqrt_euclidean_distance(s0, s1, s2);
	}

	template<typename _Ty>  __forceinline  _Ty                        mathlib::NormalS<_Ty>::dot(const NormalS<_Ty> &v)
	{
		return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
	}

	template<typename _Ty>  __forceinline  _Ty                        mathlib::NormalS<_Ty>::dot(const NormalS<_Ty> &v0, const NormalS<_Ty> &v1)
	{
		return (v0.x * v1.x) + (v0.y * v1.y) + (v0.z + v1.z);
	}

	template<typename _Ty>  __forceinline  _Ty                        mathlib::NormalS<_Ty>::dot(const NormalS<_Ty> &v0, const VectorS<_Ty> &v1)
	{
		return (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z);
	}

	template<typename _Ty>  __forceinline  _Ty                        mathlib::NormalS<_Ty>::dot(const _Ty s0, const _Ty s1, const _Ty s2,
		const _Ty s3, const _Ty s4, const _Ty s5)
	{
		return mathlib::VectorS<_Ty>::dot(s0, s1, s2, s3, s4, s5);
	}

	template<typename _Ty>  __forceinline    mathlib::NormalS<_Ty> &  mathlib::NormalS<_Ty>::cross(const NormalS<_Ty> &v0)
	{
		this->x = (this->y * v0.z) - (this->z * v0.y);
		this->y = (this->z * v0.x) - (this->x * v0.z);
		this->z = (this->x * v0.y) - (this->y * v0.x);
		return *this;
	}

	template<typename _Ty>  __forceinline   mathlib::NormalS<_Ty>     mathlib::NormalS<_Ty>::cross(const NormalS<_Ty> &v0, const NormalS<_Ty> &v1)
	{
		return NormalS<_Ty>((v0.y * v1.z) - (v0.z * v1.y), (v0.z * v1.x) - (v0.x * v1.z), (v0.x * v1.y) - (v0.y * v1.x));
	}

	template<typename _Ty>  __forceinline   mathlib::NormalS<_Ty>     mathlib::NormalS<_Ty>::cross(const NormalS<_Ty> &v0, const VectorS<_Ty> &v1)
	{
		return NormalS<_Ty>((v0.y * v1.z) - (v0.z * v1.y), (v0.z * v1.x) - (v0.x * v1.z), (v0.x * v1.y) - (v0.y * v1.x));
	}

	template<typename _Ty>  __forceinline   _Ty                       mathlib::NormalS<_Ty>::triple_scalar_product(const NormalS<_Ty> &v1, const NormalS<_Ty> &v2)
	{
		this->x = this->x * ((v1.y * v2.z) - (v1.z * v2.y));
		this->y = this->y * ((v1.z * v2.x) - (v1.x * v2.z));
		this->z = this->z * ((v1.x * v2.y) - (v1.y * v2.x));
		return this->x + this->y * this->z;
	}

	template<typename _Ty>  __forceinline   _Ty                       mathlib::NormalS<_Ty>::triple_scalar_product(const NormalS<_Ty> &v0, const NormalS<_Ty> &v1,
		const NormalS<_Ty> &v2)
	{
		v0.x = v0.x * ((v1.y * v2.z) - (v1.z * v2.y));
		v0.y = v0.y * ((v1.z * v2.x) - (v1.x * v2.z));
		v0.z = v0.z * ((v1.x * v2.y) - (v1.y * v2.x));
		return v0.x + v0.y + v0.z;
	}

	template<typename _Ty>  __forceinline   mathlib::NormalS<_Ty> &   mathlib::NormalS<_Ty>::normalize()
	{
		return this->operator/=(this->euclidean_distance());
	}

	template<typename _Ty>  __forceinline   mathlib::NormalS<_Ty>     mathlib::NormalS<_Ty>::normalize(const NormalS<_Ty> &v)
	{
		return v / v.euclidean_distance();
	}

	//Non-member operators

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>  operator+(const NormalS<_Ty> &lhs, const NormalS<_Ty> &rhs)
	{
		return NormalS<_Ty>(lhs.X() + rhs.X(), lhs.Y() + rhs.Y(), lhs.Z() + rhs.Z());
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty> operator+(const NormalS<_Ty> &lhs, const VectorS<_Ty> &rhs)
	{
		return NormalS<_Ty>(lhs.X() + rhs.X(), lhs.Y() + rhs.Y(), lhs.Z() + rhs.Z());
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty> operator+(const NormalS<_Ty> &lhs, const _Ty rhs)
	{
		return NormalS<_Ty>(lhs.X() + rhs, lhs.Y() + rhs, lhs.Z() + rhs);
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>  operator+(const _Ty lhs, const NormalS<_Ty> &rhs)
	{
		return NormalS<_Ty>(lhs + rhs.X(), lhs + rhs.Y(), lhs + rhs.Z());
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>  operator-(const NormalS<_Ty> &lhs, const NormalS<_Ty> &rhs)
	{
		return NormalS<_Ty>(lhs.X() - rhs.X(), lhs.Y() - rhs.Y(), lhs.Z() - rhs.Z());
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>  operator-(const NormalS<_Ty> &lhs, const VectorS<_Ty> &rhs)
	{
		return NormalS<_Ty>(lhs.X() - rhs.X(), lhs.Y() - rhs.Y(), lhs.Z() - rhs.Z());
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>  operator-(const NormalS<_Ty> &lhs, const _Ty rhs)
	{
		return NormalS<_Ty>(lhs.X() - rhs, lhs.Y() - rhs, lhs.Z() - rhs);
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>  operator-(const _Ty lhs, const NormalS<_Ty> &rhs)
	{
		return NormalS<_Ty>(lhs - rhs.X(), lhs - rhs.Y(), lhs - rhs.Z());
	}
     
	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>  operator*(const NormalS<_Ty> &lhs, const NormalS<_Ty> &rhs)
	{
		return NormalS<_Ty>(lhs.X() * rhs.X(), lhs.Y() * rhs.Y(), lhs.Z() * rhs.Z());
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>  operator*(const NormalS<_Ty> &lhs, const VectorS<_Ty> &rhs)
	{
		return NormalS<_Ty>(lhs.X() * rhs.X(), lhs.Y() * rhs.Y(), lhs.Z() * rhs.Z());
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>  operator*(const NormalS<_Ty> &lhs, const _Ty rhs)
	{
		return NormalS<_Ty>(lhs.X() * rhs, lhs.Y() * rhs, lhs.Z() * rhs);
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>  operator*(const _Ty lhs, const NormalS<_Ty> &rhs)
	{
		return NormalS<_Ty>(lhs * rhs.X(), lhs * rhs.Y(), lhs * rhs.Z());
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>  operator/(const NormalS<_Ty> &lhs, const NormalS<_Ty> &rhs)
	{

		_Ty invx = 1.0 / rhs.X(); _Ty invy = 1.0 / rhs.Y(); _Ty invz = 1.0 / rhs.Z();
		return NormalS<_Ty>(lhs.X() * invx, lhs.Y() * invy, lhs.Z() * invz);
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>  operator/(const NormalS<_Ty> &lhs, const VectorS<_Ty> &rhs)
	{
		_Ty invx = 1.0 / rhs.X(); _Ty invy = 1.0 / rhs.Y(); _Ty invz = 1.0 / rhs.Z();
		return NormalS<_Ty>(lhs.X() * invx, lhs.Y() * invy, lhs.Z() * invz);
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>  operator/(const NormalS<_Ty> &lhs, const _Ty rhs)
	{
		_Ty invx = 1.0 / rhs; _Ty invy = invx; _Ty invz = invx;
		return NormalS<_Ty>(lhs.X() * invx, lhs.Y() * invy, lhs.Z() * invz);
		
	}

	template<typename _Ty>  __forceinline  mathlib::NormalS<_Ty>  operator/(const _Ty lhs, const NormalS<_Ty> &rhs)
	{
		_Ty invx = 1.0 / rhs.X(); _Ty invy = 1.0 / rhs.Y(); _Ty invz = 1.0 / rhs.Z();
		return NormalS<_Ty>(lhs * invx, lhs * invy, lhs * invz);
	}

	template<typename _Ty>  __forceinline  bool                   operator==(const NormalS<_Ty> &lhs, const NormalS<_Ty> &rhs)
	{
		if (((std::fabs(lhs.X() - rhs.X()) < std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(lhs.Y() - rhs.Y())) < std::numeric_limits<_Ty>::epsilon())
			&& ((std::fabs(lhs.Z() - rhs.Z()) < std::numeric_limits<_Ty>::epsilon()))
		{
			return true;
		}
	}

	template<typename _Ty>  __forceinline  bool                   operator==(const NormalS<_Ty> &lhs, const VectorS<_Ty> &rhs)
	{
		if (((std::fabs(lhs.X() - rhs.X()) < std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(lhs.Y() - rhs.Y())) < std::numeric_limits<_Ty>::epsilon())
			&& ((std::fabs(lhs.Z() - rhs.Z()) < std::numeric_limits<_Ty>::epsilon()))
		{
				return true;
			}
	}

	template<typename _Ty>  __forceinline  bool                   operator==(const NormalS<_Ty> &lhs, const _Ty rhs)
	{
		if (((std::fabs(lhs.X() - rhs) < std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(lhs.Y() - rhs)) < std::numeric_limits<_Ty>::epsilon())
			&& ((std::fabs(lhs.Z() - rhs) < std::numeric_limits<_Ty>::epsilon()))
		{
				return true;
			}
	}

	template<typename _Ty>  __forceinline  bool                   operator==(const _Ty lhs, const NormalS<_Ty> &rhs)
	{
		if (((std::fabs(lhs - rhs.X()) < std::numeric_limits<_Ty>::epsilon()) && ((std::fabs(lhs - rhs.Y()) < std::numeric_limits<_Ty>::epsilon())
			&& ((std::fabs(lhs - rhs.Z()) < std::numeric_limits<_Ty>::epsilon()))
		{
				return true;
			}
	}

	template<typename _Ty>  __forceinline  bool                    operator!=(const NormalS<_Ty> &lhs, const NormalS<_Ty> &rhs)
	{
		if (((std::fabs(lhs.X() - rhs.X())) > std::numeric_limits<_Ty>::epsilon()) || ((std::fabs(lhs.Y() - rhs.Y())) > std::numeric_limits<_Ty>::epsilon())
			|| ((std::fabs(lhs.Z() - rhs.Z())) > std::numeric_limits<_Ty>::epsilon()))
		{
			return true;
		}
	}

	template<typename _Ty> __forceinline   bool                    operator!=(const NormalS<_Ty> &lhs, const VectorS<_Ty> &rhs)
	{
		if (((std::fabs(lhs.X() - rhs.X())) > std::numeric_limits<_Ty>::epsilon()) || ((std::fabs(lhs.Y() - rhs.Y())) > std::numeric_limits<_Ty>::epsilon())
			|| ((std::fabs(lhs.Z() - rhs.Z())) > std::numeric_limits<_Ty>::epsilon()))
		{
			return true;
		}
	}

	template<typename _Ty> __forceinline   bool                    operator!=(const NormalS<_Ty> &lhs, const _Ty rhs)
	{
		if (((std::fabs(lhs.X() - rhs)) > std::numeric_limits<_Ty>::epsilon()) || ((std::fabs(lhs.Y() - rhs)) > std::numeric_limits<_Ty>::epsilon())
			|| ((std::fabs(lhs.Z() - rhs)) > std::numeric_limits<_Ty>::epsilon()))
		{
			return true;
		}
	}

	template<typename _Ty> __forceinline   bool                    operator!=(const _Ty lhs, const NormalS<_Ty> &rhs)
	{
		if (((std::fabs(lhs - rhs.X())) > std::numeric_limits<_Ty>::epsilon()) || ((std::fabs(lhs - rhs.Y())) > std::numeric_limits<_Ty>::epsilon())
			|| ((std::fabs(lhs - rhs.Z())) > std::numeric_limits<_Ty>::epsilon()))
		{
			return true;
		}
	}

