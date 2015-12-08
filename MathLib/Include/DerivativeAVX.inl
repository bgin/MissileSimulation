
__forceinline mathlib::DyDxAVX::DyDxAVX(const __m256d deriv, const __m256d err) : derivative(deriv), error(err)
{

}

__forceinline  const __m256d  mathlib::DyDxAVX::get_derivative() const
{
	return this->derivative;
}

__forceinline        __m256d  mathlib::DyDxAVX::get_derivative()
{
	return this->derivative;
}

__forceinline  const __m256d  mathlib::DyDxAVX::get_error() const
{
	return this->error;
}

__forceinline        __m256d  mathlib::DyDxAVX::get_error()
{
	return this->error;
}

template<typename Functions> __forceinline  mathlib::DyDxAVX  mathlib::DyDxAVX::differentiate(Functions f, __m256d x, __m256d h )
{
	__m256d result = _mm256_cmp_pd(h, _mm256_setzero_pd(), 0);
	for (auto i = 0; i != 4; ++i) 
	if (result.m256d_f64[i]) throw std::runtime_error("__m256d h cannot be zero\n");

	__m256d deriv = _mm256_div_pd(_mm256_sub_pd(f(_mm256_add_pd(x, h)), f(_mm256_sub_pd(x, h))),_mm256_mul_pd(_mm256_set1_pd(2.0L),h));
	__m256d err = _mm256_mul_pd(_mm256_set1_pd(std::numeric_limits<double>::epsilon()), _mm256_div_pd(f(x), h));
	
	return DyDxAVX(deriv, err);
}