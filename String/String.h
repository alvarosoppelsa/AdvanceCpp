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
	String operator=(const String&& b) const;
	bool operator == (const String& b) const;

	void clear() { return str.clear(); }
	size_t lenght() const { return str.size(); }
	void printContent() const;

private:
	std::vector<char> str;
};

