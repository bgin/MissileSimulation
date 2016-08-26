#ifndef VIENNAGRID_ELEMENT_KEY_HPP
#define VIENNAGRID_ELEMENT_KEY_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */


#include <map>
#include <iostream>
#include <algorithm>

#include "viennagrid/forwards.hpp"
#include "viennagrid/element/element.hpp"
#include "viennagrid/topology/vertex.hpp"

#include "viennagrid/storage/container.hpp"
#include "viennagrid/storage/hidden_key_map.hpp"

/** @file viennagrid/element/element_key.hpp
    @brief Provides a key that uniquely identifies n-cells
*/

namespace viennagrid
{

  /** @brief A key type that uniquely identifies an element by its vertices */
  template <typename element_type>
  class element_key
  {
    typedef typename element_type::tag            ElementTag;
    typedef typename viennagrid::result_of::element< element_type, vertex_tag >::type vertex_type;
    typedef typename vertex_type::id_type id_type;

  public:

    explicit element_key( std::vector< id_type > const & ids) : vertex_ids(ids) {}

    explicit element_key( const element_type & el2) : vertex_ids( viennagrid::elements<vertex_tag>(el2).size() )
    {
      typedef typename viennagrid::result_of::const_element_range< element_type, vertex_tag >::type vertex_range;
      typedef typename viennagrid::result_of::const_iterator< vertex_range >::type const_iterator;

      std::size_t i = 0;
      vertex_range vertices_el2 = elements<vertex_tag>(el2);
      for (const_iterator vit = vertices_el2.begin();
           vit != vertices_el2.end();
           ++vit, ++i)
        vertex_ids[i] = static_cast<id_type>( (*vit).id() );
      //sort it:
      std::sort(vertex_ids.begin(), vertex_ids.end());
    }

    element_key( const element_key & ek2) : vertex_ids(ek2.vertex_ids.size())
    {
      std::copy( ek2.vertex_ids.begin(), ek2.vertex_ids.end(), vertex_ids.begin() );
    }

    bool operator < (element_key const & epc2) const
    {
      if ( vertex_ids.size() != epc2.vertex_ids.size() )
          return vertex_ids.size() < epc2.vertex_ids.size();

      for (std::size_t i=0; i < vertex_ids.size(); ++i)
      {
        if ( vertex_ids[i] > epc2.vertex_ids[i] )
          return false;
        else if ( vertex_ids[i] < epc2.vertex_ids[i] )
          return true;
      }
      return false;
    }

    void print() const
    {
      for (typename std::vector<id_type>::const_iterator vit = vertex_ids.begin();
            vit != vertex_ids.end();
            ++vit)
        std::cout << *vit << " ";
      std::cout << std::endl;
    }

  private:
      // TODO: rather than hard-wiring std::vector, make this configurable
    std::vector< id_type > vertex_ids;
  };
}



namespace viennagrid
{
  /** @brief A tag for selecting element_key as a key type within metafunctions */
  struct element_key_tag {};

  namespace result_of
  {
    /** \cond */
    template<typename element_type>
    struct hidden_key_map_key_type_from_tag<element_type, element_key_tag>
    {
      typedef element_key<element_type> type;
    };
    /** \endcond */
  }
}

#endif
