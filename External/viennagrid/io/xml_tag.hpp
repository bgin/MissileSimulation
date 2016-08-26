#ifndef VIENNAGRID_IO_XML_TAG_HPP
#define VIENNAGRID_IO_XML_TAG_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */


/** @file xml_tag.hpp
 *  @brief    A very simple parser for individual XML tags. Eases vtk_reader a bit.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include <algorithm>


#include "viennagrid/io/helper.hpp"

/** @file viennagrid/io/xml_tag.hpp
    @brief Helper routines for dealing with XML, used for the VTK reader
*/

namespace viennagrid
{
  namespace io
  {

    /** @brief Functor for conversion to lowercase (avoids the tolower() function as this can be a bit messy due to locales)
     *
     * @tparam dummy    A dummy template argument to disable external linkage of the function (for 'header-only' reasons)
     */
    template <int dummy = 0>
    struct char_to_lower
    {
      char operator()(char c) const
      {
        if(c <= 'Z' && c >= 'A')
          return c - static_cast<char>('Z'-'z');
        return c;
      }
    };

    /** @brief Helper function for converting a string to lowercase.
     *
     * @tparam String    More a dummy template argument to disable external linkage of the function (for 'header-only' reasons)
     */
    template <typename StringType>                    //Note: Using artifically a template argument t
    StringType string_to_lower(StringType const & s)
    {
      std::string ret = s;
      std::transform(ret.begin(), ret.end(), ret.begin(), char_to_lower<0>());

      return ret;
    }

    /** @brief Helper class that parses a XML tag
     *
     * @tparam dummy   A dummy parameter to control the linkage of the class
     */
    template <typename dummy = bool>
    class xml_tag
    {
      typedef std::pair<std::string, std::string>  AttributeType;
      typedef std::list<AttributeType>             AttributeContainer;

    public:

      /** @brief Triggers the parsing of a XML tag */
      template <typename InputStream>
      void parse(InputStream & reader)
      {
        reader.unsetf(std::ios_base::skipws);
        clear();

        char c = ' ';

        //go to start of tag:
        while (c != '<' && reader.good())
          reader >> c;

        //read tag name:
        while ( (c != ' ' && c != '>') && reader.good() )
        {
          reader >> c;
          name_.append(1,  make_lower(c));
        }

        //strip whitespace or closing tag at the end
        name_.resize(name_.size()-1);

        #ifdef VIENNAGRID_DEBUG_IO
        std::cout << name_ << std::endl;
        #endif

        if (c == '>') //we are all done
          return;

        //get attributes:
        bool end_of_attribute = false;
        bool inside_string = false;
        std::string token;
        while (c != '>' && reader.good())
        {
          reader >> c;

          if (inside_string && c == '"') //terminate string
          {
            end_of_attribute = true;
          }
          else if (!inside_string && c == '"') //start of string
          {
            inside_string = true;
          }

          if (inside_string)
            token.append(1, c); //do not transform values to lower-case (e.g. filenames may get invalid)
          else if (c != ' ')
            token.append(1, make_lower(c));


          if (end_of_attribute)
          {
            std::size_t pos = token.find_first_of('=');
            if (pos == std::string::npos)
            {
              throw bad_file_format_exception("* ViennaGrid: xml_tag::parse(): Parse error: XML attribute does not have '=' sign.");
            }
            else if (pos == 0)
            {
              throw bad_file_format_exception("* ViennaGrid: xml_tag::parse(): Parse error: XML attribute name missing.");
            }


            std::string name = token.substr(0, pos);
            std::string value = token.substr(pos+2, token.size());

            pos = value.rfind('"');
            if (pos == std::string::npos || pos == 0)
              throw bad_file_format_exception("* ViennaGrid: xml_tag::parse(): Internal XML parse error: XML attribute string not terminated.");

            #ifdef VIENNAGRID_DEBUG_IO
            std::cout << name << ":" << value.substr(0, pos) << std::endl;
            #endif
            attributes_.push_back(std::make_pair(name, value.substr(0, pos)));

            token.clear();

            end_of_attribute = false;
            inside_string = false;
          }
        }

        reader.setf(std::ios_base::skipws);
      }

      /** @brief Makes sure that the parsed XML tag has a certain name. Throws an bad_file_format_exception if not the case */
      void check_name(std::string const & expected_name,
                      std::string const & filename = std::string())
      {
        if (name_ != string_to_lower(expected_name))
        {
          std::stringstream ss;
          ss << "* ViennaGrid: xml_tag::check_name(): XML Parse error in file " << filename << ": " << expected_name << " expected, but got " << name_ << std::endl;
          throw bad_file_format_exception(ss.str());
        }
      }

      /** @brief Convenience overload for parsing a XML tag and checking the tag name */
      template <typename InputStream>
      void parse_and_check_name(InputStream & reader,
                                std::string const & expected_name,
                                std::string const & filename = std::string())
      {
        parse(reader);
        check_name(expected_name, filename);
      }

      /** @brief Returns the XML tag name */
      std::string name() const { return name_; }

      /** @brief Returns true if the XML tag has a certain attribute */
      bool has_attribute(std::string const & attrib_name) const
      {
        for (typename AttributeContainer::const_iterator it  = attributes_.begin();
                                                         it != attributes_.end();
                                                       ++it)
        {
          if (it->first == attrib_name)
            return true;
        }
        return false;
      }

      /** @brief Makes sure that the XML tag has a certain attribute. If not, a bad_file_format_exception is thrown */
      void check_attribute(std::string const & attrib_name,
                           std::string const & filename) const
      {
        if (!has_attribute(attrib_name))
        {
          std::stringstream ss;
          ss << "* ViennaGrid: xml_tag::check_attribute(): XML Parse error in file " << filename << ": Attribute " << attrib_name << " missing!" << std::endl;
          throw bad_file_format_exception(ss.str());
        }
      }

      /** @brief Returns the value of a certain attribute */
      std::string get_value(std::string const & attrib_name) const
      {
        for (typename AttributeContainer::const_iterator it  = attributes_.begin();
                                                         it != attributes_.end();
                                                       ++it)
        {
          if (it->first == attrib_name)
            return it->second;
        }
        return "";
      }

      /** @brief Clears all internal data */
      void clear()
      {
        name_ = std::string();
        attributes_.clear();
      }
    private:

      /** @brief transforms a character to lower-case */
      char make_lower(char c) const
      {
        if(c <= 'Z' && c >= 'A')
          return c - ('Z'-'z');
        return c;
      }

      std::string name_;
      AttributeContainer attributes_;
    };


  } //namespace io
} //namespace viennagrid

#endif
