#include "String2.h"
#include <iostream>

string::string()
{
	length = 0;
	data = nullptr;
}

string::string(const char* str)
{
	std::cout << "Char* Constructor\n";

	length = strlen(str);
	data = new char[length + 1];
	memcpy(data, str, length + 1);
}

string::string(const string& str)
{
	std::cout << "Copy Constructor\n";

	length = str.length;
	data = new char[length + 1];
	memcpy(data, str.data, length + 1);
}

string::string(string&& str) noexcept
{
	std::cout << "Move Constructor\n";

	length = str.length;
	data = str.data;

	str.data = nullptr;
	str.length = 0;
}

string::~string()
{
	std::cout << "Destructor\n";
	delete data;
}

bool string::operator==(const string& str) const
{
	std::cout << "operator==\n";

	if (length != str.length)
	{
		return false;
	}
	for (size_t it = 0; it < length; ++it)
	{
		if (data[it] != str.data[it])
		{
			return false;
		}
	}
	return true;
}

string& string::operator=(const string& str)
{
	std::cout << "Assignment operator\n";

	delete[] data;
	length = str.length;
	data = new char[length + 1];
	memcpy(data, str.data, length + 1);
	return *this;
}

string& string::operator=(string&& str) noexcept
{
	std::cout << "Movement operator\n";

	if (this != &str)
	{
		delete[] data;

		data = str.data;
		length = str.length;

		str.data = nullptr;
		str.length = 0;
	}
	return *this;
}

string string::operator+(const string& str) const
{
	char* newString = new char[length + str.length + 1];
	std::copy_n(data, length, newString);
	std::copy_n(str.data, str.length + 1, newString + length);
	return string(newString);
}

void string::Clear()
{
	delete[] data;
	length = 0;
	data = nullptr;
}

void string::printContent()
{
	for (size it = 0; it < this->length; ++it)
	{
		std::cout << this->data[it];
	}
	std::cout << "\n";
}

inline size string::strlen(const char* str)
{
	size_t count = 0;
	while (*str != '\0')
	{
		++count;
		str++;
	}
	return count;
}
