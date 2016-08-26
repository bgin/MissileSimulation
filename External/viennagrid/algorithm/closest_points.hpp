#ifndef VIENNAGRID_ALGORITHM_CLOSEST_POINTS_HPP
#define VIENNAGRID_ALGORITHM_CLOSEST_POINTS_HPP

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
#include <utility>

#include "viennagrid/forwards.hpp"
#include "viennagrid/topology/all.hpp"
#include "viennagrid/algorithm/norm.hpp"
#include "viennagrid/algorithm/inner_prod.hpp"
#include "viennagrid/algorithm/boundary.hpp"
#include "viennagrid/mesh/mesh.hpp"

/** @file viennagrid/algorithm/closest_points.hpp
    @brief Routines for computing the two points of two different objects being closest to each other.
*/


namespace viennagrid
{
  namespace detail
  {

    template <typename CoordT, typename CoordinateSystemT>
    std::pair<spatial_point<CoordT, CoordinateSystemT>,
              spatial_point<CoordT, CoordinateSystemT> > const &
    point_pair_with_shortest_distance( std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_1,
                                       std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_2)
    {
      if ( norm_2(pair_1.first - pair_1.second) <= norm_2(pair_2.first - pair_2.second) )
        return pair_1;

      return pair_2;
    }

    template <typename CoordT, typename CoordinateSystemT>
    std::pair<spatial_point<CoordT, CoordinateSystemT>,
              spatial_point<CoordT, CoordinateSystemT> > const &
    point_pair_with_shortest_distance( std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_1,
                                       std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_2,
                                       std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_3)
    {
      CoordT dist_pair_1 = norm_2(pair_1.first - pair_1.second);
      CoordT dist_pair_2 = norm_2(pair_2.first - pair_2.second);
      CoordT dist_pair_3 = norm_2(pair_3.first - pair_3.second);

      if (   (dist_pair_1 <= dist_pair_2)
          && (dist_pair_1 <= dist_pair_3) )
        return pair_1;

      if (   (dist_pair_2 <= dist_pair_1)
          && (dist_pair_2 <= dist_pair_3) )
        return pair_2;

      return pair_3;
    }


    template <typename CoordT, typename CoordinateSystemT>
    std::pair<spatial_point<CoordT, CoordinateSystemT>,
              spatial_point<CoordT, CoordinateSystemT> > const &
    point_pair_with_shortest_distance( std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_1,
                                       std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_2,
                                       std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_3,
                                       std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_4)
    {
      // Note: Recursive use of point_pair_with_shortest_distance() has a bit of overhead. Feel free to improve this
      return point_pair_with_shortest_distance(point_pair_with_shortest_distance(pair_1, pair_2),
                                               point_pair_with_shortest_distance(pair_3, pair_4));
    }

    template <typename CoordT, typename CoordinateSystemT>
    std::pair<spatial_point<CoordT, CoordinateSystemT>,
              spatial_point<CoordT, CoordinateSystemT> > const &
    point_pair_with_shortest_distance( std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_1,
                                       std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_2,
                                       std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_3,
                                       std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_4,
                                       std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_5)
    {
      // Note: Recursive use of point_pair_with_shortest_distance() has a bit of overhead. Feel free to improve this
      return point_pair_with_shortest_distance(point_pair_with_shortest_distance(pair_1, pair_2, pair_3),
                                               point_pair_with_shortest_distance(pair_4, pair_5));
    }

    template <typename CoordT, typename CoordinateSystemT>
    std::pair<spatial_point<CoordT, CoordinateSystemT>,
              spatial_point<CoordT, CoordinateSystemT> > const &
    point_pair_with_shortest_distance( std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_1,
                                       std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_2,
                                       std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_3,
                                       std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_4,
                                       std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_5,
                                       std::pair<spatial_point<CoordT, CoordinateSystemT>,
                                                 spatial_point<CoordT, CoordinateSystemT> > const & pair_6)
    {
      // Note: Recursive use of point_pair_with_shortest_distance() has a bit of overhead. Feel free to improve this
      return point_pair_with_shortest_distance(point_pair_with_shortest_distance(pair_1, pair_2, pair_3),
                                               point_pair_with_shortest_distance(pair_4, pair_5, pair_6));
    }


    //
    // Closest points between points (trivial)
    //

    // Closest points between two points:
    template <typename PointT>
    std::pair<PointT, PointT>
    closest_points_impl(PointT const & p1,
                        PointT const & p2)
    {
      return std::make_pair(p1, p2);
    }

    template <typename PointAccessorT, typename CoordT1, typename CoordinateSystemT1, typename CoordT2, typename CoordinateSystemT2>
    std::pair< spatial_point<CoordT1, CoordinateSystemT1>, spatial_point<CoordT2, CoordinateSystemT2> >
    closest_points_impl(PointAccessorT const,
                        spatial_point<CoordT1, CoordinateSystemT1> const & p1,
                        spatial_point<CoordT2, CoordinateSystemT2> const & p2)
    {
      return closest_points_impl(p1, p2);
    }

    template <typename PointAccessorT, typename PointT, typename WrappedConfigT>
    std::pair<PointT, typename viennagrid::result_of::point<viennagrid::element< vertex_tag,WrappedConfigT> >::type>
    closest_points_impl(PointAccessorT const accessor,
                        PointT const & p1,
                        viennagrid::element<vertex_tag,WrappedConfigT> const & v2)
    {
      return closest_points_impl(p1, accessor(v2));
    }

    template <typename PointAccessorT, typename PointT, typename WrappedConfigT>
    std::pair<typename viennagrid::result_of::point<viennagrid::element< vertex_tag,WrappedConfigT> >::type, PointT>
    closest_points_impl(PointAccessorT const accessor,
                        viennagrid::element<vertex_tag,WrappedConfigT> const & v1,
                        PointT const & p2)
    {
      return closest_points_impl(accessor(v1), p2);
    }

    // Closest points between vertices:
    template <typename PointAccessorT, typename PointT, typename WrappedConfigT>
    std::pair<typename viennagrid::result_of::point<viennagrid::element< vertex_tag,WrappedConfigT> >::type, typename viennagrid::result_of::point<viennagrid::element< vertex_tag,WrappedConfigT> >::type>
    closest_points_impl(PointAccessorT const accessor,
                        viennagrid::element<vertex_tag,WrappedConfigT> const & v1,
                        viennagrid::element<vertex_tag,WrappedConfigT> const & v2)
    {
      return closest_points_impl( accessor(v1), accessor(v2) );
    }



    //
    // Closest points between point and line segment
    //

    // Implementation: Supposed to work for arbitrary dimensions
    template <typename PointT, typename LinePointT>
    std::pair<PointT, LinePointT>
            closest_points_point_line(PointT const & p,
                                      LinePointT const & line_p1,
                                      LinePointT const & line_p2)
    {
      //typedef spatial_point<CoordT, CoordinateSystemT>  PointT;
      typedef typename viennagrid::result_of::coord< PointT >::type coord_type;

      //compute t such that projection of p onto [line_p1, line_p2] is given by p' = line_p1 + t * (line_p2 - line_p1)
      coord_type t = viennagrid::inner_prod( (p - line_p1), (line_p2 - line_p1) ) / viennagrid::inner_prod(line_p2 - line_p1, line_p2 - line_p1);

      //restrict t to line segment, i.e. t \in [0, 1]
      t = std::max<coord_type>(0, std::min<coord_type>(1, t));

      LinePointT p_prime = line_p1 + t * (line_p2 - line_p1);  //closest point to p on line

      return std::make_pair(p, p_prime);
    }


    //convenience overload: point and simplex line
    template <typename PointAccessorT, typename PointT, typename WrappedConfigT>
    std::pair< PointT, typename PointAccessorT::value_type >
            closest_points_impl(PointAccessorT const accessor,
                                PointT const & p,
                                viennagrid::element<simplex_tag<1>,WrappedConfigT> const & el)
    {
      return closest_points_point_line(p,
                                       accessor(vertices(el)[0]),
                                       accessor(vertices(el)[1]));
    }

    //convenience overload: point and hypercube line
    template <typename PointAccessorT, typename PointT, typename WrappedConfigT>
    std::pair< PointT, typename PointAccessorT::value_type >
            closest_points_impl(PointAccessorT const accessor,
                                PointT const & p,
                                viennagrid::element<hypercube_tag<1>,WrappedConfigT> const & el)
    {
      return closest_points_point_line(p,
                                       accessor(vertices(el)[0]),
                                       accessor(vertices(el)[1]));
    }

    //convenience overload: vertex and simplex line
    template <typename PointAccessorT, typename WrappedConfigT1, typename WrappedConfigT2>
    std::pair< typename PointAccessorT::value_type, typename PointAccessorT::value_type >
            closest_points_impl(PointAccessorT const accessor,
                                viennagrid::element<vertex_tag,WrappedConfigT1> const & v,
                                viennagrid::element<simplex_tag<1>,WrappedConfigT2> const & el)
    {
      return closest_points_point_line(accessor(v),
                                       accessor(vertices(el)[0]),
                                       accessor(vertices(el)[1]));
    }

    //convenience overload: vertex and hypercube line
    template <typename PointAccessorT, typename PointT, typename WrappedConfigT1, typename WrappedConfigT2>
    std::pair< typename PointAccessorT::value_type, typename PointAccessorT::value_type >
            closest_points_impl(PointAccessorT const accessor,
                                viennagrid::element<vertex_tag,WrappedConfigT1> const & v,
                                viennagrid::element<simplex_tag<1>,WrappedConfigT2> const & el)
    {
      return closest_points_point_line(accessor(v),
                                       accessor(vertices(el)[0]),
                                       accessor(vertices(el)[1]));
    }

    //
    // Distance between two line segments
    //

    // Implementation: Supposed to work for arbitrary dimensions
    template <typename PointT>
    std::pair<PointT, PointT>
            closest_points_line_line(PointT const & v0, PointT const & v1, //endpoints of first line
                                     PointT const & w0, PointT const & w1) //endpoints of second line
    {
      //typedef spatial_point<CoordT, CoordinateSystemT>  PointT;
      typedef typename viennagrid::result_of::coord< PointT >::type coord_type;

      // write V(s) = v0 + s * (v1 - v0), s \in [0,1]
      //       W(t) = w0 + t * (w1 - w0), t \in [0,1]

      // compute s and t assuming V(s) and W(t) to be infinite lines:
      // cf. http://www.softsurfer.com/Archive/algorithm_0106/algorithm_0106.htm
      PointT dir_v = v1 - v0;  //direction vector for line V(s)
      PointT dir_w = w1 - w0;  //direction vector for line W(t)

      coord_type v_in_v = viennagrid::inner_prod(dir_v, dir_v);
      coord_type v_in_w = viennagrid::inner_prod(dir_v, dir_w);
      coord_type w_in_w = viennagrid::inner_prod(dir_w, dir_w);

      coord_type denominator = v_in_v * w_in_w - v_in_w * v_in_w;
      //std::cout << "denominator: " << denominator << std::endl;

      if (denominator < 1e-6 * v_in_v * w_in_w) //lines parallel (up to round-off)
      {
        return point_pair_with_shortest_distance(closest_points_point_line(w0, v0, v1),
                                                 closest_points_point_line(w1, v0, v1),
                                                 closest_points_point_line(v0, w0, w1),
                                                 closest_points_point_line(v1, w0, w1));
      }

      //Lines are not parallel: Compute minimizers s, t:
      PointT dir_distance = v0 - w0;  //any vector connecting two points on V and W

      //if (inner_prod(dir_distance, dir_distance) / v_in_v < 1e-10)  //v0 and w0 are the same point
      //  return std::make_pair(v0, w0);

      coord_type v_in_dir_distance = viennagrid::inner_prod(dir_v, dir_distance);
      coord_type w_in_dir_distance = viennagrid::inner_prod(dir_w, dir_distance);

      coord_type s = (v_in_w * w_in_dir_distance - w_in_w * v_in_dir_distance) / denominator;
      coord_type t = (v_in_v * w_in_dir_distance - v_in_w * v_in_dir_distance) / denominator;
      //std::cout << "s = " << s << std::endl;
      //std::cout << "t = " << s << std::endl;

      //Check whether minimizing distance is within line segment, i.e. s,t \in [0,1]
      if ( (s < 0) || (s > 1) || (t < 0) || (t > 1) ) //Note: A more fine-grained check is possible for those looking for optimizations
        return point_pair_with_shortest_distance(closest_points_point_line(w0, v0, v1),
                                                 closest_points_point_line(w1, v0, v1),
                                                 closest_points_point_line(v0, w0, w1),
                                                 closest_points_point_line(v1, w0, w1));

      // compute points on V(s) an W(t) for which distance is smallest:
      PointT min_dist_point_V = v0 + s * dir_v;
      PointT min_dist_point_W = w0 + t * dir_w;

      return std::make_pair(min_dist_point_V, min_dist_point_W);
    }


    //convenience overload: simplex line and simplex line
    template <typename PointAccessorT, typename WrappedConfigT1, typename WrappedConfigT2>
    std::pair<typename PointAccessorT::value_type, typename PointAccessorT::value_type>
            closest_points_impl(PointAccessorT const accessor,
                                viennagrid::element<simplex_tag<1>,WrappedConfigT1> const & line0,
                                viennagrid::element<simplex_tag<1>,WrappedConfigT2> const & line1)
    {
      return closest_points_line_line(accessor(vertices(line0)[0]),
                                      accessor(vertices(line0)[1]),
                                      accessor(vertices(line1)[0]),
                                      accessor(vertices(line1)[1]));
    }

    //convenience overload: hypercube line and simplex line
    template <typename PointAccessorT, typename WrappedConfigT1, typename WrappedConfigT2>
    std::pair<typename PointAccessorT::value_type, typename PointAccessorT::value_type>
            closest_points_impl(PointAccessorT const accessor,
                                viennagrid::element<hypercube_tag<1>,WrappedConfigT1> const & line0,
                                viennagrid::element<simplex_tag<1>,WrappedConfigT2> const & line1)
    {
      return closest_points_line_line(accessor(vertices(line0)[0]),
                                      accessor(vertices(line0)[1]),
                                      accessor(vertices(line1)[0]),
                                      accessor(vertices(line1)[1]));
    }

    //convenience overload: simplex line and hypercube line
    template <typename PointAccessorT, typename WrappedConfigT1, typename WrappedConfigT2>
    std::pair<typename PointAccessorT::value_type, typename PointAccessorT::value_type>
            closest_points_impl(PointAccessorT const accessor,
                                viennagrid::element<simplex_tag<1>,WrappedConfigT1> const & line0,
                                viennagrid::element<hypercube_tag<1>,WrappedConfigT2> const & line1)
    {
      return closest_points_line_line(accessor(vertices(line0)[0]),
                                      accessor(vertices(line0)[1]),
                                      accessor(vertices(line1)[0]),
                                      accessor(vertices(line1)[1]));
    }

    //convenience overload: hypercube line and hypercube line
    template <typename PointAccessorT, typename WrappedConfigT1, typename WrappedConfigT2>
    std::pair<typename PointAccessorT::value_type, typename PointAccessorT::value_type>
            closest_points_impl(PointAccessorT const accessor,
                                viennagrid::element<hypercube_tag<1>,WrappedConfigT1> const & line0,
                                viennagrid::element<hypercube_tag<1>,WrappedConfigT2> const & line1)
    {
      return closest_points_line_line(accessor(vertices(line0)[0]),
                                      accessor(vertices(line0)[1]),
                                      accessor(vertices(line1)[0]),
                                      accessor(vertices(line1)[1]));
    }


    //
    // Distance between point and triangle
    //

    // Implementation: Supposed to work for arbitrary dimensions
    // Projects p onto the plane spanned by the triangle, then computes the shortest distance in the plane and uses Pythagoras for the full distance
    template <typename PointT>
    std::pair<PointT,PointT>
            closest_points_point_triangle(PointT const & p,
                                          PointT const & v0,
                                          PointT const & v1,
                                          PointT const & v2) //endpoints of second line
    {
      typedef typename viennagrid::result_of::coord< PointT >::type coord_type;

      // write T(s) =  v0 + s * (v1 - v0) + t * (v2 - v0), {s,t} \in [0,1], s+t < 1 for the triangle T
      //            =: v0 + s * u0 + t * u1
      //
      // Projection p' of p is given by the solution of the system
      //
      //  <u0, u0> * s + <u1, u0> * t = <u, u0>
      //  <u0, u1> * s + <u1, u1> * t = <u, u1>,
      //
      // where u = p - v0. This is a 2x2-system that is directly inverted.
      //
      // Write
      //
      // A = ( <u0, u0>   <u1, u0> ) = ( a  b )
      //     ( <u0, u1>   <u1, u1> )   ( c  d )
      //
      // and use b = c because of symmetry of the inner product.

      PointT u0 = v1 - v0;
      PointT u1 = v2 - v0;
      PointT u  = p  - v0;

      coord_type a = viennagrid::inner_prod(u0, u0);
      coord_type b = viennagrid::inner_prod(u0, u1);
      coord_type d = viennagrid::inner_prod(u1, u1);
      coord_type u_in_u0 = viennagrid::inner_prod(u, u0);
      coord_type u_in_u1 = viennagrid::inner_prod(u, u1);

      coord_type denominator = a * d - b * b;

      if (denominator < 1e-6 * a * d) //triangle is VERY thin: TODO: NUMERIC!!! 1e-6
      {
        std::cerr << "ViennaGrid: Warning: Strongly degenerated triangle detected: " << std::endl
                  << "vertex 0: " << v0 << std::endl
                  << "vertex 1: " << v1 << std::endl
                  << "vertex 2: " << v2 << std::endl;
      }

      coord_type s = (  d * u_in_u0 - b * u_in_u1) / denominator;
      coord_type t = (- b * u_in_u0 + a * u_in_u1) / denominator;

      PointT p_prime = v0 + s * u0 + t * u1;  //projection of p onto triangular plane

      // nonzero distance is encountered only if p_prime is outside the triangle
      if (    (s < 0 || s > 1)
           || (t < 0 || t > 1)
           || (s + t > 1) )     //p_prime is outside the triangle
      {
        // safe mode: Compute distances to all edges. Can be optimized further by using information from s, t, etc.
        return point_pair_with_shortest_distance(std::make_pair(p, closest_points_point_line(p_prime, v0, v1).second),
                                                 std::make_pair(p, closest_points_point_line(p_prime, v0, v2).second),
                                                 std::make_pair(p, closest_points_point_line(p_prime, v1, v2).second));
      }

      return std::make_pair(p, p_prime);
    }


    //convenience overload: point
    template <typename PointAccessorT, typename CoordT, typename CoordinateSystemT, typename WrappedConfigT>
    std::pair<spatial_point<CoordT, CoordinateSystemT>, typename PointAccessorT::value_type>
            closest_points_impl(PointAccessorT const accessor,
                                spatial_point<CoordT, CoordinateSystemT> const & p,
                                viennagrid::element<simplex_tag<2>,WrappedConfigT> const & el)
    {
      return closest_points_point_triangle(p,
                                           accessor(vertices(el)[0]),
                                           accessor(vertices(el)[1]),
                                           accessor(vertices(el)[2]));
    }

    //convenience overload: vertex
    template <typename PointAccessorT, typename WrappedConfigT1, typename WrappedConfigT2>
    std::pair<typename PointAccessorT::value_type,typename PointAccessorT::value_type>
    closest_points_impl(PointAccessorT const accessor,
                        viennagrid::element<vertex_tag,WrappedConfigT1> const & v,
                        viennagrid::element<simplex_tag<2>,WrappedConfigT2> const & el)
    {
      return closest_points_impl( accessor(v), el );
    }





    //
    // Distance between point and quadrilateral (using decomposition into two triangles)
    //

    //convenience overload: point
    //
    // Keep reference orientation in mind:
    //
    //   v[2]        v[3]
    //    * --------- *
    //    |   \       |
    //    |       \   |
    //    * --------- *
    //   v[0]        v[1]
    //
    template <typename PointAccessorT, typename CoordT, typename CoordinateSystemT, typename WrappedConfigT>
    std::pair<spatial_point<CoordT, CoordinateSystemT>, typename PointAccessorT::value_type>
            closest_points_impl(PointAccessorT const accessor,
                                spatial_point<CoordT, CoordinateSystemT> const & p,
                                viennagrid::element<hypercube_tag<2>,WrappedConfigT> const & el)
    {
      return point_pair_with_shortest_distance(closest_points_point_triangle(p,
                                                                             accessor(vertices(el)[0]),
                                                                             accessor(vertices(el)[1]),
                                                                             accessor(vertices(el)[2])),
                                               closest_points_point_triangle(p,
                                                                             accessor(vertices(el)[1]),
                                                                             accessor(vertices(el)[3]),
                                                                             accessor(vertices(el)[2]))
                                              );
    }

    //convenience overload: vertex
    template <typename PointAccessorT, typename WrappedConfigT1, typename WrappedConfigT2>
    std::pair<typename PointAccessorT::value_type,typename PointAccessorT::value_type>
            closest_points_impl(PointAccessorT const accessor,
                                viennagrid::element<vertex_tag,WrappedConfigT1> const & v,
                                viennagrid::element<hypercube_tag<2>,WrappedConfigT2> const & el)
    {
      return closest_points_impl( accessor(v), el);
    }



    //
    // Distance between point and tetrahedron
    //

    // Implementation: Supposed to work for arbitrary geometric dimensions
    // Projects p onto the plane spanned by the triangle, then computes the shortest distance in the plane and uses Pythagoras for the full distance
    template <typename PointT>
    std::pair<PointT,PointT>
            closest_points_point_tetrahedron(PointT const & p,
                                             PointT const & v0,
                                             PointT const & v1,
                                             PointT const & v2,
                                             PointT const & v3)
    {
      typedef typename viennagrid::result_of::coord< PointT >::type coord_type;

      // write T(s) =  v0 + r * (v1 - v0) + s * (v2 - v0) + t * (v3 - v1), {r,s,t} \in [0,1], r+s+t < 1 for the tetrahedron T
      //            =: v0 + r * u0 + s * u1 + t * u2
      //
      // Projection p' of p is given by the solution of the system
      //
      //  <u0, u0> * r + <u1, u0> * s + <u2, u0> * t = <u, u0>
      //  <u0, u1> * r + <u1, u1> * s + <u2, u1> * t = <u, u1>
      //  <u0, u2> * r + <u1, u2> * s + <u2, u2> * t = <u, u2>
      //
      // where u = p - v0. This is a 3x3-system that is directly inverted using Cramer's rule.
      //

      PointT u0 = v1 - v0;
      PointT u1 = v2 - v0;
      PointT u2 = v3 - v0;
      PointT u  = p  - v0;

      coord_type a_00 = viennagrid::inner_prod(u0, u0);
      coord_type a_01 = viennagrid::inner_prod(u1, u0);
      coord_type a_02 = viennagrid::inner_prod(u2, u0);

      coord_type a_10 = a_01;
      coord_type a_11 = viennagrid::inner_prod(u1, u1);
      coord_type a_12 = viennagrid::inner_prod(u2, u1);

      coord_type a_20 = a_02;
      coord_type a_21 = a_12;
      coord_type a_22 = viennagrid::inner_prod(u2, u2);

      coord_type u_in_u0 = viennagrid::inner_prod(u, u0);
      coord_type u_in_u1 = viennagrid::inner_prod(u, u1);
      coord_type u_in_u2 = viennagrid::inner_prod(u, u2);

      coord_type det_A =  a_00 * a_11 * a_22 + a_01 * a_12 * a_20 + a_02 * a_10 * a_21
                        - a_20 * a_11 * a_02 - a_21 * a_12 * a_00 - a_22 * a_10 * a_01;

      if (det_A < 1e-6 * std::sqrt(a_00 * a_11 * a_22)) //tetrahedron is VERY thin:
      {
        std::cerr << "ViennaGrid: Warning: Strongly degenerated tetrahedron detected: " << std::endl
                  << "vertex 0: " << v0 << std::endl
                  << "vertex 1: " << v1 << std::endl
                  << "vertex 2: " << v2 << std::endl
                  << "vertex 3: " << v3 << std::endl;
      }

      //     | <u, u0>   a_01   a_02  |
      // r = | <u, u1>   a_11   a_12  |  / det_A  and similarly for s and t
      //     | <u, u2>   a_21   a_22  |
      coord_type r = (  u_in_u0 * a_11 * a_22 + a_01 * a_12 * u_in_u2 + a_02 * u_in_u1 * a_21
                      - u_in_u2 * a_11 * a_02 - a_21 * a_12 * u_in_u0 - a_22 * u_in_u1 * a_01 ) / det_A;
      coord_type s = (  a_00 * u_in_u1 * a_22 + u_in_u0 * a_12 * a_20 + a_02 * a_10 * u_in_u2
                      - a_20 * u_in_u1 * a_02 - u_in_u2 * a_12 * a_00 - a_22 * a_10 * u_in_u0 ) / det_A;
      coord_type t = (  a_00 * a_11 * u_in_u2 + a_01 * u_in_u1 * a_20 + u_in_u0 * a_10 * a_21
                      - a_20 * a_11 * u_in_u0 - a_21 * u_in_u1 * a_00 - u_in_u2 * a_10 * a_01 ) / det_A;

      PointT p_prime = v0 + r * u0 + s * u1 + t * u2;  //projection of p onto triangular plane

      // nonzero distance is encountered only if p_prime is outside the triangle
      if (    (r < 0 || r > 1)
           || (s < 0 || s > 1)
           || (t < 0 || t > 1)
           || (r + s + t > 1) )     //p_prime is outside the triangle
      {
        // safe mode: Compute distances to all edges. Can be optimized further by using information from s, t, etc.
        return point_pair_with_shortest_distance(std::make_pair(p, closest_points_point_triangle(p_prime, v0, v1, v2).second),
                                                 std::make_pair(p, closest_points_point_triangle(p_prime, v0, v1, v3).second),
                                                 std::make_pair(p, closest_points_point_triangle(p_prime, v0, v2, v3).second),
                                                 std::make_pair(p, closest_points_point_triangle(p_prime, v1, v2, v3).second));
      }

      return std::make_pair(p, p_prime);
    }


    //convenience overload: point
    template <typename PointAccessorT, typename CoordT, typename CoordinateSystemT, typename WrappedConfigT>
    std::pair<spatial_point<CoordT, CoordinateSystemT>,typename PointAccessorT::value_type>
            closest_points_impl(PointAccessorT const accessor,
                                spatial_point<CoordT, CoordinateSystemT> const & p,
                                viennagrid::element<simplex_tag<3>,WrappedConfigT> const & el)
    {
      return closest_points_point_tetrahedron(p,
                                              accessor(vertices(el)[0]),
                                              accessor(vertices(el)[1]),
                                              accessor(vertices(el)[2]),
                                              accessor(vertices(el)[3]));
    }

    //convenience overload: vertex
    template <typename PointAccessorT, typename WrappedConfigT1, typename WrappedConfigT2>
    std::pair<typename PointAccessorT::value_type,typename PointAccessorT::value_type>
            closest_points_impl(PointAccessorT const accessor,
                                viennagrid::element<vertex_tag,WrappedConfigT1> const & v,
                                viennagrid::element<simplex_tag<3>,WrappedConfigT2> const & el)
    {
      return closest_points_impl( accessor(v), el);
    }



    //
    // Distance between point and hexahedron (using decomposition into six tetrahedra)
    //

    //convenience overload: point
    template <typename PointAccessorT, typename PointT, typename WrappedConfigT>
    std::pair<PointT,typename PointAccessorT::value_type>
            closest_points_impl(PointAccessorT const accessor,
                                PointT const & p,
                                viennagrid::element<hypercube_tag<3>,WrappedConfigT> const & el)
    {
      return point_pair_with_shortest_distance(closest_points_point_tetrahedron(p,
                                                                                accessor(vertices(el)[0]),
                                                                                accessor(vertices(el)[1]),
                                                                                accessor(vertices(el)[3]),
                                                                                accessor(vertices(el)[7])),
                                               closest_points_point_tetrahedron(p,
                                                                                accessor(vertices(el)[0]),
                                                                                accessor(vertices(el)[1]),
                                                                                accessor(vertices(el)[7]),
                                                                                accessor(vertices(el)[5])),
                                               closest_points_point_tetrahedron(p,
                                                                                accessor(vertices(el)[0]),
                                                                                accessor(vertices(el)[2]),
                                                                                accessor(vertices(el)[6]),
                                                                                accessor(vertices(el)[7])),
                                               closest_points_point_tetrahedron(p,
                                                                                accessor(vertices(el)[0]),
                                                                                accessor(vertices(el)[3]),
                                                                                accessor(vertices(el)[2]),
                                                                                accessor(vertices(el)[7])),
                                               closest_points_point_tetrahedron(p,
                                                                                accessor(vertices(el)[0]),
                                                                                accessor(vertices(el)[5]),
                                                                                accessor(vertices(el)[7]),
                                                                                accessor(vertices(el)[4])),
                                               closest_points_point_tetrahedron(p,
                                                                                accessor(vertices(el)[0]),
                                                                                accessor(vertices(el)[6]),
                                                                                accessor(vertices(el)[4]),
                                                                                accessor(vertices(el)[7]))
                                              );
    }

    //convenience overload: vertex
    template <typename PointAccessorT, typename WrappedConfigT1, typename WrappedConfigT2>
    std::pair<typename PointAccessorT::value_type,typename PointAccessorT::value_type>
    closest_points_impl(PointAccessorT const accessor,
                        viennagrid::element<vertex_tag,WrappedConfigT1> const & v,
                        viennagrid::element<hypercube_tag<3>,WrappedConfigT2> const & el)
    {
      return closest_points_impl( accessor(v), el);
    }

    //
    /////////////////////// closest_points_on_boundary ////////////////////
    //

    //
    // Closest points between points (trivial)
    //

    // Closest points between two points (overloads for vertices follow):
    template <typename PointT>
    std::pair<PointT, PointT>
    closest_points_on_boundary_impl(PointT const & p1,
                        PointT const & p2)
    {
      return std::make_pair(p1, p2);
    }

    template <typename PointAccessorT, typename CoordT1, typename CoordinateSystemT1, typename CoordT2, typename CoordinateSystemT2>
    std::pair< spatial_point<CoordT1, CoordinateSystemT1>, spatial_point<CoordT1, CoordinateSystemT1> >
    closest_points_on_boundary_impl(PointAccessorT const,
                                    spatial_point<CoordT1, CoordinateSystemT1> const & p1,
                                    spatial_point<CoordT2, CoordinateSystemT2> const & p2)
    {
      return closest_points_on_boundary_impl(p1, p2);
    }

    template <typename PointAccessorT, typename PointT, typename WrappedConfigT>
    std::pair<PointT, typename viennagrid::result_of::point<viennagrid::element< vertex_tag,WrappedConfigT> >::type>
    closest_points_on_boundary_impl(PointAccessorT const accessor,
                                    PointT const & p1,
                                    viennagrid::element<vertex_tag,WrappedConfigT> const & v2)
    {
      return std::make_pair(p1, accessor(v2));
    }

    template <typename PointAccessorT, typename PointT, typename WrappedConfigT>
    std::pair<typename viennagrid::result_of::point<viennagrid::element< vertex_tag,WrappedConfigT> >::type, PointT>
    closest_points_on_boundary_impl(PointAccessorT const accessor,
                                    PointT const & p2,
                                    viennagrid::element<vertex_tag,WrappedConfigT> const & v1)
    {
      return std::make_pair(accessor(v1), p2);
    }

    // Closest points between vertices:
    template <typename PointAccessorT, typename PointT, typename WrappedConfigT>
    std::pair<typename viennagrid::result_of::point<viennagrid::element< vertex_tag,WrappedConfigT> >::type, typename viennagrid::result_of::point<viennagrid::element< vertex_tag,WrappedConfigT> >::type>
    closest_points_on_boundary_impl(PointAccessorT const accessor,
                                    viennagrid::element<vertex_tag,WrappedConfigT> const & v1,
                                    viennagrid::element<vertex_tag,WrappedConfigT> const & v2)
    {
      return std::make_pair( accessor(v1), accessor(v2) );
    }

    ////////////////// Distance from point to container ////////////////////

    /** @tparam ContainerType   Any topological object (ncell, segment, mesh) */
    template <typename FacetTypeOrTag, typename PointAccessorT, typename PointT, typename SomethingT>
    std::pair<PointT, typename PointAccessorT::value_type>
    closest_points_on_boundary_point_to_any(PointAccessorT const accessor,
                                            PointT const & p,
                                            SomethingT const & cont)
    {
      typedef typename viennagrid::result_of::element_tag<FacetTypeOrTag>::type FacetTag;
      typedef std::pair<PointT, typename viennagrid::result_of::point<SomethingT>::type>       PairType;

      typedef typename viennagrid::result_of::const_element_range<SomethingT, FacetTag>::type           FacetRange;
      typedef typename viennagrid::result_of::iterator<FacetRange>::type                  FacetIterator;

      PairType closest_pair;
      double shortest_distance = std::numeric_limits<double>::max();

      FacetRange facets(cont);
      for (FacetIterator fit = facets.begin();
                         fit != facets.end();
                       ++fit)
      {
        if (!is_boundary(cont, *fit))
          continue;

        PairType pair = closest_points_impl(accessor, p, *fit);
        double cur_norm = norm_2(pair.first - pair.second);
        if (cur_norm < shortest_distance)
        {
          closest_pair = pair;
          shortest_distance = cur_norm;
        }
      }

      return closest_pair;
    }



    template <typename PointAccessorT, typename PointT, typename ElementTag, typename WrappedConfigT>
    std::pair<PointT, typename PointAccessorT::value_type>
    closest_points_on_boundary_impl(PointAccessorT const & mesh_obj,
                                    PointT const & v,
                                    viennagrid::element<ElementTag,WrappedConfigT> const & el)
    {
      return closest_points_on_boundary_point_to_any<typename ElementTag::facet_tag>(mesh_obj, v, el);
    }

    template <typename PointAccessorT, typename WrappedConfigT, typename PointT>
    std::pair<PointT, typename viennagrid::result_of::point< viennagrid::mesh<WrappedConfigT> >::type>
    closest_points_on_boundary_impl(PointAccessorT const point_accessor,
                                    PointT const & p,
                                    mesh<WrappedConfigT> const & mesh_obj)
    {
        typedef typename viennagrid::result_of::cell_tag< mesh<WrappedConfigT> >::type CellTag;
      return closest_points_on_boundary_point_to_any<typename CellTag::facet_tag>( point_accessor, p, mesh_obj);
    }

    template <typename PointAccessorT, typename SegmentationT, typename PointT>
    std::pair<PointT, typename viennagrid::result_of::point< segment_handle<SegmentationT> >::type>
    closest_points_on_boundary_impl(PointAccessorT const point_accessor,
                                    PointT const & p,
                                    segment_handle<SegmentationT> const & segment)
    {
        typedef typename viennagrid::result_of::cell_tag< segment_handle<SegmentationT> >::type CellTag;
      return closest_points_on_boundary_point_to_any<typename CellTag::facet_tag>( point_accessor, p, segment );
    }



    template <typename PointAccessorT,  typename WrappedConfigT1, typename EA2, typename WrappedConfigT2>
    std::pair<typename PointAccessorT::value_type, typename PointAccessorT::value_type>
    closest_points_on_boundary_impl(PointAccessorT const accessor,
                                    viennagrid::element<vertex_tag,WrappedConfigT1> const & v,
                                    viennagrid::element<EA2,WrappedConfigT2> const & el)
    {
      return closest_points_on_boundary_impl( accessor(v), el);
    }

    template <typename WrappedMeshConfigType, typename WrappedConfigT>
    std::pair< typename viennagrid::result_of::point< mesh<WrappedMeshConfigType> >::type, typename viennagrid::result_of::point< mesh<WrappedMeshConfigType> >::type >
    closest_points_on_boundary_impl(viennagrid::element<vertex_tag,WrappedConfigT> const & v,
                                    mesh<WrappedMeshConfigType> const & mesh_obj)
    {
      return closest_points_on_boundary_impl( default_point_accessor(mesh_obj)(v), mesh_obj);
    }


    ////////// Distance from Container to Container /////////////////////

    template <typename PointAccessorT, typename SomethingT1, typename SomethingT2>
    std::pair< typename PointAccessorT::value_type, typename PointAccessorT::value_type >
    closest_points_on_boundary_generic(PointAccessorT const accessor,
                                       SomethingT1 const & el1,
                                       SomethingT2 const & el2)
    {


      typedef typename viennagrid::result_of::facet_tag<SomethingT1>::type FacetTag1;
      typedef typename viennagrid::result_of::facet_tag<SomethingT2>::type FacetTag2;


      typedef std::pair< typename PointAccessorT::value_type, typename PointAccessorT::value_type > PairType;

      typedef typename viennagrid::result_of::const_element_range<SomethingT1, FacetTag1>::type           FacetRange1;
      typedef typename viennagrid::result_of::iterator<FacetRange1>::type                   FacetIterator1;

      typedef typename viennagrid::result_of::const_element_range<SomethingT2, FacetTag2>::type           FacetRange2;
      typedef typename viennagrid::result_of::iterator<FacetRange2>::type                   FacetIterator2;

      PairType closest_pair;
      double shortest_distance = std::numeric_limits<double>::max();


      FacetRange1 facets1(el1);
      FacetRange2 facets2(el2);

      for (FacetIterator1 fit1 = facets1.begin();
                          fit1 != facets1.end();
                        ++fit1)
      {
        if (!is_boundary(el1, *fit1))
          continue;

        for (FacetIterator2 fit2 = facets2.begin();
                            fit2 != facets2.end();
                          ++fit2)
        {
          if (!is_boundary(el2, *fit2))
            continue;

          PairType p = closest_points_impl(accessor, *fit1, *fit2);
          double cur_norm = norm_2(p.first - p.second);
          if (cur_norm < shortest_distance)
          {
            closest_pair = p;
            shortest_distance = cur_norm;
          }
        }
      }

      return closest_pair;
    }


    template <typename PointAccessorT,
              typename ElementTag1, typename WrappedConfigT1,
              typename ElementTag2, typename WrappedConfigT2>
    std::pair< typename PointAccessorT::value_type, typename PointAccessorT::value_type >
    closest_points_on_boundary_impl(PointAccessorT const accessor,
                                    viennagrid::element<ElementTag1,WrappedConfigT1> const & el1,
                                    viennagrid::element<ElementTag2,WrappedConfigT2> const & el2)
    {
      return closest_points_on_boundary_generic(accessor, el1, el2);
    }

    template <typename PointAccessorT,
              typename WrappedMeshConfigType,
              typename ElementTag, typename WrappedConfigT>
    std::pair< typename PointAccessorT::value_type, typename PointAccessorT::value_type >
    closest_points_on_boundary_impl(PointAccessorT const accessor,
                                    viennagrid::element<ElementTag,WrappedConfigT> const & el1,
                                    mesh<WrappedMeshConfigType> const & mesh_obj)
    {
      return closest_points_on_boundary_generic(accessor, mesh_obj, el1);
    }

    template <typename PointAccessorT,
              typename SegmentationT,
              typename ElementTag, typename WrappedConfigT>
    std::pair< typename PointAccessorT::value_type, typename PointAccessorT::value_type >
    closest_points_on_boundary_impl(PointAccessorT const accessor,
                                    viennagrid::element<ElementTag,WrappedConfigT> const & el1,
                                    segment_handle<SegmentationT> const & segment)
    {
      return closest_points_on_boundary_generic(accessor, segment, el1);
    }


    template <typename PointAccessorT,
              typename Segmentation1T,
              typename Segmentation2T>
    std::pair< typename PointAccessorT::value_type, typename PointAccessorT::value_type >
    closest_points_on_boundary_impl(PointAccessorT const accessor,
                                    segment_handle<Segmentation1T> const & segment1,
                                    segment_handle<Segmentation2T> const & segment2)
    {
      return closest_points_on_boundary_generic(accessor, segment1, segment2);
    }



    //////////////////////////// other helpers ////////////////////////

    template <typename T>
    struct topological_id
    {
        //by default, typename is unknown, thus force error by not defining 'value'
    };

    template <typename CoordT, typename CoordinateSystemT>
    struct topological_id< spatial_point<CoordT, CoordinateSystemT> >
    {
      static const int value = 1;
    };


    template <int dim, typename WrappedConfigT>
    struct topological_id< viennagrid::element<simplex_tag<dim>, WrappedConfigT> >
    {
      static const int value = 10000 + dim; //10.000 dimensions are certainly far from being ever instantiated
    };

    template <int dim, typename WrappedConfigT>
    struct topological_id< viennagrid::element<hypercube_tag<dim>, WrappedConfigT> >
    {
      static const int value = 20000 + dim;
    };

    template <typename WrappedConfigT>
    struct topological_id< viennagrid::mesh<WrappedConfigT> >
    {
      static const int value = 100000;
    };

    template <typename SegmentationT>
    struct topological_id< segment_handle<SegmentationT> >
    {
      static const int value = 100000 + 1;
    };



    template <typename T, typename U>
    struct topologically_sorted
    {
      static const bool value = (topological_id<T>::value <= topological_id<U>::value) ? true : false;
    };


    template <typename T,
              typename U,
              bool correct_order = topologically_sorted<T, U>::value >
    struct ascending_topological_order
    {
      static T const & first(T const & t, U const &) { return t; }
      static U const & second(T const &, U const & u) { return u; }
    };

    template <typename T,
              typename U>
    struct ascending_topological_order<T, U, false>
    {
      static U const & first(T const &, U const & u) { return u; }
      static T const & second(T const & t, U const &) { return t; }
    };

  } //namespace detail

  //
  // The public interface functions
  //
  /** @brief Returns the distance between n-cells */
  template <typename PointAccessorT, typename SomethingT1, typename SomethingT2>
  std::pair< typename PointAccessorT::value_type, typename PointAccessorT::value_type >
  closest_points(PointAccessorT const accessor,
                 SomethingT1 const & el1,
                 SomethingT2 const & el2)
  {
    return detail::closest_points_impl(accessor,
                                       detail::ascending_topological_order<SomethingT1, SomethingT2>::first(el1, el2),
                                       detail::ascending_topological_order<SomethingT1, SomethingT2>::second(el1, el2));
  }

  /** @brief Returns the closest points between two elements/segments using the default accessor for geometric points on vertices */
  template <typename SomethingT1, typename SomethingT2>
  std::pair< typename viennagrid::result_of::point<SomethingT1>::type, typename viennagrid::result_of::point<SomethingT1>::type >
  closest_points(SomethingT1 const & el1,
                 SomethingT2 const & el2)
  {
    return closest_points_impl(default_point_accessor(el1),
                                       detail::ascending_topological_order<SomethingT1, SomethingT2>::first(el1, el2),
                                       detail::ascending_topological_order<SomethingT1, SomethingT2>::second(el1, el2));
  }


  /** @brief Returns the closest points between two elements/segments using the provided accessor for geometric points on vertices */
  template <typename PointAccessorT, typename SomethingT1, typename SomethingT2>
  std::pair< typename PointAccessorT::value_type, typename PointAccessorT::value_type >
  closest_points_on_boundary(PointAccessorT const accessor,
                 SomethingT1 const & el1,
                 SomethingT2 const & el2)
  {
    return detail::closest_points_on_boundary_impl(accessor,
                                       detail::ascending_topological_order<SomethingT1, SomethingT2>::first(el1, el2),
                                       detail::ascending_topological_order<SomethingT1, SomethingT2>::second(el1, el2));
  }

  /** @brief Returns the distance between n-cells */
  template <typename SomethingT1, typename SomethingT2>
  std::pair< typename viennagrid::result_of::point<SomethingT1>::type, typename viennagrid::result_of::point<SomethingT1>::type >
  closest_points_on_boundary(SomethingT1 const & el1,
                             SomethingT2 const & el2)
  {
    return detail::closest_points_on_boundary_impl(default_point_accessor(el1),
                                       detail::ascending_topological_order<SomethingT1, SomethingT2>::first(el1, el2),
                                       detail::ascending_topological_order<SomethingT1, SomethingT2>::second(el1, el2));
  }


} //namespace viennagrid
#endif
