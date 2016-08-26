#ifndef VIENNAGRID_CONFIG_HEXAHEDRON_HPP
#define VIENNAGRID_CONFIG_HEXAHEDRON_HPP

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
#include "viennagrid/topology/line.hpp"
#include "viennagrid/topology/quadrilateral.hpp"

/** @file viennagrid/topology/hexahedron.hpp
    @brief Provides the topological definition of a hexahedron
*/

namespace viennagrid
{

  /** @brief A hypercube of dimension 3, aka. hexahedron */
  template <>
  struct hypercube_tag<3>
  {
    typedef hypercube_tag<2> facet_tag;

    static const int dim = 3;
    static std::string name() { return "hexahedron"; }
  };

  /** @brief Topological description of the 2-cells (quadrilateral faces) of a hexahedron */
  template <>
  struct boundary_elements<hypercube_tag<3>, hypercube_tag<2> >
  {
    typedef static_layout_tag     layout_tag;
    static const int num = 6;
  };

  /** @brief Topological description of the 1-cells (edges/lines) of a hexahedron */
  template <>
  struct boundary_elements<hypercube_tag<3>, simplex_tag<1> >
  {
    typedef static_layout_tag     layout_tag;
    static const int num = 12;
  };

  /** @brief Topological description of the 0-cells (vertices) of a hexahedron */
  template <>
  struct boundary_elements<hypercube_tag<3>, simplex_tag<0> >
  {
    typedef static_layout_tag     layout_tag;
    static const int num = 8;
  };



  namespace detail
  {
//         //fill edges according to reference orientation (use monospaced font for Full-HD ascii-art):
//         //
//         //              e11
//         //    v6-----------------v7
//         // e9  /|            e10/|
//         //    / |   e8      v5 / |
//         // v4------------------  |e7
//         //   |  |e6           |  |
//         // e2|  |______e5_____|__|
//         //   |  /v2         e4| /  v3
//         //   | /e1            |/ e3
//         // v0 ----------------  v1
//         //           e0
//         //

    template<typename BoundaryElementType>
    struct boundary_element_generator<hypercube_tag<3>, simplex_tag<1>, BoundaryElementType>
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

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(0), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(4), 1 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(1), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(3), 1 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(1), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(5), 1 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(2), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(3), 1 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(2), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(5), 1 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(3), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(7), 1 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(4), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(5), 1 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(4), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(6), 1 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(5), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(7), 1 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(6), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(7), 1 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );
      }
    };




//         //fill edges according to reference orientation (use monospaced font for Full-HD ascii-art):
//         //
//         //
//         //    v6-----------------v7
//         //     /|      f5       /|
//         //    / |           v5 / |
//         // v4------------------  |
//         //   |f2|  (f4-back)  |f3|
//         //   |  |_____________|__|
//         //   |  /v2   f1      | /  v3
//         //   | /              |/
//         // v0 ----------------  v1
//         //       (f0-bottom)
//         //
//         // orientation is such that facet normals point out of the cell

    template<typename BoundaryElementType>
    struct boundary_element_generator<hypercube_tag<3>, hypercube_tag<2>, BoundaryElementType>
    {
      template<typename element_type, typename inserter_type>
      static void create_boundary_elements(element_type & element, inserter_type & inserter)
      {
        BoundaryElementType boundary_element( inserter.get_physical_container_collection() );
        std::size_t index = 0;

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(0), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(1), 1 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(2), 2 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(3), 3 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(0), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(1), 1 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(4), 2 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(5), 3 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(0), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(2), 1 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(4), 2 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(6), 3 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(1), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(3), 1 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(5), 2 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(7), 3 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(2), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(3), 1 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(6), 2 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(7), 3 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );

        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(4), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(5), 1 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(6), 2 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(7), 3 );
        element.set_boundary_element( boundary_element, inserter.template insert<true, true>(boundary_element), index++ );
      }
    };

  } //topology
}

#endif

