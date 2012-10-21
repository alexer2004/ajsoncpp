#include "object_visitor.h"
#include "jread.h"
#include "jwrite.h"
#include <fstream>
#include <iostream>

	
int main(int argc, char* argv[])
{
	try
	{
		json::root r;
		r.create_map();
		json::map_getter::map_getter_ptr map = r.map();
		map->insert("integer", 10);
		map->insert("double", 10.0);
		map->insert_array("array");
		json::array_getter::array_getter_ptr array = map->array("array");
		array->push_back(1);
		array->push_back(2.0);
		array->push_back(json::string("three"));
		std::cout << r;
	}
	catch(const std::exception& e)
	{
		std::cout  << e.what() << std::endl;
	}
	return 0;
}