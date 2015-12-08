#ifndef _LIB_EXCEPTIONS_H_
#define _LIB_EXCEPTIONS_H_

#include <boost/exception/errinfo_api_function.hpp>
#include <boost/exception/errinfo_at_line.hpp>
#include <boost/exception/errinfo_errno.hpp>
#include <boost/exception/errinfo_file_handle.hpp>
#include <boost/exception/errinfo_file_name.hpp>
#include <boost/exception/errinfo_file_open_mode.hpp>
#include <boost/exception/errinfo_nested_exception.hpp>
#include <boost/exception/errinfo_type_info_name.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/current_exception_cast.hpp>
#include <boost/exception/get_error_info.hpp>
#include <boost/exception_ptr.hpp>
#include <boost/exception/info.hpp>
#include <boost/throw_exception.hpp>
#include <errno.h>
#include <exception>
namespace radiolocation
{

	struct error : virtual std::exception, virtual boost::exception{};

	struct file_error : virtual error{};

	struct file_open_error : virtual file_error{};

	struct file_read_error : virtual file_error{};

	struct invalid_value_arg : virtual error{};

	struct empty_vector : virtual error{};

	struct invalid_pointer : virtual error{};
	 

	 
	
}
#endif /*_LIB_EXCEPTIONS_H_*/