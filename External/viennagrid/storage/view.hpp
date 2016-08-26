#ifndef VIENNAGRID_STORAGE_VIEW_HPP
#define VIENNAGRID_STORAGE_VIEW_HPP

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
#include <algorithm>

#include "viennagrid/forwards.hpp"
#include "viennagrid/meta/typemap.hpp"

#include "viennagrid/storage/container.hpp"
#include "viennagrid/storage/container_collection.hpp"
#include "viennagrid/storage/handle.hpp"
#include "viennagrid/storage/id.hpp"


/** @file viennagrid/storage/view.hpp
    @brief General functionality for dealing with a subset of elements in a container
*/

namespace viennagrid
{
  /** @brief A view holds references to a subset of elements in another elements, but represents itself to the outside as another container.
    *
    * @tparam base_container_type_    The container type on which the view acts
    * @tparam container_tag           Categorization tag for the view in order to specialize on certain details of different container types.
    */
  template<typename base_container_type_, typename container_tag>
  class view
  {
  public:

    template<typename A, typename B>
    friend class view;

    typedef base_container_type_ base_container_type;

    typedef typename base_container_type::handle_tag handle_tag;
    typedef typename detail::result_of::handle_type<base_container_type, handle_tag>::type handle_type;
    typedef typename detail::result_of::const_handle_type<base_container_type, handle_tag>::type const_handle_type;


  private:
    typedef typename viennagrid::result_of::container<handle_type, container_tag>::type handle_container_type;


  public:
    typedef typename handle_container_type::size_type size_type;
    typedef typename base_container_type::value_type value_type;
    typedef value_type & reference;
    typedef const value_type & const_reference;
    typedef value_type * pointer;
    typedef const value_type * const_pointer;



    class iterator : public handle_container_type::iterator
    {
      typedef typename handle_container_type::iterator base;
    public:
      iterator(view & view_obj, const base & foo) : base(foo), view_(&view_obj) {}
      iterator(const iterator & it) : base(it), view_(it.view_) {}

      typedef typename std::iterator_traits<base>::difference_type   difference_type;
      typedef typename view::value_type                            value_type;
      typedef typename view::reference                             reference;
      typedef typename view::const_reference                       const_reference;
      typedef typename view::pointer                               pointer;
      typedef typename std::iterator_traits<base>::iterator_category iterator_category;

      handle_type &     handle()       { return base::operator*(); }
      const_handle_type handle() const { return base::operator*(); }

      reference       operator* ()       { return view_->dereference_handle( handle() ); }
      const_reference operator* () const { return view_->dereference_handle( handle() ); }

      pointer operator->()       { return &(operator* ()); }
      pointer operator->() const { return &(operator* ()); }

      iterator & operator++() { base::operator++(); return *this; }
      iterator operator++(int) { base::operator++(int()); return *this; }

      iterator & operator--() { base::operator--(); return *this; }
      iterator operator--(int) { base::operator--(int()); return *this; }

    private:
      view * view_;
    };


    class const_iterator : public handle_container_type::const_iterator
    {
      typedef typename handle_container_type::const_iterator base;
    public:
      const_iterator(view const & view_obj, const base & foo) : base(foo), view_(&view_obj) {}
      const_iterator(const const_iterator & it) : base(it), view_(it.view_) {}
      const_iterator(const iterator & it) : base(it), view_(it.view_) {}

      typedef typename std::iterator_traits<base>::difference_type difference_type;
      typedef typename view::value_type value_type;
      typedef typename view::const_reference reference;
      typedef typename view::const_reference const_reference;
      typedef typename view::const_pointer pointer;
      typedef typename std::iterator_traits<base>::iterator_category iterator_category;

      const_handle_type handle() { return base::operator*(); }
      const_handle_type handle() const { return base::operator*(); }

      reference operator* () { return view_->dereference_handle( handle() ); }
      const_reference operator* () const { return view_->dereference_handle( handle() ); }

      pointer operator->() const { return &(operator* ()); }

      const_iterator & operator++() { base::operator++(); return *this; }
      const_iterator operator++(int) { base::operator++(int()); return *this; }

      const_iterator & operator--() { base::operator--(); return *this; }
      const_iterator operator--(int) { base::operator--(int()); return *this; }

    private:
      view const * view_;
    };

    class reverse_iterator : public handle_container_type::reverse_iterator
    {
      typedef typename handle_container_type::reverse_iterator base;
    public:
      reverse_iterator(view & view_obj, const base & foo) : base(foo), view_(&view_obj) {}
      reverse_iterator(const reverse_iterator & it) : base(it), view_(it.view_) {}

      typedef typename std::iterator_traits<base>::difference_type difference_type;
      typedef typename view::value_type value_type;
      typedef typename view::reference reference;
      typedef typename view::const_reference const_reference;
      typedef typename view::pointer pointer;
      typedef typename std::iterator_traits<base>::iterator_category iterator_category;

      handle_type & handle() { return base::operator*(); }
      const_handle_type handle() const { return base::operator*(); }

      reference operator* () { return view_->dereference_handle( handle() ); }
      const_reference operator* () const { return view_->dereference_handle( handle() ); }

      pointer operator->() { return &(operator* ()); }
      pointer operator->() const { return &(operator* ()); }

      reverse_iterator & operator++() { base::operator++(); return *this; }
      reverse_iterator operator++(int) { base::operator++(int()); return *this; }

      reverse_iterator & operator--() { base::operator--(); return *this; }
      reverse_iterator operator--(int) { base::operator--(int()); return *this; }

    private:
      view * view_;
    };


    class const_reverse_iterator : public handle_container_type::const_reverse_iterator
    {
      typedef typename handle_container_type::const_reverse_iterator base;
    public:
      const_reverse_iterator(view const & view_obj, const base & foo) : base(foo), view_(&view_obj) {}
      const_reverse_iterator(const const_reverse_iterator & it) : base(it), view_(it.view_) {}
      const_reverse_iterator(const iterator & it) : base(it), view_(it.view_) {}

      typedef typename std::iterator_traits<base>::difference_type difference_type;
      typedef typename view::value_type value_type;
      typedef typename view::const_reference reference;
      typedef typename view::const_reference const_reference;
      typedef typename view::const_pointer pointer;
      typedef typename std::iterator_traits<base>::iterator_category iterator_category;

      const_handle_type handle() { return base::operator*(); }
      const_handle_type handle() const { return base::operator*(); }

      reference operator* () { return view_->dereference_handle( handle() ); }
      const_reference operator* () const { return view_->dereference_handle( handle() ); }

      pointer operator->() const { return &(operator* ()); }

      const_reverse_iterator & operator++() { base::operator++(); return *this; }
      const_reverse_iterator operator++(int) { base::operator++(int()); return *this; }

      const_reverse_iterator & operator--() { base::operator--(); return *this; }
      const_reverse_iterator operator--(int) { base::operator--(int()); return *this; }

    private:
      view const * view_;
    };


    view() {}

    void set_base_container( base_container_type & base_container_ )
    { base_container = &base_container_; }

    template<typename other_container_tag>
    void set_base_container( view<base_container_type, other_container_tag> & base_view )
    { base_container = base_view.base_container; }

    template<typename other_container_tag>
    void set_base_container( view<base_container_type, other_container_tag> const & base_view )
    { base_container = base_view.base_container; }


    iterator begin() { return iterator(*this, handle_container.begin()); }
    iterator end() { return iterator(*this, handle_container.end()); }

    const_iterator cbegin() { return const_iterator(*this, handle_container.begin()); }
    const_iterator cend() { return const_iterator(*this, handle_container.end()); }

    const_iterator begin() const { return const_iterator(*this, handle_container.begin()); }
    const_iterator end() const { return const_iterator(*this, handle_container.end()); }

    reference dereference_handle( handle_type handle ) { return viennagrid::detail::dereference_handle( *base_container, handle ); }
    const_reference dereference_handle( const_handle_type handle ) const { return viennagrid::detail::dereference_handle_const( *base_container, handle ); }

    handle_type handle( reference element ) { return &element; }
    const_handle_type handle( const_reference element ) const { return &element; }

    iterator find( const_reference element )
    { return std::find( begin(), end(), handle(element)); }
    const_iterator find( const_reference element ) const
    { return std::find( begin(), end(), handle(element)); }


    reference front() { return dereference_handle(handle_container.front()); }
    const_reference front() const { return dereference_handle(handle_container.front()); }

    reference back() { return dereference_handle(handle_container.back()); }
    const_reference back() const { return dereference_handle(handle_container.back()); }

    reference operator[]( size_type index ) { iterator it = begin(); std::advance(it, static_cast<long>(index)); return *it; }
    const_reference operator[]( size_type index ) const { const_iterator it = begin(); std::advance(it, static_cast<long>(index)); return *it; }


    size_type size() const { return handle_container.size(); }
    void resize(size_type size_) { handle_container.resize(size_); }
    void increment_size() { resize( size()+1 ); }

    bool empty() const { return handle_container.empty(); }
    void clear() { handle_container.clear(); }


    void insert_unique_handle(handle_type handle)
    {
      for (iterator it = begin(); it != end(); ++it)
        if (handle == it.handle()) return;

      insert_handle(handle);
    }

    void insert_handle(handle_type handle) { viennagrid::detail::insert(handle_container, handle); }
    void set_handle( handle_type element, size_type pos )
    {
      if (size() <= pos+1) resize(pos+1);
      handle_container[pos] = element;
    }
    void erase_handle(handle_type handle)
    {
      for (iterator it = begin(); it != end(); ++it)
        if (it.handle() == handle)
        {
          handle_container.erase( it );
          return;
        }
    }

    handle_type handle_at(std::size_t pos) { return viennagrid::advance(begin(), pos).handle(); }
    const_handle_type handle_at(std::size_t pos) const { return viennagrid::advance(begin(), pos).handle(); }

  private:
    handle_container_type handle_container;
    base_container_type * base_container;
  };












  // specialization for std::set
  /** \cond */
  template<typename base_container_type_, typename CompareTagT>
  class view<base_container_type_, std_set_tag<CompareTagT> >
  {
  public:

    template<typename A, typename B>
    friend class view;

    typedef base_container_type_ base_container_type;

    typedef std_set_tag<CompareTagT> container_tag;

    typedef typename base_container_type::handle_tag handle_tag;
    typedef typename detail::result_of::handle_type<base_container_type, handle_tag>::type handle_type;
    typedef typename detail::result_of::const_handle_type<base_container_type, handle_tag>::type const_handle_type;


  private:
    typedef typename viennagrid::result_of::container<handle_type, container_tag>::type handle_container_type;


  public:
    typedef typename handle_container_type::size_type size_type;
    typedef typename base_container_type::value_type value_type;
    typedef value_type & reference;
    typedef const value_type & const_reference;
    typedef value_type * pointer;
    typedef const value_type * const_pointer;



    class iterator : public handle_container_type::iterator
    {
      typedef typename handle_container_type::iterator base;
    public:
      iterator(view & view_obj, const base & foo) : base(foo), view_(&view_obj) {}
      iterator(const iterator & it) : base(it), view_(it.view_) {}

      typedef typename std::iterator_traits<base>::difference_type   difference_type;
      typedef typename view::value_type                            value_type;
      typedef typename view::reference                             reference;
      typedef typename view::const_reference                       const_reference;
      typedef typename view::pointer                               pointer;
      typedef typename std::iterator_traits<base>::iterator_category iterator_category;

      handle_type       handle()       { return base::operator*(); }
      const_handle_type handle() const { return base::operator*(); }

      reference       operator* ()       { return view_->dereference_handle( handle() ); }
      const_reference operator* () const { return view_->dereference_handle( handle() ); }

      pointer operator->()       { return &(operator* ()); }
      pointer operator->() const { return &(operator* ()); }

      iterator & operator++() { base::operator++(); return *this; }
      iterator operator++(int) { base::operator++(int()); return *this; }

      iterator & operator--() { base::operator--(); return *this; }
      iterator operator--(int) { base::operator--(int()); return *this; }

    private:
      view * view_;
    };


    class const_iterator : public handle_container_type::const_iterator
    {
      typedef typename handle_container_type::const_iterator base;
    public:
      const_iterator(view const & view_obj, const base & foo) : base(foo), view_(&view_obj) {}
      const_iterator(const const_iterator & it) : base(it), view_(it.view_) {}
      const_iterator(const iterator & it) : base(it), view_(it.view_) {}

      typedef typename std::iterator_traits<base>::difference_type difference_type;
      typedef typename view::value_type value_type;
      typedef typename view::const_reference reference;
      typedef typename view::const_reference const_reference;
      typedef typename view::const_pointer pointer;
      typedef typename std::iterator_traits<base>::iterator_category iterator_category;

      const_handle_type handle() { return base::operator*(); }
      const_handle_type handle() const { return base::operator*(); }

      reference operator* () { return view_->dereference_handle( handle() ); }
      const_reference operator* () const { return view_->dereference_handle( handle() ); }

      pointer operator->() const { return &(operator* ()); }

      const_iterator & operator++() { base::operator++(); return *this; }
      const_iterator operator++(int) { base::operator++(int()); return *this; }

      const_iterator & operator--() { base::operator--(); return *this; }
      const_iterator operator--(int) { base::operator--(int()); return *this; }

    private:
      view const * view_;
    };

    class reverse_iterator : public handle_container_type::reverse_iterator
    {
      typedef typename handle_container_type::reverse_iterator base;
    public:
      reverse_iterator(view & view_obj, const base & foo) : base(foo), view_(&view_obj) {}
      reverse_iterator(const reverse_iterator & it) : base(it), view_(it.view_) {}

      typedef typename std::iterator_traits<base>::difference_type difference_type;
      typedef typename view::value_type value_type;
      typedef typename view::reference reference;
      typedef typename view::const_reference const_reference;
      typedef typename view::pointer pointer;
      typedef typename std::iterator_traits<base>::iterator_category iterator_category;

      handle_type & handle() { return base::operator*(); }
      const_handle_type handle() const { return base::operator*(); }

      reference operator* () { return view_->dereference_handle( handle() ); }
      const_reference operator* () const { return view_->dereference_handle( handle() ); }

      pointer operator->() { return &(operator* ()); }
      pointer operator->() const { return &(operator* ()); }

      reverse_iterator & operator++() { base::operator++(); return *this; }
      reverse_iterator operator++(int) { base::operator++(int()); return *this; }

      reverse_iterator & operator--() { base::operator--(); return *this; }
      reverse_iterator operator--(int) { base::operator--(int()); return *this; }

    private:
      view * view_;
    };


    class const_reverse_iterator : public handle_container_type::const_reverse_iterator
    {
      typedef typename handle_container_type::const_reverse_iterator base;
    public:
      const_reverse_iterator(view const & view_obj, const base & foo) : base(foo), view_(&view_obj) {}
      const_reverse_iterator(const const_reverse_iterator & it) : base(it), view_(it.view_) {}
      const_reverse_iterator(const iterator & it) : base(it), view_(it.view) {}

      typedef typename std::iterator_traits<base>::difference_type difference_type;
      typedef typename view::value_type value_type;
      typedef typename view::const_reference reference;
      typedef typename view::const_reference const_reference;
      typedef typename view::const_pointer pointer;
      typedef typename std::iterator_traits<base>::iterator_category iterator_category;

      const_handle_type handle() { return base::operator*(); }
      const_handle_type handle() const { return base::operator*(); }

      reference operator* () { return view_->dereference_handle( handle() ); }
      const_reference operator* () const { return view_->dereference_handle( handle() ); }

      pointer operator->() const { return &(operator* ()); }

      const_reverse_iterator & operator++() { base::operator++(); return *this; }
      const_reverse_iterator operator++(int) { base::operator++(int()); return *this; }

      const_reverse_iterator & operator--() { base::operator--(); return *this; }
      const_reverse_iterator operator--(int) { base::operator--(int()); return *this; }

    private:
      view const * view_;
    };



    view() {}

    void set_base_container( base_container_type & base_container_ )
    { base_container = &base_container_; }

    template<typename other_container_tag>
    void set_base_container( view<base_container_type, other_container_tag> & base_view )
    { base_container = base_view.base_container; }

    template<typename other_container_tag>
    void set_base_container( view<base_container_type, other_container_tag> const & base_view )
    { base_container = base_view.base_container; }


    iterator begin() { return iterator(*this, handle_container.begin()); }
    iterator end() { return iterator(*this, handle_container.end()); }

    const_iterator cbegin() { return const_iterator(*this, handle_container.begin()); }
    const_iterator cend() { return const_iterator(*this, handle_container.end()); }

    const_iterator begin() const { return const_iterator(*this, handle_container.begin()); }
    const_iterator end() const { return const_iterator(*this, handle_container.end()); }


    reference dereference_handle( handle_type handle ) { return viennagrid::detail::dereference_handle( *base_container, handle ); }
    const_reference dereference_handle( const_handle_type handle ) const { return viennagrid::detail::dereference_handle_const( *base_container, handle ); }

    handle_type handle( reference element ) { return &element; }
    const_handle_type handle( const_reference element ) const { return &element; }

    iterator find( const_reference element )
    { return iterator(*this, handle_container.find(const_cast<handle_type>(handle(element)))); }
    const_iterator find( const_reference element ) const
    { return const_iterator(*this, handle_container.find(const_cast<handle_type>(handle(element)))); }

    reference front() { return dereference_handle(handle_container.front()); }
    const_reference front() const { return dereference_handle(handle_container.front()); }

    reference back() { return dereference_handle(handle_container.back()); }
    const_reference back() const { return dereference_handle(handle_container.back()); }

    reference operator[]( size_type index ) { iterator it = begin(); std::advance(it, static_cast<long>(index)); return *it; }
    const_reference operator[]( size_type index ) const { const_iterator it = begin(); std::advance(it, static_cast<long>(index)); return *it; }


    size_type size() const { return handle_container.size(); }
    void resize(size_type size_) { handle_container.resize(size_); }
    void increment_size() { resize( size()+1 ); }

    bool empty() const { return handle_container.empty(); }
    void clear() { handle_container.clear(); }


    void insert_unique_handle(handle_type handle)
    {
      insert_handle(handle);
    }

    void insert_handle(handle_type handle)
    {
      viennagrid::detail::insert(handle_container, handle);
    }
    void set_handle( handle_type element, size_type pos ); // not supported
    void erase_handle(handle_type handle)
    {
      for (iterator it = begin(); it != end(); ++it)
        if (it.handle() == handle)
        {
          handle_container.erase( it );
          return;
        }
    }

    handle_type handle_at(std::size_t pos) { return viennagrid::advance(begin(), pos).handle(); }
    const_handle_type handle_at(std::size_t pos) const { return viennagrid::advance(begin(), pos).handle(); }

  private:
    handle_container_type handle_container;
    base_container_type * base_container;
  };
  /** \endcond */






  namespace result_of
  {
    /** @brief Metafunction for returning a view on a container using the respective container for holding the references inside the view
      *
      * @tparam base_container_type    The container type from which the view is derived
      * @tparam view_container_tag     The tag for selecting the container inside the view, e.g. std_vector_tag or std_map_tag
      */
    template<typename base_container_type, typename view_container_tag>
    struct view
    {
      typedef viennagrid::view<base_container_type, view_container_tag> type;
    };

    /** \cond */
    template<typename base_container_type, typename base_view_container_tag, typename view_container_tag>
    struct view< viennagrid::view<base_container_type, base_view_container_tag>, view_container_tag>
    {
      typedef viennagrid::view<base_container_type, view_container_tag> type;
    };

    template<typename base_container_type, typename base_view_container_tag, typename view_container_tag>
    struct view< const viennagrid::view<base_container_type, base_view_container_tag>, view_container_tag>
    {
      typedef viennagrid::view<const base_container_type, view_container_tag> type;
    };

    template<typename base_container_type, typename base_view_container_tag, typename view_container_tag>
    struct view< const viennagrid::view<const base_container_type, base_view_container_tag>, view_container_tag>
    {
      typedef viennagrid::view<const base_container_type, view_container_tag> type;
    };

    template<typename base_container_type, typename base_view_container_tag, typename view_container_tag>
    struct view< viennagrid::view<const base_container_type, base_view_container_tag>, view_container_tag>
    {
      typedef viennagrid::view<const base_container_type, view_container_tag> type;
    };

    template<typename base_container_type, typename view_container_config>
    typename view<base_container_type, view_container_config>::type view_of( base_container_type & base_container )
    {
      typename view<base_container_type, view_container_config>::type tmp;
      tmp.set_base_container(base_container);
      return tmp;
    }
    /** \endcond */
  }



  namespace detail
  {

    template<typename base_container_type, typename view_base_container_type, typename handle_container_tag, typename predicate>
    void handle_if(base_container_type & src_container, viennagrid::view<view_base_container_type, handle_container_tag> & dst_view, predicate pred)
    {
      for (typename base_container_type::iterator it = src_container.begin(); it != src_container.end(); ++it)
        if (pred(*it))
          dst_view.insert_handle( it.handle() );
    }

    template<typename base_container_type, typename view_base_container_type, typename view_container_tag>
    void handle(base_container_type & src_container, viennagrid::view<view_base_container_type, view_container_tag> & dst_view)
    {
      handle_if(src_container, dst_view, viennagrid::detail::true_predicate());
    }

  }


  namespace result_of
  {

    /** \cond */
    template<typename container_type, typename view_container_config>
    struct view_container_tag
    {
      typedef typename container_type::value_type value_type;
      typedef typename viennagrid::detail::result_of::find<view_container_config, value_type>::type search_result;
      typedef typename viennagrid::detail::result_of::find<view_container_config, viennagrid::default_tag>::type default_container;

      typedef typename viennagrid::detail::IF<
          !viennagrid::detail::EQUAL<search_result, viennagrid::not_found>::value,
          search_result,
          default_container
      >::type::second type;
    };


    template<typename container_typemap, typename view_container_config>
    struct view_container_typemap;

    template<typename view_container_config>
    struct view_container_typemap<viennagrid::null_type, view_container_config>
    {
      typedef viennagrid::null_type type;
    };

    template<typename value_type, typename container_type, typename tail, typename view_container_config>
    struct view_container_typemap<viennagrid::typelist< viennagrid::static_pair<value_type, container_type>, tail>, view_container_config>
    {
      typedef viennagrid::typelist<
          viennagrid::static_pair<
              value_type,
              typename viennagrid::result_of::view<
                  container_type,
                  typename view_container_tag<container_type, view_container_config>::type
              >::type
          >,
          typename view_container_typemap<tail, view_container_config>::type
      > type;
    };

    template<typename container_typemap, typename view_container_config>
    struct view_collection
    {
      typedef collection<
          typename viennagrid::result_of::view_container_typemap<
              container_typemap,
              view_container_config
          >::type
      > type;
    };

    template<typename container_typelist, typename view_container_config>
    struct view_collection< viennagrid::collection<container_typelist>, view_container_config>
    {
      typedef viennagrid::collection<container_typelist> container_collection_type;

      typedef collection<
          typename viennagrid::result_of::view_container_typemap<
              container_typelist,
              view_container_config
          >::type
      > type;
    };
    /** \endcond */
  }


  namespace detail
  {
    template<typename BaseContainerT>
    typename view< BaseContainerT, std_set_tag<id_compare_tag> >::iterator find(view< BaseContainerT, std_set_tag<id_compare_tag> > & container, typename view< BaseContainerT, std_set_tag<id_compare_tag> >::value_type const & element)
    {
      return container.find(element);
//       typename view< BaseContainerT, std_set_tag<id_compare_tag> >::value_type tmp();
//       return typename view< BaseContainerT, std_set_tag<id_compare_tag> >::iterator(container, container.base_container->find(element));


//       return std::find_if(
//                   container.begin(),
//                   container.end(),
//                   viennagrid::detail::id_compare<typename view< BaseContainerT, std_set_tag<id_compare_tag> >::value_type::id_type>(id)
//           );
    }

    template<typename BaseContainerT>
    typename view< BaseContainerT, std_set_tag<id_compare_tag> >::const_iterator find(view< BaseContainerT, std_set_tag<id_compare_tag> > const & container, typename view< BaseContainerT, std_set_tag<id_compare_tag> >::value_type const & element)
    {
      return container.find(element);
//       return typename view< BaseContainerT, std_set_tag<id_compare_tag> >::const_iterator(container, container.base_container->find(element));
//       return std::find_if(
//                   container.begin(),
//                   container.end(),
//                   viennagrid::detail::id_compare<typename view< BaseContainerT, std_set_tag<id_compare_tag> >::value_type::id_type>(element)
//           );
    }




    /** @brief Helper class for set_base_container() */
    template<typename container_collection_typemap>
    struct set_base_container_helper;

    /** \cond */
    template<>
    struct set_base_container_helper<viennagrid::null_type>
    {
      template<typename base_container_collection_type, typename view_container_collection_type>
      static void exec( base_container_collection_type &, view_container_collection_type & ) {}
    };

    template<typename value_type, typename container_type, typename tail>
    struct set_base_container_helper< viennagrid::typelist< viennagrid::static_pair<value_type, container_type>, tail > >
    {
      template<typename base_container_collection_type, typename view_container_collection_type>
      static void exec( base_container_collection_type & base_container_collection, view_container_collection_type & view_container_collection )
      {
        get<value_type>(view_container_collection).set_base_container( get<value_type>(base_container_collection) );

        set_base_container_helper<tail>::exec(base_container_collection, view_container_collection);
      }
    };
    /** \endcond */
  }

  /** @brief Sets the reference to the parent container for a view. Also supports views of views, etc. */
  template<typename base_container_collection_type, typename view_container_collection_type>
  void set_base_container( base_container_collection_type & base_container_collection, view_container_collection_type & view_container_collection )
  {
    detail::set_base_container_helper< typename view_container_collection_type::typemap >::exec(base_container_collection, view_container_collection);
  }


}

#endif
