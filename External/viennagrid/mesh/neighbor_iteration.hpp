#ifndef VIENNAGRID_MESH_NEIGHBOR_ITERATION_HPP
#define VIENNAGRID_MESH_NEIGHBOR_ITERATION_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include "viennagrid/mesh/segmentation.hpp"
#include "viennagrid/mesh/coboundary_iteration.hpp"

/** @file viennagrid/mesh/neighbor_iteration.hpp
    @brief Contains definition and implementation of neighbor iteration
*/
#include "../forwards.hpp"

namespace viennagrid
{
  namespace result_of
  {
    template<typename MeshOrSegmentHandleT, typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT>
    struct neighbor_range;

    template<typename MeshOrSegmentHandleT, typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT>
    struct const_neighbor_range;
  }

  template<typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT, typename WrappedConfigT, typename ElementOrHandleT>
  typename result_of::neighbor_range<viennagrid::mesh<WrappedConfigT>, ElementTypeOrTagT, ConnectorElementTypeOrTagT>::type
  neighbor_elements(viennagrid::mesh<WrappedConfigT> & mesh_obj, ElementOrHandleT const & element_or_handle);

  template<typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT, typename WrappedConfigT, typename ElementOrHandleT>
  typename result_of::const_neighbor_range<viennagrid::mesh<WrappedConfigT>, ElementTypeOrTagT, ConnectorElementTypeOrTagT>::type
  neighbor_elements(viennagrid::mesh<WrappedConfigT> const & mesh_obj, ElementOrHandleT const & element_or_handle);

  template<typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT, typename SegmentationT, typename ElementOrHandleT>
  typename result_of::neighbor_range<segment_handle<SegmentationT>, ElementTypeOrTagT, ConnectorElementTypeOrTagT>::type
  neighbor_elements(segment_handle<SegmentationT> & segment, ElementOrHandleT const & element_or_handle);

  template<typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT, typename SegmentationT, typename ElementOrHandleT>
  typename result_of::const_neighbor_range<segment_handle<SegmentationT>, ElementTypeOrTagT, ConnectorElementTypeOrTagT>::type
  neighbor_elements(segment_handle<SegmentationT> const & segment, ElementOrHandleT const & element_or_handle);



  namespace detail
  {
    template<typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT, typename ContainerT>
    class neighbor_range_wrapper : public container_range_wrapper<ContainerT>
    {
    public:
      neighbor_range_wrapper(ContainerT & container) : container_range_wrapper<ContainerT>(&container) {}
      neighbor_range_wrapper(container_range_wrapper<ContainerT> const & base) : container_range_wrapper<ContainerT>(base) {}

      template<typename WrappedConfigT, typename ElementOrHandleT>
      neighbor_range_wrapper(viennagrid::mesh<WrappedConfigT> & mesh_obj,
                             ElementOrHandleT const & element_or_handle) : container_range_wrapper<ContainerT>(viennagrid::neighbor_elements<ElementTypeOrTagT, ConnectorElementTypeOrTagT>(mesh_obj, element_or_handle)) {}

      template<typename SegmentationT, typename ElementOrHandleT>
      neighbor_range_wrapper(viennagrid::segment_handle<SegmentationT> & segment_obj,
                             ElementOrHandleT const & element_or_handle) : container_range_wrapper<ContainerT>(viennagrid::neighbor_elements<ElementTypeOrTagT, ConnectorElementTypeOrTagT>(segment_obj, element_or_handle)) {}


      template<typename WrappedConfigT, typename ElementTagT, typename WrappedElementConfigT>
      neighbor_range_wrapper(viennagrid::mesh<WrappedConfigT> & mesh_obj,
                             viennagrid::element<ElementTagT, WrappedElementConfigT> & el) : container_range_wrapper<ContainerT>(viennagrid::neighbor_elements<ElementTypeOrTagT, ConnectorElementTypeOrTagT>(mesh_obj, viennagrid::handle(mesh_obj, el))) {}

      template<typename SegmentationT, typename ElementTagT, typename WrappedElementConfigT>
      neighbor_range_wrapper(viennagrid::segment_handle<SegmentationT> & segment_obj,
                             viennagrid::element<ElementTagT, WrappedElementConfigT> & el) : container_range_wrapper<ContainerT>(viennagrid::neighbor_elements<ElementTypeOrTagT, ConnectorElementTypeOrTagT>(segment_obj, viennagrid::handle(segment_obj, el))) {}
    };

    template<typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT, typename ContainerT>
    class neighbor_range_wrapper<ElementTypeOrTagT, ConnectorElementTypeOrTagT, const ContainerT> : public container_range_wrapper<const ContainerT>
    {
    public:
      neighbor_range_wrapper(ContainerT const & container) : container_range_wrapper<const ContainerT>(&container) {}
      neighbor_range_wrapper(container_range_wrapper<const ContainerT> const & base) : container_range_wrapper<const ContainerT>(base) {}

      template<typename WrappedConfigT, typename ElementOrHandleT>
      neighbor_range_wrapper(viennagrid::mesh<WrappedConfigT> const & mesh_obj,
                             ElementOrHandleT const & element_or_handle) : container_range_wrapper<const ContainerT>(viennagrid::neighbor_elements<ElementTypeOrTagT, ConnectorElementTypeOrTagT>(mesh_obj, element_or_handle)) {}

      template<typename SegmentationT, typename ElementOrHandleT>
      neighbor_range_wrapper(viennagrid::segment_handle<SegmentationT> const & segment_obj,
                             ElementOrHandleT const & element_or_handle) : container_range_wrapper<const ContainerT>(viennagrid::neighbor_elements<ElementTypeOrTagT, ConnectorElementTypeOrTagT>(segment_obj, element_or_handle)) {}


      template<typename WrappedConfigT, typename ElementTagT, typename WrappedElementConfigT>
      neighbor_range_wrapper(viennagrid::mesh<WrappedConfigT> const & mesh_obj,
                             viennagrid::element<ElementTagT, WrappedElementConfigT> const & el) : container_range_wrapper<const ContainerT>(viennagrid::neighbor_elements<ElementTypeOrTagT, ConnectorElementTypeOrTagT>(mesh_obj, viennagrid::handle(mesh_obj, el))) {}

      template<typename SegmentationT, typename ElementTagT, typename WrappedElementConfigT>
      neighbor_range_wrapper(viennagrid::segment_handle<SegmentationT> const & segment_obj,
                             viennagrid::element<ElementTagT, WrappedElementConfigT> const & el) : container_range_wrapper<const ContainerT>(viennagrid::neighbor_elements<ElementTypeOrTagT, ConnectorElementTypeOrTagT>(segment_obj, viennagrid::handle(segment_obj, el))) {}
    };
  }



  namespace result_of
  {
    /** \cond */
    template<typename mesh_type, typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT>
    struct neighbor_view
    {
      typedef typename viennagrid::result_of::element_tag< ElementTypeOrTagT >::type element_tag;
      typedef typename viennagrid::result_of::element_tag< ConnectorElementTypeOrTagT >::type connector_element_tag;

      typedef typename viennagrid::detail::result_of::lookup<
          typename viennagrid::detail::result_of::lookup<
              typename mesh_type::appendix_type,
              neighbor_collection_tag
            >::type,
          viennagrid::static_pair<element_tag, connector_element_tag>
        >::type::container_type::value_type type;
    };

    template<typename SegmentationT, typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT>
    struct neighbor_view< viennagrid::segment_handle<SegmentationT>, ElementTypeOrTagT, ConnectorElementTypeOrTagT >
    {
      typedef typename neighbor_view< typename viennagrid::segment_handle<SegmentationT>::view_type, ElementTypeOrTagT, ConnectorElementTypeOrTagT >::type type;
    };
    /** \endcond */


    /** @brief Metafunction for obtaining a neighbor range of an element type with a connector element type within a mesh/segment
     *
     * @tparam MeshOrSegmentHandleT             The host mesh/segment type
     * @tparam ElementTypeOrTagT            The element type/tag of which the co-boundary range is created
     * @tparam ConnectorElementTypeOrTagT   The connector element type/tag
     */
    template<typename MeshOrSegmentHandleT, typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT>
    struct neighbor_range
    {
//       typedef viennagrid::detail::container_range_wrapper< typename neighbor_view<MeshOrSegmentHandleT, ElementTypeOrTagT, ConnectorElementTypeOrTagT>::type > type;
      typedef viennagrid::detail::neighbor_range_wrapper< ElementTypeOrTagT, ConnectorElementTypeOrTagT, typename neighbor_view<MeshOrSegmentHandleT, ElementTypeOrTagT, ConnectorElementTypeOrTagT>::type > type;
    };

    /** @brief Metafunction for obtaining a const neighbor range of an element type with a connector element type within a mesh/segment
     *
     * @tparam MeshOrSegmentHandleT             The host mesh/segment type
     * @tparam ElementTypeOrTagT            The element type/tag of which the co-boundary range is created
     * @tparam ConnectorElementTypeOrTagT   The connector element type/tag
     */
    template<typename MeshOrSegmentHandleT, typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT>
    struct const_neighbor_range
    {
//       typedef viennagrid::detail::container_range_wrapper< const typename neighbor_view<MeshOrSegmentHandleT, ElementTypeOrTagT, ConnectorElementTypeOrTagT>::type > type;
      typedef viennagrid::detail::neighbor_range_wrapper< ElementTypeOrTagT, ConnectorElementTypeOrTagT, const typename neighbor_view<MeshOrSegmentHandleT, ElementTypeOrTagT, ConnectorElementTypeOrTagT>::type > type;
    };

    /** \cond */
    template<typename MeshOrSegmentHandleT, typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT>
    struct neighbor_range<const MeshOrSegmentHandleT, ElementTypeOrTagT, ConnectorElementTypeOrTagT>
    {
      typedef typename const_neighbor_range<MeshOrSegmentHandleT, ElementTypeOrTagT, ConnectorElementTypeOrTagT>::type type;
    };
    /** \endcond */

  }


  namespace detail
  {

    /** @brief For internal use only */
    template<typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT, typename mesh_type, typename neigbour_accessor_type>
    void create_neighbor_information(mesh_type & mesh_obj, neigbour_accessor_type accessor)
    {
      typedef typename viennagrid::result_of::element_tag< ElementTypeOrTagT >::type          element_tag;
      typedef typename viennagrid::result_of::element_tag< ConnectorElementTypeOrTagT >::type connector_element_tag;

      typedef typename viennagrid::result_of::element< mesh_type, ElementTypeOrTagT >::type   element_type;

      typedef typename viennagrid::result_of::element_range< mesh_type, ElementTypeOrTagT >::type element_range_type;
      typedef typename viennagrid::result_of::iterator< element_range_type >::type                element_range_iterator;

      element_range_type elements(mesh_obj);

      for ( element_range_iterator it = elements.begin(); it != elements.end(); ++it )
      {
        accessor( *it ).clear();
        accessor( *it ).set_base_container( viennagrid::get< element_type >( element_collection(mesh_obj) ) );
      }

      typedef typename viennagrid::result_of::element_range< mesh_type, connector_element_tag >::type     connector_element_range_type;
      typedef typename viennagrid::result_of::iterator< connector_element_range_type >::type              connector_element_range_iterator;

      connector_element_range_type connector_elements(mesh_obj);
      for ( connector_element_range_iterator it = connector_elements.begin(); it != connector_elements.end(); ++it )
      {
        typedef typename viennagrid::result_of::coboundary_range< mesh_type, connector_element_tag, element_tag >::type   element_on_connector_element_range_type;
        typedef typename viennagrid::result_of::iterator< element_on_connector_element_range_type >::type                 element_on_connector_element_range_iterator;

        element_on_connector_element_range_type coboundary_range = viennagrid::coboundary_elements<connector_element_tag, element_tag>( mesh_obj, it.handle() );
        if (coboundary_range.empty())
            continue;

        element_on_connector_element_range_iterator jt1 = coboundary_range.begin(); ++jt1;
        for (; jt1 != coboundary_range.end(); ++jt1)
        {
          for (element_on_connector_element_range_iterator jt0 = coboundary_range.begin(); jt0 != jt1; ++jt0)
          {
            typedef typename viennagrid::result_of::neighbor_view<mesh_type, ElementTypeOrTagT, ConnectorElementTypeOrTagT>::type view_type;
            view_type & view_obj = accessor( *jt0 );

            typename view_type::iterator kt = view_obj.begin();
            for (; kt != view_obj.end(); ++kt)
              if ( kt->id() == jt1->id() )
                break;

            if (kt == view_obj.end())
            {
              accessor( *jt0 ).insert_handle( jt1.handle() );
              accessor( *jt1 ).insert_handle( jt0.handle() );
            }
          }
        }
      }
    }


    /** @brief For internal use only */
    template<typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT, typename mesh_type>
    void create_neighbor_information(mesh_type & mesh_obj)
    {
      typedef typename viennagrid::result_of::element_tag< ElementTypeOrTagT >::type           element_tag;
      typedef typename viennagrid::result_of::element_tag< ConnectorElementTypeOrTagT >::type  connector_element_tag;
      typedef typename viennagrid::result_of::element< mesh_type, ElementTypeOrTagT >::type    element_type;

      typedef typename viennagrid::detail::result_of::lookup<
              typename viennagrid::detail::result_of::lookup<
                  typename mesh_type::appendix_type,
                  neighbor_collection_tag
              >::type,
              viennagrid::static_pair<element_tag, connector_element_tag>
              >::type neighbor_container_wrapper_type;
      neighbor_container_wrapper_type & neighbor_container_wrapper = detail::neighbor_collection<element_tag, connector_element_tag>(mesh_obj);

      create_neighbor_information<ElementTypeOrTagT, ConnectorElementTypeOrTagT>( mesh_obj, viennagrid::make_accessor<element_type>(neighbor_container_wrapper.container) );

      detail::update_change_counter( mesh_obj, neighbor_container_wrapper.change_counter );
    }



    /** @brief For internal use only */
    template<typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT, typename neigbour_accessor_type, typename ElementTag, typename WrappedConfigT>
    viennagrid::detail::container_range_wrapper<typename neigbour_accessor_type::value_type>
    neighbor_elements(neigbour_accessor_type accessor, viennagrid::element<ElementTag, WrappedConfigT> & element)
    {
      typedef viennagrid::detail::container_range_wrapper<typename neigbour_accessor_type::value_type> range_type;
      return range_type( accessor( element ) );
    }

    /** @brief For internal use only */
    template<typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT, typename neigbour_accessor_type, typename ElementTag, typename WrappedConfigT>
    viennagrid::detail::container_range_wrapper<const typename neigbour_accessor_type::value_type>
    neighbor_elements(neigbour_accessor_type const accessor, viennagrid::element<ElementTag, WrappedConfigT> const & element)
    {
      typedef viennagrid::detail::container_range_wrapper<const typename neigbour_accessor_type::value_type> range_type;
      return range_type( accessor( element ) );
    }


    /** @brief For internal use only */
    template<typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT, typename neigbour_accessor_type, typename WrappedConfigT, typename ElementOrHandleT>
    viennagrid::detail::container_range_wrapper<typename neigbour_accessor_type::value_type>
    neighbor_elements(viennagrid::mesh<WrappedConfigT> & mesh_obj, neigbour_accessor_type accessor, ElementOrHandleT & element_or_handle)
    {
      return neighbor_elements<ElementTypeOrTagT, ConnectorElementTypeOrTagT>( accessor, viennagrid::dereference_handle(mesh_obj, element_or_handle) );
    }

    /** @brief For internal use only */
    template<typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT, typename neigbour_accessor_type, typename WrappedConfigT, typename ElementOrHandleT>
    viennagrid::detail::container_range_wrapper<const typename neigbour_accessor_type::value_type>
    neighbor_elements(viennagrid::mesh<WrappedConfigT> const & mesh_obj, neigbour_accessor_type const accessor, ElementOrHandleT const & element_or_handle)
    {
      return neighbor_elements<ElementTypeOrTagT, ConnectorElementTypeOrTagT>( accessor, viennagrid::dereference_handle(mesh_obj, element_or_handle) );
    }

  }

  /** @brief Obtaines a neighbor range of an element within a mesh. This function caches the neighbor information and re-creates it if the cached information is out of date. The worst case runtime of a re-creation is linear in the number of elements of type ConnectorElementTypeOrTagT time the number of elements of type ElementTypeOrTagT within the mesh.
    *
    * @tparam ElementTypeOrTagT             The base element type/tag from which the neighbor range is obtained
    * @tparam ConnectorElementTypeOrTagT    The connector element type/tag
    * @tparam WrappedConfigT                The wrapped config of the mesh
    * @tparam ElementOrHandleT              The element or handle type for which the neighbor range is obtained
    * @param  mesh_obj                      The host mesh object in which the elements of the neighbor range exist
    * @param  element_or_handle             A handle or the element for which the neighbor range is obained
    * @return                               The neighbor range
    */
  template<typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT, typename WrappedConfigT, typename ElementOrHandleT>
  typename result_of::neighbor_range<viennagrid::mesh<WrappedConfigT>, ElementTypeOrTagT, ConnectorElementTypeOrTagT>::type
  neighbor_elements(viennagrid::mesh<WrappedConfigT> & mesh_obj, ElementOrHandleT const & element_or_handle)
  {
    typedef viennagrid::mesh<WrappedConfigT> mesh_type;
    typedef typename viennagrid::result_of::element_tag< ElementTypeOrTagT >::type element_tag;
    typedef typename viennagrid::result_of::element_tag< ConnectorElementTypeOrTagT >::type connector_element_tag;
    typedef typename viennagrid::result_of::element< mesh_type, ElementTypeOrTagT >::type element_type;

    typedef typename viennagrid::detail::result_of::lookup<
            typename viennagrid::detail::result_of::lookup<
                typename mesh_type::appendix_type,
                neighbor_collection_tag
            >::type,
            viennagrid::static_pair<element_tag, connector_element_tag>
            >::type neighbor_container_wrapper_type;
    neighbor_container_wrapper_type & neighbor_container_wrapper = detail::neighbor_collection<element_tag, connector_element_tag>(mesh_obj);

    if ( detail::is_obsolete( mesh_obj, neighbor_container_wrapper.change_counter ) )
      detail::create_neighbor_information<ElementTypeOrTagT, ConnectorElementTypeOrTagT>(mesh_obj);

    return detail::neighbor_elements<ElementTypeOrTagT, ConnectorElementTypeOrTagT>( viennagrid::make_accessor<element_type>(neighbor_container_wrapper.container), viennagrid::dereference_handle(mesh_obj, element_or_handle) );
  }

  /** @brief Obtaines a const neighbor range of an element within a mesh. This function caches the neighbor information and re-creates it if the cached information is out of date. The worst case runtime of a re-creation is linear in the number of elements of type ConnectorElementTypeOrTagT time the number of elements of type ElementTypeOrTagT within the mesh.
    *
    * @tparam ElementTypeOrTagT             The base element type/tag from which the neighbor range is obtained
    * @tparam ConnectorElementTypeOrTagT    The connector element type/tag
    * @tparam WrappedConfigT                The wrapped config of the mesh
    * @tparam ElementOrHandleT              The element or handle type for which the neighbor range is obtained
    * @param  mesh_obj                      The host mesh object in which the elements of the neighbor range exist
    * @param  element_or_handle             A handle or the element for which the neighbor range is obained
    * @return                               The const neighbor range
    */
  template<typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT, typename WrappedConfigT, typename ElementOrHandleT>
  typename result_of::const_neighbor_range<viennagrid::mesh<WrappedConfigT>, ElementTypeOrTagT, ConnectorElementTypeOrTagT>::type
  neighbor_elements(viennagrid::mesh<WrappedConfigT> const & mesh_obj, ElementOrHandleT const & element_or_handle)
  {
    typedef viennagrid::mesh<WrappedConfigT> mesh_type;
    typedef typename viennagrid::result_of::element_tag< ElementTypeOrTagT >::type element_tag;
    typedef typename viennagrid::result_of::element_tag< ConnectorElementTypeOrTagT >::type connector_element_tag;
    typedef typename viennagrid::result_of::element< mesh_type, ElementTypeOrTagT >::type element_type;

    typedef typename viennagrid::detail::result_of::lookup<
            typename viennagrid::detail::result_of::lookup<
                typename mesh_type::appendix_type,
                neighbor_collection_tag
            >::type,
            viennagrid::static_pair<element_tag, connector_element_tag>
            >::type neighbor_container_wrapper_type;
    neighbor_container_wrapper_type const & neighbor_container_wrapper = detail::neighbor_collection<element_tag, connector_element_tag>(mesh_obj);

    if ( detail::is_obsolete( mesh_obj, neighbor_container_wrapper.change_counter ) )
      detail::create_neighbor_information<ElementTypeOrTagT, ConnectorElementTypeOrTagT>( const_cast<mesh_type&>(mesh_obj) );


    return detail::neighbor_elements<ElementTypeOrTagT, ConnectorElementTypeOrTagT>( viennagrid::make_accessor<element_type>(neighbor_container_wrapper.container), viennagrid::dereference_handle(mesh_obj, element_or_handle) );
  }


  /** @brief Obtaines a neighbor range of an element within a segment. This function caches the neighbor information and re-creates it if the cached information is out of date. The worst case runtime of a re-creation is linear in the number of elements of type ConnectorElementTypeOrTagT time the number of elements of type ElementTypeOrTagT within the segment.
    *
    * @tparam ElementTypeOrTagT             The base element type/tag from which the neighbor range is obtained
    * @tparam ConnectorElementTypeOrTagT    The connector element type/tag
    * @tparam SegmentationT                 The segmentation type of the segment type
    * @tparam ElementOrHandleT              The element or handle type for which the neighbor range is obtained
    * @param  segment                       The host segment object in which the elements of the neighbor range exist
    * @param  element_or_handle             A handle or the element for which the neighbor range is obained
    * @return                               The neighbor range
    */
  template<typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT, typename SegmentationT, typename ElementOrHandleT>
  typename result_of::neighbor_range<segment_handle<SegmentationT>, ElementTypeOrTagT, ConnectorElementTypeOrTagT>::type
  neighbor_elements(segment_handle<SegmentationT> & segment, ElementOrHandleT const & element_or_handle)
  {
    return neighbor_elements<ElementTypeOrTagT, ConnectorElementTypeOrTagT>( segment.view(), element_or_handle );
  }

  /** @brief Obtaines a const neighbor range of an element within a segment. This function caches the neighbor information and re-creates it if the cached information is out of date. The worst case runtime of a re-creation is linear in the number of elements of type ConnectorElementTypeOrTagT time the number of elements of type ElementTypeOrTagT within the segment.
    *
    * @tparam ElementTypeOrTagT             The base element type/tag from which the neighbor range is obtained
    * @tparam ConnectorElementTypeOrTagT    The connector element type/tag
    * @tparam SegmentationT                 The segmentation type of the segment type
    * @tparam ElementOrHandleT              The element or handle type for which the neighbor range is obtained
    * @param  segment                       The host segment object in which the elements of the neighbor range exist
    * @param  element_or_handle             A handle or the element for which the neighbor range is obained
    * @return                               The const neighbor range
    */
  template<typename ElementTypeOrTagT, typename ConnectorElementTypeOrTagT, typename SegmentationT, typename ElementOrHandleT>
  typename result_of::const_neighbor_range<segment_handle<SegmentationT>, ElementTypeOrTagT, ConnectorElementTypeOrTagT>::type
  neighbor_elements(segment_handle<SegmentationT> const & segment, ElementOrHandleT const & element_or_handle)
  {
    return neighbor_elements<ElementTypeOrTagT, ConnectorElementTypeOrTagT>( segment.view(), element_or_handle );
  }

}


#endif
