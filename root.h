#ifndef JSON_ROOT_H
#define JSON_ROOT_H

#include "object_visitor.h"

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
	
	const object_ptr& value()const
	{
		return val;
	}

	void set_value(const object_ptr& v)
	{
		val = v;
	}
	
private:
	object_ptr val;
};





}


#endif