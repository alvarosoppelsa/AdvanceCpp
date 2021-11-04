#include "String2.h"
#include <iostream>

String2::String2()
{
	this->length = 0;
	this->data = new char;
	*this->data = '\0';
}

String2::String2(const char* str)
{
	std::cout << "Char Constructor\n";
	this->length = strlen(str);
	this->data = new char[length + 1];
	memcpy(data, str, length + 1);
}

String2::String2(char*&& str) noexcept
{
	std::cout << "Char Move Constructor\n";
	this->length = strlen(str);
	this->data = str;
}

String2::String2(size int_size)
{
	data = new char[int_size];
	length = int_size;
	for (size i = 0; i < int_size; ++i)
	{
		data[i] = '\0';
	}
}

String2::String2(const String2& string)
{
	std::cout << "Copy Constructor\n";
	length = string.length;
	data = new char[length + 1];
	memcpy(data, string.data, length + 1);
}

String2::String2(String2&& string) noexcept
{
	std::cout << "Move Constructor\n";

	length = string.length;
	data = string.data;

	string.data = nullptr;
	string.length = 0;
}

String2::~String2()
{
	std::cout << "Destructor";
	if (data != nullptr)
	{
		std::cout << " - data: " << data; 
		delete data;
	}
	std::cout << "\n";
}

bool String2::operator==(const String2& string) const
{
	std::cout << "Reference == operator\n";
	if (this->length != string.length)
	{
		return false;
	}
	for (size_t it = 0; it < this->length; ++it)
	{
		if (this->data[it] != string.data[it])
		{
			return false;
		}
	}
	return true;
}

bool String2::operator==(String2&& string) noexcept
{
	std::cout << "Movement == operator\n";
	if (this->length != string.length)
	{
		return false;
	}
	for (size_t it = 0; it < this->length; ++it)
	{
		if (this->data[it] != string.data[it])
		{
			return false;
		}
	}
	return true;
}

String2& String2::operator=(const String2& string)
{
	std::cout << "Assignment operator\n";
	delete[] data;
	length = string.length;
	data = new char[length + 1];
	memcpy(data, string.data, length + 1);
	return *this;
}

String2& String2::operator=(String2&& string) noexcept
{
	std::cout << "Movement operator\n";

	if (this != &string)
	{
		delete[] data;

		data = string.data;
		length = string.length;

		string.data = nullptr;
		string.length = 0;
	}
	return *this;
}

String2 String2::operator+(const String2& string) const
{
	char* newString = new char[length + string.length + 1];
	std::copy_n(data, length, newString);
	std::copy_n(string.data, string.length + 1, newString + length);
	return String2(newString);
}

void String2::Clear()
{
	delete[] data;
	length = 0;
	data = nullptr;
}

void String2::printContent()
{
	for (size it = 0; it < this->length; ++it)
	{
		std::cout << this->data[it];
	}
	std::cout << "\n";
}

inline size String2::strlen(const char* str)
{
	size_t count = 0;
	while (*str != '\0')
	{
		++count;
		str++;
	}
	return count;
}
