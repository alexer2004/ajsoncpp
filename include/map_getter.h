#ifndef JSON_MAP_GETTER_H
#define JSON_MAP_GETTER_H


#include "type_ptr.h"
#include "integer_visitor.h"
#include "double_visitor.h"
#include "string_visitor.h"
#include "bool_visitor.h"
#include "null_visitor.h"
#include "jshared_ptr.h"
#include <memory>
#include <vector>
#include <algorithm>

namespace json{

	class array_getter;

	class map_getter
	{
		struct inserter
		{
			typedef std::vector<string> keys;
			void operator()(const std::pair<const string, object_ptr>& p)
			{
				val.push_back(p.first);
			}
			keys val;
		};
		template<class V> typename V::value_type find(V& visitor, const string& key)const
		{
			pval->at(key)->accept(visitor);
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
		typedef std::vector<string> keys;
		map_getter()
		{
		}
		map_getter(ptr_map * v)
			:pval(v)
		{
		}		
		map_getter(const map_getter& m)
			:pval(m.pval)
		{
		}
		map_getter& operator=(const map_getter& m)
		{
			pval = m.pval;
			return *this;
		}
		const int& integer(const string& key)const
		{
			return find(integer_visitor(), key);
		}

		int& integer(const string& key)
		{
			return const_cast<int&>(static_cast<const map_getter&>(*this).integer(key));
		}

		const double& real(const string& key)const
		{
			return find(double_visitor(), key);
		}

		double& real(const string& key)
		{
			return const_cast<double&>(static_cast<const map_getter&>(*this).real(key));
		}
		const string& str(const string& key)const
		{
			return find(string_visitor(), key);
		}

		string& str(const string& key)
		{
			return const_cast<string&>(static_cast<const map_getter&>(*this).str(key));
		}

		const bool& boolean(const string& key)const
		{
			return find(bool_visitor(), key);
		}

		bool& boolean(const string& key)
		{
			return const_cast<bool&>(static_cast<const map_getter&>(*this).boolean(key));
		}
		const bool is_null(const string& key)const
		{
			return find(null_visitor(), key);
		}

		bool is_null(const string& key)
		{
			return const_cast<bool&>(static_cast<const map_getter&>(*this).boolean(key));
		}

		map_getter_ptr map(const string&);
		const map_getter_ptr map(const string&)const;

		array_getter_ptr array(const string&);
		const array_getter_ptr array(const string&)const;



		template<typename V> bool insert(const string& key, V value)
		{
			return pval->insert(std::make_pair(key, make_shared<value_object<V> >(std::move(value)))).second;
		}
		bool insert(const string& key, null_object)
		{
			return pval->insert(std::make_pair(key, make_shared<null_object>())).second;
		}

		bool insert_array(const string& key)
		{
			return pval->insert(std::make_pair(key, make_shared<ptr_array_object>())).second;
		}

		bool insert_map(const string& key)
		{
			return pval->insert(std::make_pair(key, make_shared<ptr_map_object>())).second;
		}

		size_t erase(const string& key)
		{
			return pval->erase(key);
		}

		void clear()
		{
			pval->clear();
		}

		size_t size()const
		{
			return pval->size();
		}

		keys get_keys()const
		{
			return std::for_each(cbegin(*pval), std::cend(*pval), inserter()).val;
		}

	private:
		ptr_map *pval;
	};








} 





#endif