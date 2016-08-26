#ifndef VIENNAGRID_MESH_HPP
#define VIENNAGRID_MESH_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include <typeinfo>
#include "viennagrid/forwards.hpp"

#include "viennagrid/meta/algorithm.hpp"

#include "viennagrid/storage/id_generator.hpp"
#include "viennagrid/storage/inserter.hpp"
#include "viennagrid/storage/algorithm.hpp"

#include "viennagrid/config/element_config.hpp"
#include "viennagrid/config/mesh_config.hpp"

#include "viennagrid/element/element_view.hpp"

/** @file viennagrid/mesh/mesh.hpp
    @brief Contains definition and implementation of mesh and mesh views
*/


namespace viennagrid
{
  namespace detail
  {
    /** @brief For internal use only */
    template<typename SourceWrappedConfigT, typename DestinationWrappedConfigT>
    void fix_handles( viennagrid::mesh<SourceWrappedConfigT> const & source_mesh_obj, viennagrid::mesh<DestinationWrappedConfigT> & destination_mesh );

    /** @brief For internal use only */
    template<typename container_collection_type>
    class view_mesh_setter
    {
    public:

      view_mesh_setter(container_collection_type & mesh_obj) : mesh_obj_(mesh_obj) {}

      template<typename container_type>
      void operator()( container_type & container )
      {
          typedef typename container_type::value_type value_type;
          container.set_base_container( viennagrid::get<value_type>(mesh_obj_) );
      }

    private:
      container_collection_type & mesh_obj_;
    };


    /** @brief For internal use only */
    template<typename container_type_, typename change_counter_type>
    struct coboundary_container_wrapper
    {
        typedef container_type_ container_type;
        coboundary_container_wrapper() : change_counter(0) {}

        change_counter_type change_counter;
        container_type container;
    };

    /** @brief For internal use only */
    template<typename container_type_, typename change_counter_type>
    struct neighbor_container_wrapper
    {
        typedef container_type_ container_type;
        neighbor_container_wrapper() : change_counter(0) {}

        change_counter_type change_counter;
        container_type container;
    };

    /** @brief For internal use only */
    template<typename container_type_, typename change_counter_type>
    struct boundary_information_wrapper
    {
        typedef container_type_ container_type;
        boundary_information_wrapper() : change_counter(0) {}

        change_counter_type change_counter;
        container_type container;
    };

  }

  namespace result_of
  {
    /** \cond */
    template<typename ElementTypelistT, typename ContainerTypemapT>
    struct filter_element_container;

    template<typename ContainerTypemapT>
    struct filter_element_container<viennagrid::null_type, ContainerTypemapT>
    {
        typedef viennagrid::null_type type;
    };

    template<typename ElementT, typename TailT, typename ContainerTypemapT>
    struct filter_element_container<viennagrid::typelist< ElementT, TailT> , ContainerTypemapT>
    {
        typedef typename viennagrid::detail::result_of::find<ContainerTypemapT, ElementT>::type result_type;

        typedef typename filter_element_container<TailT, ContainerTypemapT>::type new_tail;

        typedef typename viennagrid::detail::IF<
            viennagrid::detail::EQUAL< result_type, viennagrid::not_found >::value,
            new_tail,
            viennagrid::typelist<
                result_type,
                new_tail
            >
        >::type type;
    };


    /** @brief For internal use only */
    template <typename WrappedConfigT>
    struct mesh_element_collection_type
    {
      typedef typename config::result_of::element_collection< WrappedConfigT >::type   type;
    };

    template <typename WrappedMeshConfigType, typename ElementTypeList, typename ContainerConfig>
    struct mesh_element_collection_type< viennagrid::detail::decorated_mesh_view_config<WrappedMeshConfigType, ElementTypeList, ContainerConfig> >
    {
      typedef typename WrappedMeshConfigType::type   MeshConfigType;

      typedef typename mesh_element_collection_type<WrappedMeshConfigType>::type   full_mesh_element_collection_type;

      typedef typename filter_element_container<ElementTypeList, typename full_mesh_element_collection_type::typemap>::type      view_container_collection_typemap;
      typedef typename viennagrid::result_of::view_collection<view_container_collection_typemap, ContainerConfig>::type   type;
    };

    /** @brief For internal use only */
    template <typename WrappedConfigT>
    struct mesh_appendix_type
    {
      typedef typename WrappedConfigT::type   ConfigType;

      typedef collection< typename viennagrid::result_of::coboundary_container_collection_typemap<WrappedConfigT>::type >   coboundary_collection_type;
      typedef collection< typename viennagrid::result_of::neighbor_container_collection_typemap< WrappedConfigT>::type >   neighbor_collection_type;
      typedef collection< typename viennagrid::result_of::boundary_information_collection_typemap<WrappedConfigT>::type >   boundary_information_type;

      typedef typename viennagrid::collection<
            typename viennagrid::make_typemap<

                coboundary_collection_tag,
                coboundary_collection_type,

                neighbor_collection_tag,
                neighbor_collection_type,

                boundary_information_collection_tag,
                boundary_information_type

            >::type
      > type;
    };

    template <typename WrappedMeshConfigT, typename ElementTypeListT, typename ContainerConfigT>
    struct mesh_appendix_type< viennagrid::detail::decorated_mesh_view_config<WrappedMeshConfigT, ElementTypeListT, ContainerConfigT> >
    {
      typedef typename mesh_appendix_type<WrappedMeshConfigT>::type    type;
    };


    /** @brief For internal use only */
    template <typename WrappedConfigT>
    struct mesh_change_counter_type
    {
      typedef typename config::result_of::query<WrappedConfigT, long, config::mesh_change_counter_tag>::type  type;
    };

    template <typename WrappedMeshConfigT, typename ElementTypeList, typename ContainerConfig>
    struct mesh_change_counter_type< viennagrid::detail::decorated_mesh_view_config<WrappedMeshConfigT, ElementTypeList, ContainerConfig> >
    {
      typedef typename config::result_of::query<WrappedMeshConfigT, long, config::mesh_change_counter_tag>::type  type;
    };


    /** @brief For internal use only */
    template <typename WrappedConfigType>
    struct mesh_inserter_type
    {
      typedef typename config::result_of::element_collection<WrappedConfigType>::type                                                       element_collection_type;
      typedef typename viennagrid::result_of::id_generator<WrappedConfigType>::type                                                 id_generator_type;
      typedef typename mesh_change_counter_type<WrappedConfigType>::type change_counter_type;

      typedef typename viennagrid::result_of::physical_inserter<element_collection_type, change_counter_type, id_generator_type>::type   type;
    };

    template <typename WrappedMeshConfigT, typename ElementTypeList, typename ContainerConfig>
    struct mesh_inserter_type< viennagrid::detail::decorated_mesh_view_config<WrappedMeshConfigT, ElementTypeList, ContainerConfig> >
    {
      typedef viennagrid::detail::decorated_mesh_view_config<WrappedMeshConfigT, ElementTypeList, ContainerConfig>  argument_type;
      typedef WrappedMeshConfigT ConfigType;

      typedef typename mesh_element_collection_type<argument_type>::type                             view_container_collection_type;
      typedef typename mesh_inserter_type<WrappedMeshConfigT>::type                             full_mesh_inserter_type;
      typedef typename mesh_change_counter_type<WrappedMeshConfigT>::type change_counter_type;

      typedef typename viennagrid::result_of::recursive_inserter<view_container_collection_type, change_counter_type, full_mesh_inserter_type>::type      type;
    };
    /** \endcond */
  }

  /** @brief The main mesh class holding all the different elements. The data structure is configured using a configuration class. See viennagrid::config for predefined configurations.
    *
    * @tparam WrappedConfigType  A class wrapping the configuration typemap. See namespace viennagrid::config for examples.
    */
  template <typename WrappedConfigType>
  class mesh
  {
    typedef viennagrid::mesh<WrappedConfigType> self_type;

  public:
    typedef WrappedConfigType                    wrapped_config_type;
    typedef typename WrappedConfigType::type     config_type;


    typedef typename result_of::mesh_element_collection_type<WrappedConfigType>::type     element_collection_type;
    typedef typename result_of::mesh_appendix_type<WrappedConfigType>::type               appendix_type;
    typedef typename result_of::mesh_change_counter_type<WrappedConfigType>::type         change_counter_type;
    typedef typename result_of::mesh_inserter_type<WrappedConfigType>::type               inserter_type;


    /** @brief Default constructor */
    mesh() : inserter( element_container_collection, change_counter_ ), change_counter_(0) {}

    /** @brief Constructor for creating a view from another mesh/mesh view
      *
      * @tparam OtherWrappedConfigT     Wrapped config type of the mesh type from which the view is created
      * @tparam proxy                   Proxy object wrapping the mesh object from which the view is created
      */
    template<typename OtherWrappedConfigT>
    mesh( mesh_proxy<viennagrid::mesh<OtherWrappedConfigT> > proxy ) : change_counter_(0)
    {
        typedef typename viennagrid::mesh<OtherWrappedConfigT>::element_collection_type   other_element_collection_type;

        detail::view_mesh_setter< other_element_collection_type > functor(proxy.mesh_obj_->element_collection());
        viennagrid::detail::for_each(element_container_collection, functor);

        inserter = inserter_type( element_container_collection, change_counter_,proxy.mesh_obj_->get_inserter() );
    }

    ~mesh() {}


    /** @brief Copy constructor, remember that copying a mesh might have performance impact due to handle fixing: handles for boundary element will point to other locations.
      *
      * @param  other                   The mesh which is copied to *this
      */
    mesh(const mesh & other) : element_container_collection(other.element_container_collection), appendix_(other.appendix_), inserter(other.inserter), change_counter_(other.change_counter_)
    {
      inserter.set_mesh_info( element_container_collection, change_counter_ );
      increment_change_counter();

      detail::fix_handles(other, *this);
    }

    /** @brief Assignement operator, remember that assigning a mesh to another might have performance impact due to handle fixing: handles for boundary element will point to other locations.
      *
      * @param  other                   The mesh which is assigned to *this
      * @return                         reference to *this
      */
    mesh & operator=( mesh const & other)
    {
//           element_container_collection = element_collection_type();
      element_container_collection = other.element_container_collection;

      appendix_ = other.appendix_;
      inserter = other.inserter;
      change_counter_ = other.change_counter_;

      inserter.set_mesh_info( element_container_collection, change_counter_ );
      increment_change_counter();

      detail::fix_handles(other, *this);
      return *this;
    }

    /** @brief Completely clears a mesh
      *
      */
    void clear()
    {
      *this = mesh();
    }

  public:

    // TODO no direct access to collection!

    /** @brief For internal use only */
    element_collection_type & element_collection() { return element_container_collection; }
    element_collection_type const & element_collection() const { return element_container_collection; }

    /** @brief For internal use only */
    appendix_type & appendix() { return appendix_; }
    appendix_type const & appendix() const { return appendix_; }

    /** @brief For internal use only */
    inserter_type & get_inserter() { return inserter; }
    inserter_type const & get_inserter() const { return inserter; }

    /** @brief For internal use only */
    bool is_obsolete( change_counter_type change_counter_to_check ) const { return change_counter_to_check != change_counter_; }
    void update_change_counter( change_counter_type & change_counter_to_update ) const { change_counter_to_update = change_counter_; }
    void increment_change_counter() { ++change_counter_; }

  protected:
    element_collection_type element_container_collection;

    appendix_type appendix_;
    inserter_type inserter;

    change_counter_type change_counter_;
  };

  /** @brief Completely clears a mesh.
    *
    */
  template<typename WrappedConfigT>
  void clear( mesh<WrappedConfigT> & mesh_ )
  {
    mesh_.clear();
  }


  namespace result_of
  {
    /** @brief Metafunction for obtaining a mesh from a config
     *
     * @tparam WrappedConfigT     The configuration of the mesh
     */
    template<typename WrappedConfigType>
    struct mesh
    {
      typedef viennagrid::mesh<WrappedConfigType> type;
    };
  }


  namespace detail
  {

    /** @brief For internal use only */
    template<typename WrappedConfigType>
    bool is_obsolete( viennagrid::mesh<WrappedConfigType> const & mesh_obj, typename viennagrid::mesh<WrappedConfigType>::change_counter_type change_counter_to_check )
    { return mesh_obj.is_obsolete( change_counter_to_check ); }

    /** @brief For internal use only */
    template<typename WrappedConfigType>
    void update_change_counter( viennagrid::mesh<WrappedConfigType> & mesh_obj, typename viennagrid::mesh<WrappedConfigType>::change_counter_type & change_counter_to_update )
    { mesh_obj.update_change_counter( change_counter_to_update ); }

    /** @brief For internal use only */
    template<typename WrappedConfigType>
    void increment_change_counter( viennagrid::mesh<WrappedConfigType> & mesh_obj)
    { mesh_obj.increment_change_counter(); }









    /** @brief For internal use only */
    template<typename element_tag, typename coboundary_tag, typename mesh_type>
    typename viennagrid::detail::result_of::lookup<
                typename viennagrid::detail::result_of::lookup<
                    typename mesh_type::appendix_type,
                    coboundary_collection_tag
                >::type,
                viennagrid::static_pair<element_tag, coboundary_tag>
              >::type &
    coboundary_collection( mesh_type & mesh_obj)
    { return viennagrid::get< viennagrid::static_pair<element_tag, coboundary_tag> >( viennagrid::get<coboundary_collection_tag>( mesh_obj.appendix() ) );}

    /** @brief For internal use only */
    template<typename element_tag, typename coboundary_tag, typename mesh_type>
    typename viennagrid::detail::result_of::lookup<
                typename viennagrid::detail::result_of::lookup<
                    typename mesh_type::appendix_type,
                    coboundary_collection_tag
                >::type,
                viennagrid::static_pair<element_tag, coboundary_tag>
              >::type const &
    coboundary_collection( mesh_type const & mesh_obj)
    { return viennagrid::get< viennagrid::static_pair<element_tag, coboundary_tag> >( viennagrid::get<coboundary_collection_tag>( mesh_obj.appendix() ) );}


    /** @brief For internal use only */
    template<typename element_tag, typename connector_element_tag, typename mesh_type>
    typename viennagrid::detail::result_of::lookup<
                typename viennagrid::detail::result_of::lookup<
                    typename mesh_type::appendix_type,
                    neighbor_collection_tag
                >::type,
                viennagrid::static_pair<element_tag, connector_element_tag>
              >::type &
    neighbor_collection( mesh_type & mesh_obj)
    { return viennagrid::get< viennagrid::static_pair<element_tag, connector_element_tag> >( viennagrid::get<neighbor_collection_tag>( mesh_obj.appendix() ) ); }

    /** @brief For internal use only */
    template<typename element_tag, typename connector_element_tag, typename mesh_type>
    typename viennagrid::detail::result_of::lookup<
                typename viennagrid::detail::result_of::lookup<
                    typename mesh_type::appendix_type,
                    neighbor_collection_tag
                >::type,
                viennagrid::static_pair<element_tag, connector_element_tag>
              >::type const &
    neighbor_collection( mesh_type const & mesh_obj)
    { return viennagrid::get< viennagrid::static_pair<element_tag, connector_element_tag> >( viennagrid::get<neighbor_collection_tag>( mesh_obj.appendix() ) ); }


    /** @brief For internal use only */
    template<typename element_tag, typename mesh_type>
    typename viennagrid::detail::result_of::lookup<
        typename viennagrid::detail::result_of::lookup<
            typename mesh_type::appendix_type,
            boundary_information_collection_tag
        >::type,
        element_tag
    >::type &
    boundary_information_collection( mesh_type & mesh_obj)
    { return viennagrid::get<element_tag>( viennagrid::get<boundary_information_collection_tag>( mesh_obj.appendix() ) ); }

    /** @brief For internal use only */
    template<typename element_tag, typename mesh_type>
    typename viennagrid::detail::result_of::lookup<
        typename viennagrid::detail::result_of::lookup<
            typename mesh_type::appendix_type,
            boundary_information_collection_tag
        >::type,
        element_tag
    >::type const &
    boundary_information_collection( mesh_type const & mesh_obj)
    { return viennagrid::get<element_tag>( viennagrid::get<boundary_information_collection_tag>( mesh_obj.appendix() ) ); }
  }
}


namespace viennagrid
{
  namespace result_of
  {
    /** \cond */
    template<typename TypemapT>
    struct container_collection_typemap< viennagrid::collection<TypemapT> >
    {
      typedef TypemapT type;
    };

    template<typename TypemapT>
    struct container_collection_typemap< const viennagrid::collection<TypemapT> >
    {
      typedef TypemapT type;
    };

    template<typename KeyT, typename ValueT, typename TailT>
    struct container_collection_typemap< viennagrid::typelist< viennagrid::static_pair<KeyT, ValueT>, TailT > >
    {
      typedef viennagrid::typelist< viennagrid::static_pair<KeyT, ValueT>, TailT > type;
    };


    // doxygen docu in forwards.hpp
    template<typename TypemapT>
    struct element_collection< collection<TypemapT> >
    {
      typedef collection<TypemapT> type;
    };

    template<typename WrappedConfigT>
    struct element_collection< viennagrid::mesh<WrappedConfigT> >
    {
      typedef typename viennagrid::mesh<WrappedConfigT>::element_collection_type type;
    };

    template<typename WrappedConfigT>
    struct element_collection< const viennagrid::mesh<WrappedConfigT> >
    {
      typedef typename viennagrid::mesh<WrappedConfigT>::element_collection_type type;
    };
    /** \endcond */


    /** @brief Metafunction for obtaining the element typelist of something
     *
     * @tparam SomethingT     The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct element_typelist
    {
      typedef typename element_collection<SomethingT>::type container_collection;
      typedef typename viennagrid::detail::result_of::key_typelist<typename container_collection::typemap >::type type;
    };

    /** \cond */
    template<typename HostElementT>
    struct element_typelist_for_element;

    template<>
    struct element_typelist_for_element<viennagrid::null_type>
    {
      typedef viennagrid::null_type type;
    };

    template<typename HeadT, typename TailT>
    struct element_typelist_for_element< viennagrid::typelist<HeadT, TailT> >
    {
      typedef typename HeadT::first BoundaryContainerType;
      typedef typename BoundaryContainerType::value_type CurrentElementType;

      typedef viennagrid::typelist<
            CurrentElementType,
            typename element_typelist_for_element<TailT>::type
          > type;
    };

    template<typename ElementTagT, typename WrappedConfigT>
    struct element_typelist< viennagrid::element<ElementTagT, WrappedConfigT> >
    {
      typedef typename viennagrid::element<ElementTagT, WrappedConfigT>::bnd_cell_container_typelist bnd_cell_container_typelist;
      typedef typename element_typelist_for_element<bnd_cell_container_typelist>::type type;
    };
    /** \endcond */

    /** @brief Metafunction for obtaining the element typelist of something
     *
     * @tparam SomethingT     The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct element_taglist
    {
      typedef typename viennagrid::detail::TRANSFORM<
          result_of::element_tag,
          typename element_typelist<SomethingT>::type
      >::type type;
    };


    /** @brief Metafunction for query if an element type/tag is boundary element of another host element
     *
     * @tparam HostElementT                 The host element type
     * @tparam BoundaryElementTypeOrTagT    The element type/tag to be queried if it is a boundary element
     */
    template<typename HostElementT, typename BoundaryElementTypeOrTagT>
    struct is_boundary
    {
      typedef typename result_of::element_tag<BoundaryElementTypeOrTagT>::type BoundaryElementTag;
      static const bool value =
        detail::result_of::index_of<
          typename element_taglist<HostElementT>::type,
          BoundaryElementTag
        >::value != -1;
    };


    /** \cond */
    template<typename AllElementsTypelistT, typename ElementT>
    struct referencing_element_typelist_impl;

    template<typename ElementT>
    struct referencing_element_typelist_impl<viennagrid::null_type, ElementT>
    {
      typedef viennagrid::null_type type;
    };

    template<typename HeadT, typename TailT, typename ElementT>
    struct referencing_element_typelist_impl< viennagrid::typelist<HeadT, TailT>, ElementT >
    {
      typedef typename referencing_element_typelist_impl<TailT, ElementT>::type tail_typelist;

      typedef typename viennagrid::detail::IF<
          is_boundary<HeadT, ElementT>::value,
          viennagrid::typelist<HeadT, tail_typelist>,
          tail_typelist
      >::type type;
    };
    /** \endcond */

    /** @brief Metafunction for obtaining the an element typelist including all element which references a given element. e.g. in a default triangle mesh the referencing element typelist based on the mesh for a vertex contains a line type and a triangle type. The host type can also be an element in which case all boundary elements referening the given element are returned (in a default tetrahedron mesh the referencing elements for a vertex based on a triangle contains only a line type)
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     * @tparam ElementTypeOrTagT  The element type/tag which the resulting elements references
     */
    template<typename SomethingT, typename ElementTypeOrTagT>
    struct referencing_element_typelist
    {
      typedef typename element<SomethingT, ElementTypeOrTagT>::type ElementType;
      typedef typename element_typelist<SomethingT>::type AllElementsTypelist;
      typedef typename referencing_element_typelist_impl<AllElementsTypelist, ElementType>::type type;
    };


    /** @brief Metafunction for returning the status counter type from a mesh or segmentation */
    template<typename SomethingT>
    struct change_counter_type;

    /** \cond */
    template<typename WrappedConfigT>
    struct change_counter_type< viennagrid::mesh<WrappedConfigT> >
    {
      typedef typename viennagrid::mesh<WrappedConfigT>::change_counter_type type;
    };
    /** \endcond */
  }

  namespace detail
  {
    /** @brief For internal use only */
    template <typename WrappedConfigType, typename ElementTypeList, typename ContainerConfig>
    class decorated_mesh_view_config
    {
    private:
      typedef typename config::result_of::element_collection< WrappedConfigType >::type                                                   element_collection_type;
      typedef typename viennagrid::result_of::id_generator<WrappedConfigType>::type                                               id_generator_type;

      typedef typename viennagrid::result_of::filter_element_container<ElementTypeList, typename element_collection_type::typemap>::type        view_container_collection_typemap;
      typedef typename viennagrid::result_of::view_collection<view_container_collection_typemap, ContainerConfig>::type    view_container_collection_type;


    public:
      typedef view_container_collection_typemap    type;

      typedef WrappedConfigType                     mesh_config_type;
    };

    /** @brief For internal use only */
    template <typename WrappedConfigType, typename E, typename C, typename ElementTypeList, typename ContainerConfig>
    class decorated_mesh_view_config< decorated_mesh_view_config<WrappedConfigType, E, C>, ElementTypeList, ContainerConfig>
    {
    private:
      typedef typename config::result_of::element_collection< WrappedConfigType >::type                                                   element_collection_type;
      typedef typename viennagrid::result_of::id_generator<WrappedConfigType>::type                                               id_generator_type;

      typedef typename viennagrid::result_of::filter_element_container<ElementTypeList, typename element_collection_type::typemap>::type        view_container_collection_typemap;
      typedef typename viennagrid::result_of::view_collection<view_container_collection_typemap, ContainerConfig>::type    view_container_collection_type;


    public:
      typedef view_container_collection_typemap    type;

      typedef typename decorated_mesh_view_config<WrappedConfigType, E, C>::mesh_config_type      mesh_config_type;
    };
  }


  namespace result_of
  {
    /** @brief Metafunction for obtaining a mesh view from a mesh using an element type list and a container configuration
     *
     * @tparam MeshT            The host mesh type
     * @tparam ElementTypelistT   A typelist of all element types which will be referenced by the mesh view. All element from the mesh are used as default.
     * @tparam ContainerConfigT   A configuration typemap which container should be used for storing the handles within the mesh view. The default view container config is used as default (std::set is used).
     */
    template<
        typename MeshT,
        typename ElementTypelistT =
            typename viennagrid::detail::result_of::key_typelist<
                typename element_collection<MeshT>::type::typemap
            >::type,
        typename ContainerConfigT =
            default_view_container_config
        >
    struct mesh_view_from_typelist
    {
      typedef viennagrid::mesh< viennagrid::detail::decorated_mesh_view_config<typename MeshT::wrapped_config_type, ElementTypelistT, ContainerConfigT> >  type;
    };


    /** @brief Metafunction for obtaining a mesh view from a mesh. Elements can be directly given. If viennagrid::null_type is specified somewhere all following types will be ignored. The default type for all element types is viennagrid::null_type.
     *
     * @tparam MeshT              The host mesh type
     * @tparam Element0TypeOrTagT   The first element type which is present in the mesh view
     * @tparam Element1TypeOrTagT   The second element type which is present in the mesh view
     * @tparam Element2TypeOrTagT   The third element type which is present in the mesh view
     * @tparam Element3TypeOrTagT   The forth element type which is present in the mesh view
     * @tparam Element4TypeOrTagT   The fifth element type which is present in the mesh view
     * @tparam Element5TypeOrTagT   The sixth element type which is present in the mesh view
     * @tparam Element6TypeOrTagT   The seventh element type which is present in the mesh view
     * @tparam Element7TypeOrTagT   The eighth element type which is present in the mesh view
     * @tparam Element8TypeOrTagT   The nineth element type which is present in the mesh view
     * @tparam Element9TypeOrTagT   The tenth element type which is present in the mesh view
     */
    template<typename MeshT,
             typename Element0TypeOrTagT = viennagrid::null_type, typename Element1TypeOrTagT = viennagrid::null_type,
             typename Element2TypeOrTagT = viennagrid::null_type, typename Element3TypeOrTagT = viennagrid::null_type,
             typename Element4TypeOrTagT = viennagrid::null_type, typename Element5TypeOrTagT = viennagrid::null_type,
             typename Element6TypeOrTagT = viennagrid::null_type, typename Element7TypeOrTagT = viennagrid::null_type,
             typename Element8TypeOrTagT = viennagrid::null_type, typename Element9TypeOrTagT = viennagrid::null_type>
    struct mesh_view
    {
      typedef typename mesh_view_from_typelist<
          MeshT,
          typename viennagrid::make_typelist<
            typename element<MeshT, Element0TypeOrTagT>::type,
            typename element<MeshT, Element1TypeOrTagT>::type,
            typename element<MeshT, Element2TypeOrTagT>::type,
            typename element<MeshT, Element3TypeOrTagT>::type,
            typename element<MeshT, Element4TypeOrTagT>::type,
            typename element<MeshT, Element5TypeOrTagT>::type,
            typename element<MeshT, Element6TypeOrTagT>::type,
            typename element<MeshT, Element7TypeOrTagT>::type,
            typename element<MeshT, Element8TypeOrTagT>::type,
            typename element<MeshT, Element9TypeOrTagT>::type
          >::type
      >::type type;
    };

    /** \cond */
    template<typename WrappedConfigT>
    struct mesh_view<viennagrid::mesh<WrappedConfigT>,
                       viennagrid::null_type, viennagrid::null_type, viennagrid::null_type, viennagrid::null_type, viennagrid::null_type,
                       viennagrid::null_type, viennagrid::null_type, viennagrid::null_type, viennagrid::null_type, viennagrid::null_type>
    {
      typedef typename mesh_view_from_typelist< viennagrid::mesh<WrappedConfigT> >::type type;
    };
    /** \endcond */
  }

  namespace detail
  {
    /** @brief For internal use only */
    template<typename container_collection_type>
    class handle_mesh_functor
    {
    public:

      handle_mesh_functor(container_collection_type & collection_) : collection(collection_) {}

      template<typename container_type>
      void operator()( container_type & container )
      {
          typedef typename container_type::value_type value_type;
          detail::handle( viennagrid::get<value_type>(collection), container);
      }


    private:
      container_collection_type & collection;
    };
  }



  namespace detail
  {

    /** @brief For internal use only */
    template<typename ConfigType>
    typename viennagrid::mesh<ConfigType>::element_collection_type &
    element_collection( viennagrid::mesh<ConfigType> & mesh_obj)
    { return mesh_obj.element_collection(); }

    /** @brief For internal use only */
    template<typename ConfigType>
    typename viennagrid::mesh<ConfigType>::element_collection_type const &
    element_collection( viennagrid::mesh<ConfigType> const & mesh_obj)
    { return mesh_obj.element_collection(); }


    /** @brief For internal use only */
    template<typename ConfigType>
    typename viennagrid::mesh<ConfigType>::inserter_type &
    inserter(viennagrid::mesh<ConfigType> & mesh_obj)
    { return mesh_obj.get_inserter(); }

    /** @brief For internal use only */
    template<typename ConfigType>
    typename viennagrid::mesh<ConfigType>::inserter_type const &
    inserter(viennagrid::mesh<ConfigType> const & mesh_obj)
    { return mesh_obj.get_inserter(); }


    /** @brief For internal use only */
    template<typename ConfigType>
    typename viennagrid::mesh<ConfigType>::inserter_type::id_generator_type &
    id_generator(viennagrid::mesh<ConfigType> & mesh_obj)
    { return inserter(mesh_obj).get_id_generator(); }

    /** @brief For internal use only */
    template<typename ConfigType>
    typename viennagrid::mesh<ConfigType>::inserter_type::id_generator_type const &
    id_generator(viennagrid::mesh<ConfigType> const & mesh_obj)
    { return inserter(mesh_obj).get_id_generator(); }

  }


  /** @brief Function for inserting handles to all element from a mesh in a mesh view
    *
    * @tparam MeshT       The mesh or segment type
    * @tparam ViewT       The mesh view type
    * @param  mesh_obj    The input mesh/segment object
    * @param  view_obj    The output view object
    */
  template<typename MeshT, typename ViewT>
  void handle_mesh(MeshT & mesh_obj, ViewT & view_obj)
  {
    detail::handle_mesh_functor< typename result_of::element_collection<MeshT>::type > functor( detail::element_collection(mesh_obj) );
    viennagrid::detail::for_each( detail::element_collection(view_obj), functor);
  }


  /** @brief Function for obtaining the heighest ID for a specific element type/tag in a mesh/segment
    *
    * @tparam ElementTypeOrTag      The element type/tag from which the heighest ID is queried
    * @tparam MeshOrSegmentHandleT  The mesh/segment type
    * @param  mesh_or_segment       The mesh/segment object
    * @return                       The heighest ID for specified element type/tag
    */
  template<typename ElementTypeOrTag, typename MeshOrSegmentHandleT>
  typename viennagrid::result_of::id< typename viennagrid::result_of::element<MeshOrSegmentHandleT, ElementTypeOrTag>::type >::type
  id_upper_bound( MeshOrSegmentHandleT const & mesh_or_segment )
  {
    return detail::id_generator(mesh_or_segment).max_id( viennagrid::detail::tag<ElementTypeOrTag>() );
  }



  /** @brief Function for dereferencing a handle using a mesh/segment object
    *
    * @tparam WrappedConfigT     The wrapped config of the mesh/segment type
    * @tparam HandleT            A handle type
    * @param  mesh_obj           The host mesh/segment object
    * @param  handle             The handle to be dereferenced
    * @return                    A C++ reference to an element which is referenced by handle
    */
  template<typename WrappedMeshConfigT, typename HandleT>
  typename viennagrid::detail::result_of::value_type<HandleT>::type &
  dereference_handle(mesh<WrappedMeshConfigT> & mesh_obj, HandleT const & handle)
  {
    typedef typename viennagrid::detail::result_of::value_type<HandleT>::type value_type;
    return get<value_type>(viennagrid::detail::element_collection(mesh_obj)).dereference_handle( handle );
  }

  /** @brief Function for dereferencing a handle using a mesh/segment object, const version
    *
    * @tparam WrappedConfigT     The wrapped config of the mesh/segment type
    * @tparam HandleT            A handle type
    * @param  mesh_obj           The host mesh/segment object
    * @param  handle             The handle to be dereferenced
    * @return                    A C++ const reference to an element which is referenced by handle
    */
  template<typename WrappedMeshConfigT, typename HandleT>
  typename viennagrid::detail::result_of::value_type<HandleT>::type const &
  dereference_handle(mesh<WrappedMeshConfigT> const & mesh_obj, HandleT const & handle)
  {
    typedef typename viennagrid::detail::result_of::value_type<HandleT>::type value_type;
    return get<value_type>(viennagrid::detail::element_collection(mesh_obj)).dereference_handle( handle );
  }


  /** @brief Function for creating a handle for a given element using a mesh/segment object
    *
    * @tparam MeshOrSegmentHandleT      The host mesh/segment type
    * @tparam ElementTagT           The tag of the element of which a handle is created
    * @tparam WrappedConfigT        The wrapped config of the element of which a handle is created
    * @param  mesh_or_segment     The host mesh/segment object
    * @param  element               The element of which a handle is created
    * @return                       A handle referencing the given element
    */
  template<typename MeshOrSegmentHandleT, typename ElementTagT, typename WrappedConfigT>
  typename result_of::handle<MeshOrSegmentHandleT, viennagrid::element<ElementTagT, WrappedConfigT> >::type
  handle(MeshOrSegmentHandleT & mesh_or_segment, viennagrid::element<ElementTagT, WrappedConfigT> & element)
  { return get< viennagrid::element<ElementTagT, WrappedConfigT> >(detail::element_collection(mesh_or_segment)).handle( element ); }

  /** @brief Function for creating a handle for a given element using a mesh/segment object, const version
    *
    * @tparam MeshOrSegmentHandleT      The host mesh/segment type
    * @tparam ElementTagT           The tag of the element of which a handle is created
    * @tparam WrappedConfigT        The wrapped config of the element of which a handle is created
    * @param  mesh_or_segment     The host mesh/segment object
    * @param  element               The element of which a handle is created
    * @return                       A const handle referencing the given element
    */
  template<typename MeshOrSegmentHandleT, typename ElementTagT, typename WrappedConfigT>
  typename result_of::const_handle<MeshOrSegmentHandleT, viennagrid::element<ElementTagT, WrappedConfigT> >::type
  handle(MeshOrSegmentHandleT const & mesh_or_segment, viennagrid::element<ElementTagT, WrappedConfigT> const & element)
  { return get< viennagrid::element<ElementTagT, WrappedConfigT> >(detail::element_collection(mesh_or_segment)).handle( element ); }






  /** @brief Function for querying a local vertex on a boundary element within a host element
    *
    * @tparam ElementTagT               The element tag of the host element type
    * @tparam WrappedConfigT            The wrapped config of the host element type
    * @tparam BoundaryHandleT           The handle type of the boundary element
    * @param  host_element              The host element object
    * @param  boundary_element_handle   The boundary element handle
    * @param  index                     The index defining which vertex within the boundary element is queried
    * @return                           A handle referencing the given element
    */
  template<typename ElementTagT, typename WrappedConfigT, typename BoundaryHandleT>
  typename viennagrid::result_of::vertex_handle< viennagrid::element<ElementTagT, WrappedConfigT> >::type
  local_vertex(
      viennagrid::element<ElementTagT, WrappedConfigT> & host_element,
      BoundaryHandleT const & boundary_element_handle,
      std::size_t index)
  {
    typedef typename viennagrid::detail::result_of::value_type<BoundaryHandleT>::type element_type_2;
    element_type_2 & bnd_kcell = viennagrid::dereference_handle(host_element, boundary_element_handle);
    return viennagrid::vertices(bnd_kcell).handle_at(host_element.global_to_local_orientation(boundary_element_handle, index));
  }

  /** @brief Function for querying a local vertex on a boundary element within a host element, const version
    *
    * @tparam ElementTagT               The element tag of the host element type
    * @tparam WrappedConfigT            The wrapped config of the host element type
    * @tparam BoundaryHandleT           The handle type of the boundary element
    * @param  host_element              The host element object
    * @param  boundary_element_handle   The boundary element handle
    * @param  index                     The index defining which vertex within the boundary element is queried
    * @return                           A const handle referencing the given element
    */
  template<typename ElementTagT, typename WrappedConfigT, typename BoundaryHandleT>
  typename viennagrid::result_of::const_vertex_handle< viennagrid::element<ElementTagT, WrappedConfigT> >::type
  local_vertex(
      viennagrid::element<ElementTagT, WrappedConfigT> const & host_element,
      BoundaryHandleT const & boundary_element_handle,
      std::size_t index)
  {
    typedef typename viennagrid::detail::result_of::value_type<BoundaryHandleT>::type element_type_2;
    element_type_2 const & bnd_kcell = viennagrid::dereference_handle(host_element, boundary_element_handle);
    return viennagrid::vertices(bnd_kcell).handle_at(host_element.global_to_local_orientation(boundary_element_handle, index));
  }


  namespace detail
  {
    /** @brief For internal use only */
    template<typename ContainerT>
    class dereference_handle_comparator
    {
    public:

      dereference_handle_comparator(ContainerT const & container_) : container(container_) {}

      template<typename HandleT>
      bool operator() ( HandleT h1, HandleT h2 )
      {
          return &viennagrid::dereference_handle( container, h1 ) < &viennagrid::dereference_handle( container, h2 );
      }

    private:
      ContainerT const & container;
    };
  }

}



namespace viennagrid
{

  namespace result_of
  {
    /** @brief Metafunction for querying if an element is present within a mesh, mesh view or segment
     *
     * @tparam MeshViewOrSegmentHandleT       The host mesh/mesh view/segment type
     * @tparam ElementTypeOrTagT          The requested element type/tag
     */
    template<typename MeshViewOrSegmentHandleT, typename ElementTypeOrTagT>
    struct is_element_present;

    /** \cond */
    template<typename WrappedConfigType, typename element_type_or_tag>
    struct is_element_present< viennagrid::mesh<WrappedConfigType>, element_type_or_tag >
    {
      typedef typename viennagrid::result_of::element_tag<element_type_or_tag>::type tag;
      static const bool value = config::result_of::is_element_present<WrappedConfigType, tag>::value;
    };

    template<typename WrappedConfigType, typename element_type_or_tag>
    struct is_element_present< const viennagrid::mesh<WrappedConfigType>, element_type_or_tag >
    {
      static const bool value = is_element_present<viennagrid::mesh<WrappedConfigType>, element_type_or_tag>::value;
    };




    /** @brief For internal use only */
    template<typename typelist, typename element_tag>
    struct is_element_present_helper;

    template<typename element_tag>
    struct is_element_present_helper<null_type, element_tag>
    {
      static const bool value = false;
    };

    template<typename element_type, typename tail, typename element_tag>
    struct is_element_present_helper< typelist<element_type, tail>, element_tag>
    {
      static const bool value =
        viennagrid::detail::EQUAL<
          typename element_type::tag,
          element_tag
        >::value ||
        is_element_present_helper<tail, element_tag>::value;
    };


    template <typename WrappedMeshConfigType, typename ElementTypeList, typename ContainerConfig, typename element_type_or_tag>
    struct is_element_present< viennagrid::mesh< viennagrid::detail::decorated_mesh_view_config<WrappedMeshConfigType, ElementTypeList, ContainerConfig> >, element_type_or_tag >
    {
      typedef typename viennagrid::result_of::element_tag<element_type_or_tag>::type tag;
      static const bool value = is_element_present_helper<ElementTypeList, tag>::value;
    };

    template <typename WrappedMeshConfigType, typename ElementTypeList, typename ContainerConfig, typename element_type_or_tag>
    struct is_element_present< const viennagrid::mesh< viennagrid::detail::decorated_mesh_view_config<WrappedMeshConfigType, ElementTypeList, ContainerConfig> >, element_type_or_tag >
    {
      static const bool value = is_element_present<viennagrid::mesh< viennagrid::detail::decorated_mesh_view_config<WrappedMeshConfigType, ElementTypeList, ContainerConfig> >, element_type_or_tag>::value;
    };
    /** \endcond */




    /** @brief Metafunction for the type retrieval of an element
     *
     * @tparam MeshSegmentHandleType       The host type, can be a collection, an element, a mesh, a segmentation or a segment
     * @tparam element_type_or_tag         The requested element tag, element type is also supported, in this case the requested element type is returned
     */
    template<typename MeshSegmentHandleType, typename element_type_or_tag>
    struct element
    {
      typedef typename detail::STATIC_ASSERT< is_element_present<MeshSegmentHandleType, element_type_or_tag>::value >::type ERROR_ELEMENT_IS_NOT_PRESENT_IN_MESH;
      typedef typename element< typename element_collection< MeshSegmentHandleType >::type, element_type_or_tag >::type type;
    };

    /** @brief Metafunction for the type retrieval of an element handle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     * @tparam ElementTypeOrTagT  The requested element tag, element type is also supported, in this case the requested element type is returned
     */
    template<typename MeshSegmentHandleType, typename element_type_or_tag>
    struct handle
    {
      typedef typename detail::STATIC_ASSERT< is_element_present<MeshSegmentHandleType, element_type_or_tag>::value >::type ERROR_ELEMENT_IS_NOT_PRESENT_IN_MESH;
      typedef typename handle< typename element_collection< MeshSegmentHandleType >::type, element_type_or_tag >::type type;
    };

    /** @brief Metafunction for the type retrieval of a const element handle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     * @tparam ElementTypeOrTagT  The requested element tag, element type is also supported, in this case the requested element type is returned
     */
    template<typename MeshSegmentHandleType, typename element_type_or_tag>
    struct const_handle
    {
      typedef typename detail::STATIC_ASSERT< is_element_present<MeshSegmentHandleType, element_type_or_tag>::value >::type ERROR_ELEMENT_IS_NOT_PRESENT_IN_MESH;
      typedef typename const_handle< typename element_collection< MeshSegmentHandleType >::type, element_type_or_tag >::type type;
    };

    /** @brief Metafunction for the type retrieval of an element range
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, an element, a mesh, a segmentation or a segment
     * @tparam ElementTypeOrTagT  The requested element tag or element type
     */
    template<typename MeshSegmentHandleType, typename element_type_or_tag>
    struct element_range
    {
      typedef typename detail::STATIC_ASSERT< is_element_present<MeshSegmentHandleType, element_type_or_tag>::value >::type ERROR_ELEMENT_IS_NOT_PRESENT_IN_MESH;
      typedef typename element_range< typename element_collection< MeshSegmentHandleType >::type, element_type_or_tag >::type type;
    };

    /** @brief Metafunction for the type retrieval of a const element range
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, an element, a mesh, a segmentation or a segment
     * @tparam ElementTypeOrTagT  The requested element tag or element type
     */
    template<typename MeshSegmentHandleType, typename element_type_or_tag>
    struct const_element_range
    {
      typedef typename detail::STATIC_ASSERT< is_element_present<MeshSegmentHandleType, element_type_or_tag>::value >::type ERROR_ELEMENT_IS_NOT_PRESENT_IN_MESH;
      typedef typename const_element_range< typename element_collection< MeshSegmentHandleType >::type, element_type_or_tag >::type type;
    };


    /** \cond */
    template<typename typemap>
    struct topologic_cell_dimension_impl;

    template<>
    struct topologic_cell_dimension_impl<viennagrid::null_type>
    {
      static const int value = -1;
    };

    template<typename element_type, typename element_container_type, typename tail>
    struct topologic_cell_dimension_impl< viennagrid::typelist< viennagrid::static_pair<element_type, element_container_type>, tail > >
    {
      static const int tail_cell_dimension = topologic_cell_dimension_impl<tail>::value;
      static const int current_element_dimension = topologic_dimension<element_type>::value;

      static const int value = (tail_cell_dimension > current_element_dimension) ? tail_cell_dimension : current_element_dimension;
    };
    /** \endcond */

    /** @brief Metafunction for returning the topologic dimension of the cell in a mesh or segment
      *
      * @tparam something     A mesh or segment type
      */
    template<typename something>
    struct topologic_cell_dimension
    {
      static const int value = topologic_cell_dimension_impl<
              typename container_collection_typemap<
                  typename element_collection<something>::type
              >::type
          >::value;
    };





    /** \cond */
    template<typename typemap, int topologic_dimension>
    struct elements_of_topologic_dim_impl;

    template<int topologic_dimension>
    struct elements_of_topologic_dim_impl< viennagrid::null_type, topologic_dimension >
    {
      typedef viennagrid::null_type type;
    };

    template<typename element_type, typename element_container_type, typename tail, int topologic_dimension>
    struct elements_of_topologic_dim_impl< viennagrid::typelist< viennagrid::static_pair<element_type, element_container_type>, tail >, topologic_dimension >
    {
      typedef typename elements_of_topologic_dim_impl<tail, topologic_dimension>::type tail_typelist;

      typedef typename viennagrid::detail::IF<
          viennagrid::result_of::topologic_dimension<element_type>::value == topologic_dimension,
          typename viennagrid::detail::result_of::push_back<tail_typelist, element_type>::type,
          tail_typelist
      >::type type;
    };
    /** \endcond */

    /** @brief Metafunction for obtaining an element typelist of all element with a specific topologic dimension of something
     *
     * @tparam SomethingT           The host type, can be a collection, a mesh, a segmentation or a segment
     * @tparam TopologicDimensionV  The topologic dimension
     */
    template<typename something, int topologic_dimension>
    struct elements_of_topologic_dim
    {
      typedef typename elements_of_topologic_dim_impl<
          typename container_collection_typemap<
              typename element_collection<something>::type
          >::type,
          topologic_dimension>::type type;
    };



    /** @brief Metafunction for obtaining an element typelist of all cell types of something
     *
     * @tparam SomethingT           The host type, can be a collection, a mesh, a segmentation or a segment
     */
    template<typename something>
    struct cells
    {
      typedef typename elements_of_topologic_dim<
          something,
          topologic_cell_dimension<something>::value
      >::type type;
    };


    /** @brief Metafunction for obtaining the cell type of something. Will fail if there is more than one cell type
     *
     * @tparam SomethingT           The host type, can be a collection, a mesh, a segmentation or a segment
     */
    template<typename something>
    struct cell
    {
      typedef typename cells<something>::type all_cell_types;
      typedef typename viennagrid::detail::STATIC_ASSERT< viennagrid::detail::result_of::size<all_cell_types>::value == 1 >::type static_assert_typedef;

      typedef typename viennagrid::detail::result_of::at<all_cell_types,0>::type type;
    };

    /** @brief Metafunction for obtaining the cell tag of something. Will fail if there is more than one cell type
     *
     * @tparam SomethingT           The host type, can be a collection, a mesh, a segmentation or a segment
     */
    template<typename something>
    struct cell_tag
    {
      typedef typename element_tag< typename cell<something>::type >::type type;
    };
  }


  namespace detail
  {
    /** @brief For internal use only */
    template<typename MeshSegmentHandleT, typename FunctorT>
    struct for_each_element_functor
    {
      for_each_element_functor( MeshSegmentHandleT & d, FunctorT f ) : f_(f), mesh_(d) {}

      template<typename element_type>
      void operator() ( viennagrid::detail::tag<element_type> )
      {
        typedef typename viennagrid::result_of::element_range<MeshSegmentHandleT, element_type>::type element_range_type;
        typedef typename viennagrid::result_of::iterator<element_range_type>::type element_range_iterator;

        element_range_type range(mesh_);
        for (element_range_iterator it = range.begin(); it != range.end(); ++it)
          f_(*it);
      }

      template<typename element_type>
      void operator() ( viennagrid::detail::tag<element_type> ) const
      {
        typedef typename viennagrid::result_of::const_element_range<MeshSegmentHandleT, element_type>::type element_range_type;
        typedef typename viennagrid::result_of::iterator<element_range_type>::type element_range_iterator;

        element_range_type range(mesh_);
        for (element_range_iterator it = range.begin(); it != range.end(); ++it)
          f_(*it);
      }

      FunctorT f_;
      MeshSegmentHandleT & mesh_;
    };
  }


  /** @brief Function which executes functor for each element with specific topologic dimension
    *
    * @tparam TopologicDimensionV     Topologic dimension of the elements on which the functor is executed
    * @tparam MeshSegmentHandleT      Host mesh/segment type
    * @tparam FunctorT                Functor type, needs to provide void operator(ElementType &/const &) for each element type with topologic dimension equal to TopologicDimensionV
    * @param  mesh_or_segment         Host mesh/segment object
    * @param  f                       Functor object
    */
  template<int TopologicDimensionV, typename MeshSegmentHandleT, typename FunctorT>
  void for_each( MeshSegmentHandleT & mesh_or_segment, FunctorT f )
  {
    detail::for_each_element_functor<MeshSegmentHandleT, FunctorT> for_each_functor(mesh_or_segment, f);
    typedef typename viennagrid::result_of::elements_of_topologic_dim<MeshSegmentHandleT, TopologicDimensionV>::type ElementTypelist;

    viennagrid::detail::for_each<ElementTypelist>( for_each_functor );
  }

  /** @brief Function which executes functor for each element with specific topologic dimension, const version
    *
    * @tparam TopologicDimensionV     Topologic dimension of the elements on which the functor is executed
    * @tparam MeshSegmentHandleT      Host mesh/segment type
    * @tparam FunctorT                Functor type, needs to provide void operator(ElementType &/const &) for each element type with topologic dimension equal to TopologicDimensionV
    * @param  mesh_or_segment         Host mesh/segment object
    * @param  f                       Functor object
    */
  template<int TopologicDimensionV, typename MeshSegmentHandleT, typename FunctorT>
  void for_each( MeshSegmentHandleT const & mesh_or_segment, FunctorT f )
  {
    detail::for_each_element_functor<const MeshSegmentHandleT, FunctorT> for_each_functor(mesh_or_segment, f);
    typedef typename viennagrid::result_of::elements_of_topologic_dim<MeshSegmentHandleT, TopologicDimensionV>::type ElementTypelist;

    viennagrid::detail::for_each<ElementTypelist>( for_each_functor );
  }


  /** @brief Function which executes functor for each element (of all topological dimensions) of the mesh or segment. Non-const version.
    *
    * @tparam MeshSegmentHandleT      Host mesh/segment type
    * @tparam FunctorT                Functor type, needs to provide void operator(ElementType &/const &) for each element type with topologic dimension equal to TopologicDimensionV
    * @param  mesh_or_segment         Host mesh/segment object
    * @param  f                       Functor object
    */
  template<typename MeshSegmentHandleT, typename FunctorT>
  void for_each( MeshSegmentHandleT & mesh_or_segment, FunctorT f )
  {
    detail::for_each_element_functor<MeshSegmentHandleT, FunctorT> for_each_functor(mesh_or_segment, f);
    typedef typename viennagrid::result_of::element_typelist<MeshSegmentHandleT>::type ElementTypelist;

    viennagrid::detail::for_each<ElementTypelist>( for_each_functor );
  }

  /** @brief Function which executes functor for each element (of all topological dimensions) of the mesh or segment. Const version.
    *
    * @tparam MeshSegmentHandleT      Host mesh/segment type
    * @tparam FunctorT                Functor type, needs to provide void operator(ElementType &/const &) for each element type with topologic dimension equal to TopologicDimensionV
    * @param  mesh_or_segment         Host mesh/segment object
    * @param  f                       Functor object
    */
  template<typename MeshSegmentHandleT, typename FunctorT>
  void for_each( MeshSegmentHandleT const & mesh_or_segment, FunctorT f )
  {
    detail::for_each_element_functor<const MeshSegmentHandleT, FunctorT> for_each_functor(mesh_or_segment, f);
    typedef typename viennagrid::result_of::element_typelist<MeshSegmentHandleT>::type ElementTypelist;

    viennagrid::detail::for_each<ElementTypelist>( for_each_functor );
  }







  // doxygen docu in forwards.hpp
  template<typename ElementTypeOrTagT, typename WrappedConfigType>
  typename result_of::element_range<viennagrid::mesh<WrappedConfigType>, ElementTypeOrTagT>::type
  elements(viennagrid::mesh<WrappedConfigType> & mesh_obj)
  { return elements<ElementTypeOrTagT>( detail::element_collection(mesh_obj) ); }

  // doxygen docu in forwards.hpp
  template<typename ElementTypeOrTagT, typename WrappedConfigType>
  typename result_of::const_element_range<viennagrid::mesh<WrappedConfigType>, ElementTypeOrTagT>::type
  elements(viennagrid::mesh<WrappedConfigType> const & mesh_obj)
  { return elements<ElementTypeOrTagT>( detail::element_collection(mesh_obj) ); }














  /** @brief Function which finds an element based on an element. The runtime of this function depends on the container but can likely be linear in the number of elements of the requested type in the mesh.
    *
    * @tparam MeshSegmentHandleT      Host mesh/segment type
    * @tparam IDT                     ID type of the object to be found
    * @param  mesh_or_segment         Host mesh/segment object
    * @param  element                 The mesh element (cell, vertex, etc.) to be found
    * @return                         An iterator pointing to the found element. If no element was found it points to viennagrid::elements<ElementType>(mesh_or_segment).end()
    */
  template<typename MeshSegmentHandleT, typename ElementTagT, typename WrappedConfigT>
  typename viennagrid::result_of::iterator< typename viennagrid::result_of::element_range<MeshSegmentHandleT, ElementTagT>::type >::type
  find(MeshSegmentHandleT & mesh_or_segment, element<ElementTagT, WrappedConfigT> const & element )
  {
    return viennagrid::elements<ElementTagT>(mesh_or_segment).find(element);
  }

  /** @brief Function which finds an element based on an element, const version. The runtime of this function depends on the container but can likely be linear in the number of elements of the requested type in the mesh.
    *
    * @tparam MeshSegmentHandleT      Host mesh/segment type
    * @tparam IDT                     ID type of the object to be found
    * @param  mesh_or_segment         Host mesh/segment object
    * @param  element                 The mesh element (cell, vertex, etc.) to be found
    * @return                         An iterator pointing to the found element. If no element was found it points to viennagrid::elements<ElementType>(mesh_or_segment).end()
    */
  template<typename MeshSegmentHandleT, typename ElementTagT, typename WrappedConfigT>
  typename viennagrid::result_of::const_iterator< typename viennagrid::result_of::element_range<MeshSegmentHandleT, ElementTagT>::type >::type
  find(MeshSegmentHandleT const & mesh_or_segment, element<ElementTagT, WrappedConfigT> const & element )
  {
    return viennagrid::elements<ElementTagT>(mesh_or_segment).find(element);
  }




  /** @brief Function which finds an element based on an ID. The runtime of this function depends on the container but can likely be linear in the number of elements of the requested type in the mesh.
    *
    * @tparam MeshSegmentHandleT          Host mesh/segment type
    * @tparam IDT                     ID type of the object to be found
    * @param  mesh_or_segment       Host mesh/segment object
    * @param  id                      id of the object to be found
    * @return                         An iterator pointing to the found element. If no element was found it points to viennagrid::elements<ElementType>(mesh_or_segment).end()
    */
  template<typename MeshSegmentHandleT, typename IDT>
  typename viennagrid::result_of::iterator< typename viennagrid::result_of::element_range<MeshSegmentHandleT, typename IDT::value_type::tag>::type >::type
  find(MeshSegmentHandleT & mesh_or_segment, IDT id )
  {
    typedef typename IDT::value_type     element_type;
    typedef typename element_type::tag   element_tag;

    return viennagrid::elements<element_tag>(mesh_or_segment).find(id);
  }

  /** @brief Function which finds an element based on an ID, const version. The runtime of this function depends on the container but can likely be linear in the number of elements of the requested type in the mesh.
    *
    * @tparam MeshSegmentHandleT          Host mesh/segment type
    * @tparam IDT                     ID type of the object to be found
    * @param  mesh_or_segment       Host mesh/segment object
    * @param  id                      id of the object to be found
    * @return                         A const iterator pointing to the found element. If no element was found it points to viennagrid::elements<ElementType>(mesh_or_segment).end()
    */
  template<typename MeshSegmentHandleT, typename IDT>
  typename viennagrid::result_of::const_iterator< typename viennagrid::result_of::element_range<MeshSegmentHandleT, typename IDT::value_type::tag>::type >::type
  find(MeshSegmentHandleT const & mesh_or_segment, IDT id )
  {
    typedef typename IDT::value_type      element_type;
    typedef typename element_type::tag    element_tag;

    return viennagrid::elements<element_tag>(mesh_or_segment).find(id);
  }

  /** @brief Function which finds an element based on a handle. The runtime of this function is linear in the number of elements of the requested type in the mesh.
    *
    * @tparam MeshSegmentHandleT         Host mesh/segment type
    * @tparam HandleT                    The handle type of the object to be found
    * @param  mesh_or_segment            Host mesh/segment object
    * @param  handle                     Identification handle of the object to be found
    * @return                            An iterator pointing to the found element. If no element was found it points to viennagrid::elements<ElementType>(mesh_or_segment).end()
    */
  template<typename MeshSegmentHandleT, typename HandleT>
  typename viennagrid::result_of::iterator< typename viennagrid::result_of::element_range<MeshSegmentHandleT, typename detail::result_of::value_type<HandleT>::type >::type >::type
  find_by_handle(MeshSegmentHandleT & mesh_or_segment, HandleT handle)
  {
    typedef typename detail::result_of::value_type<HandleT>::type    element_type;
    typedef typename element_type::tag                                        element_tag;
    typedef typename viennagrid::result_of::element_range<MeshSegmentHandleT, element_tag>::type   RangeType;
    typedef typename viennagrid::result_of::iterator<RangeType>::type                              RangeIterator;

    RangeType range = viennagrid::elements<element_tag>(mesh_or_segment);
    for (RangeIterator it = range.begin(); it != range.end(); ++it)
    {
        if ( it.handle() == handle )
            return it;
    }

    return range.end();
  }

  /** @brief Function which finds an element based on a handle, const version. The runtime of this function is linear in the number of elements of the requested type in the mesh.
    *
    * @tparam MeshSegmentHandleT         Host mesh/segment type
    * @tparam HandleT                    The handle type of the object to be found
    * @param  mesh_or_segment            Host mesh/segment object
    * @param  handle                     Identification handle of the object to be found
    * @return                            A const iterator pointing to the found element. If no element was found it points to viennagrid::elements<ElementType>(mesh_or_segment).end()
    */
  template<typename MeshSegmentHandleT, typename HandleT>
  typename viennagrid::result_of::const_iterator< typename viennagrid::result_of::const_element_range<MeshSegmentHandleT, typename detail::result_of::value_type<HandleT>::type >::type  >::type
  find_by_handle(MeshSegmentHandleT const & mesh_or_segment, HandleT handle)
  {
    typedef typename detail::result_of::value_type<HandleT>::type          element_type;
    typedef typename element_type::tag                                              element_tag;
    typedef typename viennagrid::result_of::const_element_range<MeshSegmentHandleT, element_tag>::type   RangeType;
    typedef typename viennagrid::result_of::const_iterator<RangeType>::type                              RangeIterator;

    RangeType range = viennagrid::elements<element_tag>(mesh_or_segment);
    for (RangeIterator it = range.begin(); it != range.end(); ++it)
    {
        if ( it.handle() == handle )
            return it;
    }

    return range.end();
  }




  /** @brief Function for setting a vertex within an element. Don't use this unless you know what you are doing!
    *
    * @tparam ElementTag          Element tag of the host element type
    * @tparam WrappedConfigType   Wrapped config of the host element type
    * @tparam VertexHandleType    Vertex handle type
    * @param  element             The host element object where the vertex is to be set
    * @param  vertex_handle       A vertex handle which is to be used in the host element
    * @param  pos                 The position of the vertex to be set within the host element
    */
  template<typename ElementTag, typename WrappedConfigType, typename VertexHandleType>
  void set_vertex(
          viennagrid::element<ElementTag, WrappedConfigType> & element,
          VertexHandleType vertex_handle,
          unsigned int pos)
  {
    element.container( viennagrid::dimension_tag<0>() ).set_handle( vertex_handle, pos );
  }


  namespace detail
  {
    /** @brief For internal use only */
    template<bool generate_id, bool call_callback, typename mesh_type, typename ElementTag, typename WrappedConfigType>
    std::pair<
                typename viennagrid::result_of::container_of<
                    typename viennagrid::result_of::element_collection<mesh_type>::type,
                    viennagrid::element<ElementTag, WrappedConfigType>
                >::type::handle_type,
                bool
            >
    push_element( mesh_type & mesh_obj, viennagrid::element<ElementTag, WrappedConfigType> const & element)
    {
      return detail::inserter(mesh_obj).template insert<generate_id, call_callback>(element);
    }
  }


  namespace result_of
  {

    /** \cond */
    template<typename ConfigType>
    struct point< viennagrid::mesh<ConfigType> >
    {
      typedef typename viennagrid::result_of::vertex< viennagrid::mesh<ConfigType> >::type::appendix_type type;
    };

    template<typename ConfigType>
    struct point< const viennagrid::mesh<ConfigType> >
    {
      typedef typename viennagrid::result_of::vertex< viennagrid::mesh<ConfigType> >::type::appendix_type type;
    };

    template<typename ElementTag, typename WrappedConfigType>
    struct point< viennagrid::element<ElementTag, WrappedConfigType> >
    {
      typedef typename viennagrid::result_of::vertex< viennagrid::element<ElementTag, WrappedConfigType> >::type::appendix_type type;
    };

    template<typename ElementTag, typename WrappedConfigType>
    struct point< const viennagrid::element<ElementTag, WrappedConfigType> >
    {
      typedef typename viennagrid::result_of::vertex< viennagrid::element<ElementTag, WrappedConfigType> >::type::appendix_type type;
    };
    /** \endcond */
  }


  /** @brief Function for obtaining the point from a vertex
    *
    * @tparam WrappedConfigT      Wrapped config of the host mesh type
    * @param  vertex              The vertex of which the point is obtained
    * @return                     A reference to the point
    */
  template<typename WrappedConfigT>
  typename result_of::point< viennagrid::mesh<WrappedConfigT> >::type &
  point(viennagrid::mesh<WrappedConfigT> & /*mesh*/, typename result_of::vertex< viennagrid::mesh<WrappedConfigT> >::type & vertex)
  { return vertex.appendix(); }

  /** @brief Function for obtaining the point from a vertex, const version
    *
    * @tparam WrappedConfigT      Wrapped config of the host mesh type
    * @param  vertex              The vertex of which the point is obtained
    * @return                     A const reference to the point
    */
  template<typename WrappedConfigT>
  typename result_of::point< viennagrid::mesh<WrappedConfigT> >::type const &
  point(mesh<WrappedConfigT> const & /*mesh*/, typename result_of::vertex< viennagrid::mesh<WrappedConfigT> >::type const & vertex)
  { return vertex.appendix(); }


  /** @brief Function for obtaining the point from a vertex
    *
    * @tparam WrappedConfigT      Wrapped config of the host mesh type
    * @param  mesh_obj            The host mesh object
    * @param  vertex_handle       A handle to the vertex of which the point is obtained
    * @return                     A reference to the point
    */
  template<typename WrappedConfigT>
  typename result_of::point< viennagrid::mesh<WrappedConfigT> >::type &
  point(mesh<WrappedConfigT> & mesh_obj, typename result_of::vertex_handle< viennagrid::mesh<WrappedConfigT> >::type vertex_handle)
  { return dereference_handle(mesh_obj, vertex_handle).appendix(); }

  /** @brief Function for obtaining the point from a vertex, const version
    *
    * @tparam WrappedConfigT      Wrapped config of the host mesh type
    * @param  mesh_obj            The host mesh object
    * @param  vertex_handle       A handle to the vertex of which the point is obtained
    * @return                     A const reference to the point
    */
  template<typename WrappedConfigT>
  typename result_of::point< viennagrid::mesh<WrappedConfigT> >::type const &
  point(mesh<WrappedConfigT> const & mesh_obj, typename result_of::const_vertex_handle< viennagrid::mesh<WrappedConfigT> >::type vertex_handle)
  { return dereference_handle(mesh_obj, vertex_handle).appendix(); }


  /** @brief Function for obtaining the point from a vertex, no mesh needed
    *
    * @tparam VertexT             The vertex type
    * @param  vertex              The vertex of which the point is obtained
    * @return                     A reference to the point
    */
  template<typename VertexT>
  typename result_of::point< VertexT >::type &
  point(VertexT & vertex)
  { return default_point_accessor(vertex)(vertex); }

  /** @brief Function for obtaining the point from a vertex, no mesh needed, const version
    *
    * @tparam VertexT             The vertex type
    * @param  vertex              The vertex of which the point is obtained
    * @return                     A const reference to the point
    */
  template<typename VertexT>
  typename result_of::point< VertexT >::type const &
  point(VertexT const & vertex)
  { return default_point_accessor(vertex)(vertex); }



  namespace detail
  {

    /** @brief For internal use only */
    template<typename MeshT, typename SourceElementT, typename DestinationElementT>
    struct copy_element_setters
    {
      copy_element_setters(MeshT & mesh_obj, SourceElementT const & source_element, DestinationElementT & destination_element) :
        mesh_obj_(mesh_obj), source_element_(source_element), destination_element_(destination_element) {}

      template<typename BoundaryElementT>
      void operator() ( viennagrid::detail::tag<BoundaryElementT> )
      {
        typedef typename viennagrid::result_of::const_element_range<SourceElementT, BoundaryElementT>::type     SourceBoundaryElementRangeType;
        typedef typename viennagrid::result_of::iterator<SourceBoundaryElementRangeType>::type                  SourceBoundaryElementRangeIterator;

        typedef typename viennagrid::result_of::element_range<SourceElementT, BoundaryElementT>::type           DestinationBoundaryElementRangeType;
        typedef typename viennagrid::result_of::iterator<DestinationBoundaryElementRangeType>::type             DestinationBoundaryElementRangeIterator;

        SourceBoundaryElementRangeType      source_boundary_elements(source_element_);
        DestinationBoundaryElementRangeType destination_boundary_elements(destination_element_);

        SourceBoundaryElementRangeIterator      sit = source_boundary_elements.begin();
        DestinationBoundaryElementRangeIterator dit = destination_boundary_elements.begin();

        for (; sit != source_boundary_elements.end(); ++sit, ++dit)
        {
          dit.handle() = viennagrid::find( mesh_obj_, sit->id() ).handle();
        }
      }

      MeshT & mesh_obj_;
      SourceElementT const & source_element_;
      DestinationElementT & destination_element_;
    };


    /** @brief For internal use only */
    template<typename ElementTypelistT>
    struct fix_handle_helper;

    template<>
    struct fix_handle_helper< null_type >
    {
      template<typename SourceWrappedConfigT, typename DestinationWrappedConfigT>
      static void fix_handles( viennagrid::mesh<SourceWrappedConfigT> const &, viennagrid::mesh<DestinationWrappedConfigT> & )
      {}
    };


    template<typename SourceElementT, typename TailT>
    struct fix_handle_helper< typelist<SourceElementT, TailT> >
    {
      template<typename SourceWrappedConfigT, typename DestinationWrappedConfigT>
      static void fix_handles( viennagrid::mesh<SourceWrappedConfigT> const & source_mesh_obj, viennagrid::mesh<DestinationWrappedConfigT> & destination_mesh_obj )
      {
        typedef typename viennagrid::result_of::element_tag<SourceElementT>::type ElementTag;

        typedef viennagrid::mesh<SourceWrappedConfigT>          SourceMeshType;
        typedef viennagrid::mesh<DestinationWrappedConfigT>     DestinationMeshType;

        typedef typename viennagrid::result_of::const_element_range<SourceMeshType, SourceElementT>::type     SourceElementRangeType;
        typedef typename viennagrid::result_of::iterator<SourceElementRangeType>::type                          SourceElementRangeIterator;

        typedef typename viennagrid::result_of::element_range<DestinationMeshType, SourceElementT>::type      DestinationElementRangeType;
        typedef typename viennagrid::result_of::iterator<DestinationElementRangeType>::type                     DestinationElementRangeIterator;


        typedef typename viennagrid::result_of::element<SourceMeshType, ElementTag>::type SourceElementType;
        typedef typename viennagrid::result_of::element<DestinationMeshType, ElementTag>::type DestinationElementType;
        //typedef typename viennagrid::result_of::handle<DestinationMeshType, ElementTag>::type DestinationElementHandleType;

        SourceElementRangeType           source_elements(source_mesh_obj);
        DestinationElementRangeType destination_elements(destination_mesh_obj);

        DestinationElementRangeIterator dit = destination_elements.begin();
        for (SourceElementRangeIterator sit = source_elements.begin(); sit != source_elements.end(); ++sit, ++dit)
        {
          SourceElementType const & source_element = *sit;
          DestinationElementType & destination_element = *dit;

          if (source_element.id() != destination_element.id())
          {
            std::cout << "ERROR in fix_handles: destination element id != source element id" << std::endl;
            continue;
          }
  //           DestinationElementHandleType handle = viennagrid::push_element<false, false>(destination_mesh_obj, destination_element).first;

          typedef typename viennagrid::result_of::boundary_element_typelist<SourceElementT>::type         BoundaryElementTypelist;
          typedef typename viennagrid::result_of::element_typelist<DestinationMeshType>::type          DestinationElementTypelist;

          typedef typename viennagrid::detail::result_of::intersection<
                    BoundaryElementTypelist,
                    DestinationElementTypelist
                >::type ElementTypelist;

          detail::copy_element_setters<DestinationMeshType, SourceElementT, DestinationElementType> setter( destination_mesh_obj, source_element, destination_element );
          viennagrid::detail::for_each<ElementTypelist>(setter);
        }

        fix_handle_helper<TailT>::fix_handles( source_mesh_obj, destination_mesh_obj );
      }
    };

    /** @brief For internal use only */
    template<typename SourceWrappedConfigT, typename DestinationWrappedConfigT>
    void fix_handles( viennagrid::mesh<SourceWrappedConfigT> const & source_mesh_obj, viennagrid::mesh<DestinationWrappedConfigT> & destination_mesh )
    {
      typedef viennagrid::mesh<SourceWrappedConfigT>          SourceMeshType;
      typedef viennagrid::mesh<DestinationWrappedConfigT>     DestinationMeshType;

      typedef typename viennagrid::result_of::element_typelist<SourceMeshType>::type      SourceTypelist;
      typedef typename viennagrid::result_of::element_typelist<DestinationMeshType>::type DestinationTypelist;

      typedef typename viennagrid::detail::result_of::intersection<
                SourceTypelist,
                DestinationTypelist
            >::type ElementTypelist;

      fix_handle_helper<ElementTypelist>::fix_handles( source_mesh_obj, destination_mesh );
    }

  } //namespace detail
}

#endif
