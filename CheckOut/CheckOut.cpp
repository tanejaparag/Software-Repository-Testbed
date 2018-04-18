/////////////////////////////////////////////////////////////////////
// CheckOut.cpp -   Test stub for CheckOut Project                       //
// ver 1.0                                                         //
// Language:    C++, Visual Studio 2017                            //
// Parag Taneja, CSE687 - Object Oriented Design, Spring 2018   //
/////////////////////////////////////////////////////////////////////

/*

Class CheckOut : helps to checkout file and retunr to user.

Required Files:
* ---------------
* CheckOut.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 2 Mar 2018
*/




#include "CheckOut.h"

//This files has only ine test stub whcich is displayong class finctionality of request sent by a user to copy file from Code Repo to 
//to their local directory which takes key of DB element as a parametre.
#ifdef TEST_CHOUT

int main()
{
	std::vector<std::string> temp_vec;
	temp_vec.push_back("FileManager::FileMgr.h.2");
	std::string src = "../root";
	std::string dst = "../stage";
	CheckOut::copyFile(temp_vec, src,dst);
	std::getchar();
	return 0;
}

#endif