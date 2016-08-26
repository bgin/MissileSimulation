#ifndef VIENNAGRID_IO_SERIALIZATION_HPP
#define VIENNAGRID_IO_SERIALIZATION_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

/** @file serialization.hpp
 *  @brief    A mesh wrapper class which models the Boost Serialization concept: http://www.boost.org/libs/serialization/
 */

#include "viennagrid/forwards.hpp"
#include "viennagrid/mesh/mesh.hpp"


#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/shared_ptr.hpp>

/** @file viennagrid/io/serialization.hpp
    @brief Provides a serialization mechanism for use with Boost
*/

namespace viennagrid
{
  namespace io
  {

    /** @brief Provides an exception for the bad serialization state */
    class bad_serialization_state_exception : public std::exception
    {
      public:
        virtual const char* what() const throw()
        {
          std::stringstream ss;
          ss << "* ViennaGrid: Bad serialization state: " << msg_ << "!";
          return ss.str().c_str();
        }

        bad_serialization_state_exception(std::string msg) : msg_(msg) {}

        virtual ~bad_serialization_state_exception() throw() {}

      private:
        std::string msg_;
    };



    /** @brief Mesh wrapper which models the Boost serialization concept
     *
     */
    template<typename MeshT>
    struct mesh_serializer
    {
    private:
      typedef typename viennagrid::result_of::cell_tag<MeshT>::type                        CellTag;
      typedef typename viennagrid::result_of::const_vertex_range<MeshT>::type              ConstVertexRange;
      typedef typename viennagrid::result_of::iterator<ConstVertexRange>::type             ConstVertexIterator;
      typedef typename viennagrid::result_of::point<MeshT>::type                           PointType;
      typedef typename viennagrid::result_of::vertex<MeshT>::type                          VertexType;
      typedef typename viennagrid::result_of::vertex_handle<MeshT>::type                   VertexHandleType;
      typedef typename viennagrid::result_of::id<VertexType>::type                         VertexIDType;
      typedef typename viennagrid::result_of::cell<MeshT>::type                            CellType;
      typedef typename viennagrid::result_of::const_cell_range<MeshT>::type                ConstCellRange;
      typedef typename viennagrid::result_of::iterator<ConstCellRange>::type               ConstCellIterator;
      typedef typename viennagrid::result_of::const_vertex_range<CellType>::type           ConstVertexOnCellRange;
      typedef typename viennagrid::result_of::iterator<ConstVertexOnCellRange>::type       ConstVertexOnCellIterator;

      static const int DIMG = PointType::dim;

      friend class boost::serialization::access;

      /** @brief Save function is used to 'read' the data from the mesh */
      template<class Archive>
      void save(Archive & ar, const unsigned int version) const
      {
        if (!mesh_pointer)
          throw bad_serialization_state_exception( "Mesh not loaded into serialzer object" );

        MeshT const & mesh_obj = *mesh_pointer;

        // -----------------------------------------------
        // the geometry is read and transmitted
        //
        std::size_t point_size = viennagrid::vertices(mesh_obj).size();
        ar & point_size;
        ConstVertexRange vertices(mesh_obj);
        for (ConstVertexIterator vit = vertices.begin();
             vit != vertices.end(); ++vit)
        {
          for(int d = 0; d < DIMG; d++)
            ar & viennagrid::point(*vit)[d];
        }


        // -----------------------------------------------
        // the specific cells are read and transmitted
        //
        ConstCellRange cells(mesh_obj);

        std::size_t cell_size = viennagrid::cells(mesh_obj).size();
        ar & cell_size;

        for (ConstCellIterator cit = cells.begin();
        cit != cells.end(); ++cit)
        {
          ConstVertexOnCellRange vertices_on_cell(*cit);

          for (ConstVertexOnCellIterator vocit = vertices_on_cell.begin();
          vocit != vertices_on_cell.end();
          ++vocit)
          {
            std::size_t id = vocit->id().get();
            ar & id;
          }
        }
        // -----------------------------------------------
      }

      /** @brief Load function is used to 'write' the data to the mesh */
      template<class Archive>
      void load(Archive & ar, const unsigned int version)
      {
        if (!mesh_pointer)
          throw bad_serialization_state_exception( "Mesh not loaded into serialzer object" );

        MeshT & mesh_obj = *mesh_pointer;

        // -----------------------------------------------
        // the geometry is received and stored
        //
        std::size_t point_size;
        ar & point_size;

        for(std::size_t i = 0; i < point_size; i++)
        {
          PointType p;
          for(int d = 0; d < DIMG; d++)
            ar & p[d];

          viennagrid::make_vertex( *mesh_pointer, p );
        }
        // -----------------------------------------------


        // -----------------------------------------------
        // the specific cells are received and stored
        //

        std::size_t cell_size;
        ar & cell_size;
        for(std::size_t ci = 0; ci < cell_size; ci++)
        {
          const int num_vertices = viennagrid::boundary_elements<CellTag, vertex_tag>::num;
          VertexHandleType vertices[num_vertices];

          for (int j=0; j< num_vertices; ++j)
          {
            std::size_t id;
            ar & id;
            vertices[j] = viennagrid::find_by_id( mesh_obj, VertexIDType(id) ).handle();
          }

          viennagrid::make_cell( mesh_obj, vertices, vertices + num_vertices);
        }
        // -----------------------------------------------
      }

      // -----------------------------------------------
      // notify Boost Serialization that the save and load
      // procedures differ
      //
      BOOST_SERIALIZATION_SPLIT_MEMBER()
      // -----------------------------------------------
    public:
      /** @brief The default constructor*/
      mesh_serializer() : mesh_pointer(0) {}

      /** @brief The constructor expects a shared pointer on a mesh object and sets the state */
      mesh_serializer(MeshT & mesh_obj) : mesh_pointer(mesh_obj) {}

      /** @brief The load function enables to associate a mesh with the serialzer after
      a serializer object has been constructed. */
      inline void load(MeshT & mesh_obj) { mesh_pointer = &mesh;  }

      /** @brief The get function enables to retrieve the mesh pointer
      */
      inline MeshT & get() { return *mesh_pointer; }
      inline MeshT const & get() const { return *mesh_pointer; }

      /** @brief The functor returns a reference to the mesh state*/
      MeshT & operator()() { return *mesh_pointer; }
      MeshT const & operator()() const { return *mesh_pointer; }

      /** @brief The state holds a shared pointer to the mesh */

    private:
      MeshT * mesh_pointer;
    };

  } //namespace io
} //namespace viennagrid

#endif

