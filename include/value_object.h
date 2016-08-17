#ifndef JSON_VALUE_OBJECT_H
#define JSON_VALUE_OBJECT_H

#include "object.h"


namespace json{


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

#ifdef JSON_TR1_SHARED_PTR
		value_object<T>& operator=(const value_object<T>& v)
		{
			if(this != &v)
			{
				val = v.val;
			}
			return *this;
		}
#else 
		value_object(value_object<T>&& o)
			:val(move(o.val))
		{

		}

		value_object(value_type&& v)
			:val(move(v))
		{

		}

		value_object<T>& operator=(const value_object<T> v)
		{
			v.swap(*this);		
			return *this;
		}


		void swap(value_object<T>& o)
		{
			swap(val, o.val);
		}

#endif // !JSON_TR1_SHARED_PTR



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

}

#endif