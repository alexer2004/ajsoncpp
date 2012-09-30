#include "jwrite.h"
#include "jwrite_visitor.h"
#include <sstream>

namespace json{


std::ostream& operator<<(std::ostream& s, root& r)
{
	r.value()->accept(jwrite_visitor(s));
	return s;
}

const string read(root& r)
{
	std::stringstream s;
	s << r;
	return s.str();
}



}