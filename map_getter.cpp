#include "map_getter.h"
#include "map_visitor.h"
#include "array_getter.h"
#include "array_visitor.h"

namespace json{

	map_getter::map_getter_ptr map_getter::map(const string& key)
	{
		return static_cast<const map_getter&>(*this).map(key);
	}

	const map_getter::map_getter_ptr map_getter::map(const string& key)const
	{
		return make_shared<map_getter>(find(map_visitor(), key));
	}

	map_getter::array_getter_ptr map_getter::array(const string& key)
	{
		return static_cast<const map_getter&>(*this).array(key);
	}

	const map_getter::array_getter_ptr map_getter::array(const string& key)const
	{
		return make_shared<array_getter>(find(array_visitor(), key));
	}
}