#ifndef _COORD_AXIS_H_
#define _COORD_AXIS_H_


#include "QuaternionsLib.h"
#include  "VectorF64AVX.h"


namespace   mathlib {


	/*

	     ***     Cartesian coordinate system axis.   ***
		         templated on Position and on Orientation types.
	*/

	template<class Position, class Orientation, typename T>   class Axis {


	public:

		/*

		          ****   Construction   ****
		*/


		/*
		@brief    Default Ctor = delete
		*/
		Axis() = delete;

		/*
		@brief    "Main" class Ctor creates single axis of cartesian coordinate system.
		@params    const Position & - 3D position vector
		@params    const Orientation & - 3D orientation Quaternion.
		@return    nothing.
		*/
	    inline  	Axis(_In_ const Position &, _In_ const Orientation &);

		/*
		@brief     Axis Copy-Ctor.
		@params    const Axis &.
		@returns   nothing.
		*/
		inline      Axis(_In_ const Axis &);

		/*
		@brief     Axis Move-Ctor.
		@params    Axis &&.
		@returns   nothing.
		*/
		inline      Axis(_In_ Axis &&);

		/*

		       ***   Destruction   ***
		*/

		/*
		@brief     Axis Dtor=default.
		@params    none.
		@returns   nothing (destructor).
		*/
		~Axis() noexcept(true) = default;

		/*

		      ***  Member and friend operators  ***

		*/

		/*
		@brief     *this = rhs (copy).
		*/
		inline   auto    operator=(_In_ const Axis &)->Axis &;

		/*
		@brief     *this = rhs (move).
		*/
		inline   auto    operator=(_In_ Axis &&)->Axis &;

		/*
		@brief     *this += rhs.
		*/
		inline   auto    operator+=(_In_ const Axis &)->Axis &;

		/*
		@brief      *this += scalar.
		*/
		inline   auto    operator+=(_In_ const T)->Axis &;

		/*
		@brief      *this -= rhs
		*/
		inline   auto    operator-=(_In_ const Axis &)->Axis &;

		/*
		@brief      *this -= scalar.
		*/
		inline   auto    operator-=(_In_ const T)->Axis &;

		
		/*
		@brief       *this *= rhs
		*/
		inline   auto    operator*=(_In_ const Axis &)->Axis &;

		/*
		@brief       *this *= scalar
		*/
		inline   auto    operator*=(_In_ const T)->Axis &;

		/*
		@brief        *this /= rhs
		*/
		inline   auto    operator/=(_In_ const Axis &)->Axis &;

		/*
		@brief        *this /= scalar
		*/
		inline   auto    operator/=(_In_ const T)->Axis &;

		/*
		@brief         *this == rhs
		*/
		inline   auto    operator==(_In_ const Axis &) const->std::pair<__m256d,__m256d>;

		/*
		@brief          *this != rhs 
		*/
		inline   auto    operator!=(_In_ const Axis &) const->std::pair<__m256d,__m256d>;


		/*

		           **********          Accessors         ********
		*/

		/*
		@brief    x-component of  the position vector.
		@params   none
		@returns  x component of  the position vector.
		*/
		inline   auto    x_vec() const->T;

		/*
		@brief    y-component of the position vector.
		@params   none
		@returns  y component of  the position vector.
		*/
		inline   auto    y_vec() const->T;

		/*
		@brief    z-component of the position vector.
		@params   none
		@returns  z component of  the position vector.
		*/
		inline   auto    z_vec() const->T;

		/*
		@brief    alfa component of the orientation quaternion.
		@params   none.
		@returns  alfa component.
		*/
		inline   auto    x_quat() const->T;

		/*
		@brief    beta component of the orientation quaternion.
		@params   none.
		@returns  beta component.
		*/
		inline   auto    y_quat() const->T;

		/*
		@brief    gamma component of  the orientation quaternion.
		@params   none.
		@returns  gamma component.
		*/
		inline   auto    z_quat() const->T;

		/*
		@brief    delta component of the orientation quaternion.
		@params   none.
		@returns  delta component.
		*/
		inline   auto    w_quat() const->T;

		/*
		@brief    Position vector.
		@params   none.
		@returns  Position vector
		*/
		inline   auto    getPosition() const->Position;

		/*
		@brief    Orientation quaternion.
		@params   none.
		@returns  Orientation quaternion.
		*/
		inline    auto   getOrientation() const->Orientation;


		/*
		
		          ***  Member functions  ***
		*/

		/*
		@brief        Prints state of the Position vector and Orientation quaternion.
		@params       implicit *this.
		@return       nothing
		*/
		auto           displayAxis()const->void;

		/*
		 @brief        Computes Euclidean distance of Axis position vector.
		 @params       implicit *this.
		 @returns      scalar value of euclidean distance.
		 */
		auto           pos_magnitude() const->T;


	private:

		/*
		@brief   class variable axis vector m_oVector.
		*/
		Position  m_oVector;

		/*
		@brief   class variable axis orientation in 3D space  m_oOrientation.
		*/
		Orientation  m_oOrientation;
	};

	/*

	              ***         Free standing operators         ***
	*/

	/*
	@brief     Axis c = a + b
	@params    const mathlib::Axis<Position, Orientation, T> &
	@params    const mathlib::Axis<Position, Orientation, T> &
	@returns   mathlib::Axis<Position, Orientation, T> object.
	*/
	template<class Position, class Orientation, typename T> inline auto operator+(_In_ const mathlib::Axis<Position, Orientation, T> &,
		_In_ const mathlib::Axis<Position, Orientation, T> &)->mathlib::Axis<Position, Orientation, T>;

	/*
	@brief     Axis c = a + b, where b is of scalar type
	@params    const mathlib::Axis<Position, Orientation, T> &
	@params    const T
	@returns   mathlib::Axis<Position, Orientation, T> object.
	*/
	template<class Position, class Orientation, typename T>  std::enable_if<std::is_scalar<T>::value, mathlib::Axis<Position, Orientation, T>>::type 
		operator+(_In_ const mathlib::Axis<Position, Orientation, T> &, _In_ const T);

	/*
	@brief     Axis c = a - b
	@params    const mathlib::Axis<Position, Orientation, T> &
	@params    const mathlib::Axis<Position, Orientation, T> &
	@returns   mathlib::Axis<Position, Orientation, T> object.
	*/
	template<class Position, class Orientation, typename T> auto operator-(_In_ const mathlib::Axis<Position, Orientation, T> &,
		_In_ const mathlib::Axis<Position, Orientation, T> &)->mathlib::Axis<Position, Orientation, T>;

	/*
	@brief     Axis c = a - b, where b is of scalar type
	@params    const mathlib::Axis<Position, Orientation, T> &
	@params    const T
	@returns   mathlib::Axis<Position, Orientation, T> object.
	*/
	template<class Position, class Orientation, typename T> std::enable_if<std::is_scalar<T>::value, mathlib::Axis<Position, Orientation, T>>::type
		operator-(_In_ const mathlib::Axis<Position, Orientation, T> &, _In_ const T);

	/*
	@brief     Axis c = a * b
	@params    const mathlib::Axis<Position, Orientation, T> &
	@params    const mathlib::Axis<Position, Orientation, T> &
	@returns   mathlib::Axis<Position, Orientation, T> object.
	*/
	template<class Position, class Orientation, typename T> inline auto operator*(_In_ const mathlib::Axis<Position, Orientation, T> &,
		_In_ const mathlib::Axis<Position, Orientation, T> &)->mathlib::Axis<Position, Orientation, T>;

	/*
	@brief     Axis c = a * b, where b is of scalar type
	@params    const mathlib::Axis<Position, Orientation, T> &
	@params    const T
	@returns   mathlib::Axis<Position, Orientation, T> object.
	*/
	template<class Position, class Orientation, typename T> std::enable_if<std::is_scalar<T>::value, mathlib::Axis<Position, Orientation, T>>::type
		operator*(_In_ const mathlib::Axis<Position, Orientation, T> &, _In_ const T);

	/*
	@brief     Axis c = a / b
	@params    const mathlib::Axis<Position, Orientation, T> &
	@params    const mathlib::Axis<Position, Orientation, T> &
	@returns   mathlib::Axis<Position, Orientation, T> object.
	*/
	template<class Position, class Orientation, typename T> inline auto operator/(_In_ const mathlib::Axis<Position, Orientation, T> &,
		_In_ const mathlib::Axis<Position, Orientation, T> &)->mathlib::Axis<Position, Orientation, T>;

	/*
	@brief     Axis c = a / b, where b is of scalar type
	@params    const mathlib::Axis<Position, Orientation, T> &
	@params    const T
	@returns   mathlib::Axis<Position, Orientation, T> object.
	*/
	template<class Position, class Orientation, typename T> std::enable_if<std::is_scalar<T>::value, mathlib::Axis<Position, Orientation, T>>::type
		operator/(_In_ const mathlib::Axis<Position, Orientation, T> &, _In_ const T);

	/*
	@brief      a == b
	@params    const mathlib::Axis<Position, Orientation, T> &
	@params    const mathlib::Axis<Position, Orientation, T> &
	@returns   std::pair<__m256d, __m256d>
	*/
	template<class Position, class Orientation, typename T> inline auto operator==(_In_ const mathlib::Axis<Position, Orientation, T> &,
		_In_ const mathlib::Axis<Position, Orientation, T> &)->std::pair<__m256d, __m256d>;

	/*
	@brief      a != b
	@params    const mathlib::Axis<Position, Orientation, T> &
	@params    const mathlib::Axis<Position, Orientation, T> &
	@returns   std::pair<__m256d, __m256d>
	*/
	template<class Position, class Orientation, typename T> inline auto operator!=(_In_ const mathlib::Axis<Position, Orientation, T> &,
		_In_ const mathlib::Axis<Position, Orientation, T> &)->std::pair<__m256d, __m256d>;




#include "CoordAxis.inl"
}
#endif /*_COORD_AXIS_H_*/