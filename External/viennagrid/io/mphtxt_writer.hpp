#ifndef VIENNAGRID_MPHTXT_WRITER_HPP
#define VIENNAGRID_MPHTXT_WRITER_HPP

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
#include <fstream>

#include "viennagrid/algorithm/centroid.hpp"
#include "viennagrid/algorithm/boundary.hpp"
#include "viennagrid/algorithm/geometry.hpp"

#include "viennagrid/mesh/coboundary_iteration.hpp"
#include "viennagrid/mesh/neighbor_iteration.hpp"

/** @file viennagrid/io/mphtxt_writer.hpp
    @brief Provides a writer for Comsol .mphtxt files.
*/



namespace viennagrid
{
  namespace io
  {

    template<typename TriangleHandleT>
    struct triangle_information
    {
      triangle_information(TriangleHandleT const & handle_) : handle(handle_), up_index(0), down_index(0), contact_index(-1), segment_index(-1) {}

      TriangleHandleT handle;

      int up_index;
      int down_index;

      int contact_index;
      int segment_index;
    };









    template<typename SegmentHandleT, typename AccessorType, typename TriangleHandleT, typename SegmentIDRangeType>
    void mark_planar_neighbors( SegmentHandleT const & segment, AccessorType & contact_index_accessor,
                                TriangleHandleT const & triangle_handle, int contact_index,
                                SegmentIDRangeType const & sids )
    {
      typedef typename viennagrid::result_of::point<SegmentHandleT>::type PointType;
      typedef typename viennagrid::result_of::coord<SegmentHandleT>::type NumericType;
      typedef typename viennagrid::result_of::triangle<SegmentHandleT>::type TriangleType;
      PointType normal = viennagrid::normal_vector( viennagrid::dereference_handle(segment, triangle_handle) );

      typedef typename viennagrid::result_of::const_neighbor_range<SegmentHandleT, viennagrid::triangle_tag, viennagrid::vertex_tag>::type NeigborTriangleRangeType;
      typedef typename viennagrid::result_of::iterator<NeigborTriangleRangeType>::type NeigborTriangleIteratorType;

      NeigborTriangleRangeType neighbor_triangles( segment, triangle_handle );
      for (NeigborTriangleIteratorType ntit = neighbor_triangles.begin(); ntit != neighbor_triangles.end(); ++ntit )
      {
        if (contact_index_accessor(*ntit) != -1)
          continue;

        if (!viennagrid::is_boundary(segment, *ntit))
          continue;

        if (!sids.is_equal(viennagrid::segment_ids(segment.parent(), *ntit)))
          continue;

        PointType neighbor_normal = viennagrid::normal_vector(*ntit);

        NumericType dot = viennagrid::inner_prod( normal, neighbor_normal );

        if ( std::abs(dot) > (1.0-1e-6) * viennagrid::norm_2(normal) * viennagrid::norm_2(neighbor_normal) )
        {
          contact_index_accessor(*ntit) = contact_index;
          mark_planar_neighbors( segment, contact_index_accessor, ntit.handle(), contact_index, sids );
        }
      }
    }




    template<typename SegmentationT, typename AccessorType>
    void mark_segment_hull_contacts( SegmentationT const & segmentation, AccessorType & contact_index_accessor )
    {
      typedef typename viennagrid::result_of::segment_handle<SegmentationT>::type SegmentHandleType;
      typedef typename viennagrid::result_of::const_triangle_range<SegmentationT>::type ConstTriangleRangeType;
      typedef typename viennagrid::result_of::iterator<ConstTriangleRangeType>::type ConstTriangleIteratorType;

      ConstTriangleRangeType triangles(segmentation);
      for (ConstTriangleIteratorType tit = triangles.begin(); tit != triangles.end(); ++tit)
        contact_index_accessor(*tit) = -1;


      int current_contact_index = 0;
      for (typename SegmentationT::const_iterator sit = segmentation.begin(); sit != segmentation.end(); ++sit)
      {
        typedef typename viennagrid::result_of::const_triangle_range<SegmentHandleType>::type ConstTriangleOnSegmentRangeType;
        typedef typename viennagrid::result_of::iterator<ConstTriangleOnSegmentRangeType>::type ConstTriangleOnSegmentIteratorType;

        SegmentHandleType const & segment = *sit;

        ConstTriangleOnSegmentRangeType triangles_on_segment(segment);
        for (ConstTriangleOnSegmentIteratorType tsit = triangles_on_segment.begin(); tsit != triangles_on_segment.end(); ++tsit)
        {
          if ( viennagrid::is_boundary(segment, *tsit) && (contact_index_accessor(*tsit) == -1) )
          {
            contact_index_accessor(*tsit) = current_contact_index;

            typedef typename viennagrid::result_of::triangle<SegmentationT>::type TriangleType;
            typedef typename viennagrid::result_of::segment_id_range<SegmentationT, TriangleType>::type SegmentIDRangeType;

            SegmentIDRangeType sids = viennagrid::segment_ids(segmentation, *tsit);

            mark_planar_neighbors(segment, contact_index_accessor, tsit.handle(),
                                  current_contact_index, sids);

            ++current_contact_index;
          }
        }
      }

//       std::cout << "Number of contacts: " << current_contact_index << std::endl;
    }



    /** @brief Writer for Comsol .mphtxt files.
      *
      * See http://chemelab.ucsd.edu/CAPE/comsol/Comsol_Reference.pdf, page 396-441 for a description of the file format
      */
    class mphtxt_writer
    {
    public:

      /** @brief The functor interface triggering the read operation. Segmentations are not supported in this version.
       *
       * @param mesh            The mesh which is to be written
       * @param segmentation    The segmentation which is to be written
       * @param filename        Name of the file
       */
      template <typename MeshT, typename SegmentationT>
      void operator()(MeshT const & mesh, SegmentationT const & segmentation, std::string const & filename) const
      {
        typedef typename viennagrid::result_of::point<MeshT>::type PointType;
        typedef typename viennagrid::result_of::vertex_id<MeshT>::type VertexIDType;
        typedef typename viennagrid::result_of::triangle_id<MeshT>::type TriangleIDType;

        typedef typename viennagrid::result_of::triangle<MeshT>::type TriangleType;


        typedef typename viennagrid::result_of::const_vertex_range<MeshT>::type ConstVertexRangeType;
        typedef typename viennagrid::result_of::iterator<ConstVertexRangeType>::type ConstVertexIteratorType;

        typedef typename viennagrid::result_of::const_triangle_range<MeshT>::type ConstTriangleRangeType;
        typedef typename viennagrid::result_of::iterator<ConstTriangleRangeType>::type ConstTriangleIteratorType;

        typedef typename viennagrid::result_of::const_tetrahedron_range<MeshT>::type ConstTetrahedronRangeType;
        typedef typename viennagrid::result_of::iterator<ConstTetrahedronRangeType>::type ConstTetrahedronIteratorType;



        std::stringstream ss;
        if(filename.substr( filename.rfind(".")+1 ) == "mphtxt")
          ss << filename;
        else
          ss << filename << ".mphtxt";
        std::ofstream writer(ss.str().c_str());

        writer << "# Created by ViennaGrid mphtxt writer\n";
        writer << "\n";

        writer << "# Major & minor version\n";
        writer << "0 1\n";
        writer << "1 # number of tags\n";
        writer << "# Tags\n";
        writer << "15 viennagrid_mesh\n";
        writer << "1 # number of types\n";
        writer << "# Types\n";
        writer << "3 obj\n";

        writer << "\n";
        writer << "# --------- Object 0 ----------\n";
        writer << "\n";

        writer << "0 0 1\n";
        writer << "4 Mesh # class\n";
        writer << "2 # version\n";
        writer << viennagrid::result_of::geometric_dimension<MeshT>::value << " # sdim\n";
        writer << viennagrid::vertices(mesh).size() << " # number of mesh points\n";
        writer << "0 # lowest mesh point index\n";
        writer << "\n";

        writer << "# Mesh point coordinates\n";
        ConstVertexRangeType vertices(mesh);
        std::map<VertexIDType, int> vertex_index_map;

        std::size_t vertex_index = 0;
        for (ConstVertexIteratorType vit = vertices.begin(); vit != vertices.end(); ++vit, ++vertex_index)
        {
          vertex_index_map[ vit->id() ] = vertex_index;

          writer.precision( std::numeric_limits<typename PointType::value_type>::digits10 );
          PointType const & point = viennagrid::point(*vit);
          for (std::size_t i = 0; i < point.size(); ++i)
            writer << point[i] << " ";
          writer << "\n";
        }
        writer << "\n";

        writer << "\n";
        writer << "2 # number of element types\n";


        writer << "\n";
        writer << "3 tri\n";
        writer << "3 # nodes per element\n";
        writer << "\n";

        ConstTriangleRangeType triangles(mesh);

        typedef typename viennagrid::result_of::const_triangle_handle<MeshT>::type ConstTriangleHandleType;
        typedef triangle_information<ConstTriangleHandleType> TriInfoType;

        std::map<TriangleIDType, TriInfoType> used_triangles;
        typedef typename viennagrid::result_of::segment_handle<SegmentationT>::type SegmentHandleType;

        for (typename SegmentationT::const_iterator sit = segmentation.begin(); sit != segmentation.end(); ++sit)
        {
          typedef typename viennagrid::result_of::const_triangle_range<SegmentHandleType>::type TriangleOnSegmentRangeType;
          typedef typename viennagrid::result_of::iterator<TriangleOnSegmentRangeType>::type TriangleOnSegmentIteratorType;

          TriangleOnSegmentRangeType triangles(*sit);
          for (TriangleOnSegmentIteratorType tit = triangles.begin(); tit != triangles.end(); ++tit)
          {
            if ( viennagrid::is_boundary(*sit, *tit) )
            {
              typename std::map<TriangleIDType, TriInfoType>::iterator utit = used_triangles.find( tit->id() );
              if (utit == used_triangles.end())
                utit = used_triangles.insert( std::make_pair(tit->id(), TriInfoType(tit.handle())) ).first;

              PointType triangle_normal = viennagrid::normal_vector(*tit);
              PointType triangle_center = viennagrid::centroid(*tit);

              typedef typename viennagrid::result_of::const_coboundary_range<SegmentHandleType, viennagrid::triangle_tag, viennagrid::tetrahedron_tag>::type CoboundaryTetrahedronRangeType;
              typedef typename viennagrid::result_of::iterator<CoboundaryTetrahedronRangeType>::type CoboundaryTetrahedronIteratorType;

              CoboundaryTetrahedronRangeType coboundary_tetrahedrons(*sit, tit.handle());
              if (coboundary_tetrahedrons.size() != 1)
              {
                std::cout << "FEHLER!!! there is more than one on co-boundary tetrahedron" << std::endl;
              }

              PointType tetrahedron_center = viennagrid::centroid( coboundary_tetrahedrons[0] );

              bool orientation = viennagrid::inner_prod( triangle_center-tetrahedron_center, triangle_normal ) > 0;

              if (orientation)
              {
                if (utit->second.up_index != 0)
                {
                  std::cout << "FEHLER!!!" << std::endl;
                }

                utit->second.up_index = sit->id()+1;
              }
              else
              {
                if (utit->second.down_index != 0)
                {
                  std::cout << "FEHLER!!!" << std::endl;
                }

                utit->second.down_index = sit->id()+1;
              }
            }
          }
        }


        std::vector<int> contact_index_array;
        typename viennagrid::result_of::field< std::vector<int>, TriangleType>::type contact_index_field(contact_index_array);

        mark_segment_hull_contacts( segmentation, contact_index_field );




//         writer << viennagrid::triangles(mesh).size() << " # number of triangles\n";
        writer << used_triangles.size() << " # number of triangles\n";
        writer << "\n";

        for (typename std::map<TriangleIDType, TriInfoType>::const_iterator utit = used_triangles.begin(); utit != used_triangles.end(); ++utit)
        {
          typedef typename viennagrid::result_of::triangle<MeshT>::type TriangleType;
          typedef typename viennagrid::result_of::const_vertex_range<TriangleType>::type VertexOnTriangleRangeType;
          typedef typename viennagrid::result_of::iterator<VertexOnTriangleRangeType>::type VertexOnTriangleIteratorType;

          VertexOnTriangleRangeType vertices_on_triangle( viennagrid::dereference_handle(mesh, utit->second.handle) );
          for (VertexOnTriangleIteratorType vtit = vertices_on_triangle.begin(); vtit != vertices_on_triangle.end(); ++vtit)
          {
            writer << vertex_index_map[ vtit->id() ] << " ";
          }
          writer << "\n";
        }

        writer << "\n";
        writer << "3\n";
        writer << "0\n";

        writer << used_triangles.size() << " # number of triangles\n";
        for (typename std::map<TriangleIDType, TriInfoType>::const_iterator utit = used_triangles.begin(); utit != used_triangles.end(); ++utit)
          writer << contact_index_field( viennagrid::dereference_handle(mesh, utit->second.handle) ) << "\n";

        writer << "\n";
        writer << used_triangles.size() << " # number of triangles\n";
        writer << "\n";
        for (typename std::map<TriangleIDType, TriInfoType>::const_iterator utit = used_triangles.begin(); utit != used_triangles.end(); ++utit)
          writer << utit->second.up_index << " " << utit->second.down_index << "\n";






        writer << "\n";
        writer << "3 tet\n";
        writer << "4 # nodes per element\n";
        writer << "\n";
        writer << viennagrid::tetrahedra(mesh).size() << " # number of tetrahedron\n";
        writer << "\n";

        ConstTetrahedronRangeType tetrahedrons(mesh);
        for (ConstTetrahedronIteratorType tit = tetrahedrons.begin(); tit != tetrahedrons.end(); ++tit)
        {
          typedef typename viennagrid::result_of::tetrahedron<MeshT>::type TetrahedronType;
          typedef typename viennagrid::result_of::const_vertex_range<TetrahedronType>::type VertexOnTetrahedronRangeType;
          typedef typename viennagrid::result_of::iterator<VertexOnTetrahedronRangeType>::type VertexOnTetrahedronIteratorType;

          VertexOnTetrahedronRangeType vertices_on_tetrahedron(*tit);
          for (VertexOnTetrahedronIteratorType vtit = vertices_on_tetrahedron.begin(); vtit != vertices_on_tetrahedron.end(); ++vtit)
          {
            writer << vertex_index_map[ vtit->id() ] << " ";
          }
          writer << "\n";
        }

        writer << "\n";
        writer << "4\n";
        writer << "0\n";
//         writer << viennagrid::tetrahedra(mesh).size() << " # number of tetrahedron\n";
        writer << "\n";
        writer << viennagrid::tetrahedra(mesh).size() << " # number of tetrahedron\n";

//         ConstTetrahedronRangeType tetrahedrons(mesh);
        for (ConstTetrahedronIteratorType tit = tetrahedrons.begin(); tit != tetrahedrons.end(); ++tit)
        {
          typedef typename viennagrid::result_of::tetrahedron<MeshT>::type TetrahedronType;
          typedef typename viennagrid::result_of::const_vertex_range<TetrahedronType>::type VertexOnTetrahedronRangeType;
          typedef typename viennagrid::result_of::iterator<VertexOnTetrahedronRangeType>::type VertexOnTetrahedronIteratorType;

          typedef typename viennagrid::result_of::segment_id_range<SegmentationT, TetrahedronType>::type SegmentIDRange;

          SegmentIDRange segment_ids = viennagrid::segment_ids( segmentation, *tit );
          writer << *(segment_ids.begin())+1 << "\n";
        }

        writer << "\n";
        writer << "0\n";
      }



    private:

    };



  }
}



#endif
