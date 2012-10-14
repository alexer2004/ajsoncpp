#ifndef JSON_STRING_VISITOR_H
#define JSON_STRING_VISITOR_H

#include "object_visitor.h"
#include <stdexcept>


namespace json{

class string_visitor : public object_visitor
{
public:
	typedef string& value_type; 
	string_visitor()
		:pval(0)
	{
	}
	void visit(null_object&)
	{
		throw std::runtime_error("string expected, not null");
	}
	void visit(bool_object&)
	{
		throw std::runtime_error("string expected, not boolean");
	}
	void visit(string_object& v)
	{
		pval = &v.value();	
	}
	void visit(int_object& v)
	{
		throw std::runtime_error("string expected, not int");
	}
	void visit(double_object& v)
	{
		throw std::runtime_error("string expected, not map");	
	}
	void visit(ptr_map_object&)
	{
		throw std::runtime_error("string expected, not map");
	}
	void visit(ptr_array_object&)
	{
		throw std::runtime_error("string expected, not array");
	}
	string &value()
	{
		return *pval;
	}
	const string &value()const
	{
		return *pval;
	}
	~string_visitor(){;}
private:
	string* pval;

};




}





#endif