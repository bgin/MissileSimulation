#ifndef _POLARIZATION_H_
#define _POLARIZATION_H_

/* Copyright (c) 2015, Bernard Gingold. License: MIT License (http://www.opensource.org/licenses/mit-license.php)
 file Polarization.h
 class JonesVector
 class JonesMatrix
@aulthor: Bernard Gingold
@version:  1.0  19/10/2015

*/
#include "RadLibDefs.h"



namespace radiolocation
{


	class JonesVector
	{

	public:

		/*
		@Brief: Explicitly default Ctor - null vector.
		*/
		JonesVector() = default;

		JonesVector(_In_  std::complex<double> const&, _In_  std::complex<double> const&);

		JonesVector(_In_  struct JonesVectorParams const&);

		JonesVector(_In_ JonesVector const&);

		JonesVector(_In_ JonesVector &&);

		~JonesVector() = default;

		JonesVector&     operator=(_In_ JonesVector const&);

		JonesVector&     operator=(_In_ JonesVector &&);

		friend    std::ostream&    operator<<(_In_ std::ostream&, _In_ JonesVector const&);

		JonesVector&     operator*=(_In_ JonesVector const&);

		JonesVector&     operator*=(_In_ std::complex<double> const&);

		JonesVector&     operator/=(_In_ JonesVector const&);

		JonesVector&     operator/=(_In_ std::complex<double> const&);

		JonesVector&     operator-=(_In_ JonesVector const&);

		JonesVector&     operator-=(_In_ std::complex<double> const&);

		JonesVector&     operator+=(_In_ JonesVector const&);

		JonesVector&     operator+=(_In_ std::complex<double> const&);

		JonesVector      operator-() const;

		__m256d          operator==(_In_ JonesVector const&) const;

		__m256d          operator!=(_In_ JonesVector const&) const;

		std::complex<double>  operator*(_In_ JonesVector const&);

		friend	JonesVector   operator*(_In_ JonesVector const&, _In_ JonesVector const&);

		friend  JonesVector   operator*(_In_ JonesVector const&, _In_ std::complex<double> const&);

		friend  JonesVector   operator/(_In_ JonesVector const&, _In_ JonesVector const&);

		friend  JonesVector   operator/(_In_ JonesVector const&, _In_ std::complex<double> const&);

		friend  JonesVector   operator-(_In_ JonesVector const&, _In_ JonesVector const&);

		friend  JonesVector   operator-(_In_ JonesVector const&, _In_ std::complex<double> const&);

		friend  JonesVector   operator+(_In_ JonesVector const&, _In_ JonesVector const&);

		friend  JonesVector   operator+(_In_ JonesVector const&, _In_ std::complex<double> const&);
		

		__forceinline 	std::complex<double>   h();

		__forceinline   std::complex<double>   v();

		__forceinline  const  std::complex<double>  h() const;

		__forceinline  const  std::complex<double>  v() const;

		double     field_intensity() const;

		double     field_atan() const;

		double     field_phase_diff() const;

		double     degree_polarization() const;

	private:

		/*
		@Brief: horizontal component of electrical field
		*/
		std::complex<double> m_h;

		/*
		@Brief: vertical component of electrical field.
		*/
		std::complex<double> m_v;

	};

	class JonesMatrix
	{


	public:

		JonesMatrix() = default;

		JonesMatrix(_In_ std::complex<double> const&, _In_ std::complex<double> const&, _In_ std::complex<double> const&,
			_In_ std::complex<double> const&);

		JonesMatrix(_In_ struct JonesMatrixParams const&);

		JonesMatrix(_In_ JonesMatrix const&);

		JonesMatrix(_In_ JonesMatrix &&);

		~JonesMatrix() = default;

		__forceinline   std::complex<double>    s0();

		__forceinline   const   std::complex<double>  s0() const;

		__forceinline   std::complex<double>    s1();

		__forceinline   const   std::complex<double>  s1() const;

		__forceinline   std::complex<double>    s2();

		__forceinline   const  std::complex<double>  s2() const;

		__forceinline   std::complex<double>    s3();

		__forceinline   const  std::complex<double>  s3() const;

		__forceinline   std::complex<double>  *matrix();

		__forceinline   const  std::complex<double>  *matrix() const;

		   JonesMatrix&    operator=(_In_ JonesMatrix const&);

		   

		   JonesMatrix&    operator=(_In_ JonesMatrix &&);

		   JonesMatrix&    operator+=(_In_  JonesMatrix const&);

		   JonesMatrix&    operator+=(_In_ std::complex<double> const&);

		   JonesMatrix&    operator+=(_In_  JonesMatrix &&);

		   JonesMatrix&    operator-=(_In_  JonesMatrix const&);

		   JonesMatrix&    operator-=(_In_  std::complex<double> const&);

		   JonesMatrix&    operator-=(_In_  JonesMatrix &&);

		   JonesMatrix&    operator*=(_In_  JonesMatrix const&);

		   JonesMatrix&    operator*=(_In_  std::complex<double> const&);

		   JonesMatrix&    operator*=(_In_  JonesMatrix &&);

		   JonesMatrix&    operator/=(_In_  JonesMatrix const&);

		   JonesMatrix&    operator/=(_In_  std::complex<double> const&);

		   JonesMatrix&    operator/=(_In_  JonesMatrix &&);

		   std::complex<double>     operator[](_In_ const int);
		   
		   const std::complex<double>   operator[](_In_ const int) const;

		   JonesMatrix     operator-() const;

		   std::vector<__m256d> operator==(_In_  JonesMatrix const&) const;

		   std::vector<__m256d> operator!=(_In_  JonesMatrix const&) const;

		   std::vector<__m256d> operator==(_In_ std::complex<double> const&) const;

		   std::vector<__m256d> operator!=(_In_ std::complex<double> const&) const;

		   friend  JonesMatrix   operator+(_In_ JonesMatrix const&, _In_ JonesMatrix const&);

		   friend  JonesMatrix   operator+(_In_ JonesMatrix const& ,_In_ std::complex<double> const&);

		   friend  JonesMatrix   operator-(_In_ JonesMatrix const&, _In_ JonesMatrix const&);

		   friend JonesMatrix   operator-(_In_ JonesMatrix const&, _In_ std::complex<double> const&);

		   friend  JonesMatrix   operator*(_In_ JonesMatrix const&, _In_ JonesMatrix const&);

		   friend  JonesMatrix   operator*(_In_ JonesMatrix const&, _In_ std::complex<double> const&);

		   friend  JonesMatrix   operator/(_In_ JonesMatrix const&, _In_ JonesMatrix const&);

		   friend  std::vector<__m256d>   operator==(_In_ JonesMatrix const&, _In_ JonesMatrix const&);

		   friend std::vector<__m256d>    operator!=(_In_ JonesMatrix const&, _In_ JonesMatrix const&);

		   friend  JonesMatrix   operator/(_In_ JonesMatrix const&, _In_ std::complex<double> const&);

		   friend  std::ostream&     operator<<(_In_ std::ostream&, _In_ JonesMatrix const&);

		   JonesMatrix   matrix_transpose() const;

		   JonesMatrix   matrix_hermitian() const;
	private:

		std::complex<double> m_matrix[4];
	};


	class StokesVector
	{

	public:

		
		StokesVector() = default;

		StokesVector(_In_ const double, _In_ const double, _In_ const double, _In_ const double);

		StokesVector(_In_ struct StokesVectorParams const&);

		StokesVector(_In_ __m256d const&);

		StokesVector(_In_ StokesVector const&);

		StokesVector(_In_ StokesVector &&);

		~StokesVector() = default;

		/*
		@Brief 1st element of Stokes vector.
		*/
	__forceinline 	double            s0() const;
	/*
	@Brief: 2nd element of Stokes vector.
	*/
	__forceinline   double            s1() const;
	/*
	@Brief: 3rd element of Stokes vector.
	*/
	__forceinline   double            s2() const;
	/*
	@Brief: 4th element of Stokes vector.
	*/
	__forceinline   double            s3() const;
	/*
	@Brief: Constant pointer to this->m_stokes.
	*/
	__forceinline  const  double           *stokes() const;

	/*
	@Brief: Normalized Stokes vector elements.
	*/

	__forceinline  double  normalized_s1() const;

	__forceinline  double  normalized_s2() const;

	__forceinline  double  normalized_s3() const;

	/*
	@Brief: Stokes vector dot product.
	*/
	__forceinline  double            dot(_In_ StokesVector const&) const;

	/*
	@Brief: Principal angle of polarization
	*/
	double        poa() const;

	/*
	@Brief: Circular polarization degree.
	*/
	double        dcp() const;

	/*
	@Brief: Polarization ellipticity.
	*/
	double        polarization_ellipticity() const;


	/*
	@Brief: Elliptical plarization eccentrity
	*/
	double        polarization_eccentrity() const;

	/*
	@Brief: Zero Stokes vector.
	*/
	static   StokesVector    zero_stokes_vector();

	/*
	@Brief: Non-polarized Stokes vector.
	*/
	static   StokesVector    nonpolarized_stokes_vector();

		StokesVector&     operator=(_In_ StokesVector const&);

		StokesVector&     operator=(_In_ StokesVector &&);

		friend	std::ostream&     operator<<(_In_ std::ostream&, _In_ StokesVector const&);

		double            operator[](_In_ const int);

		const  double     operator[](_In_ const int) const;

		StokesVector&     operator+=(_In_ StokesVector const&);

		StokesVector&     operator-=(_In_ StokesVector const&);

		StokesVector&     operator*=(_In_ StokesVector const&);

		StokesVector&     operator/=(_In_ StokesVector const&);

		__m256d           operator==(_In_ StokesVector const&) const;

		__m256d           operator!=(_In_ StokesVector const&) const;

		StokesVector&     operator+=(_In_ const double);

		StokesVector&     operator-=(_In_ const double);

		StokesVector&     operator*=(_In_ const double);

		StokesVector&     operator/=(_In_ const double);

		__m256d           operator==(_In_ const double) const;

		__m256d           operator!=(_In_ const double) const;

		StokesVector      operator-() const;

		friend   StokesVector   operator+(_In_ StokesVector const&, _In_ StokesVector const&);

		friend   __m256d        operator==(_In_ StokesVector const&, _In_ StokesVector const&);

		friend  __m256d         operator!=(_In_ StokesVector const&, _In_ StokesVector const&);

		friend   StokesVector   operator-(_In_ StokesVector const&, _In_ StokesVector const&);

		friend   StokesVector   operator*(_In_ StokesVector const&, _In_ StokesVector const&);

		friend   StokesVector   operator/(_In_ StokesVector const&, _In_ StokesVector const&);

		friend   StokesVector   operator+(_In_ StokesVector const&, _In_ const double);

		friend   StokesVector   operator-(_In_ StokesVector const&, _In_ const double);

		friend   StokesVector   operator*(_In_ StokesVector const&, _In_ const double);

		friend   StokesVector   operator/(_In_ StokesVector const&, _In_ const double);

	private:

		double m_stokes[4];
	};

	

	/*
	"Brief:  Aggregate structure of JonesMatrix parameters.
	*/
	
	struct JonesMatrixParams
	{
		std::complex<double> ps0;
		std::complex<double> ps1;
		std::complex<double> ps2;
		std::complex<double> ps3;
	};

	/*
	@Brief: Aggregated structure of JonesVector parametrs.
	*/

	struct JonesVectorParams
	{
		std::complex<double> ps0;
		std::complex<double> ps1;
	};

	/*
	@Brief: Aggregated structure of StokesVectore parameters.
	*/

	struct StokesVectorParams
	{
		double ps0;
		double ps1;
		double ps2;
		double ps3;
	};

#include "Polarization.inl"
}
#endif /*_POLARIZATION_H_*/