#ifndef VIENNAGRID_ALGORITHM_CENTROID_HPP
#define VIENNAGRID_ALGORITHM_CENTROID_HPP

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

#include "viennagrid/forwards.hpp"
#include "viennagrid/topology/all.hpp"
#include "viennagrid/algorithm/volume.hpp"    //for mesh/segment centroid
#include "viennagrid/accessor.hpp"

/** @file viennagrid/algorithm/centroid.hpp
    @brief Computes the centroid (center of mass) for different cell types
*/

namespace viennagrid
{
  namespace detail
  {
    //
    // Calculation of centroid
    //
    /** @brief Implementation of the calculation of a centroid for a triangle */
    template <typename PointAccessorT, typename ElementT>
    typename PointAccessorT::value_type
    centroid(PointAccessorT const accessor, ElementT const & cell, viennagrid::triangle_tag)
    {
      typedef typename PointAccessorT::value_type PointType;
      typedef typename viennagrid::result_of::coord<PointType>::type    CoordType;

      typedef typename viennagrid::result_of::const_element_range<ElementT, vertex_tag>::type         VertexOnCellRange;
      typedef typename viennagrid::result_of::iterator<VertexOnCellRange>::type            VertexOnCellIterator;

      PointType p0(0.0, 0.0);

      VertexOnCellRange vertices = viennagrid::elements<vertex_tag>(cell);
      for (VertexOnCellIterator vocit = vertices.begin();
           vocit != vertices.end();
           ++vocit)
        p0 += accessor(*vocit);

      p0 /= static_cast<CoordType>(vertices.size());

      return p0;
    }

    //tetrahedron can reuse the algorithm defined for a triangle
    /** @brief Implementation of the calculation of a centroid for a tetrahedron */
    template <typename PointAccessorT, typename ElementT>
    typename PointAccessorT::value_type
    centroid(PointAccessorT const accessor, ElementT const & cell, viennagrid::tetrahedron_tag)
    {
      return centroid(accessor, cell, viennagrid::triangle_tag());
    }

    //
    // Note: This works for rectangles only, but not for general quadrilateral
    //
    /** @brief Implementation of the calculation of a centroid for a quadrilateral */
    template <typename PointAccessorT, typename ElementT>
    typename PointAccessorT::value_type
    centroid(PointAccessorT const accessor, ElementT const & cell, viennagrid::quadrilateral_tag)
    {
      return centroid(accessor, cell, viennagrid::triangle_tag());
    }

    //
    // Note: This works for cuboids only, but not for general hexahedra
    //
    /** @brief Implementation of the calculation of a centroid for a hexahedron */
    template <typename PointAccessorT, typename ElementT>
    typename PointAccessorT::value_type
    centroid(PointAccessorT const accessor, ElementT const & cell, viennagrid::hexahedron_tag)
    {
      return centroid(accessor, cell, viennagrid::triangle_tag());
    }


    //a line can reuse the algorithm defined for a triangle
    /** @brief Implementation of the calculation of a centroid for a line (1-simplex) */
    template <typename PointAccessorT, typename ElementT>
    typename PointAccessorT::value_type
    centroid(PointAccessorT const accessor, ElementT const & cell, viennagrid::simplex_tag<1>)
    {
      return centroid(accessor, cell, viennagrid::triangle_tag());
    }


    /** @brief Implementation of the calculation of a centroid for a line (1-hypercube) */
    template <typename PointAccessorT, typename ElementT>
    typename PointAccessorT::value_type
    centroid(PointAccessorT const accessor, ElementT const & cell, viennagrid::hypercube_tag<1>)
    {
      return centroid(accessor, cell, viennagrid::triangle_tag());
    }


    //a point is degenerate and returns its location
    /** @brief Implementation of the calculation of a centroid for a point */
    template <typename PointAccessorT, typename ElementT>
    typename PointAccessorT::value_type
    centroid(PointAccessorT const accessor, ElementT const & cell, viennagrid::vertex_tag)
    {
      return accessor(cell);
    }



    /** @brief Implementation of the calculation of a centroid for a mesh/segment */
    template <typename ElementTOrTag, typename MeshSegmentHandleType, typename PointAccessorT>
    typename viennagrid::result_of::point<MeshSegmentHandleType>::type
    centroid_mesh(MeshSegmentHandleType const & mesh_obj, PointAccessorT const point_accessor)
    {
      typedef typename viennagrid::result_of::element_tag<ElementTOrTag>::type            ElementTag;
      typedef typename viennagrid::result_of::point<MeshSegmentHandleType>::type          PointType;
      typedef typename viennagrid::result_of::const_element_range<MeshSegmentHandleType,
                                                                ElementTag>::type         CellRange;
      typedef typename viennagrid::result_of::iterator<CellRange>::type                   CellIterator;

      PointType result = 0;
      double volume = 0;

      CellRange cells = viennagrid::elements<ElementTag>(mesh_obj);
      for (CellIterator cit = cells.begin(); cit != cells.end(); ++cit)
      {
        double vol_cell = viennagrid::volume( point_accessor, *cit );
        result += vol_cell * centroid( point_accessor, *cit);
        volume += vol_cell;
      }

      return result / volume;
    }

  } //namespace detail



  /** @brief The public interface function for the computation of a centroid of an element with explicit point accessor
   *
   * @param element    The element for which the centroid should be computed
   * @param accessor   The point accessor providing point information for geometric calculation
   */
  template <typename PointAccessorT, typename ElementT>
  typename PointAccessorT::value_type
  centroid(PointAccessorT const accessor, ElementT const & element)
  {
    return detail::centroid( accessor, element, typename ElementT::tag());
  }

  /** @brief The public interface function for the computation of a centroid of an element
   *
   * @param element    The element for which the centroid should be computed
   */
  template <typename ElementTag, typename WrappedConfigT>
  typename viennagrid::result_of::point< viennagrid::element<ElementTag,WrappedConfigT> >::type
  centroid(viennagrid::element<ElementTag,WrappedConfigT> const & element)
  {
    return detail::centroid( default_point_accessor(element), element, ElementTag());
  }



  /** @brief The public interface function for the computation of a centroid of a mesh with explicit point accessor.
   *
   * @tparam ElementTOrTagT       The element type/tag of the elements for which the centroid is calculcated
   * @param  mesh_obj             The mesh which centroid is to be calculated
   * @param  point_accessor       The point accessor providing point information for geometric calculation
   */
  template<typename ElementTOrTagT, typename WrappedConfigT, typename PointAccessorT>
  typename viennagrid::result_of::point< mesh<WrappedConfigT> >::type
  centroid(mesh<WrappedConfigT> const & mesh_obj, PointAccessorT const point_accessor)
  {
    return detail::centroid_mesh<ElementTOrTagT>(mesh_obj, point_accessor);
  }

  /** @brief The public interface function for the computation of a centroid of a mesh with explicit point accessor. Cells are used for centroid calculation, will fail if there is more than one cell type.
   *
   * @param  mesh_obj           The mesh which centroid is to be calculated
   * @param  point_accessor     The point accessor providing point information for geometric calculation
   */
  template<typename WrappedConfigT, typename PointAccessorT>
  typename viennagrid::result_of::point< mesh<WrappedConfigT> >::type
  centroid(mesh<WrappedConfigT> const & mesh_obj, PointAccessorT const point_accessor)
  {
    typedef typename viennagrid::result_of::cell_tag< mesh<WrappedConfigT> >::type CellTag;
    return detail::centroid_mesh<CellTag>(mesh_obj, point_accessor);
  }


  /** @brief The public interface function for the computation of a centroid of a mesh.
   *
   * @tparam ElementTOrTagT    The element type/tag of the elements for which the centroid is calculcated
   * @param  mesh_obj          The mesh which centroid is to be calculated
   */
  template<typename ElementTOrTagT, typename WrappedConfigT>
  typename viennagrid::result_of::point< mesh<WrappedConfigT> >::type
  centroid(mesh<WrappedConfigT> const & mesh_obj)
  {
    return centroid<ElementTOrTagT>(mesh_obj, default_point_accessor(mesh_obj));
  }

  /** @brief The public interface function for the computation of a centroid of a mesh. Cells are used for centroid calculation, will fail if there is more than one cell type.
   *
   * @param  mesh_obj          The mesh which centroid is to be calculated
   */
  template<typename WrappedConfigT>
  typename viennagrid::result_of::point< mesh<WrappedConfigT> >::type
  centroid(mesh<WrappedConfigT> const & mesh_obj)
  {
    typedef typename viennagrid::result_of::cell_tag< mesh<WrappedConfigT> >::type CellTag;
    return centroid<CellTag>(mesh_obj, default_point_accessor(mesh_obj));
  }


  /** @brief The public interface function for the computation of a centroid of a segment with explicit point accessor.
   *
   * @tparam ElementTOrTagT    The element type/tag of the elements for which the centroid is calculcated
   * @param  segment              The segment which centroid is to be calculated
   * @param  point_accessor       The point accessor providing point information for geometric calculation
   */
  template<typename ElementTOrTagT, typename SegmentationT, typename PointAccessorT>
  typename viennagrid::result_of::point< segment_handle<SegmentationT> >::type
  centroid(segment_handle<SegmentationT> const & segment, PointAccessorT const point_accessor)
  {
    return detail::centroid_mesh<ElementTOrTagT>(segment, point_accessor);
  }

  /** @brief The public interface function for the computation of a centroid of a segment with explicit point accessor. Cells are used for centroid calculation, will fail if there is more than one cell type.
   *
   * @param  segment              The segment which centroid is to be calculated
   * @param  point_accessor       The point accessor providing point information for geometric calculation
   */
  template<typename SegmentationT, typename PointAccessorT>
  typename viennagrid::result_of::point< segment_handle<SegmentationT> >::type
  centroid(segment_handle<SegmentationT> const & segment, PointAccessorT const point_accessor)
  {
    typedef typename viennagrid::result_of::cell_tag< segment_handle<SegmentationT> >::type CellTag;
    return detail::centroid_mesh<CellTag>(segment, point_accessor);
  }


  /** @brief The public interface function for the computation of a centroid of a segment.
   *
   * @tparam ElementTOrTagT    The element type/tag of the elements for which the centroid is calculcated
   * @param  segment              The segment which centroid is to be calculated
   */
  template<typename ElementTOrTagT, typename SegmentationT>
  typename viennagrid::result_of::point< segment_handle<SegmentationT> >::type
  centroid(segment_handle<SegmentationT> const & segment)
  {
    return centroid<ElementTOrTagT>(segment, default_point_accessor(segment));
  }

  /** @brief The public interface function for the computation of a centroid of a segment. Cells are used for centroid calculation, will fail if there is more than one cell type.
   *
   * @param  segment               The segment which centroid is to be calculated
   */
  template<typename SegmentationT>
  typename viennagrid::result_of::point< segment_handle<SegmentationT> >::type
  centroid(segment_handle<SegmentationT> const & segment)
  {
    typedef typename viennagrid::result_of::cell_tag< segment_handle<SegmentationT> >::type CellTag;
    return centroid<CellTag>(segment, default_point_accessor(segment));
  }
} //namespace viennagrid
#endif
