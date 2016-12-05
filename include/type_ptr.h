#ifndef JSON_TYPE_PTR_H
#define JSON_TYPE_PTR_H

#include "object_visitor.h"
#include <memory>

namespace json{	
	typedef std::shared_ptr<ptr_map_object> map_ptr;
	typedef std::shared_ptr<ptr_array_object> array_ptr;
	typedef std::shared_ptr<double_object> double_ptr;
	typedef std::shared_ptr<int_object> int_ptr;
	typedef std::shared_ptr<string_object> string_ptr;
	typedef std::shared_ptr<bool_object> bool_ptr;
	typedef std::shared_ptr<null_object> null_ptr;

}
#endif