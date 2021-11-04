// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "String2.h"
#include <cassert>

String2 GetMeAString() { return String2("This is a string"); }

int main()
{
	String2 str1("String 1");
	str1.printContent();

	String2	str2 = "String 2";
	str2.printContent();

	std::cout << "Copy str1 to str3\n";
	String2 str3 = str1;
	str3.printContent();

	std::cout << "Move str3 into str4\n";
	String2 str4 = std::move(str3);
	str3.printContent();
	str4.printContent();

	assert(str1 == str4);
	std::cout << "Equal strings!\n";

	assert(str4 == "String 1");
	std::cout << "Equal strings!\n";
}