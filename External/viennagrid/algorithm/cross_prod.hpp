#ifndef VIENNAGRID_ALGORITHM_CROSS_PROD_HPP
#define VIENNAGRID_ALGORITHM_CROSS_PROD_HPP

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

/** @file viennagrid/algorithm/cross_prod.hpp
    @brief Computes the cross product of vectors
*/

namespace viennagrid
{

  namespace detail
  {
    /** @brief Implementation of the cross product calculation */
    template <typename PointT,
              long dim = viennagrid::result_of::dimension<PointT>::value>
    struct cross_prod_impl;


    //for compatibility in 1d:
    /** @brief Implementation of the cross product calculation in 1d for compatibility. Returns the zero-vector. */
    template <typename PointT>
    struct cross_prod_impl<PointT, 1>
    {
      static PointT apply(PointT const &,
                            PointT const &)
      {
        return PointT(0);
      }
    };

    //for compatibility in 2d:
    /** @brief Implementation of the cross product calculation in 2d for compatibility. Returns the zero-vector. */
    template <typename PointT>
    struct cross_prod_impl<PointT, 2>
    {
      static PointT apply(PointT,
                            PointT)
      {
        return PointT(0,0);
      }
    };

    /** @brief Implementation of the cross product calculation in 3d. */
    template <typename PointT>
    struct cross_prod_impl<PointT, 3>
    {
      static PointT apply(PointT const & p1,
                            PointT const & p2)
      {
        return PointT(p1[1]*p2[2]-p1[2]*p2[1],
                        p1[2]*p2[0]-p1[0]*p2[2],
                        p1[0]*p2[1]-p1[1]*p2[0]);
      }
    };
  }

  /** @brief Dispatched cross product function having information about the coordinate systems. Transforms to Cartesian coordinates and forwards to calculation */
  template<typename PointT1, typename PointT2, typename CSystem1, typename CSystem2>
  PointT1
  cross_prod_impl(PointT1 const & p1, PointT2 const & p2, CSystem1 const &, CSystem2 const &)
  {
    typedef typename result_of::cartesian_point<PointT1>::type   CartesianPoint1;

    return detail::cross_prod_impl<CartesianPoint1>::apply(to_cartesian(p1), to_cartesian(p2));
  }

  /** @brief Dispatched cross product function having information about the coordinate systems. Points are already in Cartesian coordinates, thus forwarding to the worker function directly. */
  template<typename PointT1, typename PointT2, int d>
  PointT1
  cross_prod_impl(PointT1 const & p1, PointT2 const & p2, cartesian_cs<d>, cartesian_cs<d>)
  {
    return detail::cross_prod_impl<PointT1>::apply(p1, p2);
  }

  /** @brief Returns the cross product of two vectors. If the vectors have one or two components only, the zero vector is returned.
   *
   * @param v1    The first vector given in some coordinate system
   * @param v2    The second vector given in another coordinate system
   */
  template<typename PointT1, typename PointT2>
  PointT1
  cross_prod(PointT1 const& v1, PointT2 const& v2)
  {
    return cross_prod_impl(v1,
                           v2,
                           typename result_of::coordinate_system<PointT1>::type(),
                           typename result_of::coordinate_system<PointT2>::type());
  }

}

#endif
