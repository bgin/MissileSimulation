#ifndef VIENNAGRID_IO_NEPER_TESS_READER_HPP
#define VIENNAGRID_IO_NEPER_TESS_READER_HPP

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
#include "viennagrid/io/helper.hpp"

/** @file viennagrid/io/neper_tess_reader.hpp
    @brief Provides a reader for Neper .tess files. See http://neper.sourceforge.net/docs/neper.pdf page 49-52
*/



namespace viennagrid
{
  namespace io
  {
    /** @brief Reader for Neper .tess files.
      *
      * See http://neper.sourceforge.net/docs/neper.pdf page 49-52 for a description of the file format
      */
    struct neper_tess_reader
    {
      /** @brief The functor interface triggering the read operation. Segmentations are not supported in this version.
       *
       * @param mesh_obj      The mesh where the file content is written to
       * @param filename      Name of the file
       */
      template <typename MeshT>
      int operator()(MeshT & mesh_obj, std::string const & filename) const
      {
        std::vector< std::pair<typename viennagrid::result_of::point<MeshT>::type, int> > seed_points;

        return (*this)(mesh_obj, filename, seed_points);
      }

      /** @brief The functor interface triggering the read operation. Segmentations are not supported in this version.
       *
       * @param mesh_obj      The mesh where the file content is written to
       * @param filename      Name of the file
       * @param seed_points   A container for seed points, output parameter
       */
      template <typename MeshT>
      void operator()(MeshT & mesh_obj, std::string const & filename,
                     std::vector< std::pair<typename viennagrid::result_of::point<MeshT>::type, int> > & seed_points) const
      {
        typedef typename viennagrid::result_of::point<MeshT>::type           PointType;

        static const int point_dim = viennagrid::result_of::static_size<PointType>::value;

        typedef typename result_of::element<MeshT, vertex_tag>::type         VertexType;
        typedef typename result_of::vertex_handle<MeshT>::type          VertexHandleType;
        typedef typename VertexType::id_type VertexIDType;

        typedef typename result_of::line_handle<MeshT>::type            LineHandleType;

        std::ifstream reader(filename.c_str());

        #if defined VIENNAGRID_DEBUG_STATUS || defined VIENNAGRID_DEBUG_IO
        std::cout << "* poly_reader::operator(): Reading file " << filename << std::endl;
        #endif

        if (!reader)
        {
          throw cannot_open_file_exception("* ViennaGrid: neper_tess_reader::operator(): File " + filename + ": Cannot open file!");
        }

        seed_points.clear();

        std::string tmp;
        std::istringstream current_line;


        if (!reader.good())
          throw bad_file_format_exception("* ViennaGrid: neper_tess_reader::operator(): File " + filename + " is empty.");


        std::map<int, VertexHandleType> vertices;
        std::map< std::pair<int, int>, LineHandleType > lines;

        while (std::getline(reader, tmp))
        {

          if (tmp.find("**vertex") != std::string::npos)
          {
            std::getline(reader, tmp);

            int num_vertices;
            current_line.str(tmp); current_line.clear();
            current_line >> num_vertices;

            for (int i = 0; i < num_vertices; ++i)
            {
              std::getline(reader, tmp);
              int vertex_id;
              current_line.str(tmp); current_line.clear();
              current_line >> vertex_id;

              std::getline(reader, tmp);
              std::getline(reader, tmp);

              PointType p;
              current_line.str(tmp); current_line.clear();
              for (int j = 0; j < std::min(point_dim,3); ++j)
                current_line >> p[j];

              vertices[vertex_id] = viennagrid::make_vertex(mesh_obj, p);
            }
          }



          if (tmp.find("**face") != std::string::npos)
          {
            std::getline(reader, tmp);

            int num_faces;
            current_line.str(tmp); current_line.clear();
            current_line >> num_faces;

            for (int i = 0; i < num_faces; ++i)
            {
              std::getline(reader, tmp);
              std::getline(reader, tmp);
              std::getline(reader, tmp);
              std::getline(reader, tmp);

              int num_vertex_ids;
              std::vector<int> vertex_ids;
              current_line.str(tmp); current_line.clear();
              current_line >> num_vertex_ids;
              vertex_ids.resize(num_vertex_ids);

              for (int j = 0; j < num_vertex_ids; ++j)
                current_line >> vertex_ids[j];

              std::vector<LineHandleType> plc_line_handles;
              for (int j = 1; j < num_vertex_ids; ++j)
              {
                std::pair<int, int> line;
                line.first = std::min( vertex_ids[j-1], vertex_ids[j] );
                line.second = std::max( vertex_ids[j-1], vertex_ids[j] );

                typename std::map< std::pair<int, int>, LineHandleType >::iterator lit = lines.find( line );
                if (lit != lines.end())
                  plc_line_handles.push_back( lit->second );
                else
                {
                  LineHandleType l = viennagrid::make_line( mesh_obj, vertices[line.first], vertices[line.second] );
                  lines[line] = l;
                  plc_line_handles.push_back(l);
                }
              }

              {
                std::pair<int, int> line;
                line.first = std::min( vertex_ids.front(), vertex_ids.back() );
                line.second = std::max( vertex_ids.front(), vertex_ids.back() );

                typename std::map< std::pair<int, int>, LineHandleType >::iterator lit = lines.find( line );
                if (lit != lines.end())
                  plc_line_handles.push_back( lit->second );
                else
                {
                  LineHandleType l = viennagrid::make_line( mesh_obj, vertices[line.first], vertices[line.second] );
                  lines[line] = l;
                  plc_line_handles.push_back(l);
                }
              }



              viennagrid::make_plc( mesh_obj, plc_line_handles.begin(), plc_line_handles.end() );

              std::getline(reader, tmp);
              std::getline(reader, tmp);
              std::getline(reader, tmp);
            }
          }



          if (tmp.find("**polyhedron") != std::string::npos)
          {
            std::getline(reader, tmp);

            int num_polyhedrons;
            current_line.str(tmp); current_line.clear();
            current_line >> num_polyhedrons;

            for (int i = 0; i < num_polyhedrons; ++i)
            {
              std::getline(reader, tmp);
              int polyherdon_id;
              current_line.str(tmp); current_line.clear();
              current_line >> polyherdon_id;

              PointType p;
              for (int j = 0; j < std::min(point_dim,3); ++j)
                current_line >> p[j];

              seed_points.push_back( std::make_pair(p, polyherdon_id) );
              std::getline(reader, tmp);
              std::getline(reader, tmp);
            }
          }

        }
      } //operator()

    }; //class tetgen_poly_reader

  } //namespace io
} //namespace viennagrid

#endif
