#ifndef VIENNAGRID_STORAGE_CONTAINER_COLLECTION_ELEMENT_HPP
#define VIENNAGRID_STORAGE_CONTAINER_COLLECTION_ELEMENT_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

/** @file viennagrid/storage/container_collection_element.hpp
    @brief Defines inserter callbacks
*/

namespace viennagrid
{
  namespace detail
  {
    template<typename container_collection_element_type, typename inserter_type>
    void insert_callback( container_collection_element_type & element, bool insert_result, inserter_type & inserter)
    {
      element.insert_callback( inserter, insert_result );
    }

    template<typename container_collection_element_type, typename inserter_type>
    void insert_callback( container_collection_element_type const & element, bool insert_result, inserter_type & inserter)
    {
      element.insert_callback( inserter, insert_result );
    }

    template<typename inserter_type>
    void insert_callback( bool & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( char & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( unsigned char & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( short & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( unsigned short & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( int & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( unsigned int & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( long & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( unsigned long & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( float & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( double & , bool , inserter_type & ) {}


    template<typename inserter_type>
    void insert_callback( const bool & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( const char & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( const unsigned char & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( const short & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( const unsigned short & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( const int & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( const unsigned int & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( const long & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( const unsigned long & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( const float & , bool , inserter_type & ) {}

    template<typename inserter_type>
    void insert_callback( const double & , bool , inserter_type & ) {}


  }
}


#endif
