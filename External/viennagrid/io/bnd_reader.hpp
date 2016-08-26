#ifndef VIENNAGRID_BND_READER_HPP
#define VIENNAGRID_BND_READER_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include "viennagrid/io/helper.hpp"
// #include "viennagrid/io/bnd.hpp"
#include "viennagrid/mesh/element_creation.hpp"

/** @file viennagrid/io/bnd_reader.hpp
    @brief Provides a reader for .bnd files.
*/


namespace viennagrid
{
  namespace io
  {
    /*
    INFORMATION ON THE BND FILE FORMAT:

    --## tested with the generated bnd files of the Synopsis Structure Editor E-2010.12 ##--

    ELEMENT TYPES:
    type 10: polyhedron used in 3d bnd files for the segment description
      syntax: 10 number_of_faces face-index0 face-index1 ... face-index-n

    type 4: polygon used in 2d bnd files for the segment description
      syntax: 4 number_of_faces face-index0 face-index1 ... face-index-n

    type 2: triangle informally also known as 'direct' or 'contact' triangle, used in 3d bnd files
      syntax: 2 edge-index0 edge-index1 edge-index2

    type 1: line informally also known as 'direct' or 'contact' line, used in 2d bnd files
      syntax: 1 vertex-index0 vertex-index1

    CONTACTS:
    in 3d, only faces can be contacts. although the synopsis structure editor
    allows to declare an edge to be a contact, it is not exported to the bnd file.
    a 3d-contact is defined by a type '2' element, which refers to _three_ edges,
    and they again to the points. which makes sense, because the 2d polygon,
    which can be a face in 3d, is a triangle (that's why it's called a simplex, btw ..)
    so, for example, a quardilateral contact consists therefore of two type '2' elements.

    in 2d, respectively, only edges can be contacts.
    a 2d-contact is defined by a type '1' element, which refers to two points, hence an edge
    */

    struct print
    {
      template<typename T1, std::size_t Size>
      void operator()(viennagrid::static_array<T1, Size> const& vec, std::ostream& ostr = std::cout)
      {
          for(typename viennagrid::static_array<T1, Size>::const_iterator iter = vec.begin();
              iter != vec.end(); iter++)
          {
            ostr << *iter << "  ";
          }
          std::cout << std::endl;
      }

      template<typename T1, std::size_t Size>
      void operator()(viennagrid::static_array<T1, Size> & vec, std::ostream& ostr = std::cout)
      {
          for(typename viennagrid::static_array<T1, Size>::iterator iter = vec.begin();
              iter != vec.end(); iter++)
          {
            ostr << *iter << "  ";
          }
          std::cout << std::endl;
      }

      template<typename T1>
      void operator()(std::vector<T1> const& vec, std::ostream& ostr = std::cout)
      {
          for(typename std::vector<T1>::const_iterator iter = vec.begin();
              iter != vec.end(); iter++)
          {
            ostr << *iter << "  ";
          }
          std::cout << std::endl;
      }

      template<typename T1>
      void operator()(std::vector<T1> & vec, std::ostream& ostr = std::cout)
      {
          for(typename std::vector<T1>::iterator iter = vec.begin();
              iter != vec.end(); iter++)
          {
            ostr << *iter << "  ";
          }
          std::cout << std::endl;
      }

      template<typename T0, typename T1>
      void operator()(std::map<T0, T1> const& vec, std::ostream& ostr = std::cout)
      {
          for(typename std::map<T0, T1>::const_iterator iter = vec.begin();
              iter != vec.end(); iter++)
          {
            ostr << iter->first << " - " << iter->second << std::endl;
          }
      }

      template<typename T0, typename T1>
      void operator()(std::map<T0, T1> & vec, std::ostream& ostr = std::cout)
      {
          for(typename std::map<T0, T1>::iterator iter = vec.begin();
              iter != vec.end(); iter++)
          {
            ostr << iter->first << " - " << iter->second << std::endl;
          }
      }
    };

    struct boolalpha_bool;

    namespace detail
    {
      template<typename DestinationT>
      struct lexical_cast_impl
      {
      public:
        typedef DestinationT result_type;

        template<typename SourceT>
        lexical_cast_impl(SourceT const & src)
        {
          ss << src;
        }

        operator result_type()
        {
          result_type tmp;
          ss >> tmp;
          return tmp;
        }

      private:
        std::stringstream ss;
      };

      template<>
      struct lexical_cast_impl<boolalpha_bool>
      {
      public:
        typedef bool result_type;

        template<typename SourceT>
        lexical_cast_impl(SourceT const & src)
        {
          ss << std::boolalpha << src;
        }

        operator result_type()
        {
          result_type tmp;
          ss >> std::boolalpha >> tmp;
          return tmp;
        }

      private:
        std::stringstream ss;
      };
    }

    template<typename DestinationT, typename SourceT>
    typename detail::lexical_cast_impl<DestinationT>::result_type lexical_cast( SourceT const & src )
    {
      return detail::lexical_cast_impl<DestinationT>(src);
    }


    inline std::string remove_begin_end_chars( std::string const & str )
    {
      std::string::size_type start = 0;
      for (; start != str.size(); ++start)
      {
        char const & cur = str[start];
        if ((cur != ' ') && (cur != '\n') && (cur != '\t'))
            break;
      }

      std::string::size_type end = str.size()-1;
      for (; end != std::size_t(-1); --end)
      {
        char const & cur = str[end];
        if ((cur != ' ') && (cur != '\n') && (cur != '\t'))
            break;
      }

      return str.substr( start, end-start+1 );
    }




    struct bnd_helper
    {

      typedef double                            numeric_type;
      //typedef viennagrid::static_array<numeric_type, DIMG>  point_type;
      typedef std::vector<numeric_type>         point_type;
      typedef std::vector<point_type>           geometry_container_type;

      typedef long                              index_type;

      typedef std::vector< index_type >         edge_type;
      typedef std::vector<edge_type>            edge_container_type;


      typedef std::vector< index_type >         polygon_type;
      typedef std::vector< polygon_type >       polygon_container_type;

      // a contact can be a line (2d) or a triangle (3d)
      typedef std::vector< index_type >         contact_face_type;
      typedef std::vector< contact_face_type >  contact_face_container_type;
      typedef std::vector< contact_face_container_type > contact_groups_type;

      // segment name, material container
      typedef std::vector<std::pair<std::string, std::string> >          segment_id_container_type;

      // contact name container
      typedef std::vector<std::string>          contact_id_container_type;

      // a domain-segment is a set of polygons
      //
      typedef std::vector<polygon_container_type>   domain_type;


      int operator()(std::string const & filename)
      {
        std::ifstream reader(filename.c_str());

        if (!reader){
          std::cerr << "Cannot open file " << filename << std::endl;
          throw cannot_open_file_exception("* ViennaGrid: bnd_helper::operator(): File " + filename + ": Cannot open file!");
        }

        try{

          std::string token;

        #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "reading geometry dimension .. " << std::endl;
        #endif
          int DIMG;
          while(1)
          {
            reader >> token;
            if(token == "dimension")
            {
               reader >> token;
               reader >> DIMG;
               break;
            }
          }
        #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "geometry dimension: " << DIMG << std::endl;
        #endif
          dim_geometry = DIMG;

        #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "reading region information .. " << std::endl;
        #endif
          while(1)
          {
            reader >> token;
            if(token == "nb_regions")
            {
               reader >> token;
               reader >> number_of_regions;
               break;
            }
          }
        #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "number of regions: " << number_of_regions << std::endl;
        #endif



          std::size_t vertices = 0;

        #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "reading geometry information .. " << std::endl;
        #endif

          while(1)
          {
            std::getline(reader, token);

            if(token.find("Vertices") != std::string::npos)
            {
              std::string::size_type delimiter_left = token.find("(")+1;
              std::string::size_type delimiter_right = token.find(")");
              std::string vertices_str = token.substr(delimiter_left, delimiter_right-delimiter_left);
              vertices = lexical_cast<std::size_t>(vertices_str);
              break;
            }
          }

        #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "vertices: " << vertices << std::endl;
        #endif

          geometry.resize(vertices);

          point_type coords(DIMG);

          for(std::size_t vi = 0; vi < vertices; vi++)
          {
            for (int j=0; j < DIMG; j++)
            {
              reader >> coords[j];
            }
            geometry[vi] = coords;
          }

        #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "  finished loading point vectors .. " <<  std::endl;
        #endif

        #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "reading topology information .. " << std::endl;
        #endif


        #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "reading edge information .. " << std::endl;
        #endif

          std::size_t edges = 0;

          while(1)
          {
            std::getline(reader, token);

            if(token.find("Edges") != std::string::npos)
            {
              std::string::size_type delimiter_left = token.find("(")+1;
              std::string::size_type delimiter_right = token.find(")");
              std::string edges_str = token.substr(delimiter_left, delimiter_right-delimiter_left);
              edges = lexical_cast<std::size_t>(edges_str);
              break;
            }
          }

        #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "edges: " << edges << std::endl;
        #endif

          edge_cont.resize(edges);

          edge_type edge(2);
          for(std::size_t i = 0; i < edges; i++)
          {
            reader >> edge[0];
            reader >> edge[1];
            edge_cont[i] = edge;
          }

        #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "  finished loading edges .. " <<  std::endl;
        #endif

          if(DIMG == 3)
          {
             std::size_t faces = 0;

             while(1)
             {
               std::getline(reader, token);

               if(token.find("Faces") != std::string::npos)
               {
                 std::string::size_type delimiter_left = token.find("(")+1;
                 std::string::size_type delimiter_right = token.find(")");
                 std::string faces_str = token.substr(delimiter_left, delimiter_right-delimiter_left);
                 faces = lexical_cast<std::size_t>(faces_str);
                 break;
               }
             }

           #ifdef VIENNAGRID_DEBUG_IO
             std::cout << "faces: " << faces << std::endl;
           #endif

             polygon_cont.resize(faces);

             std::size_t face_dim = 0;

             for(std::size_t fi = 0; fi < faces; fi++)
             {
               reader >> face_dim; // number of vertices of this face

               //std::cout << "face dim: " << face_dim << std::endl;

               polygon_cont[fi].resize(face_dim);

               for (std::size_t j=0; j < face_dim; j++)
               {
                 reader >> polygon_cont[fi][j];
               }
             }

           #ifdef VIENNAGRID_DEBUG_IO
             std::cout << "  finished loading faces .. " <<  std::endl;
           #endif
        } // end DIMG == 3

        #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "reading segment information .. " << std::endl;
        #endif

          std::size_t elements = 0;

          while(1)
          {
            std::getline(reader, token);

            if(token.find("Elements") != std::string::npos)
            {
              std::string::size_type delimiter_left = token.find("(")+1;
              std::string::size_type delimiter_right = token.find(")");
              std::string elements_str = token.substr(delimiter_left, delimiter_right-delimiter_left);
              elements = lexical_cast<std::size_t>(elements_str);
              break;
            }
          }

        #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "elements: " << elements << std::endl;
        #endif

          domain.resize(elements);

          for(std::size_t i = 0; i < elements; i++)
          {
            reader >> token; // element type, ie, 10 ... polyhedron

            if(token == "10") // aka a 3d bnd file segment
            {
              std::size_t element_faces = 0;
              reader >> element_faces;

            #ifdef VIENNAGRID_DEBUG_IO
              std::cout << "  type: segment-polyhedron" << std::endl;
              std::cout << "  element: " << i << " - faces: " << element_faces << std::endl;
            #endif

              for(std::size_t f = 0; f < element_faces; f++)
              {
                index_type face;
                reader >> face;
                index_type mapped_face = map(face);

                polygon_type polygon = polygon_cont[mapped_face];

                polygon_type polygon_new;
                std::map<index_type, bool>  uniquer;

                for(std::size_t vi = 0; vi < polygon.size(); vi++)
                {
                  index_type vertex = polygon[vi];
                  index_type mapped_vertex = map(vertex);

                  edge_type edge = edge_cont[mapped_vertex];

                  if(vertex < 0) std::reverse(edge.begin(),edge.end());

                  if(!uniquer[edge[0]])
                  {
                    polygon_new.push_back(edge[0]);
                    uniquer[edge[0]] = true;
                  }
                  if(!uniquer[edge[1]])
                  {
                    polygon_new.push_back(edge[1]);
                    uniquer[edge[1]] = true;
                  }
                }
                //std::cout << "adapt: " << polygon_new;
                domain[i].push_back(polygon_new);
              }
            }
            else if(token == "4")  // aka a 2d bnd file segment
            {
              std::size_t element_faces = 0;
              reader >> element_faces;

            #ifdef VIENNAGRID_DEBUG_IO
              std::cout << "  type: segment-polygon" << std::endl;
              std::cout << "  element: " << i << " - linesegments: " << element_faces << std::endl;
            #endif

              for(std::size_t f = 0; f < element_faces; f++)
              {
                index_type face;
                reader >> face;
                index_type mapped_face = map(face);

                edge_type edge = edge_cont[mapped_face];

                //std::cout << "adapt: " << polygon_new;
                //std::cout << "adding edge: " << edge[0] << " " << edge[1] << std::endl;
                domain[i].push_back(edge);
              }

            }
            else if(token == "2") // aka a 3d bnd file contact
            {
//               reader >> token;
//               reader >> token;
//               reader >> token;
//               domain.resize(domain.size()-1);
            #ifdef VIENNAGRID_DEBUG_IO
              std::cout << "  type: contact-triangle" << std::endl;
            #endif
              contact_face_type contact_face(3);
              reader >> contact_face[0];
              reader >> contact_face[1];
              reader >> contact_face[2];
              //std::cout << contact_face[0] << " " << contact_face[1] << " " << contact_face[2] << std::endl;
              contact_face_cont.push_back(contact_face);

              // we have to reduce the domain size, as this is not a valid segment
              domain.resize(domain.size()-1);
            }
            else if(token == "1") // aka a 2d bnd file contact
            {
//               reader >> token;
//               reader >> token;
//               domain.resize(domain.size()-1);
            #ifdef VIENNAGRID_DEBUG_IO
              std::cout << "  type: contact-line" << std::endl;
            #endif
              contact_face_type contact_face(2);
              reader >> contact_face[0];
              reader >> contact_face[1];
              //std::cout << contact_face[0] << " " << contact_face[1] << std::endl;
              contact_face_cont.push_back(contact_face);

              // we have to reduce the domain size, as this is not a valid segment
              domain.resize(domain.size()-1);
            }
            else
            {
              std::cerr << "BND-READER-Error: Elements of type: " << token << " are not supported .." << std::endl;
              throw std::runtime_error("BND-READER-Error: Elements of type: " + token + " are not supported ..");
            }
          }

        #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "  finished loading elements .. " <<  std::endl;
        #endif

        #ifdef VIENNAGRID_DEBUG_IO
          std::cout << "reading material and contact information .. " << std::endl;
        #endif
          // the domainsize acts as an offset for the number of elements
          std::size_t domainsize = domain.size();
          segment_id_cont.resize(domainsize);
          std::size_t region_cnt = 0;

          contact_groups.resize(number_of_regions-domainsize);

          while(1)
          {
            std::getline(reader, token);

            if(token.find("Region") != std::string::npos)
            {

              region_cnt++;

              std::string::size_type delimiter_left = token.find("(\"")+2;
              std::string::size_type delimiter_right = token.find("\")");
              std::string name = token.substr(delimiter_left, delimiter_right-delimiter_left);
              name = remove_begin_end_chars(name);

              while(1)
              {
                std::getline(reader, token);

                if(token.find("material") != std::string::npos)
                {
                  std::string::size_type delimiter_left = token.find("=")+1;
                  std::string::size_type delimiter_right = token.find("\n");
                  std::string material = token.substr(delimiter_left, delimiter_right-delimiter_left);
                  material = remove_begin_end_chars(material);

                  //std::cout << "name: -" << name << "- material: -" << material << "-" << std::endl;

                 std::size_t elements = 0;
                  while(1)
                  {
                    std::getline(reader, token);

                    if(token.find("Elements") != std::string::npos)
                    {
                      std::string::size_type delimiter_left = token.find("(")+1;
                      std::string::size_type delimiter_right = token.find(")");
                      std::string elements_str = token.substr(delimiter_left, delimiter_right-delimiter_left);
                      elements = lexical_cast<std::size_t>(elements_str);
                      break;
                    }
                  }
                  std::size_t ei;
                  if( material == "Contact" )
                  {
                    // store the contact name
                    contact_id_cont.push_back(name);

                    for(std::size_t i = 0; i < elements; i++)
                    {
                      // read the elment id
                      reader >> ei;

                      // determine the contact cells
                      if(DIMG == 2)
                      {
                        contact_groups[contact_id_cont.size()-1].push_back(contact_face_cont[ei-domainsize]);
                      }
                      else // 3D
                      {
                        contact_face_type edge_index_cont = contact_face_cont[ei-domainsize];

                        std::map<index_type, bool>  uniquer;
                        contact_face_type contact_triangle;

                        for(std::size_t ei = 0; ei < edge_index_cont.size(); ei++)
                        {
                          index_type edge_index = edge_index_cont[ei];
                          index_type mapped_edge_index = map(edge_index);
                          edge_type edge = edge_cont[mapped_edge_index];
                          if(edge_index < 0) std::reverse(edge.begin(),edge.end());

                          if(!uniquer[edge[0]])
                          {
                            contact_triangle.push_back(edge[0]);
                            uniquer[edge[0]] = true;
                          }
                          if(!uniquer[edge[1]])
                          {
                            contact_triangle.push_back(edge[1]);
                            uniquer[edge[1]] = true;
                          }
                        }
                        //std::cout << contact_triangle << std::endl;
                        contact_groups[contact_id_cont.size()-1].push_back(contact_triangle);
                      }
                    }
                  }
                  else
                  {
                    for(std::size_t i = 0; i < elements; i++)
                    {
                      // read the elment id
                      reader >> ei;

                      // store the name and material info on the related segment id
                      segment_id_cont[ei] = std::pair<std::string, std::string>(name, material);
                    }
                  }
                  break;
                }
              }
            }
            if(region_cnt == number_of_regions) break;
          }

        } catch (...) {
          std::cerr << "Problems while reading file " << filename << std::endl;
        }

        return EXIT_SUCCESS;
      } //operator()

      struct negate
      {
        template<typename T>
        void operator()(T& x) { x*=-1; }
      };

      void dump(std::ostream& ostr = std::cout)
      {
        ostr << "## GEOMETRY" << std::endl;
        for(std::size_t gi = 0; gi < geometry.size(); gi++)
        {
          ostr << "  point - id: " << gi << " - data: ";
          viennagrid::io::print()(geometry[gi], ostr);
        }

        ostr << "## TOPOLOGY" << std::endl;
        for(std::size_t si = 0; si < domain.size(); si++)
        {
          ostr << "  segment: " << si << std::endl;
          for(std::size_t fi = 0; fi < domain[si].size(); fi++)
          {
            ostr << "    face - id: " << fi << " - size: " << domain[si][fi].size() << " - eles: ";
            viennagrid::io::print()(domain[si][fi], ostr);
          }
        }
      }

      point_type& point(std::size_t index)
      {
         return geometry[index];
      }

      std::size_t geometry_size()
      {
         return geometry.size();
      }

      std::size_t segment_size()
      {
         return domain.size();
      }

      polygon_container_type& segment(std::size_t index)
      {
         return domain[index];
      }

      std::size_t dim_geom()
      {
         return dim_geometry;
      }

      std::size_t contact_size()
      {
        return contact_id_cont.size();
      }

      std::string contact_name(std::size_t ci)
      {
        return contact_id_cont[ci];
      }

      contact_face_container_type contact_faces(std::size_t ci)
      {
        return contact_groups[ci];
      }

      std::string segment_name(std::size_t ci)
      {
        return segment_id_cont[ci].first;
      }

      std::string segment_material(std::size_t ci)
      {
        return segment_id_cont[ci].second;
      }


      void clear()
      {
         geometry.clear();
         edge_cont.clear();
         polygon_cont.clear();
         contact_face_cont.clear();
         contact_groups.clear();
         domain.clear();
         segment_id_cont.clear();
         contact_id_cont.clear();
      }

    private:
      index_type map(index_type index)
      {
        if(index >= 0) return index;
        else           return -(index)-1;  // this is the specific mapping for negativ face and element values
      }

      geometry_container_type       geometry;
      edge_container_type           edge_cont;
      polygon_container_type        polygon_cont;
      contact_face_container_type   contact_face_cont;
      contact_groups_type           contact_groups;
      domain_type                   domain;
      segment_id_container_type     segment_id_cont;
      contact_id_container_type     contact_id_cont;
      std::size_t                   dim_geometry;
      std::size_t                   number_of_regions;

    }; //class bnd_reader








    /** @brief Reader for .bnd files.
      *
      */
    class bnd_reader
    {
    public:

      /** @brief The functor interface triggering the read operation. Segmentations are not supported in this version.
       *
       * @param mesh              The mesh where the file content is written to
       * @param segmentation      The mesh where the file content is written to
       * @param filename          Name of the file
       */
      template <typename MeshT, typename SegmentationT>
      void operator()(MeshT & mesh, SegmentationT & segmentation, std::string const & filename) const
      {
        typedef typename viennagrid::result_of::point<MeshT>::type PointType;
        typedef typename viennagrid::result_of::vertex_handle<MeshT>::type VertexHandleType;
        typedef typename viennagrid::result_of::cell_handle<MeshT>::type CellHandleType;
        typedef typename viennagrid::result_of::segment_handle<SegmentationT>::type SegmentHandleType;

        const int mesh_dimension = viennagrid::result_of::geometric_dimension<MeshT>::value;
        const int num_vertices = viennagrid::boundary_elements<viennagrid::triangle_tag, viennagrid::vertex_tag>::num;

        typedef viennagrid::io::bnd_helper BNDReaderType;
        typedef BNDReaderType::index_type BNDIndexType;
        typedef BNDReaderType::point_type BNDPointType;
        typedef BNDReaderType::polygon_container_type BNDPolygonContainerType;
        typedef BNDReaderType::polygon_type BNDPolygonType;


        BNDReaderType bnd;
        if (bnd(filename) != EXIT_SUCCESS)
          throw bad_file_format_exception("* ViennaGrid: bnd_reader::operator(): File " + filename + ": BND reading error");

        if ( mesh_dimension != bnd.dim_geom() )
          throw bad_file_format_exception("* ViennaGrid: bnd_reader::operator(): File " + filename + ": Geometric dimension mismatch.");


        std::map<BNDIndexType, VertexHandleType> vertices;
        std::map<BNDPolygonType, CellHandleType> cells;


        for (std::size_t segment_id = 0; segment_id != bnd.segment_size(); ++segment_id)
        {
          SegmentHandleType segment = segmentation.get_make_segment( segment_id );
          BNDPolygonContainerType & polygons = bnd.segment( segment_id );


          for (std::size_t poly_pos = 0; poly_pos != polygons.size(); ++poly_pos)
          {
            BNDPolygonType & polygon = polygons[poly_pos];
//             std::cout << polygon.size() << std::endl;
            std::sort(polygon.begin(), polygon.end());

            if ((num_vertices > 0) && (num_vertices != polygon.size()))
            {
              std::stringstream ss;
              ss << "* ViennaGrid: bnd_reader::operator(): File " << filename << ": ";
              ss << "ERROR: polygon " << poly_pos << " has " << polygon.size() << " vertices but should have " << num_vertices << std::endl;

              throw bad_file_format_exception(ss.str());
            }



            std::vector<VertexHandleType> vertex_handles;

            typename std::map<BNDPolygonType, CellHandleType>::iterator cit = cells.find( polygon );
            if (cit != cells.end())
            {
              viennagrid::add( segment, cit->second );
            }
            else
            {
              for (std::size_t vtx_pos = 0; vtx_pos != polygon.size(); ++vtx_pos)
              {
                BNDIndexType vtx_index = polygon[vtx_pos];

                typename std::map<BNDIndexType, VertexHandleType>::iterator vit = vertices.find( vtx_index );
                if (vit != vertices.end())
                  vertex_handles.push_back(vit->second);
                else
                {
                  BNDPointType const & bnd_point = bnd.point( vtx_index );
                  PointType point;
                  std::copy( bnd_point.begin(), bnd_point.end(), point.begin() );

                  VertexHandleType vtx_handle = viennagrid::make_vertex( mesh, point );

                  vertices[vtx_index] = vtx_handle;
                  vertex_handles.push_back(vtx_handle);
                }
              }

              cells[polygon] = viennagrid::make_cell( segment, vertex_handles.begin(), vertex_handles.end() );
            }
          }
        }
      }



    private:

    };



  }
}



#endif
