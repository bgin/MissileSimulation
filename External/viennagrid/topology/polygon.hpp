#ifndef VIENNAGRID_TOPOLOGY_POLYGON_HPP
#define VIENNAGRID_TOPOLOGY_POLYGON_HPP

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
#include "viennagrid/topology/simplex.hpp"

/** @file viennagrid/topology/polygon.hpp
    @brief Provides the topological definition of a polygon
*/

namespace viennagrid
{

  /** @brief A tag representing polygons */
  struct polygon_tag
  {
    typedef simplex_tag<1> facet_tag;

    static const int dim = 2;
    static std::string name() { return "polygon"; }
  };


  //Line:
  /** @brief Topological description of the 0-cells of a polygon */
  template <>
  struct boundary_elements<polygon_tag, vertex_tag>
  {
    typedef dynamic_layout_tag     layout_tag;
    static const int num = -1;
  };

  /** @brief Topological description of the 1-cells (edges/lines) of a polygon */
  template <>
  struct boundary_elements<polygon_tag, line_tag>
  {
    typedef dynamic_layout_tag     layout_tag;
    static const int num = -1;
  };


  namespace detail
  {
    template<typename BoundaryElementType>
    struct boundary_element_generator<polygon_tag, simplex_tag<1>, BoundaryElementType>
    {
      template<typename element_type, typename inserter_type>
      static void create_boundary_elements(element_type & element, inserter_type & inserter)
      {
        BoundaryElementType boundary_element( inserter.get_physical_container_collection() );

        std::size_t index = 0;
        for (std::size_t i = 0; i < element.container( dimension_tag<0>() ).size()-1; ++i)
        {
          boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(i), 0 );
          boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(i+1), 1 );
          element.set_boundary_element( boundary_element, inserter(boundary_element), index++ );
        }


        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at( element.container( dimension_tag<0>() ).size()-1 ), 0 );
        boundary_element.container(dimension_tag<0>()).set_handle( element.container( dimension_tag<0>() ).handle_at(0), 1 );
        element.set_boundary_element( boundary_element, inserter(boundary_element), index++ );
      }
    };


  } //topology
}

#endif

