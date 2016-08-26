#ifndef VIENNAGRID_IO_NETGEN_READER_HPP
#define VIENNAGRID_IO_NETGEN_READER_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */


#include <fstream>
#include <iostream>
#include <assert.h>
#include "viennagrid/forwards.hpp"

#include "viennagrid/mesh/mesh.hpp"
#include "viennagrid/mesh/segmentation.hpp"
#include "viennagrid/mesh/element_creation.hpp"

#include "viennagrid/io/helper.hpp"

/** @file viennagrid/io/netgen_reader.hpp
    @brief Provides a reader for Netgen files
*/

namespace viennagrid
{
  namespace io
  {

    /** @brief Reader for Netgen files obtained from the 'Export mesh...' menu item. Tested with Netgen version 4.9.12. */
    struct netgen_reader
    {
      /** @brief The functor interface triggering the read operation.
       *
       * @param mesh_obj      The mesh where the file content is written to
       * @param segmentation  The segmentation where the file content is written to
       * @param filename      Name of the file
       */
      template <typename MeshType, typename SegmentationType>
      void operator()(MeshType & mesh_obj, SegmentationType & segmentation, std::string const & filename) const
      {
        typedef typename viennagrid::result_of::point<MeshType>::type    PointType;

        const int point_dim = viennagrid::result_of::static_size<PointType>::value;

        typedef typename result_of::cell_tag<MeshType>::type CellTag;
        typedef typename result_of::element<MeshType, CellTag>::type CellType;

        typedef typename result_of::element<MeshType, vertex_tag>::type                           VertexType;
        typedef typename result_of::handle<MeshType, vertex_tag>::type                           VertexHandleType;

        std::ifstream reader(filename.c_str());

        #if defined VIENNAGRID_DEBUG_STATUS || defined VIENNAGRID_DEBUG_IO
        std::cout << "* netgen_reader::operator(): Reading file " << filename << std::endl;
        #endif

        if (!reader)
        {
          throw cannot_open_file_exception("* ViennaGrid: netgen_reader::operator(): File " + filename + ": Cannot open file!");
        }

        long node_num = 0;
        long cell_num = 0;

        if (!reader.good())
          throw bad_file_format_exception("* ViennaGrid: netgen_reader::operator(): File " + filename + " is empty.");

        //
        // Read vertices:
        //
        reader >> node_num;
        assert(node_num > 0);

        #if defined VIENNAGRID_DEBUG_STATUS || defined VIENNAGRID_DEBUG_IO
        std::cout << "* netgen_reader::operator(): Reading " << node_num << " vertices... " << std::endl;
        #endif



        for (int i=0; i<node_num; i++)
        {
          if (!reader.good())
            throw bad_file_format_exception("* ViennaGrid: netgen_reader::operator(): File " + filename + ": EOF encountered while reading vertices.");

          PointType p;

          for (std::size_t j=0; j<static_cast<std::size_t>(point_dim); j++)
            reader >> p[j];

          viennagrid::make_vertex_with_id( mesh_obj, typename VertexType::id_type(i), p );
        }

        if (!reader.good())
          throw bad_file_format_exception("* ViennaGrid: netgen_reader::operator(): File " + filename + ": EOF encountered when reading number of cells.");


        //
        // Read cells:
        //
        reader >> cell_num;

        #if defined VIENNAGRID_DEBUG_STATUS || defined VIENNAGRID_DEBUG_IO
        std::cout << "* netgen_reader::operator(): Reading " << cell_num << " cells... " << std::endl;
        #endif

        for (int i=0; i<cell_num; ++i)
        {
          std::size_t vertex_num;
          viennagrid::static_array<VertexHandleType, boundary_elements<CellTag, vertex_tag>::num> cell_vertex_handles;

          if (!reader.good())
            throw bad_file_format_exception("* ViennaGrid: netgen_reader::operator(): File " + filename + ": EOF encountered while reading cells (segment index expected).");

          int segment_index;
          reader >> segment_index;

          for (std::size_t j=0; j<static_cast<std::size_t>(boundary_elements<CellTag, vertex_tag>::num); ++j)
          {
            if (!reader.good())
              throw bad_file_format_exception("* ViennaGrid: netgen_reader::operator(): File " + filename + ": EOF encountered while reading cells (cell ID expected).");

            reader >> vertex_num;
            cell_vertex_handles[j] = viennagrid::vertices(mesh_obj).handle_at(vertex_num-1);
          }

          viennagrid::make_element_with_id<CellType>(segmentation[segment_index], cell_vertex_handles.begin(), cell_vertex_handles.end(), typename CellType::id_type(i));
        }
      } //operator()


      /** @brief The functor interface triggering the read operation.
       *
       * @param mesh_obj      The mesh where the file content is written to
       * @param filename      Name of the file
       */
      template <typename MeshType>
      void operator()(MeshType & mesh_obj, std::string const & filename)
      {
        typedef typename viennagrid::result_of::segmentation<MeshType>::type SegmentationType;
        SegmentationType tmp(mesh_obj);
        (*this)(mesh_obj, tmp, filename);
      }

    }; //class netgen_reader

  } //namespace io
} //namespace viennagrid

#endif
