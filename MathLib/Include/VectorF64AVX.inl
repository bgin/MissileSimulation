
// Vector with all elements set to 0.0
__forceinline mathlib::VecF64AVX::VecF64AVX()
{
	this->m_VecF64 = _mm256_setzero_pd();
}

// VectorF64AVX set to user passed static double array.User must align array on 8-byte boundaries.
__forceinline mathlib::VecF64AVX::VecF64AVX(const double vector[4])
{
	
	this->m_VecF64 = _mm256_loadu_pd(vector);
}

// VectorF64AVX set to user passed 4 scalars.
__forceinline mathlib::VecF64AVX::VecF64AVX(const double s0, const double s1, const double s2, const double s3)
{
	this->m_VecF64 = _mm256_set_pd(s0, s1, s2, s3);
}

/*__forceinline mathlib::VecF64AVX::VecF64AVX(const double(&vector)[4])
{
	this->m_VecF64 = _mm256_loadu_pd(vector);
}*/

__forceinline mathlib::VecF64AVX::VecF64AVX(const double s0)
{
	this->m_VecF64 = _mm256_set1_pd(s0);
	
}

__forceinline mathlib::VecF64AVX::VecF64AVX(const VecF64AVX& rhs)
{
	this->m_VecF64 = rhs.m_VecF64;
}

__forceinline mathlib::VecF64AVX::VecF64AVX(const __m256d rhs)
{
	this->m_VecF64 = rhs;
}

__forceinline mathlib::VecF64AVX::VecF64AVX(const __m256i rhs)
{
	this->m_VecF64 = _mm256_castsi256_pd(rhs);
}

__forceinline mathlib::VecF64AVX::VecF64AVX(const __m128d v0, const __m128d v1)
{
	 //mathlib::Coalesce_Vector(this->m_VecF64, v0, v1);
	this->m_VecF64 = _mm256_insertf128_pd(this->m_VecF64, v0, 0);
	this->m_VecF64 = _mm256_insertf128_pd(this->m_VecF64, v1, 1);// proper usage of _mm256_insertf128_pd() intrinsic.
}

const __m256d __forceinline mathlib::VecF64AVX::get_m_VecF64() const
{
	return this->m_VecF64;
}

__m256d      __forceinline mathlib::VecF64AVX::get_m_VecF64()
{
	return this->m_VecF64;
}

// Get low 128-bit part of 256-bit vector
__m128d      __forceinline mathlib::VecF64AVX::get_low_part() const
{
	return mathlib::Extract_Vector(this->m_VecF64, 0);
}

// Get high 128-bit part of 256-bit vector.
__m128d     __forceinline  mathlib::VecF64AVX::get_hi_part() const
{
	return mathlib::Extract_Vector(this->m_VecF64, 1);
}

// Load from double array pointed by ptr. Address should be aligned on 64-byte bondary.
__forceinline  mathlib::VecF64AVX &  mathlib::VecF64AVX::load_a(const double * ptr)
{
	this->m_VecF64 = _mm256_load_pd(ptr);
	return *this;
}

// Load from double array pointed by ptr. Address can be unaligned.
__forceinline  mathlib::VecF64AVX &  mathlib::VecF64AVX::load_u(const double * ptr)
{
	this->m_VecF64 = _mm256_loadu_pd(ptr);
	return *this;
}

__forceinline  void  mathlib::VecF64AVX::store_a(double * ptr) const
{
	_mm256_store_pd(ptr, this->m_VecF64);
}

__forceinline  void  mathlib::VecF64AVX::store_u(double * ptr) const
{
	_mm256_storeu_pd(ptr, this->m_VecF64);
}

__forceinline  void  mathlib::VecF64AVX::stream_store(double * ptr) const
{
	_mm256_stream_pd(&ptr[0], this->m_VecF64);
}

__forceinline  double mathlib::VecF64AVX::extract_scalar(unsigned int index) const
{
	
	__declspec(align(64))double v[4] = { 0.0 }; // Must be aligned on 64-byte boundaries. Divisable by 64.
	store_a(v);
	return v[index & 3];
}
// Member and friend operators:

__forceinline  std::ostream&  mathlib::operator<<(std::ostream& os, const VecF64AVX & rhs)
{
	os << "s0=" << rhs.m_VecF64.m256d_f64[0] << "s1=" << rhs.m_VecF64.m256d_f64[1] <<
		"s2=" << rhs.m_VecF64.m256d_f64[2] << "s3=" << rhs.m_VecF64.m256d_f64[3] << std::endl;
	return os;
}


__forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::operator=(const VecF64AVX& rhs)
{
	if (this == &rhs)  return *this;


	this->m_VecF64 = rhs.m_VecF64;
	return *this;

}
	
		


__forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::operator=(const __m256d & rhs)
{
	
	this->m_VecF64 = rhs;
	return *this;
}

__forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::operator+=(const VecF64AVX& rhs)
{
	this->m_VecF64 = _mm256_add_pd(this->m_VecF64, rhs.m_VecF64);
	return *this;
}

__forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::operator-=(const VecF64AVX& rhs)
{
	this->m_VecF64 = _mm256_sub_pd(this->m_VecF64, rhs.m_VecF64);
	return *this;
}

__forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::operator*=(const VecF64AVX& rhs)
{
	this->m_VecF64 = _mm256_mul_pd(this->m_VecF64, rhs.m_VecF64);
	return *this;

}

__forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::operator/=(const VecF64AVX& rhs)
{
	this->m_VecF64 = _mm256_div_pd(this->m_VecF64, rhs.m_VecF64);
	return *this;
}

__forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::operator|=(const VecF64AVX& rhs)
{
	this->m_VecF64 = _mm256_or_pd(this->m_VecF64, rhs.m_VecF64);
	return *this;
}

__forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::operator&=(const VecF64AVX& rhs)
{
	this->m_VecF64 = _mm256_and_pd(this->m_VecF64, rhs.m_VecF64);
	return *this;
}

__forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::operator^=(const VecF64AVX& rhs)
{
	this->m_VecF64 = _mm256_xor_pd(this->m_VecF64, rhs.m_VecF64);
	return *this;
}

__forceinline  mathlib::VecF64AVX   mathlib::VecF64AVX::operator==(const VecF64AVX& rhs)
{
	mathlib::VecF64AVX res = _mm256_cmp_pd(this->m_VecF64, rhs.m_VecF64, 0);
	return res;
}

__forceinline  mathlib::VecF64AVX   mathlib::VecF64AVX::operator!=(const VecF64AVX& rhs)
{
	mathlib::VecF64AVX res = _mm256_cmp_pd(this->m_VecF64, rhs.m_VecF64, 4);
	return res;
}

__forceinline  mathlib::VecF64AVX   mathlib::VecF64AVX::operator==(const double scalar)
{
	mathlib::VecF64AVX res = _mm256_cmp_pd(this->m_VecF64, _mm256_set1_pd(scalar), 0);
	return res;
}

__forceinline  mathlib::VecF64AVX   mathlib::VecF64AVX::operator!=(const double scalar)
{
	mathlib::VecF64AVX res = _mm256_cmp_pd(this->m_VecF64, _mm256_set1_pd(scalar), 4);
	return res;
}

__forceinline  double  mathlib::VecF64AVX::operator[](unsigned int index) const
{
	return extract_scalar(index);
}

__forceinline mathlib::VecF64AVX::operator __m256d () const
{
	return this->m_VecF64;
}

__forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::operator+=(const double scalar)
{
	this->m_VecF64 = _mm256_add_pd(this->m_VecF64, _mm256_set1_pd(scalar));
	return *this;
}

__forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::operator-=(const double scalar)
{
	this->m_VecF64 = _mm256_sub_pd(this->m_VecF64, _mm256_set1_pd(scalar));
	return *this;
}

__forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::operator*=(const double scalar)
{
	this->m_VecF64 = _mm256_mul_pd(this->m_VecF64, _mm256_set1_pd(scalar));
	return *this;
}

__forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::operator/=(const double scalar)
{
	this->m_VecF64 = _mm256_div_pd(this->m_VecF64, _mm256_set1_pd(scalar));
	return *this;
}

// Special Member functions
__forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::dot(const VecF64AVX &lhs, const VecF64AVX &rhs)
{
	this->m_VecF64 = _mm256_castps_pd( _mm256_dp_ps(_mm256_castpd_ps(lhs.m_VecF64), _mm256_castpd_ps(rhs.m_VecF64), 0xFF));
	return *this;
}

__forceinline   __m256d   mathlib::VecF64AVX::dot(const __m256d v0, const __m256d v1)
{

	
	return  _mm256_castps_pd(_mm256_dp_ps(_mm256_castpd_ps(v0), _mm256_castpd_ps(v1), 0xFF));
	
}

__forceinline   __m256d   mathlib::VecF64AVX::abs_dot(const __m256d v0, const __m256d v1)
{
	__m256d result = VecF64AVX::dot(v0, v1);
	return _mm256_set_pd(0.0L, std::fabs(result.m256d_f64[0]), std::fabs(result.m256d_f64[1]), std::fabs(result.m256d_f64[2]));
}

__forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::cross(const VecF64AVX &lhs, const VecF64AVX &rhs)
{
	// u x v = u2*v3 - u3*v2
	double s0 = (lhs.extract_scalar(1) * rhs.extract_scalar(2)) - (lhs.extract_scalar(2) * rhs.extract_scalar(1));
	double s1 = (lhs.extract_scalar(2) * rhs.extract_scalar(0)) - (lhs.extract_scalar(0) * rhs.extract_scalar(2));
	double s2 = (lhs.extract_scalar(0) * rhs.extract_scalar(1)) - (lhs.extract_scalar(1) * rhs.extract_scalar(0));
	this->m_VecF64 = _mm256_set_pd(s0, s1, s2, 0.0L);
	return *this;
}



__forceinline   __m256d   mathlib::VecF64AVX::cross(const __m256d v0, const __m256d v1)
{
	__declspec(align(64)) double a0[4]; __declspec(align(64)) double a1[4];
	_mm256_store_pd(a0, v0);
	_mm256_store_pd(a1, v1);
	double s0 = (a0[1] * a1[2]) - (a0[2] * a1[1]);
	double s1 = (a0[2] * a1[0]) - (a0[0] * a1[2]);
	double s2 = (a0[0] * a1[1]) - (a0[1] * a1[0]);
	return _mm256_set_pd(0.0L,s0, s1, s2);
}

__forceinline  double   mathlib::VecF64AVX::triple_scalar_prod(const __m256d v0, const __m256d v1, const __m256d v2)
{
	__declspec(align(64)) double a0[4]; __declspec(align(64)) double a1[4]; __declspec(align(64)) double a2[4];
	_mm256_store_pd(a0, v0);
	_mm256_store_pd(a1, v1);
	_mm256_store_pd(a2, v2);
	double s0 = a0[0] * ((a1[1] * a2[2]) - (a1[2] * a2[1]));
	double s1 = a0[1] * ((a1[2] * a2[0]) - (a1[0] * a2[2]));
	double s2 = a0[2] * ((a1[0] * a2[1]) - (a1[1] * a2[0]));
	return s0 + s1 + s2;
}

__forceinline   mathlib::VecF64AVX &  mathlib::VecF64AVX::direction_cosine()
{
	double a = this->extract_scalar(0); double b = this->extract_scalar(1); double c = this->extract_scalar(2);
	double s = this->sqrt_euclidean_distance();
	double l = a / s; double m = b / s; double n = c / s;
	this->m_VecF64 = _mm256_set_pd(l, m, n, 0.0L);
	return *this;

}

__forceinline double  mathlib::VecF64AVX::euclidean_distance()
{
	 //inefficient per single element access.
	this->m_VecF64 = _mm256_mul_pd(this->m_VecF64, this->m_VecF64);
	return this->m_VecF64.m256d_f64[0] + this->m_VecF64.m256d_f64[1] + this->m_VecF64.m256d_f64[2];
	
	
}

__forceinline double  mathlib::VecF64AVX::euclidean_distance2()
{
	this->m_VecF64 = _mm256_mul_pd(this->m_VecF64, this->m_VecF64);
	return this->extract_scalar(0) + this->extract_scalar(1) + this->extract_scalar(2);
}

__forceinline double mathlib::VecF64AVX::sqrt_euclidean_distance()
{
	return std::sqrt(mathlib::VecF64AVX::euclidean_distance());
}

__forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::Normalize()
{
	this->m_VecF64 = _mm256_div_pd(this->m_VecF64, _mm256_set1_pd(this->euclidean_distance()));
	return *this;
}

template<typename Function>  __forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::apply(Function f, const double s)
{
	this->m_VecF64 = _mm256_set_pd(f(s), f(s), f(s), std::numeric_limits<double>::quiet_NaN());
	return *this;
}

template<typename Function>  __forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::apply(Function f, const double s0, const double s1,
	const double s2, const double s3)
{
	this->m_VecF64 = _mm256_set_pd(f(s0), f(s1), f(s2), f(s3));
	return *this;
}

template<typename F1, typename F2, typename F3> __forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::apply(F1 f1, F2 f2, F3 f3,
	const double s0, const double s1, const double s2)
{
	this->m_VecF64 = _mm256_set_pd(f1(s0), f2(s1), f3(s2), std::numeric_limits<double>::quiet_NaN());
	return *this;
}

template<typename... Functions> __forceinline mathlib::VecF64AVX & mathlib::VecF64AVX::apply(Functions... functions)
{
	this->m_VecF64 = _mm256_set_pd(functions()...,std::numeric_limits<double>::quiet_NaN());
	return *this;
}

template<typename... Functions> __forceinline void   mathlib::VecF64AVX::apply(std::vector<mathlib::VecF64AVX> &v, Functions... f)
{
	if (!v.empty())
	{
		std::vector<mathlib::VecF64AVX>::iterator it;
		for (it = v.begin(); it != v.end(); ++it)
		{
			it.operator->()->m_VecF64 = _mm256_set_pd(std::numeric_limits<double>::quiet_NaN(), f()...);
		}
	}
	else
		throw std::runtime_error(std::string("empty vector!!\n"));
}
// Namespace functions

// Select vector from a and b by means of predicate vector.
__m256d  __forceinline  mathlib::Select_Vector(const __m256d a, const __m256d b, const __m256d predicate)
{
	return _mm256_blendv_pd(a, b, predicate);
}

// Select vector from a and b by means of predicate vector.
__m256  __forceinline   mathlib::Select_Vector(const __m256 a, const __m256 b, const  __m256 predicate)
{
	return _mm256_blendv_ps(a, b, predicate);
}

// Join 128-bit vector to existing 128-bit vector at offset specified by imm.
__m256d __forceinline   mathlib::Coalesce_Vector( __m256d a, const __m128d b, const int imm)
{
#if defined _DEBUG
	_ASSERTE(imm >= 0 && imm <= 1);
#else
	if(imm < 0 || imm > 1)
	{
		throw std::runtime_error(std::string("FATAL ERROR in mathlib::Coalesce_Vector - Expected either 1 or 0 \n"));
	}
#endif
	return _mm256_insertf128_pd(a, b, 1);
}

__m256  __forceinline  mathlib::Coalesce_Vector(__m256 a, const __m128 b, const int imm)
{
#if defined _DEBUG
	_ASSERTE(imm >= 0 && imm <= 1);
#else
	if (imm < 0 || imm > 1)
	{
		throw std::runtime_error(std::string("FATAL ERROR in mathlib::Coalesce_Vector - Expected either 1 or 0 \n"));
	}
#endif
	return _mm256_insertf128_ps(a, b, imm);
}

void  __forceinline mathlib::Coalesce_Vector(__m256d dest, const __m128d a,const  __m128d b)
{
	
	_mm256_insertf128_pd(dest, a, 0);
	_mm256_insertf128_pd(dest, b, 1);
}


__m128d  __forceinline mathlib::Extract_Vector(__m256d a, const int imm)
{
#if defined _DEBUG
	_ASSERTE(imm >= 0 && imm <= 1);
#else
	if (imm < 0 || imm > 1)
	{
		throw std::runtime_error(std::string("FATAL ERROR in mathlib::Coalesce_Vector - Expected either 1 or 0 \n"));
	}
#endif
	return _mm256_extractf128_pd(a, imm);
}


__m128   __forceinline mathlib::Extract_Vector(__m256 a, const int imm)
{
#if defined _DEBUG
	_ASSERTE(imm >= 0 && imm <= 1);
#else
	if (imm < 0 || imm > 1)
	{
		throw std::runtime_error(std::string("FATAL ERROR in mathlib::Coalesce_Vector - Expected either 1 or 0 \n"));
	}
#endif
	
	return _mm256_extractf128_ps(a, imm);
}

__m256d  __forceinline  mathlib::Normalize(const __m256d v0)
{
	__m256d temp = _mm256_mul_pd(v0, v0);
	double s0 = temp.m256d_f64[0] + temp.m256d_f64[1] + temp.m256d_f64[2];
	return _mm256_div_pd(v0, _mm256_set1_pd(s0));
}

mathlib::VecF64AVX __forceinline mathlib::operator+( VecF64AVX &lhs, const VecF64AVX &rhs)
{
	VecF64AVX c;
	c.operator=(lhs.operator+=(rhs));
	return c;
}

mathlib::VecF64AVX __forceinline mathlib::operator-( VecF64AVX &lhs, const VecF64AVX &rhs)
{
	VecF64AVX c;
	c.operator=(lhs.operator-=(rhs));
	return c;
}

mathlib::VecF64AVX __forceinline mathlib::operator*(VecF64AVX &lhs, const VecF64AVX &rhs)
{
	VecF64AVX c;
	c.operator=(lhs.operator*=(rhs));
	return c;
}

mathlib::VecF64AVX __forceinline mathlib::operator/(const VecF64AVX &lhs, const VecF64AVX &rhs)
{
	__m256d result;
	return VecF64AVX(result = _mm256_div_pd(lhs.get_m_VecF64(), rhs.get_m_VecF64()));
}

mathlib::VecF64AVX __forceinline mathlib::operator==(const VecF64AVX &lhs, const VecF64AVX &rhs)
{
	__m256d result;
	return VecF64AVX(result = _mm256_cmp_pd(lhs.get_m_VecF64(), rhs.get_m_VecF64(), 0));
}

mathlib::VecF64AVX __forceinline mathlib::operator!=(const VecF64AVX &lhs, const VecF64AVX &rhs)
{
	__m256d result;
	return VecF64AVX(result = _mm256_cmp_pd(lhs.get_m_VecF64(), rhs.get_m_VecF64(), 4));
}

mathlib::VecF64AVX __forceinline mathlib::operator+(const double s0, const VecF64AVX &rhs)
{
	__m256d result;
	return VecF64AVX(result = _mm256_add_pd(_mm256_set1_pd(s0), rhs.get_m_VecF64()));
}

mathlib::VecF64AVX __forceinline mathlib::operator-(const double s0, const  VecF64AVX &rhs)
{
	__m256d result;
	return VecF64AVX(result = _mm256_sub_pd(_mm256_set1_pd(s0), rhs.get_m_VecF64()));
}

mathlib::VecF64AVX __forceinline mathlib::operator*(const double s0, const VecF64AVX &rhs)
{
	__m256d result;
	return VecF64AVX(result = _mm256_mul_pd(_mm256_set1_pd(s0), rhs.get_m_VecF64()));
}

mathlib::VecF64AVX __forceinline mathlib::operator/(const double s0, const VecF64AVX &rhs)
{
	__m256d result;
	return VecF64AVX(result = _mm256_div_pd(_mm256_set1_pd(s0), rhs.get_m_VecF64()));
}

mathlib::VecF64AVX __forceinline mathlib::operator==(const double s0, const VecF64AVX &rhs)
{
	__m256d result;
	return VecF64AVX(result = _mm256_cmp_pd(_mm256_set1_pd(s0), rhs.get_m_VecF64(), 0));
}

mathlib::VecF64AVX __forceinline mathlib::operator!=(const double s0, const VecF64AVX &rhs)
{
	__m256d result;
	return VecF64AVX(result = _mm256_cmp_pd(_mm256_set1_pd(s0), rhs.get_m_VecF64(), 4));
}



__m256d  __forceinline   mathlib::VecF64AVX::operator+(const __m256d v0, const __m256d v1)
{
	return _mm256_add_pd(v0, v1);
}

__m256d  __forceinline   mathlib::VecF64AVX::operator-(const __m256d v0, const __m256d v1)
{
	return _mm256_sub_pd(v0, v1);
}

__m256d  __forceinline   mathlib::VecF64AVX::operator*(const __m256d v0, const __m256d v1)
{
	return _mm256_mul_pd(v0, v1);
}

__m256d  __forceinline   mathlib::VecF64AVX::operator/(const __m256d v0, const __m256d v1)
{
	return _mm256_div_pd(v0, v1);
}

__m256d  __forceinline    mathlib::VecF64AVX::operator==(const __m256d v0, const __m256d v1)
{
	return _mm256_cmp_pd(v0, v1, 0);
}

__m256d  __forceinline    mathlib::VecF64AVX::operator!=(const __m256d v0, const __m256d v1)
{
	return _mm256_cmp_pd(v0, v1, 4);
}

__m256d  __forceinline    mathlib::VecF64AVX::operator+(const  __m256d v0, const double s0)
{
	return _mm256_add_pd(v0, _mm256_set1_pd(s0));
}

__m256d  __forceinline    mathlib::VecF64AVX::operator-(const  __m256d v0, const double s0)
{
	return _mm256_sub_pd(v0, _mm256_set1_pd(s0));
}

__m256d  __forceinline    mathlib::VecF64AVX::operator*(const   __m256d v0, const double s0)
{
	return _mm256_mul_pd(v0, _mm256_set1_pd(s0));
}

__m256d  __forceinline    mathlib::VecF64AVX::operator/(const   __m256d v0, const double s0)
{
	return _mm256_div_pd(v0, _mm256_set1_pd(s0));
}

__m256d  __forceinline    mathlib::VecF64AVX::operator==(const   __m256d v0, const double s0)
{
	return _mm256_cmp_pd(v0, _mm256_set1_pd(s0), 0);
}

__m256d  __forceinline    mathlib::VecF64AVX::operator!=(const   __m256d v0, const double s0)
{
	return _mm256_cmp_pd(v0, _mm256_set1_pd(s0), 4);
}

__m256d  __forceinline    mathlib::VecF64AVX::operator+(const double s0, const  __m256d v0)
{
	return _mm256_add_pd(_mm256_set1_pd(s0), v0);
}

__m256d  __forceinline    mathlib::VecF64AVX::operator-(const double s0, const   __m256d v0)
{
	return _mm256_sub_pd(_mm256_set1_pd(s0), v0);
} 

__m256d  __forceinline    mathlib::VecF64AVX::operator*(const double s0, const   __m256d v0)
{
	return _mm256_mul_pd(_mm256_set1_pd(s0), v0);
}

__m256d  __forceinline    mathlib::VecF64AVX::operator/(const double s0, const   __m256d v0)
{
	return _mm256_div_pd(_mm256_set1_pd(s0), v0);
}

__m256d  __forceinline    mathlib::VecF64AVX::operator==(const double s0, const  __m256d v0)
{
	return _mm256_cmp_pd(_mm256_set1_pd(s0), v0, 0);
}

__m256d  __forceinline    mathlib::VecF64AVX::operator!=(const double s0, const   __m256d v0)
{
	return _mm256_cmp_pd(_mm256_set1_pd(s0), v0, 4);
}


