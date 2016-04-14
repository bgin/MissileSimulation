
template<class Position, class Orientation, typename T>  inline mathlib::Axis<Position, Orientation, T>::Axis(_In_ const Position &v,
	_In_ const Orientation &q) :
	m_oVector{ v },
	m_oOrientation{ q }
{           

}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//

template<class Position, class Orientation, typename T>  inline  mathlib::Axis<Position, Orientation, T>::Axis(_In_ const Axis &rhs) :
m_oVector{ rhs.m_oVector },
m_oOrientation{ rhs.m_oOrientation }
{

}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//

template<class Position, class Orientation, typename T>  inline  mathlib::Axis<Position , Orientation, T>::Axis(_In_ Axis &&rhs) :
m_oVector{ std::move(rhs.m_oVector) },
m_oOrientation{ std::move(rhs.m_oOrientation) }
{

}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//
template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::operator=(_In_ const Axis &rhs)->mathlib::Axis<Position, Orientation, T> & {

		if (this == &rhs) return (*this);
		this->m_oVector.operator=(rhs.m_oVector);
		this->m_oOrientation.operator=(rhs.m_oOrientation);
		return (*this);
	}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//

template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::operator=(_In_ Axis &&rhs)->mathlib::Axis<Position, Orientation, T> & {

		if (this == &rhs) return (*this);
		this->m_oVector.operator=(std::move(rhs.m_oVector));
		this->m_oOrientation.operator=(std::move(rhs.m_oOrientation));
		return (*this);
	}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//

template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::operator+=(_In_ const Axis  &rhs)->mathlib::Axis<Position, Orientation, T> & {

		this->m_oOrientation.operator+=(rhs.m_oOrientation);
		this->m_oVector.operator+=(rhs.m_oVector);
		return (*this);
	}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//
template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::operator+=(_In_ const T scalar)->mathlib::Axis<Position, Orientation, T> & {

		this->m_oOrientation.operator+=(scalar);
		this->m_oVector.operator+=(scalar);
		return (*this);
	}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//
template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::operator-=(_In_ const Axis &rhs)->mathlib::Axis<Position, Orientation, T> & {

		this->m_oOrientation.operator-=(rhs.m_oOrientation);
		this->m_oVector.operator-=(rhs.m_oVector);
		return (*this);
	}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//
template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::operator-=(_In_ const T scalar)->mathlib::Axis<Position, Orientation, T> & {

		this->m_oOrientation.operator-=(rhs.m_oOrientation);
		this->m_oVector.operator-=(rhs.m_oVector);
		return (*this);
	}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//
template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::operator*=(_In_ const Axis &rhs)->mathlib::Axis<Position, Orientation, T> & {

		this->m_oOrientation.operator*=(rhs.m_oOrientation);
		this->m_oVector.operator*=(rhs.m_oVector);
		return (*this);
	}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//
template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::operator*=(_In_ const T scalar)->mathlib::Axis<Position, Orientation, T> & {

		this->m_oOrientation.operator*=(scalar);
		this->m_oVector.operator*=(scalar);
		return (*this);
	}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//


template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::operator/=(_In_  const Axis &rhs)->mathlib::Axis<Position, Orientation, T> & {

		this->m_oOrientation.operator/=(rhs.m_oOrientation);
		this->m_oVector.operator/=(rhs.m_oVector);
		return (*this);
	}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//

template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::operator/=(_In_ const T scalar)->mathlib::Axis<Position, Orientation, T> & {

		this->m_oOrientation.operator/=(scalar);
		this->m_oVector.operator/=(scalar);
		return (*this);
	}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//

template<class Position, class Orientation, typename T> inline  auto mathlib::Axis<Position, Orientation, T>
	::operator==(_In_ const Axis &rhs) const->std::pair<__m256d, __m256d> {

		return std::pair<__m256d, __m256>{{ this->m_oVector.operator==(rhs.m_oVector),   this->m_oOrientation.operator==(rhs.m_oOrientation) }};
	}

template<class Position, class Orientation, typename T> inline  auto mathlib::Axis<Position, Orientation, T>
	::operator!=(_In_ const Axis &rhs) const->std::pair<__m256d, __m256d> {

		return std::pair<__m256d, __m256d>{{ this->m_oVector.operator!=(rhs.m_oVector), this->m_oOrientation.operator!=(rhs.m_oOrientation) }};
	}
 

template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::x_vec() const->T {

		return (this->m_oVector.extract_scalar(0));
	}

template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::y_vec() const->T {

		return (this->m_oVector.extract_scalar(1));
	}

template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::z_vec() const->T {

		return (this->m_oVector.extract_scalar(2));
	}

template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::x_quat() const->T {

		return (this->m_oOrientation.alfa());
	}

	template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::y_quat() const->T {

		return (this->m_oOrientation.beta());
	}

	template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::z_quat() const->T {

		return (this->m_oOrientation.gamma());
	}

template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::w_quat() const->T {

		return (this->m_oOrientation.delta());
	}

template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::getPosition() const->Position {

		return (this->m_oVector);
	}

template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::getOrientation() const->Orientation {

		return (this->m_oOrientation);
	}

template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
		::pos_magnitude() const->T {

			return (this->m_oVector.euclidean_distance());
		}

template<class Position, class Orientation, typename T> inline auto mathlib::Axis<Position, Orientation, T>
	::displayAxis() const->void {
		
		std::cout << std::setprecision(16) << std::fixed << std::showpoint
			<< "Axis object context\n"
			<< "Position component:\n" 
			<< this->m_oVector << std::endl
			<< "Orientation component:\n" 
			<< this->m_oOrientation << std::endl;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------//

	//-----------------------------------------------------------------------------------------------------------------------------------//
template<class Position, class Orientation, typename T>	 inline auto operator+(_In_ const mathlib::Axis<Position, Orientation, T> &lhs,
		_In_ const mathlib::Axis<Position, Orientation, T> &rhs)->mathlib::Axis<Position, Position, T> {

		Axis<Position, Orientation, T> ret_val;
		ret_val = Axis<Position, Orientation, T>{lhs.getPosition() += rhs.getPosition(), lhs.getOrientation() += rhs.getOrientation()};
		return (ret_val);
	}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//
template<class Position, class Orientation, typename T> inline std::enable_if<std::is_scalar<T>::value, mathlib::Axis<Position,Orientation,T>>::type
         operator+(_In_ const mathlib::Axis<Position, Orientation, T> &lhs, const T s) {

			 Axis<Position, Orientation, T> ret_val;
			 ret_val = Axis<Position, Orientation, T>{lhs.getPosition() += s, lhs.getOrientation() += s};
			 return (ret_val);
}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//
template<class Position, class Orientation, typename T> inline auto operator-(_In_ const mathlib::Axis<Position, Orientation, T> &lhs,
	_In_ const mathlib::Axis<Position, Orientation, T> &rhs)->mathlib::Axis<Position, Orientation, T> {

	Axis<Position, Orientation, T> ret_val;
	ret_val = Axis<Position, Orientation, T>{lhs.getPosition() -= rhs.getPosition(), lhs.getOrientation() -= rhs.getOrientation()};
	return (ret_val);
}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//
template<class Position, class Orientation, typename T> inline std::enable_if<std::is_scalar<T>::value, mathlib::Axis<Position, Orientation, T>>::type
        operator-(_In_ const mathlib::Axis<Position, Orientation, T> &lhs, _In_ const T s) {

			Axis<Position, Orientation, T> ret_val;
			ret_val = Axis<Position, Orientation, T>{lhs.getPosition() -= s, lhs.getOrientation() -= s};
}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//
template<class Position, class Orientation, typename T> inline auto operator*(_In_ const mathlib::Axis<Position, Orientation, T> &lhs,
	_In_ const mathlib::Axis<Position, Orientation, T> &rhs)->mathlib::Axis<Position, Orientation, T> {

	Axis<Position, Orientation, T> ret_val;
	ret_val = Axis<Position, Orientation, T>{lhs.getPosition() *= rhs.getPosition(), lhs.getOrientation() *= rhs.getOrientation()};
	return (ret_val);
}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//
template<class Position, class Orientation, typename T> inline std::enable_if<std::is_scalar<T>::value, mathlib::Axis<Position, Orientation, T>>::type
        operator*(_In_ const mathlib::Axis<Position, Orientation, T> &lhs, _In_ const T s) {

			Axis<Position, Orientation, T> ret_val;
			ret_val = Axis<Position, Orientation, T>{lhs.getPosition() *= s, lhs.getOrientation() *= s};
			return (ret_val);
}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//
template<class Position, class Orientation, typename T> inline auto operator/(_In_ const mathlib::Axis<Position, Orientation, T> &lhs,
	_In_ const mathlib::Axis<Position, Orientation, T> &rhs)->mathlib::Axis<Position, Orientation, T> {

	Axis<Position, Orientation, T> ret_val;
	ret_val = Axis<Position, Orientation, T>{lhs.getPosition() /= rhs.getPosition(), lhs.getOrientation() /= rhs.getOrientation()};
	return (ret_val);
}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//
template<class Position, class Orientation, typename T> inline std::enable_if<std::is_scalar<T>::value, mathlib::Axis<Position, Orientation, T>>::type
        operator/(_In_ const mathlib::Axis<Position, Orientation, T> &lhs, const T s) {

	Axis<Position, Orientation, T> ret_val;
	ret_val = Axis<Position, Orientation, T>{lhs.getPosition() /= s, lhs.getOrientation() /= s};
	return (ret_val);
}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//
template<class Position, class Orientation, typename T> inline auto operator==(_In_ const mathlib::Axis<Position, Orientation, T> &lhs,
	_In_ const mathlib::Axis<Position, Orientation, T> &rhs)->std::pair<__m256d, __m256d> {

	std::pair<__m256d, __m256d> ret_val;
	ret_val = std::pair<__m256d, __m256d>{{ lhs.getPosition() == rhs.getPosition(), lhs.getOrientation() == rhs.getOrientation() }};
	return (ret_val);
}
//-----------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------//
template<class Position, class Orientation, typename T> inline auto operator!=(_In_ const mathlib::Axis<Position, Orientation, T> &lhs,
	_In_ const mathlib::Axis<Position, Orientation, T> &rhs)->std::pair<__m256d, __m256d> {

	std::pair<__m256d, __m256d> ret_val;
	ret_val = std::pair<__m256d, __m256d>{{ lhs.getPosition() != rhs.getPosition(), lhs.getOrientation() != rhs.getOrientation() }};
	return (ret_val);
}

		
		
	
