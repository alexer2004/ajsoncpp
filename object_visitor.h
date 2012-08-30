#ifndef JSON_OBJECT_VISITOR_H
#define JSON_OBJECT_VISITOR_H

#include "null_object.h"
#include <string>
#include <deque>

#ifdef BOOST_SHARED_PTR
	#include "boost/shared_ptr.h"
	namespace json{
		typedef boost::shared_ptr<object> object_ptr;
	}
#else
	#include <memory>
	namespace json{
		typedef std::tr1::shared_ptr<object> object_ptr;
	}

#endif


#ifdef BOOST_UNODERED_MAP
        #include "boost/unordered_map.hpp"
	namespace json{
		typedef std::string string;			    //utf-8
		typedef boost::unordered_map<string, object_ptr> ptr_map;
	}
#else
	#include <unordered_map>
	namespace json{
		typedef std::string string;				//utf-8
		typedef std::tr1::unordered_map<string, object_ptr> ptr_map;
	}
#endif



namespace json{

template<class T> class value_object;
typedef value_object<bool> bool_object;
typedef value_object<string> string_object;
typedef value_object<int> int_object;
typedef value_object<double> double_object;
typedef value_object<ptr_map> ptr_map_object;
typedef std::deque<object_ptr> ptr_array;
typedef value_object<ptr_array> ptr_array_object;

class object_visitor
{
public:
	virtual void visit(null_object&)=0;
	virtual void visit(bool_object&)=0;
	virtual void visit(string_object&)=0;
	virtual void visit(int_object&)=0;
	virtual void visit(double_object&)=0;
	virtual void visit(ptr_map_object&)=0;
	virtual void visit(ptr_array_object&)=0;
	virtual ~object_visitor()=0{;}

};




}





#endif