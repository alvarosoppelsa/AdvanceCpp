#pragma once


class String
{
public:
	String();
	String(const String& b);
	String(String&& b);
	String(char&& b);
	~String();

private:
	char* str;
	int lenght;
};

