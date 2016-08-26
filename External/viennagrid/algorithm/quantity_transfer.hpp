#ifndef VIENNAGRID_ALGORITHM_QUANTITY_TRANSFER_HPP
#define VIENNAGRID_ALGORITHM_QUANTITY_TRANSFER_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include <vector>
#include "viennagrid/forwards.hpp"
#include "viennagrid/mesh/mesh.hpp"

/** @file viennagrid/algorithm/quantity_transfer.hpp
    @brief Provides routines for transferring quantities defined for elements of one topological dimensions to elements of other topological dimension.
*/

namespace viennagrid
{
  namespace detail
  {
    /** @brief Indicates a transfer from higher to lower topological dimension (boundary operation) */
    struct boundary_quantity_transfer_tag {};

    /** @brief Indicates a transfer from lower to higher topological dimension (coboundary operation) */
    struct coboundary_quantity_transfer_tag {};

    template <typename SourceTag, typename DestinationTag,
              bool less_than = (SourceTag::dim < DestinationTag::dim),
              bool larger_than = (SourceTag::dim > DestinationTag::dim)>
    struct quantity_transfer_dispatcher {};

    template <typename SourceTag, typename DestinationTag>
    struct quantity_transfer_dispatcher<SourceTag, DestinationTag, false, true>
    {
      typedef boundary_quantity_transfer_tag  type;
    };

    template <typename SourceTag, typename DestinationTag>
    struct quantity_transfer_dispatcher<SourceTag, DestinationTag, true, false>
    {
      typedef coboundary_quantity_transfer_tag  type;
    };


    // Implementation for boundary transfer
    template <typename SourceTag,      typename DestinationTag,
              typename MeshOrSegmentT, typename SourceAccessorT, typename DestinationSetterT,
              typename AveragerT,      typename SourceFilterT,   typename DestinationFilterT>
    void quantity_transfer(MeshOrSegmentT const & mesh_or_segment, SourceAccessorT const & accessor_src, DestinationSetterT & setter_dest,
                           AveragerT const & averager, SourceFilterT const & filter_src, DestinationFilterT const & filter_dest,
                           boundary_quantity_transfer_tag)
    {
      typedef typename viennagrid::result_of::element<MeshOrSegmentT, SourceTag>::type              SourceElementType;
      typedef typename viennagrid::result_of::element<MeshOrSegmentT, DestinationTag>::type         DestElementType;

      typedef typename viennagrid::result_of::const_element_range<MeshOrSegmentT, SourceTag>::type  SourceContainer;
      typedef typename viennagrid::result_of::iterator<SourceContainer>::type                       SourceIterator;

      typedef typename viennagrid::result_of::const_element_range<SourceElementType, DestinationTag>::type  DestOnSrcContainer;
      typedef typename viennagrid::result_of::iterator<DestOnSrcContainer>::type                            DestOnSrcIterator;

      typedef typename SourceAccessorT::value_type              value_type;

      typedef std::map<DestElementType const *, std::vector<value_type> >                     DestinationValueMap;  //Think about adding customization options for std::vector<double>

      SourceContainer source_cells(mesh_or_segment);

      DestinationValueMap  values_for_destination_cells;

      // Step 1: Push all values from source cells to their destination boundary.
      //         Note that a coboundary-iteration over destination cells has a higher memory footprint, thus this lightweight-variant using only boundary-iterations is used
      for (SourceIterator sit = source_cells.begin();
                          sit != source_cells.end(); ++sit)
      {
        if ( filter_src(*sit) )
        {
          DestOnSrcContainer dest_on_src(*sit);
          for (DestOnSrcIterator dosit  = dest_on_src.begin();
                                  dosit != dest_on_src.end();
                                ++dosit)
          {
            if (filter_dest(*dosit))
              values_for_destination_cells[&(*dosit)].push_back(accessor_src(*sit));
          }
        }
      }

      // Step 2: Now average over values on destination cells
      for (typename DestinationValueMap::const_iterator dest_values_it  = values_for_destination_cells.begin();
                                                        dest_values_it != values_for_destination_cells.end();
                                                      ++dest_values_it)
      {
        setter_dest(*(dest_values_it->first),
                    averager(dest_values_it->second));
      }
    }

    // Implementation for quantity transfer
    template <typename SourceTag, typename DestinationTag,
              typename MeshOrSegmentT, typename SourceAccessorT, typename DestinationSetterT,
              typename AveragerT,      typename SourceFilterT,   typename DestinationFilterT>
    void quantity_transfer(MeshOrSegmentT const & mesh_or_segment, SourceAccessorT const & accessor_src, DestinationSetterT       & setter_dest,
                           AveragerT      const & averager,        SourceFilterT   const & filter_src,   DestinationFilterT const & filter_dest,
                           coboundary_quantity_transfer_tag)
    {
      typedef typename viennagrid::result_of::element<MeshOrSegmentT, DestinationTag>::type         DestElementType;

      typedef typename viennagrid::result_of::const_element_range<MeshOrSegmentT, DestinationTag>::type DestContainer;
      typedef typename viennagrid::result_of::iterator<DestContainer>::type                             DestIterator;

      typedef typename viennagrid::result_of::const_element_range<DestElementType, SourceTag>::type  SrcOnDestContainer;
      typedef typename viennagrid::result_of::iterator<SrcOnDestContainer>::type                     SrcOnDestIterator;

      typedef typename SourceAccessorT::value_type              value_type;

      DestContainer dest_cells(mesh_or_segment);

      // Iterate over all dest n-cells, push values from source cell to container, then compute final value
      for (DestIterator dit = dest_cells.begin(); dit != dest_cells.end(); ++dit)
      {
        if ( filter_dest(*dit) )   // only consider destination cells accepted by the filter
        {
          std::vector<value_type> destination_value_container;

          // Push all values from adjacent source cells to the container
          SrcOnDestContainer src_on_dest(*dit);
          for (SrcOnDestIterator sodit  = src_on_dest.begin();
                                  sodit != src_on_dest.end();
                                ++sodit)
          {
            if (filter_src(*sodit))
              destination_value_container.push_back(accessor_src(*dit));
          }

          //
          setter_dest(*dit, averager(destination_value_container));
        }
      }
    }

  }

  /** @brief Transfers data defined on 'source' elements to 'destination' elements. For example, values defined on cells are tranferred to vertices.
   *
   * Even though this functionality is sometimes referred to as interpolation, it is not an interpolation in the strict mathematical sense.
   *
   * @tparam SourceTypeOrTag        Topological source element or tag, e.g., cell_tag
   * @tparam DestinationTypeOrTag   Topological destination element or tag, e.g., vertex_tag
   * @param mesh_or_segment    A mesh or segment, in which the source and destination elements reside
   * @param accessor_src       An accessor functor for retrieving the data defined on each source element
   * @param setter_dest        A setter for storing the data on each destination element (first argument is the destination n-cell, second argument is the value)
   * @param averager           A functor which computes the value of the destination element from an STL-compatible container holding the values of all adjacent source elements
   * @param filter_src         A functor which returns true for all source elements considered for the transfer, false otherwise
   * @param filter_dest        A functor which returns true for all destination elements considered for the transfer, false otherwise
   */
  template <typename SourceTypeOrTag, typename DestinationTypeOrTag,
            typename MeshOrSegmentT,  typename SourceAccessorT, typename DestinationSetterT,
            typename AveragerT,       typename SourceFilterT,   typename DestinationFilterT>
  void quantity_transfer(MeshOrSegmentT const & mesh_or_segment, SourceAccessorT const & accessor_src, DestinationSetterT       & setter_dest,
                         AveragerT      const & averager,        SourceFilterT   const & filter_src,   DestinationFilterT const & filter_dest)
  {
    typedef typename viennagrid::result_of::element_tag<SourceTypeOrTag>::type       SourceTag;
    typedef typename viennagrid::result_of::element_tag<DestinationTypeOrTag>::type  DestinationTag;

    detail::quantity_transfer<SourceTag, DestinationTag>(mesh_or_segment, accessor_src, setter_dest,
                                                 averager, filter_src, filter_dest,
                                                 typename detail::quantity_transfer_dispatcher<SourceTag, DestinationTag>::type());
  }

}

#endif
