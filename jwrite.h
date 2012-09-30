#ifndef JSON_JWRITE_H
#define JSON_JWRITE_H

#include "object_visitor.h"
#include "value_object.h"
#include "root.h"
#include <ostream>

namespace json{



std::ostream& operator<<(std::ostream&, root&);

const string read(root&);

}




#endif