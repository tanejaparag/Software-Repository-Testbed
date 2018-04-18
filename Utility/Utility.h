#pragma once
////////////////////////////////////////////////////////////////////////////
// Utility.h - Has a function to replace a string from a given string  //
// ver 1.0                                                                //
// Language:    C++, Visual Studio 2017                                  //
// Parag Taneja, CSE687 - Object Oriented Design, Spring 2018          //
///////////////////////////////////////////////////////////////////////////


/*
Package Operations:
* -------------------
* This package provides 1 class:
*
- Utility : replaces all the string occcurence from a given string.

Public Functions :
static void replaceCheckOut(std::string& source, std::string const& find, std::string const& replac) - 
It replaces all the string occcurence from a given string.

* Required Files:
* ---------------


*
*
* Maintenance History:
* --------------------
* ver 1.0 : 2nd Mar 2018

*/



#include <iostream>
#include <string>


class Utility
{
public:
	static void replaceCheckOut(std::string& source, std::string const& find, std::string const& replac);
};

//replaces all the string occcurence from a given string
inline void Utility::replaceCheckOut(std::string& source, std::string const& find, std::string const& replace)
{
	size_t i = 0;
	i = source.find(find, i);
	for (size_t x = i; x != std::string::npos;)
	{
		source.replace(x, find.length(), replace); //replacin function
		x += replace.length();
		x = source.find(find, x);

	}
}
