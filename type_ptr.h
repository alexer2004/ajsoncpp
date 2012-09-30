#ifndef JSON_TYPE_PTR_H
#define JSON_TYPE_PTR_H

#include "object_visitor.h"

namespace json{


#if defined(JSON_BOOST_SHARED_PTR)
	#include "boost/shared_ptr.hpp"
	typedef boost::shared_ptr<ptr_map_object> map_ptr;
	typedef boost::shared_ptr<ptr_array_object> array_ptr;
	typedef boost::shared_ptr<double_object> double_ptr;
	typedef boost::shared_ptr<int_object> int_ptr;
	typedef boost::shared_ptr<string_object> string_ptr;
	typedef boost::shared_ptr<bool_object> bool_ptr;
	typedef boost::shared_ptr<null_object> null_ptr;

#elif defined(JSON_TR1_SHARED_PTR)
	#include <memory>
	typedef std::tr1::shared_ptr<ptr_map_object> map_ptr;
	typedef std::tr1::shared_ptr<ptr_array_object> array_ptr;
	typedef std::tr1::shared_ptr<double_object> double_ptr;
	typedef std::tr1::shared_ptr<int_object> int_ptr;
	typedef std::tr1::shared_ptr<string_object> string_ptr;
	typedef std::tr1::shared_ptr<bool_object> bool_ptr;
	typedef std::tr1::shared_ptr<null_object> null_ptr;
#else
	#include <memory>
	typedef std::shared_ptr<ptr_map_object> map_ptr;
	typedef std::shared_ptr<ptr_array_object> array_ptr;
	typedef std::shared_ptr<double_object> double_ptr;
	typedef std::shared_ptr<int_object> int_ptr;
	typedef std::shared_ptr<string_object> string_ptr;
	typedef std::shared_ptr<bool_object> bool_ptr;
	typedef std::shared_ptr<null_object> null_ptr;
#endif






}




#endif