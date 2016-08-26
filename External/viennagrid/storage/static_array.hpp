#ifndef VIENNAGRID_STORAGE_STATIC_ARRAY_HPP
#define VIENNAGRID_STORAGE_STATIC_ARRAY_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include <cassert>
#include <cstddef>
#include <iterator>

/** @file viennagrid/storage/static_array.hpp
    @brief Defines an array of fixed size similar similar to std::array<> (which, unfortunately, is only available in C++11)
*/

namespace viennagrid
{
  /** @brief Reimplementation of std::array<> because we cannot reasonably expect that C++11 is available on all target machines */
  template<typename T, int N>
  class static_array
  {
    T elements_[N];    // fixed-size array of elements of type T

  public:
    // type definitions
    typedef T              value_type;
    typedef T*             pointer;
    typedef const T*       const_pointer;

    typedef T&             reference;
    typedef const T&       const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    class const_iterator;

    static_array()
    {
      for (std::size_t i=0; i<static_cast<size_t>(N); ++i)
        elements_[i] = T();
    }

    // random access iterator: http://www.cplusplus.com/reference/std/iterator/RandomAccessIterator/
    class iterator
    {
      friend class const_iterator;
    public:

      typedef std::size_t difference_type;
      typedef typename static_array::value_type value_type;
      typedef typename static_array::pointer pointer;
      typedef typename static_array::reference reference;
      typedef typename static_array::const_reference const_reference;
      typedef std::random_access_iterator_tag iterator_category;

      // default-constructable
      iterator() : ptr_(0) {}

      // copy- and copy-constructable
      iterator(const iterator & it) : ptr_(it.ptr_) {}
      iterator & operator=(const iterator & it) { ptr_ = it.ptr_; return *this; }

      // constructor for static_array
      iterator(pointer ptr) : ptr_(ptr) {}

      // equal and inequal compareable
      bool operator==(const iterator& i) const { return ptr_ == i.ptr_; }
      bool operator!=(const iterator& i) const { return ptr_ != i.ptr_; }

      bool operator==(const const_iterator & it) const;
      bool operator!=(const const_iterator & it) const;

      // dereferenceable
      reference operator*() const { return *ptr_; }
      pointer operator->() const { return ptr_; }

      // increment- and decrementable
      iterator & operator++() { ++ptr_; return *this; }
      iterator operator++(int) { iterator tmp = *this; ++*this; return tmp; }

      iterator & operator--() { --ptr_; return *this; }
      iterator operator--(int) { iterator tmp = *this; --*this; return tmp; }

      // add and subtractable; operator+ and operator- is below
      difference_type operator-(const iterator & it) const { return ptr_ - it.ptr_; }
      difference_type operator-(const const_iterator & it) const { return ptr_ - it.ptr_; }

      // less and greater compareable
      bool operator<(const iterator & it) const { return ptr_ < it.ptr; }
      bool operator<=(const iterator & it) const { return ptr_ <= it.ptr; }

      bool operator>(const iterator & it) const { return ptr_ > it.ptr; }
      bool operator>=(const iterator & it) const { return ptr_ >= it.ptr; }

      bool operator<(const const_iterator & it) const { return ptr_ < it.ptr; }
      bool operator<=(const const_iterator & it) const { return ptr_ <= it.ptr; }

      bool operator>(const const_iterator & it) const { return ptr_ > it.ptr; }
      bool operator>=(const const_iterator & it) const { return ptr_ >= it.ptr; }

      // compound assign add- and subtractable
      iterator & operator+=(long diff) { ptr_ += diff; return *this; }
      iterator & operator-=(long diff) { ptr_ -= diff; return *this; }

      iterator operator+(long diff) { iterator tmp(*this); tmp += diff; return tmp; }
      iterator operator-(long diff) { iterator tmp(*this); tmp -= diff; return tmp; }

      // offset dereferenceable
      reference operator[](std::size_t offset) { return *(ptr_+offset); }
      const_reference operator[](std::size_t offset) const { return *(ptr_+offset); }

    private:
      pointer ptr_;
    };

    class const_iterator
    {
      friend class iterator;
    public:

      typedef std::size_t difference_type;
      typedef typename static_array::value_type value_type;
      typedef typename static_array::const_pointer pointer;
      typedef typename static_array::const_reference reference;
      typedef std::random_access_iterator_tag iterator_category;


      // default-constructable
      const_iterator() : ptr_(0) {}

      // copy- and copy-constructable
      const_iterator(const const_iterator & it) : ptr_(it.ptr_) {}
      const_iterator(iterator it) : ptr_(it.ptr_) {}
      const_iterator & operator=(const iterator & it) { ptr_ = it.ptr_; return *this; }
      const_iterator & operator=(const const_iterator & it) { ptr_ = it.ptr_; return *this; }

      // constructor for static_array
      const_iterator(const_pointer ptr) : ptr_(ptr) {}

      // equal and inequal compareable
      bool operator==(const const_iterator& i) const { return ptr_ == i.ptr_; }
      bool operator!=(const const_iterator& i) const { return ptr_ != i.ptr_; }

      bool operator==(const iterator & i) const { return ptr_ == i.ptr_; }
      bool operator!=(const iterator & i) const { return ptr_ != i.ptr_; }

      // dereferenceable
      reference operator*() const { return *ptr_; }
      pointer operator->() const { return ptr_; }


      // increment- and decrementable
      const_iterator & operator++() { ++ptr_; return *this; }
      const_iterator operator++(int) { const_iterator tmp = *this; ++*this; return tmp; }

      const_iterator & operator--() { --ptr_; return *this; }
      const_iterator operator--(int) { const_iterator tmp = *this; --*this; return tmp; }

      // add and subtractable; operator+ and operator- is below
      difference_type operator-(const iterator & it) const { return ptr_ - it.ptr_; }
      difference_type operator-(const const_iterator & it) const { return ptr_ - it.ptr_; }

      // less and greater compareable
      bool operator<(const iterator & it) const { return ptr_ < it.ptr; }
      bool operator<=(const iterator & it) const { return ptr_ <= it.ptr; }

      bool operator>(const iterator & it) const { return ptr_ > it.ptr; }
      bool operator>=(const iterator & it) const { return ptr_ >= it.ptr; }

      bool operator<(const const_iterator & it) const { return ptr_ < it.ptr; }
      bool operator<=(const const_iterator & it) const { return ptr_ <= it.ptr; }

      bool operator>(const const_iterator & it) const { return ptr_ > it.ptr; }
      bool operator>=(const const_iterator & it) const { return ptr_ >= it.ptr; }

      // compound assign add- and subtractable
      const_iterator & operator+=(long diff) { ptr_ += diff; return *this; }
      const_iterator & operator-=(long diff) { ptr_ -= diff; return *this; }

      const_iterator operator+(long diff) { const_iterator tmp(*this); tmp += diff; return tmp; }
      const_iterator operator-(long diff) { const_iterator tmp(*this); tmp -= diff; return tmp; }

      // offset dereferenceable
      reference operator[](std::size_t offset) { return *(ptr_+offset); }

    private:
      pointer ptr_;
    };

    // iterator support
    iterator        begin()       { return iterator(elements_); }
    const_iterator  begin() const { return const_iterator(elements_); }
    const_iterator cbegin() const { return const_iterator(elements_); }

    iterator        end()       { return iterator(elements_+N); }
    const_iterator  end() const { return const_iterator(elements_+N); }
    const_iterator cend() const { return const_iterator(elements_+N); }

    // reverse iterator support
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const {
      return const_reverse_iterator(end());
    }
    const_reverse_iterator crbegin() const {
      return const_reverse_iterator(end());
    }

    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const {
      return const_reverse_iterator(begin());
    }
    const_reverse_iterator crend() const {
      return const_reverse_iterator(begin());
    }

    // operator[]
    reference operator[](size_type i)
    {
      assert( i < N && "out of range" );
      return elements_[i];
    }

    const_reference operator[](size_type i) const
    {
      assert( i < N && "out of range" );
      return elements_[i];
    }

    // at() with range check
    reference at(size_type i) { assert( i < N && "out of range" );  return elements_[i]; }
    const_reference at(size_type i) const { assert( i < N && "out of range" );  return elements_[i]; }

    // front() and back()
    reference front()
    {
      return elements_[0];
    }

    const_reference front() const
    {
      return elements_[0];
    }

    reference back()
    {
      return elements_[N-1];
    }

    const_reference back() const
    {
      return elements_[N-1];
    }

    // size is constant
    static size_type size() { return N; }
    static void resize(size_type s) { assert( s <= N ); (void)s; }

    static bool empty() { return false; }
    static size_type max_size() { return N; }
    static const int static_size = N;

    // swap (note: linear complexity)
    void swap (static_array<T,N>& y) {
      for (size_type i = 0; i < N; ++i)
        std::swap(elements_[i],y.elements_[i]);
    }

    // direct access to data (read-only)
    const T* data() const { return elements_; }
    T* data() { return elements_; }

    // use static_array as C array (direct read/write access to data)
    T* c_array() { return elements_; }

    // assignment with type conversion
    template <typename T2>
    static_array<T,N>& operator= (const static_array<T2,N>& rhs) {
      std::copy(rhs.begin(),rhs.end(), begin());
      return *this;
    }

    // assign one value to all elements
    void assign (const T& value) { fill ( value ); }    // A synonym for fill
    void fill   (const T& value)
    {
      std::fill_n(begin(),size(),value);
    }

  };

  // comparisons
  template<class T, std::size_t N>
  bool operator== (const static_array<T,N>& x, const static_array<T,N>& y) {
    return std::equal(x.begin(), x.end(), y.begin());
  }
  template<class T, std::size_t N>
  bool operator< (const static_array<T,N>& x, const static_array<T,N>& y) {
    return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
  }
  template<class T, std::size_t N>
  bool operator!= (const static_array<T,N>& x, const static_array<T,N>& y) {
    return !(x==y);
  }
  template<class T, std::size_t N>
  bool operator> (const static_array<T,N>& x, const static_array<T,N>& y) {
    return y<x;
  }
  template<class T, std::size_t N>
  bool operator<= (const static_array<T,N>& x, const static_array<T,N>& y) {
    return !(y<x);
  }
  template<class T, std::size_t N>
  bool operator>= (const static_array<T,N>& x, const static_array<T,N>& y) {
    return !(x<y);
  }

  // global swap()
  /** @brief Swaps the entries of the two arrays. */
  template<class T, std::size_t N>
  inline void swap (static_array<T,N>& x, static_array<T,N>& y) {
    x.swap(y);
  }

}

#endif
