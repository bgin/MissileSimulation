#ifndef VIENNAGRID_CONFIG_TOPOLOGY_CONFIG_HPP
#define VIENNAGRID_CONFIG_TOPOLOGY_CONFIG_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include "viennagrid/accessor.hpp"

#include "viennagrid/config/config.hpp"
#include "viennagrid/config/id_generator_config.hpp"


#include "viennagrid/topology/simplex.hpp"
#include "viennagrid/storage/hidden_key_map.hpp"
#include "viennagrid/element/element_key.hpp"
#include "viennagrid/config/element_config.hpp"

/** @file viennagrid/config/mesh_config.hpp
    @brief Provides meta functions for mesh configuration
*/

namespace viennagrid
{
  namespace config
  {
    namespace result_of
    {
      //
      // Meta Functions for creating a default config
      //

      /** @brief Defines the default storage layout for elements: full handling tag is default except for vertex, which don't have orientation. */
      template<typename ElementTagT, typename boundary_cell_tag>
      struct storage_layout_config
      {
        typedef typename viennagrid::detail::result_of::insert<
            typename storage_layout_config<ElementTagT, typename boundary_cell_tag::facet_tag>::type,
            viennagrid::static_pair<
                boundary_cell_tag,
                viennagrid::full_handling_tag
            >
        >::type type;
      };

      template<typename ElementTagT>
      struct storage_layout_config<ElementTagT, viennagrid::vertex_tag>
      {
        typedef typename viennagrid::make_typemap<
            viennagrid::vertex_tag,
            viennagrid::no_orientation_handling_tag
        >::type type;
      };

      template<typename ElementTagT>
      struct storage_layout_config<ElementTagT, viennagrid::null_type>
      {
        typedef viennagrid::null_type type;
      };


      /** @brief Defines the default container tag for all elements in a domain. For vertices and cells specific given containers are used, for all others, hidden key maps are used to ensure the uniqueness of elements (taking orientation into account) */
      template<typename ElementTagT, typename boundary_cell_tag, typename VertexContainerT, typename CellContainerT>
      struct default_container_tag
      {
        typedef viennagrid::hidden_key_map_tag< viennagrid::element_key_tag > type;
      };

      template<typename ElementTagT, typename VertexContainerT, typename CellContainerT>
      struct default_container_tag<ElementTagT, ElementTagT, VertexContainerT, CellContainerT>
      {
        typedef CellContainerT type;
      };

      template<typename ElementTagT, typename VertexContainerT, typename CellContainerT>
      struct default_container_tag<ElementTagT, viennagrid::vertex_tag, VertexContainerT, CellContainerT>
      {
        typedef VertexContainerT type;
      };

      template<typename VertexContainerT, typename CellContainerT>
      struct default_container_tag<viennagrid::vertex_tag, viennagrid::vertex_tag, VertexContainerT, CellContainerT>
      {
        typedef VertexContainerT type;
      };


      /** @brief Creates the complete configuration for one element. ID tag is smart_id_tag<int>, element_container_tag is defined based default_container_tag meta function, boundary_storage_layout is defined based on storage_layout_config, no appendix type. For vertex no boundary storage layout is defined. */
      template<typename CellTagT, typename ElementTagT, typename HandleTagT, typename VertexContainerT, typename CellContainerT>
      struct full_element_config
      {
        typedef typename viennagrid::result_of::handled_container<typename default_container_tag<CellTagT, ElementTagT, VertexContainerT, CellContainerT>::type,
                                                                            HandleTagT>::tag                     container_tag;

        typedef typename storage_layout_config<CellTagT,
                                                typename ElementTagT::facet_tag>::type   boundary_storage_layout;

        typedef typename viennagrid::make_typemap<
            viennagrid::config::element_id_tag,
            viennagrid::smart_id_tag<int>,

            viennagrid::config::element_container_tag,
            container_tag,

            viennagrid::config::element_boundary_storage_layout_tag,
            boundary_storage_layout,

            viennagrid::config::element_appendix_type_tag,
            viennagrid::null_type
        >::type type;
      };

      template<typename CellTagT, typename HandleTagT, typename VertexContainerT, typename CellContainerT>
      struct full_element_config<CellTagT, viennagrid::vertex_tag, HandleTagT, VertexContainerT, CellContainerT>
      {
        typedef typename viennagrid::result_of::handled_container<typename default_container_tag<CellTagT, viennagrid::vertex_tag, VertexContainerT, CellContainerT>::type,
                                                                            HandleTagT>::tag                     container_tag;

        typedef typename viennagrid::make_typemap<
            viennagrid::config::element_id_tag,
            viennagrid::smart_id_tag<int>,

            viennagrid::config::element_container_tag,
            container_tag,

            viennagrid::config::element_boundary_storage_layout_tag,
            viennagrid::null_type,

            viennagrid::config::element_appendix_type_tag,
            viennagrid::null_type
        >::type type;
      };


      /** @brief Helper meta function for creating topologic configuration using full_element_config for each element. Terminates at vertex level. */
      template<typename CellTagT, typename ElementTagT, typename HandleTagT, typename VertexContainerTagT, typename CellContainerTagT>
      struct full_topology_config_helper
      {
        typedef typename viennagrid::detail::result_of::insert<
            typename full_topology_config_helper<CellTagT, typename ElementTagT::facet_tag, HandleTagT, VertexContainerTagT, CellContainerTagT>::type,
            viennagrid::static_pair<
                ElementTagT,
                typename full_element_config<CellTagT, ElementTagT, HandleTagT, VertexContainerTagT, CellContainerTagT>::type
            >
        >::type type;
      };

      template<typename CellTagT, typename HandleTagT, typename VertexContainerTagT, typename CellContainerTagT>
      struct full_topology_config_helper<CellTagT, viennagrid::vertex_tag, HandleTagT, VertexContainerTagT, CellContainerTagT>
      {
        typedef typename viennagrid::make_typemap<
            viennagrid::vertex_tag,
            typename full_element_config<CellTagT, viennagrid::vertex_tag, HandleTagT, VertexContainerTagT, CellContainerTagT>::type
        >::type type;
      };


      /** @brief Meta function for creating a topologic configuration.
       *  @tparam CellTagT              The cell tag of the mesh
       *  @tparam HandleTagT            Defines, which handle type should be used for all elements. Default is pointer handle
       *  @tparam VertexContainerTagT   Defines, which container type should be used for vertices. Default is std::deque
       *  @tparam CellContainerTagT     Defines, which container type should be used for cells. Default is std::deque
       */
      template<typename CellTagT,
               typename HandleTagT  = viennagrid::pointer_handle_tag,
               typename VertexContainerTagT = viennagrid::std_deque_tag,
               typename CellContainerTagT = viennagrid::std_deque_tag>
      struct full_topology_config
      {
        typedef typename full_topology_config_helper<CellTagT, CellTagT, HandleTagT, VertexContainerTagT, CellContainerTagT>::type type;
      };




      /** @brief Meta function for creating a thin topologic configuration. A thin topology only holds cells and vertices, but no facets, etc.
       *  @tparam CellTagT              The cell tag of the mesh
       *  @tparam HandleTagT            Defines, which handle type should be used for all elements. Default is pointer handle
       *  @tparam VertexContainerTagT   Defines, which container type should be used for vertices. Default is std::deque
       *  @tparam CellContainerTagT     Defines, which container type should be used for cells. Default is std::deque
       */
      template<typename CellTagT,
               typename HandleTagT  = viennagrid::pointer_handle_tag,
               typename VertexContainerTagT = viennagrid::std_deque_tag,
               typename CellContainerTagT = viennagrid::std_deque_tag>
      struct thin_topology_config
      {
        typedef typename viennagrid::make_typemap<
            CellTagT,
            typename viennagrid::make_typemap<
                viennagrid::config::element_id_tag,
                viennagrid::smart_id_tag<int>,

                viennagrid::config::element_container_tag,
                typename viennagrid::result_of::handled_container<CellContainerTagT, HandleTagT>::tag,

                viennagrid::config::element_boundary_storage_layout_tag,
                typename storage_layout_config<CellTagT, viennagrid::vertex_tag>::type,

                viennagrid::config::element_appendix_type_tag,
                viennagrid::null_type
            >::type,


            viennagrid::vertex_tag,
            typename viennagrid::make_typemap<
              viennagrid::config::element_id_tag,
              viennagrid::smart_id_tag<int>,

              viennagrid::config::element_container_tag,
              typename viennagrid::result_of::handled_container<VertexContainerTagT, HandleTagT>::tag,

              viennagrid::config::element_boundary_storage_layout_tag,
              viennagrid::null_type,

              viennagrid::config::element_appendix_type_tag,
              viennagrid::null_type
            >::type
        >::type type;
      };




      /** @brief Meta function for creating a geometric configuration. A topologic configuration is created with the exception that the vertex appendix type is a given point type.
       *  @tparam CellTagT              The cell tag of the mesh
       *  @tparam PointType             The point type of the mesh
       *  @tparam HandleTagT            Defines, which handle type should be used for all elements. Default is pointer handle
       *  @tparam VertexContainerTagT   Defines, which container type should be used for vertices. Default is std::deque
       *  @tparam CellContainerTagT     Defines, which container type should be used for cells. Default is std::deque
       */
      template<typename CellTagT,
                typename PointType,
                typename HandleTagT = viennagrid::pointer_handle_tag,
                typename VertexContainerTagT = viennagrid::std_deque_tag,
                typename CellContainerTagT = viennagrid::std_deque_tag>
      struct full_mesh_config
      {
        typedef typename full_topology_config<CellTagT, HandleTagT, VertexContainerTagT, CellContainerTagT>::type MeshConfig;
        typedef typename query<MeshConfig, null_type, vertex_tag>::type VertexConfig;

        typedef typename viennagrid::detail::result_of::insert_or_modify<
            MeshConfig,
            viennagrid::static_pair<
                vertex_tag,
                typename viennagrid::detail::result_of::insert_or_modify<

                    VertexConfig,
                    viennagrid::static_pair<
                        element_appendix_type_tag,
                        PointType
                    >

                >::type
            >
        >::type type;
      };

      template<typename CellTagT, typename HandleTagT, typename VertexContainerTagT, typename CellContainerTagT>
      struct full_mesh_config<CellTagT, void, HandleTagT, VertexContainerTagT, CellContainerTagT>
      {
        typedef typename viennagrid::config::result_of::full_topology_config<CellTagT, HandleTagT, VertexContainerTagT, CellContainerTagT>::type type;
      };




      /** @brief Meta function for creating a geometric configuration with thin topology. A thin topologic configuration is created with the exception that the vertex appendix type is a given point type.
       *  @tparam CellTagT              The cell tag of the mesh
       *  @tparam PointType             The point type of the mesh
       *  @tparam HandleTagT            Defines, which handle type should be used for all elements. Default is pointer handle
       *  @tparam VertexContainerTagT   Defines, which container type should be used for vertices. Default is std::deque
       *  @tparam CellContainerTagT     Defines, which container type should be used for cells. Default is std::deque
       */
      template<typename CellTagT,
                typename PointType,
                typename HandleTagT = viennagrid::pointer_handle_tag,
                typename VertexContainerTagT = viennagrid::std_deque_tag,
                typename CellContainerTagT = viennagrid::std_deque_tag>
      struct thin_mesh_config
      {
        typedef typename thin_topology_config<CellTagT, HandleTagT, VertexContainerTagT, CellContainerTagT>::type MeshConfig;
        typedef typename query<MeshConfig, null_type, vertex_tag>::type VertexConfig;

        typedef typename viennagrid::detail::result_of::insert_or_modify<
            MeshConfig,
            viennagrid::static_pair<
                vertex_tag,
                typename viennagrid::detail::result_of::insert_or_modify<

                    VertexConfig,
                    viennagrid::static_pair<
                        element_appendix_type_tag,
                        PointType
                    >

                >::type
            >
        >::type type;
      };

      template<typename CellTagT, typename HandleTagT, typename VertexContainerTagT, typename CellContainerTagT>
      struct thin_mesh_config<CellTagT, void, HandleTagT, VertexContainerTagT, CellContainerTagT>
      {
        typedef typename viennagrid::config::result_of::thin_topology_config<CellTagT, HandleTagT, VertexContainerTagT, CellContainerTagT>::type type;
      };




      /** @brief Creates a container for a specified ElementTagT for the mesh container collection based on a wrapped config. If a container collection is used as first argument, the container for the element with tag ElementTagT within the container collection is returned. */
      template<typename WrappedConfigType, typename ElementTagT>
      struct element_container
      {
        typedef viennagrid::element<ElementTagT, WrappedConfigType> element_type;
        typedef typename viennagrid::result_of::container<element_type, typename query_element_container_tag<WrappedConfigType, ElementTagT>::type >::type type;
      };

      template<typename container_collection_typemap, typename ElementTagT>
      struct element_container< collection<container_collection_typemap>, ElementTagT >
      {
        typedef typename viennagrid::result_of::element<collection<container_collection_typemap>, ElementTagT>::type element_type;
        typedef typename viennagrid::detail::result_of::find< container_collection_typemap, element_type >::type::second type;
      };


      /** @brief Creates the typemap of all elements with their containers used by the container collection of a mesh based on a wrapped config. */
      template<typename WrappedConfigT, typename CurrentConfigT = typename WrappedConfigT::type>
      struct element_container_typemap;

      template<typename WrappedConfigT, typename ElementTagT, typename ValueConfigT, typename TailT>
      struct element_container_typemap< WrappedConfigT, viennagrid::typelist< viennagrid::static_pair<ElementTagT, ValueConfigT>, TailT > >
      {
        typedef viennagrid::typelist<
            viennagrid::static_pair<
                viennagrid::element<ElementTagT, WrappedConfigT>,
                typename element_container<WrappedConfigT, ElementTagT>::type
            >,
            typename element_container_typemap<WrappedConfigT, TailT>::type
        > type;
      };

      template<typename WrappedConfigT>
      struct element_container_typemap<WrappedConfigT, viennagrid::null_type>
      {
          typedef viennagrid::null_type type;
      };
    }



    /** @brief A generic config wrapper for mesh configs. */
    template<typename CellTagT,
              typename PointTypeT,
              typename HandleTagT = viennagrid::pointer_handle_tag,
              typename VertexContainerTagT = viennagrid::std_deque_tag,
              typename CellContainerTagT = viennagrid::std_deque_tag>
    struct wrapped_mesh_config_t
    {
      typedef typename result_of::full_mesh_config<CellTagT, PointTypeT, HandleTagT, VertexContainerTagT, CellContainerTagT>::type type;
    };
  }

  namespace result_of
  {
    /** @brief Creates the typemap for the coboundary container collection based on an element and its boundary element typelist. */
    template<typename WrappedConfigType, typename ElementTagT, typename BoundaryElementTaglistT =
      typename boundary_element_taglist< viennagrid::element<ElementTagT, WrappedConfigType> >::type >
    struct coboundary_container_collection_per_element_typemap;

    /** \cond */
    template<typename WrappedConfigType, typename ElementTagT>
    struct coboundary_container_collection_per_element_typemap<WrappedConfigType, ElementTagT, viennagrid::null_type>
    {
        typedef viennagrid::null_type type;
    };

    template<typename WrappedConfigType, typename ElementTagT, typename BoundaryElementTagT, typename tail>
    struct coboundary_container_collection_per_element_typemap<WrappedConfigType, ElementTagT, viennagrid::typelist<BoundaryElementTagT, tail> >
    {
      typedef typename config::result_of::query<WrappedConfigType, long, config::mesh_change_counter_tag>::type MeshChangeCounterType;

      typedef typename config::result_of::query<WrappedConfigType, std_vector_tag, ElementTagT, config::coboundary_container_tag, BoundaryElementTagT>::type coboundary_container_tag;
      typedef typename config::result_of::query<WrappedConfigType, std_vector_tag, ElementTagT, config::coboundary_view_container_tag, BoundaryElementTagT>::type coboundary_view_container_tag;


      typedef typename config::result_of::element_container< WrappedConfigType, ElementTagT>::type base_element_container;
      typedef typename viennagrid::result_of::view<base_element_container, coboundary_view_container_tag>::type element_view_type;
      typedef typename result_of::container<element_view_type, coboundary_container_tag >::type base_coboundary_container;

      typedef viennagrid::typelist<
          viennagrid::static_pair<
              viennagrid::static_pair<
                  BoundaryElementTagT,
                  ElementTagT
              >,
              detail::coboundary_container_wrapper<base_coboundary_container, MeshChangeCounterType>
          >,
          typename coboundary_container_collection_per_element_typemap<WrappedConfigType, ElementTagT, tail>::type
      > type;
    };
    /** \endcond */


    /** @brief Creates the typemap for the coboundary container collection for all elements by merging all typemaps created by coboundary_container_collection_per_element_typemap. */
    template<typename WrappedConfigType, typename ElementTaglistT = typename viennagrid::detail::result_of::key_typelist<typename WrappedConfigType::type>::type>
    struct coboundary_container_collection_typemap {};

    /** \cond */
    template<typename WrappedConfigType>
    struct coboundary_container_collection_typemap<WrappedConfigType, viennagrid::null_type>
    {
      typedef viennagrid::null_type type;
    };

    template<typename WrappedConfigType, typename ElementTagT, typename tail>
    struct coboundary_container_collection_typemap<WrappedConfigType, viennagrid::typelist<ElementTagT, tail> >
    {
      typedef typename viennagrid::detail::result_of::merge<
        typename coboundary_container_collection_per_element_typemap<WrappedConfigType, ElementTagT>::type,
        typename coboundary_container_collection_typemap<WrappedConfigType, tail>::type
      >::type type;
    };
    /** \endcond */
  }




  namespace result_of
  {
    /** @brief Creates the typemap for the neighbor container collection based on an element and its boundary element typelist. The boundary elements are used as connector elements. */
    template<typename WrappedConfigType, typename ElementTagT, typename BoundaryElementTaglistT =
      typename boundary_element_taglist< viennagrid::element<ElementTagT, WrappedConfigType> >::type >
    struct neighbor_container_collection_per_element_typemap {};

    /** \cond */
    template<typename WrappedConfigType, typename ElementTagT>
    struct neighbor_container_collection_per_element_typemap<WrappedConfigType, ElementTagT, viennagrid::null_type>
    {
      typedef viennagrid::null_type type;
    };

    template<typename WrappedConfigType, typename ElementTagT, typename ConnectorElementTagT, typename tail>
    struct neighbor_container_collection_per_element_typemap<WrappedConfigType, ElementTagT, viennagrid::typelist<ConnectorElementTagT, tail> >
    {
      typedef typename config::result_of::query<WrappedConfigType, long, config::mesh_change_counter_tag>::type MeshChangeCounterType;

      typedef typename config::result_of::query<WrappedConfigType, std_vector_tag, ElementTagT, config::neighbor_container_tag, ConnectorElementTagT>::type neighbor_container_tag;
      typedef typename config::result_of::query<WrappedConfigType, std_vector_tag, ElementTagT, config::neighbor_view_container_tag, ConnectorElementTagT>::type neighbor_view_container_tag;

      typedef typename config::result_of::element_container< WrappedConfigType, ElementTagT>::type base_element_container;
      typedef typename viennagrid::result_of::view<base_element_container, neighbor_view_container_tag>::type element_view_type;
      typedef typename result_of::container<element_view_type, neighbor_container_tag >::type base_container;

      typedef viennagrid::typelist<
          viennagrid::static_pair<
              viennagrid::static_pair<
                  ElementTagT,
                  ConnectorElementTagT
              >,
              detail::neighbor_container_wrapper<base_container, MeshChangeCounterType>
          >,
          typename neighbor_container_collection_per_element_typemap<WrappedConfigType, ElementTagT, tail>::type
      > type;
    };
    /** \endcond */


    /** @brief Creates the typemap for the neighbor container collection for all elements by merging all typemaps created by neighbor_container_collection_per_element_typemap. */
    template<typename WrappedConfigType, typename ElementTaglistT = typename viennagrid::detail::result_of::key_typelist<typename WrappedConfigType::type>::type>
    struct neighbor_container_collection_typemap {};

    /** \cond */
    template<typename WrappedConfigType>
    struct neighbor_container_collection_typemap<WrappedConfigType, viennagrid::null_type>
    {
      typedef viennagrid::null_type type;
    };

    template<typename WrappedConfigType, typename ElementTagT, typename tail>
    struct neighbor_container_collection_typemap<WrappedConfigType, viennagrid::typelist<ElementTagT, tail> >
    {
      typedef typename viennagrid::detail::result_of::merge<
        typename neighbor_container_collection_per_element_typemap<WrappedConfigType, ElementTagT>::type,
        typename neighbor_container_collection_typemap<WrappedConfigType, tail>::type
      >::type type;
    };
    /** \endcond */
  }


  namespace result_of
  {
    /** @brief Metafunction for obtaining the topologic dimension of the cell elements of something
     *
     * @tparam SomethingT           The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename ElementTypelistT>
    struct topologic_cell_dimension;

    /** \cond */
    template<>
    struct topologic_cell_dimension<viennagrid::null_type>
    {
      static const int value = -1;
    };

    template<typename ElementTypeOrTagT, typename TailT>
    struct topologic_cell_dimension< viennagrid::typelist<ElementTypeOrTagT, TailT> >
    {
      typedef typename viennagrid::result_of::element_tag<ElementTypeOrTagT>::type ElementTag;
      static const int tail_cell_dimension = topologic_cell_dimension<TailT>::value;
      static const int current_element_dimension = ElementTag::dim;

      static const int value = (tail_cell_dimension > current_element_dimension) ? tail_cell_dimension : current_element_dimension;
    };
    /** \endcond */



    /** @brief Meta function for querying all elements of a specific topologic dimension using a typelist of elements of element tags. */
    template<typename ElementTypelistT, int TopologicDimensionV>
    struct elements_of_topologic_dim;

    /** \cond */
    template<int TopologicDimensionV>
    struct elements_of_topologic_dim< viennagrid::null_type, TopologicDimensionV >
    {
      typedef viennagrid::null_type type;
    };

    template<typename ElementTypeOrTagT, typename TailT, int TopologicDimensionV>
    struct elements_of_topologic_dim< viennagrid::typelist<ElementTypeOrTagT, TailT>, TopologicDimensionV >
    {
      typedef typename viennagrid::result_of::element_tag<ElementTypeOrTagT>::type ElementTag;
      typedef typename elements_of_topologic_dim<TailT, TopologicDimensionV>::type TailTypelist;

      typedef typename viennagrid::detail::IF<
          ElementTag::dim == TopologicDimensionV,
          typename viennagrid::detail::result_of::push_back<TailTypelist, ElementTag>::type,
          TailTypelist
      >::type type;
    };
    /** \endcond */


    /** @brief Meta function for determining the cell tag (tag of element with maximum topologic dimension) of a typelist of elements of element tags. The first cell tag is used. */
    template<typename ElementTypelistT>
    struct cell_tag_from_typelist
    {
      static const int dim = topologic_cell_dimension<ElementTypelistT>::value;
      typedef typename elements_of_topologic_dim<ElementTypelistT, dim>::type cell_types;
      typedef typename viennagrid::detail::result_of::at<cell_types,0>::type type;
    };





    /** @brief Creates the typemap for the boundary container collection for all element within a element typelist. */
    template<typename WrappedConfigType, typename ElementTaglistT>
    struct boundary_information_collection_typemap_impl {};

    /** \cond */
    template<typename WrappedConfigType>
    struct boundary_information_collection_typemap_impl<WrappedConfigType, viennagrid::null_type>
    {
      typedef viennagrid::null_type type;
    };

    template<typename WrappedConfigType, typename ElementTagT, typename TailT>
    struct boundary_information_collection_typemap_impl<WrappedConfigType, viennagrid::typelist<ElementTagT, TailT> >
    {
      typedef typename config::result_of::query<WrappedConfigType, long, config::mesh_change_counter_tag>::type MeshChangeCounterType;

      typedef typename config::result_of::query<WrappedConfigType, std_map_tag, ElementTagT, config::boundary_information_container_tag>::type boundary_container_tag;

      typedef viennagrid::element<ElementTagT, WrappedConfigType> ElementType;
      typedef typename result_of::accessor_container<ElementType, bool, boundary_container_tag>::type base_container;

      typedef viennagrid::typelist<
          viennagrid::static_pair<
              ElementTagT,
              detail::boundary_information_wrapper<base_container, MeshChangeCounterType>
          >,
          typename boundary_information_collection_typemap_impl<WrappedConfigType, TailT>::type
      > type;
    };
    /** \endcond */

    /** @brief Creates the typemap for the boundary container collection for all elements using boundary_information_collection_typemap_impl with all elements within a wrapped domain except the cell. */
    template<typename WrappedConfigType>
    struct boundary_information_collection_typemap
    {
      typedef typename viennagrid::detail::result_of::key_typelist<typename WrappedConfigType::type>::type ElementTagTlist;

      typedef typename cell_tag_from_typelist<ElementTagTlist>::type CellTag;
      typedef typename viennagrid::detail::result_of::erase< ElementTagTlist, CellTag>::type ElementTypelistWithoutCellTag;


      typedef typename boundary_information_collection_typemap_impl<WrappedConfigType, ElementTypelistWithoutCellTag>::type type;
    };
  }



  namespace config
  {
    namespace result_of
    {
      /** @brief Meta function for querying the element typelist for a mesh based on a wrapped config. */
      template<typename WrappedConfigType>
      struct element_collection
      {
        typedef typename config::result_of::element_container_typemap<WrappedConfigType>::type element_container_typelist;
        typedef collection< element_container_typelist > type;
      };
    }
  }
}


#endif
