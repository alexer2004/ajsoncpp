// json.cpp: определяет точку входа для консольного приложения.
//
#include "object_visitor.h"
#include "jread.h"
#include <fstream>


int main(int argc, char* argv[])
{
	json::root root;
	std::fstream file1("pass1.json", std::ios_base::in);
	file1 >> root;
	return 0;
}

