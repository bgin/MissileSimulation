#ifndef VIENNAGRID_ELEMENT_CREATION_HPP
#define VIENNAGRID_ELEMENT_CREATION_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include "viennagrid/mesh/mesh.hpp"
#include "viennagrid/mesh/segmentation.hpp"
#include "viennagrid/topology/plc.hpp"
#include "viennagrid/algorithm/norm.hpp"

/** @file viennagrid/mesh/element_creation.hpp
    @brief Contains functions for creating elements within a mesh or segment
*/

namespace viennagrid
{
  // implementation for make_element and make_element_with_id
  template<typename ElementTagT>
  struct make_element_impl
  {
    /** @brief Generic implementation for creating an element. For internal use only. */
    template<typename MeshOrSegmentHandleTypeT, typename VertexHandleIteratorT>
    static typename result_of::handle<MeshOrSegmentHandleTypeT, ElementTagT>::type
    make(MeshOrSegmentHandleTypeT & mesh_obj,
         VertexHandleIteratorT vertices_begin,
         VertexHandleIteratorT const & vertices_end)
    {
      typedef typename viennagrid::result_of::element<MeshOrSegmentHandleTypeT, ElementTagT>::type ElementType;
      ElementType element = ElementType( detail::inserter(mesh_obj).get_physical_container_collection() );

      unsigned int element_index = 0;
      for ( ; vertices_begin != vertices_end; ++vertices_begin, ++element_index )
          viennagrid::set_vertex( element, *vertices_begin, element_index );

      return detail::push_element<true, true>(mesh_obj, element).first;
    }

    /** @brief Generic implementation for creating an element with a specific. For internal use only. */
    template<typename MeshOrSegmentHandleTypeT, typename VertexHandleIteratorT, typename IDT>
    static typename result_of::handle<MeshOrSegmentHandleTypeT, ElementTagT>::type
    make(MeshOrSegmentHandleTypeT & mesh_obj,
         VertexHandleIteratorT vertices_begin,
         VertexHandleIteratorT const & vertices_end,
         IDT id)
    {
      typedef typename viennagrid::result_of::element<MeshOrSegmentHandleTypeT, ElementTagT>::type ElementType;
      ElementType element = ElementType( detail::inserter(mesh_obj).get_physical_container_collection() );

      element.id( id );

      unsigned int element_index = 0;
      for ( ; vertices_begin != vertices_end; ++vertices_begin, ++element_index )
          viennagrid::set_vertex( element, *vertices_begin, element_index );

      return detail::push_element<false, true>(mesh_obj, element ).first;
    }
  };

  // specialization for PLC: no implementation! Use make_plc instead
  template<>
  struct make_element_impl<plc_tag>
  {
    /** @brief Generic implementation for creating a PLC is NOT provided, use make_plc instead. */
    template<typename MeshOrSegmentHandleTypeT, typename VertexHandleIteratorT>
    static typename result_of::handle<MeshOrSegmentHandleTypeT, plc_tag>::type
    make(MeshOrSegmentHandleTypeT & mesh_obj,
         VertexHandleIteratorT vertices_begin,
         VertexHandleIteratorT const & vertices_end);

    /** @brief Generic implementation for creating a PLC with a specific ID is NOT provided, use make_plc instead. */
    template<typename MeshOrSegmentHandleTypeT, typename VertexHandleIteratorT, typename IDT>
    static typename result_of::handle<MeshOrSegmentHandleTypeT, plc_tag>::type
    make(MeshOrSegmentHandleTypeT & mesh_obj,
         VertexHandleIteratorT vertices_begin,
         VertexHandleIteratorT const & vertices_end,
         IDT id);
  };



  // doxygen doku in forwards.hpp
  template<typename ElementTypeOrTagT, typename MeshOrSegmentHandleTypeT, typename VertexHandleIteratorT>
  typename result_of::handle<MeshOrSegmentHandleTypeT, ElementTypeOrTagT>::type
  make_element(
        MeshOrSegmentHandleTypeT & mesh_obj,
        VertexHandleIteratorT vertices_begin,
        VertexHandleIteratorT const & vertices_end)
  {
    typedef typename viennagrid::result_of::element_tag<ElementTypeOrTagT>::type ElementTagT;
    return make_element_impl<ElementTagT>::make( mesh_obj, vertices_begin, vertices_end );
  }

  // doxygen doku in forwards.hpp
  template<typename ElementTypeOrTagT, typename MeshOrSegmentHandleTypeT, typename VertexHandleIteratorT, typename IDT>
  typename result_of::handle<MeshOrSegmentHandleTypeT, ElementTypeOrTagT>::type
  make_element_with_id(
        MeshOrSegmentHandleTypeT & mesh_obj,
        VertexHandleIteratorT vertices_begin,
        VertexHandleIteratorT const & vertices_end,
        IDT id)
  {
    typedef typename viennagrid::result_of::element_tag<ElementTypeOrTagT>::type ElementTagT;
    return make_element_impl<ElementTagT>::make( mesh_obj, vertices_begin, vertices_end, id );
  }



  /** @brief Function for creating an cell within a mesh or a segment
  *
  * @param  mesh_segment            The mesh or segment object where the cell should be created
  * @param  vertices_begin          An iterator pointing to the first vertex handle of the cell
  * @param  vertices_end            An iterator defining the end of the vertices
  * @return                         A handle to the created cell
  */
  template<typename MeshOrSegmentHandleTypeT, typename VertexHandleIteratorT>
  typename result_of::cell_handle<MeshOrSegmentHandleTypeT>::type
  make_cell(
        MeshOrSegmentHandleTypeT & mesh_segment,
        VertexHandleIteratorT vertices_begin,
        VertexHandleIteratorT const & vertices_end)
  {
    typedef typename viennagrid::result_of::cell_tag<MeshOrSegmentHandleTypeT>::type CellTagType;
    return make_element<CellTagType>( mesh_segment, vertices_begin, vertices_end );
  }


  /** @brief Function for creating an cell with ID within a mesh or a segment
  *
  * @param  mesh_segment            The mesh or segment object where the cell should be created
  * @param  vertices_begin          An iterator pointing to the first vertex handle of the cell
  * @param  vertices_end            An iterator defining the end of the vertices
  * @param  id                      The cell ID to be used for the cell within the mesh or segment
  * @return                         A handle to the created cell
  */
  template<typename MeshOrSegmentHandleTypeT, typename VertexHandleIteratorT>
  typename result_of::cell_handle<MeshOrSegmentHandleTypeT>::type
  make_cell_with_id(
        MeshOrSegmentHandleTypeT & mesh_segment,
        VertexHandleIteratorT vertices_begin,
        VertexHandleIteratorT const & vertices_end,
        typename viennagrid::result_of::cell<MeshOrSegmentHandleTypeT>::type::id_type id)
  {
    typedef typename viennagrid::result_of::cell_tag<MeshOrSegmentHandleTypeT>::type CellTagType;
    return make_element_with_id<CellTagType>( mesh_segment, vertices_begin, vertices_end, id );
  }






  // doxygen doku in forwards.hpp
  template<typename MeshOrSegmentHandleTypeT>
  typename result_of::vertex_handle<MeshOrSegmentHandleTypeT>::type make_vertex(MeshOrSegmentHandleTypeT & mesh_segment)
  {
    typedef typename result_of::element<MeshOrSegmentHandleTypeT, vertex_tag>::type element_type;
    return detail::push_element<true, true>(mesh_segment, element_type() ).first;
  }

  // doxygen doku in forwards.hpp
  template<typename MeshOrSegmentHandleTypeT>
  typename result_of::vertex_handle<MeshOrSegmentHandleTypeT>::type make_vertex(
        MeshOrSegmentHandleTypeT & mesh_obj,
        typename result_of::point<MeshOrSegmentHandleTypeT>::type const & point)
  {
    typename viennagrid::result_of::vertex_handle<MeshOrSegmentHandleTypeT>::type vtx_handle = make_vertex(mesh_obj);
    viennagrid::point(mesh_obj, vtx_handle) = point;
    return vtx_handle;
  }

  // doxygen doku in forwards.hpp
  template<typename MeshOrSegmentHandleTypeT>
  typename result_of::vertex_handle<MeshOrSegmentHandleTypeT>::type make_vertex_with_id(
        MeshOrSegmentHandleTypeT & mesh_obj,
        typename viennagrid::result_of::element<MeshOrSegmentHandleTypeT, vertex_tag>::type::id_type id,
        typename result_of::point<MeshOrSegmentHandleTypeT>::type const & point)
  {
    typedef typename result_of::vertex<MeshOrSegmentHandleTypeT>::type VertexType;
    VertexType element;
    element.id( id );

    typename result_of::vertex_handle<MeshOrSegmentHandleTypeT>::type ret = detail::push_element<false, true>(mesh_obj, element ).first;
    viennagrid::point(mesh_obj, ret) = point;

    return ret;
  }

  // doxygen doku in forwards.hpp
  template<typename MeshOrSegmentHandleTypeT>
  typename result_of::vertex_handle<MeshOrSegmentHandleTypeT>::type make_unique_vertex(
        MeshOrSegmentHandleTypeT & mesh_obj,
        typename result_of::point<MeshOrSegmentHandleTypeT>::type const & point,
        typename result_of::coord<MeshOrSegmentHandleTypeT>::type tolerance)
  {
    typedef typename result_of::element_range<MeshOrSegmentHandleTypeT, vertex_tag>::type vertex_range_type;
    typedef typename result_of::iterator<vertex_range_type>::type vertex_range_iterator;

    if (tolerance > 0)
    {
      vertex_range_type vertices(mesh_obj);
      for (vertex_range_iterator hit = vertices.begin(); hit != vertices.end(); ++hit)
      {
          if (viennagrid::norm_2( point - viennagrid::point(mesh_obj, *hit) ) < tolerance )
              return hit.handle();
      }
    }

    return make_vertex(mesh_obj, point);
  }

  // doxygen doku in forwards.hpp
  template<typename MeshOrSegmentHandleTypeT>
  typename result_of::vertex_handle<MeshOrSegmentHandleTypeT>::type make_unique_vertex(
        MeshOrSegmentHandleTypeT & mesh_obj,
        typename result_of::point<MeshOrSegmentHandleTypeT>::type const & p)
  {
    return make_unique_vertex( mesh_obj, p, viennagrid::norm_2(p) / 1e6 );
  }


  // doxygen doku in forwards.hpp
  template<typename MeshOrSegmentHandleTypeT, typename VertexHandleT>
  typename result_of::line_handle<MeshOrSegmentHandleTypeT>::type make_line(
        MeshOrSegmentHandleTypeT & mesh_obj,
        VertexHandleT v0, VertexHandleT v1)
  {
    viennagrid::static_array<VertexHandleT, 2> handles;
    handles[0] = v0;
    handles[1] = v1;

    return make_element<viennagrid::line_tag>( mesh_obj, handles.begin(), handles.end() );
  }

  // doxygen doku in forwards.hpp
  template<typename MeshOrSegmentHandleTypeT, typename VertexHandleT>
  typename result_of::edge_handle<MeshOrSegmentHandleTypeT>::type make_edge(
        MeshOrSegmentHandleTypeT & mesh_obj,
        VertexHandleT v0, VertexHandleT v1)
  {
    viennagrid::static_array<VertexHandleT, 2> handles;
    handles[0] = v0;
    handles[1] = v1;

    return make_element<viennagrid::edge_tag>( mesh_obj, handles.begin(), handles.end() );
  }

  // doxygen doku in forwards.hpp
  template<typename MeshOrSegmentHandleTypeT, typename VertexHandleT>
  typename result_of::triangle_handle<MeshOrSegmentHandleTypeT>::type make_triangle(
        MeshOrSegmentHandleTypeT & mesh_obj,
        VertexHandleT v0, VertexHandleT v1, VertexHandleT v2)
  {
    viennagrid::static_array<VertexHandleT, 3> handles;
    handles[0] = v0;
    handles[1] = v1;
    handles[2] = v2;

    return make_element<viennagrid::triangle_tag>( mesh_obj, handles.begin(), handles.end() );
  }

  // doxygen doku in forwards.hpp
  template<typename MeshOrSegmentHandleTypeT, typename VertexHandleT>
  typename result_of::quadrilateral_handle<MeshOrSegmentHandleTypeT>::type make_quadrilateral(
        MeshOrSegmentHandleTypeT & mesh_obj,
        VertexHandleT v0, VertexHandleT v1, VertexHandleT v2, VertexHandleT v3)
  {
    viennagrid::static_array<VertexHandleT, 4> handles;
    handles[0] = v0;
    handles[1] = v1;
    handles[2] = v2;
    handles[3] = v3;

    return make_element<viennagrid::quadrilateral_tag>( mesh_obj, handles.begin(), handles.end() );
  }


  // doxygen doku in forwards.hpp
  template<typename MeshOrSegmentHandleTypeT, typename LineHandleIteratorT, typename VertexHandleIteratorT, typename PointIteratorT>
  typename result_of::plc_handle<MeshOrSegmentHandleTypeT>::type make_plc(
        MeshOrSegmentHandleTypeT & mesh_obj,
        LineHandleIteratorT    lines_begin,           LineHandleIteratorT     lines_end,
        VertexHandleIteratorT  loose_vertices_begin,  VertexHandleIteratorT   loose_vertices_end,
        PointIteratorT         hole_points_begin,     PointIteratorT          hole_points_end)
  {
    typedef typename viennagrid::result_of::element<MeshOrSegmentHandleTypeT, plc_tag>::type PLCType;;
    typedef typename result_of::handle<MeshOrSegmentHandleTypeT, plc_tag>::type PLCHandleType;
    PLCType plc( detail::inserter(mesh_obj).get_physical_container_collection() );

    for ( ; lines_begin != lines_end; ++lines_begin)
      plc.container( viennagrid::line_tag() ).insert_unique_handle( *lines_begin );

    for ( ; loose_vertices_begin != loose_vertices_end; ++loose_vertices_begin)
      plc.container( viennagrid::vertex_tag() ).insert_unique_handle( *loose_vertices_begin );

    PLCHandleType handle = viennagrid::detail::push_element<true, true>(mesh_obj, plc ).first;

    PLCType & inserted_plc = viennagrid::dereference_handle(mesh_obj, handle);

    std::copy(hole_points_begin, hole_points_end, std::back_inserter( inserted_plc.appendix() ) );
    return handle;
  }

  // doxygen doku in forwards.hpp
  template<typename MeshOrSegmentHandleTypeT, typename LineHandleIteratorT, typename VertexHandleIteratorT>
  typename result_of::plc_handle<MeshOrSegmentHandleTypeT>::type make_plc(
        MeshOrSegmentHandleTypeT & mesh_obj,
        LineHandleIteratorT    lines_begin,           LineHandleIteratorT     lines_end,
        VertexHandleIteratorT  loose_vertices_begin,  VertexHandleIteratorT   loose_vertices_end)
  {
    typedef typename viennagrid::result_of::point<MeshOrSegmentHandleTypeT>::type PointType;
    PointType tmp;
    return make_plc(mesh_obj, lines_begin, lines_end, loose_vertices_begin, loose_vertices_end, &tmp, &tmp);
  }

  template<typename MeshOrSegmentHandleTypeT, typename LineHandleIteratorT>
  typename result_of::plc_handle<MeshOrSegmentHandleTypeT>::type make_plc(
        MeshOrSegmentHandleTypeT & mesh_obj,
        LineHandleIteratorT    lines_begin,           LineHandleIteratorT     lines_end)
  {
    typedef typename viennagrid::result_of::vertex_handle<MeshOrSegmentHandleTypeT>::type VertexHandleType;
    VertexHandleType tmp;
    return make_plc(mesh_obj, lines_begin, lines_end, &tmp, &tmp);
  }





  // doxygen doku in forwards.hpp
  template<typename MeshOrSegmentHandleTypeT, typename VertexHandleT>
  typename result_of::tetrahedron_handle<MeshOrSegmentHandleTypeT>::type make_tetrahedron(
        MeshOrSegmentHandleTypeT & mesh_obj,
        VertexHandleT v0, VertexHandleT v1, VertexHandleT v2, VertexHandleT v3)
  {
    viennagrid::static_array<VertexHandleT, 4> handles;
    handles[0] = v0;
    handles[1] = v1;
    handles[2] = v2;
    handles[3] = v3;

    return make_element<viennagrid::tetrahedron_tag>( mesh_obj, handles.begin(), handles.end() );
  }


  // doxygen doku in forwards.hpp
  template<typename MeshOrSegmentHandleTypeT, typename VertexHandleT>
  typename result_of::hexahedron_handle<MeshOrSegmentHandleTypeT>::type make_hexahedron(
        MeshOrSegmentHandleTypeT & mesh_obj,
        VertexHandleT v0, VertexHandleT v1, VertexHandleT v2, VertexHandleT v3,
        VertexHandleT v4, VertexHandleT v5, VertexHandleT v6, VertexHandleT v7)
  {
    viennagrid::static_array<VertexHandleT, 8> handles;
    handles[0] = v0;
    handles[1] = v1;
    handles[2] = v2;
    handles[3] = v3;
    handles[4] = v4;
    handles[5] = v5;
    handles[6] = v6;
    handles[7] = v7;

    return make_element<viennagrid::hexahedron_tag>( mesh_obj, handles.begin(), handles.end() );
  }


  // doxygen doku in forwards.hpp
  template<typename ElementT, typename MeshOrSegmentHandleT>
  typename viennagrid::result_of::handle<
      MeshOrSegmentHandleT,
      typename viennagrid::result_of::element_tag<ElementT>::type
    >::type copy_element( ElementT const & element, MeshOrSegmentHandleT & mesh_segment,
                          typename viennagrid::result_of::coord<MeshOrSegmentHandleT>::type tolerance )
  {
    typedef typename viennagrid::result_of::element_tag<ElementT>::type             ElementTag;
    typedef typename viennagrid::result_of::vertex_handle<MeshOrSegmentHandleT>::type   VertexHandleType;
    std::vector<VertexHandleType> vertex_handles;

    typedef typename viennagrid::result_of::const_vertex_range<ElementT>::type      VertexRangeType;
    typedef typename viennagrid::result_of::iterator<VertexRangeType>::type         VertexRangeIterator;

    VertexRangeType vertices(element);
    for (VertexRangeIterator vit = vertices.begin(); vit != vertices.end(); ++vit)
      vertex_handles.push_back( make_unique_vertex(mesh_segment, viennagrid::point(*vit)), tolerance );

    return make_element<ElementTag>( mesh_segment, vertex_handles.begin(), vertex_handles.end() );
  }

  // doxygen doku in forwards.hpp
  template<typename ElementT, typename MeshOrSegmentHandleT>
  typename viennagrid::result_of::handle<
      MeshOrSegmentHandleT,
      typename viennagrid::result_of::element_tag<ElementT>::type
    >::type copy_element( ElementT const & element, MeshOrSegmentHandleT & mesh_segment )
  {
    copy_element(element, mesh_segment, -1.0);
  }

  namespace detail
  {
    template<typename ElementTagT>
    struct copy_elements_impl
    {
      /** @brief Generic implementation for copying elements. For internal use only. */
      template<typename ElementIteratorT, typename OutputMeshOrSegmentHandleT>
      static void copy_elements(ElementIteratorT const & begin, ElementIteratorT const & end,
                      OutputMeshOrSegmentHandleT & output_mesh,
                      typename viennagrid::result_of::coord<OutputMeshOrSegmentHandleT>::type tolerance )
      {
        typedef typename std::iterator_traits<ElementIteratorT>::value_type ElementType;
        typedef typename viennagrid::result_of::element_tag<ElementType>::type ElementTagType;

        typedef typename viennagrid::result_of::vertex_id<ElementType>::type VertexIDType;
        //typedef typename viennagrid::result_of::vertex_handle<ElementType>::type VertexHandleType;
        typedef typename viennagrid::result_of::vertex_handle<OutputMeshOrSegmentHandleT>::type OutputVertexHandleType;

        typedef typename viennagrid::result_of::const_vertex_range<ElementType>::type ConstVertexOnElementRangeType;
        typedef typename viennagrid::result_of::iterator<ConstVertexOnElementRangeType>::type ConstVertexOnElementIteratorType;

        std::map<VertexIDType, OutputVertexHandleType> vertex_map;
        for (ElementIteratorT eit = begin; eit != end; ++eit)
        {
          ConstVertexOnElementRangeType vertices_on_element( *eit );
          std::vector<OutputVertexHandleType> vtx_handles( vertices_on_element.size() );

          unsigned int index = 0;
          for (ConstVertexOnElementIteratorType vit = vertices_on_element.begin(); vit != vertices_on_element.end(); ++vit, ++index)
          {
            typename std::map<VertexIDType, OutputVertexHandleType>::iterator it = vertex_map.find( vit->id() );
            if (it == vertex_map.end())
            {
              vtx_handles[index] = viennagrid::make_unique_vertex( output_mesh, viennagrid::point(*vit), tolerance );
              vertex_map[vit->id()] = vtx_handles[index];
            }
            else
              vtx_handles[index] = it->second;
          }

          viennagrid::make_element<ElementTagType>( output_mesh, vtx_handles.begin(), vtx_handles.end() );
        }
      }

      /** @brief Generic implementation for copying element based on handles. For internal use only. */
      template<typename InputMeshOrSegmentHandleT, typename ElementHandleIteratorT, typename OutputMeshOrSegmentHandleT>
      static void copy_elements_by_handle(InputMeshOrSegmentHandleT const & input_mesh,
                                ElementHandleIteratorT const & begin, ElementHandleIteratorT const & end,
                                OutputMeshOrSegmentHandleT & output_mesh,
                                typename viennagrid::result_of::coord<OutputMeshOrSegmentHandleT>::type tolerance )
      {
        typedef typename std::iterator_traits<ElementHandleIteratorT>::value_type ElementHandleType;
        typedef typename viennagrid::detail::result_of::value_type<ElementHandleType>::type ElementType;
        typedef typename viennagrid::result_of::element_tag<ElementType>::type ElementTagType;

        typedef typename viennagrid::result_of::vertex_id<ElementType>::type VertexIDType;
        typedef typename viennagrid::result_of::vertex_handle<ElementType>::type VertexHandleType;

        typedef typename viennagrid::result_of::const_vertex_range<ElementType>::type ConstVertexOnElementRangeType;
        typedef typename viennagrid::result_of::iterator<ConstVertexOnElementRangeType>::type ConstVertexOnElementIteratorType;

        std::map<VertexIDType, VertexHandleType> vertex_map;
        for (ElementHandleIteratorT eit = begin; eit != end; ++eit)
        {
          ConstVertexOnElementRangeType vertices_on_element( viennagrid::dereference_handle(input_mesh, *eit) );
          std::vector<VertexHandleType> vtx_handles( vertices_on_element.size() );

          unsigned int index = 0;
          for (ConstVertexOnElementIteratorType vit = vertices_on_element.begin(); vit != vertices_on_element.end(); ++vit, ++index)
          {
            typename std::map<VertexIDType, VertexHandleType>::iterator it = vertex_map.find( vit->id() );
            if (it == vertex_map.end())
            {
              vtx_handles[index] = viennagrid::make_unique_vertex( output_mesh, viennagrid::point(*vit), tolerance );
              vertex_map[vit->id()] = vtx_handles[index];
            }
            else
              vtx_handles[index] = it->second;
          }

          viennagrid::make_element<ElementTagType>( output_mesh, vtx_handles.begin(), vtx_handles.end() );
        }
      }
    };


    template<>
    struct copy_elements_impl<plc_tag>
    {
      /** @brief Generic implementation for copying PLCs. For internal use only. */
      template<typename ElementIteratorT, typename OutputMeshOrSegmentHandleT>
      static void copy_elements(ElementIteratorT const & begin, ElementIteratorT const & end,
                      OutputMeshOrSegmentHandleT & output_mesh,
                      typename viennagrid::result_of::coord<OutputMeshOrSegmentHandleT>::type tolerance )
      {
        typedef typename std::iterator_traits<ElementIteratorT>::value_type ElementType;

        typedef typename viennagrid::result_of::vertex_id<ElementType>::type VertexIDType;
        typedef typename viennagrid::result_of::vertex_handle<ElementType>::type VertexHandleType;

        typedef typename viennagrid::result_of::line_id<ElementType>::type LineIDType;
        typedef typename viennagrid::result_of::line_handle<ElementType>::type LineHandleType;

        typedef typename viennagrid::result_of::const_line_range<ElementType>::type ConstLineOnElementRangeType;
        typedef typename viennagrid::result_of::iterator<ConstLineOnElementRangeType>::type ConstLineOnElementIteratorType;

        std::map<VertexIDType, VertexHandleType> vertex_map;
        std::map<LineIDType, LineHandleType> line_map;


        for (ElementIteratorT eit = begin; eit != end; ++eit)
        {
          ConstLineOnElementRangeType lines_on_element( *eit );
          std::vector<LineHandleType> line_handles( lines_on_element.size() );

          unsigned int line_index = 0;
          for (ConstLineOnElementIteratorType lit = lines_on_element.begin(); lit != lines_on_element.end(); ++lit, ++line_index)
          {
            typename std::map<LineIDType, LineHandleType>::iterator it1 = line_map.find( lit->id() );
            if (it1 == line_map.end())
            {
              VertexHandleType vtx_handles[2];
              for (unsigned int vertex_index = 0; vertex_index != 2; ++vertex_index)
              {
                typename std::map<VertexIDType, VertexHandleType>::iterator it2 = vertex_map.find( viennagrid::vertices(*lit)[vertex_index].id() );
                if (it2 == vertex_map.end())
                {
                  vtx_handles[vertex_index] = viennagrid::make_unique_vertex( output_mesh, viennagrid::point( viennagrid::vertices(*lit)[vertex_index] ), tolerance );
                  vertex_map[ viennagrid::vertices(*lit)[vertex_index].id() ] = vtx_handles[vertex_index];
                }
                else
                  vtx_handles[vertex_index] = it2->second;
              }

              line_handles[line_index] = viennagrid::make_line( output_mesh, vtx_handles[0], vtx_handles[1] );
              line_map[lit->id()] = line_handles[line_index];
            }
            else
              line_handles[line_index] = it1->second;
          }

          viennagrid::make_plc( output_mesh, line_handles.begin(), line_handles.end() );
        }
      }

      /** @brief Generic implementation for copying PLC based on handles. For internal use only. */
      template<typename InputMeshOrSegmentHandleT, typename ElementHandleIteratorT, typename OutputMeshOrSegmentHandleT>
      static void copy_elements_by_handle(InputMeshOrSegmentHandleT const & input_mesh,
                                ElementHandleIteratorT const & begin, ElementHandleIteratorT const & end,
                                OutputMeshOrSegmentHandleT & output_mesh,
                                typename viennagrid::result_of::coord<OutputMeshOrSegmentHandleT>::type tolerance )
      {
        typedef typename std::iterator_traits<ElementHandleIteratorT>::value_type ElementHandleType;
        typedef typename viennagrid::detail::result_of::value_type<ElementHandleType>::type ElementType;

        typedef typename viennagrid::result_of::vertex_id<ElementType>::type VertexIDType;
        typedef typename viennagrid::result_of::vertex_handle<ElementType>::type VertexHandleType;

        typedef typename viennagrid::result_of::line_id<ElementType>::type LineIDType;
        typedef typename viennagrid::result_of::line_handle<ElementType>::type LineHandleType;

        typedef typename viennagrid::result_of::const_line_range<ElementType>::type ConstLineOnElementRangeType;
        typedef typename viennagrid::result_of::iterator<ConstLineOnElementRangeType>::type ConstLineOnElementIteratorType;

        std::map<VertexIDType, VertexHandleType> vertex_map;
        std::map<LineIDType, LineHandleType> line_map;


        for (ElementHandleIteratorT eit = begin; eit != end; ++eit)
        {
          ConstLineOnElementRangeType lines_on_element( viennagrid::dereference_handle(input_mesh, *eit) );
          std::vector<LineHandleType> line_handles( lines_on_element.size() );

          unsigned int line_index = 0;
          for (ConstLineOnElementIteratorType lit = lines_on_element.begin(); lit != lines_on_element.end(); ++lit, ++line_index)
          {
            typename std::map<LineIDType, LineHandleType>::iterator it1 = line_map.find( lit->id() );
            if (it1 == line_map.end())
            {
              VertexHandleType vtx_handles[2];
              for (unsigned int vertex_index = 0; vertex_index != 2; ++vertex_index)
              {
                typename std::map<VertexIDType, VertexHandleType>::iterator it2 = vertex_map.find( viennagrid::vertices(*lit)[vertex_index].id() );
                if (it2 == vertex_map.end())
                {
                  vtx_handles[vertex_index] = viennagrid::make_unique_vertex( output_mesh, viennagrid::point( viennagrid::vertices(*lit)[vertex_index] ), tolerance );
                  vertex_map[ viennagrid::vertices(*lit)[vertex_index].id() ] = vtx_handles[vertex_index];
                }
                else
                  vtx_handles[vertex_index] = it2->second;
              }

              line_handles[line_index] = viennagrid::make_line( output_mesh, vtx_handles[0], vtx_handles[1] );
              line_map[lit->id()] = line_handles[line_index];
            }
            else
              line_handles[line_index] = it1->second;
          }

          viennagrid::make_plc( output_mesh, line_handles.begin(), line_handles.end() );
        }

      }
    };
  }




  // doxygen doku in forwards.hpp
  template<typename ElementIteratorT, typename OutputMeshOrSegmentHandleT>
  void copy_elements(ElementIteratorT const & begin, ElementIteratorT const & end,
                     OutputMeshOrSegmentHandleT & output_mesh,
                     typename viennagrid::result_of::coord<OutputMeshOrSegmentHandleT>::type tolerance )
  {
    typedef typename std::iterator_traits<ElementIteratorT>::value_type ElementType;
    typedef typename viennagrid::result_of::element_tag<ElementType>::type ElementTagType;

    detail::copy_elements_impl<ElementTagType>::copy_elements(begin, end, output_mesh, tolerance);
  }

  // doxygen doku in forwards.hpp
  template<typename ElementIteratorT, typename OutputMeshOrSegmentHandleT>
  void copy_elements(ElementIteratorT const & begin, ElementIteratorT const & end,
                     OutputMeshOrSegmentHandleT & output_mesh )
  {
    copy_elements(begin, end, output_mesh, -1.0);
  }


  // doxygen doku in forwards.hpp
  template<typename InputMeshOrSegmentHandleT, typename ElementHandleIteratorT, typename OutputMeshOrSegmentHandleT>
  void copy_elements_by_handle(InputMeshOrSegmentHandleT const & input_mesh,
                            ElementHandleIteratorT const & begin, ElementHandleIteratorT const & end,
                            OutputMeshOrSegmentHandleT & output_mesh,
                            typename viennagrid::result_of::coord<OutputMeshOrSegmentHandleT>::type tolerance )
  {
    typedef typename std::iterator_traits<ElementHandleIteratorT>::value_type ElementHandleType;
    typedef typename viennagrid::detail::result_of::value_type<ElementHandleType>::type ElementType;
    typedef typename viennagrid::result_of::element_tag<ElementType>::type ElementTagType;

    detail::copy_elements_impl<ElementTagType>::copy_elements_by_handle(input_mesh, begin, end, output_mesh, tolerance);
  }

  // doxygen doku in forwards.hpp
  template<typename InputMeshOrSegmentHandleT, typename ElementHandleIteratorT, typename OutputMeshOrSegmentHandleT>
  void copy_elements_by_handle(InputMeshOrSegmentHandleT const & input_mesh,
                            ElementHandleIteratorT const & begin, ElementHandleIteratorT const & end,
                            OutputMeshOrSegmentHandleT & output_mesh )
  {
    copy_elements_by_handle(input_mesh, begin, end, output_mesh, -1.0);
  }

}



#endif
