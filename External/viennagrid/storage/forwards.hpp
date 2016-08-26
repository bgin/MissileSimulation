#ifndef VIENNAGRID_STORAGE_FORWARDS_HPP
#define VIENNAGRID_STORAGE_FORWARDS_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include "viennagrid/meta/typemap.hpp"

/** @file viennagrid/storage/forwards.hpp
    @brief Contains forward declarations and definition for storage layer classes, tags, ...
*/

namespace viennagrid
{
  /** @brief The ViennaGrid namespace for the storage layer */

  /** @brief A tag defining a smart ID for a base type
    *
    * @tparam BaseT       The base type to which the smart ID references to
  */
  template<typename BaseT>
  struct smart_id_tag;

  /** @brief A smart id encapsulates a simple ID type (e.g. int) and adds additional information about the type which the ID references.
    *
    * @tparam BaseT       The base type to which the smart ID references to
    * @tparam BaseIDT     The base ID type which is encapsulated, e.g. int
  */
  template<typename BaseT, typename BaseIDT>
  class smart_id;


  // handles

  /** @brief A tag defining that no handles are used */
  struct no_handle_tag {};
  /** @brief A tag defining that pointer handles are used */
  struct pointer_handle_tag {};
  /** @brief A tag defining that ID handles are used */
  struct id_handle_tag {};
  /** @brief A tag defining that iterator handles are used */
  struct iterator_handle_tag {};


  // container
  /** @brief A tag indicating default behaviour */
  struct default_tag;

  /** @brief A tag indicating that std::vector is used as a container */
  struct std_vector_tag;
  /** @brief A tag indicating that std::deque is used as a container */
  struct std_deque_tag;
  /** @brief A tag indicating that std::list is used as a container */
  struct std_list_tag;

  struct id_compare_tag;

  /** @brief A tag indicating that std::set is used as a container */
  template<typename compare_tag = default_tag>
  struct std_set_tag;
//     /** @brief A tag indicating that std::set with ID compare is used as a container */
//     struct std_id_set_tag;
  /** @brief A tag indicating that std::map is used as a container */
  struct std_map_tag;

  /** @brief A tag indicating that storage::static_array should be used
    *
    * @tparam SizeV       The static size of the array
  */
  template<int SizeV>
  struct static_array_tag
  {
    static const int size = SizeV;
  };



  /** @brief A typemap defining default container configuration for a container collection */
  typedef viennagrid::make_typemap<
      default_tag,
      std_deque_tag
  >::type default_container_config;

  /** @brief A typemap defining default container configuration for a view container collection */
  typedef viennagrid::make_typemap<
      default_tag,
      std_set_tag<id_compare_tag>
  >::type default_view_container_config;


  /** @brief A tag indicating that a handled container is used
    *
    * @tparam ContainerTagT   A tag defining the underlying container, e.g. std_vector_tag
    * @tparam HandleTagT      A tag defining which handle type is used, e.g. pointer_handle_tag
  */
  template<typename ContainerTagT, typename HandleTagT>
  struct handled_container_tag
  {
    typedef ContainerTagT   container_tag;
    typedef HandleTagT      handle_tag;
  };

  namespace result_of
  {
    /** \cond */
    template <typename ContainerTag, typename HandleTag>
    struct handled_container
    {
        typedef handled_container_tag<ContainerTag, HandleTag>   tag;
    };
    /** \endcond */
  }
}

#endif
