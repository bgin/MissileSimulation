#ifndef _DIMENSIONAL_ANALYSIS_HPP_
#define _DIMENSIONAL_ANALYSIS_HPP_

#include "MathLibDefinitions.h"
#include <boost\units\systems\si\acceleration.hpp>
#include <boost\units\systems\si\force.hpp>
#include <boost\units\systems\si\length.hpp>
#include <boost\units\systems\si\energy.hpp>
#include <boost\units\systems\si\current.hpp>
#include <boost\units\systems\si\io.hpp>

using namespace boost::units;
using namespace boost::units::si;

namespace   mathlib{

	
	namespace physics {


		void test(){

			quantity<force, double> Force = quantity<force, double>(2.0 * newton);
			
			
			
		}

		/*

		     *** SIForce   wrapper  class around boost::unit quantity<force,T> *** 
		*/

		template<typename T>  class SIForce {



		public:

			/*
			@brief   Zero-force unit.
			*/

		constexpr	SIForce() : m_magnitude{ static_cast<T>(0) } { this->m_oForce = quantity<force, T>(this->m_magnitude * newton); }
				         
			

			/*
			@brief    Create Force object with user passed magnitude value.
			*/

		    SIForce(_In_ T const mag) : m_magnitude{ mag } { this->m_oForce = quantity<force, T>(this->m_magnitude * newton); }
				
			

			/*
			@brief  Copy-Ctor
			*/
			SIForce(_In_ const SIForce &rhs) : m_magnitude{ rhs.m_magnitude }, m_oForce{ rhs.m_oForce }{}
				
			

			/*
			@brief   Move-Ctor
			*/
			SIForce(_In_ SIForce &&rhs) : m_magnitude{ std::forward<T>(rhs.m_magnitude) }, m_oForce{ std::forward<T>(rhs.m_oForce) } {}
			

			/*
			@brief  Dtor == default
			*/
			~SIForce() = default;

			/*

			      ****   Member functions  ****
			*/

			/*  Returns  this->m_magnitude  */
			__forceinline     auto       Magnitude()->const T {

				return (this->m_magnitude);
			}

			/*  Returns  this->m_oForce  */
			__forceinline    auto Force()->const quantity<force,T>{

				return (this->m_oForce);
			}

			/*

			      ***  Member operators  ***  
			*/
			

			/* 
			@brief    *this = const &rhs
			*/
			SIForce &     operator=(_In_ const SIForce &rhs) {

				if (this == &rhs) return (*this);

				this->m_magnitude = rhs.m_magnitude;
				this->m_oForce.operator=(rhs.m_oForce);
				return (*this);
			}

			/*
			@brief    *this = &&rhs
			*/
			SIForce &     operator=(_In_ SIForce &&rhs) {

				if (this == &rhs) return (*this);

				this->m_magnitude = std::forward<T>(rhs.m_magnitude);
				this->m_oForce.operator=(std::forward<T>(rhs.m_oForce));
				return (*this);
			}

			/*
			@brief    *this +=   const  &rhs
		   */
			SIForce &      operator+=(_In_ const SIForce &rhs) {

				this->m_magnitude += rhs.m_magnitude;
				this->m_oForce.operator+=(rhs.m_oForce);
				return (*this);
			}

			

			/*
			@brief     *this +=    &&rhs
			*/
			SIForce  &      operator+=(_In_ SIForce &&rhs) {

				this->m_magnitude += rhs.m_magnitude;
				this->m_oForce.operator+=(std::forward<T>(rhs.m_oForce));
				return (*this);
			}

			/*
			@brief     *this -=    const  &rhs
			*/
			SIForce  &       operator-=(_In_ const SIForce &rhs) {

				this->m_magnitude -= rhs.m_magnitude;
				this->m_oForce.operator-=(rhs.m_oForce);
				return (*this);
			}

			/*
			@brief      *this -=   &&rhs
			*/
			SIForce  &       operator-=(_In_ SIForce &&rhs) {

				this->m_magnitude -= rhs.m_magnitude;
				this->m_oForce.operator-=(std::forward<T>(rhs.m_oForce));
				return (*this);
			}

			/*
			@brief       *this *=  const &rhs
			*/
			SIForce  &       operator*=(_In_  const SIForce &rhs) {

				this->m_magnitude *= rhs.m_magnitude;
				this->m_oForce.operator*=(rhs.m_oForce);
				return (*this);
			}

			/*
			@brief       *this *=  &&rhs
			*/
			SIForce  &       operator*=(_In_  SIForce &&rhs) {

				this->m_magnitude *= rhs.m_magnitude;
				this->m_oForce.operator*=(std::forward<T>(rhs.m_oForce));
				return (*this);
			}

			/*
			@brief        *this /=  const &rhs
			*/
			SIForce  &       operator/=(_In_ const SIForce &rhs) {

				this->m_magnitude /= rhs.m_magnitude;
				this->m_oForce.operator/=(rhs.m_oForce);
				return (*this);
			}

			/*
			@brief        *this /=   &&rhs
			*/
			SIForce  &       operator/=(_In_ SIForce &&rhs) {

				this->m_magnitude /= rhs.m_magnitude;
				this->m_oForce.operator/=(std::forward<T>(rhs.m_oForce));
				return (*this);
			}

			/*
			@brief         *this == rhs
			*/
			auto             operator==(_In_ const SIForce &rhs)->const bool {

				return (this->m_oForce.value() == rhs.m_oForce.value() &&
					this->m_magnitude == rhs.m_magnitude);
			}

			/*
			@brief           *this != rhs
			*/
			auto              operator!=(_In_ const SIForce &rhs)->const bool {

				return !(this->operator==(rhs));
			}

			
			/*
			@brief      operator<<
			*/
			friend	std::ostream &      operator<<(_In_ std::ostream &os, _In_   SIForce &rhs) {
				
				os << "Force = " << rhs.Force().value() << " N" << std::endl;
				return os;
			}

		private:

			/*
			@brief   Amount of force in unit of newton.
			*/
			T   m_magnitude;

			/*
			@brief   unit of Force.
			*/
			quantity<force, T> m_oForce;
		};

		/*
		          ***  Wrapper class for the boost::units quantity of Length.
				  
		*/

		template<typename T>   class SILength {



		public:

			/*    
			    Zero-length Default Ctor
			*/
			SILength() : m_magnitude{ static_cast<T>(0) } { this->m_oLength = quantity<length, T>(this->m_magnitude * meter) }

			/*
			    One-arg Ctor.
			*/
			SILength(const T &mag) : m_magnitude{ mag } { this->m_oLength = quantity<length, T>(this->m_magnitude * meter); }

			/*
			    Two-arg Ctor.
			*/
			SILength(const T &rhs, const quantity<length, T> &lhs) : m_magnitude{ rhs }, m_oLength{ lhs } {};
			/*
			    Copy-Ctor
			*/
			SILength(const SILength &rhs) : m_magnitude{ rhs.m_magnitude }, m_oLength{ rhs.m_oLength } {}

			/*
			    Move-Ctor
			*/
			SILength(SILength &&rhs) : m_magnitude{ std::move(rhs.m_magnitude) }, m_oLength{ std::move(rhs.m_oLength) } {}

			/*
			    Dtor = default
			*/
			~SILength() noexcept(true) = default;

			/*

			         ***   Member accessors  ***
			*/


			/*
			     Returns magnitude argument.
			*/
			__forceinline  auto   Magnitude()->const T{

				return (this->m_magnitude);
			}

			/*
			@brief   Returns  m_oLength class variable.
			*/
			__forceinline  auto   Length()->const quantity<length, T> {

				return (this->m_oLength);
			}

			

			/*

			     ***   Class member and friend operators.  *** 
			*/

			/*
			@brief     copy-assignment.
			*/
			auto  operator=(_In_ const SILength &rhs)->SILength<T> & {

				if (this == &rhs) return (*this);

				this->m_magnitude = rhs.m_magnitude;
				this->m_oLength = rhs.m_oLength;
				return (*this);
			}

			/*
			@brief      move-assignment.
			*/
			auto  operator=(_In_ SILength &&rhs)->SILength<T> & {

				if (this == &rhs) return (*this);

				this->m_magnitude = std::forward<T>(rhs.m_magnitude);
				this->m_oLength = std::forward<T>(rhs.m_oLength);
				return (*this);
			}

			/*
			@brief     *this += rhs
			*/
			auto   operator+=(_In_ const SILength &rhs)->SILength<T> & {

				this->m_magnitude += rhs.m_magnitude;
				this->m_oLength.operator+=(rhs.m_oLength);
				return (*this);
			}

			/*
			@brief    *this += rhs (move)
			*/
			auto    operator+=(_In_  SILength<T> &&rhs)->SILength<T> & {

				this->m_magnitude += std::move(rhs.m_magnitude);
				this->m_oLength.operator+=(std::move(rhs.m_oLength));
				return (*this);
			}
			  
			/*
			@brief     *this -= rhs
			*/
			auto   operator-=(_In_ const SILength &rhs)->SILength<T> & {

				this->m_magnitude -= rhs.m_magnitude;
				this->m_oLength.operator-=(rhs.m_oLength);
				return (*this);
			}

			/*
			@brief      *this -= rhs (move)
			*/
			auto    operator-=(_In_ SILength &&rhs)->SILength<T> & {

				this->m_magnitude -= std::move(rhs.m_magnitude);
				this->m_oLength.operator-=(std::move(rhs.m_oLength));
				return (*this);
			}

			/*
			@brief     *this *= rhs
			*/
			auto    operator*=(_In_ const SILength &rhs)->SILength<T> & {

				this->m_magnitude *= rhs.m_magnitude;
				this->m_oLength.operator*=(rhs.m_oLength);
				return (*this);
			}

			/*
			@brief      *this /= rhs
			*/
			auto    operator/=(_In_ SILength &&rhs)->SILength<T> & {

				this->Magnitude = std::move(rhs.m_magnitude);
				this->m_oLength.operator*=(std::move(rhs.m_oLength));
				return (*this);
			}

			/*
			@brief    *this /= rhs
			*/
			auto    operator/=(_In_ const SILength &rhs)->SILength<T> & {

				this->m_magnitude /= rhs.m_magnitude;
				this->m_oLength.operator/=(rhs.m_oLength);
				return (*this);
			}

			
			/*
			@brief        *this == rhs
		    */
			auto    operator==(_In_ const SILength &rhs)->const bool {

				return (this->m_oLength.value() == rhs.m_oLength.value() &&
					this->m_magnitude == rhs.m_magnitude);
			}

			/*
			@brief        *this != rhs
			*/
			auto    operator!=(_In_ const SILength &rhs)->const bool {

				return (!(this->operator==(rhs)));
			}

			/*
			@brief    operator<<
			*/
			friend  std::ostream &   operator<<(_In_ std::ostream &os, _In_   SILength &rhs) {

				os << "Length = " << rhs.Length().value() << " m" << std::endl;
				return os;
			}

			
				  
			

		private:

			/*  
			    T m_magnitude class variable 
			*/
			T    m_magnitude;

			/*
			    T m_oLength class variable
            
			*/

			quantity<length, T> m_oLength;
			
		};

		/*

		        ***  Generic class Work   ***
				
		*/

		template<class Force, class Distance, typename T>  
		class SIWork {


		public:

			/*
			@brief Surpress creation of Default Ctor
			*/
			SIWork() = delete;


			/*
			 @brief    One-arg Ctor
			*/

		    
			SIWork(_In_  Force &f, _In_  Distance &d) : m_oWork{ f.Force() * d.Length() } {}

			/*
			@brief     Copy-Ctor.
			*/
			SIWork(_In_ const SIWork &rhs) : m_oWork{ rhs.m_oWork } {}

			/*
			@brief     Move-Ctor
			*/
			SIWork(_In_ SIWork &&rhs) : m_oWork{ std::move(rhs.m_oWork) } {}

			/*
			@brief   Dtor
			*/
			~SIWork() noexcept(true) = default;

			

			/*

			      Class member operators, and accessor.

			*/

			auto     Work()->const SIWork<Force, Distance, T> {

				return (this->m_oWork);
			}

			/*
			         *this = rhs (copy)
			*/
			auto     operator=(_In_ const SIWork &rhs)->SIWork<Force, Distance, T> & {

				if (this == &rhs) return (*this);
				this->m_oWork.operator=(rhs.m_oWork);
				return (*this);
			}

			/*
			         *this = rhs (move)
			*/
			auto      operator=(_In_ SIWork &&rhs)->SIWork<Force, Distance, T> & {

				if (this == &rhs) return (*this);
				this->m_oWork.operator=(rhs.m_oWork);
				return (*this);
			}

			/*
			             *this += rhs
			 */
			auto      operator+=(_In_ const SIWork &rhs)->SIWork<Force, Distance, T> & {

				this->m_oWork.operator+=(rhs.m_oWork);
				return (*this);
			}

			/*
			            *this += rhs (move)
			*/
			auto       operator+=(_In_ SIWork &&rhs)->SIWork<Force, Distance, T> & {

				this->m_oWork.operator+=(std::move(rhs.m_oWork));
				return (*this);
			}

			/*
			              *this -= rhs
			*/
			auto      operator-=(_In_ const SIWork &rhs)->SIWork<Force, Distance, T> & {

				this->m_oWork.operator-=(rhs.m_oWork);
				return (*this);
			}

			/*
			               *this -= rhs
			*/
			auto       operator-=(_In_ SIWork &&rhs)->SIWork<Force, Distance, T> & {

				this->m_oWork.operator-=(std::move(rhs.m_oWork));
				return (*this);
			}




			/*
			              *this *= rhs
			*/
			auto       operator*=(_In_ const SIWork &rhs)->SIWork<Force, Distance, T> & {

				this->m_oWork.operator*=(rhs.m_oWork);
				return (*this);
			}


			/*
			               *this *= rhs (move)
			 */
			auto       operator*=(_In_ SIWork &&rhs)->SIWork<Force, Distance, T> & {

				this->m_oWork.operator*=(std::move(rhs.m_oWork));
				return (*this);
			}

			/*
			               *this /= rhs
			*/
			auto        operator/=(_In_ const SIWork &rhs)->SIWork<Force, Distance, T> & {

				this->m_oWork.operator/=(rhs.m_oWork);
				return (*this);
			}

			/*
			               *this /= rhs (move)
			*/
			auto        operator/=(_In_ SIWork &&rhs)->SIWork<Force, Distance, T> & {

				this->m_oWork.operator/=(std::move(rhs.m_oWork));
				return (*this);
			}
			
			/*
			               *this == rhs
		    */
			auto         operator==(_In_ const SIWork &rhs)->const bool {
				return (this->m_oWork.value() == rhs.m_oWork.value());
			}

			/*
			               *this == rhs (move)
			*/
			auto          operator==(_In_ SIWork &&rhs)-> const bool {
				return (std::move(this->m_oWork.value() == std::move(this->m_oWork.value())));
			}
			/*
			               *this != rhs
		    */
			auto         operator!=(_In_ const SIWork &rhs)->const bool {
				return (!(this->operator==(rhs)));
			}

			/*
			               std::cout << *this
						   
			*/
			auto     display()->const void {

				std::printf("Work = %4.16f J\n", this->m_oWork.value());
			}


		private:

			/*
			@brief    Energy(Work) class variable m_oWork
			*/
			quantity<energy, T> m_oWork;

		};

		/*
		
		             Wrapper class for boost::units::current
		       
		*/

		/*  primary template */

		template<typename T>  class SICurrent {


		public:

			/*
			@brief    Zero-current default Ctor
			*/
			SICurrent() : m_Magnitude{ static_cast<T>(0.0) }, m_oCurrent{ m_Magnitude * amperes } {}

			/*
			@brief    One-arg Ctor , constructs object of type Current.
			*/
			SICurrent(_In_ const T mag) : m_Magnitude{ mag }, m_oCurrent{ m_Magnitude * amperes } {}

			/*
			@brief    Copy-Ctor.
			*/
			SICurrent(_In_ const SICurrent &rhs) : m_Magnitude{ rhs.m_Magnitude }, m_oCurrent{ rhs.m_oCurrent } {}

			/*
			@brief    Move-Ctor
			*/
			SICurrent(_In_ SICurrent &&rhs) : m_Magnitude{ std::move(rhs.m_Magnitude) }, m_oCurrent{ std::move(rhs.m_oCurrent) } {}

			/*
			@brief    Dtor  = default.
			*/
			~SICurrent() noexcept(true) = default;


			/*

			Class member accessors and operators.

			*/

			/*
			@brief     this->m_Magnitude
			*/
			__forceinline  auto         Magnitude()->const T{

				return (this->m_Magnitude); 
			}

			/*
			@brief     this->m_oCurrent
			*/
		   __forceinline auto            Current()->const quantity<current, T> {

			  return (this->m_oCurrent);
			}

		    /*
		    @brief      *this = rhs (copy)
		    */
		   auto        operator=(_In_ const SICurrent &rhs)->SICurrent<T> {

			   if (this == &rhs) return (*this);

			   this->m_Magnitude = rhs.m_Magnitude;
			   this->m_oCurrent.operator=(rhs.m_oCurrent);
			   return (*this);
		   }

		   /*
		   @brief        *this = rhs (move)
		   */
		   auto         operator=(_In_ SICurrent &&rhs)->SICurrent<T> & {

			   if (this == &rhs) return (*this);

			   this->m_Magnitude = std::move(rhs.m_Magnitude);
			   this->m_oCurrent.operator=(std::move(rhs.m_oCurrent));
			   return (*this);
		   }

		   /*
		   @brief         *this += rhs
		   */
		   auto          operator+=(_In_ const SICurrent &rhs)->SICurrent<T> & {

			   this->m_Magnitude += rhs.m_Magnitude;
			   this->m_oCurrent.operator+=(rhs.m_oCurrent);
			   return (*this);
		   }

		   /*
		   @brief         *this += rhs (move)
		   */
		   auto           operator+=(_In_ SICurrent &&rhs)->SICurrent<T> & {

			   this->m_Magnitude += std::move(rhs.m_Magnitude);
			   this->m_oCurrent.operator+=(std::move(rhs.m_oCurrent));
			   return (*this);
		   }

		   /*
		   @brief         *this -= rhs
		   */
		   auto            operator-=(_In_ const SICurrent &rhs)->SICurrent<T> & {

			   this->m_Magnitude -= rhs.m_Magnitude;
			   this->m_oCurrent.operator-=(rhs.m_oCurrent);
			   return (*this);
		   }

		   /*
		   @brief          *this -= rhs (move)
		   */
		   auto             operator-=(_In_ SICurrent &&rhs)->SICurrent<T> & {

			   this->m_Magnitude -= std::move(rhs.m_Magnitude);
			   this->m_oCurrent.operator-=(rhs.m_oCurrent);
			   return (*this);
		   }

		   /*
		   @brief         *this *= rhs 
		   */
		   auto             operator*=(_In_ const SICurrent &rhs)->SICurrent<T> & {

			   this->m_Magnitude *= rhs.m_Magnitude;
			   this->m_oCurrent.operator*=(rhs.m_oCurrent);
			   return (*this);
		   }

		   /*
		   @brief          *this *= rhs (move)
		   */
		   auto             operator*=(_In_ SICurrent &&rhs)->SICurrent<T> & {

			   this->m_Magnitude *= std::move(rhs.m_Magnitude);
			   this->m_oCurrent.operator*=(std::move(rhs.m_oCurrent));
			   return (*this);
		   }

		   /*
		   @brief           *this /= rhs
		   */
		   auto              operator/=(_In_ const SICurrent &rhs)->SICurrent<T> & {

			   this->m_Magnitude /= rhs.m_Magnitude;
			   this->m_oCurrent.operator/=(rhs.m_oCurrent);
			   return (*this);
		   }

		   /*
		   @brief            *this /= rhs (move)
		   */
		   auto              operator/=(_In_ SICurrent &&rhs)->SICurrent<T> & {

			   this->m_Magnitude /= std::move(rhs.m_Magnitude);
			   this->m_oCurrent.operator/=(std::move(rhs.m_oCurrent));
			   return (*this);
		   }

		   /*
		   @brief              *this == rhs
		   */
		   auto              operator==(_In_ const SICurrent &rhs)->const bool {

			   return (this->m_Magnitude == rhs.m_Magnitude &&
				   this->m_oCurrent.value() == rhs.m_oCurrent.value());
		   }

		   /*
		   @brief                *this !=  rhs
		   */
		   auto              operator!=(_In_ const SICurrent &rhs)->const bool {

			   return (!(this->operator==(rhs)));
		   }

		   /*
		   @brief               operator<< , specialized only for std::complex<T> type.
		   */
		   friend  std::enable_if<std::is_class<std::complex<T>>::value,std::ostream &>::type 
			   operator<<(_In_ std::ostream &os, _In_ const SICurrent<T> &rhs) {

				       os << "Current=" << rhs.Magnitude().real() << "Re" << "+" << 
					   rhs.Magnitude().imag() << std::endl;
			   }

		   /*
		   @brief         displays the value of this->m_oCurrent in Ampere unit. Displayed value of
		                   Ampere defualted to double-precision.
		   */
		   auto         display()->void {

			   std::printf("Current=%4.16f A/n", this->m_oCurrent.value());
		   }


		private:

			/*
			@brief   quantity magnitude m_oMagnitude.
			*/
			T   m_Magnitude;

			/*
			@brief   quantity of current m_oCurrent
			*/
			quantity<current, T>  m_oCurrent;

		};

		/*

		          Wrapper class for boost::unit::quantity<resistance,T>

		*/


		template<typename T> class SIResistance {


		   public:


			   /*
			         Zero-resistance Ctor.
			   */
			   SIResistance() : m_Magnitude{ static_cast<T>(0.0) }, m_oResistance{ m_Magnitude * ohm } {}

			   /*
			         Variable-resistance Ctor.
			   */
			   SIResistance(_In_ const T &mag) : m_Magnitude{ mag }, m_oResistance{ m_Magnitude * ohm } {}

			   /*
			          Copy-Ctor.
			   */
			   SIResistance(_In_ const SIResistance &rhs) : m_Magnitude{ rhs.m_Magnitude }, m_oResistance{ rhs.m_oResistance } {}

			   /*
			           Move-Ctor.
			   */
			   SIResistance(_In_ SIResistance &&rhs) : m_Magnitude{ std::move(rhs.m_Magnitude) }, m_oResistance{ std::move(rhs.m_oResistance) } {}

			   /*
			           Dtor = default.
			   */
			   ~SIResistance() noexcept(true) = default;


			   /*

			   Accessor and member operators.

			   */

			   /*
			             Returns this->m_Magnitude
			   */
			   __forceinline auto            Magnitude()->const T{

				   return (this->m_Magnitude);
			   }

			   /*
			             Returns this->m_oResistance.
			   */
			   __forceinline  auto           Resistance()->const quantity<resistance, T> {

				   return (this->m_oResistance);
			   }

			   /*
			                 *this = rhs (copy)
			   */
			   auto            operator=(_In_ const SIResistance &rhs)->SIResistance<T> & {

				   if (this == &rhs) return (*this);

				   this->m_Magnitude = rhs.m_Magnitude;
				   this->m_oResistance.operator=(rhs.m_oResistance);
				   return (*this);
			   }

			   /*
			                  *this = rhs (move)
			   */
			   auto            operator=(_In_ SIResistance &&rhs)->SIResistance<T> & {

				   if (this == &rhs) return (*this);

				   this->m_Magnitude = std::move(rhs.m_Magnitude);
				   this->m_oResistance = std::move(rhs.m_oResistance);
				   return (*this);
			   }

			   /*
			                    *this += rhs
				*/
			   auto             operator+=(_In_ const SIResistance &rhs)->SIResistance<T> & {

				   this->m_Magnitude += rhs.m_Magnitude;
				   this->m_oResistance.operator+=(rhs.m_oResistance);
				   return (*this);
			   }

			   /*
			                     *this += rhs (move)
			   */
			   auto              operator+=(_In_ SIResistance &&rhs)->SIResistance<T> & {

				   this->m_Magnitude += std::move(rhs.m_Magnitude);
				   this->m_oResistance.operator+=(std::move(rhs.m_oResistance));
				   return (*this);
			   }

			   /*
			                      *this -= rhs
				*/
			   auto              operator-=(_In_ const SIResistance &rhs)->SIResistance<T> & {

				   this->m_Magnitude -= rhs.m_Magnitude;
				   this->m_oResistance.operator-=(rhs.m_oResistance);
				   return (*this);
			   }

			   /*
			                       *this -= rhs (move)
				*/
			   auto              operator-=(_In_ SIResistance &&rhs)->SIResistance<T> & {

				   this->m_Magnitude -= std::move(rhs.m_Magnitude);
				   this->m_oResistance.operator-=(std::move(rhs.m_oResistance));
				   return (*this);
			   }

			   /*
			                       *this *= rhs
			   */
			   auto               operator*=(_In_ const SIResistance &rhs)->SIResistance<T> & {

				   this->m_Magnitude *= rhs.m_Magnitude;
				   this->m_oResistance.operator*=(rhs.m_oResistance);
				   return (*this);
			   }

			   /*
			                        *this *= rhs  (move)
			   */
			   auto               operator*=(_In_ SIResistance &&rhs)->SIResistance<T> & {

				   this->m_Magnitude *= std::move(rhs.m_Magnitude);
				   this->m_oResistance.operator*=(std::move(rhs.m_oResistance));
				   return (*this);
			   }

			   /*
			                         *this /= rhs            
			   */
			   auto                operator/=(_In_ const SIResistance &rhs)->SIResistance<T> & {

				   this->m_Magnitude /= rhs.m_Magnitude;
				   this->m_oResistance.operator/=(rhs.m_oResistance);
				   return (*this);
			   }

			   /*
			                         *this /= rhs
				*/
			   auto                operator/=(_In_ SIResistance &&rhs)->SIResistance<T> & {

				   this->m_Magnitude /= std::move(rhs.m_Magnitude);
				   this->m_oResistance.operator/=(std::move(rhs.m_oResistance));
				   return (*this);
			   }

			   /*
			                         *this == rhs
				*/
		   private:
                
			   /*
			   @brief       magnitude of quantity<resistance,ohm>
			   */

			   T     m_Magnitude;

			   /*
			   @brief        quantity<resistance,ohm>
			   */
			   quantity<resistance, T> m_oResistance;

		};

		/*
		             mathlib::physics::SIForce namespace operators
		*/

		/*
		     c = a + b
		*/
		template<typename T> __forceinline auto operator+(_In_ const mathlib::physics::SIForce<T> &lhs,
			_In_ const mathlib::physics::SIForce<T> &rhs)->mathlib::physics::SIForce<T> {

			SIForce<T> ret_val = SIForce<T>{lhs.operator+=(rhs)};
			return (ret_val);
		}

		/*
		     c  = a * b
		*/
		template<typename T> __forceinline auto operator*(_In_ const mathlib::physics::SIForce<T> &lhs,
			_In_ const mathlib::physics::SIForce<T> &rhs)->mathlib::physics::SIForce<T> {

			SIForce<T> ret_val = SIForce<T>{lhs.operator*=(rhs)};
			return (ret_val);
		}

		/*
		     c = a - b
		*/
		template<typename T> __forceinline auto operator-(_In_ const mathlib::physics::SIForce<T> &lhs,
			_In_ const mathlib::physics::SIForce<T> &rhs)->mathlib::physics::SIForce<T> {

			SIForce<T> ret_val = SIForce<T>{lhs.operator-=(rhs)};
			return (ret_val);
		}

		/*
		     c  = a / b
		*/
		template<typename T> __forceinline auto operator/(_In_ const mathlib::physics::SIForce<T> &lhs,
			_In_ const mathlib::physics::SIForce<T> &rhs)->mathlib::physics::SIForce<T> {

			SIForce<T> ret_val = SIForce<T>{lhs.operator/=(rhs)};
			return (ret_val);
		}

		/*
		       a == b

		*/
		template<typename T> __forceinline auto operator==(_In_ const mathlib::physics::SIForce<T> &lhs,
			_In_ const mathlib::physics::SIForce<T> &rhs)->mathlib::physics::SIForce<T> {

			return (lhs.operator==(rhs));
		}

		/*
		       a !=  b
		*/
		template<typename T> __forceinline auto operator!=(_In_ const mathlib::physics::SIForce<T> &lhs,
			_In_ const mathlib::physics::SIForce<T> &rhs)->mathlib::physics::SIForce<T> {

			return (lhs.operator==(rhs));
		}


		/*
		
		                  mathlib::physics::SILength namespace operators

		*/


		/*
		      c = a + b
		*/
		template<typename T> __forceinline auto operator+(_In_  mathlib::physics::SILength<T> &lhs,
			_In_ const mathlib::physics::SILength<T> &rhs)->mathlib::physics::SILength<T> {

			SILength<T> ret_val = SILength<T>{lhs.operator+=(rhs)};
			return (ret_val);
		}



		/*
		      c =  a * b
		*/
		template<typename T> __forceinline auto operator*(_In_ const mathlib::physics::SILength<T> &lhs,
			_In_ const mathlib::physics::SILength<T> &rhs)->mathlib::physics::SILength<T> {

			SILength<T> ret_val = SILength<T>{lhs.operator*=(rhs)};
			return (ret_val);
		}


		/*
		       c = a - b
		*/
		template<typename T> __forceinline auto operator-(_In_ const mathlib::physics::SILength<T> &lhs,
			_In_ const mathlib::physics::SILength<T> &rhs)->mathlib::physics::SILength<T> {

			SILength<T> ret_val = SILength<T>{lhs.operator-=(rhs)};
			return (ret_val);
		}

		/*
		        c =  a / b
		*/
		template<typename T> __forceinline auto operator/(_In_ const mathlib::physics::SILength<T> &lhs,
			_In_ const mathlib::physics::SILength<T> &rhs)->mathlib::physics::SILength<T> {

			SILength<T> ret_val = SILength<T>{lhs.operator/=(rhs)};
			return (ret_val);
		}

		/*
		        a == b
		*/
		template<typename T> __forceinline auto operator==(_In_ const mathlib::physics::SILength<T> &lhs,
			_In_ const mathlib::physics::SILength<T> &rhs)->bool {

			return (lhs.operator==(rhs));
		}

		/*
		       a != b
		*/
		template<typename T> __forceinline auto operator!=(_In_ const mathlib::physics::SILength<T> &lhs,
			_In_ const mathlib::physics::SILength<T> &rhs)->bool {

			return (lhs.operator!=(rhs));
		}

		/*

		           mathlib::physics::SIWork namespace operators.

		*/

		/*
		         c  = lhs + rhs
		*/
		template<class Force, class Distance, typename T> __forceinline auto operator+(_In_ const mathlib::physics::SIWork<Force, Distance, T> &lhs,
			_In_ const mathlib::physics::SIWork<Force, Distance, T> &rhs)->mathlib::physics::SIWork<Force, Distance, T> {

			SIWork<Force, Distance, T> ret_val = SIWork<Force, Distance, T>{lhs.operator+=(rhs)};
			return (ret_val);
		}

		

		/*
		         c = lhs - rhs
		*/
		template<class Force, class Distance, typename T> __forceinline auto operator-(_In_ const mathlib::physics::SIWork<Force, Distance, T> &lhs,
			_In_ const mathlib::physics::SIWork<Force, Distance, T> &rhs)->mathlib::physics::SIWork<Force, Distance, T> {

			SIWork<Force, Distance, T> ret_val = SIWork<Force, Distance, T>{lhs.operator-=(rhs)};
			return (ret_val);
		}

		/*
		        c = lhs * rhs
		*/
		template<class Force, class Distance, typename T> __forceinline auto operator*(_In_ const mathlib::physics::SIWork<Force, Distance, T> &lhs,
			_In_ const mathlib::physics::SIWork<Force, Distance, T> &rhs)->mathlib::physics::SIWork<Force, Distance, T> {

			SIWork<Force, Distance, T> ret_val = SIWork<Force, Distance, T>{lhs.operator*=(rhs)};
			return (ret_val);
		}

		/*
		         c = lhs / rhs
		*/
		template<class Force, class Distance, typename T> __forceinline auto operator/(_In_ const mathlib::physics::SIWork<Force, Distance, T> &lhs,
			_In_ const mathlib::physics::SIWork<Force, Distance, T> &rhs)->mathlib::physics::SIWork<Force, Distance, T> {

			SIWork<Force, Distance, T> ret_val = SIWork<Force, Distance, T>{lhs.operator/=(rhs)};
			return (ret_val);
		}

		/*
		        lhs == rhs
		*/
		template<class Force, class Distance, typename T> __forceinline auto operator==(_In_ const mathlib::physics::SIWork<Force, Distance, T> &lhs,
			_In_ const mathlib::physics::SIWork<Force, Distance, T> &rhs)->bool {

			return (lhs.operator==(rhs));
		}

		/*
		        lhs != rhs
		*/
		template<class Force, class Distance, typename T> __forceinline auto operator!=(_In_ const mathlib::physics::SIWork<Force, Distance, T> &lhs,
			_In_ const mathlib::physics::SIWork<Force, Distance, T> &rhs)->bool {

			return (lhs.operator!=(rhs));
		}

		/*

		              mathlib::physics::SICurrent namespace operators.

		*/

		/*
		                 c = lhs + rhs
		*/
		template<typename T> __forceinline auto  operator+(_In_ const mathlib::physics::SICurrent<T> &lhs,
			_In_ const mathlib::physics::SICurrent<T> &rhs)->SICurrent<T> {

			SICurrent<T> ret_val = SICurrent<T>{lhs.operator+=(rhs)};
			return (ret_val);
		}

		/*
		                c = lhs - rhs
		*/
		template<typename T> __forceinline auto operator-(_In_ const mathlib::physics::SICurrent<T> &lhs,
			_In_ const mathlib::physics::SICurrent<T> &rhs)->SICurrent<T> {

			SICurrent<T> ret_val = SICurrent<T>{lhs.operator-=(rhs)};
			return (ret_val);
		}

		/*
		                c = lhs * rhs
		*/
		template<typename T> __forceinline auto operator*(_In_ const mathlib::physics::SICurrent<T> &lhs,
			_In_ const mathlib::physics::SICurrent<T> &rhs)->SICurrent<T> {

			SICurrent<T> ret_val = SICurrent<T>{lhs.operator*=(rhs)};
			return (ret_val);
		}

		/*
		                c =  lhs / rhs
		*/
		template<typename T> __forceinline auto operator/(_In_ const mathlib::physics::SICurrent<T> &lhs,
			_In_ const mathlib::physics::SICurrent<T> &rhs)->SICurrent<T> {

			SICurrent<T> ret_val = SICurrent<T>{lhs.operator/=(rhs)};
			return (ret_val);
		}

		/*
		                 rhs == lhs
		*/
		template<typename T> __forceinline auto operator==(_In_ const mathlib::physics::SICurrent<T> &lhs,
			_In_ const mathlib::physics::SICurrent<T> &rhs)->bool {

			return (lhs.operator==(rhs));
		}

		/*
		                 rhs != lhs
		*/
		template<typename T> __forceinline auto operator!=(_In_ const mathlib::physics::SICurrent<T> &lhs,
			_In_ const mathlib::physics::SICurrent<T> &rhs)->bool {

			return (lhs.operator!=(rhs));
		}
	}
}
#endif   /*_DIMENSIONAL_ANALYSIS_HPP_*/