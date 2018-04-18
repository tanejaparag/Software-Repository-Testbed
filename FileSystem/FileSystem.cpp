/////////////////////////////////////////////////////////////////////////////
// FileSystem.cpp - Support file and directory operations                  //
// ver 2.7                                                                 //
// ----------------------------------------------------------------------- //
// copyright © Jim Fawcett, 2012                                           //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2010                             //
// Platform:    Dell XPS 8300, Core i7, Windows 7 SP1                      //
// Application: Summer Projects, 2012                                      //
// Author:      Jim Fawcett, CST 4-187, Syracuse University                //
//              (315) 443-3948, jfawcett@twcny.rr.com                      //
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <utility>
#include <clocale>
#include <locale>
#include "FileSystem.h"

using namespace FileSystem;


//----< test stub >--------------------------------------------------------

#ifdef TEST_FILESYSTEM

void title(const std::string& title, char ch = '=')
{
	std::cout << "\n  " << title;
	std::cout << "\n " << std::string(title.size() + 2, ch);
}
int main(int argc, char* argv[])
{
	title("Demonstrate Path Class");

	std::string fs = Path::fileSpec(".", "temp.txt");
	std::cout << "\n  Path::fileSpec(\".\",\"temp.txt\") = " << fs;

	std::string path = Path::getPath(fs);
	std::cout << "\n  Path::getPath(\"" + fs + "\") = " << path;

	std::string ffs = Path::getFullFileSpec(fs);
	std::cout << "\n  Path::getFullFileSpec(\"" + fs + "\") = " << ffs;

	std::string name = Path::getName(fs);
	std::cout << "\n  Path::getName(\"" + fs + "\") = " << name;

	std::string ext = Path::getExt(fs);
	std::cout << "\n  Path::getExt(\"" + fs + "\") = " << ext;

	std::string upper = Path::toUpper("temp.txt");
	std::cout << "\n  Path::toUpper(\"temp.txt\") = " << upper;

	std::string lower = Path::toLower("Temp.Txt");
	std::cout << "\n  Path::toLower(\"Temp.Txt\") = " << lower;
	std::cout << std::endl;
	
	std::cout << "\n\n";
	return 0;
}
#endif
