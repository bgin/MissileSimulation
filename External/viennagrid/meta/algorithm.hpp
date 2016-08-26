#ifndef VIENNAGRID_META_ALGORITHM_HPP
#define VIENNAGRID_META_ALGORITHM_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include "viennagrid/meta/typelist.hpp"

/** @file viennagrid/meta/algorithm.hpp
    @brief Provides STL-like algorithms for manipulating typelists (e.g. for_each, transform)
*/


namespace viennagrid
{
  namespace detail
  {
    template<typename typelist>
    struct for_each_impl {};

    template<typename head, typename tail>
    struct for_each_impl< viennagrid::typelist<head, tail> >
    {
      template<typename functor>
      static void exec( functor & f)
      {
        f( tag<head>() );
        for_each_impl<tail>::exec(f);
      }

      template<typename functor>
      static void exec( const functor & f)
      {
        f( tag<head>() );
        for_each_impl<tail>::exec(f);
      }
    };

    template<>
    struct for_each_impl< viennagrid::null_type >
    {
      template<typename functor> static void exec( functor & ) {}
      template<typename functor> static void exec( const functor & ) {}
    };


    template<typename typelist, typename functor>
    void for_each(functor & f)
    { for_each_impl<typelist>::exec(f); }

    template<typename typelist, typename functor>
    void for_each(const functor & f)
    { for_each_impl<typelist>::exec(f); }




    template<template<typename> class functor, typename typelist>
    struct TRANSFORM;


    template<template<typename> class functor>
    struct TRANSFORM<functor, viennagrid::null_type>
    {
      typedef viennagrid::null_type type;
    };

    template<template<typename> class functor, typename head, typename tail>
    struct TRANSFORM< functor, viennagrid::typelist<head, tail> >
    {
      typedef viennagrid::typelist<
          typename functor<head>::type,
          typename TRANSFORM<functor, tail>::type
      > type;
    };

  }
}

#endif
