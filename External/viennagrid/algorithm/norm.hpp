#ifndef VIENNAGRID_ALGORITHM_NORM_HPP
#define VIENNAGRID_ALGORITHM_NORM_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include <cmath>
#include "viennagrid/forwards.hpp"
#include "viennagrid/point.hpp"

/** @file viennagrid/algorithm/norm.hpp
    @brief Functions for the computation of norms for vectors
*/

namespace viennagrid
{

  namespace detail
  {

    // -----------------------------------------------------------------------------
    //
    // norm algorithm specialization hierarchy
    //
    template<typename Tag>
    struct norm_impl
    {
      template<typename PointT>
      typename viennagrid::result_of::coord<PointT>::type operator()(PointT const&)
      {
        std::cerr << "ViennaGrid - Norm Error - this error type is not implemented" << std::endl;
        return 0.0;
      }
    };

    /** @brief Implementation of the 1-norm */
    template<>
    struct norm_impl<viennagrid::one_norm_tag>
    {
      template<typename PointT>
      typename viennagrid::result_of::coord<PointT>::type operator()(PointT const& p)
      {
        typename viennagrid::result_of::coord<PointT>::type result(0);
        for(std::size_t i = 0; i < dynamic_size(p); i++)
          result += std::abs(p[i]);
        return result;
      }
    };

    /** @brief Implementation of the 2-norm */
    template<>
    struct norm_impl<viennagrid::two_norm_tag>
    {
      template<typename PointT>
      typename viennagrid::result_of::coord<PointT>::type operator()(PointT const& p)
      {
        typename viennagrid::result_of::coord<PointT>::type result(0);
        for(std::size_t i = 0; i < dynamic_size(p); i++)
          result += p[i]*p[i];
        return std::sqrt(result);
      }
    };

    /** @brief Implementation of the inf-norm */
    template<>
    struct norm_impl<viennagrid::inf_norm_tag>
    {
      template<typename PointT>
      typename viennagrid::result_of::coord<PointT>::type operator()(PointT const& p)
      {
        typename viennagrid::result_of::coord<PointT>::type result(0);
        for(std::size_t i = 0; i < dynamic_size(p); i++)
        {
          if(std::abs(p[i]) > result)
              result = std::abs(p[i]);
        }
        return result;
      }
    };

  } //namespace detail

  /** @brief Dispatch for a point that needs coordinate conversion */
  template<typename NormTag, typename PointT, typename CoordinateSystemT>
  typename viennagrid::result_of::coord<PointT>::type
  norm_impl(PointT const & p, CoordinateSystemT const &)
  {
    return detail::norm_impl<NormTag>()(to_cartesian(p));
  }

  /** @brief Dispatch for a point that does not need coordinate conversion */
  template<typename NormTag, typename PointT1, int d>
  typename viennagrid::result_of::coord<PointT1>::type
  norm_impl(PointT1 const & p, cartesian_cs<d>)
  {
    return detail::norm_impl<NormTag>()(p);
  }


  // -----------------------------------------------------------------------------
  //
  // norm algorithm generic interface functions
  //
  /** @brief Returns the norm of a point. The type of the norm is specified by a tag. Supported tags are one_norm_tag, two_norm_tag and inf_norm_tag.
   *
   * @param p    The vector (point) for which the norm should be computed.
   */
  template<typename PointT, typename Tag>
  typename viennagrid::result_of::coord<PointT>::type
  norm(PointT const & p, Tag)
  {
    return norm_impl<Tag>(p, typename result_of::coordinate_system<PointT>::type());
  }

  /** @brief Returns the 2-norm of a point. Result is such as if the point were transformed to Cartesian coordinates first */
  template<typename PointT>
  typename viennagrid::result_of::coord<PointT>::type
  norm(PointT const & p)
  {
    return norm_impl<viennagrid::two_norm_tag>(p, typename result_of::coordinate_system<PointT>::type());
  }


  //convenience shortcuts:
  /** @brief Convenience shortcut for the 1-norm of a vector. */
  template<typename PointT>
  typename viennagrid::result_of::coord<PointT>::type
  norm_1(PointT const & p)
  {
    return norm_impl<viennagrid::one_norm_tag>(p, typename result_of::coordinate_system<PointT>::type());
  }

  /** @brief Convenience shortcut for the 2-norm of a vector. */
  template<typename PointT>
  typename viennagrid::result_of::coord<PointT>::type
  norm_2(PointT const & p)
  {
    return norm_impl<viennagrid::two_norm_tag>(p, typename result_of::coordinate_system<PointT>::type());
  }

  /** @brief Convenience shortcut for the inf-norm of a vector. */
  template<typename PointT>
  typename viennagrid::result_of::coord<PointT>::type
  norm_inf(PointT const & p)
  {
    return norm_impl<viennagrid::inf_norm_tag>(p, typename result_of::coordinate_system<PointT>::type());
  }

}

#endif

