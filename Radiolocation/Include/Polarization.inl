/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
file Polarization.h
class JonesVector
@aulthor: Bernard Gingold
@version:  1.0  19/10/2015

*/


// JonesVector inline function implementation
__forceinline  std::complex<double>   radiolocation::JonesVector::h()
{
	return this->m_h;
}

__forceinline  const  std::complex<double>  radiolocation::JonesVector::h() const
{
	return this->m_h;
}

__forceinline   std::complex<double>   radiolocation::JonesVector::v()
{
	return this->m_v;
}

__forceinline  const  std::complex<double>  radiolocation::JonesVector::v() const
{
	return this->m_v;
}


//  JonesMatrix inline functions implementation.
__forceinline  std::complex<double>         radiolocation::JonesMatrix::s0()
{
	return this->m_matrix[0];
}

__forceinline  const   std::complex<double>   radiolocation::JonesMatrix::s0() const
{
	return this->m_matrix[0];
}

__forceinline  std::complex<double>         radiolocation::JonesMatrix::s1()
{
	return this->m_matrix[1];
}

__forceinline  const  std::complex<double>  radiolocation::JonesMatrix::s1() const
{
	return this->m_matrix[1];
}

__forceinline  std::complex<double>         radiolocation::JonesMatrix::s2()
{
	return this->m_matrix[2];
}

__forceinline  const  std::complex<double>  radiolocation::JonesMatrix::s2() const
{
	return this->m_matrix[2];
}

__forceinline  std::complex<double>          radiolocation::JonesMatrix::s3()
{
	return this->m_matrix[3];
}

__forceinline  const  std::complex<double>   radiolocation::JonesMatrix::s3() const
{
	return this->m_matrix[3];
}

__forceinline  std::complex<double>          *radiolocation::JonesMatrix::matrix()
{
	return this->m_matrix;
}

__forceinline  const  std::complex<double>    *radiolocation::JonesMatrix::matrix() const
{
	return this->m_matrix;
}

__forceinline   double    radiolocation::StokesVector::s0() const
{
	return this->m_stokes[0];
}

__forceinline   double    radiolocation::StokesVector::s1() const
{
	return this->m_stokes[1];
}

__forceinline   double    radiolocation::StokesVector::s2() const
{
	return this->m_stokes[2];
}

__forceinline   double    radiolocation::StokesVector::s3() const
{
	return this->m_stokes[3];
}

__forceinline const  double   *radiolocation::StokesVector::stokes() const
{
	return this->m_stokes;
}

__forceinline   double       radiolocation::StokesVector::normalized_s1() const
{
	return s1() / s0();
}

__forceinline   double       radiolocation::StokesVector::normalized_s2() const
{
	return s2() / s0();
}

__forceinline   double       radiolocation::StokesVector::normalized_s3() const
{
	return s3() / s0();
}

__forceinline   double      radiolocation::StokesVector::dot(_In_ StokesVector const& lhs) const
{
	return (this->m_stokes[0] * lhs.m_stokes[0]) + (this->m_stokes[1] * lhs.m_stokes[1]) + (this->m_stokes[2] * lhs.m_stokes[2]) +
		(this->m_stokes[3] * lhs.m_stokes[3]);
}