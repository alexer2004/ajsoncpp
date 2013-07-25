#include "array_getter.h"
#include "array_visitor.h"
#include "map_getter.h"
#include "map_visitor.h"

namespace json{

	array_getter::map_getter_ptr array_getter::map(size_t i)
	{
		return static_cast<const array_getter&>(*this).map(i);
	}

	const array_getter::map_getter_ptr array_getter::map(size_t i)const
	{
		return make_shared<map_getter>(at(map_visitor(), i));
	}

	array_getter::array_getter_ptr array_getter::array(size_t i)
	{
		return static_cast<const array_getter&>(*this).array(i);
	}

	const array_getter::array_getter_ptr array_getter::array(size_t i)const
	{
		return make_shared<array_getter>(at(array_visitor(), i));
	}


}