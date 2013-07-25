#ifndef JSON_NULL_OBJECT_H
#define JSON_NULL_OBJECT_H

#include "object.h"


namespace json{


	class null_object : public object
	{
	public:
		void accept(object_visitor&);
		~null_object(){;}
	};
}
#endif