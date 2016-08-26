#ifndef VIENNAGRID_IO_POLY_READER_HPP
#define VIENNAGRID_IO_POLY_READER_HPP

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
#include "viennagrid/io/helper.hpp"

#include "viennagrid/mesh/mesh.hpp"

/** @file viennagrid/io/tetgen_poly_reader.hpp
    @brief Provides a reader for Tetgen .poly files. See http://wias-berlin.de/software/tetgen/fformats.poly.html
*/



namespace viennagrid
{
  namespace io
  {

    template<typename stream_type>
    bool get_valid_line( stream_type & stream, std::string & line, char comment_line = '#' )
    {
      std::string tmp;

      while (true)
      {
        if (!std::getline(stream, tmp))
          return false;

        std::size_t pos = tmp.find(comment_line);
        if (pos != std::string::npos)
          tmp = tmp.substr(0, pos);

        for (std::size_t i = 0; i != tmp.size(); ++i)
        {
          if ( tmp[i] != ' ' )
          {
            line = tmp.substr(i, std::string::npos);
            return true;
          }
        }
      }
    }

    /** @brief Reader for Tetgen .poly files.
      *
      * See http://wias-berlin.de/software/tetgen/fformats.poly.html for a description of the file format
      */
    struct tetgen_poly_reader
    {
      /** @brief The functor interface triggering the read operation. Segmentations are not supported in this version.
       *
       * @param mesh_obj      The mesh where the file content is written to
       * @param filename      Name of the file
       */
      template <typename MeshT>
      void operator()(MeshT & mesh_obj, std::string const & filename) const
      {
        std::vector< typename viennagrid::result_of::point<MeshT>::type > hole_points;
        std::vector< std::pair<typename viennagrid::result_of::point<MeshT>::type, int> > seed_points;

        (*this)(mesh_obj, filename, hole_points, seed_points);
      }

      /** @brief The functor interface triggering the read operation. Segmentations are not supported in this version.
       *
       * @param mesh_obj      The mesh where the file content is written to
       * @param filename      Name of the file
       * @param hole_points   A container for hole points, output parameter
       */
      template <typename MeshT>
      void operator()(MeshT & mesh_obj, std::string const & filename,
                     std::vector< typename viennagrid::result_of::point<MeshT>::type > & hole_points) const
      {
        std::vector< std::pair<typename viennagrid::result_of::point<MeshT>::type, int> > seed_points;
        (*this)(mesh_obj, filename, hole_points, seed_points);
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
        std::vector< typename viennagrid::result_of::point<MeshT>::type > hole_points;

        (*this)(mesh_obj, filename, hole_points, seed_points);
      }

      /** @brief The functor interface triggering the read operation. Segmentations are not supported in this version.
       *
       * @param mesh_obj      The mesh where the file content is written to
       * @param filename      Name of the file
       * @param hole_points   A container for hole points, output parameter
       * @param seed_points   A container for seed points, output parameter
       */
      template <typename MeshT>
      void operator()(MeshT & mesh_obj, std::string const & filename,
                     std::vector< typename viennagrid::result_of::point<MeshT>::type > & hole_points,
                     std::vector< std::pair<typename viennagrid::result_of::point<MeshT>::type, int> > & seed_points) const
      {
        typedef typename viennagrid::result_of::point<MeshT>::type           PointType;

        static const std::size_t point_dim = viennagrid::result_of::static_size<PointType>::value;

        typedef typename result_of::element<MeshT, vertex_tag>::type         VertexType;
        typedef typename result_of::handle<MeshT, vertex_tag>::type          VertexHandleType;
        typedef typename VertexType::id_type VertexIDType;

        typedef typename result_of::handle<MeshT, line_tag>::type            LineHandleType;

        std::ifstream reader(filename.c_str());

        #if defined VIENNAGRID_DEBUG_STATUS || defined VIENNAGRID_DEBUG_IO
        std::cout << "* poly_reader::operator(): Reading file " << filename << std::endl;
        #endif

        if (!reader)
        {
          throw cannot_open_file_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": Cannot open file!");
        }

        hole_points.clear();
        seed_points.clear();

        std::string tmp;
        std::istringstream current_line;

        long node_num = 0;
        std::size_t dim = 0;
        long attribute_num = 0;
        long boundary_marker_num = 0;


        if (!reader.good())
          throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": File is empty.");

        //
        // Read vertices:
        //
        if (!get_valid_line(reader, tmp))
          throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": EOF encountered when reading information");

        current_line.str(tmp); current_line.clear();
        current_line >> node_num >> dim >> attribute_num >> boundary_marker_num;

        if (node_num < 0)
          throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": POLY file has less than 0 nodes");
        if (dim != point_dim)
          throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": POLY point dimension missmatch");
        if (attribute_num < 0)
          throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": POLY file has less than 0 attributes");
        if ((boundary_marker_num < 0) || (boundary_marker_num > 1))
          throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": POLY file has not 0 or 1 boundary marker");

        #if defined VIENNAGRID_DEBUG_STATUS || defined VIENNAGRID_DEBUG_IO
        std::cout << "* poly_reader::operator(): Reading " << node_num << " vertices... " << std::endl;
        #endif

        for (int i=0; i<node_num; i++)
        {
          if (!get_valid_line(reader, tmp))
              throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": EOF encountered when reading information");

          typename VertexIDType::base_id_type id;

          current_line.str(tmp); current_line.clear();
          current_line >> id;

          PointType p;

          for (std::size_t j=0; j<point_dim; j++)
            current_line >> p[j];

          viennagrid::make_vertex_with_id( mesh_obj, VertexIDType(id), p );
        }

        if (!reader.good())
          throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": EOF encountered when reading number of cells.");


        //
        // Read facets:
        //
        long facet_num = 0;
        if (!get_valid_line(reader, tmp))
          throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": EOF encountered when reading information");


        current_line.str(tmp); current_line.clear();
        current_line >> facet_num >> boundary_marker_num;

        if (facet_num < 0)
          throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": POLY file has less than 0 facets");
        if ((boundary_marker_num < 0) || (boundary_marker_num > 1))
          throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": POLY file has not 0 or 1 boundary marker");

        #if defined VIENNAGRID_DEBUG_STATUS || defined VIENNAGRID_DEBUG_IO
        std::cout << "* netgen_reader::operator(): Reading " << cell_num << " cells... " << std::endl;
        #endif

        for (int i=0; i<facet_num; ++i)
        {
          long polygon_num;
          long hole_num;

          if (!get_valid_line(reader, tmp))
            throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": EOF encountered when reading information");


          current_line.str(tmp); current_line.clear();
          current_line >> polygon_num >> hole_num;

          if (polygon_num < 0)
            throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": POLY facet has less than 0 polygons");
          if (hole_num < 0)
            throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": POLY facet has less than 0 holes");

          std::list<LineHandleType> lines;
          std::list<VertexHandleType> vertices;

          for (int j = 0; j<polygon_num; ++j)
          {
            long vertex_num;

            if (!get_valid_line(reader, tmp))
              throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": EOF encountered when reading information");


            current_line.str(tmp); current_line.clear();
            current_line >> vertex_num;

            if (vertex_num < 0)
              throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": POLY polygon has less than 0 vertices");

            std::vector<VertexHandleType> vertex_handles(static_cast<std::size_t>(vertex_num));

            for (std::size_t k = 0; k<static_cast<std::size_t>(vertex_num); ++k)
            {
              typename VertexIDType::base_id_type id;
              current_line >> id;
              vertex_handles[k] = viennagrid::find( mesh_obj, VertexIDType(id) ).handle();
            }

            if (vertex_num == 1)
            {
              vertices.push_back( vertex_handles.front() );
            }
            else if (vertex_num == 2)
            {
              lines.push_back( viennagrid::make_line(mesh_obj, vertex_handles[0], vertex_handles[1]) );
            }
            else
            {
              typename std::vector<VertexHandleType>::iterator it1 = vertex_handles.begin();
              typename std::vector<VertexHandleType>::iterator it2 = it1; ++it2;
              for (; it2 != vertex_handles.end(); ++it1, ++it2)
                  lines.push_back( viennagrid::make_line(mesh_obj, *it1, *it2) );
              lines.push_back( viennagrid::make_line(mesh_obj, vertex_handles.back(), vertex_handles.front()) );
            }
          }

          std::list<PointType> hole_points_read;

          for (int j = 0; j<hole_num; ++j)
          {
            if (!get_valid_line(reader, tmp))
              throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": EOF encountered when reading information");

            long hole_id;

            current_line.str(tmp); current_line.clear();
            current_line >> hole_id;

            PointType p;

            for (std::size_t k=0; k<point_dim; k++)
              current_line >> p[k];

            hole_points_read.push_back(p);
          }



          viennagrid::make_plc(
              mesh_obj,
              lines.begin(), lines.end(),
              vertices.begin(), vertices.end(),
              hole_points_read.begin(), hole_points_read.end()
          );

        }



        long hole_num;

        if (!get_valid_line(reader, tmp))
        {
          // no holes -> Okay, SUCCESS xD
          return;
        }

        current_line.str(tmp); current_line.clear();
        current_line >> hole_num;

        if (hole_num < 0)
          throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": POLY file has less than 0 holes");

        for (int i=0; i<hole_num; ++i)
        {
          if (!get_valid_line(reader, tmp))
            throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": EOF encountered when reading information");

          long hole_number;
          PointType hole_point;

          current_line.str(tmp); current_line.clear();
          current_line >> hole_number;

          for (std::size_t j=0; j < point_dim; j++)
            current_line >> hole_point[j];

          hole_points.push_back( hole_point );
        }




        long segment_num;

        if (!get_valid_line(reader, tmp))
        {
          // no region -> SUCCESS xD
          return;
        }

        current_line.str(tmp); current_line.clear();
        current_line >> segment_num;

        if (segment_num < 0)
          throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": POLY file has less than 0 segments");

        for (int i=0; i<segment_num; ++i)
        {
          if (!get_valid_line(reader, tmp))
            throw bad_file_format_exception("* ViennaGrid: tetgen_poly_reader::operator(): File " + filename + ": EOF encountered when reading information");

          long segment_number;
          PointType seed_point;
          int segment_id;

          current_line.str(tmp); current_line.clear();
          current_line >> segment_number;

          for (std::size_t j=0; j < point_dim; j++)
            current_line >> seed_point[j];

          current_line >> segment_id;

          seed_points.push_back( std::make_pair(seed_point, segment_id) );
        }
      } //operator()

    }; //class tetgen_poly_reader

  } //namespace io
} //namespace viennagrid

#endif
