#ifndef VIENNAGRID_STORAGE_ALGORITHM_HPP
#define VIENNAGRID_STORAGE_ALGORITHM_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include "viennagrid/storage/collection.hpp"
#include "viennagrid/storage/container_collection.hpp"
#include "viennagrid/storage/view.hpp"

#include "viennagrid/meta/algorithm.hpp"


/** @file viennagrid/storage/algorithm.hpp
    @brief Provides STL-like algorithms for manipulating containers in ViennaGrid.
*/

namespace viennagrid
{
  namespace detail
  {
    template<typename collection_type, typename functor>
    struct for_each_functor
    {
      for_each_functor(collection_type & collection, functor f) : collection_(collection), f_(f) {}

      template<typename key_type, typename value_type>
      void operator()( viennagrid::detail::tag< viennagrid::static_pair<key_type, value_type> > )
      { f_( viennagrid::get<key_type>(collection_) ); }

      collection_type & collection_;
      functor           f_;
    };

    template<typename collection_type, typename functor>
    void for_each( collection_type & collection, functor f)
    {
      for_each_functor<collection_type, functor> ff(collection, f);
      viennagrid::detail::for_each< typename collection_type::typemap >(ff);
    }

    template<typename typelist, typename collection_type, typename functor>
    void for_each_typelist(collection_type & collection, functor & f)
    {
      for_each_functor<collection_type, functor> ff(collection, f);
      viennagrid::detail::for_each<typelist>(ff);
    }


    template<typename collection_type_1, typename collection_type_2, typename functor>
    class dual_for_each_functor
    {
    public:

      dual_for_each_functor(
          collection_type_1 & container_collection_1,
          collection_type_2 & container_collection_2,
          functor f) :
              container_collection_1_(container_collection_1),
              container_collection_2_(container_collection_2),
              f_(f) {}

      template<typename type>
      void operator() ( viennagrid::detail::tag<type> )
      {
          f_(
            viennagrid::get<type>(container_collection_1_),
            viennagrid::get<type>(container_collection_2_)
          );
      }

    private:
      collection_type_1 & container_collection_1_;
      collection_type_2 & container_collection_2_;
      functor             f_;
    };


    template<typename predicate>
    class copy_functor
    {
    public:
      copy_functor(predicate pred) : pred_(pred) {}

      template<typename src_container_type, typename dst_container_type>
      void operator() (const src_container_type & src_container, dst_container_type & dst_container)
      {
        for (typename src_container_type::const_iterator it = src_container.begin(); it != src_container.end(); ++it)
          if (pred_(*it))
              dst_container.insert( *it );
      }

    private:
      predicate pred_;
    };




    template<typename src_container_typelist, typename dst_container_typelist>
    void copy(const collection<src_container_typelist> & src, collection<dst_container_typelist> & dst)
    {
      detail::dual_for_each_functor<
          const collection<src_container_typelist>,
          collection<dst_container_typelist>,
          copy_functor<viennagrid::detail::true_predicate>
          > functor(src, dst, copy_functor<viennagrid::detail::true_predicate>(viennagrid::detail::true_predicate()));

      typedef typename viennagrid::result_of::common_values<
          collection<src_container_typelist>,
          collection<dst_container_typelist>
      >::type typelist;

      viennagrid::detail::for_each<typelist>(functor);
    }

    template<typename src_container_typelist, typename dst_container_typelist, typename predicate>
    void copy_if(const collection<src_container_typelist> & src, collection<dst_container_typelist> & dst, predicate pred)
    {
      detail::dual_for_each_functor<
          const collection<src_container_typelist>,
          collection<dst_container_typelist>,
          copy_functor<predicate>
          > functor(src, dst, copy_functor<predicate>(pred));

      typedef typename viennagrid::result_of::common_values<
          collection<src_container_typelist>,
          collection<dst_container_typelist>
      >::type typelist;

      viennagrid::detail::for_each<typelist>(functor);
    }





    template<typename predicate>
    class handle_functor
    {
    public:
      handle_functor(predicate pred) : pred_(pred) {}

      template<typename container_type, typename base_container_type, typename handle_container_tag>
      void operator() (container_type & src_container, viennagrid::view<base_container_type, handle_container_tag> & dst_view)
      {
          for (typename container_type::iterator it = src_container.begin(); it != src_container.end(); ++it)
              if (pred_( *it ))
                  dst_view.insert_handle( it.handle() );
      }


    private:
      predicate pred_;
    };


    template<typename src_container_typelist, typename dst_container_typelist>
    void handle(collection<src_container_typelist> & src, collection<dst_container_typelist> & dst)
    {
      detail::dual_for_each_functor<
          collection<src_container_typelist>,
          collection<dst_container_typelist>,
          handle_functor<viennagrid::detail::true_predicate>
          > functor(src, dst, handle_functor<viennagrid::detail::true_predicate>(viennagrid::detail::true_predicate()));

      typedef typename viennagrid::result_of::common_values<
          collection<src_container_typelist>,
          collection<dst_container_typelist>
      >::type typelist;

      viennagrid::detail::for_each<typelist>(functor);
    }

    template<typename src_container_typelist, typename dst_container_typelist, typename predicate>
    void handle_if(collection<src_container_typelist> & src, collection<dst_container_typelist> & dst, predicate pred)
    {
      detail::dual_for_each_functor<
          collection<src_container_typelist>,
          collection<dst_container_typelist>,
          handle_functor<predicate>
          > functor(src, dst, handle_functor<predicate>(pred));

      typedef typename viennagrid::result_of::common_values<
          collection<src_container_typelist>,
          collection<dst_container_typelist>
      >::type typelist;

      viennagrid::detail::for_each<typelist>(functor);
    }

  }
}

#endif
