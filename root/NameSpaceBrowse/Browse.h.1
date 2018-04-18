#pragma once

////////////////////////////////////////////////////////////////////////////
// Browse.h - Has design of Browse helps to browse file depednign on categoey and FileNAme.  //
// ver 1.0                                                                //
// Language:    C++, Visual Studio 2017                                  //
// Parag Taneja, CSE687 - Object Oriented Design, Spring 2018          //
///////////////////////////////////////////////////////////////////////////


/*
Package Operations:
* -------------------
* This package provides 1 class:
*
- Browse : helps to browse file depednign on categoey and FileNAme.

Public Functions :
static void browseByCategory(DbCore<T> & db , std::string &category, std::vector<std::string> & vec) - Query DB using lambda to find out all keys which has that particular category in them.
static std::string browseBySpecificName(std::string file_key , const std::string & srcrootpath, const std::string& stagefolder) - Create the destination path depending on the information provided by user.
static void  viewContentinNotepad(std::string& filepath) - Open the file in Notepad.



* Required Files:
* ---------------
* Executive.h, FileSystem.h
* Utility.h ,Process.h

*
*
* Maintenance History:
* --------------------
* ver 1.0 : 2nd Mar 2018

*/

#include <iostream>

#include "../NoSQLDB/Executive/Executive.h"
#include "../FileSystem/FileSystem.h"
#include "../Utility/Utility.h"
#include "../Process/Process.h"

using namespace NoSqlDb;

template<typename T>
class Browse
{
public:
	static void browseByCategory(DbCore<T> & db , std::string &category, std::vector<std::string> & vec);
	static std::string browseBySpecificName(std::string file_key , const std::string & srcrootpath, const std::string& stagefolder);
	static void  viewContentinNotepad(std::string& filepath);
};

template<typename T>
//Query DB using lambda to find out all keys which has that particular category in them.
inline void Browse<T>::browseByCategory(DbCore<T>& db, std::string & category, std::vector<std::string> & vec)
{
	vec.clear();
	Query<T> q1(db);
	auto hasCategory = [&category](DbElement<PayLoad>& elem) {
		return (elem.payLoad()).hasCategory(category);
	};
	vec =  q1.select(hasCategory).keys(); //Querying DB on basis of query.
}

template<typename T>
//Create the destination path depending on the information provided by user.
inline std::string Browse<T>::browseBySpecificName(std::string  file_key, const std::string& srcrootpath ,const std::string& stagefolder)
{
	Utility::replaceCheckOut(file_key, "::", "/");
	std::string temp = srcrootpath + "/" + file_key;
	size_t indexoffile = file_key.find_last_of("/");
	std::string filename_ = file_key.substr(indexoffile + 1, file_key.size());
	size_t indexofdot = filename_.find_last_of(".");
	std::string dstfilename = filename_.substr(0, indexofdot);
	std::string temp1 = stagefolder + "/" + dstfilename;
	FileSystem::File::copy(temp, temp1, false); //copy file from src to destination
	return temp1;
}

template<typename T>
//Open the file in Notepad.
inline void Browse<T>::viewContentinNotepad(std::string & filepath)
{
	Process p; //Use the PRocess Class
	std::string appPath = "c:/windows/system32/notepad.exe";
	p.application(appPath);

	std::string cmdLine = "/A " + filepath;
	p.commandLine(cmdLine); //Pass the commadn line to Process.

	std::cout << "\n  starting process: \"" << appPath << "\"";
	std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
	p.create();

	CBP callback = []() { std::cout << "\n  --- child process exited with this message ---"; };
	p.setCallBackProcessing(callback);
	p.registerCallback();

	std::cout << "\n  after OnExit";
	std::cout.flush();
	char ch;
	std::cin.read(&ch, 1);
}


