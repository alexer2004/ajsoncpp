#ifndef JSON_ARRAY_VISITOR_H
#define JSON_ARRAY_VISITOR_H

#include "object_visitor.h"
#include "array_getter.h"
#include "value_object.h"
#include <stdexcept>


namespace json{

class array_visitor : public object_visitor
{
public:
	typedef array_getter value_type;
	array_visitor()
		:pval(0)
	{
	}
	void visit(null_object&)
	{
		throw std::runtime_error("array expected, not null");
	}
	void visit(bool_object&)
	{
		throw std::runtime_error("array expected, not boolean");
	}
	void visit(string_object&)
	{
		throw std::runtime_error("array expected, not string");	
	}
	void visit(int_object& v)
	{
		throw std::runtime_error("array expected, not int");
	}
	void visit(double_object&)
	{
		throw std::runtime_error("array expected, not double");	
	}
	void visit(ptr_map_object&)
	{
		throw std::runtime_error("array expected, not map");
	}
	void visit(ptr_array_object& v)
	{
		pval = &v.value();
	}
	array_getter value()
	{
		return array_getter(pval);
	}
	const array_getter value()const
	{
		return array_getter(pval);
	}
	~array_visitor(){;}
private:
	ptr_array* pval;

};

}


#endif