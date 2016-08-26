#ifndef VIENNAGRID_DETAIL_ELEMENT_ORIENTATION_HPP
#define VIENNAGRID_DETAIL_ELEMENT_ORIENTATION_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */


#include <vector>
#include <iostream>

#include "viennagrid/forwards.hpp"

/** @file viennagrid/element/element_orientation.hpp
    @brief Provides an orienter for boundary k-cells of a n-cell
*/

namespace viennagrid
{
  namespace result_of
  {
    /** @brief  Returns the internal type used for element permutations from global to local ordering */
    template<int num_elements>
    struct permutator_type
    {
      typedef typename permutator_type<num_elements+1>::type type;
    };

    /** \cond */
    template<>
    struct permutator_type<16>  //shortcut for not instantiating too many template specializations
    {
      typedef unsigned char type;
    };

    template<>
    struct permutator_type<256>
    {
      typedef unsigned char type;
    };

    template<>
    struct permutator_type<65536>
    {
      typedef unsigned short type;
    };
    /** \endcond */
  }



  /************** Level 1: Elements contained by a higher-level element *******/

  /** @brief A permutator for mapping local orientations to global vertices of a boundary k-cell
   *
   * Local vertex numbering is in general different from global vertex numbering for lower-level topological elements
   * this permutator maps local numbers to global numbers
   * alternative implementation: vertexnum as template parameter
   */
    template <typename container_type>
    class element_orientation : public container_type
    {
      typedef typename container_type::value_type  permutator_type;
      typedef typename container_type::size_type   size_type;

    public:
      void setDefaultOrientation()
      {
        unsigned int index = 0;
        for (typename container_type::iterator it = container_type::begin(); it != container_type::end(); ++it, ++index)
          *it = static_cast<permutator_type>(index);
      }

      size_type operator()(size_type in) const { return static_cast<size_type>( (*this)[in] ); }

      void setPermutation(size_type index, size_type mappedTo) { (*this)[index] = static_cast<permutator_type>(mappedTo); }

      void print() const
      {
        unsigned int index = 0;
        for (typename container_type::const_iterator it = container_type::begin(); it != container_type::end(); ++it, ++index)
          std::cout << index << "->" << *it << ",";
        std::cout << std::endl;
      }
    };

}


#endif

