#ifndef _ATMOS_MODEL76_SIMPLE_H_14_03_16
#define _ATMOS_MODEL76_SIMPLE_H_14_03_16



#include "AtmosphereLibDefs.h"

/*---------------------------------------------------------------------------------------------*/
/*--------------------- Adapted from  Atmosphere Model 1976 -----------------------------------*/
/*-- Based on original work of  Ralph L. Carmichael, Public Domain Aeronautical Software ------*/
/*-------      REFERENCE - U.S. Standard Atmosphere, 1976. U.S. Govt Printing Office -------   */
/*------------------- Simple Atmosphere Model up to 20km Altitude -----------------------------*/

#include "AtmosphereLibDefs.h"
#include "AtmosPhysConstants.h"
#include "AtmMetricViscosity.h"

namespace  atmosphere {


	template<typename T, class PhConstants>  class AtmModel76Simple {



	public:

		/*
		 @brief       Prevent creation of default Ctor.
		              No much sense in creation of this Constructor.
		 @params      none
		*/
		AtmModel76Simple() = delete;

		/*
		@brief        "Main" class Ctor which only initializes
		               class members.
        @params        const T - desired altitude.
		*/
		AtmModel76Simple(_In_ const T);

		/*
		@brief          Copy-Ctor
		@params         const AtmModel76Simple &
		*/
		AtmModel76Simple(_In_ const AtmModel76Simple &);

		/*
		@brief         Move-Ctor
		@params        AtmModel76Simple &&
		*/
		AtmModel76Simple(_In_ AtmModel76Simple &&);

		/*
		@brief         Dtor = default
		*/
		~AtmModel76Simple()noexcept(true) = default;

		/*

		      ***   Class member operators  ***

		*/

		/*
		@brief    *this = rhs (copies).
		@params   const AtmModel76Simple &
		*/
		 inline  auto  operator=(_In_ const AtmModel76Simple &)->AtmModel76Simple &;

		 /*
		 @brief    *this = rhs (moves).
		 @params   AtmModel76Simple &&
		 */
		 inline  auto  operator=(_In_ AtmModel76Simple &&)->AtmModel76Simple &;

		 /*
		 @brief    operator[]() , mutable state (std::pair can be modified)
		 @params   const int - index to m_AtmData vector container of objects
		           of type std::pair
		 @returns  std::pair<std::string,T> indexed by the argument
		 */
		 inline  auto  operator[](_In_ const int)->std::pair<std::string, T>;

		 /*
		 @brief    operator[]() , immutable state (std::pair can not be modified)
		 @params   const int - index to m_AtmData vector container of objects
		 of type std::pair.
		 @returns  const std::pair<std::string,T> indexed by the argument
		 */
		 inline  auto  operator[](_In_ const int)const->const std::pair<std::string, T>;

		 /*
		 @brief        operator call-forwards creation to createAtmosphere member function.
		 @params       Template argument of type PhConstants
		 @returns      self-reference to *this.
		 */
		 inline  auto  operator()(_In_ const PhConstants &)->AtmModel76Simple &;

		 /*
		 @brief        operator<< , outputs to std::ostream.
		 @params       std::ostream &
		 @params       const AtmModel76Simple &
		 @returns      std::ostream &
		 */
		 friend   auto  operator<<(_In_ std::ostream &, _In_ const AtmModel76Simple &)->std::ostream &;

		 /*
		         -------    Accessor methods  --------
		 */

		 /*
		 @brief    Returns class member m_AtmData.
		           m_AtmData is const.
		 @params   none.
		 @return   const this->m_AtmData
		 */
		 inline    auto  getAtmData() const->std::vector<std::pair<std::string, T>>;

		 /*
		 @brief    Returns class member m_Altitude.
		 @params   none.
		 @returns  const this->m_Altitude.
		 */
		 inline    auto  getAltitude() const->T;

		 /*
		         ---------  Member functions -----------
		 */

		 /*
		 @brief     Creates simplified atmosphere model.
		            operates in-place on *this.
		 @params    template parameter: const PhConstants&
		 @return    nothing.
		 */
		 auto            createAtmosphere(_In_ const PhConstants &)->void;

		 /*
		 @brief     Displays internal state of *this.
		 @params    none.
		 @returns   nothing.
		 */
		 auto            displayAtmModel() const->void;



	private:

		/*
		@brief   class member m_AtmData
		         The size of this vector is 
				 constant i.e 10 elements of type std::pair<std::string,T>
				 and is set in class Ctor.
		*/
		std::vector<std::pair<std::string, T>> m_AtmData;

		/*
		@brief    class member m_Altitude of type T scalar.
		          Altitude for which data must be computed.
		*/
		T    m_Altitude;
	};

	/*
	Global function for creating and filling in static array of read-out vectors.
	This function expects pre-initialized array as an argument.
	*/
	template<typename T, class PhConstants> auto
		createAtm76Simple(_Inout_ atmosphere::AtmModel76Simple<T, PhConstants>(&)[22], _In_ const PhConstants &,_In_ const int)->void;

	/*
	Global function for creating and filling in a vector of smart pointers pointing
	to AtmModel76 objects.
	This function expects AtmModel76Simple intialized smart pointers.
	*/
	template<typename T, class PhConstants> auto
		createAtm76Simple(_Inout_ std::vector<std::unique_ptr<atmosphere::AtmModel76Simple<T, PhConstants>>> &,
		_In_ const PhConstants &)->void;

#include "AtmosModel76Simple.inl"
}
#endif /*_ATMOS_MODEL76_SIMPLE_H_14_03_16*/