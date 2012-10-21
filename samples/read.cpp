#include "object_visitor.h"
#include "jread.h"
#include "jwrite.h"
#include <fstream>
#include <iostream>

	
int main(int argc, char* argv[])
{
	
	try
	{
		json::root root;
		std::fstream file("sample.json", std::ios_base::in);
		file >> root;
		int age = root.map()->integer("age");
		root.map()->str("firstName") = "Alexandr";
		root.map()->erase("phoneNumber");
		std::cout << root;

	}
	catch(const std::exception& e)
	{
		std::cout  << e.what() << std::endl;
	}
	return 0;
}