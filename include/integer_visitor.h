#ifndef JSON_INTEGER_VISITOR_H
#define JSON_INTEGER_VISITOR_H

#include "object_visitor.h"
#include <stdexcept>
#include "value_object.h"


namespace json{

	class integer_visitor : public object_visitor
	{
	public:
		typedef int& value_type;
		integer_visitor()
			:pval(0)
		{
		}
		void visit(null_object&)
		{
			throw std::runtime_error("integer expected, not null");
		}
		void visit(bool_object&)
		{
			throw std::runtime_error("integer expected, not boolean");
		}
		void visit(string_object&)
		{
			throw std::runtime_error("integer expected, not string");	
		}
		void visit(int_object& v)
		{
			pval = &v.value();
		}
		void visit(double_object&)
		{
			throw std::runtime_error("integer expected, not double");
		}
		void visit(ptr_map_object&)
		{
			throw std::runtime_error("integer expected, not map");
		}
		void visit(ptr_array_object&)
		{
			throw std::runtime_error("integer expected, not array");
		}
		int &value()
		{
			return *pval;
		}
		const int &value()const
		{
			return *pval;
		}
		~integer_visitor(){;}
	private:
		int* pval;
	};
}
#endif