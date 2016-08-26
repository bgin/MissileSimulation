#ifndef VIENNAGRID_TOPOLOGY_PLC_HPP
#define VIENNAGRID_TOPOLOGY_PLC_HPP

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
#include "viennagrid/topology/polygon.hpp"

/** @file viennagrid/topology/plc.hpp
    @brief Provides the topological definition of a piecewise linear complex
*/


namespace viennagrid
{

  /** @brief A tag for identifying piecewise linear complexes (PLCs) */
  struct plc_tag
  {
    typedef line_tag facet_tag;

    static const int dim = 2;
    static std::string name() { return "PLC"; }
  };

  //Line:
  /** @brief Topological description of the 0-cells of a polygon */
  template <>
  struct boundary_elements<plc_tag, vertex_tag>
  {
    typedef dynamic_layout_tag     layout_tag;
    static const int num = -1;
  };

  /** @brief Topological description of the 1-cells (edges/lines) of a polygon */
  template <>
  struct boundary_elements<plc_tag, line_tag>
  {
    typedef dynamic_layout_tag     layout_tag;
    static const int num = -1;
  };



  namespace detail
  {
    template<typename BoundaryElementType>
    struct boundary_element_generator<plc_tag, line_tag, BoundaryElementType>
    {
      template<typename element_type, typename inserter_type>
      static void create_boundary_elements(element_type &, inserter_type &)
      {
      }
    };

    template<typename BoundaryElementType>
    struct boundary_element_generator<plc_tag, simplex_tag<0>, BoundaryElementType>
    {
      template<typename element_type, typename inserter_type>
      static void create_boundary_elements(element_type & plc, inserter_type &)
      {
        typedef typename viennagrid::result_of::element<element_type, line_tag>::type LineType;
        typedef typename viennagrid::result_of::element_range<element_type, line_tag>::type LineRange;
        typedef typename viennagrid::result_of::iterator<LineRange>::type LineIterator;

        LineRange lines = elements<line_tag>(plc);
        for (LineIterator lit = lines.begin(); lit != lines.end(); ++lit)
        {
          typedef typename viennagrid::result_of::element_range<LineType, vertex_tag>::type VertexOnLineRange;
          typedef typename viennagrid::result_of::iterator<VertexOnLineRange>::type VertexOnLineHandleIterator;

          VertexOnLineRange vertices = elements<vertex_tag>(*lit);
          for (VertexOnLineHandleIterator vlhit = vertices.begin(); vlhit != vertices.end(); ++vlhit)
            plc.container( vertex_tag() ).insert_unique_handle( vlhit.handle() );
        }

      }
    };
  } //topology


  /** @brief Returns the hole points associated with a PLC */
  template<typename PLCT>
  typename PLCT::appendix_type & hole_points( PLCT & plc )
  {
    return plc.appendix();
  }

  /** @brief Returns the hole points associated with a PLC */
  template<typename PLCT>
  typename PLCT::appendix_type const & hole_points( PLCT const & plc )
  {
    return plc.appendix();
  }

}

#endif

