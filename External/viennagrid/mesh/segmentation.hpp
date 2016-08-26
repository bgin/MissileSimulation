#ifndef VIENNAGRID_SEGMENTATION_HPP
#define VIENNAGRID_SEGMENTATION_HPP

/* =======================================================================
   Copyright (c) 2011-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.

                            -----------------
                     ViennaGrid - The Vienna Grid Library
                            -----------------

   License:      MIT (X11), see file LICENSE in the base directory
======================================================================= */

#include <limits>
#include <string>
#include <sstream>

#include "viennagrid/forwards.hpp"
#include "viennagrid/mesh/mesh.hpp"

#include "viennagrid/accessor.hpp"


/** @file viennagrid/mesh/segmentation.hpp
    @brief Contains definition and implementation of segmentations and segments
*/


namespace viennagrid
{
  /** @brief Provides an exception for the case of a name collision of segment names */
  class segment_name_collision_exception : public std::exception
  {
    public:
      virtual const char* what() const throw()
      {
        std::stringstream ss;
        ss << "* ViennaGrid: Collision with segment names: " << collision_name_ << "!";
        return ss.str().c_str();
      }

      segment_name_collision_exception(std::string cn) : collision_name_(cn) {}

      virtual ~segment_name_collision_exception() throw() {}

    private:
      std::string collision_name_;
  };

  /** @brief A segment defines a submesh within a segmentation. The segment_handle is used to deal with segments, since segments are not represented by a dedicated class.
    *
    * @tparam SegmentationT     The segmentation type where the segment lives
    */
  template<typename WrappedConfigType>
  class segment_handle< viennagrid::segmentation<WrappedConfigType> >
  {
    friend class viennagrid::segmentation<WrappedConfigType>;

  public:

    typedef viennagrid::segmentation<WrappedConfigType> segmentation_type;
    typedef typename segmentation_type::segment_id_type segment_id_type;
    typedef typename segmentation_type::mesh_type mesh_type;
    typedef typename segmentation_type::view_type view_type;

  private:

    typedef typename segmentation_type::segment_type segment_type;

    /** @brief Constructor, used by segmentation to create a segment */
    segment_handle(segment_type & segment_x) : segment_(&segment_x) {}

  public:

    /** @brief Returns the ID of the segment
      *
      * @return   ID of the segment
      */
    segment_id_type const & id() const { return segment_->id; }

    /** @brief Returns the name of the segment
      *
      * @return   name of the segment
      */
    std::string const & name() const { return segment_->name; }

    /** @brief Set the name of this segment. Returns false if the name is already present, true on success
      *
      * @param new_name   The new name of the segment
      * @return           Returns false if the name is already present, true on success
      */
    void set_name( std::string const & new_name )
    {
      // name is already present
      if (parent().segment_name_map.find(new_name) != parent().segment_name_map.end())
        throw segment_name_collision_exception(new_name);

      parent().segment_name_map.erase( name() );
      parent().segment_name_map[new_name] = &(parent()(id()));
      segment_->name = new_name;
    }


    /** @brief Returns the segmentation in which the segment lives
      *
      * @return   A reference to the segmentation
      */
    segmentation_type & parent() { return *(segment_->segmentation_); }
    /** @brief Returns the segmentation in which the segment lives, const version
      *
      * @return   A const reference to the segmentation
      */
    segmentation_type const & parent() const { return *(segment_->segmentation_); }

    /** @brief Returns a view which represents the elements in the segment
      *
      * @return   A reference to the view
      */
    view_type & view() { return segment_->view; }
    /** @brief Returns a view which represents the elements in the segment, const version
      *
      * @return   A const reference to the view
      */
    view_type const & view() const { return segment_->view; }

    /** @brief Returns the full mesh from the parent segmentation.
      *
      * @return   A reference to the mesh
      */
    mesh_type & mesh() { return parent().mesh(); }
    /** @brief Returns the full mesh from the parent segmentation, const version.
      *
      * @return   A const reference to the mesh
      */
    mesh_type const & mesh() const { return parent().mesh(); }

    /** @brief operator< for ordering operations (e.g. used in std::map)
      *
      * @return   A const reference to the view
      */
    bool operator<( segment_handle const & rhs ) const { return id() < rhs.id(); }

  private:

    segment_type * segment_;
  };

  /** @brief Completely clears a segmentation
    *
    */
  template<typename SegmentationT>
  void clear( segment_handle<SegmentationT> & segment_ )
  {
    segment_.view().clear();
  }

  namespace result_of
  {
    /** \cond */
    template<typename SegmentationT>
    struct change_counter_type< viennagrid::segment_handle<SegmentationT> >
    {
      typedef typename change_counter_type< typename viennagrid::segment_handle<SegmentationT>::view_type >::type type;
    };

    // doxygen docu in mesh.hpp
    template<typename SegmentationType, typename element_type_or_tag>
    struct is_element_present< viennagrid::segment_handle<SegmentationType>, element_type_or_tag >
    {
      static const bool value = is_element_present< typename viennagrid::segment_handle<SegmentationType>::view_type, element_type_or_tag>::value;
    };

    template<typename SegmentationType, typename element_type_or_tag>
    struct is_element_present< const viennagrid::segment_handle<SegmentationType>, element_type_or_tag >
    {
      static const bool value = is_element_present<viennagrid::segment_handle<SegmentationType>, element_type_or_tag>::value;
    };


    // doxygen docu in forwards.hpp
    template<typename segmentation_type>
    struct element_collection< viennagrid::segment_handle<segmentation_type> >
    {
        typedef typename element_collection<typename viennagrid::segment_handle<segmentation_type>::view_type>::type type;
    };

    template<typename segmentation_type>
    struct element_collection< const viennagrid::segment_handle<segmentation_type> >
    {
        typedef typename element_collection<const typename viennagrid::segment_handle<segmentation_type>::view_type>::type type;
    };


    // doxygen docu in mesh.hpp
    template<typename segmentation_type>
    struct point< viennagrid::segment_handle<segmentation_type> >
    {
        typedef typename point<typename viennagrid::segment_handle<segmentation_type>::mesh_type>::type type;
    };


    // doxygen docu in mesh.hpp
    template<typename WrappedConfigT>
    struct segment_handle< viennagrid::segmentation<WrappedConfigT> >
    {
      typedef viennagrid::segment_handle< viennagrid::segmentation<WrappedConfigT> > type;
    };
    /** \endcond */


    /** @brief Metafunction for obtaining the segment ID type from a segment or segmentation type
     *
     * @tparam SegmentationOrSegmentHandleT      The segmentation or segment type
     */
    template<typename SegmentationOrSegmentHandleT>
    struct segment_id;

    /** \cond */
    template<typename SegmentationType>
    struct segment_id< viennagrid::segment_handle<SegmentationType> >
    {
      typedef typename viennagrid::segment_handle<SegmentationType>::segment_id_type type;
    };

    template<typename WrappedConfigType>
    struct segment_id< viennagrid::segmentation<WrappedConfigType> >
    {
      typedef typename viennagrid::segmentation<WrappedConfigType>::segment_id_type type;
    };
    /** \endcond */


    /** \cond  */
    template<typename SegmentationT,
             typename Element0TypeOrTagT, typename Element1TypeOrTagT,
             typename Element2TypeOrTagT, typename Element3TypeOrTagT,
             typename Element4TypeOrTagT, typename Element5TypeOrTagT,
             typename Element6TypeOrTagT, typename Element7TypeOrTagT,
             typename Element8TypeOrTagT, typename Element9TypeOrTagT>
    struct mesh_view< viennagrid::segment_handle<SegmentationT>,
                      Element0TypeOrTagT, Element1TypeOrTagT, Element2TypeOrTagT, Element3TypeOrTagT, Element4TypeOrTagT,
                      Element5TypeOrTagT, Element6TypeOrTagT, Element7TypeOrTagT, Element8TypeOrTagT, Element9TypeOrTagT>
    {
      typedef typename viennagrid::segment_handle<SegmentationT>::view_type ViewType;

        typedef typename mesh_view<
            ViewType,
            Element0TypeOrTagT, Element1TypeOrTagT, Element2TypeOrTagT, Element3TypeOrTagT, Element4TypeOrTagT,
            Element5TypeOrTagT, Element6TypeOrTagT, Element7TypeOrTagT, Element8TypeOrTagT, Element9TypeOrTagT
        >::type type;
    };
    /** \endcond */
  }

  namespace detail
  {

    /** @brief For internal use only */
    template<typename SegmentationType>
    bool is_obsolete( segment_handle<SegmentationType> const & segment, typename segment_handle<SegmentationType>::view_type::change_counter_type change_counter_to_check )
    { return is_obsolete(segment.view(), change_counter_to_check); }

    /** @brief For internal use only */
    template<typename SegmentationType>
    void update_change_counter( segment_handle<SegmentationType> & segment, typename segment_handle<SegmentationType>::view_type::change_counter_type & change_counter_to_update )
    { update_change_counter(segment.view(), change_counter_to_update); }

    /** @brief For internal use only */
    template<typename SegmentationType>
    void increment_change_counter( segment_handle<SegmentationType> & segment )
    { increment_change_counter(segment.view()); }



    /** @brief For internal use only */
    template<typename SegmentationType>
    typename viennagrid::segment_handle<SegmentationType>::view_type::element_collection_type & element_collection( segment_handle<SegmentationType> & segment)
    { return element_collection( segment.view() ); }

    /** @brief For internal use only */
    template<typename SegmentationType>
    typename viennagrid::segment_handle<SegmentationType>::view_type::element_collection_type const & element_collection( segment_handle<SegmentationType> const & segment)
    { return element_collection( segment.view() ); }

    /** @brief For internal use only */
    template<typename SegmentationType>
    typename viennagrid::segment_handle<SegmentationType>::view_type::inserter_type & inserter(segment_handle<SegmentationType> & segment)
    { return detail::inserter( segment.view() ); }

    /** @brief For internal use only */
    template<typename SegmentationType>
    typename viennagrid::segment_handle<SegmentationType>::view_type::inserter_type const & inserter(segment_handle<SegmentationType> const & segment)
    { return detail::inserter( segment.view() ); }


    /** @brief For internal use only */
    template<typename SegmentationType>
    typename viennagrid::segment_handle<SegmentationType>::view_type::inserter_type::id_generator_type & id_generator(segment_handle<SegmentationType> & segment)
    { return id_generator( segment.view() ); }

    /** @brief For internal use only */
    template<typename SegmentationType>
    typename viennagrid::segment_handle<SegmentationType>::view_type::inserter_type::id_generator_type const & id_generator(segment_handle<SegmentationType> const & segment)
    { return id_generator( segment.view() ); }

  }

  /** @brief Function for obtaining the heighest ID for a specific element type/tag in a segment.  */
  template<typename ElementTypeOrTag, typename SegmentationType>
  typename viennagrid::result_of::id<
    typename viennagrid::result_of::element< segment_handle<SegmentationType>, ElementTypeOrTag>::type
  >::type id_upper_bound( segment_handle<SegmentationType> const & segment )
  { return id_upper_bound<ElementTypeOrTag>( segment.view() ); }




  /** @brief Function for dereferencing a handle using a segment object
    *
    * @param  segment_handle     The host segment object
    * @param  handle             The handle to be dereferenced
    * @return                    A C++ reference to an element which is referenced by handle
    */
  template<typename SegmentationT, typename HandleT>
  typename detail::result_of::value_type<HandleT>::type &
  dereference_handle(segment_handle<SegmentationT> & segment_handle, HandleT const & handle)
  {
    return dereference_handle( segment_handle.parent().mesh(), handle );
  }

  /** @brief Function for dereferencing a handle using a segment object
    *
    * @param  segment_handle     The host segment object
    * @param  handle             The handle to be dereferenced
    * @return                    A C++ reference to an element which is referenced by handle
    */
  template<typename SegmentationT, typename HandleT>
  typename detail::result_of::value_type<HandleT>::type const &
  dereference_handle(segment_handle<SegmentationT> const & segment_handle, HandleT const & handle)
  {
    return dereference_handle( segment_handle.parent().mesh(), handle );
  }



  /** @brief Creates a view out of a mesh using the mesh_proxy object
    *
    * @tparam SegmentationT          The segmentation type from which the mesh view is created
    * @param  segment                The segment object from which the mesh view is created
    * @return                        a mesh_proxy object holding the host mesh/segment object, can be assigned to a mesh_t object
    */
  template<typename SegmentationT>
  mesh_proxy< typename SegmentationT::view_type > make_view(segment_handle<SegmentationT> & segment)
  {
      return mesh_proxy<typename SegmentationT::view_type>( segment.view() );
  }



  /** @brief Function for obtaining the point from a vertex
    *
    * @tparam SegmentationType    Segmentation type of the segment type
    * @param  segment             The host segment object
    * @param  vertex              The vertex of which the point is obtained
    * @return                     A reference to the point
    */
  template<typename SegmentationType>
  typename result_of::point< segment_handle<SegmentationType> >::type &
  point(segment_handle<SegmentationType> & segment,
        typename result_of::vertex< typename SegmentationType::mesh_type >::type & vertex)
  { return point( segment.parent().mesh(), vertex ); }

  /** @brief Function for obtaining the point from a vertex, const version
    *
    * @tparam SegmentationType    Segmentation type of the segment type
    * @param  segment             The host segment object
    * @param  vertex              The vertex of which the point is obtained
    * @return                     A const reference to the point
    */
  template<typename SegmentationType>
  typename result_of::point< segment_handle<SegmentationType> >::type const &
  point( segment_handle<SegmentationType> const & segment,
         typename result_of::vertex< typename SegmentationType::mesh_type >::type const & vertex)
  { return point( segment.parent().mesh(), vertex ); }

  /** @brief Function for obtaining the point from a vertex
    *
    * @tparam SegmentationType    Segmentation type of the segment type
    * @param  segment             The host segment object
    * @param  vertex_handle       A handle to the vertex of which the point is obtained
    * @return                     A reference to the point
    */
  template<typename SegmentationType>
  typename result_of::point< segment_handle<SegmentationType> >::type &
  point(segment_handle<SegmentationType> & segment,
        typename result_of::vertex_handle< typename SegmentationType::mesh_type >::type vertex_handle)
  { return point( segment.parent().mesh(), vertex_handle ); }

  /** @brief Function for obtaining the point from a vertex, const version
    *
    * @tparam SegmentationType    Segmentation type of the segment type
    * @param  segment             The host segment object
    * @param  vertex_handle       A handle to the vertex of which the point is obtained
    * @return                     A const reference to the point
    */
  template<typename SegmentationType>
  typename result_of::point< segment_handle<SegmentationType> >::type const &
  point( segment_handle<SegmentationType> const & segment,
         typename result_of::const_vertex_handle< typename SegmentationType::mesh_type >::type vertex_handle)
  { return point( segment.parent().mesh(), vertex_handle ); }








  namespace result_of
  {
    /** \cond */
    template<typename WrappedConfigType>
    struct segmentation_mesh_type
    {
      typedef typename WrappedConfigType::mesh_type type;
    };

    template<typename WrappedConfigType>
    struct segmentation_view_type
    {
      typedef typename WrappedConfigType::view_type type;
    };

    template<typename WrappedConfigType>
    struct segmentation_segment_id_type
    {
      typedef typename WrappedConfigType::segment_id_type type;
    };

    template<typename WrappedConfigType>
    struct segmentation_appendix_type
    {
      typedef typename WrappedConfigType::appendix_type type;
    };

    template<typename WrappedConfigType>
    struct segmentation_segment_container_tag
    {
      typedef typename WrappedConfigType::segment_container_tag type;
    };
    /** \endcond */
  }



  namespace config
  {
    /** \cond */
    template<typename mesh_type_, typename view_type_, typename segment_id_type_, typename appendix_type_, typename segment_container_tag_>
    struct segmentation_config_wrapper_t
    {
      typedef mesh_type_ mesh_type;
      typedef view_type_ view_type;
      typedef segment_id_type_ segment_id_type;
      typedef appendix_type_ appendix_type;
      typedef segment_container_tag_ segment_container_tag;
    };
    /** \endcond */
  }


  /** @brief Provides an exception for the case a segment id cannot be found */
  class segment_id_not_found_exception : public std::exception
  {
    public:
      virtual const char* what() const throw()
      {
        std::stringstream ss;
        ss << "* ViennaGrid: Cannot find segment with ID " << id_ << "!";
        return ss.str().c_str();
      }

      segment_id_not_found_exception(long id) : id_(id) {}

      virtual ~segment_id_not_found_exception() throw() {}

    private:
      long id_;
  };


  /** @brief Provides an exception for the case a segment name cannot be found */
  class segment_name_not_found_exception : public std::exception
  {
    public:
      virtual const char* what() const throw()
      {
        std::stringstream ss;
        ss << "* ViennaGrid: Cannot find segment  " << name_ << "!";
        return ss.str().c_str();
      }

      segment_name_not_found_exception(std::string const & name) : name_(name) {}

      virtual ~segment_name_not_found_exception() throw() {}

    private:
      std::string name_;
  };


  /** @brief A segmentation is a logical decomposition of the mesh (or a subset thereof) into segments. Segments may overlap. */
  template<typename WrappedConfigType>
  class segmentation
  {
    friend class segment_handle< segmentation<WrappedConfigType> >;

  public:

    /** @brief The mesh type to which the segmentation references */
    typedef typename result_of::segmentation_mesh_type<WrappedConfigType>::type mesh_type;
    /** @brief The view type in a segment */
    typedef typename result_of::segmentation_view_type<WrappedConfigType>::type view_type;
    /** @brief The segment ID type */
    typedef typename result_of::segmentation_segment_id_type<WrappedConfigType>::type segment_id_type;
    /** @brief For internal use only */
    typedef typename result_of::segmentation_appendix_type<WrappedConfigType>::type appendix_type;
    /** @brief For internal use only */
    typedef typename result_of::segmentation_segment_container_tag<WrappedConfigType>::type segment_container_tag;

    /** @brief For internal use only */
    typedef viennagrid::segmentation<WrappedConfigType> self_type;

    /** @brief The segment type of the segmentation */
    typedef segment_handle<self_type> segment_handle_type;

  private:

    /** @brief For internal use only */
    struct segment
    {
      segment(self_type * segmentation_x, mesh_type & mesh, segment_id_type id_) :
        segmentation_(segmentation_x), view( viennagrid::make_view(mesh) ), id(id_) {}

      self_type * segmentation_;

      view_type view;
      segment_id_type id;
      std::string name;
    };

    /** @brief For internal use only */
    typedef typename viennagrid::result_of::container< segment, segment_container_tag >::type segment_container_type;
    /** @brief For internal use only */
    typedef std::map<segment_id_type, segment_handle_type> segment_id_map_type;
    /** @brief For internal use only */
    typedef std::map<std::string, segment_handle_type*> segment_name_map_type;

    /** @brief For internal use only */
    typedef segment segment_type;

  public:


    /** @brief Constructor
      *
      * @param mesh_x   The mesh object to which the segmentation references
      */
    segmentation( mesh_type & mesh_x ) : highest_id(-1), mesh_(&mesh_x) { all_elements_ = viennagrid::make_view(*mesh_); }

    /** @brief (Re-)Initializes a segmentation based on a mesh.
      *
      */
    void init( mesh_type & mesh_x )
    {
      highest_id = -1;
      mesh_ = &mesh_x;
      all_elements_ = viennagrid::make_view(*mesh_);
    }


    /** @brief Returns the mesh to which the segmentation is associated
      *
      * @return   A reference to the mesh
      */
    mesh_type & mesh() { return *mesh_; }
    /** @brief Returns the mesh to which the segmentation is associated, const version
      *
      * @return   A const reference to the mesh
      */
    mesh_type const & mesh() const { return *mesh_; }

    /** @brief Returns the appenix of the segmentation, for internal use only
      *
      * @return   A reference to the appendix
      */
    appendix_type & appendix() { return appendix_; }
    /** @brief Returns the appenix of the segmentation, const version, for internal use only
      *
      * @return   A const reference to the appendix
      */
    appendix_type const & appendix() const { return appendix_; }


    /** @brief Queries if a segment with given ID is present within the segmentation
      *
      * @param segment_id   The ID of the segment to search
      * @return             True if the segment is present, false otherwise
      */
    bool segment_present( segment_id_type const & segment_id ) const { return segment_id_map.find(segment_id) != segment_id_map.end(); }


    /** @brief Returns the segment with the given ID, will fail if no segment with segment_id is present
      *
      * @param segment_id   The ID of the segment to search
      * @return             A const reference to the segment with the given ID
      */
    segment_handle_type & get_segment( segment_id_type const & segment_id )
    {
      typename segment_id_map_type::iterator it = segment_id_map.find(segment_id);
      assert( it != segment_id_map.end() );
      return it->second; // segment already is present
    }

    /** @brief Returns the segment with the given ID, will fail if no segment with segment_id is present
      *
      * @param segment_id   The ID of the segment to search
      * @return             A const reference to the segment with the given ID
      */
    segment_handle_type const & get_segment( segment_id_type const & segment_id ) const
    {
      typename segment_id_map_type::const_iterator it = segment_id_map.find(segment_id);
      assert( it != segment_id_map.end() );
      return it->second; // segment already is present
    }

    /** @brief Returns the segment with the given name, will fail if no segment with segment_id is present
      *
      * @param segment_id   The name of the segment to search
      * @return             A const reference to the segment with the given name
      */
    segment_handle_type & get_segment( std::string const & segment_name )
    {
      typename segment_name_map_type::iterator it = segment_name_map.find(segment_name);
      assert( it != segment_name_map.end() );
      return *(it->second); // segment already is present
    }

    /** @brief Returns the segment with the given name, will fail if no segment with segment_id is present
      *
      * @param segment_id   The name of the segment to search
      * @return             A const reference to the segment with the given name
      */
    segment_handle_type const & get_segment( std::string const & segment_name ) const
    {
      typename segment_name_map_type::const_iterator it = segment_name_map.find(segment_name);
      assert( it != segment_name_map.end() );
      return *(it->second); // segment already is present
    }






    /** @brief Returns the segment with the given ID, will create a new segment if no segment with the given ID is present
      *
      * @param segment_id   The ID of the segment to search
      * @return             A reference to the segment with the given ID
      */
    segment_handle_type & get_make_segment( segment_id_type const & segment_id )
    {
      typename segment_id_map_type::iterator it = segment_id_map.find(segment_id);

      if (it != segment_id_map.end())
          return it->second; // segment already is present

      segments.push_back( segment(this, mesh(), segment_id) );
      segment & new_segment = segments.back();

      if ( highest_id < segment_id )
          highest_id = segment_id;

      it = segment_id_map.insert( std::make_pair(segment_id, segment_handle_type(new_segment)) ).first;

      std::stringstream ss;
      ss << segment_id;
      segments.back().name = ss.str();

      if (!segment_name_map.insert(std::make_pair(ss.str(), &it->second)).second)
        throw segment_name_collision_exception(ss.str());

      return it->second;
    }

    /** @brief Returns the segment with the given ID, will create a new segment if no segment with the given ID is present
      *
      * @param segment_id   The ID of the segment to search
      * @return             A reference to the segment with the given ID
      */
    segment_handle_type & get_make_segment( std::string const & segment_name )
    {
      typename segment_name_map_type::iterator it = segment_name_map.find(segment_name);

      if (it != segment_name_map.end())
          return *(it->second); // segment already is present

      segment_handle_type & segment = make_segment();
      segment.set_name(segment_name);
      return segment;
    }



    /** @brief Creates a new segment with an automatic assigned ID
      *
      * @return             A reference to newly created segment
      */
    segment_handle_type & make_segment() { return get_make_segment( ++highest_id ); }



    /** @brief Calls get_make_segment with segment_id
      *
      * @param segment_id   The ID of the segment to search
      * @return             A reference to newly created segment
      */
    segment_handle_type & operator()( segment_id_type const & segment_id ) { return get_make_segment(segment_id); }
    /** @brief Calls get_make_segment with segment_id
      *
      * @param segment_id   The ID of the segment to search
      * @return             A reference to newly created segment
      */
    segment_handle_type & operator[]( segment_id_type const & segment_id ) { return get_make_segment(segment_id); }

    /** @brief Calls get_segment with segment_id
      *
      * @param segment_id   The ID of the segment to search
      * @return             A const reference to newly created segment
      */
    segment_handle_type const & operator()( segment_id_type const & segment_id ) const { return get_segment(segment_id); }
    /** @brief Calls get_segment with segment_id
      *
      * @param segment_id   The ID of the segment to search
      * @return             A const reference to newly created segment
      */
    segment_handle_type const & operator[]( segment_id_type const & segment_id ) const { return get_segment(segment_id); }
    /** @brief Returns segment with segment_id. Throws
      *
      * @param segment_id   The ID of the segment to search
      * @return             A const reference to newly created segment
      */
    segment_handle_type const & at( segment_id_type const & segment_id ) const
    {
      typename segment_id_map_type::const_iterator it = segment_id_map.find(segment_id);
      if( it == segment_id_map.end() )
        throw viennagrid::segment_id_not_found_exception(segment_id);
      return it->second;
    }




    /** @brief Calls get_make_segment with segment_name
      *
      * @param segment_name   The name of the segment to search
      * @return               A reference to newly created segment
      */
    segment_handle_type & operator()( std::string const & segment_name ) { return get_make_segment(segment_name); }
    /** @brief Calls get_make_segment with segment_name
      *
      * @param segment_name   The name of the segment to search
      * @return               A reference to newly created segment
      */
    segment_handle_type & operator[]( std::string const & segment_name ) { return get_make_segment(segment_name); }

    /** @brief Calls get_segment with segment_name
      *
      * @param segment_name   The name of the segment to search
      * @return               A const reference to newly created segment
      */
    segment_handle_type const & operator()( std::string const & segment_name ) const { return get_segment(segment_name); }
    /** @brief Calls get_segment with segment_name
      *
      * @param segment_name   The name of the segment to search
      * @return               A const reference to newly created segment
      */
    segment_handle_type const & operator[]( std::string const & segment_name ) const { return get_segment(segment_name); }
    /** @brief Returns segment with segment_name. Throws
      *
      * @param segment_name   The name of the segment to search
      * @return               A const reference to newly created segment
      */
    segment_handle_type const & at( std::string const & segment_name ) const
    {
      typename segment_name_map_type::const_iterator it = segment_name_map.find(segment_name);
      if( it == segment_name_map.end() )
        throw viennagrid::segment_name_not_found_exception(segment_name);
      return it->second;
    }






    /** @brief Returns the heighest segment ID
      *
      * @return             The highest segment ID
      */
    segment_id_type id_upper_bound() const { return highest_id; }


    /** @brief Iterator for iterating over all segments */
    class iterator : public segment_id_map_type::iterator
    {
      typedef typename segment_id_map_type::iterator base;
    public:
      iterator() {}
      iterator(base const & foo) : base(foo) {}

      typedef segment_handle_type           value_type;
      typedef segment_handle_type &         reference;
      typedef segment_handle_type const &   const_reference;
      typedef segment_handle_type *         pointer;
      typedef segment_handle_type const *   const_pointer;

      reference       operator* ()       { return base::operator*().second; }
      const_reference operator* () const { return base::operator*().second; }

      pointer       operator->()       { return &(operator* ()); }
      const_pointer operator->() const { return &(operator* ()); }
    };

    /** @brief Const iterator for iterating over all segments */
    class const_iterator : public segment_id_map_type::const_iterator
    {
      typedef typename segment_id_map_type::const_iterator base;
    public:
      const_iterator() {}
      const_iterator(base const & foo) : base(foo) {}
      const_iterator(iterator const & it) : base(it) {}

      typedef segment_handle_type value_type;
      typedef segment_handle_type const & reference;
      typedef segment_handle_type const * pointer;

      reference operator* () const { return base::operator*().second; }

      pointer operator->() const { return &(operator* ()); }
    };

    /** @brief Returns an iterator pointing to the first segment
      *
      * @return    An iterator pointing to the first segment
      */
    iterator begin() { return iterator(segment_id_map.begin()); }
    /** @brief Returns an iterator pointing to the end of the segments
      *
      * @return    An iterator pointing to the end of the segments
      */
    iterator end() { return iterator(segment_id_map.end()); }

    /** @brief Returns a const iterator pointing to the first segment
      *
      * @return    A const iterator pointing to the first segment
      */
    const_iterator cbegin() const { return const_iterator(segment_id_map.begin()); }
    /** @brief Returns a const iterator pointing to the end of the segments
      *
      * @return    A const iterator pointing to the end of the segments
      */
    const_iterator cend() const { return const_iterator(segment_id_map.end()); }

    /** @brief Returns a const iterator pointing to the first segment, const version
      *
      * @return    A const iterator pointing to the first segment
      */
    const_iterator begin() const { return cbegin(); }
    /** @brief Returns a const iterator pointing to the end of the segments, const version
      *
      * @return    A const iterator pointing to the end of the segments
      */
    const_iterator end() const { return cend(); }

    /** @brief Returns the number of segments in the segmentation
      *
      * @return    The number of segments
      */
    std::size_t size() const { return segment_id_map.size(); }
    /** @brief Queries if the segmentation is empty
      *
      * @return    True if there are no segments, false otherwise
      */
    bool empty() const { return segment_id_map.empty(); }

    /** @brief Finds a segment with a given segment ID
      *
      * @param    segment_id    The segment ID of the segment to find
      * @return                 An iterator pointing segment with the given ID, if no segment was found it points to end()
      */
    iterator find( segment_id_type const & segment_id ) { return iterator( segment_id_map.find(segment_id) ); }
    /** @brief Finds a segment with a given segment ID, const version
      *
      * @param    segment_id    The segment ID of the segment to find
      * @return                 A const iterator pointing segment with the given ID, if no segment was found it points to end()
      */
    const_iterator find( segment_id_type const & segment_id ) const { return const_iterator( segment_id_map.find(segment_id) ); }

    /** @brief Completely clears a segmentations
      *
      */
    void clear()
    {
      highest_id = -1;
      segment_id_map.clear();
      segments.clear();
      appendix_ = appendix_type();
    }


    view_type & all_elements() { return all_elements_; }
    view_type const & all_elements() const { return all_elements_; }

  private:

    view_type all_elements_;

    segment_id_type highest_id;
    segment_id_map_type segment_id_map;
    segment_name_map_type segment_name_map;

    segment_container_type segments;

    appendix_type appendix_;

    mesh_type * mesh_;
  };


  /** @brief Completely clears a segmentation
    *
    */
  template<typename WrappedConfigT>
  void clear( segmentation<WrappedConfigT> & segmentation_ )
  {
    segmentation_.clear();
  }


  namespace detail
  {
    /** @brief For internal use only */
    template<typename WrappedConfigT>
    typename viennagrid::segmentation<WrappedConfigT>::view_type::element_collection_type &
    element_collection( viennagrid::segmentation<WrappedConfigT> & segmentation)
    { return element_collection( segmentation.all_elements() ); }

    /** @brief For internal use only */
    template<typename WrappedConfigT>
    typename viennagrid::segmentation<WrappedConfigT>::view_type::element_collection_type const &
    element_collection( viennagrid::segmentation<WrappedConfigT> const & segmentation)
    { return element_collection( segmentation.all_elements() ); }
  }


  // doxygen docu in mesh.hpp
  /** @brief Function for dereferencing a handle using a segmentation
    *
    * @param  segmentation_      The segmentation object
    * @param  handle             The handle to be dereferenced
    * @return                    A C++ reference to an element which is referenced by handle
    */
  template<typename WrappedConfigT, typename HandleT>
  typename detail::result_of::value_type<HandleT>::type &
  dereference_handle(segmentation<WrappedConfigT> & segmentation_, HandleT const & handle)
  {
    return dereference_handle( segmentation_.mesh(), handle );
  }

  // doxygen docu in mesh.hpp
  /** @brief Function for dereferencing a handle using a segmentation
    *
    * @param  segmentation_      The segmentation object
    * @param  handle             The handle to be dereferenced
    * @return                    A C++ reference to an element which is referenced by handle
    */
  template<typename WrappedConfigT, typename HandleT>
  typename detail::result_of::value_type<HandleT>::type const &
  dereference_handle(segmentation<WrappedConfigT> const & segmentation_, HandleT const & handle)
  {
    return dereference_handle( segmentation_.mesh(), handle );
  }




  namespace result_of
  {
    /** @brief Meta function for querying the mesh type of a segmentation */
    template<typename WrappedConfigType>
    struct mesh<viennagrid::segmentation<WrappedConfigType> >
    {
      typedef typename viennagrid::segmentation<WrappedConfigType>::mesh_type type;
    };

    /** @brief Meta function for querying the mesh type of a segment handle */
    template<typename SegmentationT>
    struct mesh<viennagrid::segment_handle<SegmentationT> >
    {
      typedef typename viennagrid::segment_handle<SegmentationT>::mesh_type type;
    };

    /** \cond */
    // doxygen docu in mesh.hpp
    template<typename WrappedConfigType, typename element_type_or_tag>
    struct is_element_present< viennagrid::segmentation<WrappedConfigType>, element_type_or_tag >
    {
      static const bool value = is_element_present< typename viennagrid::segmentation<WrappedConfigType>::mesh_type, element_type_or_tag>::value;
    };

    template<typename WrappedConfigType, typename element_type_or_tag>
    struct is_element_present< const viennagrid::segmentation<WrappedConfigType>, element_type_or_tag >
    {
      static const bool value = is_element_present<viennagrid::segmentation<WrappedConfigType>, element_type_or_tag>::value;
    };


    // doxygen docu in forwards.hpp
    template<typename segmentation_type>
    struct element_collection< viennagrid::segmentation<segmentation_type> >
    {
      typedef typename element_collection<typename viennagrid::segmentation<segmentation_type>::view_type>::type type;
    };

    template<typename segmentation_type>
    struct element_collection< const viennagrid::segmentation<segmentation_type> >
    {
      typedef typename element_collection<const typename viennagrid::segmentation<segmentation_type>::view_type>::type type;
    };


    // doxygen docu in mesh.hpp
    template<typename segmentation_type>
    struct point< viennagrid::segmentation<segmentation_type> >
    {
      typedef typename point<typename viennagrid::segmentation<segmentation_type>::mesh_type>::type type;
    };



    // doxygen docu in forwards.hpp
    template<typename segmentation_type, typename element_type_or_tag>
    struct element< viennagrid::segmentation<segmentation_type>, element_type_or_tag >
    {
      typedef typename element<typename viennagrid::segmentation<segmentation_type>::view_type, element_type_or_tag>::type type;
    };

    // doxygen docu in forwards.hpp
    template<typename segmentation_type, typename element_type_or_tag>
    struct handle< viennagrid::segmentation<segmentation_type>, element_type_or_tag >
    {
      typedef typename handle<typename viennagrid::segmentation<segmentation_type>::view_type, element_type_or_tag>::type type;
    };

    // doxygen docu in forwards.hpp
    template<typename segmentation_type, typename element_type_or_tag>
    struct const_handle< viennagrid::segmentation<segmentation_type>, element_type_or_tag >
    {
      typedef typename const_handle<typename viennagrid::segmentation<segmentation_type>::view_type, element_type_or_tag>::type type;
    };


    // doxygen docu in forwards.hpp
    template<typename segmentation_type, typename element_type_or_tag>
    struct element_range< viennagrid::segmentation<segmentation_type>, element_type_or_tag >
    {
      typedef typename element_range<typename viennagrid::segmentation<segmentation_type>::view_type, element_type_or_tag>::type type;
    };

    // doxygen docu in forwards.hpp

    template<typename segmentation_type, typename element_type_or_tag>
    struct const_element_range< viennagrid::segmentation<segmentation_type>, element_type_or_tag >
    {
      typedef typename const_element_range<typename viennagrid::segmentation<segmentation_type>::view_type, element_type_or_tag>::type type;
    };

    // doxygen docu in forwards.hpp
    template<typename segmentation_type>
    struct cell_tag< viennagrid::segmentation<segmentation_type> >
    {
      typedef typename cell_tag< typename viennagrid::segmentation<segmentation_type>::view_type >::type type;
    };
    /** \endcond */
  }


  namespace detail
  {

    /** @brief For internal use only */
    template<typename segment_id_type_, typename segment_element_info_type_ = viennagrid::null_type>
    struct element_segment_mapping
    {
      typedef segment_id_type_ segment_id_type;
      typedef segment_element_info_type_ segment_element_info_type;

      element_segment_mapping() {}
      element_segment_mapping( segment_id_type const & segment_id_ ) : segment_id(segment_id_) {}

      segment_id_type segment_id;
      segment_element_info_type segment_element_info;
    };


    /** @brief Information container providing iteration over segments of a segmentation */
    template<typename element_segment_mapping_type, typename container_tag = viennagrid::std_vector_tag>
    struct segment_info_t
    {
      typedef typename element_segment_mapping_type::segment_id_type segment_id_type;
      typedef typename element_segment_mapping_type::segment_element_info_type segment_element_info_type;

      typedef typename viennagrid::result_of::container<element_segment_mapping_type, container_tag>::type element_segment_mapping_container_type;


      class const_iterator : public element_segment_mapping_container_type::const_iterator
      {
        typedef typename element_segment_mapping_container_type::const_iterator base;
      public:
        const_iterator() {}
        const_iterator(base const & foo) : base(foo) {}

        typedef segment_id_type           value_type;
        typedef segment_id_type &         reference;
        typedef segment_id_type const &   const_reference;
        typedef segment_id_type *         pointer;
        typedef segment_id_type const *   const_pointer;

        const_reference operator* () const { return base::operator*().segment_id; }
        const_pointer operator->() const { return &(operator* ()); }
      };

      const_iterator cbegin() const { return const_iterator(element_segment_mapping_container.begin()); }
      const_iterator cend()   const { return const_iterator(element_segment_mapping_container.end()); }

      const_iterator begin() const { return cbegin(); }
      const_iterator end()   const { return cend(); }

      std::size_t size() const { return element_segment_mapping_container.size(); }

      bool empty() const { return element_segment_mapping_container.empty(); }

      bool is_equal( segment_info_t const & other ) const
      {
        if ( size() != other.size() )
          return false;

        std::vector<segment_id_type> this_segment_ids( size() );
        std::vector<segment_id_type> other_segment_ids( other.size() );

        std::copy( begin(), end(), this_segment_ids.begin() );
        std::copy( other.begin(), other.end(), other_segment_ids.begin() );

        std::sort( this_segment_ids.begin(), this_segment_ids.end() );
        std::sort( other_segment_ids.begin(), other_segment_ids.end() );

        return this_segment_ids == other_segment_ids;
      }


      element_segment_mapping_container_type element_segment_mapping_container;
    };


    /** @brief For internal use only */
    struct element_segment_mapping_tag;

    template<typename SegmentationT>
    typename viennagrid::detail::result_of::lookup<
            typename SegmentationT::appendix_type,
            element_segment_mapping_tag
        >::type & element_segment_mapping_collection( SegmentationT & segmentation )
    {
      return viennagrid::get<element_segment_mapping_tag>( segmentation.appendix() );
    }

    template<typename SegmentationT>
    typename viennagrid::detail::result_of::lookup<
            typename SegmentationT::appendix_type,
            element_segment_mapping_tag
        >::type const & element_segment_mapping_collection( SegmentationT const & segmentation )
    {
      return viennagrid::get<element_segment_mapping_tag>( segmentation.appendix() );
    }


    template<typename segment_handle_type>
    typename viennagrid::detail::result_of::lookup<
            typename segment_handle_type::segmentation_type::appendix_type,
            element_segment_mapping_tag
        >::type & element_segment_mapping_collection( segment_handle_type & segment )
    {
      return element_segment_mapping_collection( segment.parent() );
    }

    template<typename segment_handle_type>
    typename viennagrid::detail::result_of::lookup<
            typename segment_handle_type::segmentation_type::appendix_type,
            element_segment_mapping_tag
        >::type const & element_segment_mapping_collection( segment_handle_type const & segment )
    {
      return element_segment_mapping_collection( segment.parent() );
    }




    /** @brief For internal use only */
    template<typename container_type_, typename ChangeCounterType>
    struct segment_interface_information_wrapper
    {
      typedef container_type_ container_type;
      typedef ChangeCounterType change_counter_type;

      segment_interface_information_wrapper() : seg0_change_counter(0), seg1_change_counter(0) {}

      change_counter_type seg0_change_counter;
      change_counter_type seg1_change_counter;

      container_type container;
    };


    /** @brief For internal use only */
    template<typename segment_id_type, typename container_type_, typename ChangeCounterType>
    struct interface_information_wrapper
    {
      typedef container_type_ container_type;
      typedef segment_interface_information_wrapper<container_type, ChangeCounterType> segment_interface_information_wrapper_type;
      typedef std::pair<segment_id_type, segment_id_type> key_type;
      typedef std::map< key_type, segment_interface_information_wrapper_type > map_type;

      interface_information_wrapper() {}

      template<typename segment_handle_type>
      segment_interface_information_wrapper_type & get_interface_wrapper_impl( segment_handle_type const & seg0, segment_handle_type const & seg1 ) const
      {
        assert( seg0.id() != seg1.id() );

        key_type key( std::min(seg0.id(), seg1.id()), std::max(seg0.id(), seg1.id()) );

        return interface_flags[ key ];
      }

      template<typename segment_handle_type>
      segment_interface_information_wrapper_type & get_interface_wrapper( segment_handle_type const & seg0, segment_handle_type const & seg1 )
      { return get_interface_wrapper_impl(seg0, seg1); }

      template<typename segment_handle_type>
      segment_interface_information_wrapper_type const & get_interface_wrapper( segment_handle_type const & seg0, segment_handle_type const & seg1 ) const
      { return get_interface_wrapper_impl(seg0, seg1); }

      mutable map_type interface_flags;
    };



    template<typename element_tag, typename segment_handle_type>
    typename viennagrid::detail::result_of::lookup<
        typename viennagrid::detail::result_of::lookup<
            typename segment_handle_type::segmentation_type::appendix_type,
            interface_information_collection_tag
        >::type,
        element_tag
    >::type::segment_interface_information_wrapper_type &
    interface_information_collection( segment_handle_type & seg0, segment_handle_type & seg1 )
    { return viennagrid::get<element_tag>( viennagrid::get<interface_information_collection_tag>( seg0.parent().appendix() ) ).get_interface_wrapper(seg0, seg1); }

    template<typename element_tag, typename segment_handle_type>
    typename viennagrid::detail::result_of::lookup<
        typename viennagrid::detail::result_of::lookup<
            typename segment_handle_type::segmentation_type::appendix_type,
            interface_information_collection_tag
        >::type,
        element_tag
    >::type::segment_interface_information_wrapper_type const &
    interface_information_collection( segment_handle_type const & seg0, segment_handle_type const & seg1 )
    { return viennagrid::get<element_tag>( viennagrid::get<interface_information_collection_tag>( seg0.parent().appendix() ) ).get_interface_wrapper(seg0, seg1); }




    namespace result_of
    {
      /** @brief For internal use only */
      template<typename segment_id_type, typename interface_information_container_tag, typename ChangeCounterType, typename element_taglist>
      struct interface_information_collection_typemap_impl;

      template<typename segment_id_type, typename interface_information_container_tag, typename ChangeCounterType>
      struct interface_information_collection_typemap_impl<segment_id_type, interface_information_container_tag, ChangeCounterType, viennagrid::null_type>
      {
        typedef viennagrid::null_type type;
      };

      template<typename segment_id_type, typename interface_information_container_tag, typename ChangeCounterType, typename element_tag, typename tail>
      struct interface_information_collection_typemap_impl<segment_id_type, interface_information_container_tag, ChangeCounterType, viennagrid::typelist<element_tag, tail> >
      {
        typedef typename viennagrid::result_of::container<bool, interface_information_container_tag >::type base_container;

        typedef viennagrid::typelist<
            viennagrid::static_pair<
                element_tag,
                interface_information_wrapper<segment_id_type, base_container, ChangeCounterType>
            >,
            typename interface_information_collection_typemap_impl<segment_id_type, interface_information_container_tag, ChangeCounterType, tail>::type
        > type;
      };


      template<typename element_taglist, typename segment_id_type, typename interface_information_container_tag, typename ChangeCounterType>
      struct interface_information_collection_typemap
      {
        typedef typename viennagrid::result_of::cell_tag_from_typelist<element_taglist>::type cell_tag;
        typedef typename viennagrid::detail::result_of::erase< element_taglist, cell_tag>::type element_typelist_without_cell_tag;

        typedef typename interface_information_collection_typemap_impl<segment_id_type, interface_information_container_tag, ChangeCounterType, element_typelist_without_cell_tag>::type type;
      };
    }

    namespace result_of
    {
      /** @brief For internal use only */
      template<typename segment_element_info_container_typemap, typename segment_id_type, typename container_tag, typename segment_info_container_tag>
      struct segmentation_info_container_typemap;

      template<typename segment_id_type, typename container_tag, typename segment_info_container_tag>
      struct segmentation_info_container_typemap< viennagrid::null_type, segment_id_type, container_tag, segment_info_container_tag >
      {
        typedef viennagrid::null_type type;
      };

      template<typename element_tag, typename segment_info_type, typename tail, typename segment_id_type, typename container_tag, typename segment_info_container_tag>
      struct segmentation_info_container_typemap< viennagrid::typelist<viennagrid::static_pair<element_tag, segment_info_type>, tail>, segment_id_type, container_tag, segment_info_container_tag >
      {
        typedef viennagrid::static_pair< element_tag, segment_info_type > key_type;
        typedef typename viennagrid::result_of::container< std::pair<segment_id_type, segment_info_type>, segment_info_container_tag>::type segment_info_container;
        typedef typename viennagrid::result_of::container<segment_info_container, container_tag>::type container_type;

        typedef viennagrid::typelist<
            viennagrid::static_pair<
                element_tag,
                container_type
            >,
            typename segmentation_info_container_typemap<tail, segment_id_type, container_tag, segment_info_container_tag>::type
        > type;
      };


      /** @brief For internal use only */
      template<typename element_typelist, typename segment_id_type, typename container_tag = viennagrid::std_deque_tag>
      struct trivial_segmentation_appendix;

      template<typename segment_id_type,typename container_tag>
      struct trivial_segmentation_appendix< viennagrid::null_type, segment_id_type, container_tag >
      {
        typedef viennagrid::null_type type;
      };

      template<typename element_type, typename tail, typename segment_id_type, typename container_tag>
      struct trivial_segmentation_appendix< viennagrid::typelist<element_type, tail>, segment_id_type, container_tag >
      {
        typedef viennagrid::typelist<
            viennagrid::static_pair<
                element_type,
                typename viennagrid::result_of::container<
                    segment_info_t< element_segment_mapping<segment_id_type> >,
                    container_tag
                >::type
            >,
            typename trivial_segmentation_appendix<tail, segment_id_type, container_tag>::type
        > type;
      };
    } //namespace result_of
  } //namespace detail

  namespace result_of
  {

    /** @brief Metafunction for obtaining a segmentation type for a mesh type and with settings. Segment element information is not present (see segment_element_info for more information)
     *
     * @tparam MeshT          The base mesh type to which the segmentation is associated
     * @tparam ViewT            The mesh view type representing the referenced elements, default ist default mesh view from MeshT
     * @tparam SegmentIDType    The ID type for segments, default is int
     * @tparam AppendixType     The appendix type, for internal use only, don't change default type unless you know what you are doing :)
     */
    template<typename MeshT,
             typename ViewT = typename viennagrid::result_of::mesh_view<MeshT>::type,
             typename SegmentIDType = int,
             typename AppendixType =
                viennagrid::collection<
                    typename viennagrid::make_typemap<
                        viennagrid::detail::element_segment_mapping_tag,
                        viennagrid::collection<
                            typename viennagrid::detail::result_of::trivial_segmentation_appendix<
                                typename viennagrid::result_of::element_typelist<MeshT>::type,
                                SegmentIDType
                            >::type
                        >,


                        interface_information_collection_tag,
                        viennagrid::collection<
                          typename viennagrid::detail::result_of::interface_information_collection_typemap<
                            typename viennagrid::result_of::element_taglist<MeshT>::type,
                            SegmentIDType,
                            viennagrid::std_vector_tag,
                            typename viennagrid::result_of::change_counter_type<MeshT>::type
                          >::type
                        >

                    >::type
                >,
            typename view_container_tag = viennagrid::std_deque_tag >
    struct segmentation
    {
      typedef config::segmentation_config_wrapper_t<MeshT, ViewT, SegmentIDType, AppendixType, view_container_tag> WrappedConfigType;

      typedef viennagrid::segmentation<WrappedConfigType> type;
    };

    /** @brief Returns the underlying segmentation type from a segment_handle (Segment) object */
    template<typename SegmentationT>
    struct segmentation< viennagrid::segment_handle<SegmentationT> >
    {
      typedef SegmentationT  type;
    };

    template<typename SegmentationT>
    struct segmentation< viennagrid::segment_handle<const SegmentationT> >
    {
      typedef SegmentationT  type;
    };


    /** @brief Metafunction for obtaining a segmentation type using only cells for a mesh type and with settings. Segment element information is not present (see segment_element_info for more information)
     *
     * @tparam MeshT          The base mesh type to which the segmentation is associated
     * @tparam ViewT            The mesh view type representing the referenced elements, default ist default mesh view from MeshT
     * @tparam SegmentIDType    The ID type for segments, default is int
     * @tparam AppendixType     The appendix type, for internal use only, don't change default type unless you know what you are doing :)
     */
    template<typename MeshT,
             typename ViewT =
              typename viennagrid::result_of::mesh_view_from_typelist<
                MeshT,
                typename viennagrid::make_typelist<typename viennagrid::result_of::cell<MeshT>::type>::type,
                viennagrid::make_typemap<default_tag, std_deque_tag>::type
              >::type,
             typename SegmentIDType = int,
             typename AppendixType =
                viennagrid::collection<
                    typename viennagrid::make_typemap<
                        viennagrid::detail::element_segment_mapping_tag,
                        viennagrid::collection<
                            typename viennagrid::detail::result_of::trivial_segmentation_appendix<
                                typename viennagrid::result_of::element_typelist<MeshT>::type,
                                SegmentIDType
                            >::type
                        >,


                        interface_information_collection_tag,
                        viennagrid::collection<
                          typename viennagrid::detail::result_of::interface_information_collection_typemap<
                            typename viennagrid::result_of::element_taglist<MeshT>::type,
                            SegmentIDType,
                            viennagrid::std_vector_tag,
                            typename viennagrid::result_of::change_counter_type<MeshT>::type
                          >::type
                        >

                    >::type
                >,
            typename view_container_tag = viennagrid::std_deque_tag >
    struct cell_only_segmentation
    {
      typedef config::segmentation_config_wrapper_t<MeshT, ViewT, SegmentIDType, AppendixType, view_container_tag> WrappedConfigType;

      typedef viennagrid::segmentation<WrappedConfigType> type;
    };




    /** @brief Metafunction for obtaining a segmentation type for a 3D hull mesh type and with settings. Segment element information is a bool (see segment_element_info for more information)
     *
     * @tparam MeshT          The base mesh type to which the segmentation is associated
     * @tparam ViewT            The mesh view type representing the referenced elements, default ist default mesh view from MeshT
     * @tparam SegmentIDType    The ID type for segments, default is int
     * @tparam AppendixType     The appendix type, for internal use only, don't change default type unless you know what you are doing :)
     */
    template<typename MeshT,
             typename ViewT = typename viennagrid::result_of::mesh_view<MeshT>::type,
             typename SegmentIDType = int,
             typename AppendixType =
              viennagrid::collection<
                typename viennagrid::make_typemap<
                    viennagrid::detail::element_segment_mapping_tag,
                    viennagrid::collection<
                        typename viennagrid::detail::result_of::modify<
                            typename viennagrid::detail::result_of::trivial_segmentation_appendix<
                                typename viennagrid::result_of::element_typelist<MeshT>::type,
                                SegmentIDType
                            >::type,
                            viennagrid::static_pair<
                                typename viennagrid::result_of::element< MeshT, viennagrid::triangle_tag >::type,
                                typename viennagrid::result_of::container<
                                    viennagrid::detail::segment_info_t< viennagrid::detail::element_segment_mapping<SegmentIDType, bool> >,
                                    viennagrid::std_deque_tag
                                >::type
                            >
                        >::type
                    >,

                    interface_information_collection_tag,
                    viennagrid::collection<
                      typename viennagrid::detail::result_of::interface_information_collection_typemap<
                        typename viennagrid::result_of::element_taglist<MeshT>::type,
                        SegmentIDType,
                        viennagrid::std_vector_tag,
                        typename viennagrid::result_of::change_counter_type<MeshT>::type
                      >::type
                    >

                >::type
            >,
            typename view_container_tag = viennagrid::std_deque_tag >
    struct oriented_3d_hull_segmentation
    {
      typedef config::segmentation_config_wrapper_t<MeshT, ViewT, SegmentIDType, AppendixType, view_container_tag> WrappedConfigType;

      typedef viennagrid::segmentation<WrappedConfigType> type;
    };

  }



  namespace detail
  {


    /** @brief For internal use only */
    template<typename segment_handle_type, typename element_segment_mapping_type, typename container_tag>
    bool is_in_segment( segment_handle_type const & segment, segment_info_t<element_segment_mapping_type, container_tag> const & segment_info )
    {
      typedef typename segment_info_t<element_segment_mapping_type, container_tag>::element_segment_mapping_container_type element_segment_mapping_container_type;

      for (typename element_segment_mapping_container_type::const_iterator it = segment_info.element_segment_mapping_container.begin();
            it != segment_info.element_segment_mapping_container.end();
            ++it)
      {
        if (it->segment_id == segment.id()) return true;
      }

      return false;
    }

    /** @brief For internal use only */
    template< typename segment_handle_type, typename accessor_type, typename element_type >
    bool is_in_segment( segment_handle_type const & segment, accessor_type const accessor, element_type const & element )
    {
      return is_in_segment( segment, accessor(element) );
    }
  }

  /** @brief Queries if element is within a given segment
    *
    * @tparam SegmentHandleT        The segment type which might include the element
    * @tparam ElementTagT     The element tag of the element which might be included in the segment
    * @tparam WrappedConfigT  The wrapped config of the element which might be included in the segment
    * @param  segment         The segment object which might include the element
    * @param  element         The element object which might be included in the segment
    * @return                 True if the element is in the segment, false otherwise
    */
  template<typename SegmentHandleT, typename ElementTagT, typename WrappedConfigT>
  bool is_in_segment( SegmentHandleT const & segment, viennagrid::element<ElementTagT, WrappedConfigT> const & element )
  {
    typedef viennagrid::element<ElementTagT, WrappedConfigT> element_type;
    return detail::is_in_segment( segment, viennagrid::make_accessor<element_type>( element_segment_mapping_collection(segment) ), element );
  }


  /** @brief Defines a range of segment IDs which represents segments in which an element is included, use result_of::segment_id_range for defining this type
    *
    * @tparam SegmentInfoT        For internal use only
    */
  template<typename SegmentInfoT>
  struct segment_id_range_t
  {
  public:

    segment_id_range_t(SegmentInfoT & segment_info) : segment_info_(&segment_info) {}

    /** @brief An iterator for iterating over all segment IDs */
    typedef typename SegmentInfoT::const_iterator         iterator;
    /** @brief An iterator for iterating over all segment IDs */
    typedef typename SegmentInfoT::const_iterator   const_iterator;

    /** @brief Returns an iterator pointing to the first segment ID
      *
      * @return    An iterator pointing to the first segment ID
      */
    iterator begin() { return segment_info_->begin(); }
    /** @brief Returns an iterator pointing to the end of the segment IDs
      *
      * @return    An iterator pointing to the end of the segment IDs
      */
    iterator end() { return segment_info_->end(); }

    /** @brief Returns a const iterator pointing to the first segment ID
      *
      * @return    A const iterator pointing to the first segment ID
      */
    const_iterator cbegin() { return segment_info_->cbegin(); }
    /** @brief Returns a const iterator pointing to the end of the segment IDs
      *
      * @return    A const iterator pointing to the end of the segment IDs
      */
    const_iterator cend() { return segment_info_->cend(); }

    /** @brief Returns a const iterator pointing to the first segment ID, const version
      *
      * @return    A const iterator pointing to the first segment ID
      */
    const_iterator begin() const { return segment_info_->begin(); }
    /** @brief Returns a const iterator pointing to the end of the segment IDs, const version
      *
      * @return    A const iterator pointing to the end of the segment IDs
      */
    const_iterator end() const { return segment_info_->end(); }

    /** @brief Returns the number of segment ids
      *
      * @return    The number of segment ids
      */
    std::size_t size() const { return segment_info_->size(); }

    /** @brief Returns if the segment id container is empty
      *
      * @return    true if the segment id container is empty, false otherwise
      */
    bool empty() const { return segment_info_->empty(); }

    /** @brief Checks, if two segment id ranges are equal
      *
      * @param other  The other segment id range
      * @return       true if the segment id ranges are equal, false otherwise
      */
    std::size_t is_equal( segment_id_range_t<SegmentInfoT> const & other ) const { return segment_info_->is_equal(*other.segment_info_); }

  private:
    SegmentInfoT * segment_info_;
  };

  namespace result_of
  {
    /** @brief Defines a range of segment IDs which represents segments in which an element is included
      *
      * @tparam SegmentOrSegmentationT        The host segmentation/segment type
      * @tparam ElementT                      The element type for which the segment id range is queried
      */
    template<typename SegmentationT, typename ElementTypeOrTagT>
    struct segment_id_range
    {
      typedef typename viennagrid::result_of::element_tag<ElementTypeOrTagT>::type ElementTagT;
      typedef typename viennagrid::result_of::element<SegmentationT, ElementTagT>::type ElementType;

      typedef typename viennagrid::detail::result_of::lookup<
          typename SegmentationT::appendix_type,
          viennagrid::detail::element_segment_mapping_tag
      >::type ElementSegmentMappingCollectionType;

      typedef typename viennagrid::result_of::container_of<
        ElementSegmentMappingCollectionType,
        ElementType
      >::type ElementSegmentMappingContainerType;

      typedef segment_id_range_t<const typename ElementSegmentMappingContainerType::value_type> type;
    };

    /** \cond */
    template<typename SegmentationT, typename ElementTypeOrTagT>
    struct segment_id_range< viennagrid::segment_handle<SegmentationT>, ElementTypeOrTagT >
    {
      typedef typename segment_id_range<SegmentationT, ElementTypeOrTagT>::type type;
    };
    /** \endcond */
  }

  /** @brief Obtains the segment ID range of an element within a segmentation. The segment ID range holds all IDs of segments in which the element is included.
    *
    * @tparam SegmentationT   The host segmentation type
    * @tparam ElementTagT     The element tag of the element for which the segment ID range is obtained
    * @tparam WrappedConfigT  The wrapped config of the element for which the segment ID range is obtained
    * @param  segmentation    The host segmentation object
    * @param  element         The element object for which the segment ID range is obtained
    * @return                 The segment ID range
    */
  template<typename SegmentationT, typename ElementTagT, typename WrappedConfigT>
  typename result_of::segment_id_range< SegmentationT, viennagrid::element<ElementTagT, WrappedConfigT> >::type segment_ids( SegmentationT const & segmentation, viennagrid::element<ElementTagT, WrappedConfigT> const & element )
  {
    typedef typename result_of::segment_id_range< SegmentationT, viennagrid::element<ElementTagT, WrappedConfigT> >::type SegmentIDRangeType;
    typedef viennagrid::element<ElementTagT, WrappedConfigT> ElementType;
    return SegmentIDRangeType( viennagrid::make_field<ElementType>( viennagrid::detail::element_segment_mapping_collection(segmentation) )(element) );
  }



  namespace detail
  {

    /** @brief For internal use only */
    template<typename segment_handle_type, typename element_segment_mapping_type, typename container_tag>
    typename element_segment_mapping_type::segment_element_info_type *
    segment_element_info( segment_handle_type const & segment, segment_info_t<element_segment_mapping_type, container_tag> & segment_info )
    {
      typedef typename segment_info_t<element_segment_mapping_type, container_tag>::element_segment_mapping_container_type element_segment_mapping_container_type;

      for (typename element_segment_mapping_container_type::iterator it = segment_info.element_segment_mapping_container.begin();
            it != segment_info.element_segment_mapping_container.end();
            ++it)
      {
        if (it->segment_id == segment.id())
          return &(it->segment_element_info);
      }

      return NULL;
    }

    /** @brief For internal use only */
    template<typename segment_handle_type, typename element_segment_mapping_type, typename container_tag>
    typename element_segment_mapping_type::segment_element_info_type const *
    segment_element_info( segment_handle_type const & segment, segment_info_t<element_segment_mapping_type, container_tag> const & segment_info )
    {
      typedef typename segment_info_t<element_segment_mapping_type, container_tag>::element_segment_mapping_container_type element_segment_mapping_container_type;

      for (typename element_segment_mapping_container_type::const_iterator it = segment_info.element_segment_mapping_container.begin();
            it != segment_info.element_segment_mapping_container.end();
            ++it)
      {
        if (it->segment_id == segment.id())
          return &(it->segment_element_info);
      }

      return NULL;
    }

    /** @brief For internal use only */
    template< typename segment_handle_type, typename accessor_type, typename element_type >
    typename accessor_type::value_type::segment_element_info_type *
    segment_element_info( segment_handle_type & segment, accessor_type accessor, element_type const & element )
    {
      return segment_element_info( segment, accessor(element) );
    }

    /** @brief For internal use only */
    template< typename segment_handle_type, typename accessor_type, typename element_type >
    typename accessor_type::value_type::segment_element_info_type const *
    segment_element_info( segment_handle_type const & segment, const accessor_type accessor, element_type const & element )
    {
      return segment_element_info( segment, accessor(element) );
    }
  }

  /** @brief Returns a pointer to additional segment element information. Segment element information is meta information for a combination of a segment and an element, e.g. the orientation of a triangle in a segment in a 3D hull mesh
    *
    * @tparam SegmentHandleT        The segment type
    * @tparam ElementTagT     The element tag of the element
    * @tparam WrappedConfigT  The wrapped config of the element
    * @param  segment         The segment object
    * @param  element         The element object
    * @return                 A pointer to the segment element information type
    */
  template<typename SegmentHandleT, typename ElementTagT, typename WrappedConfigT>
  typename viennagrid::result_of::container_of<
      typename viennagrid::detail::result_of::lookup<
          typename SegmentHandleT::segmentation_type::appendix_type,
          viennagrid::detail::element_segment_mapping_tag
      >::type,
      viennagrid::element<ElementTagT, WrappedConfigT>
  >::type::value_type::segment_element_info_type const *
  segment_element_info( SegmentHandleT const & segment, viennagrid::element<ElementTagT, WrappedConfigT> const & element )
  {
    typedef viennagrid::element<ElementTagT, WrappedConfigT> element_type;
    return detail::segment_element_info( segment, viennagrid::make_accessor<element_type>( element_segment_mapping_collection(segment) ), element );
  }

  /** @brief Returns a pointer to additional segment element information. Segment element information is meta information for a combination of a segment and an element, e.g. the orientation of a triangle in a segment in a 3D hull mesh. Const version
    *
    * @tparam SegmentHandleT        The segment type
    * @tparam ElementTagT     The element tag of the element
    * @tparam WrappedConfigT  The wrapped config of the element
    * @param  segment         The segment object
    * @param  element         The element object
    * @return                 A const pointer to the segment element information type
    */
  template<typename SegmentHandleT, typename ElementTagT, typename WrappedConfigT>
  typename viennagrid::result_of::container_of<
      typename viennagrid::detail::result_of::lookup<
          typename SegmentHandleT::segmentation_type::appendix_type,
          viennagrid::detail::element_segment_mapping_tag
      >::type,
      viennagrid::element<ElementTagT, WrappedConfigT>
  >::type::value_type::segment_element_info_type *
  segment_element_info( SegmentHandleT & segment, viennagrid::element<ElementTagT, WrappedConfigT> const & element )
  {
    typedef viennagrid::element<ElementTagT, WrappedConfigT> element_type;
    return detail::segment_element_info( segment, viennagrid::make_accessor<element_type>( element_segment_mapping_collection(segment) ), element );
  }


  namespace detail
  {
    /** @brief For internal use only */
    template<typename segment_handle_type, typename element_segment_mapping_type, typename container_tag>
    void add(segment_handle_type & segment,
             segment_info_t<element_segment_mapping_type, container_tag> & segment_info)
    {
      typedef typename segment_info_t<element_segment_mapping_type, container_tag>::element_segment_mapping_container_type element_segment_mapping_container_type;

      for (typename element_segment_mapping_container_type::const_iterator it = segment_info.element_segment_mapping_container.begin();
            it != segment_info.element_segment_mapping_container.end();
            ++it)
      {
        if (it->segment_id == segment.id()) return;
      }

      segment_info.element_segment_mapping_container.push_back( element_segment_mapping_type(segment.id()) );
      increment_change_counter( segment.view() );
    }

    /** @brief For internal use only */
    template< typename segment_handle_type, typename accessor_type, typename element_type >
    void add( segment_handle_type & segment, accessor_type accessor, element_type & element )
    {
      return add( segment, accessor(element) );
    }
  }



  namespace detail
  {
    /** @brief For internal use only */
    template<typename SegmentHandleT, typename ElementTagT, typename WrappedConfigT>
    void simple_add( SegmentHandleT & segment, viennagrid::element<ElementTagT, WrappedConfigT> & element )
    {
      typedef viennagrid::element<ElementTagT, WrappedConfigT> ElementType;

      viennagrid::elements<ElementType>( segment.view() ).insert_unique_handle( viennagrid::handle( segment.parent().mesh(), element ) );
      viennagrid::elements<ElementType>( segment.parent().all_elements() ).insert_unique_handle( viennagrid::handle( segment.parent().mesh(), element ) );
      add( segment, viennagrid::make_accessor<ElementType>( detail::element_segment_mapping_collection(segment) ), element );
    }

    /** @brief For internal use only */
    template<typename SegmentT>
    struct add_functor
    {
      add_functor(SegmentT & segment_) : segment(segment_) {}

      template<typename BoundaryElementT>
      void operator()( BoundaryElementT & boundary_element )
      {
        detail::simple_add(segment, boundary_element);
      }

      SegmentT & segment;
    };

    /** @brief For internal use only */
    template<typename SegmentHandleT, typename ElementTagT, typename WrappedConfigT>
    void simple_unchecked_add( SegmentHandleT & segment, viennagrid::element<ElementTagT, WrappedConfigT> & element )
    {
      typedef viennagrid::element<ElementTagT, WrappedConfigT> ElementType;

      viennagrid::elements<ElementType>( segment.view() ).insert_handle( viennagrid::handle( segment.parent().mesh(), element ) );
      viennagrid::elements<ElementType>( segment.parent().all_elements() ).insert_handle( viennagrid::handle( segment.parent().mesh(), element ) );
      add( segment, viennagrid::make_accessor<ElementType>( detail::element_segment_mapping_collection(segment) ), element );
    }

    /** @brief For internal use only */
    template<typename SegmentT>
    struct unchecked_add_functor
    {
      unchecked_add_functor(SegmentT & segment_) : segment(segment_) {}

      template<typename BoundaryElementT>
      void operator()( BoundaryElementT & boundary_element )
      {
        detail::simple_unchecked_add(segment, boundary_element);
      }

      SegmentT & segment;
    };
  }





  /** @brief Adds an element to a segment, all boundary elements are added recursively
    *
    * @tparam SegmentHandleT        The segment type
    * @tparam ElementTagT     The element tag of the element
    * @tparam WrappedConfigT  The wrapped config of the element
    * @param  segment         The segment object to which the element is added
    * @param  element         The element object to be added
    */
  template<typename SegmentHandleT, typename ElementTagT, typename WrappedConfigT>
  void add( SegmentHandleT & segment, viennagrid::element<ElementTagT, WrappedConfigT> & element )
  {
    typedef viennagrid::element<ElementTagT, WrappedConfigT> ElementType;

    detail::simple_add(segment, element);

    typedef typename ElementType::boundary_cell_typelist BoundaryElementTypelist;
    typedef typename viennagrid::result_of::element_typelist<SegmentHandleT>::type SegmentTypelist;
    typedef typename viennagrid::detail::result_of::intersection<BoundaryElementTypelist, SegmentTypelist>::type ForEachTypelist;

    detail::add_functor<SegmentHandleT> af(segment);
    for_each_boundary_element<ForEachTypelist>( element, af );
  }

  /** @brief Adds an element to a segment, all boundary elements are added recursively
    *
    * @tparam SegmentHandleT     The segment type
    * @tparam ElementHandleT     The element tag of the element
    * @param  segment            The segment object to which the element is added
    * @param  element_handle     A handle of the element object to be added
    */
  template<typename SegmentHandleT, typename ElementHandleT>
  void add( SegmentHandleT & segment, ElementHandleT element_handle )
  { viennagrid::add( segment, viennagrid::dereference_handle(segment, element_handle) ); }



  /** @brief Adds an element to a segment, all boundary elements are added recursively
    *
    * @tparam WrappedConfigT     The wrapped config of the segmentation
    * @tparam ElementTagT        The element tag of the element
    * @tparam WrappedConfigT     The wrapped config of the element
    * @param  segmentation_obj   The segmentation object
    * @param  segment_id         The id of the segment element is added
    * @param  element            The element object to be added
    */
  template<typename WrappedConfigT, typename ElementTagT, typename WrappedElementConfigT>
  void add( segmentation<WrappedConfigT> & segmentation_obj,
            typename segmentation<WrappedConfigT>::segment_id_type segment_id,
            viennagrid::element<ElementTagT, WrappedElementConfigT> & element)
  { add( segmentation_obj[segment_id], element ); }

  /** @brief Adds an element to a segment, all boundary elements are added recursively
    *
    * @tparam WrappedConfigT     The wrapped config of the segmentation
    * @tparam ElementHandleT     The element tag of the element
    * @param  segmentation_obj   The segmentation object
    * @param  segment_id         The id of the segment element is added
    * @param  element_handle     A handle of the element object to be added
    */
  template<typename WrappedConfigT, typename ElementHandleT>
  void add( segmentation<WrappedConfigT> & segmentation_obj,
            typename segmentation<WrappedConfigT>::segment_id_type segment_id,
            ElementHandleT element_handle)
  { add( segmentation_obj[segment_id], element_handle ); }


  /** @brief Adds an element to all segment provided in a segment id iterator range
    *
    * @tparam WrappedConfigT     The wrapped config of the segmentation
    * @tparam SegmentIDIteratorT The segment id iterator type
    * @tparam ElementTagT        The element tag of the element
    * @tparam WrappedConfigT     The wrapped config of the element
    * @param  segmentation_obj   The segmentation
    * @param  segment_ids_it     The begin segment id iterator
    * @param  segment_ids_end    The end segment id iterator
    * @param  element            The element to be added
    */
  template<typename WrappedConfigT, typename SegmentIDIteratorT, typename ElementTagT, typename WrappedElementConfigT>
  void add( segmentation<WrappedConfigT> & segmentation_obj,
            SegmentIDIteratorT segment_ids_it, SegmentIDIteratorT const & segment_ids_end,
            viennagrid::element<ElementTagT, WrappedElementConfigT> & element)
  {
    for (; segment_ids_it != segment_ids_end; ++segment_ids_it)
      add( segmentation_obj[*segment_ids_it], element );
  }

  /** @brief Adds an element to all segment provided in a segment id iterator range
    *
    * @tparam WrappedConfigT     The wrapped config of the segmentation
    * @tparam SegmentIDIteratorT The segment id iterator type
    * @tparam ElementHandleT     The element tag of the element
    * @param  segmentation_obj   The segmentation object
    * @param  segment_ids_it     The begin segment id iterator
    * @param  segment_ids_end    The end segment id iterator
    * @param  element_handle     A handle of the element object to be added
    */
  template<typename WrappedConfigT, typename SegmentIDIteratorT, typename ElementHandleT>
  void add( segmentation<WrappedConfigT> & segmentation_obj,
            SegmentIDIteratorT segment_ids_it, SegmentIDIteratorT const & segment_ids_end,
            ElementHandleT element_handle)
  {
    for (; segment_ids_it != segment_ids_end; ++segment_ids_it)
      add( segmentation_obj[*segment_ids_it], element_handle );
  }


  /** @brief Adds an element to a segment, all boundary elements are added recursively, does guarantee that elements are only present once within the segment
    *
    * @tparam SegmentHandleT        The segment type
    * @tparam ElementTagT     The element tag of the element
    * @tparam WrappedConfigT  The wrapped config of the element
    * @param  segment         The segment object to which the elemen is added
    * @param  element         The element object to be added
    */
  template<typename SegmentHandleT, typename ElementTagT, typename WrappedConfigT>
  void unchecked_add( SegmentHandleT & segment, viennagrid::element<ElementTagT, WrappedConfigT> & element )
  {
    typedef viennagrid::element<ElementTagT, WrappedConfigT> ElementType;

    detail::simple_unchecked_add(segment, element);

    typedef typename ElementType::boundary_cell_typelist BoundaryElementTypelist;
    typedef typename viennagrid::result_of::element_typelist<SegmentHandleT>::type SegmentTypelist;
    typedef typename viennagrid::detail::result_of::intersection<BoundaryElementTypelist, SegmentTypelist>::type ForEachTypelist;

    detail::unchecked_add_functor<SegmentHandleT> uaf(segment);
    for_each_boundary_element<ForEachTypelist>( element, uaf );
  }

  /** @brief Adds an element to a segment, all boundary elements are added recursively, does guarantee that elements are only present once within the segment
    *
    * @tparam SegmentHandleT      The segment type
    * @tparam ElementHandleT      The element handle type
    * @param  segment             The segment object to which the elemen is added
    * @param  element_handle      A handle of the element object to be added
    */
  template<typename SegmentHandleT, typename ElementHandleT>
  void unchecked_add( SegmentHandleT & segment, ElementHandleT element_handle )
  { viennagrid::unchecked_add( segment, viennagrid::dereference_handle(segment, element_handle) ); }


  namespace detail
  {


    /** @brief For internal use only */
    template<typename SegmentHandleT, typename ElementSegmentMappingT, typename ContainerTagT>
    void erase( SegmentHandleT & segment, segment_info_t<ElementSegmentMappingT, ContainerTagT> & segment_info )
    {
      typedef typename segment_info_t<ElementSegmentMappingT, ContainerTagT>::element_segment_mapping_container_type element_segment_mapping_container_type;

      for (typename element_segment_mapping_container_type::iterator it = segment_info.element_segment_mapping_container.begin();
                                                                     it != segment_info.element_segment_mapping_container.end();
                                                                   ++it)
      {
        if (it->segment_id == segment.id())
        {
          segment_info.element_segment_mapping_container.erase(it);
          increment_change_counter( segment.view() );
          return;
        }
      }
    }

    /** @brief For internal use only */
    template< typename SegmentHandleT, typename AccessorT, typename ElementT >
    void erase( SegmentHandleT & segment, AccessorT accessor, ElementT const & element )
    {
      return erase( segment, accessor(element) );
    }


//   template<typename SegmentHandleT, typename ElementTagT, typename WrappedConfigT>
//   bool non_recursive_erase( SegmentHandleT & segment, viennagrid::element<ElementTagT, WrappedConfigT> & element )
//   {
//     typedef viennagrid::element<ElementTagT, WrappedConfigT> element_type;
//     viennagrid::elements<element_type>( segment.view() ).erase_handle( viennagrid::handle( segment.parent().mesh(), element ) );
//     return erase( segment, viennagrid::make_accessor<element_type>( element_segment_mapping_collection(segment) ), element );
//   }

    template<typename SegmentHandleT>
    struct non_recursive_erase_functor
    {
      non_recursive_erase_functor(SegmentHandleT & segment_) : segment(segment_) {}

      template<typename ElementT>
      void operator() ( ElementT & element )
      {
        // erasing element from segment view
        viennagrid::elements<ElementT>( segment.view() ).erase_handle( viennagrid::handle( segment.parent().mesh(), element ) );
        // erasing element from segment-element information
        erase( segment, viennagrid::make_accessor<ElementT>( element_segment_mapping_collection(segment) ), element );

        if (segment_ids(segment.parent(), element).empty())
          viennagrid::elements<ElementT>( segment.parent().all_elements() ).erase_handle( viennagrid::handle( segment.parent().mesh(), element ) );
      }

      SegmentHandleT & segment;
    };
  }



  /** @brief Function for creating a handle for a given element using a mesh/segment object
    *
    * @tparam MeshOrSegmentHandleT      The host mesh/segment type
    * @tparam ElementTagT           The tag of the element of which a handle is created
    * @tparam WrappedConfigT        The wrapped config of the element of which a handle is created
    * @param  mesh_or_segment     The host mesh/segment object
    * @param  element               The element of which a handle is created
    * @return                       A handle referencing the given element
    */
  template<typename SegmentationType, typename ElementTagT, typename WrappedConfigT>
  typename result_of::handle<segment_handle<SegmentationType>, viennagrid::element<ElementTagT, WrappedConfigT> >::type
  handle(segment_handle<SegmentationType> & mesh_or_segment, viennagrid::element<ElementTagT, WrappedConfigT> & element)
  { return get< viennagrid::element<ElementTagT, WrappedConfigT> >(detail::element_collection(mesh_or_segment)).handle( element ); }

  /** @brief Function for creating a handle for a given element using a mesh/segment object, const version
    *
    * @tparam MeshOrSegmentHandleT      The host mesh/segment type
    * @tparam ElementTagT           The tag of the element of which a handle is created
    * @tparam WrappedConfigT        The wrapped config of the element of which a handle is created
    * @param  mesh_or_segment     The host mesh/segment object
    * @param  element               The element of which a handle is created
    * @return                       A const handle referencing the given element
    */
  template<typename SegmentationType, typename ElementTagT, typename WrappedConfigT>
  typename result_of::const_handle<segment_handle<SegmentationType>, viennagrid::element<ElementTagT, WrappedConfigT> >::type
  handle(segment_handle<SegmentationType> const & mesh_or_segment, viennagrid::element<ElementTagT, WrappedConfigT> const & element)
  { return get< viennagrid::element<ElementTagT, WrappedConfigT> >(detail::element_collection(mesh_or_segment)).handle( element ); }


  /** @brief Deletes an element from a segment. The runtime of this function is linear in the number of elements of the element type to delete
    *
    * @tparam SegmentHandleT        The segment type
    * @tparam ElementTagT     The element tag of the element type to be deleted
    * @tparam WrappedConfigT  The wrapped config of the element type to be deleted
    * @param  segment         The segment object from which the element is to be deleted
    * @param  element         The element object to be deleted from the segment
    * @return                 True if the element is deleted from the segment, false otherwise
    */
  template<typename SegmentHandleT, typename ElementTagT, typename WrappedConfigT>
  void erase( SegmentHandleT & segment, viennagrid::element<ElementTagT, WrappedConfigT> & element )
  {
    typedef typename viennagrid::result_of::mesh_view<SegmentHandleT>::type ToEraseViewT;
    ToEraseViewT elements_to_erase = viennagrid::make_view(segment);
    viennagrid::mark_referencing_elements( segment, elements_to_erase, viennagrid::handle(segment, element) );

    detail::non_recursive_erase_functor<SegmentHandleT> functor( segment );
    viennagrid::for_each(elements_to_erase, functor);
  }


  namespace detail
  {

    /** @brief For internal use only */
    template<bool generate_id, bool call_callback, typename SegmentationType, typename ElementTag, typename WrappedConfigType>
    std::pair<
                typename viennagrid::result_of::container_of<
                    typename viennagrid::result_of::element_collection< viennagrid::segment_handle<SegmentationType> >::type,
                    viennagrid::element<ElementTag, WrappedConfigType>
                >::type::handle_type,
                bool
            >
    push_element( viennagrid::segment_handle<SegmentationType> & segment, viennagrid::element<ElementTag, WrappedConfigType> const & element)
    {
      std::pair<
              typename viennagrid::result_of::container_of<
                  typename viennagrid::result_of::element_collection< viennagrid::segment_handle<SegmentationType> >::type,
                  viennagrid::element<ElementTag, WrappedConfigType>
              >::type::handle_type,
              bool
          > result = push_element<generate_id, call_callback>( segment.view(), element );

      viennagrid::add( segment, viennagrid::dereference_handle(segment, result.first) );
      return result;
    }
  }




  /** @brief Adds a single element handle (no boundary elements/handles) to a view if it isn't already present in that view. The runtime of this function is linear in the number of elements present in the view.
    *
    * @tparam ViewT    The view/segment type
    * @tparam HandleT           The handle to be added
    * @param  view_or_segment   The view/segment object
    * @param  handle            The handle object to be inserted
    */
  template<typename ViewT, typename HandleT>
  void add_single_handle( ViewT & view_or_segment, HandleT handle )
  {
    typedef typename detail::result_of::value_type<HandleT>::type value_type;
    value_type & element = dereference_handle(view_or_segment, handle);

    typedef typename viennagrid::result_of::element_range< ViewT, value_type >::type range_type;
    typedef typename viennagrid::result_of::iterator<range_type>::type iterator_type;

    iterator_type it = find( view_or_segment, element.id() );
    if ( it == elements<value_type>(view_or_segment).end() )
      viennagrid::get<value_type>( detail::element_collection(view_or_segment) ).insert_handle( handle );

    viennagrid::detail::increment_change_counter(view_or_segment);
  }







  namespace detail
  {
    /** @brief Functor for copying a segmentation. For internal use only. */
    template<typename SourceMeshT, typename SourceSegmentationT,
            typename DestinationMeshT, typename DestinationSegmentationT>
    struct copy_segmentation_functor
    {
      copy_segmentation_functor(SourceMeshT const & src_mesh_, SourceSegmentationT const & src_segmentation_,
                                DestinationMeshT & dst_mesh_, DestinationSegmentationT & dst_segmentation_) :
                                src_mesh(src_mesh_), src_segmentation(src_segmentation_),
                                dst_mesh(dst_mesh_), dst_segmentation(dst_segmentation_) {}

      template<typename DestinationElementT>
      void operator()( DestinationElementT & dst_element )
      {
        typedef typename viennagrid::result_of::element_tag<DestinationElementT>::type ElementTag;
        typedef typename viennagrid::result_of::const_element_range<SourceMeshT, ElementTag>::type ConstSourceElementRangeType;
        typedef typename viennagrid::result_of::iterator<ConstSourceElementRangeType>::type ConstSourceElementIteratorType;

        ConstSourceElementIteratorType src_eit = viennagrid::find( src_mesh, dst_element.id() );

        typedef typename viennagrid::result_of::element<SourceMeshT, ElementTag>::type SourceElementType;
        typedef typename viennagrid::result_of::segment_id_range<SourceSegmentationT, SourceElementType>::type SegmentIDRangeType;
        typedef typename viennagrid::result_of::iterator<SegmentIDRangeType>::type SegmentIDIteratorType;
        SegmentIDRangeType segment_ids = viennagrid::segment_ids(src_segmentation, *src_eit);
        for (SegmentIDIteratorType sit = segment_ids.begin(); sit != segment_ids.end(); ++sit)
        {
          viennagrid::add( dst_segmentation.get_make_segment(*sit), dst_element );
        }
      }

      SourceMeshT const & src_mesh;
      SourceSegmentationT const & src_segmentation;

      DestinationMeshT & dst_mesh;
      DestinationSegmentationT & dst_segmentation;
    };
  }


  /** @brief Copies a segmentation. Warning: may be slow!
    *
    * @param  src_mesh_           The source mesh
    * @param  src_segmentation_   The source segmentation
    * @param  dst_mesh_           The destination mesh
    * @param  dst_segmentation_   The destination segmentation
    */
  template<typename SourceMeshT, typename SourceSegmentationT,
           typename DestinationMeshT, typename DestinationSegmentationT>
  void copy_segmentation(SourceMeshT const & src_mesh_, SourceSegmentationT const & src_segmentation_,
                         DestinationMeshT & dst_mesh_, DestinationSegmentationT & dst_segmentation_)
  {
    detail::copy_segmentation_functor<SourceMeshT, SourceSegmentationT, DestinationMeshT, DestinationSegmentationT> functor( src_mesh_, src_segmentation_, dst_mesh_, dst_segmentation_ );
    viennagrid::for_each(dst_mesh_, functor);
  }


}




#endif
