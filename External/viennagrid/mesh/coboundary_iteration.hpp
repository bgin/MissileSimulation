#ifndef VIENNAGRID_MESH_COBOUNDARY_ITERATION_HPP
#define VIENNAGRID_MESH_COBOUNDARY_ITERATION_HPP

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
#include "viennagrid/storage/forwards.hpp"
#include "viennagrid/mesh/mesh.hpp"
#include "viennagrid/accessor.hpp"

/** @file viennagrid/mesh/coboundary_iteration.hpp
    @brief Contains definition and implementation of coboundary iteration
*/

namespace viennagrid
{
  namespace result_of
  {
    template<typename MeshOrSegmentHandleT, typename ElementTypeOrTagT, typename CoboundaryTypeOrTagT>
    struct coboundary_range;

    template<typename MeshOrSegmentHandleT, typename ElementTypeOrTagT, typename CoboundaryTypeOrTagT>
    struct const_coboundary_range;
  }

  template<typename ElementTypeOrTagT, typename CoboundaryTypeOrTagT, typename WrappedConfigT, typename ElementOrHandleT>
  typename result_of::coboundary_range<viennagrid::mesh<WrappedConfigT>, ElementTypeOrTagT, CoboundaryTypeOrTagT>::type
  coboundary_elements(viennagrid::mesh<WrappedConfigT> & mesh_obj, ElementOrHandleT const & element_or_handle);

  template<typename ElementTypeOrTagT, typename CoboundaryTypeOrTagT, typename WrappedConfigT, typename ElementOrHandleT>
  typename result_of::const_coboundary_range<viennagrid::mesh<WrappedConfigT>, ElementTypeOrTagT, CoboundaryTypeOrTagT>::type
  coboundary_elements(viennagrid::mesh<WrappedConfigT> const & mesh_obj, ElementOrHandleT const & element_or_handle);

  template<typename ElementTypeOrTagT, typename CoboundaryTypeOrTagT, typename SegmentationT, typename element_or_handle_type>
  typename result_of::coboundary_range<segment_handle<SegmentationT>, ElementTypeOrTagT, CoboundaryTypeOrTagT>::type
  coboundary_elements(segment_handle<SegmentationT> & segment, element_or_handle_type const & element_or_handle);

  template<typename ElementTypeOrTagT, typename CoboundaryTypeOrTagT, typename SegmentationT, typename element_or_handle_type>
  typename result_of::const_coboundary_range<segment_handle<SegmentationT>, ElementTypeOrTagT, CoboundaryTypeOrTagT>::type
  coboundary_elements(segment_handle<SegmentationT> const & segment, element_or_handle_type const & element_or_handle);





  namespace detail
  {
    template<typename ElementTypeOrTagT, typename CoboundaryTypeOrTagT, typename ContainerT>
    class coboundary_range_wrapper : public container_range_wrapper<ContainerT>
    {
    public:
      coboundary_range_wrapper(ContainerT & container) : container_range_wrapper<ContainerT>(&container) {}
      coboundary_range_wrapper(container_range_wrapper<ContainerT> const & base) : container_range_wrapper<ContainerT>(base) {}

      template<typename WrappedConfigT, typename ElementOrHandleT>
      coboundary_range_wrapper(viennagrid::mesh<WrappedConfigT> & mesh_obj,
                               ElementOrHandleT const & element_or_handle) : container_range_wrapper<ContainerT>(viennagrid::coboundary_elements<ElementTypeOrTagT, CoboundaryTypeOrTagT>(mesh_obj, element_or_handle)) {}

      template<typename SegmentationT, typename ElementOrHandleT>
      coboundary_range_wrapper(viennagrid::segment_handle<SegmentationT> & segment_obj,
                               ElementOrHandleT const & element_or_handle) : container_range_wrapper<ContainerT>(viennagrid::coboundary_elements<ElementTypeOrTagT, CoboundaryTypeOrTagT>(segment_obj, element_or_handle)) {}


      template<typename WrappedConfigT, typename ElementTagT, typename WrappedElementConfigT>
      coboundary_range_wrapper(viennagrid::mesh<WrappedConfigT> & mesh_obj,
                               viennagrid::element<ElementTagT, WrappedElementConfigT> & element) : container_range_wrapper<ContainerT>(viennagrid::coboundary_elements<ElementTypeOrTagT, CoboundaryTypeOrTagT>(mesh_obj,  viennagrid::handle(mesh_obj, element))) {}

      template<typename SegmentationT, typename ElementTagT, typename WrappedElementConfigT>
      coboundary_range_wrapper(viennagrid::segment_handle<SegmentationT> & segment_obj,
                               viennagrid::element<ElementTagT, WrappedElementConfigT> & element) : container_range_wrapper<ContainerT>(viennagrid::coboundary_elements<ElementTypeOrTagT, CoboundaryTypeOrTagT>(segment_obj, viennagrid::handle(segment_obj, element))) {}
    };

    template<typename ElementTypeOrTagT, typename CoboundaryTypeOrTagT, typename ContainerT>
    class coboundary_range_wrapper<ElementTypeOrTagT, CoboundaryTypeOrTagT, const ContainerT> : public container_range_wrapper<const ContainerT>
    {
    public:
      coboundary_range_wrapper(ContainerT const & container) : container_range_wrapper<const ContainerT>(&container) {}
      coboundary_range_wrapper(container_range_wrapper<const ContainerT> const & base) : container_range_wrapper<const ContainerT>(base) {}

      template<typename WrappedConfigT, typename ElementOrHandleT>
      coboundary_range_wrapper(viennagrid::mesh<WrappedConfigT> const & mesh_obj,
                               ElementOrHandleT const & element_or_handle) : container_range_wrapper<const ContainerT>(viennagrid::coboundary_elements<ElementTypeOrTagT, CoboundaryTypeOrTagT>(mesh_obj, element_or_handle)) {}

      template<typename SegmentationT, typename ElementOrHandleT>
      coboundary_range_wrapper(viennagrid::segment_handle<SegmentationT> const & segment_obj,
                               ElementOrHandleT const & element_or_handle) : container_range_wrapper<const ContainerT>(viennagrid::coboundary_elements<ElementTypeOrTagT, CoboundaryTypeOrTagT>(segment_obj, element_or_handle)) {}


      template<typename WrappedConfigT, typename ElementTagT, typename WrappedElementConfigT>
      coboundary_range_wrapper(viennagrid::mesh<WrappedConfigT> const & mesh_obj,
                               viennagrid::element<ElementTagT, WrappedElementConfigT> const & element) : container_range_wrapper<const ContainerT>(viennagrid::coboundary_elements<ElementTypeOrTagT, CoboundaryTypeOrTagT>(mesh_obj, viennagrid::handle(mesh_obj, element))) {}

      template<typename SegmentationT, typename ElementTagT, typename WrappedElementConfigT>
      coboundary_range_wrapper(viennagrid::segment_handle<SegmentationT> const & segment_obj,
                               viennagrid::element<ElementTagT, WrappedElementConfigT> const & element) : container_range_wrapper<const ContainerT>(viennagrid::coboundary_elements<ElementTypeOrTagT, CoboundaryTypeOrTagT>(segment_obj, viennagrid::handle(segment_obj, element))) {}
    };
  }


  namespace result_of
  {
    /** \cond */
    template<typename mesh_type, typename element_type_or_tag, typename coboundary_type_or_tag>
    struct coboundary_view
    {
      typedef typename viennagrid::result_of::element_tag< element_type_or_tag >::type element_tag;
      typedef typename viennagrid::result_of::element_tag< coboundary_type_or_tag >::type coboundary_tag;

      typedef typename viennagrid::detail::result_of::lookup<
          typename viennagrid::detail::result_of::lookup<
              typename mesh_type::appendix_type,
              coboundary_collection_tag
            >::type,
          viennagrid::static_pair<element_tag, coboundary_tag>
        >::type::container_type::value_type type;
    };

    template<typename SegmentationType, typename element_type_or_tag, typename coboundary_type_or_tag>
    struct coboundary_view< viennagrid::segment_handle<SegmentationType>, element_type_or_tag, coboundary_type_or_tag >
    {
      typedef typename coboundary_view< typename viennagrid::segment_handle<SegmentationType>::view_type, element_type_or_tag, coboundary_type_or_tag >::type type;
    };
    /** \endcond */


    /** @brief Metafunction for obtaining a coboundary range of an element type within a mesh/segment
     *
     * @tparam MeshOrSegmentHandleT       The host mesh/segment type
     * @tparam ElementTypeOrTagT      The element type/tag of which the co-boundary range is created
     * @tparam CoboundaryTypeOrTagT   The co-boundary element type/tag
     */
    template<typename MeshOrSegmentHandleT, typename ElementTypeOrTagT, typename CoboundaryTypeOrTagT>
    struct coboundary_range
    {
      //typedef viennagrid::detail::container_range_wrapper< typename coboundary_view<MeshOrSegmentHandleT, ElementTypeOrTagT, CoboundaryTypeOrTagT>::type > type;
      typedef viennagrid::detail::coboundary_range_wrapper< ElementTypeOrTagT, CoboundaryTypeOrTagT, typename coboundary_view<MeshOrSegmentHandleT, ElementTypeOrTagT, CoboundaryTypeOrTagT>::type > type;
    };

    /** @brief Metafunction for obtaining a const coboundary range of an element type within a mesh/segment
     *
     * @tparam MeshOrSegmentHandleT       The host mesh/segment type
     * @tparam ElementTypeOrTagT      The element type/tag of which the co-boundary range is created
     * @tparam CoboundaryTypeOrTagT   The co-boundary element type/tag
     */
    template<typename MeshOrSegmentHandleT, typename ElementTypeOrTagT, typename CoboundaryTypeOrTagT>
    struct const_coboundary_range
    {
//       typedef viennagrid::detail::container_range_wrapper< const typename coboundary_view<MeshOrSegmentHandleT, ElementTypeOrTagT, CoboundaryTypeOrTagT>::type > type;
      typedef viennagrid::detail::coboundary_range_wrapper< ElementTypeOrTagT, CoboundaryTypeOrTagT, const typename coboundary_view<MeshOrSegmentHandleT, ElementTypeOrTagT, CoboundaryTypeOrTagT>::type > type;
    };

    /** \cond */
    template<typename MeshOrSegmentHandleT, typename ElementTypeOrTagT, typename CoboundaryTypeOrTagT>
    struct coboundary_range<const MeshOrSegmentHandleT, ElementTypeOrTagT, CoboundaryTypeOrTagT>
    {
      typedef typename const_coboundary_range<MeshOrSegmentHandleT, ElementTypeOrTagT, CoboundaryTypeOrTagT>::type type;
    };
    /** \endcond */
  }

  namespace detail
  {

    /** @brief For internal use only */
    template<typename element_type_or_tag, typename coboundary_type_or_tag, typename MeshT, typename coboundary_accessor_type>
    void create_coboundary_information(MeshT & mesh_obj, coboundary_accessor_type accessor)
    {
      typedef typename viennagrid::result_of::element_tag< element_type_or_tag >::type element_tag;

      typedef typename viennagrid::result_of::element< MeshT, coboundary_type_or_tag >::type coboundary_type;

      typedef typename viennagrid::result_of::element_range< MeshT, element_type_or_tag >::type element_range_type;
      typedef typename viennagrid::result_of::iterator< element_range_type >::type element_range_iterator;

      element_range_type elements(mesh_obj);


      for ( element_range_iterator it = elements.begin(); it != elements.end(); ++it )
      {
        accessor( *it ).clear();
        accessor( *it ).set_base_container( viennagrid::get< coboundary_type >( element_collection(mesh_obj) ) );
      }


      typedef typename viennagrid::result_of::element_range< MeshT, coboundary_type_or_tag >::type coboundary_element_range_type;
      typedef typename viennagrid::result_of::iterator< coboundary_element_range_type >::type coboundary_element_range_iterator;

      coboundary_element_range_type coboundary_elements(mesh_obj);
      for (coboundary_element_range_iterator it = coboundary_elements.begin(); it != coboundary_elements.end(); ++it)
      {
        typedef typename viennagrid::result_of::element_range< coboundary_type, element_tag >::type element_on_coboundary_element_range_type;
        typedef typename viennagrid::result_of::iterator< element_on_coboundary_element_range_type >::type element_on_coboundary_element_range_iterator;

        element_on_coboundary_element_range_type elements_on_coboundary_element( *it );
        for (element_on_coboundary_element_range_iterator jt = elements_on_coboundary_element.begin(); jt != elements_on_coboundary_element.end(); ++jt)
          accessor.at( *jt ).insert_handle( it.handle() );
      }
    }

    template<typename element_type_or_tag, typename coboundary_type_or_tag, typename WrappedConfigT, typename ElementTypelistT, typename ContainerConfigT, typename coboundary_accessor_type>
    void create_coboundary_information(viennagrid::mesh< viennagrid::detail::decorated_mesh_view_config<WrappedConfigT, ElementTypelistT, ContainerConfigT> > & mesh_obj, coboundary_accessor_type accessor)
    {
      typedef viennagrid::mesh< viennagrid::detail::decorated_mesh_view_config<WrappedConfigT, ElementTypelistT, ContainerConfigT> > ViewType;
      typedef typename viennagrid::result_of::element_tag< element_type_or_tag >::type element_tag;

      typedef typename viennagrid::result_of::element< ViewType, coboundary_type_or_tag >::type coboundary_type;

      typedef typename viennagrid::result_of::element_range< ViewType, element_type_or_tag >::type element_range_type;
      typedef typename viennagrid::result_of::iterator< element_range_type >::type element_range_iterator;

      element_range_type elements(mesh_obj);


      for ( element_range_iterator it = elements.begin(); it != elements.end(); ++it )
      {
        accessor( *it ).clear();
        accessor( *it ).set_base_container( viennagrid::get< coboundary_type >( element_collection(mesh_obj) ) );
      }


      typedef typename viennagrid::result_of::element_range< ViewType, coboundary_type_or_tag >::type coboundary_element_range_type;
      typedef typename viennagrid::result_of::iterator< coboundary_element_range_type >::type coboundary_element_range_iterator;

      coboundary_element_range_type coboundary_elements(mesh_obj);
      for (coboundary_element_range_iterator it = coboundary_elements.begin(); it != coboundary_elements.end(); ++it)
      {
        typedef typename viennagrid::result_of::element_range< coboundary_type, element_tag >::type element_on_coboundary_element_range_type;
        typedef typename viennagrid::result_of::iterator< element_on_coboundary_element_range_type >::type element_on_coboundary_element_range_iterator;

        element_on_coboundary_element_range_type elements_on_coboundary_element( *it );
        for (element_on_coboundary_element_range_iterator jt = elements_on_coboundary_element.begin(); jt != elements_on_coboundary_element.end(); ++jt)
        {
//           is this line needed??
//           if ( viennagrid::find(mesh_obj, *jt) !=  viennagrid::elements<element_type_or_tag>(mesh_obj).end() )
          accessor.at( *jt ).insert_handle( it.handle() );
        }
      }
    }





    /** @brief For internal use only */
    template<typename element_type_or_tag, typename coboundary_type_or_tag, typename mesh_type>
    void create_coboundary_information(mesh_type & mesh_obj)
    {
        typedef typename viennagrid::result_of::element_tag< element_type_or_tag >::type element_tag;
        typedef typename viennagrid::result_of::element_tag< coboundary_type_or_tag >::type coboundary_tag;
        typedef typename viennagrid::result_of::element< mesh_type, element_type_or_tag >::type element_type;

        typedef typename viennagrid::detail::result_of::lookup<
                typename viennagrid::detail::result_of::lookup<
                    typename mesh_type::appendix_type,
                    coboundary_collection_tag
                >::type,
                viennagrid::static_pair<element_tag, coboundary_tag>
                >::type coboundary_container_wrapper_type;

        coboundary_container_wrapper_type & coboundary_container_wrapper = detail::coboundary_collection<element_tag, coboundary_tag>(mesh_obj);//viennagrid::storage::detail::get< viennagrid::static_pair<element_tag, coboundary_tag> > ( mesh_obj.coboundary_collection() );

        create_coboundary_information<element_type_or_tag, coboundary_type_or_tag>( mesh_obj, viennagrid::make_accessor<element_type>(coboundary_container_wrapper.container) );
        detail::update_change_counter( mesh_obj, coboundary_container_wrapper.change_counter );
    }











    /** @brief For internal use only */
    template<typename ElementTypeOrTagT, typename coboundary_type_or_tag, typename coboundary_accessor_type, typename ElementTag, typename WrappedConfigType>
    viennagrid::detail::container_range_wrapper<typename coboundary_accessor_type::value_type>
    coboundary_elements(coboundary_accessor_type accessor, viennagrid::element<ElementTag, WrappedConfigType> & element)
    {
      typedef viennagrid::detail::container_range_wrapper<typename coboundary_accessor_type::value_type> range_type;
      return range_type( accessor( element ) );
    }

    /** @brief For internal use only */
    template<typename ElementTypeOrTagT, typename coboundary_type_or_tag, typename coboundary_accessor_type, typename ElementTag, typename WrappedConfigType>
    viennagrid::detail::container_range_wrapper<const typename coboundary_accessor_type::value_type>
    coboundary_elements(coboundary_accessor_type const accessor, viennagrid::element<ElementTag, WrappedConfigType> const & element)
    {
      typedef viennagrid::detail::container_range_wrapper<const typename coboundary_accessor_type::value_type> range_type;
      return range_type( accessor( element ) );
    }


    /** @brief For internal use only */
    template<typename element_type_or_tag, typename coboundary_type_or_tag, typename coboundary_accessor_type, typename WrappedConfigType, typename element_or_handle_type>
    viennagrid::detail::container_range_wrapper<typename coboundary_accessor_type::value_type>
    coboundary_elements(viennagrid::mesh<WrappedConfigType> & mesh_obj, coboundary_accessor_type accessor, element_or_handle_type & hendl)
    {
      return coboundary_elements<element_type_or_tag, coboundary_type_or_tag>( accessor, viennagrid::dereference_handle(mesh_obj, hendl) );
    }

    /** @brief For internal use only */
    template<typename element_type_or_tag, typename coboundary_type_or_tag, typename coboundary_accessor_type, typename WrappedConfigType, typename element_or_handle_type>
    viennagrid::detail::container_range_wrapper<const typename coboundary_accessor_type::value_type>
    coboundary_elements(viennagrid::mesh<WrappedConfigType> const & mesh_obj, coboundary_accessor_type const accessor, element_or_handle_type const & hendl)
    {
      return coboundary_elements<element_type_or_tag, coboundary_type_or_tag>( accessor, viennagrid::dereference_handle(mesh_obj, hendl) );
    }

  }



  /** @brief Obtaines a coboundary range of an element within a mesh. This function caches the coboundary information and re-creates it if the cached information is out of date. The runtime of a re-creation is linear in the number of elements of type CoboundaryTypeOrTagT within the mesh.
    *
    * @tparam ElementTypeOrTagT       The base element type/tag from which the coboundary range is obtained
    * @tparam CoboundaryTypeOrTagT    The coboundary element type/tag
    * @tparam WrappedConfigT          The wrapped config of the mesh
    * @tparam ElementOrHandleT        The element or handle type for which the coboundary range is obtained
    * @param  mesh_obj                The host mesh object in which the elements of the coboundary range exist
    * @param  element_or_handle       A handle or the element for which the coboundary range is obained
    * @return                         The coboundary range
    */
  template<typename ElementTypeOrTagT, typename CoboundaryTypeOrTagT, typename WrappedConfigT, typename ElementOrHandleT>
  typename result_of::coboundary_range<viennagrid::mesh<WrappedConfigT>, ElementTypeOrTagT, CoboundaryTypeOrTagT>::type
  coboundary_elements(viennagrid::mesh<WrappedConfigT> & mesh_obj, ElementOrHandleT const & element_or_handle)
  {
    typedef viennagrid::mesh<WrappedConfigT> mesh_type;
    typedef typename viennagrid::result_of::element_tag< ElementTypeOrTagT >::type element_tag;
    typedef typename viennagrid::result_of::element_tag< CoboundaryTypeOrTagT >::type coboundary_tag;
    typedef typename viennagrid::result_of::element< mesh_type, ElementTypeOrTagT >::type element_type;

    typedef typename viennagrid::detail::result_of::lookup<
            typename viennagrid::detail::result_of::lookup<
                typename mesh_type::appendix_type,
                coboundary_collection_tag
            >::type,
            viennagrid::static_pair<element_tag, coboundary_tag>
            >::type coboundary_container_wrapper_type;
    coboundary_container_wrapper_type & coboundary_container_wrapper = detail::coboundary_collection<element_tag, coboundary_tag>(mesh_obj);

    if ( detail::is_obsolete(mesh_obj, coboundary_container_wrapper.change_counter) )
      detail::create_coboundary_information<ElementTypeOrTagT, CoboundaryTypeOrTagT>(mesh_obj);

    return detail::coboundary_elements<ElementTypeOrTagT, CoboundaryTypeOrTagT>( viennagrid::make_accessor<element_type>(coboundary_container_wrapper.container), viennagrid::dereference_handle(mesh_obj, element_or_handle) );
  }

  /** @brief Obtaines a const coboundary range of an element within a mesh. This function caches the coboundary information and re-creates it if the cached information is out of date. The runtime of a re-creation is linear in the number of elements of type CoboundaryTypeOrTagT within the mesh.
    *
    * @tparam ElementTypeOrTagT       The base element type/tag from which the coboundary range is obtained
    * @tparam CoboundaryTypeOrTagT    The coboundary element type/tag
    * @tparam WrappedConfigT          The wrapped config of the mesh
    * @tparam ElementOrHandleT        The element or handle type for which the coboundary range is obtained
    * @param  mesh_obj                The host mesh object in which the elements of the coboundary range exist
    * @param  element_or_handle       A handle or the element for which the coboundary range is obained
    * @return                         The const coboundary range
    */
  template<typename ElementTypeOrTagT, typename CoboundaryTypeOrTagT, typename WrappedConfigT, typename ElementOrHandleT>
  typename result_of::const_coboundary_range<viennagrid::mesh<WrappedConfigT>, ElementTypeOrTagT, CoboundaryTypeOrTagT>::type
  coboundary_elements(viennagrid::mesh<WrappedConfigT> const & mesh_obj, ElementOrHandleT const & element_or_handle)
  {
    typedef viennagrid::mesh<WrappedConfigT> mesh_type;
    typedef typename viennagrid::result_of::element_tag< ElementTypeOrTagT >::type element_tag;
    typedef typename viennagrid::result_of::element_tag< CoboundaryTypeOrTagT >::type coboundary_tag;
    typedef typename viennagrid::result_of::element< mesh_type, ElementTypeOrTagT >::type element_type;

    typedef typename viennagrid::detail::result_of::lookup<
            typename viennagrid::detail::result_of::lookup<
                typename mesh_type::appendix_type,
                coboundary_collection_tag
            >::type,
            viennagrid::static_pair<element_tag, coboundary_tag>
            >::type coboundary_container_wrapper_type;
    coboundary_container_wrapper_type const & coboundary_container_wrapper = detail::coboundary_collection<element_tag, coboundary_tag>(mesh_obj);

    if ( detail::is_obsolete(mesh_obj, coboundary_container_wrapper.change_counter) )
      detail::create_coboundary_information<ElementTypeOrTagT, CoboundaryTypeOrTagT>( const_cast<mesh_type&>(mesh_obj) );

    return detail::coboundary_elements<ElementTypeOrTagT, CoboundaryTypeOrTagT>( viennagrid::make_accessor<element_type>(coboundary_container_wrapper.container), viennagrid::dereference_handle(mesh_obj, element_or_handle) );
  }



  /** @brief Obtaines a coboundary range of an element within a segment. This function caches the coboundary information and re-creates it if the cached information is out of date. The runtime of a re-creation is linear in the number of elements of type CoboundaryTypeOrTagT within the segment.
    *
    * @tparam ElementTypeOrTagT       The base element type/tag from which the coboundary range is obtained
    * @tparam CoboundaryTypeOrTagT    The coboundary element type/tag
    * @tparam SegmentationT           The segmentation type of the segment type
    * @tparam ElementOrHandleT        The element or handle type for which the coboundary range is obtained
    * @param  segment                 The host segment object in which the elements of the coboundary range exist
    * @param  element_or_handle       A handle or the element for which the coboundary range is obained
    * @return                         The coboundary range
    */
  template<typename ElementTypeOrTagT, typename CoboundaryTypeOrTagT, typename SegmentationT, typename element_or_handle_type>
  typename result_of::coboundary_range<segment_handle<SegmentationT>, ElementTypeOrTagT, CoboundaryTypeOrTagT>::type
  coboundary_elements(segment_handle<SegmentationT> & segment, element_or_handle_type const & element_or_handle)
  {
    return coboundary_elements<ElementTypeOrTagT, CoboundaryTypeOrTagT>( segment.view(), element_or_handle );
  }

  /** @brief Obtaines a const coboundary range of an element within a segment. This function caches the coboundary information and re-creates it if the cached information is out of date. The runtime of a re-creation is linear in the number of elements of type CoboundaryTypeOrTagT within the segment.
    *
    * @tparam ElementTypeOrTagT       The base element type/tag from which the coboundary range is obtained
    * @tparam CoboundaryTypeOrTagT    The coboundary element type/tag
    * @tparam SegmentationT           The segmentation type of the segment type
    * @tparam ElementOrHandleT        The element or handle type for which the coboundary range is obtained
    * @param  segment                 The host segment object in which the elements of the coboundary range exist
    * @param  element_or_handle       A handle or the element for which the coboundary range is obained
    * @return                         The const coboundary range
    */
  template<typename ElementTypeOrTagT, typename CoboundaryTypeOrTagT, typename SegmentationT, typename element_or_handle_type>
  typename result_of::const_coboundary_range<segment_handle<SegmentationT>, ElementTypeOrTagT, CoboundaryTypeOrTagT>::type
  coboundary_elements(segment_handle<SegmentationT> const & segment, element_or_handle_type const & element_or_handle)
  {
    return coboundary_elements<ElementTypeOrTagT, CoboundaryTypeOrTagT>( segment.view(), element_or_handle );
  }

}

#endif
