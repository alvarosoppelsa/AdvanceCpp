#include "String2.h"
#include <iostream>

String2::String2()
{
	this->length = 1;
	this->data = new char[1];
	*this->data = '\0';
}

String2::String2(const char* str)
{
	this->length = strlen(str) + 1;
	this->data = new char[length];

	for (size it = 0; it < length; ++it)
	{
		this->data[it] = *str;
		str++;
	}
	data[length] = '\0';
}

String2::String2(size int_size)
{
	this->data = new char[int_size];
	this->length = int_size;
	for (size i = 0; i < int_size; ++i)
	{
		data[i] = '\0';
	}
}

String2::String2(const String2& string)
{
	this->length = string.length;
	this->data = new char[this->length];
	
	for (size it = 0; it < this->length; ++it)
	{
		this->data[it] = string.data[it];
	}
}

String2::String2(String2&& string)
{
	this->length = string.length;
	this->data = new char[this->length];
	this->data = string.data;
}

String2::~String2()
{
	if (data != nullptr)
	{
		delete[] data;
		data = nullptr;
	}
}

bool String2::operator==(const String2& string)
{
	if (this->length != string.length)
	{
		return false;
	}
	return true;
}

String2 String2::operator+(const String2& string)
{
	String2 retString(this->length + string.length - 1);
	for (size it = 0; it < this->length; ++it)
	{
		retString.data[it] = this->data[it];
	}
	for (size it = this->length; it < retString.length; ++it)
	{
		retString.data[it] = string.data[it - this->length];
	}
	retString.data[retString.length] = '\0';
	return retString;
}

void String2::Clear()
{
	delete[] this->data;
	this->length = 1;
	this->data = new char[this->length];
	this->data = '\0';
}

void String2::printContent()
{
	for (size it = 0; it < this->length; ++it)
	{
		std::cout << this->data[it];
	}
	std::cout << "\n";
}

size String2::strlen(const char* str)
{
	size_t count = 0;
	while (*str != '\0')
	{
		++count;
		str++;
	}
	return count;
}
