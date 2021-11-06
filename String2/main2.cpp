// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "String2.h"
#include <cassert>

string GetMeAString() { return string("This is a string"); }

int main()
{
	string str1("String 1");
	str1.printContent();

	string	str2 = "String 2";
	str2.printContent();

	std::cout << "Copy str1 to str3\n";
	string str3 = str1;
	str3.printContent();

	std::cout << "Move str3 into str4\n";
	string str4 = std::move(str3);
	str3.printContent();
	str4.printContent();

	assert(str1 == str4);
	std::cout << "Equal strings!\n";

	assert(str4 == "String 1");
	std::cout << "Equal strings!\n";

	std::cout << "Get me a string function\n";
	string str5 = GetMeAString();	// Here is calling char* constructor. How could be improved?
	str5.printContent();
	std::cout << "Length: " << str5.Length() << "\n";

	std::cout << "Clear function\n";
	str5.Clear();
	str5.printContent();
}