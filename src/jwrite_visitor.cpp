#include "jwrite_visitor.h"
#include "value_object.h"
#include <iomanip>



namespace json {

	size_t length(const string&, size_t);

	size_t write_symbol(std::ostream&, const string&, size_t);

	unsigned int convert(char);

	void write_string(std::ostream&, const string&);

	inline void write_string(std::ostream& stream, const string& s)
	{
		stream << '\"';
		for (size_t i = 0; i < s.size();)
		{
			switch (s[i])
			{
			case '\"':
				stream << "\\\"";
				break;
			case '\\':
				stream << "\\\\";
				break;
			case '/':
				stream << "\\/";
				break;
			case '\b':
				stream << "\\b";
				break;
			case '\f':
				stream << "\\f";
				break;
			case '\n':
				stream << "\\n";
				break;
			case '\r':
				stream << "\\r";
				break;
			case '\t':
				stream << "\\t";
				break;
				/*case '"':
				stream << "\\u0022";
				break;*/
			default:
				i += write_symbol(stream, s, i);
				continue;
			}
			++i;
		}
		stream << '\"';

	}



	inline unsigned int convert(char c)
	{
		return static_cast<unsigned int>(c);
	}


	inline size_t length(const string& s, size_t i)
	{
		unsigned char ch = convert(s[i]);
		if (ch < 128)
		{
			return 1;
		}
		else if ((ch >> 5) == 6)
		{
			return 2;
		}
		else if ((ch >> 4) == 14)
		{
			return 3;
		}
		else if ((ch >> 3) == 30)
		{
			return 4;
		}
		else
			return 0;

	}

	inline size_t write_symbol(std::ostream& stream, const string& s, size_t i)
	{
		unsigned int cp = convert(s[i]);
		size_t n = length(s, i);
		switch (n)
		{
		case 1:
			break;
		case 2:
			cp = ((cp << 6) & 0x7ff) + (convert(s[i + 1]) & 0x3f);
			break;
		case 3:
			cp = ((cp << 12) & 0xffff) + ((convert(s[i + 1]) << 6) & 0xfff) + (convert(s[i + 2]) & 0x3f);
			break;
		case 4:
			cp = ((cp << 18) & 0x1fffff) + ((convert(s[i + 1]) << 12) & 0x3ffff)
				+ ((convert(s[i + 2]) << 6) & 0xfff) + (convert(s[i + 3]) & 0x3f);
			break;
		}

		if (cp < 128)
		{
			stream << static_cast<char>(cp);
		}
		else if (cp > 0xffff)
		{
			unsigned int c = (cp >> 10) + (0xd800 - (0x10000 >> 10));
			stream << "\\u" << std::hex << std::setfill('0') << std::setw(4) << c << std::setfill(' ') << std::setw(0);
			c = (cp & 0x3ff) + 0xdc00;
			stream << "\\u" << std::hex << std::setfill('0') << std::setw(4) << c;
		}
		else
		{
			stream << "\\u" << std::hex << std::setfill('0') << std::setw(4) << cp;
		}
		stream << std::setfill(' ') << std::setw(0) << std::dec;
		return n;
	}

	void jwrite_visitor::visit(null_object& v)
	{
		stream.get() << "null";
	}

	void jwrite_visitor::visit(bool_object& v)
	{
		stream.get() << std::boolalpha << v.value() << std::noboolalpha;
	}

	void jwrite_visitor::visit(string_object& v)
	{
		write_string(stream.get(), v.value());
	}

	void jwrite_visitor::visit(int_object& v)
	{
		stream.get() << v.value();
	}

	void jwrite_visitor::visit(double_object& v)
	{
		stream.get() << v.value();
	}

	void jwrite_visitor::visit(ptr_map_object& v)
	{
		stream.get() << '{';
		for (auto it = cbegin(v.value()); it != cend(v.value()); ++it)
		{
			write_string(stream.get(), it->first);
			string str = it->first;
			stream.get() << ':';
			it->second->accept(*this);
			auto i = it;
			++i;
			if (i != cend(v.value()))
			{
				stream.get() << ',';
			}
		}
		stream.get() << '}';
	}

	void jwrite_visitor::visit(ptr_array_object& v)
	{
		stream.get() << '[';
		for (auto it = cbegin(v.value()); it != cend(v.value()); ++it)
		{
			(*it)->accept(*this);
			if (it + 1 != cend(v.value()))
			{
				stream.get() << ',';
			}
		}
		stream.get() << ']';
	}
}