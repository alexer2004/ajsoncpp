#include "jwrite.h"
#include "jwrite_visitor.h"
#include <sstream>

namespace json{


std::ostream& operator<<(std::ostream& s, root& r)
{
	r.accept(jwrite_visitor(s));
	return s;
}

string write(root& r)
{
	std::stringstream s;
	s << r;
	return s.str();
}



}