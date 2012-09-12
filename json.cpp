// json.cpp: определяет точку входа для консольного приложения.
//
#include "object_visitor.h"
#include "jread.h"
#include <fstream>
#include <iostream>


int main(int argc, char* argv[])
{
	if(argc == 2)
	{
		try
		{
			json::root root;
			std::fstream file1(argv[1], std::ios_base::in);
			file1 >> root;
			std::cout  << "Ok!" << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout  << e.what() << std::endl;
		}

	}
	return 0;
}

