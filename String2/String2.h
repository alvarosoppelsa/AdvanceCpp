#pragma once

typedef unsigned int size;

class string
{

public:
	string();
	string(const char* data);
	string(const string& string);
	string(string&& string) noexcept;
	~string();

	bool operator==(const string& string) const;
	string& operator=(const string& string);
	string& operator=(string&& string) noexcept;
	string operator+(const string& string) const;

	const size Length() const { return this->length; }
	void Clear();
	void printContent();

private:
	size strlen(const char* str);
	char* data;
	size length;
};

