#ifndef JSON_DOUBLE_VISITOR_H
#define JSON_DOUBLE_VISITOR_H

#include "object_visitor.h"
#include <stdexcept>


namespace json{

class double_visitor : public object_visitor
{
public:
	typedef double& value_type;
	double_visitor()
		:pval(0)
	{
	}
	void visit(null_object&)
	{
		throw std::runtime_error("double expected, not null");
	}
	void visit(bool_object&)
	{
		throw std::runtime_error("double expected, not boolean");
	}
	void visit(string_object&)
	{
		throw std::runtime_error("double expected, not string");	
	}
	void visit(int_object& v)
	{
		throw std::runtime_error("double expected, not int");
	}
	void visit(double_object& v)
	{
		pval = &v.value();	
	}
	void visit(ptr_map_object&)
	{
		throw std::runtime_error("double expected, not map");
	}
	void visit(ptr_array_object&)
	{
		throw std::runtime_error("double expected, not array");
	}
	double &value()
	{
		return *pval;
	}
	const double &value()const
	{
		return *pval;
	}
	~double_visitor(){;}
private:
	double* pval;

};






}





#endif