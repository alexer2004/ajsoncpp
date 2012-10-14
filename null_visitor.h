#ifndef JSON_NULL_VISITOR_H
#define JSON_NULL_VISITOR_H

#include "object_visitor.h"
#include <stdexcept>


namespace json{

class null_visitor : public object_visitor
{
public:
	typedef bool value_type;
	null_visitor()
		:is_null(false)
	{
	}
	void visit(bool_object&)
	{
		throw std::runtime_error("null expected, not bool");
	}
	void visit(null_object& v)
	{
		is_null = true;	
	}
	void visit(string_object&)
	{
		throw std::runtime_error("null expected, not string");	
	}
	void visit(int_object& v)
	{
		throw std::runtime_error("null expected, not integer");
	}
	void visit(double_object&)
	{
		throw std::runtime_error("null expected, not double");
	}
	void visit(ptr_map_object&)
	{
		throw std::runtime_error("null expected, not map");
	}
	void visit(ptr_array_object&)
	{
		throw std::runtime_error("null query, not array");
	}
	bool value()
	{
		return is_null;
	}
	const bool value()const
	{
		return is_null;
	}
	~null_visitor(){;}
private:
	bool is_null;
};






}





#endif