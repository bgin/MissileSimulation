#ifndef VIENNAGRID_STORAGE_IO_HPP
#define VIENNAGRID_STORAGE_IO_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include <ostream>
#include <iterator>
#include <typeinfo>
#include <iostream>

#include "viennagrid/forwards.hpp"
#include "viennagrid/storage/container_collection.hpp"
#include "viennagrid/storage/algorithm.hpp"

/** @file viennagrid/storage/io.hpp
    @brief  Defines a functor for dumping the contents of a container to an output stream
*/

namespace viennagrid
{
  namespace detail
  {

    class container_output_functor
    {
    public:
      container_output_functor(std::ostream & stream,
                               const std::string & container_delimiter = "\n",
                               const std::string & element_delimiter = " ") :
                          container_delimiter_(container_delimiter), element_delimiter_(element_delimiter), stream_(stream) {}

      template<typename container_type>
      void operator() (const container_type & container)
      {
          stream_ << typeid(container).name() << " [size=" << container.size() << "] ";
          std::copy( container.begin(), container.end(), std::ostream_iterator<typename container_type::value_type>(stream_, element_delimiter_.c_str())  );
          stream_ << container_delimiter_;
      }

    private:
      std::string    container_delimiter_;
      std::string    element_delimiter_;
      std::ostream & stream_;
    };


    template <typename container_typemap>
    std::ostream & operator<<(std::ostream & os, const viennagrid::collection<container_typemap> & container_collection)
    {
      container_output_functor f(os);

      viennagrid::detail::for_each( container_collection, f );

      return os;
    }


  }

}

#endif
