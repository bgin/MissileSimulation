#ifndef VIENNAGRID_ALGORITHM_EXTRACT_BOUNDARY_HPP
#define VIENNAGRID_ALGORITHM_EXTRACT_BOUNDARY_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include "viennagrid/mesh/element_creation.hpp"
#include "viennagrid/mesh/mesh_operations.hpp"
#include "viennagrid/algorithm/boundary.hpp"

/** @file viennagrid/algorithm/extract_boundary.hpp
    @brief Extraction of a hull/boundary of a mesh.
*/

namespace viennagrid
{
  /** @brief Extracts the hull of mesh using viennagrid::boundary, e.g. the triangular hull of a tetrahedral mesh.
   *
   * @tparam HullTypeOrTagT                The type or tag of the hull element
   * @param volume_mesh                    The input mesh
   * @param hull_mesh                      The output hull mesh
   */
  template<typename HullTypeOrTagT, typename VolumeMeshT, typename HullMeshT>
  void extract_boundary(VolumeMeshT const & volume_mesh,
                        HullMeshT & hull_mesh)
  {
    viennagrid::clear(hull_mesh);

    typedef typename viennagrid::result_of::point<VolumeMeshT>::type            VolumePointType;

    typedef typename viennagrid::result_of::const_element_range<VolumeMeshT, HullTypeOrTagT>::type    HullRangeType;
    typedef typename viennagrid::result_of::iterator<HullRangeType>::type                                   HullRangeIterator;

    typedef typename viennagrid::result_of::element<VolumeMeshT, HullTypeOrTagT>::type    VolumeHullElement;
    typedef typename viennagrid::result_of::element<HullMeshT, HullTypeOrTagT>::type      HullHullElement;

    viennagrid::vertex_copy_map<VolumeMeshT, HullMeshT> vertex_map(hull_mesh);

    HullRangeType hull_elements( volume_mesh );
    for (HullRangeIterator hit = hull_elements.begin(); hit != hull_elements.end(); ++hit)
    {
      VolumeHullElement const & hull_element = *hit;

      if ( viennagrid::is_boundary( volume_mesh, hull_element ) )
      {
        typedef typename viennagrid::result_of::vertex_handle<HullMeshT>::type HullVertexHandleType;

        std::vector<HullVertexHandleType> vertices( viennagrid::vertices(hull_element).size() );
        for (std::size_t i = 0; i < viennagrid::vertices(hull_element).size(); ++i)
          vertices[i] = vertex_map(viennagrid::vertices(hull_element)[i]);

        viennagrid::make_element<HullHullElement>( hull_mesh, vertices.begin(), vertices.end() );
      }
    }
  }

  /** @brief Extracts the hull of mesh using viennagrid::boundary, e.g. the triangular hull of a tetrahedral mesh. The facet type is used as the hull element type.
   *
   * @param volume_mesh                    The input mesh
   * @param hull_mesh                      The output hull mesh
   */
  template<typename VolumeMeshT, typename HullMeshT>
  void extract_boundary(VolumeMeshT const & volume_mesh,
                        HullMeshT & hull_mesh )
  {
    typedef typename viennagrid::result_of::facet_tag<VolumeMeshT>::type FacetTag;
    extract_boundary<FacetTag>(volume_mesh, hull_mesh);
  }


  /** @brief Extracts the hull of mesh and a segmentation using viennagrid::boundary, e.g. the triangular hull of a tetrahedral mesh.
   *
   * @tparam HullTypeOrTagT                The type or tag of the hull element
   * @param volume_mesh                    The input mesh
   * @param volume_segmentation            The input segmentation
   * @param hull_mesh                      The output hull mesh
   * @param hull_segmentation              The output hull segmentation
   */
  template<typename HullTypeOrTagT, typename VolumeMeshT, typename VolumeSegmentationT, typename HullMeshT, typename HullSegmentationT>
  void extract_boundary(VolumeMeshT const & volume_mesh,
                        VolumeSegmentationT const & volume_segmentation,
                        HullMeshT & hull_mesh,
                        HullSegmentationT & hull_segmentation )
  {
    typedef typename viennagrid::result_of::element_tag<HullTypeOrTagT>::type HullTagType;

    viennagrid::clear(hull_mesh);
    viennagrid::clear(hull_segmentation);

    if (volume_segmentation.size() == 0)
      extract_boundary<HullTagType>(volume_mesh, hull_mesh);

    typedef typename viennagrid::result_of::segment_handle<VolumeSegmentationT>::type    VolumeSegmentHandleType;
    typedef typename viennagrid::result_of::point<VolumeMeshT>::type            VolumePointType;

    typedef typename viennagrid::result_of::segment_handle<HullSegmentationT>::type      HullSegmentHandleType;


    typedef typename viennagrid::result_of::element<VolumeSegmentHandleType, HullTagType>::type    VolumeHullElementType;
    typedef typename viennagrid::result_of::element<HullSegmentHandleType, HullTagType>::type     HullCellElementType;

    typedef typename viennagrid::result_of::id<VolumeHullElementType>::type VolumeHullElementIDType;
    typedef typename viennagrid::result_of::handle<HullSegmentHandleType, HullTagType>::type HullCellElementHandleType;

    typedef typename viennagrid::result_of::vertex_id<VolumeMeshT>::type VolumeVertexIDType;
    typedef typename viennagrid::result_of::vertex_handle<HullSegmentHandleType>::type HullVertexHandleType;

    viennagrid::vertex_copy_map<VolumeMeshT, HullMeshT> vertex_map(hull_mesh);
    std::map< VolumeHullElementIDType, HullCellElementHandleType > hull_element_map;

    for (typename VolumeSegmentationT::const_iterator sit = volume_segmentation.begin(); sit != volume_segmentation.end(); ++sit)
    {
      VolumeSegmentHandleType const & volume_segment = *sit;
      HullSegmentHandleType & hull_segment = hull_segmentation( volume_segment.id() );

      typedef typename viennagrid::result_of::const_element_range<VolumeSegmentHandleType, HullTagType>::type    HullRangeType;
      typedef typename viennagrid::result_of::iterator<HullRangeType>::type                                   HullRangeIterator;

      HullRangeType hull_elements( volume_segment );
      for (HullRangeIterator hit = hull_elements.begin(); hit != hull_elements.end(); ++hit)
      {
        VolumeHullElementType const & hull_element = *hit;

        if ( viennagrid::is_boundary( volume_segment, hull_element ) )
        {
          typename std::map< VolumeHullElementIDType, HullCellElementHandleType >::iterator hemit = hull_element_map.find( hit->id() );
          if ( hemit != hull_element_map.end() )
          {
            viennagrid::add( hull_segment, viennagrid::dereference_handle(hull_segment, hemit->second) );
          }
          else
          {
            typedef typename viennagrid::result_of::const_vertex_range<VolumeHullElementType>::type ConstVertexOnHullElementRangeType;
            typedef typename viennagrid::result_of::iterator<ConstVertexOnHullElementRangeType>::type ConstVertexOnHullElementIteratorType;

            ConstVertexOnHullElementRangeType vertices_on_hull_element( hull_element );
            std::vector<HullVertexHandleType> vertex_handles;

            for (ConstVertexOnHullElementIteratorType vit = vertices_on_hull_element.begin(); vit != vertices_on_hull_element.end(); ++vit)
              vertex_handles.push_back( vertex_map(*vit) );

            hull_element_map[hit->id()] = viennagrid::make_element<HullCellElementType>( hull_segment, vertex_handles.begin(), vertex_handles.end() );
          }
        }
      }
    }
  }


  /** @brief Extracts the hull of mesh and a segmentation using viennagrid::boundary, e.g. the triangular hull of a tetrahedral mesh. The facet type is used as the hull element type.
   *
   * @param volume_mesh                    The input mesh
   * @param volume_segmentation            The input segmentation
   * @param hull_mesh                      The output hull mesh
   * @param hull_segmentation              The output hull segmentation
   */
  template<typename VolumeMeshT, typename VolumeSegmentationT, typename HullMeshT, typename HullSegmentationT>
  void extract_boundary(VolumeMeshT const & volume_mesh,
                        VolumeSegmentationT const & volume_segmentation,
                        HullMeshT & hull_mesh,
                        HullSegmentationT & hull_segmentation )
  {
    typedef typename viennagrid::result_of::facet_tag<VolumeMeshT>::type FacetTag;
    extract_boundary<FacetTag>(volume_mesh, volume_segmentation, hull_mesh, hull_segmentation);
  }
}

#endif
