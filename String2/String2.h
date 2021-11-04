#pragma once

typedef unsigned int size;

class String2
{

public:
	String2();
	String2(const char* data);
	String2(char*&& data) noexcept;
	String2(size int_size);
	String2(const String2& string);
	String2(String2&& string) noexcept;
	~String2();

	bool operator==(const String2& string) const;
	bool operator==(String2&& string) noexcept;
	String2& operator=(const String2& string);
	String2& operator=(String2&& string) noexcept;
	String2 operator+(const String2& string) const;

	const size Length() const { return this->length; }
	void Clear();
	void printContent();

private:
	size strlen(const char* str);
	char* data;
	size length;
};

