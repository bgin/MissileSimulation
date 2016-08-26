#ifndef VIENNAGRID_ALGORITHM_REFINE_HPP
#define VIENNAGRID_ALGORITHM_REFINE_HPP

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
#include "viennagrid/algorithm/centroid.hpp"
#include "viennagrid/algorithm/norm.hpp"

#include "viennagrid/mesh/element_creation.hpp"
#include "viennagrid/mesh/mesh_operations.hpp"

#include "viennagrid/algorithm/detail/refine_tri.hpp"
#include "viennagrid/algorithm/detail/refine_tet.hpp"

#include "viennagrid/algorithm/detail/numeric.hpp"

/** @file viennagrid/algorithm/refine.hpp
    @brief Provides the routines for a refinement of a mesh
*/

namespace viennagrid
{

  /** @brief Refines a mesh based on edge information. A bool accessor, indicating if an edge should be refined, and a vertex handle accessor, representing the new vertex of an edge to refine, are used for the refinement process.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param mesh_out                          Output refined mesh
   * @param vertex_copy_map_                  A vertex copy map for identifying vertices
   * @param edge_refinement_flag_accessor     An accessor defining which edge should be refined. operator() takes an edge and returns a bool.
   * @param edge_to_vertex_handle_accessor    An accessor defining the vertex handle of an edge to refine. operator() takes an edge and returns a vertex handle.
   */
  template<typename ElementTypeOrTagT,
            typename WrappedMeshConfigInT,
            typename WrappedMeshConfigOutT,
            typename VertexCopyMapT,
            typename EdgeRefinementFlagAccessorT, typename RefinementVertexAccessorT>
  void simple_refine(mesh<WrappedMeshConfigInT> const & mesh_in,
                     mesh<WrappedMeshConfigOutT> & mesh_out,
                     VertexCopyMapT & vertex_copy_map_,
                     EdgeRefinementFlagAccessorT const & edge_refinement_flag_accessor,
                     RefinementVertexAccessorT const & edge_to_vertex_handle_accessor)
  {
    typedef mesh<WrappedMeshConfigInT>       InputMeshType;
    typedef mesh<WrappedMeshConfigOutT>      OutputMeshType;

    typedef typename viennagrid::result_of::const_element_range<InputMeshType, ElementTypeOrTagT>::type  ElementRange;
    typedef typename viennagrid::result_of::iterator<ElementRange>::type                                 ElementIterator;

    ElementRange cells(mesh_in);
    for (ElementIterator cit  = cells.begin();
                      cit != cells.end();
                    ++cit)
    {
      typedef typename viennagrid::result_of::vertex_handle<OutputMeshType>::type OutputVertexHandleType;
      typedef std::vector<OutputVertexHandleType> VertexHandlesContainerType;
      typedef std::vector<VertexHandlesContainerType> ElementsContainerType;
      ElementsContainerType elements_vertices;

      detail::element_refinement<ElementTypeOrTagT>::apply(*cit, mesh_out, elements_vertices, vertex_copy_map_, edge_refinement_flag_accessor, edge_to_vertex_handle_accessor);

      for (typename ElementsContainerType::iterator it = elements_vertices.begin();
            it != elements_vertices.end();
            ++it)
        viennagrid::make_element<ElementTypeOrTagT>( mesh_out, it->begin(), it->end() );
    }
  }


  /** @brief Refines a mesh and a segmentation based on edge information. A bool accessor, indicating if an edge should be refined, and a vertex handle accessor, representing the new vertex of an edge to refine, are used for the refinement process.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param segmentation_in                   Input segmentation
   * @param mesh_out                          Output refined mesh
   * @param segmentation_out                  Output refined segmentation
   * @param vertex_copy_map_                  A vertex copy map for identifying vertices
   * @param edge_refinement_flag_accessor     An accessor defining which edge should be refined. operator() takes an edge and returns a bool.
   * @param edge_to_vertex_handle_accessor    An accessor defining the vertex handle of an edge to refine. operator() takes an edge and returns a vertex handle.
   */
  template<typename ElementTypeOrTagT,
            typename WrappedMeshConfigInT,  typename WrappedSegmentationConfigInT,
            typename WrappedMeshConfigOutT, typename WrappedSegmentationConfigOutT,
            typename VertexCopyMapT,
            typename EdgeRefinementFlagAccessorT, typename RefinementVertexAccessorT>
  void simple_refine(mesh<WrappedMeshConfigInT>                 const & mesh_in,
                     segmentation<WrappedSegmentationConfigInT> const & segmentation_in,
                     mesh<WrappedMeshConfigOutT>                      & mesh_out,
                     segmentation<WrappedSegmentationConfigOutT>      & segmentation_out,
                     VertexCopyMapT & vertex_copy_map_,
                     EdgeRefinementFlagAccessorT const & edge_refinement_flag_accessor,
                     RefinementVertexAccessorT const & edge_to_vertex_handle_accessor)
  {
    typedef mesh<WrappedMeshConfigInT>    InputMeshType;
    typedef mesh<WrappedMeshConfigOutT>   OutputMeshType;

    typedef segmentation<WrappedSegmentationConfigInT>      InputSegmentationType;

    typedef typename viennagrid::result_of::const_element_range<InputMeshType, ElementTypeOrTagT>::type ElementRange;
    typedef typename viennagrid::result_of::iterator<ElementRange>::type                                ElementIterator;

    ElementRange cells(mesh_in);
    for (ElementIterator cit  = cells.begin();
                      cit != cells.end();
                    ++cit)
    {
      typedef typename viennagrid::result_of::segment_id_range<InputSegmentationType, ElementTypeOrTagT>::type SegmentIDRangeType;

      SegmentIDRangeType segment_ids = viennagrid::segment_ids( segmentation_in, *cit );

      typedef typename viennagrid::result_of::vertex_handle<OutputMeshType>::type OutputVertexHandleType;
      typedef typename viennagrid::result_of::handle<OutputMeshType, ElementTypeOrTagT>::type OutputCellHandleType;
      typedef std::vector<OutputVertexHandleType> VertexHandlesContainerType;
      typedef std::vector<VertexHandlesContainerType> ElementsContainerType;
      ElementsContainerType elements_vertices;

      detail::element_refinement<ElementTypeOrTagT>::apply(*cit, mesh_out, elements_vertices, vertex_copy_map_, edge_refinement_flag_accessor, edge_to_vertex_handle_accessor);

      for (typename ElementsContainerType::iterator it = elements_vertices.begin();
            it != elements_vertices.end();
            ++it)
      {
        OutputCellHandleType new_cell = viennagrid::make_element<ElementTypeOrTagT>( mesh_out, it->begin(), it->end() );
        viennagrid::add( segmentation_out, segment_ids.begin(), segment_ids.end(), new_cell );
      }
    }
  }




  namespace detail
  {



    /** @brief For internal use only */
    template<typename CellTagT,
              typename WrappedMeshConfigInT,
              typename WrappedMeshConfigOutT,
              typename PointAccessorT,
              typename VertexCopyMapT,
              typename EdgeRefinementFlagAccessorT, typename RefinementVertexAccessorT>
    void refine_impl(mesh<WrappedMeshConfigInT> const & mesh_in,
                     mesh<WrappedMeshConfigOutT> & mesh_out,
                     PointAccessorT const point_accessor_in,
                     VertexCopyMapT & vertex_copy_map_,
                     EdgeRefinementFlagAccessorT const & edge_refinement_flag_accessor,
                     RefinementVertexAccessorT & edge_to_vertex_handle_accessor)
    {
      typedef mesh<WrappedMeshConfigInT>       InputMeshType;

      typedef typename viennagrid::result_of::const_line_range<InputMeshType>::type                 EdgeRange;
      typedef typename viennagrid::result_of::iterator<EdgeRange>::type                             EdgeIterator;

      //
      // Step 1: Each tagged edge in old mesh results in a new vertex (temporarily store new vertex IDs on old mesh)
      //
      EdgeRange edges(mesh_in);
      for (EdgeIterator eit = edges.begin();
                        eit != edges.end();
                      ++eit)
      {
        if ( edge_refinement_flag_accessor(*eit) )
        {
          edge_to_vertex_handle_accessor( *eit ) = viennagrid::make_vertex( mesh_out, viennagrid::centroid(point_accessor_in, *eit) );
        }
      }

      //
      // Step 2: Now write new cells to new mesh
      //
      simple_refine<CellTagT>(mesh_in, mesh_out, vertex_copy_map_, edge_refinement_flag_accessor, edge_to_vertex_handle_accessor);
    }



    /** @brief For internal use only */
    template<typename CellTagT,
              typename WrappedMeshConfigInT,  typename WrappedSegmentationConfigInT,
              typename WrappedMeshConfigOutT, typename WrappedSegmentationConfigOutT,
              typename PointAccessorT,
              typename VertexCopyMapT,
              typename EdgeRefinementFlagAccessorT, typename RefinementVertexAccessorT>
    void refine_impl(mesh<WrappedMeshConfigInT>                 const & mesh_in,
                     segmentation<WrappedSegmentationConfigInT> const & segmentation_in,
                     mesh<WrappedMeshConfigOutT>                      & mesh_out,
                     segmentation<WrappedSegmentationConfigOutT>      & segmentation_out,
                     PointAccessorT const point_accessor_in,
                     VertexCopyMapT & vertex_copy_map_,
                     EdgeRefinementFlagAccessorT const & edge_refinement_flag_accessor,
                     RefinementVertexAccessorT & edge_to_vertex_handle_accessor)
    {
      typedef mesh<WrappedMeshConfigInT>    InputMeshType;

      typedef typename viennagrid::result_of::const_line_range<InputMeshType>::type       EdgeRange;
      typedef typename viennagrid::result_of::iterator<EdgeRange>::type                               EdgeIterator;


      //
      // Step 1: Each tagged edge in old mesh results in a new vertex (temporarily store new vertex IDs on old mesh)
      //
      EdgeRange edges(mesh_in);
      for (EdgeIterator eit = edges.begin();
                        eit != edges.end();
                      ++eit)
      {
        if ( edge_refinement_flag_accessor(*eit) )
        {
          edge_to_vertex_handle_accessor( *eit ) = viennagrid::make_vertex( mesh_out, viennagrid::centroid(point_accessor_in, *eit) );
        }
      }

      //
      // Step 2: Now write new cells to new mesh
      //
      simple_refine<CellTagT>( mesh_in, segmentation_in, mesh_out, segmentation_out, vertex_copy_map_, edge_refinement_flag_accessor, edge_to_vertex_handle_accessor );
    }


  } //namespace detail



  /** @brief Ensures refinement of the longest edge of each cell. If any edge is tagged for refinement in a cell, then the longest edge is refined as well. */
  template<typename CellTagIn, typename WrappedMeshConfigInT, typename EdgeRefinementFlagAccessorT>
  void ensure_longest_edge_refinement(mesh<WrappedMeshConfigInT> const & mesh_in, EdgeRefinementFlagAccessorT edge_refinement_flag_accessor)
  {
    typedef mesh<WrappedMeshConfigInT>                                            MeshInType;

    typedef typename viennagrid::result_of::element<MeshInType, vertex_tag>::type     VertexType;
    typedef typename viennagrid::result_of::element<MeshInType, line_tag>::type       EdgeType;
    typedef typename viennagrid::result_of::element<MeshInType, CellTagIn>::type      CellType;

    typedef typename viennagrid::result_of::const_element_range<MeshInType, CellTagIn>::type    CellRange;
    typedef typename viennagrid::result_of::iterator<CellRange>::type                             CellIterator;
    typedef typename viennagrid::result_of::const_element_range<CellType, line_tag>::type         EdgeOnCellRange;
    typedef typename viennagrid::result_of::iterator<EdgeOnCellRange>::type                       EdgeOnCellIterator;
    typedef typename viennagrid::result_of::const_element_range<EdgeType, vertex_tag>::type       VertexOnEdgeRange;
    typedef typename viennagrid::result_of::iterator<VertexOnEdgeRange>::type                     VertexOnEdgeIterator;


    bool something_changed = true;
    //std::size_t iter_cnt = 0;

    while (something_changed)
    {
      something_changed = false;

      CellRange cells = viennagrid::elements<CellTagIn>(mesh_in);
      for (CellIterator cit  = cells.begin();
                        cit != cells.end();
                      ++cit)
      {
        //
        // check if any edges are tagged for refinement
        //
        bool has_refinement = false;
        EdgeOnCellRange edges_on_cell = viennagrid::elements<line_tag>(*cit);
        for (EdgeOnCellIterator eocit = edges_on_cell.begin();
                                eocit != edges_on_cell.end();
                              ++eocit)
        {
          if ( edge_refinement_flag_accessor(*eocit) )
          {
            has_refinement = true;
            break;
          }
        }

        if (has_refinement)
        {
          //
          // Find longest edge
          //
          EdgeType const * longest_edge_ptr = NULL;
          double longest_edge_len = 0;

          for (EdgeOnCellIterator eocit = edges_on_cell.begin();
                                  eocit != edges_on_cell.end();
                                ++eocit)
          {
            VertexOnEdgeRange vertices_on_edge = viennagrid::elements<vertex_tag>(*eocit);
            VertexOnEdgeIterator voeit = vertices_on_edge.begin();
            VertexType const & v0 = *voeit; ++voeit;
            VertexType const & v1 = *voeit;

            double len = viennagrid::norm( viennagrid::point(mesh_in, v0) - viennagrid::point(mesh_in, v1) );
            if (len > longest_edge_len)
            {
              longest_edge_len = len;
              longest_edge_ptr = &(*eocit);
            }
          }

          //tag longest edge:
          if ( !edge_refinement_flag_accessor(*longest_edge_ptr) )
          {
            edge_refinement_flag_accessor(*longest_edge_ptr) = true;
            something_changed = true;
          }
        }

      } //for cells


    } //while
  } //ensure_longest_edge_refinement

  /** @brief Transfers tags for refinement from the cell to edges */
  template<typename CellTagIn, typename WrappedMeshConfigInT, typename CellRefinementFlagAccessorT, typename EdgeRefinementFlagAccessorT>
  void cell_refinement_to_edge_refinement(mesh<WrappedMeshConfigInT> const & mesh_in,
                                          CellRefinementFlagAccessorT cell_refinement_flag, EdgeRefinementFlagAccessorT edge_refinement_flag_accessor)
  {
    typedef mesh<WrappedMeshConfigInT>                                                        MeshInType;

    typedef typename viennagrid::result_of::element<MeshInType, CellTagIn>::type                  CellType;

    typedef typename viennagrid::result_of::const_element_range<MeshInType, CellTagIn>::type      CellRange;
    typedef typename viennagrid::result_of::iterator<CellRange>::type                               CellIterator;
    typedef typename viennagrid::result_of::const_element_range<CellType, line_tag>::type           EdgeOnCellRange;
    typedef typename viennagrid::result_of::iterator<EdgeOnCellRange>::type                         EdgeOnCellIterator;

    std::size_t cells_for_refinement = 0;
    CellRange cells(mesh_in);
    for (CellIterator cit  = cells.begin();
                      cit != cells.end();
                    ++cit)
    {
      if ( cell_refinement_flag(*cit) )
      {
        ++cells_for_refinement;

        EdgeOnCellRange edges_on_cell(*cit);
        for (EdgeOnCellIterator eocit = edges_on_cell.begin();
                                eocit != edges_on_cell.end();
                              ++eocit)
        {
          edge_refinement_flag_accessor(*eocit) = true;
        }
      }
    }

  }


  /** @brief Mark all edges for refinement -> unform refinement */
  template<typename WrappedMeshConfigInT, typename EdgeRefinementFlagAccessorT>
  void mark_all_edge_refinement(mesh<WrappedMeshConfigInT> const & mesh_in, EdgeRefinementFlagAccessorT edge_refinement_flag_accessor)
  {
    typedef mesh<WrappedMeshConfigInT>                                                                MeshInType;

    typedef typename viennagrid::result_of::const_element_range<MeshInType, viennagrid::line_tag>::type   LineRange;
    typedef typename viennagrid::result_of::iterator<LineRange>::type                                       LineIterator;

    LineRange lines(mesh_in);
    for (LineIterator it = lines.begin(); it != lines.end(); ++it)
      edge_refinement_flag_accessor(*it) = true;
  }


  /** @brief Mark edges for refinement based on a hyperplane */
  template<typename SrcMeshT, typename DstMeshT, typename PointT, typename LineRefinementTagContainerT, typename LineRefinementVertexHandleContainerT, typename NumericConfigT>
  void mark_edges_for_hyperplane_refine(SrcMeshT const & src_mesh, DstMeshT & dst_mesh,
                            PointT const & hyperplane_point, PointT const & hyperplane_normal,
                            LineRefinementTagContainerT & line_refinement_tag_accessor,
                            LineRefinementVertexHandleContainerT & line_refinement_vertex_handle_accessor,
                            NumericConfigT numeric_config)
  {
    typedef typename viennagrid::result_of::coord<SrcMeshT>::type NumericType;
    typedef typename viennagrid::result_of::const_line_range<SrcMeshT>::type ConstLineRangeType;
    typedef typename viennagrid::result_of::iterator<ConstLineRangeType>::type ConstLineIteratorType;

    ConstLineRangeType lines(src_mesh);
    for (ConstLineIteratorType lit = lines.begin(); lit != lines.end(); ++lit)
    {
      NumericType distance0 = viennagrid::inner_prod( hyperplane_normal, viennagrid::point( viennagrid::vertices(*lit)[0] )-hyperplane_point );
      NumericType distance1 = viennagrid::inner_prod( hyperplane_normal, viennagrid::point( viennagrid::vertices(*lit)[1] )-hyperplane_point );

      NumericType tolerance = viennagrid::detail::relative_tolerance(numeric_config, viennagrid::volume(*lit));

      if (distance0 > distance1)
        std::swap(distance0, distance1);

      if (distance0 < -tolerance && distance1 > tolerance)
      {
        line_refinement_tag_accessor(*lit) = true;

        PointT const & pt0 = viennagrid::point( viennagrid::vertices(*lit)[0] );
        PointT const & pt1 = viennagrid::point( viennagrid::vertices(*lit)[1] );

        double qd = viennagrid::inner_prod( hyperplane_normal, pt0-hyperplane_point );
        double pd = viennagrid::inner_prod( hyperplane_normal, pt1-hyperplane_point );

        PointT new_pt = pt1 - (pd / (pd-qd)) * (pt1 - pt0);
        line_refinement_vertex_handle_accessor(*lit) = viennagrid::make_unique_vertex( dst_mesh, new_pt );
      }
      else
        line_refinement_tag_accessor(*lit) = false;
    }
  }







  /** @brief Public interface for refinement of a mesh with explicit point accessor, edge refinement accessor and temporary accessors
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param mesh_out                          Output refined mesh
   * @param point_accessor_in                 Point accessor for input points
   * @param vertex_copy_map_                  A vertex copy map for identifying vertices
   * @param edge_refinement_flag_accessor     Accessor storing flags if an edge is marked for refinement
   * @param edge_to_vertex_handle_accessor    Temporary accessor for refined edge to vertex mapping
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT, typename WrappedMeshConfigOutT,
           typename PointAccessorType,
           typename VertexCopyMapT,
           typename EdgeRefinementFlagAccessorT, typename RefinementVertexAccessor>
  void refine(mesh<WrappedMeshConfigInT> const & mesh_in,
              mesh<WrappedMeshConfigOutT> & mesh_out,
              PointAccessorType point_accessor_in,
              VertexCopyMapT & vertex_copy_map_,
              EdgeRefinementFlagAccessorT const & edge_refinement_flag_accessor,
              RefinementVertexAccessor & edge_to_vertex_handle_accessor)
  {
      typedef typename viennagrid::result_of::element_tag<ElementTypeOrTagT>::type CellTag;

      detail::refine_impl<CellTag>(mesh_in, mesh_out, point_accessor_in,
                                  vertex_copy_map_,
                                  edge_refinement_flag_accessor, edge_to_vertex_handle_accessor);
  }


  /** @brief Public interface for refinement of a mesh with explicit point accessor and edge refinement accessor.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param mesh_out                          Output refined mesh
   * @param point_accessor_in                 Point accessor for input points
   * @param edge_refinement_flag_accessor     Accessor storing flags if an edge is marked for refinement
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT, typename WrappedMeshConfigOutT,
           typename PointAccessorType,
           typename EdgeRefinementFlagAccessorT>
  void refine(mesh<WrappedMeshConfigInT> const & mesh_in,
              mesh<WrappedMeshConfigOutT> & mesh_out,
              PointAccessorType point_accessor_in,
              EdgeRefinementFlagAccessorT const & edge_refinement_flag_accessor)
  {
    typedef mesh<WrappedMeshConfigInT>                                             MeshInType;
    typedef mesh<WrappedMeshConfigOutT>                                             MeshOutType;

    typedef typename viennagrid::result_of::line<MeshOutType>::type                     EdgeType;

    typedef typename viennagrid::result_of::vertex_handle<MeshOutType>::type            VertexHandleType;

    viennagrid::vertex_copy_map<MeshInType, MeshOutType> vertex_map(mesh_out);
    std::deque<VertexHandleType> edge_refinement_vertex_handle_container;
    typename viennagrid::result_of::accessor<std::deque<VertexHandleType>, EdgeType>::type edge_refinement_vertex_handle_accessor(edge_refinement_vertex_handle_container);

    refine<ElementTypeOrTagT>(mesh_in, mesh_out, point_accessor_in,
                    vertex_map,
                    edge_refinement_flag_accessor,
                    edge_refinement_vertex_handle_accessor);
  }

  /** @brief Public interface for refinement of a mesh with edge refinement accessor.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param mesh_out                          Output refined mesh
   * @param edge_refinement_flag_accessor     Accessor storing flags if an edge is marked for refinement
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT, typename WrappedMeshConfigOutT,
           typename EdgeRefinementFlagAccessorT>
  void refine(mesh<WrappedMeshConfigInT> const & mesh_in,
              mesh<WrappedMeshConfigOutT> & mesh_out,
              EdgeRefinementFlagAccessorT const & edge_refinement_flag_accessor)
  {
    refine<ElementTypeOrTagT>(mesh_in, mesh_out, default_point_accessor(mesh_in), edge_refinement_flag_accessor);
  }



  /** @brief Public interface for refinement of a mesh with explicit point accessor and cell refinement accessor.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param mesh_out                          Output refined mesh
   * @param point_accessor_in                 Point accessor for input points
   * @param cell_refinement_flag_accessor     Accessor storing flags if a cell is marked for refinement
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT, typename WrappedMeshConfigOutT,
           typename PointAccessorType,
           typename CellRefinementFlagAccessorT>
  void element_refine(mesh<WrappedMeshConfigInT> const & mesh_in,
                      mesh<WrappedMeshConfigOutT> & mesh_out,
                      PointAccessorType point_accessor_in, CellRefinementFlagAccessorT const cell_refinement_flag_accessor)
  {
    typedef mesh<WrappedMeshConfigOutT>                                             MeshOutType;

    typedef typename viennagrid::result_of::line<MeshOutType>::type                     EdgeType;

    std::deque<bool> edge_refinement_flag;

    edge_refinement_flag.resize( static_cast<std::size_t>(viennagrid::id_upper_bound<EdgeType>(mesh_in).get()) );

    cell_refinement_to_edge_refinement<ElementTypeOrTagT>( mesh_in,
                                        cell_refinement_flag_accessor,
                                        viennagrid::make_accessor<EdgeType>(edge_refinement_flag));

    refine<ElementTypeOrTagT>(mesh_in, mesh_out, point_accessor_in,
                    viennagrid::make_accessor<EdgeType>(edge_refinement_flag));
  }

  /** @brief Public interface for refinement of a mesh with cell refinement accessor.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param mesh_out                          Output refined mesh
   * @param cell_refinement_flag_accessor     Accessor storing flags if a cell is marked for refinement
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT, typename WrappedMeshConfigOutT,
           typename CellRefinementFlagAccessorT>
  void element_refine(mesh<WrappedMeshConfigInT> const & mesh_in,
                      mesh<WrappedMeshConfigOutT> & mesh_out,
                      CellRefinementFlagAccessorT const cell_refinement_flag_accessor)
  {
    element_refine<ElementTypeOrTagT>(mesh_in, mesh_out, default_point_accessor(mesh_in), cell_refinement_flag_accessor);
  }

  /** @brief Public interface for refinement of cells of a mesh with cell refinement accessor. If there is more than one cell type this funcion will fail.
   *
   * @param mesh_in                         Input mesh
   * @param mesh_out                        Output refined mesh
   * @param cell_refinement_flag_accessor     Accessor storing flags if a cell is marked for refinement
   */
  template<typename WrappedMeshConfigInT, typename WrappedMeshConfigOutT,
            typename CellRefinementFlagAccessorT>
  void cell_refine(mesh<WrappedMeshConfigInT> const & mesh_in,
                   mesh<WrappedMeshConfigOutT> & mesh_out,
                   CellRefinementFlagAccessorT const cell_refinement_flag_accessor)
  {
    typedef mesh<WrappedMeshConfigInT>                            MeshInType;
    typedef typename viennagrid::result_of::cell<MeshInType>::type    CellType;

    element_refine<CellType>(mesh_in, mesh_out, default_point_accessor(mesh_in), cell_refinement_flag_accessor);
  }




  /** @brief Public interface for uniform refinement of a mesh with explicit point accessor, edge refinement accessor and temporary accessors.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param mesh_out                          Output refined mesh
   * @param point_accessor_in                 Point accessor for input points
   * @param vertex_copy_map_                  A vertex copy map for identifying vertices
   * @param edge_refinement_flag_accessor     Accessor storing flags if an edge is marked for refinement
   * @param edge_to_vertex_handle_accessor    Temporary accessor for refined edge to vertex mapping
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT, typename WrappedMeshConfigOutT,
           typename PointAccessorType,
           typename VertexCopyMapT,
           typename EdgeRefinementFlagAccessorT, typename RefinementVertexAccessor>
  void refine_uniformly(mesh<WrappedMeshConfigInT> const & mesh_in,
                        mesh<WrappedMeshConfigOutT> & mesh_out,
                        PointAccessorType point_accessor_in,
                        VertexCopyMapT vertex_copy_map_,
                        EdgeRefinementFlagAccessorT const & edge_refinement_flag_accessor,
                        RefinementVertexAccessor edge_to_vertex_handle_accessor)
  {
    mark_all_edge_refinement( mesh_in, edge_refinement_flag_accessor );
    refine<ElementTypeOrTagT>(mesh_in, mesh_out, point_accessor_in,
                          vertex_copy_map_,
                          edge_refinement_flag_accessor, edge_to_vertex_handle_accessor);
  }

  /** @brief Public interface for uniform refinement of a mesh with explicit point accessor and edge refinement accessor.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param mesh_out                          Output refined mesh
   * @param point_accessor_in                 Point accessor for input points
   * @param edge_refinement_flag_accessor     Accessor storing flags if an edge is marked for refinement
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT, typename WrappedMeshConfigOutT,
           typename PointAccessorType,
           typename EdgeRefinementFlagAccessorT>
  void refine_uniformly(mesh<WrappedMeshConfigInT> const & mesh_in,
                        mesh<WrappedMeshConfigOutT> & mesh_out,
                        PointAccessorType point_accessor_in,
                        EdgeRefinementFlagAccessorT const & edge_refinement_flag_accessor)
  {
    mark_all_edge_refinement( mesh_in, edge_refinement_flag_accessor );
    refine<ElementTypeOrTagT>(mesh_in, mesh_out, point_accessor_in, edge_refinement_flag_accessor);
  }

  /** @brief Public interface for uniform refinement of a mesh with edge refinement accessor.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param mesh_out                          Output refined mesh
   * @param edge_refinement_flag_accessor     Accessor storing flags if an edge is marked for refinement
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT, typename WrappedMeshConfigOutT,
           typename EdgeRefinementFlagAccessorT>
  void refine_uniformly(mesh<WrappedMeshConfigInT> const & mesh_in,
                        mesh<WrappedMeshConfigOutT> & mesh_out,
                        EdgeRefinementFlagAccessorT const & edge_refinement_flag_accessor)
  {
    refine_uniformly<ElementTypeOrTagT>(mesh_in, mesh_out, default_point_accessor(mesh_in), edge_refinement_flag_accessor);
  }

  /** @brief Public interface for uniform refinement of a mesh.
   *
   * @tparam ElementTypeOrTagT              The element type/tag which elements are refined
   * @param mesh_in                         Input mesh
   * @param mesh_out                        Output refined mesh
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT, typename WrappedMeshConfigOutT>
  void refine_uniformly(mesh<WrappedMeshConfigInT> const & mesh_in,
                        mesh<WrappedMeshConfigOutT> & mesh_out)
  {
    typedef mesh<WrappedMeshConfigOutT>                             MeshOutType;
    typedef typename viennagrid::result_of::line<MeshOutType>::type     EdgeType;
    std::deque<bool> edge_refinement_flag;

    refine_uniformly<ElementTypeOrTagT>(mesh_in, mesh_out, viennagrid::make_accessor<EdgeType>(edge_refinement_flag));
  }

  /** @brief Public interface for uniform refinement of cells of a mesh. Will fail if there is more than one cell type.
   *
   * @param mesh_in                         Input mesh
   * @param mesh_out                        Output refined mesh
   */
  template<typename WrappedMeshConfigInT, typename WrappedMeshConfigOutT>
  void cell_refine_uniformly(mesh<WrappedMeshConfigInT> const & mesh_in,
                             mesh<WrappedMeshConfigOutT> & mesh_out)
  {
    typedef mesh<WrappedMeshConfigInT>                            MeshInType;
    typedef typename viennagrid::result_of::cell<MeshInType>::type    CellType;

    refine_uniformly<CellType>(mesh_in, mesh_out);
  }

  /** @brief Refines a mesh based on a hyperplane. All elements which intersects the hyperplane are refined in a way that they don't intersect the hyperplane afterwards.
   *
   * @param src_mesh            The input mesh
   * @param dst_mesh            The output mesh
   * @param hyperplane_point    A point representing the hyperplane
   * @param hyperplane_normal   The normale vector representing the hyperplane
   * @param numeric_config      The numeric config
   */
  template<typename SrcMeshT, typename DstMeshT, typename PointT, typename NumericConfigT>
  void hyperplane_refine(SrcMeshT const & src_mesh, DstMeshT & dst_mesh,
                         PointT const & hyperplane_point, PointT const & hyperplane_normal,
                         NumericConfigT numeric_config)
  {
    typedef typename viennagrid::result_of::cell_tag<SrcMeshT>::type CellTag;
    typedef typename viennagrid::result_of::line<SrcMeshT>::type LineType;

    typedef typename viennagrid::result_of::vertex_handle<DstMeshT>::type DstMeshVertexHandleType;

    viennagrid::vertex_copy_map<SrcMeshT, DstMeshT> vertex_map( dst_mesh );

    std::deque<bool> line_refinement_tag_container;
    typename viennagrid::result_of::accessor<std::deque<bool>, LineType>::type line_refinement_tag_accessor(line_refinement_tag_container);

    std::deque<DstMeshVertexHandleType> line_refinement_vertex_handle_container;
    typename viennagrid::result_of::accessor<std::deque<DstMeshVertexHandleType>, LineType>::type line_refinement_vertex_handle_accessor(line_refinement_vertex_handle_container);

    mark_edges_for_hyperplane_refine(src_mesh, dst_mesh, hyperplane_point, hyperplane_normal, line_refinement_tag_accessor, line_refinement_vertex_handle_accessor, numeric_config);

    viennagrid::simple_refine<CellTag>(src_mesh, dst_mesh,
                                       vertex_map,
                                       line_refinement_tag_accessor,
                                       line_refinement_vertex_handle_accessor);
  }






  /** @brief Public interface for refinement of a mesh with segmentation providing explicit point accessor, edge refinement accessor and temporary accessors
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param segmentation_in                   Input segmentation
   * @param mesh_out                          Output refined mesh
   * @param segmentation_out                  Output refined segmentation
   * @param point_accessor_in                 Point accessor for input points
   * @param edge_refinement_flag_accessor     Accessor storing flags if an edge is marked for refinement
   * @param vertex_copy_map_                  A vertex copy map for identifying vertices
   * @param edge_to_vertex_handle_accessor    Temporary accessor for refined edge to vertex mapping
   */
  template<typename ElementTypeOrTagT,
            typename WrappedMeshConfigInT, typename WrappedSegmentationConfigInT,
            typename WrappedMeshConfigOutT, typename WrappedSegmentationConfigOutT,
            typename PointAccessorT,
            typename VertexCopyMapT,
            typename EdgeRefinementFlagAccessorT, typename RefinementVertexAccessorT>
  void refine(mesh<WrappedMeshConfigInT> const & mesh_in,
              segmentation<WrappedSegmentationConfigInT> const & segmentation_in,
              mesh<WrappedMeshConfigOutT> & mesh_out,
              segmentation<WrappedSegmentationConfigOutT> & segmentation_out,
              PointAccessorT point_accessor_in,
              VertexCopyMapT & vertex_copy_map_,
              EdgeRefinementFlagAccessorT const & edge_refinement_flag_accessor,
              RefinementVertexAccessorT & edge_to_vertex_handle_accessor)
  {
    typedef typename viennagrid::result_of::element_tag<ElementTypeOrTagT>::type CellTag;

    detail::refine_impl<CellTag>(mesh_in, segmentation_in,
                                 mesh_out, segmentation_out,
                                 point_accessor_in,
                                 vertex_copy_map_,
                                 edge_refinement_flag_accessor, edge_to_vertex_handle_accessor);
  }


  /** @brief Public interface for refinement of a mesh with segmentation providing explicit point accessor and edge refinement accessor.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param segmentation_in                   Input segmentation
   * @param mesh_out                          Output refined mesh
   * @param segmentation_out                  Output refined segmentation
   * @param point_accessor_in                 Point accessor for input points
   * @param edge_refinement_flag_accessor     Accessor storing flags if an edge is marked for refinement
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT,  typename WrappedSegmentationConfigInT,
           typename WrappedMeshConfigOutT, typename WrappedSegmentationConfigOutT,
           typename PointAccessorT,
           typename EdgeRefinementFlagAccessorT>
  void refine(mesh<WrappedMeshConfigInT> const & mesh_in,  segmentation<WrappedSegmentationConfigInT> const & segmentation_in,
              mesh<WrappedMeshConfigOutT> & mesh_out,      segmentation<WrappedSegmentationConfigOutT> & segmentation_out,
              PointAccessorT point_accessor_in,
              EdgeRefinementFlagAccessorT const & edge_refinement_flag_accessor)
  {
    typedef mesh<WrappedMeshConfigInT> MeshInT;
    typedef mesh<WrappedMeshConfigOutT> MeshOutT;

    typedef typename viennagrid::result_of::line<MeshOutT>::type EdgeType;

    typedef typename viennagrid::result_of::vertex_handle<MeshOutT>::type VertexHandleType;

    viennagrid::vertex_copy_map<MeshInT, MeshOutT> vertex_map(mesh_out);
    std::deque<VertexHandleType> edge_refinement_vertex_handle_container;
    typename viennagrid::result_of::accessor<std::deque<VertexHandleType>, EdgeType>::type edge_refinement_vertex_handle_accessor(edge_refinement_vertex_handle_container);

    refine<ElementTypeOrTagT>(mesh_in, segmentation_in,
                           mesh_out, segmentation_out,
                           point_accessor_in,
                           vertex_map,
                           edge_refinement_flag_accessor,
                           edge_refinement_vertex_handle_accessor);
  }

  /** @brief Public interface for refinement of a mesh with segmentation providing edge refinement accessor.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param segmentation_in                   Input segmentation
   * @param mesh_out                          Output refined mesh
   * @param segmentation_out                  Output refined segmentation
   * @param edge_refinement_flag_accessor     Accessor storing flags if an edge is marked for refinement
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT,  typename WrappedSegmentationConfigInT,
           typename WrappedMeshConfigOutT, typename WrappedSegmentationConfigOutT,
           typename EdgeRefinementFlagAccessorT>
  void refine(mesh<WrappedMeshConfigInT> const & mesh_in,  segmentation<WrappedSegmentationConfigInT> const & segmentation_in,
              mesh<WrappedMeshConfigOutT> & mesh_out,      segmentation<WrappedSegmentationConfigOutT> & segmentation_out,
              EdgeRefinementFlagAccessorT const & edge_refinement_flag_accessor)
  {
    typedef mesh<WrappedMeshConfigOutT> MeshOutT;

    typedef typename viennagrid::result_of::vertex_handle<MeshOutT>::type VertexHandleType;

    std::deque<VertexHandleType> vertex_refinement_vertex_handle;
    std::deque<VertexHandleType> edge_refinement_vertex_handle;

    refine<ElementTypeOrTagT>(mesh_in, segmentation_in,
                           mesh_out, segmentation_out,
                           default_point_accessor(mesh_in),
                           edge_refinement_flag_accessor);
  }



  /** @brief Public interface for refinement of a mesh with segmentation providing explicit point accessor and cell refinement accessor.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param segmentation_in                   Input segmentation
   * @param mesh_out                          Output refined mesh
   * @param segmentation_out                  Output refined segmentation
   * @param point_accessor_in                 Point accessor for input points
   * @param cell_refinement_flag_accessor     Accessor storing flags if a cell is marked for refinement
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT,   typename WrappedSegmentationConfigInT,
           typename WrappedMeshConfigOutT,  typename WrappedSegmentationConfigOutT,
           typename PointAccessorT,
           typename CellRefinementFlagAccessorT>
  void element_refine(mesh<WrappedMeshConfigInT> const & mesh_in,  segmentation<WrappedSegmentationConfigInT> const & segmentation_in,
                      mesh<WrappedMeshConfigOutT> & mesh_out,      segmentation<WrappedSegmentationConfigOutT> & segmentation_out,
                      PointAccessorT point_accessor_in,
                      CellRefinementFlagAccessorT const cell_refinement_flag_accessor)
  {
    typedef mesh<WrappedMeshConfigOutT> MeshOutT;

    typedef typename viennagrid::result_of::line<MeshOutT>::type EdgeType;

    std::deque<bool> edge_refinement_flag;

    edge_refinement_flag.resize( static_cast<std::size_t>(viennagrid::id_upper_bound<EdgeType>(mesh_in).get()) );

    cell_refinement_to_edge_refinement<ElementTypeOrTagT>(
                                        mesh_in,
                                        cell_refinement_flag_accessor,
                                        viennagrid::make_accessor<EdgeType>(edge_refinement_flag));

    refine<ElementTypeOrTagT>(mesh_in, segmentation_in,
                           mesh_out, segmentation_out,
                           point_accessor_in,
                           viennagrid::make_accessor<EdgeType>(edge_refinement_flag));
  }

  /** @brief Public interface for refinement of a mesh with segmentation providing cell refinement accessor.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param segmentation_in                   Input segmentation
   * @param mesh_out                          Output refined mesh
   * @param segmentation_out                  Output refined segmentation
   * @param cell_refinement_flag_accessor     Accessor storing flags if a cell is marked for refinement
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT,   typename WrappedSegmentationConfigInT,
           typename WrappedMeshConfigOutT,  typename WrappedSegmentationConfigOutT,
           typename CellRefinementFlagAccessorT>
  void element_refine(mesh<WrappedMeshConfigInT> const & mesh_in,  segmentation<WrappedSegmentationConfigInT> const & segmentation_in,
                      mesh<WrappedMeshConfigOutT> & mesh_out,      segmentation<WrappedSegmentationConfigOutT> & segmentation_out,
                      CellRefinementFlagAccessorT const cell_refinement_flag_accessor)
  {
    element_refine<ElementTypeOrTagT>(mesh_in, segmentation_in,
                                   mesh_out, segmentation_out,
                                   default_point_accessor(mesh_in),
                                   cell_refinement_flag_accessor);
  }

  /** @brief Public interface for refinement of cells of a mesh with segmentation providing cell refinement accessor. Will fail if there is more than one cell type.
   *
   * @param mesh_in                           Input mesh
   * @param segmentation_in                   Input segmentation
   * @param mesh_out                          Output refined mesh
   * @param segmentation_out                  Output refined segmentation
   * @param cell_refinement_flag_accessor     Accessor storing flags if a cell is marked for refinement
   */
  template<typename WrappedMeshConfigInT,   typename WrappedSegmentationConfigInT,
           typename WrappedMeshConfigOutT,  typename WrappedSegmentationConfigOutT,
           typename CellRefinementFlagAccessorT>
  void cell_refine(mesh<WrappedMeshConfigInT> const & mesh_in,  segmentation<WrappedSegmentationConfigInT> const & segmentation_in,
                   mesh<WrappedMeshConfigOutT> & mesh_out,      segmentation<WrappedSegmentationConfigOutT> & segmentation_out,
                   CellRefinementFlagAccessorT const cell_refinement_flag_accessor)
  {
    typedef mesh<WrappedMeshConfigInT>                              MeshInType;
    typedef typename viennagrid::result_of::cell_tag<MeshInType>::type  CellTag;
    element_refine<CellTag>(mesh_in, segmentation_in,
                            mesh_out, segmentation_out,
                            default_point_accessor(mesh_in),
                            cell_refinement_flag_accessor);
  }






  /** @brief Public interface for uniform refinement of a mesh with segmentation providing explicit point accessor, edge refinement accessor and temporary accessors.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param segmentation_in                   Input segmentation
   * @param mesh_out                          Output refined mesh
   * @param segmentation_out                  Output refined segmentation
   * @param point_accessor_in                 Point accessor for input points
   * @param vertex_copy_map_                  A vertex copy map for identifying vertices
   * @param edge_refinement_flag_accessor     Accessor storing flags if an edge is marked for refinement
   * @param edge_to_vertex_handle_accessor    Temporary accessor for refined edge to vertex mapping
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT,   typename WrappedSegmentationConfigInT,
           typename WrappedMeshConfigOutT,  typename WrappedSegmentationConfigOutT,
           typename PointAccessorT,
           typename VertexCopyMapT,
           typename EdgeRefinementFlagAccessorT, typename RefinementVertexAccessorT>
  void refine_uniformly(mesh<WrappedMeshConfigInT> const & mesh_in,  segmentation<WrappedSegmentationConfigInT> const & segmentation_in,
                        mesh<WrappedMeshConfigOutT> & mesh_out,      segmentation<WrappedSegmentationConfigOutT> & segmentation_out,
                        PointAccessorT point_accessor_in,
                        VertexCopyMapT & vertex_copy_map_,
                        EdgeRefinementFlagAccessorT const & edge_refinement_flag_accessor,
                        RefinementVertexAccessorT & edge_to_vertex_handle_accessor)
  {
    mark_all_edge_refinement( mesh_in, edge_refinement_flag_accessor );
    refine<ElementTypeOrTagT>(mesh_in, segmentation_in,
                           mesh_out, segmentation_out,
                           point_accessor_in,
                           vertex_copy_map_,
                           edge_refinement_flag_accessor, edge_to_vertex_handle_accessor);
  }

  /** @brief Public interface for uniform refinement of a mesh with segmentation providing explicit point accessor and edge refinement accessor.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param segmentation_in                   Input segmentation
   * @param mesh_out                          Output refined mesh
   * @param segmentation_out                  Output refined segmentation
   * @param point_accessor_in                 Point accessor for input points
   * @param edge_refinement_flag_accessor     Accessor storing flags if an edge is marked for refinement
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT,   typename WrappedSegmentationConfigInT,
           typename WrappedMeshConfigOutT,  typename WrappedSegmentationConfigOutT,
           typename PointAccessorT,
           typename EdgeRefinementFlagAccessorT>
  void refine_uniformly(mesh<WrappedMeshConfigInT> const & mesh_in,  segmentation<WrappedSegmentationConfigInT> const & segmentation_in,
                        mesh<WrappedMeshConfigOutT> & mesh_out,      segmentation<WrappedSegmentationConfigOutT> & segmentation_out,
                        PointAccessorT point_accessor_in,
                        EdgeRefinementFlagAccessorT const & edge_refinement_flag_accessor)
  {
    mark_all_edge_refinement( mesh_in, edge_refinement_flag_accessor );
    refine<ElementTypeOrTagT>(mesh_in, segmentation_in,
                           mesh_out, segmentation_out,
                           point_accessor_in,
                           edge_refinement_flag_accessor);
  }

  /** @brief Public interface for uniform refinement of a mesh with segmentation providing edge refinement accessor.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param segmentation_in                   Input segmentation
   * @param mesh_out                          Output refined mesh
   * @param segmentation_out                  Output refined segmentation
   * @param edge_refinement_flag_accessor     Accessor storing flags if an edge is marked for refinement
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT,   typename WrappedSegmentationConfigInT,
           typename WrappedMeshConfigOutT,  typename WrappedSegmentationConfigOutT,
           typename EdgeRefinementFlagAccessorT>
  void refine_uniformly(mesh<WrappedMeshConfigInT> const & mesh_in,  segmentation<WrappedSegmentationConfigInT> const & segmentation_in,
                        mesh<WrappedMeshConfigOutT> & mesh_out,      segmentation<WrappedSegmentationConfigOutT> & segmentation_out,
                        EdgeRefinementFlagAccessorT const & edge_refinement_flag_accessor)
  {
    refine_uniformly<ElementTypeOrTagT>(mesh_in, segmentation_in, mesh_out, segmentation_out, default_point_accessor(mesh_in), edge_refinement_flag_accessor);
  }

  /** @brief Public interface for uniform refinement of a mesh with segmentation.
   *
   * @tparam ElementTypeOrTagT                The element type/tag which elements are refined
   * @param mesh_in                           Input mesh
   * @param segmentation_in                   Input segmentation
   * @param mesh_out                          Output refined mesh
   * @param segmentation_out                  Output refined segmentation
   */
  template<typename ElementTypeOrTagT,
           typename WrappedMeshConfigInT,   typename WrappedSegmentationConfigInT,
           typename WrappedMeshConfigOutT,  typename WrappedSegmentationConfigOutT>
  void refine_uniformly(mesh<WrappedMeshConfigInT> const & mesh_in,  segmentation<WrappedSegmentationConfigInT> const & segmentation_in,
                        mesh<WrappedMeshConfigOutT> & mesh_out,      segmentation<WrappedSegmentationConfigOutT> & segmentation_out)
  {
    typedef mesh<WrappedMeshConfigOutT>                           MeshOutType;
    typedef typename viennagrid::result_of::line<MeshOutType>::type   EdgeType;
    std::deque<bool> edge_refinement_flag;

    refine_uniformly<ElementTypeOrTagT>(mesh_in, segmentation_in, mesh_out, segmentation_out, viennagrid::make_accessor<EdgeType>(edge_refinement_flag));
  }

  /** @brief Public interface for uniform refinement of cells of a mesh with segmentation. Will fail if there is more than one cell type.
   *
   * @param mesh_in                           Input mesh
   * @param segmentation_in                   Input segmentation
   * @param mesh_out                          Output refined mesh
   * @param segmentation_out                  Output refined segmentation
   */
  template<typename WrappedMeshConfigInT,   typename WrappedSegmentationConfigInT,
           typename WrappedMeshConfigOutT,  typename WrappedSegmentationConfigOutT>
  void cell_refine_uniformly(mesh<WrappedMeshConfigInT> const & mesh_in,  segmentation<WrappedSegmentationConfigInT> const & segmentation_in,
                             mesh<WrappedMeshConfigOutT> & mesh_out,      segmentation<WrappedSegmentationConfigOutT> & segmentation_out)
  {
    typedef mesh<WrappedMeshConfigInT>                            MeshInType;
    typedef typename viennagrid::result_of::cell<MeshInType>::type    CellType;
    refine_uniformly<CellType>(mesh_in, segmentation_in, mesh_out, segmentation_out);
  }

  /** @brief Refines a mesh and a segmentation based on a hyperplane. All elements which intersects the hyperplane are refined in a way that they don't intersect the hyperplane afterwards.
   *
   * @param src_mesh            The input mesh
   * @param src_segmentation    The input segmentation
   * @param dst_mesh            The output mesh
   * @param dst_segmentation    The output segmentation
   * @param hyperplane_point    A point representing the hyperplane
   * @param hyperplane_normal   The normale vector representing the hyperplane
   * @param numeric_config      The numeric config
   */
  template<typename SrcMeshT, typename SrcSegmentationT, typename DstMeshT, typename DstSegmentationT, typename PointT, typename NumericConfigT>
  void hyperplane_refine(SrcMeshT const & src_mesh, SrcSegmentationT const & src_segmentation,
                         DstMeshT & dst_mesh, DstSegmentationT & dst_segmentation,
                         PointT const & hyperplane_point, PointT const & hyperplane_normal,
                         NumericConfigT numeric_config)
  {
    typedef typename viennagrid::result_of::cell_tag<SrcMeshT>::type CellTag;
    typedef typename viennagrid::result_of::line<SrcMeshT>::type LineType;
    typedef typename viennagrid::result_of::vertex_handle<DstMeshT>::type DstMeshVertexHandleType;

    viennagrid::vertex_copy_map<SrcMeshT, DstMeshT> vertex_map( dst_mesh );

    std::deque<bool> line_refinement_tag_container;
    typename viennagrid::result_of::accessor<std::deque<bool>, LineType>::type line_refinement_tag_accessor(line_refinement_tag_container);

    std::deque<DstMeshVertexHandleType> line_refinement_vertex_handle_container;
    typename viennagrid::result_of::accessor<std::deque<DstMeshVertexHandleType>, LineType>::type line_refinement_vertex_handle_accessor(line_refinement_vertex_handle_container);

    mark_edges_for_hyperplane_refine(src_mesh, dst_mesh, hyperplane_point, hyperplane_normal, line_refinement_tag_accessor, line_refinement_vertex_handle_accessor, numeric_config);


    viennagrid::simple_refine<CellTag>(src_mesh, src_segmentation,
                                       dst_mesh, dst_segmentation,
                                       vertex_map,
                                       line_refinement_tag_accessor,
                                       line_refinement_vertex_handle_accessor);
  }


}

#endif
