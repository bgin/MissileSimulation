#ifndef VIENNAGRID_MESH_DEFAULT_CONFIGS_HPP
#define VIENNAGRID_MESH_DEFAULT_CONFIGS_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */


#include "viennagrid/mesh/segmentation.hpp"
#include "viennagrid/mesh/mesh.hpp"
#include "viennagrid/topology/simplex.hpp"
#include "viennagrid/topology/quadrilateral.hpp"
#include "viennagrid/topology/polygon.hpp"
#include "viennagrid/topology/hexahedron.hpp"
#include "viennagrid/topology/plc.hpp"

/** @file viennagrid/config/default_configs.hpp
    @brief Provides default configuration classes for meshs
*/

namespace viennagrid
{
  ////////////////// topologically 1d meshs ///////////////////

  namespace config
  {
    /** @brief Point type with cartesian coordinate system in 1d */
    typedef viennagrid::spatial_point<double, viennagrid::cartesian_cs<1> > point_type_1d;
    /** @brief Point type with cartesian coordinate system in 2d */
    typedef viennagrid::spatial_point<double, viennagrid::cartesian_cs<2> > point_type_2d;
    /** @brief Point type with cartesian coordinate system in 3d */
    typedef viennagrid::spatial_point<double, viennagrid::cartesian_cs<3> > point_type_3d;
  }


  namespace config
  {
    /** @brief A default config for vertices in 1d, pointer handles are used */
    struct vertex_1d
    {
      typedef result_of::full_mesh_config< viennagrid::vertex_tag, point_type_1d, viennagrid::pointer_handle_tag >::type type;
    };

    /** @brief A default config for vertices in 2d, pointer handles are used */
    struct vertex_2d
    {
      typedef result_of::full_mesh_config< viennagrid::vertex_tag, point_type_2d, viennagrid::pointer_handle_tag >::type type;
    };

    /** @brief A default config for vertices in 3d, pointer handles are used */
    struct vertex_3d
    {
      typedef result_of::full_mesh_config< viennagrid::vertex_tag, point_type_3d, viennagrid::pointer_handle_tag >::type type;
    };
  }


  /** @brief A default mesh for vertices in 1d, default config is used */
  typedef viennagrid::mesh< config::vertex_1d >                                       vertex_1d_mesh;
  /** @brief A default segmentation for vertices in 1d, default config is used */
  typedef viennagrid::result_of::segmentation< vertex_1d_mesh >::type                 vertex_1d_segmentation;
  /** @brief A default segment for vertices in 1d, default config is used */
  typedef viennagrid::result_of::segment_handle< vertex_1d_segmentation >::type       vertex_1d_segment_handle;
  /** @brief A default mesh view for vertices in 1d, default config is used */
  typedef viennagrid::result_of::mesh_view< vertex_1d_mesh >::type                    vertex_1d_view;
  /** @brief A default cell for vertices in 1d, default config is used */
  typedef viennagrid::result_of::cell<vertex_1d_mesh>::type                           vertex_1d_cell;

  /** @brief A default mesh for vertices in 2d, default config is used */
  typedef viennagrid::mesh< config::vertex_2d >                                       vertex_2d_mesh;
  /** @brief A default segmentation for vertices in 2d, default config is used */
  typedef viennagrid::result_of::segmentation< vertex_2d_mesh >::type                 vertex_2d_segmentation;
  /** @brief A default segment for vertices in 2d, default config is used */
  typedef viennagrid::result_of::segment_handle< vertex_2d_segmentation >::type       vertex_2d_segment_handle;
  /** @brief A default mesh view for vertices in 2d, default config is used */
  typedef viennagrid::result_of::mesh_view< vertex_2d_mesh >::type                    vertex_2d_view;
  /** @brief A default cell for vertices in 2d, default config is used */
  typedef viennagrid::result_of::cell<vertex_2d_mesh>::type                           vertex_2d_cell;

  /** @brief A default mesh for vertices in 3d, default config is used */
  typedef viennagrid::mesh< config::vertex_3d >                                       vertex_3d_mesh;
  /** @brief A default segmentation for vertices in 3d, default config is used */
  typedef viennagrid::result_of::segmentation< vertex_3d_mesh >::type                 vertex_3d_segmentation;
  /** @brief A default segment for vertices in 3d, default config is used */
  typedef viennagrid::result_of::segment_handle< vertex_3d_segmentation >::type       vertex_3d_segment_handle;
  /** @brief A default mesh view for vertices in 3d, default config is used */
  typedef viennagrid::result_of::mesh_view< vertex_3d_mesh >::type                    vertex_3d_view;
  /** @brief A default cell for vertices in 3d, default config is used */
  typedef viennagrid::result_of::cell<vertex_3d_mesh>::type                           vertex_3d_cell;


  namespace config
  {
    // topologically 1d meshs (cell type is line)

    /** @brief A default config for lines in 1d, pointer handles are used */
    struct line_1d
    {
      typedef result_of::full_mesh_config< viennagrid::line_tag, point_type_1d, viennagrid::pointer_handle_tag >::type type;
    };

    /** @brief A default config for lines in 2d, pointer handles are used */
    struct line_2d
    {
      typedef result_of::full_mesh_config< viennagrid::line_tag, point_type_2d, viennagrid::pointer_handle_tag >::type type;
    };

    /** @brief A default config for lines in 3d, pointer handles are used */
    struct line_3d
    {
      typedef result_of::full_mesh_config< viennagrid::line_tag, point_type_3d, viennagrid::pointer_handle_tag >::type type;
    };
  }

  /** @brief A default mesh for lines in 1d, default config is used */
  typedef viennagrid::mesh< config::line_1d >                                       line_1d_mesh;
  /** @brief A default segmentation for lines in 1d, default config is used */
  typedef viennagrid::result_of::segmentation< line_1d_mesh >::type                 line_1d_segmentation;
  /** @brief A default segment for lines in 1d, default config is used */
  typedef viennagrid::result_of::segment_handle< line_1d_segmentation >::type       line_1d_segment_handle;
  /** @brief A default mesh view for lines in 1d, default config is used */
  typedef viennagrid::result_of::mesh_view< line_1d_mesh >::type                    line_1d_view;
  /** @brief A default cell for lines in 1d, default config is used */
  typedef viennagrid::result_of::cell<line_1d_mesh>::type                           line_1d_cell;

  /** @brief A thin segmentation for lines including only cells in 1d, thin config is used */
  typedef viennagrid::result_of::cell_only_segmentation< line_1d_mesh >::type  cell_only_line_1d_segmentation;
  /** @brief A thin segment for lines including only cells in 1d, thin config is used */
  typedef viennagrid::result_of::segment_handle< cell_only_line_1d_segmentation >::type  cell_only_line_1d_segment_handle;


  /** @brief A default mesh for lines in 2d, default config is used */
  typedef viennagrid::mesh< config::line_2d >                                       line_2d_mesh;
  /** @brief A default segmentation for lines in 2d, default config is used */
  typedef viennagrid::result_of::segmentation< line_2d_mesh >::type                 line_2d_segmentation;
  /** @brief A default segment for lines in 2d, default config is used */
  typedef viennagrid::result_of::segment_handle< line_2d_segmentation >::type       line_2d_segment_handle;
  /** @brief A default mesh view for lines in 2d, default config is used */
  typedef viennagrid::result_of::mesh_view< line_2d_mesh >::type                    line_2d_view;
  /** @brief A default cell for lines in 2d, default config is used */
  typedef viennagrid::result_of::cell<line_2d_mesh>::type                           line_2d_cell;

  /** @brief A thin segmentation for lines including only cells in 2d, thin config is used */
  typedef viennagrid::result_of::cell_only_segmentation< line_2d_mesh >::type  cell_only_line_2d_segmentation;
  /** @brief A thin segment for lines including only cells in 2d, thin config is used */
  typedef viennagrid::result_of::segment_handle< cell_only_line_2d_segmentation >::type  cell_only_line_2d_segment_handle;


  /** @brief A default mesh for lines in 3d, default config is used */
  typedef viennagrid::mesh< config::line_3d >                                       line_3d_mesh;
  /** @brief A default segmentation for lines in 3d, default config is used */
  typedef viennagrid::result_of::segmentation< line_3d_mesh >::type                 line_3d_segmentation;
  /** @brief A default segment for lines in 3d, default config is used */
  typedef viennagrid::result_of::segment_handle< line_3d_segmentation >::type       line_3d_segment_handle;
  /** @brief A default mesh view for lines in 3d, default config is used */
  typedef viennagrid::result_of::mesh_view< line_3d_mesh >::type                    line_3d_view;
  /** @brief A default cell for lines in 3d, default config is used */
  typedef viennagrid::result_of::cell<line_3d_mesh>::type                           line_3d_cell;

  /** @brief A thin segmentation for lines including only cells in 3d, thin config is used */
  typedef viennagrid::result_of::cell_only_segmentation< line_3d_mesh >::type  cell_only_line_3d_segmentation;
  /** @brief A thin segment for lines including only cells in 3d, thin config is used */
  typedef viennagrid::result_of::segment_handle< cell_only_line_3d_segmentation >::type  cell_only_line_3d_segment_handle;


  ////////////////// topologically 2d meshs ///////////////////

  namespace config
  {

    /** @brief A default config for triangles in 2d, pointer handles are used */
    struct triangular_2d
    {
      typedef result_of::full_mesh_config< viennagrid::triangle_tag, point_type_2d, viennagrid::pointer_handle_tag >::type     type;
    };

    /** @brief A minimal configuration for triangles in 2d, no facts/edges */
    struct thin_triangular_2d
    {
      typedef result_of::thin_mesh_config< viennagrid::triangle_tag, point_type_2d, viennagrid::pointer_handle_tag >::type  type;
    };


    /** @brief A default config for triangles in 3d, pointer handles are used */
    struct triangular_3d
    {
      typedef result_of::full_mesh_config< viennagrid::triangle_tag, point_type_3d, viennagrid::pointer_handle_tag >::type     type;
    };

    /** @brief A minimal configuration for triangles in 3d, no facts/edges */
    struct thin_triangular_3d
    {
      typedef result_of::thin_mesh_config< viennagrid::triangle_tag, point_type_3d, viennagrid::pointer_handle_tag >::type  type;
    };

    /** @brief A default config for quadrilaterals in 2d, pointer handles are used */
    struct quadrilateral_2d
    {
      typedef result_of::full_mesh_config< viennagrid::quadrilateral_tag, point_type_2d, viennagrid::pointer_handle_tag >::type     type;
    };

    /** @brief A minimal configuration for quadrilaterals in 2d, no facts/edges */
    struct thin_quadrilateral_2d
    {
      typedef result_of::thin_mesh_config< viennagrid::quadrilateral_tag, point_type_2d, viennagrid::pointer_handle_tag >::type     type;
    };

    /** @brief A default config for quadrilaterals in 3d, pointer handles are used */
    struct quadrilateral_3d
    {
      typedef result_of::full_mesh_config< viennagrid::quadrilateral_tag, point_type_3d, viennagrid::pointer_handle_tag >::type     type;
    };

    /** @brief A minimal configuration for quadrilaterals in 3d, no facts/edges */
    struct thin_quadrilateral_3d
    {
      typedef result_of::thin_mesh_config< viennagrid::quadrilateral_tag, point_type_3d, viennagrid::pointer_handle_tag >::type     type;
    };

    /** @brief A default config for polygons in 2d, pointer handles are used */
    struct polygonal_2d
    {
      typedef result_of::full_mesh_config< viennagrid::polygon_tag, point_type_2d, viennagrid::pointer_handle_tag >::type     type;
    };

    /** @brief A default config for polygons in 3d, pointer handles are used */
    struct polygonal_3d
    {
      typedef result_of::full_mesh_config< viennagrid::polygon_tag, point_type_3d, viennagrid::pointer_handle_tag >::type     type;
    };

//     /** @brief A default config for PLCs in 2d, pointer handles are used */
//     struct plc_2d
//     {
//       typedef result_of::full_mesh_config< viennagrid::plc_tag, point_type_2d, viennagrid::pointer_handle_tag >::type     type;
//     };

    /** @brief A default config for PLCs in 3d, pointer handles are used */
    struct plc_3d
    {
      typedef result_of::full_mesh_config< viennagrid::plc_tag, point_type_3d, viennagrid::pointer_handle_tag >::type     type;
    };
  }


  /** @brief A default mesh for triangles in 2d, default config is used */
  typedef viennagrid::mesh< config::triangular_2d >                                       triangular_2d_mesh;
  /** @brief A default segmentation for triangles in 2d, default config is used */
  typedef viennagrid::result_of::segmentation< triangular_2d_mesh >::type                 triangular_2d_segmentation;
  /** @brief A default segment for triangles in 2d, default config is used */
  typedef viennagrid::result_of::segment_handle< triangular_2d_segmentation >::type       triangular_2d_segment_handle;
  /** @brief A default mesh view for triangles in 2d, default config is used */
  typedef viennagrid::result_of::mesh_view< triangular_2d_mesh >::type                    triangular_2d_view;
  /** @brief A default cell for triangles in 2d, default config is used */
  typedef viennagrid::result_of::cell<triangular_2d_mesh>::type                           triangular_2d_cell;

  /** @brief A thin mesh for triangles in 2d, thin config is used */
  typedef viennagrid::mesh< config::thin_triangular_2d >                                  thin_triangular_2d_mesh;
  /** @brief A thin segmentation for triangles in 2d, thin config is used */
  typedef viennagrid::result_of::segmentation< thin_triangular_2d_mesh >::type            thin_triangular_2d_segmentation;
  /** @brief A thin segment for triangles in 2d, thin config is used */
  typedef viennagrid::result_of::segment_handle< thin_triangular_2d_segmentation >::type  thin_triangular_2d_segment_handle;
  /** @brief A thin mesh view for triangles in 2d, thin config is used */
  typedef viennagrid::result_of::mesh_view< thin_triangular_2d_mesh >::type               thin_triangular_2d_view;
  /** @brief A thin cell for triangles in 2d, thin config is used */
  typedef viennagrid::result_of::cell<thin_triangular_2d_mesh>::type                      thin_triangular_2d_cell;

  /** @brief A thin segmentation for triangles including only cells in 2d, thin config is used */
  typedef viennagrid::result_of::cell_only_segmentation< thin_triangular_2d_mesh >::type  thin_cell_only_triangular_2d_segmentation;
  /** @brief A thin segment for triangles including only cells in 2d, thin config is used */
  typedef viennagrid::result_of::segment_handle< thin_cell_only_triangular_2d_segmentation >::type  thin_cell_only_triangular_2d_segment_handle;





  /** @brief A default mesh for triangles in 3d, default config is used */
  typedef viennagrid::mesh< config::triangular_3d >                                         triangular_3d_mesh;
  /** @brief A default segmentation for triangles in 3d, default config is used */
  typedef viennagrid::result_of::segmentation< triangular_3d_mesh >::type                   triangular_3d_segmentation;
  /** @brief A default segment for triangles in 3d, default config is used */
  typedef viennagrid::result_of::segment_handle< triangular_3d_segmentation >::type         triangular_3d_segment_handle;
  /** @brief An oriented hull segmentation for triangles in 3d, default config is used */
  typedef viennagrid::result_of::oriented_3d_hull_segmentation< triangular_3d_mesh >::type  triangular_hull_3d_segmentation;
  /** @brief An oriented hull segmentat for triangles in 3d, default config is used */
  typedef viennagrid::result_of::segment_handle< triangular_hull_3d_segmentation >::type    triangular_hull_3d_segment_handle;
  /** @brief A default mesh view for triangles in 3d, default config is used */
  typedef viennagrid::result_of::mesh_view< triangular_3d_mesh >::type                      triangular_3d_view;
  /** @brief A default cell for triangles in 3d, default config is used */
  typedef viennagrid::result_of::cell<triangular_3d_mesh>::type                             triangular_3d_cell;



  /** @brief A thin mesh for triangles in 3d, thin config is used */
  typedef viennagrid::mesh< config::thin_triangular_3d >                                  thin_triangular_3d_mesh;
  /** @brief A thin segmentation for triangles in 3d, thin config is used */
  typedef viennagrid::result_of::segmentation< thin_triangular_3d_mesh >::type            thin_triangular_3d_segmentation;
  /** @brief A thin segment for triangles in 3d, thin config is used */
  typedef viennagrid::result_of::segment_handle< thin_triangular_3d_segmentation >::type  thin_triangular_3d_segment_handle;
  /** @brief An oriented hull segmentation for triangles in 3d, thin config is used */
  typedef viennagrid::result_of::oriented_3d_hull_segmentation< thin_triangular_3d_mesh >::type  thin_triangular_hull_3d_segmentation;
  /** @brief An oriented hull segmentat for triangles in 3d, thin config is used */
  typedef viennagrid::result_of::segment_handle< thin_triangular_hull_3d_segmentation >::type    thin_triangular_hull_3d_segment_handle;
  /** @brief A thin mesh view for triangles in 3d, thin config is used */
  typedef viennagrid::result_of::mesh_view< thin_triangular_3d_mesh >::type               thin_triangular_3d_view;
  /** @brief A thin cell for triangles in 3d, thin config is used */
  typedef viennagrid::result_of::cell<thin_triangular_3d_mesh>::type                      thin_triangular_3d_cell;

  /** @brief A thin segmentation for triangles including only cells in 3d, thin config is used */
  typedef viennagrid::result_of::cell_only_segmentation< thin_triangular_3d_mesh >::type  thin_cell_only_triangular_3d_segmentation;
  /** @brief A thin segment for triangles including only cells in 3d, thin config is used */
  typedef viennagrid::result_of::segment_handle< thin_cell_only_triangular_3d_segmentation >::type  thin_cell_only_triangular_3d_segment_handle;





  /** @brief A default mesh for quadrilaterals in 2d, default config is used */
  typedef viennagrid::mesh< config::quadrilateral_2d >                                       quadrilateral_2d_mesh;
  /** @brief A default segmentation for quadrilaterals in 2d, default config is used */
  typedef viennagrid::result_of::segmentation< quadrilateral_2d_mesh >::type                 quadrilateral_2d_segmentation;
  /** @brief A default segment for quadrilaterals in 2d, default config is used */
  typedef viennagrid::result_of::segment_handle< quadrilateral_2d_segmentation >::type       quadrilateral_2d_segment_handle;
  /** @brief A default mesh view for quadrilaterals in 2d, default config is used */
  typedef viennagrid::result_of::mesh_view< quadrilateral_2d_mesh >::type                    quadrilateral_2d_view;
  /** @brief A default cell for quadrilaterals in 2d, default config is used */
  typedef viennagrid::result_of::cell<quadrilateral_2d_mesh>::type                           quadrilateral_2d_cell;

  /** @brief A default mesh for quadrilaterals in 3d, default config is used */
  typedef viennagrid::mesh< config::quadrilateral_3d >                                       quadrilateral_3d_mesh;
  /** @brief A default segmentation for quadrilaterals in 3d, default config is used */
  typedef viennagrid::result_of::segmentation< quadrilateral_3d_mesh >::type                 quadrilateral_3d_segmentation;
  /** @brief A default segment for quadrilaterals in 3d, default config is used */
  typedef viennagrid::result_of::segment_handle< quadrilateral_3d_segmentation >::type       quadrilateral_3d_segment_handle;
  /** @brief A default mesh view for quadrilaterals in 3d, default config is used */
  typedef viennagrid::result_of::mesh_view< quadrilateral_3d_mesh >::type                    quadrilateral_3d_view;
  /** @brief A default cell for quadrilaterals in 3d, default config is used */
  typedef viennagrid::result_of::cell<quadrilateral_3d_mesh>::type                           quadrilateral_3d_cell;


  /** @brief A default mesh for polygons in 2d, default config is used */
  typedef viennagrid::mesh< config::polygonal_2d >                                       polygonal_2d_mesh;
  /** @brief A default segmentation for polygons in 2d, default config is used */
  typedef viennagrid::result_of::segmentation< polygonal_2d_mesh >::type                 polygonal_2d_segmentation;
  /** @brief A default segment for polygons in 2d, default config is used */
  typedef viennagrid::result_of::segment_handle< polygonal_2d_segmentation >::type       polygonal_2d_segment_handle;
  /** @brief A default mesh view for polygons in 2d, default config is used */
  typedef viennagrid::result_of::mesh_view< polygonal_2d_mesh >::type                    polygonal_2d_view;
  /** @brief A default cell for polygons in 2d, default config is used */
  typedef viennagrid::result_of::cell<polygonal_2d_mesh>::type                           polygonal_2d_cell;

  /** @brief A default mesh for polygons in 3d, default config is used */
  typedef viennagrid::mesh< config::polygonal_3d >                                       polygonal_3d_mesh;
  /** @brief A default segmentation for polygons in 3d, default config is used */
  typedef viennagrid::result_of::segmentation< polygonal_3d_mesh >::type                 polygonal_3d_segmentation;
  /** @brief A default segment for polygons in 3d, default config is used */
  typedef viennagrid::result_of::segment_handle< polygonal_3d_segmentation >::type       polygonal_3d_segment_handle;
  /** @brief A default mesh view for polygons in 3d, default config is used */
  typedef viennagrid::result_of::mesh_view< polygonal_3d_mesh >::type                    polygonal_3d_view;
  /** @brief A default cell for polygons in 3d, default config is used */
  typedef viennagrid::result_of::cell<polygonal_3d_mesh>::type                           polygonal_3d_cell;

  /** @brief A default mesh for PLCs in 3d, default config is used */
  typedef viennagrid::mesh< config::plc_3d >                                         plc_3d_mesh;
  /** @brief A default segmentation for PLCs in 3d, default config is used */
  typedef viennagrid::result_of::segmentation< plc_3d_mesh >::type                   plc_3d_segmentation;
  /** @brief A default segment for PLCs in 3d, default config is used */
  typedef viennagrid::result_of::segment_handle< plc_3d_segmentation >::type         plc_3d_segment_handle;
  /** @brief A default mesh view for PLCs in 3d, default config is used */
  typedef viennagrid::result_of::mesh_view< plc_3d_mesh >::type                      plc_3d_view;
  /** @brief A default cell for PLCs in 3d, default config is used */
  typedef viennagrid::result_of::cell<plc_3d_mesh>::type                             plc_3d_cell;



  ////////////////// topologically 3d meshs ///////////////////

  namespace config
  {
    /** @brief A default config for tetrahedrons in 3d, pointer handles are used */
    struct tetrahedral_3d
    {
      typedef result_of::full_mesh_config< viennagrid::tetrahedron_tag, point_type_3d, viennagrid::pointer_handle_tag >::type  type;
    };

    /** @brief A minimal configuration for tetrahedra in 3d, no facts or edges */
    struct thin_tetrahedral_3d
    {
      typedef result_of::thin_mesh_config< viennagrid::tetrahedron_tag, point_type_3d, viennagrid::pointer_handle_tag >::type  type;
    };

    /** @brief A default config for hexahedrons in 3d, pointer handles are used */
    struct hexahedral_3d
    {
      typedef result_of::full_mesh_config< viennagrid::hexahedron_tag, point_type_3d, viennagrid::pointer_handle_tag >::type   type;
    };

    /** @brief A minimal configuration for hexahedra in 3d, no facts or edges */
    struct thin_hexahedral_3d
    {
      typedef result_of::thin_mesh_config< viennagrid::hexahedron_tag, point_type_3d, viennagrid::pointer_handle_tag >::type   type;
    };
  }

  /** @brief A default mesh for tetrahedrons in 3d, default config is used */
  typedef viennagrid::mesh< config::tetrahedral_3d >                                       tetrahedral_3d_mesh;
  /** @brief A default segmentation for tetrahedrons in 3d, default config is used */
  typedef viennagrid::result_of::segmentation< tetrahedral_3d_mesh >::type                 tetrahedral_3d_segmentation;
  /** @brief A default segment for tetrahedrons in 3d, default config is used */
  typedef viennagrid::result_of::segment_handle< tetrahedral_3d_segmentation >::type       tetrahedral_3d_segment_handle;
  /** @brief A default mesh view for tetrahedrons in 3d, default config is used */
  typedef viennagrid::result_of::mesh_view< tetrahedral_3d_mesh >::type                    tetrahedral_3d_view;
  /** @brief A default cell for tetrahedrons in 3d, default config is used */
  typedef viennagrid::result_of::cell<tetrahedral_3d_mesh>::type                           tetrahedral_3d_cell;


  /** @brief A thin mesh for tetrahedrons in 3d, thin config is used */
  typedef viennagrid::mesh< config::thin_tetrahedral_3d >                                  thin_tetrahedral_3d_mesh;
  /** @brief A thin segmentation for tetrahedrons in 3d, thin config is used */
  typedef viennagrid::result_of::segmentation< thin_tetrahedral_3d_mesh >::type            thin_tetrahedral_3d_segmentation;
  /** @brief A thin segment for tetrahedrons in 3d, thin config is used */
  typedef viennagrid::result_of::segment_handle< thin_tetrahedral_3d_segmentation >::type  thin_tetrahedral_3d_segment_handle;
  /** @brief A thin mesh view for tetrahedrons in 3d, thin config is used */
  typedef viennagrid::result_of::mesh_view< thin_tetrahedral_3d_mesh >::type               thin_tetrahedral_3d_view;
  /** @brief A thin cell for tetrahedrons in 3d, thin config is used */
  typedef viennagrid::result_of::cell<thin_tetrahedral_3d_mesh>::type                      thin_tetrahedral_3d_cell;

  /** @brief A thin segmentation for tetrahedrons including only cells in 3d, thin config is used */
  typedef viennagrid::result_of::cell_only_segmentation< thin_tetrahedral_3d_mesh >::type  thin_cell_only_tetrahedral_3d_segmentation;
  /** @brief A thin segment for tetrahedrons including only cells in 3d, thin config is used */
  typedef viennagrid::result_of::segment_handle< thin_cell_only_tetrahedral_3d_segmentation >::type  thin_cell_only_tetrahedral_3d_segment_handle;


  /** @brief A default mesh for hexahedrons in 3d, default config is used */
  typedef viennagrid::mesh< config::hexahedral_3d >                                         hexahedral_3d_mesh;
  /** @brief A default segmentation for hexahedrons in 3d, default config is used */
  typedef viennagrid::result_of::segmentation< hexahedral_3d_mesh >::type                   hexahedral_3d_segmentation;
  /** @brief A default segment for hexahedrons in 3d, default config is used */
  typedef viennagrid::result_of::segment_handle< hexahedral_3d_segmentation >::type         hexahedral_3d_segment_handle;
  /** @brief A default mesh view for hexahedrons in 3d, default config is used */
  typedef viennagrid::result_of::mesh_view< hexahedral_3d_mesh >::type                      hexahedral_3d_view;
  /** @brief A default cell for hexahedrons in 3d, default config is used */
  typedef viennagrid::result_of::cell<hexahedral_3d_mesh>::type                             hexahedral_3d_cell;





  /** @brief A default mesh for a boundary representation in 1d: vertex 1d */
  typedef vertex_1d_mesh                                                                    brep_1d_mesh;
  /** @brief A segmentation for a boundary representation in 1d: vertex 1d */
  typedef vertex_1d_segmentation                                                            brep_1d_segmentation;
  /** @brief A segment for a boundary representation in 1d: vertex 1d */
  typedef vertex_1d_segment_handle                                                          brep_1d_segment_handle;
  /** @brief A default view for a boundary representation in 1d: vertex 1d */
  typedef vertex_1d_view                                                                    brep_1d_view;
  /** @brief A default cell for a boundary representation in 1d: vertex 1d */
  typedef vertex_1d_cell                                                                    brep_1d_cell;

  /** @brief A default mesh for a boundary representation in 2d: line 2d */
  typedef line_2d_mesh                                                                      brep_2d_mesh;
  /** @brief A segmentation for a boundary representation in 2d: line 2d */
  typedef line_2d_segmentation                                                              brep_2d_segmentation;
  /** @brief A segment for a boundary representation in 2d: line 2d */
  typedef line_2d_segment_handle                                                            brep_2d_segment_handle;
  /** @brief A default view for a boundary representation in 2d: line 2d */
  typedef line_2d_view                                                                      brep_2d_view;
  /** @brief A default cell for a boundary representation in 2d: line 2d */
  typedef line_2d_cell                                                                      brep_2d_cell;

  /** @brief A default mesh for a boundary representation in 3d: plc 3d */
  typedef plc_3d_mesh                                                                       brep_3d_mesh;
  /** @brief A segmentation for a boundary representation in 3d: plc 3d */
  typedef plc_3d_segmentation                                                               brep_3d_segmentation;
  /** @brief A segment for a boundary representation in 3d: plc 3d */
  typedef plc_3d_segment_handle                                                             brep_3d_segment_handle;
  /** @brief A default view for a boundary representation in 3d: plc 3d */
  typedef plc_3d_view                                                                       brep_3d_view;
  /** @brief A default cell for a boundary representation in 3d: plc 3d */
  typedef plc_3d_cell                                                                       brep_3d_cell;
}


#endif
