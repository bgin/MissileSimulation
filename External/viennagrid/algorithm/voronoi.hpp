#ifndef VIENNAGRID_ALGORITHM_VORONOI_HPP
#define VIENNAGRID_ALGORITHM_VORONOI_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "viennagrid/forwards.hpp"
#include "viennagrid/mesh/segmentation.hpp"
#include "viennagrid/mesh/coboundary_iteration.hpp"
#include "viennagrid/algorithm/circumcenter.hpp"
#include "viennagrid/algorithm/spanned_volume.hpp"
#include "viennagrid/algorithm/volume.hpp"
#include "viennagrid/algorithm/inner_prod.hpp"


/** @file viennagrid/algorithm/voronoi.hpp
    @brief Computes the Voronoi information for a Delaunay triangulation.
*/


namespace viennagrid
{
  namespace result_of
  {
    /** @brief Returns the internal type used for the individual Voronoi quantity contributions.
      *
      * @tparam ConstCellHandleT    The handle type for cells used as key for the container
      */
    template <typename ConstCellHandleT>
    struct voronoi_cell_contribution
    {
      typedef std::vector< std::pair<ConstCellHandleT, double> >   type;
    };
  }


  namespace detail
  {
    /** @brief Adds a pair [CellPtr, contribution] to the Voronoi quantities stored in the container. If data for the particular Cell are already stored, no new element is inserted, but existing 'contribution' is updated.
     */
    template <typename ContainerT, typename PairT>
    void voronoi_unique_quantity_update(ContainerT & container,
                                        PairT const & update_pair)
    {
      bool found = false;
      for (typename ContainerT::iterator it = container.begin();
                                            it != container.end();
                                          ++it)
      {
        if (it->first == update_pair.first)
        {
          it->second += update_pair.second;
          found = true;
          break;
        }
      }

      if (!found)
      {
        container.push_back(update_pair);
      }
    }


    /** @brief Implementation of the computation of Voronoi quantities for a one-dimensional mesh (line, 1-simplex) */
    template <typename CellTag,
              typename MeshT,
              typename InterfaceAreaAccessorT,
              typename InterfaceAreaCellContributionAccessorT,
              typename VertexBoxVolumeAccessorT,
              typename VertexBoxVolumeCellContributionAccessorT,
              typename EdgeBoxVolumeAccessorT,
              typename EdgeBoxVolumeCellContributionAccessorT>
    void write_voronoi_info(MeshT const & mesh_obj,
                            InterfaceAreaAccessorT interface_area_accessor,
                            InterfaceAreaCellContributionAccessorT interface_area_cell_contribution_accessor,
                            VertexBoxVolumeAccessorT vertex_box_volume_accessor,
                            VertexBoxVolumeCellContributionAccessorT vertex_box_volume_cell_contribution_accessor,
                            EdgeBoxVolumeAccessorT edge_box_volume_accessor,
                            EdgeBoxVolumeCellContributionAccessorT edge_box_volume_cell_contribution_accessor,
                            viennagrid::simplex_tag<1>)
    {
      typedef typename viennagrid::result_of::element<MeshT, CellTag>::type                 CellType;

      typedef typename viennagrid::result_of::element<MeshT, vertex_tag>::type              VertexType;

      typedef typename viennagrid::result_of::const_element_range<MeshT, CellTag>::type     CellRange;
      typedef typename viennagrid::result_of::iterator<CellRange>::type                        CellIterator;


      typedef typename viennagrid::result_of::const_element_range<CellType, vertex_tag>::type  VertexOnCellRange;
      typedef typename viennagrid::result_of::iterator<VertexOnCellRange>::type                VertexOnCellIterator;

      //
      // Write Voronoi information
      //

      CellRange cells = viennagrid::elements<CellTag>(mesh_obj);
      for (CellIterator cit  = cells.begin();
                        cit != cells.end();
                      ++cit)
      {
        interface_area_accessor(*cit) = 1;
        interface_area_cell_contribution_accessor(*cit).push_back( std::make_pair( cit.handle(), 1) );

        double edge_contribution = 0;
        VertexOnCellRange vertices_on_cell = viennagrid::elements<VertexType>(*cit);
        for (VertexOnCellIterator vocit  = vertices_on_cell.begin();
                                  vocit != vertices_on_cell.end();
                                ++vocit)
        {
          double contribution = volume(*cit) / 2.0;
          edge_contribution += contribution;

          vertex_box_volume_accessor(*vocit) += contribution;
          vertex_box_volume_cell_contribution_accessor(*vocit).push_back( std::make_pair( cit.handle(), contribution) );
        }

        edge_box_volume_accessor(*cit) = edge_contribution;
        edge_box_volume_cell_contribution_accessor(*cit).push_back( std::make_pair( cit.handle(), edge_contribution) );

      }
    }

    /** @brief Implementation of the computation of Voronoi quantities for a one-dimensional mesh (line, 1-hypercube) */
    template <typename CellTag,
              typename MeshT,
              typename InterfaceAreaAccessorT,
              typename InterfaceAreaCellContributionAccessorT,
              typename VertexBoxVolumeAccessorT,
              typename VertexBoxVolumeCellContributionAccessorT,
              typename EdgeBoxVolumeAccessorT,
              typename EdgeBoxVolumeCellContributionAccessorT>
    void write_voronoi_info(MeshT const & mesh_obj,
                            InterfaceAreaAccessorT interface_area_accessor,
                            InterfaceAreaCellContributionAccessorT interface_area_cell_contribution_accessor,
                            VertexBoxVolumeAccessorT vertex_box_volume_accessor,
                            VertexBoxVolumeCellContributionAccessorT vertex_box_volume_cell_contribution_accessor,
                            EdgeBoxVolumeAccessorT edge_box_volume_accessor,
                            EdgeBoxVolumeCellContributionAccessorT edge_box_volume_cell_contribution_accessor,
                            viennagrid::hypercube_tag<1>)
    {
        write_voronoi_info<CellTag>(mesh_obj,
                                    interface_area_accessor, interface_area_cell_contribution_accessor,
                                    vertex_box_volume_accessor, vertex_box_volume_cell_contribution_accessor,
                                    edge_box_volume_accessor, edge_box_volume_cell_contribution_accessor,
                                    viennagrid::simplex_tag<1>());
    }

    //
    // Voronoi information in two (topological) dimensions
    //
    /** @brief Implementation of the computation of Voronoi quantities for a quadrilateral mesh */
    template <typename CellTag,
              typename MeshT,
              typename InterfaceAreaAccessorT,
              typename InterfaceAreaCellContributionAccessorT,
              typename VertexBoxVolumeAccessorT,
              typename VertexBoxVolumeCellContributionAccessorT,
              typename EdgeBoxVolumeAccessorT,
              typename EdgeBoxVolumeCellContributionAccessorT>
    void write_voronoi_info(MeshT const & mesh_obj,
                            InterfaceAreaAccessorT interface_area_accessor,
                            InterfaceAreaCellContributionAccessorT interface_area_cell_contribution_accessor,
                            VertexBoxVolumeAccessorT vertex_box_volume_accessor,
                            VertexBoxVolumeCellContributionAccessorT vertex_box_volume_cell_contribution_accessor,
                            EdgeBoxVolumeAccessorT edge_box_volume_accessor,
                            EdgeBoxVolumeCellContributionAccessorT edge_box_volume_cell_contribution_accessor,
                            viennagrid::quadrilateral_tag)
    {
      typedef typename viennagrid::result_of::element<MeshT, CellTag>::type CellType;

      typedef typename viennagrid::result_of::point<MeshT>::type                            PointType;
      typedef typename viennagrid::result_of::element<MeshT, vertex_tag>::type              VertexType;
      typedef typename viennagrid::result_of::element<MeshT, line_tag>::type                EdgeType;

      typedef typename viennagrid::result_of::const_element_range<MeshT, CellTag>::type     CellRange;
      typedef typename viennagrid::result_of::iterator<CellRange>::type                        CellIterator;

      typedef typename viennagrid::result_of::const_element_range<CellType, line_tag>::type    EdgeOnCellRange;
      typedef typename viennagrid::result_of::iterator<EdgeOnCellRange>::type                  EdgeOnCellIterator;

      typedef typename viennagrid::result_of::const_element_range<EdgeType, vertex_tag>::type  VertexOnEdgeRange;
      typedef typename viennagrid::result_of::iterator<VertexOnEdgeRange>::type                VertexOnEdgeIterator;


      //
      // Algorithm: Iterate over all cells, compute circumcenter and add interface area to edge, box volume to vertex.
      //

      CellRange cells = viennagrid::elements<CellTag>(mesh_obj);
      for (CellIterator cit  = cells.begin();
                        cit != cells.end();
                      ++cit)
      {
        PointType circ_center = circumcenter(*cit);

        //iterate over edges:
        EdgeOnCellRange edges_on_cell = viennagrid::elements<EdgeType>(*cit);
        for (EdgeOnCellIterator eocit  = edges_on_cell.begin();
                                eocit != edges_on_cell.end();
                              ++eocit)
        {
          PointType edge_midpoint = circumcenter(*eocit);

          // interface contribution:
          double interface_contribution = spanned_volume(circ_center, edge_midpoint);

          interface_area_accessor(*eocit) += interface_contribution;
          interface_area_cell_contribution_accessor(*eocit).push_back( std::make_pair( cit.handle(), interface_contribution) );

          //box volume contribution:
          double edge_contribution = 0;
          VertexOnEdgeRange vertices_on_edge = viennagrid::elements<VertexType>(*eocit);
          for (VertexOnEdgeIterator voeit  = vertices_on_edge.begin();
                                    voeit != vertices_on_edge.end();
                                  ++voeit)
          {
            double contribution = spanned_volume(circ_center, edge_midpoint, viennagrid::point(*voeit));
            edge_contribution += contribution;

            vertex_box_volume_accessor(*voeit) += contribution;
            vertex_box_volume_cell_contribution_accessor(*voeit).push_back( std::make_pair( cit.handle(), contribution) );
          }

          edge_box_volume_accessor(*eocit) += edge_contribution;
          edge_box_volume_cell_contribution_accessor(*eocit).push_back( std::make_pair( cit.handle(), edge_contribution) );

        } //for edges on cells

      } //for cells

    } //write_voronoi_info(triangle_tag)


    /** @brief Converts a point to local (barycentric) coordinates (lambda_1, lambda_2). lambda_3 = 1 - lambda_1 - lambda_2 is not stored explicitly  */
    //template <typename PointType, typename ConfigType>
    //PointType point_to_local_coordinates(PointType const & p, viennagrid::element<ConfigType, viennagrid::simplex_tag<2> > const & triangle)
    template<typename TriangleType>
    typename viennagrid::result_of::point<TriangleType>::type point_to_local_coordinates( typename viennagrid::result_of::point<TriangleType>::type const & p,
                                                                                          const TriangleType & triangle)
    {
      typedef TriangleType CellType;
      typedef typename viennagrid::result_of::const_element_range<CellType, vertex_tag>::type    VertexRange;
      typedef typename viennagrid::result_of::point<TriangleType>::type                          PointType;

      VertexRange vertices = viennagrid::elements<viennagrid::vertex_tag>(triangle);

      PointType const & a = viennagrid::point(vertices[0]);
      PointType const & b = viennagrid::point(vertices[1]);
      PointType const & c = viennagrid::point(vertices[2]);

      PointType v0 = b - a;
      PointType v1 = c - a;
      PointType vp = p - a;

      double det = v0[0] * v1[1] - v0[1] * v1[0];

      return PointType( (v1[1] * vp[0] - v1[0] * vp[1]) / det,
                        (v0[0] * vp[1] - v0[1] * vp[0]) / det  );
    }


    /** @brief Computes the intersection of the two lines [a,b] and [c,d] */
    template <typename PointType>
    PointType line_intersection(PointType const & a, PointType const & b,
                                PointType const & c, PointType const & d)
    {
      double det = (a[0] - b[0])*(c[1] - d[1]) - (a[1] - b[1])*(c[0] - d[0]);

      if (std::fabs(det) < 1e-10 * viennagrid::norm(b-a))
        std::cerr << "viennagrid::detail::line_intersection(): Warning: Determinant is close to zero!" << std::endl;

      double px =   (a[0]*b[1] - a[1]*b[0]) * (c[0] - d[0])
                  - (a[0] - b[0]) * (c[0]*d[1] - c[1]*d[0]);
      double py =   (a[0]*b[1] - a[1]*b[0]) * (c[1] - d[1])
                  - (a[1] - b[1]) * (c[0]*d[1] - c[1]*d[0]);

      return PointType(px / det, py / det);
    }


    /** @brief Implementation of the computation of Voronoi quantities for a triangular mesh */
    template <typename CellTag,
              typename MeshT,
              typename InterfaceAreaAccessorT,
              typename InterfaceAreaCellContributionAccessorT,
              typename VertexBoxVolumeAccessorT,
              typename VertexBoxVolumeCellContributionAccessorT,
              typename EdgeBoxVolumeAccessorT,
              typename EdgeBoxVolumeCellContributionAccessorT>
    void write_voronoi_info(MeshT const & mesh_obj,
                            InterfaceAreaAccessorT                   interface_area_accessor,
                            InterfaceAreaCellContributionAccessorT   interface_area_cell_contribution_accessor,
                            VertexBoxVolumeAccessorT                 vertex_box_volume_accessor,
                            VertexBoxVolumeCellContributionAccessorT vertex_box_volume_cell_contribution_accessor,
                            EdgeBoxVolumeAccessorT                   edge_box_volume_accessor,
                            EdgeBoxVolumeCellContributionAccessorT   edge_box_volume_cell_contribution_accessor,
                            viennagrid::triangle_tag)
    {
      typedef typename viennagrid::result_of::element<MeshT, CellTag>::type             CellType;
      typedef typename viennagrid::result_of::const_handle<MeshT, CellTag>::type        ConstCellHandleType;

      typedef typename viennagrid::result_of::point<MeshT>::type                        PointType;
      typedef typename viennagrid::result_of::element<MeshT, vertex_tag>::type          VertexType;
      typedef typename viennagrid::result_of::element<MeshT, line_tag>::type            EdgeType;

      typedef typename viennagrid::result_of::const_element_range<MeshT, CellTag>::type CellRange;
      typedef typename viennagrid::result_of::iterator<CellRange>::type                    CellIterator;

      typedef typename viennagrid::result_of::const_element_range<CellType, vertex_tag>::type           VertexOnCellRange;

      typedef typename viennagrid::result_of::const_coboundary_range<MeshT, EdgeType, CellTag>::type CellOnEdgeRange;

//       typedef typename viennagrid::result_of::const_element_range<EdgeType, CellTag>::type           CellOnEdgeRange;
      typedef typename viennagrid::result_of::iterator<CellOnEdgeRange>::type                           CellOnEdgeIterator;

      typedef typename viennagrid::result_of::const_element_range<CellType, line_tag>::type             EdgeOnCellRange;
      typedef typename viennagrid::result_of::iterator<EdgeOnCellRange>::type                           EdgeOnCellIterator;

      typedef typename viennagrid::result_of::const_element_range<EdgeType, vertex_tag>::type           VertexOnEdgeRange;
      typedef typename viennagrid::result_of::iterator<VertexOnEdgeRange>::type                         VertexOnEdgeIterator;

      CellRange cells = viennagrid::elements<CellTag>(mesh_obj);
      for (CellIterator cit  = cells.begin();
                        cit != cells.end();
                      ++cit)
      {
        PointType circ_center = circumcenter(*cit);


        PointType circ_center_local = point_to_local_coordinates(circ_center, *cit);

        if (    (circ_center_local[0] < 0)
             || (circ_center_local[1] < 0)
             || (circ_center_local[0] + circ_center_local[1] > 1.0) )   //circumcenter is outside triangle - things get complicated
        {
          EdgeOnCellRange edges_on_cell = viennagrid::elements<EdgeType>(*cit);
          VertexOnCellRange vertices_on_cell = viennagrid::elements<VertexType>(*cit);

          //
          // Step 1: Get intersected edge, find opposite vertex and the 'other' triangle
          //
          EdgeType const * intersected_edge_ptr = NULL;
          VertexType const * opposite_vertex_ptr = NULL;
          if (circ_center_local[1] < 0)
          {
            intersected_edge_ptr = &(edges_on_cell[0]);
            opposite_vertex_ptr = &(vertices_on_cell[2]);
          }
          else if (circ_center_local[0] < 0)
          {
            intersected_edge_ptr = &(edges_on_cell[1]);
            opposite_vertex_ptr = &(vertices_on_cell[1]);
          }
          else
          {
            intersected_edge_ptr = &(edges_on_cell[2]);
            opposite_vertex_ptr = &(vertices_on_cell[0]);
          }

          //find 'other' triangle
          ConstCellHandleType other_cell;

//           CellType const * other_cell = NULL;
          CellOnEdgeRange other_cells = viennagrid::coboundary_elements<EdgeType, CellTag>(mesh_obj, viennagrid::handle(mesh_obj, *intersected_edge_ptr) );
          detail::set_handle_invalid( other_cells, other_cell );

          for (CellOnEdgeIterator coeit  = other_cells.begin();
                                  coeit != other_cells.end();
                                ++coeit)
          {
            if ( coeit->id() != cit->id() )
            {
              other_cell = coeit.handle();
              break;
            }
          }

          //
          // Step 2: Precompute intersection of opposite vertex with intersected edge
          //
          VertexOnEdgeRange vertices_on_intersected_edge = viennagrid::elements<VertexType>(*intersected_edge_ptr);
          PointType opposite_vertex_edge_intersection = line_intersection( viennagrid::point(*opposite_vertex_ptr), circ_center,
                                                                           viennagrid::point(vertices_on_intersected_edge[0]),
                                                                           viennagrid::point(vertices_on_intersected_edge[1]));

          //
          // Step 3: Compute contributions
          //
          for (EdgeOnCellIterator eocit  = edges_on_cell.begin();
                                  eocit != edges_on_cell.end();
                                ++eocit)
          {
            PointType edge_midpoint = circumcenter(*eocit);

            if ( intersected_edge_ptr != &(*eocit) )  // non-intersected edge: Split contributions into contributions from cell itself and contribution from other cell
            {
              PointType edge_intersection = line_intersection( edge_midpoint, circ_center,
                                                               viennagrid::point(vertices_on_intersected_edge[0]),
                                                               viennagrid::point(vertices_on_intersected_edge[1]));

              //
              // Interface contributions (two contributions: From edge midpoint to intersected edge, and from intersected edge to circumcenter)
              //

              double interface_contribution = 0;

              // contribution from cell:
              interface_contribution = spanned_volume(edge_intersection, edge_midpoint);

              interface_area_accessor(*eocit) += interface_contribution;
              voronoi_unique_quantity_update(interface_area_cell_contribution_accessor(*eocit), std::make_pair( cit.handle(), interface_contribution) );

              // contribution from other cell containing the circumcenter:
              interface_contribution = spanned_volume(edge_intersection, circ_center);
              interface_area_accessor(*eocit) += interface_contribution;
              //if ( other_cell != NULL)
              if (!detail::is_handle_invalid( other_cells, other_cell ))
                voronoi_unique_quantity_update(interface_area_cell_contribution_accessor(*eocit), std::make_pair( other_cell, interface_contribution) );


              //
              // Box volume contribution:
              //
              double edge_contribution = 0;

              // contribution from cell itself:
              VertexOnEdgeRange vertices_on_edge = viennagrid::elements<VertexType>(*eocit);
              for (VertexOnEdgeIterator voeit  = vertices_on_edge.begin();
                                        voeit != vertices_on_edge.end();
                                      ++voeit)
              {
                double contribution = spanned_volume(edge_intersection, edge_midpoint, viennagrid::point(*voeit));
                edge_contribution += contribution;

                vertex_box_volume_accessor(*voeit) += contribution;
                voronoi_unique_quantity_update(vertex_box_volume_cell_contribution_accessor(*voeit), std::make_pair( cit.handle(), contribution) );

                if ( &(*voeit) != opposite_vertex_ptr )  // non-splitted contribution
                {
//                   if (other_cell != NULL)
                  if (!detail::is_handle_invalid( other_cells, other_cell ))
                  {
                    double contribution_other = spanned_volume(circ_center, edge_intersection, viennagrid::point(*voeit));
                    vertex_box_volume_accessor(*voeit) += contribution_other;
                    voronoi_unique_quantity_update(vertex_box_volume_cell_contribution_accessor(*voeit),
                                                   std::make_pair(other_cell, contribution_other) );
                    edge_box_volume_accessor(*eocit) += contribution_other;
                    voronoi_unique_quantity_update(edge_box_volume_cell_contribution_accessor(*eocit),
                                                   std::make_pair(other_cell, contribution_other) );
                  }
                }
                else //splitted contribution around center of the edge. Contributes to opposite vertex
                {
                  double contribution_cell = spanned_volume(opposite_vertex_edge_intersection, edge_intersection, viennagrid::point(*voeit));
                  vertex_box_volume_accessor(*voeit) += contribution_cell;
                  voronoi_unique_quantity_update(vertex_box_volume_cell_contribution_accessor(*voeit),
                                                 std::make_pair( cit.handle(), contribution_cell) );
                  edge_box_volume_accessor(*eocit) += contribution_cell;
                  voronoi_unique_quantity_update(edge_box_volume_cell_contribution_accessor(*eocit),
                                                 std::make_pair( cit.handle(), contribution_cell) );

//                   if (other_cell != NULL)
                  if (!detail::is_handle_invalid( other_cells, other_cell ))
                  {
                    double contribution_other = spanned_volume(circ_center, edge_intersection, opposite_vertex_edge_intersection);
                    vertex_box_volume_accessor(*voeit) += contribution_other;
                    voronoi_unique_quantity_update(vertex_box_volume_cell_contribution_accessor(*voeit),
                                                   std::make_pair(other_cell, contribution_other) );
                    edge_box_volume_accessor(*eocit) += contribution_other;
                    voronoi_unique_quantity_update(edge_box_volume_cell_contribution_accessor(*eocit),
                                                   std::make_pair(other_cell, contribution_other) );
                  }
                }


              }
              edge_box_volume_accessor(*eocit) += edge_contribution;
              voronoi_unique_quantity_update(edge_box_volume_cell_contribution_accessor(*eocit),
                                             std::make_pair( cit.handle(), edge_contribution) );

            }
//             else if (other_cell != NULL)// intersected edge: Write negative contributions to other cell
            else if (!detail::is_handle_invalid( other_cells, other_cell ))
            {
              // interface contribution:
              double interface_contribution = spanned_volume(circ_center, edge_midpoint);
              interface_area_accessor(*eocit) -= interface_contribution;
              voronoi_unique_quantity_update(interface_area_cell_contribution_accessor(*eocit),
                                             std::make_pair(other_cell, -1.0 * interface_contribution) );


              //box volume contribution:
              double edge_contribution = 0;
              VertexOnEdgeRange vertices_on_edge = viennagrid::elements<VertexType>(*eocit);
              for (VertexOnEdgeIterator voeit  = vertices_on_edge.begin();
                                        voeit != vertices_on_edge.end();
                                      ++voeit)
              {
                double contribution = spanned_volume(circ_center, edge_midpoint, viennagrid::point(*voeit));
                edge_contribution += contribution;
                vertex_box_volume_accessor(*voeit) -= contribution;
                voronoi_unique_quantity_update(vertex_box_volume_cell_contribution_accessor(*voeit),
                                               std::make_pair(other_cell, -1.0 * contribution) );
              }
              edge_box_volume_accessor(*eocit) -= edge_contribution;
              voronoi_unique_quantity_update(edge_box_volume_cell_contribution_accessor(*eocit),
                                             std::make_pair(other_cell, -1.0 * edge_contribution) );
            }
            // else {}    //nothing to do for a boundary edge

          } //for edges on cells

        }
        else    // circumcenter  is inside triangle (everything is simple... ;-) )
        {

          //iterate over edges:
          EdgeOnCellRange edges_on_cell = viennagrid::elements<EdgeType>(*cit);
          for (EdgeOnCellIterator eocit  = edges_on_cell.begin();
                                  eocit != edges_on_cell.end();
                                ++eocit)
          {
            PointType edge_midpoint = circumcenter(*eocit);

            // interface contribution:
            double interface_contribution = spanned_volume(circ_center, edge_midpoint);
            interface_area_accessor(*eocit) += interface_contribution;
            voronoi_unique_quantity_update(interface_area_cell_contribution_accessor(*eocit),
                                           std::make_pair( cit.handle(), interface_contribution) );


            //box volume contribution:
            double edge_contribution = 0;
            VertexOnEdgeRange vertices_on_edge = viennagrid::elements<VertexType>(*eocit);
            for (VertexOnEdgeIterator voeit  = vertices_on_edge.begin();
                                      voeit != vertices_on_edge.end();
                                    ++voeit)
            {
              double contribution = spanned_volume(circ_center, edge_midpoint, viennagrid::point(*voeit));
              edge_contribution += contribution;
              vertex_box_volume_accessor(*voeit) += contribution;
              voronoi_unique_quantity_update(vertex_box_volume_cell_contribution_accessor(*voeit),
                                             std::make_pair( cit.handle(), contribution) );
            }
            edge_box_volume_accessor(*eocit) += edge_contribution;
            voronoi_unique_quantity_update(edge_box_volume_cell_contribution_accessor(*eocit),
                                           std::make_pair( cit.handle(), edge_contribution) );
          } //for edges on cells

        }

      } //for cells

    }


    //
    // Voronoi information in three dimensions
    //

    /** @brief Implementation of the computation of Voronoi quantities for a tetrahedral mesh
     *
     *  Note: Interface contributions per cell are only approximate for tetrahedral meshes, while they are precise for triangular meshes.
     *        They are consistent in the sense that
     *          total_interface_volume = sum_over_cells(interface_volume_per_cell).
     *        As a consequence, the same holds true for volume contributions.
     *
     */
    template <typename CellTag,
              typename MeshT,
              typename InterfaceAreaAccessorT,
              typename InterfaceAreaCellContributionAccessorT,
              typename VertexBoxVolumeAccessorT,
              typename VertexBoxVolumeCellContributionAccessorT,
              typename EdgeBoxVolumeAccessorT,
              typename EdgeBoxVolumeCellContributionAccessorT>
    void write_voronoi_info(MeshT const & mesh_obj,
                            InterfaceAreaAccessorT                    interface_area_accessor,
                            InterfaceAreaCellContributionAccessorT    interface_area_cell_contribution_accessor,
                            VertexBoxVolumeAccessorT                  vertex_box_volume_accessor,
                            VertexBoxVolumeCellContributionAccessorT  vertex_box_volume_cell_contribution_accessor,
                            EdgeBoxVolumeAccessorT                    edge_box_volume_accessor,
                            EdgeBoxVolumeCellContributionAccessorT    edge_box_volume_cell_contribution_accessor,
                            viennagrid::tetrahedron_tag)
    {
      typedef typename viennagrid::result_of::element<MeshT, CellTag>::type CellType;
      typedef typename viennagrid::result_of::const_handle<MeshT, CellTag>::type ConstCellHandleType;

      typedef typename viennagrid::result_of::point<MeshT>::type                           PointType;
      typedef typename viennagrid::result_of::element<MeshT, vertex_tag>::type             VertexType;
      typedef typename viennagrid::result_of::element<MeshT, line_tag>::type               EdgeType;
      typedef typename viennagrid::result_of::const_handle<MeshT, line_tag>::type          ConstEdgeHandleType;
      typedef typename viennagrid::result_of::element<MeshT, triangle_tag>::type           FacetType;
      typedef typename viennagrid::result_of::const_handle<MeshT, triangle_tag>::type      ConstFacetHandleType;

      typedef typename viennagrid::result_of::coord<PointType>::type    CoordType;

      typedef typename viennagrid::result_of::const_element_range<MeshT, CellTag>::type    CellRange;
      typedef typename viennagrid::result_of::iterator<CellRange>::type                       CellIterator;

      typedef typename viennagrid::result_of::const_element_range<MeshT, typename CellTag::facet_tag>::type  FacetRange;
      typedef typename viennagrid::result_of::iterator<FacetRange>::type                                        FacetIterator;

      typedef typename viennagrid::result_of::const_element_range<MeshT, line_tag>::type                   EdgeRange;
      typedef typename viennagrid::result_of::iterator<EdgeRange>::type                                       EdgeIterator;

      typedef typename viennagrid::result_of::const_element_range<CellType, typename CellTag::facet_tag>::type  FacetOnCellRange;
      typedef typename viennagrid::result_of::iterator<FacetOnCellRange>::type                                  FacetOnCellIterator;

      typedef typename viennagrid::result_of::const_element_range<FacetType, line_tag>::type                    EdgeOnFacetRange;
      typedef typename viennagrid::result_of::iterator<EdgeOnFacetRange>::type                                  EdgeOnFacetIterator;

      typedef typename viennagrid::result_of::const_element_range<EdgeType, vertex_tag>::type                   VertexOnEdgeRange;
      typedef typename viennagrid::result_of::iterator<VertexOnEdgeRange>::type                                 VertexOnEdgeIterator;

      typedef std::pair<PointType, ConstCellHandleType>             PointWithCellInfo;
      typedef std::pair<std::pair<PointType, PointType>,
                        ConstCellHandleType>                        EdgePointsWithCellInfo;
      typedef std::vector< PointWithCellInfo >                      CircumcenterContainer;


      //
      // Step one: Write circumcenters to facets
      //

      viennagrid::detail::dereference_handle_comparator<MeshT> comp(mesh_obj);

      std::map< ConstFacetHandleType, CircumcenterContainer, viennagrid::detail::dereference_handle_comparator<MeshT> >
                                                               circumcenters_on_facets( comp );
      //std::map< EdgeType const *,
      std::map< ConstEdgeHandleType,
                std::vector< EdgePointsWithCellInfo >,
                viennagrid::detail::dereference_handle_comparator<MeshT>
              >                                                interface_boundaries_on_edges(comp);


      CellRange cells = viennagrid::elements<CellType>(mesh_obj);
      for (CellIterator cit  = cells.begin();
                        cit != cells.end();
                      ++cit)
      {
        const CellType & cell = *cit;
        PointType circ_center = circumcenter(cell);

        FacetOnCellRange facets_on_cell = viennagrid::elements<FacetType>(cell);
        for (FacetOnCellIterator focit  = facets_on_cell.begin();
                                 focit != facets_on_cell.end();
                                 ++focit)
        {
          circumcenters_on_facets[focit.handle()].push_back( PointWithCellInfo(circ_center, cit.handle()) );
        } //for edges on cells
      } //for cells


      //
      // Step two: Write lines connecting circumcenters to edges
      //
      FacetRange facets = viennagrid::elements<FacetType>(mesh_obj);
      for (FacetIterator fit  = facets.begin();
                         fit != facets.end();
                       ++fit)
      {
        CircumcenterContainer & circ_centers = circumcenters_on_facets[fit.handle()];
        const FacetType & facet = *fit;

        EdgeOnFacetRange edges_on_facet = viennagrid::elements<EdgeType>( facet );
        for (EdgeOnFacetIterator eofit  = edges_on_facet.begin();
                                 eofit != edges_on_facet.end();
                              ++eofit)
        {
          const EdgeType & edge = *eofit;

          if (circ_centers.size() == 1)
          {
            interface_boundaries_on_edges[eofit.handle()].push_back(std::make_pair( std::make_pair(circ_centers[0].first, circumcenter(facet)),
                                                                               circ_centers[0].second)
                                                              );
            interface_boundaries_on_edges[eofit.handle()].push_back(std::make_pair( std::make_pair(circumcenter(edge), circumcenter(facet)),
                                                                               circ_centers[0].second)
                                                              );
          }
          else if (circ_centers.size() == 2)
          {
            PointType edge_mid = circ_centers[0].first + circ_centers[1].first;
            edge_mid /= 2.0;

            interface_boundaries_on_edges[eofit.handle()].push_back(std::make_pair( std::make_pair(circ_centers[0].first, edge_mid),
                                                                               circ_centers[0].second)
                                                              );
            interface_boundaries_on_edges[eofit.handle()].push_back(std::make_pair( std::make_pair(edge_mid, circ_centers[1].first),
                                                                               circ_centers[1].second)
                                                              );
          }
          else
          {
            std::cerr << "circ_centers.size() = " << circ_centers.size() << std::endl;
            std::cerr << "*fit: " << facet << std::endl;
            throw std::runtime_error("More than two circumcenters for a facet in three dimensions!");
          }

        } //for edges on cells
      }


      //
      // Step three: Compute Voronoi information:
      //
      EdgeRange edges = viennagrid::elements<EdgeType>(mesh_obj);
      for (EdgeIterator eit  = edges.begin();
                        eit != edges.end();
                        ++eit)
      {
        const EdgeType & edge = *eit;

        //get vertices of edge:
        VertexOnEdgeRange vertices_on_edge = viennagrid::elements<VertexType>(edge);
        VertexOnEdgeIterator voeit = vertices_on_edge.begin();



        VertexType const & v0 = *voeit;
        ++voeit;
        VertexType const & v1 = *voeit;

        double edge_length = spanned_volume( viennagrid::point(mesh_obj, v0), viennagrid::point(mesh_obj, v1));

        std::vector< EdgePointsWithCellInfo > & interface_segments = interface_boundaries_on_edges[eit.handle()];

        //
        // determine inner point of convex interface polygon:
        //
        PointType inner_point = (interface_segments[0].first.first + interface_segments[0].first.second) / 2.0;
        for (std::size_t i=1; i<interface_segments.size(); ++i)
        {
          inner_point += (interface_segments[i].first.first + interface_segments[i].first.second) / 2.0;
        }
        inner_point /= static_cast<CoordType>(interface_segments.size());

        //
        // compute interface area
        //
        double interface_area = 0.0;
        for (std::size_t i=0; i<interface_segments.size(); ++i)
        {
          // interface area:
          double interface_contribution = spanned_volume(interface_segments[i].first.first, interface_segments[i].first.second, inner_point);
          if (interface_contribution > 0)
          {
            voronoi_unique_quantity_update(interface_area_cell_contribution_accessor( edge ),
                                           std::make_pair(interface_segments[i].second, interface_contribution) );
            interface_area += interface_contribution;

            // box volume:
            double volume_contribution = interface_contribution * edge_length / 6.0;
            voronoi_unique_quantity_update(edge_box_volume_cell_contribution_accessor( edge ),
                                           std::make_pair(interface_segments[i].second, 2.0 * volume_contribution) ); //volume contribution of both box volumes associated with the edge
            voronoi_unique_quantity_update(vertex_box_volume_cell_contribution_accessor(v0),
                                           std::make_pair( interface_segments[i].second, volume_contribution) );
            voronoi_unique_quantity_update(vertex_box_volume_cell_contribution_accessor(v1),
                                           std::make_pair( interface_segments[i].second, volume_contribution) );
          }
        }

        //
        // Write Voronoi info:
        //

        //std::cout << "Interface area: " << interface_area << std::endl;
        interface_area_accessor( edge ) = interface_area;
        double volume_contribution = interface_area * edge_length / 6.0;
        edge_box_volume_accessor(edge) = 2.0 * volume_contribution; //volume contribution of both box volumes associated with the edge
        vertex_box_volume_accessor(v0) += volume_contribution;
        vertex_box_volume_accessor(v1) += volume_contribution;

      } //for edges

    } //write_voronoi_info(tetrahedron_tag)



    /** @brief Implementation of the computation of Voronoi quantities for a hexahedral mesh */
    template <typename CellTag,
              typename MeshT,
              typename InterfaceAreaAccessorT,
              typename InterfaceAreaCellContributionAccessorT,
              typename VertexBoxVolumeAccessorT,
              typename VertexBoxVolumeCellContributionAccessorT,
              typename EdgeBoxVolumeAccessorT,
              typename EdgeBoxVolumeCellContributionAccessorT>
    void write_voronoi_info(MeshT const & mesh_obj,
                            InterfaceAreaAccessorT interface_area_accessor,
                            InterfaceAreaCellContributionAccessorT interface_area_cell_contribution_accessor,
                            VertexBoxVolumeAccessorT vertex_box_volume_accessor,
                            VertexBoxVolumeCellContributionAccessorT vertex_box_volume_cell_contribution_accessor,
                            EdgeBoxVolumeAccessorT edge_box_volume_accessor,
                            EdgeBoxVolumeCellContributionAccessorT edge_box_volume_cell_contribution_accessor,
                            viennagrid::hexahedron_tag)
    {
      //std::cout << "Warning: Voronoi info for hexahedron is only correct when having regular cuboids only." << std::endl;

      typedef typename viennagrid::result_of::element<MeshT, CellTag>::type CellType;

      typedef typename viennagrid::result_of::point<MeshT>::type                            PointType;
      typedef typename viennagrid::result_of::element<MeshT, vertex_tag>::type              VertexType;
      typedef typename viennagrid::result_of::element<MeshT, line_tag>::type                EdgeType;
      typedef typename viennagrid::result_of::element<MeshT, quadrilateral_tag>::type       FacetType;

      typedef typename viennagrid::result_of::const_element_range<MeshT, CellTag>::type     CellRange;
      typedef typename viennagrid::result_of::iterator<CellRange>::type                        CellIterator;

      typedef typename viennagrid::result_of::const_element_range<CellType, quadrilateral_tag>::type          FacetOnCellRange;
      typedef typename viennagrid::result_of::iterator<FacetOnCellRange>::type                                FacetOnCellIterator;

      typedef typename viennagrid::result_of::const_element_range<FacetType, line_tag>::type                  EdgeOnFacetRange;
      typedef typename viennagrid::result_of::iterator<EdgeOnFacetRange>::type                                EdgeOnFacetIterator;

      typedef typename viennagrid::result_of::const_element_range<EdgeType, vertex_tag>::type                 VertexOnEdgeRange;
      typedef typename viennagrid::result_of::iterator<VertexOnEdgeRange>::type                               VertexOnEdgeIterator;

      //
      // Algorithm: Iterate over all cells, compute circumcenter and add interface area to edge, box volume to vertex.
      //

      CellRange cells = viennagrid::elements<CellTag>(mesh_obj);
      for (CellIterator cit  = cells.begin();
                        cit != cells.end();
                        ++cit)
      {
        const CellType & cell = *cit;
        PointType cell_center = circumcenter(cell);

        FacetOnCellRange facets_on_cell = viennagrid::elements<viennagrid::quadrilateral_tag>(cell);
        for (FacetOnCellIterator focit  = facets_on_cell.begin();
                                focit != facets_on_cell.end();
                              ++focit)
        {
          PointType facet_center = circumcenter(*focit);

          //iterate over edges:
          EdgeOnFacetRange edges_on_facet = viennagrid::elements<EdgeType>(*focit);
          for (EdgeOnFacetIterator eocit  = edges_on_facet.begin();
                                  eocit != edges_on_facet.end();
                                ++eocit)
          {
            PointType edge_midpoint = viennagrid::circumcenter(*eocit);

            // interface contribution:
            double interface_contribution = spanned_volume(cell_center, facet_center, edge_midpoint);
            interface_area_cell_contribution_accessor(*eocit).push_back(std::make_pair(cit.handle(), interface_contribution) );   //Note: Due to iteration over cells there is no need to use a voronoi_unique_quantity_update() here
            interface_area_accessor(*eocit) += interface_contribution;

            //box volume contribution:
            double edge_contribution = 0;
            VertexOnEdgeRange vertices_on_edge = viennagrid::elements<VertexType>(*eocit);
            for (VertexOnEdgeIterator voeit  = vertices_on_edge.begin();
                                      voeit != vertices_on_edge.end();
                                    ++voeit)
            {
              //double contribution = spanned_volume(cell_center, facet_center, edge_midpoint, voeit->point());
              double contribution = spanned_volume(cell_center, facet_center, edge_midpoint, viennagrid::point(mesh_obj, *voeit));
              vertex_box_volume_cell_contribution_accessor(*voeit).push_back(std::make_pair( cit.handle(), contribution) );
              vertex_box_volume_accessor(*voeit) += contribution;
              edge_contribution += contribution;
            }
            edge_box_volume_cell_contribution_accessor(*eocit).push_back(std::make_pair( cit.handle(), edge_contribution) );
            edge_box_volume_accessor(*eocit) += edge_contribution;
          } //for edges on facet

        } //for facets on cell

      } //for cells

    }

  } //namespace detail

  //
  // The public interface
  //

  /** @brief Writes Voronoi information to the mesh or segment using the provided accessors
   *
   * @tparam ElementTypeOrTagT                              The element/cell type/tag for which the voronoi information is calculated
   * @param  mesh_obj                                       The mesh
   * @param  interface_area_accessor                        An accessor where the interface areas are stored
   * @param  interface_area_cell_contribution_accessor      An accessor where the interface area element contributions are stored
   * @param  vertex_box_volume_accessor                     An accessor where the vertex box volumes are stored
   * @param  vertex_box_volume_cell_contribution_accessor   An accessor where the vertex box volume element contributions are stored
   * @param  edge_box_volume_accessor                       An accessor where the edge box volumes are stored
   * @param  edge_box_volume_cell_contribution_accessor     An accessor where the edge box volume element contributions are stored
   */
  template <typename ElementTypeOrTagT,
            typename MeshT,
            typename InterfaceAreaAccessorT,
            typename InterfaceAreaCellContributionAccessorT,
            typename VertexBoxVolumeAccessorT,
            typename VertexBoxVolumeCellContributionAccessorT,
            typename EdgeBoxVolumeAccessorT,
            typename EdgeBoxVolumeCellContributionAccessorT>
  void apply_voronoi(MeshT const & mesh_obj,
                     InterfaceAreaAccessorT                     interface_area_accessor,
                     InterfaceAreaCellContributionAccessorT     interface_area_cell_contribution_accessor,
                     VertexBoxVolumeAccessorT                   vertex_box_volume_accessor,
                     VertexBoxVolumeCellContributionAccessorT   vertex_box_volume_cell_contribution_accessor,
                     EdgeBoxVolumeAccessorT                     edge_box_volume_accessor,
                     EdgeBoxVolumeCellContributionAccessorT     edge_box_volume_cell_contribution_accessor)
  {
    typedef typename viennagrid::result_of::element_tag<ElementTypeOrTagT>::type ElementTag;

    detail::write_voronoi_info<ElementTag>(mesh_obj,
                               interface_area_accessor,
                               interface_area_cell_contribution_accessor,
                               vertex_box_volume_accessor,
                               vertex_box_volume_cell_contribution_accessor,
                               edge_box_volume_accessor,
                               edge_box_volume_cell_contribution_accessor,
                               ElementTag());
  }

} //namespace viennagrid
#endif
