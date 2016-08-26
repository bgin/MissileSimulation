#ifndef VIENNAGRID_ALGORITHM_DISTANCE_HPP
#define VIENNAGRID_ALGORITHM_DISTANCE_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <limits>

#include "viennagrid/forwards.hpp"
#include "viennagrid/topology/all.hpp"
#include "viennagrid/algorithm/norm.hpp"
#include "viennagrid/algorithm/inner_prod.hpp"
#include "viennagrid/algorithm/closest_points.hpp"

/** @file viennagrid/algorithm/distance.hpp
    @brief Computes the (Cartesian) distance between different elements.
*/


namespace viennagrid
{
  namespace detail
  {

    //
    // Distance between points
    //

    // Distance between two points:
    template <typename PointT1, typename PointT2>
    typename viennagrid::result_of::coord<PointT1>::type
    distance_impl(PointT1 const & p1,
                  PointT2 const & p2)
    {
      return norm_2(p1 - p2);
    }

    template <typename PointT1, typename PointT2>
    typename viennagrid::result_of::coord<PointT1>::type
    distance_impl( std::pair<PointT1,PointT2> const & pts)
    {
      return distance_impl(pts.first, pts.second);
    }

    template <typename PointAccessorT, typename CoordT1, typename CoordinateSystemT1, typename CoordT2, typename CoordinateSystemT2>
    CoordT1
    distance_impl(PointAccessorT const,
                  spatial_point<CoordT1, CoordinateSystemT1> const & p1,
                  spatial_point<CoordT2, CoordinateSystemT2> const & p2)
    {
      return distance_impl(p1, p2);
    }

    template <typename PointAccessorT, typename PointT, typename WrappedConfigT>
    typename viennagrid::result_of::coord<PointT>::type
    distance_impl(PointAccessorT const accessor,
                  PointT const & p1,
                  viennagrid::element<viennagrid::vertex_tag, WrappedConfigT> const & v2)
    {
      return distance_impl(p1, accessor(v2));
    }

    template <typename PointAccessorT, typename PointT, typename WrappedConfigT>
    typename viennagrid::result_of::coord<typename PointAccessorT::value_type>::type
    distance_impl(PointAccessorT const accessor,
                  viennagrid::element<viennagrid::vertex_tag, WrappedConfigT> const & v1,
                  PointT const & p2)
    {
      return distance_impl(accessor(v1), p2);
    }

    // Distance between vertices: Use point distance
    template <typename PointAccessorT, typename PointT, typename WrappedConfigT1, typename WrappedConfigT2>
    typename viennagrid::result_of::coord<typename PointAccessorT::value_type>::type
    distance_impl(PointAccessorT const accessor,
                  viennagrid::element<viennagrid::vertex_tag, WrappedConfigT1> const & v1,
                  viennagrid::element<viennagrid::vertex_tag, WrappedConfigT2> const & v2)
    {
      return distance_impl(accessor(v1), accessor(v2));
    }



    //
    // Generic distance computation: Reuse closest_points()
    //
    template <typename PointAccessorT, typename SomethingT1, typename SomethingT2>
    typename viennagrid::result_of::coord<typename PointAccessorT::value_type>::type
    distance_impl(PointAccessorT const accessor,
                  SomethingT1 const & el1,
                  SomethingT2 const & el2)
    {
      //typedef typename result_of::point<ElementType1>::type   PointT;
      typedef typename PointAccessorT::value_type PointT;

      std::pair<PointT, PointT> points = closest_points(accessor, el1, el2);

      return distance_impl( points );
    }



    ////////////////////////////////// boundary distance //////////////////////////////////////


    template <typename PointT1, typename PointT2>
    typename viennagrid::result_of::coord<PointT1>::type
    boundary_distance_impl(PointT1 const & p1,
                  PointT2 const & p2)
    {
      return norm_2(p1 - p2);
    }

    template <typename PointT1, typename PointT2>
    typename viennagrid::result_of::coord<PointT1>::type
    boundary_distance_impl( std::pair<PointT1,PointT2> const & pts)
    {
      return boundary_distance_impl(pts.first, pts.second);
    }

    template <typename PointAccessorT, typename CoordT1, typename CoordinateSystemT1, typename CoordT2, typename CoordinateSystemT2>
    CoordT1
    boundary_distance_impl(PointAccessorT const,
                  spatial_point<CoordT1, CoordinateSystemT1> const & p1,
                  spatial_point<CoordT2, CoordinateSystemT2> const & p2)
    {
      return boundary_distance_impl(p1, p2);
    }

    template <typename PointAccessorT, typename PointT, typename WrappedConfigT>
    typename viennagrid::result_of::coord<PointT>::type
    boundary_distance_impl(PointAccessorT const accessor,
                  PointT const & p1,
                  viennagrid::element<viennagrid::vertex_tag, WrappedConfigT> const & v2)
    {
      return boundary_distance_impl(p1, accessor(v2));
    }

    template <typename PointAccessorT, typename PointT, typename WrappedConfigT>
    typename viennagrid::result_of::coord<typename PointAccessorT::value_type>::type
    boundary_distance_impl(PointAccessorT const accessor,
                  viennagrid::element<viennagrid::vertex_tag, WrappedConfigT> const & v1,
                  PointT const & p2)
    {
      return boundary_distance_impl(accessor(v1), p2);
    }

    // Distance between vertices: Use point distance
    template <typename PointAccessorT, typename PointT, typename WrappedConfigT1, typename WrappedConfigT2>
    typename viennagrid::result_of::coord<typename PointAccessorT::value_type>::type
    boundary_distance_impl(PointAccessorT const accessor,
                  viennagrid::element<viennagrid::vertex_tag, WrappedConfigT1> const & v1,
                  viennagrid::element<viennagrid::vertex_tag, WrappedConfigT2> const & v2)
    {
      return boundary_distance_impl(accessor(v1), accessor(v2));
    }



    //
    // Generic distance computation: Reuse closest_points()
    //
    template <typename PointAccessorT, typename SomethingT1, typename SomethingT2>
    typename viennagrid::result_of::coord<typename PointAccessorT::value_type>::type
    boundary_distance_impl(PointAccessorT const accessor,
                           SomethingT1 const & el1,
                           SomethingT2 const & el2)
    {
      //typedef typename result_of::point<ElementType1>::type      PointT;
      typedef typename PointAccessorT::value_type PointT;

      std::pair<PointT, PointT> points = closest_points_on_boundary(accessor, el1, el2);

      return boundary_distance_impl(points);
    }

  } //namespace detail

  //
  // The public interface functions
  //
  /** @brief Returns the distance between elements, segments and/or meshs using the point accessor provided */
  template <typename PointAccessorT, typename SomethingT1, typename SomethingT2>
  typename viennagrid::result_of::coord<SomethingT1>::type
  distance(PointAccessorT const accessor,
           SomethingT1 const & el1,
           SomethingT2 const & el2)
  {
    return detail::distance_impl(accessor, el1, el2);
  }


  /** @brief Returns the distance between elements, segments and/or meshs using the default point accessor*/
  template <typename SomethingT1, typename SomethingT2>
  typename viennagrid::result_of::coord<SomethingT1>::type
  distance(SomethingT1 const & el1,
           SomethingT2 const & el2)
  {
    return detail::distance_impl( default_point_accessor(el1), el1, el2 );
  }

  /** @brief Returns the distance between a point and an element/segment/meshs using the default point accessor*/
  template <typename SomethingT, typename CoordT, typename CoordinateSystemT>
  typename viennagrid::result_of::coord<SomethingT>::type
  distance(SomethingT const & el1,
           spatial_point<CoordT, CoordinateSystemT> const & el2)
  {
    return detail::distance_impl( default_point_accessor(el1), el1, el2 );
  }

  /** @brief Returns the distance between a point and an element/segment/meshs using the default point accessor*/
  template <typename CoordT, typename CoordinateSystemT, typename SomethingT>
  typename viennagrid::result_of::coord<SomethingT>::type
  distance(spatial_point<CoordT, CoordinateSystemT> const & el1,
           SomethingT const & el2)
  {
    return detail::distance_impl( default_point_accessor(el2), el1, el2 );
  }

  /** @brief Returns the Euclidian distance between two points */
  template <typename CoordT1, typename CoordinateSystemT1, typename CoordT2, typename CoordinateSystemT2>
  typename viennagrid::result_of::coord< spatial_point<CoordT1, CoordinateSystemT1> >::type
  distance(spatial_point<CoordT1, CoordinateSystemT1> const & el1,
           spatial_point<CoordT2, CoordinateSystemT2> const & el2)
  {
    return detail::distance_impl( el1, el2 );
  }


  /** @brief Returns the Euclidian distance between the boundary of a segment and a line */
  template<typename WrappedMeshConfigT, typename SegmentationT>
  typename result_of::coord< segment_handle<SegmentationT> >::type distance( element<line_tag, WrappedMeshConfigT> const & line, segment_handle<SegmentationT> const & segment_handle )
  {
    typedef viennagrid::segment_handle<SegmentationT> SegmentHandleType;
    typedef typename result_of::const_line_range<SegmentHandleType>::type ConstLineRangeType;
    typedef typename result_of::iterator<ConstLineRangeType>::type ConstLineIteratorType;

    typedef typename result_of::coord<SegmentHandleType>::type CoordType;

    ConstLineRangeType lines(segment_handle);
    if (lines.empty())
      return -1;

    ConstLineIteratorType lit = lines.begin();
    CoordType min_distance = distance(line, *(lit++));

    for (; lit != lines.end(); ++lit)
    {
      CoordType current_distance = distance(line, *lit);
      if (current_distance < min_distance)
        min_distance = current_distance;
    }

    return min_distance;
  }

  template<typename SegmentationT, typename WrappedMeshConfigT>
  typename result_of::coord< segment_handle<SegmentationT> >::type distance( segment_handle<SegmentationT> const & segment_handle, element<line_tag, WrappedMeshConfigT> const & line )
  {
    return distance( line, segment_handle );
  }





  /** @brief Returns the distance between elements, segments and/or meshs
    *
    * @param accessor     Accessor functor for obtaining a point from a vertex
    * @param el1          The first element/mesh/vertex
    * @param el2          The second element/mesh/vertex
    */
  template <typename PointAccessorT, typename SomethingT1, typename SomethingT2>
  typename viennagrid::result_of::coord<SomethingT1>::type
  boundary_distance(PointAccessorT const accessor,
                    SomethingT1 const & el1,
                    SomethingT2 const & el2)
  {
    return detail::boundary_distance_impl(accessor, el1, el2);
  }

  /** @brief Returns the distance between elements, segments and/or meshs */
  template <typename SomethingT1, typename SomethingT2>
  typename viennagrid::result_of::coord<SomethingT1>::type
  boundary_distance(SomethingT1 const & el1,
                    SomethingT2 const & el2)
  {
    return detail::boundary_distance_impl( default_point_accessor(el1), el1, el2 );
  }

  /** @brief Returns the distance between a point and an element, segment and/or mesh */
  template <typename SomethingT, typename CoordT, typename CoordinateSystemT>
  typename viennagrid::result_of::coord<SomethingT>::type
  boundary_distance(SomethingT const & el1,
                    spatial_point<CoordT, CoordinateSystemT> const & el2)
  {
    return detail::boundary_distance_impl( default_point_accessor(el1), el1, el2 );
  }

  /** @brief Returns the distance between a point and an element, segment and/or mesh */
  template <typename CoordT, typename CoordinateSystemT, typename SomethingT>
  typename viennagrid::result_of::coord<SomethingT>::type
  boundary_distance(spatial_point<CoordT, CoordinateSystemT> const & el1,
                    SomethingT const & el2)
  {
    return detail::boundary_distance_impl( default_point_accessor(el2), el1, el2 );
  }


} //namespace viennagrid
#endif
