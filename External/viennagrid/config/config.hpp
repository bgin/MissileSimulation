#ifndef VIENNAGRID_CONFIG_HPP
#define VIENNAGRID_CONFIG_HPP

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
#include "viennagrid/storage/forwards.hpp"
#include "../meta/utils.hpp"

/** @file viennagrid/config/config.hpp
    @brief Basic functionality and tags for configuration
*/

namespace viennagrid
{
  namespace config
  {
    /** @brief Defines the key within a typemap tree config for identifying the id tag of an element type. */
    struct element_id_tag;
    /** @brief Defines the key within a typemap tree config for identifying the container tag of an element type. */
    struct element_container_tag;
    /** @brief Defines the key within a typemap tree config for identifying the boundary storage layout tag of a host element type and a boundary element type. Possible values: no_handling_tag, no_orientation_handling_tag, full_handling_tag. */
    struct element_boundary_storage_layout_tag;
    /** @brief Defines the key within a typemap tree config for identifying the appendix type of an element type. */
    struct element_appendix_type_tag;

    /** @brief Defines the key within a typemap tree config for identifying the id generator tag for all element types. Possible value: continuous_id_generator_tag. */
    struct id_generator_tag;
    /** @brief Represents a continuous id generator. */
    struct continuous_id_generator_tag;

    /** @brief Defines the key within a typemap tree config for identifying the container tag for the container of all coboundary views of a host element typeand a coboundary element type. */
    struct coboundary_container_tag;
    /** @brief Defines the key within a typemap tree config for identifying the container tag for the coboundary view of a host element type and a coboundary element type. */
    struct coboundary_view_container_tag;

    /** @brief Defines the key within a typemap tree config for identifying the container tag for the container of all neighbor views of a host element type and a connector element type. */
    struct neighbor_container_tag;
    /** @brief Defines the key within a typemap tree config for identifying the container tag for the neighbor view of a host element type and a connector element type. */
    struct neighbor_view_container_tag;

    /** @brief Defines the key within a typemap tree config for identifying the container tag for the boundary information of an element type. */
    struct boundary_information_container_tag;

    /** @brief Defines the key within a typemap tree config for identifying the container tag for the interface information of an element type. */
    struct interface_information_container_tag;

    /** @brief Defines the key within a typemap tree config for identifying the geometrical vector type. */
    struct vector_type_tag;

    /** @brief Defines the key within a typemap tree config for identifying the change counter type of meshes and views. */
    struct mesh_change_counter_tag;


    namespace result_of
    {
      /** \cond */

      /** @brief Query a specific config element within a typemap tree config providing a default value which is used if the query was not successful. Up to 10 search tags can be provided. The first tag is searched and then, using the value type as the child config, the query is executed recursively.
       *
       * @tparam WrappedConfigT         The configuration, wrapped and non-wrapped configs are supported
       * @tparam DefaultT               The default value type
       */
      template<typename WrappedConfigT, typename DefaultT,
                typename SearchTag0T = viennagrid::null_type, typename SearchTag1T = viennagrid::null_type, typename SearchTag2T = viennagrid::null_type,
                typename SearchTag3T = viennagrid::null_type, typename SearchTag4T = viennagrid::null_type, typename SearchTag5T = viennagrid::null_type,
                typename SearchTag6T = viennagrid::null_type, typename SearchTag7T = viennagrid::null_type, typename SearchTag8T = viennagrid::null_type,
                typename SearchTag9T = viennagrid::null_type>
      struct query
      {
        typedef typename query<typename WrappedConfigT::type, DefaultT,
                SearchTag0T, SearchTag1T, SearchTag2T, SearchTag3T, SearchTag4T, SearchTag5T, SearchTag6T, SearchTag7T, SearchTag8T, SearchTag9T>::type type;
      };

      template<typename DefaultT, typename SearchTag0T, typename SearchTag1T, typename SearchTag2T, typename SearchTag3T, typename SearchTag4T,
                              typename SearchTag5T, typename SearchTag6T, typename SearchTag7T, typename SearchTag8T, typename SearchTag9T>
      struct query<viennagrid::not_found, DefaultT, SearchTag0T, SearchTag1T, SearchTag2T, SearchTag3T, SearchTag4T,
                                                                              SearchTag5T, SearchTag6T, SearchTag7T, SearchTag8T, SearchTag9T>
      {
        typedef DefaultT type;
      };



      template<typename HeadT, typename TailT, typename DefaultT, typename SearchTag0T, typename SearchTag2T, typename SearchTag3T, typename SearchTag4T,
                              typename SearchTag5T, typename SearchTag6T, typename SearchTag7T, typename SearchTag8T, typename SearchTag9T>
      struct query<viennagrid::typelist<HeadT, TailT>, DefaultT, SearchTag0T, viennagrid::null_type, SearchTag2T, SearchTag3T, SearchTag4T,
                                                          SearchTag5T, SearchTag6T, SearchTag7T, SearchTag8T, SearchTag9T>
      {
        typedef viennagrid::typelist<HeadT, TailT> ConfigType;
        typedef typename viennagrid::detail::result_of::lookup<ConfigType, SearchTag0T>::type EntryType;
        typedef typename viennagrid::detail::IF<
            viennagrid::detail::EQUAL<EntryType, viennagrid::not_found>::value,
            DefaultT,
            EntryType>::type type;
      };


      template<typename HeadT, typename TailT, typename DefaultT>
      struct query<viennagrid::typelist<HeadT, TailT>, DefaultT,
          viennagrid::null_type, viennagrid::null_type, viennagrid::null_type, viennagrid::null_type, viennagrid::null_type,
          viennagrid::null_type, viennagrid::null_type, viennagrid::null_type, viennagrid::null_type, viennagrid::null_type>
      {
        typedef DefaultT type;
      };


      template<typename HeadT, typename TailT, typename DefaultT,
                typename SearchTag0T, typename SearchTag1T, typename SearchTag2T,
                typename SearchTag3T, typename SearchTag4T, typename SearchTag5T,
                typename SearchTag6T, typename SearchTag7T, typename SearchTag8T,
                typename SearchTag9T>
      struct query<viennagrid::typelist<HeadT, TailT>, DefaultT,
                   SearchTag0T, SearchTag1T, SearchTag2T, SearchTag3T, SearchTag4T, SearchTag5T, SearchTag6T, SearchTag7T, SearchTag8T, SearchTag9T>
      {
        typedef viennagrid::typelist<HeadT, TailT> ConfigT;
        typedef typename viennagrid::detail::result_of::lookup<ConfigT, SearchTag0T>::type EntryType;
        typedef typename query<
              EntryType, DefaultT,
              SearchTag1T, SearchTag2T, SearchTag3T, SearchTag4T, SearchTag5T, SearchTag6T, SearchTag7T, SearchTag8T, SearchTag9T
            >::type type;
      };

      /** \endcond */
    }
  }

}


#endif
