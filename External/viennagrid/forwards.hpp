#ifndef VIENNAGRID_FORWARDS_H
#define VIENNAGRID_FORWARDS_H

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

/**
 @mainpage Source Code Documentation for ViennaGrid 2.1.0

 This is the source code documentation of ViennaGrid. Detailed information about the functions in ViennaGrid can be found here.

 For a general overview over the types and functionality provided by ViennaGrid, please refer to the file doc/viennagrid.pdf

*/

#include <iostream>
#include <vector>
#include <map>
#include <cstddef>     //for std::size_t
#include <cstdlib>     //for EXIT_SUCCESS and EXIT_FAILURE

#define VIENNAGRID_MAJOR_VERSION   2
#define VIENNAGRID_MINOR_VERSION   1
#define VIENNAGRID_BUGFIX_LEVEL    0


#include "viennagrid/storage/static_array.hpp"
#include "viennagrid/storage/forwards.hpp"

//Debug levels:
//VIENNAGRID_DEBUG_ALL          Output every little piece of debug information
//VIENNAGRID_DEBUG_IO           Debug IO operations
//VIENNAGRID_DEBUG_STATUS       Print status messages to std::cout (very little debug info)

#ifdef VIENNAGRID_DEBUG_ALL
  #define VIENNAGRID_DEBUG_IO
  #define VIENNAGRID_DEBUG_STATUS
#endif

/** @file viennagrid/forwards.hpp
    @brief Contains forward declarations and definition of small classes that must be defined at an early stage
*/

/** @brief The main ViennaGrid namespace. Most user functionality resides directly in this namespace rather than in sub-namespaces. */
namespace viennagrid
{
  /** @brief Namespace for implementation details. Not intended to be used directly by a library user */
  namespace detail
  {
    /** @brief Namespace for metafunctions for implementation details. Not intended to be used directly by a library user */
    namespace result_of {}
  }

  /** @brief Provides a number of predefined configuration classes, which cover the most frequent use cases. */
  namespace config
  {
    /** @brief Namespace for metafunctions for obtaining the respective mesh configurations. */
    namespace result_of {}
  }

  /** @brief A namespace with all the input/output functionality, in particular file readers and writers */
  namespace io
  {
    /** @brief Namespace for implementation details. Not intended to be used directly by a library user */
    namespace detail {}
  }

  /** @brief Advances an iterator and returns it
    *
    * @param in          the input iterator
    * @param distance    the distance to advance
    * @return            the iterator, advanced by distance
    */
  template<typename iterator_type, typename distance_type>
  iterator_type advance(iterator_type const & in, distance_type distance)
  {
      iterator_type out(in);
      std::advance(out, static_cast<long>(distance));
      return out;
  }


  /** @brief A global size_type equivalent for use throughout ViennaData. */
  typedef std::size_t       dim_type;

  /********* Tags ***********************/

  /** @brief Forward declaration of a d-dimensional Cartesian coordinate system */
  template <int d>
  struct cartesian_cs;    //Cartesian coordinate system

  /** @brief Forward declaration of a polar coordinate system */
  struct polar_cs;        //Polar coordinate system (r, phi)
  /** @brief Forward declaration of a spherical coordinate system */
  struct spherical_cs;    //Spherical coordinate system (r, theta, phi)
  /** @brief Forward declaration of a cylindrical coordinate system */
  struct cylindrical_cs;  //Cylindrical coordinate system (rho, theta, z)

  //Dimension Tag: (for tag dispatching)
  /** @brief A helper tag for dispatches based on the geometrical or topological dimension */
  template <int d>
  struct dimension_tag
  {
      static const int value = d;
  };

  //Tags for the handling of elements at different topological levels (see topology::subcell_desc)
  /** @brief A tag denoting full storage of boundary elements of a certain topological element */
  struct full_handling_tag {};
  /** @brief A tag denoting that the boundary elements should not be stored at all */
  struct no_handling_tag {};

  /** @brief A tag denoting that the boundary elements should stored without orientation */
  struct no_orientation_handling_tag {};

//   Lazy storage reserved for future use
  /** @brief A tag denoting that orientation should be stored/computed only on request ('lazy'). */
  struct no_orientation_lazy_handling_tag {};
  /** @brief A tag denoting lazy handling of boundary elements. Reserved for future use. */
  struct full_lazy_handling_tag {};


  /** @brief A tag for identifying the coboundary collection */
  struct coboundary_collection_tag {};
  /** @brief A tag for identifying the neighbor element collection */
  struct neighbor_collection_tag {};
  /** @brief A tag for identifying boundary information */
  struct boundary_information_collection_tag {};
  /** @brief A tag identifying interface information */
  struct interface_information_collection_tag {};


  /********* Forward definitions of main classes *******************/

  // Simplex family:
  /** @brief A tag for the simplex family (triangle, tetrahedron, etc.) */
  template <int dim>
  struct simplex_tag;

  /** @brief Convenience type definition for a vertex */
  typedef simplex_tag<0>    vertex_tag;
  /** @brief Convenience type definition for a line (same as edge_tag) */
  typedef simplex_tag<1>    line_tag;
  /** @brief Convenience type definition for a line (same as line_tag) */
  typedef simplex_tag<1>    edge_tag;
  /** @brief Convenience type definition for a triangle */
  typedef simplex_tag<2>    triangle_tag;
  /** @brief Convenience type definition for a tetrahedron */
  typedef simplex_tag<3>    tetrahedron_tag;

  // Hypercube family:
  /** @brief A tag for the family of hypercubes (line, quadrilateral, hexahedron, etc.) */
  template <int dim>
  struct hypercube_tag;

  //typedef hypercube_tag<1>    line_tag;
  /** @brief Convenience type definition for a quadrilateral */
  typedef hypercube_tag<2>  quadrilateral_tag;
  /** @brief Convenience type definition for a hexahedron */
  typedef hypercube_tag<3>  hexahedron_tag;

  //see viennagrid/topology/polygon.hpp
  struct polygon_tag;

  //see viennagrid/topology/plc.hpp
  struct plc_tag;


  /** @brief Tag that indicates that a static container can be used for storing the boundary element handles (e.g. used in simplices and hypercubes) */
  struct static_layout_tag {};
  /** @brief Tag that indicates that a dynamic container has to be used for storing the boundary element handles (e.g. polygon and plc) */
  struct dynamic_layout_tag {};



  //forward declarations:

  /** @brief Represents an arbitrary point in the underlying coordinate system.
   *
   * @tparam CoordType          Type of each coordinate entry (usually double or float)
   * @tparam CoordinateSystem   The underlying coordinate system of the point.
   */
  template <typename CoordType, typename CoordinateSystem>
  class spatial_point;

  /** @brief Represents a topological element within a mesh
   *
   * @tparam ElementTag         Tag representing the element (e.g. vertex_tag)
   * @tparam WrappedConfigType  The configuration of the complex where the element lives
   */
  template<typename ElementTag, typename WrappedConfigType>
  class element;



  /** @brief Helper class for defining boundary element information
   *
   * @tparam ElementTag         Tag for the identification of the hosting element
   * @tparam BoundaryElementTag A tag representing the boundary element of the element with ElementTag
   */
  template <typename ElementTag, typename BoundaryElementTag = ElementTag>
  struct boundary_elements
  {
    //the default case is simultaneously a pathetic case:
    //cell-handling within the cell

    /** @brief Number of boundary cells at this level */
    static const int num = 1;     //1 cell

    /** @brief k-cell tag for identification of the type */
    typedef ElementTag            tag;
  };


  namespace detail
  {
    /** @brief Worker class that generates the boundary elements of a host element
     *
     * @tparam ElementTag           Tag for the identification of the hosting n-cell
     * @tparam BoundaryElementTag   Topological boundary tag
     * @tparam BoundaryElementType  Topological boundary type, used within create_boundary_elements method
     */
    template <typename ElementTag, typename BoundaryElementTag, typename BoundaryElementType>
    struct boundary_element_generator {};

    template<typename ElementTag, typename BoundaryElementType>
    struct boundary_element_generator<ElementTag, vertex_tag, BoundaryElementType>
    {
      template<typename element_type, typename inserter_type>
      static void create_boundary_elements(element_type &, inserter_type &) {}
    };

  }





  namespace detail
  {
    template <typename MeshConfigT, typename ElementTypeListT, typename ContainerConfigT>
    class decorated_mesh_view_config;
  }

  // see mesh.hpp
  template <typename WrappedConfigT>
  class mesh;

  // see segmentation.hpp
  template<typename WrappedConfigT>
  class segmentation;

  // see segmentation.hpp
  template<typename SegmentationT>
  class segment_handle;

  namespace detail
  {
    template<typename container_type_, typename change_counter_type>
    struct coboundary_container_wrapper;

    template<typename container_type_, typename change_counter_type>
    struct neighbor_container_wrapper;

    template<typename container_type_, typename change_counter_type>
    struct boundary_information_wrapper;


    template<typename ConfigType>
    typename viennagrid::mesh<ConfigType>::inserter_type &
    inserter(viennagrid::mesh<ConfigType> & mesh_obj);

    template<typename ConfigType>
    typename viennagrid::mesh<ConfigType>::inserter_type const &
    inserter(viennagrid::mesh<ConfigType> const & mesh_obj);

    template<typename SegmentationType>
    typename viennagrid::segment_handle<SegmentationType>::view_type::inserter_type & inserter(segment_handle<SegmentationType> & segment);

    template<typename SegmentationType>
    typename viennagrid::segment_handle<SegmentationType>::view_type::inserter_type const & inserter(segment_handle<SegmentationType> const & segment);
  }





  /** @brief The metafunction layer. Provides type generators that derive the respective type from the mesh configuration */
  namespace result_of
  {
    template<typename WrappedConfigT>
    struct mesh;

    /** @brief Metafunction for obtaining the element collection of something
     *
     * @tparam SomethingT     The host type, can be a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct element_collection {};

    /** @brief Metafunction for obtaining the container collection typemap of something
     *
     * @tparam SomethingT     The host type, can be a typelist or a collection
     */
    template<typename SomethingT>
    struct container_collection_typemap {};

    template<typename SomethingT>
    struct topologic_cell_dimension;

    template<typename SomethingT, int TopologicDimensionV>
    struct elements_of_topologic_dim;

    template<typename SomethingT>
    struct cells;

    template<typename SomethingT>
    struct cell;

    template<typename SomethingT>
    struct cell_tag;


    /** @brief Metafunction for obtaining the geometric point type of something
     *
     * @tparam SomethingT           The host type, can be an element, a mesh, a segmentation, a segment, an accessor or a field
     */
    template<typename SomethingT>
    struct point {};

    /** @brief Metafunction for obtaining the coordinate type of the geometric point type of something
     *
     * @tparam SomethingT           The host type, can be a point, an element, a mesh, a segmentation, a segment, an accessor or a field
     */
    template<typename SomethingT>
    struct coord
    {
      typedef typename coord< typename point<SomethingT>::type >::type type;
    };

    /** @brief Metafunction for obtaining the geometric dimension of something
     *
     * @tparam SomethingT           The host type, can be an element, a mesh, a segmentation, a segment, an accessor or a field
     */
    template<typename SomethingT>
    struct geometric_dimension
    {
      static const int value = geometric_dimension< typename point<SomethingT>::type >::value;
    };


    /** @brief Metafunction for obtaining the id type of an element
     *
     * @tparam ElementT           The host element type
     */
    template<typename ElementT>
    struct id
    {
      typedef typename ElementT::id_type type;
    };


    template<typename SomethingT, typename ElementTypeOrTagT>
    struct element;

    /** \cond */
    template<typename element_tag, typename WrappedConfigType>
    struct element< viennagrid::element<element_tag, WrappedConfigType>, viennagrid::element<element_tag, WrappedConfigType> >
    {
      typedef viennagrid::element<element_tag, WrappedConfigType> type;
    };

    template<typename element_tag, typename WrappedConfigType>
    struct element< viennagrid::element<element_tag, WrappedConfigType>, element_tag >
    {
      typedef viennagrid::element<element_tag, WrappedConfigType> type;
    };

    template<typename SomethingT>
    struct element<SomethingT, viennagrid::null_type>
    {
      typedef viennagrid::null_type type;
    };
    /** \endcond */

    /** @brief Convenience metafunction for the type retrieval of a vertex
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct vertex
    {
      typedef typename element<SomethingT, vertex_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a line (same as edge)
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct line
    {
      typedef typename element<SomethingT, line_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a edge (same as line)
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct edge
    {
      typedef typename element<SomethingT, edge_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a triangle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct triangle
    {
      typedef typename element<SomethingT, triangle_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a quadrilateral
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct quadrilateral
    {
      typedef typename element<SomethingT, quadrilateral_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a polygon
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct polygon
    {
      typedef typename element<SomethingT, polygon_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a plc
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct plc
    {
      typedef typename element<SomethingT, plc_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a tetrahedron
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct tetrahedron
    {
      typedef typename element<SomethingT, tetrahedron_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a hexahedron
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct hexahedron
    {
      typedef typename element<SomethingT, hexahedron_tag>::type type;
    };


    template<typename SomethingT, typename ElementTypeOrTagT>
    struct handle;

    /** @brief Convenience metafunction for the type retrieval of a cell handle. Will fail if there is more than one cell type
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct cell_handle
    {
      typedef typename cell_tag<SomethingT>::type cell_tag;
      typedef typename handle<SomethingT, cell_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a vertex handle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct vertex_handle
    {
      typedef typename handle<SomethingT, vertex_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a line handle (same as edge_handle)
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct line_handle
    {
      typedef typename handle<SomethingT, line_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a line handle (same as line_handle)
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct edge_handle
    {
      typedef typename handle<SomethingT, edge_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a triangle handle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct triangle_handle
    {
      typedef typename handle<SomethingT, triangle_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a quadrilateral handle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct quadrilateral_handle
    {
      typedef typename handle<SomethingT, quadrilateral_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a polygon handle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct polygon_handle
    {
      typedef typename handle<SomethingT, polygon_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a plc handle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct plc_handle
    {
      typedef typename handle<SomethingT, plc_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a tetrahedron handle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct tetrahedron_handle
    {
      typedef typename handle<SomethingT, tetrahedron_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a hexahedron handle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct hexahedron_handle
    {
      typedef typename handle<SomethingT, hexahedron_tag>::type type;
    };



    template<typename SomethingT, typename ElementTypeOrTagT>
    struct const_handle;

    /** @brief Convenience metafunction for the type retrieval of a const cell handle. Will fail if there is more than one cell type
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_cell_handle
    {
      typedef typename cell_tag<SomethingT>::type cell_tag;
      typedef typename const_handle<SomethingT, cell_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const vertex handle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_vertex_handle
    {
      typedef typename const_handle<SomethingT, vertex_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const line handle (same as const_edge_handle)
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_line_handle
    {
      typedef typename const_handle<SomethingT, line_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const line handle (same as const_line_handle)
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_edge_handle
    {
      typedef typename const_handle<SomethingT, edge_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const triangle handle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_triangle_handle
    {
      typedef typename const_handle<SomethingT, triangle_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const quadrilateral handle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_quadrilateral_handle
    {
      typedef typename const_handle<SomethingT, quadrilateral_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const polygon handle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_polygon_handle
    {
      typedef typename const_handle<SomethingT, polygon_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const plc handle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_plc_handle
    {
      typedef typename const_handle<SomethingT, plc_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const tetrahedron handle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_tetrahedron_handle
    {
      typedef typename const_handle<SomethingT, tetrahedron_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const hexahedron handle
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_hexahedron_handle
    {
      typedef typename const_handle<SomethingT, hexahedron_tag>::type type;
    };







    /** @brief Convenience metafunction for the type retrieval of a cell ID. Will fail if there is more than one cell type
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct cell_id
    {
      typedef typename id< typename cell<SomethingT>::type >::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a vertex ID
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct vertex_id
    {
      typedef typename id< typename vertex<SomethingT>::type >::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a line ID (same as edge_id)
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct line_id
    {
      typedef typename id< typename line<SomethingT>::type >::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a line ID (same as line_id)
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct edge_id
    {
      typedef typename id< typename edge<SomethingT>::type >::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a triangle ID
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct triangle_id
    {
      typedef typename id< typename triangle<SomethingT>::type >::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a quadrilateral ID
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct quadrilateral_id
    {
      typedef typename id< typename quadrilateral<SomethingT>::type >::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a polygon v
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct polygon_id
    {
      typedef typename id< typename polygon<SomethingT>::type >::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a plc ID
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct plc_id
    {
      typedef typename id< typename plc<SomethingT>::type >::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a tetrahedron ID
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct tetrahedron_id
    {
      typedef typename id< typename tetrahedron<SomethingT>::type >::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a hexahedron ID
     *
     * @tparam SomethingT         The host type, can be a collection, an element, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct hexahedron_id
    {
      typedef typename id< typename hexahedron<SomethingT>::type >::type type;
    };









    template <typename SomethingT,
              typename ElementTypeOrTagT>
    struct element_range;


    /** @brief Convenience metafunction for the type retrieval of a cell range. Will fail if there is more than one cell type
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct cell_range
    {
      typedef typename cell_tag<SomethingT>::type cell_tag;
      typedef typename element_range<SomethingT, cell_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a vertex range
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct vertex_range
    {
      typedef typename element_range<SomethingT, vertex_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a line range (same as edge_range)
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct line_range
    {
      typedef typename element_range<SomethingT, line_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a edge range (same as line_range)
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct edge_range
    {
      typedef typename element_range<SomethingT, edge_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a triangle range
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct triangle_range
    {
      typedef typename element_range<SomethingT, triangle_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a quadrilateral range
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct quadrilateral_range
    {
      typedef typename element_range<SomethingT, quadrilateral_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a polygon range
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct polygon_range
    {
      typedef typename element_range<SomethingT, polygon_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a PLC range
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct plc_range
    {
      typedef typename element_range<SomethingT, plc_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a tetrahedron range
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct tetrahedron_range
    {
      typedef typename element_range<SomethingT, tetrahedron_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a hexahedron range
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct hexahedron_range
    {
      typedef typename element_range<SomethingT, hexahedron_tag>::type type;
    };






    template <typename SomethingT,
              typename ElementTypeOrTagT>
    struct const_element_range;


    /** @brief Convenience metafunction for the type retrieval of a const cell range. Will fail if there is more than one cell type
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_cell_range
    {
      typedef typename cell_tag<SomethingT>::type cell_tag;
      typedef typename const_element_range<SomethingT, cell_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const vertex range
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_vertex_range
    {
      typedef typename const_element_range<SomethingT, vertex_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const line range (same as const_edge_range)
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_line_range
    {
      typedef typename const_element_range<SomethingT, line_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const edge range (same as const_line_range)
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_edge_range
    {
      typedef typename const_element_range<SomethingT, edge_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const triangle range
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_triangle_range
    {
      typedef typename const_element_range<SomethingT, triangle_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const quadrilateral range
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_quadrilateral_range
    {
      typedef typename const_element_range<SomethingT, quadrilateral_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const polygon range
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_polygon_range
    {
      typedef typename const_element_range<SomethingT, polygon_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const PLC range
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_plc_range
    {
      typedef typename const_element_range<SomethingT, plc_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const tetrahedron range
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_tetrahedron_range
    {
      typedef typename const_element_range<SomethingT, tetrahedron_tag>::type type;
    };

    /** @brief Convenience metafunction for the type retrieval of a const hexahedron range
     *
     * @tparam SomethingT         The host type, can be a typelist, a collection, a mesh, a segmentation or a segment
     */
    template<typename SomethingT>
    struct const_hexahedron_range
    {
      typedef typename const_element_range<SomethingT, hexahedron_tag>::type type;
    };




    /** @brief Metafunction for the type retrieval of an iterator from a container or range
     *
     * @tparam ContainerT         The container type, can also be a range
     */
    template <typename ContainerT>
    struct iterator
    {
      typedef typename ContainerT::iterator type;
    };

    /** @brief Metafunction for the type retrieval of a const iterator from a container or range
     *
     * @tparam ContainerT         The container type, can also be a range
     */
    template <typename ContainerT>
    struct const_iterator
    {
      typedef typename ContainerT::const_iterator type;
    };

    /** \cond */
    template <typename ContainerT>
    struct iterator<const ContainerT>
    {
      typedef typename const_iterator<ContainerT>::type type;
    };
    /** \endcond */



    /** @brief Metafunction for retrieving the tag of an element
     *
     * @tparam ElementTypeOrTagT    The element type of which the tag is requested, can also be a tag. In this case the tag is returned.
     */
    template<typename ElementTypeOrTagT>
    struct element_tag
    {
      typedef ElementTypeOrTagT type;
    };

    /** \cond */
    template<typename ElementTagT, typename WrappedConfigT>
    struct element_tag< viennagrid::element<ElementTagT, WrappedConfigT> >
    {
      typedef ElementTagT type;
    };

    template<typename ElementTagT, typename WrappedConfigT>
    struct element_tag< const viennagrid::element<ElementTagT, WrappedConfigT> >
    {
      typedef ElementTagT type;
    };
    /** \endcond */


    /** @brief Metafunction for retrieving the facet tag of an element, a mesh, a segmentation or a segment
     *
     * @tparam SomethingT    The element type of which the facet tag is requested. Can also be a mesh, a segmentation or a segment. In this case the facet tag of the cell type is returned.
     */
    template<typename SomethingT>
    struct facet_tag
    {
      typedef typename element_tag<SomethingT>::type::facet_tag type;
    };

    /** \cond */
    template<typename SomethingT>
    struct facet_tag< const SomethingT>
    {
      typedef typename facet_tag<SomethingT>::type  type;
    };

    template<typename WrappedMeshConfigT>
    struct facet_tag< viennagrid::mesh<WrappedMeshConfigT> >
    {
      typedef typename facet_tag< typename cell_tag< viennagrid::mesh<WrappedMeshConfigT> >::type >::type type;
    };

    template<typename WrappedSegmentationConfigT>
    struct facet_tag< viennagrid::segmentation<WrappedSegmentationConfigT> >
    {
      typedef typename facet_tag< typename cell_tag< viennagrid::segmentation<WrappedSegmentationConfigT> >::type >::type type;
    };

    template<typename SegmentationT>
    struct facet_tag< viennagrid::segment_handle<SegmentationT> >
    {
      typedef typename facet_tag< typename cell_tag< viennagrid::segment_handle<SegmentationT> >::type >::type type;
    };
    /** \endcond */




    /** @brief Metafunction for retrieving the facet element type an element, a mesh, a segmentation or a segment
     *
     * @tparam SomethingT    The element type of which the facet type is requested. Can also be a mesh, a segmentation or a segment. In this case the facet type of the cell type is returned.
     */
    template<typename SomethingT>
    struct facet
    {
      typedef typename element<SomethingT, typename facet_tag<SomethingT>::type >::type type;
    };

    /** \cond */
    template<typename SomethingT>
    struct facet< const SomethingT>
    {
      typedef typename facet<SomethingT>::type    type;
    };

    template<typename WrappedMeshConfigT>
    struct facet< viennagrid::mesh<WrappedMeshConfigT> >
    {
      typedef typename facet< typename cell< viennagrid::mesh<WrappedMeshConfigT> >::type >::type type;
    };

    template<typename WrappedSegmentationConfigT>
    struct facet< viennagrid::segmentation<WrappedSegmentationConfigT> >
    {
      typedef typename facet< typename cell< viennagrid::segmentation<WrappedSegmentationConfigT> >::type >::type type;
    };

    template<typename SegmentationT>
    struct facet< viennagrid::segment_handle<SegmentationT> >
    {
      typedef typename facet< typename cell< viennagrid::segment_handle<SegmentationT> >::type >::type type;
    };
    /** \endcond */


    /** @brief Metafunction for retrieving the facet handle type an element, a mesh, a segmentation or a segment
     *
     * @tparam SomethingT    The element type of which the facet handle type is requested. Can also be a mesh, a segmentation or a segment. In this case the facet handle type of the cell type is returned.
     */
    template<typename SomethingT>
    struct facet_handle
    {
      typedef typename handle< SomethingT, typename facet_tag<SomethingT>::type >::type type;
    };

    /** @brief Metafunction for retrieving the const facet handle type an element, a mesh, a segmentation or a segment
     *
     * @tparam SomethingT    The element type of which the const facet handle type is requested. Can also be a mesh, a segmentation or a segment. In this case the const facet handle type of the cell type is returned.
     */
    template<typename SomethingT>
    struct const_facet_handle
    {
      typedef typename const_handle< SomethingT, typename facet_tag<SomethingT>::type >::type type;
    };

    /** @brief Metafunction for retrieving the facet handle type an element, a mesh, a segmentation or a segment
     *
     * @tparam SomethingT    The element type of which the facet handle type is requested. Can also be a mesh, a segmentation or a segment. In this case the facet handle type of the cell type is returned.
     */
    template<typename SomethingT>
    struct facet_id
    {
      typedef typename id< typename facet<SomethingT>::type >::type type;
    };


    /** @brief Metafunction for retrieving the facet range type an element, a mesh, a segmentation or a segment
     *
     * @tparam SomethingT    The element type of which the facet range type is requested. Can also be a mesh, a segmentation or a segment. In this case the facet range type of the cell type is returned.
     */
    template<typename SomethingT>
    struct facet_range
    {
      typedef typename element_range<SomethingT, typename facet_tag<SomethingT>::type >::type type;
    };

    /** @brief Metafunction for retrieving the const facet range type an element, a mesh, a segmentation or a segment
     *
     * @tparam SomethingT    The element type of which the const facet range type is requested. Can also be a mesh, a segmentation or a segment. In this case the const facet range type of the cell type is returned.
     */
    template<typename SomethingT>
    struct const_facet_range
    {
      typedef typename const_element_range<SomethingT, typename facet_tag<SomethingT>::type >::type type;
    };


    /** @brief Metafunction for obtaining the segment type from a segmentation type
     *
     * @tparam SegmentationT      The segmentation type
     */
    template<typename SegmentationT>
    struct segment_handle;
  }


  /** @brief Function for retrieving an element range or a boundary element range from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @tparam ElementTypeOrTagT  The element type/tag for the requested element range
    * @param  something          The host object of type SomethingT
    * @return                    An element range
    */
  template<typename ElementTypeOrTagT, typename SomethingT>
  typename result_of::element_range<SomethingT, ElementTypeOrTagT>::type elements(SomethingT & something);


  /** @brief Function for retrieving an element range or a boundary element range from a mesh. Non-const version.
    *
    * @tparam WrappedConfigType  The host mesh configuration class (providing the typemap as 'type' member type)
    * @tparam ElementTypeOrTagT  The element type/tag for the requested element range
    * @param  mesh_obj           The mesh object
    * @return                    An element range
    */
  template<typename ElementTypeOrTagT, typename WrappedConfigType>
  typename result_of::element_range<viennagrid::mesh<WrappedConfigType>, ElementTypeOrTagT>::type
  elements(viennagrid::mesh<WrappedConfigType> & mesh_obj);


  /** @brief Function for retrieving an element range or a boundary element range from a segment
    *
    * @tparam SegmentationT      The host segmentation
    * @tparam ElementTypeOrTagT  The element type/tag for the requested element range
    * @param  segment            The host object of type SomethingT
    * @return                    An element range
    */
  template<typename ElementTypeOrTagT, typename SegmentationT>
  typename result_of::element_range< viennagrid::segment_handle<SegmentationT>, ElementTypeOrTagT>::type
  elements( viennagrid::segment_handle<SegmentationT> & segment)
  { return elements<ElementTypeOrTagT>( segment.view() ); }

  /** @brief Function for retrieving an element range or a boundary element range from a segmentation. Non-const version.
    *
    * @tparam ElementTypeOrTagT  The element type/tag for the requested element range
    * @tparam WrappedConfigT     The host mesh configuration class (providing the typemap as 'type' member type)
    * @param  segm               The hosting segmentation object
    * @return                    An element range
    */
  template<typename ElementTypeOrTagT, typename WrappedConfigT>
  typename result_of::element_range<segmentation<WrappedConfigT>, ElementTypeOrTagT>::type
  elements( viennagrid::segmentation<WrappedConfigT> & segm)
  { return elements<ElementTypeOrTagT>( segm.all_elements() ); }


  /** @brief Function for retrieving a boundary element range from a host element. Non-const version.
    *
    * @tparam sub_element_type_or_tag  The element type/tag for the requested boundary element range
    * @tparam element_tag              The element tag of the host element
    * @tparam WrappedConfigType        The host mesh/element configuration class (providing the typemap as 'type' member type)
    * @param  element                  The host element from which the boundary element range should be obtained
    * @return                          An element range
    */
  template<typename sub_element_type_or_tag, typename element_tag, typename WrappedConfigType>
  typename result_of::element_range<viennagrid::element<element_tag, WrappedConfigType>, sub_element_type_or_tag>::type
  elements( viennagrid::element<element_tag, WrappedConfigType> & element);

  /** @brief Function for retrieving a boundary element range from a host element. Const version.
    *
    * @tparam sub_element_type_or_tag  The element type/tag for the requested boundary element range
    * @tparam element_tag              The element tag of the host element
    * @tparam WrappedConfigType        The host mesh/element configuration class (providing the typemap as 'type' member type)
    * @param  element                  The host element from which the boundary element range should be obtained
    * @return                          An element range
    */
  template<typename sub_element_type_or_tag, typename element_tag, typename WrappedConfigType>
  typename result_of::const_element_range<viennagrid::element<element_tag, WrappedConfigType>, sub_element_type_or_tag>::type
  elements( const viennagrid::element<element_tag, WrappedConfigType> & element);


  /** @brief Function for retrieving a cell range object from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A cell range
    */
  template<typename SomethingT>
  typename result_of::cell_range<SomethingT>::type cells(SomethingT & something)
  { return elements<typename result_of::cell_tag<SomethingT>::type>(something); }

  /** @brief Function for retrieving a facet range object from a host object
    *
    * @tparam ElementT           The host element (cell)
    * @param  element            The host object of type ElementT
    * @return                    A facet range
    */
  template<typename ElementT>
  typename result_of::facet_range<ElementT>::type facets(ElementT & element)
  { return elements< typename result_of::facet_tag<ElementT>::type >(element); }

  /** @brief Function for retrieving a vertex range object from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A vertex range
    */
  template<typename SomethingT>
  typename result_of::element_range<SomethingT, vertex_tag>::type vertices(SomethingT & something)
  { return elements<vertex_tag>(something); }

  /** @brief Function for retrieving a line range object from a host object (same as edges)
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A line range
    */
  template<typename SomethingT>
  typename result_of::element_range<SomethingT, line_tag>::type lines(SomethingT & something)
  { return elements<line_tag>(something); }

  /** @brief Function for retrieving a edge range object from a host object (same as lines)
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    An edge range
    */
  template<typename SomethingT>
  typename result_of::element_range<SomethingT, edge_tag>::type edges(SomethingT & something)
  { return elements<edge_tag>(something); }

  /** @brief Function for retrieving a triangle range object from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A triangle range
    */
  template<typename SomethingT>
  typename result_of::element_range<SomethingT, triangle_tag>::type triangles(SomethingT & something)
  { return elements<triangle_tag>(something); }

  /** @brief Function for retrieving a quadrilaterals range object from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A quadrilateral range
    */
  template<typename SomethingT>
  typename result_of::element_range<SomethingT, quadrilateral_tag>::type quadrilaterals(SomethingT & something)
  { return elements<quadrilateral_tag>(something); }

  /** @brief Function for retrieving a polygon range object from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A polygon range
    */
  template<typename SomethingT>
  typename result_of::element_range<SomethingT, polygon_tag>::type polygons(SomethingT & something)
  { return elements<polygon_tag>(something); }

  /** @brief Function for retrieving a PLC range object from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A PLC range
    */
  template<typename SomethingT>
  typename result_of::element_range<SomethingT, plc_tag>::type plcs(SomethingT & something)
  { return elements<plc_tag>(something); }

  /** @brief Function for retrieving a tetrahedron range object from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A tetrahedron range
    */
  template<typename SomethingT>
  typename result_of::element_range<SomethingT, tetrahedron_tag>::type tetrahedra(SomethingT & something)
  { return elements<tetrahedron_tag>(something); }

  /** @brief Function for retrieving a hexahedron range object from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A hexahedron range
    */
  template<typename SomethingT>
  typename result_of::element_range<SomethingT, hexahedron_tag>::type hexahedra(SomethingT & something)
  { return elements<hexahedron_tag>(something); }



  /** @brief Function for retrieving a const element range or a boundary element range from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @tparam ElementTypeOrTagT  The element type/tag for the requested element range
    * @param  something          The host object of type SomethingT
    * @return                    A const element range
    */
  template<typename ElementTypeOrTagT, typename SomethingT>
  typename result_of::const_element_range<SomethingT, ElementTypeOrTagT>::type elements(SomethingT const & something);

  /** @brief Function for retrieving an element range or a boundary element range from a mesh. Const version.
    *
    * @tparam WrappedConfigType  The host mesh configuration class (providing the typemap as 'type' member type)
    * @tparam ElementTypeOrTagT  The element type/tag for the requested element range
    * @param  mesh_obj           The mesh object
    * @return                    An element range
    */
  template<typename ElementTypeOrTagT, typename WrappedConfigType>
  typename result_of::const_element_range<viennagrid::mesh<WrappedConfigType>, ElementTypeOrTagT>::type
  elements(viennagrid::mesh<WrappedConfigType> const & mesh_obj);


  /** @brief Function for retrieving a const element range or a boundary element range from a segment. Const-version.
    *
    * @tparam SegmentationT      The host segmentation
    * @tparam ElementTypeOrTagT  The element type/tag for the requested element range
    * @param  segment            The host object of type SomethingT
    * @return                    A const element range
    */
  template<typename ElementTypeOrTagT, typename SegmentationT>
  typename result_of::const_element_range< viennagrid::segment_handle<SegmentationT>, ElementTypeOrTagT>::type
  elements( viennagrid::segment_handle<SegmentationT> const & segment)
  { return elements<ElementTypeOrTagT>( segment.view() ); }


  /** @brief Function for retrieving an element range or a boundary element range from a segmentation. Const version.
    *
    * @tparam ElementTypeOrTagT  The element type/tag for the requested element range
    * @tparam WrappedConfigT     The host mesh configuration class (providing the typemap as 'type' member type)
    * @param  segm               The hosting segmentation object
    * @return                    An element range
    */
  template<typename ElementTypeOrTagT, typename WrappedConfigT>
  typename result_of::const_element_range<viennagrid::segmentation<WrappedConfigT>, ElementTypeOrTagT>::type
  elements(viennagrid::segmentation<WrappedConfigT> const & segm)
  { return elements<ElementTypeOrTagT>( segm.all_elements() ); }


  /** @brief Function for retrieving a const cell range object from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A const cell range
    */
  template<typename SomethingT>
  typename result_of::const_cell_range<SomethingT>::type cells( SomethingT const & something)
  { return elements<typename result_of::cell_tag<SomethingT>::type>(something); }

  /** @brief Function for retrieving a const facet range object from a host object
    *
    * @tparam ElementT         The host element type
    * @param  element          The host object of type SomethingT
    * @return                  A const facet range
    */
  template<typename ElementT>
  typename result_of::const_facet_range<ElementT>::type facets(const ElementT & element)
  { return elements< typename result_of::facet_tag<ElementT>::type >(element); }

  /** @brief Function for retrieving a const vertex range object from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A const vertex range
    */
  template<typename SomethingT>
  typename result_of::const_element_range<SomethingT, vertex_tag>::type vertices(SomethingT const & something)
  { return elements<vertex_tag>(something); }

  /** @brief Function for retrieving a const line range object from a host object (same as edges)
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A const line range
    */
  template<typename SomethingT>
  typename result_of::const_element_range<SomethingT, line_tag>::type lines(SomethingT const & something)
  { return elements<line_tag>(something); }

  /** @brief Function for retrieving a const edge range object from a host object (same as lines)
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A const edge range
    */
  template<typename SomethingT>
  typename result_of::const_element_range<SomethingT, edge_tag>::type edges(SomethingT const & something)
  { return elements<edge_tag>(something); }

  /** @brief Function for retrieving a const triangles range object from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A const triangle range
    */
  template<typename SomethingT>
  typename result_of::const_element_range<SomethingT, triangle_tag>::type triangles(SomethingT const & something)
  { return elements<triangle_tag>(something); }

  /** @brief Function for retrieving a const quadrilateral range object from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A const quadrilateral range
    */
  template<typename SomethingT>
  typename result_of::const_element_range<SomethingT, quadrilateral_tag>::type quadrilaterals(SomethingT const & something)
  { return elements<quadrilateral_tag>(something); }

  /** @brief Function for retrieving a const polygon range object from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A const polygon range
    */
  template<typename SomethingT>
  typename result_of::const_element_range<SomethingT, polygon_tag>::type polygons(SomethingT const & something)
  { return elements<polygon_tag>(something); }

  /** @brief Function for retrieving a const PLC range object from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A const PLC range
    */
  template<typename SomethingT>
  typename result_of::const_element_range<SomethingT, plc_tag>::type plcs(SomethingT const & something)
  { return elements<plc_tag>(something); }

  /** @brief Function for retrieving a const tetrahedron range object from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A const tetrahedron range
    */
  template<typename SomethingT>
  typename result_of::const_element_range<SomethingT, tetrahedron_tag>::type tetrahedra(SomethingT const & something)
  { return elements<tetrahedron_tag>(something); }

  /** @brief Function for retrieving a const hexahedron range object from a host object
    *
    * @tparam SomethingT         The host type, can be an element, a collection, a mesh, a segment or a segmentation
    * @param  something          The host object of type SomethingT
    * @return                    A const hexahedron range
    */
  template<typename SomethingT>
  typename result_of::const_element_range<SomethingT, hexahedron_tag>::type hexahedra(SomethingT const & something)
  { return elements<hexahedron_tag>(something); }




  /** @brief Function for creating an element within a mesh or a segment. For PLC use make_plc
    *
    * @tparam ElementTypeOrTagT       The element type/tag to be created
    * @tparam MeshOrSegmentHandleTypeT    The mesh or segment type where the element is created
    * @tparam VertexHandleIteratorT   A vertex handle iterator type
    * @param  mesh_segment            The mesh or segment object where the element should be created
    * @param  array_start             An iterator pointing to the first vertex handle of the element
    * @param  array_end               An iterator defining the end of the vertices
    * @return                         A handle to the created element
    */
  template<typename ElementTypeOrTagT, typename MeshOrSegmentHandleTypeT, typename VertexHandleIteratorT>
  typename result_of::handle<MeshOrSegmentHandleTypeT, ElementTypeOrTagT>::type make_element(
        MeshOrSegmentHandleTypeT & mesh_segment,
        VertexHandleIteratorT array_start,
        VertexHandleIteratorT const & array_end );


  /** @brief Function for creating an element within a mesh or segment with a specific ID. For PLC use make_plc
    *
    * @tparam ElementTypeOrTagT       The element type/tag to be created
    * @tparam MeshOrSegmentHandleTypeT    The mesh or segment type where the element is created
    * @tparam VertexHandleIteratorT   A vertex handle iterator type
    * @param  mesh_segment            The mesh or segment object where the element should be created
    * @param  array_start             An iterator pointing to the first vertex handle of the element
    * @param  array_end               An iterator defining the end of the vertices
    * @param  id                      The id of the new element
    * @return                         A handle to the created element
    */
  template<typename ElementTypeOrTagT, typename MeshOrSegmentHandleTypeT, typename VertexHandleIteratorT, typename IDT>
  typename result_of::handle<MeshOrSegmentHandleTypeT, ElementTypeOrTagT>::type make_element_with_id(
        MeshOrSegmentHandleTypeT & mesh_segment,
        VertexHandleIteratorT array_start,
        VertexHandleIteratorT const & array_end,
        IDT id );

  /** @brief Function for creating a vertex within a mesh or a segment
    *
    * @tparam MeshOrSegmentHandleT    The mesh or segment type where the vertex is created
    * @param  mesh_segment            The mesh or segment object where the vertex should be created
    * @return                         A handle to the created vertex
    */
  template<typename MeshOrSegmentHandleTypeT>
  typename result_of::vertex_handle<MeshOrSegmentHandleTypeT>::type make_vertex(MeshOrSegmentHandleTypeT & mesh_segment);

  /** @brief Function for creating a vertex within a mesh or a segment with a specific point
    *
    * @tparam MeshOrSegmentHandleT    The mesh or segment type where the vertex is created
    * @param  mesh_segment            The mesh or segment object where the vertex should be created
    * @param  point                   The point which corresponds to the created vertex
    * @return                         A handle to the created vertex
    */
  template<typename MeshOrSegmentHandleTypeT>
  typename result_of::vertex_handle<MeshOrSegmentHandleTypeT>::type make_vertex(
        MeshOrSegmentHandleTypeT & mesh_segment,
        typename result_of::point<MeshOrSegmentHandleTypeT>::type const & point);

  /** @brief Function for creating a vertex within a mesh or a segment with a specific point and specific ID
    *
    * @tparam MeshOrSegmentHandleT    The mesh or segment type where the vertex is created
    * @param  mesh_segment            The mesh or segment object where the vertex should be created
    * @param  id                      The id of the new vertex
    * @param  point                   The point which corresponds to the created vertex
    * @return                         A handle to the created vertex
    */
#ifndef _MSC_VER
  template<typename MeshOrSegmentHandleTypeT>
  typename result_of::vertex_handle<MeshOrSegmentHandleTypeT>::type make_vertex_with_id(
        MeshOrSegmentHandleTypeT & mesh_segment,
        typename viennagrid::result_of::element<MeshOrSegmentHandleTypeT, vertex_tag>::type::id_type id,
        typename result_of::point<MeshOrSegmentHandleTypeT>::type const & point);
#endif

  /** @brief Function for creating a unique vertex. The uniqueness is checked by using the point of the vertex: if there is any vertex whose point is close to the point currently inserted, this handle is returned. A new vertex is created otherwise. A classical 2-norm and the tolerance is used for distance checking. The runtime of this function is linear in the vertices within the mesh.
    *
    * @tparam MeshOrSegmentHandleT    The mesh or segment type where the vertex is created
    * @param  mesh_segment            The mesh or segment object where the vertex should be created
    * @param  point                   The point which corresponds to the created vertex
    * @param  tolerance               The tolerance of the 2-norm for checking if two points are equal, is ignored if tolerance is less of equal to zero
    * @return                         A handle to a vertex which is close enough to point or a handle to a newly created vertex
    */
  template<typename MeshOrSegmentHandleTypeT>
  typename result_of::vertex_handle<MeshOrSegmentHandleTypeT>::type make_unique_vertex(
        MeshOrSegmentHandleTypeT & mesh_segment,
        typename result_of::point<MeshOrSegmentHandleTypeT>::type const & point,
        typename result_of::coord<MeshOrSegmentHandleTypeT>::type tolerance);

  /** @brief Function for creating a unique vertex. The uniqueness is checked by using the point of the vertex: if there is any vertex whose point is close to the point currently inserted, this handle is returned. A new vertex is created otherwise. A classical 2-norm and the 2-norm of points as tolerance is used for distance checking. The runtime of this function is linear in the vertices within the mesh.
    *
    * @tparam MeshOrSegmentHandleT    The mesh or segment type where the vertex is created
    * @param  mesh_segment            The mesh or segment object where the vertex should be created
    * @param  p                       The point which corresponds to the created vertex
    * @return                         A handle to a vertex which is close enough to point or a handle to a newly created vertex
    */
  template<typename MeshOrSegmentHandleTypeT>
  typename result_of::vertex_handle<MeshOrSegmentHandleTypeT>::type make_unique_vertex(
        MeshOrSegmentHandleTypeT & mesh_segment,
        typename result_of::point<MeshOrSegmentHandleTypeT>::type const & p);

  /** @brief Function for creating a line within a mesh or a segment (same as make_edge)
    *
    * @tparam MeshOrSegmentHandleT    The mesh or segment type where the line is created
    * @tparam VertexHandleT           The vertex handle type
    * @param  mesh_segment            The mesh or segment object where the line should be created
    * @param  v0                      A handle to the first vertex of the line
    * @param  v1                      A handle to the second vertex of the line
    * @return                         A handle to the created line
    */
  template<typename MeshOrSegmentHandleTypeT, typename VertexHandleT>
  typename result_of::line_handle<MeshOrSegmentHandleTypeT>::type make_line(
        MeshOrSegmentHandleTypeT & mesh_segment,
        VertexHandleT v0, VertexHandleT v1);

  /** @brief Function for creating an edge within a mesh or a segment (same as make_edge)
    *
    * @tparam MeshOrSegmentHandleT    The mesh or segment type where the edge is created
    * @tparam VertexHandleT           The vertex handle type
    * @param  mesh_segment            The mesh or segment object where the edge should be created
    * @param  v0                      A handle to the first vertex of the edge
    * @param  v1                      A handle to the second vertex of the edge
    * @return                         A handle to the created edge
    */
  template<typename MeshOrSegmentHandleTypeT, typename VertexHandleT>
  typename result_of::edge_handle<MeshOrSegmentHandleTypeT>::type make_edge(
        MeshOrSegmentHandleTypeT & mesh_segment,
        VertexHandleT v0, VertexHandleT v1);

  /** @brief Function for creating a triangle within a mesh or a segment
    *
    * @tparam MeshOrSegmentHandleT    The mesh or segment type where the triangle is created
    * @tparam VertexHandleT           The vertex handle type
    * @param  mesh_segment            The mesh or segment object where the triangle should be created
    * @param  v0                      A handle to the first vertex of the triangle
    * @param  v1                      A handle to the second vertex of the triangle
    * @param  v2                      A handle to the third vertex of the triangle
    * @return                         A handle to the created triangle
    */
  template<typename MeshOrSegmentHandleTypeT, typename VertexHandleT>
  typename result_of::triangle_handle<MeshOrSegmentHandleTypeT>::type make_triangle(
        MeshOrSegmentHandleTypeT & mesh_segment,
        VertexHandleT v0, VertexHandleT v1, VertexHandleT v2);

  /** @brief Function for creating a quadrilateral within a mesh or a segment
    *
    * @tparam MeshOrSegmentHandleT    The mesh or segment type where the quadrilateral is created
    * @tparam VertexHandleT           The vertex handle type
    * @param  mesh_segment            The mesh or segment object where the quadrilateral should be created
    * @param  v0                      A handle to the first vertex of the quadrilateral
    * @param  v1                      A handle to the second vertex of the quadrilateral
    * @param  v2                      A handle to the third vertex of the quadrilateral
    * @param  v3                      A handle to the forth vertex of the quadrilateral
    * @return                         A handle to the created quadrilateral
    */
  template<typename MeshOrSegmentHandleTypeT, typename VertexHandleT>
  typename result_of::quadrilateral_handle<MeshOrSegmentHandleTypeT>::type make_quadrilateral(
        MeshOrSegmentHandleTypeT & mesh_segment,
        VertexHandleT v0, VertexHandleT v1, VertexHandleT v2, VertexHandleT v3);

  /** @brief Function for creating a PLC within a mesh or a segment
    *
    * @tparam MeshOrSegmentHandleT    The mesh or segment type where the PLC is created
    * @tparam LineHandleIteratorT     A line handle iterator type
    * @tparam VertexHandleIteratorT   A vertex handle iterator type
    * @tparam PointIteratorT          A point handle iterator type
    * @param  mesh_segment            The mesh or segment object where the PLC should be created
    * @param  lines_begin             An iterator pointing to the first line handle of the PLC
    * @param  lines_end               An iterator defining the end of the lines
    * @param  loose_vertices_begin    An iterator pointing to the first loose vertex handle of the PLC
    * @param  loose_vertices_end      An iterator defining the end of the loose vertices
    * @param  hole_points_begin       An iterator pointing to the first hole point of the PLC
    * @param  hole_points_end         An iterator defining the end of the hole points
    * @return                         A handle to the created PLC
    */
  template<typename MeshOrSegmentHandleTypeT, typename LineHandleIteratorT, typename VertexHandleIteratorT, typename PointIteratorT>
  typename result_of::plc_handle<MeshOrSegmentHandleTypeT>::type make_plc(
        MeshOrSegmentHandleTypeT & mesh_segment,
        LineHandleIteratorT    lines_begin,           LineHandleIteratorT     lines_end,
        VertexHandleIteratorT  loose_vertices_begin,  VertexHandleIteratorT   loose_vertices_end,
        PointIteratorT         hole_points_begin,     PointIteratorT          hole_points_end);

  /** @brief Function for creating a tetrahedron within a mesh or a segment
    *
    * @tparam MeshOrSegmentHandleT    The mesh or segment type where the tetrahedron is created
    * @tparam VertexHandleT           The vertex handle type
    * @param  mesh_segment            The mesh or segment object where the tetrahedron should be created
    * @param  v0                      A handle to the first vertex of the tetrahedron
    * @param  v1                      A handle to the second vertex of the tetrahedron
    * @param  v2                      A handle to the third vertex of the tetrahedron
    * @param  v3                      A handle to the forth vertex of the tetrahedron
    * @return                         A handle to the created tetrahedron
    */
  template<typename MeshOrSegmentHandleTypeT, typename VertexHandleT>
  typename result_of::tetrahedron_handle<MeshOrSegmentHandleTypeT>::type make_tetrahedron(
        MeshOrSegmentHandleTypeT & mesh_segment,
        VertexHandleT v0, VertexHandleT v1, VertexHandleT v2, VertexHandleT v3);

  /** @brief Function for creating a hexahedron within a mesh or a segment
    *
    * @tparam MeshOrSegmentHandleT    The mesh or segment type where the hexahedron is created
    * @tparam VertexHandleT           The vertex handle type
    * @param  mesh_segment            The mesh or segment object where the hexahedron should be created
    * @param  v0                      A handle to the first vertex of the hexahedron
    * @param  v1                      A handle to the second vertex of the hexahedron
    * @param  v2                      A handle to the third vertex of the hexahedron
    * @param  v3                      A handle to the forth vertex of the hexahedron
    * @param  v4                      A handle to the fifth vertex of the hexahedron
    * @param  v5                      A handle to the sixth vertex of the hexahedron
    * @param  v6                      A handle to the seventh vertex of the hexahedron
    * @param  v7                      A handle to the eighth vertex of the hexahedron
    * @return                         A handle to the created hexahedron
    */
  template<typename MeshOrSegmentHandleTypeT, typename VertexHandleT>
  typename result_of::hexahedron_handle<MeshOrSegmentHandleTypeT>::type make_hexahedron(
        MeshOrSegmentHandleTypeT & mesh_segment,
        VertexHandleT v0, VertexHandleT v1, VertexHandleT v2, VertexHandleT v3,
        VertexHandleT v4, VertexHandleT v5, VertexHandleT v6, VertexHandleT v7);

  /** @brief Function for copying an element to a mesh or segment
    *
    * @tparam ElementT                The element type which is copied
    * @tparam MeshOrSegmentHandleT    The mesh or segment type where the element is created
    * @param  element                 The element which is copied
    * @param  mesh_segment            The mesh or segment object where the element is copied to
    * @param  tolerance               An absolute tolerance of the 2-norm for checking if two points are equal. If tolerance is less of equal to zero, no quality check is performed.
    * @return                         A handle to the copied element
    */
  template<typename ElementT, typename MeshOrSegmentHandleT>
  typename viennagrid::result_of::handle<
      MeshOrSegmentHandleT,
      typename viennagrid::result_of::element_tag<ElementT>::type
    >::type copy_element( ElementT const & element, MeshOrSegmentHandleT & mesh_segment,
                          typename viennagrid::result_of::coord<MeshOrSegmentHandleT>::type tolerance );

  /** @brief Function for copying an element to a mesh or segment
    *
    * @tparam ElementT                The element type which is copied
    * @tparam MeshOrSegmentHandleT    The mesh or segment type where the element is created
    * @param  element                 The element which is copied
    * @param  mesh_segment            The mesh or segment object where the element is copied to
    * @return                         A handle to the copied element
    */
  template<typename ElementT, typename MeshOrSegmentHandleT>
  typename viennagrid::result_of::handle<
      MeshOrSegmentHandleT,
      typename viennagrid::result_of::element_tag<ElementT>::type
    >::type copy_element( ElementT const & element, MeshOrSegmentHandleT & mesh_segment );



  /** @brief Function for copying an element iterator range to a mesh or segment
    *
    * @tparam ElementIteratorT            The element iterator type which is copied
    * @tparam OutputMeshOrSegmentHandleT  The mesh or segment type where the elements are created
    * @param  begin                       The begin of the element iterator range of element to be copied
    * @param  end                         The end of the element iterator range of element to be copied
    * @param  output_mesh                 The mesh or segment object where the elements are copied to
    * @param  tolerance                   An absolute tolerance of the 2-norm for checking if two points are equal. If tolerance is less of equal to zero, no quality check is performed.
    */
  template<typename ElementIteratorT, typename OutputMeshOrSegmentHandleT>
  void copy_elements(ElementIteratorT const & begin, ElementIteratorT const & end,
                     OutputMeshOrSegmentHandleT & output_mesh,
                     typename viennagrid::result_of::coord<OutputMeshOrSegmentHandleT>::type tolerance );

  /** @brief Function for copying an element iterator range to a mesh or segment
    *
    * @tparam ElementIteratorT            The element iterator type which is copied
    * @tparam OutputMeshOrSegmentHandleT  The mesh or segment type where the elements are created
    * @param  begin                       The begin of the element iterator range of element to be copied
    * @param  end                         The end of the element iterator range of element to be copied
    * @param  output_mesh                 The mesh or segment object where the elements are copied to
    */
  template<typename ElementIteratorT, typename OutputMeshOrSegmentHandleT>
  void copy_elements(ElementIteratorT const & begin, ElementIteratorT const & end,
                     OutputMeshOrSegmentHandleT & output_mesh );

  /** @brief Function for copying an element handle iterator range to a mesh or segment.
    *
    * @tparam InputMeshOrSegmentHandleT   The mesh or segment type where the original elements live
    * @tparam ElementHandleIteratorT      The element handle iterator type which is copied
    * @tparam OutputMeshOrSegmentHandleT  The mesh or segment type where the elements are created
    * @param  input_mesh                  The mesh or segment object where the original elements live
    * @param  begin                       The begin of element handle the iterator range of element to be copied
    * @param  end                         The end of the element handle iterator range of element to be copied
    * @param  output_mesh                 The mesh or segment object where the elements are copied to
    * @param  tolerance                   An absolute tolerance of the 2-norm for checking if two points are equal. If tolerance is less of equal to zero, no quality check is performed.
    */
  template<typename InputMeshOrSegmentHandleT, typename ElementHandleIteratorT, typename OutputMeshOrSegmentHandleT>
  void copy_element_by_handles(InputMeshOrSegmentHandleT const & input_mesh,
                            ElementHandleIteratorT const & begin, ElementHandleIteratorT const & end,
                            OutputMeshOrSegmentHandleT & output_mesh,
                            typename viennagrid::result_of::coord<OutputMeshOrSegmentHandleT>::type tolerance );

  /** @brief Function for copying an element handle iterator range to a mesh or segment.
    *
    * @tparam InputMeshOrSegmentHandleT   The mesh or segment type where the original elements live
    * @tparam ElementHandleIteratorT      The element handle iterator type which is copied
    * @tparam OutputMeshOrSegmentHandleT  The mesh or segment type where the elements are created
    * @param  input_mesh                  The mesh or segment object where the original elements live
    * @param  begin                       The begin of element handle the iterator range of element to be copied
    * @param  end                         The end of the element handle iterator range of element to be copied
    * @param  output_mesh                 The mesh or segment object where the elements are copied to
    */
  template<typename InputMeshOrSegmentHandleT, typename ElementHandleIteratorT, typename OutputMeshOrSegmentHandleT>
  void copy_element_by_handles(InputMeshOrSegmentHandleT const & input_mesh,
                            ElementHandleIteratorT const & begin, ElementHandleIteratorT const & end,
                            OutputMeshOrSegmentHandleT & output_mesh );


  /** @brief Function for dereferencing an element -> identity
    *
    * @tparam WrappedMeshConfigT      Wrapped config of the mesh type
    * @tparam ElementTagT             Element tag of the element to dereference
    * @tparam WrappedConfigT          Wrapped config of the element to dereference
    * @param  element                 The element to be derferenced, this object is returned
    * @return                         element (identity)
    */
  template<typename WrappedMeshConfigT, typename ElementTagT, typename WrappedConfigT>
  viennagrid::element<ElementTagT, WrappedConfigT> & dereference_handle( viennagrid::mesh<WrappedMeshConfigT> &, viennagrid::element<ElementTagT, WrappedConfigT> & element)
  { return element; }

  /** @brief Function for dereferencing an element -> identity
    *
    * @tparam WrappedMeshConfigT      Wrapped config of the mesh type
    * @tparam ElementTagT             Element tag of the element to dereference
    * @tparam WrappedConfigT          Wrapped config of the element to dereference
    * @param  element                 The element to be derferenced, this object is returned
    * @return                         element (identity)
    */
  template<typename WrappedMeshConfigT, typename ElementTagT, typename WrappedConfigT>
  viennagrid::element<ElementTagT, WrappedConfigT> & dereference_handle( viennagrid::segment_handle<WrappedMeshConfigT> &, viennagrid::element<ElementTagT, WrappedConfigT> & element)
  { return element; }

  /** @brief Function for dereferencing an element -> identity
    *
    * @tparam WrappedMeshConfigT      Wrapped config of the mesh type
    * @tparam ElementTagT             Element tag of the element to dereference
    * @tparam WrappedConfigT          Wrapped config of the element to dereference
    * @param  element                 The element to be derferenced, this object is returned
    * @return                         element (identity)
    */
  template<typename HostElementTagT, typename WrappedHostElementConfigT, typename ElementTagT, typename WrappedConfigT>
  viennagrid::element<ElementTagT, WrappedConfigT> & dereference_handle( viennagrid::element<HostElementTagT, WrappedHostElementConfigT> &, viennagrid::element<ElementTagT, WrappedConfigT> & element)
  { return element; }

  /** @brief Function for dereferencing a const element -> identity
    *
    * @tparam WrappedMeshConfigT      Wrapped config of the mesh type
    * @tparam ElementTagT             Element tag of the element to dereference
    * @tparam WrappedConfigT          Wrapped config of the element to dereference
    * @param  element                 The element to be derferenced, this object is returned
    * @return                         element (identity)
    */
  template<typename WrappedMeshConfigT, typename ElementTagT, typename WrappedConfigT>
  viennagrid::element<ElementTagT, WrappedConfigT> const & dereference_handle( viennagrid::mesh<WrappedMeshConfigT> const &, viennagrid::element<ElementTagT, WrappedConfigT> const & element)
  { return element; }

  /** @brief Function for dereferencing a const element -> identity */
  template<typename WrappedMeshConfigT, typename ElementTagT, typename WrappedConfigT>
  viennagrid::element<ElementTagT, WrappedConfigT> const & dereference_handle( viennagrid::mesh<WrappedMeshConfigT> &, viennagrid::element<ElementTagT, WrappedConfigT> const & element)
  { return element; }

  /** @brief Function for dereferencing a const element -> identity */
  template<typename WrappedMeshConfigT, typename ElementTagT, typename WrappedConfigT>
  viennagrid::element<ElementTagT, WrappedConfigT> const & dereference_handle( viennagrid::mesh<WrappedMeshConfigT> const &, viennagrid::element<ElementTagT, WrappedConfigT> & element)
  { return element; }


  /** @brief Function for dereferencing a const element -> identity */
  template<typename SegmentationT, typename ElementTagT, typename WrappedConfigT>
  viennagrid::element<ElementTagT, WrappedConfigT> const & dereference_handle( viennagrid::segment_handle<SegmentationT> const &, viennagrid::element<ElementTagT, WrappedConfigT> const & element)
  { return element; }

  /** @brief Function for dereferencing a const element -> identity */
  template<typename SegmentationT, typename ElementTagT, typename WrappedConfigT>
  viennagrid::element<ElementTagT, WrappedConfigT> const & dereference_handle( viennagrid::segment_handle<SegmentationT> &, viennagrid::element<ElementTagT, WrappedConfigT> const & element)
  { return element; }

  /** @brief Function for dereferencing an element -> identity */
  template<typename SegmentationT, typename ElementTagT, typename WrappedConfigT>
  viennagrid::element<ElementTagT, WrappedConfigT> const & dereference_handle( viennagrid::segment_handle<SegmentationT> const &, viennagrid::element<ElementTagT, WrappedConfigT> & element)
  { return element; }


  /** @brief Function for dereferencing a const element -> identity */
  template<typename HostElementTagT, typename WrappedHostElementConfigT, typename ElementTagT, typename WrappedConfigT>
  viennagrid::element<ElementTagT, WrappedConfigT> const & dereference_handle( viennagrid::element<HostElementTagT, WrappedHostElementConfigT> const &, viennagrid::element<ElementTagT, WrappedConfigT> const & element)
  { return element; }

  /** @brief Function for dereferencing a const element -> identity */
  template<typename HostElementTagT, typename WrappedHostElementConfigT, typename ElementTagT, typename WrappedConfigT>
  viennagrid::element<ElementTagT, WrappedConfigT> const & dereference_handle( viennagrid::element<HostElementTagT, WrappedHostElementConfigT> &, viennagrid::element<ElementTagT, WrappedConfigT> const & element)
  { return element; }

  /** @brief Function for dereferencing an element -> identity */
  template<typename HostElementTagT, typename WrappedHostElementConfigT, typename ElementTagT, typename WrappedConfigT>
  viennagrid::element<ElementTagT, WrappedConfigT> const & dereference_handle( viennagrid::element<HostElementTagT, WrappedHostElementConfigT> const &, viennagrid::element<ElementTagT, WrappedConfigT> & element)
  { return element; }

  /** @brief Function for creating a handle, default implementation -> identity
    *
    * @tparam MeshOrSegmentHandleT    Wrapped config of the mesh type
    * @tparam HandleT                 Type of the handle
    * @param  handle                  The handle object
    * @return                         handle (identity)
    */
  template<typename MeshOrSegmentHandleT, typename HandleT>
  HandleT handle( MeshOrSegmentHandleT &, HandleT handle) { return handle; }

  /** @brief Function for creating a const handle, default implementation -> identity
    *
    * @tparam MeshOrSegmentHandleT    Wrapped config of the mesh type
    * @tparam HandleT                 Type of the handle
    * @param  handle                  The handle object
    * @return                         handle (identity)
    */
  template<typename MeshOrSegmentHandleT, typename HandleT>
  const HandleT handle( MeshOrSegmentHandleT const &, HandleT handle) { return handle; }

  template<typename MeshT, typename MeshViewT, typename HandleT>
  void mark_referencing_elements( MeshT & mesh_obj, MeshViewT & element_view, HandleT host_element );




  /** @brief Proxy object for a mesh. This is used for wrapping a mesh/mesh view when creating a view
    *
    * @tparam MeshT    The mesh/mesh view type
    */
  template<typename MeshT>
  struct mesh_proxy
  {
    mesh_proxy( MeshT & mesh_obj ) : mesh_obj_(&mesh_obj){}
    MeshT * mesh_obj_;
  };

  /** @brief Creates a view out of a mesh using the mesh_proxy object
    *
    * @tparam MeshOrSegmentHandleT    The mesh or segment type from which the mesh view is created
    * @param  mesh_obj                The mesh or segment object from which the mesh view is created
    * @return                         A mesh_proxy object holding the host mesh/segment object, can be assigned to a mesh_t object
    */
  template<typename WrappedConfigT>
  mesh_proxy< viennagrid::mesh<WrappedConfigT> > make_view(viennagrid::mesh<WrappedConfigT> & mesh_obj)
  {
    return mesh_proxy< viennagrid::mesh<WrappedConfigT> >( mesh_obj );
  }

  /** @brief Creates an empty view out of a segment. */
  template<typename SegmentationT>
  mesh_proxy< typename SegmentationT::view_type > make_view(segment_handle<SegmentationT> & segment);


  // norm tags for: algorithm/norm.hpp
  /** @brief Tag for denoting the 1-norm */
  struct one_norm_tag {};
  /** @brief Tag for denoting the 2-norm */
  struct two_norm_tag {};
  /** @brief Tag for denoting the infinity-norm */
  struct inf_norm_tag {};

  /** @brief Types for cell normals in algorithm/cell_normals.hpp (to be added in a future release) */
  struct seg_cell_normal_tag {};

  /** @brief Data type for cell normals in algorithm/cell_normals.hpp (to be added in a future release) */
  struct seg_cell_normal_data {
    typedef viennagrid::spatial_point<double, cartesian_cs<3> >         point_type;
    typedef std::map<std::size_t, point_type>    type;
  };


  namespace detail
  {
    /** @brief Helper struct for element refinement */
    template <typename ElementTagT>
    struct element_refinement;
  }
}

#endif
