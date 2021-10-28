#include "String.h"
#include <iostream>

String::String()
{
	str.push_back('\0');
}

String::String(const String& b)
{
	str = b.str;
}

String::String(String&& b) : str(b.str)
{
	b.clear();
}

String::String(const char* b)
{

	for (; *b != '\0'; ++b)
	{
		str.push_back(*b);
	}
}

String::~String()
{
}

String String::operator+(const String& b) const
{
	String retString(*this);
	for (auto it = b.str.begin(); it != b.str.end(); ++it)
	{
		retString.str.push_back(*it);
	}
	return retString;
}

bool String::operator==(const String& b) const
{
	bool equals = true;

	if (str.size() != b.str.size())
	{
		return false;
	}

	for (int i = 0; equals && i != str.size(); ++i)
	{
		if (str[i] != b.str[i])
		{
			equals = false;
		}
	}

	return equals;
}

void String::clear()
{
	str.clear();
}

size_t String::lenght() const
{
	return str.size();
}

void String::printContent() const
{
	for (auto it = str.begin(); it != str.end(); ++it)
	{
		std::cout << *it;
	}
	std::cout << "\n";
}
