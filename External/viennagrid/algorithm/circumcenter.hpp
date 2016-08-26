#ifndef VIENNAGRID_ALGORITHM_CIRCUMCENTER_HPP
#define VIENNAGRID_ALGORITHM_CIRCUMCENTER_HPP

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
#include "viennagrid/algorithm/spanned_volume.hpp"
#include "viennagrid/algorithm/cross_prod.hpp"
#include "viennagrid/topology/all.hpp"

/** @file viennagrid/algorithm/circumcenter.hpp
    @brief Computes the circumcenter of n-cells.
*/

namespace viennagrid
{
  namespace detail
  {
    /** @brief Throws a compile time error if the n-cell type is not supported. */
    template <typename ElementT, typename GeometricContainerT, typename ElementTag, typename DimensionTag>
    typename viennagrid::result_of::point<GeometricContainerT>::type
    circumcenter(ElementT const &, GeometricContainerT const &, ElementTag const &, DimensionTag const &)
    {
      typename ElementT::ERROR_COMPUTATION_OF_CIRCUMCENTER_NOT_IMPLEMENTED   error_object;
      (void)error_object;
      return typename viennagrid::result_of::point<GeometricContainerT>::type();
    }


    //a point is degenerate and returns its location
    /** @brief Implementation of the calculation of a circumcenter for a point (degenerate case) */
    template <typename PointAccessorT, typename ElementT>
    typename PointAccessorT::value_type
    circumcenter(PointAccessorT const accessor, ElementT const & cell, viennagrid::vertex_tag)
    {
      return accessor(cell);
    }

    //
    // Calculation of circumcenter for a line
    //
    /** @brief Implementation of the calculation of a circumcenter for a line (1-simplex) */
    template <typename PointAccessorT, typename ElementT, typename DimensionTag>
    typename PointAccessorT::value_type
    circumcenter(PointAccessorT const accessor, ElementT const & cell, viennagrid::simplex_tag<1>, DimensionTag)
    {
      typedef typename PointAccessorT::value_type PointType;

      PointType const & A = accessor( vertices(cell)[0] );
      PointType const & B = accessor( vertices(cell)[1] );

      PointType ret = A + B;
      ret /= 2.0;

      return ret;
    }

    /** @brief Implementation of the calculation of a circumcenter for a line (1-hypercube) */
    template <typename PointAccessorT, typename ElementT, typename DimensionTag>
    typename PointAccessorT::value_type
    circumcenter(PointAccessorT const accessor, ElementT const & cell, viennagrid::hypercube_tag<1>, DimensionTag)
    {
      return circumcenter(accessor, cell, viennagrid::simplex_tag<1>(), DimensionTag());
    }

    //
    // Calculation of circumcenter taken from Wikipedia (better reference required...)
    //
    /** @brief Implementation of the calculation of a circumcenter for a triangle in two dimensions */
    template <typename PointAccessorT, typename ElementT>
    typename PointAccessorT::value_type
    circumcenter(PointAccessorT const accessor, ElementT const & cell, viennagrid::triangle_tag, viennagrid::dimension_tag<2>)
    {
      typedef typename PointAccessorT::value_type PointType;

      PointType const & A = accessor( vertices(cell)[0] );
      PointType const & B = accessor( vertices(cell)[1] );
      PointType const & C = accessor( vertices(cell)[2] );

      PointType circ_cent;

      double D = 2.0 * (   A[0] * (B[1] - C[1])
                         + B[0] * (C[1] - A[1])
                         + C[0] * (A[1] - B[1]) );

      double x =  (   (A[1] * A[1] + A[0] * A[0]) * (B[1] - C[1])
                    + (B[1] * B[1] + B[0] * B[0]) * (C[1] - A[1])
                    + (C[1] * C[1] + C[0] * C[0]) * (A[1] - B[1])  ) / D;

      double y =  (   (A[1] * A[1] + A[0] * A[0]) * (C[0] - B[0])
                    + (B[1] * B[1] + B[0] * B[0]) * (A[0] - C[0])
                    + (C[1] * C[1] + C[0] * C[0]) * (B[0] - A[0])  ) / D;

      circ_cent[0] = x;
      circ_cent[1] = y;

      return circ_cent;
    }


    //
    // TODO: This works for rectangles only, but not for general quadrilaterals
    //
    /** @brief Implementation of the calculation of a circumcenter for a quadrilateral in two dimensions. Mind that the user has to ensure that the quadrilateral actually has a circumcenter! */
    template <typename PointAccessorT, typename ElementT>
    typename PointAccessorT::value_type
    circumcenter(PointAccessorT const accessor, ElementT const & cell, viennagrid::quadrilateral_tag, viennagrid::dimension_tag<2>)
    {
      typedef typename PointAccessorT::value_type PointType;
      typedef typename viennagrid::result_of::coord<PointType>::type    CoordType;

      typedef typename viennagrid::result_of::const_element_range<ElementT, vertex_tag>::type         VertexOnCellRange;
      typedef typename viennagrid::result_of::iterator<VertexOnCellRange>::type      VertexOnCellIterator;

      PointType p0(0.0, 0.0);

      VertexOnCellRange vertices = viennagrid::elements<vertex_tag>(cell);
      for (VertexOnCellIterator vocit = vertices.begin();
           vocit != vertices.end();
           ++vocit)
      {
        p0 += accessor( *vocit );
      }

      p0 /= static_cast<CoordType>(vertices.size());

      return p0;
    }



    //
    // Calculation of circumcenter taken from Wikipedia (better reference required...)
    //
    /** @brief Implementation of the calculation of a circumcenter for a triangle in three dimensions */
    template <typename PointAccessorT, typename ElementT>
    typename PointAccessorT::value_type
    circumcenter(PointAccessorT const accessor, ElementT const & cell, viennagrid::triangle_tag, viennagrid::dimension_tag<3>)
    {
      typedef typename PointAccessorT::value_type PointType;

      PointType const & A = accessor( vertices(cell)[0] );
      PointType const & B = accessor( vertices(cell)[1] );
      PointType const & C = accessor( vertices(cell)[2] );

      double denominator = 2.0 * viennagrid::inner_prod(viennagrid::cross_prod(A-B, B-C), viennagrid::cross_prod(A-B, B-C));

      double alpha = viennagrid::inner_prod(B - C, B - C) * viennagrid::inner_prod(A - B, A - C);
      double beta  = viennagrid::inner_prod(A - C, A - C) * viennagrid::inner_prod(B - A, B - C);
      double gamma = viennagrid::inner_prod(A - B, A - B) * viennagrid::inner_prod(C - A, C - B);


      PointType circ_cent = A * (alpha/denominator) + B * (beta/denominator) + C * (gamma/denominator);

      return circ_cent;
    }


    //
    // Note: This works for rectangles only, but not for general quadrilaterals
    //
    /** @brief Implementation of the calculation of a circumcenter for a quadrilateral in three dimensions. Mind that the user has to ensure that the quadrilateral actually has a circumcenter! */
    template <typename PointAccessorT, typename ElementT>
    typename PointAccessorT::value_type
    circumcenter(PointAccessorT const accessor, ElementT const & cell, viennagrid::quadrilateral_tag, viennagrid::dimension_tag<3>)
    {
      typedef typename PointAccessorT::value_type PointType;
      typedef typename viennagrid::result_of::coord<PointType>::type    CoordType;

      typedef typename viennagrid::result_of::const_element_range<ElementT, vertex_tag>::type         VertexOnCellRange;
      typedef typename viennagrid::result_of::iterator<VertexOnCellRange>::type      VertexOnCellIterator;

      PointType p0(0.0, 0.0, 0.0);

      VertexOnCellRange vertices = viennagrid::elements<vertex_tag>(cell);
      for (VertexOnCellIterator vocit = vertices.begin();
           vocit != vertices.end();
           ++vocit)
      {
        p0 += accessor( *vocit );
      }

      p0 /= static_cast<CoordType>(vertices.size());

      return p0;
    }


    //
    // Calculation of circumcenter taken from Wikipedia (better reference required...)
    //
    /** @brief Implementation of the calculation of a circumcenter for a tetrahedron in three dimensions */
    template <typename PointAccessorT, typename ElementT>
    typename PointAccessorT::value_type
    circumcenter(PointAccessorT const accessor, ElementT const & cell, viennagrid::tetrahedron_tag, viennagrid::dimension_tag<3>)
    {
      typedef typename PointAccessorT::value_type PointType;

      typedef typename viennagrid::result_of::const_element_range<ElementT, vertex_tag>::type         VertexOnCellRange;
      typedef typename viennagrid::result_of::iterator<VertexOnCellRange>::type            VertexOnCellIterator;

      VertexOnCellRange vertices = viennagrid::elements<vertex_tag>(cell);
      VertexOnCellIterator vocit = vertices.begin();

      PointType const & O = accessor(*vocit); ++vocit;
      PointType const & A = accessor(*vocit) - O; ++vocit;
      PointType const & B = accessor(*vocit) - O; ++vocit;
      PointType const & C = accessor(*vocit) - O;

      PointType circ_cent = (cross_prod(A, B) * viennagrid::inner_prod(C, C)
                             + cross_prod(C, A) * viennagrid::inner_prod(B, B)
                             + cross_prod(B, C) * viennagrid::inner_prod(A, A)
                             ) / (viennagrid::inner_prod(A, viennagrid::cross_prod(B, C)) * 2.0);
      PointType cprodBC = viennagrid::cross_prod(B, C);
      if (std::fabs(viennagrid::inner_prod(A, cprodBC)) < 1e-10 * viennagrid::norm(cprodBC) )
      {
        std::cerr << "Near singularity in circum center calculation!" << std::endl;
        std::cerr << "A: " << A << std::endl;
        std::cerr << "B: " << B << std::endl;
        std::cerr << "C: " << C << std::endl;
        std::cerr << "B x C: " << viennagrid::cross_prod(B, C) << std::endl;
        throw std::runtime_error("Near singularity in circum center calculation!");
      }
      return circ_cent + O;
    }

    //
    // Note: This works for rectangles only, but not for general quadrilaterals
    //
    /** @brief Implementation of the calculation of a circumcenter for a hexahedron in three dimensions.  Mind that the user has to ensure that the quadrilateral actually has a circumcenter! */
    template <typename PointAccessorT, typename ElementT>
    typename PointAccessorT::value_type
    circumcenter(PointAccessorT const accessor, ElementT const & cell, viennagrid::hexahedron_tag, viennagrid::dimension_tag<3>)
    {
      typedef typename PointAccessorT::value_type PointType;
      typedef typename viennagrid::result_of::coord<PointType>::type    CoordType;

      typedef typename viennagrid::result_of::const_element_range<ElementT, vertex_tag>::type         VertexOnCellRange;
      typedef typename viennagrid::result_of::iterator<VertexOnCellRange>::type      VertexOnCellIterator;

      PointType p0(0.0, 0.0);

      VertexOnCellRange vertices = viennagrid::elements<vertex_tag>(cell);
      for (VertexOnCellIterator vocit = vertices.begin();
           vocit != vertices.end();
           ++vocit)
      {
        p0 += accessor(*vocit);
      }

      p0 /= static_cast<CoordType>(vertices.size());

      return p0;
    }

  } //namespace detail

  /** @brief The public interface function for the calculation of the circumcenter with explicit point accessor.
   *
   * @param element       The element for which the circumcenter should be computed
   * @param accessor      The point accessor providing point information for geometric calculation
   */
  template <typename PointAccessorT, typename ElementT>
  typename PointAccessorT::value_type
  circumcenter(PointAccessorT const accessor, ElementT const & element)
  {
    typedef typename PointAccessorT::value_type PointType;

    return detail::circumcenter(accessor,
                        element,
                        typename ElementT::tag(),
                        viennagrid::dimension_tag< result_of::static_size<PointType>::value >());
  }


  /** @brief The public interface function for the calculation of the circumcenter.
   *
   * @param element       The element for which the circumcenter should be computed
   */
  template<typename ElementT>
  typename viennagrid::result_of::point< ElementT >::type
  circumcenter(ElementT const & element)
  {
   return circumcenter( default_point_accessor(element), element );
  }


} //namespace viennagrid
#endif
