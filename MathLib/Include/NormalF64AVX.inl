
// Constructors Implementation.
__forceinline  mathlib::NormF64AVX::NormF64AVX() : mathlib::VecF64AVX()
{
#if defined _DEBUG
	std::printf("NormF64AVX::NormF64AVX(): called at loc=%d\n", __LINE__);
	std::printf("----------------------------------------------------\n");
	std::printf("In file:%s\n\n", __FILE__);
#endif
}

__forceinline  mathlib::NormF64AVX::NormF64AVX(const double s) : mathlib::VecF64AVX(s)
{
#if defined _DEBUG
	std::printf("NormF64AVX::NormF64AVX(const double): called at loc=%d\n", __LINE__);
	std::printf("----------------------------------------------------\n");
	std::printf("In file:%s\n\n", __FILE__);
#endif
}

__forceinline  mathlib::NormF64AVX::NormF64AVX(const double v[4]) : mathlib::VecF64AVX(v)
{
#if defined _DEBUG
	std::printf("NormF64AVX::NormF64AVX(const double *): called at loc=%d\n", __LINE__);
	std::printf("----------------------------------------------------\n");
	std::printf("In file:%s\n\n", __FILE__);
#endif
}

__forceinline  mathlib::NormF64AVX::NormF64AVX(const double s0, const double s1, const double s2, const double s3) : mathlib::VecF64AVX(s0, s1, s2, s3)
{
#if defined _DEBUG
	std::printf("NormF64AVX::NormF64AVX(const double,const double,const double,const double): called at loc=%d\n", __LINE__);
	std::printf("----------------------------------------------------\n");
	std::printf("In file:%s\n\n", __FILE__);
#endif
}

__forceinline mathlib::NormF64AVX::NormF64AVX(const __m256d v) : mathlib::VecF64AVX(v)
{
#if defined _DEBUG
	std::printf("NormF64AVX::NormF64AVX(const __m256d): called at loc=%d\n", __LINE__);
	std::printf("----------------------------------------------------\n");
	std::printf("In file:%s\n\n", __FILE__);
#endif
}

__forceinline mathlib::NormF64AVX::NormF64AVX(const __m256i v) : mathlib::VecF64AVX(v)
{
#if defined _DEBUG
	std::printf("NormF64AVX::NormF64AVX(const __m256i): called at loc=%d\n", __LINE__);
	std::printf("----------------------------------------------------\n");
	std::printf("In file:%s\n\n", __FILE__);
#endif
}

__forceinline mathlib::NormF64AVX::NormF64AVX(const __m128d v0, const __m128d v1) : mathlib::VecF64AVX(v0, v1)
{
#if defined _DEBUG
	std::printf("NormF64AVX::NormF64AVX(const __m128d, const __m128d): called at loc=%d\n", __LINE__);
	std::printf("----------------------------------------------------\n");
	std::printf("In file:%s\n\n", __FILE__);
#endif
}

__forceinline mathlib::NormF64AVX::NormF64AVX(const NormF64AVX &rhs)
{
	this->m_VecF64 = rhs.m_VecF64;
#if defined _DEBUG
	std::printf("NormF64AVX::NormF64AVX(const NormF64AVX &): called at loc=%d\n", __LINE__);
	std::printf("----------------------------------------------------\n");
	std::printf("In file:%s\n\n", __FILE__);
#endif
}

// Member operators implementation.

__forceinline mathlib::NormF64AVX & mathlib::NormF64AVX::operator=(const NormF64AVX &rhs)
{
	this->m_VecF64 = rhs;
	return *this;
}

__forceinline mathlib::NormF64AVX & mathlib::NormF64AVX::operator+=(const NormF64AVX &rhs)
{
	this->m_VecF64 = _mm256_add_pd(this->m_VecF64, rhs.m_VecF64);
	return *this;
}

__forceinline mathlib::NormF64AVX & mathlib::NormF64AVX::operator-=(const NormF64AVX &rhs)
{
	this->m_VecF64 = _mm256_sub_pd(this->m_VecF64, rhs.m_VecF64);
	return *this;
}

__forceinline mathlib::NormF64AVX &  mathlib::NormF64AVX::operator*=(const NormF64AVX &rhs)
{
	this->m_VecF64 = _mm256_mul_pd(this->m_VecF64, rhs.m_VecF64);
	return *this;
}

__forceinline mathlib::NormF64AVX &  mathlib::NormF64AVX::operator/=(const NormF64AVX &rhs)
{
	this->m_VecF64 = _mm256_div_pd(this->m_VecF64, rhs.m_VecF64);
	return *this;
}

__forceinline mathlib::NormF64AVX    mathlib::NormF64AVX::operator==(const NormF64AVX &rhs)
{
	
	return mathlib::NormF64AVX(_mm256_cmp_pd(this->m_VecF64, rhs.m_VecF64, 0));
}

__forceinline mathlib::NormF64AVX    mathlib::NormF64AVX::operator!=(const NormF64AVX &rhs)
{
	return mathlib::NormF64AVX(_mm256_cmp_pd(this->m_VecF64, rhs.m_VecF64, 4));
}

__forceinline mathlib::NormF64AVX &  mathlib::NormF64AVX::operator+=(const double scalar)
{
	this->m_VecF64 = _mm256_add_pd(this->m_VecF64, _mm256_set_pd(scalar,scalar,scalar,scalar));
	return *this;
}

__forceinline mathlib::NormF64AVX &  mathlib::NormF64AVX::operator-=(const double scalar)
{   
	this->m_VecF64 = _mm256_sub_pd(this->m_VecF64, _mm256_set_pd(scalar, scalar, scalar, scalar));
	return *this;
}

__forceinline mathlib::NormF64AVX &  mathlib::NormF64AVX::operator*=(const double scalar)
{
	this->m_VecF64 = _mm256_mul_pd(this->m_VecF64, _mm256_set_pd(scalar, scalar, scalar, scalar));
	return *this;
}

__forceinline mathlib::NormF64AVX &  mathlib::NormF64AVX::operator/=(const double scalar)
{
	this->m_VecF64 = _mm256_div_pd(this->m_VecF64, _mm256_set_pd(scalar, scalar, scalar, scalar));
	return *this;
}

__forceinline mathlib::NormF64AVX    mathlib::NormF64AVX::operator==(const double scalar)
{
	
	return mathlib::NormF64AVX(_mm256_cmp_pd(this->m_VecF64, _mm256_set_pd(scalar, scalar, scalar, scalar), 0));
}

__forceinline mathlib::NormF64AVX    mathlib::NormF64AVX::operator!=(const double scalar)
{
	return mathlib::NormF64AVX(_mm256_cmp_pd(this->m_VecF64, _mm256_set_pd(scalar, scalar, scalar, scalar), 4));
}

__forceinline  __m256d               mathlib::NormF64AVX::operator+(const __m256d v0, const __m256d v1)
{
	return mathlib::VecF64AVX::operator+(v0, v1);
}

__forceinline __m256d                mathlib::NormF64AVX::operator-(const __m256d v0, const __m256d v1)
{
	return mathlib::VecF64AVX::operator-(v0, v1);
}

__forceinline __m256d                mathlib::NormF64AVX::operator*(const __m256d v0, const __m256d v1)
{
	return mathlib::VecF64AVX::operator*(v0, v1);
}

__forceinline __m256d                mathlib::NormF64AVX::operator/(const __m256d v0, const __m256d v1)
{
	return mathlib::VecF64AVX::operator/(v0, v1);
}

__forceinline __m256d                mathlib::NormF64AVX::operator==(const __m256d v0, const __m256d v1)
{
	return mathlib::VecF64AVX::operator==(v0, v1);
}

__forceinline __m256d                mathlib::NormF64AVX::operator!=(const __m256d v0, const __m256d v1)
{
	return mathlib::VecF64AVX::operator!=(v0, v1);
}

__forceinline __m256d                mathlib::NormF64AVX::operator+(const  __m256d v0, const double s0)
{
	return mathlib::VecF64AVX::operator+(v0, s0);
}

__forceinline __m256d                mathlib::NormF64AVX::operator-(const  __m256d v0, const double s0)
{
	return mathlib::VecF64AVX::operator-(v0, s0);
}

__forceinline __m256d                mathlib::NormF64AVX::operator*(const  __m256d v0, const double s0)
{
	return mathlib::VecF64AVX::operator*(v0, s0);
}

__forceinline __m256d                mathlib::NormF64AVX::operator/(const  __m256d v0, const double s0)
{
	return mathlib::VecF64AVX::operator/(v0, s0);
}

__forceinline __m256d                mathlib::NormF64AVX::operator==(const  __m256d v0, const double s0)
{
	return mathlib::VecF64AVX::operator==(v0, s0);
}

__forceinline __m256d                mathlib::NormF64AVX::operator!=(const   __m256d v0, const double s0)
{
	return mathlib::VecF64AVX::operator!=(v0, s0);
}

__forceinline __m256d                mathlib::NormF64AVX::operator+(const double s0, const  __m256d v0)
{
	return mathlib::VecF64AVX::operator+(s0, v0);
}

__forceinline __m256d                mathlib::NormF64AVX::operator-(const  double s0, const  __m256d v0)
{
	return mathlib::VecF64AVX::operator-(s0, v0);
}

__forceinline __m256d                mathlib::NormF64AVX::operator*(const  double s0, const   __m256d v0)
{
	return mathlib::VecF64AVX::operator*(s0, v0);
}

__forceinline __m256d                mathlib::NormF64AVX::operator/(const  double s0, const   __m256d v0)
{
	return mathlib::VecF64AVX::operator/(s0, v0);
}

__forceinline __m256d                mathlib::NormF64AVX::operator==(const double s0, const   __m256d v0)
{
	return mathlib::VecF64AVX::operator==(s0, v0);
}

__forceinline __m256d                mathlib::NormF64AVX::operator!=(const double s0, const   __m256d v0)
{
	return mathlib::VecF64AVX::operator!=(s0, v0);
}
// Special member functions implementation.

__forceinline mathlib::NormF64AVX &  mathlib::NormF64AVX::dot(const NormF64AVX &lhs, const NormF64AVX &rhs)
{
	this->m_VecF64 = _mm256_castps_pd(_mm256_dp_ps(_mm256_castpd_ps(lhs.m_VecF64), _mm256_castpd_ps(rhs.m_VecF64), 1));
	return *this;
}

__forceinline double mathlib::NormF64AVX::euclidean_distance()
{
	return this->mathlib::VecF64AVX::euclidean_distance();

}

__forceinline double mathlib::NormF64AVX::sqrt_euclidean_distance()
{
	return this->mathlib::VecF64AVX::sqrt_euclidean_distance();
}

__forceinline mathlib::NormF64AVX & mathlib::NormF64AVX::Normalize()
{
	this->m_VecF64 = _mm256_div_pd(this->m_VecF64, _mm256_set1_pd(this->sqrt_euclidean_distance()));
	return *this;
}

__forceinline mathlib::NormF64AVX & mathlib::NormF64AVX::abs_dot(const NormF64AVX &lhs, const NormF64AVX &rhs)
{
	__m256d temp = _mm256_castps_pd(_mm256_dp_ps(_mm256_castpd_ps(lhs.m_VecF64), _mm256_castpd_ps(rhs.m_VecF64), 1));
	this->m_VecF64 = _mm256_set_pd(0.0L, std::fabs(temp.m256d_f64[0]), std::fabs(temp.m256d_f64[1]), std::fabs(temp.m256d_f64[2]));
	return *this;

}

__forceinline  __m256d  mathlib::NormF64AVX::abs_dot(const __m256d v0, const __m256d v1)
{
	return mathlib::VecF64AVX::abs_dot(v0, v1);
}

__forceinline  double   mathlib::NormF64AVX::triple_scalar_prod(const __m256d v0, const __m256d v1, const __m256d v2)
{
	return mathlib::VecF64AVX::triple_scalar_prod(v0, v1, v2);
}


__forceinline  __m256d  mathlib::NormF64AVX::cross(const __m256d v0, const __m256d v1)
{
	return mathlib::VecF64AVX::cross(v0, v1);
}

template<typename... Functions> __forceinline mathlib::NormF64AVX & mathlib::NormF64AVX::apply(Functions... f)
{
	// Proper way of calling variadic templated Function argument.
	this->m_VecF64 = _mm256_set_pd(std::numeric_limits<double>::quiet_NaN(),f()...);
	return *this;
}

template<typename... Functions> __forceinline void mathlib::NormF64AVX::apply2(std::vector<mathlib::NormF64AVX> &v, Functions ...f )
{
	if (!v.empty())
	{
		std::vector<mathlib::NormF64AVX>::iterator it;
		for (it = v.begin(); it != v.end(); ++it)
		{
			it.operator->()->m_VecF64 = _mm256_set_pd(std::numeric_limits<double>::quiet_NaN(),f()...);
		}

	}
	else
		throw std::runtime_error(std::string("empty vector\n"));
}

// Non-member operators and functions implementation.

template<typename... Functions> __forceinline std::vector<mathlib::NormF64AVX>  apply2(Functions... f, std::vector < mathlib::NormF64AVX> v)
{
	if (!v.empty())
	{
		std::vector<mathlib::NormF64AVX>::iterator it;
		for (it = v.begin(); it != v.end(); ++it)
		{
			it->apply(f()..., f()..., f()...);
		}
		return std::vector<mathlib::NormF64AVX>(v);
	}
	else throw std::runtime_error(std::string("empty vector\n"));
}

__forceinline mathlib::NormF64AVX   mathlib::operator+(const NormF64AVX &lhs, const NormF64AVX &rhs)
{
	__m256d result;
	return NormF64AVX(result = _mm256_add_pd(lhs.get_m_VecF64(), rhs.get_m_VecF64()));
}

__forceinline mathlib::NormF64AVX   mathlib::operator-(const NormF64AVX &lhs, const NormF64AVX &rhs)
{
	__m256d result;
	return NormF64AVX(result = _mm256_sub_pd(lhs.get_m_VecF64(), rhs.get_m_VecF64()));
}

__forceinline mathlib::NormF64AVX   mathlib::operator*(const NormF64AVX &lhs, const NormF64AVX &rhs)
{
	__m256d result;
	return NormF64AVX(result = _mm256_mul_pd(lhs.get_m_VecF64(), rhs.get_m_VecF64()));
}

__forceinline mathlib::NormF64AVX   mathlib::operator/(const NormF64AVX &lhs, const NormF64AVX &rhs)
{
	__m256d result;
	return NormF64AVX(result = _mm256_div_pd(lhs.get_m_VecF64(), rhs.get_m_VecF64()));
}

__forceinline mathlib::NormF64AVX   mathlib::operator==(const NormF64AVX &lhs, const NormF64AVX &rhs)
{
	__m256d result;
	return NormF64AVX(result = _mm256_cmp_pd(lhs.get_m_VecF64(), rhs.get_m_VecF64(), 0));
}

__forceinline mathlib::NormF64AVX   mathlib::operator!=(const NormF64AVX &lhs, const NormF64AVX &rhs)
{
	__m256d result;
	return NormF64AVX(result = _mm256_cmp_pd(lhs.get_m_VecF64(), rhs.get_m_VecF64(), 4));
}

__forceinline mathlib::NormF64AVX   mathlib::operator+(const NormF64AVX &lhs, const double s)
{
	__m256d result;
	return NormF64AVX(result = _mm256_add_pd(lhs.get_m_VecF64(), _mm256_set1_pd(s)));
}

__forceinline mathlib::NormF64AVX   mathlib::operator-(const NormF64AVX &lhs, const double s)
{
	__m256d result;
	return NormF64AVX(result = _mm256_sub_pd(lhs.get_m_VecF64(), _mm256_set1_pd(s)));
}

__forceinline mathlib::NormF64AVX   mathlib::operator*(const NormF64AVX &lhs, const double s)
{
	__m256d result;
	return NormF64AVX(result = _mm256_mul_pd(lhs.get_m_VecF64(), _mm256_set1_pd(s)));
}

__forceinline mathlib::NormF64AVX   mathlib::operator/(const NormF64AVX &lhs, const double s)
{
	__m256d result;
	return NormF64AVX(result = _mm256_div_pd(lhs.get_m_VecF64(), _mm256_set1_pd(s)));
}

__forceinline mathlib::NormF64AVX   mathlib::operator==(const NormF64AVX &lhs, const double s)
{
	__m256d result;
	return NormF64AVX(result = _mm256_cmp_pd(lhs.get_m_VecF64(), _mm256_set1_pd(s), 0));
}

__forceinline mathlib::NormF64AVX   mathlib::operator!=(const NormF64AVX &lhs, const double s)
{
	__m256d result;
	return NormF64AVX(result = _mm256_cmp_pd(lhs.get_m_VecF64(), _mm256_set1_pd(s), 4));
}

__forceinline mathlib::NormF64AVX   mathlib::operator+(const double s, const NormF64AVX &lhs)
{
	__m256d result;
	return NormF64AVX(result = _mm256_add_pd(_mm256_set1_pd(s), lhs.get_m_VecF64()));
}

__forceinline mathlib::NormF64AVX   mathlib::operator-(const double s, const NormF64AVX &lhs)
{
	__m256d result;
	return NormF64AVX(result = _mm256_sub_pd(_mm256_set1_pd(s), lhs.get_m_VecF64()));
}

__forceinline mathlib::NormF64AVX   mathlib::operator*(const double s, const NormF64AVX &lhs)
{
	__m256d result;
	return NormF64AVX(result = _mm256_mul_pd(_mm256_set1_pd(s), lhs.get_m_VecF64()));
}

__forceinline mathlib::NormF64AVX   mathlib::operator/(const double s, const NormF64AVX &lhs)
{
	__m256d result;
	return NormF64AVX(result = _mm256_div_pd(_mm256_set1_pd(s), lhs.get_m_VecF64()));
}

__forceinline mathlib::NormF64AVX   mathlib::operator==(const double s, const NormF64AVX &lhs)
{
	__m256d result;
	return NormF64AVX(result = _mm256_cmp_pd(_mm256_set1_pd(s), lhs.get_m_VecF64(), 0));
}

__forceinline mathlib::NormF64AVX   mathlib::operator!=(const double s, const NormF64AVX &lhs)
{
	__m256d result;
	return NormF64AVX(result = _mm256_cmp_pd(_mm256_set1_pd(s), lhs.get_m_VecF64(), 4));
}