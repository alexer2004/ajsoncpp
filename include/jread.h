#ifndef JSON_JREAD_H
#define JSON_JREAD_H

#include "object_visitor.h"
#include "value_object.h"
#include "root.h"
#include <istream>

namespace json{

std::istream& operator>>(std::istream&, root&);

root read(const string&);

}
#endif