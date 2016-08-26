#ifndef VIENNAGRID_FUNCTORS_HPP
#define VIENNAGRID_FUNCTORS_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

/** @file viennagrid/functors.hpp
    @brief A collection of general functors
*/

namespace viennagrid
{
  /** @brief A trivial functor which always returns true */
  struct true_functor
  {
    typedef bool result_type;

    template<typename ValueT>
    bool operator()(ValueT const &) const
    { return true; }
  };
}


#endif
