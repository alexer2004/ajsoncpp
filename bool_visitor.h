#ifndef JSON_BOOL_VISITOR_H
#define JSON_BOOL_VISITOR_H

#include "object_visitor.h"
#include <stdexcept>


namespace json{

class bool_visitor : public object_visitor
{
public:
	typedef bool& value_type;
	bool_visitor()
		:pval(0)
	{
	}
	void visit(null_object&)
	{
		throw std::runtime_error("bool expected, not null");
	}
	void visit(bool_object& v)
	{
		pval = &v.value();	
	}
	void visit(string_object&)
	{
		throw std::runtime_error("bool expected, not string");	
	}
	void visit(int_object& v)
	{
		throw std::runtime_error("bool expected, not integer");
	}
	void visit(double_object&)
	{
		throw std::runtime_error("bool expected, not double");
	}
	void visit(ptr_map_object&)
	{
		throw std::runtime_error("bool expected, not map");
	}
	void visit(ptr_array_object&)
	{
		throw std::runtime_error("bool expected, not array");
	}
	bool &value()
	{
		return *pval;
	}
	const bool &value()const
	{
		return *pval;
	}
	~bool_visitor(){;}
private:
	bool* pval;

};






}





#endif