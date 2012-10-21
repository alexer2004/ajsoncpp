ajsoncpp version 1.0
========================

JSON (JavaScript Object Notation) is a lightweight data-interchange format(http://www.json.org/).
It can represent and manipulate integer values, real numbers, strings, arrays of values and collections of key/value pairs.
You can use it to serialize your program's state. JSON is a standard, so it's very good for data exchangig between different applications.

ajsoncpp (another JSON cpp library) is a API to work with JSON values, it is useful to control serialization of the data.

Parsing JSON
=========================


This is JSON data from wikipedia page(http://en.wikipedia.org/wiki/JSON)
'''javascript
{
    "firstName": "John",
    "lastName": "Smith",
    "age": 25,
    "address": {
        "streetAddress": "21 2nd Street",
        "city": "New York",
        "state": "NY",
        "postalCode": "10021"
    },
    "phoneNumber": [
        {
            "type": "home",
            "number": "212 555-1234"
        },
        {
            "type": "fax",
            "number": "646 555-4567"
        }
    ]
}
'''

To parse such data format with jsoncpp you build object tree:

'''c
    json::root root = json::read(json_string);
'''
Now you can get value from tree. 

'''c
	int age = root.map()->integer("age");
'''

You can change value of tree's element.

'''c
	root.map()->str("firstName") = "Alexandr";
'''

Delete "phononumber". We have no phones.:)

'''c
	root.map()->erase("phoneNumber");
'''

If we try to retrieve data's type, which doesn't exist, ajsoncpp throw exception.
For example:
'''c
	json::string age = root.map()->string("age"); //throw exception std::runtime_error	
'''

When we escape from scope, root delete all objects in tree.

Parsing streams
=================

You can parse files with JSON data to receive whole objects tree.
'''c
        std::fstream istream("sample.json");
	json::root root; 
	istream >> root;
	//do something
	std::stream ostream("out.json");
	ostream << root; 

'''


Filtering JSON data
====================

If you need for only special kind of JSON data, you may create filter and 
traverse objects tree.
For example i want to get whole phone numbers.


'''c

class phonenumber_visitor : public object_visitor
{
public:
	void visit(null_object& v)
	{
	}
	
	void visit(bool_object& v)
	{
	}
	void visit(string_object& v)
	{
		value.push_back(v.value());	
	}
	void visit(int_object& v);
	{
	
	}
	void visit(double_object& v)
	{
	}
	void visit(ptr_map_object& v)
	{
		ptr_map_object::value_type::iterator it = v.value().find("phononumber");
		if(it != v.value().end())
		{
			it->second->accept(*this);
		}

		it = v.value().find("number");
		if(it != v.value().end())
		{
			it->second->accept(*this);
		}

	}	
	void visit(ptr_array_object& v)
	{
		for(ptr_array_object::value_type::iterator it = v.value().begin(); it != v.value().end(); ++it)
		{
			(it)->accept(*this);
		}
		
	}
	~phonenumber_visitor(){;}
	typedef std::vector<string> strings;
	strings value;
};

	json::root root = json::read(json_string);
	phonenumber_visitor visitor;
	root.accept(visitor);
	//do somthing with visitor.value -- whole phones



'''

Creating JSON data
====================

Create objects tree in code.

'''c
	json::root r;
	r.create_map();
	json::map_getter::map_getter_ptr map = r.map();
	map->insert("integer", 10);
	map->insert("double", 10.0);
	map->insert_array("array");
	json::array_getter::array_getter_ptr array = map->array("array");
	array->push_back(1);
	array->push_back(2.0);
	array->push_back(json::string("three"));
	std::cout << r;
'''
I create map object and insert in it int, double and array data.
I fill array with int, double and string data. At the end i get such JSON data:

'''javascript
	{"array":[1,2,"three"],"double":10,"integer":12}
''''

ajsoncpp data structures
=========================

'''c

class object_visitor;

class object
{
public:
	virtual void accept(object_visitor&)=0;
	virtual ~object()=0{;}

};

template<class T> class value_object : public object
{
public:
	typedef T value_type;
	value_object()
	{
	}
	explicit value_object(const value_type& v)
		:val(v)
	{
	}

	value_object(const value_object<T>& v)
		:val(v.val)
	{
	} 
	
	value_object<T>& operator=(const value_object<T>& v)
	{
		if(this != &v)
		{
			val = v.val;
		}
		return *this;
	}
	~value_object(){;}	
	value_type& value()
	{
		return const_cast<value_type&>(static_cast<const value_object&>(*this).value());
	}

	const value_type& value()const
	{
		return val;
	}
	void set_value(const value_type& v)
	{
		val = v;
	}

	void accept(object_visitor& v)
	{
		v.visit(*this);		
	}

private:
	value_type val;

};

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


'''





