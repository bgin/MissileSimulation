#ifndef VIENNAGRID_ELEMENT_DELETION_HPP
#define VIENNAGRID_ELEMENT_DELETION_HPP

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
#include "viennagrid/storage/container_collection.hpp"
#include "viennagrid/mesh/mesh.hpp"
#include "viennagrid/mesh/segmentation.hpp"
#include "viennagrid/mesh/coboundary_iteration.hpp"
#include "viennagrid/mesh/mesh_operations.hpp"
#include <iterator>


/** @file viennagrid/mesh/element_deletion.hpp
    @brief Contains functions for deleting elements from a domin
*/


namespace viennagrid
{
  namespace detail
  {
    /** @brief For internal use only */
    template<typename MeshT, typename ToSwtichElementHandleT>
    struct switch_handle_functor
    {
      typedef typename viennagrid::detail::result_of::value_type<ToSwtichElementHandleT>::type to_switch_element_type;

      switch_handle_functor(MeshT & mesh_obj, ToSwtichElementHandleT from, ToSwtichElementHandleT to) : mesh_obj_(mesh_obj), from_(from), to_(to) {}

      template<typename ParentElementTypeOrTagT>
      void operator() ( viennagrid::detail::tag<ParentElementTypeOrTagT> )
      {
        typedef typename viennagrid::result_of::element<MeshT, ParentElementTypeOrTagT>::type ParentElementType;
        typedef typename viennagrid::result_of::element_range<MeshT, ParentElementTypeOrTagT>::type ParentElementRangeType;
        typedef typename viennagrid::result_of::iterator<ParentElementRangeType>::type ParentElementRangeIterator;

        ParentElementRangeType parent_elements(mesh_obj_);
        for (ParentElementRangeIterator it = parent_elements.begin(); it != parent_elements.end(); ++it)
        {
          typedef typename viennagrid::result_of::element_range<ParentElementType, to_switch_element_type>::type ToSwitchElementRangeType;
          typedef typename viennagrid::result_of::iterator<ToSwitchElementRangeType>::type ToSwitchElementRangeIterator;

          ToSwitchElementRangeType to_switch_elements(*it);
          for (ToSwitchElementRangeIterator jt = to_switch_elements.begin(); jt != to_switch_elements.end(); ++jt)
          {
            if (jt.handle() == from_)
            {
              jt.handle() = to_;
            }
          }
        }
      }

      MeshT & mesh_obj_;
      ToSwtichElementHandleT from_;
      ToSwtichElementHandleT to_;
    };


    /** @brief For internal use only */
    template<typename MeshT, typename HandleT>
    void switch_handle( MeshT & mesh_obj, HandleT old_handle, HandleT new_handle)
    {
      typedef typename viennagrid::detail::result_of::value_type<HandleT>::type ToSwitchElementType;
      typedef typename viennagrid::result_of::referencing_element_typelist<MeshT, ToSwitchElementType>::type ParentElementTypelist;

      switch_handle_functor<MeshT, HandleT> functor(mesh_obj, old_handle, new_handle);

      viennagrid::detail::for_each<ParentElementTypelist>( functor );
    }


    /** @brief For internal use only */
    template<typename MeshT, typename MeshViewT>
    struct erase_functor
    {
      erase_functor(MeshT & mesh_obj, MeshViewT & view_to_erase) : mesh_obj_(mesh_obj), view_to_erase_(view_to_erase) {}

      template<typename ElementT>
      void operator()( viennagrid::detail::tag<ElementT> )
      {
        typedef typename viennagrid::result_of::element_range<MeshViewT, ElementT>::type ToEraseElementRangeType;
        typedef typename viennagrid::result_of::iterator<ToEraseElementRangeType>::type ToEraseElementRangeIterator;

        typedef typename viennagrid::result_of::handle<MeshT, ElementT>::type ElementHandle;
        typedef typename viennagrid::result_of::element_range<MeshT, ElementT>::type ElementRangeType;
        typedef typename viennagrid::result_of::iterator<ElementRangeType>::type ElementRangeIterator;

        typedef typename viennagrid::result_of::id<ElementT>::type id_type;

  //             std::vector< std::pair<element_range_iterator, element_range_iterator> > swtiching_map;

        std::deque<id_type> ids_to_erase;

        ToEraseElementRangeType elements_to_erase(view_to_erase_);
        for (ToEraseElementRangeIterator it = elements_to_erase.begin(); it != elements_to_erase.end(); ++it)
          ids_to_erase.push_back( it->id() );

        ElementRangeType elements(mesh_obj_);

        for (typename std::deque<id_type>::iterator it = ids_to_erase.begin(); it != ids_to_erase.end(); ++it)
        {
          ElementRangeIterator to_erase_it = find( mesh_obj_, *it );
          ElementRangeIterator back_it = --elements.end();

          if (back_it != to_erase_it)
          {
            ElementHandle old_handle = back_it.handle();
            std::swap( *back_it, *to_erase_it );
            ElementHandle new_handle = to_erase_it.handle();

            switch_handle( mesh_obj_, old_handle, new_handle );
          }

          elements.erase( back_it );
        }
      }

      MeshT & mesh_obj_;
      MeshViewT & view_to_erase_;
    };
  } //namespace detail


  /** @brief Erases all elements marked for deletion and all elements which references these elements from a mesh
    *
    * @tparam WrappedConfigT            The wrapped config of the mesh type in which the elements to erase live
    * @tparam ToEraseViewT              The mesh view type which stores all elements to erase
    * @param  mesh_obj                  The host mesh object
    * @param  elements_to_erase         A mesh view which stores all elements marked for deletion
    */
  template<typename WrappedConfigT, typename ToEraseViewT>
  void erase_elements(viennagrid::mesh<WrappedConfigT> & mesh_obj, ToEraseViewT & elements_to_erase)
  {
    typedef viennagrid::mesh<WrappedConfigT> MeshType;

    typedef typename viennagrid::detail::result_of::reverse<
      typename viennagrid::result_of::element_typelist<ToEraseViewT>::type
    >::type SegmentElementTypelist;

    detail::erase_functor<MeshType, ToEraseViewT> functor( mesh_obj, elements_to_erase );
    viennagrid::detail::for_each<SegmentElementTypelist>(functor);

    viennagrid::detail::increment_change_counter(mesh_obj);
  }

  namespace detail
  {
    template<typename MeshViewT>
    struct erase_from_view_functor
    {
      erase_from_view_functor(MeshViewT & view_obj) : view_(view_obj) {}

      template<typename ElementT>
      void operator() (ElementT & element)
      {
  //       std::cout << "Erasing " << element << std::endl;
        viennagrid::elements<ElementT>(view_).erase_handle( viennagrid::handle(view_, element) );
      }

      MeshViewT & view_;
    };
  }

  /** @brief Erases all elements marked for deletion and all elements which references these elements from a view
    *
    * @param  view_obj                  The host mesh object
    * @param  elements_to_erase         A mesh view which stores all elements marked for deletion
    */
  template <typename WrappedConfigType, typename ElementTypeList, typename ContainerConfig, typename ToEraseViewT>
  void erase_elements(viennagrid::mesh< viennagrid::detail::decorated_mesh_view_config<WrappedConfigType, ElementTypeList, ContainerConfig> > & view_obj, ToEraseViewT & elements_to_erase)
  {
    typedef viennagrid::mesh< viennagrid::detail::decorated_mesh_view_config<WrappedConfigType, ElementTypeList, ContainerConfig> > ViewType;

    detail::erase_from_view_functor<ViewType> functor( view_obj );
    viennagrid::for_each(elements_to_erase, functor);

    viennagrid::detail::increment_change_counter(view_obj);
  }



  /** @brief Tags all elements connected to a given host_element for erasure. Call erase_element on 'elements_to_erase' to finally delete them. */
  template<typename MeshT, typename MeshViewT, typename HandleT>
  void mark_erase_elements( MeshT & mesh_obj, MeshViewT & elements_to_erase, HandleT host_element )
  {
    typedef typename viennagrid::detail::result_of::value_type<HandleT>::type ElementType;
    viennagrid::elements<ElementType>(elements_to_erase).insert_unique_handle( host_element );

    mark_referencing_elements(mesh_obj, elements_to_erase, host_element);
  }


  /** @brief Erases a single elements and all elements which references this element from a mesh. If more than one element is erase use erase_elements instead for better performance.
    *
    * @tparam MeshT                     The mesh type
    * @tparam HandleT                   The handle type of the element to delete
    * @param  mesh_obj                  The host mesh object
    * @param  element_to_erase          A handle to the element to be deleted
    */
  template<typename MeshT, typename HandleT>
  void erase_element(MeshT & mesh_obj, HandleT element_to_erase)
  {
    typedef typename viennagrid::result_of::mesh_view<MeshT>::type ToEraseViewType;
    ToEraseViewType elements_to_erase = viennagrid::make_view(mesh_obj);
    viennagrid::mark_erase_elements( mesh_obj, elements_to_erase, element_to_erase );
    viennagrid::erase_elements(mesh_obj, elements_to_erase);
  }


}


#endif

