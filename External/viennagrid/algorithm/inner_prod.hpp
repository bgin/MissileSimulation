#ifndef VIENNAGRID_ALGORITHM_INNERPROD_HPP
#define VIENNAGRID_ALGORITHM_INNERPROD_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include "viennagrid/forwards.hpp"
#include "viennagrid/point.hpp"

/** @file viennagrid/algorithm/inner_prod.hpp
    @brief Computes the inner product of vectors
*/

namespace viennagrid
{

  namespace detail
  {
    template <typename PointT,
              long dim = viennagrid::result_of::dimension<PointT>::value>
    struct inner_prod_impl;

    //
    // 1d
    //
    /** @brief Implementation of the inner product in one dimension */
    template <typename PointT>
    struct inner_prod_impl<PointT, 1>
    {
      typedef typename viennagrid::result_of::coord<PointT>::type    value_type;

      template <typename PointT2>
      static value_type apply(PointT const & p1,
                              PointT2 const & p2)
      {
        return p1[0] * p2[0];
      }
    };

    //
    // 2d
    //
    /** @brief Implementation of the inner product in two dimensions */
    template <typename PointT>
    struct inner_prod_impl<PointT, 2>
    {
      typedef typename viennagrid::result_of::coord<PointT>::type    value_type;

      template <typename PointT2>
      static value_type apply(PointT const & p1,
                              PointT2 const & p2)
      {
        return p1[0] * p2[0] + p1[1] * p2[1];
      }
    };

    //
    // 3d
    //
    /** @brief Implementation of the inner product in three dimensions */
    template <typename PointT>
    struct inner_prod_impl<PointT, 3>
    {
      typedef typename viennagrid::result_of::coord<PointT>::type    value_type;

      template <typename PointT2>
      static value_type apply(PointT const & p1,
                              PointT2 const & p2)
      {
        return p1[0] * p2[0] + p1[1] * p2[1] + p1[2] * p2[2];
      }
    };
  }

  /** @brief Dispatched inner product function having full information about the coordinate systems. Transforms to Cartesian coordinates and forwards the calculation to the worker */
  template<typename PointT1, typename PointT2, typename CoordinateSystemT1, typename CoordinateSystemT2>
  typename viennagrid::result_of::coord<PointT1>::type
  inner_prod_impl(PointT1 const & p1, PointT2 const & p2, CoordinateSystemT1 const &, CoordinateSystemT2 const &)
  {
    typedef typename result_of::cartesian_point<PointT1>::type   CartesianPoint1;

    return detail::inner_prod_impl<CartesianPoint1>::apply(to_cartesian(p1), to_cartesian(p2));
  }

  /** @brief Dispatched inner product function having full information about the coordinate systems. Vectors/Points are in a Cartesian coordinate system already, thus no transformation required. */
  template<typename PointT1, typename PointT2, int d>
  typename viennagrid::result_of::coord<PointT1>::type
  inner_prod_impl(PointT1 const & p1, PointT2 const & p2, cartesian_cs<d>, cartesian_cs<d>)
  {
    return detail::inner_prod_impl<PointT1>::apply(p1, p2);
  }

  /** @brief Returns the inner product of two vectors, which can be given in different coordinate systems
   *
   * @param p1   First vector
   * @param p2   Second vector
   */
  template<typename PointT1, typename PointT2>
  typename viennagrid::result_of::coord<PointT1>::type
  inner_prod(PointT1 const & p1, PointT2 const & p2)
  {
    return inner_prod_impl(p1,
                           p2,
                           typename result_of::coordinate_system<PointT1>::type(),
                           typename result_of::coordinate_system<PointT2>::type());
  }

}

#endif
