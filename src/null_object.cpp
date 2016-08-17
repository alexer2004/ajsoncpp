#include "null_object.h"
#include "object_visitor.h"
#include "value_object.h"

namespace json{

	void null_object::accept(object_visitor& v)
	{
		v.visit(*this);
	}
}