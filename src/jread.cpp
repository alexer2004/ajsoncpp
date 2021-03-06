#include "jread.h"
#include <stdexcept>
#include <locale>
#include <iomanip>
#include "type_ptr.h"
#include <sstream>
#include <algorithm>
#include "jshared_ptr.h"
#ifdef JSON_FAST_STRING_TO_NUMBER
#include <stdio.h>
#endif


namespace json {

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
		PLUS = '+'

	};

	struct unicode_decoder
	{
		unsigned int count;
		void operator()(const char ch)
		{
			count *= 16;
			if (std::isdigit(ch, std::locale::classic()))
			{
				count += ch - '0';
			}
			else
			{
				if (ch >= 'a' || ch <= 'f')
				{
					count += ch - 'a' + 10;
				}
				else
				{
					if (ch >= 'A' || ch <= 'F')
					{
						count += ch - 'A' + 10;
					}
					else
						throw std::runtime_error("bad unicode sequence: unicode_decoder");
				}
			}
		}
	};

	struct char_finder
	{
		bool operator()(char ch)
		{
			return ch == 'e' || ch == 'E' || ch == '.';
		}
	};



	inline integer str_to_int(const string&);

	inline double str_to_double(const string&);

	inline unsigned int decode_unicode(const std::string& str);

	token_value get_token(std::istream&);


	string get_string(std::istream&);
	string get_escape_sequence(std::istream&);

	unsigned int get_unicode_code_point(std::istream&);

	string code_point_to_utf8(unsigned int);

	object_ptr get_object(std::istream&, token_value);

	object_ptr get_map_object(std::istream&);

	object_ptr get_array_object(std::istream&);

	object_ptr get_string_object(std::istream&);

	object_ptr get_number_object(std::istream&);

	object_ptr get_boolean_object(std::istream&);

	object_ptr get_empty_object(std::istream&);

	inline integer str_to_int(const string& s)
	{
		return static_cast<integer>(std::stoi(s));
	}

	inline double str_to_double(const string& s)
	{
		return std::stod(s);
	}






	std::istream& operator >> (std::istream& s, root& r)
	{
		token_value t = get_token(s);
		switch (t)
		{
		case OBJECT_MAP:
		case OBJECT_ARRAY:
			r.val = get_object(s, t);
			break;
		default:
			throw std::runtime_error("irregular token: operator>> wait for { or [");
		}

		char ch = 0;
		while (!s.get(ch) == false)
		{
			if (!std::isspace(ch, std::locale::classic()))
				throw std::runtime_error("misplaced data");
			ch = 0;
		}
		return s;
	}

	root read(const string&)
	{
		std::stringstream stream;
		stream.imbue(std::locale::classic());
		root r;
		stream >> r;
		return r;
	}

	object_ptr get_object(std::istream& s, token_value t)
	{
		switch (t)
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

	string get_string(std::istream& s)
	{
		string str;
		str.reserve(80);
		char ch = 0;
		if (!s.get(ch))
			throw std::runtime_error("bad stream: get_string");
		while (ch != '"')
		{
			switch (ch)
			{
			case '\\':
				str += get_escape_sequence(s);
				break;
			case '\f':
			case '\n':
			case '\r':
			case '\t':
			case '\b':
				throw std::runtime_error("bad white-space: get_string");
			default:
				str += ch;
			}
			if (!s.get(ch))
				throw std::runtime_error("bad stream: get_string");
		}

		return str;
	}

	string get_escape_sequence(std::istream& s)
	{
		string str;
		str.resize(1);
		char ch = 0;
		if (!s.get(ch))
			throw std::runtime_error("bad stream: get_escape_sequence");
		switch (ch)
		{
		case '"':
		case '\\':
		case '/':
			str[0] = ch;
			break;
		case 'u':
			str = code_point_to_utf8(get_unicode_code_point(s));
			break;
		case 'b':
			str[0] = '\b';
			break;
		case 'f':
			str[0] = '\f';
			break;
		case 'n':
			str += '\n';
			break;
		case 'r':
			str[0] = '\r';
			break;
		case 't':
			str[0] = '\t';
			break;
		default:
			throw std::runtime_error("bad escape sequence: get_escape_sequence");
		}
		return str;
	}

	inline unsigned int decode_unicode(const std::string& str)
	{
		return std::for_each(std::cbegin(str), std::cend(str), unicode_decoder()).count;
	}

	unsigned int get_unicode_code_point(std::istream& s)
	{
		string str;
		str.reserve(4);
		s >> std::setw(4) >> str >> std::setw(0);
		if (str.size() != 4)
		{
			throw std::runtime_error("bad unicode sequence: get_unicode_code_point expected 4 characters");
		}
		unsigned int code = decode_unicode(str);
		if (code >= 0xD800 && code <= 0xDBFF)
		{
			char ch = 0;
			if (!s.get(ch))
			{
				throw std::runtime_error("bad stream: get_unicode_code_point");
			}
			if (ch == '\\')
			{
				if (!s.get(ch))
				{
					throw std::runtime_error("bad stream: get_unicode_code_point");
				}
				if (ch == 'u')
				{
					s >> std::setw(4) >> str >> std::setw(0);
					if (str.size() != 4)
					{
						throw std::runtime_error("bad unicode sequence: get_unicode_code_point expected 4 characters");
					}
					code = 0x10000 + ((code & 0x3ff) << 10) + (decode_unicode(str) & 0x3ff);
				}
				else
				{
					throw std::runtime_error("bad unicode sequence: get_unicode_code_point expected 'u'");
				}
			}
			else
			{
				throw std::runtime_error("bad unicode sequence: get_unicode_code_point expected '\\'");
			}
		}
		return code;
	}

	string code_point_to_utf8(unsigned int code)
	{
		std::string str;
		if (code <= 0x7f)
		{
			str.resize(1);
			str[0] = static_cast<char>(code);
		}
		else if (code <= 0x7FF)
		{
			str.resize(2);
			str[0] = static_cast<char>(0xC0 | (0x1f & (code >> 6)));
			str[1] = static_cast<char>(0x80 | (0x3f & code));

		}
		else if (code <= 0xFFFF)
		{
			str.resize(3);
			str[0] = static_cast<char>(0xE0 | ((0xf & (code >> 12))));
			str[1] = static_cast<char>(0x80 | ((0x3f & (code >> 6))));
			str[2] = static_cast<char>(0x80 | (0x3f & code));
		}
		else if (code <= 0x10FFFF)
		{
			str.resize(4);
			str[0] = static_cast<char>(0xF0 | (0x7 & (code >> 18)));
			str[1] = static_cast<char>(0x80 | (0x3f & (code >> 12)));
			str[2] = static_cast<char>(0x80 | (0x3f & (code >> 6)));
			str[3] = static_cast<char>(0x80 | (0x3f & code));
		}
		return str;
	}


	object_ptr get_map_object(std::istream& s)
	{
		token_value t;
		ptr_map map;
		string str;
		char ch = 0;
		do
		{
			if (!s.get(ch))
			{
				throw std::runtime_error("bad stream : get_map_object");
			}
		} while (std::isspace(ch, std::locale::classic()));
		if (ch != RFP)
		{
			s.putback(ch);
			do
			{
				if (STRING == get_token(s))
				{
					str = get_string(s);
				}
				else
				{
					throw std::runtime_error("irregular token: get_map_object wait for quote");
				}
				if (COLON != get_token(s))
				{
					throw std::runtime_error("irregular token: get_map_object wait for colon");
				}
				map.insert(std::make_pair(str, get_object(s, get_token(s))));
				t = get_token(s);
			} while (t != RFP && t == COMMA);
			if (t != RFP)
			{
				throw std::runtime_error("irregular token: get_map_object wait for RFP");
			}
		}
		return make_shared<ptr_map_object>(map);
	}

	object_ptr get_array_object(std::istream& s)
	{
		token_value t;
		ptr_array arr;
		string str;
		char ch = 0;
		do
		{
			if (!s.get(ch))
			{
				throw std::runtime_error("bad stream : get_array_object");
			}
		} while (std::isspace(ch, std::locale::classic()));
		if (ch != RRP)
		{
			s.putback(ch);
			do
			{
				arr.push_back(get_object(s, get_token(s)));
				t = get_token(s);
			} while (t != RRP && t == COMMA);
			if (t != RRP)
			{
				throw std::runtime_error("irregular token: get_array_object wait for RRP");
			}
		}
		return make_shared<ptr_array_object>(arr);
	}

	object_ptr get_string_object(std::istream& s)
	{
		return make_shared<string_object>(get_string(s));
	}

	object_ptr get_number_object(std::istream& s)
	{
		string str;
		str.reserve(40);
		char ch = 0;
		if (!s.get(ch))
			throw std::runtime_error("bad stream: get_number_object");

		while (std::isdigit(ch, std::locale::classic()) || ch == 'e' || ch == 'E' || ch == '.' || ch == '-' || ch == '+')
		{
			str += ch;
			ch = 0;
			if (!s.get(ch))
				throw std::runtime_error("bad stream: get_number_object");
		}
		s.putback(ch);

		if (std::find_if(std::cbegin(str), std::cend(str), char_finder()) != std::cend(str))
		{
			if (str[0] == '0' &&  str.size() > 1 && str[1] != '.')
				throw std::runtime_error("number cannot have leading zeroes: get_number_object");
			return make_shared<double_object>(str_to_double(str));
		}
		if (str[0] == '0' &&  str.size() > 1)
			throw std::runtime_error("number cannot have leading zeroes: get_number_object");
		return make_shared<int_object>(str_to_int(str));
	}

	object_ptr get_boolean_object(std::istream& s)
	{
		bool b;
		string str;
		s >> std::setw(4) >> str >> std::setw(0);

		if (str == "true")
		{
			b = true;
		}
		else if (str == "fals")
		{
			char ch = 0;
			if (!s.get(ch))
				throw std::runtime_error("bad stream: get_number_object");
			if (ch == 'e')
			{
				b = false;
			}
			else
				throw std::runtime_error("error boolean value: get_boolean_object");
		}
		else
			throw std::runtime_error("error boolean value: get_boolean_object");
		return make_shared<bool_object>(b);
	}

	object_ptr get_empty_object(std::istream& s)
	{
		string str;
		s >> std::setw(4) >> str >> std::setw(0);
		if (str != "null")
		{
			throw std::runtime_error("irregular token: get_empty_object wait for null");
		}
		return make_shared<null_object>();
	}

	token_value get_token(std::istream& stream)
	{
		char ch = 0;
		token_value token = END;
		do
		{
			if (!stream.get(ch))
			{
				return token;
			}
		} while (std::isspace(ch, std::locale::classic()));
		switch (ch)
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
		case '8':case'9':case'.':case'-':
			token = NUMBER;
			stream.putback(ch);
			break;
		default:
			throw std::runtime_error("irregular token");
		}
		return token;
	}



}