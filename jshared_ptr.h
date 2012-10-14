#ifndef JSON_SHARED_PTR
#define JSON_SHARED_PTR


#if defined(JSON_BOOST_SHARED_PTR)
#include "boost/make_shared.hpp" 
namespace json{
	using namespace boost;
}
	
#elif defined(JSON_TR1_SHARED_PTR)
namespace json{
	using namespace std::tr1;
}
#else
namespace json{
	using namespace std;
}

}
#endif

#endif