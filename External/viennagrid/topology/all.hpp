#ifndef VIENNAGRID_TOPOLOGY_ALL_HPP
#define VIENNAGRID_TOPOLOGY_ALL_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

/** @file viennagrid/topology/all.hpp
    @brief Convenience header file for all topological objects
*/

// simplex:
#include "viennagrid/topology/simplex.hpp"

//one-dimensional:
#include "viennagrid/topology/line.hpp"

//two-dimensional:
#include "viennagrid/topology/quadrilateral.hpp"

#include "viennagrid/topology/polygon.hpp"

//three-dimensional:
#include "viennagrid/topology/hexahedron.hpp"

#endif

