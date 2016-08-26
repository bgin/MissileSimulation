#ifndef VIENNAGRID_TOPOLOGY_POINT_HPP
#define VIENNAGRID_TOPOLOGY_POINT_HPP

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

/** @file viennagrid/topology/vertex.hpp
    @brief Provides the topological definition of a point (vertex)
*/

namespace viennagrid
{

  /** @brief Topological description of a 0-cell (vertex). */
  template <>
  struct simplex_tag<0>
  {
    typedef viennagrid::null_type facet_tag;

    static const int dim = 0;
    static std::string name() { return "vertex"; }
  };

  //no need to have a separate subelements specialization here -> covered by default case

}

#endif

