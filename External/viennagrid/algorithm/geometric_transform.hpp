#ifndef VIENNAGRID_ALGORITHM_GEOMETRIC_TRANSFORM_HPP
#define VIENNAGRID_ALGORITHM_GEOMETRIC_TRANSFORM_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include "viennagrid/forwards.hpp"
#include "viennagrid/mesh/mesh.hpp"

/** @file viennagrid/algorithm/geometric_transform.hpp
    @brief Provides geometric transformation routines (e.g. scale()) for a mesh.
*/

namespace viennagrid
{
  /** @brief Transforms all points of a mesh based on a functor
   *
   * @param mesh                    The input mesh
   * @param func                    The functor object, has to be a function or provide an operator(). Interface: MeshPointType func(MeshPointType)
   * @param accessor                Point accessor for input points
   */
  template<typename MeshT, typename FunctorT, typename PointAccessorT>
  void geometric_transform(MeshT & mesh, FunctorT func, PointAccessorT accessor)
  {
    typedef typename viennagrid::result_of::element_range<MeshT, viennagrid::vertex_tag>::type   VertexContainer;
    typedef typename viennagrid::result_of::iterator<VertexContainer>::type                      VertexIterator;

    VertexContainer vertices(mesh);
    for ( VertexIterator vit = vertices.begin();
          vit != vertices.end();
          ++vit )
      accessor(*vit) = func( accessor(*vit) );
  }

  /** @brief Transforms all points of a mesh based on a functor
   *
   * @param mesh                    The input mesh
   * @param func                    The functor object, has to be a function or provide an operator(). Interface: MeshPointType func(MeshPointType)
   */
  template<typename MeshT, typename FunctorT>
  void geometric_transform(MeshT & mesh, FunctorT func)
  {
    geometric_transform(mesh, func, viennagrid::default_point_accessor(mesh));
  }


  /** @brief Scale functor with scaling factor and scale center
   *
   * @param MeshT                   The mesh type
   */
  template<typename MeshT>
  struct scale_functor
  {
    typedef typename viennagrid::result_of::point<MeshT>::type PointType;
    typedef typename viennagrid::result_of::coord<MeshT>::type ScalarType;

    scale_functor() {}
    scale_functor(ScalarType factor_) : factor(factor_), scale_center(0) {}
    scale_functor(ScalarType factor_, PointType const & scale_center_) :
        factor(factor_), scale_center(scale_center_) {}

    PointType operator()(PointType p) const
    {
      p -= scale_center;
      p *= factor;
      p += scale_center;
      return p;
    }

    ScalarType factor;
    PointType scale_center;
  };

  /** @brief Function for scaling a mesh, uses scale_functor
   *
   * @param mesh                    The input mesh
   * @param factor                  The scaling factor
   * @param scaling_center          The center of the scaling operation
   */
  template<typename MeshT, typename ScalarT, typename PointType>
  void scale(MeshT & mesh, ScalarT factor, PointType const & scaling_center)
  {
    scale_functor<MeshT> func(factor, scaling_center);
    geometric_transform(mesh, func);
  }

  /** @brief Function for scaling a mesh, uses scale_functor. Scaling center is the origin.
   *
   * @param mesh                    The input mesh
   * @param factor                  The scaling factor
   */
  template<typename MeshT, typename ScalarT>
  void scale(MeshT & mesh, ScalarT factor)
  {
    scale_functor<MeshT> func(factor);
    geometric_transform(mesh, func);
  }




  /** @brief Affine transform functor using a ScalarType * as matrix (row major layout) and a translation vector
   *
   * @param MeshT                   The mesh type
   */
  template<typename MeshT>
  struct affine_transform_functor
  {
    typedef typename viennagrid::result_of::point<MeshT>::type PointType;
    typedef typename viennagrid::result_of::coord<MeshT>::type ScalarType;
    static const unsigned int point_dim = viennagrid::result_of::geometric_dimension<MeshT>::value;

    affine_transform_functor() {}
    affine_transform_functor(ScalarType const * matrix_) : matrix(matrix_), translation(0) {}
    affine_transform_functor(ScalarType const * matrix_, PointType const & translation_) :
        matrix(matrix_), translation(translation_) {}

    PointType operator()(PointType const & p) const
    {
      PointType tmp = translation;
      for (unsigned int row = 0; row != point_dim; ++row)
      {
        for (unsigned int column = 0; column != point_dim; ++column)
          tmp[row] += p[column] * matrix[ row*point_dim + column ];
      }

      return tmp;
    }

    ScalarType const * matrix;
    PointType translation;
  };

  /** @brief Function for an affine transformation of a mesh, uses affine_transform_functor
   *
   * @param mesh                    The input mesh
   * @param matrix                  The matrix representing the linear transformation part, row major layout. Attention! There are no out-of boundary checks, the user is responsible to provide a suitable matrix pointer.
   * @param translation             The translation vector
   */
  template<typename MeshT>
  void affine_transform( MeshT & mesh,
                         typename viennagrid::result_of::coord<MeshT>::type const * matrix,
                         typename viennagrid::result_of::point<MeshT>::type const & translation )
  {
    affine_transform_functor<MeshT> func(matrix, translation);
    geometric_transform(mesh, func);
  }

}

#endif
