#ifndef _CARTESIAN_COORD_SYSTEM_HPP_
#define _CARTESIAN_COORD_SYSTEM_HPP_ 0x1


#include "MathLibDefinitions.h"


namespace    mathlib {

	/*
	        Earth reference frame.
	*/

	template<class Vector>  class EarthRefFrame {

     


	public:

		/*
		@brief    Default Ctor.
		*/
		EarthRefFrame() noexept(true) = default;

		/*
		@brief    "Main" class Ctor.
		*/
		EarthRefFrame(_In_ const Vector &v1, _In_ const Vector &v2) :
			m_oV1{ v1 }, m_oV2{ v2 } {

			this->m_oV3.operator=( Vector.cross(m_oV1, m_oV2));
		}

		/*
		@brief     Copy-Ctor
		*/
		EarthRefFrame(_In_ const EarthRefFrame &rhs) :
			m_oV1{ rhs.m_oV1 },
			m_oV2{ rhs.m_oV2 },
			m_oV3{ rhs.m_oV3 }
		{}

		/*
		@brief     Move-Ctor.
		*/
		EarthRefFrame(_In_ EarthRefFrame &&rhs) :
			m_oV1{ std::move(rhs.m_oV1) },
			m_oV2{ std::move(rhs.m_oV2) },
			m_oV3{ std::move(rhs.m_oV3) }
		{}

		/*
		@brief     Default Dtor
		*/
		~EarthRefFrame() noexcept(true) = default;


		/*
		@brief   *this = rhs (copy)
		*/
		auto operator=(_In_ const EarthRefFrame &rhs)->EarthRefFrame & {

			if (this == &rhs) return (*this);
			this->m_oV1.operator=(rhs.m_oV1);
			this->m_oV2.operator=(rhs.m_oV2);
			this->m_oV3.operator=(rhs.m_oV3);
			return (*this);
		}

		/*
		@brief    *this = rhs (move)
		*/
	   auto	operator=(_In_ EarthRefFrame &&rhs)->EarthRefFrame & {

			if (this == &rhs) return (*this);
			this->m_oV1.operator(std::move(rhs.m_oV1));
			this->m_oV2.operator(std::move(rhs.m_oV2));
			this->m_oV3.operator(std::move(rhs.m_oV3));
			return (*this);
		}

		/*
		@brief    ostream&  operator<<
		*/


	private:

		/*
		@brief      component v1 of the coordinate system.
		*/
		Vector  m_oV1;

		/*
		@brief      component v2 of the coordinate system.
		*/
		Vector  m_oV2;

		/*
		@brief      component v3 of the coordinate system.
		*/
		Vector  m_oV3;
	};
}
#endif /*_CARTESIAN_COORD_SYSTEM_HPP_*/