#ifndef JSON_ROOT_H
#define JSON_ROOT_H

#include "object_visitor.h"
#include <istream>
#include "map_getter.h"

#include "jshared_ptr.h"
#include "map_visitor.h"

#include "array_getter.h"
#include "array_visitor.h"



namespace json{


class root
{
public:
	root()
	{
	}
	root(object_ptr p)
		:val(p)
	{
	}
	root(const root& r)
		:val(r.val)
	{
	}

	root& operator=(const root& r)
	{
		val = r.val;
	}
	
	template<typename V> void accept(V& v)
	{
		val->accept(v);
	}

	void create_map()
	{
		val = make_shared<ptr_map_object>();
	}

	void create_array()
	{
		val = make_shared<ptr_array_object>();
	}

	map_getter map()
	{
		map_visitor visitor;
		val->accept(visitor);
		return visitor.value();
	}

	const map_getter map()const
	{
		return static_cast<const root&>(*this).map();
	}

	array_getter array()
	{
		array_visitor visitor;
		val->accept(visitor);
		return visitor.value();
	}

	const array_getter array()const
	{
		return static_cast<const root&>(*this).array();
	}
	

	friend std::istream& operator>>(std::istream& s, root& r);
private:
	object_ptr val;
};





}


#endif