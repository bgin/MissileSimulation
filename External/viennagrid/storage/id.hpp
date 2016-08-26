#ifndef VIENNAGRID_STORAGE_ID_HPP
#define VIENNAGRID_STORAGE_ID_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include <iostream>

/** @file   viennagrid/storage/id.hpp
    @brief  Defines the smart_id type which unifies different ways of identifying objects (numeric ID, pointer, etc.)
*/

namespace viennagrid
{
  template<typename id_type>
  struct id_tag;

  template<typename base_id_type>
  struct smart_id_tag;

  namespace detail
  {
    template<typename value_type_, typename base_id_type_>
    class smart_id
    {
    public:
      typedef smart_id self_type;
      typedef value_type_ value_type;
      typedef base_id_type_ base_id_type;

      typedef smart_id<const value_type, base_id_type> self_const_type;

      smart_id() : internal_id(-1) {}
      explicit smart_id( base_id_type internal_id_ ) : internal_id(internal_id_) {}

      base_id_type get() const { return internal_id; }
      void set( base_id_type internal_id_ ) { internal_id =internal_id_; }

      bool operator== ( self_type rhs ) const { return internal_id == rhs.get(); }
      bool operator!= ( self_type rhs ) const { return !(*this == rhs); }
      bool operator< ( self_type rhs ) const { return internal_id < rhs.get(); }
      bool operator<= ( self_type rhs ) const { return internal_id <= rhs.get(); }
      bool operator> ( self_type rhs ) const { return internal_id > rhs.get(); }
      bool operator>= (self_type rhs ) const { return internal_id >= rhs.get(); }

      bool operator== ( self_const_type rhs ) const { return internal_id == rhs.get(); }
      bool operator!= ( self_const_type rhs ) const { return !(*this == rhs); }
      bool operator< ( self_const_type rhs ) const { return internal_id < rhs.get(); }
      bool operator<= ( self_const_type rhs ) const { return internal_id <= rhs.get(); }
      bool operator> ( self_const_type rhs ) const { return internal_id > rhs.get(); }
      bool operator>= (self_const_type rhs ) const { return internal_id >= rhs.get(); }

      self_type & operator++() { ++internal_id; return *this; }
      self_type operator++(int) { self_type tmp(*this); ++*this; return tmp; }

    private:
      base_id_type internal_id;
    };



    template<typename value_type_, typename base_id_type_>
    class smart_id<const value_type_, base_id_type_>
    {
    public:
      typedef smart_id self_type;
      typedef value_type_ value_type;
      typedef base_id_type_ base_id_type;

      typedef smart_id<value_type, base_id_type> self_non_const_type;

      smart_id() : internal_id(-1) {}
      smart_id( smart_id<value_type_, base_id_type> const & id_ ) : internal_id(id_.get()) {}
      explicit smart_id( base_id_type internal_id_ ) : internal_id(internal_id_) {}

      base_id_type get() const { return internal_id; }
      void set( base_id_type internal_id_ ) { internal_id =internal_id_; }

      bool operator== ( self_type rhs ) const { return internal_id == rhs.get(); }
      bool operator!= ( self_type rhs ) const { return !(*this == rhs); }
      bool operator< ( self_type rhs ) const { return internal_id < rhs.get(); }
      bool operator<= ( self_type rhs ) const { return internal_id <= rhs.get(); }
      bool operator> ( self_type rhs ) const { return internal_id > rhs.get(); }
      bool operator>= (self_type rhs ) const { return internal_id >= rhs.get(); }

      bool operator== ( self_non_const_type rhs ) const { return internal_id == rhs.get(); }
      bool operator!= ( self_non_const_type rhs ) const { return !(*this == rhs); }
      bool operator< ( self_non_const_type rhs ) const { return internal_id < rhs.get(); }
      bool operator<= ( self_non_const_type rhs ) const { return internal_id <= rhs.get(); }
      bool operator> ( self_non_const_type rhs ) const { return internal_id > rhs.get(); }
      bool operator>= (self_non_const_type rhs ) const { return internal_id >= rhs.get(); }

      self_type & operator++() { ++internal_id; return *this; }
      self_type operator++(int) { self_type tmp(*this); ++*this; return tmp; }

    private:
      base_id_type internal_id;
    };


    template<typename value_type, typename base_id_type>
    bool operator<( smart_id<value_type, base_id_type> const & lhs, smart_id<value_type, base_id_type> const & rhs )
    { return lhs.get() < rhs.get(); }

    template<typename value_type, typename base_id_type>
    bool operator<( smart_id<const value_type, base_id_type> const & lhs, smart_id<value_type, base_id_type> const & rhs )
    { return lhs.get() < rhs.get(); }

    template<typename value_type, typename base_id_type>
    bool operator<( smart_id<value_type, base_id_type> const & lhs, smart_id<const value_type, base_id_type> const & rhs )
    { return lhs.get() < rhs.get(); }

    template<typename value_type, typename base_id_type>
    bool operator<( smart_id<const value_type, base_id_type> const & lhs, smart_id<const value_type, base_id_type> const & rhs )
    { return lhs.get() < rhs.get(); }



    template<typename value_type_, typename base_id_type>
    std::ostream & operator<< (std::ostream & os, smart_id<value_type_, base_id_type> id)
    {
      os << id.get();
      return os;
    }

    namespace result_of
    {
      template<typename value_type, typename id_tag>
      struct make_id;

      template<typename value_type, typename id_type>
      struct make_id<value_type, id_tag<id_type> >
      {
        typedef id_type type;
      };

      template<typename value_type, typename base_id_type>
      struct make_id<value_type, smart_id_tag<base_id_type> >
      {
        typedef smart_id<value_type, base_id_type> type;
      };


      template<typename id_type>
      struct const_id
      {
        typedef const id_type type;
      };

      template<typename value_type, typename id_type>
      struct const_id< smart_id<value_type, id_type> >
      {
        typedef smart_id<const value_type, id_type> type;
      };
    }



    template<typename id_type_>
    class id_handler
    {
    public:
      typedef id_type_ id_type;
      typedef typename result_of::const_id<id_type>::type const_id_type;

      id_handler() {}
      id_handler(const id_handler & rhs) : id_(rhs.id_) {}

      void id(id_type id) { id_ = id; }
      id_type id() const { return id_; }

    private:
      id_type id_;
    };


    namespace result_of
    {
      template<typename some_type>
      struct id
      {
        typedef typename some_type::id_type type;
      };
    }



    template<typename id_type_>
    class id_compare
    {
    public:
      typedef id_type_ id_type;
      typedef typename result_of::const_id<id_type>::type const_id_type;

      id_compare(const_id_type id_) : id(id_) {}

      template<typename type>
      bool operator() ( const type & to_compare )
      {
        return to_compare.id() == id;
      }

    private:
      const_id_type id;
    };


    template<typename element_type, typename id_type>
    void set_id( element_type & element, id_type id )
    {
      element.id(id);
    }

    template<typename id_type> void set_id( bool &, id_type ) {}
    template<typename id_type> void set_id( char &, id_type ) {}
    template<typename id_type> void set_id( unsigned char &, id_type ) {}
    template<typename id_type> void set_id( short &, id_type ) {}
    template<typename id_type> void set_id( unsigned short &, id_type ) {}
    template<typename id_type> void set_id( int &, id_type ) {}
    template<typename id_type> void set_id( unsigned int &, id_type ) {}
    template<typename id_type> void set_id( long &, id_type ) {}
    template<typename id_type> void set_id( unsigned long &, id_type ) {}
    template<typename id_type> void set_id( float &, id_type ) {}
    template<typename id_type> void set_id( double &, id_type ) {}


  }

}

#endif
