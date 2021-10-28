#pragma once
#include <vector>


class String
{
public:
	String();
	String(const String& b);
	String(String&& b);
	String(const char* b);
	~String();

	// operator overloads
	String operator + (const String& b) const;
	bool operator == (const String& b) const;

	void clear();
	size_t lenght() const;
	void printContent() const;

private:
	std::vector<char> str;
};

