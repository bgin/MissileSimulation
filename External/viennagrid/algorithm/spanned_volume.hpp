#ifndef VIENNAGRID_ALGORITHM_SPANNED_VOLUME_HPP
#define VIENNAGRID_ALGORITHM_SPANNED_VOLUME_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */



//#include <math.h>
#include "viennagrid/forwards.hpp"
#include "viennagrid/algorithm/cross_prod.hpp"
#include "viennagrid/algorithm/norm.hpp"
#include "viennagrid/algorithm/inner_prod.hpp"


/** @file viennagrid/algorithm/spanned_volume.hpp
    @brief Computes the volume of n-simplices spanned by points
*/

namespace viennagrid
{

  namespace detail
  {
    template <typename PointT, int DimV = viennagrid::result_of::dimension<PointT>::value>
    struct signed_spanned_volume_impl;


    /** @brief Implementation of the volume spanned by two points in one dimension */
    template <typename PointT>
    struct signed_spanned_volume_impl<PointT, 1>
    {
      typedef typename viennagrid::result_of::coord<PointT>::type    value_type;

      static value_type apply(PointT const & p1,
                              PointT const & p2)
      {
        return p2[0] - p1[0];
      }
    };

    //in 2d:
    /** @brief Implementation of the volume of simplices spanned by points in two geometrical dimension */
    template <typename PointT>
    struct signed_spanned_volume_impl<PointT, 2>
    {
      typedef typename viennagrid::result_of::coord<PointT>::type    value_type;

      static value_type apply(PointT const & p1,
                              PointT const & p2)
      {
        //a line
        return sqrt(   (p2[0] - p1[0]) * (p2[0] - p1[0])
                     + (p2[1] - p1[1]) * (p2[1] - p1[1])  );
      }

      static value_type apply(PointT const & A,
                              PointT const & B,
                              PointT const & C)
      {
        //a triangle:
        return (  A[0] * (B[1] - C[1])
                    + B[0] * (C[1] - A[1])
                    + C[0] * (A[1] - B[1]) ) / 2.0;
      }

    };


    /** @brief Implementation of the volume of simplices spanned by points in three geometrical dimension */
    template <typename PointT>
    struct signed_spanned_volume_impl<PointT, 3>
    {
      typedef typename viennagrid::result_of::coord<PointT>::type    value_type;

      static value_type apply(PointT const & p1,
                              PointT const & p2)
      {
        //a line
        return sqrt(   (p2[0] - p1[0]) * (p2[0] - p1[0])
                     + (p2[1] - p1[1]) * (p2[1] - p1[1])
                     + (p2[2] - p1[2]) * (p2[2] - p1[2]) );
      }

      static value_type apply(PointT const & p1,
                              PointT const & p2,
                              PointT const & p3)
      {
        PointT v1 = p2 - p1;
        PointT v2 = p3 - p1;

        PointT v3 = cross_prod(v1, v2);

        return norm(v3) / 2.0;
      }

      static value_type apply(PointT const & p1,
                              PointT const & p2,
                              PointT const & p3,
                              PointT const & p4)
      {
        PointT v1 = p2 - p1;
        PointT v2 = p3 - p1;
        PointT v3 = p4 - p1;

        return (inner_prod(v1, cross_prod(v2, v3)) ) / 6.0;
      }

    };
  } //namespace detail






  //
  // Mixed coordinate systems:
  //
  /** @brief Dispatch facility for two points with possibly different coordinate systems */
  template<typename PointT1, typename PointT2, typename CoordinateSystemT1, typename CoordinateSystemT2>
  typename viennagrid::result_of::coord<PointT1>::type
  signed_spanned_volume_impl(PointT1 const & p1,
                      PointT2 const & p2,
                      CoordinateSystemT1 const &,
                      CoordinateSystemT2 const &)
  {
    typedef typename result_of::cartesian_point<PointT1>::type   CartesianPoint1;

    return detail::signed_spanned_volume_impl<CartesianPoint1>::apply(to_cartesian(p1), to_cartesian(p2));
  }

  /** @brief Dispatch facility for three points with possibly different coordinate systems */
  template<typename PointT1, typename PointT2, typename PointT3,
           typename CoordinateSystemT1, typename CoordinateSystemT2, typename CoordinateSystemT3>
  typename viennagrid::result_of::coord<PointT1>::type
  signed_spanned_volume_impl(PointT1 const & p1,
                      PointT2 const & p2,
                      PointT3 const & p3,
                      CoordinateSystemT1 const &,
                      CoordinateSystemT2 const &,
                      CoordinateSystemT3 const &)
  {
    typedef typename result_of::cartesian_point<PointT1>::type   CartesianPoint1;

    return detail::signed_spanned_volume_impl<CartesianPoint1>::apply(to_cartesian(p1), to_cartesian(p2), to_cartesian(p3));
  }

  /** @brief Dispatch facility for four points with possibly different coordinate systems */
  template<typename PointT1, typename PointT2, typename PointT3, typename PointT4,
           typename CoordinateSystemT1, typename CoordinateSystemT2, typename CoordinateSystemT3, typename CoordinateSystemT4>
  typename viennagrid::result_of::coord<PointT1>::type
  signed_spanned_volume_impl(PointT1 const & p1,
                      PointT2 const & p2,
                      PointT3 const & p3,
                      PointT4 const & p4,
                      CoordinateSystemT1 const &,
                      CoordinateSystemT2 const &,
                      CoordinateSystemT3 const &,
                      CoordinateSystemT4 const &)
  {
    typedef typename result_of::cartesian_point<PointT1>::type   CartesianPoint1;

    return detail::signed_spanned_volume_impl<CartesianPoint1>::apply(to_cartesian(p1), to_cartesian(p2), to_cartesian(p3), to_cartesian(p4));
  }

  //
  // All Cartesian:
  //
  /** @brief Dispatch facility for two points in Cartesian coordinates */
  template<typename PointT1, typename PointT2, int DimV>
  typename viennagrid::result_of::coord<PointT1>::type
  signed_spanned_volume_impl(PointT1 const & p1,
                      PointT2 const & p2,
                      cartesian_cs<DimV>,
                      cartesian_cs<DimV>)
  {
    return detail::signed_spanned_volume_impl<PointT1>::apply(p1, p2);
  }

  /** @brief Dispatch facility for three points in Cartesian coordinates */
  template <typename PointT1, typename PointT2, typename PointT3, int DimV>
  typename viennagrid::result_of::coord<PointT1>::type
  signed_spanned_volume_impl(PointT1 const & p1,
                      PointT2 const & p2,
                      PointT3 const & p3,
                      cartesian_cs<DimV>,
                      cartesian_cs<DimV>,
                      cartesian_cs<DimV>)
  {
    return detail::signed_spanned_volume_impl<PointT1>::apply(p1, p2, p3);
  }

  /** @brief Dispatch facility for four points in Cartesian coordinates */
  template <typename PointT1, typename PointT2, typename PointT3, typename PointT4, int DimV>
  typename viennagrid::result_of::coord<PointT1>::type
  signed_spanned_volume_impl(PointT1 const & p1,
                      PointT2 const & p2,
                      PointT3 const & p3,
                      PointT4 const & p4,
                      cartesian_cs<DimV>,
                      cartesian_cs<DimV>,
                      cartesian_cs<DimV>,
                      cartesian_cs<DimV>)
  {
    return detail::signed_spanned_volume_impl<PointT1>::apply(p1, p2, p3, p4);
  }



  //
  // public interface
  //
  /** @brief Returns the volume of the 1-simplex (line) spanned by the two points */
  template <typename PointT1, typename PointT2>
  typename viennagrid::result_of::coord<PointT1>::type
  signed_spanned_volume(PointT1 const & p1, PointT2 const & p2)
  {
    return signed_spanned_volume_impl(p1,
                               p2,
                               typename viennagrid::result_of::coordinate_system<PointT1>::type(),
                               typename viennagrid::result_of::coordinate_system<PointT2>::type());
  }


  /** @brief Returns the two-dimensional volume of the 2-simplex (triangle) spanned by the three points */
  template <typename PointT1, typename PointT2, typename PointT3>
  typename viennagrid::result_of::coord<PointT1>::type
  signed_spanned_volume(PointT1 const & p1, PointT2 const & p2, PointT3 const & p3)
  {
    return signed_spanned_volume_impl(p1,
                               p2,
                               p3,
                               typename viennagrid::result_of::coordinate_system<PointT1>::type(),
                               typename viennagrid::result_of::coordinate_system<PointT2>::type(),
                               typename viennagrid::result_of::coordinate_system<PointT3>::type()
                              );

  }


  /** @brief Returns the three-dimensional volume of the 3-simplex (tetrahedron) spanned by the four points */
  template <typename PointT1, typename PointT2, typename PointT3, typename PointT4>
  typename viennagrid::result_of::coord<PointT1>::type
  signed_spanned_volume(PointT1 const & p1,
                  PointT2 const & p2,
                  PointT3 const & p3,
                  PointT4 const & p4)
  {
    return signed_spanned_volume_impl(p1,
                               p2,
                               p3,
                               p4,
                               typename viennagrid::result_of::coordinate_system<PointT1>::type(),
                               typename viennagrid::result_of::coordinate_system<PointT2>::type(),
                               typename viennagrid::result_of::coordinate_system<PointT3>::type(),
                               typename viennagrid::result_of::coordinate_system<PointT4>::type()
                              );
  }


  /** @brief Returns the volume of the 1-simplex (line) spanned by the two points */
  template <typename PointT1, typename PointT2>
  typename viennagrid::result_of::coord<PointT1>::type
  spanned_volume(PointT1 const & p1, PointT2 const & p2)
  {
    return std::abs(signed_spanned_volume(p1, p2));
  }


  /** @brief Returns the two-dimensional volume of the 2-simplex (triangle) spanned by the three points */
  template <typename PointT1, typename PointT2, typename PointT3>
  typename viennagrid::result_of::coord<PointT1>::type
  spanned_volume(PointT1 const & p1, PointT2 const & p2, PointT3 const & p3)
  {
    return std::abs(signed_spanned_volume(p1, p2, p3));
  }


  /** @brief Returns the three-dimensional volume of the 3-simplex (tetrahedron) spanned by the four points */
  template <typename PointT1, typename PointT2, typename PointT3, typename PointT4>
  typename viennagrid::result_of::coord<PointT1>::type
  spanned_volume(PointT1 const & p1,
                  PointT2 const & p2,
                  PointT3 const & p3,
                  PointT4 const & p4)
  {
    return std::abs(signed_spanned_volume(p1, p2, p3, p4));
  }

}
#endif
