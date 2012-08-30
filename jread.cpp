#include "jread.h"
#include <stdexcept>
#include <locale>
#include <iomanip>
#include "type_ptr.h"


namespace json{

	
enum token_value
{
	NAME,
	END,
	EMPTY,
	BOOLEAN,
	NUMBER,
	INTEGER,
	STRING,
	OBJECT_MAP,
	OBJECT_ARRAY,
	COLON = ':',
    COMMA = ',',
	LRP = '[',
	RRP = ']',
	LFP = '{',
	RFP = '}', 
	QUOTE = '"',
	MINUS = '-',
	PLUS  = '+'

};

token_value get_token(std::istream&); 


const string get_string(std::istream&);

object_ptr get_object(std::istream&, token_value);

object_ptr get_map_object(std::istream&);

object_ptr get_array_object(std::istream&);

object_ptr get_string_object(std::istream&);

object_ptr get_number_object(std::istream&);

object_ptr get_boolean_object(std::istream&);

object_ptr get_empty_object(std::istream&);







std::istream& operator>>(std::istream& s, root& r)
{
	token_value t = get_token(s);
	switch(t)
	{
	case OBJECT_MAP:
	case OBJECT_ARRAY:
		r.set_value(get_object(s, t));
		break;
	default:
		throw std::runtime_error("irregular token: operator>> wait for { or [");
	}	
	return s;
}

const root read(const string&)
{
	return root();
}

object_ptr get_object(std::istream& s, token_value t)
{
	switch(t)
	{
	case OBJECT_MAP:
		return get_map_object(s);
		break;
	case OBJECT_ARRAY:
		return get_array_object(s);
		break;
	case STRING:
		return get_string_object(s);
		break;
	case NUMBER:
		return get_number_object(s);
		break;
	case BOOLEAN:
		return get_boolean_object(s);
		break;
	case EMPTY:
		return get_empty_object(s);
		break;
	default:
		throw std::runtime_error("irregular token, get_object");
	}
}

const string get_string(std::istream& s)
{
	return string();
}


object_ptr get_map_object(std::istream& s)
{
	token_value t;
	ptr_map map;
	string str;
	char ch = 0;
	s.get(ch);
	if(ch != RFP)
	{
		s.putback(ch);
		do
		{		
			switch(get_token(s))
			{
			case STRING:
				str = get_string(s);
				break;
			default:
				throw std::runtime_error("irregular token: get_map_object wait for quote");
			}		
			switch(get_token(s))
			{
			case COLON:
				str = get_string(s);
				break;
			default:
				throw std::runtime_error("irregular token: get_map_object wait for colon");
			}
			map.insert(std::make_pair(str, get_object(s, get_token(s))));
			t = get_token(s);
		} while(t != RFP && t == COMMA);
		if(t != RFP)
		{
			throw std::runtime_error("irregular token: get_map_object wait for RFP");
		}
	}
	return std::make_shared<ptr_map_object>(map);
}

object_ptr get_array_object(std::istream& s)
{
	token_value t;
	ptr_array arr;
	string str;
	char ch = 0;
	s.get(ch);
	if(ch != RRP)
	{
		s.putback(ch);
		do
		{					
			arr.push_back(get_object(s, get_token(s)));
			t = get_token(s);
		} while(t != RRP && t == COMMA);
		if(t != RRP)
		{
			throw std::runtime_error("irregular token: get_array_object wait for RRP");
		}
	}
	return std::make_shared<ptr_array_object>(arr);
}

object_ptr get_string_object(std::istream& s)
{
	return std::make_shared<string_object>(get_string(s));
}

object_ptr get_number_object(std::istream& s)
{
	return std::make_shared<int_object>(1);
}

object_ptr get_boolean_object(std::istream& s)
{
	bool b;
	s >> std::boolalpha >> b;
	return std::make_shared<bool_object>(b);
}

object_ptr get_empty_object(std::istream& s)
{
	string str;
	s >> std::setw(4) >> str;
	if(str != "null")
	{	
		throw std::runtime_error("irregular token: get_empty_object wait for null");
	}
	return std::make_shared<null_object>();
}

token_value get_token(std::istream& stream)
{
	char ch = 0;
    token_value token = END;
	do
	{
		if(!stream.get(ch))
		{
			return token;
		}
	} while(std::isspace(ch, std::locale::classic()));
	switch(ch)
	{
	case 't':
	case 'f':
		token = BOOLEAN;
		stream.putback(ch);
		break;
	case 'n':
		token = EMPTY;
		stream.putback(ch);
        break;
	case '{':
		token = OBJECT_MAP;
        break;
	case '[':
		token = OBJECT_ARRAY;
        break;
	case ':':
	case ',':
	case '}':
	case ']':
		token = token_value(ch);
		break;
	case '"':
		token = STRING;
		break;
	case '0':case'1':case '2':case'3':
	case '4':case'5':case '6':case'7':
	case '8':case'9':case'.':
		token = NUMBER;
		stream.putback(ch);
		break;
	default:
		throw std::runtime_error("irregular token");
	}
	return token;
}



}