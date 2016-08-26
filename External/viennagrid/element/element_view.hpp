#ifndef VIENNAGRID_ELEMENT_VIEW_HPP
#define VIENNAGRID_ELEMENT_VIEW_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */


#include "viennagrid/element/element.hpp"
#include "viennagrid/mesh/mesh.hpp"

/** @file viennagrid/element/element_view.hpp
    @brief Provides routines for extracting the sub-elements of an element (e.g. all edges of a triangle)
*/

namespace viennagrid
{
  namespace result_of
  {

    /** @brief Returns a (non-const) view type for the provided element type or tag and the given container type selected for the view */
    template <typename something,
             typename element_type_or_tag,
             typename view_container_tag = std_deque_tag>
    struct element_view
    {
      typedef typename element_range<something, element_type_or_tag>::type::base_container_type base_container_type;
      typedef typename result_of::view<base_container_type, view_container_tag>::type type;
    };

    /** @brief Returns a const view type for the provided element type or tag and the given container type selected for the view */
    template <typename something,
             typename element_type_or_tag,
             typename view_container_tag = std_deque_tag>
    struct const_element_view
    {
      typedef typename const_element_range<something, element_type_or_tag>::type::base_container_type base_container_type;
      typedef typename result_of::view<const base_container_type, view_container_tag>::type type;
    };

  }

  /** @brief Returns an empty view object derived from the respective element. */
  template<typename element_type_or_tag, typename something>
  typename result_of::element_view<something, element_type_or_tag>::type
  element_view( something & s )
  {
    typedef typename result_of::element_tag<element_type_or_tag>::type element_tag;
    typedef typename result_of::element<something, element_tag>::type element_type;

    typename result_of::element_view<something, element_tag>::type view_obj;
    view_obj.set_base_container( viennagrid::get<element_type>( s.element_collection() ) );

    return view_obj;
  }


  /** @brief Returns a view object derived from the respective mesh or segment. Whenever the provided filter functor evaluates to true for an element, it is added to the view. Non-const version. */
  template<typename element_type_or_tag, typename something, typename functor>
  typename result_of::element_view<something, element_type_or_tag>::type
  element_view( something & s, functor f )
  {
    typedef typename result_of::element_tag<element_type_or_tag>::type element_tag;

    typedef typename result_of::element_range<something, element_tag>::type RangeType;
    typedef typename result_of::iterator<RangeType>::type IteratorType;

    RangeType range = viennagrid::elements<element_tag>(s);

    typename result_of::element_view<something, element_tag>::type view_obj;
    view_obj.set_base_container( *range.get_base_container() );

    for ( IteratorType it = range.begin(); it != range.end(); ++it )
    {
      if ( f(*it) )
        view_obj.insert_handle( it.handle() );
    }

    return view_obj;
  }

  /** @brief Returns a view object derived from the respective mesh or segment. Whenever the provided filter functor evaluates to true for an element, it is added to the view. Const version. */
  template<typename element_type_or_tag, typename something, typename functor>
  typename result_of::const_element_view<something, element_type_or_tag>::type
  element_view( something const & s, functor f )
  {
    typedef typename result_of::element_tag<element_type_or_tag>::type element_tag;

    typedef typename result_of::const_element_range<something, element_tag>::type RangeType;
    typedef typename result_of::iterator<RangeType>::type IteratorType;

    RangeType range = viennagrid::elements<element_tag>(s);

    typename result_of::element_view<something, element_tag>::type view_obj;
    view_obj.set_base_container( *range.get_base_container() );

    for ( IteratorType it = range.begin(); it != range.end(); ++it )
    {
      if ( f(*it) )
        view_obj.insert_handle( it.handle() );
    }

    return view_obj;
  }

}


#endif
