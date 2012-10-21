#include "object_visitor.h"
#include "jread.h"
#include <fstream>
#include <iostream>
#include <vector>

namespace json{


class phonenumber_visitor : public object_visitor
{
public:
	void visit(null_object& v)
	{
	}
	
	void visit(bool_object& v)
	{
	}
	void visit(string_object& v)
	{
		value.push_back(v.value());	
	}
	void visit(int_object& v)
	{
	
	}
	void visit(double_object& v)
	{
	}
	void visit(ptr_map_object& v)
	{
		ptr_map_object::value_type::iterator it = v.value().find("phononumber");
		if(it != v.value().end())
		{
			it->second->accept(*this);
		}

		it = v.value().find("number");
		if(it != v.value().end())
		{
			it->second->accept(*this);
		}

	}	
	void visit(ptr_array_object& v)
	{
		for(ptr_array_object::value_type::iterator it = v.value().begin(); it != v.value().end(); ++it)
		{
			(*it)->accept(*this);
		}
		
	}
	~phonenumber_visitor(){;}
	typedef std::vector<string> strings;
	strings value;
};

}
	
int main(int argc, char* argv[])
{	
	try
	{
		json::root root;
		std::fstream file("sample.json", std::ios_base::in);
		json::phonenumber_visitor visitor;
		root.accept(visitor);
		json::phonenumber_visitor::strings value = visitor.value;		

	}
	catch(const std::exception& e)
	{
		std::cout  << e.what() << std::endl;
	}
	return 0;
}