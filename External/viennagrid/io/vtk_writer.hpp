#ifndef VIENNAGRID_IO_VTK_WRITER_HPP
#define VIENNAGRID_IO_VTK_WRITER_HPP

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
#include <sstream>
#include <iostream>

#include "viennagrid/forwards.hpp"
#include "viennagrid/mesh/segmentation.hpp"
#include "viennagrid/mesh/mesh.hpp"
#include "viennagrid/io/helper.hpp"
#include "viennagrid/io/vtk_common.hpp"

/** @file viennagrid/io/vtk_writer.hpp
    @brief Provides a writer to VTK files
*/

namespace viennagrid
{
  namespace io
  {

    template<typename ElementType>
    struct ValueTypeInformation;

    template<>
    struct ValueTypeInformation<double>
    {
      typedef double value_type;

      static std::string type_name() { return "Float32"; }
      static int num_components() { return 1; }
      static void write( std::ostream & os, value_type value ) { os << value; }
    };

    template<>
    struct ValueTypeInformation< std::vector<double> >
    {
      typedef std::vector<double> value_type;

      static std::string type_name() { return "Float32"; }
      static int num_components() { return 3; }
      static void write( std::ostream & os, value_type const & value )
      {
        os << value[0] << " " << value[1] << " " << value[2];
//         for (int i = 0; i < std::min(value.size(), std::size_t(3)); ++i)
//           os << value[i] << " ";
//
//         for (int i = std::min(value.size(), std::size_t(3)); i < 3; ++i)
//           os << "0 ";
      }
    };


    /////////////////// VTK export ////////////////////////////

    //helper: translate element tags to VTK-element types
    // (see: http://www.vtk.org/VTK/img/file-formats.pdf, page 9)

    /** @brief Main VTK writer class. Writes a mesh or a segment to a file
     *
     * @tparam MeshType         Type of the ViennaGrid mesh. Must not be a segment!
     * @tparam SegmentationType   Type of the ViennaGrid segmentation. Default is the default segmentation of MeshType
     */
    template < typename MeshType, typename SegmentationType = typename viennagrid::result_of::segmentation<MeshType>::type >
    class vtk_writer
    {
    protected:

      typedef typename SegmentationType::segment_id_type segment_id_type;

      typedef typename result_of::point<MeshType>::type   PointType;
      typedef typename result_of::coord<PointType>::type  CoordType;

      typedef typename result_of::cell_tag<MeshType>::type                   CellTag;
      typedef typename result_of::element<MeshType, CellTag>::type           CellType;
      typedef typename result_of::const_handle<MeshType, CellTag>::type      ConstCellHandleType;
      typedef typename result_of::id<CellType>::type                         CellIDType;

      typedef typename result_of::element<MeshType, vertex_tag>::type            VertexType;
      typedef typename result_of::handle<MeshType, vertex_tag>::type             VertexHandleType;
      typedef typename result_of::const_handle<MeshType, vertex_tag>::type       ConstVertexHandleType;
      typedef typename result_of::id<VertexType>::type                           VertexIDType;

      typedef typename SegmentationType::segment_handle_type SegmentHandleType;


      typedef std::vector<double> vector_data_type;

      typedef base_dynamic_field<const double, VertexType> VertexScalarBaseAccesor;
      typedef std::map< std::string, VertexScalarBaseAccesor * > VertexScalarOutputAccessorContainer;

      typedef base_dynamic_field<const vector_data_type, VertexType> VertexVectorBaseAccesor;
      typedef std::map< std::string, VertexVectorBaseAccesor * > VertexVectorOutputAccessorContainer;

      typedef base_dynamic_field<const double, CellType> CellScalarBaseAccesor;
      typedef std::map< std::string, CellScalarBaseAccesor * > CellScalarOutputAccessorContainer;

      typedef base_dynamic_field<const vector_data_type, CellType> CellVectorBaseAccesor;
      typedef std::map< std::string, CellVectorBaseAccesor * > CellVectorOutputAccessorContainer;

    protected:


      template<typename map_type>
      void clear_map( map_type & map )
      {
        for (typename map_type::iterator it = map.begin(); it != map.end(); ++it)
          delete it->second;

        map.clear();
      }

      void clear()
      {
        clear_map(vertex_scalar_data);
        clear_map(vertex_vector_data);

        clear_map(cell_scalar_data);
        clear_map(cell_vector_data);


        for (typename std::map< segment_id_type, VertexScalarOutputAccessorContainer>::iterator it = segment_vertex_scalar_data.begin(); it != segment_vertex_scalar_data.end(); ++it)
          clear_map(it->second);

        for (typename std::map< segment_id_type, VertexVectorOutputAccessorContainer>::iterator it = segment_vertex_vector_data.begin(); it != segment_vertex_vector_data.end(); ++it)
          clear_map(it->second);


        for (typename std::map< segment_id_type, CellScalarOutputAccessorContainer>::iterator it = segment_cell_scalar_data.begin(); it != segment_cell_scalar_data.end(); ++it)
          clear_map(it->second);

        for (typename std::map< segment_id_type, CellVectorOutputAccessorContainer>::iterator it = segment_cell_vector_data.begin(); it != segment_cell_vector_data.end(); ++it)
          clear_map(it->second);


        segment_vertex_scalar_data.clear();
        segment_vertex_vector_data.clear();

        segment_cell_scalar_data.clear();
        segment_cell_vector_data.clear();


        used_vertex_map.clear();
        vertex_to_index_map.clear();
        used_cell_map.clear();
      }

      /** @brief Writes the XML file header */
      void writeHeader(std::ofstream & writer)
      {
        writer << "<?xml version=\"1.0\"?>" << std::endl;
        writer << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">" << std::endl;
        writer << " <UnstructuredGrid>" << std::endl;
      }


      template<typename SegmentHandleT>
      std::size_t preparePoints(SegmentHandleT const & segment, segment_id_type seg_id)
      {
        typedef typename viennagrid::result_of::const_element_range<SegmentHandleT, CellTag>::type     CellRange;
        typedef typename viennagrid::result_of::iterator<CellRange>::type                                         CellIterator;

        typedef typename viennagrid::result_of::const_element_range<CellType, vertex_tag>::type      VertexOnCellRange;
        typedef typename viennagrid::result_of::iterator<VertexOnCellRange>::type         VertexOnCellIterator;

        std::map< VertexIDType, ConstVertexHandleType > & current_used_vertex_map = used_vertex_map[seg_id];
        std::map< ConstVertexHandleType, VertexIDType > & current_vertex_to_index_map = vertex_to_index_map[seg_id];


        CellRange cells(segment);

        for (CellIterator it = cells.begin(); it != cells.end(); ++it)
        {
          VertexOnCellRange vertices_on_cell(*it);
          for (VertexOnCellIterator jt = vertices_on_cell.begin(); jt != vertices_on_cell.end(); ++jt)
          {
              typename std::map< VertexIDType, ConstVertexHandleType >::iterator kt = current_used_vertex_map.find( jt->id() );
              if (kt == current_used_vertex_map.end())
                current_used_vertex_map.insert( std::make_pair(jt->id(), jt.handle()) );


//                   typename std::map< ConstVertexHandleType, VertexIDType >::iterator kt = current_vertex_to_index_map.find( jt.handle() );
//                   if (kt == current_vertex_to_index_map.end())
//                   {
// //                       current_vertex_to_index_map.insert( std::make_pair( jt.handle(), jt->id() ) );
//                       current_vertex_to_index_map.insert( std::make_pair( jt.handle(), index ) );
// //                       current_used_vertex_map[ index ] = jt.handle();
//                       current_used_vertex_map[ jt->id() ] = jt.handle();
//                       index++;
//                   }
          }
        }

        typename VertexIDType::base_id_type index = 0;
        for (typename std::map< VertexIDType, ConstVertexHandleType >::iterator it = current_used_vertex_map.begin(); it != current_used_vertex_map.end(); ++it)
          current_vertex_to_index_map.insert( std::make_pair( it->second, VertexIDType(index++) ) );

        return current_vertex_to_index_map.size();
      }

      template<typename MeshSegmentHandleT>
      std::size_t prepareCells(MeshSegmentHandleT const & domseg, segment_id_type seg_id)
      {
        typedef typename viennagrid::result_of::const_element_range<MeshSegmentHandleT, CellTag>::type     CellRange;
        typedef typename viennagrid::result_of::iterator<CellRange>::type                                         CellIterator;

        std::map< CellIDType, ConstCellHandleType > & current_used_cells_map = used_cell_map[seg_id];

        int index = 0;
        CellRange cells(domseg);
        for (CellIterator cit  = cells.begin();
                          cit != cells.end();
                        ++cit, ++index)
            {
              current_used_cells_map[ cit->id() ] = cit.handle();
            }

        return current_used_cells_map.size();
      }

      /** @brief Writes the vertices in the mesh */
      template <typename MeshSegmentHandleT>
      void writePoints(MeshSegmentHandleT const & domseg, std::ofstream & writer, segment_id_type seg_id)
      {
        std::map< VertexIDType, ConstVertexHandleType > & current_used_vertex_map = used_vertex_map[seg_id];

        writer << "   <Points>" << std::endl;
        writer << "    <DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">" << std::endl;

        for (typename std::map< VertexIDType, ConstVertexHandleType >::iterator it = current_used_vertex_map.begin(); it != current_used_vertex_map.end(); ++it)
        {
          const int dim = result_of::static_size<PointType>::value;
          PointWriter<dim>::write(writer, viennagrid::point(domseg, it->second) );

          // add 0's for less than three dimensions
          for (int i = dim; i < 3; ++i)
            writer << " " << 0;

          writer << std::endl;
        }
        writer << std::endl;
        writer << "    </DataArray>" << std::endl;
        writer << "   </Points> " << std::endl;
      } //writePoints()

      /** @brief Writes the cells to the mesh */
      template <typename MeshSegmentHandleT>
      void writeCells(MeshSegmentHandleT const & domseg, std::ofstream & writer, segment_id_type seg_id)
      {
        typedef typename viennagrid::result_of::const_element_range<CellType, vertex_tag>::type      VertexOnCellRange;
        typedef typename viennagrid::result_of::iterator<VertexOnCellRange>::type         VertexOnCellIterator;

        std::map< ConstVertexHandleType, VertexIDType > & current_vertex_to_index_map = vertex_to_index_map[seg_id];

        writer << "   <Cells> " << std::endl;
        writer << "    <DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">" << std::endl;

        std::map< CellIDType, ConstCellHandleType > & current_used_cells_map = used_cell_map[seg_id];
        for (typename std::map< CellIDType, ConstCellHandleType >::iterator it = current_used_cells_map.begin(); it != current_used_cells_map.end(); ++it)

        {
          //step 1: Write vertex indices in ViennaGrid orientation to array:
          CellType const & cell = viennagrid::dereference_handle(domseg, it->second);
//             CellType const & cell = *cit;

          std::vector<VertexIDType> viennagrid_vertices(viennagrid::boundary_elements<CellTag, vertex_tag>::num);
          VertexOnCellRange vertices_on_cell = viennagrid::elements<vertex_tag>(cell);
          std::size_t j = 0;
          for (VertexOnCellIterator vocit = vertices_on_cell.begin();
              vocit != vertices_on_cell.end();
              ++vocit, ++j)
          {
            viennagrid_vertices[j] = current_vertex_to_index_map[vocit.handle()];
          }

          //Step 2: Write the transformed connectivities:
          detail::viennagrid_to_vtk_orientations<CellTag> reorderer;
          for (std::size_t i=0; i<viennagrid_vertices.size(); ++i)
            writer << viennagrid_vertices[reorderer(i)] << " ";

          writer << std::endl;
        }

        writer << std::endl;
        writer << "    </DataArray>" << std::endl;

        writer << "    <DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">" << std::endl;
        for (std::size_t offsets = 1;
              //offsets <= current_used_cells_map.size();
              offsets <= viennagrid::elements<CellTag>(domseg).size();
              ++offsets)
        {
          writer << ( offsets * viennagrid::boundary_elements<CellTag, vertex_tag>::num) << " ";
        }
        writer << std::endl;
        writer << "    </DataArray>" << std::endl;

        writer << "    <DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">" << std::endl;
        for (std::size_t offsets = 1;
              //offsets <= current_used_cells_map.size();
             offsets <= viennagrid::elements<CellTag>(domseg).size();
              ++offsets)
        {
          writer << detail::ELEMENT_TAG_TO_VTK_TYPE<CellTag>::value << " ";
        }
        writer << std::endl;
        writer << "    </DataArray>" << std::endl;
        writer << "   </Cells>" << std::endl;
      }








      /** @brief Writes vector-valued data defined on vertices (points) to file */
      template <typename SegmentHandleT, typename IOAccessorType>
      void writePointData(SegmentHandleT const & segment, std::ofstream & writer, std::string const & name, IOAccessorType const & accessor, segment_id_type seg_id)
      {
        typedef typename IOAccessorType::value_type ValueType;

        writer << "    <DataArray type=\"" << ValueTypeInformation<ValueType>::type_name() << "\" Name=\"" << name <<
          "\" NumberOfComponents=\"" << ValueTypeInformation<ValueType>::num_components() << "\" format=\"ascii\">" << std::endl;

        std::map< VertexIDType, ConstVertexHandleType > & current_used_vertex_map = used_vertex_map[seg_id];
        for (typename std::map< VertexIDType, ConstVertexHandleType >::iterator it = current_used_vertex_map.begin(); it != current_used_vertex_map.end(); ++it)
        {
          ValueTypeInformation<ValueType>::write(writer, accessor( viennagrid::dereference_handle(segment, it->second) ));
          writer << " ";
        }
        writer << std::endl;

        writer << "    </DataArray>" << std::endl;
      } //writePointDataScalar


      /** @brief Writes vector-valued data defined on vertices (points) to file */
      template <typename SegmentHandleT, typename IOAccessorType>
      void writeCellData(SegmentHandleT const & segment, std::ofstream & writer, std::string const & name, IOAccessorType const & accessor, segment_id_type seg_id)
      {
        typedef typename IOAccessorType::value_type ValueType;

        writer << "    <DataArray type=\"" << ValueTypeInformation<ValueType>::type_name() << "\" Name=\"" << name <<
          "\" NumberOfComponents=\"" << ValueTypeInformation<ValueType>::num_components() << "\" format=\"ascii\">" << std::endl;


        std::map< CellIDType, ConstCellHandleType > & current_used_cells_map = used_cell_map[seg_id];
        for (typename std::map< CellIDType, ConstCellHandleType >::iterator it = current_used_cells_map.begin(); it != current_used_cells_map.end(); ++it)

        {
          //step 1: Write vertex indices in ViennaGrid orientation to array:
          CellType const & cell = viennagrid::dereference_handle(segment, it->second);
//             CellType const & cell = *cit;

          ValueTypeInformation<ValueType>::write(writer, accessor(cell));
          writer << " ";
        }
        writer << std::endl;

        writer << "    </DataArray>" << std::endl;
      } //writePointDataScalar



      /** @brief Writes the XML footer */
      void writeFooter(std::ofstream & writer)
      {
        writer << " </UnstructuredGrid>" << std::endl;
        writer << "</VTKFile>" << std::endl;
      }

    public:


      ~vtk_writer() { clear(); }

      /** @brief Triggers the write process to a XML file. Make sure that all data to be written to the file is already passed to the writer
       *
       * @param mesh_obj   The ViennaGrid mesh.
       * @param filename   The file to write to
       */
      void operator()(MeshType const & mesh_obj, std::string const & filename)
      {
          std::stringstream ss;
          ss << filename << ".vtu";
          std::ofstream writer(ss.str().c_str());

          if (!writer)
            throw cannot_open_file_exception("* ViennaGrid: vtk_writer::operator(): File " + filename + ": Cannot open file!");

          writeHeader(writer);

          segment_id_type tmp_id = segment_id_type();

          std::size_t num_points = preparePoints(mesh_obj, tmp_id);
          prepareCells(mesh_obj, tmp_id);

          writer << "  <Piece NumberOfPoints=\""
                 << num_points
                 << "\" NumberOfCells=\""
                 << viennagrid::elements<CellTag>(mesh_obj).size()
                 << "\">" << std::endl;

          writePoints(mesh_obj, writer, tmp_id);

          if (vertex_scalar_data.size() > 0 || vertex_vector_data.size() > 0)
          {
            writer << "   <PointData>" << std::endl;

              for (typename VertexScalarOutputAccessorContainer::const_iterator it = vertex_scalar_data.begin(); it != vertex_scalar_data.end(); ++it)
                writePointData( mesh_obj, writer, it->first, *(it->second), tmp_id );
              for (typename VertexVectorOutputAccessorContainer::const_iterator it = vertex_vector_data.begin(); it != vertex_vector_data.end(); ++it)
                writePointData( mesh_obj, writer, it->first, *(it->second), tmp_id );

            writer << "   </PointData>" << std::endl;
          }

          writeCells(mesh_obj, writer, tmp_id);
          if (cell_scalar_data.size() > 0 || cell_vector_data.size() > 0)
          {
            writer << "   <CellData>" << std::endl;

              for (typename CellScalarOutputAccessorContainer::const_iterator it = cell_scalar_data.begin(); it != cell_scalar_data.end(); ++it)
                writeCellData( mesh_obj, writer, it->first, *(it->second), tmp_id );
              for (typename CellVectorOutputAccessorContainer::const_iterator it = cell_vector_data.begin(); it != cell_vector_data.end(); ++it)
                writeCellData( mesh_obj, writer, it->first, *(it->second), tmp_id );

            writer << "   </CellData>" << std::endl;
          }

          writer << "  </Piece>" << std::endl;
          writeFooter(writer);

        clear();
      }

      /** @brief Triggers the write process to a XML file. Make sure that all data to be written to the file is already passed to the writer
       *
       * @param mesh_obj      The ViennaGrid mesh.
       * @param segmentation  The ViennaGrid segmentation.
       * @param filename      The file to write to
       */
      void operator()(MeshType const & mesh_obj, SegmentationType const & segmentation, std::string const & filename)
      {
          if (segmentation.size() <= 1) return (*this)(mesh_obj, filename);

          //
          // Step 1: Write meta information
          //
          {
            std::stringstream ss;
            ss << filename << "_main.pvd";
            std::ofstream writer(ss.str().c_str());

            std::string short_filename = filename;
            std::string::size_type pos = filename.rfind("/");
            if (pos == std::string::npos)
              pos = filename.rfind("\\");   //A tribute to Windows

            if (pos != std::string::npos)
              short_filename = filename.substr(pos+1, filename.size());

            if (!writer){
              clear();
              throw cannot_open_file_exception("* ViennaGrid: vtk_writer::operator(): File " + filename + ": Cannot open file!");
            }

            writer << "<?xml version=\"1.0\"?>" << std::endl;
            writer << "<VTKFile type=\"Collection\" version=\"0.1\" byte_order=\"LittleEndian\" compressor=\"vtkZLibDataCompressor\">" << std::endl;
            writer << "<Collection>" << std::endl;

            for (typename SegmentationType::const_iterator it = segmentation.begin(); it != segmentation.end(); ++it)
            {
              SegmentHandleType const & seg = *it;
              writer << "    <DataSet part=\"" << seg.id() << "\" file=\"" << short_filename << "_" << seg.id() << ".vtu\" name=\"Segment_" << seg.id() << "\"/>" << std::endl;
            }

            writer << "  </Collection>" << std::endl;
            writer << "</VTKFile>" << std::endl;
            writer.close();
          }

          //
          // Step 2: Write segments to individual files
          //

          for (typename SegmentationType::const_iterator it = segmentation.begin(); it != segmentation.end(); ++it)
          {
            SegmentHandleType const & seg = *it;

            std::stringstream ss;
            ss << filename << "_" << seg.id() << ".vtu";
            std::ofstream writer(ss.str().c_str());
            writeHeader(writer);

            if (!writer)
            {
              clear();
              throw cannot_open_file_exception("* ViennaGrid: vtk_writer::operator(): File " + ss.str() + ": Cannot open file!");
            }

            std::size_t num_points = preparePoints(seg, seg.id());
            prepareCells(seg, seg.id());

            writer << "  <Piece NumberOfPoints=\""
                  << num_points
                  << "\" NumberOfCells=\""
                  << viennagrid::elements<CellTag>(seg).size()
                  << "\">" << std::endl;

            writePoints(seg, writer, seg.id());


            VertexScalarOutputAccessorContainer const & current_segment_vertex_scalar_data = segment_vertex_scalar_data[ seg.id() ];
            VertexVectorOutputAccessorContainer const & current_segment_vertex_vector_data = segment_vertex_vector_data[ seg.id() ];

            if (vertex_scalar_data.size() > 0 || vertex_vector_data.size() > 0 || current_segment_vertex_scalar_data.size() > 0 || current_segment_vertex_vector_data.size() > 0)
            {
              writer << "   <PointData>" << std::endl;

              for (typename VertexScalarOutputAccessorContainer::const_iterator data_it = vertex_scalar_data.begin(); data_it != vertex_scalar_data.end(); ++data_it)
                writePointData( seg, writer, data_it->first, *(data_it->second), seg.id() );
              for (typename VertexVectorOutputAccessorContainer::const_iterator data_it = vertex_vector_data.begin(); data_it != vertex_vector_data.end(); ++data_it)
                writePointData( seg, writer, data_it->first, *(data_it->second), seg.id() );


              for (typename VertexScalarOutputAccessorContainer::const_iterator data_it = current_segment_vertex_scalar_data.begin(); data_it != current_segment_vertex_scalar_data.end(); ++data_it)
                writePointData( seg, writer, data_it->first, *(data_it->second), seg.id() );

              for (typename VertexVectorOutputAccessorContainer::const_iterator data_it = current_segment_vertex_vector_data.begin(); data_it != current_segment_vertex_vector_data.end(); ++data_it)
                writePointData( seg, writer, data_it->first, *(data_it->second), seg.id() );

              writer << "   </PointData>" << std::endl;
            }

            writeCells(seg, writer, seg.id());

            CellScalarOutputAccessorContainer const & current_segment_cell_scalar_data = segment_cell_scalar_data[ seg.id() ];
            CellVectorOutputAccessorContainer const & current_segment_cell_vector_data = segment_cell_vector_data[ seg.id() ];
            if (cell_scalar_data.size() > 0 || cell_vector_data.size() > 0 || current_segment_cell_scalar_data.size() > 0 || current_segment_cell_vector_data.size() > 0)
            {
              writer << "   <CellData>" << std::endl;

              for (typename CellScalarOutputAccessorContainer::const_iterator data_it = cell_scalar_data.begin(); data_it != cell_scalar_data.end(); ++data_it)
                writeCellData( seg, writer, data_it->first, *(data_it->second), seg.id() );
              for (typename CellVectorOutputAccessorContainer::const_iterator data_it = cell_vector_data.begin(); data_it != cell_vector_data.end(); ++data_it)
                writeCellData( seg, writer, data_it->first, *(data_it->second), seg.id() );


              for (typename CellScalarOutputAccessorContainer::const_iterator data_it = current_segment_cell_scalar_data.begin(); data_it != current_segment_cell_scalar_data.end(); ++data_it)
                writeCellData( seg, writer, data_it->first, *(data_it->second), seg.id() );
              for (typename CellVectorOutputAccessorContainer::const_iterator data_it = current_segment_cell_vector_data.begin(); data_it != current_segment_cell_vector_data.end(); ++data_it)
                writeCellData( seg, writer, data_it->first, *(data_it->second), seg.id() );

              writer << "   </CellData>" << std::endl;
            }

            writer << "  </Piece>" << std::endl;
            writeFooter(writer);
            writer.close();
          }

        clear();
      }



  private:


    template<typename MapType, typename AccessorOrFieldType, typename AccessType>
    void add_to_container(MapType & map, AccessorOrFieldType const accessor_or_field, std::string const & quantity_name)
    {
        typename MapType::iterator it = map.find(quantity_name);
        if (it != map.end())
        {
          delete it->second;
          it->second = new dynamic_field_wrapper<const AccessorOrFieldType, AccessType>( accessor_or_field );
        }
        else
          map[quantity_name] = new dynamic_field_wrapper<const AccessorOrFieldType, AccessType>( accessor_or_field );
    }

    template<typename MapType, typename AccessorOrFieldType>
    void add_to_vertex_container(MapType & map, AccessorOrFieldType const accessor_or_field, std::string const & quantity_name)
    {
      add_to_container<MapType, AccessorOrFieldType, VertexType>(map, accessor_or_field, quantity_name);
    }

    template<typename MapType, typename AccessorOrFieldType>
    void add_to_cell_container(MapType & map, AccessorOrFieldType const accessor_or_field, std::string const & quantity_name)
    {
      add_to_container<MapType, AccessorOrFieldType, CellType>(map, accessor_or_field, quantity_name);
    }

  public:


      /** @brief Register an accessor/field for scalar data on vertices with a given quantity name */
      template <typename AccessorOrFieldType>
      void add_scalar_data_on_vertices(AccessorOrFieldType const accessor_or_field, std::string const & quantity_name)
      { add_to_vertex_container(vertex_scalar_data, accessor_or_field, quantity_name); }

      /** @brief Register an accessor/field for scalar data on vertices for a given segment ID with a given quantity name */
      template <typename AccessorOrFieldType>
      void add_scalar_data_on_vertices(segment_id_type seg_id, AccessorOrFieldType const accessor_or_field, std::string const & quantity_name)
      { add_to_vertex_container(segment_vertex_scalar_data[seg_id], accessor_or_field, quantity_name); }

      /** @brief Register an accessor/field for scalar data on vertices for a given segment with a given quantity name */
      template <typename AccessorOrFieldType>
      void add_scalar_data_on_vertices(SegmentHandleType const & segment, AccessorOrFieldType const accessor_or_field, std::string const & quantity_name)
      { add_scalar_data_on_vertices(segment.id(), accessor_or_field, quantity_name); }


      /** @brief Register an accessor/field for vector data on vertices with a given quantity name */
      template <typename AccessorOrFieldType>
      void add_vector_data_on_vertices(AccessorOrFieldType const accessor_or_field, std::string const & quantity_name)
      { add_to_vertex_container(vertex_vector_data, accessor_or_field, quantity_name); }

      /** @brief Register an accessor/field for vector data on vertices for a given segment ID with a given quantity name */
      template <typename AccessorOrFieldType>
      void add_vector_data_on_vertices(segment_id_type seg_id, AccessorOrFieldType const accessor_or_field, std::string const & quantity_name)
      { add_to_vertex_container(segment_vertex_vector_data[seg_id], accessor_or_field, quantity_name); }

      /** @brief Register an accessor/field for vector data on vertices for a given segment with a given quantity name */
      template <typename AccessorOrFieldType>
      void add_vector_data_on_vertices(SegmentHandleType const & segment, AccessorOrFieldType const accessor_or_field, std::string const & quantity_name)
      { add_vector_data_on_vertices(segment.id(), accessor_or_field, quantity_name); }



      /** @brief Register an accessor/field for scalar data on cells with a given quantity name */
      template <typename AccessorOrFieldType>
      void add_scalar_data_on_cells(AccessorOrFieldType const accessor_or_field, std::string const & quantity_name)
      { add_to_cell_container(cell_scalar_data, accessor_or_field, quantity_name); }

      /** @brief Register an accessor/field for scalar data on cells for a given segment ID with a given quantity name */
      template <typename AccessorOrFieldType>
      void add_scalar_data_on_cells(segment_id_type seg_id, AccessorOrFieldType const accessor_or_field, std::string const & quantity_name)
      { add_to_cell_container(segment_cell_scalar_data[seg_id], accessor_or_field, quantity_name); }

      /** @brief Register an accessor/field for scalar data on cells for a given segment with a given quantity name */
      template <typename AccessorOrFieldType>
      void add_scalar_data_on_cells(SegmentHandleType const & segment, AccessorOrFieldType const accessor_or_field, std::string const & quantity_name)
      { add_scalar_data_on_cells(segment.id(), accessor_or_field, quantity_name); }


      /** @brief Register an accessor/field for vector data on cells with a given quantity name */
      template <typename AccessorOrFieldType>
      void add_vector_data_on_cells(AccessorOrFieldType const accessor_or_field, std::string const & quantity_name)
      { add_to_cell_container(cell_vector_data, accessor_or_field, quantity_name); }

      /** @brief Register an accessor/field for vector data on cells for a given segment ID with a given quantity name */
      template <typename AccessorOrFieldType>
      void add_vector_data_on_cells(segment_id_type seg_id, AccessorOrFieldType const accessor_or_field, std::string const & quantity_name)
      { add_to_cell_container(segment_cell_vector_data[seg_id], accessor_or_field, quantity_name); }

      /** @brief Register an accessor/field for vector data on cells for a given segment with a given quantity name */
      template <typename AccessorOrFieldType>
      void add_vector_data_on_cells(SegmentHandleType const & segment, AccessorOrFieldType const accessor_or_field, std::string const & quantity_name)
      { add_vector_data_on_cells(segment.id(), accessor_or_field, quantity_name); }


    private:

      std::map< segment_id_type, std::map< ConstVertexHandleType, VertexIDType> >             vertex_to_index_map;
      std::map< segment_id_type, std::map< VertexIDType, ConstVertexHandleType> >             used_vertex_map;
      std::map< segment_id_type, std::map< CellIDType, ConstCellHandleType> >                 used_cell_map;


      VertexScalarOutputAccessorContainer          vertex_scalar_data;
      VertexVectorOutputAccessorContainer          vertex_vector_data;

      CellScalarOutputAccessorContainer          cell_scalar_data;
      CellVectorOutputAccessorContainer          cell_vector_data;

      std::map< segment_id_type, VertexScalarOutputAccessorContainer > segment_vertex_scalar_data;
      std::map< segment_id_type, VertexVectorOutputAccessorContainer > segment_vertex_vector_data;

      std::map< segment_id_type, CellScalarOutputAccessorContainer >   segment_cell_scalar_data;
      std::map< segment_id_type, CellVectorOutputAccessorContainer >   segment_cell_vector_data;
    };

    /** @brief Convenience function that exports a mesh to file directly. Does not export quantities */
    template < typename MeshType, typename SegmentationType >
    int export_vtk(MeshType const & mesh_obj, SegmentationType const & segmentation, std::string const & filename)
    {
      vtk_writer<MeshType> vtk_writer;
      return vtk_writer(mesh_obj, segmentation, filename);
    }

    /** @brief Convenience function that exports a mesh to file directly. Does not export quantities */
    template < typename MeshType >
    int export_vtk(MeshType const & mesh_obj, std::string const & filename)
    {
      vtk_writer<MeshType> vtk_writer;
      return vtk_writer(mesh_obj, filename);
    }


    /** @brief Registers scalar-valued data on vertices at the VTK writer. At most one data set is allowed.
      *
      * @tparam MeshT             The mesh type to be written
      * @tparam SegmentationT       The segmentation type to be written
      * @tparam AccessorOrFieldT    An accessor/field type holding scalar data
      * @param  writer              The VTK writer object for which the data should be registered
      * @param  accessor_or_field   The accessor/field object holding scalar data on vertices
      * @param  quantity_name       The quantity name within the VTK file
      */
    template <typename MeshT, typename SegmentationT, typename AccessorOrFieldT>
    vtk_writer<MeshT, SegmentationT> & add_scalar_data_on_vertices(vtk_writer<MeshT, SegmentationT> & writer,
                                                                    AccessorOrFieldT const accessor_or_field,
                                                                    std::string const & quantity_name)
    {
      writer.add_scalar_data_on_vertices(accessor_or_field, quantity_name);
      return writer;
    }

    /** @brief Registers vector-valued data on vertices at the VTK writer. At most one data set is allowed.
      *
      * @tparam MeshT             The mesh type to be written
      * @tparam SegmentationT       The segmentation type to be written
      * @tparam AccessorOrFieldT    An accessor/field type holding vector data
      * @param  writer              The VTK writer object for which the data should be registered
      * @param  accessor_or_field   The accessor/field object holding vector data on vertices
      * @param  quantity_name       The quantity name within the VTK file
      */
    template <typename MeshT, typename SegmentationT, typename AccessorOrFieldT>
    vtk_writer<MeshT, SegmentationT> & add_vector_data_on_vertices(vtk_writer<MeshT, SegmentationT> & writer,
                                                                    AccessorOrFieldT const accessor_or_field,
                                                                    std::string const & quantity_name)
    {
      writer.add_vector_data_on_vertices(accessor_or_field, quantity_name);
      return writer;
    }

    /** @brief Registers scalar-valued data on vertices for a given segment at the VTK writer. At most one data set is allowed.
      *
      * @tparam MeshT             The mesh type to be written
      * @tparam SegmentationT       The segmentation type to be written
      * @tparam AccessorOrFieldT    An accessor/field type holding scalar data
      * @param  writer              The VTK writer object for which the data should be registered
      * @param  segment             The segment for which the data is defined
      * @param  accessor_or_field   The accessor/field object holding scalar data on vertices
      * @param  quantity_name       The quantity name within the VTK file
      */
    template <typename MeshT, typename SegmentationT, typename AccessorOrFieldT>
    vtk_writer<MeshT, SegmentationT> & add_scalar_data_on_vertices(vtk_writer<MeshT, SegmentationT> & writer,
                                                                    segment_handle<SegmentationT> const & segment,
                                                                    AccessorOrFieldT const accessor_or_field,
                                                                    std::string const & quantity_name)
    {
      writer.add_scalar_data_on_vertices(segment, accessor_or_field, quantity_name);
      return writer;
    }

    /** @brief Registers vector-valued data on vertices for a given segment at the VTK writer. At most one data set is allowed.
      *
      * @tparam MeshT             The mesh type to be written
      * @tparam SegmentationT       The segmentation type to be written
      * @tparam AccessorOrFieldT    An accessor/field type holding vector data
      * @param  writer              The VTK writer object for which the data should be registered
      * @param  segment             The segment for which the data is defined
      * @param  accessor_or_field   The accessor/field object holding vector data on vertices
      * @param  quantity_name       The quantity name within the VTK file
      */
    template <typename MeshT, typename SegmentationT, typename AccessorOrFieldT>
    vtk_writer<MeshT, SegmentationT> & add_vector_data_on_vertices(vtk_writer<MeshT, SegmentationT> & writer,
                                                                    segment_handle<SegmentationT> const & segment,
                                                                    AccessorOrFieldT const accessor_or_field,
                                                                    std::string const & quantity_name)
    {
      writer.add_vector_data_on_vertices(segment, accessor_or_field, quantity_name);
      return writer;
    }





    /** @brief Registers scalar-valued data on cells at the VTK writer. At most one data set is allowed.
      *
      * @tparam MeshT             The mesh type to be written
      * @tparam SegmentationT       The segmentation type to be written
      * @tparam AccessorOrFieldT    An accessor/field type holding scalar data
      * @param  writer              The VTK writer object for which the data should be registered
      * @param  accessor_or_field   The accessor/field object holding scalar data on cells
      * @param  quantity_name       The quantity name within the VTK file
      */
    template <typename MeshT, typename SegmentationT, typename AccessorOrFieldT>
    vtk_writer<MeshT, SegmentationT> & add_scalar_data_on_cells(vtk_writer<MeshT, SegmentationT> & writer,
                                                                    AccessorOrFieldT const accessor_or_field,
                                                                    std::string const & quantity_name)
    {
      writer.add_scalar_data_on_cells(accessor_or_field, quantity_name);
      return writer;
    }

    /** @brief Registers vector-valued data on cells at the VTK writer. At most one data set is allowed.
      *
      * @tparam MeshT             The mesh type to be written
      * @tparam SegmentationT       The segmentation type to be written
      * @tparam AccessorOrFieldT    An accessor/field type holding vector data
      * @param  writer              The VTK writer object for which the data should be registered
      * @param  accessor_or_field   The accessor/field object holding vector data on cells
      * @param  quantity_name       The quantity name within the VTK file
      */
    template <typename MeshT, typename SegmentationT, typename AccessorOrFieldT>
    vtk_writer<MeshT, SegmentationT> & add_vector_data_on_cells(vtk_writer<MeshT, SegmentationT> & writer,
                                                                    AccessorOrFieldT const accessor_or_field,
                                                                    std::string const & quantity_name)
    {
      writer.add_vector_data_on_cells(accessor_or_field, quantity_name);
      return writer;
    }

    /** @brief Registers scalar-valued data on cells for a given segment at the VTK writer. At most one data set is allowed.
      *
      * @tparam MeshT             The mesh type to be written
      * @tparam SegmentationT       The segmentation type to be written
      * @tparam AccessorOrFieldT    An accessor/field type holding scalar data
      * @param  writer              The VTK writer object for which the data should be registered
      * @param  segment             The segment for which the data is defined
      * @param  accessor_or_field   The accessor/field object holding scalar data on cells
      * @param  quantity_name       The quantity name within the VTK file
      */
    template <typename MeshT, typename SegmentationT, typename AccessorOrFieldT>
    vtk_writer<MeshT, SegmentationT> & add_scalar_data_on_cells(vtk_writer<MeshT, SegmentationT> & writer,
                                                                  segment_handle<SegmentationT> const & segment,
                                                                  AccessorOrFieldT const accessor_or_field,
                                                                  std::string const & quantity_name)
    {
      writer.add_scalar_data_on_cells(segment, accessor_or_field, quantity_name);
      return writer;
    }

    /** @brief Registers vector-valued data on cells for a given segment at the VTK writer. At most one data set is allowed.
      *
      * @tparam MeshT             The mesh type to be written
      * @tparam SegmentationT       The segmentation type to be written
      * @tparam AccessorOrFieldT    An accessor/field type holding vector data
      * @param  writer              The VTK writer object for which the data should be registered
      * @param  segment             The segment for which the data is defined
      * @param  accessor_or_field   The accessor/field object holding vector data on cells
      * @param  quantity_name       The quantity name within the VTK file
      */
    template <typename MeshT, typename SegmentationT, typename AccessorOrFieldT>
    vtk_writer<MeshT, SegmentationT> & add_vector_data_on_cells(vtk_writer<MeshT, SegmentationT> & writer,
                                                                  segment_handle<SegmentationT> const & segment,
                                                                  AccessorOrFieldT const accessor_or_field,
                                                                  std::string const & quantity_name)
    {
      writer.add_vector_data_on_cells(segment, accessor_or_field, quantity_name);
      return writer;
    }


  } //namespace io
} //namespace viennagrid

#endif
