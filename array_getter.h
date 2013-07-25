#ifndef JSON_ARRAY_GETTER_H
#define JSON_ARRAY_GETTER_H

#include "object_visitor.h"
#include "integer_visitor.h"
#include "double_visitor.h"
#include "string_visitor.h"
#include "bool_visitor.h"
#include "null_visitor.h"
#include "jshared_ptr.h"

namespace json{

	class map_getter;

	class array_getter
	{
		template<class V> typename V::value_type at(V& visitor, size_t i)const
		{
#ifdef JSON_OUT_OF_RANGE
			pval->at(i)->accept(visitor);
#else
			pval->operator[](i)->accept(visitor);
#endif
			return visitor.value();
		}
	public:
#if defined(JSON_BOOST_SHARED_PTR)
		typedef boost::shared_ptr<map_getter> map_getter_ptr;
		typedef boost::shared_ptr<array_getter> array_getter_ptr;
#elif defined(JSON_TR1_SHARED_PTR) 
		typedef std::tr1::shared_ptr<map_getter> map_getter_ptr;
		typedef std::tr1::shared_ptr<array_getter> array_getter_ptr;
#else
		typedef std::shared_ptr<map_getter> map_getter_ptr;
		typedef std::shared_ptr<array_getter> array_getter_ptr;
#endif
		array_getter()
			:pval(0)
		{
		}
		array_getter(ptr_array *p)
			:pval(p)
		{
		}

		array_getter(const array_getter& a)
			:pval(a.pval)
		{
		}

		array_getter& operator=(const array_getter& a)
		{
			pval = a.pval;
			return *this;
		}

		const int& integer(size_t i)const
		{
			return at(integer_visitor(), i);
		}

		int& integer(size_t i)
		{
			return const_cast<int&>(static_cast<const array_getter&>(*this).integer(i));
		}

		const double& real(size_t i)const
		{
			return at(double_visitor(), i);
		}

		double& real(size_t i)
		{
			return const_cast<double&>(static_cast<const array_getter&>(*this).real(i));
		}
		const string& str(size_t i)const
		{
			return at(string_visitor(), i);
		}

		string& str(size_t i)
		{
			return const_cast<string&>(static_cast<const array_getter&>(*this).str(i));
		}

		const bool& boolean(size_t i)const
		{
			return at(bool_visitor(), i);
		}

		bool& boolean(size_t i)
		{
			return const_cast<bool&>(static_cast<const array_getter&>(*this).boolean(i));
		}
		const bool is_null(size_t i)const
		{
			return at(null_visitor(), i);
		}

		bool is_null(size_t i)
		{
			return const_cast<bool&>(static_cast<const array_getter&>(*this).boolean(i));
		}

		map_getter_ptr map(size_t);
		const map_getter_ptr map(size_t)const;

		array_getter_ptr array(size_t);
		const array_getter_ptr array(size_t)const;

		template<typename V> void push_back(V value)
		{
			pval->push_back(make_shared<value_object<V> >(std::move(value)));
		}
		void push_back(null_object)
		{
			pval->push_back(make_shared<null_object>());
		}
		void push_back_array()
		{
			pval->push_back(make_shared<ptr_array_object>());
		}
		void push_back_map()
		{
			pval->push_back(make_shared<ptr_map_object>());
		}
		void erase(size_t i)
		{
			pval->erase(pval->begin() + i);
		}

		void clear()
		{
			pval->clear();
		}

		size_t size()const
		{
			return pval->size();
		}

	private:
		ptr_array *pval;
	};
}
#endif