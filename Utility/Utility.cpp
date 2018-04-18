/////////////////////////////////////////////////////////////////////
// Utility.cpp -   Test stub for Utility Project                       //
// ver 1.0                                                         //
// Language:    C++, Visual Studio 2017                            //
// Parag Taneja, CSE687 - Object Oriented Design, Spring 2018   //
/////////////////////////////////////////////////////////////////////

/*

Class Utility : has function to replace the occurences of string.

Required Files:
* ---------------
* Utility.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 2 Mar 2018
*/

#include "Utility.h"

#ifdef TEST_UTILITY
int main()
{
	std::string temp_string = "I study OOD , I Pass OOD , Fawcett teaches OOD ";
	std::string temp_find = "OOD";
	std::string temp_replace = "SMA";
	Utility::replaceCheckOut(temp_string,temp_find,temp_replace);
	std::cout << "Instance of OOD is replaced by SMA\n\n";
	std::cout << temp_string;
	std::getchar();
	return 0;
}
#endif