#ifndef VIENNAGRID_STORAGE_HIDDEN_KEY_MAP_HPP
#define VIENNAGRID_STORAGE_HIDDEN_KEY_MAP_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include <map>
#include "viennagrid/storage/container.hpp"

/** @file viennagrid/storage/hidden_key_map.hpp
    @brief Provides the implementation of the hidden key map and its surrounding functionality
*/

namespace viennagrid
{
  /** @brief An iterator over all values of a hidden_key_map */
  template<typename HiddenKeyMapT>
  class hidden_key_map_iterator : public HiddenKeyMapT::container_type::iterator
  {
    typedef typename HiddenKeyMapT::container_type::iterator base;
  public:
    hidden_key_map_iterator() {}
    hidden_key_map_iterator(const base & foo) : base(foo) {}

    typedef typename HiddenKeyMapT::value_type value_type;
    typedef typename HiddenKeyMapT::reference reference;
    typedef typename HiddenKeyMapT::const_reference const_reference;
    typedef typename HiddenKeyMapT::pointer pointer;

    reference operator* () { return base::operator*().second; }
    const_reference operator* () const { return base::operator*().second; }
  };

  /** @brief A const-iterator over all values of a hidden_key_map */
  template<typename HiddenKeyMapT>
  class hidden_key_map_const_iterator : public HiddenKeyMapT::container_type::const_iterator
  {
    typedef typename HiddenKeyMapT::container_type::const_iterator base;
  public:
    hidden_key_map_const_iterator() {}
    hidden_key_map_const_iterator(base const & foo) : base(foo) {}
    hidden_key_map_const_iterator(hidden_key_map_iterator<HiddenKeyMapT> const & it) : base(it) {}

    typedef typename HiddenKeyMapT::value_type value_type;
    typedef typename HiddenKeyMapT::const_reference reference;
    typedef typename HiddenKeyMapT::const_reference const_reference;
    typedef typename HiddenKeyMapT::const_pointer pointer;

    const_reference operator* () const { return base::operator*().second; }
  };

  /** @brief A iterator over all values of a hidden_key_map in reverse direction */
  template<typename HiddenKeyMapT>
  class hidden_key_map_reverse_iterator : public HiddenKeyMapT::container_type::reverse_iterator
  {
    typedef typename HiddenKeyMapT::container_type::reverse_iterator base;
  public:
    hidden_key_map_reverse_iterator() {}
    hidden_key_map_reverse_iterator(base const & foo) : base(foo) {}

    typedef typename HiddenKeyMapT::value_type value_type;
    typedef typename HiddenKeyMapT::reference reference;
    typedef typename HiddenKeyMapT::const_reference const_reference;
    typedef typename HiddenKeyMapT::pointer pointer;

    reference operator* () { return base::operator*().second; }
    const_reference operator* () const { return base::operator*().second; }
  };

  /** @brief A const-iterator over all values of a hidden_key_map in reverse direction */
  template<typename HiddenKeyMapT>
  class hidden_key_map_const_reverse_iterator : public HiddenKeyMapT::container_type::const_reverse_iterator
  {
    typedef typename HiddenKeyMapT::container_type::const_reverse_iterator base;
  public:
    hidden_key_map_const_reverse_iterator() {}
    hidden_key_map_const_reverse_iterator(base const & foo) : base(foo) {}
    hidden_key_map_const_reverse_iterator(hidden_key_map_reverse_iterator<HiddenKeyMapT> const & it) : base(it) {}

    typedef typename HiddenKeyMapT::value_type value_type;
    typedef typename HiddenKeyMapT::const_reference reference;
    typedef typename HiddenKeyMapT::const_reference const_reference;
    typedef typename HiddenKeyMapT::const_pointer pointer;

    const_reference operator* () const { return base::operator*().second; }
  };


  /** @brief STL-like map where the key is automatically deduced from the value object (hence 'hidden').
    *
    * @tparam  KeyT    The key functor type which extracts the key from the value object
    * @tparam  ValueT  The value type, i.e. the element stored inside the map.
    */
  template<typename KeyT, typename ValueT>
  class hidden_key_map
  {
    typedef hidden_key_map<KeyT, ValueT> SelfType;

    friend class hidden_key_map_iterator<SelfType>;
    friend class hidden_key_map_const_iterator<SelfType>;
    friend class hidden_key_map_reverse_iterator<SelfType>;
    friend class hidden_key_map_const_reverse_iterator<SelfType>;

  public:

    typedef std::map< KeyT, ValueT >           container_type;
    typedef KeyT                               key_type;
    typedef ValueT                             value_type;
    typedef typename container_type::size_type size_type;
    typedef value_type &                       reference;
    typedef const value_type &                 const_reference;
    typedef value_type *                       pointer;
    typedef const value_type *                 const_pointer;

    typedef hidden_key_map_iterator<SelfType>                             iterator;
    typedef hidden_key_map_const_iterator<SelfType>                 const_iterator;

    typedef hidden_key_map_reverse_iterator<SelfType>             reverse_iterator;
    typedef hidden_key_map_const_reverse_iterator<SelfType> const_reverse_iterator;


    iterator begin() { return iterator(container.begin()); }
    iterator end()   { return iterator(container.end()); }

    const_iterator begin() const { return const_iterator(container.begin()); }
    const_iterator end()   const { return const_iterator(container.end()); }

    iterator find( const value_type & element)
    {
      return iterator(container.find( key_type(element) ));
    }

    const_iterator find( const value_type & element) const
    {
      return const_iterator(container.find( key_type(element) ));
    }

    std::pair<iterator, bool> insert( const value_type & element )
    {
      std::pair<typename container_type::iterator, bool> ret = container.insert( std::make_pair( key_type(element), element ) );
      return std::make_pair( iterator(ret.first), ret.second );
    }

    iterator erase( iterator to_erase )
    {
      container.erase( to_erase++ );
      return to_erase;
    }

    void clear()
    {
      container.clear();
    }


    size_type size() const { return container.size(); }
    bool empty()     const { return container.empty(); }

  private:
    container_type container;
  };



  namespace detail
  {
    template<typename KeyT, typename ElementT, typename handle_tag>
    class container_base<hidden_key_map<KeyT, ElementT>, handle_tag> : public handled_container<hidden_key_map<KeyT, ElementT>, handle_tag>
    {
    public:

      typedef handled_container<hidden_key_map<KeyT, ElementT>, handle_tag> handled_container_type;
      typedef typename handled_container_type::container_type container_type;

      typedef typename handled_container_type::value_type value_type;

      typedef typename handled_container_type::pointer pointer;
      typedef typename handled_container_type::const_pointer const_pointer;

      typedef typename handled_container_type::reference reference;
      typedef typename handled_container_type::const_reference const_reference;

      typedef typename handled_container_type::iterator iterator;
      typedef typename handled_container_type::const_iterator const_iterator;

      typedef typename handled_container_type::handle_type handle_type;
      typedef typename handled_container_type::const_handle_type const_handle_type;

      typedef std::pair<handle_type, bool> return_type;

      bool is_present( const value_type & element ) const
      {
        return container_type::find(element) != container_type::end();
      }

      typename container_type::iterator find( const value_type & element ) const
      {
        return container_type::find(element);
      }

      return_type insert( const value_type & element )
      {
        std::pair<typename container_type::iterator, bool> tmp = container_type::insert( element );
        return std::make_pair( handled_container_type::handle(*tmp.first), tmp.second);
      }
    };
  }


  /** @brief A tag for selecting a hidden key map as a storage type.
    *
    * @tparam  KeyTypeTagT      A tag identifying the key deduction mechanism to be used in the hidden key map.
    */
  template<typename KeyTypeTagT>
  struct hidden_key_map_tag {};

  namespace result_of
  {
    /** \cond */
    template<typename element_tag, typename key_type_tag>
    struct hidden_key_map_key_type_from_tag;

    template<typename element_type, typename key_type_tag>
    struct container<element_type, hidden_key_map_tag<key_type_tag> >
    {
      typedef hidden_key_map< typename hidden_key_map_key_type_from_tag<element_type, key_type_tag>::type, element_type > type;
    };
    /** \endcond */
  }

  namespace detail
  {
    template<typename KeyT, typename ValueT>
    std::pair<typename hidden_key_map<KeyT, ValueT>::iterator, bool>
        insert( hidden_key_map<KeyT, ValueT> & container, const ValueT & element )
    {
      return container.insert( element );
    }

    /** \cond */

    template<typename HiddenKeyMapT, typename HandleTagT>
    struct IDCompare<
          viennagrid::detail::iterator<
            viennagrid::hidden_key_map_iterator<HiddenKeyMapT>,
            viennagrid::hidden_key_map_const_iterator<HiddenKeyMapT>,
            HandleTagT
          >
        >
    {
      bool operator() (               viennagrid::detail::iterator<
            viennagrid::hidden_key_map_iterator<HiddenKeyMapT>,
            viennagrid::hidden_key_map_const_iterator<HiddenKeyMapT>,
            HandleTagT
          > const & lhs,
                                      viennagrid::detail::iterator<
            viennagrid::hidden_key_map_iterator<HiddenKeyMapT>,
            viennagrid::hidden_key_map_const_iterator<HiddenKeyMapT>,
            HandleTagT
          > const & rhs )
      {
        return lhs->second.id() < rhs->second.id();
      }
    };

    /** \endcond */
  }
}

#endif
