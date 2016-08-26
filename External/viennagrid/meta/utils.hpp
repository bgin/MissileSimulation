#ifndef VIENNAGRID_META_UTILS_HPP
#define VIENNAGRID_META_UTILS_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include <iterator>

/** @file viennagrid/meta/utils.hpp
    @brief A collection of tools for meta programming
*/

namespace viennagrid
{

  /** @brief An empty type, used within typelists and typemaps */
  class null_type {};

  // some special types
  /** @brief Empty type used to indicate that an element in a typelist/typemap is out of range */
  class out_of_range {};
  /** @brief Empty type indicating that an element in a typelist/typemap wasn't found */
  class not_found {};


  // a static type pair
  /** @brief A static pair time. To be seen as the equivalent of std::pair<>, but for metaprogramming. */
  template<typename FirstT, typename SecondT>
  struct static_pair
  {
    typedef FirstT   first;
    typedef SecondT  second;
  };

  namespace detail
  {
    // basic operations
    template<typename type1, typename type2>
    struct EQUAL
    {
      static const bool value = false;
    };

    template<typename type>
    struct EQUAL<type,type>
    {
      static const bool value = true;
    };

    template<typename type1, typename type2>
    struct NOT_EQUAL
    {
      static const bool value = !EQUAL<type1, type2>::value;
    };

    template<bool condition, typename type1, typename type2>
    struct IF
    {
      typedef type1 type;
    };

    template<typename type1, typename type2>
    struct IF<false, type1, type2>
    {
      typedef type2 type;
    };

    template<typename T>
    struct IDENTITY
    {
      typedef T type;
    };


    // error generator
    template<bool ErrorT>
    struct STATIC_ASSERT
    {
      typedef void type;
    };

    template<>
    struct STATIC_ASSERT<false>
    {};



    namespace result_of
    {
      template<typename pair>
      struct first
      {
          typedef not_found type;
      };

      template<typename first_, typename second_>
      struct first< static_pair<first_, second_> >
      {
          typedef first_ type;
      };

      template<typename pair>
      struct second
      {
          typedef not_found type;
      };

      template<typename first_, typename second_>
      struct second< static_pair<first_, second_> >
      {
          typedef second_ type;
      };
    }


    // a tag wrapper
    template<typename foo>
    class tag {};


    // a true functor
    struct true_predicate
    {
      template<typename type>
      bool operator()(const type &)
      {
          return true;
      }
    };






    template<typename some_type>
    struct remove_const
    {
      typedef some_type type;
    };

    template<typename some_type>
    struct remove_const<const some_type>
    {
      typedef some_type type;
    };



    // http://stackoverflow.com/questions/5423246/how-to-detect-if-a-type-is-an-iterator-or-const-iterator
    template<typename T>
    struct is_const_pointer { static const bool value = false; };

    template<typename T>
    struct is_const_pointer<const T*> { static const bool value = true; };

    template <typename TIterator>
    struct is_const_iterator
    {
      typedef typename std::iterator_traits<TIterator>::pointer pointer;
      static const bool value = is_const_pointer<pointer>::value;
    };

  } // namespace detail
} // namespace viennagrid


#endif
