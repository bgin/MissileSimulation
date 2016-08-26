#ifndef VIENNAGRID_ALGORITHM_INTERFACE_HPP
#define VIENNAGRID_ALGORITHM_INTERFACE_HPP

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
#include "viennagrid/algorithm/norm.hpp"
#include "viennagrid/algorithm/centroid.hpp"
#include "viennagrid/algorithm/boundary.hpp"

/** @file viennagrid/algorithm/interface.hpp
    @brief Provides the detection and check for boundary n-cells at the interface of two segments.
*/


namespace viennagrid
{
  namespace detail
  {
    /** @brief For internal use only. */
    template< bool BoundaryStorageB>
    struct detect_interface_impl;

    template<>
    struct detect_interface_impl<false>
    {
      template <typename AccessorT, typename MeshT1, typename MeshT2>
      static void detect(AccessorT,
                        MeshT1 const &,
                        MeshT2 const &)
      {
        typename MeshT1::ERROR_CANNOT_DETECT_INTERFACE_BECAUSE_FACETS_ARE_DISABLED error_obj;
        (void)error_obj;
      }
    };

    template<>
    struct detect_interface_impl<true>
    {
      template <typename AccessorT, typename MeshT1, typename MeshT2>
      static void detect(AccessorT accessor,
                        MeshT1 const & seg0,
                        MeshT2 const & seg1)
      {
        typedef typename viennagrid::result_of::cell_tag<MeshT1>::type CellTag;
        typedef typename viennagrid::result_of::element<MeshT1, typename CellTag::facet_tag>::type   FacetType;
        typedef typename viennagrid::result_of::const_handle<MeshT1, typename CellTag::facet_tag>::type   ConstFacetHandleType;

        typedef typename viennagrid::result_of::const_element_range<MeshT1, typename CellTag::facet_tag>::type      FacetRange;
        typedef typename viennagrid::result_of::iterator<FacetRange>::type                                           FacetIterator;

        std::set<ConstFacetHandleType>  facets_ptrs_seg0;

        //
        // Step 1: Write facets of segment 1 to a map:
        //
        FacetRange facets_seg0(seg0);
        for (FacetIterator fit = facets_seg0.begin();
              fit != facets_seg0.end();
              ++fit)
        {
          const FacetType & facet = *fit;

          if (is_boundary(seg0, facet))
            facets_ptrs_seg0.insert( fit.handle() );
        }

        //
        // Step 2: Compare facet in segment 2 with those stored in the map
        //
        FacetRange facets_seg1(seg1);
        for (FacetIterator fit = facets_seg1.begin();
              fit != facets_seg1.end();
              ++fit)
        {
          const FacetType & facet = *fit;

          if (facets_ptrs_seg0.find( fit.handle() ) != facets_ptrs_seg0.end()) accessor(facet) = true;
        }

      }
    };


    /** @brief For internal use only. */
    template<typename SegmentationT>
    class interface_setter_functor
    {
    public:
      typedef segment_handle<SegmentationT> SegmentHandleType;

      interface_setter_functor(SegmentHandleType & seg0_, SegmentHandleType & seg1_) : seg0(seg0_), seg1(seg1_) {}

      template<typename something>
      void operator()( viennagrid::detail::tag<something> )
      {
        typedef typename viennagrid::result_of::element_tag< something >::type element_tag;
        typedef typename viennagrid::result_of::element< SegmentHandleType, element_tag >::type element_type;

        typedef typename viennagrid::result_of::cell_tag< SegmentHandleType >::type cell_tag;
        typedef typename viennagrid::result_of::facet_tag< cell_tag >::type facet_tag;
        typedef typename viennagrid::result_of::element< SegmentHandleType, facet_tag >::type facet_type;

        typedef typename viennagrid::detail::result_of::lookup<
                typename viennagrid::detail::result_of::lookup<
                    typename SegmentationT::appendix_type,
                    interface_information_collection_tag
                  >::type,
                  facet_tag
                >::type::segment_interface_information_wrapper_type src_interface_information_container_wrapper_type;

          src_interface_information_container_wrapper_type & src_interface_information_container_wrapper = interface_information_collection<facet_tag>( seg0, seg1 );
    //             viennagrid::dense_container_accessor_t< const typename src_interface_information_container_wrapper_type::container_type, facet_type > src_accessor( src_interface_information_container_wrapper.container );




        typedef typename viennagrid::detail::result_of::lookup<
                typename viennagrid::detail::result_of::lookup<
                    typename SegmentationT::appendix_type,
                    interface_information_collection_tag
                  >::type,
                  element_tag
                >::type::segment_interface_information_wrapper_type dst_interface_information_container_wrapper_type;

        dst_interface_information_container_wrapper_type & dst_interface_information_container_wrapper = interface_information_collection<element_tag>( seg0, seg1 );
        typename viennagrid::result_of::accessor< typename dst_interface_information_container_wrapper_type::container_type, element_type >::type dst_accessor( dst_interface_information_container_wrapper.container );

        transfer_boundary_information(seg0, viennagrid::make_field<facet_type>(src_interface_information_container_wrapper.container), dst_accessor);
        transfer_boundary_information(seg1, viennagrid::make_field<facet_type>(src_interface_information_container_wrapper.container), dst_accessor);

        detail::update_change_counter( seg0, dst_interface_information_container_wrapper.seg0_change_counter );
        detail::update_change_counter( seg1, dst_interface_information_container_wrapper.seg1_change_counter );
      }
    private:

      SegmentHandleType & seg0;
      SegmentHandleType & seg1;
    };



    /** @brief For internal use only. */
    template<typename SegmentationT>
    void transfer_interface_information( segment_handle<SegmentationT> & seg0, segment_handle<SegmentationT> & seg1 )
    {
      assert( &seg0.parent() == &seg1.parent() );

      typedef segment_handle<SegmentationT> segment_handle_type;
      typedef typename viennagrid::result_of::cell_tag< segment_handle_type >::type cell_tag;
      typedef typename viennagrid::result_of::facet_tag< cell_tag >::type facet_tag;

      typedef typename viennagrid::detail::result_of::erase<
          typename viennagrid::detail::result_of::key_typelist<
              typename viennagrid::detail::result_of::lookup<
                  typename SegmentationT::appendix_type,
                  interface_information_collection_tag
              >::type::typemap
          >::type,
          facet_tag
      >::type typelist;

      interface_setter_functor<SegmentationT> functor(seg0, seg1);

      viennagrid::detail::for_each< typelist >( functor );
    }






    /** @brief For internal use only. */
    template <typename SegmentationT, typename AccessorT>
    void detect_interface(segment_handle<SegmentationT> & seg0,
                          segment_handle<SegmentationT> & seg1,
                          AccessorT accessor)
    {
      assert( &seg0.parent() == &seg1.parent() );

      typedef typename viennagrid::result_of::cell_tag< segment_handle<SegmentationT> >::type CellTag;
      typedef typename viennagrid::result_of::element< segment_handle<SegmentationT>, CellTag>::type CellType;

      viennagrid::detail::detect_interface_impl< viennagrid::result_of::has_boundary<CellType, typename CellTag::facet_tag>::value >::detect(accessor, seg0, seg1);
    }

    /** @brief For internal use only. */
    template <typename ElementT, typename AccessorT>
    bool is_interface(AccessorT const accessor,
                      ElementT const & el)
    { return accessor(el); }


  }

  /** @brief Public interface function for the detection of interface n-cells between two segments. No need to call this function explicitly, since it is called by is_interface()
   *
   * @param seg0  The first segment
   * @param seg1  The second segment
   */
  template <typename SegmentationT>
  void detect_interface(segment_handle<SegmentationT> & seg0,
                        segment_handle<SegmentationT> & seg1)
  {
    assert( &seg0.parent() == &seg1.parent() );

    typedef typename result_of::cell_tag< segment_handle<SegmentationT> >::type CellTag;
    typedef typename result_of::facet_tag<CellTag>::type FacetTag;
    typedef typename result_of::element< segment_handle<SegmentationT>, FacetTag >::type FacetType;

    typedef typename viennagrid::detail::result_of::lookup<
            typename viennagrid::detail::result_of::lookup<
                typename SegmentationT::appendix_type,
                interface_information_collection_tag
              >::type,
              FacetTag
            >::type::segment_interface_information_wrapper_type interface_information_container_wrapper_type;
    interface_information_container_wrapper_type & interface_information_container_wrapper = detail::interface_information_collection<FacetTag>( seg0, seg1 );


    detail::detect_interface( seg0, seg1, viennagrid::make_field<FacetType>(interface_information_container_wrapper.container) );

    transfer_interface_information( seg0, seg1 );
    detail::update_change_counter( seg0, interface_information_container_wrapper.seg0_change_counter );
    detail::update_change_counter( seg1, interface_information_container_wrapper.seg1_change_counter );
  }



  /** @brief Returns true if the n-cell is located at the interface between two segments
   *
   * @param seg0      The first segment
   * @param seg1      The sevond segment
   * @param element   The element under test
   */
  template <typename SegmentationT, typename ElementT>
  bool is_interface(segment_handle<SegmentationT> const & seg0,
                    segment_handle<SegmentationT> const & seg1,
                    ElementT const & element)
  {
    assert( &seg0.parent() == &seg1.parent() );

    typedef segment_handle<SegmentationT> SegmentHandleType;

    typedef typename viennagrid::result_of::element_tag<ElementT>::type element_tag;


    typedef typename viennagrid::detail::result_of::lookup<
            typename viennagrid::detail::result_of::lookup<
                typename SegmentationT::appendix_type,
                interface_information_collection_tag
              >::type,
              element_tag
            >::type::segment_interface_information_wrapper_type interface_information_container_wrapper_type;
    interface_information_container_wrapper_type const & interface_information_container_wrapper = detail::interface_information_collection<element_tag>( seg0, seg1 );

    if ( (detail::is_obsolete(seg0, interface_information_container_wrapper.seg0_change_counter)) ||
         (detail::is_obsolete(seg1, interface_information_container_wrapper.seg1_change_counter) ))
        detect_interface( const_cast<SegmentHandleType&>(seg0), const_cast<SegmentHandleType&>(seg1) );

    return detail::is_interface( viennagrid::make_field<ElementT>(interface_information_container_wrapper.container), element );
  }

}

#endif
