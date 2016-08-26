#ifndef VIENNAGRID_IO_HELPER_HPP
#define VIENNAGRID_IO_HELPER_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */


#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <string>
#include <limits>
#include <stdexcept>

#include "viennagrid/forwards.hpp"

/** @file viennagrid/io/helper.hpp
    @brief Various helpers for I/O operations
*/


namespace viennagrid
{
  namespace io
  {
    /** @brief Helper class for writing points to file. Aids as a generic layer for point types that don't have operator<< overloaded in a suitable way */
    template <int dim>
    struct PointWriter
    {};

    template <>
    struct PointWriter<1>
    {
      template <typename PointType>
      static void write(std::ofstream & writer, PointType const& point)
      {
        writer.precision( std::numeric_limits<typename PointType::value_type>::digits10 );
        writer << point[0];
      }

      template <typename PointType>
      static void write(std::ofstream & writer, PointType & point)
      {
        writer.precision( std::numeric_limits<typename PointType::value_type>::digits10 );
        writer << point[0];
      }
    };

    template <>
    struct PointWriter<2>
    {
      template <typename PointType>
      static void write(std::ofstream & writer, PointType const& point)
      {
        writer.precision( std::numeric_limits<typename PointType::value_type>::digits10 );
        writer << point[0] << " " << point[1];
      }

      template <typename PointType>
      static void write(std::ofstream & writer, PointType & point)
      {
        writer.precision( std::numeric_limits<typename PointType::value_type>::digits10 );
        writer << point[0] << " " << point[1];
      }
    };

    template <>
    struct PointWriter<3>
    {
      template <typename PointType>
      static void write(std::ofstream & writer, PointType const& point)
      {
        writer.precision( std::numeric_limits<typename PointType::value_type>::digits10 );
        writer << point[0] << " " << point[1] << " " << point[2];
      }

      template <typename PointType>
      static void write(std::ofstream & writer, PointType & point)
      {
        writer.precision( std::numeric_limits<typename PointType::value_type>::digits10 );
        writer << point[0] << " " << point[1] << " " << point[2];
      }
    };

    /** @brief Checks for a string being a number */
    struct strChecker
    {
      //******************************************
      // Checks, if a string is a number or not
      //******************************************
      static bool myIsNumber(std::string& str) {
        bool numberFlag = true;
        std::size_t strLen = str.size();
        std::size_t idx = 0;

        while(numberFlag == true && idx < strLen)
        {
          if(!isdigit(str[idx]))
          {
            numberFlag = false;
          }

          idx++;
        }

        return numberFlag;
      }
    };



    /** @brief Provides an exception for the case a file cannot be opened */
    class cannot_open_file_exception : public std::runtime_error
    {
    public:
      explicit cannot_open_file_exception(std::string message) : std::runtime_error(message) {}

      virtual ~cannot_open_file_exception() throw() {}
    };

    /** @brief Provides an exception for the case a parser problem occurs */
    class bad_file_format_exception : public std::runtime_error
    {
    public:
      explicit bad_file_format_exception(std::string message) : std::runtime_error(message) {}

      virtual ~bad_file_format_exception() throw() {}
    };

  } //namespace io
} //namespace  viennagrid

#endif
