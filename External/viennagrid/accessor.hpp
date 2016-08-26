#ifndef VIENNAGRID_ACCESSOR_HPP
#define VIENNAGRID_ACCESSOR_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include <stdexcept>
#include <assert.h>

#include "viennagrid/forwards.hpp"
#include "viennagrid/storage/id.hpp"
#include "viennagrid/storage/container_collection.hpp"

/** @file viennagrid/accessor.hpp
    @brief Defines various accessors for storing data for the different element types.
*/

#ifdef VIENNAGRID_WITH_VIENNADATA
#include "viennadata/api.hpp"


namespace viennadata
{
  namespace result_of
  {
    template<typename value_type, typename base_id_type>
    struct offset< viennagrid::storage::smart_id<value_type, base_id_type> >
    {
      typedef viennagrid::storage::smart_id<value_type, base_id_type> id_type;
      typedef base_id_type type;

      static type get(id_type const & id) { return id.get(); }
    };
  }
}
#endif


namespace viennagrid
{
  /** @brief Accessor class for the data members appended (injected) to an element */
  template<typename value_type_, typename element_type>
  class appendix_accessor
  {
  public:
      typedef value_type_ value_type;
      typedef element_type access_type;

      bool is_valid() const { return true; }

      value_type       * find( access_type & element )              { return &element.appendix(); }
      value_type const * find( access_type const & element )  const { return &element.appendix(); }

      value_type       & at( access_type & element )             { return element.appendix(); }
      value_type const & at( access_type const & element ) const { return element.appendix(); }

      value_type       & operator()( access_type & element )             { return at(element); }
      value_type const & operator()( access_type const & element ) const { return at(element); }
  };


  namespace result_of
  {

    /** @brief Metafunction returning the default point accessor type for a vertex. */
    template<typename mesh_or_element_type>
    struct default_point_accessor
    {
      typedef viennagrid::appendix_accessor<
        typename viennagrid::result_of::point<mesh_or_element_type>::type,
        typename viennagrid::result_of::vertex<mesh_or_element_type>::type
      > type;
    };

  }

  /** @brief Convenience function for returning the default point accessor (i.e. accessing the point stored in the element's appendix) for a mesh or element. */
  template<typename mesh_or_element_type>
  typename result_of::default_point_accessor<mesh_or_element_type>::type default_point_accessor( mesh_or_element_type const & )
  {
    return viennagrid::appendix_accessor<
      typename viennagrid::result_of::point<mesh_or_element_type>::type,
      typename viennagrid::result_of::vertex<mesh_or_element_type>::type
    >();
  }


  namespace result_of
  {
    /** @brief Returns the underlying container type for storing data of type 'ValueT' on elements of type 'ElementT'.
      *
      * @tparam ElementT       The element type, e.g. a cell
      * @tparam ValueT         Type of the data to be stored
      * @tparam ContainerTagT  A tag selecting the appropriate container, e.g. std_vector_tag or std_map_tag
      */
    template<typename ElementT, typename ValueT, typename ContainerTagT = std_vector_tag>
    struct accessor_container {};

    /** \cond */
    template<typename ElementT, typename ValueT>
    struct accessor_container<ElementT, ValueT, std_vector_tag>
    {
      typedef std::vector<ValueT> type;
    };

    template<typename ElementT, typename ValueT>
    struct accessor_container<ElementT, ValueT, std_deque_tag>
    {
      typedef std::deque<ValueT> type;
    };

    template<typename ElementT, typename ValueT>
    struct accessor_container<ElementT, ValueT, std_map_tag>
    {
      typedef std::map< typename result_of::id<ElementT>::type, ValueT > type;
    };
    /** \endcond */
  }




  struct id_unpack
  {
    template<typename ElementT>
    typename viennagrid::result_of::id<ElementT>::type operator()(ElementT const & element) const
    { return element.id(); }
  };

  struct base_id_unpack
  {
    template<typename ElementT>
    typename viennagrid::result_of::id<ElementT>::type::base_id_type operator()(ElementT const & element) const
    { return element.id().get(); }
  };

  namespace result_of
  {
    template<typename ContainerT>
    struct unpack;

    template<typename T, typename Alloc>
    struct unpack< std::vector<T, Alloc> >
    {
      typedef base_id_unpack type;
    };

    template<typename T, typename Alloc>
    struct unpack< const std::vector<T, Alloc> >
    {
      typedef base_id_unpack type;
    };

    template<typename T, typename Alloc>
    struct unpack< std::deque<T, Alloc> >
    {
      typedef base_id_unpack type;
    };

    template<typename T, typename Alloc>
    struct unpack< const std::deque<T, Alloc> >
    {
      typedef base_id_unpack type;
    };

    template<typename Key, typename T, typename Compare, typename Alloc>
    struct unpack< std::map<Key, T, Compare, Alloc> >
    {
      typedef id_unpack type;
    };

    template<typename Key, typename T, typename Compare, typename Alloc>
    struct unpack< const std::map<Key, T, Compare, Alloc> >
    {
      typedef id_unpack type;
    };
  }




  /** @brief Implementation of an accessor for dense containers (most importantly std::vector, std::deque) which fulfills the accessor concept.
    *
    * @tparam   ContainerType    The underlying container type (e.g. std::vector<>)
    * @tparam   AccessType       The element from which data should be accessed
    */
  template<typename ContainerType, typename AccessType, typename UnpackT = base_id_unpack>
  class dense_container_accessor
  {
  public:

    typedef ContainerType                                           container_type;
    typedef typename ContainerType::value_type                      value_type;
    typedef AccessType                                              access_type;

    typedef typename ContainerType::reference       reference;
    typedef typename ContainerType::const_reference const_reference;

    typedef typename ContainerType::pointer         pointer;
    typedef typename ContainerType::const_pointer   const_pointer;

    typedef typename access_type::id_type::base_id_type offset_type;

    dense_container_accessor() : container(0) {}
    dense_container_accessor( ContainerType & container_ ) : container(&container_) {}

    bool is_valid() const { return container != NULL; }

    pointer find(AccessType const & element)
    {
      offset_type offset = unpack(element);
      return (static_cast<offset_type>((*container).size()) > unpack(element)) ? (&(*container)[static_cast<std::size_t>(offset)]) : NULL;
    }

    const_pointer find(AccessType const & element) const
    {
      offset_type offset = unpack(element);
      return (static_cast<offset_type>((*container).size()) > unpack(element)) ? (&(*container)[static_cast<std::size_t>(offset)]) : NULL;
    }

    reference operator()(AccessType const & element)
    {
      offset_type offset = unpack(element);
      if ( static_cast<offset_type>((*container).size()) <= offset) (*container).resize(static_cast<std::size_t>(offset+1));
      return (*container)[static_cast<std::size_t>(offset)];
    }

    const_reference operator()(AccessType const & element) const
    {
      offset_type offset = unpack(element);
      assert( static_cast<offset_type>((*container).size()) > offset );
      return (*container)[static_cast<std::size_t>(offset)];
    }

    reference at(AccessType const & element)
    {
      offset_type offset = unpack(element);
      if ( static_cast<offset_type>((*container).size()) <= offset) throw std::out_of_range("dense_container_accessor::at() failed");
      return (*container)[static_cast<std::size_t>(offset)];
    }

    const_reference at(AccessType const & element) const
    {
      offset_type offset = unpack(element);
      if ( static_cast<offset_type>((*container).size()) <= offset) throw std::out_of_range("dense_container_accessor::at() const failed");
      return (*container)[static_cast<std::size_t>(offset)];
    }

  protected:
    UnpackT unpack;
    ContainerType * container;
  };


  /** \cond */
  template<typename ContainerType, typename AccessType, typename UnpackT>
  class dense_container_accessor<const ContainerType, AccessType, UnpackT>
  {
  public:

    typedef const ContainerType                                     container_type;
    typedef typename ContainerType::value_type                      value_type;
    typedef AccessType                                              access_type;

    typedef typename ContainerType::const_reference       reference;
    typedef typename ContainerType::const_reference const_reference;

    typedef typename ContainerType::const_pointer         pointer;
    typedef typename ContainerType::const_pointer   const_pointer;

    typedef typename access_type::id_type::base_id_type offset_type;

    dense_container_accessor() : container(0) {}
    dense_container_accessor( container_type & container_ ) : container(&container_) {}

    bool is_valid() const { return container != NULL; }

    const_pointer find(AccessType const & element) const
    {
      offset_type offset = unpack(element);
      return (static_cast<offset_type>((*container).size()) > unpack(element)) ? (&(*container)[static_cast<std::size_t>(offset)]) : NULL;
    }

    const_reference operator()(AccessType const & element) const
    {
      offset_type offset = unpack(element);
      assert( static_cast<offset_type>((*container).size()) > offset );
      return (*container)[static_cast<std::size_t>(offset)];
    }

    const_reference at(AccessType const & element) const
    {
      offset_type offset = unpack(element);
      if ( static_cast<offset_type>((*container).size()) <= offset) throw std::out_of_range("dense_container_accessor::at() const failed");
      return (*container)[static_cast<std::size_t>(offset)];
    }

    void erase(AccessType const & element);
    void clear();
    void resize( std::size_t size );


  protected:
    UnpackT unpack;
    container_type * container;
  };
  /** \endcond */







  /** @brief  An accessor (fulfilling the accessor concept) for a container of interface similar to std::map<> */
  template<typename ContainerType, typename AccessType, typename UnpackT = id_unpack>
  class std_map_accessor
  {
  public:

    typedef ContainerType                                           container_type;
    typedef typename ContainerType::value_type::second_type         value_type;
    typedef typename ContainerType::value_type::first_type          key_type;
    typedef AccessType                                              access_type;

    typedef value_type &       reference;
    typedef value_type const & const_reference;

    typedef value_type *         pointer;
    typedef value_type const *   const_pointer;

    std_map_accessor() : container(0) {}
    std_map_accessor( ContainerType & container_ ) : container(&container_) {}

    bool is_valid() const { return container != NULL; }

    pointer find(AccessType const & element)
    {
      typename container_type::iterator it = (*container).find( unpack(element) );
      return (it != (*container).end()) ? &it->second : NULL; // return NULL if not found
    }

    const_pointer find(AccessType const & element) const
    {
      typename container_type::const_iterator it = (*container).find( unpack(element) );
      return (it != (*container).end()) ? &it->second : NULL; // return NULL if not found
    }

    reference operator()(AccessType const & element)
    {
      return (*container)[ unpack(element) ];
    }

    const_reference operator()(AccessType const & element) const
    {
      typename container_type::const_iterator it = (*container).find( unpack(element) );
      assert(it != (*container).end()); // no release-runtime check for accessing elements outside (*container)
      return it->second;
    }

    reference at(AccessType const & element)
    {
      return (*this)(element);
    }

    const_reference at(AccessType const & element) const
    {
      typename container_type::const_iterator it = (*container).find( unpack(element) );
      if (it == (*container).end()) throw std::out_of_range("std_map_accessor::at() const failed");
      return it->second;
    }

  protected:
    UnpackT unpack;
    ContainerType * container;
  };


  /** \cond */
  template<typename ContainerType, typename AccessType, typename UnpackT>
  class std_map_accessor<const ContainerType, AccessType, UnpackT>
  {
  public:

    typedef const ContainerType                                     container_type;
    typedef typename ContainerType::value_type::second_type         value_type;
    typedef typename ContainerType::value_type::first_type          key_type;
    typedef AccessType                                              access_type;

    typedef value_type const &       reference;
    typedef value_type const & const_reference;

    typedef value_type const *         pointer;
    typedef value_type const *   const_pointer;

    std_map_accessor() : container(0) {}
    std_map_accessor( container_type & container_ ) : container(&container_) {}

    bool is_valid() const { return container != NULL; }

    const_pointer find(AccessType const & element) const
    {
      typename container_type::const_iterator it = (*container).find( unpack(element) );
      return (it != (*container).end()) ? &it->second : NULL; // return NULL if not found
    }

    const_reference operator()(AccessType const & element) const
    {
      typename container_type::const_iterator it = (*container).find( unpack(element) );
      assert(it != (*container).end()); // no release-runtime check for accessing elements outside (*container)
      return it->second;
    }

    const_reference at(AccessType const & element) const
    {
      typename container_type::const_iterator it = (*container).find( unpack(element) );
      if (it == (*container).end()) throw std::out_of_range("std_map_accessor::at() const failed");
      return it->second;
    }

  protected:
    UnpackT unpack;
    container_type * container;
  };
  /** \endcond */



  namespace result_of
  {
    /** @brief Metafunction for retrieving the accessor type for a certain container and a certain object type from which to access data
      *
      * @tparam ContainerType   The container type for which the accessor should be obtained
      * @tparam AccessType      Type of the element which should be accessed, e.g. a vertex
      */
    template<typename ContainerType, typename AccessType, typename UnpackT = typename viennagrid::result_of::unpack<ContainerType>::type>
    struct accessor;

    /** \cond */
    template<typename T, typename Alloc, typename AccessType, typename UnpackT>
    struct accessor< std::vector<T, Alloc>, AccessType, UnpackT >
    {
      typedef viennagrid::dense_container_accessor<std::vector<T, Alloc>, AccessType, UnpackT> type;
    };

    template<typename T, typename Alloc, typename AccessType, typename UnpackT>
    struct accessor< const std::vector<T, Alloc>, AccessType, UnpackT >
    {
      typedef viennagrid::dense_container_accessor<const std::vector<T, Alloc>, AccessType, UnpackT> type;
    };

    template<typename T, typename Alloc, typename AccessType, typename UnpackT>
    struct accessor< std::deque<T, Alloc>, AccessType, UnpackT >
    {
      typedef viennagrid::dense_container_accessor<std::deque<T, Alloc>, AccessType, UnpackT> type;
    };

    template<typename T, typename Alloc, typename AccessType, typename UnpackT>
    struct accessor< const std::deque<T, Alloc>, AccessType, UnpackT >
    {
      typedef viennagrid::dense_container_accessor<const std::deque<T, Alloc>, AccessType, UnpackT> type;
    };

    template<typename Key, typename T, typename Compare, typename Alloc, typename AccessType, typename UnpackT>
    struct accessor< std::map<Key, T, Compare, Alloc>, AccessType, UnpackT >
    {
      typedef viennagrid::std_map_accessor<std::map<Key, T, Compare, Alloc>, AccessType, UnpackT> type;
    };

    template<typename Key, typename T, typename Compare, typename Alloc, typename AccessType, typename UnpackT>
    struct accessor< const std::map<Key, T, Compare, Alloc>, AccessType, UnpackT >
    {
      typedef viennagrid::std_map_accessor<const std::map<Key, T, Compare, Alloc>, AccessType, UnpackT> type;
    };
    /** \endcond */
  }


  /** @brief Convenience function for returning an accessor for the supplied container. Non-const version.
    *
    * @tparam AccessType      The element type for which data should be accessed (for example a vertex type)
    * @tparam ContainerType   The container type. Usually not supplied explicitly by the user.
    */
  template<typename AccessType, typename ContainerType>
  typename result_of::accessor<ContainerType, AccessType>::type make_accessor( ContainerType & container )
  {
    return typename result_of::accessor<ContainerType, AccessType>::type(container);
  }

  /** @brief Convenience function for returning an accessor for the supplied container. Const-version.
    *
    * @tparam AccessType      The element type for which data should be accessed (for example a vertex type)
    * @tparam ContainerType   The container type. Usually not supplied explicitly by the user.
    */
  template<typename AccessType, typename ContainerType>
  typename result_of::accessor<const ContainerType, AccessType>::type make_accessor( ContainerType const & container )
  {
    return typename result_of::accessor<const ContainerType, AccessType>::type(container);
  }



  /** @brief Convenience function for returning an accessor for the supplied container collection. Non-const-version.
    *
    * @tparam AccessType                    The element type for which data should be accessed (for example a vertex type)
    * @tparam ContainerCollectionTypemapT   Configuration typemap for the collection. To be deduced by the compiler, not passed explicitly.
    */
  template<typename AccessType, typename ContainerCollectionTypemapT>
  typename result_of::accessor<
      typename result_of::container_of<
          ContainerCollectionTypemapT,
          AccessType
      >::type,
      AccessType>::type make_accessor( collection<ContainerCollectionTypemapT> & collection_obj )
  {
    return make_accessor<AccessType>( get<AccessType>(collection_obj) );
  }

  /** @brief Convenience function for returning an accessor for the supplied container collection. Const-version.
    *
    * @tparam AccessType                    The element type for which data should be accessed (for example a vertex type)
    * @tparam ContainerCollectionTypemapT   Configuration typemap for the collection. To be deduced by the compiler, not passed explicitly.
    */
  template<typename AccessType, typename ContainerCollectionTypemapT>
  typename result_of::accessor<
      const typename result_of::container_of<
          ContainerCollectionTypemapT,
          AccessType
      >::type,
      AccessType>::type make_accessor( collection<ContainerCollectionTypemapT> const & collection_obj )
  {
    return make_accessor<AccessType>( get<AccessType>(collection_obj) );
  }



  /** @brief Base class for all dynamic accessor.
   *
   *  @tparam ValueType     The data type, e.g. double
   *  @tparam AccessType    The element for which data is accessed, e.g. a vertex
   */
  template<typename ValueType, typename AccessType>
  class base_dynamic_accessor
  {
  public:
    typedef ValueType  value_type;
    typedef AccessType access_type;

    typedef value_type       &       reference;
    typedef value_type const & const_reference;

    typedef value_type       *       pointer;
    typedef value_type const * const_pointer;

    virtual ~base_dynamic_accessor() {}

    virtual       pointer find( access_type const & ) { return 0; }
    virtual const_pointer find( access_type const & ) const { return 0; }

    virtual       reference operator()( access_type const & element ) = 0;
    virtual const_reference operator()( access_type const & element ) const = 0;

    virtual       reference at( access_type const & element ) = 0;
    virtual const_reference at( access_type const & element ) const = 0;
  };

  /** \cond */
  template<typename ValueType, typename AccessType>
  class base_dynamic_accessor<const ValueType, AccessType>
  {
  public:
    typedef ValueType value_type;
    typedef AccessType access_type;

    typedef value_type const & reference;
    typedef value_type const & const_reference;

    typedef value_type const * pointer;
    typedef value_type const * const_pointer;

    virtual ~base_dynamic_accessor() {}

    virtual const_pointer find( access_type const & ) const { return 0; }
    virtual const_reference operator()( access_type const & element ) const = 0;
    virtual const_reference at( access_type const & element ) const = 0;
  };
  /** \endcond */



  /** @brief A dynamic accessor class which wraps any user accessor type fulfilling the accessor concept.
    *
    * This can be used for storing different accessors to the same element type for data with the same value type in a common container.
    */
  template<typename AccessorType>
  class dynamic_accessor_wrapper : public base_dynamic_accessor< typename AccessorType::value_type, typename AccessorType::access_type >
  {
  public:
    typedef base_dynamic_accessor< typename AccessorType::value_type, typename AccessorType::access_type > BaseAccessorType;

    typedef typename BaseAccessorType::value_type value_type;
    typedef typename BaseAccessorType::access_type access_type;

    typedef typename BaseAccessorType::reference reference;
    typedef typename BaseAccessorType::const_reference const_reference;

    typedef typename BaseAccessorType::pointer pointer;
    typedef typename BaseAccessorType::const_pointer const_pointer;


    dynamic_accessor_wrapper(AccessorType accessor_) : accessor(accessor_) {}

    virtual pointer find( access_type const & element ) { return accessor.find(element); }
    virtual const_pointer find( access_type const & element ) const { return accessor.find(element); }

    virtual reference operator()( access_type const & element )       { return access(element); }
    virtual const_reference operator()( access_type const & element ) const { return access(element); }

    virtual reference at( access_type const & element ) { return accessor.access(element); }
    virtual const_reference at( access_type const & element ) const { return accessor.access(element); }

  private:
    AccessorType accessor;
  };

  /** \cond */
  template<typename AccessorType>
  class dynamic_accessor_wrapper<const AccessorType> : public base_dynamic_accessor< const typename AccessorType::value_type, typename AccessorType::access_type >
  {
  public:
    typedef base_dynamic_accessor< const typename AccessorType::value_type, typename AccessorType::access_type > BaseAccessorType;

    typedef typename BaseAccessorType::value_type value_type;
    typedef typename BaseAccessorType::access_type access_type;

    typedef typename BaseAccessorType::const_reference reference;
    typedef typename BaseAccessorType::const_reference const_reference;

    typedef typename BaseAccessorType::const_pointer pointer;
    typedef typename BaseAccessorType::const_pointer const_pointer;


    dynamic_accessor_wrapper(AccessorType accessor_) : accessor(accessor_) {}

    virtual const_pointer find( access_type const & element ) const { return accessor.find(element); }
    virtual const_reference operator()( access_type const & element ) const { return access(element); }
    virtual const_reference at( access_type const & element ) const { return accessor.access(element); }

  private:
    AccessorType accessor;
  };
  /** \endcond */












  /** @brief Accessor class implementing the field concept for dense containers (most importantly std::vector<> and std::deque<>).
    *
    * @tparam ContainerType   Type of the dense container, e.g. std::vector<double>
    * @tparam AccessType      The element type from which data is queried, e.g. a vertex
    */
  template<typename ContainerType, typename AccessType, typename UnpackT = base_id_unpack>
  class dense_container_field
  {
  public:

    typedef ContainerType                                           container_type;
    typedef typename ContainerType::value_type                      value_type;
    typedef AccessType                                              access_type;

    typedef typename ContainerType::reference       reference;
    typedef typename ContainerType::const_reference const_reference;

    typedef typename ContainerType::pointer         pointer;
    typedef typename ContainerType::const_pointer   const_pointer;

    typedef typename access_type::id_type::base_id_type offset_type;

    dense_container_field() : default_value() {}
    dense_container_field( ContainerType & container_ ) : container(&container_), default_value() {}
    dense_container_field( ContainerType & container_, value_type const & value_type_ ) : container(&container_), default_value(value_type_) {}

    bool is_valid() const { return container != NULL; }

    pointer find(AccessType const & element)
    {
      offset_type offset = unpack(element);
      return (static_cast<offset_type>((*container).size()) > offset) ? (&(*container)[static_cast<std::size_t>(offset)]) : NULL;
    }

    const_pointer find(AccessType const & element) const
    {
      offset_type offset = unpack(element);
      return (static_cast<offset_type>((*container).size()) > offset) ? (&(*container)[static_cast<std::size_t>(offset)]) : NULL;
    }

    reference operator()(AccessType const & element)
    {
      offset_type offset = unpack(element);
      if ( static_cast<offset_type>((*container).size()) <= offset) (*container).resize(static_cast<std::size_t>(offset+1));
      return (*container)[static_cast<std::size_t>(offset)];
    }

    const_reference operator()(AccessType const & element) const
    {
      offset_type offset = unpack(element);

      if ( static_cast<offset_type>((*(this->container)).size()) <= offset)
        return default_value;

      return (*(this->container))[static_cast<std::size_t>(offset)];
    }

    reference at(AccessType const & element)
    {
      offset_type offset = unpack(element);
      if ( static_cast<offset_type>((*container).size()) <= offset) throw std::out_of_range("dense_container_field::at() failed");
      return (*container)[static_cast<std::size_t>(offset)];
    }

    const_reference at(AccessType const & element) const
    {
      offset_type offset = unpack(element);
      if ( static_cast<offset_type>((*container).size()) <= offset) throw std::out_of_range("dense_container_field::at() failed");
      return (*container)[static_cast<std::size_t>(offset)];
    }



  protected:
    UnpackT unpack;
    ContainerType * container;
    value_type default_value;
  };

  /** \cond */
  template<typename ContainerType, typename AccessType, typename UnpackT>
  class dense_container_field<const ContainerType, AccessType, UnpackT>
  {
  public:

    typedef const ContainerType                                     container_type;
    typedef typename ContainerType::value_type                      value_type;
    typedef AccessType                                              access_type;

    typedef typename ContainerType::const_reference       reference;
    typedef typename ContainerType::const_reference const_reference;

    typedef typename ContainerType::const_pointer         pointer;
    typedef typename ContainerType::const_pointer   const_pointer;

    typedef typename access_type::id_type::base_id_type offset_type;

    dense_container_field() : default_value() {}
    dense_container_field( ContainerType const & container_ ) : container(&container_), default_value() {}
    dense_container_field( ContainerType const & container_, value_type const & value_type_ ) : container(&container_), default_value(value_type_) {}

    bool is_valid() const { return container != NULL; }

    const_pointer find(AccessType const & element) const
    {
      offset_type offset = unpack(element);
      return (static_cast<offset_type>((*container).size()) > offset) ? (&(*container)[static_cast<std::size_t>(offset)]) : NULL;
    }

    const_reference operator()(AccessType const & element) const
    {
      offset_type offset = unpack(element);

      if ( static_cast<offset_type>((*(this->container)).size()) <= offset)
        return default_value;

      return (*(this->container))[static_cast<std::size_t>(offset)];
    }

    const_reference at(AccessType const & element) const
    {
      offset_type offset = unpack(element);
      if ( static_cast<offset_type>((*container).size()) <= offset) throw std::out_of_range("dense_container_field::at() failed");
      return (*container)[static_cast<std::size_t>(offset)];
    }

    void erase(AccessType const & element);
    void clear();
    void resize( std::size_t size );


  protected:
    UnpackT unpack;
    container_type * container;
    value_type default_value;
  };
  /** \endcond */



  /** @brief  An accessor (fulfilling the field concept) for a container of interface similar to std::map<> */
  template<typename ContainerType, typename AccessType, typename UnpackT = id_unpack>
  class std_map_field
  {
  public:

    typedef ContainerType                                           container_type;
    typedef typename ContainerType::value_type::second_type         value_type;
    typedef typename ContainerType::value_type::first_type          key_type;
    typedef AccessType                                              access_type;

    typedef value_type &       reference;
    typedef value_type const & const_reference;

    typedef value_type *         pointer;
    typedef value_type const *   const_pointer;

    std_map_field() : default_value() {}
    std_map_field( ContainerType & container_ ) : container(&container_), default_value() {}
    std_map_field( ContainerType & container_, value_type const & value_type_ ) : container(&container_), default_value(value_type_) {}

    bool is_valid() const { return container != NULL; }

    pointer find(AccessType const & element)
    {
      typename container_type::iterator it = (*container).find( unpack(element) );
      return (it != (*container).end()) ? &it->second : NULL; // return NULL if not found
    }

    const_pointer find(AccessType const & element) const
    {
      typename container_type::const_iterator it = (*container).find( unpack(element) );
      return (it != (*container).end()) ? &it->second : NULL; // return NULL if not found
    }

    reference operator()(AccessType const & element)
    {
      return (*container)[ unpack(element) ];
    }

    const_reference operator()(AccessType const & element) const
    {
      typename container_type::const_iterator it = (*(this->container)).find( unpack(element) );

      if (it == (*(this->container)).end())
        return default_value;

      return it->second;
    }

    reference at(AccessType const & element)
    {
      return (*this)(element);
    }

    const_reference at(AccessType const & element) const
    {
      typename container_type::const_iterator it = (*container).find( unpack(element) );
      if (it == (*container).end()) throw std::out_of_range("std_map_field::at() const failed");
      return it->second;
    }

  protected:
    UnpackT unpack;
    ContainerType * container;
    value_type default_value;
  };


  /** \cond */
  template<typename ContainerType, typename AccessType, typename UnpackT>
  class std_map_field<const ContainerType, AccessType, UnpackT>
  {
  public:

    typedef const ContainerType                                     container_type;
    typedef typename ContainerType::value_type::second_type         value_type;
    typedef typename ContainerType::value_type::first_type          key_type;
    typedef AccessType                                              access_type;

    typedef value_type const &       reference;
    typedef value_type const & const_reference;

    typedef value_type const *         pointer;
    typedef value_type const *   const_pointer;

    std_map_field() : default_value() {}
    std_map_field( ContainerType const & container_ ) : container(&container_), default_value() {}
    std_map_field( ContainerType const & container_, value_type const & value_type_ ) : container(&container_), default_value(value_type_) {}

    bool is_valid() const { return container != NULL; }

    const_pointer find(AccessType const & element) const
    {
      typename container_type::const_iterator it = (*container).find( unpack(element) );
      return (it != (*container).end()) ? &it->second : NULL; // return NULL if not found
    }

    const_reference operator()(AccessType const & element) const
    {
      typename container_type::const_iterator it = (*(this->container)).find( unpack(element) );

      if (it == (*(this->container)).end())
        return default_value;

      return it->second;
    }

    const_reference at(AccessType const & element) const
    {
      typename container_type::const_iterator it = (*container).find( unpack(element) );
      if (it == (*container).end()) throw std::out_of_range("std_map_field::at() const failed");
      return it->second;
    }

  protected:
    UnpackT unpack;
    container_type * container;
    value_type default_value;
  };
  /** \endcond */





  namespace result_of
  {
    /** @brief Metafunction for retrieving the field accessor type for a certain container and a certain object type from which to access data
      *
      * @tparam ContainerType   The container type for which the accessor should be obtained
      * @tparam AccessType      Type of the element which should be accessed, e.g. a vertex
      */
    template<typename ContainerType, typename AccessType, typename UnpackT = typename viennagrid::result_of::unpack<ContainerType>::type >
    struct field;

    /** \cond */
    template<typename T, typename Alloc, typename AccessType, typename UnpackT>
    struct field< std::vector<T, Alloc>, AccessType, UnpackT >
    {
      typedef viennagrid::dense_container_field<std::vector<T, Alloc>, AccessType, UnpackT> type;
    };

    template<typename T, typename Alloc, typename AccessType, typename UnpackT>
    struct field< const std::vector<T, Alloc>, AccessType, UnpackT >
    {
      typedef viennagrid::dense_container_field<const std::vector<T, Alloc>, AccessType, UnpackT> type;
    };

    template<typename T, typename Alloc, typename AccessType, typename UnpackT>
    struct field< std::deque<T, Alloc>, AccessType, UnpackT >
    {
      typedef viennagrid::dense_container_field<std::deque<T, Alloc>, AccessType, UnpackT> type;
    };

    template<typename T, typename Alloc, typename AccessType, typename UnpackT>
    struct field< const std::deque<T, Alloc>, AccessType, UnpackT >
    {
      typedef viennagrid::dense_container_field<const std::deque<T, Alloc>, AccessType, UnpackT> type;
    };

    template<typename Key, typename T, typename Compare, typename Alloc, typename AccessType, typename UnpackT>
    struct field< std::map<Key, T, Compare, Alloc>, AccessType, UnpackT >
    {
      typedef viennagrid::std_map_field<std::map<Key, T, Compare, Alloc>, AccessType, UnpackT> type;
    };

    template<typename Key, typename T, typename Compare, typename Alloc, typename AccessType, typename UnpackT>
    struct field< const std::map<Key, T, Compare, Alloc>, AccessType, UnpackT >
    {
      typedef viennagrid::std_map_field<const std::map<Key, T, Compare, Alloc>, AccessType, UnpackT> type;
    };
    /** \endcond */
  }


  /** \brief Convenience function for creating a suitable field out of a container. Non-const version.
    *
    * @tparam AccessType      The element for which the container is accessed
    * @tparam ContainerType   Type of the container. Possible types: std::vector, std::deque, std::map
    */
  template<typename AccessType, typename ContainerType>
  typename result_of::field<ContainerType, AccessType>::type make_field( ContainerType & container )
  {
    return typename result_of::field<ContainerType, AccessType>::type(container);
  }

  /** \brief Convenience function for creating a suitable field out of a container. Const-version.
    *
    * @tparam AccessType      The element for which the container is accessed
    * @tparam ContainerType   Type of the container. Possible types: std::vector, std::deque, std::map
    */
  template<typename AccessType, typename ContainerType>
  typename result_of::field<const ContainerType, AccessType>::type make_field( ContainerType const & container )
  {
    return typename result_of::field<const ContainerType, AccessType>::type(container);
  }



  /** \brief Convenience function for creating a suitable field out of a collection of containers. Non-const-version.
    *
    * @tparam AccessType      The element for which the container is accessed
    * @tparam ContainerType   Type of the container. Possible types: std::vector, std::deque, std::map
    */
  template<typename AccessType, typename ContainerCollectionTypemapT>
  typename result_of::field<
      typename result_of::container_of<
          ContainerCollectionTypemapT,
          AccessType
      >::type,
      AccessType>::type make_field( collection<ContainerCollectionTypemapT> & collection_obj )
  {
    return make_field<AccessType>( get<AccessType>(collection_obj) );
  }

  /** \brief Convenience function for creating a suitable field out of a collection of containers. Const-version.
    *
    * @tparam AccessType      The element for which the container is accessed
    * @tparam ContainerType   Type of the container. Possible types: std::vector, std::deque, std::map
    */
  template<typename AccessType, typename ContainerCollectionTypemapT>
  typename result_of::field<
      const typename result_of::container_of<
          ContainerCollectionTypemapT,
          AccessType
      >::type,
      AccessType>::type make_field( collection<ContainerCollectionTypemapT> const & collection_obj )
  {
    return make_field<AccessType>( get<AccessType>(collection_obj) );
  }






  /** @brief Common base class for dynamic data accessors fulfilling the field concept */
  template<typename ValueType, typename AccessType>
  class base_dynamic_field
  {
  public:
    typedef ValueType value_type;
    typedef AccessType access_type;

    typedef value_type & reference;
    typedef value_type const & const_reference;

    typedef value_type * pointer;
    typedef value_type const * const_pointer;

    virtual ~base_dynamic_field() {}

    virtual pointer find( access_type const & ) { return 0; }
    virtual const_pointer find( access_type const & ) const { return 0; }

    virtual reference operator()( access_type const & element ) = 0;
    virtual const_reference operator()( access_type const & element ) const = 0;

    virtual reference at( access_type const & element ) = 0;
    virtual const_reference at( access_type const & element ) const = 0;
  };

  /** \cond */
  template<typename ValueType, typename AccessType>
  class base_dynamic_field<const ValueType, AccessType>
  {
  public:
    typedef ValueType value_type;
    typedef AccessType access_type;

    typedef value_type const & reference;
    typedef value_type const & const_reference;

    typedef value_type const * pointer;
    typedef value_type const * const_pointer;

    virtual ~base_dynamic_field() {}

    virtual const_pointer find( access_type const & ) const { return 0; }
    virtual const_reference operator()( access_type const & element ) const = 0;
    virtual const_reference at( access_type const & element ) const = 0;
  };
  /** \endcond */




  /** @brief A dynamic accessor class which wraps any user accessor type fulfilling the field concept.
    *
    * Used within IO reader/writers to store different accessors for data on vertices and cells inside a single container.
    */
  template<typename FieldType, typename AccessType = typename FieldType::access_type>
  class dynamic_field_wrapper : public base_dynamic_field< typename FieldType::value_type, AccessType >
  {
  public:
    typedef base_dynamic_field< typename FieldType::value_type, AccessType > BaseFieldType;

    typedef typename BaseFieldType::value_type value_type;
    typedef typename BaseFieldType::access_type access_type;

    typedef typename BaseFieldType::reference reference;
    typedef typename BaseFieldType::const_reference const_reference;

    typedef typename BaseFieldType::pointer pointer;
    typedef typename BaseFieldType::const_pointer const_pointer;


    dynamic_field_wrapper(FieldType field_) : field(field_) {}

    virtual pointer find( access_type const & element ) { return field.find(element); }
    virtual const_pointer find( access_type const & element ) const { return field.find(element); }

    virtual reference  operator()( access_type const & element )       { return field(element); }
    virtual const_reference operator()( access_type const & element ) const { return field(element); }

    virtual reference  at( access_type const & element )       { return field.at(element); }
    virtual const_reference at( access_type const & element ) const { return field.at(element); }

  private:
    FieldType field;
  };


  /** \cond */
  template<typename FieldType, typename AccessType>
  class dynamic_field_wrapper<const FieldType, AccessType> : public base_dynamic_field< const typename FieldType::value_type, AccessType >
  {
  public:
    typedef base_dynamic_field< const typename FieldType::value_type, AccessType > BaseFieldType;

    typedef typename BaseFieldType::value_type value_type;
    typedef typename BaseFieldType::access_type access_type;

    typedef typename BaseFieldType::const_reference reference;
    typedef typename BaseFieldType::const_reference const_reference;

    typedef typename BaseFieldType::const_pointer pointer;
    typedef typename BaseFieldType::const_pointer const_pointer;


    dynamic_field_wrapper(FieldType field_) : field(field_) {}

    virtual const_pointer find( access_type const & element ) const       { return field.find(element); }
    virtual const_reference    operator()( access_type const & element ) const { return field(element); }
    virtual const_reference    at( access_type const & element ) const         { return field.at(element); }

  private:
    FieldType field;
  };
  /** \endcond */



#ifdef VIENNAGRID_WITH_VIENNADATA
  namespace result_of
  {
    template<typename ContainerType, typename AccessType, typename AccessTag>
    struct point< viennadata::container_accessor<ContainerType, AccessType, AccessTag> >
    {
      typedef typename viennadata::container_accessor<ContainerType, AccessType, AccessTag>::value_type type;
    };

    template<typename ContainerType, typename AccessType, typename AccessTag>
    struct point< const viennadata::container_accessor<ContainerType, AccessType, AccessTag> >
    {
      typedef typename viennadata::container_accessor<ContainerType, AccessType, AccessTag>::value_type type;
    };
  }
#endif


}


#endif
