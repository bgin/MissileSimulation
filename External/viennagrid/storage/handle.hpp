#ifndef VIENNAGRID_STORAGE_HANDLE_HPP
#define VIENNAGRID_STORAGE_HANDLE_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include <iterator>
#include <vector>
#include <map>
#include <algorithm>

#include "viennagrid/meta/typemap.hpp"
#include "viennagrid/storage/id.hpp"
#include "viennagrid/storage/forwards.hpp"

/** @file viennagrid/storage/handle.hpp
    @brief Defines the generic layer for handles (generalized references) to elements
*/

namespace viennagrid
{
  namespace detail
  {

    namespace result_of
    {

      template<typename base_container_type, typename handle_tag>
      struct handle_type
      {};

      template<typename base_container_type>
      struct handle_type<base_container_type, no_handle_tag>
      {
        typedef viennagrid::null_type type;
      };

      template<typename base_container_type>
      struct handle_type<base_container_type, pointer_handle_tag>
      {
        typedef typename base_container_type::pointer type;
      };

      template<typename base_container_type>
      struct handle_type<base_container_type, iterator_handle_tag>
      {
        typedef typename base_container_type::iterator type;
      };

      template<typename base_container_type>
      struct handle_type<base_container_type, id_handle_tag>
      {
        typedef typename base_container_type::value_type::id_type type;
      };




      template<typename base_container_type, typename handle_tag>
      struct const_handle_type
      {};

      template<typename base_container_type>
      struct const_handle_type<base_container_type, no_handle_tag>
      {
        typedef viennagrid::null_type type;
      };

      template<typename base_container_type>
      struct const_handle_type<base_container_type, pointer_handle_tag>
      {
        typedef typename base_container_type::const_pointer type;
      };

      template<typename base_container_type>
      struct const_handle_type<base_container_type, iterator_handle_tag>
      {
        typedef typename base_container_type::const_iterator type;
      };

      template<typename base_container_type>
      struct const_handle_type<base_container_type, id_handle_tag>
      {
        typedef typename base_container_type::value_type::const_id_type type;
      };




      // default = iterator
      template<typename handle_type>
      struct value_type
      {
        typedef typename viennagrid::detail::IF<
            viennagrid::detail::is_const_iterator<handle_type>::value,
            const typename handle_type::value_type,
            typename handle_type::value_type
        >::type type;
      };

      // pointer
      template<typename value_type_>
      struct value_type< value_type_ * >
      {
        typedef value_type_ type;
      };

      template<typename value_type_>
      struct value_type< const value_type_ * >
      {
        typedef value_type_ type;
      };

      // id
      template<typename value_type_, typename base_id_type_>
      struct value_type< smart_id<value_type_, base_id_type_> >
      {
        typedef value_type_ type;
      };

      template<typename value_type_, typename base_id_type_>
      struct value_type< smart_id<const value_type_, base_id_type_> >
      {
        typedef value_type_ type;
      };




      // default = iterator
      template<typename handle_type>
      struct handle_tag
      {
        typedef iterator_handle_tag type;
      };

      // no handle
      template<>
      struct handle_tag<viennagrid::null_type>
      {
        typedef no_handle_tag type;
      };

      // pointer
      template<typename value_type>
      struct handle_tag<value_type *>
      {
        typedef pointer_handle_tag type;
      };

      // id
      template<typename value_type_, typename base_id_type_>
      struct handle_tag< smart_id<value_type_, base_id_type_> >
      {
        typedef id_handle_tag type;
      };

    }



    template<typename container_type, typename handle_type>
    void set_handle_invalid( container_type const &, handle_type & handle, pointer_handle_tag )
    { handle = NULL; }

    template<typename container_type, typename handle_type>
    void set_handle_invalid( container_type & container, handle_type & handle, iterator_handle_tag )
    { handle = container.end(); }

    template<typename container_type, typename handle_type>
    void set_handle_invalid( container_type const & container, handle_type & handle, iterator_handle_tag )
    { handle = container.end(); }

    template<typename container_type, typename handle_type>
    void set_handle_invalid( container_type & /*container*/, handle_type & handle, id_handle_tag )
    { handle = handle_type(); }

    template<typename container_type, typename handle_type>
    void set_handle_invalid( container_type const & /*container*/, handle_type & handle, id_handle_tag )
    { handle = handle_type(); }


    template<typename container_type, typename handle_type>
    void set_handle_invalid( container_type const & container, handle_type & handle )
    { set_handle_invalid(container, handle, typename result_of::handle_tag<handle_type>::type()); }

    template<typename container_type, typename handle_type>
    void set_handle_invalid( container_type & container, handle_type & handle )
    { set_handle_invalid(container, handle, typename result_of::handle_tag<handle_type>::type()); }




    template<typename container_type, typename handle_type>
    bool is_handle_invalid( container_type const & container, handle_type handle )
    {
      handle_type tmp;
      set_handle_invalid(container, tmp);
      return handle == tmp;
    }

    template<typename container_type, typename handle_type>
    bool is_handle_invalid( container_type & container, handle_type handle )
    {
      handle_type tmp;
      set_handle_invalid(container, tmp);
      return handle == tmp;
    }






    template<typename HandleTagT>
    struct dereference_handle_helper;

    template<typename HandleTagT>
    struct dereference_handle_helper
    {
      template<typename ContainerT, typename HandleT>
      static typename result_of::value_type<HandleT>::type & dereference_handle( ContainerT &, HandleT handle )
      { return *handle; }

      template<typename ContainerT, typename HandleT>
      static typename result_of::value_type<HandleT>::type const & dereference_handle( ContainerT const &, HandleT handle )
      { return *handle; }
    };


    template<>
    struct dereference_handle_helper<id_handle_tag>
    {
      template<typename ContainerT, typename HandleT>
      static typename result_of::value_type<HandleT>::type & dereference_handle( ContainerT & container, HandleT handle )
      {
        typedef typename result_of::value_type<HandleT>::type ElementType;
        typedef typename result_of::id<ElementType>::type IDType;

        return *std::find_if(
            container.begin(),
            container.end(),
            id_compare<IDType>(handle)
        );
      }

      template<typename ContainerT, typename HandleT>
      static typename result_of::value_type<HandleT>::type const & dereference_handle( ContainerT const & container, HandleT handle )
      {
        typedef typename result_of::value_type<HandleT>::type ElementType;
        typedef typename result_of::id<ElementType>::type IDType;

        return *std::find_if(
            container.begin(),
            container.end(),
            id_compare<IDType>(handle)
        );
      }
    };


    template<typename ContainerT, typename HandleT>
    typename result_of::value_type<HandleT>::type & dereference_handle( ContainerT & container, HandleT handle )
    { return dereference_handle_helper< typename result_of::handle_tag<HandleT>::type >::dereference_handle(container, handle); }

    template<typename ContainerT, typename HandleT>
    typename result_of::value_type<HandleT>::type const & dereference_handle( ContainerT const & container, HandleT handle )
    { return dereference_handle_helper< typename result_of::handle_tag<HandleT>::type >::dereference_handle(container, handle); }

    template<typename ContainerT, typename HandleT>
    typename result_of::value_type<HandleT>::type const & dereference_handle_const( ContainerT const & container, HandleT handle )
    { return dereference_handle_helper< typename result_of::handle_tag<HandleT>::type >::dereference_handle(container, handle); }




    template<typename container_type, typename value_type, typename handle_tag>
    struct handle_helper;


    template<typename container_type, typename value_type>
    struct handle_helper<container_type, value_type, no_handle_tag>
    {
        static typename result_of::handle_type<container_type, no_handle_tag>::type handle( container_type &, value_type & )
        { return typename result_of::handle_type<container_type, no_handle_tag>::type(); }

        static typename result_of::const_handle_type<container_type, no_handle_tag>::type handle( container_type const &, value_type const & )
        { return typename result_of::handle_type<container_type, no_handle_tag>::type(); }
    };

    template<typename container_type, typename value_type>
    struct handle_helper<container_type, value_type, iterator_handle_tag>
    {
        static typename result_of::handle_type<container_type, iterator_handle_tag>::type handle( container_type & container, value_type & value )
        {
          for (typename container_type::iterator it = container.begin(); it != container.end(); ++it)
            if ( &(*it) == &value ) return it;
          return container.end();
        }

        static typename result_of::const_handle_type<container_type, iterator_handle_tag>::type handle( container_type const & container, value_type const & value )
        {
          for (typename container_type::const_iterator it = container.begin(); it != container.end(); ++it)
            if ( &(*it) == &value ) return it;
          return container.end();
        }
    };

    template<typename container_type, typename value_type>
    struct handle_helper<container_type, value_type, pointer_handle_tag>
    {
      static typename result_of::handle_type<container_type, pointer_handle_tag>::type handle( container_type &, value_type & value )
      { return &value; }

      static typename result_of::const_handle_type<container_type, pointer_handle_tag>::type handle( container_type const &, value_type const & value )
      { return &value; }
    };

    template<typename container_type, typename value_type>
    struct handle_helper<container_type, value_type, id_handle_tag>
    {
      static typename result_of::handle_type<container_type, id_handle_tag>::type handle( container_type &, value_type & value )
      { return value.id(); }

      static typename result_of::const_handle_type<container_type, id_handle_tag>::type handle( container_type const &, value_type const & value )
      { return value.id(); }
    };



    template<typename container_type, typename value_type, typename handle_tag>
    typename result_of::handle_type<container_type, handle_tag>::type handle( container_type & container, value_type & value, handle_tag )
    { return handle_helper<container_type, value_type, handle_tag>::handle( container,value ); }

    template<typename container_type, typename value_type, typename handle_tag>
    typename result_of::const_handle_type<container_type, handle_tag>::type handle( container_type const & container, value_type const & value, handle_tag )
    { return handle_helper<container_type, value_type, handle_tag>::handle( container,value ); }


  }

}

#endif
