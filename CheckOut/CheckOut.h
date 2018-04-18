#pragma once

////////////////////////////////////////////////////////////////////////////
// CheckOut.h - Has design of CheckOut which helps to checkout file and return to user.  //
// ver 1.0                                                                //
// Language:    C++, Visual Studio 2017                                  //
// Parag Taneja, CSE687 - Object Oriented Design, Spring 2018          //
///////////////////////////////////////////////////////////////////////////


/*
Package Operations:
* -------------------
* This package provides 1 class:
*
- CheckOut : helps to checkout file and retunr to user.

Public Functions :
static void copyFile(const std::vector<std::string> & param_vec,const std::string& srcrootpath, const std::string& destinationrootpath) - this 
functions copyfile from repo to to stage directory through which user can access.




* Required Files:
* ---------------
* FileMgr.h, Utility.h


*
*
* Maintenance History:
* --------------------
* ver 1.0 : 2nd Mar 2018

*/


#include<iostream>
#include<vector>
#include<algorithm>
#include "../FileMgr/FileMgr.h"
#include "../Utility/Utility.h"




class CheckOut
{

public:
	static void copyFile(const std::vector<std::string> & param_vec,const std::string& srcrootpath, const std::string& destinationrootpath);
};

//This function fins outs the file name from a key specifed by user and copies to a stage location acceessible by user.
void CheckOut::copyFile(const std::vector<std::string>& param_vec, const std::string& srcrootpath , const std::string& destinationrootpath)
{
	for (auto x : param_vec)
	{
		Utility::replaceCheckOut( x, "::", "/");
		std::string temp = srcrootpath + "/" + x;
		size_t indexoffile = x.find_last_of("/");
		std::string filename_ = x.substr(indexoffile + 1, x.size());
		size_t indexofdot = filename_.find_last_of(".");
		std::string dstfilename = filename_.substr(0, indexofdot);
		std::string temp1 = destinationrootpath + "/" + dstfilename;
		FileSystem::File::copy(temp, temp1, false); //Copying File to stage directory.
	}
}

