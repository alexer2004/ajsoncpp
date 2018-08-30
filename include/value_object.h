#ifndef JSON_VALUE_OBJECT_H
#define JSON_VALUE_OBJECT_H

#include "object.h"


namespace json{


	template<class T> class value_object final : public object 
	{
	public:
		typedef T value_type;
		value_object() = default;
		
		explicit value_object(const value_type& v)
			:val(v)
		{
		}
		value_object(value_type&& v)
			:val(move(v))
		{

		}

		value_object(const value_object<T>& v) = default;
		value_object(value_object<T>&& o) = default;
		value_object<T>& operator=(const value_object<T>& v) = default;
		value_object<T>& operator=(value_object<T>&& v) = default;
		
		~value_object() = default;
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

}

#endif