#ifndef VIENNAGRID_ELEMENT_CONFIG_HPP
#define VIENNAGRID_ELEMENT_CONFIG_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */


#include "viennagrid/storage/view.hpp"
#include "viennagrid/element/element_orientation.hpp"
#include "viennagrid/config/config.hpp"
#include "viennagrid/topology/polygon.hpp"


/** @file viennagrid/config/element_config.hpp
    @brief Provides meta functions for creating element configuration
*/

namespace viennagrid
{
  namespace config
  {
    namespace result_of
    {
      /** @brief Defines the container tag based on storage layout and size of elements. Static layout -> staic_array, dynamic layout -> std::vector */
      template<typename storage_layout_tag, int num>
      struct boundary_cell_container_tag;

      template<int num>
      struct boundary_cell_container_tag<viennagrid::static_layout_tag, num>
      {
        typedef viennagrid::static_array_tag<num> type;
      };

      template<int num>
      struct boundary_cell_container_tag<viennagrid::dynamic_layout_tag, num>
      {
        typedef viennagrid::std_vector_tag type;
      };



      //
      // Generates an element type
      //

      /** @brief Determines if a given element tag is present within a wrapped config */
      template<typename WrappedConfigType, typename element_tag>
      struct is_element_present
      {
        typedef typename query<WrappedConfigType, null_type, element_tag>::type  ElementConfigType;

        static const bool value = !viennagrid::detail::EQUAL<ElementConfigType, viennagrid::not_found>::value;
      };


      /** @brief Queries the element id tag for a given element tag from a wrapped config, default is smart_id_tag<int>. */
      template<typename WrappedConfigType, typename element_tag>
      struct query_element_id_tag
      {
        typedef typename query<WrappedConfigType, viennagrid::smart_id_tag<int>, element_tag, element_id_tag>::type  type;
      };

      /** @brief Queries the container tag for a given element tag from a wrapped config, default is std::deque with pointer handle. */
      template<typename WrappedConfigType, typename element_tag>
      struct query_element_container_tag
      {
        typedef typename query<WrappedConfigType, viennagrid::handled_container_tag<viennagrid::std_deque_tag, viennagrid::pointer_handle_tag>, element_tag, element_container_tag>::type  type;
      };

      /** @brief Queries the appendix type for a given element tag from a wrapped config. PLC appendix type is std::vector<PointType> for holes. Default is null_type. */
      template<typename WrappedConfigType, typename element_tag>
      struct query_appendix_type
      {
        typedef typename query<WrappedConfigType, null_type, element_tag, element_appendix_type_tag>::type  type;
      };

      template<typename WrappedConfigType>
      struct query_appendix_type<WrappedConfigType, plc_tag>
      {
        typedef typename query_appendix_type<WrappedConfigType, vertex_tag>::type PointType;
        typedef std::vector<PointType> type;
      };


      /** @brief Helper class for has_boundary_cells, using dispatch if the host element is present. */
      template<typename WrappedConfigT, typename HostElementTagT, typename BoundaryElementTagT, bool is_present = is_element_present<WrappedConfigT, BoundaryElementTagT>::value >
      struct has_boundary_helper
      {
        static const bool value =
            !viennagrid::detail::EQUAL<
                typename query<WrappedConfigT, viennagrid::no_handling_tag, HostElementTagT, element_boundary_storage_layout_tag, BoundaryElementTagT>::type,
                viennagrid::no_handling_tag
            >::value;
      };

      template<typename WrappedConfigT, typename HostElementTagT, typename BoundaryElementTagT>
      struct has_boundary_helper<WrappedConfigT, HostElementTagT, BoundaryElementTagT, false>
      {
        static const bool value = false;
      };


      /** @brief Determines if a given host element has a given boundary element using a wrapped config */
      template<typename WrappedConfigT, typename HostElementTagT, typename BoundaryElementTagT>
      struct has_boundary
      {
        static const bool is_present = is_element_present<WrappedConfigT, BoundaryElementTagT>::value;
        static const bool value = has_boundary_helper<WrappedConfigT, HostElementTagT, BoundaryElementTagT, is_present>::value;
      };


      /** @brief Helper class for has_orientation, using dispatch if the host element is present. */
      template<typename WrappedConfigT, typename HostElementTagT, typename BoundaryElementTagT, bool is_present = is_element_present<WrappedConfigT, BoundaryElementTagT>::value >
      struct has_orientation_helper
      {
        static const bool value =
            viennagrid::detail::EQUAL<
                typename query<WrappedConfigT, viennagrid::no_handling_tag, HostElementTagT, element_boundary_storage_layout_tag, BoundaryElementTagT>::type,
                viennagrid::full_handling_tag
            >::value
                ||
            viennagrid::detail::EQUAL<
                typename query<WrappedConfigT, viennagrid::no_handling_tag, HostElementTagT, element_boundary_storage_layout_tag, BoundaryElementTagT>::type,
                viennagrid::full_lazy_handling_tag
            >::value;
      };

      template<typename WrappedConfigT, typename HostElementTagT, typename BoundaryElementTagT>
      struct has_orientation_helper<WrappedConfigT, HostElementTagT, BoundaryElementTagT, false>
      {
        static const bool value = false;
      };


      /** @brief Determines if orientation is available for a given host element and a given boundary element using a wrapped config */
      template<typename WrappedConfigT, typename HostElementTagT, typename BoundaryElementTagT>
      struct has_orientation
      {
        static const bool is_present = is_element_present<WrappedConfigT, BoundaryElementTagT>::value;
        static const bool value = has_orientation_helper<WrappedConfigT, HostElementTagT, BoundaryElementTagT, is_present>::value;
      };





      // TODO: handle possible other tags (lazy_handling_tag, ...)
      /** @brief Helper meta function for creating the boundary element container using a wrapped config: a view for the boundary elements and a possible orientation container. Handles elements which are not present. */
      template<typename WrappedConfigT, typename HostElementTagT, typename BoundaryElementTagT, bool is_present>
      struct element_boundary_element_container_helper
      {
        //
        // boundary cell view
        //
        typedef viennagrid::element<BoundaryElementTagT, WrappedConfigT> boundary_cell_type;

        typedef typename viennagrid::result_of::container<
            boundary_cell_type,                                         // the 'value_type', i.e. vertices
            typename query_element_container_tag<WrappedConfigT, BoundaryElementTagT>::type
        >::type boundary_cell_container;


        typedef typename boundary_cell_container_tag<
                typename viennagrid::boundary_elements< HostElementTagT, BoundaryElementTagT>::layout_tag,
                viennagrid::boundary_elements< HostElementTagT, BoundaryElementTagT>::num
            >::type container_tag;


        typedef typename viennagrid::result_of::view<
                boundary_cell_container,
                container_tag
            >::type
        boundary_cell_view;



        //
        // Orientation
        //

        typedef typename viennagrid::result_of::permutator_type<
            viennagrid::boundary_elements<
                BoundaryElementTagT,
                typename BoundaryElementTagT::facet_tag
            >::num
        >::type permutator_type;

        typedef typename boundary_cell_container_tag<
                typename viennagrid::boundary_elements< BoundaryElementTagT, typename BoundaryElementTagT::facet_tag>::layout_tag,
                viennagrid::boundary_elements< BoundaryElementTagT, typename BoundaryElementTagT::facet_tag>::num
            >::type orientation_container_tag;


        typedef typename viennagrid::result_of::container<permutator_type, orientation_container_tag>::type orientation_container_type;
        typedef viennagrid::element_orientation<orientation_container_type> facet_orientation_type;

        typedef typename
            viennagrid::detail::IF<
                has_orientation< WrappedConfigT, HostElementTagT, BoundaryElementTagT>::value,
                typename viennagrid::result_of::container< facet_orientation_type, container_tag >::type,
                viennagrid::null_type
            >::type facet_orientation_container_type;


        //
        // final container pair
        //

        typedef viennagrid::static_pair<
                        boundary_cell_view,
                        facet_orientation_container_type
                    > type;
      };

      template<typename WrappedConfigT, typename HostElementTagT, bool is_present>
      struct element_boundary_element_container_helper<WrappedConfigT, HostElementTagT, vertex_tag, is_present>
      {
        typedef vertex_tag BoundaryElementTag;

        //
        // boundary cell view
        //

        typedef viennagrid::element<BoundaryElementTag, WrappedConfigT> boundary_cell_type;

        typedef typename viennagrid::result_of::container<
            boundary_cell_type,                                         // the 'value_type', i.e. vertices
            typename query_element_container_tag<WrappedConfigT, BoundaryElementTag>::type
        >::type boundary_cell_container;


        typedef typename boundary_cell_container_tag<
                typename viennagrid::boundary_elements< HostElementTagT, BoundaryElementTag>::layout_tag,
                viennagrid::boundary_elements< HostElementTagT, BoundaryElementTag>::num
            >::type container_tag;


        typedef typename viennagrid::result_of::view<
                boundary_cell_container,
                container_tag
            >::type
        boundary_cell_view;



        //
        // Orientation
        //

        typedef viennagrid::null_type facet_orientation_container_type;


        //
        // final container pair
        //

        typedef viennagrid::static_pair<
                        boundary_cell_view,
                        facet_orientation_container_type
                    > type;
      };

      template<typename WrappedConfigT, typename HostElementTagT, typename BoundaryElementTagT>
      struct element_boundary_element_container_helper<WrappedConfigT, HostElementTagT, BoundaryElementTagT, false>
      {
        typedef viennagrid::null_type type;
      };


      /** @brief Creates the boundary element container and possible orientation container */
      template<typename WrappedConfigT, typename HostElementTagT, typename BoundaryElementTagT>
      struct element_boundary_element_container
      {
        static const bool is_present = has_boundary<WrappedConfigT, HostElementTagT, BoundaryElementTagT>::value;

        typedef typename element_boundary_element_container_helper<WrappedConfigT, HostElementTagT, BoundaryElementTagT, is_present>::type type;
      };


      /** @brief Creates a typelist of all boundary container types for a given element tag using a wrapped config */
      template<typename WrappedConfigT, typename HostElementTagT, typename BoundaryElementTagT = HostElementTagT>
      struct element_boundary_element_container_typelist
      {
        typedef typename BoundaryElementTagT::facet_tag facet_tag;

        typedef typename element_boundary_element_container<WrappedConfigT, HostElementTagT, facet_tag>::type boundary_cell_layer_containers;
        typedef typename viennagrid::detail::result_of::push_back<
            typename element_boundary_element_container_typelist< WrappedConfigT, HostElementTagT, facet_tag >::type,
            boundary_cell_layer_containers
        >::type type;
      };

      template<typename WrappedConfigT, typename HostElementTagT>
      struct element_boundary_element_container_typelist<WrappedConfigT, HostElementTagT, viennagrid::vertex_tag>
      {
        typedef viennagrid::null_type type;
      };
    }
  }
}


#endif
