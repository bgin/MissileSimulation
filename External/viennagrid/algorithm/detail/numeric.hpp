#ifndef VIENNAGRID_ALGORITHM_NUMERIC_HPP
#define VIENNAGRID_ALGORITHM_NUMERIC_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include <algorithm>
#include <cmath>

/** @file viennagrid/algorithm/detail/numeric.hpp
    @brief Helper routines controlling numeric tolerances
*/

namespace viennagrid
{
  namespace detail
  {
    namespace result_of
    {
      template<typename NumericConfigT, typename OuterNumericT>
      struct numeric_type
      {
        typedef typename NumericConfigT::numeric_type type;
      };

      template<typename OuterNumericT>
      struct numeric_type<double, OuterNumericT>
      {
        typedef double type;
      };
    }

    template<typename OuterNumericT, typename NumericConfigT>
    typename result_of::numeric_type<NumericConfigT, OuterNumericT>::type absolute_tolerance( NumericConfigT config )
    {
      typedef typename result_of::numeric_type<NumericConfigT, OuterNumericT>::type numeric_type;
      return static_cast<numeric_type>(config.eps);
    }

    template<typename OuterNumericT, typename NumericConfigT>
    typename result_of::numeric_type<NumericConfigT, OuterNumericT>::type relative_tolerance( NumericConfigT config, OuterNumericT base )
    {
      typedef typename result_of::numeric_type<NumericConfigT, OuterNumericT>::type numeric_type;
      return std::max( static_cast<numeric_type>(config.eps) * static_cast<numeric_type>(base), absolute_tolerance<OuterNumericT>(config) );
    }

    template<typename OuterNumericT>
    typename result_of::numeric_type<double, OuterNumericT>::type absolute_tolerance( double eps )
    {
      typedef typename result_of::numeric_type<double, OuterNumericT>::type numeric_type;
      return std::abs(static_cast<numeric_type>(eps));
    }

    template<typename OuterNumericT>
    typename result_of::numeric_type<double, OuterNumericT>::type relative_tolerance( double eps, OuterNumericT base )
    {
      typedef typename result_of::numeric_type<double, OuterNumericT>::type numeric_type;
//       return static_cast<numeric_type>(eps) * base;
      return std::max( static_cast<numeric_type>(eps) * base, absolute_tolerance<OuterNumericT>(eps) );
    }


    template<typename NumericConfigT, typename NumericT>
    bool is_equal( NumericConfigT nc, NumericT first, NumericT second )
    {
      return (std::abs(first-second) < relative_tolerance(nc, first));
    }

    template<typename NumericConfigT, typename NumericT>
    bool is_not_equal( NumericConfigT nc, NumericT first, NumericT second )
    {
      return !is_equal(nc, first, second);
    }

  }

}

#endif

