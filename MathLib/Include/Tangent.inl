
__forceinline  mathlib::TangentF64AVX::TangentF64AVX() : mathlib::VecF64AVX()
{

}

__forceinline  mathlib::TangentF64AVX::TangentF64AVX(const double s) : mathlib::VecF64AVX(s)
{

}

__forceinline  mathlib::TangentF64AVX::TangentF64AVX(const double v[4]) : mathlib::VecF64AVX(v)
{

}

__forceinline  mathlib::TangentF64AVX::TangentF64AVX(const double s0, const double s1, const double s2, const double s3) : mathlib::VecF64AVX(s0, s1, s2, s3)
{

}

__forceinline  mathlib::TangentF64AVX::TangentF64AVX(const __m256d vec) : mathlib::VecF64AVX(vec)
{

}

__forceinline  mathlib::TangentF64AVX::TangentF64AVX(const __m256i vec) : mathlib::VecF64AVX(vec)
{

}

__forceinline  mathlib::TangentF64AVX::TangentF64AVX(const __m128d v0, const __m128d v1) : mathlib::VecF64AVX(v0, v1)
{

}

__forceinline  mathlib::TangentF64AVX::TangentF64AVX(const TangentF64AVX &rhs)
{
	this->m_VecF64 = rhs.m_VecF64;
}

// Member operators implementation

__forceinline  mathlib::TangentF64AVX & mathlib::TangentF64AVX::operator=(const TangentF64AVX &rhs)
{
	this->m_VecF64 = rhs.m_VecF64;
	return *this;
}

__forceinline  mathlib::TangentF64AVX & mathlib::TangentF64AVX::operator+=(const TangentF64AVX &rhs)
{
	return this->operator+=(rhs);
}

__forceinline  mathlib::TangentF64AVX & mathlib::TangentF64AVX::operator-=(const TangentF64AVX &rhs)
{
	return this->operator-=(rhs);
}

__forceinline  mathlib::TangentF64AVX & mathlib::TangentF64AVX::operator*=(const TangentF64AVX &rhs)
{
	return this->operator*=(rhs);
}

__forceinline  mathlib::TangentF64AVX & mathlib::TangentF64AVX::operator/=(const TangentF64AVX &rhs)
{
	return this->operator/=(rhs);
}

__forceinline  mathlib::TangentF64AVX & mathlib::TangentF64AVX::operator==(const TangentF64AVX &rhs)
{
	return this->operator==(rhs);
}

__forceinline  mathlib::TangentF64AVX & mathlib::TangentF64AVX::operator!=(const TangentF64AVX &rhs)
{
	return this->operator!=(rhs);
}

__forceinline  mathlib::TangentF64AVX & mathlib::TangentF64AVX::operator+=(const double scalar)
{
	return this->operator+=(scalar);

}

__forceinline  mathlib::TangentF64AVX & mathlib::TangentF64AVX::operator-=(const double scalar)
{
	return this->operator-=(scalar);
}

__forceinline  mathlib::TangentF64AVX & mathlib::TangentF64AVX::operator*=(const double scalar)
{
	return this->operator*=(scalar);
}

__forceinline  mathlib::TangentF64AVX & mathlib::TangentF64AVX::operator/=(const double scalar)
{
	return this->operator/=(scalar);
}

__forceinline  mathlib::TangentF64AVX & mathlib::TangentF64AVX::operator==(const double scalar)
{
	return this->operator==(scalar);
}

__forceinline  mathlib::TangentF64AVX & mathlib::TangentF64AVX::operator!=(const double scalar)
{
	return this->operator!=(scalar);
}

__forceinline  __m256d  mathlib::TangentF64AVX::operator+(const __m256d v0, const __m256d v1)
{
	return mathlib::VecF64AVX::operator+(v0, v1);
}

__forceinline  __m256d  mathlib::TangentF64AVX::operator*(const __m256d v0, const __m256d v1)
{
	return mathlib::VecF64AVX::operator*(v0, v1);
}

__forceinline  __m256d  mathlib::TangentF64AVX::operator/(const __m256d v0, const __m256d v1)
{
	return mathlib::VecF64AVX::operator/(v0, v1);
}

__forceinline  __m256d  mathlib::TangentF64AVX::operator==(const __m256d v0, const __m256d v1)
{
	return mathlib::VecF64AVX::operator==(v0, v1);
}

__forceinline  __m256d  mathlib::TangentF64AVX::operator!=(const __m256d v0, const __m256d v1)
{
	return mathlib::VecF64AVX::operator!=(v0, v1);
}

__forceinline  __m256d  mathlib::TangentF64AVX::operator+(const  __m256d v0, const double s0)
{
	return mathlib::VecF64AVX::operator+(v0, s0);
}

__forceinline  __m256d  mathlib::TangentF64AVX::operator-(const  __m256d v0, const double s0)
{
	return mathlib::VecF64AVX::operator-(v0, s0);
}

__forceinline  __m256d  mathlib::TangentF64AVX::operator*(const  __m256d v0, const double s0)
{
	return mathlib::VecF64AVX::operator*(v0, s0);
}

__forceinline  __m256d  mathlib::TangentF64AVX::operator/(const  __m256d v0, const double s0)
{
	return mathlib::VecF64AVX::operator/(v0, s0);
}

__forceinline  __m256d  mathlib::TangentF64AVX::operator==(const  __m256d v0, const double s0)
{
	return mathlib::VecF64AVX::operator==(v0, s0);
}

__forceinline  __m256d  mathlib::TangentF64AVX::operator!=(const  __m256d v0, const double s0)
{
	return mathlib::VecF64AVX::operator!=(v0, s0);
}

__forceinline  __m256d  mathlib::TangentF64AVX::operator+(const double s0, const  __m256d v0)
{
	return mathlib::VecF64AVX::operator+(s0, v0);
}

__forceinline  __m256d  mathlib::TangentF64AVX::operator*(const double s0, const  __m256d v0)
{
	return mathlib::VecF64AVX::operator*(s0, v0);
}

__forceinline   __m256d  mathlib::TangentF64AVX::operator-(const double s0, const  __m256d v0)
{
	return mathlib::VecF64AVX::operator-(s0, v0);
}

__forceinline   __m256d  mathlib::TangentF64AVX::operator/(const double s0, const  __m256d v0)
{
	return mathlib::VecF64AVX::operator/(s0, v0);
}

__forceinline   __m256d  mathlib::TangentF64AVX::operator==(const double s0, const __m256d v0)
{
	return mathlib::VecF64AVX::operator==(s0, v0);
}

__forceinline   __m256d  mathlib::TangentF64AVX::operator!=(const double s0, const __m256d v0)
{
	return mathlib::VecF64AVX::operator!=(s0, v0);
}

// Special member functions implementation.

__forceinline  mathlib::TangentF64AVX & mathlib::TangentF64AVX::dot(const TangentF64AVX &lhs, const TangentF64AVX &rhs)
{
	this->m_VecF64 = _mm256_castps_pd(_mm256_dp_ps(_mm256_castpd_ps(lhs.m_VecF64), _mm256_castpd_ps(rhs.m_VecF64), 1));
	return *this;
}

__forceinline  mathlib::TangentF64AVX & mathlib::TangentF64AVX::abs_dot(const TangentF64AVX &lhs, const TangentF64AVX &rhs)
{
	__m256d temp = _mm256_castps_pd(_mm256_dp_ps(_mm256_castpd_ps(lhs.m_VecF64), _mm256_castpd_ps(rhs.m_VecF64), 1));
	this->m_VecF64 = _mm256_set_pd(0.0L, std::fabs(temp.m256d_f64[0]), std::fabs(temp.m256d_f64[1]), std::fabs(temp.m256d_f64[2]));
	return *this;
}

__forceinline  __m256d  mathlib::TangentF64AVX::abs_dot(const __m256d v0, const __m256d v1)
{
	return mathlib::VecF64AVX::abs_dot(v0, v1);
}

__forceinline   __m256d  mathlib::TangentF64AVX::dot(const __m256d v0, const __m256d v1)
{
	return mathlib::VecF64AVX::dot(v0, v1);
}

__forceinline  __m256d   mathlib::TangentF64AVX::cross(const __m256d v0, const __m256d v1)
{
	return mathlib::VecF64AVX::cross(v0, v1);
}

__forceinline  mathlib::TangentF64AVX &  mathlib::TangentF64AVX::direction_cosine()
{
	double a = this->extract_scalar(0); double b = this->extract_scalar(1); double c = this->extract_scalar(2);
	double s = this->sqrt_euclidean_distance();
	std::printf("s=%.9f,a=%.9f, b=%.9f, c=%.9f\n",s, a, b, c);

	double l = a / s; double m = b / s; double n = c / s;
	this->m_VecF64 = _mm256_set_pd(0.0L, l, m, n); //order shuold be reversed ie [left-to-right]
	return *this;
}

__forceinline   double   mathlib::TangentF64AVX::euclidean_distance()
{
	return this->mathlib::VecF64AVX::euclidean_distance();
}

__forceinline   double   mathlib::TangentF64AVX::sqrt_euclidean_distance()
{
	return this->mathlib::VecF64AVX::sqrt_euclidean_distance();
}

__forceinline  mathlib::TangentF64AVX & mathlib::TangentF64AVX::Normalize()
{
	this->m_VecF64 = _mm256_div_pd(this->m_VecF64, _mm256_set1_pd(this->sqrt_euclidean_distance()));
	return *this;
}

__forceinline  double   mathlib::TangentF64AVX::triple_scalar_prod(const __m256d v0, const __m256d v1, const __m256d v2)
{
	return mathlib::VecF64AVX::triple_scalar_prod(v0, v1, v2);
}

// Non-member operators

__forceinline   mathlib::TangentF64AVX  mathlib::operator+(const TangentF64AVX &lhs, const TangentF64AVX &rhs)
{
	
	__m256d result = _mm256_add_pd(lhs.get_m_VecF64(), rhs.get_m_VecF64());
	return TangentF64AVX(result);
}

__forceinline   mathlib::TangentF64AVX  mathlib::operator-(const TangentF64AVX &lhs, const TangentF64AVX &rhs)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_sub_pd(lhs.get_m_VecF64(), rhs.get_m_VecF64()));
}

__forceinline   mathlib::TangentF64AVX  mathlib::operator*( const TangentF64AVX &lhs, const TangentF64AVX &rhs)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_mul_pd(lhs.get_m_VecF64(), rhs.get_m_VecF64()));
}

__forceinline   mathlib::TangentF64AVX  mathlib::operator/(const  TangentF64AVX &lhs, const TangentF64AVX &rhs)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_div_pd(lhs.get_m_VecF64(), rhs.get_m_VecF64()));
}

__forceinline   mathlib::TangentF64AVX  mathlib::operator==(const  TangentF64AVX &lhs, const TangentF64AVX &rhs)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_cmp_pd(lhs.get_m_VecF64(), rhs.get_m_VecF64(), 0));
}

__forceinline   mathlib::TangentF64AVX  mathlib::operator!=(const TangentF64AVX &lhs, const  TangentF64AVX &rhs)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_cmp_pd(lhs.get_m_VecF64(), rhs.get_m_VecF64(), 4));
}

__forceinline   mathlib::TangentF64AVX  mathlib::operator+(const double scalar, const TangentF64AVX &v)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_add_pd(_mm256_set1_pd(scalar), v.get_m_VecF64()));
}

__forceinline  mathlib::TangentF64AVX    mathlib::operator-(const double scalar, const TangentF64AVX &v)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_sub_pd(_mm256_set1_pd(scalar), v.get_m_VecF64()));
}

__forceinline  mathlib::TangentF64AVX    mathlib::operator*(const double scalar, const TangentF64AVX &v)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_mul_pd(_mm256_set1_pd(scalar), v.get_m_VecF64()));
}

__forceinline  mathlib::TangentF64AVX    mathlib::operator/(const double scalar, const TangentF64AVX &v)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_div_pd(_mm256_set1_pd(scalar), v.get_m_VecF64()));
}

__forceinline  mathlib::TangentF64AVX    mathlib::operator==(const double scalar, const TangentF64AVX &v)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_cmp_pd(_mm256_set1_pd(scalar), v.get_m_VecF64(), 0));
}

__forceinline  mathlib::TangentF64AVX    mathlib::operator!=(const double scalar, const TangentF64AVX &v)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_cmp_pd(_mm256_set1_pd(scalar), v.get_m_VecF64(), 4));
}

__forceinline  mathlib::TangentF64AVX    mathlib::operator+(const  TangentF64AVX &v, const double scalar)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_add_pd(v.get_m_VecF64(), _mm256_set1_pd(scalar)));
}

__forceinline  mathlib::TangentF64AVX    mathlib::operator-(const   TangentF64AVX &v, const double scalar)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_sub_pd(v.get_m_VecF64(), _mm256_set1_pd(scalar)));
}

__forceinline  mathlib::TangentF64AVX    mathlib::operator*(const    TangentF64AVX &v, const double scalar)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_mul_pd(v.get_m_VecF64(), _mm256_set1_pd(scalar)));
}

__forceinline  mathlib::TangentF64AVX    mathlib::operator/(const    TangentF64AVX &v, const double scalar)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_div_pd(v.get_m_VecF64(), _mm256_set1_pd(scalar)));
}

__forceinline  mathlib::TangentF64AVX    mathlib::operator==(const   TangentF64AVX &v, const double scalar)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_cmp_pd(v.get_m_VecF64(), _mm256_set1_pd(scalar), 0));
}

__forceinline  mathlib::TangentF64AVX    mathlib::operator!=(const   TangentF64AVX &v, const double scalar)
{
	__m256d result;
	return TangentF64AVX(result = _mm256_cmp_pd(v.get_m_VecF64(), _mm256_set1_pd(scalar), 4));
}