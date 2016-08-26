#ifndef VIENNAGRID_ALGORITHM_EXTRACT_SEED_POINTS_HPP
#define VIENNAGRID_ALGORITHM_EXTRACT_SEED_POINTS_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include "viennagrid/algorithm/centroid.hpp"
#include "viennagrid/mesh/neighbor_iteration.hpp"

/** @file viennagrid/algorithm/extract_seed_points.hpp
    @brief Extraction of seed points per segment of a mesh.
*/

namespace viennagrid
{
  namespace detail
  {
    /** @brief For internal use only. */
    template<typename MeshT, typename UnvisitedCellMapT>
    void neighbor_mark( MeshT const & mesh, UnvisitedCellMapT & unvisitied_cells )
    {
      bool found = true;
      while (found)
      {
        found = false;

        for (typename UnvisitedCellMapT::iterator ucit = unvisitied_cells.begin(); ucit != unvisitied_cells.end(); )
        {
          typedef typename viennagrid::result_of::cell_tag<MeshT>::type CellTagType;
          typedef typename viennagrid::result_of::facet_tag<MeshT>::type FacetTagType;
          typedef typename viennagrid::result_of::const_neighbor_range<MeshT, CellTagType, FacetTagType>::type NeighborRangeType;
          typedef typename viennagrid::result_of::iterator<NeighborRangeType>::type NeighborIteratorType;

          NeighborRangeType neighbors( mesh, ucit->second );
          NeighborIteratorType ncit = neighbors.begin();
          for (; ncit != neighbors.end(); ++ncit)
          {
            typename UnvisitedCellMapT::iterator ucit2 = unvisitied_cells.find( ncit->id() );
            if (ucit2 == unvisitied_cells.end())
              break;
          }

          if (ncit != neighbors.end())
          {
            found = true;
            unvisitied_cells.erase( ucit++ );
          }
          else
            ++ucit;
        }
      }
    }
  }

  /** @brief Extracts seed points of a mesh. For each connected part of the mesh, a point which is inside this part is added to the seed_points container.
   *
   * @param mesh                    The input mesh
   * @param seed_points             A container of seed points. The container has to support .push_back() for points of the mesh.
   */
  template<typename MeshSegmentT, typename SeedPointContainerT>
  void extract_seed_points( MeshSegmentT const & mesh, SeedPointContainerT & seed_points )
  {
    typedef typename viennagrid::result_of::cell_id<MeshSegmentT>::type CellIDType;
    typedef typename viennagrid::result_of::const_cell_handle<MeshSegmentT>::type ConstCellHandleType;

    typedef typename viennagrid::result_of::const_cell_range<MeshSegmentT>::type CellRangeType;
    typedef typename viennagrid::result_of::iterator<CellRangeType>::type CellIteratorType;

    CellRangeType cells(mesh);

    if (!cells.empty())
    {
      typedef std::map<CellIDType, ConstCellHandleType> UnvisitedCellMapType;
      UnvisitedCellMapType unvisited_cells;

      for (CellIteratorType cit = cells.begin(); cit != cells.end(); ++cit)
        unvisited_cells[ cit->id() ] = cit.handle();

      while (!unvisited_cells.empty())
      {
        for (CellIteratorType cit = cells.begin(); cit != cells.end(); ++cit)
        {
          typename UnvisitedCellMapType::iterator ucit = unvisited_cells.find( cit->id() );
          if (ucit == unvisited_cells.end())
            continue;

          seed_points.push_back( viennagrid::centroid(*cit) );
          unvisited_cells.erase( ucit );

          neighbor_mark( mesh, unvisited_cells );
        }
      }
    }
  }

  /** @brief Extracts seed points of a mesh with segmentation. For each segment, seed points are extracted.
   *
   * @param mesh                    The input mesh
   * @param segmentation            The input segmentation
   * @param seed_points             A container of seed points and segment ids. The container has to support .push_back() for std::pair<MeshPointType,int>
   */
  template<typename MeshT, typename SegmentationT, typename SeedPointContainerT>
  void extract_seed_points( MeshT const & mesh, SegmentationT const & segmentation, SeedPointContainerT & seed_points )
  {
    typedef typename viennagrid::result_of::point<MeshT>::type PointType;

    if (segmentation.empty())
    {
      std::vector<PointType> points;
      extract_seed_points(mesh, points);
      for (unsigned int i = 0; i < points.size(); ++i)
        seed_points.push_back( std::make_pair(points[i], 0) );
    }
    else
    {
      for (typename SegmentationT::const_iterator sit = segmentation.begin(); sit != segmentation.end(); ++sit)
      {
        std::vector<PointType> points;
        extract_seed_points( *sit, points );
        for (unsigned int i = 0; i < points.size(); ++i)
          seed_points.push_back( std::make_pair(points[i], sit->id()) );
      }
    }
  }
}


#endif
