#ifndef VIENNAGRID_STORAGE_ID_GENERATOR_HPP
#define VIENNAGRID_STORAGE_ID_GENERATOR_HPP

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
#include "viennagrid/meta/typelist.hpp"
#include "viennagrid/meta/typemap.hpp"
#include "viennagrid/storage/id.hpp"
#include "viennagrid/config/config.hpp"

/** @file viennagrid/storage/id_generator.hpp
    @brief Generator for IDs of a certain type
*/

namespace viennagrid
{
  namespace detail
  {
    namespace result_of
    {
      template<typename typelist, typename id_type>
      struct continuous_id_generator_config_helper;

      /** \cond */
      template<typename head, typename tail, typename id_type>
      struct continuous_id_generator_config_helper< viennagrid::typelist<head, tail>, id_type >
      {
        typedef typename viennagrid::detail::result_of::insert<
            typename continuous_id_generator_config_helper<tail, id_type>::type,
            viennagrid::static_pair<
                head,
                id_type
            >
        >::type type;
      };

      template<typename id_type>
      struct continuous_id_generator_config_helper<viennagrid::null_type, id_type>
      {
        typedef viennagrid::null_type type;
      };


      template<typename WrappedConfigType, typename typemap>
      struct continuous_id_generator_config_from_mesh_config_helper;

      template<typename WrappedConfigType, typename element_tag, typename element_config, typename tail>
      struct continuous_id_generator_config_from_mesh_config_helper< WrappedConfigType, viennagrid::typelist<viennagrid::static_pair<element_tag, element_config>, tail> >
      {
        typedef typename viennagrid::detail::result_of::insert<
            typename continuous_id_generator_config_from_mesh_config_helper<WrappedConfigType, tail>::type,
            viennagrid::static_pair<
                viennagrid::element<element_tag, WrappedConfigType>,
//                         typename viennagrid::result_of::element<mesh_config, element_tag>::type,
                typename config::result_of::query<element_config, viennagrid::smart_id_tag<int>, config::element_id_tag>::type
//                         typename element_config::element_config::id_tag
            >
        >::type type;
      };

      template<typename WrappedConfigType>
      struct continuous_id_generator_config_from_mesh_config_helper<WrappedConfigType, viennagrid::null_type>
      {
        typedef viennagrid::null_type type;
      };

      template<typename typelist, typename id_type>
      struct continuous_id_generator_config
      {
        typedef typename continuous_id_generator_config_helper<
            typename viennagrid::detail::result_of::no_duplicates<typelist>::type,
            id_type
        >::type type;
      };

      template<typename WrappedConfigType>
      struct continuous_id_generator_config_from_mesh_config
      {
        typedef typename continuous_id_generator_config_from_mesh_config_helper<WrappedConfigType, typename WrappedConfigType::type>::type type;
      };

      /** \endcond */
    }




    template<typename id_generator_config>
    class continuous_id_generator_layer;

    template<typename value_type, typename id_tag, typename tail>
    class continuous_id_generator_layer<viennagrid::typelist< viennagrid::static_pair<value_type, id_tag>, tail> > : public continuous_id_generator_layer<tail>
    {
      typedef continuous_id_generator_layer<tail> base;
    public:

      typedef viennagrid::typelist< viennagrid::static_pair<value_type, id_tag>, tail> config_type;

      typedef typename result_of::make_id<value_type, id_tag>::type id_type;

      continuous_id_generator_layer() : base(), last_id(0) {}

      using base::operator();
      id_type operator()( viennagrid::detail::tag<value_type> )
      {
        return last_id++;
      }

      using base::set_max_id;
      void set_max_id( id_type last_id_ )
      {
        if (last_id_ > last_id)
        {
          last_id = last_id_;
          ++last_id;
        }
      }

      using base::max_id;
      id_type max_id( viennagrid::detail::tag<value_type> ) const
      {
        return last_id;
      }

    private:
      id_type last_id;
    };

    template<>
    class continuous_id_generator_layer<viennagrid::null_type>
    {
    public:
      void operator()();
      void set_max_id();
      void max_id() const;
    };

  }

  /** @brief A generator which returns numerical IDs (of possibly different type) in a continuous fashion starting from zero for each requested type.
    *
    * The configuration is carried out via a type map. For an element <KeyType, IDTag> the KeyType is used for the operator() dispatch, while the IDTag specifies the type of the ID used.
    */
  template<typename typemap>
  class continuous_id_generator : public detail::continuous_id_generator_layer< typemap >
  {};

  namespace result_of
  {
    /** \cond */
    template<typename typemap>
    struct continuous_id_generator
    {
      typedef viennagrid::continuous_id_generator< typemap > type;
    };
    /** \endcond */
  }
}

#endif
