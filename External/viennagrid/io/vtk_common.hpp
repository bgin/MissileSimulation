#ifndef VIENNAGRID_IO_VTK_COMMON_HPP
#define VIENNAGRID_IO_VTK_COMMON_HPP

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
#include "viennagrid/io/helper.hpp"
#include "viennagrid/topology/all.hpp"
#include "viennagrid/forwards.hpp"

/** @file viennagrid/io/vtk_common.hpp
    @brief Provides common things for VTK reader and writer
*/

namespace viennagrid
{
  namespace io
  {
    namespace detail
    {
      /** @brief Translates element tags to VTK type identifiers
       *
       * see http://www.vtk.org/VTK/img/file-formats.pdf, Figure 2, for an overview
       *
       * @tparam ElementTag    The tag identifying the n-cell type
       */
      template <typename ElementTag>
      struct ELEMENT_TAG_TO_VTK_TYPE
      {
        static const int value = ElementTag::ERROR_ELEMENT_TYPE_NOT_SUPPORTED;
      };

      /** @brief Specialization for a hexahedron */
      template <>
      struct ELEMENT_TAG_TO_VTK_TYPE<hexahedron_tag>
      {
        static const int value = 12;
      };

      /** @brief Specialization for a tetrahedron */
      template <>
      struct ELEMENT_TAG_TO_VTK_TYPE<tetrahedron_tag>
      {
        static const int value = 10;
      };

      /** @brief Specialization for a quadrilateral */
      template <>
      struct ELEMENT_TAG_TO_VTK_TYPE<quadrilateral_tag>
      {
        static const int value = 9;
      };

      /** @brief Specialization for a triangle */
      template <>
      struct ELEMENT_TAG_TO_VTK_TYPE<triangle_tag>
      {
        static const int value = 5;
      };

      /** @brief Specialization for a line (one-dimensional hypercube) */
      template <>
      struct ELEMENT_TAG_TO_VTK_TYPE<hypercube_tag<1> >
      {
        static const int value = 3;
      };

      /** @brief Specialization for a line (one-dimensional simplex) */
      template <>
      struct ELEMENT_TAG_TO_VTK_TYPE<simplex_tag<1> >
      {
        static const int value = 3;
      };

      /** @brief Tranformations of reference orientations from VTK to ViennaGrid
       *
       * While nothing needs to be done for simplices, hypercubes are oriented differently.
       */
      template <typename CellTag>
      struct vtk_to_viennagrid_orientations
      {
        std::size_t operator()(std::size_t j) const { return j; }  //default case: do nothing
      };

      /** @brief Tranformations of reference orientations from ViennaGrid to VTK
       *
       * While nothing needs to be done for simplices, hypercubes are oriented differently.
       */
      template <typename CellTag>
      struct viennagrid_to_vtk_orientations
      {
        std::size_t operator()(std::size_t j) const { return j; }  //default case: do nothing
      };

      /** @brief Specialization for quadrilaterals: Switch vertices 2 and 3 */
      template <>
      struct vtk_to_viennagrid_orientations<quadrilateral_tag>
      {
        std::size_t operator()(std::size_t j) const
        {
          switch (j)
          {
            case 2: return 3;
            case 3: return 2;
            default: return j;
          }
          //return j;  //unreachable code
        }
      };

      /** @brief Specialization for quadrilaterals: Switch vertices 2 and 3 */
      template <>
      struct viennagrid_to_vtk_orientations<quadrilateral_tag>
      {
        std::size_t operator()(std::size_t j) const
        {
          return vtk_to_viennagrid_orientations<quadrilateral_tag>()(j);
        }
      };

      // for hexahedra:
      /** @brief Specialization for hexahedra: Switch vertices (2, 3) and (6, 7) */
      template <>
      struct vtk_to_viennagrid_orientations<hexahedron_tag>
      {
        std::size_t operator()(std::size_t j) const
        {
          switch (j)
          {
            case 2: return 3;
            case 3: return 2;
            case 6: return 7;
            case 7: return 6;
            default: return j;
          }
          //return j;  //unreachable code
        }
      };

      /** @brief Specialization for hexahedra: Switch vertices (2, 3) and (6, 7) */
      template <>
      struct viennagrid_to_vtk_orientations<hexahedron_tag>
      {
        std::size_t operator()(std::size_t j) const
        {
          return vtk_to_viennagrid_orientations<hexahedron_tag>()(j);
        }
      };
    } //namespace detail
  } //namespace io
} //namespace viennagrid

#endif

