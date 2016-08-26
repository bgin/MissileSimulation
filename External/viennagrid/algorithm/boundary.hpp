#ifndef VIENNAGRID_ALGORITHM_BOUNDARY_HPP
#define VIENNAGRID_ALGORITHM_BOUNDARY_HPP

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
#include "viennagrid/element/element.hpp"
#include "viennagrid/accessor.hpp"
#include "viennagrid/mesh/segmentation.hpp"


/** @file viennagrid/algorithm/boundary.hpp
    @brief Contains functions for detecting and querying boundary information
*/


namespace viennagrid
{
  namespace detail
  {

    /** @brief For internal use only. */
    template <typename MeshT, typename AccessorT>
    void detect_boundary(MeshT & mesh_obj, AccessorT boundary_info_accessor)
    {
      typedef typename viennagrid::result_of::cell_tag<MeshT>::type CellTag;
      typedef typename viennagrid::result_of::facet_tag<CellTag>::type FacetTag;

      typedef typename viennagrid::result_of::element<MeshT, CellTag>::type     CellType;

      typedef typename viennagrid::result_of::element_range<MeshT, FacetTag>::type      FacetRange;
      typedef typename viennagrid::result_of::iterator<FacetRange>::type                                           FacetIterator;

      typedef typename viennagrid::result_of::element_range<MeshT, CellTag>::type        CellRange;
      typedef typename viennagrid::result_of::iterator<CellRange>::type                                            CellIterator;

      typedef typename viennagrid::result_of::element_range<CellType, FacetTag>::type     FacetOnCellRange;
      typedef typename viennagrid::result_of::iterator<FacetOnCellRange>::type                           FacetOnCellIterator;


      FacetRange facets(mesh_obj);

      for (FacetIterator fit = facets.begin();
            fit != facets.end();
            ++fit)
          boundary_info_accessor(*fit) = false;

      //iterate over all cells, over facets there and tag them:
      CellRange cells(mesh_obj);
      for (CellIterator cit = cells.begin();
            cit != cells.end();
            ++cit)
      {
        FacetOnCellRange facets_on_cell(*cit);
        for (FacetOnCellIterator focit = facets_on_cell.begin();
              focit != facets_on_cell.end();
              ++focit)
              boundary_info_accessor(*focit) = !boundary_info_accessor(*focit);
      }
    }



    /** @brief For internal use only. */
    template <typename MeshT, typename SourceAccessorT, typename DestinationAccessorT>
    void transfer_boundary_information(MeshT const & mesh_obj,
                         SourceAccessorT const source_boundary_info_accessor,
                         DestinationAccessorT destination_boundary_info_accessor
                        )
    {
      typedef typename SourceAccessorT::access_type src_element_type;
      typedef typename DestinationAccessorT::access_type dst_element_type;

      typedef typename viennagrid::result_of::const_element_range< MeshT, dst_element_type >::type dst_range_type;
      typedef typename viennagrid::result_of::iterator< dst_range_type >::type dst_range_iterator;

      dst_range_type dst_elements(mesh_obj);

      for (dst_range_iterator it = dst_elements.begin(); it != dst_elements.end(); ++it)
          destination_boundary_info_accessor(*it) = false;


      typedef typename viennagrid::result_of::const_element_range< MeshT, src_element_type >::type src_range_type;
      typedef typename viennagrid::result_of::iterator< src_range_type >::type src_range_iterator;

      src_range_type src_elements(mesh_obj);

      for (src_range_iterator fit = src_elements.begin();
          fit != src_elements.end();
          ++fit)
      {
        if ( source_boundary_info_accessor(*fit) )
        {
          typedef typename viennagrid::result_of::const_element_range< src_element_type, dst_element_type >::type dst_on_src_range_type;
          typedef typename viennagrid::result_of::iterator< dst_on_src_range_type >::type dst_on_src_range_iterator;

          dst_on_src_range_type dst_on_src_range(*fit);
          for (dst_on_src_range_iterator dosit = dst_on_src_range.begin(); dosit != dst_on_src_range.end(); ++dosit)
              destination_boundary_info_accessor(*dosit) = true;
        }
      }
    }




    /** @brief For internal use only. */
    template<typename MeshT>
    class boundary_setter_functor
    {
    public:
      boundary_setter_functor(MeshT & mesh_obj) : mesh_obj_(mesh_obj) {}

      template<typename something>
      void operator()( viennagrid::detail::tag<something> )
      {
        typedef typename viennagrid::result_of::element_tag< something >::type element_tag;
        typedef typename viennagrid::result_of::element< MeshT, element_tag >::type element_type;

        typedef typename viennagrid::result_of::cell_tag< MeshT >::type cell_tag;
        typedef typename viennagrid::result_of::facet_tag< cell_tag >::type facet_tag;
        typedef typename viennagrid::result_of::element< MeshT, facet_tag >::type facet_type;

        typedef typename viennagrid::detail::result_of::lookup<
                typename viennagrid::detail::result_of::lookup<
                    typename MeshT::appendix_type,
                    boundary_information_collection_tag
                  >::type,
                  facet_tag
                >::type src_boundary_information_container_wrapper_type;

          src_boundary_information_container_wrapper_type & src_boundary_information_container_wrapper = detail::boundary_information_collection<facet_tag>( mesh_obj_ );


        typedef typename viennagrid::detail::result_of::lookup<
                typename viennagrid::detail::result_of::lookup<
                    typename MeshT::appendix_type,
                    boundary_information_collection_tag
                  >::type,
                  element_tag
                >::type dst_boundary_information_container_wrapper_type;

        dst_boundary_information_container_wrapper_type & dst_boundary_information_container_wrapper = detail::boundary_information_collection<element_tag>( mesh_obj_ );

        transfer_boundary_information(mesh_obj_,
                                      viennagrid::make_field<facet_type>( src_boundary_information_container_wrapper.container ),
                                      viennagrid::make_field<element_type>( dst_boundary_information_container_wrapper.container ));

        detail::update_change_counter( mesh_obj_, dst_boundary_information_container_wrapper.change_counter );
      }
    private:

      MeshT & mesh_obj_;
    };


    /** @brief For internal use only. */
    template<typename WrappedConfigT>
    void transfer_boundary_information( mesh<WrappedConfigT> & mesh_obj)
    {
      typedef mesh<WrappedConfigT> mesh_type;
      typedef typename viennagrid::result_of::cell_tag< mesh_type >::type cell_tag;
      typedef typename viennagrid::result_of::facet_tag< cell_tag >::type facet_tag;

      typedef typename viennagrid::detail::result_of::erase<
          typename viennagrid::detail::result_of::key_typelist<
              typename viennagrid::detail::result_of::lookup<
                  typename mesh_type::appendix_type,
                  boundary_information_collection_tag
              >::type::typemap
          >::type,
          facet_tag
      >::type typelist;

      boundary_setter_functor<mesh_type> functor(mesh_obj);

      viennagrid::detail::for_each< typelist >( functor );
    }

    /** @brief For internal use only. */
    template<typename SegmentationT>
    void transfer_boundary_information( segment_handle<SegmentationT> & segment )
    { transfer_boundary_information( segment.view() ); }


    /** @brief For internal use only. */
    template<typename WrappedConfigT>
    void detect_boundary( mesh<WrappedConfigT> & mesh_obj)
    {
      typedef mesh<WrappedConfigT> mesh_type;
      typedef typename viennagrid::result_of::cell_tag< mesh_type >::type cell_tag;
      typedef typename viennagrid::result_of::facet_tag< cell_tag >::type facet_tag;

      typedef typename viennagrid::result_of::element< mesh_type, facet_tag >::type facet_type;

      typedef typename viennagrid::detail::result_of::lookup<
              typename viennagrid::detail::result_of::lookup<
                  typename mesh_type::appendix_type,
                  boundary_information_collection_tag
                >::type,
                facet_tag
              >::type boundary_information_container_wrapper_type;
      boundary_information_container_wrapper_type & boundary_information_container_wrapper = detail::boundary_information_collection<facet_tag>(mesh_obj);
      detect_boundary( mesh_obj, viennagrid::make_field<facet_type>( boundary_information_container_wrapper.container ) );

      transfer_boundary_information(mesh_obj);
      detail::update_change_counter( mesh_obj, boundary_information_container_wrapper.change_counter );
    }

    /** @brief For internal use only. */
    template<typename SegmentationT>
    void detect_boundary( segment_handle<SegmentationT> & segment )
    { detect_boundary( segment.view() ); }

    /** @brief For internal use only. */
    template <typename ElementT, typename AccessorT>
    bool is_boundary(AccessorT const boundary_info_accessor,
                     ElementT const & element)
    {
      return boundary_info_accessor(element);
    }


  }


  /** @brief Returns true if an element is located on the boundary of the mesh
   *
   * @param mesh_obj    The ViennaGrid mesh
   * @param element     The element
   */
  template <typename WrappedConfigT, typename ElementT>
  bool is_boundary(mesh<WrappedConfigT> const & mesh_obj, ElementT const & element)
  {
    typedef mesh<WrappedConfigT> mesh_type;
    typedef typename viennagrid::result_of::element_tag<ElementT>::type element_tag;

    typedef typename viennagrid::detail::result_of::lookup<
            typename viennagrid::detail::result_of::lookup<
                typename mesh_type::appendix_type,
                boundary_information_collection_tag
              >::type,
              element_tag
            >::type boundary_information_container_wrapper_type;
    boundary_information_container_wrapper_type const & boundary_information_container_wrapper = detail::boundary_information_collection<element_tag>(mesh_obj);

    if (mesh_obj.is_obsolete(boundary_information_container_wrapper.change_counter))
      detail::detect_boundary( const_cast<mesh_type&>(mesh_obj) );

    return detail::is_boundary( viennagrid::make_field<ElementT>(boundary_information_container_wrapper.container), element );
  }

  /** @brief Returns true if an element is located on the boundary of the segment
   *
   * @param segment      The ViennaGrid segment
   * @param element      The element
   */
  template <typename SegmentationT, typename ElementT>
  bool is_boundary(segment_handle<SegmentationT> const & segment, ElementT const & element)
  { return is_boundary( segment.view(), element ); }


  /** @brief Returns true if the element provided as second argument is on the boundary of the element provided as first argument
   *
   * @param host_element    The host element
   * @param element         The (potential) boundary element
   */
  template <typename ElementTag1, typename WrappedConfigT1,
            typename ElementTag2, typename WrappedConfigT2>
  bool is_boundary(viennagrid::element<ElementTag1, WrappedConfigT1> const & host_element,
                   viennagrid::element<ElementTag2, WrappedConfigT2> const & element)
  {

    typedef typename viennagrid::result_of::const_element_range<viennagrid::element<ElementTag2, WrappedConfigT2>, ElementTag1>::type   BoundaryRange;
    typedef typename viennagrid::result_of::iterator<BoundaryRange>::type               BoundaryIterator;

    BoundaryRange bnd_cells(host_element);
    for (BoundaryIterator bit = bnd_cells.begin();
                          bit != bnd_cells.end();
                        ++bit)
    {
      if (&(*bit) == &element)
        return true;
    }

    return false;
  }

}

#endif
