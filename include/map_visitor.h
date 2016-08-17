#ifndef JSON_MAP_VISITOR_H
#define JSON_MAP_VISITOR_H

#include "object_visitor.h"
#include <stdexcept>
#include "map_getter.h"
#include "value_object.h"



namespace json{

	class map_visitor : public object_visitor
	{
	public:
		typedef map_getter value_type;
		map_visitor()
			:pval(0)
		{
		}
		void visit(bool_object&)
		{
			throw std::runtime_error("map expected, not bool");
		}
		void visit(null_object& v)
		{
			throw std::runtime_error("map expected, not null");	
		}
		void visit(string_object&)
		{
			throw std::runtime_error("map expected, not string");	
		}
		void visit(int_object& v)
		{
			throw std::runtime_error("map expected, not integer");
		}
		void visit(double_object&)
		{
			throw std::runtime_error("map expected, not double");
		}
		void visit(ptr_map_object& v)
		{
			pval = &v.value();	
		}
		void visit(ptr_array_object&)
		{
			throw std::runtime_error("map expected, not array");
		}
		map_getter value()
		{
			return map_getter(pval);
		}
		const map_getter value()const
		{
			return map_getter(pval);
		}
		~map_visitor(){;}
	private:
		ptr_map *pval;
	};
}
#endif