#ifndef JSON_WRITE_VISITOR_H
#define JSON_WRITE_VISITOR_H

#include "object_visitor.h"
#include "root.h"
#include <ostream>
#include <functional>
#include <locale>


#if defined(JSON_BOOST_REF)
#include "boost/ref.hpp"
namespace json{
	typedef boost::reference_wrapper<std::ostream> ref_ostream;
}
#elif defined(JSON_TR1_REF)
#include <functional>
namespace json{
	typedef std::tr1::reference_wrapper<std::ostream> ref_ostream;
}
#else
#include <functional>
namespace json{
	typedef std::reference_wrapper<std::ostream> ref_ostream;
}
#endif



namespace json{


	class jwrite_visitor : public object_visitor
	{
	public:
		jwrite_visitor(std::ostream& s)
			:stream(s)
		{
			s.imbue(std::locale::classic());
		}

		void visit(null_object&);
		void visit(bool_object&);
		void visit(string_object&);
		void visit(int_object&);
		void visit(double_object&);
		void visit(ptr_map_object&);
		void visit(ptr_array_object&);
		~jwrite_visitor(){;}
	private:
		ref_ostream stream;
	};
}

#endif