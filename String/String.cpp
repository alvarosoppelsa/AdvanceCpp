#include "String.h"

String::String()
{
	str = new char[1];
	str = '\0';
	lenght = 0;
}

String::String(const String& b)
{
	str = new char[sizeof(b.str)];
	str = b.str;
}

String::String(String&& b)
{
	str = b.str;
	b.str = nullptr;
}

String::String(char&& b)
{
	str = new char[(sizeof(b))];
	str = &b;
}

String::~String()
{
	delete str;
}
