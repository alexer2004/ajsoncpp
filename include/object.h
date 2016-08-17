#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H


namespace json{

	class object_visitor;

	class object
	{
	public:
		virtual void accept(object_visitor&)=0;
		virtual ~object()=0;

	};

	inline object::~object()
	{
	}
}
#endif