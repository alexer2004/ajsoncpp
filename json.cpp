// json.cpp: ���������� ����� ����� ��� ����������� ����������.
//
#include "object_visitor.h"
#include "jread.h"
#include <fstream>


int main(int argc, char* argv[])
{
	std::fstream file("sample.json", std::ios_base::in);
	json::root root;
	file >> root;
	return 0;
}

