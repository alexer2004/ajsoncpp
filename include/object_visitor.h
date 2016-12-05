#ifndef JSON_OBJECT_VISITOR_H
#define JSON_OBJECT_VISITOR_H

#include "null_object.h"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cstdint>



namespace json{
	typedef std::int32_t integer;
	
	typedef std::shared_ptr<object> object_ptr;
	typedef std::string string;				//utf-8
	typedef std::unordered_map<string, object_ptr> ptr_map;
	template<class T> class value_object;
	typedef value_object<bool> bool_object;
	typedef value_object<string> string_object;
	typedef value_object<int> int_object;
	typedef value_object<double> double_object;
	typedef value_object<ptr_map> ptr_map_object;
	typedef std::vector<object_ptr> ptr_array;
	typedef value_object<ptr_array> ptr_array_object;

	class object_visitor
	{
	public:
		virtual void visit(null_object&)=0;
		virtual void visit(bool_object&)=0;
		virtual void visit(string_object&)=0;
		virtual void visit(int_object&)=0;
		virtual void visit(double_object&)=0;
		virtual void visit(ptr_map_object&)=0;
		virtual void visit(ptr_array_object&)=0;
		virtual ~object_visitor()=0;

	};

	inline object_visitor::~object_visitor()
	{
	}
}
#endif