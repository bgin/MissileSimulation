#ifndef VIENNAGRID_STORAGE_RANGE_HPP
#define VIENNAGRID_STORAGE_RANGE_HPP

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
#include "viennagrid/storage/container.hpp"

/** @file viennagrid/storage/range.hpp
    @brief Allows to deal with a subset of a container
*/

namespace viennagrid
{

  namespace detail
  {
    template<typename container_type>
    class container_range_wrapper
    {
      friend class container_range_wrapper<const container_type>;

    public:

      typedef container_type base_container_type;

      typedef typename container_type::size_type  size_type;
      typedef typename container_type::value_type value_type;
      typedef typename viennagrid::result_of::id<value_type>::type id_type;

      typedef typename container_type::reference             reference;
      typedef typename container_type::const_reference const_reference;

      typedef typename container_type::pointer             pointer;
      typedef typename container_type::const_pointer const_pointer;

      typedef typename container_type::iterator             iterator;
      typedef typename container_type::const_iterator const_iterator;

      typedef typename container_type::reverse_iterator             reverse_iterator;
      typedef typename container_type::const_reverse_iterator const_reverse_iterator;


      container_range_wrapper(container_type & container) : container_(&container) {}


      template<typename WrappedConfigT>
      container_range_wrapper( mesh<WrappedConfigT> & mesh_obj )
      { *this = elements<value_type>(mesh_obj); }

      template<typename WrappedConfigT>
      container_range_wrapper( segmentation<WrappedConfigT> & segmentation_obj )
      { *this = elements<value_type>(segmentation_obj); }

      template<typename SegmentationT>
      container_range_wrapper( segment_handle<SegmentationT> & segment_obj )
      { *this = elements<value_type>(segment_obj); }

      template<typename ElementTagT, typename WrappedConfigT>
      container_range_wrapper( element<ElementTagT, WrappedConfigT> & element_obj )
      { *this = elements<value_type>(element_obj); }

      iterator       begin()       { return container_->begin(); }
      const_iterator begin() const { return container_->begin(); }
      iterator       end()         { return container_->end(); }
      const_iterator end()   const { return container_->end(); }

      reverse_iterator       rbegin()       { return container_->rbegin(); }
      const_reverse_iterator rbegin() const { return container_->rbegin(); }
      reverse_iterator       rend()         { return container_->rend(); }
      const_reverse_iterator rend()   const { return container_->rend(); }



      reference front()             { return container_->front(); }
      const_reference front() const { return container_->front(); }
      reference back()              { return container_->back(); }
      const_reference back()  const { return container_->back(); }



      iterator find( id_type const & id )
      { return viennagrid::detail::find(*container_, id); }
      const_iterator find( id_type const & id ) const
      { return viennagrid::detail::find(*container_, id); }

      iterator find( value_type const & element )
      { return viennagrid::detail::find(*container_, element); }
      const_iterator find( value_type const & element ) const
      { return viennagrid::detail::find(*container_, element); }





      reference operator[] (size_type index)
      { iterator it = begin(); std::advance(it, static_cast<long>(index)); return *it; }
      const_reference operator[] (size_type index) const
      { const_iterator it = begin(); std::advance(it, static_cast<long>(index)); return *it; }



      bool     empty() const { return container_->empty(); }
      size_type size() const { return container_->size(); }


      typedef typename container_type::handle_type             handle_type;
      typedef typename container_type::const_handle_type const_handle_type;


      iterator erase( iterator pos ) { return container_->erase( pos ); }




      handle_type handle_at(std::size_t pos)
      { return viennagrid::advance(begin(), pos).handle(); }
      const_handle_type handle_at(std::size_t pos) const
      { return viennagrid::advance(begin(), pos).handle(); }


      void erase_handle(handle_type handle)
      { container_->erase_handle(handle); }
      void insert_unique_handle(handle_type handle)
      { container_->insert_unique_handle(handle); }
      void insert_handle(handle_type handle)
      { container_->insert_handle(handle); }
      void set_handle_at(handle_type handle, std::size_t pos)
      { container_->set_handle(handle, pos); }

            container_type * get_base_container()       { return container_; }
      const container_type * get_base_container() const { return container_; }

    private:

      container_type * container_;
    };

    template<typename container_type>
    class container_range_wrapper<const container_type>
    {
    public:

      typedef const container_type base_container_type;

      typedef typename container_type::size_type size_type;
      typedef typename container_type::value_type value_type;
      typedef typename viennagrid::result_of::id<value_type>::type id_type;

      typedef typename container_type::const_reference reference;
      typedef typename container_type::const_reference const_reference;

      typedef typename container_type::const_pointer pointer;
      typedef typename container_type::const_pointer const_pointer;

      typedef typename container_type::const_iterator iterator;
      typedef typename container_type::const_iterator const_iterator;

      typedef typename container_type::const_reverse_iterator reverse_iterator;
      typedef typename container_type::const_reverse_iterator const_reverse_iterator;


      container_range_wrapper(const container_type & container) : container_(&container) {}
      container_range_wrapper(const container_range_wrapper<container_type> & rhs) : container_(rhs.container_) {}

      template<typename WrappedConfigT>
      container_range_wrapper( mesh<WrappedConfigT> & mesh_obj )
      { *this = elements<value_type>(mesh_obj); }

      template<typename WrappedConfigT>
      container_range_wrapper( segmentation<WrappedConfigT> & segmentation_obj )
      { *this = elements<value_type>(segmentation_obj); }

      template<typename SegmentationT>
      container_range_wrapper( segment_handle<SegmentationT> & segment_obj )
      { *this = elements<value_type>(segment_obj); }

      template<typename ElementTagT, typename WrappedConfigT>
      container_range_wrapper( element<ElementTagT, WrappedConfigT> & element_obj )
      { *this = elements<value_type>(element_obj); }



      template<typename WrappedConfigT>
      container_range_wrapper( mesh<WrappedConfigT> const & mesh_obj )
      { *this = elements<value_type>(mesh_obj); }

      template<typename WrappedConfigT>
      container_range_wrapper( segmentation<WrappedConfigT> const & segmentation_obj )
      { *this = elements<value_type>(segmentation_obj); }

      template<typename SegmentationT>
      container_range_wrapper( segment_handle<SegmentationT> const & segment_obj )
      { *this = elements<value_type>(segment_obj); }

      template<typename ElementTagT, typename WrappedConfigT>
      container_range_wrapper( element<ElementTagT, WrappedConfigT> const & element_obj )
      { *this = elements<value_type>(element_obj); }


            iterator begin()       { return container_->begin(); }
      const_iterator begin() const { return container_->begin(); }
            iterator end()         { return container_->end(); }
      const_iterator end()   const { return container_->end(); }

            reverse_iterator rbegin()       { return container_->rbegin(); }
      const_reverse_iterator rbegin() const { return container_->rbegin(); }
            reverse_iterator rend()         { return container_->rend(); }
      const_reverse_iterator rend()   const { return container_->rend(); }



            reference front()       { return container_->front(); }
      const_reference front() const { return container_->front(); }
            reference back()        { return container_->back(); }
      const_reference back()  const { return container_->back(); }



      const_iterator find( id_type const & id ) const
      { return viennagrid::detail::find(*container_, id); }

      const_iterator find( value_type const & element ) const
      { return viennagrid::detail::find(*container_, element); }



      reference operator[] (size_type index)
      { iterator it = begin(); std::advance(it, static_cast<long>(index)); return *it; }
      const_reference operator[] (size_type index) const
      { const_iterator it = begin(); std::advance(it, static_cast<long>(index)); return *it; }



      bool empty() const { return container_->empty(); }
      size_type size() const { return container_->size(); }



      typedef typename container_type::const_handle_type handle_type;
      typedef typename container_type::const_handle_type const_handle_type;

      handle_type handle_at(std::size_t pos)
      { return viennagrid::advance(begin(), pos).handle(); }
      const_handle_type handle_at(std::size_t pos) const
      { return viennagrid::advance(begin(), pos).handle(); }

      const container_type * get_base_container() const { return container_; }

    private:

      const container_type * container_;
    };



    template<typename iterator_type>
    class forward_iterator_range
    {
    public:

      forward_iterator_range(iterator_type first, iterator_type last) : first_(first), last_(last) {}

      typedef typename iterator_type::T value_type;

      typedef       typename iterator_type::Reference       reference;
      typedef const typename iterator_type::Reference const_reference;

      typedef       typename iterator_type::Pointer       pointer;
      typedef const typename iterator_type::Pointer const_pointer;

      typedef       iterator_type       iterator;
      typedef const iterator_type const_iterator;



            iterator begin()       { return first_; }
      const_iterator begin() const { return first_; }
            iterator end()         { return last_; }
      const_iterator end()   const { return last_; }


            reference front()       { return *first_; }
      const_reference front() const { return *first_; }
            reference back()        { iterator_type tmp = last_; return *(--tmp); }
      const_reference back()  const { iterator_type tmp = last_; return *(--tmp); }

      bool empty() const { return first_ == last_; }

    private:
      iterator_type first_;
      iterator_type last_;
    };

  }

}

#endif

