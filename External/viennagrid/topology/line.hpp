#ifndef VIENNAGRID_TOPOLOGY_LINE_HPP
#define VIENNAGRID_TOPOLOGY_LINE_HPP

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

/** @file viennagrid/topology/line.hpp
    @brief Provides the topological definition of a line
*/

namespace viennagrid
{

  //for compatibility: allow hypercube<1> to be used as line_tag as well:
  /** @brief Topological description of a 1-cell (line). Same as simplex_tag<1>. */
  template <>
  struct hypercube_tag<1>
  {
    static const int dim = 1;
    static std::string name() { return "Line"; }
  };


  namespace detail
  {

    //Line:
    /** @brief Topological description of the 0-cells of a line */
    template<typename BoundaryElementType>
    struct boundary_element_generator<simplex_tag<1>, simplex_tag<0>, BoundaryElementType>
    {
      template<typename element_type, typename inserter_type>
      static void create_boundary_elements(element_type &, inserter_type &) {}
    };

  }

}

#endif

