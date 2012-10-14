// json.cpp: определяет точку входа для консольного приложения.
//
#include "object_visitor.h"
#include "jread.h"
#include "jwrite.h"
#include <fstream>
#include <iostream>

	
int main(int argc, char* argv[])
{
	if(argc == 2)
	{
		try
		{
			/*json::root root;
			std::fstream file1(argv[1], std::ios_base::in);
			file1 >> root;
			std::cout << "Ok!" << std::endl;
			std::cout << root;*/
		}
		catch(const std::exception& e)
		{
			std::cout  << e.what() << std::endl;
		}

	}
	json::root r;
	r.create_map();
	r.map().insert("integer", 10);
	r.map().insert("double", 10.0);
	r.map().integer("integer") = 12;
	r.map().insert("array", json::ptr_array());
	r.map().array("array")->push_back(1);
	r.map().array("array")->push_back(2.0);
	r.map().array("array")->push_back(json::string("three"));
	std::cout << r;
	return 0;
}

