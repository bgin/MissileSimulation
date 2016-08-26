#ifndef VIENNAGRID_IO_VTK_READER_HPP
#define VIENNAGRID_IO_VTK_READER_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */


/** @file viennagrid/io/vtk_reader.hpp
 *  @brief    This is a simple vtk-reader implementation. Refer to the vtk-standard (cf. http://www.vtk.org/pdf/file-formats.pdf) and make sure the same order of XML tags is preserved.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>

#include "viennagrid/forwards.hpp"
#include "viennagrid/point.hpp"
#include "viennagrid/io/vtk_common.hpp"
#include "viennagrid/io/helper.hpp"
#include "viennagrid/io/xml_tag.hpp"
#include "viennagrid/mesh/element_creation.hpp"

namespace viennagrid
{
  namespace io
  {

    /** @brief A VTK reader class that allows to read meshes from XML-based VTK files as defined in http://www.vtk.org/pdf/file-formats.pdf
     *
     * @tparam MeshType         The type of the mesh to be read. Must not be a segment type!
     * @tparam SegmentationType   The type of the segmentation to be read, default is the default segmentation of MeshType
     */
    template <typename MeshType, typename SegmentationType = typename viennagrid::result_of::segmentation<MeshType>::type >
    class vtk_reader
    {
    protected:

      typedef MeshType mesh_type;
      typedef SegmentationType segmentation_type;

      typedef typename SegmentationType::segment_handle_type SegmentHandleType;
      typedef typename SegmentationType::segment_id_type segment_id_type;


      typedef typename viennagrid::result_of::point<MeshType>::type PointType;
      typedef typename viennagrid::result_of::coord<PointType>::type CoordType;
      static const int geometric_dim = viennagrid::result_of::static_size<PointType>::value;

      typedef typename viennagrid::result_of::cell_tag<MeshType>::type CellTag;


      typedef typename result_of::vertex<MeshType>::type                          VertexType;
      typedef typename result_of::vertex_handle<MeshType>::type                           VertexHandleType;
      typedef typename result_of::vertex_id<MeshType>::type                           VertexIDType;
      typedef typename result_of::element<MeshType, CellTag>::type     CellType;
      typedef typename result_of::handle<MeshType, CellTag>::type     CellHandleType;

      typedef typename viennagrid::result_of::vertex_range<MeshType>::type   VertexRange;
      typedef typename viennagrid::result_of::iterator<VertexRange>::type                             VertexIterator;

      typedef typename viennagrid::result_of::line_range<MeshType>::type     EdgeRange;
      typedef typename viennagrid::result_of::iterator<EdgeRange>::type                               EdgeIterator;

      typedef typename viennagrid::result_of::facet_range<MeshType>::type   FacetRange;
      typedef typename viennagrid::result_of::iterator<FacetRange>::type                                   FacetIterator;

      typedef typename viennagrid::result_of::cell_range<MeshType>::type     CellRange;
      typedef typename viennagrid::result_of::iterator<CellRange>::type                  CellIterator;


      typedef std::vector<double> vector_data_type;

      typedef std::map< std::string, base_dynamic_field<double, VertexType> * >             VertexScalarOutputFieldContainer;
      typedef std::map< std::string, base_dynamic_field<vector_data_type, VertexType> * >   VertexVectorOutputFieldContainer;

      typedef std::map< std::string, base_dynamic_field<double, CellType> * >               CellScalarOutputFieldContainer;
      typedef std::map< std::string, base_dynamic_field<vector_data_type, CellType> * >     CellVectorOutputFieldContainer;





      std::ifstream                                        reader;
      std::map<PointType, std::size_t, point_less>         global_points;
      std::map<std::size_t, PointType>                     global_points_2;
      std::map<int, std::deque<std::size_t> >              local_to_global_map;
      std::map<int, std::deque<std::size_t> >              local_cell_vertices;
      std::map<int, std::deque<std::size_t> >              local_cell_offsets;
      std::map<int, std::size_t>                           local_cell_num;
      std::map<int, std::deque<CellHandleType> >           local_cell_handle;

      typedef viennagrid::element_key<CellType> CellElementKeyType;
      std::map<CellElementKeyType, CellHandleType>         global_cells;

      //data containers:
      std::map<int, std::deque<std::pair<std::string, std::deque<double> > > >  local_scalar_vertex_data;
      std::map<int, std::deque<std::pair<std::string, std::deque<double> > > >  local_vector_vertex_data;
      std::map<int, std::deque<std::pair<std::string, std::deque<double> > > >  local_scalar_cell_data;
      std::map<int, std::deque<std::pair<std::string, std::deque<double> > > >  local_vector_cell_data;


      template<typename map_type>
      void clear_map( map_type & map )
      {
        for (typename map_type::iterator it = map.begin(); it != map.end(); ++it)
          delete it->second;

        map.clear();
      }

      void post_clear()
      {
        clear_map(registered_vertex_scalar_data);
        clear_map(registered_vertex_vector_data);

        clear_map(registered_cell_scalar_data);
        clear_map(registered_cell_vector_data);


        for (typename std::map< segment_id_type, VertexScalarOutputFieldContainer>::iterator it = registered_segment_vertex_scalar_data.begin(); it != registered_segment_vertex_scalar_data.end(); ++it)
          clear_map(it->second);

        for (typename std::map< segment_id_type, VertexVectorOutputFieldContainer>::iterator it = registered_segment_vertex_vector_data.begin(); it != registered_segment_vertex_vector_data.end(); ++it)
          clear_map(it->second);


        for (typename std::map< segment_id_type, CellScalarOutputFieldContainer>::iterator it = registered_segment_cell_scalar_data.begin(); it != registered_segment_cell_scalar_data.end(); ++it)
          clear_map(it->second);

        for (typename std::map< segment_id_type, CellVectorOutputFieldContainer>::iterator it = registered_segment_cell_vector_data.begin(); it != registered_segment_cell_vector_data.end(); ++it)
          clear_map(it->second);


        registered_segment_vertex_scalar_data.clear();
        registered_segment_vertex_vector_data.clear();

        registered_segment_cell_scalar_data.clear();
        registered_segment_cell_vector_data.clear();
      }


      void pre_clear()
      {
        vertex_data_scalar_read.clear();
        vertex_data_vector_read.clear();

        cell_data_scalar_read.clear();
        cell_data_vector_read.clear();

        vertex_scalar_data.clear();
        vertex_vector_data.clear();

        cell_scalar_data.clear();
        cell_vector_data.clear();

        global_points.clear();
        global_points_2.clear();
        local_to_global_map.clear();
        local_cell_vertices.clear();
        local_cell_offsets.clear();
        local_cell_num.clear();
        local_cell_handle.clear();

        global_cells.clear();

        local_scalar_vertex_data.clear();
        local_vector_vertex_data.clear();
        local_scalar_cell_data.clear();
        local_vector_cell_data.clear();
      }





      /** @brief Opens a file */
      void openFile(std::string const & filename)
      {
        reader.open(filename.c_str());
        if(!reader)
        {
          throw cannot_open_file_exception("* ViennaGrid: vtk_reader::openFile(): File " + filename + ": Cannot open file!");
        }
      }

      /** @brief Closes a file */
      void closeFile()
      {
        reader.close();
      }

     /** @brief compares the lower-case representation of two strings */
      bool lowercase_compare(std::string const & s1, std::string const & s2)
      {
        std::string s1_lower = s1;
        std::transform(s1.begin(), s1.end(), s1_lower.begin(), char_to_lower<>());

        std::string s2_lower = s2;
        std::transform(s2.begin(), s2.end(), s2_lower.begin(), char_to_lower<>());

        return s1_lower == s2_lower;
      }

      /** @brief Make sure that the next token is given by 'expectedToken'. Throws a bad_file_format_exception if this is not the case */
      void checkNextToken(std::string const & expectedToken)
      {
        std::string token;
        reader >> token;

        if ( !lowercase_compare(token, expectedToken) )
        {
          std::cerr << "* vtk_reader::operator(): Expected \"" << expectedToken << "\", but got \"" << token << "\"" << std::endl;
          std::stringstream ss;
          ss << "* ViennaGrid: vtk_reader::operator(): Expected \"" << expectedToken << "\", but got \"" << token << "\"";
          throw bad_file_format_exception(ss.str());
        }
      }

      /** @brief Reads the coordinates of the points/vertices in the mesh */
      void readNodeCoordinates(std::size_t nodeNum, std::size_t numberOfComponents, segment_id_type seg_id)
      {
        double nodeCoord;
        local_to_global_map[seg_id].resize(nodeNum);

        for(std::size_t i = 0; i < nodeNum; i++)
        {
          PointType p;

          for(std::size_t j = 0; j < numberOfComponents; j++)
          {
            reader >> nodeCoord;
            if (j < static_cast<std::size_t>(geometric_dim))
              p[j] = nodeCoord;
          }

          //add point to global list if not already there
          if (global_points.find(p) == global_points.end())
          {
            std::size_t new_global_id = global_points.size();
            global_points.insert( std::make_pair(p, new_global_id) );
            global_points_2.insert( std::make_pair(new_global_id, p) );
            local_to_global_map[seg_id][i] = new_global_id;
          }
          else
          {
            local_to_global_map[seg_id][i] = global_points[p];
          }
        }
      }

      /** @brief Reads the vertex indices of the cells inside the mesh */
      void readCellIndices(segment_id_type seg_id)
      {
        std::size_t cellNode = 0;
        std::string token;
        reader >> token;

        while (token != "</DataArray>")
        {
          assert( strChecker::myIsNumber(token) && "Cell vertex index is not a number!" );

          cellNode = static_cast<std::size_t>(atoi(token.c_str()));
          local_cell_vertices[seg_id].push_back(cellNode);

          reader >> token;
        }
      }

      /** @brief Read the cell offsets for the vertex indices */
      void readOffsets(segment_id_type seg_id)
      {
          //****************************************************************************
          // read in the offsets: describe the affiliation of the nodes to the cells
          // (see: http://www.vtk.org/pdf/file-formats.pdf , page 9)
          //****************************************************************************

          std::string token;
          std::size_t offset = 0;
          reader >> token;

          while(token != "</DataArray>")
          {
            assert( strChecker::myIsNumber(token) && "Cell offset is not a number!" );

            offset = static_cast<std::size_t>(atoi(token.c_str()));
            local_cell_offsets[seg_id].push_back(offset);

            //std::cout << "Vertex#: " << offset << std::endl;
            reader >> token;
          }
      }

      /** @brief Read the types of each cell. */
      void readTypes()
      {
          //****************************************************************************
          // read in the offsets: describe the affiliation of the nodes to the cells
          // (see: http://www.vtk.org/pdf/file-formats.pdf , page 9)
          //****************************************************************************

          std::string token;
#ifndef NDEBUG
          long type = 0;
#endif
          reader >> token;

          while(token != "</DataArray>")
          {
            assert( strChecker::myIsNumber(token) && "Cell type is not a number!" );
#ifndef NDEBUG
            type = atoi(token.c_str());
            assert(type == detail::ELEMENT_TAG_TO_VTK_TYPE<CellTag>::value && "Error in VTK reader: Type mismatch!");
#endif
            //std::cout << "Vertex#: " << offset << std::endl;
            reader >> token;
          }
      }

      /** @brief Read data and push it to a container. Helper function. */
      void readData(std::deque<double> & container)
      {
        std::string token;
        reader >> token;

        while (string_to_lower(token) != "</dataarray>")
        {
          container.push_back( atof(token.c_str()) );
          reader >> token;
        }
      }

      /** @brief Read point or cell data and fill the respective data containers */
      template <typename ContainerType, typename NameContainerType>
      void readPointCellData(segment_id_type seg_id,
                             ContainerType & scalar_data,
                             ContainerType & vector_data,
                             NameContainerType & data_names_scalar,
                             NameContainerType & data_names_vector)
      {
        std::string name;
        std::size_t components = 1;

        xml_tag<> tag;

        tag.parse(reader);

        while (tag.name() == "dataarray")
        {
          tag.check_attribute("name", "");
          name = tag.get_value("name");

          if (tag.has_attribute("numberofcomponents"))
            components = static_cast<std::size_t>(atoi(tag.get_value("numberofcomponents").c_str()));

          //now read data:
          if (components == 1)
          {
            data_names_scalar.push_back(std::make_pair(seg_id, name));
            scalar_data[seg_id].push_back( std::make_pair(name, std::deque<double>()) );
            readData(scalar_data[seg_id].back().second);
          }
          else if (components == 3)
          {
            data_names_vector.push_back(std::make_pair(seg_id, name));
            vector_data[seg_id].push_back( std::make_pair(name, std::deque<double>()) );
            readData(vector_data[seg_id].back().second);
          }
          else
            throw bad_file_format_exception("* ViennaGrid: vtk_reader::readPointCellData(): Number of components for data invalid!");

          tag.parse(reader);
        }


        if (tag.name() != "/pointdata" && tag.name() != "/celldata")
            throw bad_file_format_exception("* ViennaGrid: vtk_reader::readPointCellData(): XML Parse error: Expected </PointData> or </CellData>!");

      }

      /////////////////////////// Routines for pushing everything to mesh ///////////////

      /** @brief Pushes the vertices read to the mesh */
      void setupVertices(MeshType & mesh_obj)
      {
        for (std::size_t i=0; i<global_points_2.size(); ++i)
          viennagrid::make_vertex_with_id( mesh_obj, typename VertexType::id_type(typename VertexType::id_type::base_id_type(i)), global_points_2[i] );
      }

      /** @brief Pushes the cells read to the mesh. Preserves segment information. */
      void setupCells(MeshType & mesh_obj, SegmentationType & segmentation, segment_id_type seg_id)
      {
        //***************************************************
        // building up the cells in ViennaGrid
        // -------------------------------------------------
        // "cells"   ... contain the indices of the nodes
        // "offsets" ... contain the information about
        //               the affiliation of the nodes
        //               to the cells
        //***************************************************
        //CellType cell;
        std::size_t numVertices = 0;
        std::size_t offsetIdx = 0;

        std::deque<std::size_t> const & offsets = local_cell_offsets[seg_id];

        for (std::size_t i = 0; i < local_cell_num[seg_id]; i++)
        {
          //*************************************************
          // choose the offset index for the i-th cell
          // in the "cells"-vector and calculate the
          // number of vertices belonging to the i-th cell
          //*************************************************
          if(i == 0)
          {
            offsetIdx = 0;
            numVertices = offsets[i];
          }
          else
          {
            offsetIdx = offsets[i-1];
            numVertices = offsets[i]-offsets[i-1];
          }


          //****************************************************
          // read out the node indices form the "cells"-vector
          // and add the cells to the "vertices"-array
          //****************************************************

          viennagrid::static_array<VertexHandleType, boundary_elements<CellTag, vertex_tag>::num> cell_vertex_handles;
          std::vector<VertexIDType> cell_vertex_ids(numVertices);

          detail::vtk_to_viennagrid_orientations<CellTag> reorderer;
          for (std::size_t j = 0; j < numVertices; j++)
          {
            std::size_t reordered_j = reorderer(j);
            std::size_t local_index = local_cell_vertices[seg_id][reordered_j + offsetIdx];
            std::size_t global_vertex_index = local_to_global_map[seg_id][local_index];

            cell_vertex_handles[j] = viennagrid::elements<viennagrid::vertex_tag>(mesh_obj).handle_at(global_vertex_index);
            viennagrid::add( segmentation[seg_id], viennagrid::dereference_handle(segmentation, cell_vertex_handles[j]) );

            cell_vertex_ids[j] = viennagrid::dereference_handle(mesh_obj, cell_vertex_handles[j]).id();
          }


          CellElementKeyType cell_key(cell_vertex_ids);
          typename std::map<CellElementKeyType, CellHandleType>::iterator chit = global_cells.find( cell_key );
          if (chit != global_cells.end())
          {
            local_cell_handle[seg_id].push_back( chit->second );
            viennagrid::add( segmentation[seg_id], viennagrid::dereference_handle(mesh_obj, chit->second) );
          }
          else
          {
            CellHandleType cell_handle = viennagrid::make_element<CellType>(segmentation[seg_id], cell_vertex_handles.begin(), cell_vertex_handles.end());
            global_cells[cell_key] = cell_handle;

            local_cell_handle[seg_id].push_back(cell_handle);
          }
        }
      }

      /** @brief Writes data for vertices to the ViennaGrid mesh using ViennaData */
      template <typename ContainerType>
      void setupDataVertex(MeshType & mesh_obj, SegmentHandleType &
#ifndef NDEBUG
        segment
#endif
        , segment_id_type seg_id, ContainerType const & container, std::size_t num_components)
      {
        std::string const & name = container.first;

        if (num_components == 1)
        {
          VertexScalarOutputFieldContainer & current_registered_segment_vertex_scalar_data = registered_segment_vertex_scalar_data[seg_id];
          if (registered_vertex_scalar_data.find(name) != registered_vertex_scalar_data.end())
          {
            for (std::size_t i=0; i<container.second.size(); ++i)
            {
              std::size_t global_vertex_id = local_to_global_map[seg_id][i];
              VertexType const & vertex = viennagrid::elements<viennagrid::vertex_tag>(mesh_obj)[global_vertex_id];

              (*registered_vertex_scalar_data[name])(vertex) = (container.second)[i];
            }
          }
          else if (current_registered_segment_vertex_scalar_data.find(name) != current_registered_segment_vertex_scalar_data.end())
          {
            for (std::size_t i=0; i<container.second.size(); ++i)
            {
              std::size_t global_vertex_id = local_to_global_map[seg_id][i];
              VertexType const & vertex = viennagrid::elements<viennagrid::vertex_tag>(mesh_obj)[global_vertex_id];

              (*current_registered_segment_vertex_scalar_data[name])(vertex) = (container.second)[i];
            }
          }
          else
          {
            #if defined VIENNAGRID_DEBUG_ALL || defined VIENNAGRID_DEBUG_IO
            std::cout << "* vtk_reader::operator(): Reading scalar quantity "
                      << container.first << " to vertices." << std::endl;
            #endif
            for (std::size_t i=0; i<container.second.size(); ++i)
            {
              std::size_t global_vertex_id = local_to_global_map[seg_id][i];
              VertexType const & vertex = viennagrid::elements<viennagrid::vertex_tag>(mesh_obj)[global_vertex_id];

              if ( static_cast<typename VertexType::id_type::base_id_type>(vertex_scalar_data[container.first][seg_id].size()) <= vertex.id().get())
                vertex_scalar_data[container.first][seg_id].resize(static_cast<std::size_t>(vertex.id().get()+1));
              vertex_scalar_data[container.first][seg_id][static_cast<std::size_t>(vertex.id().get())] = (container.second)[i];
            }
          }
        }
        else
        {
          VertexVectorOutputFieldContainer & current_registered_segment_vertex_vector_data = registered_segment_vertex_vector_data[seg_id];
          if (registered_vertex_vector_data.find(name) != registered_vertex_vector_data.end())
          {
            for (std::size_t i=0; i<container.second.size()/3; ++i)
            {
              std::size_t global_vertex_id = local_to_global_map[seg_id][i];
              VertexType const & vertex = viennagrid::elements<viennagrid::vertex_tag>(mesh_obj)[global_vertex_id];

              (*registered_vertex_vector_data[name])(vertex).resize(3);
              (*registered_vertex_vector_data[name])(vertex)[0] = (container.second)[3*i+0];
              (*registered_vertex_vector_data[name])(vertex)[1] = (container.second)[3*i+1];
              (*registered_vertex_vector_data[name])(vertex)[2] = (container.second)[3*i+2];
            }
          }
          else if (current_registered_segment_vertex_vector_data.find(name) != current_registered_segment_vertex_vector_data.end())
          {
            for (std::size_t i=0; i<container.second.size(); ++i)
            {
              std::size_t global_vertex_id = local_to_global_map[seg_id][i];
              VertexType const & vertex = viennagrid::elements<viennagrid::vertex_tag>(mesh_obj)[global_vertex_id];

              (*current_registered_segment_vertex_vector_data[name])(vertex).resize(3);
              (*current_registered_segment_vertex_vector_data[name])(vertex)[0] = (container.second)[3*i+0];
              (*current_registered_segment_vertex_vector_data[name])(vertex)[1] = (container.second)[3*i+1];
              (*current_registered_segment_vertex_vector_data[name])(vertex)[2] = (container.second)[3*i+2];
            }
          }
          else
          {
            #if defined VIENNAGRID_DEBUG_ALL || defined VIENNAGRID_DEBUG_IO
            std::cout << "* vtk_reader::operator(): Reading vector quantity "
                      << container.first << " to vertices." << std::endl;
            #endif
            assert( 3 * viennagrid::elements<viennagrid::vertex_tag>(segment).size() == container.second.size());
            for (std::size_t i=0; i<container.second.size() / 3; ++i)
            {
              std::size_t global_vertex_id = local_to_global_map[seg_id][i];
              VertexType const & vertex = viennagrid::elements<viennagrid::vertex_tag>(mesh_obj)[global_vertex_id];

              if ( static_cast<typename VertexType::id_type::base_id_type>(vertex_vector_data[container.first][seg_id].size()) <= vertex.id().get())
                vertex_vector_data[container.first][seg_id].resize(static_cast<std::size_t>(vertex.id().get()+1));
              vertex_vector_data[container.first][seg_id][static_cast<std::size_t>(vertex.id().get())].resize(3);
              vertex_vector_data[container.first][seg_id][static_cast<std::size_t>(vertex.id().get())][0] = (container.second)[3*i+0];
              vertex_vector_data[container.first][seg_id][static_cast<std::size_t>(vertex.id().get())][1] = (container.second)[3*i+1];
              vertex_vector_data[container.first][seg_id][static_cast<std::size_t>(vertex.id().get())][2] = (container.second)[3*i+2];
            }
          }
        }
      }

      /** @brief Writes data for cells to the ViennaGrid mesh using ViennaData */
      template <typename ContainerType>
      void setupDataCell(MeshType &, SegmentHandleType & segment, segment_id_type seg_id, ContainerType const & container, std::size_t num_components)
      {
        std::string const & name = container.first;

        if (num_components == 1)
        {
          CellScalarOutputFieldContainer & current_registered_segment_cell_scalar_data = registered_segment_cell_scalar_data[seg_id];
          if (registered_cell_scalar_data.find(name) != registered_cell_scalar_data.end())
          {
            for (std::size_t i=0; i<container.second.size(); ++i)
            {
              CellType const & cell = viennagrid::dereference_handle( segment, local_cell_handle[seg_id][i] );

              (*registered_cell_scalar_data[name])(cell) = (container.second)[i];
            }
          }
          else if (current_registered_segment_cell_scalar_data.find(name) != current_registered_segment_cell_scalar_data.end())
          {
            for (std::size_t i=0; i<container.second.size(); ++i)
            {
              CellType const & cell = viennagrid::dereference_handle( segment, local_cell_handle[seg_id][i] );

              (*current_registered_segment_cell_scalar_data[name])(cell) = (container.second)[i];
            }
          }
          else
          {
            #if defined VIENNAGRID_DEBUG_ALL || defined VIENNAGRID_DEBUG_IO
            std::cout << "* vtk_reader::operator(): Reading scalar quantity "
                      << container.first << " to vertices." << std::endl;
            #endif
            for (std::size_t i=0; i<container.second.size(); ++i)
            {
              CellType const & cell = viennagrid::dereference_handle( segment, local_cell_handle[seg_id][i] );

              if ( static_cast<typename CellType::id_type::base_id_type>(cell_scalar_data[container.first][seg_id].size()) <= cell.id().get())
                cell_scalar_data[container.first][seg_id].resize(static_cast<std::size_t>(cell.id().get()+1));
              cell_scalar_data[container.first][seg_id][static_cast<std::size_t>(cell.id().get())] = (container.second)[i];
            }
          }
        }
        else
        {
          CellVectorOutputFieldContainer & current_registered_segment_cell_vector_data = registered_segment_cell_vector_data[seg_id];
          if (registered_cell_vector_data.find(name) != registered_cell_vector_data.end())
          {
            for (std::size_t i=0; i<container.second.size()/3; ++i)
            {
              CellType const & cell = viennagrid::dereference_handle( segment, local_cell_handle[seg_id][i] );

              (*registered_cell_vector_data[name])(cell).resize(3);
              (*registered_cell_vector_data[name])(cell)[0] = (container.second)[3*i+0];
              (*registered_cell_vector_data[name])(cell)[1] = (container.second)[3*i+1];
              (*registered_cell_vector_data[name])(cell)[2] = (container.second)[3*i+2];
            }
          }
          else if (current_registered_segment_cell_vector_data.find(name) != current_registered_segment_cell_vector_data.end())
          {
            for (std::size_t i=0; i<container.second.size(); ++i)
            {
              CellType const & cell = viennagrid::dereference_handle( segment, local_cell_handle[seg_id][i] );

              (*current_registered_segment_cell_vector_data[name])(cell).resize(3);
              (*current_registered_segment_cell_vector_data[name])(cell)[0] = (container.second)[3*i+0];
              (*current_registered_segment_cell_vector_data[name])(cell)[1] = (container.second)[3*i+1];
              (*current_registered_segment_cell_vector_data[name])(cell)[2] = (container.second)[3*i+2];
            }
          }
          else
          {
            #if defined VIENNAGRID_DEBUG_ALL || defined VIENNAGRID_DEBUG_IO
            std::cout << "* vtk_reader::operator(): Reading vector quantity "
                      << container.first << " to vertices." << std::endl;
            #endif
            assert( 3 * viennagrid::elements<CellTag>(segment).size() == container.second.size());
            for (std::size_t i=0; i<container.second.size() / 3; ++i)
            {
              CellType const & cell = viennagrid::dereference_handle( segment, local_cell_handle[seg_id][i] );

              if ( static_cast<typename CellType::id_type::base_id_type>(cell_vector_data[container.first][seg_id].size()) <= cell.id().get())
                cell_vector_data[container.first][seg_id].resize(static_cast<std::size_t>(cell.id().get()+1));
              cell_vector_data[container.first][seg_id][static_cast<std::size_t>(cell.id().get())].resize(3);
              cell_vector_data[container.first][seg_id][static_cast<std::size_t>(cell.id().get())][0] = (container.second)[3*i+0];
              cell_vector_data[container.first][seg_id][static_cast<std::size_t>(cell.id().get())][1] = (container.second)[3*i+1];
              cell_vector_data[container.first][seg_id][static_cast<std::size_t>(cell.id().get())][2] = (container.second)[3*i+2];
            }
          }
        }
      }

      /** @brief Writes all data read from files to the mesh */
      void setupData(MeshType & mesh_obj, SegmentationType & segmentation, segment_id_type seg_id)
      {
        for (size_t i=0; i<local_scalar_vertex_data[seg_id].size(); ++i)
        {
          setupDataVertex(mesh_obj, segmentation[seg_id], seg_id, local_scalar_vertex_data[seg_id][i], 1);
        }

        for (size_t i=0; i<local_vector_vertex_data[seg_id].size(); ++i)
        {
          setupDataVertex(mesh_obj, segmentation[seg_id], seg_id, local_vector_vertex_data[seg_id][i], 3);
        }


        for (size_t i=0; i<local_scalar_cell_data[seg_id].size(); ++i)
        {
          setupDataCell(mesh_obj, segmentation[seg_id], seg_id, local_scalar_cell_data[seg_id][i], 1);
        }

        for (size_t i=0; i<local_vector_cell_data[seg_id].size(); ++i)
        {
          setupDataCell(mesh_obj, segmentation[seg_id], seg_id, local_vector_cell_data[seg_id][i], 3);
        }

      }

      /** @brief Parses a .vtu file referring to a segment of the mesh */
      void parse_vtu_segment(std::string filename, segment_id_type seg_id)
      {

        try
        {
          openFile(filename);

          std::size_t nodeNum = 0;
          std::size_t numberOfComponents = 0;

          xml_tag<> tag;

          tag.parse(reader);
          if (tag.name() != "?xml" && tag.name() != "?xml?")
            throw bad_file_format_exception("* ViennaGrid: vtk_reader::parse_vtu_segment(): Parse error: No opening ?xml tag!");

          tag.parse_and_check_name(reader, "vtkfile", filename);
          tag.parse_and_check_name(reader, "unstructuredgrid", filename);

          tag.parse_and_check_name(reader, "piece", filename);

          tag.check_attribute("numberofpoints", filename);

          nodeNum = static_cast<std::size_t>(atoi(tag.get_value("numberofpoints").c_str()));
          #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "#Nodes: " << nodeNum << std::endl;
          #endif

          tag.check_attribute("numberofcells", filename);

          local_cell_num[seg_id] = static_cast<std::size_t>(atoi(tag.get_value("numberofcells").c_str()));
          #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "#Cells: " << local_cell_num[seg_id] << std::endl;
          #endif

          tag.parse_and_check_name(reader, "points", filename);

          tag.parse_and_check_name(reader, "dataarray", filename);
          tag.check_attribute("numberofcomponents", filename);

          numberOfComponents = static_cast<std::size_t>(atoi(tag.get_value("numberofcomponents").c_str()));
          readNodeCoordinates(nodeNum, numberOfComponents, seg_id);

          tag.parse_and_check_name(reader, "/dataarray", filename);
          tag.parse_and_check_name(reader, "/points", filename);

          tag.parse(reader);
          if (tag.name() == "pointdata")
          {
             readPointCellData(seg_id, local_scalar_vertex_data, local_vector_vertex_data,
                                      vertex_data_scalar_read, vertex_data_vector_read);
            tag.parse(reader);
          }

          if (tag.name() != "cells")
            throw bad_file_format_exception("* ViennaGrid: vtk_reader::parse_vtu_segment(): Parse error: Expected Cells tag!");

          for (std::size_t i=0; i<3; ++i)
          {
            tag.parse_and_check_name(reader, "dataarray", filename);
            tag.check_attribute("name", filename);

            if (tag.get_value("name") == "connectivity")
              readCellIndices(seg_id);
            else if (tag.get_value("name") == "offsets")
              readOffsets(seg_id);
            else if (tag.get_value("name") == "types")
              readTypes();
            else
              throw bad_file_format_exception("* ViennaGrid: vtk_reader::parse_vtu_segment(): Parse error: <DataArray> is not named 'connectivity', 'offsets' or 'types'!");
          }

          tag.parse_and_check_name(reader, "/cells", filename);

          tag.parse(reader);
          if (tag.name() == "celldata")
          {
            readPointCellData(seg_id, local_scalar_cell_data, local_vector_cell_data,
                                      cell_data_scalar_read, cell_data_vector_read);
            tag.parse(reader);
          }


          if (tag.name() != "/piece")
            throw bad_file_format_exception("* ViennaGrid: vtk_reader::parse_vtu_segment(): Parse error: Expected </Piece> tag!");

          tag.parse_and_check_name(reader, "/unstructuredgrid", filename);
          tag.parse_and_check_name(reader, "/vtkfile", filename);

          closeFile();
        }
        catch (std::exception const & ex) {
          std::cerr << "Problems while reading file " << filename << std::endl;
          std::cerr << "what(): " << ex.what() << std::endl;
        }

      }

      /** @brief Processes a .vtu file that represents a full mesh */
      void process_vtu(std::string const & filename)
      {
        parse_vtu_segment(filename, 0);
      }

      /** @brief Processes a .pvd file containing the links to the segments stored in individual .vtu files */
      void process_pvd(std::string const & filename)
      {
        std::map<int, std::string> filenames;

        //extract path from .pvd file:
        std::string::size_type pos = filename.rfind("/");
        std::string path_to_pvd;
        if (pos == std::string::npos)
          pos = filename.rfind("\\"); //a tribute to Windows... ;-)

        if (pos != std::string::npos)
          path_to_pvd = filename.substr(0, pos + 1);

        openFile(filename);

        //
        // Step 1: Get segments from pvd file:
        //
        xml_tag<> tag;

        tag.parse(reader);
        if (tag.name() != "?xml" && tag.name() != "?xml?")
          throw bad_file_format_exception("* ViennaGrid: vtk_reader::process_pvd(): Parse error: No opening <?xml?> tag!");

        tag.parse(reader);
        if (tag.name() != "vtkfile")
          throw bad_file_format_exception("* ViennaGrid: vtk_reader::process_pvd(): Parse error: VTKFile tag expected!");

        if (!tag.has_attribute("type"))
          throw bad_file_format_exception("* ViennaGrid: vtk_reader::process_pvd(): Parse error: VTKFile tag has no attribute 'type'!");

        if (string_to_lower(tag.get_value("type")) != "collection")
          throw bad_file_format_exception("* ViennaGrid: vtk_reader::process_pvd(): Parse error: Type-attribute of VTKFile tag is not 'Collection'!");

        tag.parse(reader);
        if (tag.name() != "collection")
          throw bad_file_format_exception("* ViennaGrid: vtk_reader::process_pvd(): Parse error: Collection tag expected!");

        while (reader.good())
        {
          tag.parse(reader);

          if (tag.name() == "/collection")
            break;

          if (tag.name() != "dataset")
            throw bad_file_format_exception("* ViennaGrid: vtk_reader::process_pvd(): Parse error: DataSet tag expected!");

          if (!tag.has_attribute("file"))
            throw bad_file_format_exception("* ViennaGrid: vtk_reader::process_pvd(): Parse error: DataSet tag has no file attribute!");

          filenames[ atoi(tag.get_value("part").c_str()) ] = tag.get_value("file");

        }

        tag.parse(reader);
        if (tag.name() != "/vtkfile")
          throw bad_file_format_exception("* ViennaGrid: vtk_reader::process_pvd(): Parse error: Closing VTKFile tag expected!");

        closeFile();

        assert(filenames.size() > 0 && "No segments in pvd-file specified!");

        //
        // Step 2: Parse .vtu files:
        //
        for (std::map<int, std::string>::iterator it = filenames.begin(); it != filenames.end(); ++it)
        {
          #if defined VIENNAGRID_DEBUG_ALL || defined VIENNAGRID_DEBUG_IO
          std::cout << "Parsing file " << path_to_pvd + it->second << std::endl;
          #endif
          parse_vtu_segment(path_to_pvd + it->second, it->first);
        }

      }


    public:


      ~vtk_reader() { pre_clear(); post_clear(); }


      /** @brief Triggers the read process.
       *
       * @param mesh_obj      The mesh to which the file content is read
       * @param segmentation  The segmentation to which the file content is read
       * @param filename      Name of the file containing the mesh. Either .pvd (multi-segment) or .vtu (single segment)
       */
      void operator()(MeshType & mesh_obj, SegmentationType & segmentation, std::string const & filename)
      {
        pre_clear();

        std::string::size_type pos  = filename.rfind(".")+1;
        std::string extension = filename.substr(pos, filename.size());

        if(extension == "vtu")
        {
          process_vtu(filename);
        }
        else if(extension == "pvd")
        {
          process_pvd(filename);
        }
        else
        {
          std::stringstream ss;
          ss << "* ViennaGrid: " << filename << " - ";
          ss << "Error: vtk-reader does not support file extension: " << extension << "\n";
          ss << "       the vtk-reader supports: \n";
          ss << "       *.vtu -- single-segment meshs\n";
          ss << "       *.pvd -- multi-segment meshs\n";

          throw bad_file_format_exception(ss.str());
        }

        //
        // push everything to the ViennaGrid mesh:
        //
        setupVertices(mesh_obj);
//         for (size_t seg_id = 0; seg_id < local_cell_num.size(); ++seg_id)
        for (std::map<int, std::size_t>::iterator it = local_cell_num.begin(); it != local_cell_num.end(); ++it)
        {
          segmentation.get_make_segment( it->first );
        }

//         for (size_t seg_id = 0; seg_id < local_cell_num.size(); ++seg_id)
        for (std::map<int, std::size_t>::iterator it = local_cell_num.begin(); it != local_cell_num.end(); ++it)
        {
          setupCells(mesh_obj, segmentation, it->first);
          setupData(mesh_obj, segmentation, it->first);
        }

        post_clear();
      } //operator()


      /** @brief Triggers the read process.
       *
       * @param mesh_obj      The mesh to which the file content is read
       * @param filename      Name of the file containing the mesh. Either .pvd (multi-segment) or .vtu (single segment)
       */
      void operator()(MeshType & mesh_obj, std::string const & filename)
      {
        SegmentationType tmp(mesh_obj);
        (*this)(mesh_obj, tmp, filename);
      }




      /** @brief Returns the data names of all scalar vertex data read */
      std::vector<std::string> scalar_vertex_data_names(segment_id_type segment_id) const
      {
        std::vector<std::string> ret;

        std::map<int, std::deque<std::pair<std::string, std::deque<double> > > >::const_iterator it = local_scalar_vertex_data.find(segment_id);
        if (it == local_scalar_vertex_data.end())
          return ret;

        for (std::size_t i=0; i<it->second.size(); ++i)
          ret.push_back(it->second[i].first);

        return ret;
      }

      /** @brief Returns the data names of all vector vertex data read */
      std::vector<std::string> vector_vertex_data_names(segment_id_type segment_id) const
      {
        std::vector<std::string> ret;

        std::map<int, std::deque<std::pair<std::string, std::deque<double> > > >::const_iterator it = local_vector_vertex_data.find(segment_id);
        if (it == local_vector_vertex_data.end())
          return ret;

        for (std::size_t i=0; i<it->second.size(); ++i)
          ret.push_back(it->second[i].first);

        return ret;
      }

      /** @brief Returns the data names of all scalar cell data read */
      std::vector<std::string> scalar_cell_data_names(segment_id_type segment_id) const
      {
        std::vector<std::string> ret;

        std::map<int, std::deque<std::pair<std::string, std::deque<double> > > >::const_iterator it = local_scalar_cell_data.find(segment_id);
        if (it == local_scalar_cell_data.end())
          return ret;

        for (std::size_t i=0; i<it->second.size(); ++i)
          ret.push_back(it->second[i].first);

        return ret;
      }

      /** @brief Returns the data names of all vector cell data read */
      std::vector<std::string> vector_cell_data_names(segment_id_type segment_id) const
      {
        std::vector<std::string> ret;

        std::map<int, std::deque<std::pair<std::string, std::deque<double> > > >::const_iterator it = local_vector_cell_data.find(segment_id);
        if (it == local_vector_cell_data.end())
          return ret;

        for (std::size_t i=0; i<it->second.size(); ++i)
          ret.push_back(it->second[i].first);

        return ret;
      }

        // Extract data read from file:

        /** @brief Returns the names of all scalar-valued data read for vertices */
        std::vector<std::pair<std::size_t, std::string> > const & get_scalar_data_on_vertices() const
        {
          return vertex_data_scalar_read;
        }

        /** @brief Returns the names of all vector-valued data read for vertices */
        std::vector<std::pair<std::size_t, std::string> > const & get_vector_data_on_vertices() const
        {
          return vertex_data_vector_read;
        }

        /** @brief Returns the names of all scalar-valued data read for cells */
        std::vector<std::pair<std::size_t, std::string> > const & get_scalar_data_on_cells() const
        {
          return cell_data_scalar_read;
        }

        /** @brief Returns the names of all vector-valued data read for cells */
        std::vector<std::pair<std::size_t, std::string> > const & get_vector_data_on_cells() const
        {
          return cell_data_vector_read;
        }



    private:

      template<typename MapType, typename AccessorOrFieldType>
      void register_to_map(MapType & map, AccessorOrFieldType accessor_or_field, std::string const & name)
      {
          typename MapType::iterator it = map.find(name);
          if (it != map.end())
          {
            delete it->second;
            it->second = new dynamic_field_wrapper<AccessorOrFieldType>( accessor_or_field );
          }
          else
            map[name] = new dynamic_field_wrapper<AccessorOrFieldType>( accessor_or_field );
      }


    public:

      /** @brief Registers a vertex scalar accessor/field with a given quantity name */
      template<typename AccessorOrFieldType>
      void register_vertex_scalar(AccessorOrFieldType accessor_or_field, std::string const & quantity_name)
      { register_to_map(registered_vertex_scalar_data, accessor_or_field, quantity_name); }

      /** @brief Registers a vertex scalar accessor/field with a given quantity name for a given segment ID */
      template<typename AccessorOrFieldType>
      void register_vertex_scalar(segment_id_type seg_id, AccessorOrFieldType accessor_or_field, std::string const & quantity_name)
      { register_to_map(registered_segment_vertex_scalar_data[seg_id], accessor_or_field, quantity_name); }

      /** @brief Registers a vertex scalar accessor/field with a given quantity name for a given segment */
      template<typename AccessorOrFieldType>
      void register_vertex_scalar(SegmentHandleType const & segment, AccessorOrFieldType accessor_or_field, std::string const & quantity_name)
      { register_vertex_scalar(segment.id(), accessor_or_field, quantity_name); }


      /** @brief Registers a vertex vector accessor/field with a given quantity name */
      template<typename AccessorOrFieldType>
      void register_vertex_vector(AccessorOrFieldType accessor_or_field, std::string const & quantity_name)
      { register_to_map(registered_vertex_vector_data, accessor_or_field, quantity_name); }

      /** @brief Registers a vertex vector accessor/field with a given quantity name for a given segment ID */
      template<typename AccessorOrFieldType>
      void register_vertex_vector(segment_id_type seg_id, AccessorOrFieldType accessor_or_field, std::string const & quantity_name)
      { register_to_map(registered_segment_vertex_vector_data[seg_id], accessor_or_field, quantity_name); }

      /** @brief Registers a vertex vector accessor/field with a given quantity name for a given segment */
      template<typename AccessorOrFieldType>
      void register_vertex_vector(SegmentHandleType const & segment, AccessorOrFieldType accessor_or_field, std::string const & quantity_name)
      { register_vertex_vector(segment.id(), accessor_or_field, quantity_name); }




      /** @brief Registers a cell scalar accessor/field with a given quantity name */
      template<typename AccessorOrFieldType>
      void register_cell_scalar(AccessorOrFieldType accessor_or_field, std::string const & quantity_name)
      { register_to_map(registered_cell_scalar_data, accessor_or_field, quantity_name); }

      /** @brief Registers a cell scalar accessor/field with a given quantity name for a given segment ID */
      template<typename AccessorOrFieldType>
      void register_cell_scalar(segment_id_type seg_id, AccessorOrFieldType accessor_or_field, std::string const & quantity_name)
      { register_to_map(registered_segment_cell_scalar_data[seg_id], accessor_or_field, quantity_name); }

      /** @brief Registers a cell scalar accessor/field with a given quantity name for a given segment */
      template<typename AccessorOrFieldType>
      void register_cell_scalar(SegmentHandleType const & segment, AccessorOrFieldType accessor_or_field, std::string const & quantity_name)
      { register_cell_scalar(segment.id(), accessor_or_field, quantity_name); }


      /** @brief Registers a cell vector accessor/field with a given quantity name */
      template<typename AccessorOrFieldType>
      void register_cell_vector(AccessorOrFieldType accessor_or_field, std::string const & quantity_name)
      { register_to_map(registered_cell_vector_data, accessor_or_field, quantity_name); }

      /** @brief Registers a cell vector accessor/field with a given quantity name for a given segment ID */
      template<typename AccessorOrFieldType>
      void register_cell_vector(segment_id_type seg_id, AccessorOrFieldType accessor_or_field, std::string const & quantity_name)
      { register_to_map(registered_segment_cell_vector_data[seg_id], accessor_or_field, quantity_name); }

      /** @brief Registers a cell vector accessor/field with a given quantity name for a given segment */
      template<typename AccessorOrFieldType>
      void register_cell_vector(SegmentHandleType const & segment, AccessorOrFieldType accessor_or_field, std::string const & quantity_name)
      { register_cell_vector(segment.id(), accessor_or_field, quantity_name); }






      /** @brief Returns the vertex scalar field for a given quantity name and a given segment ID. If the quantity name was registered before an invalid field is returned. */
      typename viennagrid::result_of::field<const std::deque<double>, VertexType >::type vertex_scalar_field( std::string const & quantity_name, segment_id_type seg_id ) const
      {
        typename std::map< std::string, std::map<segment_id_type, std::deque<double> > >::const_iterator it = vertex_scalar_data.find(quantity_name);
        if (it == vertex_scalar_data.end()) return typename viennagrid::result_of::field<const std::deque<double>, VertexType >::type();

        typename std::map<segment_id_type, std::deque<double> >::const_iterator jt = it->second.find( seg_id );
        if (jt == it->second.end()) return typename viennagrid::result_of::field<const std::deque<double>, VertexType >::type();

        return viennagrid::make_field<VertexType>( jt->second );
      }

      /** @brief Returns the vertex scalar field for a given quantity name and a given segment. If the quantity name was registered before an invalid field is returned. */
      typename viennagrid::result_of::field<const std::deque<double>, VertexType >::type vertex_scalar_field( std::string const & quantity_name, SegmentHandleType const & segment ) const
      { return vertex_scalar_field(quantity_name, segment.id()); }


      /** @brief Returns the vertex vector field for a given quantity name and a given segment ID. If the quantity name was registered before an invalid field is returned. */
      typename viennagrid::result_of::field<const std::deque<vector_data_type>, VertexType >::type vertex_vector_field( std::string const & quantity_name, segment_id_type seg_id ) const
      {
        typename std::map< std::string, std::map<segment_id_type, std::deque<vector_data_type> > >::const_iterator it = vertex_vector_data.find(quantity_name);
        if (it == vertex_vector_data.end()) return typename viennagrid::result_of::field<const std::deque<vector_data_type>, VertexType >::type();

        typename std::map<segment_id_type, std::deque<vector_data_type> >::const_iterator jt = it->second.find( seg_id );
        if (jt == it->second.end()) return typename viennagrid::result_of::field<const std::deque<vector_data_type>, VertexType >::type();

        return viennagrid::make_field<VertexType>( jt->second );
      }

      /** @brief Returns the vertex vector field for a given quantity name and a given segment. If the quantity name was registered before an invalid field is returned. */
      typename viennagrid::result_of::field<const std::deque<vector_data_type>, VertexType >::type vertex_vector_field( std::string const & quantity_name, SegmentHandleType const & segment )
      { return vertex_vector_field(quantity_name, segment.id()); }



      /** @brief Returns the cell scalar field for a given quantity name and a given segment ID. If the quantity name was registered before an invalid field is returned. */
      typename viennagrid::result_of::field<const std::deque<double>, CellType >::type cell_scalar_field( std::string const & quantity_name, segment_id_type seg_id ) const
      {
        typename std::map< std::string, std::map<segment_id_type, std::deque<double> > >::const_iterator it = cell_scalar_data.find(quantity_name);
        if (it == cell_scalar_data.end()) return typename viennagrid::result_of::field<const std::deque<double>, CellType >::type();

        typename std::map<segment_id_type, std::deque<double> >::const_iterator jt = it->second.find( seg_id );
        if (jt == it->second.end()) return typename viennagrid::result_of::field<const std::deque<double>, CellType >::type();

        return viennagrid::make_field<CellType>( jt->second );
      }

      /** @brief Returns the cell scalar field for a given quantity name and a given segment. If the quantity name was registered before an invalid field is returned. */
      typename viennagrid::result_of::field<const std::deque<double>, CellType >::type cell_scalar_field( std::string const & quantity_name, SegmentHandleType const & segment ) const
      { return cell_scalar_field(quantity_name, segment.id()); }


      /** @brief Returns the cell vector field for a given quantity name and a given segment ID. If the quantity name was registered before an invalid field is returned. */
      typename viennagrid::result_of::field<const std::deque<vector_data_type>, CellType >::type cell_vector_field( std::string const & quantity_name, segment_id_type seg_id ) const
      {
        typename std::map< std::string, std::map<segment_id_type, std::deque<vector_data_type> > >::const_iterator it = cell_vector_data.find(quantity_name);
        if (it == cell_vector_data.end()) return typename viennagrid::result_of::field<const std::deque<vector_data_type>, CellType >::type();

        typename std::map<segment_id_type, std::deque<vector_data_type> >::const_iterator jt = it->second.find( seg_id );
        if (jt == it->second.end()) return typename viennagrid::result_of::field<const std::deque<vector_data_type>, CellType >::type();

        return viennagrid::make_field<CellType>( jt->second );
      }

      /** @brief Returns the cell vector field for a given quantity name and a given segment. If the quantity name was registered before an invalid field is returned. */
      typename viennagrid::result_of::field<const std::deque<vector_data_type>, CellType >::type cell_vector_field( std::string const & quantity_name, SegmentHandleType const & segment ) const
      { return cell_vector_field(quantity_name, segment.id()); }


    private:

      // Quantities read:
      std::vector<std::pair<std::size_t, std::string> >         vertex_data_scalar_read;
      std::vector<std::pair<std::size_t, std::string> >         vertex_data_vector_read;

      std::vector<std::pair<std::size_t, std::string> >         cell_data_scalar_read;
      std::vector<std::pair<std::size_t, std::string> >         cell_data_vector_read;


      std::map< std::string, std::map<segment_id_type, std::deque<double> > >           vertex_scalar_data;
      std::map< std::string, std::map<segment_id_type, std::deque<vector_data_type> > > vertex_vector_data;

      std::map< std::string, std::map<segment_id_type, std::deque<double> > >           cell_scalar_data;
      std::map< std::string, std::map<segment_id_type, std::deque<vector_data_type> > > cell_vector_data;


      VertexScalarOutputFieldContainer          registered_vertex_scalar_data;
      VertexVectorOutputFieldContainer          registered_vertex_vector_data;

      CellScalarOutputFieldContainer          registered_cell_scalar_data;
      CellVectorOutputFieldContainer          registered_cell_vector_data;

      std::map< segment_id_type, VertexScalarOutputFieldContainer > registered_segment_vertex_scalar_data;
      std::map< segment_id_type, VertexVectorOutputFieldContainer > registered_segment_vertex_vector_data;

      std::map< segment_id_type, CellScalarOutputFieldContainer >   registered_segment_cell_scalar_data;
      std::map< segment_id_type, CellVectorOutputFieldContainer >   registered_segment_cell_vector_data;

    }; //class vtk_reader


    /** @brief Convenience function for importing a mesh using a single line of code. */
    template <typename MeshType, typename SegmentationType >
    int import_vtk(MeshType & mesh_obj, SegmentationType & segmentation, std::string const & filename)
    {
      vtk_reader<MeshType, SegmentationType> vtk_reader;
      return vtk_reader(mesh_obj, segmentation, filename);
    }

    /** @brief Convenience function for importing a mesh using a single line of code. */
    template <typename MeshType>
    int import_vtk(MeshType & mesh_obj, std::string const & filename)
    {
      vtk_reader<MeshType> vtk_reader;
      return vtk_reader(mesh_obj, filename);
    }





    /** @brief Registers scalar-valued data on vertices at the VTK reader
      *
      * @tparam MeshT             The mesh type to be read to
      * @tparam SegmentationT       The segmentation type to be read to
      * @tparam AccessorOrFieldT    An accessor/field holding scalar data
      * @param  reader              The VTK reader object for which the data should be registered
      * @param  accessor_or_field   The accessor object holding scalar data on vertices
      * @param  quantity_name       The quantity name within the VTK file
      */
    template <typename MeshT, typename SegmentationT, typename AccessorOrFieldT>
    vtk_reader<MeshT, SegmentationT> & add_scalar_data_on_vertices(vtk_reader<MeshT, SegmentationT> & reader,
                                                                    AccessorOrFieldT const accessor_or_field,
                                                                    std::string const & quantity_name)
    {
      reader.register_vertex_scalar(accessor_or_field, quantity_name);
      return reader;
    }

    /** @brief Registers vector-valued data on vertices at the VTK reader
      *
      * @tparam MeshT             The mesh type to be read to
      * @tparam SegmentationT       The segmentation type to be read to
      * @tparam AccessorOrFieldT    An accessor/field holding vector data
      * @param  reader              The VTK reader object for which the data should be registered
      * @param  accessor_or_field   The accessor object holding vector data on vertices
      * @param  quantity_name       The quantity name within the VTK file
      */
    template <typename MeshT, typename SegmentationT, typename AccessorOrFieldT>
    vtk_reader<MeshT, SegmentationT> & add_vector_data_on_vertices(vtk_reader<MeshT, SegmentationT> & reader,
                                                                    AccessorOrFieldT const accessor_or_field,
                                                                    std::string const & quantity_name)
    {
      reader.register_vertex_vector(accessor_or_field, quantity_name);
      return reader;
    }





    /** @brief Registers scalar-valued data on cells at the VTK reader
      *
      * @tparam MeshT             The mesh type to be read to
      * @tparam SegmentationT       The segmentation type to be read to
      * @tparam AccessorOrFieldT    An accessor/field holding scalar data
      * @param  reader              The VTK reader object for which the data should be registered
      * @param  accessor_or_field   The accessor object holding scalar data on cells
      * @param  quantity_name       The quantity name within the VTK file
      */
    template <typename MeshT, typename SegmentationT, typename AccessorOrFieldT>
    vtk_reader<MeshT, SegmentationT> & add_scalar_data_on_cells(vtk_reader<MeshT, SegmentationT> & reader,
                                                                    AccessorOrFieldT const accessor_or_field,
                                                                    std::string const & quantity_name)
    {
      reader.register_cell_scalar(accessor_or_field, quantity_name);
      return reader;
    }

    /** @brief Registers vector-valued data on cells at the VTK reader
      *
      * @tparam MeshT             The mesh type to be read to
      * @tparam SegmentationT       The segmentation type to be read to
      * @tparam AccessorOrFieldT    An accessor/field holding vector data
      * @param  reader              The VTK reader object for which the data should be registered
      * @param  accessor_or_field   The accessor object holding vector data on cells
      * @param  quantity_name       The quantity name within the VTK file
      */
    template <typename MeshT, typename SegmentationT, typename AccessorOrFieldT>
    vtk_reader<MeshT, SegmentationT> & add_vector_data_on_cells(vtk_reader<MeshT, SegmentationT> & reader,
                                                                    AccessorOrFieldT const accessor_or_field,
                                                                    std::string const & quantity_name)
    {
      reader.register_cell_vector(accessor_or_field, quantity_name);
      return reader;
    }




    /** @brief Returns the names of all scalar-valued data read for vertices */
    template<typename VTKReaderT>
    std::vector<std::pair<std::size_t, std::string> > const & get_scalar_data_on_vertices(VTKReaderT const & reader)
    {
      return reader.get_scalar_data_on_vertices();
    }

    /** @brief Returns the names of all vector-valued data read for vertices */
    template<typename VTKReaderT>
    std::vector<std::pair<std::size_t, std::string> > const & get_vector_data_on_vertices(VTKReaderT const & reader)
    {
      return reader.get_vector_data_on_vertices();
    }

    /** @brief Returns the names of all scalar-valued data read for cells */
    template<typename VTKReaderT>
    std::vector<std::pair<std::size_t, std::string> > const & get_scalar_data_on_cells(VTKReaderT const & reader)
    {
      return reader.get_scalar_data_on_cells();
    }

    /** @brief Returns the names of all vector-valued data read for cells */
    template<typename VTKReaderT>
    std::vector<std::pair<std::size_t, std::string> > const & get_vector_data_on_cells(VTKReaderT const & reader)
    {
      return reader.get_vector_data_on_cells();
    }



  } //namespace io
} //namespace viennagrid

#endif
