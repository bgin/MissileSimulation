#ifndef VIENNAGRID_TOPOLOGY_QUADRILATERAL_HPP
#define VIENNAGRID_TOPOLOGY_QUADRILATERAL_HPP

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
#include "viennagrid/topology/vertex.hpp"
#include "viennagrid/topology/line.hpp"

/** @file viennagrid/topology/quadrilateral.hpp
    @brief Provides the topological definition of a quadrilateral
*/

namespace viennagrid
{
  /** @brief Topological description of a quadrilateral.*/
  template <>
  struct hypercube_tag<2>
  {
    typedef simplex_tag<1> facet_tag;

    static const int dim = 2;
    static std::string name() { return "quadrilateral"; }
  };

  /** @brief Topological description of the 1-cells (edges/lines) of a quadrilateral */
  template <>
  struct boundary_elements<hypercube_tag<2>, simplex_tag<1> >
  {
    typedef static_layout_tag     layout_tag;
    static const int num = 4;
  };

  /** @brief Topological description of the 0-cells (vertices) of a quadrilateral */
  template <>
  struct boundary_elements<hypercube_tag<2>, simplex_tag<0> >
  {
    typedef static_layout_tag     layout_tag;
    static const int num = 4;
  };

  namespace detail
  {
      //fill edges:
      //
      // Reference orientation: (v... vertices, e...edges)
      //        e3
      // v2 --------- v3
      //    |       |
      // e1 |       | e2
      //    |       |
      // v0 --------- v1
      //        e0

    template<typename BoundaryElementType>
    struct boundary_element_generator<hypercube_tag<2>, simplex_tag<1>, BoundaryElementType>
    {
      template<typename element_type, typename inserter_type>
      static void create_boundary_elements(element_type & element, inserter_type & inserter)
      {
        BoundaryElementType boundary_element( inserter.get_physical_container_collection() );
        std::size_t index = 0;

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(0), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(1), 1 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(0), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(2), 1 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(1), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(3), 1 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(2), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(3), 1 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );
      }
    };

  }

}

#endif

