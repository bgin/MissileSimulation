#ifndef VIENNAGRID_STORAGE_INSERTER_HPP
#define VIENNAGRID_STORAGE_INSERTER_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include "viennagrid/storage/container_collection.hpp"
#include "viennagrid/storage/container_collection_element.hpp"

/** @file viennagrid/storage/inserter.hpp
    @brief Defines the inserter functors for adding elements to a container or collection
*/

namespace viennagrid
{
  namespace detail
  {
    /** \cond */

    /** @brief Used to avoid unreachable code warnings if a runtime-check for the compile-time variable generate_id is used instead. */
    template <bool generate_id, typename ValueT>
    struct physical_insert_id_dispatcher
    {
      template <typename ContainerT, typename ElementT, typename IDGeneratorT>
      static void apply(ContainerT & container, ElementT & elem, IDGeneratorT & id_generator)
      {
        if (!container.is_present( elem ) )
          viennagrid::detail::set_id(elem, id_generator( viennagrid::detail::tag<ValueT>() ) );
      }
    };

    template <typename ValueT>
    struct physical_insert_id_dispatcher<false, ValueT>
    {
      template <typename ContainerT, typename ElementT, typename IDGeneratorT>
      static void apply(ContainerT &, ElementT & elem, IDGeneratorT & id_generator)
      {
        id_generator.set_max_id( elem.id() );
      }
    };

    /** \endcond */
  }

  /** @brief An inserter class which adds elements to a the provided container collection. For example, this inserts a triangle into a segment s, but not into the mesh or segment where s was derived from. */
  template<typename container_collection_type, typename change_counter_type, typename id_generator_type_>
  class physical_inserter
  {
  public:
    typedef container_collection_type physical_container_collection_type;
    typedef id_generator_type_ id_generator_type;

    physical_inserter() : collection(0), change_counter(0) {}
    physical_inserter(container_collection_type & collection_obj) : collection(&collection_obj), change_counter(0) {}
    physical_inserter(container_collection_type & collection_obj, id_generator_type id_generator_) : collection(&collection_obj), change_counter(0), id_generator(id_generator_) {}

    physical_inserter(container_collection_type & collection_obj, change_counter_type & change_counter_) :
        collection(&collection_obj), change_counter(&change_counter_) {}
    physical_inserter(container_collection_type & collection_obj, change_counter_type & change_counter_, id_generator_type id_generator_) :
        collection(&collection_obj), change_counter(&change_counter_), id_generator(id_generator_) {}

    void set_mesh_info(container_collection_type & collection_obj, change_counter_type & change_counter_)
    {
      collection     = &collection_obj;
      change_counter = &change_counter_;
    }

    template<bool generate_id, bool call_callback, typename value_type>
    std::pair<
        typename viennagrid::result_of::container_of<container_collection_type, value_type>::type::handle_type,
        bool
    >
    insert( const value_type & element )
    {
      return physical_insert<generate_id, call_callback>( element, *this );
    }

    template<typename value_type>
    std::pair<
        typename viennagrid::result_of::container_of<container_collection_type, value_type>::type::handle_type,
        bool
    >
    operator()( const value_type & element )
    {
      return insert<true, true>( element );
    }

    container_collection_type & get_physical_container_collection() { return *collection; }
    container_collection_type const & get_physical_container_collection() const { return *collection; }

    id_generator_type & get_id_generator() { return id_generator; }
    id_generator_type const & get_id_generator() const { return id_generator; }

    template<bool generate_id, bool call_callback, typename value_type, typename inserter_type>
    std::pair<
        typename viennagrid::result_of::container_of<container_collection_type, value_type>::type::handle_type,
        bool
    >
    physical_insert( value_type element, inserter_type & inserter )
    {
      typedef typename viennagrid::result_of::container_of<container_collection_type, value_type>::type container_type;
      typedef typename viennagrid::result_of::container_of<container_collection_type, value_type>::type::handle_type handle_type;


      container_type & container = viennagrid::get< value_type >( *collection );

      detail::physical_insert_id_dispatcher<generate_id, value_type>::apply(container, element, id_generator);
      //if ( generate_id && !container.is_present( element ) )
      //    viennagrid::detail::set_id(element, id_generator( viennagrid::detail::tag<value_type>() ) );

      //if (!generate_id)
      //  id_generator.set_max_id( element.id() );

      std::pair<handle_type, bool> ret = container.insert( element );
      if (change_counter) ++(*change_counter);

      if (call_callback)
          viennagrid::detail::insert_callback(
              container.dereference_handle(ret.first),
              ret.second,
              inserter);

      inserter.handle_insert( ret.first, viennagrid::detail::tag<value_type>() );

      return ret;
    }

    template<typename handle_type, typename value_type>
    void handle_insert( handle_type, viennagrid::detail::tag<value_type> ) {}

  private:

    container_collection_type * collection;
    change_counter_type * change_counter;

    id_generator_type id_generator;
  };







  /** @brief Recursive inserter which inserts an element into the provided collection and all dependent collections.
    *
    * For example, if a segment s was derived from another segment t and a mesh m, adding an element to s will also insert the element into t and m.
    */
  template<typename view_collection_type, typename change_counter_type, typename dependent_inserter_type>
  class recursive_inserter
  {
  public:
    recursive_inserter() : view_collection(0), change_counter(0), dependent_inserter(0) {}
    recursive_inserter(view_collection_type & collection_) : view_collection(&collection_), change_counter(0), dependent_inserter(0) {}

    recursive_inserter(view_collection_type & collection_obj, change_counter_type & change_counter_) :
        view_collection(&collection_obj), change_counter(&change_counter_) {}
    recursive_inserter(view_collection_type & collection_obj, dependent_inserter_type & dependent_inserter_) :
        view_collection(&collection_obj), change_counter(0), dependent_inserter(&dependent_inserter_) {}

    recursive_inserter(view_collection_type & collection_obj, change_counter_type & change_counter_, dependent_inserter_type & dependent_inserter_) :
        view_collection(&collection_obj), change_counter(&change_counter_), dependent_inserter(&dependent_inserter_) {}


//             recursive_inserter(view_collection_type & collection_, dependent_inserter_type & dependent_inserter_) :
//                view_collection(&collection_), dependent_inserter(&dependent_inserter_) {}


    void set_mesh_info(view_collection_type & collection_obj, change_counter_type & change_counter_)
    {
      view_collection = &collection_obj;
      change_counter  = &change_counter_;
    }


    template<typename handle_type, typename value_type>
    void handle_insert( handle_type ref, viennagrid::detail::tag<value_type> )
    {
      viennagrid::detail::handle_or_ignore( *view_collection, ref, viennagrid::detail::tag<value_type>() );

      dependent_inserter->handle_insert( ref, viennagrid::detail::tag<value_type>() );
      if (change_counter) ++(*change_counter);
    }


    typedef typename dependent_inserter_type::physical_container_collection_type physical_container_collection_type;

    template<bool generate_id, bool call_callback, typename value_type, typename inserter_type>
    std::pair<
        typename viennagrid::result_of::container_of<physical_container_collection_type, value_type>::type::handle_type,
        bool
    >
    physical_insert( const value_type & element, inserter_type & inserter )
    {
        return dependent_inserter->template physical_insert<generate_id, call_callback>( element, inserter );
    }



    template<bool generate_id, bool call_callback, typename value_type>
    std::pair<
        typename viennagrid::result_of::container_of<physical_container_collection_type, value_type>::type::handle_type,
        bool
    >
    insert( const value_type & element )
    {
      return physical_insert<generate_id, call_callback>( element, *this );
    }

    template<typename value_type>
    std::pair<
        typename viennagrid::result_of::container_of<physical_container_collection_type, value_type>::type::handle_type,
        bool
    >
    operator()( const value_type & element )
    {
      return insert<true, true>( element );
    }

    physical_container_collection_type & get_physical_container_collection() { return dependent_inserter->get_physical_container_collection(); }
    physical_container_collection_type const & get_physical_container_collection() const { return dependent_inserter->get_physical_container_collection(); }

    typedef typename dependent_inserter_type::id_generator_type id_generator_type;
    id_generator_type & get_id_generator() { return dependent_inserter->get_id_generator(); }
    id_generator_type const & get_id_generator() const { return dependent_inserter->get_id_generator(); }


  private:
    view_collection_type * view_collection;
    change_counter_type * change_counter;

    dependent_inserter_type * dependent_inserter;
  };


  namespace result_of
  {
    /** @brief Helper metafunction for obtaining the recursive inserter type for a container collection.
      *
      * @tparam container_collection_type     The container collection in which to insert
      * @tparam change_counter_type           Type of the status counter (incremented at each change
      * @tparam dependent_inserter_type       Inserter type for other containers which is called after the insert
      */
    template<typename container_collection_type, typename change_counter_type, typename dependent_inserter_type>
    struct recursive_inserter
    {
      typedef viennagrid::recursive_inserter<container_collection_type, change_counter_type, dependent_inserter_type> type;
    };

    /** @brief Helper metafunction for obtaining the physical inserter for a container collection. Inserts an element, not just a reference
      *
      * @tparam container_collection_type     The container collection in which to insert
      * @tparam change_counter_type           Type of the status counter (incremented at each change
      * @tparam id_generator_type             Type of the ID generator used for assigning an ID to the newly inserted element
      */
    template<typename container_collection_type, typename change_counter_type, typename id_generator_type>
    struct physical_inserter
    {
      typedef viennagrid::physical_inserter<container_collection_type, change_counter_type, id_generator_type> type;
    };
  }
}

#endif
