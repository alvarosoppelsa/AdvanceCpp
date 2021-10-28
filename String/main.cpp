// String.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "String.h"
#include <cassert>

String GetMeAString() { return String("This is a string"); }

int main()
{
    std::cout << "Construct from char* : \n";
    String string("Hello World!");
    string.printContent();
    
    std::cout << "Copy Constructor: \n";
    String string1(string);
    string1.printContent();

    std::cout << "Move Construct: \n";
    String string2(std::move(string));
    string2.printContent();

    assert((string1 == string2));
    if (string1 == string2)
    {
        std::cout << "Strings are equals!!\n";
    }

    String string3 = string1 + string2;
    string3.printContent();

    assert(!(string2 == string3));
    if (string3 == string2)
    {
        std::cout << "Strings shouldn't be equal!!\n";
    }
    else
    {
        std::cout << "Strings are different\n";
    }

    String string4("Hello World?");
    string4.printContent();
    assert(!(string4 == string2));
    if (string2 == string4)
    {
        std::cout << "Strings shouldn't be equal!!\n";
    }
    else
    {
        std::cout << "Strings are different\n";
    }

    String string5 = GetMeAString();
    string5.printContent();

    assert(string5 == "This is a string");
    if (string5 == "This is a string")
    {
        std::cout << "Strings are equals!!\n";
    }

    std::cout << "Lenght: " << string5.lenght() << "\n";
    std::cout << "Clear content: " <<  "\n";
    string5.clear();
    string5.printContent();
}

