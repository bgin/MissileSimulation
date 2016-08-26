#ifndef VIENNAGRID_META_TYPELIST_HPP
#define VIENNAGRID_META_TYPELIST_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include "viennagrid/meta/utils.hpp"

/** @file viennagrid/meta/typelist.hpp
    @brief Defines typelists and provides algorithms for their manipulation
*/

namespace viennagrid
{
  /** @brief Implementation of a typelist as described by Alexandrescu in his book "Modern C++ Programming" */
  template <class HeadT, class TailT>
  struct typelist
  {
    typedef HeadT head;
    typedef TailT tail;
  };


//     C++11 version

//     template<typename ... types>
//     struct make_typelist;
//
//     template<>
//     struct make_typelist<>
//     {
//         typedef viennagrid::null_type type;
//     };
//
//     template<typename head, typename ... tail>
//     struct make_typelist<head, tail...>
//     {
//         typedef viennagrid::typelist<head, typename make_typelist<tail...>::type> type;
//     };




  /** @brief Convenience meta function for creating a typelist out of the provided types */
  template<   typename T01 = viennagrid::null_type, typename T02 = viennagrid::null_type, typename T03 = viennagrid::null_type, typename T04 = viennagrid::null_type,
              typename T05 = viennagrid::null_type, typename T06 = viennagrid::null_type, typename T07 = viennagrid::null_type, typename T08 = viennagrid::null_type,
              typename T09 = viennagrid::null_type, typename T10 = viennagrid::null_type, typename T11 = viennagrid::null_type, typename T12 = viennagrid::null_type,
              typename T13 = viennagrid::null_type, typename T14 = viennagrid::null_type, typename T15 = viennagrid::null_type, typename T16 = viennagrid::null_type,
              typename T17 = viennagrid::null_type, typename T18 = viennagrid::null_type, typename T19 = viennagrid::null_type, typename T20 = viennagrid::null_type >
  struct make_typelist
  {
    typedef
        typelist<
            T01,
            typename make_typelist<T02, T03, T04, T05, T06, T07, T08, T09, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20>::type
        > type;
  };

  /** \cond */
  template<>
  struct make_typelist<
      viennagrid::null_type, viennagrid::null_type, viennagrid::null_type, viennagrid::null_type,
      viennagrid::null_type, viennagrid::null_type, viennagrid::null_type, viennagrid::null_type,
      viennagrid::null_type, viennagrid::null_type, viennagrid::null_type, viennagrid::null_type,
      viennagrid::null_type, viennagrid::null_type, viennagrid::null_type, viennagrid::null_type,
      viennagrid::null_type, viennagrid::null_type, viennagrid::null_type, viennagrid::null_type>
  {
    typedef viennagrid::null_type type;
  };
  /** \endcond */


  namespace detail
  {

    namespace result_of
    {

      // size of a typelist
      template <typename typelist> struct size;

      template <> struct size<null_type>
      {
        static const int value = 0;
      };

      template <typename head, typename tail>
      struct size< typelist<head, tail> >
      {
        static const int value = 1 + size<tail>::value;
      };


      // index access
      template <typename typelist, int index>
      struct at
      {
          typedef out_of_range type;
      };

      template <typename head, typename tail>
      struct at<typelist<head, tail>, 0>
      {
          typedef head type;
      };

      template <typename head, typename tail, int i>
      struct at<typelist<head, tail>, i>
      {
          typedef typename at<tail, i - 1>::type type;
      };



      // returns the index of the first type in the typelist
      template <typename typelist, typename to_find> struct index_of;

      template <typename to_find>
      struct index_of<null_type, to_find>
      {
        static const int value = -1;
      };

      template <typename to_find, typename tail>
      struct index_of<typelist<to_find, tail>, to_find>
      {
        static const int value = 0;
      };

      template <typename head, typename tail, typename to_find>
      struct index_of<typelist<head, tail>, to_find>
      {
      private:
        static const int temp = index_of<tail, to_find>::value;
      public:
        static const int value = (temp == -1 ? -1 : 1 + temp);
      };



      // push back a single type
      template <typename typelist, typename to_add> struct push_back;

      template <>
      struct push_back<null_type, null_type>
      {
        typedef null_type type;
      };

      template <typename to_add>
      struct push_back<null_type, to_add>
      {
        typedef typelist<to_add, null_type> type;
      };

      template <typename head, typename tail, typename to_add>
      struct push_back<typelist<head, tail>, to_add>
      {
        typedef typelist<head, typename push_back<tail, to_add>::type> type;
      };



      // push back list
      template <typename typelist, typename typelisto_add> struct push_back_list;

      template <>
      struct push_back_list<null_type, null_type>
      {
        typedef null_type type;
      };

      template <typename head, typename tail>
      struct push_back_list<null_type, typelist<head, tail> >
      {
        typedef typelist<head, tail> type;
      };

      template <typename head, typename tail>
      struct push_back_list<typelist<head, tail>, null_type >
      {
        typedef typelist<head, tail> type;
      };

      template <typename head1, typename tail1, typename head2, typename tail2>
      struct push_back_list<typelist<head1, tail1>, typelist<head2, tail2> >
      {
        typedef typename push_back_list< typename push_back< typelist<head1, tail1>, head2>::type, tail2 >::type type;
      };



      // erase_at the type at index
      template <typename typelist, int index_to_erase>
      struct erase_at;

      template <int index_to_erase>
      struct erase_at<null_type, index_to_erase>
      {
        typedef null_type type;
      };

      template <typename head, typename tail>
      struct erase_at< typelist<head, tail>, 0>
      {
        typedef tail type;
      };

      template <typename head, typename tail, int index_to_erase>
      struct erase_at< typelist<head, tail>, index_to_erase>
      {
        typedef typelist<head, typename erase_at<tail, index_to_erase-1>::type> type;
      };



      // erase the first type
      template <typename typelist, typename to_erase> struct erase;

      template <typename to_erase>
      struct erase<null_type, to_erase>
      {
        typedef null_type type;
      };

      template <typename to_erase, typename tail>
      struct erase< typelist<to_erase, tail>, to_erase>
      {
        typedef tail type;
      };

      template <typename head, typename tail, typename to_erase>
      struct erase< typelist<head, tail>, to_erase>
      {
        typedef typelist<head, typename erase<tail, to_erase>::type> type;
      };


      // erase all types
      template <typename typelist, typename to_erase>
      struct erase_all;

      template <typename to_erase>
      struct erase_all<null_type, to_erase>
      {
        typedef null_type type;
      };

      template <typename to_erase, typename tail>
      struct erase_all< typelist<to_erase, tail>, to_erase>
      {
        // Go all the way down the list removing the type
        typedef typename erase_all<tail, to_erase>::type type;
      };
      template <typename head, typename tail, typename to_erase>

      struct erase_all< typelist<head, tail>, to_erase>
      {
        // Go all the way down the list removing the type
        typedef typelist<head, typename erase_all<tail, to_erase>::type> type;
      };



      // reverse
      template <typename typelist> struct reverse;

      template <> struct
      reverse<null_type>
      {
        typedef null_type type;
      };

      template <typename head, typename tail>
      struct reverse< typelist<head, tail> >
      {
        typedef typelist<head, tail> t_list;
      public:

        typedef typelist<
            typename at<
              t_list,
              size<t_list>::value-1
            >::type,
            typename reverse<
              typename erase_at<
                t_list,
                size<t_list>::value-1
              >::type
            >::type
        > type;
      };



      // no duplicate types
      template <typename typelist> struct no_duplicates;

      template <> struct
      no_duplicates<null_type>
      {
        typedef null_type type;
      };

      template <typename head, typename tail>
      struct no_duplicates< typelist<head, tail> >
      {
      private:
        typedef typename no_duplicates<tail>::type L1;
        typedef typename erase<L1, head>::type L2;
      public:
        typedef typelist<head, L2> type;
      };


      // replace the type at index by another type
      template <typename typelist, int index_to_replace, typename replaced> struct replace_at;

      template <typename replaced>
      struct replace_at<null_type, -1, replaced>
      {
        typedef null_type type;
      };

      template <typename head, typename tail, typename replaced>
      struct replace_at<typelist<head, tail>, -1, replaced>
      {
        typedef null_type type;
      };

      template <int index_to_replace, typename replaced>
      struct replace_at<null_type, index_to_replace, replaced>
      {
        typedef null_type type;
      };

      template <typename head, typename tail, typename replaced>
      struct replace_at<typelist<head, tail>, 0, replaced>
      {
        typedef typelist<replaced, tail> type;
      };

      template <typename head, typename tail, int index_to_replace, typename replaced>
      struct replace_at<typelist<head, tail>, index_to_replace, replaced>
      {
        typedef typelist<head, typename replace_at<tail, index_to_replace-1, replaced>::type> type;
      };

      // replace the first type by another type
      template <typename typelist, typename to_replace, typename replaced> struct replace;

      template <typename to_replace, typename replaced>
      struct replace<null_type, to_replace, replaced>
      {
        typedef null_type type;
      };

      template <typename to_replace, typename tail, typename replaced>
      struct replace<typelist<to_replace, tail>, to_replace, replaced>
      {
        typedef typelist<replaced, tail> type;
      };

      template <typename head, typename tail, typename to_replace, typename replaced>
      struct replace<typelist<head, tail>, to_replace, replaced>
      {
        typedef typelist<head, typename replace<tail, to_replace, replaced>::type> type;
      };


      // replace all types by another type
      template <typename typelist, typename to_replace, typename replaced> struct replace_all;

      template <typename to_replace, typename replaced>
      struct replace_all<null_type, to_replace, replaced>
      {
        typedef null_type type;
      };

      template <typename to_replace, typename tail, typename replaced>
      struct replace_all<typelist<to_replace, tail>, to_replace, replaced>
      {
        typedef typelist<replaced, typename replace_all<tail, to_replace, replaced>::type> type;
      };

      template <typename head, typename tail, typename to_replace, typename replaced>
      struct replace_all<typelist<head, tail>, to_replace, replaced>
      {
        typedef typelist<head, typename replace_all<tail, to_replace, replaced>::type> type;
      };



      // returns only those types which are in both typelists
      template<typename typelist1, typename typelist2>
      struct intersection {};

      template<>
      struct intersection<null_type, null_type>
      {
        typedef null_type type;
      };

      template<typename head1, typename tail1>
      struct intersection<typelist<head1, tail1>, null_type>
      {
        typedef null_type type;
      };

      template<typename head2, typename tail2>
      struct intersection<null_type, typelist<head2, tail2> >
      {
        typedef null_type type;
      };

      template<typename head1, typename tail1, typename head2, typename tail2>
      struct intersection< typelist<head1, tail1>, typelist<head2, tail2> >
      {
        typedef typelist<head1, tail1> typelist1;
        typedef typelist<head2, tail2> typelist2;

        static const int search_result = index_of< typelist2, head1 >::value;
        static const bool found = (search_result >= 0); //otherwise there are parsing problems with Doxygen 1.7.6.1

        typedef typename IF<
            found,
            typename erase_at<typelist2, search_result>::type,
            typelist2
        >::type new_typelist2;

        typedef typename IF<
            found,
            typelist<head1, typename intersection<tail1, new_typelist2>::type >,
            typename intersection<tail1, new_typelist2>::type
        >::type type;
      };

    }
  } // namespace detail
} // namespace viennagrid


#endif // end file guardian
